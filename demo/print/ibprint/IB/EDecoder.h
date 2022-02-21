/* Copyright (C) 2019 Interactive Brokers LLC. All rights reserved. This code is subject to the terms
 * and conditions of the IB API Non-Commercial License or the IB API Commercial License, as applicable. */

#pragma once
#ifndef TWS_API_CLIENT_EDECODER_H
#define TWS_API_CLIENT_EDECODER_H

#include "platformspecific.h"
#include "Contract.h"
#include "HistoricalTick.h"
#include "HistoricalTickBidAsk.h"
#include "HistoricalTickLast.h"



//const int MIN_SERVER_VER_REAL_TIME_BARS       = 34;
//const int MIN_SERVER_VER_SCALE_ORDERS         = 35;
//const int MIN_SERVER_VER_SNAPSHOT_MKT_DATA    = 35;
//const int MIN_SERVER_VER_SSHORT_COMBO_LEGS    = 35;
//const int MIN_SERVER_VER_WHAT_IF_ORDERS       = 36;
//const int MIN_SERVER_VER_CONTRACT_CONID       = 37;
const int MIN_SERVER_VER_PTA_ORDERS                 = 39;
const int MIN_SERVER_VER_FUNDAMENTAL_DATA           = 40;
const int MIN_SERVER_VER_DELTA_NEUTRAL              = 40;
const int MIN_SERVER_VER_CONTRACT_DATA_CHAIN        = 40;
const int MIN_SERVER_VER_SCALE_ORDERS2              = 40;
const int MIN_SERVER_VER_ALGO_ORDERS                = 41;
const int MIN_SERVER_VER_EXECUTION_DATA_CHAIN       = 42;
const int MIN_SERVER_VER_NOT_HELD                   = 44;
const int MIN_SERVER_VER_SEC_ID_TYPE                = 45;
const int MIN_SERVER_VER_PLACE_ORDER_CONID          = 46;
const int MIN_SERVER_VER_REQ_MKT_DATA_CONID         = 47;
const int MIN_SERVER_VER_REQ_CALC_IMPLIED_VOLAT     = 49;
const int MIN_SERVER_VER_REQ_CALC_OPTION_PRICE      = 50;
const int MIN_SERVER_VER_CANCEL_CALC_IMPLIED_VOLAT  = 50;
const int MIN_SERVER_VER_CANCEL_CALC_OPTION_PRICE   = 50;
const int MIN_SERVER_VER_SSHORTX_OLD                = 51;
const int MIN_SERVER_VER_SSHORTX                    = 52;
const int MIN_SERVER_VER_REQ_GLOBAL_CANCEL          = 53;
const int MIN_SERVER_VER_HEDGE_ORDERS               = 54;
const int MIN_SERVER_VER_REQ_MARKET_DATA_TYPE       = 55;
const int MIN_SERVER_VER_OPT_OUT_SMART_ROUTING      = 56;
const int MIN_SERVER_VER_SMART_COMBO_ROUTING_PARAMS = 57;
const int MIN_SERVER_VER_DELTA_NEUTRAL_CONID        = 58;
const int MIN_SERVER_VER_SCALE_ORDERS3              = 60;
const int MIN_SERVER_VER_ORDER_COMBO_LEGS_PRICE     = 61;
const int MIN_SERVER_VER_TRAILING_PERCENT           = 62;
const int MIN_SERVER_VER_DELTA_NEUTRAL_OPEN_CLOSE   = 66;
const int MIN_SERVER_VER_POSITIONS                  = 67;
const int MIN_SERVER_VER_ACCOUNT_SUMMARY            = 67;
const int MIN_SERVER_VER_TRADING_CLASS              = 68;
const int MIN_SERVER_VER_SCALE_TABLE                = 69;
const int MIN_SERVER_VER_LINKING                    = 70;
const int MIN_SERVER_VER_ALGO_ID                    = 71;
const int MIN_SERVER_VER_OPTIONAL_CAPABILITIES      = 72;
const int MIN_SERVER_VER_ORDER_SOLICITED            = 73;
const int MIN_SERVER_VER_LINKING_AUTH               = 74;
const int MIN_SERVER_VER_PRIMARYEXCH                = 75;
const int MIN_SERVER_VER_RANDOMIZE_SIZE_AND_PRICE   = 76;
const int MIN_SERVER_VER_FRACTIONAL_POSITIONS       = 101;
const int MIN_SERVER_VER_PEGGED_TO_BENCHMARK        = 102;
const int MIN_SERVER_VER_MODELS_SUPPORT             = 103;
const int MIN_SERVER_VER_SEC_DEF_OPT_PARAMS_REQ     = 104;
const int MIN_SERVER_VER_EXT_OPERATOR               = 105;
const int MIN_SERVER_VER_SOFT_DOLLAR_TIER           = 106;
const int MIN_SERVER_VER_REQ_FAMILY_CODES           = 107;
const int MIN_SERVER_VER_REQ_MATCHING_SYMBOLS       = 108;
const int MIN_SERVER_VER_PAST_LIMIT                 = 109;
const int MIN_SERVER_VER_MD_SIZE_MULTIPLIER         = 110;
const int MIN_SERVER_VER_CASH_QTY                   = 111;
const int MIN_SERVER_VER_REQ_MKT_DEPTH_EXCHANGES    = 112;
const int MIN_SERVER_VER_TICK_NEWS                  = 113;
const int MIN_SERVER_VER_REQ_SMART_COMPONENTS       = 114;
const int MIN_SERVER_VER_REQ_NEWS_PROVIDERS         = 115;
const int MIN_SERVER_VER_REQ_NEWS_ARTICLE           = 116;
const int MIN_SERVER_VER_REQ_HISTORICAL_NEWS        = 117;
const int MIN_SERVER_VER_REQ_HEAD_TIMESTAMP         = 118;
const int MIN_SERVER_VER_REQ_HISTOGRAM              = 119;
const int MIN_SERVER_VER_SERVICE_DATA_TYPE          = 120;
const int MIN_SERVER_VER_AGG_GROUP                  = 121;
const int MIN_SERVER_VER_UNDERLYING_INFO            = 122;
const int MIN_SERVER_VER_CANCEL_HEADTIMESTAMP       = 123;
const int MIN_SERVER_VER_SYNT_REALTIME_BARS         = 124;
const int MIN_SERVER_VER_CFD_REROUTE                = 125;
const int MIN_SERVER_VER_MARKET_RULES               = 126;
const int MIN_SERVER_VER_DAILY_PNL                  = 127;
const int MIN_SERVER_VER_PNL                        = 127;
const int MIN_SERVER_VER_NEWS_QUERY_ORIGINS         = 128;
const int MIN_SERVER_VER_UNREALIZED_PNL             = 129;
const int MIN_SERVER_VER_HISTORICAL_TICKS           = 130;
const int MIN_SERVER_VER_MARKET_CAP_PRICE           = 131;
const int MIN_SERVER_VER_PRE_OPEN_BID_ASK           = 132;
const int MIN_SERVER_VER_REAL_EXPIRATION_DATE       = 134;
const int MIN_SERVER_VER_REALIZED_PNL               = 135;
const int MIN_SERVER_VER_LAST_LIQUIDITY             = 136;
const int MIN_SERVER_VER_TICK_BY_TICK               = 137;
const int MIN_SERVER_VER_DECISION_MAKER             = 138;
const int MIN_SERVER_VER_MIFID_EXECUTION            = 139;
const int MIN_SERVER_VER_TICK_BY_TICK_IGNORE_SIZE   = 140;
const int MIN_SERVER_VER_AUTO_PRICE_FOR_HEDGE       = 141;
const int MIN_SERVER_VER_WHAT_IF_EXT_FIELDS         = 142;
const int MIN_SERVER_VER_SCANNER_GENERIC_OPTS       = 143;
const int MIN_SERVER_VER_API_BIND_ORDER             = 144;
const int MIN_SERVER_VER_ORDER_CONTAINER            = 145;
const int MIN_SERVER_VER_SMART_DEPTH                = 146;
const int MIN_SERVER_VER_REMOVE_NULL_ALL_CASTING    = 147;
const int MIN_SERVER_VER_D_PEG_ORDERS               = 148;
const int MIN_SERVER_VER_MKT_DEPTH_PRIM_EXCHANGE    = 149;
const int MIN_SERVER_VER_COMPLETED_ORDERS           = 150;
const int MIN_SERVER_VER_PRICE_MGMT_ALGO            = 151;

/* 100+ messaging */
// 100 = enhanced handshake, msg length prefixes

const int MIN_CLIENT_VER = 100;
const int MAX_CLIENT_VER = MIN_SERVER_VER_PRICE_MGMT_ALGO;


// incoming msg id's
const int TICK_PRICE                                = 1;
const int TICK_SIZE                                 = 2;
const int ORDER_STATUS                              = 3;
const int ERR_MSG                                   = 4;
const int OPEN_ORDER                                = 5;
const int ACCT_VALUE                                = 6;
const int PORTFOLIO_VALUE                           = 7;
const int ACCT_UPDATE_TIME                          = 8;
const int NEXT_VALID_ID                             = 9;
const int CONTRACT_DATA                             = 10;
const int EXECUTION_DATA                            = 11;
const int MARKET_DEPTH                              = 12;
const int MARKET_DEPTH_L2                           = 13;
const int NEWS_BULLETINS                            = 14;
const int MANAGED_ACCTS                             = 15;
const int RECEIVE_FA                                = 16;
const int HISTORICAL_DATA                           = 17;
const int BOND_CONTRACT_DATA                        = 18;
const int SCANNER_PARAMETERS                        = 19;
const int SCANNER_DATA                              = 20;
const int TICK_OPTION_COMPUTATION                   = 21;
const int TICK_GENERIC                              = 45;
const int TICK_STRING                               = 46;
const int TICK_EFP                                  = 47;
const int CURRENT_TIME                              = 49;
const int REAL_TIME_BARS                            = 50;
const int FUNDAMENTAL_DATA                          = 51;
const int CONTRACT_DATA_END                         = 52;
const int OPEN_ORDER_END                            = 53;
const int ACCT_DOWNLOAD_END                         = 54;
const int EXECUTION_DATA_END                        = 55;
const int DELTA_NEUTRAL_VALIDATION                  = 56;
const int TICK_SNAPSHOT_END                         = 57;
const int MARKET_DATA_TYPE                          = 58;
const int COMMISSION_REPORT                         = 59;
const int POSITION_DATA                             = 61;
const int POSITION_END                              = 62;
const int ACCOUNT_SUMMARY                           = 63;
const int ACCOUNT_SUMMARY_END                       = 64;
const int VERIFY_MESSAGE_API                        = 65;
const int VERIFY_COMPLETED                          = 66;
const int DISPLAY_GROUP_LIST                        = 67;
const int DISPLAY_GROUP_UPDATED                     = 68;
const int VERIFY_AND_AUTH_MESSAGE_API               = 69;
const int VERIFY_AND_AUTH_COMPLETED                 = 70;
const int POSITION_MULTI                            = 71;
const int POSITION_MULTI_END                        = 72;
const int ACCOUNT_UPDATE_MULTI                      = 73;
const int ACCOUNT_UPDATE_MULTI_END                  = 74;
const int SECURITY_DEFINITION_OPTION_PARAMETER      = 75;
const int SECURITY_DEFINITION_OPTION_PARAMETER_END  = 76;
const int SOFT_DOLLAR_TIERS                         = 77;
const int FAMILY_CODES                              = 78;
const int SYMBOL_SAMPLES                            = 79;
const int MKT_DEPTH_EXCHANGES                       = 80;
const int TICK_REQ_PARAMS                           = 81;
const int SMART_COMPONENTS                          = 82;
const int NEWS_ARTICLE                              = 83;
const int TICK_NEWS                                 = 84;
const int NEWS_PROVIDERS                            = 85;
const int HISTORICAL_NEWS                           = 86;
const int HISTORICAL_NEWS_END                       = 87;
const int HEAD_TIMESTAMP                            = 88;
const int HISTOGRAM_DATA                            = 89;
const int HISTORICAL_DATA_UPDATE                    = 90;
const int REROUTE_MKT_DATA_REQ                      = 91;
const int REROUTE_MKT_DEPTH_REQ                     = 92;
const int MARKET_RULE                               = 93;
const int PNL                                       = 94;
const int PNL_SINGLE                                = 95;
const int HISTORICAL_TICKS                          = 96;
const int HISTORICAL_TICKS_BID_ASK                  = 97;
const int HISTORICAL_TICKS_LAST                     = 98;
const int TICK_BY_TICK                              = 99;
const int ORDER_BOUND                               = 100;
const int COMPLETED_ORDER                           = 101;
const int COMPLETED_ORDERS_END                      = 102;

const int HEADER_LEN = 4; // 4 bytes for msg length
const int MAX_MSG_LEN = 0xFFFFFF; // 16Mb - 1byte
const char API_SIGN[4] = { 'A', 'P', 'I', '\0' }; // "API"


// helper structures
namespace {

struct BarData {
   std::string date;
   double open;
   double high;
   double low;
   double close;
   int volume;
   double average;
   std::string hasGaps;
   int barCount;
};

struct ScanData {
   ContractDetails contract;
   int rank;
   std::string distance;
   std::string benchmark;
   std::string projection;
   std::string legsStr;
};

} // end of anonymous namespace

class EWrapper;
struct EClientMsgSink;

class TWSAPIDLLEXP EDecoder
{
    EWrapper *m_pEWrapper;
    int m_serverVersion;
    EClientMsgSink *m_pClientMsgSink;

    const char* processTickPriceMsg(const char* ptr, const char* endPtr);
    const char* processTickSizeMsg(const char* ptr, const char* endPtr);
    const char* processTickOptionComputationMsg(const char* ptr, const char* endPtr);
    const char* processTickGenericMsg(const char* ptr, const char* endPtr);
    const char* processTickStringMsg(const char* ptr, const char* endPtr);
    const char* processTickEfpMsg(const char* ptr, const char* endPtr);
    const char* processOrderStatusMsg(const char* ptr, const char* endPtr);
    const char* processErrMsgMsg(const char* ptr, const char* endPtr);
    const char* processOpenOrderMsg(const char* ptr, const char* endPtr);
    const char* processAcctValueMsg(const char* ptr, const char* endPtr);
    const char* processPortfolioValueMsg(const char* ptr, const char* endPtr);
    const char* processAcctUpdateTimeMsg(const char* ptr, const char* endPtr);
    const char* processNextValidIdMsg(const char* ptr, const char* endPtr);
    const char* processContractDataMsg(const char* ptr, const char* endPtr);
    const char* processBondContractDataMsg(const char* ptr, const char* endPtr);
    const char* processExecutionDetailsMsg(const char* ptr, const char* endPtr);
    const char* processMarketDepthMsg(const char* ptr, const char* endPtr);
    const char* processMarketDepthL2Msg(const char* ptr, const char* endPtr);
    const char* processNewsBulletinsMsg(const char* ptr, const char* endPtr);
    const char* processManagedAcctsMsg(const char* ptr, const char* endPtr);
    const char* processReceiveFaMsg(const char* ptr, const char* endPtr);
    const char* processHistoricalDataMsg(const char* ptr, const char* endPtr);
    const char* processScannerDataMsg(const char* ptr, const char* endPtr);
    const char* processScannerParametersMsg(const char* ptr, const char* endPtr);
    const char* processCurrentTimeMsg(const char* ptr, const char* endPtr);
    const char* processRealTimeBarsMsg(const char* ptr, const char* endPtr);
    const char* processFundamentalDataMsg(const char* ptr, const char* endPtr);
    const char* processContractDataEndMsg(const char* ptr, const char* endPtr);
    const char* processOpenOrderEndMsg(const char* ptr, const char* endPtr);
    const char* processAcctDownloadEndMsg(const char* ptr, const char* endPtr);
    const char* processExecutionDetailsEndMsg(const char* ptr, const char* endPtr);
    const char* processDeltaNeutralValidationMsg(const char* ptr, const char* endPtr);
    const char* processTickSnapshotEndMsg(const char* ptr, const char* endPtr);
    const char* processMarketDataTypeMsg(const char* ptr, const char* endPtr);
    const char* processCommissionReportMsg(const char* ptr, const char* endPtr);
    const char* processPositionDataMsg(const char* ptr, const char* endPtr);
    const char* processPositionEndMsg(const char* ptr, const char* endPtr);
    const char* processAccountSummaryMsg(const char* ptr, const char* endPtr);
    const char* processAccountSummaryEndMsg(const char* ptr, const char* endPtr);
    const char* processVerifyMessageApiMsg(const char* ptr, const char* endPtr);
    const char* processVerifyCompletedMsg(const char* ptr, const char* endPtr);
    const char* processDisplayGroupListMsg(const char* ptr, const char* endPtr);
    const char* processDisplayGroupUpdatedMsg(const char* ptr, const char* endPtr);
    const char* processVerifyAndAuthMessageApiMsg(const char* ptr, const char* endPtr);
    const char* processVerifyAndAuthCompletedMsg(const char* ptr, const char* endPtr);
    const char* processPositionMultiMsg(const char* ptr, const char* endPtr);
    const char* processPositionMultiEndMsg(const char* ptr, const char* endPtr);
    const char* processAccountUpdateMultiMsg(const char* ptr, const char* endPtr);
    const char* processAccountUpdateMultiEndMsg(const char* ptr, const char* endPtr);
    const char* processSecurityDefinitionOptionalParameterMsg(const char* ptr, const char* endPtr);
    const char* processSecurityDefinitionOptionalParameterEndMsg(const char* ptr, const char* endPtr);
    const char* processSoftDollarTiersMsg(const char* ptr, const char* endPtr);
    const char* processFamilyCodesMsg(const char* ptr, const char* endPtr);
    const char* processSymbolSamplesMsg(const char* ptr, const char* endPtr);
    const char* processMktDepthExchangesMsg(const char* ptr, const char* endPtr);
    const char* processTickNewsMsg(const char* ptr, const char* endPtr);
    const char* processTickReqParamsMsg(const char* ptr, const char* endPtr);
    const char* processSmartComponentsMsg(const char* ptr, const char* endPtr);
    const char* processNewsProvidersMsg(const char* ptr, const char* endPtr);
    const char* processNewsArticleMsg(const char* ptr, const char* endPtr);
    const char* processHistoricalNewsMsg(const char* ptr, const char* endPtr);
    const char* processHistoricalNewsEndMsg(const char* ptr, const char* endPtr);
    const char* processHeadTimestampMsg(const char* ptr, const char* endPtr);
    const char* processHistogramDataMsg(const char* ptr, const char* endPtr);
    const char* processHistoricalDataUpdateMsg(const char* ptr, const char* endPtr);
	const char* processRerouteMktDataReqMsg(const char* ptr, const char* endPtr);
	const char* processRerouteMktDepthReqMsg(const char* ptr, const char* endPtr);
	const char* processMarketRuleMsg(const char* ptr, const char* endPtr);
    const char* processPnLMsg(const char* ptr, const char* endPtr);
    const char* processPnLSingleMsg(const char* ptr, const char* endPtr);
    const char* processHistoricalTicks(const char* ptr, const char* endPtr);
    const char* processHistoricalTicksBidAsk(const char* ptr, const char* endPtr);
    const char* processHistoricalTicksLast(const char* ptr, const char* endPtr);
    const char* processTickByTickDataMsg(const char* ptr, const char* endPtr);
    const char* processOrderBoundMsg(const char* ptr, const char* endPtr);
    const char* processCompletedOrderMsg(const char* ptr, const char* endPtr);
    const char* processCompletedOrdersEndMsg(const char* ptr, const char* endPtr);


    int processConnectAck(const char*& beginPtr, const char* endPtr);

    static const char* decodeTick(HistoricalTick& tick, const char* ptr, const char* endPtr);
    static const char* decodeTick(HistoricalTickBidAsk& tick, const char* ptr, const char* endPtr);
    static const char* decodeTick(HistoricalTickLast& tick, const char* ptr, const char* endPtr);
    void callEWrapperCallBack(int reqId, const std::vector<HistoricalTick> &ticks, bool done);
    void callEWrapperCallBack(int reqId, const std::vector<HistoricalTickBidAsk> &ticks, bool done);
    void callEWrapperCallBack(int reqId, const std::vector<HistoricalTickLast> &ticks, bool done);
    template<typename T> const char* processHistoricalTicks(const char* ptr, const char* endPtr);

	const char* decodeLastTradeDate(const char* ptr, const char* endPtr, ContractDetails& contract, bool isBond);

public:
    static bool CheckOffset(const char* ptr, const char* endPtr);
    static const char* FindFieldEnd(const char* ptr, const char* endPtr);
    // decoders
    static bool DecodeField(bool&, const char*& ptr, const char* endPtr);
    static bool DecodeField(int&, const char*& ptr, const char* endPtr);
    static bool DecodeField(long&, const char*& ptr, const char* endPtr);
    static bool DecodeField(long long&, const char*& ptr, const char* endPtr);
    static bool DecodeField(double&, const char*& ptr, const char* endPtr);
    static bool DecodeField(std::string&, const char*& ptr, const char* endPtr);
    static bool DecodeField(char&, const char*& ptr, const char* endPtr);

    static bool DecodeFieldTime(time_t&, const char*& ptr, const char* endPtr);

    static bool DecodeFieldMax(int&, const char*& ptr, const char* endPtr);
    static bool DecodeFieldMax(long&, const char*& ptr, const char* endPtr);
    static bool DecodeFieldMax(double&, const char*& ptr, const char* endPtr);

    EDecoder(int serverVersion, EWrapper *callback, EClientMsgSink *clientMsgSink = 0);

    int parseAndProcessMsg(const char*& beginPtr, const char* endPtr);
};

#define DECODE_FIELD(x) if (!EDecoder::DecodeField(x, ptr, endPtr)) return 0;
#define DECODE_FIELD_TIME(x) if (!EDecoder::DecodeFieldTime(x, ptr, endPtr)) return 0;
#define DECODE_FIELD_MAX(x) if (!EDecoder::DecodeFieldMax(x, ptr, endPtr)) return 0;
#endif