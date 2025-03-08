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
// #include "session_interface.hpp"
#include "tag.hpp"

#include "order_book.hpp"
 
namespace quantfi { namespace coinbase_md {
 
using namespace qffixlib;
 

 template<Version V>
 class CoinbaseMdSession : public Session<V> {
    public:
        virtual ~CoinbaseMdSession() {};
        CoinbaseMdSession(std::shared_ptr<EventManagerInterface> em):Session<V>(em){}

        void sendQuote(const std::string&);
        void updateQuote(const std::string& symbol);
        void cancelQuote(const std::string& symbol);
        void onTime();
        void massCancel();


        void onMessage(char msgType, TokenIterator& fixIter) override;

        std::vector<double> values = {0.2, -0.2, 0.4, -0.4, -0.3, 0.3};
        std::map<std::string, std::pair<int, int>> mClordIds;
        std::shared_ptr<RecurringTimer> mTimer;
        double px = 13.50;
        int counter = 0;
};

}}

#endif