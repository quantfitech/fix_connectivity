#ifndef SESSION_INTERFACE_H
#define SESSION_INTERFACE_H

#include  <string>
#include "message.hpp"
#include "fix_message.hpp"


namespace qffixlib {

    class SessionInterface {
    public:
        virtual ~SessionInterface() {};
        //virtual void openConnection(const std::string& host, int port) = 0;
        virtual void onConnected() = 0;
        virtual void onDisconnected() = 0;
        virtual void onMessage(char, TokenIterator&) = 0;
    };

}

#endif //SESSION_INTERFACE_H
