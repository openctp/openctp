#ifndef YD_DATA_STRUCT_H
#define YD_DATA_STRUCT_H

#include <math.h>
#include "ydDataType.h"
#include <float.h>

/// Data structs for YDApi

class YDSystemParam
{
public:
	YDString Name;
	YDString Target;
	YDString Value;
};

class YDExchangeTradeConstrain
{
public:
	int ExchangeOrderSpeed;
	int ExchangeOrderPeriod;
};

class YDExchangeConnectionInfo
{
public:
	int SystemUse1;
	int SystemUse2;
	int SystemUse3;
	int SystemUse4;
	int ExchangeRef;
	int ConnectionID;
	int ConnectionStatus;
	char Info[28];
	char InsertFlowControl[32];
	char CancelFlowControl[32];
};

class YDExchange
{
public:
	YDExchangeID ExchangeID;		    // Short string identify the exchange, e.g. "CFFEX", "DCE", "SHFE", ...
	int ExchangeRef;                    // An integer uniquely identify the exchange
	int ConnectionCount;                // Number of connections(seats) to the exchange
	int ProductRefStart;
	int ProductRefEnd;
	bool UseTodayPosition;              // Whether today and previous positions are traded separately. True for SHFE and INE
	bool UseArbitragePosition;          // Besides speculation and hedge, whether the exchange maintains separate position for arbitration. True for CFFEX 
	bool CloseTodayFirst;               // When "UseTodayPosition" is false, whether today opened positions are closed first. The commission may be different. True for CFFEX
	bool SingleSideMargin;              // Whether margin is calculated using larger side of the product or product group. True for SHFE, INE, and CFFEX
	int OptionExecutionSupport;         // 0 for not support, 1 for support without risk control, 2 for support with risk constrol
	int OptionAbandonExecutionSupport;  // 0 for not support, 1 for support without risk control, 2 for support with risk constrol
	int QuoteVolumeRestriction;         // 0 for allow single side, 1 for allow different volume, 2 for require same volume
	unsigned short ExchangeFlag;		// see constants start with YD_EF_
	bool SystemUse2;
	bool TradeStockOptions;	            // whether this exchange is trading stock/etf options(SSE/SZSE)
	YDExchangeTradeConstrain TradeConstrains[YD_MaxHedgeFlag];
	bool IsPublicConnectionID[64];      // Whether this connectionID can be used by every user
	YDExchangeConnectionInfo *ConnectionInfos;	// point to an array of YDExchangeConnectionInfo, array size if ConnectionCount
	mutable void *pUser;
	mutable double UserFloat;
	mutable int UserInt1;
	mutable int UserInt2;
	void *pInternalUse;
};

class YDTradeConstraint
{
public:
	int OpenLimit;
	int CancelLimit;
	int PositionLimit;
	int TradeVolumeLimit;
	int DirectionOpenLimit[2];
	int DirectionPositionLimit[2];
};

class YDProduct
{
public:
	YDProductID ProductID;              // Short string identify the product, e.g. "cu", "IC", "cu_o", ...
	int ProductRef;
	int ExchangeRef;
	int ProductClass;                   // Refer to "Product Class" section of ydDataType.h
	int Multiple;                       // Contract size
	double Tick;                        // Minimum amount for price change
	double UnderlyingMultiply;          // Volume of corresponding underlying instrument. Used for options, normally equals to 1
	int MaxMarketOrderVolume;
	int MinMarketOrderVolume;
	int MaxLimitOrderVolume;
	int MinLimitOrderVolume;
	int InstrumentRefStart;
	int InstrumentRefEnd;
	int SystemUse7[24];
	int SubProductClass;                // Refer to "Sub Product Class" section of ydDataType.h
	int SystemUse8[7];
	YDProductID ProductHint;
	const YDProduct *m_pMarginProduct;  // Points to the product that represents the product group, when single side margin is used
	const YDExchange *m_pExchange;
	mutable void *pUser;
	mutable double UserFloat;
	mutable int UserInt1;
	mutable int UserInt2;
	void *pInternalUse;
};

class YDInstrument;

class YDMarketData
{
public:
	int InstrumentRef;
	int TradingDay;
	double PreSettlementPrice;
	double PreClosePrice;
	double PreOpenInterest;
	double UpperLimitPrice;
	double LowerLimitPrice;
	double LastPrice;
	double BidPrice;
	double AskPrice;
	int BidVolume;
	int AskVolume;
	double Turnover;
	double OpenInterest;
	int Volume;
	int TimeStamp;
	double AveragePrice;
	double DynamicBasePrice;
	int LastTradeTimeStamp;
	int MarketDataFlag;                    // Refer to "Market Data Flag" section of ydDataType.h
	const YDInstrument *m_pInstrument;
	mutable void *pUser;
	mutable double UserFloat;
	mutable int UserInt1;
	mutable int UserInt2;
	void *pInternalUse;
};

class YDMarginRate;
class YDCombPositionDef;

class YDInstrument
{
public:
	YDInstrumentID InstrumentID;        // Short string identify the instrument, e.g. "cu2101", "IC2212", "c2103-C-2620", ...
	int InstrumentRef;                  // An integer uniquely identify the instrument
	int ProductRef;
	int ExchangeRef;
	int ProductClass;                   // Refer to "Product Class" section of ydDataType.h
	int DeliveryYear;
	int DeliveryMonth;
	int MaxMarketOrderVolume;
	int MinMarketOrderVolume;
	int MaxLimitOrderVolume;
	int MinLimitOrderVolume;
	double Tick;                        // Minimum amount for price change
	int Multiple;                       // Contract size
	int ExpireDate;
	double StrikePrice;
	int UnderlyingInstrumentRef;
	int OptionsType;                    // Refer to "Options Type" section of ydDataType.h
	double UnderlyingMultiply;          // Volume of corresponding underlying instrument. Used for options, normally equals to 1
	int SystemUse7[24];
	int SubProductClass;                // Refer to "Sub Product Class" section of ydDataType.h
	int CashInstrumentFlag;             // Refer to "Cash Instrument Flag" section of ydDataType.h
	int TradeControlFlag;				// Refer to "Trade Control Flag" section of ydDataType.h
	int QtyUnit;
	double Interest;
	int SystemUse8[2];
	bool SingleSideMargin;              // Whether margin is calculated using larger side of the product or product group. True for futures of SHFE, INE, and CFFEX
	bool InstrumentSingleSideMargin;    // Whether margin is calculated using larger side of instrument. True for futures of CZCE
	short ExpireTradingDayCount;
	int MarginCalcMethod;               // Option margin calculation method, 1 for CFFEX, 2 for SSE & SZSE, 0 for others 
	YDInstrumentID InstrumentHint;      // Hint of this instrument, useful for options of SSE/SZSE, e.g. "510050C2009M02350"
	const YDInstrument *m_pUnderlyingInstrument;  // Points to underlying instrument, only valid for options
	const YDExchange *m_pExchange;
	const YDProduct *m_pProduct;
	const YDMarketData *m_pMarketData;
	const YDInstrument *m_pLegInstrument[2];
	char LegDirction[2];
	short m_SystemUse8;
	const YDCombPositionDef *m_pCombPositionDef[2][YD_MaxHedgeFlag];

	mutable void *pUser;
	mutable double UserFloat;
	mutable int UserInt1;
	mutable int UserInt2;
	void *pInternalUse;
	int InternalUseInt1;
	int InternalUseInt2;
	bool AutoSubscribed;
	bool UserSubscribed;
	/// following fields are only valid when using ydExtendedApi
	bool IsStaticMargin;
	int MarginBasePriceType;
	int OrderPremiumBasePriceType[2];
	int OrderMarginBasePriceType;
	int MarginBasePriceAsUnderlyingType;
	double MarginBasePrice;
	const YDMarginRate *m_pExchangeMarginRate[YD_MaxHedgeFlag];

	inline double getPreSettlementPrice(void) const
	{
		return m_pMarketData->PreSettlementPrice;
	}
	inline double getPreClosePrice(void) const
	{
		return m_pMarketData->PreClosePrice;
	}
	inline double getPreOpenInterest(void) const
	{
		return m_pMarketData->PreOpenInterest;
	}
	inline double getUpperLimitPrice(void) const
	{
		return m_pMarketData->UpperLimitPrice;
	}
	inline double getLowerLimitPrice(void) const
	{
		return m_pMarketData->LowerLimitPrice;
	}
	inline double getLastPrice(void) const
	{
		return m_pMarketData->LastPrice;
	}
	inline double getBidPrice(void) const
	{
		return m_pMarketData->BidPrice;
	}
	inline double getAskPrice(void) const
	{
		return m_pMarketData->AskPrice;
	}
	inline int getBidVolume(void) const
	{
		return m_pMarketData->BidVolume;
	}
	inline int getAskVolume(void) const
	{
		return m_pMarketData->AskVolume;
	}
	inline double getTurnover(void) const
	{
		return m_pMarketData->Turnover;
	}
	inline double getOpenInterest(void) const
	{
		return m_pMarketData->OpenInterest;
	}
	inline int getVolume(void) const
	{
		return m_pMarketData->Volume;
	}
	inline double getAveragePrice(void) const
	{
		return m_pMarketData->AveragePrice;
	}

	inline double getMaxLastPreSettlementPrice(void) const
	{
		if ((m_pMarketData->Volume>0) && isfinite(m_pMarketData->LastPrice) && (m_pMarketData->LastPrice!=DBL_MAX) && (m_pMarketData->LastPrice>m_pMarketData->PreSettlementPrice))
		{
			return m_pMarketData->LastPrice;
		}
		else
		{
			return m_pMarketData->PreSettlementPrice;
		}
	}
};

class YDCombPositionDef
{
public:
	char SystemUse1[32];
	int CombPositionRef;
	int ExchangeRef;
	int Priority;
	short CombHedgeFlag;
	short CombPositionType;
	double Parameter;
	YDLongInstrumentID CombPositionID;
	const YDExchange *m_pExchange;
	const YDInstrument *m_pInstrument[2];
	int PositionDirection[2];
	int HedgeFlag[2];
	int PositionDate[2];
	mutable void *pUser;
	mutable double UserFloat;
	mutable int UserInt1;
	mutable int UserInt2;
};

class YDAccount
{
public:
	int SystemUse1;
	int AccountRef;
	YDAccountID AccountID;              // User account name in broker
	double PreBalance;
	double WarningLevel1;
	double WarningLevel2;
	double MaxMoneyUsage;               // Rate of fund that can be used for trading, should be less than 1
	double Deposit;
	double Withdraw;
	double FrozenWithdraw;
	int TradingRight;
	int MaxOrderCount;                  // Maximum number of orders that can be placed, read only
	int MaxLoginCount;                  // Maximum number of current login allowed, read only
	int LoginCount;                     // Number of active logins, read only
	int AccountFlag;                    // Bit map, refer to "Account Flag" section of ydDataType.h
	int SystemUse3;
	char TradingRightFromSource[YD_TRS_Count];
	int MaxCancelCount;                 // Maximum number of cancel order requestes, read only
	short MaxRequestSpeed;
	short SystemUse4;
	int SystemUse5;
	mutable void *pUser;
	mutable double UserFloat;
	mutable int UserInt1;
	mutable int UserInt2;
	void *pInternalUse;
};

class YDPrePosition
{
public:
	int SystemUse1;
	int AccountRef;
	int InstrumentRef;
	int PositionDirection;
	int HedgeFlag;
	int PrePosition;
	double PreSettlementPrice;
	double AverageOpenPrice;
	const YDInstrument *m_pInstrument;
	const YDAccount *m_pAccount;
};

class YDPreHolding
{
public:
	int SystemUse1;
	int AccountRef;
	int InstrumentRef;
	int PreHolding;
	double AverageOpenPrice;
	const YDInstrument *m_pInstrument;
	const YDAccount *m_pAccount;
};

class YDSpotPrePosition
{
public:
	int SystemUse1;
	int AccountRef;
	int InstrumentRef;
	int Position;
	int ExchangeFrozenVolume;
	int ExecAllocatedVolume;
	double ExecAllocatedAmount;
	const YDInstrument *m_pInstrument;
	const YDAccount *m_pAccount;
};

class YDCombPosition
{
public:
	int SystemUse1;
	int SystemUse2;
	int SystemUse3;
	int AccountRef;
	int CombPositionRef;
	int Position;
	int CombPositionDetailID;
	int SystemUse6;
};

class YDInputOrder
{
public:
	int SystemUse1;
	int SystemUse2;
	int SystemUse3;
	int SystemUse4;
	int SystemUse5;
	char Direction;                     // Refer to "Direction" section of ydDataType.h
	char OffsetFlag;                    // Refer to "Offset Flag" section of ydDataType.h
	char HedgeFlag;                     // Refer to "Hedge Flag" section of ydDataType.h
	char ConnectionSelectionType;       // Refer to "Connection Selection Type" section of ydDataType.h
	union
	{
		double Price;                   // Price for limit orders
		struct
		{
			int CombPositionDetailID;   // Set only when YDOrderFlag is YD_YOF_CombPosition, and Direction is YD_D_Split for SSE or SZSE
			int SystemUse6;
		};
	};
	int OrderVolume;
	int OrderRef;                       // User defined reference of the order. Will be passed back in later order and trade notifications 
	char OrderType;                     // Refer to "Order Type" section of ydDataType.h
	char YDOrderFlag;                   // Refer to "YD OrderFlag" section of ydDataType.h
	char ConnectionID;                  // Target connection ID if ConnectionSelectionType is not YD_CS_Any
	char SystemUse10;
	int ErrorNo;                        // Set by ydAPI, refer to "ydError.h"
	unsigned char OrderGroupID;         // indicates OrderRef management group, 0 for normal, 1-63 for strict management
	char GroupOrderRefControl;          // OrderRef control method for this order if OrderGroupID in in [1,63], refer to "Order group ref control" section of ydDataType.h
	char OrderTriggerType;              // Refer to "Order trigger type" section of ydDataType.h
	char ExchangeOrderAttribute;        // Refer to "Exchange Order Attribute" section of ydDataType.h
	int SystemUse8;
	long long SystemUse9;
	double TriggerPrice;                // Trigger price for trigger order
};

/*
Here are field requirements in YDInputOrder for different YDOrderFlag (please set all unused fields to 0)
	Common fields
		pInstrument in insertOrder(): point to YDInstrument, unless using YD_YOF_CombPosition
		pAccount in insertOrder(): point to YDAccount, can ignore or use NULL for traders
		HedgeFlag: hedge flag,must specify, even it is meaningless in this kind of order
		OrderRef: user set reference of order, please use positive number, 0 is reserved for YDClient, will be set by system if using checkAndInsertOrder
		ConnectionSelectionType: specify how to select exchange connection
		ConnectionID: if (ConnectionSelectionType==YD_CS_Fixed) || (ConnectionSelectionType==YD_CS_Prefered), specify connectionID,
			must be in IsPublicConnectionID set of YDExchange or IsDedicatedConnectionID set of YDAccountExchange
		ErrorNo: will be set in return message
	YDOrderFlag==YD_YOF_Normal
		Direction: direction, YD_D_Buy or YD_D_Sell
		OffsetFlag: offset flag, YD_OF_Open,YD_OF_Close,YD_OF_CloseToday or YD_OF_CloseYesterday (YD_OF_CloseToday and YD_OF_CloseYesterday are only for SHFE/INE),
			YD_OF_ForceClose can only be used by admin user
		OrderType: order Type, YD_ODT_Limit,YD_ODT_FAK,YD_ODT_Market or YD_ODT_FOK
		OrderVolume: order volume
		Price: limit price, useless if OrderType==YD_ODT_Market
	(YDOrderFlag==YD_YOF_OptionExecute) || (YDOrderFlag==YD_YOF_OptionAbandonExecute)
		Direction: useless, will be set to YD_D_Sell by system
		OffsetFlag: specify will position to execute, YD_OF_Close,YD_OF_CloseToday or YD_OF_CloseYesterday (YD_OF_CloseToday and YD_OF_CloseYesterday are only for SHFE/INE)
		OrderType: useless, will be set to YD_ODT_Limit
		OrderVolume: execute volume
		Price: useless
	YDOrderFlag==YD_YOF_RequestForQuote
		OrderVolume,Direction,OffsetFlag,OrderType,Price: useless
		HedgeFlag: meaningless
		this kind of order has no notify
	YDOrderFlag==YD_YOF_CombPosition
		use insertCombPositionOrder() instead of insertOrder()
		pCombPositionDef: pointer to combine position definition
		Direction: action direction, YD_D_Make or YD_D_Split
		OrderVolume: volume
		CombPositionDetailID: combine position detail ID, only use when Direction==YD_D_Split, and trade on stock exchanges
		OffsetFlag: useless for trader, admin user can use YD_OF_ForceClose to indicate forced split
		OrderType: useless
		HedgeFlag:  meaningless
	YDOrderFlag==YD_YOF_OptionExecuteTogether
		use insertOptionExecTogetherOrder() instead of insertOrder()
		pInstrument2: point to YDInstrument
		OrderVolume: volume
		Direction,OffsetFlag,OrderType: useless
	YDOrderFlag==YD_YOF_Mark
		Direction: action direction, YD_D_Buy for set, YD_D_Sell for cancel
		OrderType: YD_ODT_PositionOffsetMark, YD_ODT_OptionAbandonExecuteMark or YD_ODT_CloseFuturesPositionMark
		OrderVolume,OffsetFlag,Price: useless
		HedgeFlag: meaningless
		Special Note: when OrderType is YD_ODT_CloseFuturesPositionMark, pInstrument only means related exchange, has nothing to do with this instrument
	YDOrderFlag==YD_YOF_OptionSelfClose
		OrderVolume: volume, can be 0
		OrderType: order type, YD_ODT_CloseSelfOptionPosition, YD_ODT_ReserveOptionPosition or YD_ODT_SellCloseSelfFuturesPosition
		Direction,OffsetFlag,Price: useless
		HedgeFlag: meaningless
	YDOrderFlag==YD_YOF_FreezeUnderlying
		Direction: action direction, YD_D_Freeze or YD_D_Unfreeze
		OrderVolume: volume
		OffsetFlag,OrderType,Price: useless
		HedgeFlag: meaningless
	YDOrderFlag==YD_YOF_Cover (this is not covered order, but convesion between normal and covered positions)
		Direction: action direction, YD_D_Normal2Covered or YD_D_Covered2Normal
		OrderVolume: volume
		OffsetFlag,OrderType,Price: useless
		HedgeFlag: meaningless

For covered order in SSE/SZSE, use YDOrderFlag=YD_YOF_Normal and HedgeFlag=YD_HF_Covered
*/

class YDOrder
{
public:
	int SystemUse1;
	int SystemUse2;
	int SystemUse3;
	int SystemUse4;
	int SystemUse5;
	char Direction;                     // Refer to "Direction" section of ydDataType.h
	char OffsetFlag;                    // Refer to "Offset Flag" section of ydDataType.h
	char HedgeFlag;                     // Refer to "Hedge Flag" section of ydDataType.h
	char ConnectionSelectionType;       // Refer to "Connection Selection Type" section of ydDataType.h
	union
	{
		double Price;                   // Price for limit orders
		struct
		{
			int CombPositionDetailID;   // Set only when YDOrderFlag is YD_YOF_CombPosition, and Direction is YD_D_Split for SSE or SZSE
			int SystemUse6;
		};
	};
	int OrderVolume;
	int OrderRef;                       // User defined reference of the order. Will be passed back in later order and trade notifications 
	char OrderType;                     // Refer to "Order Type" section of ydDataType.h
	char YDOrderFlag;                   // Refer to "YD OrderFlag" section of ydDataType.h
	char ConnectionID;                  // Target connection ID if ConnectionSelectionType is not YD_CS_Any
	char RealConnectionID;              // Real connection ID for this order, <0 if not from connections of other systems
	int ErrorNo;                        // Set by ydAPI, refer to "ydError.h"
	int ExchangeRef;
	union
	{
		YDSysOrderID OrderSysID;
		int MaxOrderRef;                // When ErrorNo==YD_ERROR_InvalidGroupOrderRef
	};
	int OrderStatus;                    // Refer to "Order Status" section of ydDataType.h
	int TradeVolume;
	int InsertTime;
	YDLocalOrderID OrderLocalID;
	unsigned char OrderGroupID;         // Indicates OrderRef management group, 0 for normal, 1-63 for strict management
	char GroupOrderRefControl;          // OrderRef control method for this order if OrderGroupID in in [1,63], refer to "Order group ref control" section of ydDataType.h
	char OrderTriggerType;              // Refer to "Order trigger type" section of ydDataType.h
	char ExchangeOrderAttribute;        // Refer to "Exchange Order Attribute" section of ydDataType.h
	int SystemUse8;
	long long SystemUse9;
	double TriggerPrice;                // Trigger price for trigger order
	int OrderTriggerStatus;             // Refer to "Order trigger status" section of ydDataType.h
	int InsertTimeStamp;
	YDLongOrderSysID LongOrderSysID;
	int CancelTimeStamp;
	int SessionID;
};

typedef YDOrder YDMissingOrder;
// in YDMissingOrder, InsertTime is time in ydServer, not time in exchange

class YDCancelOrder
{
public:
	int SystemUse1;
	int SystemUse2;
	int SystemUse3;
	int SystemUse4;
	union
	{
		YDSysOrderID OrderSysID;
		int OrderRef;                   // When OrderGroupID!=0
	};
	char SystemUse5;
	char ConnectionSelectionType;       // Refer to "Connection Selection Type" section of ydDataType.h
	char ConnectionID;                  // Target connection ID if ConnectionSelectionType is not YD_CS_Any
	char YDOrderFlag;                   // Refer to "YD OrderFlag" section of ydDataType.h
	unsigned char OrderGroupID;         // If OrderGroupID!=0, use (OrderGroupID,OrderRef) indicate an order
	char SystemUse6;
	short SystemUse7;
	int SystemUse8;
	YDLongOrderSysID LongOrderSysID;
};

class YDFailedCancelOrder
{
public:
	int SystemUse1;
	int SystemUse2;
	int SystemUse3;
	int AccountRef;
	YDSysOrderID OrderSysID;
	char ExchangeRef;
	unsigned char OrderGroupID;
	char SystemUse7;
	char YDOrderFlag;                   // Refer to "YD OrderFlag" section of ydDataType.h
	int ErrorNo;                        // Set by ydAPI, refer to "ydError.h"
	int IsQuote;
	int OrderRef;
	int SystemUse9;
	YDLongOrderSysID LongOrderSysID;
};

class YDTrade
{
public:
	int SystemUse1;
	int SystemUse2;
	int SystemUse3;
	int AccountRef;
	int InstrumentRef;
	char Direction;                     // Refer to "Direction" section of ydDataType.h
	char OffsetFlag;                    // Refer to "Offset Flag" section of ydDataType.h
	char HedgeFlag;                     // Refer to "Hedge Flag" section of ydDataType.h
	char SystemUse6;
	YDTradeID TradeID;
	YDSysOrderID OrderSysID;
	double Price;
	int Volume;
	int TradeTime;
	double Commission;
	YDLocalOrderID OrderLocalID;
	int OrderRef;                       // User defined reference of the order. Will be passed back in later order and trade notifications 
	unsigned char OrderGroupID;         // User defined reference of the order. Will be passed back in later order and trade notifications
	char RealConnectionID;
	short SystemUse8;
	int TradeTimeStamp;
	YDLongOrderSysID LongOrderSysID;
	YDLongTradeID LongTradeID;
};

class YDInputQuote
{
public:
	int SystemUse1;
	int SystemUse2;
	int SystemUse3;
	int SystemUse4;
	int SystemUse5;
	char BidOffsetFlag;                 // Refer to "Offset Flag" section of ydDataType.h
	char BidHedgeFlag;                  // Refer to "Offset Flag" section of ydDataType.h
	char AskOffsetFlag;                 // Refer to "Offset Flag" section of ydDataType.h
	char AskHedgeFlag;                  // Refer to "Offset Flag" section of ydDataType.h
	double BidPrice;
	double AskPrice;
	int BidVolume;
	int AskVolume;
	int OrderRef;                       // User defined reference of the order. Will be passed back in later order and trade notifications 
	char ConnectionSelectionType;       // Refer to "Connection Selection Type" section of ydDataType.h
	char ConnectionID;                  // Target connection ID if ConnectionSelectionType is not YD_CS_Any
	char SystemUse7;
	char YDQuoteFlag;                   // Refer to "YD QuoteFlag" section of ydDataType.h, 
	unsigned char OrderGroupID;         // indicates OrderRef management group, 0 for normal, 1-63 for strict management
	char GroupOrderRefControl;          // OrderRef control method for this order if OrderGroupID in in [1,63], refer to "Order group ref control" section of ydDataType.h
	char ExchangeQuoteAttribute;        // Refer to "Exchange Order Attribute" section of ydDataType.h
	char SystemUse6;
	int ErrorNo;                        // Set by ydAPI, refer to "ydError.h"
};

class YDQuote
{
public:
	int SystemUse1;
	int SystemUse2;
	int SystemUse3;
	int SystemUse4;
	int SystemUse5;
	char BidOffsetFlag;                 // Refer to "Offset Flag" section of ydDataType.h
	char BidHedgeFlag;                  // Refer to "Offset Flag" section of ydDataType.h
	char AskOffsetFlag;                 // Refer to "Offset Flag" section of ydDataType.h
	char AskHedgeFlag;                  // Refer to "Offset Flag" section of ydDataType.h
	double BidPrice;
	double AskPrice;
	int BidVolume;
	int AskVolume;
	int OrderRef;                       // User defined reference of the order. Will be passed back in later order and trade notifications 
	char ConnectionSelectionType;       // Refer to "Connection Selection Type" section of ydDataType.h
	char ConnectionID;                  // Target connection ID if ConnectionSelectionType is not YD_CS_Any
	char RealConnectionID;              // Real connection ID for this quote, <0 if not from connections of other systems
	char YDQuoteFlag;                   // Refer to "YD QuoteFlag" section of ydDataType.h, 
	unsigned char OrderGroupID;         // indicates OrderRef management group, 0 for normal, 1-63 for strict management
	char GroupOrderRefControl;          // OrderRef control method for this order if OrderGroupID in in [1,63], refer to "Order group ref control" section of ydDataType.h
	char ExchangeQuoteAttribute;        // Refer to "Exchange Order Attribute" section of ydDataType.h
	char SystemUse6;
	int ErrorNo;                        // Set by ydAPI, refer to "ydError.h"
	int ExchangeRef;
	union
	{
		YDSysOrderID QuoteSysID;
		int MaxOrderRef;                // When ErrorNo==YD_ERROR_InvalidGroupOrderRef
	};
	YDSysOrderID BidOrderSysID;
	YDSysOrderID AskOrderSysID;
	YDRFQID RequestForQuoteID;
	int SessionID;
	YDLongOrderSysID LongQuoteSysID;
	YDLongOrderSysID LongBidOrderSysID;
	YDLongOrderSysID LongAskOrderSysID;
	YDLongRFQID LongRequestForQuoteID;
};

class YDCancelQuote
{
public:
	int SystemUse1;
	int SystemUse2;
	int SystemUse3;
	int SystemUse4;
	union
	{
		YDSysOrderID QuoteSysID;
		int OrderRef;                   // When OrderGroupID!=0
	};
	char SystemUse5;
	char ConnectionSelectionType;       // Refer to "Connection Selection Type" section of ydDataType.h
	char ConnectionID;                  // Target connection ID if ConnectionSelectionType is not YD_CS_Any
	unsigned char OrderGroupID;         // If OrderGroupID!=0, use (OrderGroupID,OrderRef) indicate an order
	YDLongOrderSysID LongQuoteSysID;
};

class YDFailedCancelQuote
{
public:
	int SystemUse1;
	int SystemUse2;
	int SystemUse3;
	int AccountRef;
	YDSysOrderID QuoteSysID;
	char ExchangeRef;
	unsigned char OrderGroupID;
	char SystemUse7;
	char SystemUse8;
	int ErrorNo;                        // Set by ydAPI, refer to "ydError.h"
	int IsQuote;
	int OrderRef;
	int SystemUse10;
	YDLongOrderSysID LongQuoteSysID;
};

class YDRequestForQuote
{
public:
	int SystemUse1;
	int SystemUse2;
	int SystemUse3;
	int SystemUse4;
	int InstrumentRef;
	int RequestTime;
	YDRFQID RequestForQuoteID;
	int SystemUse6;
	YDLongRFQID LongRequestForQuoteID;
};

class YDMarginRate
{
public:
	int SystemUse1;
	int SystemUse2;
	int SystemUse3;
	int SystemUse4;
	int HedgeFlag;                     // Refer to "Hedge Flag" section of ydDataType.h
	int SystemUse5;
	union 
	{
		double LongMarginRatioByMoney;
		double PutMarginRatioByMoney;
	};
	union
	{
		double LongMarginRatioByVolume;
		double PutMarginRatioByVolume;
		double BaseMarginRate;
	};
	union
	{
		double ShortMarginRatioByMoney;
		double CallMarginRatioByMoney;
		double LinearFactor;
	};
	union
	{
		double ShortMarginRatioByVolume;
		double CallMarginRatioByVolume;
		double LowerBoundaryCoef;
	};

	const YDInstrument *m_pInstrument;
	const YDProduct *m_pProduct;
	const YDAccount *m_pAccount;
};

class YDCommissionRate
{
public:
	int SystemUse1;
	int SystemUse2;
	int SystemUse3;
	int SystemUse4;
	int HedgeFlag;                     // Refer to "Hedge Flag" section of ydDataType.h
	int SystemUse5;
	double OpenRatioByMoney;
	double OpenRatioByVolume;
	double CloseRatioByMoney;
	double CloseRatioByVolume;
	double CloseTodayRatioByMoney;
	double CloseTodayRatioByVolume;
	double OrderCommByVolume;
	double OrderActionCommByVolume;
	double ExecRatioByMoney;
	double ExecRatioByVolume;
	const YDInstrument *m_pInstrument;
	const YDProduct *m_pProduct;
	const YDAccount *m_pAccount;
};

class YDCashCommissionRate
{
public:
	int SystemUse1;
	int SystemUse2;
	int SubProductClass;               // Refer to "Sub Product Class" section of ydDataType.h
	int SystemUse3;
	int SystemUse4;
	int SystemUse5;
	int YDOrderFlag;                   // Refer to "YD OrderFlag" section of ydDataType.h
	int Direction;
	YDCashCommissionRatePiece RatePiece[YD_CCT_Count];
	const YDInstrument *m_pInstrument;
	const YDProduct *m_pProduct;
	const YDExchange *m_pExchange;
	const YDAccount *m_pAccount;
};

class YDMessageCommissionRate
{
public:
	int SystemUse1;
	int SystemUse2;
	int SystemUse3;
	int SystemUse4;
	int ProductRef;
	int MessageCount;
	double OTR;
	double CommissionRate;
};

class YDMarginModelParam
{
public:
	int SystemUse1;
	int SystemUse2;
	int SystemUse3;
	int SystemUse4;
	int MarginModelID;
	int SystemUse5;
	char ParamName[256];
	char ParamValue[32];
};

class YDIDFromExchange
{
public:
	int SystemUse1;
	int SystemUse2;
	int SystemUse3;
	int AccountRef;
	int ExchangeRef;
	int IDType;                         // Refer to "IDType in IDFromExchange" section of ydDataType.h
	int IDInSystem;
	int SystemUse6;
	char IDFromExchange[24];
	YDLongOrderSysID LongIDInSystem;
};

class YDUpdateMarginRate
{
public:
	int SystemUse1;
	int SystemUse2;
	int SystemUse3;
	int AccountRef;
	int ProductRef;
	int InstrumentRef;
	int UnderlyingInstrumentRef;
	int HedgeFlagSet;
	int ExpireDate;
	int Multiple;
	int OptionTypeSet;
	int SystemUse4;
	union
	{
		double LongMarginRatioByMoney;
		double PutMarginRatioByMoney;
	};
	union
	{
		double LongMarginRatioByVolume;
		double PutMarginRatioByVolume;
		double BaseMarginRate;
	};
	union
	{
		double ShortMarginRatioByMoney;
		double CallMarginRatioByMoney;
		double LinearFactor;
	};
	union
	{
		double ShortMarginRatioByVolume;
		double CallMarginRatioByVolume;
		double LowerBoundaryCoef;
	};
};

class YDUpdateMessageCommissionConfig
{
public:
	int SystemUse1;
	int SystemUse2;
	int SystemUse3;
	int AccountRef;
	int ExchangeRef;
	int ProductRef;
	int InstrumentRef;
	int MaxMessage;
	int SystemUse4;
	int SystemUse5;
};

class YDAccountExchangeInfo
{
public:
	int SystemUse1;
	int AccountRef;
	int ExchangeRef;
	int TradingRight;                   // Refer to "Trade Right" section of ydDataType.h
	char TradingRightFromSource[YD_TRS_Count];
	int SystemUse2;
	bool IsDedicatedConnectionID[64];   // Whether this connectionID is dedicated for this account
	YDTradingCode TradingCode[YD_MaxHedgeFlag];
	const YDAccount *m_pAccount;
	const YDExchange *m_pExchange;
	mutable void *pUser;
	mutable double UserFloat;
	mutable int UserInt1;
	mutable int UserInt2;
	void *pInternalUse;
};

class YDAccountProductInfo
{
public:
	int SystemUse1;
	int AccountRef;
	int ProductRef;
	int TradingRight;                   // Refer to "Trade Right" section of ydDataType.h
	char TradingRightFromSource[YD_TRS_Count];
	int SystemUse2;
	YDTradeConstraint TradingConstraints[YD_MaxHedgeFlag];
	const YDAccount *m_pAccount;
	const YDProduct *m_pProduct;
	mutable void *pUser;
	mutable double UserFloat;
	mutable int UserInt1;
	mutable int UserInt2;
	void *pInternalUse;
};

class YDAccountInstrumentInfo
{
public:
	int SystemUse1;
	int AccountRef;
	int InstrumentRef;
	int TradingRight;					// Refer to "Trade Right" section of ydDataType.h
	unsigned short RFQCount;			// only valid for SHFE/INE options and message commission calculation is required, 0 for otherwise
	char ExemptMessageCommissionYDOrderFlag;	// don't calculate message commission if YDOrderFlag>ExemptMessageCommissionYDOrderFlag
	char SystemUse2;
	char TradingRightFromSource[YD_TRS_Count];
	int MaxMessage;
	int SystemUse3;
	YDTradeConstraint TradingConstraints[YD_MaxHedgeFlag];
	const YDAccount *m_pAccount;
	const YDInstrument *m_pInstrument;
	const YDMarginRate *m_pMarginRate[YD_MaxHedgeFlag];
	const YDCommissionRate *m_pCommissionRate[YD_MaxHedgeFlag];
	const YDCashCommissionRate *m_pCashCommissionRate[2];
	mutable void *pUser;
	mutable double UserFloat;
	mutable int UserInt1;
	mutable int UserInt2;
	void *pInternalUse;
};

class YDAccountMarginModelInfo
{
public:
	int SystemUse1;
	int SystemUse2;
	int SystemUse3;
	int AccountRef;
	int MarginModelID;
	int CloseVerify;
	double MarginRatio;
	char ProductRange[256];
	int SystemUse4;
	int SystemUse5;

	const YDAccount *m_pAccount;
	mutable void *pUser;
	mutable double UserFloat;
	mutable int UserInt1;
	mutable int UserInt2;
};

class YDGeneralRiskParam
{
public:
	int SystemUse1;
	int SystemUse2;
	int SystemUse3;
	int AccountRef;
	int GeneralRiskParamType;
	int ExtendedRef;
	double FloatValue;
	int IntValue1;
	int IntValue2;
};

class YDTradingSegmentDetail
{
public:
	int SystemUse1;
	int SystemUse2;
	int SystemUse3;
	int SystemUse4;
	short ExchangeRef;
	short ProductRef;
	int InstrumentRef;
	int SegmentTime;
	int TradingStatus;                  // Refer to "Trade Status" section of ydDataType.h
	const YDExchange *m_pExchange;
	const YDProduct *m_pProduct;
	const YDInstrument *m_pInstrument;
};

/// Data structs for YDExtendedApi

class YDExtendedOrder: public YDOrder
{
public:
	union
	{
		const YDInstrument *m_pInstrument;
		const YDCombPositionDef *m_pCombPositionDef;
	};
	const YDAccount *m_pAccount;
	const YDInstrument *m_pInstrument2;
};

class YDExtendedTrade: public YDTrade
{
public:
	const YDInstrument *m_pInstrument;
	const YDAccount *m_pAccount;
};

class YDExtendedQuote: public YDQuote
{
public:
	bool BidOrderFinished,AskOrderFinished;
	const YDInstrument *m_pInstrument;
	const YDAccount *m_pAccount;
};

class YDExtendedRequestForQuote: public YDRequestForQuote
{
public:
	const YDInstrument *m_pInstrument;
};

class YDExtendedAccount
{
public:
	double CloseProfit;
	double CashIn;
	double OtherCloseProfit;
	double Commission;
	double Margin;
	double PositionProfit;
	double Balance;
	double Available;
	unsigned UsedOrderCount;
	int Useless;
	const YDAccount *m_pAccount;
	double ExecMargin;
	double OptionLongPositionCost;
	double OptionLongPositionCostLimit;
	double PrePositionMarketValue;
	// Init value of PositionMarketValue is same as PrePositionMarketValue. It will only be changed after calling recalcPositionMarketValue()
	double PositionMarketValue;
	double ExecAllocatedAmount;
	double MessageCommission;

	double usable(void) const
	{
		if ((PositionProfit>0) && !(m_pAccount->AccountFlag&YD_AF_UsePositionProfit))
		{
			return Available;
		}
		else
		{
			return Available+PositionProfit;
		}
	}
	double useable(void) const
	{
		return usable();
	}
	bool canUse(double value) const
	{
		return usable()>value;
	}
	double staticCashBalance(void) const
	{
		return m_pAccount->PreBalance+m_pAccount->Deposit-m_pAccount->Withdraw;
	}
	double dynamicCashBalance(void) const
	{
		return CloseProfit+PositionProfit+CashIn-Commission;
	}
	double cashBalance(void) const
	{
		return staticCashBalance()*m_pAccount->MaxMoneyUsage+dynamicCashBalance();
	}
	double marketValue(void) const
	{
		return cashBalance()+PositionMarketValue;
	}
	double preCashBalance(void) const
	{
		return m_pAccount->PreBalance*m_pAccount->MaxMoneyUsage;
	}
	double preMarketValue(void) const
	{
		return preCashBalance()+PrePositionMarketValue;
	}
};

class YDExtendedPosition
{
public:
	class CPositionDetail
	{
	public:
		CPositionDetail *m_pNext;
		double Price;
		// TradeID<0 indicates history position
		union
		{
			YDTradeID TradeID;
			YDLongTradeID LongTradeID;
		};
		int Volume;
	};
	
	int PositionDate;
	int PositionDirection;
	int HedgeFlag;
	int Position;
	int OpenFrozen;
	int CloseFrozen;
	int ExecFrozen;
	int AbandonExecFrozen;
	int PositionByOrder;
	// Yesterday position used for commission calculation only, based on each exchange's commission rules.
	int YDPositionForCommission;
	int PossibleOpenVolume;
	int TotalCombPositions;
	double TotalOpenPrice;
	double Margin;
	double PositionProfit;
	// MarginPerlot is margin when price is preSettlementPrice
	double MarginPerLot;
	double CloseProfit;
	double OtherCloseProfit;
	const YDAccountInstrumentInfo *m_pAccountInstrumentInfo;
	CPositionDetail *PositionDetailList;
	void *Padding1;
	unsigned CombPositionCount;

	const YDAccount *getAccount(void) const
	{
		return m_pAccountInstrumentInfo->m_pAccount;
	}
	const YDInstrument *getInstrument(void) const
	{
		return m_pAccountInstrumentInfo->m_pInstrument;
	}
	const YDMarginRate *getMarginRate(void) const
	{
		return m_pAccountInstrumentInfo->m_pMarginRate[HedgeFlag-1];
	}
	const YDCommissionRate *getCommissionRate(void) const
	{
		return m_pAccountInstrumentInfo->m_pCommissionRate[HedgeFlag-1];
	}

	//DEPRECATED: This function is deprecated and will be remove in future release. Use getOpenPrice() instead
	double OpenPrice(void) const
	{
		return getOpenPrice();
	}

	double getOpenPrice(void) const
	{
		if (Position>0)
		{
			return TotalOpenPrice/Position;
		}
		else
		{
			return 0;
		}
	}

	// Return yesterday position calculated according to "first open, first close" rule
	int getYDPosition() const
	{
		int position=0;
		CPositionDetail *p=PositionDetailList;
		while (p && (p->LongTradeID<0))
		{
			position+=p->Volume;
			p = p->m_pNext;
		}
		return position;
	}
};

class YDExtendedHolding
{
public:
	const YDAccountInstrumentInfo *m_pAccountInstrumentInfo;
	YDHoldingPiece HoldingPiece[YD_CHT_Count];
	YDHoldingPiece TotalHolding;
	int ExternalSellFrozen;
	int SystemUse1;

	const YDAccount *getAccount(void) const
	{
		return m_pAccountInstrumentInfo->m_pAccount;
	}
	const YDInstrument *getInstrument(void) const
	{
		return m_pAccountInstrumentInfo->m_pInstrument;
	}
};

class YDExtendedSpotPosition
{
public:
	int Padding1;
	int Position;
	int ExchangeFrozenVolume;
	int ExecAllocatedVolume;
	double ExecAllocatedAmount;
	int CoveredVolume;
	int ExecVolume;
	const YDAccountInstrumentInfo *m_pAccountInstrumentInfo;

	const YDAccount *getAccount(void) const
	{
		return m_pAccountInstrumentInfo->m_pAccount;
	}
	const YDInstrument *getInstrument(void) const
	{
		return m_pAccountInstrumentInfo->m_pInstrument;
	}
};

class YDExtendedCombPositionDetail
{
public:
	const YDAccount *m_pAccount;
	const YDCombPositionDef *m_pCombPositionDef;
	int Position;
	int CombPositionDetailID;
};

class YDExtendedPositionFilter
{
public:
	/// -1 in following 3 fields indicates any
	int PositionDate;
	int PositionDirection;
	int HedgeFlag;

	/// NULL in following 4 fields indicates any
	const YDInstrument *pInstrument;
	const YDProduct *pProduct;
	const YDExchange *pExchange;
	const YDAccount *pAccount;
};

class YDExtendedHoldingFilter
{
public:
	/// NULL in following 4 fields indicates any
	const YDInstrument *pInstrument;
	const YDProduct *pProduct;
	const YDExchange *pExchange;
	const YDAccount *pAccount;
};

class YDExtendedSpotPositionFilter
{
public:
	/// NULL in following 4 fields indicates any
	const YDInstrument *pInstrument;
	const YDProduct *pProduct;
	const YDExchange *pExchange;
	const YDAccount *pAccount;
};

class YDOrderFilter
{
public:
	/// -1 in following 2 fields indicates any
	int StartTime;
	int EndTime;

	/// or of several (1<<YDOrderFlag)
	int YDOrderFlags;

	/// NULL in following 5 fields indicates any
	const YDCombPositionDef* pCombPositionDef;
	const YDInstrument *pInstrument;
	const YDProduct *pProduct;
	const YDExchange *pExchange;
	const YDAccount *pAccount;
};

class YDQuoteFilter
{
public:
	/// -1 in following 2 fields indicates any
	int StartTime;
	int EndTime;

	/// NULL in following 4 fields indicates any
	const YDInstrument *pInstrument;
	const YDProduct *pProduct;
	const YDExchange *pExchange;
	const YDAccount *pAccount;
};

class YDTradeFilter
{
public:
	/// -1 in following 2 fields indicates any
	int StartTime;
	int EndTime;

	/// NULL in following 4 fields indicates any
	const YDInstrument *pInstrument;
	const YDProduct *pProduct;
	const YDExchange *pExchange;
	const YDAccount *pAccount;
};

class YDCombPositionDetailFilter
{
public:
	/// NULL or 0 in following 4 fields indicates any
	const YDCombPositionDef *pCombPositionDef;
	const YDAccount *pAccount;
	/// if following 2 fields are specified, it should match one leg of this combination position
	const YDInstrument *pInstrument;
	int PositionDirection;
	/// if IncludeSplit is false, only current valid combPositions are included
	bool IncludeSplit;
};

template<class T> class YDQueryResult
{
protected:
	virtual ~YDQueryResult(void)
	{
	}
public:
	virtual int getCount(void) const=0;
	virtual const T *get(int pos) const=0;
	virtual void destroy(void)=0;
};


#endif
