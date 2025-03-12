#ifndef FIX_VALUES_HPP
#define FIX_VALUES_HPP

#include <string_view>

  namespace qffixlib {

    namespace Values {

    namespace  AdvSide {
        constexpr char Buy = 'B';
        constexpr char Sell = 'S';
        constexpr char Trade = 'T';
        constexpr char Cross = 'X';
    }
    namespace  AdvTransType {
        constexpr char New = 'N';
        constexpr char Cancel = 'C';
        constexpr char Replace = 'R';
    }
    namespace  CommType {
        constexpr char PerUnit = '1';
        constexpr char Percent = '2';
        constexpr char Absolute = '3';
        constexpr char PercentageWaivedCashDiscount = '4';
        constexpr char PercentageWaivedEnhancedUnits = '5';
        constexpr char PointsPerBondOrContract = '6';
    }
    namespace  ExecInst {
    }
    namespace  HandlInst {
        constexpr char AutomatedExecutionNoIntervention = '1';
        constexpr char AutomatedExecutionInterventionOK = '2';
        constexpr char ManualOrder = '3';
    }
    namespace  SecurityIDSource {
        constexpr char CUSIP = '1';
        constexpr char SEDOL = '2';
        constexpr char QUIK = '3';
        constexpr char ISINNumber = '4';
        constexpr char RICCode = '5';
        constexpr char ISOCurrencyCode = '6';
        constexpr char ISOCountryCode = '7';
        constexpr char ExchangeSymbol = '8';
        constexpr char ConsolidatedTapeAssociation = '9';
        constexpr char BloombergSymbol = 'A';
        constexpr char Wertpapier = 'B';
        constexpr char Dutch = 'C';
        constexpr char Valoren = 'D';
        constexpr char Sicovam = 'E';
        constexpr char Belgian = 'F';
        constexpr char Common = 'G';
        constexpr char ClearingHouse = 'H';
        constexpr char ISDAFpMLSpecification = 'I';
        constexpr char OptionPriceReportingAuthority = 'J';
        constexpr char ISDAFpMLURL = 'K';
        constexpr char LetterOfCredit = 'L';
        constexpr char MarketplaceAssignedIdentifier = 'M';
    }
    namespace  IOIQltyInd {
        constexpr char High = 'H';
        constexpr char Low = 'L';
        constexpr char Medium = 'M';
    }
    namespace  IOIQty {
        constexpr char Small = 'S';
        constexpr char Medium = 'M';
        constexpr char Large = 'L';
        constexpr char UndisclosedQuantity = 'U';
    }
    namespace  IOITransType {
        constexpr char New = 'N';
        constexpr char Cancel = 'C';
        constexpr char Replace = 'R';
    }
    namespace  LastCapacity {
        constexpr char Agent = '1';
        constexpr char CrossAsAgent = '2';
        constexpr char CrossAsPrincipal = '3';
        constexpr char Principal = '4';
    }
    namespace  OrdStatus {
        constexpr char New = '0';
        constexpr char PartiallyFilled = '1';
        constexpr char Filled = '2';
        constexpr char DoneForDay = '3';
        constexpr char Canceled = '4';
        constexpr char Replaced = '5';
        constexpr char PendingCancel = '6';
        constexpr char Stopped = '7';
        constexpr char Rejected = '8';
        constexpr char Suspended = '9';
        constexpr char PendingNew = 'A';
        constexpr char Calculated = 'B';
        constexpr char Expired = 'C';
        constexpr char AcceptedForBidding = 'D';
        constexpr char PendingReplace = 'E';
    }
    namespace  OrdType {
        constexpr char Market = '1';
        constexpr char Limit = '2';
        constexpr char Stop = '3';
        constexpr char StopLimit = '4';
        constexpr char MarketOnClose = '5';
        constexpr char WithOrWithout = '6';
        constexpr char LimitOrBetter = '7';
        constexpr char LimitWithOrWithout = '8';
        constexpr char OnBasis = '9';
        constexpr char OnClose = 'A';
        constexpr char LimitOnClose = 'B';
        constexpr char ForexMarket = 'C';
        constexpr char PreviouslyQuoted = 'D';
        constexpr char PreviouslyIndicated = 'E';
        constexpr char ForexLimit = 'F';
        constexpr char ForexSwap = 'G';
        constexpr char ForexPreviouslyQuoted = 'H';
        constexpr char Funari = 'I';
        constexpr char MarketIfTouched = 'J';
        constexpr char MarketWithLeftOverAsLimit = 'K';
        constexpr char PreviousFundValuationPoint = 'L';
        constexpr char NextFundValuationPoint = 'M';
        constexpr char Pegged = 'P';
        constexpr char CounterOrderSelection = 'Q';
    }
    namespace  PossDupFlag {
        constexpr char OriginalTransmission = 'N';
        constexpr char PossibleDuplicate = 'Y';
    }
    namespace  Side {
        constexpr char Buy = '1';
        constexpr char Sell = '2';
        constexpr char BuyMinus = '3';
        constexpr char SellPlus = '4';
        constexpr char SellShort = '5';
        constexpr char SellShortExempt = '6';
        constexpr char Undisclosed = '7';
        constexpr char Cross = '8';
        constexpr char CrossShort = '9';
        constexpr char CrossShortExempt = 'A';
        constexpr char AsDefined = 'B';
        constexpr char Opposite = 'C';
        constexpr char Subscribe = 'D';
        constexpr char Redeem = 'E';
        constexpr char Lend = 'F';
        constexpr char Borrow = 'G';
    }
    namespace  TimeInForce {
        constexpr char Day = '0';
        constexpr char GoodTillCancel = '1';
        constexpr char AtTheOpening = '2';
        constexpr char ImmediateOrCancel = '3';
        constexpr char FillOrKill = '4';
        constexpr char GoodTillCrossing = '5';
        constexpr char GoodTillDate = '6';
        constexpr char AtTheClose = '7';
        constexpr char GoodThroughCrossing = '8';
        constexpr char AtCrossing = '9';
    }
    namespace  Urgency {
        constexpr char Normal = '0';
        constexpr char Flash = '1';
        constexpr char Background = '2';
    }
    namespace  SettlType {
        constexpr char Regular = '0';
        constexpr char Cash = '1';
        constexpr char NextDay = '2';
        constexpr char TPlus2 = '3';
        constexpr char TPlus3 = '4';
        constexpr char TPlus4 = '5';
        constexpr char Future = '6';
        constexpr char WhenAndIfIssued = '7';
        constexpr char SellersOption = '8';
        constexpr char TPlus5 = '9';
        constexpr char BrokenDate = 'B';
        constexpr char FXSpotNextSettlement = 'C';
    }
    namespace  SymbolSfx {
        constexpr std::string_view EUCPWithLumpSumInterest = "CD";
        constexpr std::string_view WhenIssued = "WI";
    }
    namespace  AllocTransType {
        constexpr char New = '0';
        constexpr char Replace = '1';
        constexpr char Cancel = '2';
        constexpr char Preliminary = '3';
        constexpr char Calculated = '4';
        constexpr char CalculatedWithoutPreliminary = '5';
        constexpr char Reversal = '6';
    }
    namespace  PositionEffect {
        constexpr char Close = 'C';
        constexpr char FIFO = 'F';
        constexpr char Open = 'O';
        constexpr char Rolled = 'R';
        constexpr char CloseButNotifyOnOpen = 'N';
        constexpr char Default = 'D';
    }
    namespace  ProcessCode {
        constexpr char Regular = '0';
        constexpr char SoftDollar = '1';
        constexpr char StepIn = '2';
        constexpr char StepOut = '3';
        constexpr char SoftDollarStepIn = '4';
        constexpr char SoftDollarStepOut = '5';
        constexpr char PlanSponsor = '6';
    }
    namespace  AllocStatus {
        constexpr int Accepted = 0;
        constexpr int BlockLevelReject = 1;
        constexpr int AccountLevelReject = 2;
        constexpr int Received = 3;
        constexpr int Incomplete = 4;
        constexpr int RejectedByIntermediary = 5;
        constexpr int AllocationPending = 6;
        constexpr int Reversed = 7;
    }
    namespace  AllocRejCode {
        constexpr int UnknownAccount = 0;
        constexpr int IncorrectQuantity = 1;
        constexpr int IncorrectAveragegPrice = 2;
        constexpr int UnknownExecutingBrokerMnemonic = 3;
        constexpr int CommissionDifference = 4;
        constexpr int UnknownOrderID = 5;
        constexpr int UnknownListID = 6;
        constexpr int OtherSeeText = 7;
        constexpr int IncorrectAllocatedQuantity = 8;
        constexpr int CalculationDifference = 9;
        constexpr int UnknownOrStaleExecID = 10;
        constexpr int MismatchedData = 11;
        constexpr int UnknownClOrdID = 12;
        constexpr int WarehouseRequestRejected = 13;
    }
    namespace  EmailType {
        constexpr char New = '0';
        constexpr char Reply = '1';
        constexpr char AdminReply = '2';
    }
    namespace  PossResend {
        constexpr char OriginalTransmission = 'N';
        constexpr char PossibleResend = 'Y';
    }
    namespace  EncryptMethod {
        constexpr int None = 0;
        constexpr int PKCS = 1;
        constexpr int DES = 2;
        constexpr int PKCSDES = 3;
        constexpr int PGPDES = 4;
        constexpr int PGPDESMD5 = 5;
        constexpr int PEM = 6;
    }
    namespace  CxlRejReason {
        constexpr int TooLateToCancel = 0;
        constexpr int UnknownOrder = 1;
        constexpr int BrokerCredit = 2;
        constexpr int OrderAlreadyInPendingStatus = 3;
        constexpr int UnableToProcessOrderMassCancelRequest = 4;
        constexpr int OrigOrdModTime = 5;
        constexpr int DuplicateClOrdID = 6;
        constexpr int PriceExceedsCurrentPrice = 7;
        constexpr int PriceExceedsCurrentPriceBand = 8;
        constexpr int InvalidPriceIncrement = 18;
        constexpr int Other = 99;
    }
    namespace  OrdRejReason {
        constexpr int BrokerCredit = 0;
        constexpr int UnknownSymbol = 1;
        constexpr int ExchangeClosed = 2;
        constexpr int OrderExceedsLimit = 3;
        constexpr int TooLateToEnter = 4;
        constexpr int UnknownOrder = 5;
        constexpr int DuplicateOrder = 6;
        constexpr int DuplicateOfAVerballyCommunicatedOrder = 7;
        constexpr int StaleOrder = 8;
        constexpr int TradeAlongRequired = 9;
        constexpr int InvalidInvestorID = 10;
        constexpr int UnsupportedOrderCharacteristic = 11;
        constexpr int SurveillenceOption = 12;
        constexpr int IncorrectQuantity = 13;
        constexpr int IncorrectAllocatedQuantity = 14;
        constexpr int UnknownAccount = 15;
        constexpr int PriceExceedsCurrentPriceBand = 16;
        constexpr int InvalidPriceIncrement = 18;
        constexpr int Other = 99;
    }
    namespace  IOIQualifier {
        constexpr char AllOrNone = 'A';
        constexpr char MarketOnClose = 'B';
        constexpr char AtTheClose = 'C';
        constexpr char VWAP = 'D';
        constexpr char InTouchWith = 'I';
        constexpr char Limit = 'L';
        constexpr char MoreBehind = 'M';
        constexpr char AtTheOpen = 'O';
        constexpr char TakingAPosition = 'P';
        constexpr char AtTheMarket = 'Q';
        constexpr char ReadyToTrade = 'R';
        constexpr char PortfolioShown = 'S';
        constexpr char ThroughTheDay = 'T';
        constexpr char Versus = 'V';
        constexpr char Indication = 'W';
        constexpr char CrossingOpportunity = 'X';
        constexpr char AtTheMidpoint = 'Y';
        constexpr char PreOpen = 'Z';
    }
    namespace  ReportToExch {
        constexpr char SenderReports = 'N';
        constexpr char ReceiverReports = 'Y';
    }
    namespace  LocateReqd {
        constexpr char No = 'N';
        constexpr char Yes = 'Y';
    }
    namespace  ForexReq {
        constexpr char DoNotExecuteForexAfterSecurityTrade = 'N';
        constexpr char ExecuteForexAfterSecurityTrade = 'Y';
    }
    namespace  GapFillFlag {
        constexpr char SequenceReset = 'N';
        constexpr char GapFillMessage = 'Y';
    }
    namespace  DKReason {
        constexpr char UnknownSymbol = 'A';
        constexpr char WrongSide = 'B';
        constexpr char QuantityExceedsOrder = 'C';
        constexpr char NoMatchingOrder = 'D';
        constexpr char PriceExceedsLimit = 'E';
        constexpr char CalculationDifference = 'F';
        constexpr char Other = 'Z';
    }
    namespace  IOINaturalFlag {
        constexpr char NotNatural = 'N';
        constexpr char Natural = 'Y';
    }
    namespace  MiscFeeType {
        constexpr char Regulatory = '1';
        constexpr char Tax = '2';
        constexpr char LocalCommission = '3';
        constexpr char ExchangeFees = '4';
        constexpr char Stamp = '5';
        constexpr char Levy = '6';
        constexpr char Other = '7';
        constexpr char Markup = '8';
        constexpr char ConsumptionTax = '9';
        constexpr std::string_view PerTransaction = "10";
        constexpr std::string_view Conversion = "11";
        constexpr std::string_view Agent = "12";
        constexpr std::string_view TransferFee = "13";
        constexpr std::string_view SecurityLending = "14";
    }
    namespace  ResetSeqNumFlag {
        constexpr char No = 'N';
        constexpr char Yes = 'Y';
    }
    namespace  ExecType {
        constexpr char New = '0';
        constexpr char DoneForDay = '3';
        constexpr char Canceled = '4';
        constexpr char Replaced = '5';
        constexpr char PendingCancel = '6';
        constexpr char Stopped = '7';
        constexpr char Rejected = '8';
        constexpr char Suspended = '9';
        constexpr char PendingNew = 'A';
        constexpr char Calculated = 'B';
        constexpr char Expired = 'C';
        constexpr char Restated = 'D';
        constexpr char PendingReplace = 'E';
        constexpr char Trade = 'F';
        constexpr char TradeCorrect = 'G';
        constexpr char TradeCancel = 'H';
        constexpr char OrderStatus = 'I';
        constexpr char TradeInAClearingHold = 'J';
        constexpr char TradeHasBeenReleasedToClearing = 'K';
        constexpr char TriggeredOrActivatedBySystem = 'L';
    }
    namespace  SettlCurrFxRateCalc {
        constexpr char Multiply = 'M';
        constexpr char Divide = 'D';
    }
    namespace  SettlInstMode {
        constexpr char Default = '0';
        constexpr char StandingInstructionsProvided = '1';
        constexpr char SpecificAllocationAccountOverriding = '2';
        constexpr char SpecificAllocationAccountStanding = '3';
        constexpr char SpecificOrderForASingleAccount = '4';
        constexpr char RequestReject = '5';
    }
    namespace  SettlInstTransType {
        constexpr char New = 'N';
        constexpr char Cancel = 'C';
        constexpr char Replace = 'R';
        constexpr char Restate = 'T';
    }
    namespace  SettlInstSource {
        constexpr char BrokerCredit = '1';
        constexpr char Institution = '2';
        constexpr char Investor = '3';
    }
    namespace  SecurityType {
        constexpr std::string_view USTreasuryNoteOld = "UST";
        constexpr std::string_view USTreasuryBillOld = "USTB";
        constexpr std::string_view EuroSupranationalCoupons = "EUSUPRA";
        constexpr std::string_view FederalAgencyCoupon = "FAC";
        constexpr std::string_view FederalAgencyDiscountNote = "FADN";
        constexpr std::string_view PrivateExportFunding = "PEF";
        constexpr std::string_view USDSupranationalCoupons = "SUPRA";
        constexpr std::string_view CorporateBond = "CORP";
        constexpr std::string_view CorporatePrivatePlacement = "CPP";
        constexpr std::string_view ConvertibleBond = "CB";
        constexpr std::string_view DualCurrency = "DUAL";
        constexpr std::string_view EuroCorporateBond = "EUCORP";
        constexpr std::string_view EuroCorporateFloatingRateNotes = "EUFRN";
        constexpr std::string_view USCorporateFloatingRateNotes = "FRN";
        constexpr std::string_view IndexedLinked = "XLINKD";
        constexpr std::string_view StructuredNotes = "STRUCT";
        constexpr std::string_view YankeeCorporateBond = "YANK";
        constexpr std::string_view ForeignExchangeContract = "FOR";
        constexpr std::string_view CreditDefaultSwap = "CDS";
        constexpr std::string_view Future = "FUT";
        constexpr std::string_view Option = "OPT";
        constexpr std::string_view OptionsOnFutures = "OOF";
        constexpr std::string_view OptionsOnPhysical = "OOP";
        constexpr std::string_view InterestRateSwap = "IRS";
        constexpr std::string_view OptionsOnCombo = "OOC";
        constexpr std::string_view CommonStock = "CS";
        constexpr std::string_view PreferredStock = "PS";
        constexpr std::string_view Repurchase = "REPO";
        constexpr std::string_view Forward = "FORWARD";
        constexpr std::string_view BuySellback = "BUYSELL";
        constexpr std::string_view SecuritiesLoan = "SECLOAN";
        constexpr std::string_view SecuritiesPledge = "SECPLEDGE";
        constexpr std::string_view BradyBond = "BRADY";
        constexpr std::string_view CanadianTreasuryNotes = "CAN";
        constexpr std::string_view CanadianTreasuryBills = "CTB";
        constexpr std::string_view EuroSovereigns = "EUSOV";
        constexpr std::string_view CanadianProvincialBonds = "PROV";
        constexpr std::string_view TreasuryBill = "TB";
        constexpr std::string_view USTreasuryBond = "TBOND";
        constexpr std::string_view InterestStripFromAnyBondOrNote = "TINT";
        constexpr std::string_view USTreasuryBill = "TBILL";
        constexpr std::string_view TreasuryInflationProtectedSecurities = "TIPS";
        constexpr std::string_view PrincipalStripOfACallableBondOrNote = "TCAL";
        constexpr std::string_view PrincipalStripFromANonCallableBondOrNote = "TPRN";
        constexpr std::string_view USTreasuryNote = "TNOTE";
        constexpr std::string_view TermLoan = "TERM";
        constexpr std::string_view RevolverLoan = "RVLV";
        constexpr std::string_view Revolver = "RVLVTRM";
        constexpr std::string_view BridgeLoan = "BRIDGE";
        constexpr std::string_view LetterOfCredit = "LOFC";
        constexpr std::string_view SwingLineFacility = "SWING";
        constexpr std::string_view DebtorInPossession = "DINP";
        constexpr std::string_view Defaulted = "DEFLTED";
        constexpr std::string_view Withdrawn = "WITHDRN";
        constexpr std::string_view Replaced = "REPLACD";
        constexpr std::string_view Matured = "MATURED";
        constexpr std::string_view Amended = "AMENDED";
        constexpr std::string_view Retired = "RETIRED";
        constexpr std::string_view BankersAcceptance = "BA";
        constexpr std::string_view BankDepositoryNote = "BDN";
        constexpr std::string_view BankNotes = "BN";
        constexpr std::string_view BillOfExchanges = "BOX";
        constexpr std::string_view CanadianMoneyMarkets = "CAMM";
        constexpr std::string_view CertificateOfDeposit = "CD";
        constexpr std::string_view CallLoans = "CL";
        constexpr std::string_view CommercialPaper = "CP";
        constexpr std::string_view DepositNotes = "DN";
        constexpr std::string_view EuroCertificateOfDeposit = "EUCD";
        constexpr std::string_view EuroCommercialPaper = "EUCP";
        constexpr std::string_view LiquidityNote = "LQN";
        constexpr std::string_view MediumTermNotes = "MTN";
        constexpr std::string_view Overnight = "ONITE";
        constexpr std::string_view PromissoryNote = "PN";
        constexpr std::string_view ShortTermLoanNote = "STN";
        constexpr std::string_view PlazosFijos = "PZFJ";
        constexpr std::string_view SecuredLiquidityNote = "SLQN";
        constexpr std::string_view TimeDeposit = "TD";
        constexpr std::string_view TermLiquidityNote = "TLQN";
        constexpr std::string_view ExtendedCommNote = "XCN";
        constexpr std::string_view YankeeCertificateOfDeposit = "YCD";
        constexpr std::string_view AssetBackedSecurities = "ABS";
        constexpr std::string_view CanadianMortgageBonds = "CMB";
        constexpr std::string_view Corp = "CMBS";
        constexpr std::string_view CollateralizedMortgageObligation = "CMO";
        constexpr std::string_view IOETTEMortgage = "IET";
        constexpr std::string_view MortgageBackedSecurities = "MBS";
        constexpr std::string_view MortgageInterestOnly = "MIO";
        constexpr std::string_view MortgagePrincipalOnly = "MPO";
        constexpr std::string_view MortgagePrivatePlacement = "MPP";
        constexpr std::string_view MiscellaneousPassThrough = "MPT";
        constexpr std::string_view Pfandbriefe = "PFAND";
        constexpr std::string_view ToBeAnnounced = "TBA";
        constexpr std::string_view OtherAnticipationNotes = "AN";
        constexpr std::string_view CertificateOfObligation = "COFO";
        constexpr std::string_view CertificateOfParticipation = "COFP";
        constexpr std::string_view GeneralObligationBonds = "GO";
        constexpr std::string_view MandatoryTender = "MT";
        constexpr std::string_view RevenueAnticipationNote = "RAN";
        constexpr std::string_view RevenueBonds = "REV";
        constexpr std::string_view SpecialAssessment = "SPCLA";
        constexpr std::string_view SpecialObligation = "SPCLO";
        constexpr std::string_view SpecialTax = "SPCLT";
        constexpr std::string_view TaxAnticipationNote = "TAN";
        constexpr std::string_view TaxAllocation = "TAXA";
        constexpr std::string_view TaxExemptCommercialPaper = "TECP";
        constexpr std::string_view TaxableMunicipalCP = "TMCP";
        constexpr std::string_view TaxRevenueAnticipationNote = "TRAN";
        constexpr std::string_view VariableRateDemandNote = "VRDN";
        constexpr std::string_view Warrant = "WAR";
        constexpr std::string_view MutualFund = "MF";
        constexpr std::string_view MultilegInstrument = "MLEG";
        constexpr std::string_view NoSecurityType = "NONE";
        constexpr char Wildcard = '?';
        constexpr std::string_view Cash = "CASH";
    }
    namespace  StandInstDbType {
        constexpr int Other = 0;
        constexpr int DTCSID = 1;
        constexpr int ThomsonALERT = 2;
        constexpr int AGlobalCustodian = 3;
        constexpr int AccountNet = 4;
    }
    namespace  SettlDeliveryType {
        constexpr int Versus = 0;
        constexpr int Free = 1;
        constexpr int TriParty = 2;
        constexpr int HoldInCustody = 3;
    }
    namespace  AllocLinkType {
        constexpr int FXNetting = 0;
        constexpr int FXSwap = 1;
    }
    namespace  PutOrCall {
        constexpr int Put = 0;
        constexpr int Call = 1;
    }
    namespace  CoveredOrUncovered {
        constexpr int Covered = 0;
        constexpr int Uncovered = 1;
    }
    namespace  NotifyBrokerOfCredit {
        constexpr char DetailsShouldNotBeCommunicated = 'N';
        constexpr char DetailsShouldBeCommunicated = 'Y';
    }
    namespace  AllocHandlInst {
        constexpr int Match = 1;
        constexpr int Forward = 2;
        constexpr int ForwardAndMatch = 3;
    }
    namespace  RoutingType {
        constexpr int TargetFirm = 1;
        constexpr int TargetList = 2;
        constexpr int BlockFirm = 3;
        constexpr int BlockList = 4;
    }
    namespace  BenchmarkCurveName {
        constexpr std::string_view EONIA = "EONIA";
        constexpr std::string_view EUREPO = "EUREPO";
        constexpr std::string_view Euribor = "Euribor";
        constexpr std::string_view FutureSWAP = "FutureSWAP";
        constexpr std::string_view LIBID = "LIBID";
        constexpr std::string_view LIBOR = "LIBOR";
        constexpr std::string_view MuniAAA = "MuniAAA";
        constexpr std::string_view OTHER = "OTHER";
        constexpr std::string_view Pfandbriefe = "Pfandbriefe";
        constexpr std::string_view SONIA = "SONIA";
        constexpr std::string_view SWAP = "SWAP";
        constexpr std::string_view Treasury = "Treasury";
    }
    namespace  StipulationType {
        constexpr std::string_view AlternativeMinimumTax = "AMT";
        constexpr std::string_view AutoReinvestment = "AUTOREINV";
        constexpr std::string_view BankQualified = "BANKQUAL";
        constexpr std::string_view BargainConditions = "BGNCON";
        constexpr std::string_view CouponRange = "COUPON";
        constexpr std::string_view ISOCurrencyCode = "CURRENCY";
        constexpr std::string_view CustomStart = "CUSTOMDATE";
        constexpr std::string_view Geographics = "GEOG";
        constexpr std::string_view ValuationDiscount = "HAIRCUT";
        constexpr std::string_view Insured = "INSURED";
        constexpr std::string_view IssueDate = "ISSUE";
        constexpr std::string_view Issuer = "ISSUER";
        constexpr std::string_view IssueSizeRange = "ISSUESIZE";
        constexpr std::string_view LookbackDays = "LOOKBACK";
        constexpr std::string_view ExplicitLotIdentifier = "LOT";
        constexpr std::string_view LotVariance = "LOTVAR";
        constexpr std::string_view MaturityYearAndMonth = "MAT";
        constexpr std::string_view MaturityRange = "MATURITY";
        constexpr std::string_view MaximumSubstitutions = "MAXSUBS";
        constexpr std::string_view MinimumDenomination = "MINDNOM";
        constexpr std::string_view MinimumIncrement = "MININCR";
        constexpr std::string_view MinimumQuantity = "MINQTY";
        constexpr std::string_view PaymentFrequency = "PAYFREQ";
        constexpr std::string_view NumberOfPieces = "PIECES";
        constexpr std::string_view PoolsMaximum = "PMAX";
        constexpr std::string_view PoolsPerLot = "PPL";
        constexpr std::string_view PoolsPerMillion = "PPM";
        constexpr std::string_view PoolsPerTrade = "PPT";
        constexpr std::string_view PriceRange = "PRICE";
        constexpr std::string_view PricingFrequency = "PRICEFREQ";
        constexpr std::string_view ProductionYear = "PROD";
        constexpr std::string_view CallProtection = "PROTECT";
        constexpr std::string_view Purpose = "PURPOSE";
        constexpr std::string_view BenchmarkPriceSource = "PXSOURCE";
        constexpr std::string_view RatingSourceAndRange = "RATING";
        constexpr std::string_view TypeOfRedemption = "REDEMPTION";
        constexpr std::string_view Restricted = "RESTRICTED";
        constexpr std::string_view MarketSector = "SECTOR";
        constexpr std::string_view SecurityTypeIncludedOrExcluded = "SECTYPE";
        constexpr std::string_view Structure = "STRUCT";
        constexpr std::string_view SubstitutionsFrequency = "SUBSFREQ";
        constexpr std::string_view SubstitutionsLeft = "SUBSLEFT";
        constexpr std::string_view FreeformText = "TEXT";
        constexpr std::string_view TradeVariance = "TRDVAR";
        constexpr std::string_view WeightedAverageCoupon = "WAC";
        constexpr std::string_view WeightedAverageLifeCoupon = "WAL";
        constexpr std::string_view WeightedAverageLoanAge = "WALA";
        constexpr std::string_view WeightedAverageMaturity = "WAM";
        constexpr std::string_view WholePool = "WHOLE";
        constexpr std::string_view YieldRange = "YIELD";
        constexpr std::string_view AverageFICOScore = "AVFICO";
        constexpr std::string_view AverageLoanSize = "AVSIZE";
        constexpr std::string_view MaximumLoanBalance = "MAXBAL";
        constexpr std::string_view PoolIdentifier = "POOL";
        constexpr std::string_view TypeOfRollTrade = "ROLLTYPE";
        constexpr std::string_view ReferenceToRollingOrClosingTrade = "REFTRADE";
        constexpr std::string_view PrincipalOfRollingOrClosingTrade = "REFPRIN";
        constexpr std::string_view InterestOfRollingOrClosingTrade = "REFINT";
        constexpr std::string_view AvailableOfferQuantityToBeShownToTheStreet = "AVAILQTY";
        constexpr std::string_view BrokerCredit = "BROKERCREDIT";
        constexpr std::string_view OfferPriceToBeShownToInternalBrokers = "INTERNALPX";
        constexpr std::string_view OfferQuantityToBeShownToInternalBrokers = "INTERNALQTY";
        constexpr std::string_view TheMinimumResidualOfferQuantity = "LEAVEQTY";
        constexpr std::string_view MaximumOrderSize = "MAXORDQTY";
        constexpr std::string_view OrderQuantityIncrement = "ORDRINCR";
        constexpr std::string_view PrimaryOrSecondaryMarketIndicator = "PRIMARY";
        constexpr std::string_view BrokerSalesCreditOverride = "SALESCREDITOVR";
        constexpr std::string_view TraderCredit = "TRADERCREDIT";
        constexpr std::string_view DiscountRate = "DISCOUNT";
        constexpr std::string_view YieldToMaturity = "YTM";
        constexpr std::string_view AbsolutePrepaymentSpeed = "ABS";
        constexpr std::string_view ConstantPrepaymentPenalty = "CPP";
        constexpr std::string_view ConstantPrepaymentRate = "CPR";
        constexpr std::string_view ConstantPrepaymentYield = "CPY";
        constexpr std::string_view FinalCPROfHomeEquityPrepaymentCurve = "HEP";
        constexpr std::string_view PercentOfManufacturedHousingPrepaymentCurve = "MHP";
        constexpr std::string_view MonthlyPrepaymentRate = "MPR";
        constexpr std::string_view PercentOfProspectusPrepaymentCurve = "PPC";
        constexpr std::string_view PercentOfBMAPrepaymentCurve = "PSA";
        constexpr std::string_view SingleMonthlyMortality = "SMM";
    }
    namespace  YieldType {
        constexpr std::string_view AfterTaxYield = "AFTERTAX";
        constexpr std::string_view AnnualYield = "ANNUAL";
        constexpr std::string_view YieldAtIssue = "ATISSUE";
        constexpr std::string_view YieldToAverageMaturity = "AVGMATURITY";
        constexpr std::string_view BookYield = "BOOK";
        constexpr std::string_view YieldToNextCall = "CALL";
        constexpr std::string_view YieldChangeSinceClose = "CHANGE";
        constexpr std::string_view ClosingYield = "CLOSE";
        constexpr std::string_view CompoundYield = "COMPOUND";
        constexpr std::string_view CurrentYield = "CURRENT";
        constexpr std::string_view GvntEquivalentYield = "GOVTEQUIV";
        constexpr std::string_view TrueGrossYield = "GROSS";
        constexpr std::string_view YieldWithInflationAssumption = "INFLATION";
        constexpr std::string_view InverseFloaterBondYield = "INVERSEFLOATER";
        constexpr std::string_view MostRecentClosingYield = "LASTCLOSE";
        constexpr std::string_view ClosingYieldMostRecentMonth = "LASTMONTH";
        constexpr std::string_view ClosingYieldMostRecentQuarter = "LASTQUARTER";
        constexpr std::string_view ClosingYieldMostRecentYear = "LASTYEAR";
        constexpr std::string_view YieldToLongestAverageLife = "LONGAVGLIFE";
        constexpr std::string_view MarkToMarketYield = "MARK";
        constexpr std::string_view YieldToMaturity = "MATURITY";
        constexpr std::string_view YieldToNextRefund = "NEXTREFUND";
        constexpr std::string_view OpenAverageYield = "OPENAVG";
        constexpr std::string_view PreviousCloseYield = "PREVCLOSE";
        constexpr std::string_view ProceedsYield = "PROCEEDS";
        constexpr std::string_view YieldToNextPut = "PUT";
        constexpr std::string_view SemiAnnualYield = "SEMIANNUAL";
        constexpr std::string_view YieldToShortestAverageLife = "SHORTAVGLIFE";
        constexpr std::string_view SimpleYield = "SIMPLE";
        constexpr std::string_view TaxEquivalentYield = "TAXEQUIV";
        constexpr std::string_view YieldToTenderDate = "TENDER";
        constexpr std::string_view TrueYield = "TRUE";
        constexpr std::string_view YieldValueOf32nds = "VALUE1_32";
        constexpr std::string_view YieldToWorst = "WORST";
    }
    namespace  TradedFlatSwitch {
        constexpr char NotTradedFlat = 'N';
        constexpr char TradedFlat = 'Y';
    }
    namespace  SubscriptionRequestType {
        constexpr char Snapshot = '0';
        constexpr char SnapshotAndUpdates = '1';
        constexpr char DisablePreviousSnapshot = '2';
    }
    namespace  MDUpdateType {
        constexpr int FullRefresh = 0;
        constexpr int IncrementalRefresh = 1;
    }
    namespace  AggregatedBook {
        constexpr char BookEntriesToBeAggregated = 'Y';
        constexpr char BookEntriesShouldNotBeAggregated = 'N';
    }
    namespace  MDEntryType {
        constexpr char Bid = '0';
        constexpr char Offer = '1';
        constexpr char Trade = '2';
        constexpr char IndexValue = '3';
        constexpr char OpeningPrice = '4';
        constexpr char ClosingPrice = '5';
        constexpr char SettlementPrice = '6';
        constexpr char TradingSessionHighPrice = '7';
        constexpr char TradingSessionLowPrice = '8';
        constexpr char TradingSessionVWAPPrice = '9';
        constexpr char Imbalance = 'A';
        constexpr char TradeVolume = 'B';
        constexpr char OpenInterest = 'C';
        constexpr char CompositeUnderlyingPrice = 'D';
        constexpr char SimulatedSellPrice = 'E';
        constexpr char SimulatedBuyPrice = 'F';
        constexpr char MarginRate = 'G';
        constexpr char MidPrice = 'H';
        constexpr char EmptyBook = 'J';
        constexpr char SettleHighPrice = 'K';
        constexpr char SettleLowPrice = 'L';
        constexpr char PriorSettlePrice = 'M';
        constexpr char SessionHighBid = 'N';
        constexpr char SessionLowOffer = 'O';
        constexpr char EarlyPrices = 'P';
        constexpr char AuctionClearingPrice = 'Q';
        constexpr char SwapValueFactor = 'S';
        constexpr char DailyValueAdjustmentForLongPositions = 'R';
        constexpr char CumulativeValueAdjustmentForLongPositions = 'T';
        constexpr char DailyValueAdjustmentForShortPositions = 'U';
        constexpr char CumulativeValueAdjustmentForShortPositions = 'V';
    }
    namespace  TickDirection {
        constexpr char PlusTick = '0';
        constexpr char ZeroPlusTick = '1';
        constexpr char MinusTick = '2';
        constexpr char ZeroMinusTick = '3';
    }
    namespace  QuoteCondition {
        constexpr std::string_view Open = "A";
        constexpr std::string_view Closed = "B";
        constexpr std::string_view ExchangeBest = "C";
        constexpr std::string_view ConsolidatedBest = "D";
        constexpr std::string_view Locked = "E";
        constexpr std::string_view Crossed = "F";
        constexpr std::string_view Depth = "G";
        constexpr std::string_view FastTrading = "H";
        constexpr std::string_view NonFirm = "I";
        constexpr std::string_view Manual = "L";
        constexpr std::string_view OutrightPrice = "J";
        constexpr std::string_view ImpliedPrice = "K";
        constexpr std::string_view DepthOnOffer = "M";
        constexpr std::string_view DepthOnBid = "N";
        constexpr std::string_view Closing = "O";
        constexpr std::string_view NewsDissemination = "P";
        constexpr std::string_view TradingRange = "Q";
        constexpr std::string_view OrderInflux = "R";
        constexpr std::string_view DueToRelated = "S";
        constexpr std::string_view NewsPending = "T";
        constexpr std::string_view AdditionalInfo = "U";
        constexpr std::string_view AdditionalInfoDueToRelated = "V";
        constexpr std::string_view Resume = "W";
        constexpr std::string_view ViewOfCommon = "X";
        constexpr std::string_view VolumeAlert = "Y";
        constexpr std::string_view OrderImbalance = "Z";
        constexpr std::string_view EquipmentChangeover = "a";
        constexpr std::string_view NoOpen = "b";
        constexpr std::string_view RegularETH = "c";
        constexpr std::string_view AutomaticExecution = "d";
        constexpr std::string_view AutomaticExecutionETH = "e";
        constexpr std::string_view FastMarketETH = "f ";
        constexpr std::string_view InactiveETH = "g";
        constexpr std::string_view Rotation = "h";
        constexpr std::string_view RotationETH = "i";
        constexpr std::string_view Halt = "j";
        constexpr std::string_view HaltETH = "k";
        constexpr std::string_view DueToNewsDissemination = "l";
        constexpr std::string_view DueToNewsPending = "m";
        constexpr std::string_view TradingResume = "n";
        constexpr std::string_view OutOfSequence = "o";
        constexpr std::string_view BidSpecialist = "p";
        constexpr std::string_view OfferSpecialist = "q";
        constexpr std::string_view BidOfferSpecialist = "r";
        constexpr std::string_view EndOfDaySAM = "s";
        constexpr std::string_view ForbiddenSAM = "t";
        constexpr std::string_view FrozenSAM = "u";
        constexpr std::string_view PreOpeningSAM = "v";
        constexpr std::string_view OpeningSAM = "w";
        constexpr std::string_view OpenSAM = "x";
        constexpr std::string_view SurveillanceSAM = "y";
        constexpr std::string_view SuspendedSAM = "z";
        constexpr std::string_view ReservedSAM = "0";
        constexpr std::string_view NoActiveSAM = "1";
        constexpr std::string_view Restricted = "2";
        constexpr std::string_view RestOfBookVWAP = "3";
        constexpr std::string_view BetterPricesInConditionalOrders = "4";
        constexpr std::string_view MedianPrice = "5";
    }
    namespace  TradeCondition {
        constexpr std::string_view Cash = "A";
        constexpr std::string_view AveragePriceTrade = "B";
        constexpr std::string_view CashTrade = "C";
        constexpr std::string_view NextDay = "D";
        constexpr std::string_view Opening = "E";
        constexpr std::string_view IntradayTradeDetail = "F";
        constexpr std::string_view Rule127Trade = "G";
        constexpr std::string_view Rule155Trade = "H";
        constexpr std::string_view SoldLast = "I";
        constexpr std::string_view NextDayTrade = "J";
        constexpr std::string_view Opened = "K";
        constexpr std::string_view Seller = "L";
        constexpr std::string_view Sold = "M";
        constexpr std::string_view StoppedStock = "N";
        constexpr std::string_view ImbalanceMoreBuyers = "P";
        constexpr std::string_view ImbalanceMoreSellers = "Q";
        constexpr std::string_view OpeningPrice = "R";
        constexpr std::string_view BargainCondition = "S";
        constexpr std::string_view ConvertedPriceIndicator = "T";
        constexpr std::string_view ExchangeLast = "U";
        constexpr std::string_view FinalPriceOfSession = "V";
        constexpr std::string_view ExPit = "W";
        constexpr std::string_view Crossed = "X";
        constexpr std::string_view TradesResultingFromManual = "Y";
        constexpr std::string_view TradesResultingFromIntermarketSweep = "Z";
        constexpr std::string_view VolumeOnly = "a";
        constexpr std::string_view DirectPlus = "b";
        constexpr std::string_view Acquisition = "c";
        constexpr std::string_view Bunched = "d";
        constexpr std::string_view Distribution = "e";
        constexpr std::string_view BunchedSale = "f";
        constexpr std::string_view SplitTrade = "g";
        constexpr std::string_view CancelStopped = "h";
        constexpr std::string_view CancelETH = "i";
        constexpr std::string_view CancelStoppedETH = "j";
        constexpr std::string_view OutOfSequenceETH = "k";
        constexpr std::string_view CancelLastETH = "l";
        constexpr std::string_view SoldLastSaleETH = "m";
        constexpr std::string_view CancelLast = "n";
        constexpr std::string_view SoldLastSale = "o";
        constexpr std::string_view CancelOpen = "p";
        constexpr std::string_view CancelOpenETH = "q";
        constexpr std::string_view OpenedSaleETH = "r";
        constexpr std::string_view CancelOnly = "s";
        constexpr std::string_view CancelOnlyETH = "t";
        constexpr std::string_view LateOpenETH = "u";
        constexpr std::string_view AutoExecutionETH = "v";
        constexpr std::string_view Reopen = "w";
        constexpr std::string_view ReopenETH = "x";
        constexpr std::string_view Adjusted = "y";
        constexpr std::string_view AdjustedETH = "z";
        constexpr std::string_view Spread = "AA";
        constexpr std::string_view SpreadETH = "AB";
        constexpr std::string_view Straddle = "AC";
        constexpr std::string_view StraddleETH = "AD";
        constexpr std::string_view Stopped = "AE";
        constexpr std::string_view StoppedETH = "AF";
        constexpr std::string_view RegularETH = "AG";
        constexpr std::string_view Combo = "AH";
        constexpr std::string_view ComboETH = "AI";
        constexpr std::string_view OfficialClosingPrice = "AJ";
        constexpr std::string_view PriorReferencePrice = "AK";
        constexpr std::string_view Cancel = "0";
        constexpr std::string_view StoppedSoldLast = "AL";
        constexpr std::string_view StoppedOutOfSequence = "AM";
        constexpr std::string_view OfficalClosingPrice = "AN";
        constexpr std::string_view CrossedOld = "AO";
        constexpr std::string_view FastMarket = "AP";
        constexpr std::string_view AutomaticExecution = "AQ";
        constexpr std::string_view FormT = "AR";
        constexpr std::string_view BasketIndex = "AS";
        constexpr std::string_view BurstBasket = "AT";
        constexpr std::string_view OutsideSpread = "AV";
        constexpr std::string_view ImpliedTrade = "1";
        constexpr std::string_view MarketplaceEnteredTrade = "2";
        constexpr std::string_view MultAssetClassMultilegTrade = "3";
        constexpr std::string_view MultilegToMultilegTrade = "4";
    }
    namespace  MDUpdateAction {
        constexpr char New = '0';
        constexpr char Change = '1';
        constexpr char Delete = '2';
        constexpr char DeleteThru = '3';
        constexpr char DeleteFrom = '4';
        constexpr char Overlay = '5';
    }
    namespace  MDReqRejReason {
        constexpr char UnknownSymbol = '0';
        constexpr char DuplicateMDReqID = '1';
        constexpr char InsufficientBandwidth = '2';
        constexpr char InsufficientPermissions = '3';
        constexpr char UnsupportedSubscriptionRequestType = '4';
        constexpr char UnsupportedMarketDepth = '5';
        constexpr char UnsupportedMDUpdateType = '6';
        constexpr char UnsupportedAggregatedBook = '7';
        constexpr char UnsupportedMDEntryType = '8';
        constexpr char UnsupportedTradingSessionID = '9';
        constexpr char UnsupportedScope = 'A';
        constexpr char UnsupportedOpenCloseSettleFlag = 'B';
        constexpr char UnsupportedMDImplicitDelete = 'C';
        constexpr char InsufficientCredit = 'D';
    }
    namespace  DeleteReason {
        constexpr char Cancellation = '0';
        constexpr char Error = '1';
    }
    namespace  OpenCloseSettlFlag {
    }
    namespace  FinancialStatus {
    }
    namespace  CorporateAction {
    }
    namespace  QuoteStatus {
        constexpr int Accepted = 0;
        constexpr int CancelForSymbol = 1;
        constexpr int CanceledForSecurityType = 2;
        constexpr int CanceledForUnderlying = 3;
        constexpr int CanceledAll = 4;
        constexpr int Rejected = 5;
        constexpr int RemovedFromMarket = 6;
        constexpr int Expired = 7;
        constexpr int Query = 8;
        constexpr int QuoteNotFound = 9;
        constexpr int Pending = 10;
        constexpr int Pass = 11;
        constexpr int LockedMarketWarning = 12;
        constexpr int CrossMarketWarning = 13;
        constexpr int CanceledDueToLockMarket = 14;
        constexpr int CanceledDueToCrossMarket = 15;
        constexpr int Active = 16;
        constexpr int Canceled = 17;
        constexpr int UnsolicitedQuoteReplenishment = 18;
        constexpr int PendingEndTrade = 19;
        constexpr int TooLateToEnd = 20;
    }
    namespace  QuoteCancelType {
        constexpr int CancelForOneOrMoreSecurities = 1;
        constexpr int CancelForSecurityType = 2;
        constexpr int CancelForUnderlyingSecurity = 3;
        constexpr int CancelAllQuotes = 4;
        constexpr int CancelQuoteSpecifiedInQuoteID = 5;
    }
    namespace  QuoteRejectReason {
        constexpr int UnknownSymbol = 1;
        constexpr int Exchange = 2;
        constexpr int QuoteRequestExceedsLimit = 3;
        constexpr int TooLateToEnter = 4;
        constexpr int UnknownQuote = 5;
        constexpr int DuplicateQuote = 6;
        constexpr int InvalidBid = 7;
        constexpr int InvalidPrice = 8;
        constexpr int NotAuthorizedToQuoteSecurity = 9;
        constexpr int PriceExceedsCurrentPriceBand = 10;
        constexpr int QuoteLocked = 11;
        constexpr int Other = 99;
    }
    namespace  QuoteResponseLevel {
        constexpr int NoAcknowledgement = 0;
        constexpr int AcknowledgeOnlyNegativeOrErroneousQuotes = 1;
        constexpr int AcknowledgeEachQuoteMessage = 2;
        constexpr int SummaryAcknowledgement = 3;
    }
    namespace  QuoteRequestType {
        constexpr int Manual = 1;
        constexpr int Automatic = 2;
    }
    namespace  SecurityRequestType {
        constexpr int RequestSecurityIdentityAndSpecifications = 0;
        constexpr int RequestSecurityIdentityForSpecifications = 1;
        constexpr int RequestListSecurityTypes = 2;
        constexpr int RequestListSecurities = 3;
        constexpr int Symbol = 4;
        constexpr int SecurityTypeAndOrCFICode = 5;
        constexpr int Product = 6;
        constexpr int TradingSessionID = 7;
        constexpr int AllSecurities = 8;
        constexpr int MarketIDOrMarketID = 9;
    }
    namespace  SecurityResponseType {
        constexpr int AcceptAsIs = 1;
        constexpr int AcceptWithRevisions = 2;
        constexpr int ListOfSecurityTypesReturnedPerRequest = 3;
        constexpr int ListOfSecuritiesReturnedPerRequest = 4;
        constexpr int RejectSecurityProposal = 5;
        constexpr int CannotMatchSelectionCriteria = 6;
    }
    namespace  UnsolicitedIndicator {
        constexpr char MessageIsBeingSentAsAResultOfAPriorRequest = 'N';
        constexpr char MessageIsBeingSentUnsolicited = 'Y';
    }
    namespace  SecurityTradingStatus {
        constexpr int OpeningDelay = 1;
        constexpr int TradingHalt = 2;
        constexpr int Resume = 3;
        constexpr int NoOpen = 4;
        constexpr int PriceIndication = 5;
        constexpr int TradingRangeIndication = 6;
        constexpr int MarketImbalanceBuy = 7;
        constexpr int MarketImbalanceSell = 8;
        constexpr int MarketOnCloseImbalanceBuy = 9;
        constexpr int MarketOnCloseImbalanceSell = 10;
        constexpr int NoMarketImbalance = 12;
        constexpr int NoMarketOnCloseImbalance = 13;
        constexpr int ITSPreOpening = 14;
        constexpr int NewPriceIndication = 15;
        constexpr int TradeDisseminationTime = 16;
        constexpr int ReadyToTrade = 17;
        constexpr int NotAvailableForTrading = 18;
        constexpr int NotTradedOnThisMarket = 19;
        constexpr int UnknownOrInvalid = 20;
        constexpr int PreOpen = 21;
        constexpr int OpeningRotation = 22;
        constexpr int FastMarket = 23;
        constexpr int PreCross = 24;
        constexpr int Cross = 25;
    }
    namespace  InViewOfCommon {
        constexpr char HaltWasNotRelatedToAHaltOfTheCommonStock = 'N';
        constexpr char HaltWasDueToCommonStockBeingHalted = 'Y';
    }
    namespace  DueToRelated {
        constexpr char NotRelatedToSecurityHalt = 'N';
        constexpr char RelatedToSecurityHalt = 'Y';
    }
    namespace  Adjustment {
        constexpr int Cancel = 1;
        constexpr int Error = 2;
        constexpr int Correction = 3;
    }
    namespace  TradingSessionID {
        constexpr char Day = '1';
        constexpr char HalfDay = '2';
        constexpr char Morning = '3';
        constexpr char Afternoon = '4';
        constexpr char Evening = '5';
        constexpr char AfterHours = '6';
    }
    namespace  TradSesMethod {
        constexpr int Electronic = 1;
        constexpr int OpenOutcry = 2;
        constexpr int TwoParty = 3;
    }
    namespace  TradSesMode {
        constexpr int Testing = 1;
        constexpr int Simulated = 2;
        constexpr int Production = 3;
    }
    namespace  TradSesStatus {
        constexpr int Unknown = 0;
        constexpr int Halted = 1;
        constexpr int Open = 2;
        constexpr int Closed = 3;
        constexpr int PreOpen = 4;
        constexpr int PreClose = 5;
        constexpr int RequestRejected = 6;
    }
    namespace  SessionRejectReason {
        constexpr int InvalidTagNumber = 0;
        constexpr int RequiredTagMissing = 1;
        constexpr int TagNotDefinedForThisMessageType = 2;
        constexpr int UndefinedTag = 3;
        constexpr int TagSpecifiedWithoutAValue = 4;
        constexpr int ValueIsIncorrect = 5;
        constexpr int IncorrectDataFormatForValue = 6;
        constexpr int DecryptionProblem = 7;
        constexpr int SignatureProblem = 8;
        constexpr int CompIDProblem = 9;
        constexpr int SendingTimeAccuracyProblem = 10;
        constexpr int InvalidMsgType = 11;
        constexpr int XMLValidationError = 12;
        constexpr int TagAppearsMoreThanOnce = 13;
        constexpr int TagSpecifiedOutOfRequiredOrder = 14;
        constexpr int RepeatingGroupFieldsOutOfOrder = 15;
        constexpr int IncorrectNumInGroupCountForRepeatingGroup = 16;
        constexpr int Non = 17;
        constexpr int Invalid = 18;
        constexpr int Other = 99;
    }
    namespace  BidRequestTransType {
        constexpr char Cancel = 'C';
        constexpr char New = 'N';
    }
    namespace  SolicitedFlag {
        constexpr char WasNotSolicited = 'N';
        constexpr char WasSolicited = 'Y';
    }
    namespace  ExecRestatementReason {
        constexpr int GTCorporateAction = 0;
        constexpr int GTRenewal = 1;
        constexpr int VerbalChange = 2;
        constexpr int RepricingOfOrder = 3;
        constexpr int BrokerOption = 4;
        constexpr int PartialDeclineOfOrderQty = 5;
        constexpr int CancelOnTradingHalt = 6;
        constexpr int CancelOnSystemFailure = 7;
        constexpr int Market = 8;
        constexpr int Canceled = 9;
        constexpr int WarehouseRecap = 10;
        constexpr int PegRefresh = 11;
        constexpr int Other = 99;
    }
    namespace  BusinessRejectReason {
        constexpr int Other = 0;
        constexpr int UnknownID = 1;
        constexpr int UnknownSecurity = 2;
        constexpr int UnsupportedMessageType = 3;
        constexpr int ApplicationNotAvailable = 4;
        constexpr int ConditionallyRequiredFieldMissing = 5;
        constexpr int NotAuthorized = 6;
        constexpr int DeliverToFirmNotAvailableAtThisTime = 7;
        constexpr int InvalidPriceIncrement = 18;
    }
    namespace  MsgDirection {
        constexpr char Receive = 'R';
        constexpr char Send = 'S';
    }
    namespace  DiscretionInst {
        constexpr char RelatedToDisplayedPrice = '0';
        constexpr char RelatedToMarketPrice = '1';
        constexpr char RelatedToPrimaryPrice = '2';
        constexpr char RelatedToLocalPrimaryPrice = '3';
        constexpr char RelatedToMidpointPrice = '4';
        constexpr char RelatedToLastTradePrice = '5';
        constexpr char RelatedToVWAP = '6';
        constexpr char AveragePriceGuarantee = '7';
    }
    namespace  BidType {
        constexpr int NonDisclosed = 1;
        constexpr int Disclosed = 2;
        constexpr int NoBiddingProcess = 3;
    }
    namespace  BidDescriptorType {
        constexpr int Sector = 1;
        constexpr int Country = 2;
        constexpr int Index = 3;
    }
    namespace  SideValueInd {
        constexpr int SideValue1 = 1;
        constexpr int SideValue2 = 2;
    }
    namespace  LiquidityIndType {
        constexpr int FiveDayMovingAverage = 1;
        constexpr int TwentyDayMovingAverage = 2;
        constexpr int NormalMarketSize = 3;
        constexpr int Other = 4;
    }
    namespace  ExchangeForPhysical {
        constexpr char False = 'N';
        constexpr char True = 'Y';
    }
    namespace  ProgRptReqs {
        constexpr int BuySideRequests = 1;
        constexpr int SellSideSends = 2;
        constexpr int RealTimeExecutionReports = 3;
    }
    namespace  IncTaxInd {
        constexpr int Net = 1;
        constexpr int Gross = 2;
    }
    namespace  BidTradeType {
        constexpr char Agency = 'A';
        constexpr char VWAPGuarantee = 'G';
        constexpr char GuaranteedClose = 'J';
        constexpr char RiskTrade = 'R';
    }
    namespace  BasisPxType {
        constexpr char ClosingPriceAtMorningSession = '2';
        constexpr char ClosingPrice = '3';
        constexpr char CurrentPrice = '4';
        constexpr char SQ = '5';
        constexpr char VWAPThroughADay = '6';
        constexpr char VWAPThroughAMorningSession = '7';
        constexpr char VWAPThroughAnAfternoonSession = '8';
        constexpr char VWAPThroughADayExcept = '9';
        constexpr char VWAPThroughAMorningSessionExcept = 'A';
        constexpr char VWAPThroughAnAfternoonSessionExcept = 'B';
        constexpr char Strike = 'C';
        constexpr char Open = 'D';
        constexpr char Others = 'Z';
    }
    namespace  PriceType {
        constexpr int Percentage = 1;
        constexpr int PerUnit = 2;
        constexpr int FixedAmount = 3;
        constexpr int Discount = 4;
        constexpr int Premium = 5;
        constexpr int Spread = 6;
        constexpr int TEDPrice = 7;
        constexpr int TEDYield = 8;
        constexpr int Yield = 9;
        constexpr int FixedCabinetTradePrice = 10;
        constexpr int VariableCabinetTradePrice = 11;
        constexpr int ProductTicksInHalfs = 13;
        constexpr int ProductTicksInFourths = 14;
        constexpr int ProductTicksInEights = 15;
        constexpr int ProductTicksInSixteenths = 16;
        constexpr int ProductTicksInThirtySeconds = 17;
        constexpr int ProductTicksInSixtyForths = 18;
        constexpr int ProductTicksInOneTwentyEights = 19;
    }
    namespace  GTBookingInst {
        constexpr int BookOutAllTradesOnDayOfExecution = 0;
        constexpr int AccumulateUntilFilledOrExpired = 1;
        constexpr int AccumulateUntilVerballyNotifiedOtherwise = 2;
    }
    namespace  ListStatusType {
        constexpr int Ack = 1;
        constexpr int Response = 2;
        constexpr int Timed = 3;
        constexpr int ExecStarted = 4;
        constexpr int AllDone = 5;
        constexpr int Alert = 6;
    }
    namespace  NetGrossInd {
        constexpr int Net = 1;
        constexpr int Gross = 2;
    }
    namespace  ListOrderStatus {
        constexpr int InBiddingProcess = 1;
        constexpr int ReceivedForExecution = 2;
        constexpr int Executing = 3;
        constexpr int Cancelling = 4;
        constexpr int Alert = 5;
        constexpr int AllDone = 6;
        constexpr int Reject = 7;
    }
    namespace  ListExecInstType {
        constexpr char Immediate = '1';
        constexpr char WaitForInstruction = '2';
        constexpr char SellDriven = '3';
        constexpr char BuyDrivenCashTopUp = '4';
        constexpr char BuyDrivenCashWithdraw = '5';
    }
    namespace  CxlRejResponseTo {
        constexpr char OrderCancelRequest = '1';
        constexpr char OrderCancel = '2';
    }
    namespace  MultiLegReportingType {
        constexpr char SingleSecurity = '1';
        constexpr char IndividualLegOfAMultiLegSecurity = '2';
        constexpr char MultiLegSecurity = '3';
    }
    namespace  PartyIDSource {
        constexpr char UKNationalInsuranceOrPensionNumber = '6';
        constexpr char USSocialSecurityNumber = '7';
        constexpr char USEmployerOrTaxIDNumber = '8';
        constexpr char AustralianBusinessNumber = '9';
        constexpr char AustralianTaxFileNumber = 'A';
        constexpr char KoreanInvestorID = '1';
        constexpr char TaiwaneseForeignInvestorID = '2';
        constexpr char TaiwaneseTradingAcct = '3';
        constexpr char MalaysianCentralDepository = '4';
        constexpr char ChineseInvestorID = '5';
        constexpr char ISITCAcronym = 'I';
        constexpr char BIC = 'B';
        constexpr char GeneralIdentifier = 'C';
        constexpr char Proprietary = 'D';
        constexpr char ISOCountryCode = 'E';
        constexpr char SettlementEntityLocation = 'F';
        constexpr char MIC = 'G';
        constexpr char CSDParticipant = 'H';
    }
    namespace  PartyRole {
        constexpr int ExecutingFirm = 1;
        constexpr int BrokerOfCredit = 2;
        constexpr int ClientID = 3;
        constexpr int ClearingFirm = 4;
        constexpr int InvestorID = 5;
        constexpr int IntroducingFirm = 6;
        constexpr int EnteringFirm = 7;
        constexpr int Locate = 8;
        constexpr int FundManagerClientID = 9;
        constexpr int SettlementLocation = 10;
        constexpr int OrderOriginationTrader = 11;
        constexpr int ExecutingTrader = 12;
        constexpr int OrderOriginationFirm = 13;
        constexpr int GiveupClearingFirm = 14;
        constexpr int CorrespondantClearingFirm = 15;
        constexpr int ExecutingSystem = 16;
        constexpr int ContraFirm = 17;
        constexpr int ContraClearingFirm = 18;
        constexpr int SponsoringFirm = 19;
        constexpr int UnderlyingContraFirm = 20;
        constexpr int ClearingOrganization = 21;
        constexpr int Exchange = 22;
        constexpr int CustomerAccount = 24;
        constexpr int CorrespondentClearingOrganization = 25;
        constexpr int CorrespondentBroker = 26;
        constexpr int Buyer = 27;
        constexpr int Custodian = 28;
        constexpr int Intermediary = 29;
        constexpr int Agent = 30;
        constexpr int SubCustodian = 31;
        constexpr int Beneficiary = 32;
        constexpr int InterestedParty = 33;
        constexpr int RegulatoryBody = 34;
        constexpr int LiquidityProvider = 35;
        constexpr int EnteringTrader = 36;
        constexpr int ContraTrader = 37;
        constexpr int PositionAccount = 38;
        constexpr int ContraInvestorID = 39;
        constexpr int TransferToFirm = 40;
        constexpr int ContraPositionAccount = 41;
        constexpr int ContraExchange = 42;
        constexpr int InternalCarryAccount = 43;
        constexpr int OrderEntryOperatorID = 44;
        constexpr int SecondaryAccountNumber = 45;
        constexpr int ForeignFirm = 46;
        constexpr int ThirdPartyAllocationFirm = 47;
        constexpr int ClaimingAccount = 48;
        constexpr int AssetManager = 49;
        constexpr int PledgorAccount = 50;
        constexpr int PledgeeAccount = 51;
        constexpr int LargeTraderReportableAccount = 52;
        constexpr int TraderMnemonic = 53;
        constexpr int SenderLocation = 54;
        constexpr int SessionID = 55;
        constexpr int AcceptableCounterparty = 56;
        constexpr int UnacceptableCounterparty = 57;
        constexpr int EnteringUnit = 58;
        constexpr int ExecutingUnit = 59;
        constexpr int IntroducingBroker = 60;
        constexpr int QuoteOriginator = 61;
        constexpr int ReportOriginator = 62;
        constexpr int SystematicInternaliser = 63;
        constexpr int MultilateralTradingFacility = 64;
        constexpr int RegulatedMarket = 65;
        constexpr int MarketMaker = 66;
        constexpr int InvestmentFirm = 67;
        constexpr int HostCompetentAuthority = 68;
        constexpr int HomeCompetentAuthority = 69;
        constexpr int CompetentAuthorityLiquidity = 70;
        constexpr int CompetentAuthorityTransactionVenue = 71;
        constexpr int ReportingIntermediary = 72;
        constexpr int ExecutionVenue = 73;
        constexpr int MarketDataEntryOriginator = 74;
        constexpr int LocationID = 75;
        constexpr int DeskID = 76;
        constexpr int MarketDataMarket = 77;
        constexpr int AllocationEntity = 78;
        constexpr int PrimeBroker = 79;
        constexpr int StepOutFirm = 80;
        constexpr int BrokerClearingID = 81;
    }
    namespace  Product {
        constexpr int AGENCY = 1;
        constexpr int COMMODITY = 2;
        constexpr int CORPORATE = 3;
        constexpr int CURRENCY = 4;
        constexpr int EQUITY = 5;
        constexpr int GOVERNMENT = 6;
        constexpr int INDEX = 7;
        constexpr int LOAN = 8;
        constexpr int MONEYMARKET = 9;
        constexpr int MORTGAGE = 10;
        constexpr int MUNICIPAL = 11;
        constexpr int OTHER = 12;
        constexpr int FINANCING = 13;
    }
    namespace  TestMessageIndicator {
        constexpr char Fales = 'N';
        constexpr char True = 'Y';
    }
    namespace  RoundingDirection {
        constexpr char RoundToNearest = '0';
        constexpr char RoundDown = '1';
        constexpr char RoundUp = '2';
    }
    namespace  DistribPaymentMethod {
        constexpr int CREST = 1;
        constexpr int NSCC = 2;
        constexpr int Euroclear = 3;
        constexpr int Clearstream = 4;
        constexpr int Cheque = 5;
        constexpr int TelegraphicTransfer = 6;
        constexpr int FedWire = 7;
        constexpr int DirectCredit = 8;
        constexpr int ACHCredit = 9;
        constexpr int BPAY = 10;
        constexpr int HighValueClearingSystemHVACS = 11;
        constexpr int ReinvestInFund = 12;
    }
    namespace  CancellationRights {
        constexpr char Yes = 'Y';
        constexpr char NoExecutionOnly = 'N';
        constexpr char NoWaiverAgreement = 'M';
        constexpr char NoInstitutional = 'O';
    }
    namespace  MoneyLaunderingStatus {
        constexpr char Passed = 'Y';
        constexpr char NotChecked = 'N';
        constexpr char ExemptBelowLimit = '1';
        constexpr char ExemptMoneyType = '2';
        constexpr char ExemptAuthorised = '3';
    }
    namespace  ExecPriceType {
        constexpr char BidPrice = 'B';
        constexpr char CreationPrice = 'C';
        constexpr char CreationPricePlusAdjustmentPercent = 'D';
        constexpr char CreationPricePlusAdjustmentAmount = 'E';
        constexpr char OfferPrice = 'O';
        constexpr char OfferPriceMinusAdjustmentPercent = 'P';
        constexpr char OfferPriceMinusAdjustmentAmount = 'Q';
        constexpr char SinglePrice = 'S';
    }
    namespace  TradeReportTransType {
        constexpr int New = 0;
        constexpr int Cancel = 1;
        constexpr int Replace = 2;
        constexpr int Release = 3;
        constexpr int Reverse = 4;
        constexpr int CancelDueToBackOutOfTrade = 5;
    }
    namespace  PaymentMethod {
        constexpr int CREST = 1;
        constexpr int NSCC = 2;
        constexpr int Euroclear = 3;
        constexpr int Clearstream = 4;
        constexpr int Cheque = 5;
        constexpr int TelegraphicTransfer = 6;
        constexpr int FedWire = 7;
        constexpr int DebitCard = 8;
        constexpr int DirectDebit = 9;
        constexpr int DirectCredit = 10;
        constexpr int CreditCard = 11;
        constexpr int ACHDebit = 12;
        constexpr int ACHCredit = 13;
        constexpr int BPAY = 14;
        constexpr int HighValueClearingSystem = 15;
    }
    namespace  TaxAdvantageType {
        constexpr int None = 0;
        constexpr int MaxiISA = 1;
        constexpr int TESSA = 2;
        constexpr int MiniCashISA = 3;
        constexpr int MiniStocksAndSharesISA = 4;
        constexpr int MiniInsuranceISA = 5;
        constexpr int CurrentYearPayment = 6;
        constexpr int PriorYearPayment = 7;
        constexpr int AssetTransfer = 8;
        constexpr int EmployeePriorYear = 9;
        constexpr int EmployeeCurrentYear = 10;
        constexpr int EmployerPriorYear = 11;
        constexpr int EmployerCurrentYear = 12;
        constexpr int NonFundPrototypeIRA = 13;
        constexpr int NonFundQualifiedPlan = 14;
        constexpr int DefinedContributionPlan = 15;
        constexpr int IRA = 16;
        constexpr int IRARollover = 17;
        constexpr int KEOGH = 18;
        constexpr int ProfitSharingPlan = 19;
        constexpr int US401K = 20;
        constexpr int SelfDirectedIRA = 21;
        constexpr int US403b = 22;
        constexpr int US457 = 23;
        constexpr int RothIRAPrototype = 24;
        constexpr int RothIRANonPrototype = 25;
        constexpr int RothConversionIRAPrototype = 26;
        constexpr int RothConversionIRANonPrototype = 27;
        constexpr int EducationIRAPrototype = 28;
        constexpr int EducationIRANonPrototype = 29;
        constexpr int Other = 999;
    }
    namespace  FundRenewWaiv {
        constexpr char No = 'N';
        constexpr char Yes = 'Y';
    }
    namespace  RegistStatus {
        constexpr char Accepted = 'A';
        constexpr char Rejected = 'R';
        constexpr char Held = 'H';
        constexpr char Reminder = 'N';
    }
    namespace  RegistRejReasonCode {
        constexpr int InvalidAccountType = 1;
        constexpr int InvalidTaxExemptType = 2;
        constexpr int InvalidOwnershipType = 3;
        constexpr int NoRegDetails = 4;
        constexpr int InvalidRegSeqNo = 5;
        constexpr int InvalidRegDetails = 6;
        constexpr int InvalidMailingDetails = 7;
        constexpr int InvalidMailingInstructions = 8;
        constexpr int InvalidInvestorID = 9;
        constexpr int InvalidInvestorIDSource = 10;
        constexpr int InvalidDateOfBirth = 11;
        constexpr int InvalidCountry = 12;
        constexpr int InvalidDistribInstns = 13;
        constexpr int InvalidPercentage = 14;
        constexpr int InvalidPaymentMethod = 15;
        constexpr int InvalidAccountName = 16;
        constexpr int InvalidAgentCode = 17;
        constexpr int InvalidAccountNum = 18;
        constexpr int Other = 99;
    }
    namespace  RegistTransType {
        constexpr char New = '0';
        constexpr char Cancel = '2';
        constexpr char Replace = '1';
    }
    namespace  OwnershipType {
        constexpr char JointInvestors = 'J';
        constexpr char TenantsInCommon = 'T';
        constexpr char JointTrustees = '2';
    }
    namespace  ContAmtType {
        constexpr int CommissionAmount = 1;
        constexpr int CommissionPercent = 2;
        constexpr int InitialChargeAmount = 3;
        constexpr int InitialChargePercent = 4;
        constexpr int DiscountAmount = 5;
        constexpr int DiscountPercent = 6;
        constexpr int DilutionLevyAmount = 7;
        constexpr int DilutionLevyPercent = 8;
        constexpr int ExitChargeAmount = 9;
        constexpr int ExitChargePercent = 10;
        constexpr int FundBasedRenewalCommissionPercent = 11;
        constexpr int ProjectedFundValue = 12;
        constexpr int FundBasedRenewalCommissionOnOrder = 13;
        constexpr int FundBasedRenewalCommissionOnFund = 14;
        constexpr int NetSettlementAmount = 15;
    }
    namespace  OwnerType {
        constexpr int IndividualInvestor = 1;
        constexpr int PublicCompany = 2;
        constexpr int PrivateCompany = 3;
        constexpr int IndividualTrustee = 4;
        constexpr int CompanyTrustee = 5;
        constexpr int PensionPlan = 6;
        constexpr int CustodianUnderGiftsToMinorsAct = 7;
        constexpr int Trusts = 8;
        constexpr int Fiduciaries = 9;
        constexpr int NetworkingSubAccount = 10;
        constexpr int NonProfitOrganization = 11;
        constexpr int CorporateBody = 12;
        constexpr int Nominee = 13;
    }
    namespace  OrderCapacity {
        constexpr char Agency = 'A';
        constexpr char Proprietary = 'G';
        constexpr char Individual = 'I';
        constexpr char Principal = 'P';
        constexpr char RisklessPrincipal = 'R';
        constexpr char AgentForOtherMember = 'W';
    }
    namespace  OrderRestrictions {
    }
    namespace  MassCancelRequestType {
        constexpr char CancelOrdersForASecurity = '1';
        constexpr char CancelOrdersForAnUnderlyingSecurity = '2';
        constexpr char CancelOrdersForAProduct = '3';
        constexpr char CancelOrdersForACFICode = '4';
        constexpr char CancelOrdersForASecurityType = '5';
        constexpr char CancelOrdersForATradingSession = '6';
        constexpr char CancelAllOrders = '7';
        constexpr char CancelOrdersForAMarket = '8';
        constexpr char CancelOrdersForAMarketSegment = '9';
        constexpr char CancelOrdersForASecurityGroup = 'A';
    }
    namespace  MassCancelResponse {
        constexpr char CancelRequestRejected = '0';
        constexpr char CancelOrdersForASecurity = '1';
        constexpr char CancelOrdersForAnUnderlyingSecurity = '2';
        constexpr char CancelOrdersForAProduct = '3';
        constexpr char CancelOrdersForACFICode = '4';
        constexpr char CancelOrdersForASecurityType = '5';
        constexpr char CancelOrdersForATradingSession = '6';
        constexpr char CancelAllOrders = '7';
        constexpr char CancelOrdersForAMarket = '8';
        constexpr char CancelOrdersForAMarketSegment = '9';
        constexpr char CancelOrdersForASecurityGroup = 'A';
    }
    namespace  MassCancelRejectReason {
        constexpr int MassCancelNotSupported = 0;
        constexpr int InvalidOrUnknownSecurity = 1;
        constexpr int InvalidOrUnkownUnderlyingSecurity = 2;
        constexpr int InvalidOrUnknownProduct = 3;
        constexpr int InvalidOrUnknownCFICode = 4;
        constexpr int InvalidOrUnknownSecurityType = 5;
        constexpr int InvalidOrUnknownTradingSession = 6;
        constexpr int InvalidOrUnknownMarket = 7;
        constexpr int InvalidOrUnkownMarketSegment = 8;
        constexpr int InvalidOrUnknownSecurityGroup = 9;
        constexpr int Other = 99;
    }
    namespace  QuoteType {
        constexpr int Indicative = 0;
        constexpr int Tradeable = 1;
        constexpr int RestrictedTradeable = 2;
        constexpr int Counter = 3;
    }
    namespace  CashMargin {
        constexpr char Cash = '1';
        constexpr char MarginOpen = '2';
        constexpr char MarginClose = '3';
    }
    namespace  Scope {
    }
    namespace  MDImplicitDelete {
        constexpr char No = 'N';
        constexpr char Yes = 'Y';
    }
    namespace  CrossType {
        constexpr int CrossAON = 1;
        constexpr int CrossIOC = 2;
        constexpr int CrossOneSide = 3;
        constexpr int CrossSamePrice = 4;
    }
    namespace  CrossPrioritization {
        constexpr int None = 0;
        constexpr int BuySideIsPrioritized = 1;
        constexpr int SellSideIsPrioritized = 2;
    }
    namespace  NoSides {
    }
    namespace  SecurityListRequestType {
        constexpr int Symbol = 0;
        constexpr int SecurityTypeAnd = 1;
        constexpr int Product = 2;
        constexpr int TradingSessionID = 3;
        constexpr int AllSecurities = 4;
        constexpr int MarketIDOrMarketID = 5;
    }
    namespace  SecurityRequestResult {
        constexpr int ValidRequest = 0;
        constexpr int InvalidOrUnsupportedRequest = 1;
        constexpr int NoInstrumentsFound = 2;
        constexpr int NotAuthorizedToRetrieveInstrumentData = 3;
        constexpr int InstrumentDataTemporarilyUnavailable = 4;
        constexpr int RequestForInstrumentDataNotSupported = 5;
    }
    namespace  MultiLegRptTypeReq {
        constexpr int ReportByMulitlegSecurityOnly = 0;
        constexpr int ReportByMultilegSecurityAndInstrumentLegs = 1;
        constexpr int ReportByInstrumentLegsOnly = 2;
    }
    namespace  TradSesStatusRejReason {
        constexpr int UnknownOrInvalidTradingSessionID = 1;
        constexpr int Other = 99;
    }
    namespace  TradeRequestType {
        constexpr int AllTrades = 0;
        constexpr int MatchedTradesMatchingCriteria = 1;
        constexpr int UnmatchedTradesThatMatchCriteria = 2;
        constexpr int UnreportedTradesThatMatchCriteria = 3;
        constexpr int AdvisoriesThatMatchCriteria = 4;
    }
    namespace  PreviouslyReported {
        constexpr char NotReportedToCounterparty = 'N';
        constexpr char PerviouslyReportedToCounterparty = 'Y';
    }
    namespace  MatchStatus {
        constexpr char Compared = '0';
        constexpr char Uncompared = '1';
        constexpr char AdvisoryOrAlert = '2';
    }
    namespace  MatchType {
        constexpr char OnePartyTradeReport = '1';
        constexpr char TwoPartyTradeReport = '2';
        constexpr char ConfirmedTradeReport = '3';
        constexpr char AutoMatch = '4';
        constexpr char CrossAuction = '5';
        constexpr char CounterOrderSelection = '6';
        constexpr char CallAuction = '7';
        constexpr char Issuing = '8';
        constexpr std::string_view ACTAcceptedTrade = "M3";
        constexpr std::string_view ACTDefaultTrade = "M4";
        constexpr std::string_view ACTDefaultAfterM2 = "M5";
        constexpr std::string_view ACTM6Match = "M6";
        constexpr std::string_view ExactMatchPlus4BadgesExecTime = "A1";
        constexpr std::string_view ExactMatchPlus4Badges = "A2";
        constexpr std::string_view ExactMatchPlus2BadgesExecTime = "A3";
        constexpr std::string_view ExactMatchPlus2Badges = "A4";
        constexpr std::string_view ExactMatchPlusExecTime = "A5";
        constexpr std::string_view StampedAdvisoriesOrSpecialistAccepts = "AQ";
        constexpr std::string_view A1ExactMatchSummarizedQuantity = "S1";
        constexpr std::string_view A2ExactMatchSummarizedQuantity = "S2";
        constexpr std::string_view A3ExactMatchSummarizedQuantity = "S3";
        constexpr std::string_view A4ExactMatchSummarizedQuantity = "S4";
        constexpr std::string_view A5ExactMatchSummarizedQuantity = "S5";
        constexpr std::string_view ExactMatchMinusBadgesTimes = "M1";
        constexpr std::string_view SummarizedMatchMinusBadgesTimes = "M2";
        constexpr std::string_view OCSLockedIn = "MT";
    }
    namespace  OddLot {
        constexpr char TreatAsRoundLot = 'N';
        constexpr char TreatAsOddLot = 'Y';
    }
    namespace  ClearingInstruction {
        constexpr int ProcessNormally = 0;
        constexpr int ExcludeFromAllNetting = 1;
        constexpr int BilateralNettingOnly = 2;
        constexpr int ExClearing = 3;
        constexpr int SpecialTrade = 4;
        constexpr int MultilateralNetting = 5;
        constexpr int ClearAgainstCentralCounterparty = 6;
        constexpr int ExcludeFromCentralCounterparty = 7;
        constexpr int ManualMode = 8;
        constexpr int AutomaticPostingMode = 9;
        constexpr int AutomaticGiveUpMode = 10;
        constexpr int QualifiedServiceRepresentativeQSR = 11;
        constexpr int CustomerTrade = 12;
        constexpr int SelfClearing = 13;
    }
    namespace  AccountType {
        constexpr int CarriedCustomerSide = 1;
        constexpr int CarriedNonCustomerSide = 2;
        constexpr int HouseTrader = 3;
        constexpr int FloorTrader = 4;
        constexpr int CarriedNonCustomerSideCrossMargined = 6;
        constexpr int HouseTraderCrossMargined = 7;
        constexpr int JointBackOfficeAccount = 8;
    }
    namespace  CustOrderCapacity {
        constexpr int MemberTradingForTheirOwnAccount = 1;
        constexpr int ClearingFirmTradingForItsProprietaryAccount = 2;
        constexpr int MemberTradingForAnotherMember = 3;
        constexpr int AllOther = 4;
    }
    namespace  MassStatusReqType {
        constexpr int StatusForOrdersForASecurity = 1;
        constexpr int StatusForOrdersForAnUnderlyingSecurity = 2;
        constexpr int StatusForOrdersForAProduct = 3;
        constexpr int StatusForOrdersForACFICode = 4;
        constexpr int StatusForOrdersForASecurityType = 5;
        constexpr int StatusForOrdersForATradingSession = 6;
        constexpr int StatusForAllOrders = 7;
        constexpr int StatusForOrdersForAPartyID = 8;
    }
    namespace  DayBookingInst {
        constexpr char Auto = '0';
        constexpr char SpeakWithOrderInitiatorBeforeBooking = '1';
        constexpr char Accumulate = '2';
    }
    namespace  BookingUnit {
        constexpr char EachPartialExecutionIsABookableUnit = '0';
        constexpr char AggregatePartialExecutionsOnThisOrder = '1';
        constexpr char AggregateExecutionsForThisSymbol = '2';
    }
    namespace  PreallocMethod {
        constexpr char ProRata = '0';
        constexpr char DoNotProRata = '1';
    }
    namespace  TradingSessionSubID {
        constexpr char PreTrading = '1';
        constexpr char OpeningOrOpeningAuction = '2';
        constexpr char Continuous = '3';
        constexpr char ClosingOrClosingAuction = '4';
        constexpr char PostTrading = '5';
        constexpr char IntradayAuction = '6';
        constexpr char Quiescent = '7';
    }
    namespace  AllocType {
        constexpr int Calculated = 1;
        constexpr int Preliminary = 2;
        constexpr int SellsideCalculatedUsingPreliminary = 3;
        constexpr int SellsideCalculatedWithoutPreliminary = 4;
        constexpr int ReadyToBook = 5;
        constexpr int BuysideReadyToBook = 6;
        constexpr int WarehouseInstruction = 7;
        constexpr int RequestToIntermediary = 8;
        constexpr int Accept = 9;
        constexpr int Reject = 10;
        constexpr int AcceptPending = 11;
        constexpr int IncompleteGroup = 12;
        constexpr int CompleteGroup = 13;
        constexpr int ReversalPending = 14;
    }
    namespace  ClearingFeeIndicator {
        constexpr char FirstYearDelegate = '1';
        constexpr char SecondYearDelegate = '2';
        constexpr char ThirdYearDelegate = '3';
        constexpr char FourthYearDelegate = '4';
        constexpr char FifthYearDelegate = '5';
        constexpr char SixthYearDelegate = '9';
        constexpr char CBOEMember = 'B';
        constexpr char NonMemberAndCustomer = 'C';
        constexpr char EquityMemberAndClearingMember = 'E';
        constexpr char FullAndAssociateMember = 'F';
        constexpr char Firms106HAnd106J = 'H';
        constexpr char GIM = 'I';
        constexpr char Lessee106FEmployees = 'L';
        constexpr char AllOtherOwnershipTypes = 'M';
    }
    namespace  WorkingIndicator {
        constexpr char NotWorking = 'N';
        constexpr char Working = 'Y';
    }
    namespace  PriorityIndicator {
        constexpr int PriorityUnchanged = 0;
        constexpr int LostPriorityAsResultOfOrderChange = 1;
    }
    namespace  LegalConfirm {
        constexpr char DoesNotConsituteALegalConfirm = 'N';
        constexpr char LegalConfirm = 'Y';
    }
    namespace  QuoteRequestRejectReason {
        constexpr int UnknownSymbol = 1;
        constexpr int Exchange = 2;
        constexpr int QuoteRequestExceedsLimit = 3;
        constexpr int TooLateToEnter = 4;
        constexpr int InvalidPrice = 5;
        constexpr int NotAuthorizedToRequestQuote = 6;
        constexpr int NoMatchForInquiry = 7;
        constexpr int NoMarketForInstrument = 8;
        constexpr int NoInventory = 9;
        constexpr int Pass = 10;
        constexpr int InsufficientCredit = 11;
        constexpr int Other = 99;
    }
    namespace  AcctIDSource {
        constexpr int BIC = 1;
        constexpr int SIDCode = 2;
        constexpr int TFM = 3;
        constexpr int OMGEO = 4;
        constexpr int DTCCCode = 5;
        constexpr int Other = 99;
    }
    namespace  ConfirmStatus {
        constexpr int Received = 1;
        constexpr int MismatchedAccount = 2;
        constexpr int MissingSettlementInstructions = 3;
        constexpr int Confirmed = 4;
        constexpr int RequestRejected = 5;
    }
    namespace  ConfirmTransType {
        constexpr int New = 0;
        constexpr int Replace = 1;
        constexpr int Cancel = 2;
    }
    namespace  DeliveryForm {
        constexpr int BookEntry = 1;
        constexpr int Bearer = 2;
    }
    namespace  LegSwapType {
        constexpr int ParForPar = 1;
        constexpr int ModifiedDuration = 2;
        constexpr int Risk = 4;
        constexpr int Proceeds = 5;
    }
    namespace  QuotePriceType {
        constexpr int Percent = 1;
        constexpr int PerShare = 2;
        constexpr int FixedAmount = 3;
        constexpr int Discount = 4;
        constexpr int Premium = 5;
        constexpr int Spread = 6;
        constexpr int TEDPrice = 7;
        constexpr int TEDYield = 8;
        constexpr int YieldSpread = 9;
        constexpr int Yield = 10;
    }
    namespace  QuoteRespType {
        constexpr int Hit = 1;
        constexpr int Counter = 2;
        constexpr int Expired = 3;
        constexpr int Cover = 4;
        constexpr int DoneAway = 5;
        constexpr int Pass = 6;
        constexpr int EndTrade = 7;
        constexpr int TimedOut = 8;
    }
    namespace  PosType {
        constexpr std::string_view AllocationTradeQty = "ALC";
        constexpr std::string_view OptionAssignment = "AS";
        constexpr std::string_view AsOfTradeQty = "ASF";
        constexpr std::string_view DeliveryQty = "DLV";
        constexpr std::string_view ElectronicTradeQty = "ETR";
        constexpr std::string_view OptionExerciseQty = "EX";
        constexpr std::string_view EndOfDayQty = "FIN";
        constexpr std::string_view IntraSpreadQty = "IAS";
        constexpr std::string_view InterSpreadQty = "IES";
        constexpr std::string_view AdjustmentQty = "PA";
        constexpr std::string_view PitTradeQty = "PIT";
        constexpr std::string_view StartOfDayQty = "SOD";
        constexpr std::string_view IntegralSplit = "SPL";
        constexpr std::string_view TransactionFromAssignment = "TA";
        constexpr std::string_view TotalTransactionQty = "TOT";
        constexpr std::string_view TransactionQuantity = "TQ";
        constexpr std::string_view TransferTradeQty = "TRF";
        constexpr std::string_view TransactionFromExercise = "TX";
        constexpr std::string_view CrossMarginQty = "XM";
        constexpr std::string_view ReceiveQuantity = "RCV";
        constexpr std::string_view CorporateActionAdjustment = "CAA";
        constexpr std::string_view DeliveryNoticeQty = "DN";
        constexpr std::string_view ExchangeForPhysicalQty = "EP";
        constexpr std::string_view PrivatelyNegotiatedTradeQty = "PNTN";
    }
    namespace  PosQtyStatus {
        constexpr int Submitted = 0;
        constexpr int Accepted = 1;
        constexpr int Rejected = 2;
    }
    namespace  PosAmtType {
        constexpr std::string_view CashAmount = "CASH";
        constexpr std::string_view CashResidualAmount = "CRES";
        constexpr std::string_view FinalMarkToMarketAmount = "FMTM";
        constexpr std::string_view IncrementalMarkToMarketAmount = "IMTM";
        constexpr std::string_view PremiumAmount = "PREM";
        constexpr std::string_view StartOfDayMarkToMarketAmount = "SMTM";
        constexpr std::string_view TradeVariationAmount = "TVAR";
        constexpr std::string_view ValueAdjustedAmount = "VADJ";
        constexpr std::string_view SettlementValue = "SETL";
    }
    namespace  PosTransType {
        constexpr int Exercise = 1;
        constexpr int DoNotExercise = 2;
        constexpr int PositionAdjustment = 3;
        constexpr int PositionChangeSubmission = 4;
        constexpr int Pledge = 5;
        constexpr int LargeTraderSubmission = 6;
    }
    namespace  PosMaintAction {
        constexpr int New = 1;
        constexpr int Replace = 2;
        constexpr int Cancel = 3;
        constexpr int Reverse = 4;
    }
    namespace  SettlSessID {
        constexpr std::string_view Intraday = "ITD";
        constexpr std::string_view RegularTradingHours = "RTH";
        constexpr std::string_view ElectronicTradingHours = "ETH";
        constexpr std::string_view EndOfDay = "EOD";
    }
    namespace  AdjustmentType {
        constexpr int ProcessRequestAsMarginDisposition = 0;
        constexpr int DeltaPlus = 1;
        constexpr int DeltaMinus = 2;
        constexpr int Final = 3;
    }
    namespace  PosMaintStatus {
        constexpr int Accepted = 0;
        constexpr int AcceptedWithWarnings = 1;
        constexpr int Rejected = 2;
        constexpr int Completed = 3;
        constexpr int CompletedWithWarnings = 4;
    }
    namespace  PosMaintResult {
        constexpr int SuccessfulCompletion = 0;
        constexpr int Rejected = 1;
        constexpr int Other = 99;
    }
    namespace  PosReqType {
        constexpr int Positions = 0;
        constexpr int Trades = 1;
        constexpr int Exercises = 2;
        constexpr int Assignments = 3;
        constexpr int SettlementActivity = 4;
        constexpr int BackoutMessage = 5;
    }
    namespace  ResponseTransportType {
        constexpr int Inband = 0;
        constexpr int OutOfBand = 1;
    }
    namespace  PosReqResult {
        constexpr int ValidRequest = 0;
        constexpr int InvalidOrUnsupportedRequest = 1;
        constexpr int NoPositionsFoundThatMatchCriteria = 2;
        constexpr int NotAuthorizedToRequestPositions = 3;
        constexpr int RequestForPositionNotSupported = 4;
        constexpr int Other = 99;
    }
    namespace  PosReqStatus {
        constexpr int Completed = 0;
        constexpr int CompletedWithWarnings = 1;
        constexpr int Rejected = 2;
    }
    namespace  SettlPriceType {
        constexpr int Final = 1;
        constexpr int Theoretical = 2;
    }
    namespace  AssignmentMethod {
        constexpr char ProRata = 'P';
        constexpr char Random = 'R';
    }
    namespace  ExerciseMethod {
        constexpr char Automatic = 'A';
        constexpr char Manual = 'M';
    }
    namespace  TradeRequestResult {
        constexpr int Successful = 0;
        constexpr int InvalidOrUnknownInstrument = 1;
        constexpr int InvalidTypeOfTradeRequested = 2;
        constexpr int InvalidParties = 3;
        constexpr int InvalidTransportTypeRequested = 4;
        constexpr int InvalidDestinationRequested = 5;
        constexpr int TradeRequestTypeNotSupported = 8;
        constexpr int NotAuthorized = 9;
        constexpr int Other = 99;
    }
    namespace  TradeRequestStatus {
        constexpr int Accepted = 0;
        constexpr int Completed = 1;
        constexpr int Rejected = 2;
    }
    namespace  TradeReportRejectReason {
        constexpr int Successful = 0;
        constexpr int InvalidPartyOnformation = 1;
        constexpr int UnknownInstrument = 2;
        constexpr int UnauthorizedToReportTrades = 3;
        constexpr int InvalidTradeType = 4;
        constexpr int Other = 99;
    }
    namespace  SideMultiLegReportingType {
        constexpr int SingleSecurity = 1;
        constexpr int IndividualLegOfAMultilegSecurity = 2;
        constexpr int MultilegSecurity = 3;
    }
    namespace  TrdRegTimestampType {
        constexpr int ExecutionTime = 1;
        constexpr int TimeIn = 2;
        constexpr int TimeOut = 3;
        constexpr int BrokerReceipt = 4;
        constexpr int BrokerExecution = 5;
        constexpr int DeskReceipt = 6;
    }
    namespace  ConfirmType {
        constexpr int Status = 1;
        constexpr int Confirmation = 2;
        constexpr int ConfirmationRequestRejected = 3;
    }
    namespace  ConfirmRejReason {
        constexpr int MismatchedAccount = 1;
        constexpr int MissingSettlementInstructions = 2;
        constexpr int Other = 99;
    }
    namespace  BookingType {
        constexpr int RegularBooking = 0;
        constexpr int CFD = 1;
        constexpr int TotalReturnSwap = 2;
    }
    namespace  AllocSettlInstType {
        constexpr int UseDefaultInstructions = 0;
        constexpr int DeriveFromParametersProvided = 1;
        constexpr int FullDetailsProvided = 2;
        constexpr int SSIDBIDsProvided = 3;
        constexpr int PhoneForInstructions = 4;
    }
    namespace  DlvyInstType {
        constexpr char Cash = 'C';
        constexpr char Securities = 'S';
    }
    namespace  TerminationType {
        constexpr int Overnight = 1;
        constexpr int Term = 2;
        constexpr int Flexible = 3;
        constexpr int Open = 4;
    }
    namespace  SettlInstReqRejCode {
        constexpr int UnableToProcessRequest = 0;
        constexpr int UnknownAccount = 1;
        constexpr int NoMatchingSettlementInstructionsFound = 2;
        constexpr int Other = 99;
    }
    namespace  AllocReportType {
        constexpr int PreliminaryRequestToIntermediary = 2;
        constexpr int SellsideCalculatedUsingPreliminary = 3;
        constexpr int SellsideCalculatedWithoutPreliminary = 4;
        constexpr int WarehouseRecap = 5;
        constexpr int RequestToIntermediary = 8;
        constexpr int Accept = 9;
        constexpr int Reject = 10;
        constexpr int AcceptPending = 11;
        constexpr int Complete = 12;
        constexpr int ReversePending = 14;
    }
    namespace  AllocCancReplaceReason {
        constexpr int OriginalDetailsIncomplete = 1;
        constexpr int ChangeInUnderlyingOrderDetails = 2;
        constexpr int Other = 99;
    }
    namespace  AllocAccountType {
        constexpr int CarriedCustomerSide = 1;
        constexpr int CarriedNonCustomerSide = 2;
        constexpr int HouseTrader = 3;
        constexpr int FloorTrader = 4;
        constexpr int CarriedNonCustomerSideCrossMargined = 6;
        constexpr int HouseTraderCrossMargined = 7;
        constexpr int JointBackOfficeAccount = 8;
    }
    namespace  PartySubIDType {
        constexpr int Firm = 1;
        constexpr int Person = 2;
        constexpr int System = 3;
        constexpr int Application = 4;
        constexpr int FullLegalNameOfFirm = 5;
        constexpr int PostalAddress = 6;
        constexpr int PhoneNumber = 7;
        constexpr int EmailAddress = 8;
        constexpr int ContactName = 9;
        constexpr int SecuritiesAccountNumber = 10;
        constexpr int RegistrationNumber = 11;
        constexpr int RegisteredAddressForConfirmation = 12;
        constexpr int RegulatoryStatus = 13;
        constexpr int RegistrationName = 14;
        constexpr int CashAccountNumber = 15;
        constexpr int BIC = 16;
        constexpr int CSDParticipantMemberCode = 17;
        constexpr int RegisteredAddress = 18;
        constexpr int FundAccountName = 19;
        constexpr int TelexNumber = 20;
        constexpr int FaxNumber = 21;
        constexpr int SecuritiesAccountName = 22;
        constexpr int CashAccountName = 23;
        constexpr int Department = 24;
        constexpr int LocationDesk = 25;
        constexpr int PositionAccountType = 26;
        constexpr int SecurityLocateID = 27;
        constexpr int MarketMaker = 28;
        constexpr int EligibleCounterparty = 29;
        constexpr int ProfessionalClient = 30;
        constexpr int Location = 31;
        constexpr int ExecutionVenue = 32;
        constexpr int CurrencyDeliveryIdentifier = 33;
    }
    namespace  AllocIntermedReqType {
        constexpr int PendingAccept = 1;
        constexpr int PendingRelease = 2;
        constexpr int PendingReversal = 3;
        constexpr int Accept = 4;
        constexpr int BlockLevelReject = 5;
        constexpr int AccountLevelReject = 6;
    }
    namespace  ApplQueueResolution {
        constexpr int NoActionTaken = 0;
        constexpr int QueueFlushed = 1;
        constexpr int OverlayLast = 2;
        constexpr int EndSession = 3;
    }
    namespace  ApplQueueAction {
        constexpr int NoActionTaken = 0;
        constexpr int QueueFlushed = 1;
        constexpr int OverlayLast = 2;
        constexpr int EndSession = 3;
    }
    namespace  AvgPxIndicator {
        constexpr int NoAveragePricing = 0;
        constexpr int Trade = 1;
        constexpr int LastTrade = 2;
    }
    namespace  TradeAllocIndicator {
        constexpr int AllocationNotRequired = 0;
        constexpr int AllocationRequired = 1;
        constexpr int UseAllocationProvidedWithTheTrade = 2;
        constexpr int AllocationGiveUpExecutor = 3;
        constexpr int AllocationFromExecutor = 4;
        constexpr int AllocationToClaimAccount = 5;
    }
    namespace  ExpirationCycle {
        constexpr int ExpireOnTradingSessionClose = 0;
        constexpr int ExpireOnTradingSessionOpen = 1;
        constexpr int SpecifiedExpiration = 2;
    }
    namespace  TrdType {
        constexpr int RegularTrade = 0;
        constexpr int BlockTrade = 1;
        constexpr int EFP = 2;
        constexpr int Transfer = 3;
        constexpr int LateTrade = 4;
        constexpr int TTrade = 5;
        constexpr int WeightedAveragePriceTrade = 6;
        constexpr int BunchedTrade = 7;
        constexpr int LateBunchedTrade = 8;
        constexpr int PriorReferencePriceTrade = 9;
        constexpr int AfterHoursTrade = 10;
        constexpr int ExchangeForRisk = 11;
        constexpr int ExchangeForSwap = 12;
        constexpr int ExchangeOfFuturesFor = 13;
        constexpr int ExchangeOfOptionsForOptions = 14;
        constexpr int TradingAtSettlement = 15;
        constexpr int AllOrNone = 16;
        constexpr int FuturesLargeOrderExecution = 17;
        constexpr int ExchangeOfFuturesForFutures = 18;
        constexpr int OptionInterimTrade = 19;
        constexpr int OptionCabinetTrade = 20;
        constexpr int PrivatelyNegotiatedTrades = 22;
        constexpr int SubstitutionOfFuturesForForwards = 23;
        constexpr int NonStandardSettlement = 48;
        constexpr int DerivativeRelatedTransaction = 49;
        constexpr int PortfolioTrade = 50;
        constexpr int VolumeWeightedAverageTrade = 51;
        constexpr int ExchangeGrantedTrade = 52;
        constexpr int RepurchaseAgreement = 53;
        constexpr int OTC = 54;
        constexpr int ExchangeBasisFacility = 55;
        constexpr int ErrorTrade = 24;
        constexpr int SpecialCumDividend = 25;
        constexpr int SpecialExDividend = 26;
        constexpr int SpecialCumCoupon = 27;
        constexpr int SpecialExCoupon = 28;
        constexpr int CashSettlement = 29;
        constexpr int SpecialPrice = 30;
        constexpr int GuaranteedDelivery = 31;
        constexpr int SpecialCumRights = 32;
        constexpr int SpecialExRights = 33;
        constexpr int SpecialCumCapitalRepayments = 34;
        constexpr int SpecialExCapitalRepayments = 35;
        constexpr int SpecialCumBonus = 36;
        constexpr int SpecialExBonus = 37;
        constexpr int LargeTrade = 38;
        constexpr int WorkedPrincipalTrade = 39;
        constexpr int BlockTrades = 40;
        constexpr int NameChange = 41;
        constexpr int PortfolioTransfer = 42;
        constexpr int ProrogationBuy = 43;
        constexpr int ProrogationSell = 44;
        constexpr int OptionExercise = 45;
        constexpr int DeltaNeutralTransaction = 46;
        constexpr int FinancingTransaction = 47;
    }
    namespace  TrdSubType {
        constexpr int CMTA = 0;
        constexpr int InternalTransferOrAdjustment = 1;
        constexpr int ExternalTransferOrTransferOfAccount = 2;
        constexpr int RejectForSubmittingSide = 3;
        constexpr int AdvisoryForContraSide = 4;
        constexpr int OffsetDueToAnAllocation = 5;
        constexpr int OnsetDueToAnAllocation = 6;
        constexpr int DifferentialSpread = 7;
        constexpr int ImpliedSpreadLegExecutedAgainstAnOutright = 8;
        constexpr int TransactionFromExercise = 9;
        constexpr int TransactionFromAssignment = 10;
        constexpr int ACATS = 11;
        constexpr int OffHoursTrade = 33;
        constexpr int OnHoursTrade = 34;
        constexpr int OTCQuote = 35;
        constexpr int ConvertedSWAP = 36;
        constexpr int AI = 14;
        constexpr int B = 15;
        constexpr int K = 16;
        constexpr int LC = 17;
        constexpr int M = 18;
        constexpr int N = 19;
        constexpr int NM = 20;
        constexpr int NR = 21;
        constexpr int P = 22;
        constexpr int PA = 23;
        constexpr int PC = 24;
        constexpr int PN = 25;
        constexpr int R = 26;
        constexpr int RO = 27;
        constexpr int RT = 28;
        constexpr int SW = 29;
        constexpr int T = 30;
        constexpr int WN = 31;
        constexpr int WT = 32;
        constexpr int CrossedTrade = 37;
        constexpr int InterimProtectedTrade = 38;
        constexpr int LargeInScale = 39;
    }
    namespace  PegMoveType {
        constexpr int Floating = 0;
        constexpr int Fixed = 1;
    }
    namespace  PegOffsetType {
        constexpr int Price = 0;
        constexpr int BasisPoints = 1;
        constexpr int Ticks = 2;
        constexpr int PriceTier = 3;
    }
    namespace  PegLimitType {
        constexpr int OrBetter = 0;
        constexpr int Strict = 1;
        constexpr int OrWorse = 2;
    }
    namespace  PegRoundDirection {
        constexpr int MoreAggressive = 1;
        constexpr int MorePassive = 2;
    }
    namespace  PegScope {
        constexpr int Local = 1;
        constexpr int National = 2;
        constexpr int Global = 3;
        constexpr int NationalExcludingLocal = 4;
    }
    namespace  DiscretionMoveType {
        constexpr int Floating = 0;
        constexpr int Fixed = 1;
    }
    namespace  DiscretionOffsetType {
        constexpr int Price = 0;
        constexpr int BasisPoints = 1;
        constexpr int Ticks = 2;
        constexpr int PriceTier = 3;
    }
    namespace  DiscretionLimitType {
        constexpr int OrBetter = 0;
        constexpr int Strict = 1;
        constexpr int OrWorse = 2;
    }
    namespace  DiscretionRoundDirection {
        constexpr int MoreAggressive = 1;
        constexpr int MorePassive = 2;
    }
    namespace  DiscretionScope {
        constexpr int Local = 1;
        constexpr int National = 2;
        constexpr int Global = 3;
        constexpr int NationalExcludingLocal = 4;
    }
    namespace  TargetStrategy {
        constexpr int VWAP = 1;
        constexpr int Participate = 2;
        constexpr int MininizeMarketImpact = 3;
    }
    namespace  LastLiquidityInd {
        constexpr int AddedLiquidity = 1;
        constexpr int RemovedLiquidity = 2;
        constexpr int LiquidityRoutedOut = 3;
        constexpr int Auction = 4;
    }
    namespace  PublishTrdIndicator {
        constexpr char DoNotReportTrade = 'N';
        constexpr char ReportTrade = 'Y';
    }
    namespace  ShortSaleReason {
        constexpr int DealerSoldShort = 0;
        constexpr int DealerSoldShortExempt = 1;
        constexpr int SellingCustomerSoldShort = 2;
        constexpr int SellingCustomerSoldShortExempt = 3;
        constexpr int QualifiedServiceRepresentative = 4;
        constexpr int QSROrAGUContraSideSoldShortExempt = 5;
    }
    namespace  QtyType {
        constexpr int Units = 0;
        constexpr int Contracts = 1;
        constexpr int UnitsOfMeasurePerTimeUnit = 2;
    }
    namespace  TradeReportType {
        constexpr int Submit = 0;
        constexpr int Alleged = 1;
        constexpr int Accept = 2;
        constexpr int Decline = 3;
        constexpr int Addendum = 4;
        constexpr int No = 5;
        constexpr int TradeReportCancel = 6;
        constexpr int LockedIn = 7;
        constexpr int Defaulted = 8;
        constexpr int InvalidCMTA = 9;
        constexpr int Pended = 10;
        constexpr int AllegedNew = 11;
        constexpr int AllegedAddendum = 12;
        constexpr int AllegedNo = 13;
        constexpr int AllegedTradeReportCancel = 14;
        constexpr int AllegedTradeBreak = 15;
    }
    namespace  AllocNoOrdersType {
        constexpr int NotSpecified = 0;
        constexpr int ExplicitListProvided = 1;
    }
    namespace  EventType {
        constexpr int Put = 1;
        constexpr int Call = 2;
        constexpr int Tender = 3;
        constexpr int SinkingFundCall = 4;
        constexpr int Activation = 5;
        constexpr int Inactiviation = 6;
        constexpr int LastEligibleTradeDate = 7;
        constexpr int SwapStartDate = 8;
        constexpr int SwapEndDate = 9;
        constexpr int SwapRollDate = 10;
        constexpr int SwapNextStartDate = 11;
        constexpr int SwapNextRollDate = 12;
        constexpr int FirstDeliveryDate = 13;
        constexpr int LastDeliveryDate = 14;
        constexpr int InitialInventoryDueDate = 15;
        constexpr int FinalInventoryDueDate = 16;
        constexpr int FirstIntentDate = 17;
        constexpr int LastIntentDate = 18;
        constexpr int PositionRemovalDate = 19;
        constexpr int Other = 99;
    }
    namespace  InstrAttribType {
        constexpr int Flat = 1;
        constexpr int ZeroCoupon = 2;
        constexpr int InterestBearing = 3;
        constexpr int NoPeriodicPayments = 4;
        constexpr int VariableRate = 5;
        constexpr int LessFeeForPut = 6;
        constexpr int SteppedCoupon = 7;
        constexpr int CouponPeriod = 8;
        constexpr int When = 9;
        constexpr int OriginalIssueDiscount = 10;
        constexpr int Callable = 11;
        constexpr int EscrowedToMaturity = 12;
        constexpr int EscrowedToRedemptionDate = 13;
        constexpr int PreRefunded = 14;
        constexpr int InDefault = 15;
        constexpr int Unrated = 16;
        constexpr int Taxable = 17;
        constexpr int Indexed = 18;
        constexpr int SubjectToAlternativeMinimumTax = 19;
        constexpr int OriginalIssueDiscountPrice = 20;
        constexpr int CallableBelowMaturityValue = 21;
        constexpr int CallableWithoutNotice = 22;
        constexpr int PriceTickRulesForSecurity = 23;
        constexpr int TradeTypeEligibilityDetailsForSecurity = 24;
        constexpr int InstrumentDenominator = 25;
        constexpr int InstrumentNumerator = 26;
        constexpr int InstrumentPricePrecision = 27;
        constexpr int InstrumentStrikePrice = 28;
        constexpr int TradeableIndicator = 29;
        constexpr int Text = 99;
    }
    namespace  CPProgram {
        constexpr int Program3a3 = 1;
        constexpr int Program42 = 2;
        constexpr int Other = 99;
    }
    namespace  MiscFeeBasis {
        constexpr int Absolute = 0;
        constexpr int PerUnit = 1;
        constexpr int Percentage = 2;
    }
    namespace  LastFragment {
        constexpr char NotLastMessage = 'N';
        constexpr char LastMessage = 'Y';
    }
    namespace  CollAsgnReason {
        constexpr int Initial = 0;
        constexpr int Scheduled = 1;
        constexpr int TimeWarning = 2;
        constexpr int MarginDeficiency = 3;
        constexpr int MarginExcess = 4;
        constexpr int ForwardCollateralDemand = 5;
        constexpr int EventOfDefault = 6;
        constexpr int AdverseTaxEvent = 7;
    }
    namespace  CollInquiryQualifier {
        constexpr int TradeDate = 0;
        constexpr int GCInstrument = 1;
        constexpr int CollateralInstrument = 2;
        constexpr int SubstitutionEligible = 3;
        constexpr int NotAssigned = 4;
        constexpr int PartiallyAssigned = 5;
        constexpr int FullyAssigned = 6;
        constexpr int OutstandingTrades = 7;
    }
    namespace  CollAsgnTransType {
        constexpr int New = 0;
        constexpr int Replace = 1;
        constexpr int Cancel = 2;
        constexpr int Release = 3;
        constexpr int Reverse = 4;
    }
    namespace  CollAsgnRespType {
        constexpr int Received = 0;
        constexpr int Accepted = 1;
        constexpr int Declined = 2;
        constexpr int Rejected = 3;
    }
    namespace  CollAsgnRejectReason {
        constexpr int UnknownDeal = 0;
        constexpr int UnknownOrInvalidInstrument = 1;
        constexpr int UnauthorizedTransaction = 2;
        constexpr int InsufficientCollateral = 3;
        constexpr int InvalidTypeOfCollateral = 4;
        constexpr int ExcessiveSubstitution = 5;
        constexpr int Other = 99;
    }
    namespace  CollStatus {
        constexpr int Unassigned = 0;
        constexpr int PartiallyAssigned = 1;
        constexpr int AssignmentProposed = 2;
        constexpr int Assigned = 3;
        constexpr int Challenged = 4;
    }
    namespace  LastRptRequested {
        constexpr char NotLastMessage = 'N';
        constexpr char LastMessage = 'Y';
    }
    namespace  DeliveryType {
        constexpr int VersusPayment = 0;
        constexpr int Free = 1;
        constexpr int TriParty = 2;
        constexpr int HoldInCustody = 3;
    }
    namespace  UserRequestType {
        constexpr int LogOnUser = 1;
        constexpr int LogOffUser = 2;
        constexpr int ChangePasswordForUser = 3;
        constexpr int RequestIndividualUserStatus = 4;
    }
    namespace  UserStatus {
        constexpr int LoggedIn = 1;
        constexpr int NotLoggedIn = 2;
        constexpr int UserNotRecognised = 3;
        constexpr int PasswordIncorrect = 4;
        constexpr int PasswordChanged = 5;
        constexpr int Other = 6;
        constexpr int ForcedUserLogoutByExchange = 7;
        constexpr int SessionShutdownWarning = 8;
    }
    namespace  StatusValue {
        constexpr int Connected = 1;
        constexpr int NotConnectedUnexpected = 2;
        constexpr int NotConnectedExpected = 3;
        constexpr int InProcess = 4;
    }
    namespace  NetworkRequestType {
        constexpr int Snapshot = 1;
        constexpr int Subscribe = 2;
        constexpr int StopSubscribing = 4;
        constexpr int LevelOfDetail = 8;
    }
    namespace  NetworkStatusResponseType {
        constexpr int Full = 1;
        constexpr int IncrementalUpdate = 2;
    }
    namespace  TrdRptStatus {
        constexpr int Accepted = 0;
        constexpr int Rejected = 1;
        constexpr int AcceptedWithErrors = 3;
    }
    namespace  AffirmStatus {
        constexpr int Received = 1;
        constexpr int ConfirmRejected = 2;
        constexpr int Affirmed = 3;
    }
    namespace  CollAction {
        constexpr int Retain = 0;
        constexpr int Add = 1;
        constexpr int Remove = 2;
    }
    namespace  CollInquiryStatus {
        constexpr int Accepted = 0;
        constexpr int AcceptedWithWarnings = 1;
        constexpr int Completed = 2;
        constexpr int CompletedWithWarnings = 3;
        constexpr int Rejected = 4;
    }
    namespace  CollInquiryResult {
        constexpr int Successful = 0;
        constexpr int InvalidOrUnknownInstrument = 1;
        constexpr int InvalidOrUnknownCollateralType = 2;
        constexpr int InvalidParties = 3;
        constexpr int InvalidTransportTypeRequested = 4;
        constexpr int InvalidDestinationRequested = 5;
        constexpr int NoCollateralFoundForTheTradeSpecified = 6;
        constexpr int NoCollateralFoundForTheOrderSpecified = 7;
        constexpr int CollateralInquiryTypeNotSupported = 8;
        constexpr int UnauthorizedForCollateralInquiry = 9;
        constexpr int Other = 99;
    }
    namespace  StrategyParameterType {
        constexpr int Int = 1;
        constexpr int Length = 2;
        constexpr int NumInGroup = 3;
        constexpr int SeqNum = 4;
        constexpr int TagNum = 5;
        constexpr int Float = 6;
        constexpr int Qty = 7;
        constexpr int Price = 8;
        constexpr int PriceOffset = 9;
        constexpr int Amt = 10;
        constexpr int Percentage = 11;
        constexpr int Char = 12;
        constexpr int Boolean = 13;
        constexpr int String = 14;
        constexpr int MultipleCharValue = 15;
        constexpr int Currency = 16;
        constexpr int Exchange = 17;
        constexpr int MonthYear = 18;
        constexpr int UTCTimestamp = 19;
        constexpr int UTCTimeOnly = 20;
        constexpr int LocalMktDate = 21;
        constexpr int UTCDateOnly = 22;
        constexpr int Data = 23;
        constexpr int MultipleStringValue = 24;
    }
    namespace  SecurityStatus {
        constexpr char Active = '1';
        constexpr char Inactive = '2';
    }
    namespace  UnderlyingCashType {
        constexpr std::string_view FIXED = "FIXED";
        constexpr std::string_view DIFF = "DIFF";
    }
    namespace  UnderlyingSettlementType {
        constexpr int TPlus1 = 2;
        constexpr int TPlus3 = 4;
        constexpr int TPlus4 = 5;
    }
    namespace  SecurityUpdateAction {
        constexpr char Add = 'A';
        constexpr char Delete = 'D';
        constexpr char Modify = 'M';
    }
    namespace  ExpirationQtyType {
        constexpr int AutoExercise = 1;
        constexpr int NonAutoExercise = 2;
        constexpr int FinalWillBeExercised = 3;
        constexpr int ContraryIntention = 4;
        constexpr int Difference = 5;
    }
    namespace  IndividualAllocType {
        constexpr int SubAllocate = 1;
        constexpr int ThirdPartyAllocation = 2;
    }
    namespace  UnitOfMeasure {
        constexpr std::string_view BillionCubicFeet = "Bcf";
        constexpr std::string_view MillionBarrels = "MMbbl";
        constexpr std::string_view OneMillionBTU = "MMBtu";
        constexpr std::string_view MegawattHours = "MWh";
        constexpr std::string_view Barrels = "Bbl";
        constexpr std::string_view Bushels = "Bu";
        constexpr std::string_view Pounds = "lbs";
        constexpr std::string_view Gallons = "Gal";
        constexpr std::string_view TroyOunces = "oz_tr";
        constexpr char MetricTons = 't';
        constexpr std::string_view Tons = "tn";
        constexpr std::string_view USDollars = "USD";
    }
    namespace  TimeUnit {
        constexpr char Hour = 'H';
        constexpr std::string_view Minute = "Min";
        constexpr char Second = 'S';
        constexpr char Day = 'D';
        constexpr std::string_view Week = "Wk";
        constexpr std::string_view Month = "Mo";
        constexpr std::string_view Year = "Yr";
    }
    namespace  AllocMethod {
        constexpr int Automatic = 1;
        constexpr int Guarantor = 2;
        constexpr int Manual = 3;
    }
    namespace  AsOfIndicator {
        constexpr char False = '0';
        constexpr char True = '1';
    }
    namespace  MDBookType {
        constexpr int TopOfBook = 1;
        constexpr int PriceDepth = 2;
        constexpr int OrderDepth = 3;
    }
    namespace  MDOriginType {
        constexpr int Book = 0;
        constexpr int OffBook = 1;
        constexpr int Cross = 2;
    }
    namespace  CustOrderHandlingInst {
        constexpr std::string_view AddOnOrder = "ADD";
        constexpr std::string_view AllOrNone = "AON";
        constexpr std::string_view CashNotHeld = "CNH";
        constexpr std::string_view DirectedOrder = "DIR";
        constexpr std::string_view ExchangeForPhysicalTransaction = "E.W";
        constexpr std::string_view FillOrKill = "FOK";
        constexpr std::string_view ImbalanceOnly = "IO";
        constexpr std::string_view ImmediateOrCancel = "IOC";
        constexpr std::string_view LimitOnOpen = "LOO";
        constexpr std::string_view LimitOnClose = "LOC";
        constexpr std::string_view MarketAtOpen = "MAO";
        constexpr std::string_view MarketAtClose = "MAC";
        constexpr std::string_view MarketOnOpen = "MOO";
        constexpr std::string_view MarketOnClose = "MOC";
        constexpr std::string_view MinimumQuantity = "MQT";
        constexpr std::string_view NotHeld = "NH";
        constexpr std::string_view OverTheDay = "OVD";
        constexpr std::string_view Pegged = "PEG";
        constexpr std::string_view ReserveSizeOrder = "RSV";
        constexpr std::string_view StopStockTransaction = "S.W";
        constexpr std::string_view Scale = "SCL";
        constexpr std::string_view TimeOrder = "TMO";
        constexpr std::string_view TrailingStop = "TS";
        constexpr std::string_view Work = "WRK";
    }
    namespace  OrderHandlingInstSource {
        constexpr int NASDOATS = 1;
    }
    namespace  DeskType {
        constexpr char Agency = 'A';
        constexpr std::string_view Arbitrage = "AR";
        constexpr char Derivatives = 'D';
        constexpr std::string_view International = "IN";
        constexpr std::string_view Institutional = "IS";
        constexpr char Other = 'O';
        constexpr std::string_view PreferredTrading = "PF";
        constexpr std::string_view Proprietary = "PR";
        constexpr std::string_view ProgramTrading = "PT";
        constexpr char Sales = 'S';
        constexpr char Trading = 'T';
    }
    namespace  DeskTypeSource {
        constexpr int NASDOATS = 1;
    }
    namespace  DeskOrderHandlingInst {
        constexpr std::string_view AddOnOrder = "ADD";
        constexpr std::string_view AllOrNone = "AON";
        constexpr std::string_view CashNotHeld = "CNH";
        constexpr std::string_view DirectedOrder = "DIR";
        constexpr std::string_view ExchangeForPhysicalTransaction = "E.W";
        constexpr std::string_view FillOrKill = "FOK";
        constexpr std::string_view ImbalanceOnly = "IO";
        constexpr std::string_view ImmediateOrCancel = "IOC";
        constexpr std::string_view LimitOnOpen = "LOO";
        constexpr std::string_view LimitOnClose = "LOC";
        constexpr std::string_view MarketAtOpen = "MAO";
        constexpr std::string_view MarketAtClose = "MAC";
        constexpr std::string_view MarketOnOpen = "MOO";
        constexpr std::string_view MarketOnClose = "MOC";
        constexpr std::string_view MinimumQuantity = "MQT";
        constexpr std::string_view NotHeld = "NH";
        constexpr std::string_view OverTheDay = "OVD";
        constexpr std::string_view Pegged = "PEG";
        constexpr std::string_view ReserveSizeOrder = "RSV";
        constexpr std::string_view StopStockTransaction = "S.W";
        constexpr std::string_view Scale = "SCL";
        constexpr std::string_view TimeOrder = "TMO";
        constexpr std::string_view TrailingStop = "TS";
        constexpr std::string_view Work = "WRK";
    }
    namespace  ExecAckStatus {
        constexpr char Received = '0';
        constexpr char Accepted = '1';
        constexpr char Don = '2';
    }
    namespace  CollApplType {
        constexpr int SpecificDeposit = 0;
        constexpr int General = 1;
    }
    namespace  UnderlyingFXRateCalc {
        constexpr char Divide = 'D';
        constexpr char Multiply = 'M';
    }
    namespace  AllocPositionEffect {
        constexpr char Open = 'O';
        constexpr char Close = 'C';
        constexpr char Rolled = 'R';
        constexpr char FIFO = 'F';
    }
    namespace  AggressorIndicator {
        constexpr char OrderInitiatorIsAggressor = 'Y';
        constexpr char OrderInitiatorIsPassive = 'N';
    }
    namespace  MDQuoteType {
        constexpr int Indicative = 0;
        constexpr int Tradeable = 1;
        constexpr int RestrictedTradeable = 2;
        constexpr int Counter = 3;
        constexpr int IndicativeAndTradeable = 4;
    }
    namespace  RefOrderIDSource {
        constexpr char SecondaryOrderID = '0';
        constexpr char OrderID = '1';
        constexpr char MDEntryID = '2';
        constexpr char QuoteEntryID = '3';
    }
    namespace  DisplayWhen {
        constexpr char Immediate = '1';
        constexpr char Exhaust = '2';
    }
    namespace  DisplayMethod {
        constexpr char Initial = '1';
        constexpr char New = '2';
        constexpr char Random = '3';
    }
    namespace  PriceProtectionScope {
        constexpr char None = '0';
        constexpr char Local = '1';
        constexpr char National = '2';
        constexpr char Global = '3';
    }
    namespace  LotType {
        constexpr char OddLot = '1';
        constexpr char RoundLot = '2';
        constexpr char BlockLot = '3';
    }
    namespace  PegPriceType {
        constexpr int LastPeg = 1;
        constexpr int MidPricePeg = 2;
        constexpr int OpeningPeg = 3;
        constexpr int MarketPeg = 4;
        constexpr int PrimaryPeg = 5;
        constexpr int PegToVWAP = 7;
        constexpr int TrailingStopPeg = 8;
        constexpr int PegToLimitPrice = 9;
    }
    namespace  TriggerType {
        constexpr char PartialExecution = '1';
        constexpr char SpecifiedTradingSession = '2';
        constexpr char NextAuction = '3';
        constexpr char PriceMovement = '4';
    }
    namespace  TriggerAction {
        constexpr char Activate = '1';
        constexpr char Modify = '2';
        constexpr char Cancel = '3';
    }
    namespace  TriggerPriceType {
        constexpr char BestOffer = '1';
        constexpr char LastTrade = '2';
        constexpr char BestBid = '3';
        constexpr char BestBidOrLastTrade = '4';
        constexpr char BestOfferOrLastTrade = '5';
        constexpr char BestMid = '6';
    }
    namespace  TriggerPriceTypeScope {
        constexpr char None = '0';
        constexpr char Local = '1';
        constexpr char National = '2';
        constexpr char Global = '3';
    }
    namespace  TriggerPriceDirection {
        constexpr char Up = 'U';
        constexpr char Down = 'D';
    }
    namespace  TriggerOrderType {
        constexpr char Market = '1';
        constexpr char Limit = '2';
    }
    namespace  OrderCategory {
        constexpr char Order = '1';
        constexpr char Quote = '2';
        constexpr char PrivatelyNegotiatedTrade = '3';
        constexpr char MultilegOrder = '4';
        constexpr char LinkedOrder = '5';
        constexpr char QuoteRequest = '6';
        constexpr char ImpliedOrder = '7';
        constexpr char CrossOrder = '8';
        constexpr char StreamingPrice = '9';
    }
    namespace  TradeHandlingInstr {
        constexpr char TradeConfirmation = '0';
        constexpr char TwoPartyReport = '1';
        constexpr char OnePartyReportForMatching = '2';
        constexpr char OnePartyReportForPassThrough = '3';
        constexpr char AutomatedFloorOrderRouting = '4';
        constexpr char TwoPartyReportForClaim = '5';
    }
    namespace  ApplVerID {
        constexpr char FIX27 = '0';
        constexpr char FIX30 = '1';
        constexpr char FIX40 = '2';
        constexpr char FIX41 = '3';
        constexpr char FIX42 = '4';
        constexpr char FIX43 = '5';
        constexpr char FIX44 = '6';
        constexpr char FIX50 = '7';
        constexpr char FIX50SP1 = '8';
    }
    namespace  ExDestinationIDSource {
        constexpr char BIC = 'B';
        constexpr char GeneralIdentifier = 'C';
        constexpr char Proprietary = 'D';
        constexpr char ISOCountryCode = 'E';
        constexpr char MIC = 'G';
    }
    namespace  ImpliedMarketIndicator {
        constexpr int NotImplied = 0;
        constexpr int ImpliedIn = 1;
        constexpr int ImpliedOut = 2;
        constexpr int BothImpliedInAndImpliedOut = 3;
    }
    namespace  SettlObligMode {
        constexpr int Preliminary = 1;
        constexpr int Final = 2;
    }
    namespace  SettlObligTransType {
        constexpr char Cancel = 'C';
        constexpr char New = 'N';
        constexpr char Replace = 'R';
        constexpr char Restate = 'T';
    }
    namespace  SettlObligSource {
        constexpr char InstructionsOfBroker = '1';
        constexpr char InstructionsForInstitution = '2';
        constexpr char Investor = '3';
    }
    namespace  QuoteEntryStatus {
        constexpr int Accepted = 0;
        constexpr int Rejected = 5;
        constexpr int RemovedFromMarket = 6;
        constexpr int Expired = 7;
        constexpr int LockedMarketWarning = 12;
        constexpr int CrossMarketWarning = 13;
        constexpr int CanceledDueToLockMarket = 14;
        constexpr int CanceledDueToCrossMarket = 15;
        constexpr int Active = 16;
    }
    namespace  PrivateQuote {
        constexpr char PrivateQuote = 'Y';
        constexpr char PublicQuote = 'N';
    }
    namespace  RespondentType {
        constexpr int AllMarketParticipants = 1;
        constexpr int SpecifiedMarketParticipants = 2;
        constexpr int AllMarketMakers = 3;
        constexpr int PrimaryMarketMaker = 4;
    }
    namespace  SecurityTradingEvent {
        constexpr int OrderImbalance = 1;
        constexpr int TradingResumes = 2;
        constexpr int PriceVolatilityInterruption = 3;
        constexpr int ChangeOfTradingSession = 4;
        constexpr int ChangeOfTradingSubsession = 5;
        constexpr int ChangeOfSecurityTradingStatus = 6;
        constexpr int ChangeOfBookType = 7;
        constexpr int ChangeOfMarketDepth = 8;
    }
    namespace  StatsType {
        constexpr int ExchangeLast = 1;
        constexpr int High = 2;
        constexpr int AveragePrice = 3;
        constexpr int Turnover = 4;
    }
    namespace  MDSecSizeType {
        constexpr int Customer = 1;
    }
    namespace  SettlMethod {
        constexpr char CashSettlementRequired = 'C';
        constexpr char PhysicalSettlementRequired = 'P';
    }
    namespace  ExerciseStyle {
        constexpr int European = 0;
        constexpr int American = 1;
        constexpr int Bermuda = 2;
    }
    namespace  PriceQuoteMethod {
        constexpr std::string_view Standard = "STD";
        constexpr std::string_view Index = "INX";
        constexpr std::string_view InterestRateIndex = "INT";
    }
    namespace  ValuationMethod {
        constexpr std::string_view PremiumStyle = "EQTY";
        constexpr std::string_view FuturesStyleMarkToMarket = "FUT";
        constexpr std::string_view FuturesStyleWithAnAttachedCashAdjustment = "FUTDA";
    }
    namespace  ListMethod {
        constexpr int PreListedOnly = 0;
        constexpr int UserRequested = 1;
    }
    namespace  TickRuleType {
        constexpr int Regular = 0;
        constexpr int Variable = 1;
        constexpr int Fixed = 2;
        constexpr int TradedAsASpreadLeg = 3;
        constexpr int SettledAsASpreadLeg = 4;
    }
    namespace  MaturityMonthYearIncrementUnits {
        constexpr int Months = 0;
        constexpr int Days = 1;
        constexpr int Weeks = 2;
        constexpr int Years = 3;
    }
    namespace  MaturityMonthYearFormat {
        constexpr int YearMonthOnly = 0;
        constexpr int YearMonthDay = 1;
        constexpr int YearMonthWeek = 2;
    }
    namespace  PriceLimitType {
        constexpr int Price = 0;
        constexpr int Ticks = 1;
        constexpr int Percentage = 2;
    }
    namespace  MarketUpdateAction {
        constexpr char Add = 'A';
        constexpr char Delete = 'D';
        constexpr char Modify = 'M';
    }
    namespace  SessionStatus {
        constexpr int SessionActive = 0;
        constexpr int SessionPasswordChanged = 1;
        constexpr int SessionPasswordDueToExpire = 2;
        constexpr int NewSessionPasswordDoesNotComplyWithPolicy = 3;
        constexpr int SessionLogoutComplete = 4;
        constexpr int InvalidUsernameOrPassword = 5;
        constexpr int AccountLocked = 6;
        constexpr int LogonsAreNotAllowedAtThisTime = 7;
        constexpr int PasswordExpired = 8;
    }
    namespace  TradSesEvent {
        constexpr int TradingResumes = 0;
        constexpr int ChangeOfTradingSession = 1;
        constexpr int ChangeOfTradingSubsession = 2;
        constexpr int ChangeOfTradingStatus = 3;
    }
    namespace  MassActionType {
        constexpr int SuspendOrders = 1;
        constexpr int ReleaseOrdersFromSuspension = 2;
        constexpr int CancelOrders = 3;
    }
    namespace  MassActionScope {
        constexpr int AllOrdersForASecurity = 1;
        constexpr int AllOrdersForAnUnderlyingSecurity = 2;
        constexpr int AllOrdersForAProduct = 3;
        constexpr int AllOrdersForACFICode = 4;
        constexpr int AllOrdersForASecurityType = 5;
        constexpr int AllOrdersForATradingSession = 6;
        constexpr int AllOrders = 7;
        constexpr int AllOrdersForAMarket = 8;
        constexpr int AllOrdersForAMarketSegment = 9;
        constexpr int AllOrdersForASecurityGroup = 10;
    }
    namespace  MassActionResponse {
        constexpr int Rejected = 0;
        constexpr int Accepted = 1;
    }
    namespace  MassActionRejectReason {
        constexpr int MassActionNotSupported = 0;
        constexpr int InvalidOrUnknownSecurity = 1;
        constexpr int InvalidOrUnknownUnderlyingSecurity = 2;
        constexpr int InvalidOrUnknownProduct = 3;
        constexpr int InvalidOrUnknownCFICode = 4;
        constexpr int InvalidOrUnknownSecurityType = 5;
        constexpr int InvalidOrUnknownTradingSession = 6;
        constexpr int InvalidOrUnknownMarket = 7;
        constexpr int InvalidOrUnknownMarketSegment = 8;
        constexpr int InvalidOrUnknownSecurityGroup = 9;
        constexpr int Other = 99;
    }
    namespace  MultilegModel {
        constexpr int PredefinedMultilegSecurity = 0;
        constexpr int UserDefinedMultilegSecurity = 1;
        constexpr int UserDefined = 2;
    }
    namespace  MultilegPriceMethod {
        constexpr int NetPrice = 0;
        constexpr int ReversedNetPrice = 1;
        constexpr int YieldDifference = 2;
        constexpr int Individual = 3;
        constexpr int ContractWeightedAveragePrice = 4;
        constexpr int MultipliedPrice = 5;
    }
    namespace  ContingencyType {
        constexpr int OneCancelsTheOther = 1;
        constexpr int OneTriggersTheOther = 2;
        constexpr int OneUpdatesTheOtherAbsolute = 3;
        constexpr int OneUpdatesTheOtherProportional = 4;
    }
    namespace  ListRejectReason {
        constexpr int BrokerCredit = 0;
        constexpr int ExchangeClosed = 2;
        constexpr int TooLateToEnter = 4;
        constexpr int UnknownOrder = 5;
        constexpr int DuplicateOrder = 6;
        constexpr int UnsupportedOrderCharacteristic = 11;
        constexpr int Other = 99;
    }
    namespace  TradePublishIndicator {
        constexpr int DoNotPublishTrade = 0;
        constexpr int PublishTrade = 1;
        constexpr int DeferredPublication = 2;
    }
    namespace  ApplReqType {
        constexpr int Retransmission = 0;
        constexpr int Subscription = 1;
        constexpr int RequestLastSeqNum = 2;
        constexpr int RequestApplications = 3;
        constexpr int Unsubscribe = 4;
    }
    namespace  ApplResponseType {
        constexpr int RequestSuccessfullyProcessed = 0;
        constexpr int ApplicationDoesNotExist = 1;
        constexpr int MessagesNotAvailable = 2;
    }
    namespace  ApplResponseError {
        constexpr int ApplicationDoesNotExist = 0;
        constexpr int MessagesRequestedAreNotAvailable = 1;
        constexpr int UserNotAuthorizedForApplication = 2;
    }
    namespace  ApplReportType {
        constexpr int ApplSeqNumReset = 0;
        constexpr int LastMessageSent = 1;
        constexpr int ApplicationAlive = 2;
    }
    namespace  OrderDelayUnit {
        constexpr int Seconds = 0;
        constexpr int TenthsOfASecond = 1;
        constexpr int HundredthsOfASecond = 2;
        constexpr int Milliseconds = 3;
        constexpr int Microseconds = 4;
        constexpr int Nanoseconds = 5;
        constexpr int Minutes = 10;
        constexpr int Hours = 11;
        constexpr int Days = 12;
        constexpr int Weeks = 13;
        constexpr int Months = 14;
        constexpr int Years = 15;
    }
    namespace  VenueType {
        constexpr char Electronic = 'E';
        constexpr char Pit = 'P';
        constexpr char ExPit = 'X';
    }
    namespace  RefOrdIDReason {
        constexpr int GTCFromPreviousDay = 0;
        constexpr int PartialFillRemaining = 1;
        constexpr int OrderChanged = 2;
    }
    namespace  OrigCustOrderCapacity {
        constexpr int MemberTradingForTheirOwnAccount = 1;
        constexpr int ClearingFirmTradingForItsProprietaryAccount = 2;
        constexpr int MemberTradingForAnotherMember = 3;
        constexpr int AllOther = 4;
    }
    namespace  TrdRegTimestampType {
        constexpr int SubmissionToClearing = 7;
    }
    namespace  RefOrderIDSource {
        constexpr char OriginalOrderID = '4';
    }
    namespace  OrderRestrictions {
    }
    namespace  ApplReqType {
        constexpr int CancelRetransmission = 5;
        constexpr int CancelRetransmissionUnsubscribe = 6;
    }
    namespace  QuoteCancelType {
        constexpr int CancelByQuoteType = 6;
    }
    namespace  DisplayMethod {
        constexpr char Undisclosed = '4';
    }
    namespace  PosReqType {
        constexpr int DeltaPositions = 6;
    }
    namespace  PartyRole {
        constexpr int CentralRegistrationDepository = 82;
    }
    namespace  ModelType {
        constexpr int UtilityProvidedStandardModel = 0;
        constexpr int ProprietaryModel = 1;
    }
    namespace  PosType {
        constexpr std::string_view NetDeltaQty = "DLT";
    }
    namespace  LotType {
        constexpr char RoundLotBasedUpon = '4';
    }
    namespace  ContractMultiplierUnit {
        constexpr int Shares = 0;
        constexpr int Hours = 1;
        constexpr int Days = 2;
    }
    namespace  FlowScheduleType {
        constexpr int NERCEasternOffPeak = 0;
        constexpr int NERCWesternOffPeak = 1;
        constexpr int NERCCalendarAllDaysInMonth = 2;
        constexpr int NERCEasternPeak = 3;
        constexpr int NERCWesternPeak = 4;
    }
    namespace  RateSource {
        constexpr int Bloomberg = 0;
        constexpr int Reuters = 1;
        constexpr int Telerate = 2;
        constexpr int Other = 99;
    }
    namespace  RateSourceType {
        constexpr int Primary = 0;
        constexpr int Secondary = 1;
    }
    namespace  SecurityType {
        constexpr std::string_view NonDeliverableForward = "FXNDF";
        constexpr std::string_view FXSpot = "FXSPOT";
        constexpr std::string_view FXForward = "FXFWD";
        constexpr std::string_view FXSwap = "FXSWAP";
    }
    namespace  RestructuringType {
        constexpr std::string_view FullRestructuring = "FR";
        constexpr std::string_view ModifiedRestructuring = "MR";
        constexpr std::string_view ModifiedModRestructuring = "MM";
        constexpr std::string_view NoRestructuringSpecified = "XR";
    }
    namespace  Seniority {
        constexpr std::string_view SeniorSecured = "SD";
        constexpr std::string_view Senior = "SR";
        constexpr std::string_view Subordinated = "SB";
    }
    namespace  PriceQuoteMethod {
        constexpr std::string_view PercentOfPar = "PCTPAR";
    }
    namespace  ValuationMethod {
        constexpr std::string_view CDSStyleCollateralization = "CDS";
        constexpr std::string_view CDSInDeliveryUseRecoveryRateToCalculate = "CDSD";
    }
    namespace  PosAmtType {
        constexpr std::string_view InitialTradeCouponAmount = "ICPN";
        constexpr std::string_view AccruedCouponAmount = "ACPN";
        constexpr std::string_view CouponAmount = "CPN";
        constexpr std::string_view IncrementalAccruedCoupon = "IACPN";
        constexpr std::string_view CollateralizedMarkToMarket = "CMTM";
        constexpr std::string_view IncrementalCollateralizedMarkToMarket = "ICMTM";
        constexpr std::string_view CompensationAmount = "DLV";
        constexpr std::string_view TotalBankedAmount = "BANK";
        constexpr std::string_view TotalCollateralizedAmount = "COLAT";
    }
    namespace  PosType {
        constexpr std::string_view CreditEventAdjustment = "CEA";
        constexpr std::string_view SuccessionEventAdjustment = "SEA";
    }
    namespace  MDEntryType {
        constexpr char RecoveryRate = 'Y';
        constexpr char RecoveryRateForLong = 'Z';
        constexpr char RecoveryRateForShort = 'a';
    }
    namespace  QuoteCondition {
        constexpr std::string_view FullCurve = "6";
        constexpr std::string_view FlatCurve = "7";
    }
    namespace  MDEntryType {
        constexpr char FixingPrice = 'W';
        constexpr char CashRate = 'X';
    }
    namespace  SecurityTradingStatus {
        constexpr int PostClose = 26;
    }
    namespace  QuoteCancelType {
        constexpr int CancelForSecurityIssuer = 7;
        constexpr int CancelForIssuerOfUnderlyingSecurity = 8;
    }
    namespace  QuoteRejectReason {
        constexpr int InvalidOrUnknownSecurityIssuer = 12;
        constexpr int InvalidOrUnknownIssuerOfUnderlyingSecurity = 13;
    }
    namespace  MassCancelRequestType {
        constexpr char CancelOrdersForSecurityIssuer = 'B';
        constexpr char CancelForIssuerOfUnderlyingSecurity = 'C';
    }
    namespace  MassCancelResponse {
        constexpr char CancelOrdersForASecuritiesIssuer = 'B';
        constexpr char CancelOrdersForIssuerOfUnderlyingSecurity = 'C';
    }
    namespace  MassCancelRejectReason {
        constexpr int InvalidOrUnknownSecurityIssuer = 10;
        constexpr int InvalidOrUnknownIssuerOfUnderlyingSecurity = 11;
    }
    namespace  MassStatusReqType {
        constexpr int StatusForSecurityIssuer = 9;
        constexpr int StatusForIssuerOfUnderlyingSecurity = 10;
    }
    namespace  MassActionScope {
        constexpr int CancelForSecurityIssuer = 11;
        constexpr int CancelForIssuerOfUnderlyingSecurity = 12;
    }
    namespace  MassActionRejectReason {
        constexpr int InvalidOrUnknownSecurityIssuer = 10;
        constexpr int InvalidOrUnknownIssuerOfUnderlyingSecurity = 11;
    }
    namespace  HaltReason {
        constexpr int NewsDissemination = 0;
        constexpr int OrderInflux = 1;
        constexpr int OrderImbalance = 2;
        constexpr int AdditionalInformation = 3;
        constexpr int NewsPending = 4;
        constexpr int EquipmentChangeover = 5;
    }
    namespace  SecurityListType {
        constexpr int IndustryClassification = 1;
        constexpr int TradingList = 2;
        constexpr int Market = 3;
        constexpr int NewspaperList = 4;
    }
    namespace  SecurityListTypeSource {
        constexpr int ICB = 1;
        constexpr int NAICS = 2;
        constexpr int GICS = 3;
    }
    namespace  UnitOfMeasure {
        constexpr std::string_view Allowances = "Alw";
    }
    namespace  NewsCategory {
        constexpr int CompanyNews = 0;
        constexpr int MarketplaceNews = 1;
        constexpr int FinancialMarketNews = 2;
        constexpr int TechnicalNews = 3;
        constexpr int OtherNews = 99;
    }
    namespace  NewsRefType {
        constexpr int Replacement = 0;
        constexpr int OtherLanguage = 1;
        constexpr int Complimentary = 2;
    }
    namespace  ApplReportType {
        constexpr int ResendComplete = 3;
    }
    namespace  StrikePriceDeterminationMethod {
        constexpr int FixedStrike = 1;
        constexpr int StrikeSetAtExpiration = 2;
        constexpr int StrikeSetToAverageAcrossLife = 3;
        constexpr int StrikeSetToOptimalValue = 4;
    }
    namespace  StrikePriceBoundaryMethod {
        constexpr int LessThan = 1;
        constexpr int LessThanOrEqual = 2;
        constexpr int Equal = 3;
        constexpr int GreaterThanOrEqual = 4;
        constexpr int GreaterThan = 5;
    }
    namespace  UnderlyingPriceDeterminationMethod {
        constexpr int Regular = 1;
        constexpr int SpecialReference = 2;
        constexpr int OptimalValue = 3;
        constexpr int AverageValue = 4;
    }
    namespace  OptPayoutType {
        constexpr int Vanilla = 1;
        constexpr int Capped = 2;
        constexpr int Binary = 3;
    }
    namespace  ComplexEventType {
        constexpr int Capped = 1;
        constexpr int Trigger = 2;
        constexpr int KnockInUp = 3;
        constexpr int KockInDown = 4;
        constexpr int KnockOutUp = 5;
        constexpr int KnockOutDown = 6;
        constexpr int Underlying = 7;
        constexpr int ResetBarrier = 8;
        constexpr int RollingBarrier = 9;
    }
    namespace  ComplexEventPriceBoundaryMethod {
        constexpr int LessThanComplexEventPrice = 1;
        constexpr int LessThanOrEqualToComplexEventPrice = 2;
        constexpr int EqualToComplexEventPrice = 3;
        constexpr int GreaterThanOrEqualToComplexEventPrice = 4;
        constexpr int GreaterThanComplexEventPrice = 5;
    }
    namespace  ComplexEventPriceTimeType {
        constexpr int Expiration = 1;
        constexpr int Immediate = 2;
        constexpr int SpecifiedDate = 3;
    }
    namespace  ComplexEventCondition {
        constexpr int And = 1;
        constexpr int Or = 2;
    }
    namespace  StreamAsgnReqType {
        constexpr int StreamAssignmentForNewCustomer = 1;
        constexpr int StreamAssignmentForExistingCustomer = 2;
    }
    namespace  StreamAsgnRejReason {
        constexpr int UnknownClient = 0;
        constexpr int ExceedsMaximumSize = 1;
        constexpr int UnknownOrInvalidCurrencyPair = 2;
        constexpr int NoAvailableStream = 3;
        constexpr int Other = 99;
    }
    namespace  StreamAsgnAckType {
        constexpr int AssignmentAccepted = 0;
        constexpr int AssignmentRejected = 1;
    }
    namespace  StreamAsgnType {
        constexpr int Assignment = 1;
        constexpr int Rejected = 2;
        constexpr int Terminate = 3;
    }
    namespace  DealingCapacity {
        constexpr char Agent = 'A';
        constexpr char Principal = 'P';
        constexpr char RisklessPrincipal = 'R';
    }
    namespace  InstrmtAssignmentMethod {
        constexpr char ProRata = 'P';
        constexpr char Random = 'R';
    }
    namespace  AllocRejCode {
        constexpr int Other = 99;
    }
    namespace  StrategyParameterType {
        constexpr int Country = 25;
        constexpr int Language = 26;
        constexpr int TZTimeOnly = 27;
        constexpr int TZTimestamp = 28;
        constexpr int Tenor = 29;
    }
    namespace  PartyRole {
        constexpr int ClearingAccount = 83;
        constexpr int AcceptableSettlingCounterparty = 84;
        constexpr int UnacceptableSettlingCounterparty = 85;
    }
    namespace  ApplVerID {
        constexpr char FIX50SP2 = '9';
    }
    namespace  MsgType {
        constexpr char Heartbeat = '0';
        constexpr char TestRequest = '1';
        constexpr char ResendRequest = '2';
        constexpr char Reject = '3';
        constexpr char SequenceReset = '4';
        constexpr char Logout = '5';
        constexpr char IOI = '6';
        constexpr char Advertisement = '7';
        constexpr char ExecutionReport = '8';
        constexpr char OrderCancelReject = '9';
        constexpr char Logon = 'A';
        constexpr std::string_view DerivativeSecurityList = "AA";
        constexpr std::string_view NewOrderMultileg = "AB";
        constexpr std::string_view MultilegOrderCancelReplace = "AC";
        constexpr std::string_view TradeCaptureReportRequest = "AD";
        constexpr std::string_view TradeCaptureReport = "AE";
        constexpr std::string_view OrderMassStatusRequest = "AF";
        constexpr std::string_view QuoteRequestReject = "AG";
        constexpr std::string_view RFQRequest = "AH";
        constexpr std::string_view QuoteStatusReport = "AI";
        constexpr std::string_view QuoteResponse = "AJ";
        constexpr std::string_view Confirmation = "AK";
        constexpr std::string_view PositionMaintenanceRequest = "AL";
        constexpr std::string_view PositionMaintenanceReport = "AM";
        constexpr std::string_view RequestForPositions = "AN";
        constexpr std::string_view RequestForPositionsAck = "AO";
        constexpr std::string_view PositionReport = "AP";
        constexpr std::string_view TradeCaptureReportRequestAck = "AQ";
        constexpr std::string_view TradeCaptureReportAck = "AR";
        constexpr std::string_view AllocationReport = "AS";
        constexpr std::string_view AllocationReportAck = "AT";
        constexpr std::string_view ConfirmationAck = "AU";
        constexpr std::string_view SettlementInstructionRequest = "AV";
        constexpr std::string_view AssignmentReport = "AW";
        constexpr std::string_view CollateralRequest = "AX";
        constexpr std::string_view CollateralAssignment = "AY";
        constexpr std::string_view CollateralResponse = "AZ";
        constexpr char News = 'B';
        constexpr std::string_view CollateralReport = "BA";
        constexpr std::string_view CollateralInquiry = "BB";
        constexpr std::string_view NetworkCounterpartySystemStatusRequest = "BC";
        constexpr std::string_view NetworkCounterpartySystemStatusResponse = "BD";
        constexpr std::string_view UserRequest = "BE";
        constexpr std::string_view UserResponse = "BF";
        constexpr std::string_view CollateralInquiryAck = "BG";
        constexpr std::string_view ConfirmationRequest = "BH";
        constexpr std::string_view TradingSessionListRequest = "BI";
        constexpr std::string_view TradingSessionList = "BJ";
        constexpr std::string_view SecurityListUpdateReport = "BK";
        constexpr std::string_view AdjustedPositionReport = "BL";
        constexpr std::string_view AllocationInstructionAlert = "BM";
        constexpr std::string_view ExecutionAcknowledgement = "BN";
        constexpr std::string_view ContraryIntentionReport = "BO";
        constexpr std::string_view SecurityDefinitionUpdateReport = "BP";
        constexpr std::string_view SettlementObligationReport = "BQ";
        constexpr std::string_view DerivativeSecurityListUpdateReport = "BR";
        constexpr std::string_view TradingSessionListUpdateReport = "BS";
        constexpr std::string_view MarketDefinitionRequest = "BT";
        constexpr std::string_view MarketDefinition = "BU";
        constexpr std::string_view MarketDefinitionUpdateReport = "BV";
        constexpr std::string_view ApplicationMessageRequest = "BW";
        constexpr std::string_view ApplicationMessageRequestAck = "BX";
        constexpr std::string_view ApplicationMessageReport = "BY";
        constexpr std::string_view OrderMassActionReport = "BZ";
        constexpr char Email = 'C';
        constexpr std::string_view OrderMassActionRequest = "CA";
        constexpr std::string_view UserNotification = "CB";
        constexpr std::string_view StreamAssignmentRequest = "CC";
        constexpr std::string_view StreamAssignmentReport = "CD";
        constexpr std::string_view StreamAssignmentReportACK = "CE";
        constexpr char NewOrderSingle = 'D';
        constexpr char NewOrderList = 'E';
        constexpr char OrderCancelRequest = 'F';
        constexpr char OrderCancelReplaceRequest = 'G';
        constexpr char OrderStatusRequest = 'H';
        constexpr char AllocationInstruction = 'J';
        constexpr char ListCancelRequest = 'K';
        constexpr char ListExecute = 'L';
        constexpr char ListStatusRequest = 'M';
        constexpr char ListStatus = 'N';
        constexpr char AllocationInstructionAck = 'P';
        constexpr char DontKnowTrade = 'Q';
        constexpr char QuoteRequest = 'R';
        constexpr char Quote = 'S';
        constexpr char SettlementInstructions = 'T';
        constexpr char MarketDataRequest = 'V';
        constexpr char MarketDataSnapshotFullRefresh = 'W';
        constexpr char MarketDataIncrementalRefresh = 'X';
        constexpr char MarketDataRequestReject = 'Y';
        constexpr char QuoteCancel = 'Z';
        constexpr char QuoteStatusRequest = 'a';
        constexpr char MassQuoteAcknowledgement = 'b';
        constexpr char SecurityDefinitionRequest = 'c';
        constexpr char SecurityDefinition = 'd';
        constexpr char SecurityStatusRequest = 'e';
        constexpr char SecurityStatus = 'f';
        constexpr char TradingSessionStatusRequest = 'g';
        constexpr char TradingSessionStatus = 'h';
        constexpr char MassQuote = 'i';
        constexpr char BusinessMessageReject = 'j';
        constexpr char BidRequest = 'k';
        constexpr char BidResponse = 'l';
        constexpr char ListStrikePrice = 'm';
        constexpr char XMLnonFIX = 'n';
        constexpr char RegistrationInstructions = 'o';
        constexpr char RegistrationInstructionsResponse = 'p';
        constexpr char OrderMassCancelRequest = 'q';
        constexpr char OrderMassCancelReport = 'r';
        constexpr char NewOrderCross = 's';
        constexpr char CrossOrderCancelReplaceRequest = 't';
        constexpr char CrossOrderCancelRequest = 'u';
        constexpr char SecurityTypeRequest = 'v';
        constexpr char SecurityTypes = 'w';
        constexpr char SecurityListRequest = 'x';
        constexpr char SecurityList = 'y';
        constexpr char DerivativeSecurityListRequest = 'z';

        }
    }

  }

#endif //VALUES