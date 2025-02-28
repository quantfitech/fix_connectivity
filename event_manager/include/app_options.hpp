#ifndef APP_OPTIONS_HPP
#define APP_OPTIONS_HPP

#include <string>

namespace qfapp {

    enum class ConnectionType {
        ACCEPTOR,
        INITIATOR
    };

    struct Connection {
        std::string host {};
        int port={};
        ConnectionType type {ConnectionType::INITIATOR};
    };

    struct AppOptions {
    
    std::string application_name{};
    Connection connection{};

    };

}

#endif

