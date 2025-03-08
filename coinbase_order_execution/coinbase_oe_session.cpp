#include "coinbase_oe_session.hpp"
#include "v50sp2/messages.hpp"
#include "version_selector.hpp"
#include <cstdlib>

namespace quantfi { namespace coinbase_md {

    template <Version V>
    void CoinbaseMdSession<V>::sendQuote(const std::string& symbol){
        Header header;
        this->fillHeader(header);
        v50sp2::Message::NewOrderSingle neworder(&header);

        counter++;
        auto clorderid = "Clordid" + std::to_string(counter);
        neworder.set<FIX::Tag::ClOrdID>(clorderid);

        auto& party = neworder.createGroup<FIX::Tag::NoPartyIDs>();
        party.set<FIX::Tag::PartyID>("01939cc7-253c-70d0-ba54-b34b418839df");
        party.set<FIX::Tag::PartyRole>(24);
        neworder.set<FIX::Tag::ExecInst>("6");
        neworder.set<FIX::Tag::OrderQty>(1);
        neworder.set<FIX::Tag::OrdType>('2');

        neworder.set<FIX::Tag::Price>(px - 0.2);

        neworder.set<FIX::Tag::Side>('1'); //buy
        neworder.set<FIX::Tag::Symbol>(symbol);
        neworder.set<FIX::Tag::TimeInForce>('1');
      
        LOG_INFO("sending bid clordid {}", neworder.get<FIX::Tag::ClOrdID>());
        this->send(neworder, encode_options::standard);

        counter++;
        clorderid = "Clordid" + std::to_string(counter);
        neworder.set<FIX::Tag::ClOrdID>(clorderid);
        neworder.set<FIX::Tag::Price>(px + 0.20);
        neworder.set<FIX::Tag::Side>('2'); //sell

        LOG_INFO("sending ask clordid {}", neworder.get<FIX::Tag::ClOrdID>());
        this->send(neworder, encode_options::standard);

        mClordIds[symbol] = std::make_pair(counter-1, counter);
    }

    template <Version V>
    void CoinbaseMdSession<V>::updateQuote(const std::string& symbol){
        Header header;
        this->fillHeader(header);
        v50sp2::Message::OrderCancelReplaceRequest orderRplc(&header);

        counter++;
        auto clorderid = "Clordid" + std::to_string(counter);
        orderRplc.set<FIX::Tag::ClOrdID>(clorderid);

        auto& party = orderRplc.createGroup<FIX::Tag::NoPartyIDs>();
        party.set<FIX::Tag::PartyID>("01939cc7-253c-70d0-ba54-b34b418839df");
        party.set<FIX::Tag::PartyRole>(24);


        orderRplc.set<FIX::Tag::OrigClOrdID>("Clordid" + std::to_string(mClordIds[symbol].first));
        orderRplc.set<FIX::Tag::OrderQty>(1);
        orderRplc.set<FIX::Tag::Price>(px - 0.2);
        orderRplc.set<FIX::Tag::Symbol>(symbol);

        LOG_INFO("update bid clordid {}", orderRplc.get<FIX::Tag::ClOrdID>(), orderRplc.get<FIX::Tag::OrigClOrdID>());
        
        this->send(orderRplc, encode_options::standard);

        counter++;
        clorderid = "Clordid" + std::to_string(counter);
        orderRplc.set<FIX::Tag::ClOrdID>(clorderid);
        orderRplc.set<FIX::Tag::OrigClOrdID>("Clordid" + std::to_string(mClordIds[symbol].second));
        orderRplc.set<FIX::Tag::Price>(px + 0.20);

        LOG_INFO("update ask clordid {} orig {}", orderRplc.get<FIX::Tag::ClOrdID>(), orderRplc.get<FIX::Tag::OrigClOrdID>());
        
        this->send(orderRplc, encode_options::standard);

         mClordIds[symbol] = std::make_pair(counter-2, counter-1);
    }

    template <Version V>
    void CoinbaseMdSession<V>::cancelQuote(const std::string& symbol){
        Header header;
        this->fillHeader(header);
        v50sp2::Message::OrderCancelRequest cancelReq(&header);

        counter++;
        auto clorderid = "Clordid" + std::to_string(counter);
        cancelReq.set<FIX::Tag::ClOrdID>(clorderid);

        auto& party = cancelReq.createGroup<FIX::Tag::NoPartyIDs>();
        party.set<FIX::Tag::PartyID>("01939cc7-253c-70d0-ba54-b34b418839df");
        party.set<FIX::Tag::PartyRole>(24);


        cancelReq.set<FIX::Tag::OrigClOrdID>("Clordid" + std::to_string(mClordIds[symbol].first));
        cancelReq.set<FIX::Tag::Symbol>(symbol);

        LOG_INFO("update bid clordid {}", cancelReq.get<FIX::Tag::ClOrdID>(), cancelReq.get<FIX::Tag::OrigClOrdID>());
        
        this->send(cancelReq, encode_options::standard);

        counter++;
        clorderid = "Clordid" + std::to_string(counter);
        cancelReq.set<FIX::Tag::ClOrdID>(clorderid);
        cancelReq.set<FIX::Tag::OrigClOrdID>("Clordid" + std::to_string(mClordIds[symbol].second));

        LOG_INFO("update ask clordid {} orig {}", cancelReq.get<FIX::Tag::ClOrdID>(), cancelReq.get<FIX::Tag::OrigClOrdID>());
        
        this->send(cancelReq, encode_options::standard);

         mClordIds[symbol] = std::make_pair(counter-2, counter-1);
    }

    template <Version V>
    void CoinbaseMdSession<V>::onTime() {
     
        // Generate a random index
        int randomIndex = std::rand() % values.size();

        // Get the random element
        int randomValue = values[randomIndex];
        px += randomValue;

        if (mClordIds["TRUMP-PERP"].first == mClordIds["TRUMP-PERP"].second) {
            sendQuote("TRUMP-PERP");
        } else {
            updateQuote("TRUMP-PERP");
        }
    }

    template <Version V>
    void CoinbaseMdSession<V>::massCancel() {
         Header headerMass;
        this->fillHeader(headerMass);
        v50sp2::Message::OrderMassCancelRequest masscancel(&headerMass);
        masscancel.set<FIX::Tag::ClOrdID>("Clordid" + std::to_string(counter++));
        this->send(masscancel, encode_options::standard);
    }

    template <Version V>
    void CoinbaseMdSession<V>::onMessage(char msgType, TokenIterator& fixIter) 
    {
        switch(msgType)
        {
            case FIX::MsgType::Logon:
            {                
                sendQuote("TRUMP-PERP");
                updateQuote("TRUMP-PERP");
                cancelQuote("TRUMP-PERP");

                mTimer = std::make_shared<RecurringTimer>(std::chrono::seconds(2), [this]() { onTime(); }, "msgseqout");
                this->addRecurringTimer(mTimer);
                break;
            }
            case FIX::MsgType::BusinessMessageReject: 
            {
                Header header;
                v50sp2::Message::BusinessMessageReject businessreject(&header);
                businessreject.deserialize(fixIter);

                massCancel();
            }
            case FIX::MsgType::ExecutionReport:
            {
                Header header;
                v50sp2::Message::ExecutionReport execreport(&header);
                execreport.deserialize(fixIter);
                auto extt = execreport.get<FIX::Tag::ExecTransType>();
                auto exectype = execreport.get<FIX::Tag::ExecType>();
                auto symbol = execreport.get<FIX::Tag::Symbol>();
                auto ordId = execreport.get<FIX::Tag::OrderID>();
                auto orddstat = execreport.get<FIX::Tag::OrdStatus>();
                auto ordqty= execreport.get<FIX::Tag::OrderQty>();
                auto ordpx = execreport.get<FIX::Tag::Price>();
                auto ordleaves = execreport.get<FIX::Tag::LeavesQty>();
                if (exectype == '8') {
                    LOG_DEBUG("clordid {} is rejected", execreport.get<FIX::Tag::ClOrdID>());
                    massCancel();
                } else if (exectype == '2') {
                    LOG_DEBUG("clordid {} is filled", execreport.get<FIX::Tag::ClOrdID>());
                    mClordIds[symbol] = std::pair(0,0);
                } else if (exectype == '4') {
                    LOG_DEBUG("clordid {} is cancelled", execreport.get<FIX::Tag::ClOrdID>());
                    mClordIds[symbol] = std::pair(0,0);
                }
                LOG_INFO("exec report {} {} {} id {} stat {} qty {} px {} leaves {} ", execreport.get<FIX::Tag::Symbol>(), extt, exectype, ordId, orddstat, ordqty, ordpx, ordleaves);

                break;
            }
        }       
    } 

    template class CoinbaseMdSession<Version::v50sp2>;
}
}