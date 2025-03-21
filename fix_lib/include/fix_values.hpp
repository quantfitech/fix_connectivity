#ifndef FIX_VALUES_HPP
#define FIX_VALUES_HPP

#include <string_view>

  namespace qffixlib {

    namespace Values {

    namespace DefaultApplVerID {
        constexpr int64_t FIX44 = 6;
        constexpr int64_t FIX50 = 7;
        constexpr int64_t FIX50SP1 = 8;
        constexpr int64_t FIX50SP2 = 9;

    }

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
        constexpr int64_t Accepted = 0;
        constexpr int64_t BlockLevelReject = 1;
        constexpr int64_t AccountLevelReject = 2;
        constexpr int64_t Received = 3;
        constexpr int64_t Incomplete = 4;
        constexpr int64_t RejectedByIntermediary = 5;
        constexpr int64_t AllocationPending = 6;
        constexpr int64_t Reversed = 7;
    }
    namespace  AllocRejCode {
        constexpr int64_t UnknownAccount = 0;
        constexpr int64_t IncorrectQuantity = 1;
        constexpr int64_t IncorrectAveragegPrice = 2;
        constexpr int64_t UnknownExecutingBrokerMnemonic = 3;
        constexpr int64_t CommissionDifference = 4;
        constexpr int64_t UnknownOrderID = 5;
        constexpr int64_t UnknownListID = 6;
        constexpr int64_t OtherSeeText = 7;
        constexpr int64_t IncorrectAllocatedQuantity = 8;
        constexpr int64_t CalculationDifference = 9;
        constexpr int64_t UnknownOrStaleExecID = 10;
        constexpr int64_t MismatchedData = 11;
        constexpr int64_t UnknownClOrdID = 12;
        constexpr int64_t WarehouseRequestRejected = 13;
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
        constexpr int64_t None = 0;
        constexpr int64_t PKCS = 1;
        constexpr int64_t DES = 2;
        constexpr int64_t PKCSDES = 3;
        constexpr int64_t PGPDES = 4;
        constexpr int64_t PGPDESMD5 = 5;
        constexpr int64_t PEM = 6;
    }
    namespace  CxlRejReason {
        constexpr int64_t TooLateToCancel = 0;
        constexpr int64_t UnknownOrder = 1;
        constexpr int64_t BrokerCredit = 2;
        constexpr int64_t OrderAlreadyInPendingStatus = 3;
        constexpr int64_t UnableToProcessOrderMassCancelRequest = 4;
        constexpr int64_t OrigOrdModTime = 5;
        constexpr int64_t DuplicateClOrdID = 6;
        constexpr int64_t PriceExceedsCurrentPrice = 7;
        constexpr int64_t PriceExceedsCurrentPriceBand = 8;
        constexpr int64_t InvalidPriceIncrement = 18;
        constexpr int64_t Other = 99;
    }
    namespace  OrdRejReason {
        constexpr int64_t BrokerCredit = 0;
        constexpr int64_t UnknownSymbol = 1;
        constexpr int64_t ExchangeClosed = 2;
        constexpr int64_t OrderExceedsLimit = 3;
        constexpr int64_t TooLateToEnter = 4;
        constexpr int64_t UnknownOrder = 5;
        constexpr int64_t DuplicateOrder = 6;
        constexpr int64_t DuplicateOfAVerballyCommunicatedOrder = 7;
        constexpr int64_t StaleOrder = 8;
        constexpr int64_t TradeAlongRequired = 9;
        constexpr int64_t InvalidInvestorID = 10;
        constexpr int64_t UnsupportedOrderCharacteristic = 11;
        constexpr int64_t SurveillenceOption = 12;
        constexpr int64_t IncorrectQuantity = 13;
        constexpr int64_t IncorrectAllocatedQuantity = 14;
        constexpr int64_t UnknownAccount = 15;
        constexpr int64_t PriceExceedsCurrentPriceBand = 16;
        constexpr int64_t InvalidPriceIncrement = 18;
        constexpr int64_t Other = 99;
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
        constexpr int64_t Other = 0;
        constexpr int64_t DTCSID = 1;
        constexpr int64_t ThomsonALERT = 2;
        constexpr int64_t AGlobalCustodian = 3;
        constexpr int64_t AccountNet = 4;
    }
    namespace  SettlDeliveryType {
        constexpr int64_t Versus = 0;
        constexpr int64_t Free = 1;
        constexpr int64_t TriParty = 2;
        constexpr int64_t HoldInCustody = 3;
    }
    namespace  AllocLinkType {
        constexpr int64_t FXNetting = 0;
        constexpr int64_t FXSwap = 1;
    }
    namespace  PutOrCall {
        constexpr int64_t Put = 0;
        constexpr int64_t Call = 1;
    }
    namespace  CoveredOrUncovered {
        constexpr int64_t Covered = 0;
        constexpr int64_t Uncovered = 1;
    }
    namespace  NotifyBrokerOfCredit {
        constexpr char DetailsShouldNotBeCommunicated = 'N';
        constexpr char DetailsShouldBeCommunicated = 'Y';
    }
    namespace  AllocHandlInst {
        constexpr int64_t Match = 1;
        constexpr int64_t Forward = 2;
        constexpr int64_t ForwardAndMatch = 3;
    }
    namespace  RoutingType {
        constexpr int64_t TargetFirm = 1;
        constexpr int64_t TargetList = 2;
        constexpr int64_t BlockFirm = 3;
        constexpr int64_t BlockList = 4;
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
        constexpr int64_t FullRefresh = 0;
        constexpr int64_t IncrementalRefresh = 1;
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
        constexpr char FairValueLimitUp = 'g';
        constexpr char FairValueLimitDown = 'h';
        constexpr char FinalFundingRate = 'f';
        constexpr char MarkPrice = 'm';
        constexpr char PredictedFundingRate = 'p';
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
        constexpr int64_t Accepted = 0;
        constexpr int64_t CancelForSymbol = 1;
        constexpr int64_t CanceledForSecurityType = 2;
        constexpr int64_t CanceledForUnderlying = 3;
        constexpr int64_t CanceledAll = 4;
        constexpr int64_t Rejected = 5;
        constexpr int64_t RemovedFromMarket = 6;
        constexpr int64_t Expired = 7;
        constexpr int64_t Query = 8;
        constexpr int64_t QuoteNotFound = 9;
        constexpr int64_t Pending = 10;
        constexpr int64_t Pass = 11;
        constexpr int64_t LockedMarketWarning = 12;
        constexpr int64_t CrossMarketWarning = 13;
        constexpr int64_t CanceledDueToLockMarket = 14;
        constexpr int64_t CanceledDueToCrossMarket = 15;
        constexpr int64_t Active = 16;
        constexpr int64_t Canceled = 17;
        constexpr int64_t UnsolicitedQuoteReplenishment = 18;
        constexpr int64_t PendingEndTrade = 19;
        constexpr int64_t TooLateToEnd = 20;
    }
    namespace  QuoteCancelType {
        constexpr int64_t CancelForOneOrMoreSecurities = 1;
        constexpr int64_t CancelForSecurityType = 2;
        constexpr int64_t CancelForUnderlyingSecurity = 3;
        constexpr int64_t CancelAllQuotes = 4;
        constexpr int64_t CancelQuoteSpecifiedInQuoteID = 5;
    }
    namespace  QuoteRejectReason {
        constexpr int64_t UnknownSymbol = 1;
        constexpr int64_t Exchange = 2;
        constexpr int64_t QuoteRequestExceedsLimit = 3;
        constexpr int64_t TooLateToEnter = 4;
        constexpr int64_t UnknownQuote = 5;
        constexpr int64_t DuplicateQuote = 6;
        constexpr int64_t InvalidBid = 7;
        constexpr int64_t InvalidPrice = 8;
        constexpr int64_t NotAuthorizedToQuoteSecurity = 9;
        constexpr int64_t PriceExceedsCurrentPriceBand = 10;
        constexpr int64_t QuoteLocked = 11;
        constexpr int64_t Other = 99;
    }
    namespace  QuoteResponseLevel {
        constexpr int64_t NoAcknowledgement = 0;
        constexpr int64_t AcknowledgeOnlyNegativeOrErroneousQuotes = 1;
        constexpr int64_t AcknowledgeEachQuoteMessage = 2;
        constexpr int64_t SummaryAcknowledgement = 3;
    }
    namespace  QuoteRequestType {
        constexpr int64_t Manual = 1;
        constexpr int64_t Automatic = 2;
    }
    namespace  SecurityRequestType {
        constexpr int64_t RequestSecurityIdentityAndSpecifications = 0;
        constexpr int64_t RequestSecurityIdentityForSpecifications = 1;
        constexpr int64_t RequestListSecurityTypes = 2;
        constexpr int64_t RequestListSecurities = 3;
        constexpr int64_t Symbol = 4;
        constexpr int64_t SecurityTypeAndOrCFICode = 5;
        constexpr int64_t Product = 6;
        constexpr int64_t TradingSessionID = 7;
        constexpr int64_t AllSecurities = 8;
        constexpr int64_t MarketIDOrMarketID = 9;
    }
    namespace  SecurityResponseType {
        constexpr int64_t AcceptAsIs = 1;
        constexpr int64_t AcceptWithRevisions = 2;
        constexpr int64_t ListOfSecurityTypesReturnedPerRequest = 3;
        constexpr int64_t ListOfSecuritiesReturnedPerRequest = 4;
        constexpr int64_t RejectSecurityProposal = 5;
        constexpr int64_t CannotMatchSelectionCriteria = 6;
    }
    namespace  UnsolicitedIndicator {
        constexpr char MessageIsBeingSentAsAResultOfAPriorRequest = 'N';
        constexpr char MessageIsBeingSentUnsolicited = 'Y';
    }
    namespace  SecurityTradingStatus {
        constexpr int64_t OpeningDelay = 1;
        constexpr int64_t TradingHalt = 2;
        constexpr int64_t Resume = 3;
        constexpr int64_t NoOpen = 4;
        constexpr int64_t PriceIndication = 5;
        constexpr int64_t TradingRangeIndication = 6;
        constexpr int64_t MarketImbalanceBuy = 7;
        constexpr int64_t MarketImbalanceSell = 8;
        constexpr int64_t MarketOnCloseImbalanceBuy = 9;
        constexpr int64_t MarketOnCloseImbalanceSell = 10;
        constexpr int64_t NoMarketImbalance = 12;
        constexpr int64_t NoMarketOnCloseImbalance = 13;
        constexpr int64_t ITSPreOpening = 14;
        constexpr int64_t NewPriceIndication = 15;
        constexpr int64_t TradeDisseminationTime = 16;
        constexpr int64_t ReadyToTrade = 17;
        constexpr int64_t NotAvailableForTrading = 18;
        constexpr int64_t NotTradedOnThisMarket = 19;
        constexpr int64_t UnknownOrInvalid = 20;
        constexpr int64_t PreOpen = 21;
        constexpr int64_t OpeningRotation = 22;
        constexpr int64_t FastMarket = 23;
        constexpr int64_t PreCross = 24;
        constexpr int64_t Cross = 25;
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
        constexpr int64_t Cancel = 1;
        constexpr int64_t Error = 2;
        constexpr int64_t Correction = 3;
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
        constexpr int64_t Electronic = 1;
        constexpr int64_t OpenOutcry = 2;
        constexpr int64_t TwoParty = 3;
    }
    namespace  TradSesMode {
        constexpr int64_t Testing = 1;
        constexpr int64_t Simulated = 2;
        constexpr int64_t Production = 3;
    }
    namespace  TradSesStatus {
        constexpr int64_t Unknown = 0;
        constexpr int64_t Halted = 1;
        constexpr int64_t Open = 2;
        constexpr int64_t Closed = 3;
        constexpr int64_t PreOpen = 4;
        constexpr int64_t PreClose = 5;
        constexpr int64_t RequestRejected = 6;
    }
    namespace  SessionRejectReason {
        constexpr int64_t InvalidTagNumber = 0;
        constexpr int64_t RequiredTagMissing = 1;
        constexpr int64_t TagNotDefinedForThisMessageType = 2;
        constexpr int64_t UndefinedTag = 3;
        constexpr int64_t TagSpecifiedWithoutAValue = 4;
        constexpr int64_t ValueIsIncorrect = 5;
        constexpr int64_t IncorrectDataFormatForValue = 6;
        constexpr int64_t DecryptionProblem = 7;
        constexpr int64_t SignatureProblem = 8;
        constexpr int64_t CompIDProblem = 9;
        constexpr int64_t SendingTimeAccuracyProblem = 10;
        constexpr int64_t InvalidMsgType = 11;
        constexpr int64_t XMLValidationError = 12;
        constexpr int64_t TagAppearsMoreThanOnce = 13;
        constexpr int64_t TagSpecifiedOutOfRequiredOrder = 14;
        constexpr int64_t RepeatingGroupFieldsOutOfOrder = 15;
        constexpr int64_t IncorrectNumInGroupCountForRepeatingGroup = 16;
        constexpr int64_t Non = 17;
        constexpr int64_t Invalid = 18;
        constexpr int64_t Other = 99;
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
        constexpr int64_t GTCorporateAction = 0;
        constexpr int64_t GTRenewal = 1;
        constexpr int64_t VerbalChange = 2;
        constexpr int64_t RepricingOfOrder = 3;
        constexpr int64_t BrokerOption = 4;
        constexpr int64_t PartialDeclineOfOrderQty = 5;
        constexpr int64_t CancelOnTradingHalt = 6;
        constexpr int64_t CancelOnSystemFailure = 7;
        constexpr int64_t Market = 8;
        constexpr int64_t Canceled = 9;
        constexpr int64_t WarehouseRecap = 10;
        constexpr int64_t PegRefresh = 11;
        constexpr int64_t Other = 99;
    }
    namespace  BusinessRejectReason {
        constexpr int64_t Other = 0;
        constexpr int64_t UnknownID = 1;
        constexpr int64_t UnknownSecurity = 2;
        constexpr int64_t UnsupportedMessageType = 3;
        constexpr int64_t ApplicationNotAvailable = 4;
        constexpr int64_t ConditionallyRequiredFieldMissing = 5;
        constexpr int64_t NotAuthorized = 6;
        constexpr int64_t DeliverToFirmNotAvailableAtThisTime = 7;
        constexpr int64_t InvalidPriceIncrement = 18;
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
        constexpr int64_t NonDisclosed = 1;
        constexpr int64_t Disclosed = 2;
        constexpr int64_t NoBiddingProcess = 3;
    }
    namespace  BidDescriptorType {
        constexpr int64_t Sector = 1;
        constexpr int64_t Country = 2;
        constexpr int64_t Index = 3;
    }
    namespace  SideValueInd {
        constexpr int64_t SideValue1 = 1;
        constexpr int64_t SideValue2 = 2;
    }
    namespace  LiquidityIndType {
        constexpr int64_t FiveDayMovingAverage = 1;
        constexpr int64_t TwentyDayMovingAverage = 2;
        constexpr int64_t NormalMarketSize = 3;
        constexpr int64_t Other = 4;
    }
    namespace  ExchangeForPhysical {
        constexpr char False = 'N';
        constexpr char True = 'Y';
    }
    namespace  ProgRptReqs {
        constexpr int64_t BuySideRequests = 1;
        constexpr int64_t SellSideSends = 2;
        constexpr int64_t RealTimeExecutionReports = 3;
    }
    namespace  IncTaxInd {
        constexpr int64_t Net = 1;
        constexpr int64_t Gross = 2;
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
        constexpr int64_t Percentage = 1;
        constexpr int64_t PerUnit = 2;
        constexpr int64_t FixedAmount = 3;
        constexpr int64_t Discount = 4;
        constexpr int64_t Premium = 5;
        constexpr int64_t Spread = 6;
        constexpr int64_t TEDPrice = 7;
        constexpr int64_t TEDYield = 8;
        constexpr int64_t Yield = 9;
        constexpr int64_t FixedCabinetTradePrice = 10;
        constexpr int64_t VariableCabinetTradePrice = 11;
        constexpr int64_t ProductTicksInHalfs = 13;
        constexpr int64_t ProductTicksInFourths = 14;
        constexpr int64_t ProductTicksInEights = 15;
        constexpr int64_t ProductTicksInSixteenths = 16;
        constexpr int64_t ProductTicksInThirtySeconds = 17;
        constexpr int64_t ProductTicksInSixtyForths = 18;
        constexpr int64_t ProductTicksInOneTwentyEights = 19;
    }
    namespace  GTBookingInst {
        constexpr int64_t BookOutAllTradesOnDayOfExecution = 0;
        constexpr int64_t AccumulateUntilFilledOrExpired = 1;
        constexpr int64_t AccumulateUntilVerballyNotifiedOtherwise = 2;
    }
    namespace  ListStatusType {
        constexpr int64_t Ack = 1;
        constexpr int64_t Response = 2;
        constexpr int64_t Timed = 3;
        constexpr int64_t ExecStarted = 4;
        constexpr int64_t AllDone = 5;
        constexpr int64_t Alert = 6;
    }
    namespace  NetGrossInd {
        constexpr int64_t Net = 1;
        constexpr int64_t Gross = 2;
    }
    namespace  ListOrderStatus {
        constexpr int64_t InBiddingProcess = 1;
        constexpr int64_t ReceivedForExecution = 2;
        constexpr int64_t Executing = 3;
        constexpr int64_t Cancelling = 4;
        constexpr int64_t Alert = 5;
        constexpr int64_t AllDone = 6;
        constexpr int64_t Reject = 7;
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
        constexpr int64_t ExecutingFirm = 1;
        constexpr int64_t BrokerOfCredit = 2;
        constexpr int64_t ClientID = 3;
        constexpr int64_t ClearingFirm = 4;
        constexpr int64_t InvestorID = 5;
        constexpr int64_t IntroducingFirm = 6;
        constexpr int64_t EnteringFirm = 7;
        constexpr int64_t Locate = 8;
        constexpr int64_t FundManagerClientID = 9;
        constexpr int64_t SettlementLocation = 10;
        constexpr int64_t OrderOriginationTrader = 11;
        constexpr int64_t ExecutingTrader = 12;
        constexpr int64_t OrderOriginationFirm = 13;
        constexpr int64_t GiveupClearingFirm = 14;
        constexpr int64_t CorrespondantClearingFirm = 15;
        constexpr int64_t ExecutingSystem = 16;
        constexpr int64_t ContraFirm = 17;
        constexpr int64_t ContraClearingFirm = 18;
        constexpr int64_t SponsoringFirm = 19;
        constexpr int64_t UnderlyingContraFirm = 20;
        constexpr int64_t ClearingOrganization = 21;
        constexpr int64_t Exchange = 22;
        constexpr int64_t CustomerAccount = 24;
        constexpr int64_t CorrespondentClearingOrganization = 25;
        constexpr int64_t CorrespondentBroker = 26;
        constexpr int64_t Buyer = 27;
        constexpr int64_t Custodian = 28;
        constexpr int64_t Intermediary = 29;
        constexpr int64_t Agent = 30;
        constexpr int64_t SubCustodian = 31;
        constexpr int64_t Beneficiary = 32;
        constexpr int64_t InterestedParty = 33;
        constexpr int64_t RegulatoryBody = 34;
        constexpr int64_t LiquidityProvider = 35;
        constexpr int64_t EnteringTrader = 36;
        constexpr int64_t ContraTrader = 37;
        constexpr int64_t PositionAccount = 38;
        constexpr int64_t ContraInvestorID = 39;
        constexpr int64_t TransferToFirm = 40;
        constexpr int64_t ContraPositionAccount = 41;
        constexpr int64_t ContraExchange = 42;
        constexpr int64_t InternalCarryAccount = 43;
        constexpr int64_t OrderEntryOperatorID = 44;
        constexpr int64_t SecondaryAccountNumber = 45;
        constexpr int64_t ForeignFirm = 46;
        constexpr int64_t ThirdPartyAllocationFirm = 47;
        constexpr int64_t ClaimingAccount = 48;
        constexpr int64_t AssetManager = 49;
        constexpr int64_t PledgorAccount = 50;
        constexpr int64_t PledgeeAccount = 51;
        constexpr int64_t LargeTraderReportableAccount = 52;
        constexpr int64_t TraderMnemonic = 53;
        constexpr int64_t SenderLocation = 54;
        constexpr int64_t SessionID = 55;
        constexpr int64_t AcceptableCounterparty = 56;
        constexpr int64_t UnacceptableCounterparty = 57;
        constexpr int64_t EnteringUnit = 58;
        constexpr int64_t ExecutingUnit = 59;
        constexpr int64_t IntroducingBroker = 60;
        constexpr int64_t QuoteOriginator = 61;
        constexpr int64_t ReportOriginator = 62;
        constexpr int64_t SystematicInternaliser = 63;
        constexpr int64_t MultilateralTradingFacility = 64;
        constexpr int64_t RegulatedMarket = 65;
        constexpr int64_t MarketMaker = 66;
        constexpr int64_t InvestmentFirm = 67;
        constexpr int64_t HostCompetentAuthority = 68;
        constexpr int64_t HomeCompetentAuthority = 69;
        constexpr int64_t CompetentAuthorityLiquidity = 70;
        constexpr int64_t CompetentAuthorityTransactionVenue = 71;
        constexpr int64_t ReportingIntermediary = 72;
        constexpr int64_t ExecutionVenue = 73;
        constexpr int64_t MarketDataEntryOriginator = 74;
        constexpr int64_t LocationID = 75;
        constexpr int64_t DeskID = 76;
        constexpr int64_t MarketDataMarket = 77;
        constexpr int64_t AllocationEntity = 78;
        constexpr int64_t PrimeBroker = 79;
        constexpr int64_t StepOutFirm = 80;
        constexpr int64_t BrokerClearingID = 81;
    }
    namespace  Product {
        constexpr int64_t AGENCY = 1;
        constexpr int64_t COMMODITY = 2;
        constexpr int64_t CORPORATE = 3;
        constexpr int64_t CURRENCY = 4;
        constexpr int64_t EQUITY = 5;
        constexpr int64_t GOVERNMENT = 6;
        constexpr int64_t INDEX = 7;
        constexpr int64_t LOAN = 8;
        constexpr int64_t MONEYMARKET = 9;
        constexpr int64_t MORTGAGE = 10;
        constexpr int64_t MUNICIPAL = 11;
        constexpr int64_t OTHER = 12;
        constexpr int64_t FINANCING = 13;
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
        constexpr int64_t CREST = 1;
        constexpr int64_t NSCC = 2;
        constexpr int64_t Euroclear = 3;
        constexpr int64_t Clearstream = 4;
        constexpr int64_t Cheque = 5;
        constexpr int64_t TelegraphicTransfer = 6;
        constexpr int64_t FedWire = 7;
        constexpr int64_t DirectCredit = 8;
        constexpr int64_t ACHCredit = 9;
        constexpr int64_t BPAY = 10;
        constexpr int64_t HighValueClearingSystemHVACS = 11;
        constexpr int64_t ReinvestInFund = 12;
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
        constexpr int64_t New = 0;
        constexpr int64_t Cancel = 1;
        constexpr int64_t Replace = 2;
        constexpr int64_t Release = 3;
        constexpr int64_t Reverse = 4;
        constexpr int64_t CancelDueToBackOutOfTrade = 5;
    }
    namespace  PaymentMethod {
        constexpr int64_t CREST = 1;
        constexpr int64_t NSCC = 2;
        constexpr int64_t Euroclear = 3;
        constexpr int64_t Clearstream = 4;
        constexpr int64_t Cheque = 5;
        constexpr int64_t TelegraphicTransfer = 6;
        constexpr int64_t FedWire = 7;
        constexpr int64_t DebitCard = 8;
        constexpr int64_t DirectDebit = 9;
        constexpr int64_t DirectCredit = 10;
        constexpr int64_t CreditCard = 11;
        constexpr int64_t ACHDebit = 12;
        constexpr int64_t ACHCredit = 13;
        constexpr int64_t BPAY = 14;
        constexpr int64_t HighValueClearingSystem = 15;
    }
    namespace  TaxAdvantageType {
        constexpr int64_t None = 0;
        constexpr int64_t MaxiISA = 1;
        constexpr int64_t TESSA = 2;
        constexpr int64_t MiniCashISA = 3;
        constexpr int64_t MiniStocksAndSharesISA = 4;
        constexpr int64_t MiniInsuranceISA = 5;
        constexpr int64_t CurrentYearPayment = 6;
        constexpr int64_t PriorYearPayment = 7;
        constexpr int64_t AssetTransfer = 8;
        constexpr int64_t EmployeePriorYear = 9;
        constexpr int64_t EmployeeCurrentYear = 10;
        constexpr int64_t EmployerPriorYear = 11;
        constexpr int64_t EmployerCurrentYear = 12;
        constexpr int64_t NonFundPrototypeIRA = 13;
        constexpr int64_t NonFundQualifiedPlan = 14;
        constexpr int64_t DefinedContributionPlan = 15;
        constexpr int64_t IRA = 16;
        constexpr int64_t IRARollover = 17;
        constexpr int64_t KEOGH = 18;
        constexpr int64_t ProfitSharingPlan = 19;
        constexpr int64_t US401K = 20;
        constexpr int64_t SelfDirectedIRA = 21;
        constexpr int64_t US403b = 22;
        constexpr int64_t US457 = 23;
        constexpr int64_t RothIRAPrototype = 24;
        constexpr int64_t RothIRANonPrototype = 25;
        constexpr int64_t RothConversionIRAPrototype = 26;
        constexpr int64_t RothConversionIRANonPrototype = 27;
        constexpr int64_t EducationIRAPrototype = 28;
        constexpr int64_t EducationIRANonPrototype = 29;
        constexpr int64_t Other = 999;
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
        constexpr int64_t InvalidAccountType = 1;
        constexpr int64_t InvalidTaxExemptType = 2;
        constexpr int64_t InvalidOwnershipType = 3;
        constexpr int64_t NoRegDetails = 4;
        constexpr int64_t InvalidRegSeqNo = 5;
        constexpr int64_t InvalidRegDetails = 6;
        constexpr int64_t InvalidMailingDetails = 7;
        constexpr int64_t InvalidMailingInstructions = 8;
        constexpr int64_t InvalidInvestorID = 9;
        constexpr int64_t InvalidInvestorIDSource = 10;
        constexpr int64_t InvalidDateOfBirth = 11;
        constexpr int64_t InvalidCountry = 12;
        constexpr int64_t InvalidDistribInstns = 13;
        constexpr int64_t InvalidPercentage = 14;
        constexpr int64_t InvalidPaymentMethod = 15;
        constexpr int64_t InvalidAccountName = 16;
        constexpr int64_t InvalidAgentCode = 17;
        constexpr int64_t InvalidAccountNum = 18;
        constexpr int64_t Other = 99;
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
        constexpr int64_t CommissionAmount = 1;
        constexpr int64_t CommissionPercent = 2;
        constexpr int64_t InitialChargeAmount = 3;
        constexpr int64_t InitialChargePercent = 4;
        constexpr int64_t DiscountAmount = 5;
        constexpr int64_t DiscountPercent = 6;
        constexpr int64_t DilutionLevyAmount = 7;
        constexpr int64_t DilutionLevyPercent = 8;
        constexpr int64_t ExitChargeAmount = 9;
        constexpr int64_t ExitChargePercent = 10;
        constexpr int64_t FundBasedRenewalCommissionPercent = 11;
        constexpr int64_t ProjectedFundValue = 12;
        constexpr int64_t FundBasedRenewalCommissionOnOrder = 13;
        constexpr int64_t FundBasedRenewalCommissionOnFund = 14;
        constexpr int64_t NetSettlementAmount = 15;
    }
    namespace  OwnerType {
        constexpr int64_t IndividualInvestor = 1;
        constexpr int64_t PublicCompany = 2;
        constexpr int64_t PrivateCompany = 3;
        constexpr int64_t IndividualTrustee = 4;
        constexpr int64_t CompanyTrustee = 5;
        constexpr int64_t PensionPlan = 6;
        constexpr int64_t CustodianUnderGiftsToMinorsAct = 7;
        constexpr int64_t Trusts = 8;
        constexpr int64_t Fiduciaries = 9;
        constexpr int64_t NetworkingSubAccount = 10;
        constexpr int64_t NonProfitOrganization = 11;
        constexpr int64_t CorporateBody = 12;
        constexpr int64_t Nominee = 13;
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
        constexpr int64_t MassCancelNotSupported = 0;
        constexpr int64_t InvalidOrUnknownSecurity = 1;
        constexpr int64_t InvalidOrUnkownUnderlyingSecurity = 2;
        constexpr int64_t InvalidOrUnknownProduct = 3;
        constexpr int64_t InvalidOrUnknownCFICode = 4;
        constexpr int64_t InvalidOrUnknownSecurityType = 5;
        constexpr int64_t InvalidOrUnknownTradingSession = 6;
        constexpr int64_t InvalidOrUnknownMarket = 7;
        constexpr int64_t InvalidOrUnkownMarketSegment = 8;
        constexpr int64_t InvalidOrUnknownSecurityGroup = 9;
        constexpr int64_t Other = 99;
    }
    namespace  QuoteType {
        constexpr int64_t Indicative = 0;
        constexpr int64_t Tradeable = 1;
        constexpr int64_t RestrictedTradeable = 2;
        constexpr int64_t Counter = 3;
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
        constexpr int64_t CrossAON = 1;
        constexpr int64_t CrossIOC = 2;
        constexpr int64_t CrossOneSide = 3;
        constexpr int64_t CrossSamePrice = 4;
    }
    namespace  CrossPrioritization {
        constexpr int64_t None = 0;
        constexpr int64_t BuySideIsPrioritized = 1;
        constexpr int64_t SellSideIsPrioritized = 2;
    }
    namespace  NoSides {
    }
    namespace  SecurityListRequestType {
        constexpr int64_t Symbol = 0;
        constexpr int64_t SecurityTypeAnd = 1;
        constexpr int64_t Product = 2;
        constexpr int64_t TradingSessionID = 3;
        constexpr int64_t AllSecurities = 4;
        constexpr int64_t MarketIDOrMarketID = 5;
    }
    namespace  SecurityRequestResult {
        constexpr int64_t ValidRequest = 0;
        constexpr int64_t InvalidOrUnsupportedRequest = 1;
        constexpr int64_t NoInstrumentsFound = 2;
        constexpr int64_t NotAuthorizedToRetrieveInstrumentData = 3;
        constexpr int64_t InstrumentDataTemporarilyUnavailable = 4;
        constexpr int64_t RequestForInstrumentDataNotSupported = 5;
    }
    namespace  MultiLegRptTypeReq {
        constexpr int64_t ReportByMulitlegSecurityOnly = 0;
        constexpr int64_t ReportByMultilegSecurityAndInstrumentLegs = 1;
        constexpr int64_t ReportByInstrumentLegsOnly = 2;
    }
    namespace  TradSesStatusRejReason {
        constexpr int64_t UnknownOrInvalidTradingSessionID = 1;
        constexpr int64_t Other = 99;
    }
    namespace  TradeRequestType {
        constexpr int64_t AllTrades = 0;
        constexpr int64_t MatchedTradesMatchingCriteria = 1;
        constexpr int64_t UnmatchedTradesThatMatchCriteria = 2;
        constexpr int64_t UnreportedTradesThatMatchCriteria = 3;
        constexpr int64_t AdvisoriesThatMatchCriteria = 4;
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
        constexpr int64_t ProcessNormally = 0;
        constexpr int64_t ExcludeFromAllNetting = 1;
        constexpr int64_t BilateralNettingOnly = 2;
        constexpr int64_t ExClearing = 3;
        constexpr int64_t SpecialTrade = 4;
        constexpr int64_t MultilateralNetting = 5;
        constexpr int64_t ClearAgainstCentralCounterparty = 6;
        constexpr int64_t ExcludeFromCentralCounterparty = 7;
        constexpr int64_t ManualMode = 8;
        constexpr int64_t AutomaticPostingMode = 9;
        constexpr int64_t AutomaticGiveUpMode = 10;
        constexpr int64_t QualifiedServiceRepresentativeQSR = 11;
        constexpr int64_t CustomerTrade = 12;
        constexpr int64_t SelfClearing = 13;
    }
    namespace  AccountType {
        constexpr int64_t CarriedCustomerSide = 1;
        constexpr int64_t CarriedNonCustomerSide = 2;
        constexpr int64_t HouseTrader = 3;
        constexpr int64_t FloorTrader = 4;
        constexpr int64_t CarriedNonCustomerSideCrossMargined = 6;
        constexpr int64_t HouseTraderCrossMargined = 7;
        constexpr int64_t JointBackOfficeAccount = 8;
    }
    namespace  CustOrderCapacity {
        constexpr int64_t MemberTradingForTheirOwnAccount = 1;
        constexpr int64_t ClearingFirmTradingForItsProprietaryAccount = 2;
        constexpr int64_t MemberTradingForAnotherMember = 3;
        constexpr int64_t AllOther = 4;
    }
    namespace  MassStatusReqType {
        constexpr int64_t StatusForOrdersForASecurity = 1;
        constexpr int64_t StatusForOrdersForAnUnderlyingSecurity = 2;
        constexpr int64_t StatusForOrdersForAProduct = 3;
        constexpr int64_t StatusForOrdersForACFICode = 4;
        constexpr int64_t StatusForOrdersForASecurityType = 5;
        constexpr int64_t StatusForOrdersForATradingSession = 6;
        constexpr int64_t StatusForAllOrders = 7;
        constexpr int64_t StatusForOrdersForAPartyID = 8;
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
        constexpr int64_t Calculated = 1;
        constexpr int64_t Preliminary = 2;
        constexpr int64_t SellsideCalculatedUsingPreliminary = 3;
        constexpr int64_t SellsideCalculatedWithoutPreliminary = 4;
        constexpr int64_t ReadyToBook = 5;
        constexpr int64_t BuysideReadyToBook = 6;
        constexpr int64_t WarehouseInstruction = 7;
        constexpr int64_t RequestToIntermediary = 8;
        constexpr int64_t Accept = 9;
        constexpr int64_t Reject = 10;
        constexpr int64_t AcceptPending = 11;
        constexpr int64_t IncompleteGroup = 12;
        constexpr int64_t CompleteGroup = 13;
        constexpr int64_t ReversalPending = 14;
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
        constexpr int64_t PriorityUnchanged = 0;
        constexpr int64_t LostPriorityAsResultOfOrderChange = 1;
    }
    namespace  LegalConfirm {
        constexpr char DoesNotConsituteALegalConfirm = 'N';
        constexpr char LegalConfirm = 'Y';
    }
    namespace  QuoteRequestRejectReason {
        constexpr int64_t UnknownSymbol = 1;
        constexpr int64_t Exchange = 2;
        constexpr int64_t QuoteRequestExceedsLimit = 3;
        constexpr int64_t TooLateToEnter = 4;
        constexpr int64_t InvalidPrice = 5;
        constexpr int64_t NotAuthorizedToRequestQuote = 6;
        constexpr int64_t NoMatchForInquiry = 7;
        constexpr int64_t NoMarketForInstrument = 8;
        constexpr int64_t NoInventory = 9;
        constexpr int64_t Pass = 10;
        constexpr int64_t InsufficientCredit = 11;
        constexpr int64_t Other = 99;
    }
    namespace  AcctIDSource {
        constexpr int64_t BIC = 1;
        constexpr int64_t SIDCode = 2;
        constexpr int64_t TFM = 3;
        constexpr int64_t OMGEO = 4;
        constexpr int64_t DTCCCode = 5;
        constexpr int64_t Other = 99;
    }
    namespace  ConfirmStatus {
        constexpr int64_t Received = 1;
        constexpr int64_t MismatchedAccount = 2;
        constexpr int64_t MissingSettlementInstructions = 3;
        constexpr int64_t Confirmed = 4;
        constexpr int64_t RequestRejected = 5;
    }
    namespace  ConfirmTransType {
        constexpr int64_t New = 0;
        constexpr int64_t Replace = 1;
        constexpr int64_t Cancel = 2;
    }
    namespace  DeliveryForm {
        constexpr int64_t BookEntry = 1;
        constexpr int64_t Bearer = 2;
    }
    namespace  LegSwapType {
        constexpr int64_t ParForPar = 1;
        constexpr int64_t ModifiedDuration = 2;
        constexpr int64_t Risk = 4;
        constexpr int64_t Proceeds = 5;
    }
    namespace  QuotePriceType {
        constexpr int64_t Percent = 1;
        constexpr int64_t PerShare = 2;
        constexpr int64_t FixedAmount = 3;
        constexpr int64_t Discount = 4;
        constexpr int64_t Premium = 5;
        constexpr int64_t Spread = 6;
        constexpr int64_t TEDPrice = 7;
        constexpr int64_t TEDYield = 8;
        constexpr int64_t YieldSpread = 9;
        constexpr int64_t Yield = 10;
    }
    namespace  QuoteRespType {
        constexpr int64_t Hit = 1;
        constexpr int64_t Counter = 2;
        constexpr int64_t Expired = 3;
        constexpr int64_t Cover = 4;
        constexpr int64_t DoneAway = 5;
        constexpr int64_t Pass = 6;
        constexpr int64_t EndTrade = 7;
        constexpr int64_t TimedOut = 8;
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
        constexpr int64_t Submitted = 0;
        constexpr int64_t Accepted = 1;
        constexpr int64_t Rejected = 2;
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
        constexpr int64_t Exercise = 1;
        constexpr int64_t DoNotExercise = 2;
        constexpr int64_t PositionAdjustment = 3;
        constexpr int64_t PositionChangeSubmission = 4;
        constexpr int64_t Pledge = 5;
        constexpr int64_t LargeTraderSubmission = 6;
    }
    namespace  PosMaintAction {
        constexpr int64_t New = 1;
        constexpr int64_t Replace = 2;
        constexpr int64_t Cancel = 3;
        constexpr int64_t Reverse = 4;
    }
    namespace  SettlSessID {
        constexpr std::string_view Intraday = "ITD";
        constexpr std::string_view RegularTradingHours = "RTH";
        constexpr std::string_view ElectronicTradingHours = "ETH";
        constexpr std::string_view EndOfDay = "EOD";
    }
    namespace  AdjustmentType {
        constexpr int64_t ProcessRequestAsMarginDisposition = 0;
        constexpr int64_t DeltaPlus = 1;
        constexpr int64_t DeltaMinus = 2;
        constexpr int64_t Final = 3;
    }
    namespace  PosMaintStatus {
        constexpr int64_t Accepted = 0;
        constexpr int64_t AcceptedWithWarnings = 1;
        constexpr int64_t Rejected = 2;
        constexpr int64_t Completed = 3;
        constexpr int64_t CompletedWithWarnings = 4;
    }
    namespace  PosMaintResult {
        constexpr int64_t SuccessfulCompletion = 0;
        constexpr int64_t Rejected = 1;
        constexpr int64_t Other = 99;
    }
    namespace  PosReqType {
        constexpr int64_t Positions = 0;
        constexpr int64_t Trades = 1;
        constexpr int64_t Exercises = 2;
        constexpr int64_t Assignments = 3;
        constexpr int64_t SettlementActivity = 4;
        constexpr int64_t BackoutMessage = 5;
    }
    namespace  ResponseTransportType {
        constexpr int64_t Inband = 0;
        constexpr int64_t OutOfBand = 1;
    }
    namespace  PosReqResult {
        constexpr int64_t ValidRequest = 0;
        constexpr int64_t InvalidOrUnsupportedRequest = 1;
        constexpr int64_t NoPositionsFoundThatMatchCriteria = 2;
        constexpr int64_t NotAuthorizedToRequestPositions = 3;
        constexpr int64_t RequestForPositionNotSupported = 4;
        constexpr int64_t Other = 99;
    }
    namespace  PosReqStatus {
        constexpr int64_t Completed = 0;
        constexpr int64_t CompletedWithWarnings = 1;
        constexpr int64_t Rejected = 2;
    }
    namespace  SettlPriceType {
        constexpr int64_t Final = 1;
        constexpr int64_t Theoretical = 2;
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
        constexpr int64_t Successful = 0;
        constexpr int64_t InvalidOrUnknownInstrument = 1;
        constexpr int64_t InvalidTypeOfTradeRequested = 2;
        constexpr int64_t InvalidParties = 3;
        constexpr int64_t InvalidTransportTypeRequested = 4;
        constexpr int64_t InvalidDestinationRequested = 5;
        constexpr int64_t TradeRequestTypeNotSupported = 8;
        constexpr int64_t NotAuthorized = 9;
        constexpr int64_t Other = 99;
    }
    namespace  TradeRequestStatus {
        constexpr int64_t Accepted = 0;
        constexpr int64_t Completed = 1;
        constexpr int64_t Rejected = 2;
    }
    namespace  TradeReportRejectReason {
        constexpr int64_t Successful = 0;
        constexpr int64_t InvalidPartyOnformation = 1;
        constexpr int64_t UnknownInstrument = 2;
        constexpr int64_t UnauthorizedToReportTrades = 3;
        constexpr int64_t InvalidTradeType = 4;
        constexpr int64_t Other = 99;
    }
    namespace  SideMultiLegReportingType {
        constexpr int64_t SingleSecurity = 1;
        constexpr int64_t IndividualLegOfAMultilegSecurity = 2;
        constexpr int64_t MultilegSecurity = 3;
    }
    namespace  TrdRegTimestampType {
        constexpr int64_t ExecutionTime = 1;
        constexpr int64_t TimeIn = 2;
        constexpr int64_t TimeOut = 3;
        constexpr int64_t BrokerReceipt = 4;
        constexpr int64_t BrokerExecution = 5;
        constexpr int64_t DeskReceipt = 6;
    }
    namespace  ConfirmType {
        constexpr int64_t Status = 1;
        constexpr int64_t Confirmation = 2;
        constexpr int64_t ConfirmationRequestRejected = 3;
    }
    namespace  ConfirmRejReason {
        constexpr int64_t MismatchedAccount = 1;
        constexpr int64_t MissingSettlementInstructions = 2;
        constexpr int64_t Other = 99;
    }
    namespace  BookingType {
        constexpr int64_t RegularBooking = 0;
        constexpr int64_t CFD = 1;
        constexpr int64_t TotalReturnSwap = 2;
    }
    namespace  AllocSettlInstType {
        constexpr int64_t UseDefaultInstructions = 0;
        constexpr int64_t DeriveFromParametersProvided = 1;
        constexpr int64_t FullDetailsProvided = 2;
        constexpr int64_t SSIDBIDsProvided = 3;
        constexpr int64_t PhoneForInstructions = 4;
    }
    namespace  DlvyInstType {
        constexpr char Cash = 'C';
        constexpr char Securities = 'S';
    }
    namespace  TerminationType {
        constexpr int64_t Overnight = 1;
        constexpr int64_t Term = 2;
        constexpr int64_t Flexible = 3;
        constexpr int64_t Open = 4;
    }
    namespace  SettlInstReqRejCode {
        constexpr int64_t UnableToProcessRequest = 0;
        constexpr int64_t UnknownAccount = 1;
        constexpr int64_t NoMatchingSettlementInstructionsFound = 2;
        constexpr int64_t Other = 99;
    }
    namespace  AllocReportType {
        constexpr int64_t PreliminaryRequestToIntermediary = 2;
        constexpr int64_t SellsideCalculatedUsingPreliminary = 3;
        constexpr int64_t SellsideCalculatedWithoutPreliminary = 4;
        constexpr int64_t WarehouseRecap = 5;
        constexpr int64_t RequestToIntermediary = 8;
        constexpr int64_t Accept = 9;
        constexpr int64_t Reject = 10;
        constexpr int64_t AcceptPending = 11;
        constexpr int64_t Complete = 12;
        constexpr int64_t ReversePending = 14;
    }
    namespace  AllocCancReplaceReason {
        constexpr int64_t OriginalDetailsIncomplete = 1;
        constexpr int64_t ChangeInUnderlyingOrderDetails = 2;
        constexpr int64_t Other = 99;
    }
    namespace  AllocAccountType {
        constexpr int64_t CarriedCustomerSide = 1;
        constexpr int64_t CarriedNonCustomerSide = 2;
        constexpr int64_t HouseTrader = 3;
        constexpr int64_t FloorTrader = 4;
        constexpr int64_t CarriedNonCustomerSideCrossMargined = 6;
        constexpr int64_t HouseTraderCrossMargined = 7;
        constexpr int64_t JointBackOfficeAccount = 8;
    }
    namespace  PartySubIDType {
        constexpr int64_t Firm = 1;
        constexpr int64_t Person = 2;
        constexpr int64_t System = 3;
        constexpr int64_t Application = 4;
        constexpr int64_t FullLegalNameOfFirm = 5;
        constexpr int64_t PostalAddress = 6;
        constexpr int64_t PhoneNumber = 7;
        constexpr int64_t EmailAddress = 8;
        constexpr int64_t ContactName = 9;
        constexpr int64_t SecuritiesAccountNumber = 10;
        constexpr int64_t RegistrationNumber = 11;
        constexpr int64_t RegisteredAddressForConfirmation = 12;
        constexpr int64_t RegulatoryStatus = 13;
        constexpr int64_t RegistrationName = 14;
        constexpr int64_t CashAccountNumber = 15;
        constexpr int64_t BIC = 16;
        constexpr int64_t CSDParticipantMemberCode = 17;
        constexpr int64_t RegisteredAddress = 18;
        constexpr int64_t FundAccountName = 19;
        constexpr int64_t TelexNumber = 20;
        constexpr int64_t FaxNumber = 21;
        constexpr int64_t SecuritiesAccountName = 22;
        constexpr int64_t CashAccountName = 23;
        constexpr int64_t Department = 24;
        constexpr int64_t LocationDesk = 25;
        constexpr int64_t PositionAccountType = 26;
        constexpr int64_t SecurityLocateID = 27;
        constexpr int64_t MarketMaker = 28;
        constexpr int64_t EligibleCounterparty = 29;
        constexpr int64_t ProfessionalClient = 30;
        constexpr int64_t Location = 31;
        constexpr int64_t ExecutionVenue = 32;
        constexpr int64_t CurrencyDeliveryIdentifier = 33;
    }
    namespace  AllocIntermedReqType {
        constexpr int64_t PendingAccept = 1;
        constexpr int64_t PendingRelease = 2;
        constexpr int64_t PendingReversal = 3;
        constexpr int64_t Accept = 4;
        constexpr int64_t BlockLevelReject = 5;
        constexpr int64_t AccountLevelReject = 6;
    }
    namespace  ApplQueueResolution {
        constexpr int64_t NoActionTaken = 0;
        constexpr int64_t QueueFlushed = 1;
        constexpr int64_t OverlayLast = 2;
        constexpr int64_t EndSession = 3;
    }
    namespace  ApplQueueAction {
        constexpr int64_t NoActionTaken = 0;
        constexpr int64_t QueueFlushed = 1;
        constexpr int64_t OverlayLast = 2;
        constexpr int64_t EndSession = 3;
    }
    namespace  AvgPxIndicator {
        constexpr int64_t NoAveragePricing = 0;
        constexpr int64_t Trade = 1;
        constexpr int64_t LastTrade = 2;
    }
    namespace  TradeAllocIndicator {
        constexpr int64_t AllocationNotRequired = 0;
        constexpr int64_t AllocationRequired = 1;
        constexpr int64_t UseAllocationProvidedWithTheTrade = 2;
        constexpr int64_t AllocationGiveUpExecutor = 3;
        constexpr int64_t AllocationFromExecutor = 4;
        constexpr int64_t AllocationToClaimAccount = 5;
    }
    namespace  ExpirationCycle {
        constexpr int64_t ExpireOnTradingSessionClose = 0;
        constexpr int64_t ExpireOnTradingSessionOpen = 1;
        constexpr int64_t SpecifiedExpiration = 2;
    }
    namespace  TrdType {
        constexpr int64_t RegularTrade = 0;
        constexpr int64_t BlockTrade = 1;
        constexpr int64_t EFP = 2;
        constexpr int64_t Transfer = 3;
        constexpr int64_t LateTrade = 4;
        constexpr int64_t TTrade = 5;
        constexpr int64_t WeightedAveragePriceTrade = 6;
        constexpr int64_t BunchedTrade = 7;
        constexpr int64_t LateBunchedTrade = 8;
        constexpr int64_t PriorReferencePriceTrade = 9;
        constexpr int64_t AfterHoursTrade = 10;
        constexpr int64_t ExchangeForRisk = 11;
        constexpr int64_t ExchangeForSwap = 12;
        constexpr int64_t ExchangeOfFuturesFor = 13;
        constexpr int64_t ExchangeOfOptionsForOptions = 14;
        constexpr int64_t TradingAtSettlement = 15;
        constexpr int64_t AllOrNone = 16;
        constexpr int64_t FuturesLargeOrderExecution = 17;
        constexpr int64_t ExchangeOfFuturesForFutures = 18;
        constexpr int64_t OptionInterimTrade = 19;
        constexpr int64_t OptionCabinetTrade = 20;
        constexpr int64_t PrivatelyNegotiatedTrades = 22;
        constexpr int64_t SubstitutionOfFuturesForForwards = 23;
        constexpr int64_t NonStandardSettlement = 48;
        constexpr int64_t DerivativeRelatedTransaction = 49;
        constexpr int64_t PortfolioTrade = 50;
        constexpr int64_t VolumeWeightedAverageTrade = 51;
        constexpr int64_t ExchangeGrantedTrade = 52;
        constexpr int64_t RepurchaseAgreement = 53;
        constexpr int64_t OTC = 54;
        constexpr int64_t ExchangeBasisFacility = 55;
        constexpr int64_t ErrorTrade = 24;
        constexpr int64_t SpecialCumDividend = 25;
        constexpr int64_t SpecialExDividend = 26;
        constexpr int64_t SpecialCumCoupon = 27;
        constexpr int64_t SpecialExCoupon = 28;
        constexpr int64_t CashSettlement = 29;
        constexpr int64_t SpecialPrice = 30;
        constexpr int64_t GuaranteedDelivery = 31;
        constexpr int64_t SpecialCumRights = 32;
        constexpr int64_t SpecialExRights = 33;
        constexpr int64_t SpecialCumCapitalRepayments = 34;
        constexpr int64_t SpecialExCapitalRepayments = 35;
        constexpr int64_t SpecialCumBonus = 36;
        constexpr int64_t SpecialExBonus = 37;
        constexpr int64_t LargeTrade = 38;
        constexpr int64_t WorkedPrincipalTrade = 39;
        constexpr int64_t BlockTrades = 40;
        constexpr int64_t NameChange = 41;
        constexpr int64_t PortfolioTransfer = 42;
        constexpr int64_t ProrogationBuy = 43;
        constexpr int64_t ProrogationSell = 44;
        constexpr int64_t OptionExercise = 45;
        constexpr int64_t DeltaNeutralTransaction = 46;
        constexpr int64_t FinancingTransaction = 47;
    }
    namespace  TrdSubType {
        constexpr int64_t CMTA = 0;
        constexpr int64_t InternalTransferOrAdjustment = 1;
        constexpr int64_t ExternalTransferOrTransferOfAccount = 2;
        constexpr int64_t RejectForSubmittingSide = 3;
        constexpr int64_t AdvisoryForContraSide = 4;
        constexpr int64_t OffsetDueToAnAllocation = 5;
        constexpr int64_t OnsetDueToAnAllocation = 6;
        constexpr int64_t DifferentialSpread = 7;
        constexpr int64_t ImpliedSpreadLegExecutedAgainstAnOutright = 8;
        constexpr int64_t TransactionFromExercise = 9;
        constexpr int64_t TransactionFromAssignment = 10;
        constexpr int64_t ACATS = 11;
        constexpr int64_t OffHoursTrade = 33;
        constexpr int64_t OnHoursTrade = 34;
        constexpr int64_t OTCQuote = 35;
        constexpr int64_t ConvertedSWAP = 36;
        constexpr int64_t AI = 14;
        constexpr int64_t B = 15;
        constexpr int64_t K = 16;
        constexpr int64_t LC = 17;
        constexpr int64_t M = 18;
        constexpr int64_t N = 19;
        constexpr int64_t NM = 20;
        constexpr int64_t NR = 21;
        constexpr int64_t P = 22;
        constexpr int64_t PA = 23;
        constexpr int64_t PC = 24;
        constexpr int64_t PN = 25;
        constexpr int64_t R = 26;
        constexpr int64_t RO = 27;
        constexpr int64_t RT = 28;
        constexpr int64_t SW = 29;
        constexpr int64_t T = 30;
        constexpr int64_t WN = 31;
        constexpr int64_t WT = 32;
        constexpr int64_t CrossedTrade = 37;
        constexpr int64_t InterimProtectedTrade = 38;
        constexpr int64_t LargeInScale = 39;
    }
    namespace  PegMoveType {
        constexpr int64_t Floating = 0;
        constexpr int64_t Fixed = 1;
    }
    namespace  PegOffsetType {
        constexpr int64_t Price = 0;
        constexpr int64_t BasisPoints = 1;
        constexpr int64_t Ticks = 2;
        constexpr int64_t PriceTier = 3;
    }
    namespace  PegLimitType {
        constexpr int64_t OrBetter = 0;
        constexpr int64_t Strict = 1;
        constexpr int64_t OrWorse = 2;
    }
    namespace  PegRoundDirection {
        constexpr int64_t MoreAggressive = 1;
        constexpr int64_t MorePassive = 2;
    }
    namespace  PegScope {
        constexpr int64_t Local = 1;
        constexpr int64_t National = 2;
        constexpr int64_t Global = 3;
        constexpr int64_t NationalExcludingLocal = 4;
    }
    namespace  DiscretionMoveType {
        constexpr int64_t Floating = 0;
        constexpr int64_t Fixed = 1;
    }
    namespace  DiscretionOffsetType {
        constexpr int64_t Price = 0;
        constexpr int64_t BasisPoints = 1;
        constexpr int64_t Ticks = 2;
        constexpr int64_t PriceTier = 3;
    }
    namespace  DiscretionLimitType {
        constexpr int64_t OrBetter = 0;
        constexpr int64_t Strict = 1;
        constexpr int64_t OrWorse = 2;
    }
    namespace  DiscretionRoundDirection {
        constexpr int64_t MoreAggressive = 1;
        constexpr int64_t MorePassive = 2;
    }
    namespace  DiscretionScope {
        constexpr int64_t Local = 1;
        constexpr int64_t National = 2;
        constexpr int64_t Global = 3;
        constexpr int64_t NationalExcludingLocal = 4;
    }
    namespace  TargetStrategy {
        constexpr int64_t VWAP = 1;
        constexpr int64_t Participate = 2;
        constexpr int64_t MininizeMarketImpact = 3;
    }
    namespace  LastLiquidityInd {
        constexpr int64_t AddedLiquidity = 1;
        constexpr int64_t RemovedLiquidity = 2;
        constexpr int64_t LiquidityRoutedOut = 3;
        constexpr int64_t Auction = 4;
    }
    namespace  PublishTrdIndicator {
        constexpr char DoNotReportTrade = 'N';
        constexpr char ReportTrade = 'Y';
    }
    namespace  ShortSaleReason {
        constexpr int64_t DealerSoldShort = 0;
        constexpr int64_t DealerSoldShortExempt = 1;
        constexpr int64_t SellingCustomerSoldShort = 2;
        constexpr int64_t SellingCustomerSoldShortExempt = 3;
        constexpr int64_t QualifiedServiceRepresentative = 4;
        constexpr int64_t QSROrAGUContraSideSoldShortExempt = 5;
    }
    namespace  QtyType {
        constexpr int64_t Units = 0;
        constexpr int64_t Contracts = 1;
        constexpr int64_t UnitsOfMeasurePerTimeUnit = 2;
    }
    namespace  TradeReportType {
        constexpr int64_t Submit = 0;
        constexpr int64_t Alleged = 1;
        constexpr int64_t Accept = 2;
        constexpr int64_t Decline = 3;
        constexpr int64_t Addendum = 4;
        constexpr int64_t No = 5;
        constexpr int64_t TradeReportCancel = 6;
        constexpr int64_t LockedIn = 7;
        constexpr int64_t Defaulted = 8;
        constexpr int64_t InvalidCMTA = 9;
        constexpr int64_t Pended = 10;
        constexpr int64_t AllegedNew = 11;
        constexpr int64_t AllegedAddendum = 12;
        constexpr int64_t AllegedNo = 13;
        constexpr int64_t AllegedTradeReportCancel = 14;
        constexpr int64_t AllegedTradeBreak = 15;
    }
    namespace  AllocNoOrdersType {
        constexpr int64_t NotSpecified = 0;
        constexpr int64_t ExplicitListProvided = 1;
    }
    namespace  EventType {
        constexpr int64_t Put = 1;
        constexpr int64_t Call = 2;
        constexpr int64_t Tender = 3;
        constexpr int64_t SinkingFundCall = 4;
        constexpr int64_t Activation = 5;
        constexpr int64_t Inactiviation = 6;
        constexpr int64_t LastEligibleTradeDate = 7;
        constexpr int64_t SwapStartDate = 8;
        constexpr int64_t SwapEndDate = 9;
        constexpr int64_t SwapRollDate = 10;
        constexpr int64_t SwapNextStartDate = 11;
        constexpr int64_t SwapNextRollDate = 12;
        constexpr int64_t FirstDeliveryDate = 13;
        constexpr int64_t LastDeliveryDate = 14;
        constexpr int64_t InitialInventoryDueDate = 15;
        constexpr int64_t FinalInventoryDueDate = 16;
        constexpr int64_t FirstIntentDate = 17;
        constexpr int64_t LastIntentDate = 18;
        constexpr int64_t PositionRemovalDate = 19;
        constexpr int64_t Other = 99;
    }
    namespace  InstrAttribType {
        constexpr int64_t Flat = 1;
        constexpr int64_t ZeroCoupon = 2;
        constexpr int64_t InterestBearing = 3;
        constexpr int64_t NoPeriodicPayments = 4;
        constexpr int64_t VariableRate = 5;
        constexpr int64_t LessFeeForPut = 6;
        constexpr int64_t SteppedCoupon = 7;
        constexpr int64_t CouponPeriod = 8;
        constexpr int64_t When = 9;
        constexpr int64_t OriginalIssueDiscount = 10;
        constexpr int64_t Callable = 11;
        constexpr int64_t EscrowedToMaturity = 12;
        constexpr int64_t EscrowedToRedemptionDate = 13;
        constexpr int64_t PreRefunded = 14;
        constexpr int64_t InDefault = 15;
        constexpr int64_t Unrated = 16;
        constexpr int64_t Taxable = 17;
        constexpr int64_t Indexed = 18;
        constexpr int64_t SubjectToAlternativeMinimumTax = 19;
        constexpr int64_t OriginalIssueDiscountPrice = 20;
        constexpr int64_t CallableBelowMaturityValue = 21;
        constexpr int64_t CallableWithoutNotice = 22;
        constexpr int64_t PriceTickRulesForSecurity = 23;
        constexpr int64_t TradeTypeEligibilityDetailsForSecurity = 24;
        constexpr int64_t InstrumentDenominator = 25;
        constexpr int64_t InstrumentNumerator = 26;
        constexpr int64_t InstrumentPricePrecision = 27;
        constexpr int64_t InstrumentStrikePrice = 28;
        constexpr int64_t TradeableIndicator = 29;
        constexpr int64_t Text = 99;
    }
    namespace  CPProgram {
        constexpr int64_t Program3a3 = 1;
        constexpr int64_t Program42 = 2;
        constexpr int64_t Other = 99;
    }
    namespace  MiscFeeBasis {
        constexpr int64_t Absolute = 0;
        constexpr int64_t PerUnit = 1;
        constexpr int64_t Percentage = 2;
    }
    namespace  LastFragment {
        constexpr char NotLastMessage = 'N';
        constexpr char LastMessage = 'Y';
    }
    namespace  CollAsgnReason {
        constexpr int64_t Initial = 0;
        constexpr int64_t Scheduled = 1;
        constexpr int64_t TimeWarning = 2;
        constexpr int64_t MarginDeficiency = 3;
        constexpr int64_t MarginExcess = 4;
        constexpr int64_t ForwardCollateralDemand = 5;
        constexpr int64_t EventOfDefault = 6;
        constexpr int64_t AdverseTaxEvent = 7;
    }
    namespace  CollInquiryQualifier {
        constexpr int64_t TradeDate = 0;
        constexpr int64_t GCInstrument = 1;
        constexpr int64_t CollateralInstrument = 2;
        constexpr int64_t SubstitutionEligible = 3;
        constexpr int64_t NotAssigned = 4;
        constexpr int64_t PartiallyAssigned = 5;
        constexpr int64_t FullyAssigned = 6;
        constexpr int64_t OutstandingTrades = 7;
    }
    namespace  CollAsgnTransType {
        constexpr int64_t New = 0;
        constexpr int64_t Replace = 1;
        constexpr int64_t Cancel = 2;
        constexpr int64_t Release = 3;
        constexpr int64_t Reverse = 4;
    }
    namespace  CollAsgnRespType {
        constexpr int64_t Received = 0;
        constexpr int64_t Accepted = 1;
        constexpr int64_t Declined = 2;
        constexpr int64_t Rejected = 3;
    }
    namespace  CollAsgnRejectReason {
        constexpr int64_t UnknownDeal = 0;
        constexpr int64_t UnknownOrInvalidInstrument = 1;
        constexpr int64_t UnauthorizedTransaction = 2;
        constexpr int64_t InsufficientCollateral = 3;
        constexpr int64_t InvalidTypeOfCollateral = 4;
        constexpr int64_t ExcessiveSubstitution = 5;
        constexpr int64_t Other = 99;
    }
    namespace  CollStatus {
        constexpr int64_t Unassigned = 0;
        constexpr int64_t PartiallyAssigned = 1;
        constexpr int64_t AssignmentProposed = 2;
        constexpr int64_t Assigned = 3;
        constexpr int64_t Challenged = 4;
    }
    namespace  LastRptRequested {
        constexpr char NotLastMessage = 'N';
        constexpr char LastMessage = 'Y';
    }
    namespace  DeliveryType {
        constexpr int64_t VersusPayment = 0;
        constexpr int64_t Free = 1;
        constexpr int64_t TriParty = 2;
        constexpr int64_t HoldInCustody = 3;
    }
    namespace  UserRequestType {
        constexpr int64_t LogOnUser = 1;
        constexpr int64_t LogOffUser = 2;
        constexpr int64_t ChangePasswordForUser = 3;
        constexpr int64_t RequestIndividualUserStatus = 4;
    }
    namespace  UserStatus {
        constexpr int64_t LoggedIn = 1;
        constexpr int64_t NotLoggedIn = 2;
        constexpr int64_t UserNotRecognised = 3;
        constexpr int64_t PasswordIncorrect = 4;
        constexpr int64_t PasswordChanged = 5;
        constexpr int64_t Other = 6;
        constexpr int64_t ForcedUserLogoutByExchange = 7;
        constexpr int64_t SessionShutdownWarning = 8;
    }
    namespace  StatusValue {
        constexpr int64_t Connected = 1;
        constexpr int64_t NotConnectedUnexpected = 2;
        constexpr int64_t NotConnectedExpected = 3;
        constexpr int64_t InProcess = 4;
    }
    namespace  NetworkRequestType {
        constexpr int64_t Snapshot = 1;
        constexpr int64_t Subscribe = 2;
        constexpr int64_t StopSubscribing = 4;
        constexpr int64_t LevelOfDetail = 8;
    }
    namespace  NetworkStatusResponseType {
        constexpr int64_t Full = 1;
        constexpr int64_t IncrementalUpdate = 2;
    }
    namespace  TrdRptStatus {
        constexpr int64_t Accepted = 0;
        constexpr int64_t Rejected = 1;
        constexpr int64_t AcceptedWithErrors = 3;
    }
    namespace  AffirmStatus {
        constexpr int64_t Received = 1;
        constexpr int64_t ConfirmRejected = 2;
        constexpr int64_t Affirmed = 3;
    }
    namespace  CollAction {
        constexpr int64_t Retain = 0;
        constexpr int64_t Add = 1;
        constexpr int64_t Remove = 2;
    }
    namespace  CollInquiryStatus {
        constexpr int64_t Accepted = 0;
        constexpr int64_t AcceptedWithWarnings = 1;
        constexpr int64_t Completed = 2;
        constexpr int64_t CompletedWithWarnings = 3;
        constexpr int64_t Rejected = 4;
    }
    namespace  CollInquiryResult {
        constexpr int64_t Successful = 0;
        constexpr int64_t InvalidOrUnknownInstrument = 1;
        constexpr int64_t InvalidOrUnknownCollateralType = 2;
        constexpr int64_t InvalidParties = 3;
        constexpr int64_t InvalidTransportTypeRequested = 4;
        constexpr int64_t InvalidDestinationRequested = 5;
        constexpr int64_t NoCollateralFoundForTheTradeSpecified = 6;
        constexpr int64_t NoCollateralFoundForTheOrderSpecified = 7;
        constexpr int64_t CollateralInquiryTypeNotSupported = 8;
        constexpr int64_t UnauthorizedForCollateralInquiry = 9;
        constexpr int64_t Other = 99;
    }
    namespace  StrategyParameterType {
        constexpr int64_t Int = 1;
        constexpr int64_t Length = 2;
        constexpr int64_t NumInGroup = 3;
        constexpr int64_t SeqNum = 4;
        constexpr int64_t TagNum = 5;
        constexpr int64_t Float = 6;
        constexpr int64_t Qty = 7;
        constexpr int64_t Price = 8;
        constexpr int64_t PriceOffset = 9;
        constexpr int64_t Amt = 10;
        constexpr int64_t Percentage = 11;
        constexpr int64_t Char = 12;
        constexpr int64_t Boolean = 13;
        constexpr int64_t String = 14;
        constexpr int64_t MultipleCharValue = 15;
        constexpr int64_t Currency = 16;
        constexpr int64_t Exchange = 17;
        constexpr int64_t MonthYear = 18;
        constexpr int64_t UTCTimestamp = 19;
        constexpr int64_t UTCTimeOnly = 20;
        constexpr int64_t LocalMktDate = 21;
        constexpr int64_t UTCDateOnly = 22;
        constexpr int64_t Data = 23;
        constexpr int64_t MultipleStringValue = 24;
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
        constexpr int64_t TPlus1 = 2;
        constexpr int64_t TPlus3 = 4;
        constexpr int64_t TPlus4 = 5;
    }
    namespace  SecurityUpdateAction {
        constexpr char Add = 'A';
        constexpr char Delete = 'D';
        constexpr char Modify = 'M';
    }
    namespace  ExpirationQtyType {
        constexpr int64_t AutoExercise = 1;
        constexpr int64_t NonAutoExercise = 2;
        constexpr int64_t FinalWillBeExercised = 3;
        constexpr int64_t ContraryIntention = 4;
        constexpr int64_t Difference = 5;
    }
    namespace  IndividualAllocType {
        constexpr int64_t SubAllocate = 1;
        constexpr int64_t ThirdPartyAllocation = 2;
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
        constexpr int64_t Automatic = 1;
        constexpr int64_t Guarantor = 2;
        constexpr int64_t Manual = 3;
    }
    namespace  AsOfIndicator {
        constexpr char False = '0';
        constexpr char True = '1';
    }
    namespace  MDBookType {
        constexpr int64_t TopOfBook = 1;
        constexpr int64_t PriceDepth = 2;
        constexpr int64_t OrderDepth = 3;
    }
    namespace  MDOriginType {
        constexpr int64_t Book = 0;
        constexpr int64_t OffBook = 1;
        constexpr int64_t Cross = 2;
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
        constexpr int64_t NASDOATS = 1;
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
        constexpr int64_t NASDOATS = 1;
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
        constexpr int64_t SpecificDeposit = 0;
        constexpr int64_t General = 1;
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

    namespace AggressorSide {
        constexpr int64_t Buy = 1;
        constexpr int64_t Sell = 2;
    };

    namespace  AggressorIndicator {
        constexpr char OrderInitiatorIsAggressor = 'Y';
        constexpr char OrderInitiatorIsPassive = 'N';
    }
    namespace  MDQuoteType {
        constexpr int64_t Indicative = 0;
        constexpr int64_t Tradeable = 1;
        constexpr int64_t RestrictedTradeable = 2;
        constexpr int64_t Counter = 3;
        constexpr int64_t IndicativeAndTradeable = 4;
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
        constexpr int64_t LastPeg = 1;
        constexpr int64_t MidPricePeg = 2;
        constexpr int64_t OpeningPeg = 3;
        constexpr int64_t MarketPeg = 4;
        constexpr int64_t PrimaryPeg = 5;
        constexpr int64_t PegToVWAP = 7;
        constexpr int64_t TrailingStopPeg = 8;
        constexpr int64_t PegToLimitPrice = 9;
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
        constexpr int64_t NotImplied = 0;
        constexpr int64_t ImpliedIn = 1;
        constexpr int64_t ImpliedOut = 2;
        constexpr int64_t BothImpliedInAndImpliedOut = 3;
    }
    namespace  SettlObligMode {
        constexpr int64_t Preliminary = 1;
        constexpr int64_t Final = 2;
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
        constexpr int64_t Accepted = 0;
        constexpr int64_t Rejected = 5;
        constexpr int64_t RemovedFromMarket = 6;
        constexpr int64_t Expired = 7;
        constexpr int64_t LockedMarketWarning = 12;
        constexpr int64_t CrossMarketWarning = 13;
        constexpr int64_t CanceledDueToLockMarket = 14;
        constexpr int64_t CanceledDueToCrossMarket = 15;
        constexpr int64_t Active = 16;
    }
    namespace  PrivateQuote {
        constexpr char PrivateQuote = 'Y';
        constexpr char PublicQuote = 'N';
    }
    namespace  RespondentType {
        constexpr int64_t AllMarketParticipants = 1;
        constexpr int64_t SpecifiedMarketParticipants = 2;
        constexpr int64_t AllMarketMakers = 3;
        constexpr int64_t PrimaryMarketMaker = 4;
    }
    namespace  SecurityTradingEvent {
        constexpr int64_t OrderImbalance = 1;
        constexpr int64_t TradingResumes = 2;
        constexpr int64_t PriceVolatilityInterruption = 3;
        constexpr int64_t ChangeOfTradingSession = 4;
        constexpr int64_t ChangeOfTradingSubsession = 5;
        constexpr int64_t ChangeOfSecurityTradingStatus = 6;
        constexpr int64_t ChangeOfBookType = 7;
        constexpr int64_t ChangeOfMarketDepth = 8;
    }
    namespace  StatsType {
        constexpr int64_t ExchangeLast = 1;
        constexpr int64_t High = 2;
        constexpr int64_t AveragePrice = 3;
        constexpr int64_t Turnover = 4;
    }
    namespace  MDSecSizeType {
        constexpr int64_t Customer = 1;
    }
    namespace  SettlMethod {
        constexpr char CashSettlementRequired = 'C';
        constexpr char PhysicalSettlementRequired = 'P';
    }
    namespace  ExerciseStyle {
        constexpr int64_t European = 0;
        constexpr int64_t American = 1;
        constexpr int64_t Bermuda = 2;
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
        constexpr int64_t PreListedOnly = 0;
        constexpr int64_t UserRequested = 1;
    }
    namespace  TickRuleType {
        constexpr int64_t Regular = 0;
        constexpr int64_t Variable = 1;
        constexpr int64_t Fixed = 2;
        constexpr int64_t TradedAsASpreadLeg = 3;
        constexpr int64_t SettledAsASpreadLeg = 4;
    }
    namespace  MaturityMonthYearIncrementUnits {
        constexpr int64_t Months = 0;
        constexpr int64_t Days = 1;
        constexpr int64_t Weeks = 2;
        constexpr int64_t Years = 3;
    }
    namespace  MaturityMonthYearFormat {
        constexpr int64_t YearMonthOnly = 0;
        constexpr int64_t YearMonthDay = 1;
        constexpr int64_t YearMonthWeek = 2;
    }
    namespace  PriceLimitType {
        constexpr int64_t Price = 0;
        constexpr int64_t Ticks = 1;
        constexpr int64_t Percentage = 2;
    }
    namespace  MarketUpdateAction {
        constexpr char Add = 'A';
        constexpr char Delete = 'D';
        constexpr char Modify = 'M';
    }
    namespace  SessionStatus {
        constexpr int64_t SessionActive = 0;
        constexpr int64_t SessionPasswordChanged = 1;
        constexpr int64_t SessionPasswordDueToExpire = 2;
        constexpr int64_t NewSessionPasswordDoesNotComplyWithPolicy = 3;
        constexpr int64_t SessionLogoutComplete = 4;
        constexpr int64_t InvalidUsernameOrPassword = 5;
        constexpr int64_t AccountLocked = 6;
        constexpr int64_t LogonsAreNotAllowedAtThisTime = 7;
        constexpr int64_t PasswordExpired = 8;
    }
    namespace  TradSesEvent {
        constexpr int64_t TradingResumes = 0;
        constexpr int64_t ChangeOfTradingSession = 1;
        constexpr int64_t ChangeOfTradingSubsession = 2;
        constexpr int64_t ChangeOfTradingStatus = 3;
    }
    namespace  MassActionType {
        constexpr int64_t SuspendOrders = 1;
        constexpr int64_t ReleaseOrdersFromSuspension = 2;
        constexpr int64_t CancelOrders = 3;
    }
    namespace  MassActionScope {
        constexpr int64_t AllOrdersForASecurity = 1;
        constexpr int64_t AllOrdersForAnUnderlyingSecurity = 2;
        constexpr int64_t AllOrdersForAProduct = 3;
        constexpr int64_t AllOrdersForACFICode = 4;
        constexpr int64_t AllOrdersForASecurityType = 5;
        constexpr int64_t AllOrdersForATradingSession = 6;
        constexpr int64_t AllOrders = 7;
        constexpr int64_t AllOrdersForAMarket = 8;
        constexpr int64_t AllOrdersForAMarketSegment = 9;
        constexpr int64_t AllOrdersForASecurityGroup = 10;
    }
    namespace  MassActionResponse {
        constexpr int64_t Rejected = 0;
        constexpr int64_t Accepted = 1;
    }
    namespace  MassActionRejectReason {
        constexpr int64_t MassActionNotSupported = 0;
        constexpr int64_t InvalidOrUnknownSecurity = 1;
        constexpr int64_t InvalidOrUnknownUnderlyingSecurity = 2;
        constexpr int64_t InvalidOrUnknownProduct = 3;
        constexpr int64_t InvalidOrUnknownCFICode = 4;
        constexpr int64_t InvalidOrUnknownSecurityType = 5;
        constexpr int64_t InvalidOrUnknownTradingSession = 6;
        constexpr int64_t InvalidOrUnknownMarket = 7;
        constexpr int64_t InvalidOrUnknownMarketSegment = 8;
        constexpr int64_t InvalidOrUnknownSecurityGroup = 9;
        constexpr int64_t Other = 99;
    }
    namespace  MultilegModel {
        constexpr int64_t PredefinedMultilegSecurity = 0;
        constexpr int64_t UserDefinedMultilegSecurity = 1;
        constexpr int64_t UserDefined = 2;
    }
    namespace  MultilegPriceMethod {
        constexpr int64_t NetPrice = 0;
        constexpr int64_t ReversedNetPrice = 1;
        constexpr int64_t YieldDifference = 2;
        constexpr int64_t Individual = 3;
        constexpr int64_t ContractWeightedAveragePrice = 4;
        constexpr int64_t MultipliedPrice = 5;
    }
    namespace  ContingencyType {
        constexpr int64_t OneCancelsTheOther = 1;
        constexpr int64_t OneTriggersTheOther = 2;
        constexpr int64_t OneUpdatesTheOtherAbsolute = 3;
        constexpr int64_t OneUpdatesTheOtherProportional = 4;
    }
    namespace  ListRejectReason {
        constexpr int64_t BrokerCredit = 0;
        constexpr int64_t ExchangeClosed = 2;
        constexpr int64_t TooLateToEnter = 4;
        constexpr int64_t UnknownOrder = 5;
        constexpr int64_t DuplicateOrder = 6;
        constexpr int64_t UnsupportedOrderCharacteristic = 11;
        constexpr int64_t Other = 99;
    }
    namespace  TradePublishIndicator {
        constexpr int64_t DoNotPublishTrade = 0;
        constexpr int64_t PublishTrade = 1;
        constexpr int64_t DeferredPublication = 2;
    }
    namespace  ApplReqType {
        constexpr int64_t Retransmission = 0;
        constexpr int64_t Subscription = 1;
        constexpr int64_t RequestLastSeqNum = 2;
        constexpr int64_t RequestApplications = 3;
        constexpr int64_t Unsubscribe = 4;
    }
    namespace  ApplResponseType {
        constexpr int64_t RequestSuccessfullyProcessed = 0;
        constexpr int64_t ApplicationDoesNotExist = 1;
        constexpr int64_t MessagesNotAvailable = 2;
    }
    namespace  ApplResponseError {
        constexpr int64_t ApplicationDoesNotExist = 0;
        constexpr int64_t MessagesRequestedAreNotAvailable = 1;
        constexpr int64_t UserNotAuthorizedForApplication = 2;
    }
    namespace  ApplReportType {
        constexpr int64_t ApplSeqNumReset = 0;
        constexpr int64_t LastMessageSent = 1;
        constexpr int64_t ApplicationAlive = 2;
    }
    namespace  OrderDelayUnit {
        constexpr int64_t Seconds = 0;
        constexpr int64_t TenthsOfASecond = 1;
        constexpr int64_t HundredthsOfASecond = 2;
        constexpr int64_t Milliseconds = 3;
        constexpr int64_t Microseconds = 4;
        constexpr int64_t Nanoseconds = 5;
        constexpr int64_t Minutes = 10;
        constexpr int64_t Hours = 11;
        constexpr int64_t Days = 12;
        constexpr int64_t Weeks = 13;
        constexpr int64_t Months = 14;
        constexpr int64_t Years = 15;
    }
    namespace  VenueType {
        constexpr char Electronic = 'E';
        constexpr char Pit = 'P';
        constexpr char ExPit = 'X';
    }
    namespace  RefOrdIDReason {
        constexpr int64_t GTCFromPreviousDay = 0;
        constexpr int64_t PartialFillRemaining = 1;
        constexpr int64_t OrderChanged = 2;
    }
    namespace  OrigCustOrderCapacity {
        constexpr int64_t MemberTradingForTheirOwnAccount = 1;
        constexpr int64_t ClearingFirmTradingForItsProprietaryAccount = 2;
        constexpr int64_t MemberTradingForAnotherMember = 3;
        constexpr int64_t AllOther = 4;
    }
    namespace  TrdRegTimestampType {
        constexpr int64_t SubmissionToClearing = 7;
    }
    namespace  RefOrderIDSource {
        constexpr char OriginalOrderID = '4';
    }
    namespace  OrderRestrictions {
    }
    namespace  ApplReqType {
        constexpr int64_t CancelRetransmission = 5;
        constexpr int64_t CancelRetransmissionUnsubscribe = 6;
    }
    namespace  QuoteCancelType {
        constexpr int64_t CancelByQuoteType = 6;
    }
    namespace  DisplayMethod {
        constexpr char Undisclosed = '4';
    }
    namespace  PosReqType {
        constexpr int64_t DeltaPositions = 6;
    }
    namespace  PartyRole {
        constexpr int64_t CentralRegistrationDepository = 82;
    }
    namespace  ModelType {
        constexpr int64_t UtilityProvidedStandardModel = 0;
        constexpr int64_t ProprietaryModel = 1;
    }
    namespace  PosType {
        constexpr std::string_view NetDeltaQty = "DLT";
    }
    namespace  LotType {
        constexpr char RoundLotBasedUpon = '4';
    }
    namespace  ContractMultiplierUnit {
        constexpr int64_t Shares = 0;
        constexpr int64_t Hours = 1;
        constexpr int64_t Days = 2;
    }
    namespace  FlowScheduleType {
        constexpr int64_t NERCEasternOffPeak = 0;
        constexpr int64_t NERCWesternOffPeak = 1;
        constexpr int64_t NERCCalendarAllDaysInMonth = 2;
        constexpr int64_t NERCEasternPeak = 3;
        constexpr int64_t NERCWesternPeak = 4;
    }
    namespace  RateSource {
        constexpr int64_t Bloomberg = 0;
        constexpr int64_t Reuters = 1;
        constexpr int64_t Telerate = 2;
        constexpr int64_t Other = 99;
    }
    namespace  RateSourceType {
        constexpr int64_t Primary = 0;
        constexpr int64_t Secondary = 1;
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
        constexpr int64_t PostClose = 26;
    }
    namespace  QuoteCancelType {
        constexpr int64_t CancelForSecurityIssuer = 7;
        constexpr int64_t CancelForIssuerOfUnderlyingSecurity = 8;
    }
    namespace  QuoteRejectReason {
        constexpr int64_t InvalidOrUnknownSecurityIssuer = 12;
        constexpr int64_t InvalidOrUnknownIssuerOfUnderlyingSecurity = 13;
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
        constexpr int64_t InvalidOrUnknownSecurityIssuer = 10;
        constexpr int64_t InvalidOrUnknownIssuerOfUnderlyingSecurity = 11;
    }
    namespace  MassStatusReqType {
        constexpr int64_t StatusForSecurityIssuer = 9;
        constexpr int64_t StatusForIssuerOfUnderlyingSecurity = 10;
    }
    namespace  MassActionScope {
        constexpr int64_t CancelForSecurityIssuer = 11;
        constexpr int64_t CancelForIssuerOfUnderlyingSecurity = 12;
    }
    namespace  MassActionRejectReason {
        constexpr int64_t InvalidOrUnknownSecurityIssuer = 10;
        constexpr int64_t InvalidOrUnknownIssuerOfUnderlyingSecurity = 11;
    }
    namespace  HaltReason {
        constexpr int64_t NewsDissemination = 0;
        constexpr int64_t OrderInflux = 1;
        constexpr int64_t OrderImbalance = 2;
        constexpr int64_t AdditionalInformation = 3;
        constexpr int64_t NewsPending = 4;
        constexpr int64_t EquipmentChangeover = 5;
    }
    namespace  SecurityListType {
        constexpr int64_t IndustryClassification = 1;
        constexpr int64_t TradingList = 2;
        constexpr int64_t Market = 3;
        constexpr int64_t NewspaperList = 4;
    }
    namespace  SecurityListTypeSource {
        constexpr int64_t ICB = 1;
        constexpr int64_t NAICS = 2;
        constexpr int64_t GICS = 3;
    }
    namespace  UnitOfMeasure {
        constexpr std::string_view Allowances = "Alw";
    }
    namespace  NewsCategory {
        constexpr int64_t CompanyNews = 0;
        constexpr int64_t MarketplaceNews = 1;
        constexpr int64_t FinancialMarketNews = 2;
        constexpr int64_t TechnicalNews = 3;
        constexpr int64_t OtherNews = 99;
    }
    namespace  NewsRefType {
        constexpr int64_t Replacement = 0;
        constexpr int64_t OtherLanguage = 1;
        constexpr int64_t Complimentary = 2;
    }
    namespace  ApplReportType {
        constexpr int64_t ResendComplete = 3;
    }
    namespace  StrikePriceDeterminationMethod {
        constexpr int64_t FixedStrike = 1;
        constexpr int64_t StrikeSetAtExpiration = 2;
        constexpr int64_t StrikeSetToAverageAcrossLife = 3;
        constexpr int64_t StrikeSetToOptimalValue = 4;
    }
    namespace  StrikePriceBoundaryMethod {
        constexpr int64_t LessThan = 1;
        constexpr int64_t LessThanOrEqual = 2;
        constexpr int64_t Equal = 3;
        constexpr int64_t GreaterThanOrEqual = 4;
        constexpr int64_t GreaterThan = 5;
    }
    namespace  UnderlyingPriceDeterminationMethod {
        constexpr int64_t Regular = 1;
        constexpr int64_t SpecialReference = 2;
        constexpr int64_t OptimalValue = 3;
        constexpr int64_t AverageValue = 4;
    }
    namespace  OptPayoutType {
        constexpr int64_t Vanilla = 1;
        constexpr int64_t Capped = 2;
        constexpr int64_t Binary = 3;
    }
    namespace  ComplexEventType {
        constexpr int64_t Capped = 1;
        constexpr int64_t Trigger = 2;
        constexpr int64_t KnockInUp = 3;
        constexpr int64_t KockInDown = 4;
        constexpr int64_t KnockOutUp = 5;
        constexpr int64_t KnockOutDown = 6;
        constexpr int64_t Underlying = 7;
        constexpr int64_t ResetBarrier = 8;
        constexpr int64_t RollingBarrier = 9;
    }
    namespace  ComplexEventPriceBoundaryMethod {
        constexpr int64_t LessThanComplexEventPrice = 1;
        constexpr int64_t LessThanOrEqualToComplexEventPrice = 2;
        constexpr int64_t EqualToComplexEventPrice = 3;
        constexpr int64_t GreaterThanOrEqualToComplexEventPrice = 4;
        constexpr int64_t GreaterThanComplexEventPrice = 5;
    }
    namespace  ComplexEventPriceTimeType {
        constexpr int64_t Expiration = 1;
        constexpr int64_t Immediate = 2;
        constexpr int64_t SpecifiedDate = 3;
    }
    namespace  ComplexEventCondition {
        constexpr int64_t And = 1;
        constexpr int64_t Or = 2;
    }
    namespace  StreamAsgnReqType {
        constexpr int64_t StreamAssignmentForNewCustomer = 1;
        constexpr int64_t StreamAssignmentForExistingCustomer = 2;
    }
    namespace  StreamAsgnRejReason {
        constexpr int64_t UnknownClient = 0;
        constexpr int64_t ExceedsMaximumSize = 1;
        constexpr int64_t UnknownOrInvalidCurrencyPair = 2;
        constexpr int64_t NoAvailableStream = 3;
        constexpr int64_t Other = 99;
    }
    namespace  StreamAsgnAckType {
        constexpr int64_t AssignmentAccepted = 0;
        constexpr int64_t AssignmentRejected = 1;
    }
    namespace  StreamAsgnType {
        constexpr int64_t Assignment = 1;
        constexpr int64_t Rejected = 2;
        constexpr int64_t Terminate = 3;
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
        constexpr int64_t Other = 99;
    }
    namespace  StrategyParameterType {
        constexpr int64_t Country = 25;
        constexpr int64_t Language = 26;
        constexpr int64_t TZTimeOnly = 27;
        constexpr int64_t TZTimestamp = 28;
        constexpr int64_t Tenor = 29;
    }
    namespace  PartyRole {
        constexpr int64_t ClearingAccount = 83;
        constexpr int64_t AcceptableSettlingCounterparty = 84;
        constexpr int64_t UnacceptableSettlingCounterparty = 85;
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