#ifndef FIX_HEADER_HPP
#define FIX_HEADER_HPP

#include "fix_group.hpp"
#include "fix_types.hpp"


namespace qffixlib {

    using Header = BaseMessage<Types::BeginString,
                               Types::BodyLength,
                               Types::MsgType,
                               Types::ResetSeqNumFlag,
                               Types::SenderCompID,
                               Types::TargetCompID,
                               Types::MsgSeqNum,
                               Types::SenderSubID,
                               Types::PossResend,
                               Types::SendingTime,
                               Types::LastMsgSeqNumProcessed>;

}

#endif //FIX_HEADER_HPP