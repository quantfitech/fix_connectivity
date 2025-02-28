#ifndef SESSION_STATE_HPP
#define SESSION_STATE_HPP

#include <string>

namespace qffixlib
{

    enum class SessionState
    {
        disconnected,
        connected,
        logging_on,
        resending,
        logged_on,
        resetting
    };

    std::string to_string(SessionState state);

}

#endif //SESSION_STATE_HPP
