#include "session_state.hpp"

namespace qffixlib
{
    std::string to_string(SessionState state)
    {
        switch (state)
        {
            case SessionState::connected:
                return "connected";

            case SessionState::logging_on:
                return "loggin_on";

            case SessionState::resending:
                return "resending";

            case SessionState::logged_on:
                return "logged_on";

            case SessionState::resetting:
                return "resetting";

            default:
                return "unknown";
        }    
    }
}