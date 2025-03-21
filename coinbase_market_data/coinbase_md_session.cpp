#include "coinbase_md_session.hpp"
#include "v50sp2/messages.hpp"
#include "version_selector.hpp"
#include "fix_values.hpp"
#include <nlohmann/json.hpp>

namespace qfapp { namespace coinbase_md {

    int64_t utcTsToInt64(const FIX::UTCTimestamp& tstamp) {
        return static_cast<int64_t>(std::chrono::duration_cast<std::chrono::milliseconds>(tstamp.time_since_epoch()).count());
    }

    template <Version V>
    void CoinbaseMdSession<V>::onSessionConnected() {

    }

    template <Version V>
    std::string CoinbaseMdSession<V>::generateUniqueRequestId() {
        auto t = std::time(nullptr);
        auto tm = *std::localtime(&t);
        std::stringstream ss;
        ss << "req_" << std::put_time(&tm, "%Y%m%d-%H.%M.%S") << ++mCounter;
        return ss.str();
    }

    template <Version V>
    void CoinbaseMdSession<V>::publishTradeTick(const std::string&symbol, double price, double size, int64_t tstamp, std::string&& aggSide) {
        if (mRedis) {
            json j;
            j["symbol"] = symbol;
            j["price"] = price;
            j["size"] = size;
            j["aggressorSide"] = std::move(aggSide);
            j["timestamp"] = tstamp;
            mRedis->publishTradeTick(j.dump());
        }
    }

    template <Version V>
    void CoinbaseMdSession<V>::publishPrices(const std::string& symbol) {
        OrderBook& book = mOrderBookManager.getBook(symbol);
        if (mRedis) {
            auto bboj = book.orderBookAsJson(symbol);
            mRedis->publishPrice(symbol.c_str(), bboj.dump());
        }
    }

    template <Version V>
    void CoinbaseMdSession<V>::onMessage(const MsgChars& msgType, TokenIterator& fixIter) 
    {
        if (msgType == FIX::MsgType::Logon)
        {
            Header header;
            this->fillHeader(header);
            v50sp2::Message::SecurityListRequest securityList(&header);
            securityList.set<FIX::Tag::SecurityReqID>(generateUniqueRequestId());
            securityList.set<FIX::Tag::SecurityListRequestType>(Values::SecurityListRequestType::AllSecurities);
            this->send(securityList, encode_options::standard);
        }
        else if (msgType == FIX::MsgType::SecurityList)
        {
            Header header;
            v50sp2::Message::SecurityList securityList(&header);
            securityList.deserialize(fixIter);
            auto toRelSymbols = securityList.get<FIX::Tag::TotNoRelatedSym>();
            auto lastFragment = securityList.get<FIX::Tag::LastFragment>();
            LOG_DEBUG("recv tot symbols {} last {}", toRelSymbols, lastFragment);
            if (lastFragment) {
                Header header;
                this->fillHeader(header);
                v50sp2::Message::MarketDataRequest mdRequest(&header);
                mdRequest.set<FIX::Tag::MDReqID>("unique_market_data_id");
                mdRequest.set<FIX::Tag::SubscriptionRequestType>(Values::SubscriptionRequestType::SnapshotAndUpdates);
                mdRequest.set<FIX::Tag::MarketDepth>(20);
                this->send(mdRequest, encode_options::standard);
            }
        }
        else if (msgType == FIX::MsgType::SecurityDefinition)
        {
            Header header;
            v50sp2::Message::SecurityDefinition securityDefinition(&header);
            securityDefinition.deserialize(fixIter);
            auto symbol = securityDefinition.get<FIX::Tag::Symbol>();
            auto type = securityDefinition.get<FIX::Tag::SecurityType>();
            LOG_DEBUG("recv sec def {} last {}", symbol, type);
        }
        else if (msgType == FIX::MsgType::MarketDataSnapshotFullRefresh)
        {
            Header header;
            v50sp2::Message::MarketDataSnapshot snapshot(&header);
            snapshot.deserialize(fixIter);
            auto symbol = snapshot.get<FIX::Tag::Symbol>();
            auto groups = snapshot.getGroups<FIX::Tag::NoMDEntries>();
            LOG_DEBUG("recv w {} groups {}", symbol, groups.size());
            for(const auto& group: groups) {
                auto type = group. template get<FIX::Tag::MDEntryType>();
                Side side = Side::UNKNOWN;
                if (type == Values::MDEntryType::Bid) {
                    side = Side::BID;
                } else if (type == Values::MDEntryType::Offer) {
                    side = Side::ASK;
                } else if (type == Values::MDEntryType::Trade) {
                    publishTradeTick( symbol, group. template get<FIX::Tag::MDEntryPx>(), group. template get<FIX::Tag::MDEntrySize>(),
                                     utcTsToInt64(group. template get<FIX::Tag::TransactTime>()),
                                     (group. template get<FIX::Tag::AggressorSide>() == Values::AggressorSide::Buy) ? "buy" : "sell" );
                } else if (type == Values::MDEntryType::IndexValue) {
                    auto px = group. template get<FIX::Tag::MDEntryPx>();
                    LOG_DEBUG("index {} px {} ", symbol, px);
                }
                else if (type == Values::MDEntryType::OpeningPrice) {
                    auto px = group. template get<FIX::Tag::MDEntryPx>();
                    LOG_DEBUG("opening {} px {} ", symbol, px);
                }
                else if (type == Values::MDEntryType::SettlementPrice) {
                    auto px = group. template get<FIX::Tag::MDEntryPx>();
                    LOG_DEBUG("settlmnt {} px {} ", symbol, px);
                }
                else if (type == Values::MDEntryType::MarkPrice) {
                    auto px = group. template get<FIX::Tag::MDEntryPx>();
                    LOG_DEBUG("mark {} px {} ", symbol, px);
                }
                if (side != Side::UNKNOWN) {
                    auto level = group. template get<FIX::Tag::MDPriceLevel>();
                    auto px = group. template get<FIX::Tag::MDEntryPx>();
                    auto size = group. template get<FIX::Tag::MDEntrySize>();
                    auto tstamp = group. template get<FIX::Tag::TransactTime>();
                    LOG_DEBUG("recv w {} {} {}", level, px, size);
                    OrderBook& book = mOrderBookManager.getBook(symbol);
                    book.addOrAmendLevel(side, level, px, size, utcTsToInt64(tstamp));
                }
            }
            publishPrices(symbol);
        }
        else if (msgType == FIX::MsgType::MarketDataIncrementalRefresh)
        {
            Header header;
            v50sp2::Message::MarketDataIncrementalRefresh incremental(&header);
            incremental.deserialize(fixIter);
            std::string last_symbol{""};
            auto groups = incremental.getGroups<FIX::Tag::NoMDEntries>();
            for(const auto& group: groups) {
                Side side = Side::UNKNOWN;
                auto type = group. template get<FIX::Tag::MDEntryType>();
                if (type == Values::MDEntryType::Bid) {
                    side = Side::BID;
                }
                else if (type == Values::MDEntryType::Offer) {
                    side = Side::ASK;
                }
                else if (type == Values::MDEntryType::Trade) {
                    auto symbol = group.get<FIX::Tag::Symbol>();
                     publishTradeTick( symbol, group. template get<FIX::Tag::MDEntryPx>(), group. template get<FIX::Tag::MDEntrySize>(),
                                      utcTsToInt64(group. template get<FIX::Tag::TransactTime>()),
                                      (group. template get<FIX::Tag::AggressorSide>() == Values::AggressorSide::Buy) ? "buy" : "sell" );
                }
                if (side != Side::UNKNOWN) {
                    auto update_action = group.get<FIX::Tag::MDUpdateAction>();
                    auto symbol = group.get<FIX::Tag::Symbol>();
                    last_symbol = symbol;
                    if (update_action == Values::MDUpdateAction::Delete) {
                        auto px = group. template get<FIX::Tag::MDEntryPx>();
                        OrderBook& book = mOrderBookManager.getBook(symbol);
                        book.deleteLevel(side, px);
                    } else {
                        auto level = group. template get<FIX::Tag::MDPriceLevel>();
                        auto px = group. template get<FIX::Tag::MDEntryPx>();
                        auto size = group. template get<FIX::Tag::MDEntrySize>();
                        auto tstamp = group. template get<FIX::Tag::TransactTime>();
                        OrderBook& book = mOrderBookManager.getBook(symbol);
                        book.addOrAmendLevel(side, level, px, size, utcTsToInt64(tstamp));
                    }
                }
            }
            if (!last_symbol.empty()) {
                publishPrices(last_symbol);
            }
        } else if (msgType == FIX::MsgType::MarketDataRequestReject) {
            Header header;
            v50sp2::Message::MarketDataRequestReject reject(&header);
            reject.deserialize(fixIter);
            LOG_ERROR("md rejection: reason {} text {}", 
                reject.get<FIX::Tag::MDReqRejReason>(), reject.get<FIX::Tag::Text>());
            this->stop("rejection received");
        }
   
    } 

    template class CoinbaseMdSession<Version::v50sp2>;
}
}