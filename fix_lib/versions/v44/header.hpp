#pragma once

#include "fix_group.hpp"
#include "fix_types.hpp"


namespace qffixlib
{
	namespace v44
	{
		using Header = BaseMessage<Types::BeginString,
                                   Types::BodyLength,
                                   Types::MsgType,
                                   Types::MsgSeqNum,
                                   Types::PossDupFlag,
                                   Types::SenderCompID,
                                   Types::TargetCompID,
                                   Types::SendingTime,
                                   Types::PossResend>;
    }
}