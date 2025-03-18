#ifndef VERSION_SELECTOR_HPP
#define VERSION_SELECTOR_HPP

#include "v50sp2/messages.hpp"
#include "v50sp2/header.hpp"
#include "v44/messages.hpp"
#include "v44/header.hpp"
//#include "fix_header.hpp"

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
        //using Header = v50sp2::Header;
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
        //using Header = v44::Header;
        using Logon = v44::Message::Logon;
        using Logout = v44::Message::Logout;
        using Reject = v44::Message::Reject;
        using TestRequest = v44::Message::TestRequest;
        using ResendRequest = v44::Message::ResendRequest;
        using SequenceReset = v44::Message::SequenceReset;
        using Heartbeat = v44::Message::Heartbeat;
        static constexpr std::string_view VERSION_STR = "FIX.4.4.";
    };
}

#endif //VERSION_SELECTOR_HPP