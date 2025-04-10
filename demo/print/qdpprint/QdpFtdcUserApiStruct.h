/////////////////////////////////////////////////////////////////////////
///@system QuantDo Platform
///@company 上海量投网络科技有限公司
///@file QdpFtdcUserApiStruct.h
///@brief 定义了客户端接口使用的业务数据结构
///@history 
/////////////////////////////////////////////////////////////////////////

#if !defined(Qdp_FTDCSTRUCT_H)
#define Qdp_FTDCSTRUCT_H

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "QdpFtdcUserApiDataType.h"

///系统用户登录请求
struct CQdpFtdcReqUserLoginField
{
	///交易日
	TQdpFtdcDateType	TradingDay;
	///交易用户代码
	TQdpFtdcUserIDType	UserID;
	///经纪公司编号
	TQdpFtdcBrokerIDType	BrokerID;
	///密码
	TQdpFtdcPasswordType	Password;
	///用户端产品信息
	TQdpFtdcProductInfoType	UserProductInfo;
	///接口端产品信息
	TQdpFtdcProductInfoType	InterfaceProductInfo;
	///协议信息
	TQdpFtdcProtocolInfoType	ProtocolInfo;
	///IP地址
	TQdpFtdcIPAddressType	IPAddress;
	///Mac地址
	TQdpFtdcMacAddressType	MacAddress;
	///数据中心代码
	TQdpFtdcDataCenterIDType	DataCenterID;
	///动态密码
	TQdpFtdcPasswordType	OneTimePassword;
	///终端IP地址
	TQdpFtdcIPAddressType	ClientIPAddress;
};

///系统用户登录应答
struct CQdpFtdcRspUserLoginField
{
	///交易日
	TQdpFtdcDateType	TradingDay;
	///经纪公司编号
	TQdpFtdcBrokerIDType	BrokerID;
	///交易用户代码
	TQdpFtdcUserIDType	UserID;
	///登录成功时间
	TQdpFtdcTimeType	LoginTime;
	///用户最大本地报单号
	TQdpFtdcUserOrderLocalIDType	MaxOrderLocalID;
	///交易系统名称
	TQdpFtdcTradingSystemNameType	TradingSystemName;
	///数据中心代码
	TQdpFtdcDataCenterIDType	DataCenterID;
	///会员私有流当前长度
	TQdpFtdcSequenceNoType	PrivateFlowSize;
	///交易员私有流当前长度
	TQdpFtdcSequenceNoType	UserFlowSize;
	///会话编号
	TQdpFtdcSessionIDType	SessionID;
	///前置编号
	TQdpFtdcFrontIDType	FrontID;
};

///用户登出请求
struct CQdpFtdcReqUserLogoutField
{
	///经纪公司编号
	TQdpFtdcBrokerIDType	BrokerID;
	///交易用户代码
	TQdpFtdcUserIDType	UserID;
	///Session退出原因
	TQdpFtdcNumberType	LogoutReason;
};

///用户登出请求
struct CQdpFtdcRspUserLogoutField
{
	///经纪公司编号
	TQdpFtdcBrokerIDType	BrokerID;
	///交易用户代码
	TQdpFtdcUserIDType	UserID;
	///Session退出原因
	TQdpFtdcNumberType	LogoutReason;
};

///强制用户退出
struct CQdpFtdcForceUserExitField
{
	///经纪公司编号
	TQdpFtdcBrokerIDType	BrokerID;
	///交易用户代码
	TQdpFtdcUserIDType	UserID;
};

///用户口令修改
struct CQdpFtdcUserPasswordUpdateField
{
	///经纪公司编号
	TQdpFtdcBrokerIDType	BrokerID;
	///交易用户代码
	TQdpFtdcUserIDType	UserID;
	///旧密码
	TQdpFtdcPasswordType	OldPassword;
	///新密码
	TQdpFtdcPasswordType	NewPassword;
};

///输入报单
struct CQdpFtdcInputOrderField
{
	///经纪公司编号
	TQdpFtdcBrokerIDType	BrokerID;
	///交易所代码
	TQdpFtdcExchangeIDType	ExchangeID;
	///系统报单编号
	TQdpFtdcOrderSysIDType	OrderSysID;
	///投资者编号
	TQdpFtdcInvestorIDType	InvestorID;
	///用户代码
	TQdpFtdcUserIDType	UserID;
	///合约代码
	TQdpFtdcInstrumentIDType	InstrumentID;
	///用户本地报单号
	TQdpFtdcUserOrderLocalIDType	UserOrderLocalID;
	///价格类型
	TQdpFtdcOrderPriceTypeType	OrderPriceType;
	///买卖方向
	TQdpFtdcDirectionType	Direction;
	///开平标志
	TQdpFtdcOffsetFlagType	OffsetFlag;
	///投机套保标志
	TQdpFtdcHedgeFlagType	HedgeFlag;
	///价格
	TQdpFtdcPriceType	LimitPrice;
	///数量
	TQdpFtdcVolumeType	Volume;
	///有效期类型
	TQdpFtdcTimeConditionType	TimeCondition;
	///GTD日期
	TQdpFtdcDateType	GTDDate;
	///成交量类型
	TQdpFtdcVolumeConditionType	VolumeCondition;
	///最小成交量
	TQdpFtdcVolumeType	MinVolume;
	///止损价
	TQdpFtdcPriceType	StopPrice;
	///强平原因
	TQdpFtdcForceCloseReasonType	ForceCloseReason;
	///自动挂起标志
	TQdpFtdcBoolType	IsAutoSuspend;
	///业务单元
	TQdpFtdcBusinessUnitType	BusinessUnit;
	///用户自定义域
	TQdpFtdcCustomType	UserCustom;
	///营业部代码
	TQdpFtdcBranchIDType	BranchID;
	///记录编号
	TQdpFtdcSequenceNoType	RecNum;
	///业务类别
	TQdpFtdcBusinessTypeType	BusinessType;
};

///报单操作
struct CQdpFtdcOrderActionField
{
	///交易所代码
	TQdpFtdcExchangeIDType	ExchangeID;
	///报单编号
	TQdpFtdcOrderSysIDType	OrderSysID;
	///经纪公司编号
	TQdpFtdcBrokerIDType	BrokerID;
	///投资者编号
	TQdpFtdcInvestorIDType	InvestorID;
	///用户代码
	TQdpFtdcUserIDType	UserID;
	///合约代码
	TQdpFtdcInstrumentIDType	InstrumentID;
	///本次撤单操作的本地编号
	TQdpFtdcUserOrderLocalIDType	UserOrderActionLocalID;
	///被撤订单的本地报单编号
	TQdpFtdcUserOrderLocalIDType	UserOrderLocalID;
	///报单操作标志
	TQdpFtdcActionFlagType	ActionFlag;
	///价格
	TQdpFtdcPriceType	LimitPrice;
	///数量变化
	TQdpFtdcVolumeType	VolumeChange;
	///记录编号
	TQdpFtdcSequenceNoType	RecNum;
	///前置编号
	TQdpFtdcFrontIDType	FrontID;
	///会话编号
	TQdpFtdcSessionIDType	SessionID;
};

///内存表导出
struct CQdpFtdcMemDbField
{
	///内存表名
	TQdpFtdcMemTableNameType	MemTableName;
};

///投资者资金帐户出入金请求
struct CQdpFtdcReqAccountDepositField
{
	///经纪公司编号
	TQdpFtdcBrokerIDType	BrokerID;
	///资金流水号
	TQdpFtdcAccountSeqNoType	AccountSeqNo;
	///资金帐号
	TQdpFtdcAccountIDType	AccountID;
	///连续递增的总资金流水号
	TQdpFtdcAccountSeqNoType	AccountInsideSeqNo;
	///投资者编号
	TQdpFtdcInvestorIDType	InvestorID;
	///金额
	TQdpFtdcMoneyType	Amount;
	///出入金方向
	TQdpFtdcAccountDirectionType	AmountDirection;
	///用户代码
	TQdpFtdcUserIDType	UserID;
};

///投资者资金帐户出入金应答
struct CQdpFtdcRspAccountDepositField
{
	///经纪公司编号
	TQdpFtdcBrokerIDType	BrokerID;
	///投资者编号
	TQdpFtdcInvestorIDType	InvestorID;
	///资金帐号
	TQdpFtdcAccountIDType	AccountID;
	///资金流水号
	TQdpFtdcAccountSeqNoType	AccountSeqNo;
	///连续递增的总资金流水号
	TQdpFtdcAccountSeqNoType	AccountInsideSeqNo;
	///金额
	TQdpFtdcMoneyType	Amount;
	///出入金方向
	TQdpFtdcAccountDirectionType	AmountDirection;
	///可用资金
	TQdpFtdcMoneyType	Available;
	///结算准备金
	TQdpFtdcMoneyType	Balance;
	///用户代码
	TQdpFtdcUserIDType	UserID;
};

///输入报单
struct CQdpFtdcUdpInputOrderField
{
	///经纪公司编号
	TQdpFtdcBrokerIDUdpType	BrokerID;
	///交易所代码
	TQdpFtdcExchangeIDUdpType	ExchangeID;
	///投资者编号
	TQdpFtdcInvestorIDUdpType	InvestorID;
	///用户代码
	TQdpFtdcUserIDUdpType	UserID;
	///合约代码
	TQdpFtdcInstrumentIDUdpType	InstrumentID;
	///用户本地报单号
	TQdpFtdcUserOrderLocalIDType	UserOrderLocalID;
	///价格类型
	TQdpFtdcOrderPriceTypeType	OrderPriceType;
	///买卖方向
	TQdpFtdcDirectionType	Direction;
	///开平标志
	TQdpFtdcOffsetFlagType	OffsetFlag;
	///投机套保标志
	TQdpFtdcHedgeFlagType	HedgeFlag;
	///价格
	TQdpFtdcPriceType	LimitPrice;
	///数量
	TQdpFtdcVolumeType	Volume;
	///有效期类型
	TQdpFtdcTimeConditionType	TimeCondition;
	///成交量类型
	TQdpFtdcVolumeConditionType	VolumeCondition;
	///营业部代码
	TQdpFtdcBranchIDType	BranchID;
	///止损价
	TQdpFtdcPriceType	StopPrice;
	///用户自定义域
	TQdpFtdcUdpCustomType	UserCustom;
};

///客户信息量阈值
struct CQdpFtdcClientMaxSigVolField
{
	///经纪公司编号
	TQdpFtdcBrokerIDType	BrokerID;
	///交易所代码
	TQdpFtdcExchangeIDType	ExchangeID;
	///投资者编码
	TQdpFtdcInvestorIDType	InvestorID;
	///投机套保标志
	TQdpFtdcHedgeFlagType	HedgeFlag;
	///合约代码
	TQdpFtdcInstrumentIDType	InstrumentID;
	///最大信号量
	TQdpFtdcVolumeType	MaxSigVol;
};

///响应信息
struct CQdpFtdcRspInfoField
{
	///错误代码
	TQdpFtdcErrorIDType	ErrorID;
	///错误信息
	TQdpFtdcErrorMsgType	ErrorMsg;
};

///报单查询
struct CQdpFtdcQryOrderField
{
	///经纪公司编号
	TQdpFtdcBrokerIDType	BrokerID;
	///用户代码
	TQdpFtdcUserIDType	UserID;
	///交易所代码
	TQdpFtdcExchangeIDType	ExchangeID;
	///投资者编号
	TQdpFtdcInvestorIDType	InvestorID;
	///报单编号
	TQdpFtdcOrderSysIDType	OrderSysID;
	///合约代码
	TQdpFtdcInstrumentIDType	InstrumentID;
};

///成交查询
struct CQdpFtdcQryTradeField
{
	///经纪公司编号
	TQdpFtdcBrokerIDType	BrokerID;
	///用户代码
	TQdpFtdcUserIDType	UserID;
	///交易所代码
	TQdpFtdcExchangeIDType	ExchangeID;
	///投资者编号
	TQdpFtdcInvestorIDType	InvestorID;
	///成交编号
	TQdpFtdcTradeIDType	TradeID;
	///合约代码
	TQdpFtdcInstrumentIDType	InstrumentID;
};

///合约查询
struct CQdpFtdcQryInstrumentField
{
	///交易所代码
	TQdpFtdcExchangeIDType	ExchangeID;
	///品种代码
	TQdpFtdcProductIDType	ProductID;
	///合约代码
	TQdpFtdcInstrumentIDType	InstrumentID;
};

///合约查询应答
struct CQdpFtdcRspInstrumentField
{
	///交易所代码
	TQdpFtdcExchangeIDType	ExchangeID;
	///品种代码
	TQdpFtdcProductIDType	ProductID;
	///品种名称
	TQdpFtdcProductNameType	ProductName;
	///合约代码
	TQdpFtdcInstrumentIDType	InstrumentID;
	///合约名称
	TQdpFtdcInstrumentNameType	InstrumentName;
	///交割年份
	TQdpFtdcYearType	DeliveryYear;
	///交割月
	TQdpFtdcMonthType	DeliveryMonth;
	///限价单最大下单量
	TQdpFtdcVolumeType	MaxLimitOrderVolume;
	///限价单最小下单量
	TQdpFtdcVolumeType	MinLimitOrderVolume;
	///市价单最大下单量
	TQdpFtdcVolumeType	MaxMarketOrderVolume;
	///市价单最小下单量
	TQdpFtdcVolumeType	MinMarketOrderVolume;
	///数量乘数
	TQdpFtdcVolumeMultipleType	VolumeMultiple;
	///报价单位
	TQdpFtdcPriceTickType	PriceTick;
	///币种
	TQdpFtdcCurrencyType	Currency;
	///多头限仓
	TQdpFtdcVolumeType	LongPosLimit;
	///空头限仓
	TQdpFtdcVolumeType	ShortPosLimit;
	///跌停板价
	TQdpFtdcPriceType	LowerLimitPrice;
	///涨停板价
	TQdpFtdcPriceType	UpperLimitPrice;
	///昨结算
	TQdpFtdcPriceType	PreSettlementPrice;
	///合约交易状态
	TQdpFtdcInstrumentStatusType	InstrumentStatus;
	///创建日
	TQdpFtdcDateType	CreateDate;
	///上市日
	TQdpFtdcDateType	OpenDate;
	///到期日
	TQdpFtdcDateType	ExpireDate;
	///开始交割日
	TQdpFtdcDateType	StartDelivDate;
	///最后交割日
	TQdpFtdcDateType	EndDelivDate;
	///挂牌基准价
	TQdpFtdcPriceType	BasisPrice;
	///当前是否交易
	TQdpFtdcBoolType	IsTrading;
	///基础商品代码
	TQdpFtdcInstrumentIDType	UnderlyingInstrID;
	///基础商品乘数
	TQdpFtdcUnderlyingMultipleType	UnderlyingMultiple;
	///持仓类型
	TQdpFtdcPositionTypeType	PositionType;
	///执行价
	TQdpFtdcPriceType	StrikePrice;
	///期权类型
	TQdpFtdcOptionsTypeType	OptionsType;
	///产品类型
	TQdpFtdcProductClassType	ProductClass;
	///期权行权方式
	TQdpFtdcOptionsModeType	OptionsMode;
};

///合约状态
struct CQdpFtdcInstrumentStatusField
{
	///交易所代码
	TQdpFtdcExchangeIDType	ExchangeID;
	///品种代码
	TQdpFtdcProductIDType	ProductID;
	///品种名称
	TQdpFtdcProductNameType	ProductName;
	///合约代码
	TQdpFtdcInstrumentIDType	InstrumentID;
	///合约名称
	TQdpFtdcInstrumentNameType	InstrumentName;
	///交割年份
	TQdpFtdcYearType	DeliveryYear;
	///交割月
	TQdpFtdcMonthType	DeliveryMonth;
	///限价单最大下单量
	TQdpFtdcVolumeType	MaxLimitOrderVolume;
	///限价单最小下单量
	TQdpFtdcVolumeType	MinLimitOrderVolume;
	///市价单最大下单量
	TQdpFtdcVolumeType	MaxMarketOrderVolume;
	///市价单最小下单量
	TQdpFtdcVolumeType	MinMarketOrderVolume;
	///数量乘数
	TQdpFtdcVolumeMultipleType	VolumeMultiple;
	///报价单位
	TQdpFtdcPriceTickType	PriceTick;
	///币种
	TQdpFtdcCurrencyType	Currency;
	///多头限仓
	TQdpFtdcVolumeType	LongPosLimit;
	///空头限仓
	TQdpFtdcVolumeType	ShortPosLimit;
	///跌停板价
	TQdpFtdcPriceType	LowerLimitPrice;
	///涨停板价
	TQdpFtdcPriceType	UpperLimitPrice;
	///昨结算
	TQdpFtdcPriceType	PreSettlementPrice;
	///合约交易状态
	TQdpFtdcInstrumentStatusType	InstrumentStatus;
	///创建日
	TQdpFtdcDateType	CreateDate;
	///上市日
	TQdpFtdcDateType	OpenDate;
	///到期日
	TQdpFtdcDateType	ExpireDate;
	///开始交割日
	TQdpFtdcDateType	StartDelivDate;
	///最后交割日
	TQdpFtdcDateType	EndDelivDate;
	///挂牌基准价
	TQdpFtdcPriceType	BasisPrice;
	///当前是否交易
	TQdpFtdcBoolType	IsTrading;
	///基础商品代码
	TQdpFtdcInstrumentIDType	UnderlyingInstrID;
	///基础商品乘数
	TQdpFtdcUnderlyingMultipleType	UnderlyingMultiple;
	///持仓类型
	TQdpFtdcPositionTypeType	PositionType;
	///执行价
	TQdpFtdcPriceType	StrikePrice;
	///期权类型
	TQdpFtdcOptionsTypeType	OptionsType;
	///产品类型
	TQdpFtdcProductClassType	ProductClass;
	///期权行权方式
	TQdpFtdcOptionsModeType	OptionsMode;
};

///投资者资金查询
struct CQdpFtdcQryInvestorAccountField
{
	///经纪公司编号
	TQdpFtdcBrokerIDType	BrokerID;
	///用户代码
	TQdpFtdcUserIDType	UserID;
	///投资者编号
	TQdpFtdcInvestorIDType	InvestorID;
};

///投资者资金应答
struct CQdpFtdcRspInvestorAccountField
{
	///经纪公司编号
	TQdpFtdcBrokerIDType	BrokerID;
	///投资者编号
	TQdpFtdcInvestorIDType	InvestorID;
	///资金帐号
	TQdpFtdcAccountIDType	AccountID;
	///上次结算准备金
	TQdpFtdcMoneyType	PreBalance;
	///上日可用资金
	TQdpFtdcMoneyType	PreAvailable;
	///入金金额
	TQdpFtdcMoneyType	Deposit;
	///出金金额
	TQdpFtdcMoneyType	Withdraw;
	///占用保证金
	TQdpFtdcMoneyType	Margin;
	///期权权利金收支
	TQdpFtdcMoneyType	Premium;
	///手续费
	TQdpFtdcMoneyType	Fee;
	///冻结的保证金
	TQdpFtdcMoneyType	FrozenMargin;
	///冻结权利金
	TQdpFtdcMoneyType	FrozenPremium;
	///冻结手续费
	TQdpFtdcMoneyType	FrozenFee;
	///平仓盈亏
	TQdpFtdcMoneyType	CloseProfit;
	///持仓盈亏
	TQdpFtdcMoneyType	PositionProfit;
	///可用资金
	TQdpFtdcMoneyType	Available;
	///结算准备金
	TQdpFtdcMoneyType	Balance;
	///多头占用保证金
	TQdpFtdcMoneyType	LongMargin;
	///空头占用保证金
	TQdpFtdcMoneyType	ShortMargin;
	///多头冻结的保证金
	TQdpFtdcMoneyType	LongFrozenMargin;
	///空头冻结的保证金
	TQdpFtdcMoneyType	ShortFrozenMargin;
	///动态权益
	TQdpFtdcMoneyType	DynamicRights;
	///风险度
	TQdpFtdcMoneyType	Risk;
	///其他费用
	TQdpFtdcMoneyType	OtherFee;
	///质押金额
	TQdpFtdcMoneyType	Mortgage;
	///币种
	TQdpFtdcCurrencyIDType	Currency;
};

///可用投资者查询
struct CQdpFtdcQryUserInvestorField
{
	///经纪公司编号
	TQdpFtdcBrokerIDType	BrokerID;
	///用户代码
	TQdpFtdcUserIDType	UserID;
};

///可用投资者应答
struct CQdpFtdcRspUserInvestorField
{
	///经纪公司编号
	TQdpFtdcBrokerIDType	BrokerID;
	///交易用户代码
	TQdpFtdcUserIDType	UserID;
	///投资者编号
	TQdpFtdcInvestorIDType	InvestorID;
};

///交易编码查询
struct CQdpFtdcQryTradingCodeField
{
	///经纪公司编号
	TQdpFtdcBrokerIDType	BrokerID;
	///用户代码
	TQdpFtdcUserIDType	UserID;
	///投资者编号
	TQdpFtdcInvestorIDType	InvestorID;
	///交易所代码
	TQdpFtdcExchangeIDType	ExchangeID;
};

///交易编码查询
struct CQdpFtdcRspTradingCodeField
{
	///经纪公司编号
	TQdpFtdcBrokerIDType	BrokerID;
	///投资者编号
	TQdpFtdcInvestorIDType	InvestorID;
	///资金帐号
	TQdpFtdcAccountIDType	AccountID;
	///交易所代码
	TQdpFtdcExchangeIDType	ExchangeID;
	///会员编号
	TQdpFtdcParticipantIDType	ParticipantID;
	///客户代码
	TQdpFtdcClientIDType	ClientID;
	///客户代码权限
	TQdpFtdcTradingRightType	ClientRight;
	///客户类型
	TQdpFtdcClientTypeType	ClientType;
	///客户保值类型
	TQdpFtdcHedgeFlagType	ClientHedgeFlag;
	///是否活跃
	TQdpFtdcIsActiveType	IsActive;
};

///交易所查询请求
struct CQdpFtdcQryExchangeField
{
	///交易所代码
	TQdpFtdcExchangeIDType	ExchangeID;
};

///交易所查询应答
struct CQdpFtdcRspExchangeField
{
	///交易日
	TQdpFtdcTradingDayType	TradingDay;
	///交易所代码
	TQdpFtdcExchangeIDType	ExchangeID;
	///交易所名称
	TQdpFtdcExchangeNameType	ExchangeName;
};

///投资者持仓查询请求
struct CQdpFtdcQryInvestorPositionField
{
	///经纪公司编号
	TQdpFtdcBrokerIDType	BrokerID;
	///用户代码
	TQdpFtdcUserIDType	UserID;
	///交易所代码
	TQdpFtdcExchangeIDType	ExchangeID;
	///投资者编号
	TQdpFtdcInvestorIDType	InvestorID;
	///合约代码
	TQdpFtdcInstrumentIDType	InstrumentID;
};

///投资者持仓查询应答
struct CQdpFtdcRspInvestorPositionField
{
	///经纪公司编号
	TQdpFtdcBrokerIDType	BrokerID;
	///交易所代码
	TQdpFtdcExchangeIDType	ExchangeID;
	///投资者编号
	TQdpFtdcInvestorIDType	InvestorID;
	///会员编号
	TQdpFtdcParticipantIDType	ParticipantID;
	///客户代码
	TQdpFtdcClientIDType	ClientID;
	///合约代码
	TQdpFtdcInstrumentIDType	InstrumentID;
	///买卖方向
	TQdpFtdcDirectionType	Direction;
	///投机套保标志
	TQdpFtdcHedgeFlagType	HedgeFlag;
	///占用保证金
	TQdpFtdcMoneyType	UsedMargin;
	///总持仓量
	TQdpFtdcVolumeType	Position;
	///今日持仓成本
	TQdpFtdcPriceType	PositionCost;
	///昨持仓量(不变值)
	TQdpFtdcVolumeType	YdPosition;
	///昨日持仓成本
	TQdpFtdcMoneyType	YdPositionCost;
	///冻结的保证金
	TQdpFtdcMoneyType	FrozenMargin;
	///开仓冻结持仓
	TQdpFtdcVolumeType	FrozenPosition;
	///平仓冻结持仓
	TQdpFtdcVolumeType	FrozenClosing;
	///冻结的权利金
	TQdpFtdcMoneyType	FrozenPremium;
	///最后一笔成交编号
	TQdpFtdcTradeIDType	LastTradeID;
	///最后一笔本地报单编号
	TQdpFtdcOrderLocalIDType	LastOrderLocalID;
	///币种
	TQdpFtdcCurrencyIDType	Currency;
	///持仓盈亏
	TQdpFtdcMoneyType	PositionProfit;
	///今持仓量
	TQdpFtdcVolumeType	TodayPosition;
	///今仓平仓冻结
	TQdpFtdcVolumeType	FrozenTodayClosing;
};

///用户查询
struct CQdpFtdcQryUserField
{
	///交易用户代码
	TQdpFtdcUserIDType	StartUserID;
	///交易用户代码
	TQdpFtdcUserIDType	EndUserID;
};

///用户
struct CQdpFtdcUserField
{
	///经纪公司编号
	TQdpFtdcBrokerIDType	BrokerID;
	///用户代码
	TQdpFtdcUserIDType	UserID;
	///用户登录密码
	TQdpFtdcPasswordType	Password;
	///是否活跃
	TQdpFtdcIsActiveType	IsActive;
	///用户名称
	TQdpFtdcUserNameType	UserName;
	///用户类型
	TQdpFtdcUserTypeType	UserType;
	///营业部
	TQdpFtdcDepartmentType	Department;
	///授权功能集
	TQdpFtdcGrantFuncSetType	GrantFuncSet;
	///是否检查IP和MAC
	TQdpFtdcBoolType	CheckIpMacAddr;
};

///投资者手续费率查询
struct CQdpFtdcQryInvestorFeeField
{
	///经纪公司编号
	TQdpFtdcBrokerIDType	BrokerID;
	///用户代码
	TQdpFtdcUserIDType	UserID;
	///投资者编号
	TQdpFtdcInvestorIDType	InvestorID;
	///交易所代码
	TQdpFtdcExchangeIDType	ExchangeID;
	///合约代码
	TQdpFtdcInstrumentIDType	InstrumentID;
	///投机套保标志
	TQdpFtdcHedgeFlagType	HedgeFlag;
};

///投资者手续费率
struct CQdpFtdcInvestorFeeField
{
	///经纪公司编号
	TQdpFtdcBrokerIDType	BrokerID;
	///交易所代码
	TQdpFtdcExchangeIDType	ExchangeID;
	///投资者编码
	TQdpFtdcInvestorIDType	InvestorID;
	///合约代码
	TQdpFtdcInstrumentIDType	InstrumentID;
	///投机套保标志
	TQdpFtdcHedgeFlagType	HedgeFlag;
	///开仓手续费按比例
	TQdpFtdcRatioType	OpenFeeRate;
	///开仓手续费按手数
	TQdpFtdcRatioType	OpenFeeAmt;
	///平仓手续费按比例
	TQdpFtdcRatioType	OffsetFeeRate;
	///平仓手续费按手数
	TQdpFtdcRatioType	OffsetFeeAmt;
	///平今仓手续费按比例
	TQdpFtdcRatioType	OTFeeRate;
	///平今仓手续费按手数
	TQdpFtdcRatioType	OTFeeAmt;
};

///投资者保证金率查询
struct CQdpFtdcQryInvestorMarginField
{
	///经纪公司编号
	TQdpFtdcBrokerIDType	BrokerID;
	///用户代码
	TQdpFtdcUserIDType	UserID;
	///投资者编号
	TQdpFtdcInvestorIDType	InvestorID;
	///交易所代码
	TQdpFtdcExchangeIDType	ExchangeID;
	///合约代码
	TQdpFtdcInstrumentIDType	InstrumentID;
	///投机套保标志
	TQdpFtdcHedgeFlagType	HedgeFlag;
};

///投资者保证金率
struct CQdpFtdcInvestorMarginField
{
	///经纪公司编号
	TQdpFtdcBrokerIDType	BrokerID;
	///交易所代码
	TQdpFtdcExchangeIDType	ExchangeID;
	///投资者编码
	TQdpFtdcInvestorIDType	InvestorID;
	///合约代码
	TQdpFtdcInstrumentIDType	InstrumentID;
	///投机套保标志
	TQdpFtdcHedgeFlagType	HedgeFlag;
	///多头占用保证金按比例
	TQdpFtdcRatioType	LongMarginRate;
	///多头保证金按手数
	TQdpFtdcRatioType	LongMarginAmt;
	///空头占用保证金按比例
	TQdpFtdcRatioType	ShortMarginRate;
	///空头保证金按手数
	TQdpFtdcRatioType	ShortMarginAmt;
};

///实时行情查询请求
struct CQdpFtdcQryMarketDataField
{
	///交易所代码
	TQdpFtdcExchangeIDType	ExchangeID;
	///合约代码
	TQdpFtdcInstrumentIDType	InstrumentID;
};

///实时行情查询应答
struct CQdpFtdcMarketDataField
{
	///交易日
	TQdpFtdcTradingDayType	TradingDay;
	///交易所代码
	TQdpFtdcExchangeIDType	ExchangeID;
	///合约代码
	TQdpFtdcInstrumentIDType	InstrumentID;
	///今开盘
	TQdpFtdcPriceType	OpenPrice;
	///最高价
	TQdpFtdcPriceType	HighestPrice;
	///最低价
	TQdpFtdcPriceType	LowestPrice;
	///最新价
	TQdpFtdcPriceType	LastPrice;
	///数量
	TQdpFtdcVolumeType	Volume;
	///成交金额
	TQdpFtdcMoneyType	Turnover;
	///跌停板价
	TQdpFtdcPriceType	LowerLimitPrice;
	///涨停板价
	TQdpFtdcPriceType	UpperLimitPrice;
	///持仓量
	TQdpFtdcVolumeType	OpenInterest;
	///昨收盘
	TQdpFtdcPriceType	PreClosePrice;
	///昨持仓量
	TQdpFtdcVolumeType	PreOpenInterest;
	///昨结算
	TQdpFtdcPriceType	PreSettlementPrice;
	///今结算
	TQdpFtdcPriceType	SettlementPrice;
	///最后修改毫秒
	TQdpFtdcMillisecType	UpdateMillisec;
	///最后修改时间
	TQdpFtdcTimeType	UpdateTime;
};

///行情查询应答
struct CQdpFtdcRspMarketDataField
{
	///交易所代码
	TQdpFtdcExchangeIDType	ExchangeID;
	///交易日
	TQdpFtdcTradingDayType	TradingDay;
	///结算组代码
	TQdpFtdcSettlementGroupIDType	SettlementGroupID;
	///结算编号
	TQdpFtdcSettlementIDType	SettlementID;
	///昨结算
	TQdpFtdcPriceType	PreSettlementPrice;
	///昨收盘
	TQdpFtdcPriceType	PreClosePrice;
	///昨持仓量
	TQdpFtdcLargeVolumeType	PreOpenInterest;
	///昨虚实度
	TQdpFtdcRatioType	PreDelta;
	///今开盘
	TQdpFtdcPriceType	OpenPrice;
	///最高价
	TQdpFtdcPriceType	HighestPrice;
	///最低价
	TQdpFtdcPriceType	LowestPrice;
	///今收盘
	TQdpFtdcPriceType	ClosePrice;
	///涨停板价
	TQdpFtdcPriceType	UpperLimitPrice;
	///跌停板价
	TQdpFtdcPriceType	LowerLimitPrice;
	///今结算
	TQdpFtdcPriceType	SettlementPrice;
	///今虚实度
	TQdpFtdcRatioType	CurrDelta;
	///最新价
	TQdpFtdcPriceType	LastPrice;
	///数量
	TQdpFtdcVolumeType	Volume;
	///成交金额
	TQdpFtdcMoneyType	Turnover;
	///持仓量
	TQdpFtdcLargeVolumeType	OpenInterest;
	///申买价一
	TQdpFtdcPriceType	BidPrice1;
	///申买量一
	TQdpFtdcVolumeType	BidVolume1;
	///申卖价一
	TQdpFtdcPriceType	AskPrice1;
	///申卖量一
	TQdpFtdcVolumeType	AskVolume1;
	///合约代码
	TQdpFtdcInstrumentIDType	InstrumentID;
	///最后修改时间
	TQdpFtdcTimeType	UpdateTime;
	///最后修改毫秒
	TQdpFtdcMillisecType	UpdateMillisec;
};

///金交所递延费率查询请求
struct CQdpFtdcQrySGEDeferRateField
{
	///合约代码
	TQdpFtdcInstrumentIDType	InstrumentID;
};

///金交所递延费率查询应答
struct CQdpFtdcSGEDeferRateField
{
	///合约代码
	TQdpFtdcInstrumentIDType	InstrumentID;
	///交易所代码
	TQdpFtdcExchangeIDType	ExchangeID;
	///交易日期
	TQdpFtdcTradingDayType	TradeDate;
	///支付方向
	TQdpFtdcPayDirectionType	Direction;
	///递延费率
	TQdpFtdcRatioType	DeferRate;
};

///分价表查询请求
struct CQdpFtdcQryMBLMarketDataField
{
	///交易所代码
	TQdpFtdcExchangeIDType	ExchangeID;
	///起始合约代码
	TQdpFtdcInstrumentIDType	InstIDStart;
	///结束合约代码
	TQdpFtdcInstrumentIDType	InstIDEnd;
	///买卖方向
	TQdpFtdcDirectionType	Direction;
};

///分价表查询应答
struct CQdpFtdcMBLMarketDataField
{
	///合约代码
	TQdpFtdcInstrumentIDType	InstrumentID;
	///买卖方向
	TQdpFtdcDirectionType	Direction;
	///价格
	TQdpFtdcPriceType	Price;
	///数量
	TQdpFtdcVolumeType	Volume;
	///最后修改时间
	TQdpFtdcTimeType	UpdateTime;
	///最后修改毫秒
	TQdpFtdcMillisecType	UpdateMillisec;
};

///查询持仓明细请求
struct CQdpFtdcQryInvestorPositionDetailField
{
	///经纪公司编号
	TQdpFtdcBrokerIDType	BrokerID;
	///交易所代码
	TQdpFtdcExchangeIDType	ExchangeID;
	///投资者编号
	TQdpFtdcInvestorIDType	InvestorID;
	///单腿合约代码
	TQdpFtdcInstrumentIDType	InstrumentID;
};

///查询持仓明细应答
struct CQdpFtdcRspInvestorPositionDetailField
{
	///经纪公司编号
	TQdpFtdcBrokerIDType	BrokerID;
	///交易所代码
	TQdpFtdcExchangeIDType	ExchangeID;
	///投资者编号
	TQdpFtdcInvestorIDType	InvestorID;
	///合约代码
	TQdpFtdcInstrumentIDType	InstrumentID;
	///投机套保标志
	TQdpFtdcHedgeFlagType	HedgeFlag;
	///买卖方向
	TQdpFtdcDirectionType	Direction;
	///开仓日期
	TQdpFtdcDateType	OpenDate;
	///成交编号
	TQdpFtdcTradeIDType	TradeID;
	///数量
	TQdpFtdcVolumeType	Volume;
	///开仓价
	TQdpFtdcMoneyType	OpenPrice;
	///交易日
	TQdpFtdcDateType	TradingDay;
	///交易类型
	TQdpFtdcTradeTypeType	TradeType;
	///组合合约代码
	TQdpFtdcInstrumentIDType	CombInstrumentID;
	///逐日盯市平仓盈亏
	TQdpFtdcMoneyType	CloseProfitByDate;
	///逐笔对冲平仓盈亏
	TQdpFtdcMoneyType	CloseProfitByTrade;
	///逐日盯市持仓盈亏
	TQdpFtdcMoneyType	PositionProfitByDate;
	///逐笔对冲持仓盈亏
	TQdpFtdcMoneyType	PositionProfitByTrade;
	///投资者保证金
	TQdpFtdcMoneyType	Margin;
	///交易所保证金
	TQdpFtdcMoneyType	ExchMargin;
	///保证金率
	TQdpFtdcMoneyType	MarginRateByMoney;
	///保证金率(按手数)
	TQdpFtdcMoneyType	MarginRateByVolume;
	///昨结算价
	TQdpFtdcPriceType	LastSettlementPrice;
	///结算价
	TQdpFtdcPriceType	SettlementPrice;
	///平仓量
	TQdpFtdcVolumeType	CloseVolume;
	///平仓金额
	TQdpFtdcMoneyType	CloseAmount;
};

///投资者期权手续费率查询
struct CQdpFtdcQryInvestorOptionFeeField
{
	///经纪公司编号
	TQdpFtdcBrokerIDType	BrokerID;
	///用户代码
	TQdpFtdcUserIDType	UserID;
	///投资者编号
	TQdpFtdcInvestorIDType	InvestorID;
	///交易所代码
	TQdpFtdcExchangeIDType	ExchangeID;
	///合约代码
	TQdpFtdcInstrumentIDType	InstrumentID;
};

///投资者期权手续费率
struct CQdpFtdcRspInvestorOptionFeeField
{
	///经纪公司编号
	TQdpFtdcBrokerIDType	BrokerID;
	///交易所代码
	TQdpFtdcExchangeIDType	ExchangeID;
	///投资者编码
	TQdpFtdcInvestorIDType	InvestorID;
	///合约代码
	TQdpFtdcInstrumentIDType	InstrumentID;
	///开仓手续费按比例
	TQdpFtdcRatioType	OpenFeeRate;
	///开仓手续费按手数
	TQdpFtdcRatioType	OpenFeeAmt;
	///平仓手续费按比例
	TQdpFtdcRatioType	OffsetFeeRate;
	///平仓手续费按手数
	TQdpFtdcRatioType	OffsetFeeAmt;
	///平今仓手续费按比例
	TQdpFtdcRatioType	OTFeeRate;
	///平今仓手续费按手数
	TQdpFtdcRatioType	OTFeeAmt;
	///执行手续费按比例
	TQdpFtdcRatioType	StrikeFeeRate;
	///执行手续费按手数
	TQdpFtdcRatioType	StrikeFeeAmt;
};

///QDP前置通道信息
struct CQdpFtdcFrontInfoField
{
	///交易所API的前置编号
	TQdpFtdcBranchIDType	BranchID;
	///交易所代码
	TQdpFtdcExchangeIDType	ExchangeID;
	///席位号
	TQdpFtdcSeatIDType	SeatID;
	///连接地址
	TQdpFtdcFrontAddrType	FrontAddr;
};

///查询QDP前置通道信息
struct CQdpFtdcQryFrontInfoField
{
	///交易所代码
	TQdpFtdcExchangeIDType	ExchangeID;
};

///投资者持仓限额查询
struct CQdpFtdcQryInvestorPositionLimitField
{
	///经纪公司编号
	TQdpFtdcBrokerIDType	BrokerID;
	///投资者编号
	TQdpFtdcInvestorIDType	InvestorID;
	///交易所代码
	TQdpFtdcExchangeIDType	ExchangeID;
	///合约代码
	TQdpFtdcInstrumentIDType	InstrumentID;
};

///投资者持仓限额
struct CQdpFtdcRspInvestorPositionLimitField
{
	///经纪公司编号
	TQdpFtdcBrokerIDType	BrokerID;
	///投资者编号
	TQdpFtdcInvestorIDType	InvestorID;
	///交易所代码
	TQdpFtdcExchangeIDType	ExchangeID;
	///合约代码
	TQdpFtdcInstrumentIDType	InstrumentID;
	///多头持仓限额
	TQdpFtdcVolumeType	LongPosiLimit;
	///多头持仓限额
	TQdpFtdcVolumeType	ShortPosiLimit;
	///品种多头持仓
	TQdpFtdcVolumeType	LongPosition;
	///品种多头冻结持仓
	TQdpFtdcVolumeType	LongFrozen;
	///品种空头持仓
	TQdpFtdcVolumeType	ShortPosition;
	///品种空头冻结持仓
	TQdpFtdcVolumeType	ShortFrozen;
};

///交易汇率查询
struct CQdpFtdcQryExchangeRateField
{
	///币种
	TQdpFtdcCurrencyIDType	InstCurrency;
	///币种
	TQdpFtdcCurrencyIDType	AccCurrency;
};

///交易汇率通知
struct CQdpFtdcRspExchangeRateField
{
	///币种
	TQdpFtdcCurrencyIDType	InstCurrency;
	///币种
	TQdpFtdcCurrencyIDType	AccCurrency;
	///汇率
	TQdpFtdcRatioType	ExchangeRate;
};

///询价录入
struct CQdpFtdcInputForQuoteField
{
	///经纪公司编号
	TQdpFtdcBrokerIDType	BrokerID;
	///投资者编号
	TQdpFtdcInvestorIDType	InvestorID;
	///用户代码
	TQdpFtdcUserIDType	UserID;
	///用户本地报单号
	TQdpFtdcUserOrderLocalIDType	UserOrderLocalID;
	///用户自定义域
	TQdpFtdcCustomType	UserCustom;
	///交易所代码
	TQdpFtdcExchangeIDType	ExchangeID;
	///合约代码
	TQdpFtdcInstrumentIDType	InstrumentID;
	///本地报单编号
	TQdpFtdcOrderLocalIDType	OrderLocalID;
};

///报价录入
struct CQdpFtdcInputQuoteField
{
	///经纪公司编号
	TQdpFtdcBrokerIDType	BrokerID;
	///投资者编号
	TQdpFtdcInvestorIDType	InvestorID;
	///用户代码
	TQdpFtdcUserIDType	UserID;
	///用户本地报单号
	TQdpFtdcUserOrderLocalIDType	UserOrderLocalID;
	///用户自定义域
	TQdpFtdcCustomType	UserCustom;
	///交易所代码
	TQdpFtdcExchangeIDType	ExchangeID;
	///合约代码
	TQdpFtdcInstrumentIDType	InstrumentID;
	///系统报单编号
	TQdpFtdcOrderSysIDType	OrderSysID;
	///应价编号
	TQdpFtdcOrderSysIDType	ForQuoteSysID;
	///卖价格
	TQdpFtdcPriceType	AskPrice;
	///卖数量
	TQdpFtdcVolumeType	AskVolume;
	///卖开平标志
	TQdpFtdcOffsetFlagType	AskOffsetFlag;
	///卖投机套保标志
	TQdpFtdcHedgeFlagType	AskHedgeFlag;
	///买价格
	TQdpFtdcPriceType	BidPrice;
	///买数量
	TQdpFtdcVolumeType	BidVolume;
	///买开平标志
	TQdpFtdcOffsetFlagType	BidOffsetFlag;
	///买投机套保标志
	TQdpFtdcHedgeFlagType	BidHedgeFlag;
	///业务单元
	TQdpFtdcBusinessUnitType	BusinessUnit;
	///营业部代码
	TQdpFtdcBranchIDType	BranchID;
	///买方本地报单编号
	TQdpFtdcUserOrderLocalIDType	BidOrderRef;
	///卖方本地报单编号
	TQdpFtdcUserOrderLocalIDType	AskOrderRef;
};

///询价流通知
struct CQdpFtdcForQuoteRspField
{
	///交易日
	TQdpFtdcDateType	TradingDay;
	///合约代码
	TQdpFtdcInstrumentIDType	InstrumentID;
	///询价编号
	TQdpFtdcOrderSysIDType	OrderSysID;
	///交易所代码
	TQdpFtdcExchangeIDType	ExchangeID;
	///插入时间
	TQdpFtdcTimeType	InsertTime;
};

///报价通知
struct CQdpFtdcQuoteField
{
	///经纪公司编号
	TQdpFtdcBrokerIDType	BrokerID;
	///投资者编号
	TQdpFtdcInvestorIDType	InvestorID;
	///用户代码
	TQdpFtdcUserIDType	UserID;
	///用户本地报单号
	TQdpFtdcUserOrderLocalIDType	UserOrderLocalID;
	///用户自定义域
	TQdpFtdcCustomType	UserCustom;
	///交易所代码
	TQdpFtdcExchangeIDType	ExchangeID;
	///合约代码
	TQdpFtdcInstrumentIDType	InstrumentID;
	///系统报单编号
	TQdpFtdcOrderSysIDType	OrderSysID;
	///应价编号
	TQdpFtdcOrderSysIDType	ForQuoteSysID;
	///卖价格
	TQdpFtdcPriceType	AskPrice;
	///卖数量
	TQdpFtdcVolumeType	AskVolume;
	///卖开平标志
	TQdpFtdcOffsetFlagType	AskOffsetFlag;
	///卖投机套保标志
	TQdpFtdcHedgeFlagType	AskHedgeFlag;
	///买价格
	TQdpFtdcPriceType	BidPrice;
	///买数量
	TQdpFtdcVolumeType	BidVolume;
	///买开平标志
	TQdpFtdcOffsetFlagType	BidOffsetFlag;
	///买投机套保标志
	TQdpFtdcHedgeFlagType	BidHedgeFlag;
	///业务单元
	TQdpFtdcBusinessUnitType	BusinessUnit;
	///营业部代码
	TQdpFtdcBranchIDType	BranchID;
	///买方本地报单编号
	TQdpFtdcUserOrderLocalIDType	BidOrderRef;
	///卖方本地报单编号
	TQdpFtdcUserOrderLocalIDType	AskOrderRef;
	///交易日
	TQdpFtdcTradingDayType	TradingDay;
	///会员编号
	TQdpFtdcParticipantIDType	ParticipantID;
	///客户号
	TQdpFtdcClientIDType	ClientID;
	///下单席位号
	TQdpFtdcSeatIDType	SeatID;
	///插入时间
	TQdpFtdcTimeType	InsertTime;
	///本地报单编号
	TQdpFtdcOrderLocalIDType	OrderLocalID;
	///报单来源
	TQdpFtdcOrderSourceType	OrderSource;
	///报单状态
	TQdpFtdcOrderStatusType	OrderStatus;
	///撤销时间
	TQdpFtdcTimeType	CancelTime;
	///撤单用户编号
	TQdpFtdcUserIDType	CancelUserID;
	///今成交数量
	TQdpFtdcVolumeType	VolumeTraded;
	///剩余数量
	TQdpFtdcVolumeType	VolumeRemain;
	///前置编号
	TQdpFtdcFrontIDType	FrontID;
	///会话编号
	TQdpFtdcSessionIDType	SessionID;
	///冻结手续费
	TQdpFtdcMoneyType	FrozenFee;
	///冻结的保证金
	TQdpFtdcMoneyType	FrozenMargin;
	///期权权利金收支
	TQdpFtdcMoneyType	FrozenPremium;
	///资金帐号
	TQdpFtdcAccountIDType	AccountID;
	///下单用户编号
	TQdpFtdcUserIDType	OrderUserID;
	///交易类型
	TQdpFtdcTradeTypeType	TradeType;
	///处理标志
	TQdpFtdcDealFlagType	DealFlag;
	///已成交佣金
	TQdpFtdcMoneyType	TradeCommision;
	///成交金额
	TQdpFtdcMoneyType	TradeAmnt;
	///撤单数量
	TQdpFtdcVolumeType	CancleVolume;
	///请求编号
	TQdpFtdcRequestIDType	RequestID;
	///通道对应的APIID
	TQdpFtdcNumberType	APIID;
	///下单IP地址
	TQdpFtdcIPAddressType	IPAddress;
	///下单MAC地址
	TQdpFtdcMacAddressType	MacAddress;
	///买方系统报单编号
	TQdpFtdcOrderSysIDType	BidOrderSysID;
	///卖方系统报单编号
	TQdpFtdcOrderSysIDType	AskOrderSysID;
};

///报价操作
struct CQdpFtdcQuoteActionField
{
	///交易所代码
	TQdpFtdcExchangeIDType	ExchangeID;
	///报单编号
	TQdpFtdcOrderSysIDType	OrderSysID;
	///经纪公司编号
	TQdpFtdcBrokerIDType	BrokerID;
	///投资者编号
	TQdpFtdcInvestorIDType	InvestorID;
	///用户代码
	TQdpFtdcUserIDType	UserID;
	///合约代码
	TQdpFtdcInstrumentIDType	InstrumentID;
	///本次撤单操作的本地编号
	TQdpFtdcUserOrderLocalIDType	UserOrderActionLocalID;
	///被撤订单的本地报单编号
	TQdpFtdcUserOrderLocalIDType	UserOrderLocalID;
	///报单操作标志
	TQdpFtdcActionFlagType	ActionFlag;
	///价格
	TQdpFtdcPriceType	LimitPrice;
	///数量变化
	TQdpFtdcVolumeType	VolumeChange;
	///记录编号
	TQdpFtdcSequenceNoType	RecNum;
	///前置编号
	TQdpFtdcFrontIDType	FrontID;
	///会话编号
	TQdpFtdcSessionIDType	SessionID;
};

///询价查询
struct CQdpFtdcQryForQuoteField
{
	///经纪公司编号
	TQdpFtdcBrokerIDType	BrokerID;
	///投资者编号
	TQdpFtdcInvestorIDType	InvestorID;
	///合约代码
	TQdpFtdcInstrumentIDType	InstrumentID;
	///交易所代码
	TQdpFtdcExchangeIDType	ExchangeID;
};

///询价查询应答
struct CQdpFtdcForQuoteField
{
	///经纪公司编号
	TQdpFtdcBrokerIDType	BrokerID;
	///投资者编号
	TQdpFtdcInvestorIDType	InvestorID;
	///用户代码
	TQdpFtdcUserIDType	UserID;
	///用户本地报单号
	TQdpFtdcUserOrderLocalIDType	UserOrderLocalID;
	///用户自定义域
	TQdpFtdcCustomType	UserCustom;
	///交易所代码
	TQdpFtdcExchangeIDType	ExchangeID;
	///合约代码
	TQdpFtdcInstrumentIDType	InstrumentID;
	///本地报单编号
	TQdpFtdcOrderLocalIDType	OrderLocalID;
	///询价状态
	TQdpFtdcForQuoteStatusTypeType	ForQuoteStatus;
	///交易日
	TQdpFtdcDateType	TradingDay;
	///插入时间
	TQdpFtdcTimeType	InsertTime;
};

///报价查询
struct CQdpFtdcQryQuoteField
{
	///经纪公司编号
	TQdpFtdcBrokerIDType	BrokerID;
	///用户代码
	TQdpFtdcUserIDType	UserID;
	///投资者编号
	TQdpFtdcInvestorIDType	InvestorID;
	///合约代码
	TQdpFtdcInstrumentIDType	InstrumentID;
	///交易所代码
	TQdpFtdcExchangeIDType	ExchangeID;
	///系统报单编号
	TQdpFtdcOrderSysIDType	OrderSysID;
};

///成交
struct CQdpFtdcTradeField
{
	///交易日
	TQdpFtdcTradingDayType	TradingDay;
	///经纪公司编号
	TQdpFtdcBrokerIDType	BrokerID;
	///交易所代码
	TQdpFtdcExchangeIDType	ExchangeID;
	///会员编号
	TQdpFtdcParticipantIDType	ParticipantID;
	///下单席位号
	TQdpFtdcSeatIDType	SeatID;
	///投资者编号
	TQdpFtdcInvestorIDType	InvestorID;
	///客户号
	TQdpFtdcClientIDType	ClientID;
	///用户编号
	TQdpFtdcUserIDType	UserID;
	///成交编号
	TQdpFtdcTradeIDType	TradeID;
	///报单编号
	TQdpFtdcOrderSysIDType	OrderSysID;
	///本地报单编号
	TQdpFtdcUserOrderLocalIDType	UserOrderLocalID;
	///合约代码
	TQdpFtdcInstrumentIDType	InstrumentID;
	///买卖方向
	TQdpFtdcDirectionType	Direction;
	///开平标志
	TQdpFtdcOffsetFlagType	OffsetFlag;
	///投机套保标志
	TQdpFtdcHedgeFlagType	HedgeFlag;
	///成交价格
	TQdpFtdcPriceType	TradePrice;
	///成交数量
	TQdpFtdcVolumeType	TradeVolume;
	///成交时间
	TQdpFtdcTimeType	TradeTime;
	///清算会员编号
	TQdpFtdcParticipantIDType	ClearingPartID;
	///成交金额
	TQdpFtdcMoneyType	TradeAmnt;
	///记录编号
	TQdpFtdcSequenceNoType	RecNum;
	///交易类型
	TQdpFtdcTradeTypeType	TradeType;
};

///报单
struct CQdpFtdcOrderField
{
	///经纪公司编号
	TQdpFtdcBrokerIDType	BrokerID;
	///交易所代码
	TQdpFtdcExchangeIDType	ExchangeID;
	///系统报单编号
	TQdpFtdcOrderSysIDType	OrderSysID;
	///投资者编号
	TQdpFtdcInvestorIDType	InvestorID;
	///用户代码
	TQdpFtdcUserIDType	UserID;
	///合约代码
	TQdpFtdcInstrumentIDType	InstrumentID;
	///用户本地报单号
	TQdpFtdcUserOrderLocalIDType	UserOrderLocalID;
	///价格类型
	TQdpFtdcOrderPriceTypeType	OrderPriceType;
	///买卖方向
	TQdpFtdcDirectionType	Direction;
	///开平标志
	TQdpFtdcOffsetFlagType	OffsetFlag;
	///投机套保标志
	TQdpFtdcHedgeFlagType	HedgeFlag;
	///价格
	TQdpFtdcPriceType	LimitPrice;
	///数量
	TQdpFtdcVolumeType	Volume;
	///有效期类型
	TQdpFtdcTimeConditionType	TimeCondition;
	///GTD日期
	TQdpFtdcDateType	GTDDate;
	///成交量类型
	TQdpFtdcVolumeConditionType	VolumeCondition;
	///最小成交量
	TQdpFtdcVolumeType	MinVolume;
	///止损价
	TQdpFtdcPriceType	StopPrice;
	///强平原因
	TQdpFtdcForceCloseReasonType	ForceCloseReason;
	///自动挂起标志
	TQdpFtdcBoolType	IsAutoSuspend;
	///业务单元
	TQdpFtdcBusinessUnitType	BusinessUnit;
	///用户自定义域
	TQdpFtdcCustomType	UserCustom;
	///营业部代码
	TQdpFtdcBranchIDType	BranchID;
	///记录编号
	TQdpFtdcSequenceNoType	RecNum;
	///业务类别
	TQdpFtdcBusinessTypeType	BusinessType;
	///交易日
	TQdpFtdcTradingDayType	TradingDay;
	///会员编号
	TQdpFtdcParticipantIDType	ParticipantID;
	///客户号
	TQdpFtdcClientIDType	ClientID;
	///下单席位号
	TQdpFtdcSeatIDType	SeatID;
	///插入时间
	TQdpFtdcTimeType	InsertTime;
	///本地报单编号
	TQdpFtdcOrderLocalIDType	OrderLocalID;
	///报单来源
	TQdpFtdcOrderSourceType	OrderSource;
	///报单状态
	TQdpFtdcOrderStatusType	OrderStatus;
	///撤销时间
	TQdpFtdcTimeType	CancelTime;
	///撤单用户编号
	TQdpFtdcUserIDType	CancelUserID;
	///今成交数量
	TQdpFtdcVolumeType	VolumeTraded;
	///剩余数量
	TQdpFtdcVolumeType	VolumeRemain;
	///前置编号
	TQdpFtdcFrontIDType	FrontID;
	///会话编号
	TQdpFtdcSessionIDType	SessionID;
};

///数据流回退
struct CQdpFtdcFlowMessageCancelField
{
	///序列系列号
	TQdpFtdcSequenceSeriesType	SequenceSeries;
	///交易日
	TQdpFtdcDateType	TradingDay;
	///数据中心代码
	TQdpFtdcDataCenterIDType	DataCenterID;
	///回退起始序列号
	TQdpFtdcSequenceNoType	StartSequenceNo;
	///回退结束序列号
	TQdpFtdcSequenceNoType	EndSequenceNo;
};

///信息分发
struct CQdpFtdcDisseminationField
{
	///序列系列号
	TQdpFtdcSequenceSeriesType	SequenceSeries;
	///序列号
	TQdpFtdcSequenceNoType	SequenceNo;
};

///出入金结果
struct CQdpFtdcInvestorAccountDepositResField
{
	///经纪公司编号
	TQdpFtdcBrokerIDType	BrokerID;
	///投资者编号
	TQdpFtdcInvestorIDType	InvestorID;
	///资金帐号
	TQdpFtdcAccountIDType	AccountID;
	///资金流水号
	TQdpFtdcAccountSeqNoType	AccountSeqNo;
	///连续递增的总资金流水号
	TQdpFtdcAccountSeqNoType	AccountInsideSeqNo;
	///金额
	TQdpFtdcMoneyType	Amount;
	///出入金方向
	TQdpFtdcAccountDirectionType	AmountDirection;
	///可用资金
	TQdpFtdcMoneyType	Available;
	///结算准备金
	TQdpFtdcMoneyType	Balance;
	///用户代码
	TQdpFtdcUserIDType	UserID;
};

///QDP警告消息通知
struct CQdpFtdcMessageNotifyInfoField
{
	///经纪公司编号
	TQdpFtdcBrokerIDType	BrokerID;
	///修改用户编号
	TQdpFtdcUserIDType	UserID;
	///投资者编号
	TQdpFtdcInvestorIDType	InvestorID;
	///交易所代码
	TQdpFtdcExchangeIDType	ExchangeID;
	///累加次数
	TQdpFtdcTotalNumsType	Nums;
	///业务类别
	TQdpFtdcBusinessTypeType	BusinessType;
	///警告信息
	TQdpFtdcErrorMsgType	WarnMsg;
};

///行情基础属性
struct CQdpFtdcMarketDataBaseField
{
	///交易日
	TQdpFtdcTradingDayType	TradingDay;
	///结算组代码
	TQdpFtdcSettlementGroupIDType	SettlementGroupID;
	///结算编号
	TQdpFtdcSettlementIDType	SettlementID;
	///昨结算
	TQdpFtdcPriceType	PreSettlementPrice;
	///昨收盘
	TQdpFtdcPriceType	PreClosePrice;
	///昨持仓量
	TQdpFtdcLargeVolumeType	PreOpenInterest;
	///昨虚实度
	TQdpFtdcRatioType	PreDelta;
};

///行情静态属性
struct CQdpFtdcMarketDataStaticField
{
	///今开盘
	TQdpFtdcPriceType	OpenPrice;
	///最高价
	TQdpFtdcPriceType	HighestPrice;
	///最低价
	TQdpFtdcPriceType	LowestPrice;
	///今收盘
	TQdpFtdcPriceType	ClosePrice;
	///涨停板价
	TQdpFtdcPriceType	UpperLimitPrice;
	///跌停板价
	TQdpFtdcPriceType	LowerLimitPrice;
	///今结算
	TQdpFtdcPriceType	SettlementPrice;
	///今虚实度
	TQdpFtdcRatioType	CurrDelta;
};

///行情最新成交属性
struct CQdpFtdcMarketDataLastMatchField
{
	///最新价
	TQdpFtdcPriceType	LastPrice;
	///数量
	TQdpFtdcVolumeType	Volume;
	///成交金额
	TQdpFtdcMoneyType	Turnover;
	///持仓量
	TQdpFtdcLargeVolumeType	OpenInterest;
};

///行情最优价属性
struct CQdpFtdcMarketDataBestPriceField
{
	///申买价一
	TQdpFtdcPriceType	BidPrice1;
	///申买量一
	TQdpFtdcVolumeType	BidVolume1;
	///申卖价一
	TQdpFtdcPriceType	AskPrice1;
	///申卖量一
	TQdpFtdcVolumeType	AskVolume1;
};

///行情申买二、三属性
struct CQdpFtdcMarketDataBid23Field
{
	///申买价二
	TQdpFtdcPriceType	BidPrice2;
	///申买量二
	TQdpFtdcVolumeType	BidVolume2;
	///申买价三
	TQdpFtdcPriceType	BidPrice3;
	///申买量三
	TQdpFtdcVolumeType	BidVolume3;
};

///行情申卖二、三属性
struct CQdpFtdcMarketDataAsk23Field
{
	///申卖价二
	TQdpFtdcPriceType	AskPrice2;
	///申卖量二
	TQdpFtdcVolumeType	AskVolume2;
	///申卖价三
	TQdpFtdcPriceType	AskPrice3;
	///申卖量三
	TQdpFtdcVolumeType	AskVolume3;
};

///行情申买四、五属性
struct CQdpFtdcMarketDataBid45Field
{
	///申买价四
	TQdpFtdcPriceType	BidPrice4;
	///申买量四
	TQdpFtdcVolumeType	BidVolume4;
	///申买价五
	TQdpFtdcPriceType	BidPrice5;
	///申买量五
	TQdpFtdcVolumeType	BidVolume5;
};

///行情申卖四、五属性
struct CQdpFtdcMarketDataAsk45Field
{
	///申卖价四
	TQdpFtdcPriceType	AskPrice4;
	///申卖量四
	TQdpFtdcVolumeType	AskVolume4;
	///申卖价五
	TQdpFtdcPriceType	AskPrice5;
	///申卖量五
	TQdpFtdcVolumeType	AskVolume5;
};

///行情更新时间属性
struct CQdpFtdcMarketDataUpdateTimeField
{
	///合约代码
	TQdpFtdcInstrumentIDType	InstrumentID;
	///最后修改时间
	TQdpFtdcTimeType	UpdateTime;
	///最后修改毫秒
	TQdpFtdcMillisecType	UpdateMillisec;
};

///深度行情
struct CQdpFtdcDepthMarketDataField
{
	///交易日
	TQdpFtdcTradingDayType	TradingDay;
	///结算组代码
	TQdpFtdcSettlementGroupIDType	SettlementGroupID;
	///结算编号
	TQdpFtdcSettlementIDType	SettlementID;
	///昨结算
	TQdpFtdcPriceType	PreSettlementPrice;
	///昨收盘
	TQdpFtdcPriceType	PreClosePrice;
	///昨持仓量
	TQdpFtdcLargeVolumeType	PreOpenInterest;
	///昨虚实度
	TQdpFtdcRatioType	PreDelta;
	///今开盘
	TQdpFtdcPriceType	OpenPrice;
	///最高价
	TQdpFtdcPriceType	HighestPrice;
	///最低价
	TQdpFtdcPriceType	LowestPrice;
	///今收盘
	TQdpFtdcPriceType	ClosePrice;
	///涨停板价
	TQdpFtdcPriceType	UpperLimitPrice;
	///跌停板价
	TQdpFtdcPriceType	LowerLimitPrice;
	///今结算
	TQdpFtdcPriceType	SettlementPrice;
	///今虚实度
	TQdpFtdcRatioType	CurrDelta;
	///最新价
	TQdpFtdcPriceType	LastPrice;
	///数量
	TQdpFtdcVolumeType	Volume;
	///成交金额
	TQdpFtdcMoneyType	Turnover;
	///持仓量
	TQdpFtdcLargeVolumeType	OpenInterest;
	///申买价一
	TQdpFtdcPriceType	BidPrice1;
	///申买量一
	TQdpFtdcVolumeType	BidVolume1;
	///申卖价一
	TQdpFtdcPriceType	AskPrice1;
	///申卖量一
	TQdpFtdcVolumeType	AskVolume1;
	///申买价二
	TQdpFtdcPriceType	BidPrice2;
	///申买量二
	TQdpFtdcVolumeType	BidVolume2;
	///申买价三
	TQdpFtdcPriceType	BidPrice3;
	///申买量三
	TQdpFtdcVolumeType	BidVolume3;
	///申卖价二
	TQdpFtdcPriceType	AskPrice2;
	///申卖量二
	TQdpFtdcVolumeType	AskVolume2;
	///申卖价三
	TQdpFtdcPriceType	AskPrice3;
	///申卖量三
	TQdpFtdcVolumeType	AskVolume3;
	///申买价四
	TQdpFtdcPriceType	BidPrice4;
	///申买量四
	TQdpFtdcVolumeType	BidVolume4;
	///申买价五
	TQdpFtdcPriceType	BidPrice5;
	///申买量五
	TQdpFtdcVolumeType	BidVolume5;
	///申卖价四
	TQdpFtdcPriceType	AskPrice4;
	///申卖量四
	TQdpFtdcVolumeType	AskVolume4;
	///申卖价五
	TQdpFtdcPriceType	AskPrice5;
	///申卖量五
	TQdpFtdcVolumeType	AskVolume5;
	///合约代码
	TQdpFtdcInstrumentIDType	InstrumentID;
	///最后修改时间
	TQdpFtdcTimeType	UpdateTime;
	///最后修改毫秒
	TQdpFtdcMillisecType	UpdateMillisec;
	///交易所代码
	TQdpFtdcExchangeIDType	ExchangeID;
	///申卖价六
	TQdpFtdcPriceType	AskPrice6;
	///申卖量六
	TQdpFtdcVolumeType	AskVolume6;
	///申卖价七
	TQdpFtdcPriceType	AskPrice7;
	///申卖量七
	TQdpFtdcVolumeType	AskVolume7;
	///申卖价八
	TQdpFtdcPriceType	AskPrice8;
	///申卖量八
	TQdpFtdcVolumeType	AskVolume8;
	///申卖价九
	TQdpFtdcPriceType	AskPrice9;
	///申卖量九
	TQdpFtdcVolumeType	AskVolume9;
	///申买价六
	TQdpFtdcPriceType	BidPrice6;
	///申买量六
	TQdpFtdcVolumeType	BidVolume6;
	///申买价七
	TQdpFtdcPriceType	BidPrice7;
	///申买量七
	TQdpFtdcVolumeType	BidVolume7;
	///申买价八
	TQdpFtdcPriceType	BidPrice8;
	///申买量八
	TQdpFtdcVolumeType	BidVolume8;
	///申买价九
	TQdpFtdcPriceType	BidPrice9;
	///申买量九
	TQdpFtdcVolumeType	BidVolume9;
	///申卖价十
	TQdpFtdcPriceType	AskPrice10;
	///申卖量十
	TQdpFtdcVolumeType	AskVolume10;
	///申买价十
	TQdpFtdcPriceType	BidPrice10;
	///申买量十
	TQdpFtdcVolumeType	BidVolume10;
};

///订阅合约的相关信息
struct CQdpFtdcSpecificInstrumentField
{
	///合约代码
	TQdpFtdcInstrumentIDType	InstrumentID;
};

///共享内存行情查询
struct CQdpFtdcShmDepthMarketDataField
{
	///合约代码
	TQdpFtdcInstrumentIDType	InstrumentID;
	///IP地址
	TQdpFtdcIPAddressType	IPAddress;
	///订阅号
	TQdpFtdcTopicIDType	TopicID;
};

///交易所代码
struct CQdpFtdcMarketDataExchangeIDField
{
	///交易所代码
	TQdpFtdcExchangeIDType	ExchangeID;
};

///TOPIC查询
struct CQdpFtdcTopicSearchField
{
	///订阅号
	TQdpFtdcTopicIDType	TopicID;
};

///合约状态
struct CQdpFtdcQmdInstrumentStateField
{
	///交易所代码
	TQdpFtdcExchangeIDType	ExchangeID;
	///合约代码
	TQdpFtdcInstrumentIDType	InstrumentID;
	///合约交易状态
	TQdpFtdcInstrumentStatusType	InstrumentStatus;
};

///行情申卖六七属性
struct CQdpFtdcMarketDataAsk67Field
{
	///申卖价六
	TQdpFtdcPriceType	AskPrice6;
	///申卖量六
	TQdpFtdcVolumeType	AskVolume6;
	///申卖价七
	TQdpFtdcPriceType	AskPrice7;
	///申卖量七
	TQdpFtdcVolumeType	AskVolume7;
};

///行情申卖八九属性
struct CQdpFtdcMarketDataAsk89Field
{
	///申卖价八
	TQdpFtdcPriceType	AskPrice8;
	///申卖量八
	TQdpFtdcVolumeType	AskVolume8;
	///申卖价九
	TQdpFtdcPriceType	AskPrice9;
	///申卖量九
	TQdpFtdcVolumeType	AskVolume9;
};

///行情申买六七属性
struct CQdpFtdcMarketDataBid67Field
{
	///申买价六
	TQdpFtdcPriceType	BidPrice6;
	///申买量六
	TQdpFtdcVolumeType	BidVolume6;
	///申买价七
	TQdpFtdcPriceType	BidPrice7;
	///申买量七
	TQdpFtdcVolumeType	BidVolume7;
};

///行情申买八九属性
struct CQdpFtdcMarketDataBid89Field
{
	///申买价八
	TQdpFtdcPriceType	BidPrice8;
	///申买量八
	TQdpFtdcVolumeType	BidVolume8;
	///申买价九
	TQdpFtdcPriceType	BidPrice9;
	///申买量九
	TQdpFtdcVolumeType	BidVolume9;
};

///行情申买申卖十属性
struct CQdpFtdcMarketDataAskBid10Field
{
	///申卖价十
	TQdpFtdcPriceType	AskPrice10;
	///申卖量十
	TQdpFtdcVolumeType	AskVolume10;
	///申买价十
	TQdpFtdcPriceType	BidPrice10;
	///申买量十
	TQdpFtdcVolumeType	BidVolume10;
};

///用户采集信息
struct CQdpFtdcUserSystemInfoField
{
	///经纪公司编号
	TQdpFtdcBrokerIDType	BrokerID;
	///用户代码
	TQdpFtdcUserIDType	UserID;
	///信息长度
	TQdpFtdcSystemInfoLenType	ClientSystemInfoLen;
	///信息内容
	TQdpFtdcClientSystemInfoType	ClientSystemInfo;
	///客户ip
	TQdpFtdcIPAddressType	ClientPublicIP;
	///客户端口
	TQdpFtdcIPPortType	ClientIPPort;
	///登录时间
	TQdpFtdcFullLoginTimeType	ClientLoginTime;
	///客户认证appid
	TQdpFtdcAppIDType	ClientAppID;
};

///请求认证系统信息
struct CQdpFtdcAuthenticateField
{
	///经纪公司编号
	TQdpFtdcBrokerIDType	BrokerID;
	///用户代码
	TQdpFtdcUserIDType	UserID;
	///接入版本信息
	TQdpFtdcProductInfoType	UserProductInfo;
	///客户认证appid
	TQdpFtdcAppIDType	AppID;
	///接入认证id
	TQdpFtdcPasswordType	AuthCode;
};

///返回认证系统信息
struct CQdpFtdcRtnAuthenticateField
{
	///经纪公司编号
	TQdpFtdcBrokerIDType	BrokerID;
	///用户代码
	TQdpFtdcUserIDType	UserID;
	///接入版本信息
	TQdpFtdcProductInfoType	UserProductInfo;
	///客户认证appid
	TQdpFtdcAppIDType	AppID;
	///Socket编号
	TQdpFtdcNumberType	SockID;
	///客户接入类型
	TQdpFtdcAppTypeType	AppType;
};

///返回认证公钥
struct CQdpFtdcRSAPubKeyField
{
	///认证公钥
	TQdpFtdcSecKeyInfoType	SecKeyInfo;
};

///Full Market Data
struct CQdpFtdcClientDepthMarketDataField
{
	///Client ID
	TQdpFtdcClientIDType	ClientID;
	///交易所代码
	TQdpFtdcExchangeIDType	ExchangeID;
	///交易日
	TQdpFtdcTradingDayType	TradingDay;
	///结算组代码
	TQdpFtdcSettlementGroupIDType	SettlementGroupID;
	///结算编号
	TQdpFtdcSettlementIDType	SettlementID;
	///昨结算
	TQdpFtdcPriceType	PreSettlementPrice;
	///昨收盘
	TQdpFtdcPriceType	PreClosePrice;
	///昨持仓量
	TQdpFtdcLargeVolumeType	PreOpenInterest;
	///昨虚实度
	TQdpFtdcRatioType	PreDelta;
	///今开盘
	TQdpFtdcPriceType	OpenPrice;
	///最高价
	TQdpFtdcPriceType	HighestPrice;
	///最低价
	TQdpFtdcPriceType	LowestPrice;
	///今收盘
	TQdpFtdcPriceType	ClosePrice;
	///涨停板价
	TQdpFtdcPriceType	UpperLimitPrice;
	///跌停板价
	TQdpFtdcPriceType	LowerLimitPrice;
	///今结算
	TQdpFtdcPriceType	SettlementPrice;
	///今虚实度
	TQdpFtdcRatioType	CurrDelta;
	///最新价
	TQdpFtdcPriceType	LastPrice;
	///数量
	TQdpFtdcVolumeType	Volume;
	///成交金额
	TQdpFtdcMoneyType	Turnover;
	///持仓量
	TQdpFtdcLargeVolumeType	OpenInterest;
	///申买价一
	TQdpFtdcPriceType	BidPrice1;
	///申买量一
	TQdpFtdcVolumeType	BidVolume1;
	///申卖价一
	TQdpFtdcPriceType	AskPrice1;
	///申卖量一
	TQdpFtdcVolumeType	AskVolume1;
	///合约代码
	TQdpFtdcInstrumentIDType	InstrumentID;
	///最后修改时间
	TQdpFtdcTimeType	UpdateTime;
	///最后修改毫秒
	TQdpFtdcMillisecType	UpdateMillisec;
};

///流水状态
struct CQdpFtdcFlowStatusField
{
	///序列系列号
	TQdpFtdcSequenceSeriesType	SequenceSeries;
	///是否就绪
	TQdpFtdcBoolType	bReady;
};



#endif
