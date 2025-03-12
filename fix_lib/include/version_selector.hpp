#ifndef VERSION_SELECTOR_HPP
#define VERSION_SELECTOR_HPP

#include "v50sp2/messages.hpp"
#include "fix_header.hpp"

namespace qffixlib {

    enum class Version {
        v50sp2,
        v44
    };

    // VersionSelector picks the correct version based on the template argument
    template <Version V>
    struct VersionSelector;

    template <>
    struct VersionSelector<Version::v50sp2> {
        using Logon = v50sp2::Message::Logon;
        using Logout = v50sp2::Message::Logout;
        using Reject = v50sp2::Message::Reject;
        using TestRequest = v50sp2::Message::TestRequest;
        using ResendRequest = v50sp2::Message::ResendRequest;
        using SequenceReset = v50sp2::Message::SequenceReset;
        using Heartbeat = v50sp2::Message::Heartbeat;
       static constexpr std::string_view VERSION_STR = "FIXT.1.1";
    };

    template <>
    struct VersionSelector<Version::v44> {
        //using Logon = v50sp2::Message::Logon;
        //using Logout = v50sp2::Message::Logout;
        static constexpr std::string_view VERSION_STR = "FIX.4.4.";
    };
}

#endif //VERSION_SELECTOR_HPP