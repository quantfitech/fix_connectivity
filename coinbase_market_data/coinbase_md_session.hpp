#ifndef COINBASE_MD_SESSION_HPP 
#define  COINBASE_MD_SESSION_HPP


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
 
namespace quantfi { namespace coinbase_md {
 
using namespace qffixlib;
 
 class CoinbaseMdSession : public SessionInterface {
    public:
        virtual ~CoinbaseMdSession() {};
        void onConnected() {}
        void onDisconnected() {}
        void onMessage(char, TokenIterator&);

        std::shared_ptr<qffixlib::Session> session;
        OrderBookManager mOrderBookManager;
};

}}

#endif