/* Copyright (C) 2019 Interactive Brokers LLC. All rights reserved. This code is subject to the terms
 * and conditions of the IB API Non-Commercial License or the IB API Commercial License, as applicable. */

#pragma once
#ifndef TWS_API_CLIENT_EORDERDECODER_H
#define TWS_API_CLIENT_EORDERDECODER_H

#include "platformspecific.h"
#include "Contract.h"
#include "Order.h"
#include "OrderState.h"
#include "EDecoder.h"

class EOrderDecoder
{
public:
	EOrderDecoder(Contract *contract, Order *order, OrderState *orderState, int version, int serverVersion);

public:
	char* decodeOrderId(const char*& ptr, const char* endPtr);
	char* decodeContract(const char*& ptr, const char* endPtr);
	char* decodeAction(const char*& ptr, const char* endPtr);
	char* decodeTotalQuantity(const char*& ptr, const char* endPtr);
	char* decodeOrderType(const char*& ptr, const char* endPtr);
	char* decodeLmtPrice(const char*& ptr, const char* endPtr);
	char* decodeAuxPrice(const char*& ptr, const char* endPtr);
	char* decodeTIF(const char*& ptr, const char* endPtr);
	char* decodeOcaGroup(const char*& ptr, const char* endPtr);
	char* decodeAccount(const char*& ptr, const char* endPtr);
	char* decodeOpenClose(const char*& ptr, const char* endPtr);
	char* decodeOrigin(const char*& ptr, const char* endPtr);
	char* decodeOrderRef(const char*& ptr, const char* endPtr);
	char* decodeClientId(const char*& ptr, const char* endPtr);
	char* decodePermId(const char*& ptr, const char* endPtr);
	char* decodeOutsideRth(const char*& ptr, const char* endPtr);
	char* decodeHidden(const char*& ptr, const char* endPtr);
	char* decodeDiscretionaryAmount(const char*& ptr, const char* endPtr);
	char* decodeGoodAfterTime(const char*& ptr, const char* endPtr);
	char* skipSharesAllocation(const char*& ptr, const char* endPtr);
	char* decodeFAParams(const char*& ptr, const char* endPtr);
	char* decodeModelCode(const char*& ptr, const char* endPtr);
	char* decodeGoodTillDate(const char*& ptr, const char* endPtr);
	char* decodeRule80A(const char*& ptr, const char* endPtr);
	char* decodePercentOffset(const char*& ptr, const char* endPtr);
	char* decodeSettlingFirm(const char*& ptr, const char* endPtr);
	char* decodeShortSaleParams(const char*& ptr, const char* endPtr);
	char* decodeAuctionStrategy(const char*& ptr, const char* endPtr);
	char* decodeBoxOrderParams(const char*& ptr, const char* endPtr);
	char* decodePegToStkOrVolOrderParams(const char*& ptr, const char* endPtr);
	char* decodeDisplaySize(const char*& ptr, const char* endPtr);
	char* decodeBlockOrder(const char*& ptr, const char* endPtr);
	char* decodeSweepToFill(const char*& ptr, const char* endPtr);
	char* decodeAllOrNone(const char*& ptr, const char* endPtr);
	char* decodeMinQty(const char*& ptr, const char* endPtr);
	char* decodeOcaType(const char*& ptr, const char* endPtr);
	char* decodeETradeOnly(const char*& ptr, const char* endPtr);
	char* decodeFirmQuoteOnly(const char*& ptr, const char* endPtr);
	char* decodeNbboPriceCap(const char*& ptr, const char* endPtr);
	char* decodeParentId(const char*& ptr, const char* endPtr);
	char* decodeTriggerMethod(const char*& ptr, const char* endPtr);
	char* decodeVolOrderParams(const char*& ptr, const char* endPtr, bool decodeOpenOrderAttribs);
	char* decodeTrailParams(const char*& ptr, const char* endPtr);
	char* decodeBasisPoints(const char*& ptr, const char* endPtr);
	char* decodeComboLegs(const char*& ptr, const char* endPtr);
	char* decodeSmartComboRoutingParams(const char*& ptr, const char* endPtr);
	char* decodeScaleOrderParams(const char*& ptr, const char* endPtr);
	char* decodeHedgeParams(const char*& ptr, const char* endPtr);
	char* decodeOptOutSmartRouting(const char*& ptr, const char* endPtr);
	char* decodeClearingParams(const char*& ptr, const char* endPtr);
	char* decodeNotHeld(const char*& ptr, const char* endPtr);
	char* decodeDeltaNeutral(const char*& ptr, const char* endPtr);
	char* decodeAlgoParams(const char*& ptr, const char* endPtr);
	char* decodeSolicited(const char*& ptr, const char* endPtr);
	char* decodeWhatIfInfoAndCommission(const char*& ptr, const char* endPtr);
	char* decodeOrderStatus(const char*& ptr, const char* endPtr);
	char* decodeVolRandomizeFlags(const char*& ptr, const char* endPtr);
	char* decodePegBenchParams(const char*& ptr, const char* endPtr);
	char* decodeConditions(const char*& ptr, const char* endPtr);
	char* decodeAdjustedOrderParams(const char*& ptr, const char* endPtr);
	char* decodeStopPriceAndLmtPriceOffset(const char*& ptr, const char* endPtr);
	char* decodeSoftDollarTier(const char*& ptr, const char* endPtr);
	char* decodeCashQty(const char*& ptr, const char* endPtr);
	char* decodeDontUseAutoPriceForHedge(const char*& ptr, const char* endPtr);
	char* decodeIsOmsContainer(const char*& ptr, const char* endPtr);
	char* decodeDiscretionaryUpToLimitPrice(const char*& ptr, const char* endPtr);
	char* decodeAutoCancelDate(const char*& ptr, const char* endPtr);
	char* decodeFilledQuantity(const char*& ptr, const char* endPtr);
	char* decodeRefFuturesConId(const char*& ptr, const char* endPtr);
	char* decodeAutoCancelParent(const char*& ptr, const char* endPtr);
	char* decodeShareholder(const char*& ptr, const char* endPtr);
	char* decodeImbalanceOnly(const char*& ptr, const char* endPtr);
	char* decodeRouteMarketableToBbo(const char*& ptr, const char* endPtr);
	char* decodeParentPermId(const char*& ptr, const char* endPtr);
	char* decodeCompletedTime(const char*& ptr, const char* endPtr);
	char* decodeCompletedStatus(const char*& ptr, const char* endPtr);
	char* decodeUsePriceMgmtAlgo(const char*& ptr, const char* endPtr);

private:
	Contract* m_contract;
	Order* m_order;
	OrderState* m_orderState;
	int m_version;
	int m_serverVersion;
};

#endif