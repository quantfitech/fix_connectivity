#include "ssl_client_connection.hpp"
#include "logger.hpp"
#include "session.hpp"
#include "event_manager.hpp"

#include "client_connection.hpp"
#include "ssl_socket.hpp"

#include "application.hpp"
#include "app_options.hpp"
#include "logger_options.hpp"
#include "session_interface.hpp"
#include "message.hpp"
#include "tag.hpp"

#include "order_book.hpp"

#define SERVER_IP "3.114.19.227" // Change to the server's IP address
#define SERVER_PORT 6120         // Change to the server's port number
#define BUFFER_SIZE 8192

using namespace qfapp;
    using namespace qffixlib;

    class MySession : public SessionInterface {
    public:
        virtual ~MySession() {};
        void onConnected() {}
        void onDisconnected() {}
        void onMessage(const qffixlib::Message& msg) 
        {
            if (msg.MsgType() == FIX::MsgType::Logon) {
                 auto securityListRequest = Message(true, {
                        Field( FIX::Tag::MsgType, FIX::MsgType::SecurityListRequest),                        
                        Field( FIX::Tag::SecurityReqID, "unique_request_id"),
                        Field( FIX::Tag::SecurityListRequestType, "4")
                    });
                session->send(securityListRequest);
            }

            if (msg.MsgType() == FIX::MsgType::SecurityList) {
                auto request_id = msg.fields().try_get_or_default(FIX::Tag::SecurityReqID, "");
                auto result = msg.fields().try_get_or_default(FIX::Tag::SecurityRequestResult, "1");
                auto total = msg.fields().try_get_or_default(FIX::Tag::TotNoRelatedSym, 0);
                auto last = msg.fields().try_get_or_default(FIX::Tag::LastFragment, "N");
                auto nrOfRel = msg.fields().try_get_or_default(FIX::Tag::NoRelatedSym, "N");
                LOG_INFO("security list req={} res={} total={} last={} nr={}", request_id.value(), result.value(), total.value(), last.value(), nrOfRel.value())

                if (last.value() == "Y") {
                        auto marketDataRequest = Message(true,  { 
                            Field( FIX::Tag::MsgType, FIX::MsgType::MarketDataRequest),                        
                            Field( FIX::Tag::MDReqID, "unique_market_data_id"),
                            Field( FIX::Tag::SubscriptionRequestType, 1),
                            Field( FIX::Tag::MarketDepth, 20)                            
                        });
                    session->send(marketDataRequest);   
                }
            }

            if (msg.MsgType() == FIX::MsgType::MarketDataSnapshotFullRefresh || msg.MsgType() == FIX::MsgType::MarketDataIncrementalRefresh) {

                auto request_id = msg.fields().try_get_or_default(FIX::Tag::MDReqID, "");
                auto symbol = msg.fields().try_get_or_default(FIX::Tag::Symbol, "");
                auto security_type = msg.fields().try_get_or_default(FIX::Tag::SecurityType, "");
                auto md_entries = msg.fields().try_get_or_default(FIX::Tag::NoMDEntries, 0);

                auto groups = msg.groups();
                if (std::stoi(md_entries.value()) != groups.size()) {
                    LOG_ERROR("parsig error");
                }

                bool book_changed = false;

                for(const auto& group : groups) {
                    auto md_entry_type = group.fields.try_get_or_default(FIX::Tag::MDEntryType, "");
                    Side side = Side::UNKNOWN;
                    if (md_entry_type.value() == "0") {
                        side = Side::BID;
                    } else if (md_entry_type.value() == "1") {
                        side = Side::ASK;     
                    }
                    if (side != Side::UNKNOWN) {
                        auto update_action = group.fields.try_get(FIX::Tag::MDUpdateAction);
                        auto level = group.fields.try_get(FIX::Tag::MDEntryType);
                        if (update_action && update_action->value() == "2") {                        
                            auto book = mOrderBookManager.books[symbol.value()];
                            book.deleteLevel(side, std::stoi(level->value()));
                            book_changed = true;
                        } else {
                            auto level = group.fields.try_get(FIX::Tag::MDEntryType);
                            auto px = group.fields.try_get(FIX::Tag::MDEntryPx);
                            auto size = group.fields.try_get(FIX::Tag::MDEntrySize);
                            auto tstamp = group.fields.try_get(FIX::Tag::TransactTime);
                            auto book = mOrderBookManager.books[symbol.value()];
                            book.addOrAmendLevel(side, std::stoi(level->value()), std::stod(px->value()), std::stod(size->value()), tstamp->value());
                            book_changed = true;
                        }
                    }
                }

                if (book_changed) {
                    mOrderBookManager.books[symbol.value()].print(symbol.value());
                }
            }
            
        }
        std::shared_ptr<qffixlib::Session> session;
        OrderBookManager mOrderBookManager;
    };


int main() {

    // Add security symbols to the repeating group
    
    AppOptions app_options;
    app_options.application_name = "test_lib";
    LoggerOptions logging_options;
    logging_options.console_log = true;
    logging_options.console_log_level_str ="debug";
    auto app = std::make_unique<Application>(app_options, logging_options); 
    LOG_INFO("starting app");

    auto eventManager = std::make_shared<qfapp::EventManager>();

    auto session_obs = std::make_shared<MySession>();

	auto sess = std::make_shared<qffixlib::Session>(session_obs, eventManager);
	sess->begin_string("FIXT.1.1");
    sess->sender_comp_id("pv3hnDiPUkJrGS5K"); //ams
	//sess.sender_comp_id("KQySnxBocoJGMBVk"); //haarlem
    sess->target_comp_id("CBINTLMD");
	sess->username(sess->sender_comp_id());
    sess->password("jhgJHGJHFGHf765jhgffghg");//ams 
	//sess.password("dX!PU_fcCwTx23Yihd@-5hh86r"); //harlem

    session_obs->session = sess;

    

    //auto client = std::make_shared<fixlib::SSLClientConnection>(std::move(sess), eventManager);
    //sess->set_writer(client);
    SSLSocket* sock = new SSLSocket();
    sess->set_writer(sock);
    auto client = std::make_shared<ClientConnection>(sess, sock, eventManager);

    client->open_connection("3.114.19.227", 6120);

    eventManager->addFileDescriptor(client);

    eventManager->run();

	return 0;
}