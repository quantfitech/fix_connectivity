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
#include "tag.hpp"

#include "order_book.hpp"
 
namespace qfapp { namespace coinbase_md {
 
using namespace qffixlib;
 

 template<Version V>
 class CoinbaseMdSession : public Session<V> {
    public:
        virtual ~CoinbaseMdSession() {};
        CoinbaseMdSession(std::shared_ptr<EventManagerInterface> em):Session<V>(em){}
        void onMessage(const MsgChars& msgType, TokenIterator& fixIter) override;
        OrderBookManager mOrderBookManager;
};

}}

#endif