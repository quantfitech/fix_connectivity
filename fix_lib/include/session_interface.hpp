#ifndef SESSION_INTERFACE_H
#define SESSION_INTERFACE_H

#include  <string>
#include "token_iterator.hpp"

namespace qffixlib {

    class SessionInterface {
    public:
        virtual ~SessionInterface() {};
        virtual void onConnected() = 0;
        virtual void onDisconnected() = 0;
        virtual void onMessage(char, TokenIterator&) = 0;
    };

}

#endif //SESSION_INTERFACE_H
