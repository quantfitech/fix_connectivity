#pragma once

#include "fix_group.hpp"
#include "fix_message.hpp"
#include "fix_types.hpp"


namespace qffixlib
{
	namespace v50sp2
	{
		namespace Message
		{
            using Heartbeat = FIXMessage<FIX::MsgType::Heartbeat, Types::TestReqID>;

            using TestRequest = FIXMessage<FIX::MsgType::TestRequest, Types::TestReqID>;

            using ResendRequest = FIXMessage<FIX::MsgType::ResendRequest, Types::BeginSeqNo, Types::EndSeqNo>;

            using Reject = FIXMessage<FIX::MsgType::Reject,
                            Types::RefSeqNum, Types::RefTagID, Types::RefMsgType, Types::SessionRejectReason,
                            Types::Text, Types::EncodedTextLen, Types::EncodedText>;

            using SequenceReset = FIXMessage<FIX::MsgType::SequenceReset, Types::PossDupFlag, Types::GapFillFlag, Types::NewSeqNo>;

            using Logon = FIXMessage<FIX::MsgType::Logon,
                  Types::EncryptMethod, Types::HeartBtInt, Types::RawDataLength, Types::RawData,
                  Types::NextExpectedMsgSeqNum,
                  Types::ResetSeqNumFlag, Types::Username, Types::Password,  Types::MaxMessageSize,
                  Types::Text, Types::DefaultApplVerID, Types::DefaultSelfTradePreventionStrategy,
                  Types::CancelOrdersOnDisconnect, Types::CancelOrdersOnInternalDisconnect>;

            using Logout = FIXMessage<FIX::MsgType::Logout, Types::Text, Types::EncodedTextLen, Types::EncodedText>;

            using SecurityListRequest = FIXMessage<FIX::MsgType::SecurityListRequest, Types::SecurityReqID, 
                                                   Types::SecurityListRequestType, Types::Symbol>;

            using SecurityList = FIXMessage<FIX::MsgType::SecurityList, Types::SecurityReqID, Types::SecurityResponseID, Types::SecurityRequestResult,
                                            Types::TotNoRelatedSym, Types::LastFragment, Group<FIX::Tag::NoRelatedSym, Types::Symbol, Types::SecurityType,
                                            Types::SecuritySubType, Types::ContractMultiplier, Types::MinPriceIncrement, Types::MarginRatio, Types::DefaultMarginRatio, 
                                            Group<FIX::Tag::NoInstrAttrib, Types::InstrAttribType,Types::InstrAttribValue>, Group<FIX::Tag::NoEvents, Types:: EventType, Types::EventTime>,
                                            Types::Currency, Types::MinTradeVol,Types::MaxTradeVol,
                                            Types::PositionLimit, Types::RoundLot, Types::MDSecurityTradingStatus>, Group<FIX::Tag::NoUnderlyings, Types::UnderlyingSecurityType>>;


            using SecurityDefinition = FIXMessage<FIX::MsgType::SecurityDefinition, Types::SecurityUpdateAction, Types::LastUpdateTime, Types::Symbol, Types::SecurityType, Types::SecuritySubType, Types::ContractMultiplier,
                                                  Types::MinPriceIncrement, Types::MarginRatio, Types::DefaultMarginRatio, Group<FIX::Tag::NoInstrAttrib, Types::InstrAttribType, Types::InstrAttribValue>, Group<FIX::Tag::NoEvents,
                                                  Types::EventType, Types::EventTime>, Types::Currency, Types::MinTradeVol, Types::MaxTradeVol, Types::PositionLimit, Types::RoundLot, Types::MDSecurityTradingStatus,
                                                  Group<FIX::Tag::NoUnderlyings,Types::UnderlyingSecurityType>>;

            using MarketDataRequest = FIXMessage<FIX::MsgType::MarketDataRequest, Types::MDReqID, Types::SubscriptionRequestType, Types::MarketDepth, Group<FIX::Tag::NoRelatedSym, Types::Symbol, Types::SecurityType>>;

            using MarketDataRequestReject = FIXMessage<FIX::MsgType::MarketDataRequestReject, Types::MDReqID, Types::MDReqRejReason, Types::Text>;


			using MarketDataSnapshot = FIXMessage<FIX::MsgType::MarketDataSnapshotFullRefresh,
                                                  Types::MDReqID, Types::Symbol, Types::SecurityType, 
                                                  Group<FIX::Tag::NoMDEntries, Types::MDEntryType, Types::MDEntryID, Types::MDEntryPx, Types::MDEntrySize, Types::TransactTime,
                                                  Types::MDPriceLevel, Types::AggressorSide>>;

            using MarketDataIncrementalRefresh = FIXMessage<FIX::MsgType::MarketDataIncrementalRefresh, Types::MDReqID, 
                                                            Group<FIX::Tag::NoMDEntries, Types::MDUpdateAction, Types::MDEntryType, Types::MDEntryID, Types::Symbol, 
                                                            Types::MDEntryPx,Types:: MDEntrySize, Types::TransactTime, Types::MDPriceLevel, Types::AggressorSide>
                                                            >;

            using NewOrderSingle = FIXMessage<'D', Types::ClOrdID, Group<FIX::Tag::NoPartyIDs, Types::PartyRole>, Types::ExecInst, Types::OrderQty, Types::OrdType, Types::Price,
                                                   Types::Side, Types::Symbol, Types::TimeInForce, 
                                                   Types::ExpireTime, Types::StopPx, Types::StopLimitPx, Types::SelfTradePreventionStrategy, Types::TargetStrategy>; 

            using OrderCancelReplaceRequest = FIXMessage<'G', Types::ClOrdID, Group<FIX::Tag::NoPartyIDs, Types::PartyRole>, Types::OrigClOrdID, Types::OrderQty,  Types::Price, Types::Symbol,
                                                            Types::StopPx>;


		} // namespace Message		
	}
} 