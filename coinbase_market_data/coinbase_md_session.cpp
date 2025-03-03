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
                    Side side = Side::UNKNOWN;
                    if (type == '0') {
                        side = Side::BID;
                    }
                    if (type == '1') {
                        side = Side::ASK;
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
                for(const auto& group: groups) {
                    Side side = Side::UNKNOWN;
                    auto type = group. template get<FIX::Tag::MDEntryType>();
                    if (type == '0') {
                        side = Side::BID;
                    }
                    if (type == '1') {
                        side = Side::ASK;
                    }
                    if (side != Side::UNKNOWN) {
                        auto update_action = group.get<FIX::Tag::MDUpdateAction>();
                        auto symbol = group.get<FIX::Tag::Symbol>();
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