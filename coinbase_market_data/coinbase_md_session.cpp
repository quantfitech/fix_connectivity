#include "coinbase_md_session.hpp"
#include "v50sp2/messages.hpp"
#include "version_selector.hpp"
#include "fix_values.hpp"

namespace qfapp { namespace coinbase_md {


    template <Version V>
    void CoinbaseMdSession<V>::onMessage(const MsgChars& msgType, TokenIterator& fixIter) 
    {
        if (msgType == FIX::MsgType::Logon)
        {
            Header header;
            this->fillHeader(header);
            v50sp2::Message::SecurityListRequest securityList(&header);
            securityList.set<FIX::Tag::SecurityReqID>("unique_request_id");
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
                }
                if (type == Values::MDEntryType::Offer) {
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

            Header header1;
            this->fillHeader(header1);
            v50sp2::Message::MarketDataRequest mdRequest(&header1);
            mdRequest.set<FIX::Tag::MDReqID>("unique_market_data_id");
            mdRequest.set<FIX::Tag::SubscriptionRequestType>(Values::SubscriptionRequestType::SnapshotAndUpdates);
            mdRequest.set<FIX::Tag::MarketDepth>(20);
            auto& gr = mdRequest.createGroup<FIX::Tag::NoRelatedSym>();
            gr.set<FIX::Tag::Symbol>("BTC-PERP");
            gr.set<FIX::Tag::SecurityType>("PERP");
            this->send(mdRequest, encode_options::standard);
        }
        else if (msgType == FIX::MsgType::MarketDataIncrementalRefresh)
        {
            Header header;
            v50sp2::Message::MarketDataIncrementalRefresh incremental(&header);
            incremental.deserialize(fixIter);
            auto groups = incremental.getGroups<FIX::Tag::NoMDEntries>();
            for(const auto& group: groups) {
                Side side = Side::UNKNOWN;
                auto type = group. template get<FIX::Tag::MDEntryType>();
                if (type == Values::MDEntryType::Bid) {
                    side = Side::BID;
                }
                if (type == Values::MDEntryType::Offer) {
                    side = Side::ASK;
                }
                if (side != Side::UNKNOWN) {
                    auto update_action = group.get<FIX::Tag::MDUpdateAction>();
                    auto symbol = group.get<FIX::Tag::Symbol>();
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
                        book.addOrAmendLevel(side, level, px, size, "");
                    }
                    mOrderBookManager.books[symbol].print(symbol);
                }
            }
        }
   
    } 

    template class CoinbaseMdSession<Version::v50sp2>;
}
}