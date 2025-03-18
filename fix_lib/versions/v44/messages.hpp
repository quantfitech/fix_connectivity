#pragma once

#include "fix_group.hpp"
#include "fix_message.hpp"
#include "fix_types.hpp"
#include "tag.hpp"


namespace qffixlib
{
	namespace v44
	{
		namespace Message
		{
                  using Heartbeat = FIXMessage<FIX::MsgType::Heartbeat , Types::TestReqID >;
                  using TestRequest = FIXMessage<FIX::MsgType::TestRequest , Types::TestReqID >;
                  using ResendRequest = FIXMessage<FIX::MsgType::ResendRequest , Types::BeginSeqNo, Types::EndSeqNo >;
                  using Reject = FIXMessage<FIX::MsgType::Reject , Types::RefSeqNum, Types::RefTagID, Types::RefMsgType, Types::SessionRejectReason, Types::Text >;
                  using SequenceReset = FIXMessage<FIX::MsgType::SequenceReset , Types::GapFillFlag, Types::NewSeqNo >;
                  using Logout = FIXMessage<FIX::MsgType::Logout , Types::Text >;
                  using Logon = FIXMessage<FIX::MsgType::Logon , Types::EncryptMethod, Types::HeartBtInt, Types::RawDataLength, Types::RawData, Types::ResetSeqNumFlag, 
                                          Types::NextExpectedMsgSeqNum, Types::MaxMessageSize, Types::TestMessageIndicator, Types::Username, Types::Password, Types::CancelOnDisconnectType, Types::CancelOnDisconnectScope >;

                  using BusinessMessageReject = FIXMessage<FIX::MsgType::BusinessMessageReject , Types::RefSeqNum, Types::RefMsgType, Types::BusinessRejectRefID, Types::ExecRefID, Types::BusinessRejectReason, Types::Text >;
                  using OrderMassStatusRequest = FIXMessage<FIX::MsgType::OrderMassStatusRequest , Types::MassStatusReqID, Types::MassStatusReqType, Types::OrigClOrdID, Types::SecurityType, Types::OrderID, Types::Symbol, Types::DateFrom, 
                                                            Types::DateTo, Types::ReqLimit, Types::MassStatusReqDataType >;
                  using MassOrder = FIXMessage<FIX::MsgType::MassOrder , Types::MassOrderRequestID, Types::ReceiveWindow, Types::ExtrimmedSymbol, Types::ExtrimmedSelfMatchPreventionScope, 
                                                Types::ExtrimmedSelfMatchPreventionInstruction, Types::ExtrimmedSelfMatchPreventionID, Types::OrderResponseLevel, Types::TotNoOrderEntries, Types::LastFragment >;
                  
                  using NewOrderSingle = FIXMessage<FIX::MsgType::NewOrderSingle , Types::ReceiveWindow, Types::ClOrdID, Types::CashMargin, Types::ExecInst, Types::Side, Types::TransactTime, Types::OrderQty, Types::CashOrderQty,
                                                       Types::OrdType, Types::Price, Types::TriggerPrice, Types::TriggerPriceType, Types::Currency, Types::QuoteID, Types::TimeInForce, Types::BrokerID, Types::CommissionCurrency, 
                                                       Types::Symbol, Types::SelfMatchPreventionScope, Types::SelfMatchPreventionInstruction, Types::SelfMatchPreventionID >;
                  using OrderCancelReplaceRequest = FIXMessage<FIX::MsgType::OrderCancelReplaceRequest , Types::ReceiveWindow, Types::ClOrdID, Types::OrigClOrdID, Types::OrderID, Types::Price, Types::OrderQty, Types::SelfMatchPreventionInstruction >;
                  using OrderCancelRequest = FIXMessage<FIX::MsgType::OrderCancelRequest , Types::ReceiveWindow, Types::ClOrdID, Types::OrigClOrdID, Types::OrderID, Types::Symbol >;
                  using QuoteRequest = FIXMessage<FIX::MsgType::QuoteRequest , Types::QuoteReqID >;
                  using Quote = FIXMessage<FIX::MsgType::Quote , Types::QuoteID, Types::QuoteReqID, Types::Symbol, Types::Currency, Types::OrderQty, Types::Side, Types::BidPx, Types::BidSize, Types::OfferPx, Types::OfferSize >;
                  using QuoteRequestReject = FIXMessage<FIX::MsgType::QuoteRequestReject , Types::QuoteReqID, Types::QuoteRequestRejectReason >;
                  
                  using OrderStatusRequest = FIXMessage<FIX::MsgType::OrderStatusRequest , Types::OrderID, Types::ClOrdID, Types::Symbol >;
                  using OrderCancelReject = FIXMessage<FIX::MsgType::OrderCancelReject , Types::OrderID, Types::ClOrdID, Types::OrigClOrdID, Types::OrdStatus, Types::ExecRefID, Types::TransactTime, Types::CxlRejResponseTo, Types::CxlRejReason, Types::Text >;
                  using OrderMassCancelRequest = FIXMessage<FIX::MsgType::OrderMassCancelRequest , Types::ClOrdID, Types::ReceiveWindow, Types::MassCancelRequestType, Types::Symbol, Types::SecurityType >;
                  using OrderMassCancelReport = FIXMessage<FIX::MsgType::OrderMassCancelReport , Types::ClOrdID, Types::MassCancelRequestType, Types::MassCancelResponse, Types::MassCancelRejectReason, Types::ExecRefID >;
                  using ExecutionReport = FIXMessage<FIX::MsgType::ExecutionReport , Types::OrderID, Types::ClOrdID, Types::OrigClOrdID, Types::TotNumReports, Types::LastRptRequested, Types::ExecID, Types::ExecType, Types::OrdStatus,
                                                       Types::OrdRejReason, Types::ExecRefID, Types::Account, Types::CashMargin, Types::Symbol, Types::Side, Types::OrderQty, Types::CashOrderQty, Types::OrdType, Types::Price, Types::TriggerPrice,
                                                       Types::TriggerPriceType, Types::TimeInForce, Types::ExecInst, Types::LastShares, Types::LastPx, Types::LeavesQty, Types::CumQty, Types::AvgPx, Types::TransactTime, Types::Text, Types::LastLiquidityInd, 
                                                       Types::OrderCreateTime, Types::CommType, Types::Commission, Types::CommissionCurrency, Types::MassStatusReqDataType, Types::MassStatusReqID, Types::WorkingIndicator, Types::Currency, Types::TrdMatchID,
                                                       Types::MatchCount, Types::MatchIndex >;
                  

            using MarketDataRequest = FIXMessage<FIX::MsgType::MarketDataRequest , Types::MDReqID, Types::SubscriptionRequestType, Types::MarketDepth, Types::MDUpdateType, Types::AggregatedBook, Types::MDImplicitDelete, Types::TimeToExpiration >;
            using MarketDataIncrementalRefresh = FIXMessage<FIX::MsgType::MarketDataIncrementalRefresh , Types::MDReqID, Types::MDEntryID, Types::MDEntryRefID, Types::Symbol, Types::MDEntryTimeMs, Types::Text, Types::LastFragment >;
            using MarketDataSnapshot = FIXMessage<FIX::MsgType::MarketDataSnapshotFullRefresh , Types::MDReqID, Types::MDEntryID, Types::MDEntryRefID, Types::Symbol, Types::MDEntryTimeMs, Types::Text >;
            using MarketDataRequestReject = FIXMessage<FIX::MsgType::MarketDataRequestReject , Types::MDReqID, Types::MDReqRejReason, Types::Text, Types::EncodedTextLen, Types::EncodedText >;
            using SecurityListRequest = FIXMessage<FIX::MsgType::SecurityListRequest , Types::SecurityReqID, Types::SecurityListRequestType, Types::SubscriptionRequestType >;
            using SecurityList = FIXMessage<FIX::MsgType::SecurityList , Types::SecurityReqID, Types::SecurityResponseID, Types::SecurityRequestResult, Types::LastFragment >;
            using SecurityDefRequest = FIXMessage<FIX::MsgType::SecurityDefRequest , Types::SecurityReqID, Types::SecurityRequestType, Types::Symbol, Types::SubscriptionRequestType >;
            using SecurityDefinition = FIXMessage<FIX::MsgType::SecurityDefinition , Types::SecurityReqID, Types::SecurityResponseID, Types::SecurityResponseType, Types::Symbol >;


		} // namespace Message		
	}
} 