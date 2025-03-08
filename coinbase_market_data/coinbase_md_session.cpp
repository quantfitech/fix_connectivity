#include "coinbase_md_session.hpp"
#include "v50sp2/messages.hpp"
#include "version_selector.hpp"

namespace quantfi { namespace coinbase_md {


    template <Version V>
    void CoinbaseMdSession<V>::onMessage(char msgType, TokenIterator& fixIter) 
    {
        switch(msgType)
        {
            case FIX::MsgType::Logon:
            {
                Header header;
                this->fillHeader(header);
                v50sp2::Message::SecurityListRequest securityList(&header);
                securityList.set<FIX::Tag::SecurityReqID>("unique_request_id");
                securityList.set<FIX::Tag::SecurityListRequestType>(4);
                this->send(securityList, encode_options::standard);
                break;
            }
            case FIX::MsgType::SecurityList:
            {
                Header header;
                v50sp2::Message::SecurityList securityList(&header);
                securityList.deserialize(fixIter);
                auto toRelSymbols = securityList.get<FIX::Tag::TotNoRelatedSym>();
                auto groups = securityList.getGroups<FIX::Tag::NoRelatedSym>();
                for( auto & group : groups) {
                    auto symbol = group.get<FIX::Tag::Symbol>();
                    auto minpxincr = group.get<FIX::Tag::MinPriceIncrement>();
                    auto currency = group.get<FIX::Tag::Currency>();
                    auto mintrdvol = group.get<FIX::Tag::MinTradeVol>();
                    auto maxtrdvol = group.get<FIX::Tag::MaxTradeVol>();
                    auto roundLot = group.get<FIX::Tag::RoundLot>();
                    LOG_DEBUG(" symbol {} inc {} curr {} mintv{} maxtv {} round{}", symbol, minpxincr, currency, mintrdvol, maxtrdvol, roundLot);
                }
                auto lastFragment = securityList.get<FIX::Tag::LastFragment>();
                LOG_DEBUG("recv tot symbols {} last {}", toRelSymbols, lastFragment);
                if (lastFragment) {
                    Header header;
                    this->fillHeader(header);
                    v50sp2::Message::MarketDataRequest mdRequest(&header);
                    mdRequest.set<FIX::Tag::MDReqID>("unique_market_data_id");
                    mdRequest.set<FIX::Tag::SubscriptionRequestType>('1');
                    mdRequest.set<FIX::Tag::MarketDepth>(20);
                    this->send(mdRequest, encode_options::standard);
                    break;
                }
                break;
            }
            case FIX::MsgType::SecurityDefinition:
            {
                Header header;
                v50sp2::Message::SecurityDefinition securityDefinition(&header);
                securityDefinition.deserialize(fixIter);
                auto symbol = securityDefinition.get<FIX::Tag::Symbol>();
                auto type = securityDefinition.get<FIX::Tag::SecurityType>();
                LOG_DEBUG("recv sec def {} last {}", symbol, type);
                break;
            }
            case FIX::MsgType::MarketDataSnapshotFullRefresh:
            {
                Header header;
                v50sp2::Message::MarketDataSnapshot snapshot(&header);
                snapshot.deserialize(fixIter);
                auto symbol = snapshot.get<FIX::Tag::Symbol>();
                auto groups = snapshot.getGroups<FIX::Tag::NoMDEntries>();
                LOG_DEBUG("recv w {} groups {}", symbol, groups.size());
                for(const auto& group: groups) {
                    auto type = group. template get<FIX::Tag::MDEntryType>();
                    LOG_DEBUG(" TYPE {}", type);
                    Side side = Side::UNKNOWN;
                    if (type == '0') {
                        side = Side::BID;
                    }
                    else if (type == '1') {
                        side = Side::ASK;
                    }
                    else if (type == '2') {
                        auto px = group. template get<FIX::Tag::MDEntryPx>();
                        LOG_DEBUG("trade {} px {} ", symbol, px);
                    }
                    else if (type == '3') {
                        auto px = group. template get<FIX::Tag::MDEntryPx>();
                        LOG_DEBUG("index {} px {} ", symbol, px);
                    }
                    else if (type == '4') {
                        auto px = group. template get<FIX::Tag::MDEntryPx>();
                        LOG_DEBUG("opening {} px {} ", symbol, px);
                    }
                    else if (type == '6') {
                        auto px = group. template get<FIX::Tag::MDEntryPx>();
                        LOG_DEBUG("settlmnt {} px {} ", symbol, px);
                    }
                    else if (type == 'm') {
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
                        book.addOrAmendLevel(side, level, px, size, "");
                    }
                }
                mOrderBookManager.books[symbol].print(symbol);
                break;
            }
            case FIX::MsgType::MarketDataIncrementalRefresh:
            {
                Header header;
                v50sp2::Message::MarketDataIncrementalRefresh incremental(&header);
                incremental.deserialize(fixIter);
                auto groups = incremental.getGroups<FIX::Tag::NoMDEntries>();
                LOG_DEBUG("recv X groups {}", groups.size());
                for(const auto& group: groups) {
                    Side side = Side::UNKNOWN;
                    auto type = group. template get<FIX::Tag::MDEntryType>();
                    auto symbol = group.get<FIX::Tag::Symbol>();
                    LOG_DEBUG(" TYPE {}", type);
                    if (type == '0') {
                        side = Side::BID;
                    }
                    else if (type == '1') {
                        side = Side::ASK;
                    }
                    else if (type == '2') {
                        auto px = group. template get<FIX::Tag::MDEntryPx>();
                        LOG_DEBUG("trade {} px {} ", symbol, px);
                    }
                    else if (type == '3') {
                        auto px = group. template get<FIX::Tag::MDEntryPx>();
                        LOG_DEBUG("index {} px {} ", symbol, px);
                    }
                    else if (type == '4') {
                        auto px = group. template get<FIX::Tag::MDEntryPx>();
                        LOG_DEBUG("opening {} px {} ", symbol, px);
                    }
                    else if (type == '6') {
                        auto px = group. template get<FIX::Tag::MDEntryPx>();
                        LOG_DEBUG("settlmnt {} px {} ", symbol, px);
                    }
                    else if (type == 'm') {
                        auto px = group. template get<FIX::Tag::MDEntryPx>();
                        LOG_DEBUG("mark {} px {} ", symbol, px);
                    }
                    if (side != Side::UNKNOWN) {
                        auto update_action = group.get<FIX::Tag::MDUpdateAction>();
                        //auto symbol = group.get<FIX::Tag::Symbol>();
                        if (update_action == '2') {
                            auto px = group. template get<FIX::Tag::MDEntryPx>();
                            OrderBook& book = mOrderBookManager.getBook(symbol);
                            book.deleteLevel(side, px);
                        } else {
                            auto level = group. template get<FIX::Tag::MDPriceLevel>();
                            auto px = group. template get<FIX::Tag::MDEntryPx>();
                            auto size = group. template get<FIX::Tag::MDEntrySize>();
                            auto tstamp = group. template get<FIX::Tag::TransactTime>();
                            OrderBook& book = mOrderBookManager.getBook(symbol);
                            LOG_DEBUG("{} pxlevel {} px {}", symbol, level, px);
                            book.addOrAmendLevel(side, level, px, size, "");
                        }
                        mOrderBookManager.books[symbol].print(symbol);
                    }
                }
                break;
            }
        }       
    } 

    template class CoinbaseMdSession<Version::v50sp2>;
}
}