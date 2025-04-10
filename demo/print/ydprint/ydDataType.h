#ifndef YD_DATA_TYPE_H
#define YD_DATA_TYPE_H

#include <stdio.h>

typedef char YDExchangeID[12];
typedef char YDProductID[32];
typedef char YDInstrumentID[32];
typedef char YDLongInstrumentID[64];
typedef char YDTradingCode[24];
typedef char YDAccountID[16];
typedef char YDPassword[16];
typedef char YDString[32];

typedef int YDSysOrderID;
typedef int YDTradeID;
typedef int YDLocalOrderID;
typedef int YDRFQID;

typedef long long YDLongOrderSysID;
typedef long long YDLongTradeID;
typedef long long YDLongRFQID;

// Product Class
const int YD_PC_Futures=1;
const int YD_PC_Options=2;
const int YD_PC_Combination=3;
const int YD_PC_Index=4;
const int YD_PC_Cash=5;

// Sub Product Class
const int YD_SPC_Other=0;
const int YD_SPC_Stock=1;
const int YD_SPC_Bond=2;
const int YD_SPC_Fund=3;

// Options Type
const int YD_OT_NotOption=0;
const int YD_OT_CallOption=1;
const int YD_OT_PutOption=2;

// Direction
// Directions is most situations
const int YD_D_Buy=0;
const int YD_D_Sell=1;
// Directions when YDOrderFlag is YD_YOF_CombPosition
const int YD_D_Make=0;
const int YD_D_Split=1;
// Directions when YDOrderFlag is YD_YOF_FreezeUnderlying
const int YD_D_Freeze=0;
const int YD_D_Unfreeze=1;
// Directions when YDOrderFlag is YD_YOF_Cover
const int YD_D_Normal2Covered=0;
const int YD_D_Covered2Normal=1;

// Position Direction
const int YD_PD_Long=2;
const int YD_PD_Short=3;

// Position Date
const int YD_PSD_Today=1;
const int YD_PSD_History=2;

// Hedge Flag
// following hedge flags are used in futures exchanges
const int YD_HF_Speculation=1;
const int YD_HF_Arbitrage=2;
const int YD_HF_Hedge=3;
const int YD_HF_Internal=4;
// following hedge flags are used in stock exchanges
const int YD_HF_Normal=1;
const int YD_HF_Covered=3;

const int YD_MaxHedgeFlag=4;

// Trade Right
const int YD_TR_Allow=0;
const int YD_TR_CloseOnly=1;
const int YD_TR_Forbidden=2;

// Offset Flag
const int YD_OF_Open=0;
const int YD_OF_Close=1;
const int YD_OF_ForceClose=2;
const int YD_OF_CloseToday=3;
const int YD_OF_CloseYesterday=4;
/// For SHFE and INE, only YD_OF_CloseYesterday and YD_OF_CloseToday are valid for close. For all other exchanges, only YD_OF_Close is valid for close
const int YD_OF_Open1Close2=5;
const int YD_OF_Close1Open2=6;
/// YD_OF_Open1Close2 and YD_OF_Close1Open2 can only be used for combination instrument trading

// Order Type
// following order types can be used when ydOrderFlag is YD_YOF_Normal
const int YD_ODT_Limit=0;
const int YD_ODT_FAK=1;
const int YD_ODT_Market=2;
const int YD_ODT_FOK=3;
// following order types can be used when ydOrderFlag is YD_YOF_OptionSelfClose
const int YD_ODT_CloseSelfOptionPosition=0;
const int YD_ODT_ReserveOptionPosition=1;
const int YD_ODT_SellCloseSelfFuturesPosition=2;
// following order types can be used when ydOrderFlag is YD_YOF_Mark
const int YD_ODT_PositionOffsetMark=0;
const int YD_ODT_OptionAbandonExecuteMark=1;
const int YD_ODT_CloseFuturesPositionMark=2;

// Order trigger type
const int YD_OTT_NoTrigger=0;
const int YD_OTT_TakeProfit=1;
const int YD_OTT_StopLoss=2;

// Exchange Order Attribute
const int YD_EOA_DCE_GIS=1;

// Order group ref control
const int YD_GORF_Increase=0;
const int YD_GORF_IncreaseOne=1;

// Order Status
const int YD_OS_Accepted=0;
const int YD_OS_Queuing=1;
const int YD_OS_Canceled=2;
const int YD_OS_AllTraded=3;
const int YD_OS_Rejected=4;

// Order trigger status
const int YD_OTS_NotTriggered=0;
const int YD_OTS_Triggered=1;

// YD OrderFlag
const int YD_YOF_Normal=0;
const int YD_YOF_QuoteDerived=1;			// YD_YOF_QuoteDerived is for derived orders from quotes, can not be used when insert order
const int YD_YOF_OptionExecute=2;			// YD_YOF_OptionExecute can be used in SHFE,INE,DCE,CZCE,GFEX
const int YD_YOF_OptionAbandonExecute=3;	// YD_YOF_OptionAbandonExecute can be used in SHFE,INE,CZCE
const int YD_YOF_RequestForQuote=4;			// YD_YOF_RequestForQuote can be used in SHFE,INE,CFFEX,DCE,CZCE,GFEX
const int YD_YOF_CombPosition=5;			// YD_YOF_CombPosition can be used in DCE,SSE,SZSE,GFEX
const int YD_YOF_OptionExecuteTogether=6;	// YD_YOF_OptionExecuteTogether can be used in SSE,SZSE
const int YD_YOF_Mark=7;					// YD_YOF_Mark can be used in DCE,GFEX
const int YD_YOF_OptionSelfClose=8;			// YD_YOF_OptionSelfClose can be used in SHFE,INE
const int YD_YOF_FreezeUnderlying=9;		// YD_YOF_FreezeUnderlying can can be used in SSE
const int YD_YOF_Cover=10;					// YD_YOF_Cover can be used in SSE,SZSE

// YD QuoteFlag, can be bitwise or of following flags
const int YD_YQF_ResponseOfRFQ=1;
const int YD_YQF_ReplaceLastQuote=2;

// Combine Hedge Flag
const int YD_CHF_SpecSpec=1;
const int YD_CHF_SpecHedge=2;
const int YD_CHF_HedgeHedge=3;
const int YD_CHF_HedgeSpec=4;

const int YD_MaxCombHedgeFlag=4;

// DCE Combine Position Types
const int YD_CPT_DCE_FuturesOffset=0;
const int YD_CPT_DCE_OptionsOffset=1;
const int YD_CPT_DCE_FuturesCalendarSpread=2;
const int YD_CPT_DCE_FuturesProductSpread=3;
const int YD_CPT_DCE_BuyOptionsVerticalSpread=4;
const int YD_CPT_DCE_SellOptionsVerticalSpread=5;
const int YD_CPT_DCE_OptionsStraddle=7;
const int YD_CPT_DCE_OptionsStrangle=8;
const int YD_CPT_DCE_BuyOptionsCovered=9;
const int YD_CPT_DCE_SellOptionsCovered=10;

// GFEX Combine Position Types
const int YD_CPT_GFEX_FuturesOffset=0;
const int YD_CPT_GFEX_OptionsOffset=1;
const int YD_CPT_GFEX_FuturesCalendarSpread=2;
const int YD_CPT_GFEX_FuturesProductSpread=3;
const int YD_CPT_GFEX_BuyOptionsVerticalSpread=4;
const int YD_CPT_GFEX_SellOptionsVerticalSpread=5;
const int YD_CPT_GFEX_OptionsStraddle=7;
const int YD_CPT_GFEX_OptionsStrangle=8;
const int YD_CPT_GFEX_BuyOptionsCovered=9;
const int YD_CPT_GFEX_SellOptionsCovered=10;

// CZCE Combinde PositionTypes
const int YD_CPT_CZCE_Spread=50;
const int YD_CPT_CZCE_StraddleStrangle=51;
const int YD_CPT_CZCE_SellOptionConvered=52;

// SSE/SZSE Combine Position Types
const int YD_CPT_StockOption_CNSJC=100;
const int YD_CPT_StockOption_CXSJC=101;
const int YD_CPT_StockOption_PNSJC=102;
const int YD_CPT_StockOption_PXSJC=103;
const int YD_CPT_StockOption_KS=104;
const int YD_CPT_StockOption_KKS=105;

// Connection Selection Type
const int YD_CS_Any=0;
const int YD_CS_Fixed=1;
const int YD_CS_Prefered=2;

// Alter Money Type
const int YD_AM_ModifyUsage=0;
const int YD_AM_Deposit=1;
const int YD_AM_FrozenWithdraw=2;
const int YD_AM_CancelFrozenWithdraw=3;
const int YD_AM_Withdraw=4;
const int YD_AM_DepositTo=5;
const int YD_AM_WithdrawTo=6;
const int YD_AM_ForceModifyUsage=7;

// Request Type
const int YD_RT_ChangePassword=0;
const int YD_RT_SetTradingRight=1;
const int YD_RT_AlterMoney=2;
const int YD_RT_SelectConnection=3;
const int YD_RT_AdminTrading=4;
const int YD_RT_UpdateMarginRate=5;
const int YD_RT_UpdateSpotPosition=6;
const int YD_RT_UpdateSpotAlive=7;
const int YD_RT_AdjustAccountMarginModelInfo=8;
const int YD_RT_UpdateMessageCommissionConfig=9;
const int YD_RT_UpdateHoldingExternalFrozen=10;

// API Event
const int YD_AE_TCPTradeConnected=0;
const int YD_AE_TCPTradeDisconnected=1;
const int YD_AE_TCPMarketDataConnected=2;
const int YD_AE_TCPMarketDataDisconnected=3;
const int YD_AE_ServerRestarted=4;
const int YD_AE_ServerSwitched=5;
const int YD_AE_XTCPTradeConnected=6;
const int YD_AE_XTCPTradeDisconnected=7;

// Account Flag
const int YD_AF_SelectConnection=1;
const int YD_AF_AutoMakeCombPosition=2;
const int YD_AF_RawProtocol=4;
const int YD_AF_DisableSelfTradeCheck=8;
const int YD_AF_NotifyOrderAccept=16;
const int YD_AF_NoCloseFrozenOnInsertOrder=32;
const int YD_AF_OrderRefCheck=64;
const int YD_AF_UsePositionProfit=128;

// Margin and Premium Calculation Base Price Type
const int YD_CBT_PreSettlementPrice=0;
const int YD_CBT_OpenPrice=1;
const int YD_CBT_LastPrice=2;
const int YD_CBT_MarketAveragePrice=3;
const int YD_CBT_MaxLastPreSettlementPrice=4;
const int YD_CBT_OrderPrice=5;
const int YD_CBT_None=6;
const int YD_CBT_SamePrice=7;

// IDType in IDFromExchange
const int YD_IDT_NormalOrderSysID=0;
const int YD_IDT_QuoteDerivedOrderSysID=1;
const int YD_IDT_OptionExecuteOrderSysID=2;
const int YD_IDT_OptionAbandonExecuteOrderSysID=3;
const int YD_IDT_RequestForQuoteOrderSysID=4;
const int YD_IDT_CombPositionOrderSysID=5;
const int YD_IDT_OptionExecuteTogether=6;
const int YD_IDT_Mark=7;
const int YD_IDT_OptionSelfClose=8;
const int YD_IDT_FreezeUnderlying=9;
const int YD_IDT_Cover=10;
const int YD_IDT_TradeID=128;
const int YD_IDT_CombPositionDetailID=129;
const int YD_IDT_QuoteSysID=130;

// General Risk Param Types
const int YD_GRPT_OptionLongPositionCost=1;
const int YD_GRPT_TradePositionRatio=2;
const int YD_GRPT_OrderCancelRatio=3;
const int YD_GRPT_DynamicPriceLimitUpperRatio=4;
const int YD_GRPT_DynamicPriceLimitLowerRatio=5;
const int YD_GRPT_DynamicPriceLimitUpperTickCount=6;
const int YD_GRPT_DynamicPriceLimitLowerTickCount=7;
const int YD_GRPT_DynamicLastPriceLimitUpperRatio=8;
const int YD_GRPT_DynamicLastPriceLimitLowerRatio=9;
const int YD_GRPT_DynamicLastPriceLimitUpperTickCount=10;
const int YD_GRPT_DynamicLastPriceLimitLowerTickCount=11;
const int YD_GRPT_ExchangeMaxOrderVolume=12;
const int YD_GRPT_ProductMaxOrderVolume=13;
const int YD_GRPT_InstrumentMaxOrderVolume=14;
const int YD_GRPT_ExchangeOptionLongPositionCost=15;
const int YD_GRPT_ExchangeSTBuyVolume=16;
const int YD_GRPT_ProductSTBuyVolume=17;
const int YD_GRPT_ExchangeBuyVolume=18;
const int YD_GRPT_ProductBuyVolume=19;
const int YD_GRPT_InstrumentBuyVolume=20;
const int YD_GRPT_ExchangeCashTradingRight=21;
const int YD_GRPT_ProductCashTradingRight=22;
const int YD_GRPT_InstrumentCashTradingRight=23;
const int YD_GRPT_ExchangeHoldingLimit=24;
const int YD_GRPT_ProductHoldingLimit=25;
const int YD_GRPT_InstrumentHoldingLimit=26;
const int YD_GRPT_TradeST=27;
const int YD_GRPT_TradeStarST=28;
const int YD_GRPT_QualifiedBondInvestor=29;
const int YD_GRPT_QualifiedBondCorpInvestor=30;

// Trading Right Source
const int YD_TRS_AdminPermanent=0;
const int YD_TRS_UserPermanent=1;
const int YD_TRS_AdminTemp=2;
const int YD_TRS_UserTemp=3;
// YD_TRS_Count is not a valid trading right source
const int YD_TRS_Count=4;

// Trading Status
const int YD_TS_NoTrading=0;
const int YD_TS_Continuous=1;
const int YD_TS_Auction=2;

// Margin Model ID
const int YD_MM_Normal=0;
const int YD_MM_SPBM=1;
const int YD_MM_RULE=2;

const int YD_MM_NewModelStart=1;
const int YD_MM_Count=3;

// Close Verify
const int YD_CV_Verify=0;
const int YD_CV_NotVerify=1;

// Exchange Flag
const int YD_EF_SHFE=0x01;
const int YD_EF_DCE=0x02;
const int YD_EF_CZCE=0x04;
const int YD_EF_CFFEX=0x08;
const int YD_EF_INE=0x10;
const int YD_EF_SSE_OPTION=0x20;
const int YD_EF_SZSE_OPTION=0x40;
const int YD_EF_GFEX=0x80;
const int YD_EF_SSE_CASH=0x100;
const int YD_EF_SZSE_CASH=0x200;

// Exchange Connection Status
const int YD_ECS_DISCONNECTED=0;
const int YD_ECS_CONNECTED=1;

// Cash Trading Holding Type
const int YD_CHT_History=0;
const int YD_CHT_TodayTrading=1;
const int YD_CHT_TodayCreationRedemption=2;
const int YD_CHT_Count=3;

class YDHoldingPiece
{
public:
	int Holding;
	int BuyFrozen;
	int SellFrozen;
	int SystemUse;
	double TotalCost;
	double BuyFrozenCost;
	double AverageCost(int multiple=1) const
	{
		if (Holding<=0)
		{
			return 0;
		}
		else
		{
			return TotalCost/Holding/multiple;
		}
	}
	int MaxPossibleHolding(void) const
	{
		return Holding+BuyFrozen;
	}
	int MaxPossibleSellVolume(void) const
	{
		return Holding-SellFrozen;
	}
	double MaxPossibleCost(void) const
	{
		return TotalCost+BuyFrozenCost;
	}
};

// Cash Commission Type
const int YD_CCT_StampDuty=0;
const int YD_CCT_SecuritiesManagementFee=1;
const int YD_CCT_HandlingFee=2;
const int YD_CCT_TransferFee=3;
const int YD_CCT_BrokerageFee=4;
const int YD_CCT_Count=5;

class YDCashCommissionRatePiece
{
public:
	double RateByAmount;
	double RateByVolume;
	double MaxValue;
	double MinValue;
};

// Cash Instrument Flag
const int YD_CIF_SupportDayTrading=0x01;
const int YD_CIF_SupportTrading=0x02;
const int YD_CIF_SupportCreationRedemption=0x04;
const int YD_CIF_IsRepo=0x08;

// Trade Control Flag
const int YD_TCF_ST=0x01;
const int YD_TCF_StarST=0x02;
const int YD_TCF_QualifiedBondInvestor=0x04;
const int YD_TCF_QualifiedBondCorpInvestor=0x08;

// Market Data Flag
const int YD_MDF_PauseTrading=0x01;

// get the opposite position direction
inline int oppositePositionDirection(int positiondir)
{
	return YD_PD_Long+YD_PD_Short-positiondir;
}

#endif
