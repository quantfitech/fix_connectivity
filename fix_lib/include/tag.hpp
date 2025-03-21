#ifndef TAG_HPP
#define TAG_HPP

#include <string>
#include <optional>
#include <ctime>
#include <chrono>


namespace FIX {

	using UTCTimestamp = std::chrono::system_clock::time_point;

	struct Char {
		Char() = default;
		Char(char value): mValue(value){}
		char mValue{};
	};
	
	struct UTCDate 
	{		
		UTCDate(std::time_t&& date): mDate(std::move(date)) {}
		std::time_t mDate;
	};

	struct UTCTimeOnly 
	{
		UTCTimeOnly(std::time_t&& time): mTime(std::move(time)) {}		
		std::time_t mTime;
	};

	using LocalMktDate = std::string;

	using Amt = double;
    using Price = double;
    using PriceOffset = double;
    using Qty = double;	
	using MultipleValueString = std::string;
	using Data = std::string;
	using NumInGroup = int64_t;
	using SeqNum = int64_t;
	using MonthYear = std::string;
	using Percentage = double;
	using MultipleCharValue = std::string;



	namespace MsgType {
		constexpr std::array<char, 2> Heartbeat = {'0', '\n'};
		constexpr std::array<char, 2> TestRequest = {'1', '\n'};
		constexpr std::array<char, 2> ResendRequest = {'2', '\n'};
		constexpr std::array<char, 2> Reject = {'3', '\n'};
		constexpr std::array<char, 2> SequenceReset = {'4', '\n'};
		constexpr std::array<char, 2> Logout = {'5', '\n'};
		constexpr std::array<char, 2> Logon = {'A', '\n'};
		//app messages
		constexpr std::array<char, 2> MarketDataRequest = {'V', '\n'};
		constexpr std::array<char, 2> MarketDataIncrementalRefresh = {'X', '\n'};
		constexpr std::array<char, 2> MarketDataSnapshotFullRefresh = {'W', '\n'};
		constexpr std::array<char, 2> MarketDataRequestReject = {'Y', '\n'};
		constexpr std::array<char, 2> SecurityListRequest = {'x', '\n'};
		constexpr std::array<char, 2> SecurityList = {'y', '\n'};
		constexpr std::array<char, 2> SecurityDefRequest = {'c', '\n'};
		constexpr std::array<char, 2> SecurityDefinition = {'d', '\n'};
		//order entry
		constexpr std::array<char, 2> NewOrderSingle = {'D', '\n'};
		constexpr std::array<char, 2> OrderCancelReplaceRequest = {'G', '\n'};
		constexpr std::array<char, 2> OrderCancelRequest = {'F', '\n'};
		constexpr std::array<char, 2> MassOrder = {'D', 'J'};
		constexpr std::array<char, 2> QuoteRequest = {'R', '\n'};
		constexpr std::array<char, 2> Quote = {'S', '\n'};
		constexpr std::array<char, 2> QuoteRequestReject = {'A', 'G'};
		constexpr std::array<char, 2> OrderMassStatusRequest = {'A', 'F'};
		constexpr std::array<char, 2> BusinessMessageReject = {'j', '\n'};
		constexpr std::array<char, 2> OrderStatusRequest = {'H', '\n'};
		constexpr std::array<char, 2> OrderCancelReject = {'9', '\n'};
		constexpr std::array<char, 2> OrderMassCancelRequest = {'q', '\n'};
		constexpr std::array<char, 2> OrderMassCancelReport = {'r', '\n'};
		constexpr std::array<char, 2> ExecutionReport = {'8', '\n'};
		//drop copy
		constexpr std::array<char, 2> LastExecIDRequest = {'F', '1'};
		constexpr std::array<char, 2> LastExecID = {'F', '2'};
		constexpr std::array<char, 2> EventResendRequest = {'F', '3'};
		constexpr std::array<char, 2> EventResendComplete = {'F', '4'};
		constexpr std::array<char, 2> EventResendReject = {'F', '5'};
	}
	namespace Tag {
		constexpr int BeginSeqNo = 7;
		constexpr int BeginString = 8;
		constexpr int BodyLength = 9;
		constexpr int CheckSum = 10;
		constexpr int EndSeqNo = 16;
		constexpr int MsgSeqNum = 34;
		constexpr int MsgType = 35;
		constexpr int NewSeqNo = 36;
		constexpr int PossDupFlag = 43;
		constexpr int RefSeqNum = 45;
		constexpr int SenderCompID = 49;
		constexpr int SenderSubID = 50;
		constexpr int SendingTime = 52;
		constexpr int Symbol = 55;
		constexpr int TargetCompID = 56;
		constexpr int TargetSubID = 57;
		constexpr int Text = 58;
		constexpr int TransactTime = 60;
		constexpr int Signature = 89;
		constexpr int SecureDataLen = 90;
		constexpr int SecureData = 91;
		constexpr int SignatureLength = 93;
		constexpr int RawDataLength = 95;
		constexpr int RawData = 96;
		constexpr int PossResend = 97;
		constexpr int EncryptMethod = 98;
		constexpr int HeartBtInt = 108;
		constexpr int TestReqID = 112;
		constexpr int OnBehalfOfCompID = 115;
		constexpr int OnBehalfOfSubID = 116;
		constexpr int OrigSendingTime = 122;
		constexpr int GapFillFlag = 123;
		constexpr int DeliverToCompID = 128;
		constexpr int DeliverToSubID = 129;
		constexpr int ResetSeqNumFlag = 141;
		constexpr int SenderLocationID = 142;
		constexpr int TargetLocationID = 143;
		constexpr int OnBehalfOfLocationID = 144;
		constexpr int DeliverToLocationID = 145;
		constexpr int NoRelatedSym = 146;
		constexpr int SecurityType = 167;
		constexpr int XmlDataLen = 212;
		constexpr int XmlData = 213;
		constexpr int MDReqID = 262;
		constexpr int SubscriptionRequestType = 263;
		constexpr int MarketDepth = 264;
		constexpr int NoMDEntries = 268;
		constexpr int MDEntryType = 269;
		constexpr int MDEntryPx = 270;
		constexpr int MDEntrySize = 271;
		constexpr int MDEntryID = 278;
		constexpr int MDUpdateAction = 279;
		constexpr int MDReqRejReason = 281;
		constexpr int SecurityReqID = 320;
		constexpr int MessageEncoding = 347;
		constexpr int EncodedTextLen = 354;
		constexpr int EncodedText = 355;
		constexpr int LastMsgSeqNumProcessed = 369;
		constexpr int RefTagID = 371;
		constexpr int RefMsgType = 372;
		constexpr int SessionRejectReason = 373;
		constexpr int MaxMessageSize = 383;
		constexpr int TotNoRelatedSym = 393;
		constexpr int NoPartyIDs = 453;
		constexpr int TestMessageIndicator = 464;
		constexpr int Username = 553;
		constexpr int Password = 554;
		constexpr int SecurityListRequestType = 559;
		constexpr int SecurityRequestResult = 560;
		constexpr int NoHops = 627;
		constexpr int HopCompID = 628;
		constexpr int HopSendingTime = 629;
		constexpr int HopRefID = 630;
		constexpr int NoUnderlyings = 711;
		constexpr int NextExpectedMsgSeqNum = 789;
		constexpr int NoEvents = 864;
		constexpr int NoInstrAttrib = 870;
		constexpr int LastFragment = 893;
		constexpr int NewPassword = 925;
		constexpr int MDPriceLevel = 1023;
		constexpr int DefaultApplVerID  = 1137;
		constexpr int AggressorSide = 2446;
		constexpr int DefaultSelfTradePreventionStrategy = 8001;
		constexpr int CancelOrdersOnDisconnect = 8013;
		constexpr int CancelOrdersOnInternalDisconnect = 8014;
		constexpr int BeginExecID = 22003;
		constexpr int EndExecID = 22004;
	}
}

#endif