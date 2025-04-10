/* Copyright (C) 2019 Interactive Brokers LLC. All rights reserved. This code is subject to the terms
 * and conditions of the IB API Non-Commercial License or the IB API Commercial License, as applicable. */

#include "StdAfx.h"
#include "EWrapper.h"
#include "Order.h"
#include "Contract.h"
#include "OrderState.h"
#include "Execution.h"
#include "FamilyCode.h"
#include "CommissionReport.h"
#include "TwsSocketClientErrors.h"
#include "EDecoder.h"
#include "EClientMsgSink.h"
#include "PriceIncrement.h"
#include "EOrderDecoder.h"

#include <string.h>
#include <cstdlib>
#include <sstream>
#include <assert.h>
#include <string>
#include <bitset>


EDecoder::EDecoder(int serverVersion, EWrapper *callback, EClientMsgSink *clientMsgSink) {
	m_pEWrapper = callback;
	m_serverVersion = serverVersion;
	m_pClientMsgSink = clientMsgSink;
}

const char* EDecoder::processTickPriceMsg(const char* ptr, const char* endPtr) {
	int version;
	int tickerId;
	int tickTypeInt;
	double price;

	int size;
	int attrMask;

	DECODE_FIELD( version);
	DECODE_FIELD( tickerId);
	DECODE_FIELD( tickTypeInt);
	DECODE_FIELD( price);
	DECODE_FIELD( size); // ver 2 field
	DECODE_FIELD( attrMask); // ver 3 field

	TickAttrib attrib = {};

	attrib.canAutoExecute = attrMask == 1;

	if (m_serverVersion >= MIN_SERVER_VER_PAST_LIMIT)
	{
		std::bitset<32> mask(attrMask);

		attrib.canAutoExecute = mask[0];
		attrib.pastLimit = mask[1];

		if (m_serverVersion >= MIN_SERVER_VER_PRE_OPEN_BID_ASK)
		{
			attrib.preOpen = mask[2];
		}
	}

	m_pEWrapper->tickPrice( tickerId, (TickType)tickTypeInt, price, attrib);

	// process ver 2 fields
	{
		TickType sizeTickType = NOT_SET;
		switch( (TickType)tickTypeInt) {
		case BID:
			sizeTickType = BID_SIZE;
			break;
		case ASK:
			sizeTickType = ASK_SIZE;
			break;
		case LAST:
			sizeTickType = LAST_SIZE;
			break;
		case DELAYED_BID:
			sizeTickType = DELAYED_BID_SIZE;
			break;
		case DELAYED_ASK:
			sizeTickType = DELAYED_ASK_SIZE;
			break;
		case DELAYED_LAST:
			sizeTickType = DELAYED_LAST_SIZE;
			break;
		default:
			break;
		}
		if( sizeTickType != NOT_SET)
			m_pEWrapper->tickSize( tickerId, sizeTickType, size);
	}

	return ptr;
}

const char* EDecoder::processTickSizeMsg(const char* ptr, const char* endPtr) {
	int version;
	int tickerId;
	int tickTypeInt;
	int size;

	DECODE_FIELD( version);
	DECODE_FIELD( tickerId);
	DECODE_FIELD( tickTypeInt);
	DECODE_FIELD( size);

	m_pEWrapper->tickSize( tickerId, (TickType)tickTypeInt, size);

	return ptr;
}

const char* EDecoder::processTickOptionComputationMsg(const char* ptr, const char* endPtr) {
	int version;
	int tickerId;
	int tickTypeInt;
	double impliedVol;
	double delta;

	double optPrice = DBL_MAX;
	double pvDividend = DBL_MAX;

	double gamma = DBL_MAX;
	double vega = DBL_MAX;
	double theta = DBL_MAX;
	double undPrice = DBL_MAX;

	DECODE_FIELD( version);
	DECODE_FIELD( tickerId);
	DECODE_FIELD( tickTypeInt);

	DECODE_FIELD( impliedVol);
	DECODE_FIELD( delta);

	if( impliedVol == -1) { // -1 is the "not computed" indicator
		impliedVol = DBL_MAX;
	}
	if( delta == -2) { // -2 is the "not computed" indicator
		delta = DBL_MAX;
	}

	if( version >= 6 || tickTypeInt == MODEL_OPTION || tickTypeInt == DELAYED_MODEL_OPTION_COMPUTATION) { // introduced in version == 5

		DECODE_FIELD( optPrice);
		DECODE_FIELD( pvDividend);

		if( optPrice == -1) { // -1 is the "not computed" indicator
			optPrice = DBL_MAX;
		}
		if( pvDividend == -1) { // -1 is the "not computed" indicator
			pvDividend = DBL_MAX;
		}
	}
	if( version >= 6) {

		DECODE_FIELD( gamma);
		DECODE_FIELD( vega);
		DECODE_FIELD( theta);
		DECODE_FIELD( undPrice);

		if( gamma == -2) { // -2 is the "not yet computed" indicator
			gamma = DBL_MAX;
		}
		if( vega == -2) { // -2 is the "not yet computed" indicator
			vega = DBL_MAX;
		}
		if( theta == -2) { // -2 is the "not yet computed" indicator
			theta = DBL_MAX;
		}
		if( undPrice == -1) { // -1 is the "not computed" indicator
			undPrice = DBL_MAX;
		}
	}
	m_pEWrapper->tickOptionComputation( tickerId, (TickType)tickTypeInt,
		impliedVol, delta, optPrice, pvDividend, gamma, vega, theta, undPrice);

	return ptr;
}

const char* EDecoder::processTickGenericMsg(const char* ptr, const char* endPtr) {
	int version;
	int tickerId;
	int tickTypeInt;
	double value;

	DECODE_FIELD( version);
	DECODE_FIELD( tickerId);
	DECODE_FIELD( tickTypeInt);
	DECODE_FIELD( value);

	m_pEWrapper->tickGeneric( tickerId, (TickType)tickTypeInt, value);

	return ptr;
}

const char* EDecoder::processTickStringMsg(const char* ptr, const char* endPtr) {
	int version;
	int tickerId;
	int tickTypeInt;
	std::string value;

	DECODE_FIELD( version);
	DECODE_FIELD( tickerId);
	DECODE_FIELD( tickTypeInt);
	DECODE_FIELD( value);

	m_pEWrapper->tickString( tickerId, (TickType)tickTypeInt, value);

	return ptr;
}

const char* EDecoder::processTickEfpMsg(const char* ptr, const char* endPtr) {
	int version;
	int tickerId;
	int tickTypeInt;
	double basisPoints;
	std::string formattedBasisPoints;
	double impliedFuturesPrice;
	int holdDays;
	std::string futureLastTradeDate;
	double dividendImpact;
	double dividendsToLastTradeDate;

	DECODE_FIELD( version);
	DECODE_FIELD( tickerId);
	DECODE_FIELD( tickTypeInt);
	DECODE_FIELD( basisPoints);
	DECODE_FIELD( formattedBasisPoints);
	DECODE_FIELD( impliedFuturesPrice);
	DECODE_FIELD( holdDays);
	DECODE_FIELD( futureLastTradeDate);
	DECODE_FIELD( dividendImpact);
	DECODE_FIELD( dividendsToLastTradeDate);

	m_pEWrapper->tickEFP( tickerId, (TickType)tickTypeInt, basisPoints, formattedBasisPoints,
		impliedFuturesPrice, holdDays, futureLastTradeDate, dividendImpact, dividendsToLastTradeDate);

	return ptr;
}

const char* EDecoder::processOrderStatusMsg(const char* ptr, const char* endPtr) {
    int version = INT_MAX;
	int orderId;
	std::string status;
	double filled;
	double remaining;
	double avgFillPrice;
	int permId;
	int parentId;
	double lastFillPrice;
	int clientId;
	std::string whyHeld;

    if (m_serverVersion < MIN_SERVER_VER_MARKET_CAP_PRICE) 
    {
	    DECODE_FIELD( version);
    }
	
    DECODE_FIELD( orderId);
	DECODE_FIELD( status);

	if (m_serverVersion >= MIN_SERVER_VER_FRACTIONAL_POSITIONS)
	{
		DECODE_FIELD( filled);
	}
	else
	{
		int iFilled;

		DECODE_FIELD(iFilled);

		filled = iFilled;
	}

	if (m_serverVersion >= MIN_SERVER_VER_FRACTIONAL_POSITIONS)
	{
		DECODE_FIELD( remaining);
	}
	else
	{
		int iRemaining;

		DECODE_FIELD(iRemaining);

		remaining = iRemaining;
	}

	DECODE_FIELD( avgFillPrice);

	DECODE_FIELD( permId); // ver 2 field
	DECODE_FIELD( parentId); // ver 3 field
	DECODE_FIELD( lastFillPrice); // ver 4 field
	DECODE_FIELD( clientId); // ver 5 field
	DECODE_FIELD( whyHeld); // ver 6 field

	double mktCapPrice = UNSET_DOUBLE;

	if (m_serverVersion >= MIN_SERVER_VER_MARKET_CAP_PRICE)
	{
		DECODE_FIELD(mktCapPrice);
	}

	m_pEWrapper->orderStatus( orderId, status, filled, remaining,
		avgFillPrice, permId, parentId, lastFillPrice, clientId, whyHeld, mktCapPrice);


	return ptr;
}

const char* EDecoder::processErrMsgMsg(const char* ptr, const char* endPtr) {
	int version;
	int id; // ver 2 field
	int errorCode; // ver 2 field
	std::string errorMsg;

	DECODE_FIELD( version);
	DECODE_FIELD( id);
	DECODE_FIELD( errorCode);
	DECODE_FIELD( errorMsg);

	m_pEWrapper->error( id, errorCode, errorMsg);

	return ptr;
}

const char* EDecoder::processOpenOrderMsg(const char* ptr, const char* endPtr) {
	// read version
	int version = m_serverVersion;

    if (m_serverVersion < MIN_SERVER_VER_ORDER_CONTAINER) {
	    DECODE_FIELD(version);
    }

	Order order;
	Contract contract;
	OrderState orderState;
	EOrderDecoder eOrderDecoder(&contract, &order, &orderState, version, m_serverVersion);

	// read order id
	eOrderDecoder.decodeOrderId(ptr, endPtr);

	// read contract fields
	eOrderDecoder.decodeContract(ptr, endPtr);

	// read order fields
	eOrderDecoder.decodeAction(ptr, endPtr);
	eOrderDecoder.decodeTotalQuantity(ptr, endPtr);
	eOrderDecoder.decodeOrderType(ptr, endPtr);
	eOrderDecoder.decodeLmtPrice(ptr, endPtr);
	eOrderDecoder.decodeAuxPrice(ptr, endPtr);
	eOrderDecoder.decodeTIF(ptr, endPtr);
	eOrderDecoder.decodeOcaGroup(ptr, endPtr);
	eOrderDecoder.decodeAccount(ptr, endPtr);
	eOrderDecoder.decodeOpenClose(ptr, endPtr);
	eOrderDecoder.decodeOrigin(ptr, endPtr);
	eOrderDecoder.decodeOrderRef(ptr, endPtr);
	eOrderDecoder.decodeClientId(ptr, endPtr);
	eOrderDecoder.decodePermId(ptr, endPtr);
	eOrderDecoder.decodeOutsideRth(ptr, endPtr);
	eOrderDecoder.decodeHidden(ptr, endPtr);
	eOrderDecoder.decodeDiscretionaryAmount(ptr, endPtr);
	eOrderDecoder.decodeGoodAfterTime(ptr, endPtr);
	eOrderDecoder.skipSharesAllocation(ptr, endPtr);
	eOrderDecoder.decodeFAParams(ptr, endPtr);
	eOrderDecoder.decodeModelCode(ptr, endPtr);
	eOrderDecoder.decodeGoodTillDate(ptr, endPtr);
	eOrderDecoder.decodeRule80A(ptr, endPtr);
	eOrderDecoder.decodePercentOffset(ptr, endPtr);
	eOrderDecoder.decodeSettlingFirm(ptr, endPtr);
	eOrderDecoder.decodeShortSaleParams(ptr, endPtr);
	eOrderDecoder.decodeAuctionStrategy(ptr, endPtr);
	eOrderDecoder.decodeBoxOrderParams(ptr, endPtr);
	eOrderDecoder.decodePegToStkOrVolOrderParams(ptr, endPtr);
	eOrderDecoder.decodeDisplaySize(ptr, endPtr);
	eOrderDecoder.decodeBlockOrder(ptr, endPtr);
	eOrderDecoder.decodeSweepToFill(ptr, endPtr);
	eOrderDecoder.decodeAllOrNone(ptr, endPtr);
	eOrderDecoder.decodeMinQty(ptr, endPtr);
	eOrderDecoder.decodeOcaType(ptr, endPtr);
	eOrderDecoder.decodeETradeOnly(ptr, endPtr);
	eOrderDecoder.decodeFirmQuoteOnly(ptr, endPtr);
	eOrderDecoder.decodeNbboPriceCap(ptr, endPtr);
	eOrderDecoder.decodeParentId(ptr, endPtr);
	eOrderDecoder.decodeTriggerMethod(ptr, endPtr);
	eOrderDecoder.decodeVolOrderParams(ptr, endPtr, true);
	eOrderDecoder.decodeTrailParams(ptr, endPtr);
	eOrderDecoder.decodeBasisPoints(ptr, endPtr);
	eOrderDecoder.decodeComboLegs(ptr, endPtr);
	eOrderDecoder.decodeSmartComboRoutingParams(ptr, endPtr);
	eOrderDecoder.decodeScaleOrderParams(ptr, endPtr);
	eOrderDecoder.decodeHedgeParams(ptr, endPtr);
	eOrderDecoder.decodeOptOutSmartRouting(ptr, endPtr);
	eOrderDecoder.decodeClearingParams(ptr, endPtr);
	eOrderDecoder.decodeNotHeld(ptr, endPtr);
	eOrderDecoder.decodeDeltaNeutral(ptr, endPtr);
	eOrderDecoder.decodeAlgoParams(ptr, endPtr);
	eOrderDecoder.decodeSolicited(ptr, endPtr);
	eOrderDecoder.decodeWhatIfInfoAndCommission(ptr, endPtr);
	eOrderDecoder.decodeVolRandomizeFlags(ptr, endPtr);
	eOrderDecoder.decodePegBenchParams(ptr, endPtr);
	eOrderDecoder.decodeConditions(ptr, endPtr);
	eOrderDecoder.decodeAdjustedOrderParams(ptr, endPtr);
	eOrderDecoder.decodeSoftDollarTier(ptr, endPtr);
	eOrderDecoder.decodeCashQty(ptr, endPtr);
	eOrderDecoder.decodeDontUseAutoPriceForHedge(ptr, endPtr);
	eOrderDecoder.decodeIsOmsContainer(ptr, endPtr);
	eOrderDecoder.decodeDiscretionaryUpToLimitPrice(ptr, endPtr);
	eOrderDecoder.decodeUsePriceMgmtAlgo(ptr, endPtr);

	m_pEWrapper->openOrder((OrderId)order.orderId, contract, order, orderState);

	return ptr;
} 

const char* EDecoder::processAcctValueMsg(const char* ptr, const char* endPtr) {
	int version;
	std::string key;
	std::string val;
	std::string cur;
	std::string accountName;

	DECODE_FIELD( version);
	DECODE_FIELD( key);
	DECODE_FIELD( val);
	DECODE_FIELD( cur);
	DECODE_FIELD( accountName); // ver 2 field

	m_pEWrapper->updateAccountValue( key, val, cur, accountName);
	return ptr;
}

const char* EDecoder::processPortfolioValueMsg(const char* ptr, const char* endPtr) {
	// decode version
	int version;
	DECODE_FIELD( version);

	// read contract fields
	Contract contract;
	DECODE_FIELD( contract.conId); // ver 6 field
	DECODE_FIELD( contract.symbol);
	DECODE_FIELD( contract.secType);
	DECODE_FIELD( contract.lastTradeDateOrContractMonth);
	DECODE_FIELD( contract.strike);
	DECODE_FIELD( contract.right);

	if( version >= 7) {
		DECODE_FIELD( contract.multiplier);
		DECODE_FIELD( contract.primaryExchange);
	}

	DECODE_FIELD( contract.currency);
	DECODE_FIELD( contract.localSymbol); // ver 2 field
	if (version >= 8) {
		DECODE_FIELD( contract.tradingClass);
	}

	double  position;
	double  marketPrice;
	double  marketValue;
	double  averageCost;
	double  unrealizedPNL;
	double  realizedPNL;

	if (m_serverVersion >= MIN_SERVER_VER_FRACTIONAL_POSITIONS)
	{
		DECODE_FIELD( position);
	}
	else
	{
		int iPosition;

		DECODE_FIELD(iPosition);

		position = iPosition;
	}

	DECODE_FIELD( marketPrice);
	DECODE_FIELD( marketValue);
	DECODE_FIELD( averageCost); // ver 3 field
	DECODE_FIELD( unrealizedPNL); // ver 3 field
	DECODE_FIELD( realizedPNL); // ver 3 field

	std::string accountName;
	DECODE_FIELD( accountName); // ver 4 field

	if( version == 6 && m_serverVersion == 39) {
		DECODE_FIELD( contract.primaryExchange);
	}

	m_pEWrapper->updatePortfolio( contract,
		position, marketPrice, marketValue, averageCost,
		unrealizedPNL, realizedPNL, accountName);

	return ptr;
}

const char* EDecoder::processAcctUpdateTimeMsg(const char* ptr, const char* endPtr) {
	int version;
	std::string accountTime;

	DECODE_FIELD( version);
	DECODE_FIELD( accountTime);

	m_pEWrapper->updateAccountTime( accountTime);

	return ptr;
}

const char* EDecoder::processNextValidIdMsg(const char* ptr, const char* endPtr) {
	int version;
	int orderId;

	DECODE_FIELD( version);
	DECODE_FIELD( orderId);

	m_pEWrapper->nextValidId(orderId);

	return ptr;
}

const char* EDecoder::processContractDataMsg(const char* ptr, const char* endPtr) {
	int version;
	DECODE_FIELD( version);

	int reqId = -1;
	if( version >= 3) {
		DECODE_FIELD( reqId);
	}

	ContractDetails contract;
	DECODE_FIELD( contract.contract.symbol);
	DECODE_FIELD( contract.contract.secType);
	ptr = decodeLastTradeDate(ptr, endPtr, contract, false);
	DECODE_FIELD( contract.contract.strike);
	DECODE_FIELD( contract.contract.right);
	DECODE_FIELD( contract.contract.exchange);
	DECODE_FIELD( contract.contract.currency);
	DECODE_FIELD( contract.contract.localSymbol);
	DECODE_FIELD( contract.marketName);
	DECODE_FIELD( contract.contract.tradingClass);
	DECODE_FIELD( contract.contract.conId);
	DECODE_FIELD( contract.minTick);
	if (m_serverVersion >= MIN_SERVER_VER_MD_SIZE_MULTIPLIER) {
		DECODE_FIELD( contract.mdSizeMultiplier);
	}
	DECODE_FIELD( contract.contract.multiplier);
	DECODE_FIELD( contract.orderTypes);
	DECODE_FIELD( contract.validExchanges);
	DECODE_FIELD( contract.priceMagnifier); // ver 2 field
	if( version >= 4) {
		DECODE_FIELD( contract.underConId);
	}
	if( version >= 5) {
		DECODE_FIELD( contract.longName);
		DECODE_FIELD( contract.contract.primaryExchange);
	}
	if( version >= 6) {
		DECODE_FIELD( contract.contractMonth);
		DECODE_FIELD( contract.industry);
		DECODE_FIELD( contract.category);
		DECODE_FIELD( contract.subcategory);
		DECODE_FIELD( contract.timeZoneId);
		DECODE_FIELD( contract.tradingHours);
		DECODE_FIELD( contract.liquidHours);
	}
	if( version >= 8) {
		DECODE_FIELD( contract.evRule);
		DECODE_FIELD( contract.evMultiplier);
	}
	if( version >= 7) {
		int secIdListCount = 0;
		DECODE_FIELD( secIdListCount);
		if( secIdListCount > 0) {
			TagValueListSPtr secIdList( new TagValueList);
			secIdList->reserve( secIdListCount);
			for( int i = 0; i < secIdListCount; ++i) {
				TagValueSPtr tagValue( new TagValue());
				DECODE_FIELD( tagValue->tag);
				DECODE_FIELD( tagValue->value);
				secIdList->push_back( tagValue);
			}
			contract.secIdList = secIdList;
		}
	}
	if (m_serverVersion >= MIN_SERVER_VER_AGG_GROUP) {
		DECODE_FIELD( contract.aggGroup);
	}
	if (m_serverVersion >= MIN_SERVER_VER_UNDERLYING_INFO) {
		DECODE_FIELD( contract.underSymbol);
		DECODE_FIELD( contract.underSecType);
	}
	if (m_serverVersion >= MIN_SERVER_VER_MARKET_RULES) {
		DECODE_FIELD( contract.marketRuleIds);
	}
	if (m_serverVersion >= MIN_SERVER_VER_REAL_EXPIRATION_DATE) {
		DECODE_FIELD( contract.realExpirationDate);
	}

	m_pEWrapper->contractDetails( reqId, contract);

	return ptr;
}

const char* EDecoder::processBondContractDataMsg(const char* ptr, const char* endPtr) {
	int version;
	DECODE_FIELD( version);

	int reqId = -1;
	if( version >= 3) {
		DECODE_FIELD( reqId);
	}

	ContractDetails contract;
	DECODE_FIELD( contract.contract.symbol);
	DECODE_FIELD( contract.contract.secType);
	DECODE_FIELD( contract.cusip);
	DECODE_FIELD( contract.coupon);
	ptr = decodeLastTradeDate(ptr, endPtr, contract, true);
	DECODE_FIELD( contract.issueDate);
	DECODE_FIELD( contract.ratings);
	DECODE_FIELD( contract.bondType);
	DECODE_FIELD( contract.couponType);
	DECODE_FIELD( contract.convertible);
	DECODE_FIELD( contract.callable);
	DECODE_FIELD( contract.putable);
	DECODE_FIELD( contract.descAppend);
	DECODE_FIELD( contract.contract.exchange);
	DECODE_FIELD( contract.contract.currency);
	DECODE_FIELD( contract.marketName);
	DECODE_FIELD( contract.contract.tradingClass);
	DECODE_FIELD( contract.contract.conId);
	DECODE_FIELD( contract.minTick);
	if (m_serverVersion >= MIN_SERVER_VER_MD_SIZE_MULTIPLIER) {
		DECODE_FIELD( contract.mdSizeMultiplier);
	}
	DECODE_FIELD( contract.orderTypes);
	DECODE_FIELD( contract.validExchanges);
	DECODE_FIELD( contract.nextOptionDate); // ver 2 field
	DECODE_FIELD( contract.nextOptionType); // ver 2 field
	DECODE_FIELD( contract.nextOptionPartial); // ver 2 field
	DECODE_FIELD( contract.notes); // ver 2 field
	if( version >= 4) {
		DECODE_FIELD( contract.longName);
	}
	if( version >= 6) {
		DECODE_FIELD( contract.evRule);
		DECODE_FIELD( contract.evMultiplier);
	}
	if( version >= 5) {
		int secIdListCount = 0;
		DECODE_FIELD( secIdListCount);
		if( secIdListCount > 0) {
			TagValueListSPtr secIdList( new TagValueList);
			secIdList->reserve( secIdListCount);
			for( int i = 0; i < secIdListCount; ++i) {
				TagValueSPtr tagValue( new TagValue());
				DECODE_FIELD( tagValue->tag);
				DECODE_FIELD( tagValue->value);
				secIdList->push_back( tagValue);
			}
			contract.secIdList = secIdList;
		}
	}
	if (m_serverVersion >= MIN_SERVER_VER_AGG_GROUP) {
		DECODE_FIELD( contract.aggGroup);
	}
	if (m_serverVersion >= MIN_SERVER_VER_MARKET_RULES) {
		DECODE_FIELD( contract.marketRuleIds);
	}

	m_pEWrapper->bondContractDetails( reqId, contract);

	return ptr;
}

const char* EDecoder::processExecutionDetailsMsg(const char* ptr, const char* endPtr) {
    int version = m_serverVersion;

    if (m_serverVersion < MIN_SERVER_VER_LAST_LIQUIDITY) {
	    DECODE_FIELD(version);
    }

	int reqId = -1;
	if( version >= 7) {
		DECODE_FIELD(reqId);
	}

	int orderId;
	DECODE_FIELD( orderId);

	// decode contract fields
	Contract contract;
	DECODE_FIELD( contract.conId); // ver 5 field
	DECODE_FIELD( contract.symbol);
	DECODE_FIELD( contract.secType);
	DECODE_FIELD( contract.lastTradeDateOrContractMonth);
	DECODE_FIELD( contract.strike);
	DECODE_FIELD( contract.right);
	if( version >= 9) {
		DECODE_FIELD( contract.multiplier);
	}
	DECODE_FIELD( contract.exchange);
	DECODE_FIELD( contract.currency);
	DECODE_FIELD( contract.localSymbol);
	if (version >= 10) {
		DECODE_FIELD( contract.tradingClass);
	}

	// decode execution fields
	Execution exec;
	exec.orderId = orderId;
	DECODE_FIELD( exec.execId);
	DECODE_FIELD( exec.time);
	DECODE_FIELD( exec.acctNumber);
	DECODE_FIELD( exec.exchange);
	DECODE_FIELD( exec.side);

	if (m_serverVersion >= MIN_SERVER_VER_FRACTIONAL_POSITIONS) {
		DECODE_FIELD( exec.shares)
	} 
	else {
		int iShares;

		DECODE_FIELD(iShares);

		exec.shares = iShares;
	}

	DECODE_FIELD( exec.price);
	DECODE_FIELD( exec.permId); // ver 2 field
	DECODE_FIELD( exec.clientId); // ver 3 field
	DECODE_FIELD( exec.liquidation); // ver 4 field

	if( version >= 6) {
		DECODE_FIELD( exec.cumQty);
		DECODE_FIELD( exec.avgPrice);
	}

	if( version >= 8) {
		DECODE_FIELD( exec.orderRef);
	}

	if( version >= 9) {
		DECODE_FIELD( exec.evRule);
		DECODE_FIELD( exec.evMultiplier);
	}
	if( m_serverVersion >= MIN_SERVER_VER_MODELS_SUPPORT) {
		DECODE_FIELD( exec.modelCode);
	}

    if (m_serverVersion >= MIN_SERVER_VER_LAST_LIQUIDITY) {
        DECODE_FIELD(exec.lastLiquidity);
    }

	m_pEWrapper->execDetails( reqId, contract, exec);

	return ptr;
}

const char* EDecoder::processMarketDepthMsg(const char* ptr, const char* endPtr) {
	int version;
	int id;
	int position;
	int operation;
	int side;
	double price;
	int size;

	DECODE_FIELD( version);
	DECODE_FIELD( id);
	DECODE_FIELD( position);
	DECODE_FIELD( operation);
	DECODE_FIELD( side);
	DECODE_FIELD( price);
	DECODE_FIELD( size);

	m_pEWrapper->updateMktDepth( id, position, operation, side, price, size);

	return ptr;
}

const char* EDecoder::processMarketDepthL2Msg(const char* ptr, const char* endPtr) {
	int version;
	int id;
	int position;
	std::string marketMaker;
	int operation;
	int side;
	double price;
	int size;
	bool isSmartDepth = false;

	DECODE_FIELD( version);
	DECODE_FIELD( id);
	DECODE_FIELD( position);
	DECODE_FIELD( marketMaker);
	DECODE_FIELD( operation);
	DECODE_FIELD( side);
	DECODE_FIELD( price);
	DECODE_FIELD( size);

	if( m_serverVersion >= MIN_SERVER_VER_SMART_DEPTH) {
		DECODE_FIELD( isSmartDepth);
	}

	m_pEWrapper->updateMktDepthL2( id, position, marketMaker, operation, side,
		price, size, isSmartDepth);

	return ptr;
}

const char* EDecoder::processNewsBulletinsMsg(const char* ptr, const char* endPtr) {
	int version;
	int msgId;
	int msgType;
	std::string newsMessage;
	std::string originatingExch;

	DECODE_FIELD( version);
	DECODE_FIELD( msgId);
	DECODE_FIELD( msgType);
	DECODE_FIELD( newsMessage);
	DECODE_FIELD( originatingExch);

	m_pEWrapper->updateNewsBulletin( msgId, msgType, newsMessage, originatingExch);

	return ptr;
}

const char* EDecoder::processManagedAcctsMsg(const char* ptr, const char* endPtr) {
	int version;
	std::string accountsList;

	DECODE_FIELD( version);
	DECODE_FIELD( accountsList);

	m_pEWrapper->managedAccounts( accountsList);

	return ptr;
}

const char* EDecoder::processReceiveFaMsg(const char* ptr, const char* endPtr) {
	int version;
	int faDataTypeInt;
	std::string cxml;

	DECODE_FIELD( version);
	DECODE_FIELD( faDataTypeInt);
	DECODE_FIELD( cxml);

	m_pEWrapper->receiveFA( (faDataType)faDataTypeInt, cxml);

	return ptr;
}

const char* EDecoder::processHistoricalDataMsg(const char* ptr, const char* endPtr) {
    int version = INT_MAX;
	int reqId;
	std::string startDateStr;
	std::string endDateStr;

    if (m_serverVersion < MIN_SERVER_VER_SYNT_REALTIME_BARS) {
	    DECODE_FIELD(version);
    }

	DECODE_FIELD( reqId);
	DECODE_FIELD( startDateStr); // ver 2 field
	DECODE_FIELD( endDateStr); // ver 2 field

	int itemCount;
	DECODE_FIELD( itemCount);

	typedef std::vector<Bar> BarDataList;
	BarDataList bars;

	bars.reserve( itemCount);

	for( int ctr = 0; ctr < itemCount; ++ctr) {
		Bar bar;

		DECODE_FIELD( bar.time);
		DECODE_FIELD( bar.open);
		DECODE_FIELD( bar.high);
		DECODE_FIELD( bar.low);
		DECODE_FIELD( bar.close);

        int vol;

        if (m_serverVersion < MIN_SERVER_VER_SYNT_REALTIME_BARS) {
		    DECODE_FIELD( vol);

            bar.volume = vol;
        } else {
            DECODE_FIELD( bar.volume);
        }

		DECODE_FIELD( bar.wap);

        if (m_serverVersion < MIN_SERVER_VER_SYNT_REALTIME_BARS) {
	        std::string hasGaps;

		    DECODE_FIELD( hasGaps);
        }

		DECODE_FIELD( bar.count); // ver 3 field

		bars.push_back(bar);
	}

	assert( (int)bars.size() == itemCount);

	for( int ctr = 0; ctr < itemCount; ++ctr) {

		const Bar& bar = bars[ctr];

		m_pEWrapper->historicalData( reqId, bar);
	}

	// send end of dataset marker
	m_pEWrapper->historicalDataEnd( reqId, startDateStr, endDateStr);

	return ptr;
}

const char* EDecoder::processHistoricalDataUpdateMsg(const char* ptr, const char* endPtr) {
	int reqId;
	std::string startDateStr;
	std::string endDateStr;

	DECODE_FIELD( reqId);

	Bar bar;

	DECODE_FIELD(bar.count);
	DECODE_FIELD(bar.time);
	DECODE_FIELD(bar.open);
	DECODE_FIELD(bar.close);
	DECODE_FIELD(bar.high);
	DECODE_FIELD(bar.low);
	DECODE_FIELD(bar.wap);
	DECODE_FIELD(bar.volume);

	m_pEWrapper->historicalDataUpdate( reqId, bar);

	return ptr;
}

const char* EDecoder::processScannerDataMsg(const char* ptr, const char* endPtr) {
	int version;
	int tickerId;

	DECODE_FIELD( version);
	DECODE_FIELD( tickerId);

	int numberOfElements;
	DECODE_FIELD( numberOfElements);

	typedef std::vector<ScanData> ScanDataList;
	ScanDataList scannerDataList;

	scannerDataList.reserve( numberOfElements);

	for( int ctr=0; ctr < numberOfElements; ++ctr) {

		ScanData data;

		DECODE_FIELD( data.rank);
		DECODE_FIELD( data.contract.contract.conId); // ver 3 field
		DECODE_FIELD( data.contract.contract.symbol);
		DECODE_FIELD( data.contract.contract.secType);
		DECODE_FIELD( data.contract.contract.lastTradeDateOrContractMonth);
		DECODE_FIELD( data.contract.contract.strike);
		DECODE_FIELD( data.contract.contract.right);
		DECODE_FIELD( data.contract.contract.exchange);
		DECODE_FIELD( data.contract.contract.currency);
		DECODE_FIELD( data.contract.contract.localSymbol);
		DECODE_FIELD( data.contract.marketName);
		DECODE_FIELD( data.contract.contract.tradingClass);
		DECODE_FIELD( data.distance);
		DECODE_FIELD( data.benchmark);
		DECODE_FIELD( data.projection);
		DECODE_FIELD( data.legsStr);

		scannerDataList.push_back( data);
	}

	assert( (int)scannerDataList.size() == numberOfElements);

	for( int ctr=0; ctr < numberOfElements; ++ctr) {

		const ScanData& data = scannerDataList[ctr];
		m_pEWrapper->scannerData( tickerId, data.rank, data.contract,
			data.distance, data.benchmark, data.projection, data.legsStr);
	}

	m_pEWrapper->scannerDataEnd( tickerId);

	return ptr;
}

const char* EDecoder::processScannerParametersMsg(const char* ptr, const char* endPtr) {
	int version;
	std::string xml;

	DECODE_FIELD( version);
	DECODE_FIELD( xml);

	m_pEWrapper->scannerParameters( xml);

	return ptr;
}

const char* EDecoder::processCurrentTimeMsg(const char* ptr, const char* endPtr) {
	int version;
	int time;

	DECODE_FIELD(version);
	DECODE_FIELD(time);

	m_pEWrapper->currentTime( time);

	return ptr;
}

const char* EDecoder::processRealTimeBarsMsg(const char* ptr, const char* endPtr) {
	int version;
	int reqId;
	int time;
	double open;
	double high;
	double low;
	double close;
	int volume;
	double average;
	int count;

	DECODE_FIELD( version);
	DECODE_FIELD( reqId);
	DECODE_FIELD( time);
	DECODE_FIELD( open);
	DECODE_FIELD( high);
	DECODE_FIELD( low);
	DECODE_FIELD( close);
	DECODE_FIELD( volume);
	DECODE_FIELD( average);
	DECODE_FIELD( count);

	m_pEWrapper->realtimeBar( reqId, time, open, high, low, close,
		volume, average, count);

	return ptr;
}

const char* EDecoder::processFundamentalDataMsg(const char* ptr, const char* endPtr) {
	int version;
	int reqId;
	std::string data;

	DECODE_FIELD( version);
	DECODE_FIELD( reqId);
	DECODE_FIELD( data);

	m_pEWrapper->fundamentalData( reqId, data);

	return ptr;
}

const char* EDecoder::processContractDataEndMsg(const char* ptr, const char* endPtr) {
	int version;
	int reqId;

	DECODE_FIELD( version);
	DECODE_FIELD( reqId);

	m_pEWrapper->contractDetailsEnd( reqId);

	return ptr;
}

const char* EDecoder::processOpenOrderEndMsg(const char* ptr, const char* endPtr) {
	int version;

	DECODE_FIELD( version);

	m_pEWrapper->openOrderEnd();

	return ptr;
}

const char* EDecoder::processAcctDownloadEndMsg(const char* ptr, const char* endPtr) {
	int version;
	std::string account;

	DECODE_FIELD( version);
	DECODE_FIELD( account);

	m_pEWrapper->accountDownloadEnd( account);

	return ptr;
}

const char* EDecoder::processExecutionDetailsEndMsg(const char* ptr, const char* endPtr) {
	int version;
	int reqId;

	DECODE_FIELD( version);
	DECODE_FIELD( reqId);

	m_pEWrapper->execDetailsEnd( reqId);

	return ptr;
}

const char* EDecoder::processDeltaNeutralValidationMsg(const char* ptr, const char* endPtr) {
	int version;
	int reqId;

	DECODE_FIELD( version);
	DECODE_FIELD( reqId);

	DeltaNeutralContract deltaNeutralContract;

	DECODE_FIELD( deltaNeutralContract.conId);
	DECODE_FIELD( deltaNeutralContract.delta);
	DECODE_FIELD( deltaNeutralContract.price);

	m_pEWrapper->deltaNeutralValidation( reqId, deltaNeutralContract);

	return ptr;
}

const char* EDecoder::processTickSnapshotEndMsg(const char* ptr, const char* endPtr) {
	int version;
	int reqId;

	DECODE_FIELD( version);
	DECODE_FIELD( reqId);

	m_pEWrapper->tickSnapshotEnd( reqId);

	return ptr;
}

const char* EDecoder::processMarketDataTypeMsg(const char* ptr, const char* endPtr) {
	int version;
	int reqId;
	int marketDataType;

	DECODE_FIELD( version);
	DECODE_FIELD( reqId);
	DECODE_FIELD( marketDataType);

	m_pEWrapper->marketDataType( reqId, marketDataType);

	return ptr;
}

const char* EDecoder::processCommissionReportMsg(const char* ptr, const char* endPtr) {
	int version;
	DECODE_FIELD( version);

	CommissionReport commissionReport;
	DECODE_FIELD( commissionReport.execId);
	DECODE_FIELD( commissionReport.commission);
	DECODE_FIELD( commissionReport.currency);
	DECODE_FIELD( commissionReport.realizedPNL);
	DECODE_FIELD( commissionReport.yield);
	DECODE_FIELD( commissionReport.yieldRedemptionDate);

	m_pEWrapper->commissionReport( commissionReport);

	return ptr;
}

const char* EDecoder::processPositionDataMsg(const char* ptr, const char* endPtr) {
	int version;
	std::string account;
	double position;
	double avgCost = 0;

	DECODE_FIELD( version);
	DECODE_FIELD( account);

	// decode contract fields
	Contract contract;
	DECODE_FIELD( contract.conId);
	DECODE_FIELD( contract.symbol);
	DECODE_FIELD( contract.secType);
	DECODE_FIELD( contract.lastTradeDateOrContractMonth);
	DECODE_FIELD( contract.strike);
	DECODE_FIELD( contract.right);
	DECODE_FIELD( contract.multiplier);
	DECODE_FIELD( contract.exchange);
	DECODE_FIELD( contract.currency);
	DECODE_FIELD( contract.localSymbol);
	if (version >= 2) {
		DECODE_FIELD( contract.tradingClass);
	}

	if (m_serverVersion >= MIN_SERVER_VER_FRACTIONAL_POSITIONS)
	{
		DECODE_FIELD( position);
	}
	else
	{
		int iPosition;

		DECODE_FIELD(iPosition);

		position = iPosition;
	}

	if (version >= 3) {
		DECODE_FIELD( avgCost);
	}

	m_pEWrapper->position( account, contract, position, avgCost);

	return ptr;
}

const char* EDecoder::processPositionEndMsg(const char* ptr, const char* endPtr) {
	int version;

	DECODE_FIELD( version);

	m_pEWrapper->positionEnd();

	return ptr;
}

const char* EDecoder::processAccountSummaryMsg(const char* ptr, const char* endPtr) {
	int version;
	int reqId;
	std::string account;
	std::string tag;
	std::string value;
	std::string curency;

	DECODE_FIELD( version);
	DECODE_FIELD( reqId);
	DECODE_FIELD( account);
	DECODE_FIELD( tag);
	DECODE_FIELD( value);
	DECODE_FIELD( curency);

	m_pEWrapper->accountSummary( reqId, account, tag, value, curency);

	return ptr;
}

const char* EDecoder::processAccountSummaryEndMsg(const char* ptr, const char* endPtr) {
	int version;
	int reqId;

	DECODE_FIELD( version);
	DECODE_FIELD( reqId);

	m_pEWrapper->accountSummaryEnd( reqId);

	return ptr;
}

const char* EDecoder::processVerifyMessageApiMsg(const char* ptr, const char* endPtr) {
	int version;
	std::string apiData;

	DECODE_FIELD( version);
	DECODE_FIELD( apiData);

	m_pEWrapper->verifyMessageAPI( apiData);

	return ptr;
}

const char* EDecoder::processVerifyCompletedMsg(const char* ptr, const char* endPtr) {
	int version;
	std::string isSuccessful;
	std::string errorText;

	DECODE_FIELD( version);
	DECODE_FIELD( isSuccessful);
	DECODE_FIELD( errorText);

	bool bRes = isSuccessful == "true";

	m_pEWrapper->verifyCompleted( bRes, errorText);

	return ptr;
}

const char* EDecoder::processDisplayGroupListMsg(const char* ptr, const char* endPtr) {
	int version;
	int reqId;
	std::string groups;

	DECODE_FIELD( version);
	DECODE_FIELD( reqId);
	DECODE_FIELD( groups);

	m_pEWrapper->displayGroupList( reqId, groups);

	return ptr;
}

const char* EDecoder::processDisplayGroupUpdatedMsg(const char* ptr, const char* endPtr) {
	int version;
	int reqId;
	std::string contractInfo;

	DECODE_FIELD( version);
	DECODE_FIELD( reqId);
	DECODE_FIELD( contractInfo);

	m_pEWrapper->displayGroupUpdated( reqId, contractInfo);

	return ptr;
}

const char* EDecoder::processVerifyAndAuthMessageApiMsg(const char* ptr, const char* endPtr) {
	int version;
	std::string apiData;
	std::string xyzChallenge;

	DECODE_FIELD( version);
	DECODE_FIELD( apiData);
	DECODE_FIELD( xyzChallenge);

	m_pEWrapper->verifyAndAuthMessageAPI( apiData, xyzChallenge);

	return ptr;
}

const char* EDecoder::processVerifyAndAuthCompletedMsg(const char* ptr, const char* endPtr) {
	int version;
	std::string isSuccessful;
	std::string errorText;

	DECODE_FIELD( version);
	DECODE_FIELD( isSuccessful);
	DECODE_FIELD( errorText);

	bool bRes = isSuccessful == "true";

	m_pEWrapper->verifyAndAuthCompleted( bRes, errorText);

	return ptr;
}

const char* EDecoder::processPositionMultiMsg(const char* ptr, const char* endPtr) {
	int version;
	int reqId;
	std::string account;
	std::string modelCode;
	double position;
	double avgCost = 0;

	DECODE_FIELD( version);
	DECODE_FIELD( reqId);
	DECODE_FIELD( account);

	// decode contract fields
	Contract contract;
	DECODE_FIELD( contract.conId);
	DECODE_FIELD( contract.symbol);
	DECODE_FIELD( contract.secType);
	DECODE_FIELD( contract.lastTradeDateOrContractMonth);
	DECODE_FIELD( contract.strike);
	DECODE_FIELD( contract.right);
	DECODE_FIELD( contract.multiplier);
	DECODE_FIELD( contract.exchange);
	DECODE_FIELD( contract.currency);
	DECODE_FIELD( contract.localSymbol);
	DECODE_FIELD( contract.tradingClass);
	DECODE_FIELD( position);
	DECODE_FIELD( avgCost);
	DECODE_FIELD( modelCode);

	m_pEWrapper->positionMulti( reqId, account, modelCode, contract, position, avgCost);

	return ptr;
}

const char* EDecoder::processPositionMultiEndMsg(const char* ptr, const char* endPtr) {
	int version;
	int reqId;

	DECODE_FIELD( version);
	DECODE_FIELD( reqId);

	m_pEWrapper->positionMultiEnd( reqId);

	return ptr;
}

const char* EDecoder::processAccountUpdateMultiMsg(const char* ptr, const char* endPtr) {
	int version;
	int reqId;
	std::string account;
	std::string modelCode;
	std::string key;
	std::string value;
	std::string currency;

	DECODE_FIELD( version);
	DECODE_FIELD( reqId);
	DECODE_FIELD( account);
	DECODE_FIELD( modelCode);
	DECODE_FIELD( key);
	DECODE_FIELD( value);
	DECODE_FIELD( currency);

	m_pEWrapper->accountUpdateMulti( reqId, account, modelCode, key, value, currency);

	return ptr;
}

const char* EDecoder::processAccountUpdateMultiEndMsg(const char* ptr, const char* endPtr) {
	int version;
	int reqId;

	DECODE_FIELD( version);
	DECODE_FIELD( reqId);

	m_pEWrapper->accountUpdateMultiEnd( reqId);

	return ptr;
}

const char* EDecoder::processSecurityDefinitionOptionalParameterMsg(const char* ptr, const char* endPtr) {
	int reqId;
	std::string exchange;
	int underlyingConId;
	std::string tradingClass;
	std::string multiplier;
	int expirationsSize, strikesSize;
	std::set<std::string> expirations;
	std::set<double> strikes;

	DECODE_FIELD(reqId);
	DECODE_FIELD(exchange);
	DECODE_FIELD(underlyingConId);
	DECODE_FIELD(tradingClass);
	DECODE_FIELD(multiplier);
	DECODE_FIELD(expirationsSize);

	for (int i = 0; i < expirationsSize; i++) {
		std::string expiration;

		DECODE_FIELD(expiration);

		expirations.insert(expiration);
	}

	DECODE_FIELD(strikesSize);

	for (int i = 0; i < strikesSize; i++) {
		double strike;

		DECODE_FIELD(strike);

		strikes.insert(strike);
	}

	m_pEWrapper->securityDefinitionOptionalParameter(reqId, exchange, underlyingConId, tradingClass, multiplier, expirations, strikes);

	return ptr;
}

const char* EDecoder::processSecurityDefinitionOptionalParameterEndMsg(const char* ptr, const char* endPtr) {
	int reqId;

	DECODE_FIELD(reqId);

	m_pEWrapper->securityDefinitionOptionalParameterEnd(reqId);

	return ptr;
}

const char* EDecoder::processSoftDollarTiersMsg(const char* ptr, const char* endPtr) 
{
	int reqId;
	int nTiers;

	DECODE_FIELD(reqId);
	DECODE_FIELD(nTiers);

	std::vector<SoftDollarTier> tiers(nTiers); 

	for (int i = 0; i < nTiers; i++) {
		std::string name, value, dislplayName;

		DECODE_FIELD(name);
		DECODE_FIELD(value);
		DECODE_FIELD(dislplayName);

		tiers[i] = SoftDollarTier(name, value, dislplayName); 
	}

	m_pEWrapper->softDollarTiers(reqId, tiers);

	return ptr;
}

const char* EDecoder::processFamilyCodesMsg(const char* ptr, const char* endPtr) 
{
	typedef std::vector<FamilyCode> FamilyCodeList;
	FamilyCodeList familyCodes;
	int nFamilyCodes = 0;
	DECODE_FIELD( nFamilyCodes);

	if (nFamilyCodes > 0) {
		familyCodes.resize(nFamilyCodes);
		for( int i = 0; i < nFamilyCodes; ++i) {
			DECODE_FIELD( familyCodes[i].accountID);
			DECODE_FIELD( familyCodes[i].familyCodeStr);
		}
	}

	m_pEWrapper->familyCodes(familyCodes);

	return ptr;
}

const char* EDecoder::processSymbolSamplesMsg(const char* ptr, const char* endPtr) 
{
	int reqId;
	typedef std::vector<ContractDescription> ContractDescriptionList;
	ContractDescriptionList contractDescriptions;
	int nContractDescriptions = 0;
	DECODE_FIELD( reqId);
	DECODE_FIELD( nContractDescriptions);

	if (nContractDescriptions > 0) {
		contractDescriptions.resize(nContractDescriptions);
		for( int i = 0; i < nContractDescriptions; ++i) {
			ContractDescription& contractDescription = contractDescriptions[i];
			Contract& contract = contractDescription.contract;
			DECODE_FIELD( contract.conId);
			DECODE_FIELD( contract.symbol);
			DECODE_FIELD( contract.secType);
			DECODE_FIELD( contract.primaryExchange);
			DECODE_FIELD( contract.currency);

			int nDerivativeSecTypes = 0;
			DECODE_FIELD(nDerivativeSecTypes);
			if (nDerivativeSecTypes <= 0)
				continue;

			ContractDescription::DerivativeSecTypesList& derivativeSecTypes = contractDescription.derivativeSecTypes;
			derivativeSecTypes.resize(nDerivativeSecTypes);
			for (int j = 0; j < nDerivativeSecTypes; ++j){
				DECODE_FIELD( derivativeSecTypes[j]);
			}
		}
	}

	m_pEWrapper->symbolSamples(reqId, contractDescriptions);

	return ptr;
}

const char* EDecoder::processMktDepthExchangesMsg(const char* ptr, const char* endPtr) 
{
	typedef std::vector<DepthMktDataDescription> DepthMktDataDescriptionList;
	DepthMktDataDescriptionList depthMktDataDescriptions;
	int nDepthMktDataDescriptions = 0;
	DECODE_FIELD( nDepthMktDataDescriptions);

	if (nDepthMktDataDescriptions > 0) {
		depthMktDataDescriptions.resize(nDepthMktDataDescriptions);
		for( int i = 0; i < nDepthMktDataDescriptions; ++i) {
			if (m_serverVersion >= MIN_SERVER_VER_SERVICE_DATA_TYPE) {
				DECODE_FIELD( depthMktDataDescriptions[i].exchange);
				DECODE_FIELD( depthMktDataDescriptions[i].secType);
				DECODE_FIELD( depthMktDataDescriptions[i].listingExch);
				DECODE_FIELD( depthMktDataDescriptions[i].serviceDataType);
				DECODE_FIELD( depthMktDataDescriptions[i].aggGroup);
			} else {
				DECODE_FIELD( depthMktDataDescriptions[i].exchange);
				DECODE_FIELD( depthMktDataDescriptions[i].secType);
				bool isL2;
				DECODE_FIELD( isL2);
				depthMktDataDescriptions[i].serviceDataType = isL2 ? "Deep2" : "Deep";
			}
		}
	}

	m_pEWrapper->mktDepthExchanges(depthMktDataDescriptions);

	return ptr;
}

const char* EDecoder::processTickNewsMsg(const char* ptr, const char* endPtr) 
{
	int tickerId;
	time_t timeStamp;
	std::string providerCode;
	std::string articleId;
	std::string headline;
	std::string extraData;

	DECODE_FIELD( tickerId);
	DECODE_FIELD_TIME( timeStamp);
	DECODE_FIELD( providerCode);
	DECODE_FIELD( articleId);
	DECODE_FIELD( headline);
	DECODE_FIELD( extraData);

	m_pEWrapper->tickNews(tickerId, timeStamp, providerCode, articleId, headline, extraData);

	return ptr;
}

const char* EDecoder::processNewsProvidersMsg(const char* ptr, const char* endPtr) 
{
	typedef std::vector<NewsProvider> NewsProviderList;
	NewsProviderList newsProviders;
	int nNewsProviders = 0;
	DECODE_FIELD( nNewsProviders);

	if (nNewsProviders > 0) {
		newsProviders.resize(nNewsProviders);
		for( int i = 0; i < nNewsProviders; ++i) {
			DECODE_FIELD( newsProviders[i].providerCode);
			DECODE_FIELD( newsProviders[i].providerName);
		}
	}

	m_pEWrapper->newsProviders(newsProviders);

	return ptr;
}

const char* EDecoder::processNewsArticleMsg(const char* ptr, const char* endPtr) 
{
	int requestId;
	int articleType;
	std::string articleText;

	DECODE_FIELD( requestId);
	DECODE_FIELD( articleType);
	DECODE_FIELD( articleText);

	m_pEWrapper->newsArticle(requestId, articleType, articleText);

	return ptr;
}

const char* EDecoder::processHistoricalNewsMsg(const char* ptr, const char* endPtr) 
{
	int requestId;
	std::string time;
	std::string providerCode;
	std::string articleId;
	std::string headline;

	DECODE_FIELD( requestId);
	DECODE_FIELD( time);
	DECODE_FIELD( providerCode);
	DECODE_FIELD( articleId);
	DECODE_FIELD( headline);

	m_pEWrapper->historicalNews(requestId, time, providerCode, articleId, headline);

	return ptr;
}

const char* EDecoder::processHistoricalNewsEndMsg(const char* ptr, const char* endPtr) 
{
	int requestId;
	bool hasMore;

	DECODE_FIELD( requestId);
	DECODE_FIELD( hasMore);

	m_pEWrapper->historicalNewsEnd(requestId, hasMore);

	return ptr;
}

const char* EDecoder::processMarketRuleMsg(const char* ptr, const char* endPtr)
{
	int marketRuleId;
	typedef std::vector<PriceIncrement> PriceIncrementList;
	PriceIncrementList priceIncrements;
	int nPriceIncrements = 0;

	DECODE_FIELD( marketRuleId);
	DECODE_FIELD( nPriceIncrements);

	if (nPriceIncrements > 0) {
		priceIncrements.resize(nPriceIncrements);
		for( int i = 0; i < nPriceIncrements; ++i) {
			DECODE_FIELD( priceIncrements[i].lowEdge);
			DECODE_FIELD( priceIncrements[i].increment);
		}
	}

	m_pEWrapper->marketRule(marketRuleId, priceIncrements);

	return ptr;
}

int EDecoder::processConnectAck(const char*& beginPtr, const char* endPtr)
{
	// process a connect Ack message from the buffer;
	// return number of bytes consumed
	assert( beginPtr && beginPtr < endPtr);

	try {

		const char* ptr = beginPtr;

		// check server version
		DECODE_FIELD( m_serverVersion);

		// handle redirects
		if( m_serverVersion < 0) {
			m_serverVersion = 0;

			std::string hostport, host;
			int port = -1;

			DECODE_FIELD( hostport);

			std::string::size_type sep = hostport.find( ':');
			if( sep != std::string::npos) {
				host = hostport.substr(0, sep);
				port = atoi( hostport.c_str() + ++sep);
			}
			else {
				host = hostport;
			}

			if (m_pClientMsgSink)
				m_pClientMsgSink->redirect(host.c_str(), port);
		} else {
			std::string twsTime;

			if( m_serverVersion >= 20) {

				DECODE_FIELD(twsTime);
			}

			if (m_pClientMsgSink)
				m_pClientMsgSink->serverVersion(m_serverVersion, twsTime.c_str());

			m_pEWrapper->connectAck();
		}

		int processed = ptr - beginPtr;
		beginPtr = ptr;
		return processed;
	}
	catch(const std::exception& e) {
		m_pEWrapper->error( NO_VALID_ID, SOCKET_EXCEPTION.code(), SOCKET_EXCEPTION.msg() + e.what());
	}

	return 0;
}

const char* EDecoder::processSmartComponentsMsg(const char* ptr, const char* endPtr) {
	int reqId;
	int n;
	SmartComponentsMap theMap;

	DECODE_FIELD(reqId);
	DECODE_FIELD(n);

	for (int i = 0; i < n; i++) {
		int bitNumber;
		std::string exchange;
		char exchangeLetter;

		DECODE_FIELD(bitNumber);
		DECODE_FIELD(exchange);
		DECODE_FIELD(exchangeLetter);

		theMap[bitNumber] = std::make_tuple(exchange, exchangeLetter);
	}

	m_pEWrapper->smartComponents(reqId, theMap);
	
	return ptr;
}

const char* EDecoder::processTickReqParamsMsg(const char* ptr, const char* endPtr) {
	int tickerId;
	double minTick;
	std::string bboExchange;
	int snapshotPermissions;

	DECODE_FIELD(tickerId);
	DECODE_FIELD(minTick);
	DECODE_FIELD(bboExchange);
	DECODE_FIELD(snapshotPermissions);

	m_pEWrapper->tickReqParams(tickerId, minTick, bboExchange, snapshotPermissions);
	
	return ptr;
}

const char* EDecoder::processHeadTimestampMsg(const char* ptr, const char* endPtr) {
	int reqId;
	std::string headTimestamp;

	DECODE_FIELD(reqId);
	DECODE_FIELD(headTimestamp);

	m_pEWrapper->headTimestamp(reqId, headTimestamp);
	
	return ptr;
}

const char* EDecoder::processHistogramDataMsg(const char* ptr, const char* endPtr) {
	int reqId;
	int n;
	HistogramDataVector data;
	HistogramEntry entry;

	DECODE_FIELD(reqId);
	DECODE_FIELD(n);

	for (int i = 0; i < n; i++) {
		DECODE_FIELD(entry.price);
		DECODE_FIELD(entry.size);

		data.push_back(entry);
	}

	m_pEWrapper->histogramData(reqId, data);
	
	return ptr;
}

const char* EDecoder::processRerouteMktDataReqMsg(const char* ptr, const char* endPtr) {
	int reqId;
	int conId;
	std::string exchange;

	DECODE_FIELD(reqId);
	DECODE_FIELD(conId);
	DECODE_FIELD(exchange);

	m_pEWrapper->rerouteMktDataReq(reqId, conId, exchange);
	
	return ptr;
}

const char* EDecoder::processRerouteMktDepthReqMsg(const char* ptr, const char* endPtr) {
	int reqId;
	int conId;
	std::string exchange;

	DECODE_FIELD(reqId);
	DECODE_FIELD(conId);
	DECODE_FIELD(exchange);

	m_pEWrapper->rerouteMktDepthReq(reqId, conId, exchange);
	
	return ptr;
}

const char* EDecoder::processPnLMsg(const char* ptr, const char* endPtr) {
    int reqId;
    double dailyPnL;
    double unrealizedPnL = DBL_MAX;
    double realizedPnL = DBL_MAX;

    DECODE_FIELD(reqId)
    DECODE_FIELD(dailyPnL)

    if (m_serverVersion >= MIN_SERVER_VER_UNREALIZED_PNL) {
        DECODE_FIELD(unrealizedPnL)
    }

    if (m_serverVersion >= MIN_SERVER_VER_REALIZED_PNL) {
        DECODE_FIELD(realizedPnL)
    }

    m_pEWrapper->pnl(reqId, dailyPnL, unrealizedPnL, realizedPnL);
    
    return ptr;
}

const char* EDecoder::processPnLSingleMsg(const char* ptr, const char* endPtr) {
    int reqId;
    int pos;
    double dailyPnL;
    double unrealizedPnL = DBL_MAX;
    double realizedPnL = DBL_MAX;
    double value;

    DECODE_FIELD(reqId);
    DECODE_FIELD(pos);
    DECODE_FIELD(dailyPnL);

    if (m_serverVersion >= MIN_SERVER_VER_UNREALIZED_PNL) {
        DECODE_FIELD(unrealizedPnL)
    }

    if (m_serverVersion >= MIN_SERVER_VER_REALIZED_PNL) {
        DECODE_FIELD(realizedPnL)
    }

    DECODE_FIELD(value);


    m_pEWrapper->pnlSingle(reqId, pos, dailyPnL, unrealizedPnL, realizedPnL, value);

    return ptr;
}

template<typename T>
const char* EDecoder::processHistoricalTicks(const char* ptr, const char* endPtr) {
    int reqId, nTicks;
    bool done;

    DECODE_FIELD(reqId);
    DECODE_FIELD(nTicks);

    std::vector<T> ticks(nTicks);

    for (int i = 0; i < nTicks; i++) {
        T &tick = ticks[i];

        ptr = decodeTick(tick, ptr, endPtr);
    }

    DECODE_FIELD(done);

    callEWrapperCallBack(reqId, ticks, done);

    return ptr;
}


const char* EDecoder::decodeTick(HistoricalTick& tick, const char* ptr, const char* endPtr) {
    int nope;

    DECODE_FIELD(tick.time);
    DECODE_FIELD(nope);
    DECODE_FIELD(tick.price);
    DECODE_FIELD(tick.size);

    return ptr;
}

void EDecoder::callEWrapperCallBack(int reqId, const std::vector<HistoricalTick> &ticks, bool done) {
    m_pEWrapper->historicalTicks(reqId, ticks, done);
}

const char* EDecoder::decodeTick(HistoricalTickBidAsk& tick, const char* ptr, const char* endPtr) {
    DECODE_FIELD(tick.time);
    int attrMask;
    DECODE_FIELD(attrMask);
    std::bitset<32> mask(attrMask);
    tick.tickAttribBidAsk.askPastHigh = mask[0];
    tick.tickAttribBidAsk.bidPastLow = mask[1];
    DECODE_FIELD(tick.priceBid);
    DECODE_FIELD(tick.priceAsk);
    DECODE_FIELD(tick.sizeBid);
    DECODE_FIELD(tick.sizeAsk);

    return ptr;
}

void EDecoder::callEWrapperCallBack(int reqId, const std::vector<HistoricalTickBidAsk> &ticks, bool done) {
    m_pEWrapper->historicalTicksBidAsk(reqId, ticks, done);
}

const char* EDecoder::decodeTick(HistoricalTickLast& tick, const char* ptr, const char* endPtr) {
    DECODE_FIELD(tick.time);
    int attrMask;
    DECODE_FIELD(attrMask);
    std::bitset<32> mask(attrMask);
    tick.tickAttribLast.pastLimit = mask[0];
    tick.tickAttribLast.unreported = mask[1];
    DECODE_FIELD(tick.price);
    DECODE_FIELD(tick.size);
    DECODE_FIELD(tick.exchange);
    DECODE_FIELD(tick.specialConditions);

    return ptr;
}

void EDecoder::callEWrapperCallBack(int reqId, const std::vector<HistoricalTickLast> &ticks, bool done) {
    m_pEWrapper->historicalTicksLast(reqId, ticks, done);
}

const char* EDecoder::processHistoricalTicks(const char* ptr, const char* endPtr) {
    return processHistoricalTicks<HistoricalTick>(ptr, endPtr);
}

const char* EDecoder::processHistoricalTicksBidAsk(const char* ptr, const char* endPtr) {
    return processHistoricalTicks<HistoricalTickBidAsk>(ptr, endPtr);
}

const char* EDecoder::processHistoricalTicksLast(const char* ptr, const char* endPtr) {
    return processHistoricalTicks<HistoricalTickLast>(ptr, endPtr);
}

const char* EDecoder::processTickByTickDataMsg(const char* ptr, const char* endPtr) {
    int reqId;
    int tickType = 0;
	time_t time;

    DECODE_FIELD(reqId);
    DECODE_FIELD(tickType);
    DECODE_FIELD(time);

    if (tickType == 1 || tickType == 2) { // Last/AllLast
            double price;
            int size;
            int attrMask;
            TickAttribLast tickAttribLast = {};
            std::string exchange;
            std::string specialConditions;

            DECODE_FIELD(price);
            DECODE_FIELD(size);
            DECODE_FIELD(attrMask);

            std::bitset<32> mask(attrMask);
            tickAttribLast.pastLimit = mask[0];
            tickAttribLast.unreported = mask[1];

            DECODE_FIELD(exchange);
            DECODE_FIELD(specialConditions);

            m_pEWrapper->tickByTickAllLast(reqId, tickType, time, price, size, tickAttribLast, exchange, specialConditions);

    } else if (tickType == 3) { // BidAsk
            double bidPrice;
            double askPrice;
            int bidSize;
            int askSize;
            int attrMask;
            DECODE_FIELD(bidPrice);
            DECODE_FIELD(askPrice);
            DECODE_FIELD(bidSize);
            DECODE_FIELD(askSize);
            DECODE_FIELD(attrMask);

            TickAttribBidAsk tickAttribBidAsk = {};
            std::bitset<32> mask(attrMask);
            tickAttribBidAsk.bidPastLow = mask[0];
            tickAttribBidAsk.askPastHigh = mask[1];

            m_pEWrapper->tickByTickBidAsk(reqId, time, bidPrice, askPrice, bidSize, askSize, tickAttribBidAsk);
    } else if (tickType == 4) { // MidPoint
            double midPoint;
            DECODE_FIELD(midPoint);

            m_pEWrapper->tickByTickMidPoint(reqId, time, midPoint);
    }

    return ptr;
}

const char* EDecoder::processOrderBoundMsg(const char* ptr, const char* endPtr) {
	long long orderId;
	int apiClientId;
	int apiOrderId;

	DECODE_FIELD( orderId);
	DECODE_FIELD( apiClientId);
	DECODE_FIELD( apiOrderId);

	m_pEWrapper->orderBound( orderId, apiClientId, apiOrderId);

	return ptr;
}

const char* EDecoder::processCompletedOrderMsg(const char* ptr, const char* endPtr) 
{
	Order order;
	Contract contract;
	OrderState orderState;
	EOrderDecoder eOrderDecoder(&contract, &order, &orderState, UNSET_INTEGER, m_serverVersion);

	// read contract fields
	eOrderDecoder.decodeContract(ptr, endPtr);

	// read order fields
	eOrderDecoder.decodeAction(ptr, endPtr);
	eOrderDecoder.decodeTotalQuantity(ptr, endPtr);
	eOrderDecoder.decodeOrderType(ptr, endPtr);
	eOrderDecoder.decodeLmtPrice(ptr, endPtr);
	eOrderDecoder.decodeAuxPrice(ptr, endPtr);
	eOrderDecoder.decodeTIF(ptr, endPtr);
	eOrderDecoder.decodeOcaGroup(ptr, endPtr);
	eOrderDecoder.decodeAccount(ptr, endPtr);
	eOrderDecoder.decodeOpenClose(ptr, endPtr);
	eOrderDecoder.decodeOrigin(ptr, endPtr);
	eOrderDecoder.decodeOrderRef(ptr, endPtr);
	eOrderDecoder.decodePermId(ptr, endPtr);
	eOrderDecoder.decodeOutsideRth(ptr, endPtr);
	eOrderDecoder.decodeHidden(ptr, endPtr);
	eOrderDecoder.decodeDiscretionaryAmount(ptr, endPtr);
	eOrderDecoder.decodeGoodAfterTime(ptr, endPtr);
	eOrderDecoder.decodeFAParams(ptr, endPtr);
	eOrderDecoder.decodeModelCode(ptr, endPtr);
	eOrderDecoder.decodeGoodTillDate(ptr, endPtr);
	eOrderDecoder.decodeRule80A(ptr, endPtr);
	eOrderDecoder.decodePercentOffset(ptr, endPtr);
	eOrderDecoder.decodeSettlingFirm(ptr, endPtr);
	eOrderDecoder.decodeShortSaleParams(ptr, endPtr);
	eOrderDecoder.decodeBoxOrderParams(ptr, endPtr);
	eOrderDecoder.decodePegToStkOrVolOrderParams(ptr, endPtr);
	eOrderDecoder.decodeDisplaySize(ptr, endPtr);
	eOrderDecoder.decodeSweepToFill(ptr, endPtr);
	eOrderDecoder.decodeAllOrNone(ptr, endPtr);
	eOrderDecoder.decodeMinQty(ptr, endPtr);
	eOrderDecoder.decodeOcaType(ptr, endPtr);
	eOrderDecoder.decodeTriggerMethod(ptr, endPtr);
	eOrderDecoder.decodeVolOrderParams(ptr, endPtr, false);
	eOrderDecoder.decodeTrailParams(ptr, endPtr);
	eOrderDecoder.decodeComboLegs(ptr, endPtr);
	eOrderDecoder.decodeSmartComboRoutingParams(ptr, endPtr);
	eOrderDecoder.decodeScaleOrderParams(ptr, endPtr);
	eOrderDecoder.decodeHedgeParams(ptr, endPtr);
	eOrderDecoder.decodeClearingParams(ptr, endPtr);
	eOrderDecoder.decodeNotHeld(ptr, endPtr);
	eOrderDecoder.decodeDeltaNeutral(ptr, endPtr);
	eOrderDecoder.decodeAlgoParams(ptr, endPtr);
	eOrderDecoder.decodeSolicited(ptr, endPtr);
	eOrderDecoder.decodeOrderStatus(ptr, endPtr);
	eOrderDecoder.decodeVolRandomizeFlags(ptr, endPtr);
	eOrderDecoder.decodePegBenchParams(ptr, endPtr);
	eOrderDecoder.decodeConditions(ptr, endPtr);
	eOrderDecoder.decodeStopPriceAndLmtPriceOffset(ptr, endPtr);
	eOrderDecoder.decodeCashQty(ptr, endPtr);
	eOrderDecoder.decodeDontUseAutoPriceForHedge(ptr, endPtr);
	eOrderDecoder.decodeIsOmsContainer(ptr, endPtr);
	eOrderDecoder.decodeAutoCancelDate(ptr, endPtr);
	eOrderDecoder.decodeFilledQuantity(ptr, endPtr);
	eOrderDecoder.decodeRefFuturesConId(ptr, endPtr);
	eOrderDecoder.decodeAutoCancelParent(ptr, endPtr);
	eOrderDecoder.decodeShareholder(ptr, endPtr);
	eOrderDecoder.decodeImbalanceOnly(ptr, endPtr);
	eOrderDecoder.decodeRouteMarketableToBbo(ptr, endPtr);
	eOrderDecoder.decodeParentPermId(ptr, endPtr);
	eOrderDecoder.decodeCompletedTime(ptr, endPtr);
	eOrderDecoder.decodeCompletedStatus(ptr, endPtr);

	m_pEWrapper->completedOrder(contract, order, orderState);

	return ptr;
}

const char* EDecoder::processCompletedOrdersEndMsg(const char* ptr, const char* endPtr) 
{
	m_pEWrapper->completedOrdersEnd();
	return ptr;
}


int EDecoder::parseAndProcessMsg(const char*& beginPtr, const char* endPtr) {
	// process a single message from the buffer;
	// return number of bytes consumed

	assert( beginPtr && beginPtr < endPtr);

	if (m_serverVersion == 0)
		return processConnectAck(beginPtr, endPtr);

	try {

		const char* ptr = beginPtr;

		int msgId;
		DECODE_FIELD( msgId);

		switch( msgId) {
		case TICK_PRICE:
			ptr = processTickPriceMsg(ptr, endPtr);
			break;

		case TICK_SIZE:
			ptr = processTickSizeMsg(ptr, endPtr);
			break;

		case TICK_OPTION_COMPUTATION:
			ptr = processTickOptionComputationMsg(ptr, endPtr);
			break;

		case TICK_GENERIC:
			ptr = processTickGenericMsg(ptr, endPtr);
			break;

		case TICK_STRING:
			ptr = processTickStringMsg(ptr, endPtr);
			break;

		case TICK_EFP:
			ptr = processTickEfpMsg(ptr, endPtr);
			break;

		case ORDER_STATUS:
			ptr = processOrderStatusMsg(ptr, endPtr);
			break;

		case ERR_MSG:
			ptr = processErrMsgMsg(ptr, endPtr);
			break;

		case OPEN_ORDER:
			ptr = processOpenOrderMsg(ptr, endPtr);
			break;

		case ACCT_VALUE:
			ptr = processAcctValueMsg(ptr, endPtr);
			break;

		case PORTFOLIO_VALUE:
			ptr = processPortfolioValueMsg(ptr, endPtr);
			break;

		case ACCT_UPDATE_TIME:
			ptr = processAcctUpdateTimeMsg(ptr, endPtr);
			break;

		case NEXT_VALID_ID:
			ptr = processNextValidIdMsg(ptr, endPtr);
			break;

		case CONTRACT_DATA:
			ptr = processContractDataMsg(ptr, endPtr);
			break;

		case BOND_CONTRACT_DATA:
			ptr = processBondContractDataMsg(ptr, endPtr);
			break;

		case EXECUTION_DATA:
			ptr = processExecutionDetailsMsg(ptr, endPtr);
			break;

		case MARKET_DEPTH:
			ptr = processMarketDepthMsg(ptr, endPtr);
			break;

		case MARKET_DEPTH_L2:
			ptr = processMarketDepthL2Msg(ptr, endPtr);
			break;

		case NEWS_BULLETINS:
			ptr = processNewsBulletinsMsg(ptr, endPtr);
			break;

		case MANAGED_ACCTS:
			ptr = processManagedAcctsMsg(ptr, endPtr);
			break;

		case RECEIVE_FA:
			ptr = processReceiveFaMsg(ptr, endPtr);
			break;

		case HISTORICAL_DATA:
			ptr = processHistoricalDataMsg(ptr, endPtr);
			break;

		case SCANNER_DATA:
			ptr = processScannerDataMsg(ptr, endPtr);
			break;

		case SCANNER_PARAMETERS:
			ptr = processScannerParametersMsg(ptr, endPtr);
			break;

		case CURRENT_TIME:
			ptr = processCurrentTimeMsg(ptr, endPtr);
			break;

		case REAL_TIME_BARS:
			ptr = processRealTimeBarsMsg(ptr, endPtr);
			break;

		case FUNDAMENTAL_DATA:
			ptr = processFundamentalDataMsg(ptr, endPtr);
			break;

		case CONTRACT_DATA_END:
			ptr = processContractDataEndMsg(ptr, endPtr);
			break;

		case OPEN_ORDER_END:
			ptr = processOpenOrderEndMsg(ptr, endPtr);
			break;

		case ACCT_DOWNLOAD_END:
			ptr = processAcctDownloadEndMsg(ptr, endPtr);
			break;

		case EXECUTION_DATA_END:
			ptr = processExecutionDetailsEndMsg(ptr, endPtr);
			break;

		case DELTA_NEUTRAL_VALIDATION:
			ptr = processDeltaNeutralValidationMsg(ptr, endPtr);
			break;

		case TICK_SNAPSHOT_END:
			ptr = processTickSnapshotEndMsg(ptr, endPtr);
			break;

		case MARKET_DATA_TYPE:
			ptr = processMarketDataTypeMsg(ptr, endPtr);
			break;

		case COMMISSION_REPORT:
			ptr = processCommissionReportMsg(ptr, endPtr);
			break;

		case POSITION_DATA:
			ptr = processPositionDataMsg(ptr, endPtr);
			break;

		case POSITION_END:
			ptr = processPositionEndMsg(ptr, endPtr);
			break;

		case ACCOUNT_SUMMARY:
			ptr = processAccountSummaryMsg(ptr, endPtr);
			break;

		case ACCOUNT_SUMMARY_END:
			ptr = processAccountSummaryEndMsg(ptr, endPtr);
			break;

		case VERIFY_MESSAGE_API:
			ptr = processVerifyMessageApiMsg(ptr, endPtr);
			break;

		case VERIFY_COMPLETED:
			ptr = processVerifyCompletedMsg(ptr, endPtr);
			break;

		case DISPLAY_GROUP_LIST:
			ptr = processDisplayGroupListMsg(ptr, endPtr);
			break;

		case DISPLAY_GROUP_UPDATED:
			ptr = processDisplayGroupUpdatedMsg(ptr, endPtr);
			break;

		case VERIFY_AND_AUTH_MESSAGE_API:
			ptr = processVerifyAndAuthMessageApiMsg(ptr, endPtr);
			break;

		case VERIFY_AND_AUTH_COMPLETED:
			ptr = processVerifyAndAuthCompletedMsg(ptr, endPtr);
			break;

		case POSITION_MULTI:
			ptr = processPositionMultiMsg(ptr, endPtr);
			break;

		case POSITION_MULTI_END:
			ptr = processPositionMultiEndMsg(ptr, endPtr);
			break;

		case ACCOUNT_UPDATE_MULTI:
			ptr = processAccountUpdateMultiMsg(ptr, endPtr);
			break;

		case ACCOUNT_UPDATE_MULTI_END:
			ptr = processAccountUpdateMultiEndMsg(ptr, endPtr);
			break;

		case SECURITY_DEFINITION_OPTION_PARAMETER:
			ptr = processSecurityDefinitionOptionalParameterMsg(ptr, endPtr);
			break;

		case SECURITY_DEFINITION_OPTION_PARAMETER_END:
			ptr = processSecurityDefinitionOptionalParameterEndMsg(ptr, endPtr);
			break;

		case SOFT_DOLLAR_TIERS:
			ptr = processSoftDollarTiersMsg(ptr, endPtr);
			break;

		case FAMILY_CODES:
			ptr = processFamilyCodesMsg(ptr, endPtr);
			break;

		case SMART_COMPONENTS:
			ptr = processSmartComponentsMsg(ptr, endPtr);
			break;

		case TICK_REQ_PARAMS:
			ptr = processTickReqParamsMsg(ptr, endPtr);
			break;

		case SYMBOL_SAMPLES:
			ptr = processSymbolSamplesMsg(ptr, endPtr);
			break;

		case MKT_DEPTH_EXCHANGES:
			ptr = processMktDepthExchangesMsg(ptr, endPtr);
			break;			

		case TICK_NEWS:
			ptr = processTickNewsMsg(ptr, endPtr);
			break;

		case NEWS_PROVIDERS:
			ptr = processNewsProvidersMsg(ptr, endPtr);
			break;

		case NEWS_ARTICLE:
			ptr = processNewsArticleMsg(ptr, endPtr);
			break;

		case HISTORICAL_NEWS:
			ptr = processHistoricalNewsMsg(ptr, endPtr);
			break;

		case HISTORICAL_NEWS_END:
			ptr = processHistoricalNewsEndMsg(ptr, endPtr);
			break;

		case HEAD_TIMESTAMP:
			ptr = processHeadTimestampMsg(ptr, endPtr);
			break;

		case HISTOGRAM_DATA:
			ptr = processHistogramDataMsg(ptr, endPtr);
			break;

		case HISTORICAL_DATA_UPDATE:
			ptr = processHistoricalDataUpdateMsg(ptr, endPtr);
			break;

		case REROUTE_MKT_DATA_REQ:
			ptr = processRerouteMktDataReqMsg(ptr, endPtr);
			break;

		case REROUTE_MKT_DEPTH_REQ:
			ptr = processRerouteMktDepthReqMsg(ptr, endPtr);
			break;

		case MARKET_RULE:
			ptr = processMarketRuleMsg(ptr, endPtr);
			break;

        case PNL:
            ptr = processPnLMsg(ptr, endPtr);
            break;

        case PNL_SINGLE:
            ptr = processPnLSingleMsg(ptr, endPtr);
            break;

		case HISTORICAL_TICKS:
			ptr = processHistoricalTicks(ptr, endPtr);
			break;

        case HISTORICAL_TICKS_BID_ASK:
            ptr = processHistoricalTicksBidAsk(ptr, endPtr);
            break;

        case HISTORICAL_TICKS_LAST:
            ptr = processHistoricalTicksLast(ptr, endPtr);
            break;

        case TICK_BY_TICK:
            ptr = processTickByTickDataMsg(ptr, endPtr);
            break;

        case ORDER_BOUND:
            ptr = processOrderBoundMsg(ptr, endPtr);
            break;

        case COMPLETED_ORDER:
            ptr = processCompletedOrderMsg(ptr, endPtr);
            break;

        case COMPLETED_ORDERS_END:
            ptr = processCompletedOrdersEndMsg(ptr, endPtr);
            break;

		default:
			{
				m_pEWrapper->error( msgId, UNKNOWN_ID.code(), UNKNOWN_ID.msg());
				m_pEWrapper->connectionClosed();
				break;
			}
		}

		if (!ptr)
			return 0;

		int processed = ptr - beginPtr;
		beginPtr = ptr;
		return processed;
	}
	catch(const std::exception& e) {
		m_pEWrapper->error( NO_VALID_ID, SOCKET_EXCEPTION.code(), SOCKET_EXCEPTION.msg() + e.what());
	}
	return 0;
}


bool EDecoder::CheckOffset(const char* ptr, const char* endPtr)
{
	assert (ptr && ptr <= endPtr);
	return (ptr && ptr < endPtr);
}

const char* EDecoder::FindFieldEnd(const char* ptr, const char* endPtr)
{
	return (const char*)memchr(ptr, 0, endPtr - ptr);
}

bool EDecoder::DecodeField(bool& boolValue, const char*& ptr, const char* endPtr)
{
	int intValue;
	if( !DecodeField(intValue, ptr, endPtr))
		return false;
	boolValue = (intValue > 0);
	return true;
}

bool EDecoder::DecodeField(int& intValue, const char*& ptr, const char* endPtr)
{
	if( !CheckOffset(ptr, endPtr))
		return false;
	const char* fieldBeg = ptr;
	const char* fieldEnd = FindFieldEnd(fieldBeg, endPtr);
	if( !fieldEnd)
		return false;
	intValue = atoi(fieldBeg);
	ptr = ++fieldEnd;
	return true;
}

bool EDecoder::DecodeFieldTime(time_t& time_tValue, const char*& ptr, const char* endPtr)
{
	if( !CheckOffset(ptr, endPtr))
		return false;
	const char* fieldBeg = ptr;
	const char* fieldEnd = FindFieldEnd(fieldBeg, endPtr);
	if( !fieldEnd)
		return false;
	time_tValue = atoll(fieldBeg);
	ptr = ++fieldEnd;
	return true;
}

bool EDecoder::DecodeField(long long& longLongValue, const char*& ptr, const char* endPtr)
{
	if( !CheckOffset(ptr, endPtr))
		return false;
	const char* fieldBeg = ptr;
	const char* fieldEnd = FindFieldEnd(fieldBeg, endPtr);
	if( !fieldEnd)
		return false;
	longLongValue = atoll(fieldBeg);
	ptr = ++fieldEnd;
	return true;
}

bool EDecoder::DecodeField(long& longValue, const char*& ptr, const char* endPtr)
{
	if( !CheckOffset(ptr, endPtr))
		return false;
	const char* fieldBeg = ptr;
	const char* fieldEnd = FindFieldEnd(fieldBeg, endPtr);
	if( !fieldEnd)
		return false;
	longValue = atol(fieldBeg);
	ptr = ++fieldEnd;
	return true;
}

bool EDecoder::DecodeField(double& doubleValue, const char*& ptr, const char* endPtr)
{
	if( !CheckOffset(ptr, endPtr))
		return false;
	const char* fieldBeg = ptr;
	const char* fieldEnd = FindFieldEnd(fieldBeg, endPtr);
	if( !fieldEnd)
		return false;
	doubleValue = atof(fieldBeg);
	ptr = ++fieldEnd;
	return true;
}

bool EDecoder::DecodeField(std::string& stringValue,
						   const char*& ptr, const char* endPtr)
{
	if( !CheckOffset(ptr, endPtr))
		return false;
	const char* fieldBeg = ptr;
	const char* fieldEnd = FindFieldEnd(ptr, endPtr);
	if( !fieldEnd)
		return false;
	stringValue = fieldBeg; // better way?
	ptr = ++fieldEnd;
	return true;
}

bool EDecoder::DecodeField(char& charValue,
						   const char*& ptr, const char* endPtr)
{
	if( !CheckOffset(ptr, endPtr))
		return false;
	const char* fieldBeg = ptr;
	const char* fieldEnd = FindFieldEnd(ptr, endPtr);
	if( !fieldEnd)
		return false;
	charValue = fieldBeg[0]; // better way?
	ptr = ++fieldEnd;
	return true;
}

bool EDecoder::DecodeFieldMax(int& intValue, const char*& ptr, const char* endPtr)
{
	std::string stringValue;
	if( !DecodeField(stringValue, ptr, endPtr))
		return false;
	intValue = stringValue.empty() ? UNSET_INTEGER : atoi(stringValue.c_str());
	return true;
}

bool EDecoder::DecodeFieldMax(long& longValue, const char*& ptr, const char* endPtr)
{
	int intValue;
	if( !DecodeFieldMax(intValue, ptr, endPtr))
		return false;
	longValue = intValue;
	return true;
}

bool EDecoder::DecodeFieldMax(double& doubleValue, const char*& ptr, const char* endPtr)
{
	std::string stringValue;
	if( !DecodeField(stringValue, ptr, endPtr))
		return false;
	doubleValue = stringValue.empty() ? UNSET_DOUBLE : atof(stringValue.c_str());
	return true;
}

const char* EDecoder::decodeLastTradeDate(const char* ptr, const char* endPtr, ContractDetails& contract, bool isBond) {
	std::string lastTradeDateOrContractMonth;
	DECODE_FIELD( lastTradeDateOrContractMonth);
	if (!lastTradeDateOrContractMonth.empty()){
		std::vector<std::string> splitted;
		std::istringstream buf(lastTradeDateOrContractMonth);
		for(std::string s; buf >> s; ) {
			splitted.push_back(s);
		}
		if (splitted.size() > 0) {
			if (isBond) {
				contract.maturity = splitted[0];
			} else {
				contract.contract.lastTradeDateOrContractMonth = splitted[0];
			}
		}
		if (splitted.size() > 1) {
			contract.lastTradeTime = splitted[1];
		}
		if (isBond && splitted.size() > 2) {
			contract.timeZoneId = splitted[2];
		}
	}
	return ptr;
}
