/* Copyright (C) 2019 Interactive Brokers LLC. All rights reserved. This code is subject to the terms
 * and conditions of the IB API Non-Commercial License or the IB API Commercial License, as applicable. */

#pragma once
#ifndef TWS_API_CLIENT_EWRAPPER_H
#define TWS_API_CLIENT_EWRAPPER_H

#include <string>
#include <set>
#include <map>
#include <tuple>
#include <vector>
#include "CommonDefs.h"
#include "SoftDollarTier.h"
#include "DepthMktDataDescription.h"
#include "FamilyCode.h"
#include "NewsProvider.h"
#include "TickAttrib.h"
#include "HistogramEntry.h"
#include "bar.h"
#include "PriceIncrement.h"
#include "HistoricalTick.h"
#include "HistoricalTickBidAsk.h"
#include "HistoricalTickLast.h"

enum TickType { BID_SIZE, BID, ASK, ASK_SIZE, LAST, LAST_SIZE,
				HIGH, LOW, VOLUME, CLOSE,
				BID_OPTION_COMPUTATION,
				ASK_OPTION_COMPUTATION,
				LAST_OPTION_COMPUTATION,
				MODEL_OPTION,
				OPEN,
				LOW_13_WEEK,
				HIGH_13_WEEK,
				LOW_26_WEEK,
				HIGH_26_WEEK,
				LOW_52_WEEK,
				HIGH_52_WEEK,
				AVG_VOLUME,
				OPEN_INTEREST,
				OPTION_HISTORICAL_VOL,
				OPTION_IMPLIED_VOL,
				OPTION_BID_EXCH,
				OPTION_ASK_EXCH,
				OPTION_CALL_OPEN_INTEREST,
				OPTION_PUT_OPEN_INTEREST,
				OPTION_CALL_VOLUME,
				OPTION_PUT_VOLUME,
				INDEX_FUTURE_PREMIUM,
				BID_EXCH,
				ASK_EXCH,
				AUCTION_VOLUME,
				AUCTION_PRICE,
				AUCTION_IMBALANCE,
				MARK_PRICE,
				BID_EFP_COMPUTATION,
				ASK_EFP_COMPUTATION,
				LAST_EFP_COMPUTATION,
				OPEN_EFP_COMPUTATION,
				HIGH_EFP_COMPUTATION,
				LOW_EFP_COMPUTATION,
				CLOSE_EFP_COMPUTATION,
				LAST_TIMESTAMP,
				SHORTABLE,
				FUNDAMENTAL_RATIOS,
				RT_VOLUME,
				HALTED,
				BID_YIELD,
				ASK_YIELD,
				LAST_YIELD,
				CUST_OPTION_COMPUTATION,
				TRADE_COUNT,
				TRADE_RATE,
				VOLUME_RATE,
				LAST_RTH_TRADE,
				RT_HISTORICAL_VOL,
				IB_DIVIDENDS,
				BOND_FACTOR_MULTIPLIER,
				REGULATORY_IMBALANCE,
				NEWS_TICK,
				SHORT_TERM_VOLUME_3_MIN,
				SHORT_TERM_VOLUME_5_MIN,
				SHORT_TERM_VOLUME_10_MIN,
				DELAYED_BID,
				DELAYED_ASK,
				DELAYED_LAST,
				DELAYED_BID_SIZE,
				DELAYED_ASK_SIZE,
				DELAYED_LAST_SIZE,
				DELAYED_HIGH,
				DELAYED_LOW,
				DELAYED_VOLUME,
				DELAYED_CLOSE,
				DELAYED_OPEN,
				RT_TRD_VOLUME,
				CREDITMAN_MARK_PRICE,
				CREDITMAN_SLOW_MARK_PRICE,
				DELAYED_BID_OPTION_COMPUTATION,
				DELAYED_ASK_OPTION_COMPUTATION,
				DELAYED_LAST_OPTION_COMPUTATION,
				DELAYED_MODEL_OPTION_COMPUTATION,
				LAST_EXCH,
				LAST_REG_TIME,
				FUTURES_OPEN_INTEREST,
				AVG_OPT_VOLUME,
				DELAYED_LAST_TIMESTAMP,
				SHORTABLE_SHARES,
				NOT_SET };

typedef std::map<int, std::tuple<std::string, char>> SmartComponentsMap;
typedef std::vector<HistogramEntry> HistogramDataVector;


inline bool isPrice( TickType tickType) {
	return tickType == BID || tickType == ASK || tickType == LAST || tickType == DELAYED_BID || tickType == DELAYED_ASK || tickType == DELAYED_LAST;
}

struct Contract;
struct ContractDetails;
struct ContractDescription;
struct Order;
struct OrderState;
struct Execution;
struct DeltaNeutralContract;
struct CommissionReport;

class EWrapper
{
public:
   virtual ~EWrapper() {};

	#define EWRAPPER_VIRTUAL_IMPL {}
	#include "EWrapper_prototypes.h"
};


#endif
