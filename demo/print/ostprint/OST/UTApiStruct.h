#pragma once

#include "UTApiDataType.h"


///期权合约保证金率
struct CUTOptionInstrMarginRateField
{
	///交易所代码
	TUTExchangeIDType	ExchangeID;
	///合约代码
	TUTInstrumentIDType	InstrumentID;
	///投资者范围
	TUTInvestorRangeType	InvestorRange;
	///投资者代码
	TUTInvestorIDType	InvestorID;
	///投机套保标志
	TUTHedgeFlagType	HedgeFlag;
	///保证金调整系数
	TUTRatioType	MarginRatioByMoney;
	///保证金调整系数
	TUTMoneyType	MarginRatioByVolume;
};
///手续费率
struct CUTInstrumentCommissionRateField
{
	///交易所代码
	TUTExchangeIDType	ExchangeID;
	///合约代码
	TUTInstrumentIDType	InstrumentID;
	///投资者范围
	TUTInvestorRangeType	InvestorRange;
	///投资者代码
	TUTInvestorIDType	InvestorID;
	///投机套保标志
	TUTHedgeFlagType	HedgeFlag;
	///持仓方向
	TUTPosiDirectionType	PosiDirection;
	///开仓手续费率
	TUTRatioType	OpenRatioByMoney;
	///开仓手续费
	TUTRatioType	OpenRatioByVolume;
	///平仓手续费率
	TUTRatioType	CloseRatioByMoney;
	///平仓手续费
	TUTRatioType	CloseRatioByVolume;
	///平今手续费率
	TUTRatioType	CloseTodayRatioByMoney;
	///平今手续费
	TUTRatioType	CloseTodayRatioByVolume;
	///开仓税率
	TUTRatioType	OpenTaxRatioByMoney;
	///开仓税率
	TUTRatioType	OpenTaxRatioByVolume;
	///平仓税率
	TUTRatioType	CloseTaxRatioByMoney;
	///平仓税率
	TUTRatioType	CloseTaxRatioByVolume;
	///手续费按笔数
	TUTMoneyType	CommByOrder;
	///每笔报单最低手续费(不包含CommByOrder)
	TUTMoneyType	MinCommByOrder;
};
///资金
struct CUTTradingAccountField
{
	///投资者帐号
	TUTAccountIDType	AccountID;
	///币种代码
	TUTCurrencyIDType	CurrencyID;
	///账户类型
	TUTAccTypeType	AccType;
	///交易日
	TUTDateType	TradingDay;
	///上次质押金额
	TUTMoneyType	PreMortgage;
	///上次信用额度
	TUTMoneyType	PreCredit;
	///上次存款额
	TUTMoneyType	PreDeposit;
	///上次结算准备金
	TUTMoneyType	PreBalance;
	///上次占用的保证金
	TUTMoneyType	PreMargin;
	///利息基数
	TUTMoneyType	InterestBase;
	///利息收入
	TUTMoneyType	Interest;
	///入金金额
	TUTMoneyType	Deposit;
	///出金金额
	TUTMoneyType	Withdraw;
	///冻结的保证金
	TUTMoneyType	FrozenMargin;
	///冻结的资金
	TUTMoneyType	FrozenCash;
	///冻结的手续费
	TUTMoneyType	FrozenCommission;
	///当前保证金总额
	TUTMoneyType	CurrMargin;
	///资金差额
	TUTMoneyType	CashIn;
	///手续费
	TUTMoneyType	Commission;
	///平仓盈亏
	TUTMoneyType	CloseProfit;
	///持仓盈亏
	TUTMoneyType	PositionProfit;
	///期货结算准备金
	TUTMoneyType	Balance;
	///可用资金
	TUTMoneyType	Available;
	///可取资金
	TUTMoneyType	WithdrawQuota;
	///基本准备金
	TUTMoneyType	Reserve;
	///信用额度
	TUTMoneyType	Credit;
	///质押金额
	TUTMoneyType	Mortgage;
	///投资者交割保证金
	TUTMoneyType	DeliveryMargin;
	///税费
	TUTMoneyType	Tax;
	///融资金额
	TUTMoneyType	CreditFund;
	///冻结的融资金额
	TUTMoneyType	CreditFundFrozen;
	///融券金额
	TUTMoneyType	CreditStock;
	///冻结的融券金额
	TUTMoneyType	CreditStockFrozen;
	///保证金可用余额
	TUTMoneyType	CreditAvailable;
	///保证金余额变量
	TUTMoneyType	CreditAvailableParam;
	///融券平仓冻结(计算保证金可用余额和非高流通开仓可用)
	TUTMoneyType	CreditStockCloseFrozen;
	///担保品买入冻结偏移(计算保证金可用余额)
	TUTMoneyType	CreditCollBuyFrozenOffset;
	///高流通证券开仓成本
	TUTMoneyType	CreditLiquidCost;
	///融资融券利息(计算保证金可用余额和还款)
	TUTMoneyType	CreditInterest;
	///证券市值
	TUTMoneyType	CreditTotalValue;
	///融券当前市值
	TUTMoneyType	CreditStockValue;
	///今日已还融资金额(包括利息)
	TUTMoneyType	CreditFundPayback;
	///融资融券未结利息(不可还)
	TUTMoneyType	CreditInterestProcess;
	///今日融资手续费(不可还)
	TUTMoneyType	CreditFundCommission;
};
///持仓
struct CUTInvestorPositionField
{
	///投资者代码
	TUTInvestorIDType	InvestorID;
	///交易所代码
	TUTExchangeIDType	ExchangeID;
	///合约代码
	TUTInstrumentIDType	InstrumentID;
	///投机套保标志
	TUTHedgeFlagType	HedgeFlag;
	///持仓多空方向
	TUTPosiDirectionType	PosiDirection;
	///上日持仓
	TUTLargeVolumeType	YdPosition;
	///总持仓
	TUTLargeVolumeType	Position;
	///多头冻结
	TUTLargeVolumeType	LongFrozen;
	///空头冻结
	TUTLargeVolumeType	ShortFrozen;
	///多头冻结金额
	TUTMoneyType	LongFrozenAmount;
	///空头冻结金额
	TUTMoneyType	ShortFrozenAmount;
	///开仓量
	TUTLargeVolumeType	OpenVolume;
	///平仓量
	TUTLargeVolumeType	CloseVolume;
	///开仓金额
	TUTMoneyType	OpenAmount;
	///平仓金额
	TUTMoneyType	CloseAmount;
	///持仓成本
	TUTMoneyType	PositionCost;
	///占用的保证金
	TUTMoneyType	UseMargin;
	///冻结的保证金
	TUTMoneyType	FrozenMargin;
	///冻结的资金
	TUTMoneyType	FrozenCash;
	///冻结的手续费
	TUTMoneyType	FrozenCommission;
	///资金差额
	TUTMoneyType	CashIn;
	///手续费
	TUTMoneyType	Commission;
	///平仓盈亏
	TUTMoneyType	CloseProfit;
	///持仓盈亏
	TUTMoneyType	PositionProfit;
	///上次结算价
	TUTPriceType	PreSettlementPrice;
	///本次结算价
	TUTPriceType	SettlementPrice;
	///交易日
	TUTDateType	TradingDay;
	///开仓成本
	TUTMoneyType	OpenCost;
	///组合成交形成的持仓
	TUTLargeVolumeType	CombPosition;
	///逐日盯市平仓盈亏
	TUTMoneyType	CloseProfitByDate;
	///逐笔对冲平仓盈亏
	TUTMoneyType	CloseProfitByTrade;
	///今日持仓
	TUTLargeVolumeType	TodayPosition;
	///每手保证金
	TUTRatioType	MarginByVolume;
	///执行冻结
	TUTLargeVolumeType	StrikeFrozen;
	///执行冻结金额
	TUTMoneyType	StrikeFrozenAmount;
	///放弃执行冻结
	TUTLargeVolumeType	AbandonFrozen;
	///融资金额
	TUTMoneyType	CreditFund;
	///ETF申赎持仓(记入总持仓)
	TUTLargeVolumeType	RedemptionPosition;
	///申赎或直接还券造成的冻结
	TUTLargeVolumeType	RedemptionFrozen;
	///买卖造成的ETF申赎持仓冻结
	TUTLargeVolumeType	RedemptionPositionFrozen;
	///融资数量
	TUTMoneyType	CreditFundVolume;
	///融资今仓手续费(不可还)
	TUTMoneyType	CreditFundCommission;
};
///行情
struct CUTDepthMarketDataField
{
	///交易所代码
	TUTExchangeIDType	ExchangeID;
	///合约代码
	TUTInstrumentIDType	InstrumentID;
	///交易日
	TUTDateType	TradingDay;
	///上次结算价;基金为上一日净值
	TUTPriceType	PreSettlementPrice;
	///昨收盘
	TUTPriceType	PreClosePrice;
	///昨持仓量
	TUTLargeVolumeType	PreOpenInterest;
	///涨停板价
	TUTPriceType	UpperLimitPrice;
	///跌停板价
	TUTPriceType	LowerLimitPrice;
	///自然日
	TUTDateType	ActionDay;
	///最后修改时间
	TUTTimeType	UpdateTime;
	///今开盘
	TUTPriceType	OpenPrice;
	///今收盘
	TUTPriceType	ClosePrice;
	///本次结算价;基金为实时参考净值
	TUTPriceType	SettlementPrice;
	///最高价
	TUTPriceType	HighestPrice;
	///最低价
	TUTPriceType	LowestPrice;
	///合约交易状态
	TUTInstrumentStatusType	InstrumentStatus;
	///最新价
	TUTPriceType	LastPrice;
	///数量
	TUTLargeVolumeType	Volume;
	///成交金额
	TUTMoneyType	Turnover;
	///持仓量
	TUTLargeVolumeType	OpenInterest;
	///申买价一
	TUTPriceType	BidPrice1;
	///申卖价一
	TUTPriceType	AskPrice1;
	///申买量一
	TUTLargeVolumeType	BidVolume1;
	///申卖量一
	TUTLargeVolumeType	AskVolume1;
	///申买价二
	TUTPriceType	BidPrice2;
	///申卖价二
	TUTPriceType	AskPrice2;
	///申买量二
	TUTLargeVolumeType	BidVolume2;
	///申卖量二
	TUTLargeVolumeType	AskVolume2;
	///申买价三
	TUTPriceType	BidPrice3;
	///申卖价三
	TUTPriceType	AskPrice3;
	///申买量三
	TUTLargeVolumeType	BidVolume3;
	///申卖量三
	TUTLargeVolumeType	AskVolume3;
	///申买价四
	TUTPriceType	BidPrice4;
	///申卖价四
	TUTPriceType	AskPrice4;
	///申买量四
	TUTLargeVolumeType	BidVolume4;
	///申卖量四
	TUTLargeVolumeType	AskVolume4;
	///申买价五
	TUTPriceType	BidPrice5;
	///申卖价五
	TUTPriceType	AskPrice5;
	///申买量五
	TUTLargeVolumeType	BidVolume5;
	///申卖量五
	TUTLargeVolumeType	AskVolume5;
};
///合约
struct CUTInstrumentField
{
	///交易所代码
	TUTExchangeIDType	ExchangeID;
	///合约代码
	TUTInstrumentIDType	InstrumentID;
	///合约名称
	TUTInstrumentNameType	InstrumentName;
	///产品代码
	TUTProductIDType	ProductID;
	///产品类型
	TUTProductClassType	ProductClass;
	///交割年份
	TUTYearType	DeliveryYear;
	///交割月
	TUTMonthType	DeliveryMonth;
	///市价单最大下单量
	TUTVolumeType	MaxMarketOrderVolume;
	///市价单最小下单量
	TUTVolumeType	MinMarketOrderVolume;
	///限价单最大下单量
	TUTVolumeType	MaxLimitOrderVolume;
	///限价单最小下单量
	TUTVolumeType	MinLimitOrderVolume;
	///合约数量乘数
	TUTVolumeMultipleType	VolumeMultiple;
	///最小变动价位
	TUTPriceType	PriceTick;
	///创建日
	TUTDateType	CreateDate;
	///上市日
	TUTDateType	OpenDate;
	///到期日
	TUTDateType	ExpireDate;
	///开始交割日
	TUTDateType	StartDelivDate;
	///结束交割日
	TUTDateType	EndDelivDate;
	///当前是否交易
	TUTBoolType	IsTrading;
	///合约生命周期状态
	TUTInstLifePhaseType	InstLifePhase;
	///持仓类型
	TUTPositionTypeType	PositionType;
	///持仓日期类型
	TUTPositionDateTypeType	PositionDateType;
	///是否使用大额单边保证金算法
	TUTMaxMarginSideAlgorithmType	MaxMarginSideAlgorithm;
	///期权类型
	TUTOptionsTypeType	OptionsType;
	///组合类型
	TUTCombinationTypeType	CombinationType;
	///基础商品代码;证券时表示子类别,期权时表示标的
	TUTInstrumentIDType	UnderlyingInstrID;
	///执行价
	TUTPriceType	StrikePrice;
	///合约基础商品乘数;个股期权表示交易所每手保证金
	TUTUnderlyingMultipleType	UnderlyingMultiple;
	///限价单最小买下单单位
	TUTVolumeType	MinBuyVolume;
	///限价单最小卖下单单位
	TUTVolumeType	MinSellVolume;
	///合约标识码;证券时内部使用,个股期权时表示合约英文名
	TUTInstrumentCodeType	InstrumentCode;
	///币种代码
	TUTCurrencyIDType	CurrencyID;
	///市价单最小买下单单位;个股期权表示参数1放大1000倍
	TUTVolumeType	MinMarketBuyVolume;
	///市价单最小卖下单单位;个股期权表示参数2放大1000倍
	TUTVolumeType	MinMarketSellVolume;
};
///投资者
struct CUTInvestorField
{
	///投资者代码
	TUTInvestorIDType	InvestorID;
	///投资者分组代码
	TUTInvestorIDType	InvestorGroupID;
	///投资者名称
	TUTPartyNameType	InvestorName;
	///证件类型
	TUTIdCardTypeType	IdentifiedCardType;
	///证件号码
	TUTIdentifiedCardNoType	IdentifiedCardNo;
	///是否活跃
	TUTBoolType	IsActive;
	///联系电话
	TUTTelephoneType	Telephone;
	///通讯地址
	TUTAddressType	Address;
	///开户日期
	TUTDateType	OpenDate;
	///手机
	TUTMobileType	Mobile;
	///手续费率模板代码
	TUTInvestorIDType	CommModelID;
	///保证金率模板代码
	TUTInvestorIDType	MarginModelID;
	///组织架构代码
	TUTInvestorIDType	DepartmentID;
	///投资者终端认证分组代码
	TUTInvestorIDType	AuthGroupID;
	///投资者合约交易权限分组代码
	TUTInvestorIDType	TradingRightGroupID;
	///投资者安装编号
	TUTInstallIDType	InvestorInstallID;
};
///期权手续费率
struct CUTOptionInstrCommRateField
{
	///交易所代码
	TUTExchangeIDType	ExchangeID;
	///合约代码
	TUTInstrumentIDType	InstrumentID;
	///投资者范围
	TUTInvestorRangeType	InvestorRange;
	///投资者代码
	TUTInvestorIDType	InvestorID;
	///投机套保标志
	TUTHedgeFlagType	HedgeFlag;
	///持仓方向
	TUTPosiDirectionType	PosiDirection;
	///开仓手续费率
	TUTRatioType	OpenRatioByMoney;
	///开仓手续费
	TUTRatioType	OpenRatioByVolume;
	///平仓手续费率
	TUTRatioType	CloseRatioByMoney;
	///平仓手续费
	TUTRatioType	CloseRatioByVolume;
	///平今手续费率
	TUTRatioType	CloseTodayRatioByMoney;
	///平今手续费
	TUTRatioType	CloseTodayRatioByVolume;
	///执行手续费率
	TUTRatioType	StrikeRatioByMoney;
	///执行手续费
	TUTRatioType	StrikeRatioByVolume;
	///佣金按笔数
	TUTMoneyType	CommByOrder;
};
///交易所
struct CUTExchangeField
{
	///交易所代码
	TUTExchangeIDType	ExchangeID;
	///交易所名称
	TUTExchangeNameType	ExchangeName;
};
///经纪公司用户口令
struct CUTBrokerUserPasswordField
{
	///用户代码
	TUTUserIDType	UserID;
	///密码
	TUTPasswordType	Password;
	///用户名称
	TUTUserNameType	UserName;
	///用户类型
	TUTUserTypeType	UserType;
	///是否活跃
	TUTBoolType	IsActive;
};
///交易所交易员信息
struct CUTTraderField
{
	///交易所代码
	TUTExchangeIDType	ExchangeID;
	///会员代码
	TUTParticipantIDType	ParticipantID;
	///交易所交易员代码
	TUTTraderIDType	TraderID;
	///交易员类型
	TUTTraderClassType	TraderClass;
	///业务类型
	TUTBizTypeType	BizType;
	///密码
	TUTPasswordType	Password;
	///安装编号
	TUTInstallIDType	InstallID;
	///本地报单编号
	TUTOrderLocalIDType	OrderLocalID;
	///交易所交易日
	TUTDateType	TradingDay;
	///交易所数据中心号
	TUTDataCenterIDType	DataCenterID;
	///交易所交易员连接状态
	TUTTraderConnectStatusType	TraderConnectStatus;
};
///操作员组织架构关系
struct CUTDepartmentUserField
{
	///用户代码
	TUTUserIDType	UserID;
	///投资者范围
	TUTDepartmentRangeType	InvestorRange;
	///投资者代码
	TUTInvestorIDType	InvestorID;
};
///交易编码
struct CUTTradingCodeField
{
	///投资者代码
	TUTInvestorIDType	InvestorID;
	///交易所代码
	TUTExchangeIDType	ExchangeID;
	///客户代码
	TUTClientIDType	ClientID;
	///是否活跃
	TUTBoolType	IsActive;
	///交易编码类型
	TUTClientIDTypeType	ClientIDType;
	///营业部编号
	TUTBranchIDType	BranchID;
	///营业部前缀编号
	TUTBranchIDType	PreBranchID;
	///所属营业部
	TUTBranchIDType	DepartmentBranchID;
};
///会员编码和经纪公司编码对照表
struct CUTPartBrokerField
{
	///交易所代码
	TUTExchangeIDType	ExchangeID;
	///会员代码
	TUTParticipantIDType	ParticipantID;
	///是否活跃
	TUTBoolType	IsActive;
};
///E+1日行权冻结
struct CUTExecFreezeField
{
	///投资者代码
	TUTInvestorIDType	InvestorID;
	///交易所代码
	TUTExchangeIDType	ExchangeID;
	///标的合约代码
	TUTInstrumentIDType	InstrumentID;
	///持仓多空方向
	TUTPosiDirectionType	PosiDirection;
	///期权类型
	TUTOptionsTypeType	OptionsType;
	///冻结的数量_单位股
	TUTVolumeType	Volume;
	///冻结金额
	TUTMoneyType	FrozenAmount;
};
///逐笔委托行情
struct CUTL2OrderField
{
	///交易所代码
	TUTExchangeIDType	ExchangeID;
	///合约代码
	TUTInstrumentIDType	InstrumentID;
	///自然日
	TUTDateType	ActionDay;
	///时间
	TUTTimeType	Time;
	///逐笔行情频道
	TUTChannelNoType	ChannelNo;
	///序号
	TUTSequenceNoType	SequenceNo;
	///价格
	TUTPriceType	Price;
	///数量
	TUTVolumeType	Volume;
	///买卖方向
	TUTDirectionType	Direction;
	///价格类型
	TUTOrderPriceTypeType	OrderPriceType;
};
///逐笔成交行情
struct CUTL2TradeField
{
	///交易所代码
	TUTExchangeIDType	ExchangeID;
	///合约代码
	TUTInstrumentIDType	InstrumentID;
	///自然日
	TUTDateType	ActionDay;
	///时间
	TUTTimeType	Time;
	///逐笔行情频道
	TUTChannelNoType	ChannelNo;
	///序号
	TUTSequenceNoType	SequenceNo;
	///价格
	TUTPriceType	Price;
	///数量
	TUTVolumeType	Volume;
	///成交类别
	TUTTradeExecTypeType	TradeExecType;
	///内外盘标志
	TUTBSFlagType	BSFlag;
	///买方委托序号
	TUTSequenceNoType	BidSequenceNo;
	///卖方委托序号
	TUTSequenceNoType	AskSequenceNo;
};
///主中心
struct CUTMainCenterField
{
	///主中心号
	TUTDRIdentityIDType	DRIdentityID;
};
///交易参数
struct CUTTradeParamField
{
	///参数代码
	TUTTradeParamIDType	TradeParamID;
	///参数代码值
	TUTTradeParamValueType	TradeParamValue;
};
///终端认证口令
struct CUTAuthPasswordField
{
	///用户端产品信息
	TUTProductInfoType	UserProductInfo;
	///用户端认证码
	TUTPasswordType	UserProductPassword;
};
///客户端认证授权表
struct CUTAuthInvestorField
{
	///投资者范围
	TUTInvestorRangeType	InvestorRange;
	///投资者代码
	TUTInvestorIDType	InvestorID;
	///用户端产品信息
	TUTProductInfoType	UserProductInfo;
};
///终端IP限制表
struct CUTAuthIPField
{
	///用户端产品信息
	TUTProductInfoType	UserProductInfo;
	///IP地址
	TUTIPAddressType	IPAddress;
	///IP地址掩码
	TUTIPAddressType	IPMask;
	///Mac地址
	TUTMacAddressType	MacAddress;
};
///合约交易模式
struct CUTInstrumentTradingModeField
{
	///合约代码
	TUTInstrumentIDType	InstrumentID;
	///交易所代码
	TUTExchangeIDType	ExchangeID;
	///合约交易模式
	TUTTradingModeType	TradingMode;
};
///投资者合约交易权限
struct CUTInstrumentTradingRightField
{
	///交易所代码
	TUTExchangeIDType	ExchangeID;
	///合约代码
	TUTInstrumentIDType	InstrumentID;
	///投资者范围
	TUTInvestorRangeType	InvestorRange;
	///投资者代码
	TUTInvestorIDType	InvestorID;
	///投机套保标志
	TUTHedgeFlagType	HedgeFlag;
	///交易权限
	TUTTradingRightType	TradingRight;
};
///行情时间
struct CUTMarketDataUpdateTimeField
{
	///自然日
	TUTDateType	ActionDay;
	///最后修改时间
	TUTTimeType	UpdateTime;
};
///静态行情
struct CUTMarketDataStaticField
{
	///今开盘
	TUTPriceType	OpenPrice;
	///今收盘
	TUTPriceType	ClosePrice;
	///本次结算价;基金为实时参考净值
	TUTPriceType	SettlementPrice;
	///最高价
	TUTPriceType	HighestPrice;
	///最低价
	TUTPriceType	LowestPrice;
	///合约交易状态
	TUTInstrumentStatusType	InstrumentStatus;
};
///行情最新成交
struct CUTMarketDataLastMatchField
{
	///最新价
	TUTPriceType	LastPrice;
	///数量
	TUTLargeVolumeType	Volume;
	///成交金额
	TUTMoneyType	Turnover;
	///持仓量
	TUTLargeVolumeType	OpenInterest;
};
///最优行情
struct CUTMarketDataBestPriceField
{
	///申买价一
	TUTIntPriceType	BidPrice1;
	///申卖价一
	TUTIntPriceType	AskPrice1;
	///申买量一
	TUTLargeVolumeType	BidVolume1;
	///申卖量一
	TUTLargeVolumeType	AskVolume1;
};
///最优行情
struct CUTL2MarketDataBestPriceField
{
	///申买价一
	TUTIntPriceType	BidPrice1;
	///申卖价一
	TUTIntPriceType	AskPrice1;
	///申买量一
	TUTLargeVolumeType	BidVolume1;
	///申卖量一
	TUTLargeVolumeType	AskVolume1;
	///申买报单量一
	TUTVolumeType	BidOrderVolume1;
	///申卖报单量一
	TUTVolumeType	AskOrderVolume1;
};
///核心需要的更新行情
struct CUTMarketDataForKernelField
{
	///交易所代码
	TUTExchangeIDType	ExchangeID;
	///合约代码
	TUTInstrumentIDType	InstrumentID;
	///自然日
	TUTDateType	ActionDay;
	///最后修改时间
	TUTTimeType	UpdateTime;
	///合约交易状态
	TUTInstrumentStatusType	InstrumentStatus;
	///最新价
	TUTPriceType	LastPrice;
};
///变动的L2行情
struct CUTVariableL2DepthMarketDataField
{
	///自然日
	TUTDateType	ActionDay;
	///最后修改时间
	TUTTimeType	UpdateTime;
	///今开盘
	TUTIntPriceType	OpenPrice;
	///今收盘
	TUTIntPriceType	ClosePrice;
	///本次结算价;基金为实时参考净值
	TUTIntPriceType	SettlementPrice;
	///最高价
	TUTIntPriceType	HighestPrice;
	///最低价
	TUTIntPriceType	LowestPrice;
	///合约交易状态
	TUTInstrumentStatusType	InstrumentStatus;
	///最新价
	TUTIntPriceType	LastPrice;
	///数量
	TUTLargeVolumeType	Volume;
	///成交金额
	TUTMoneyType	Turnover;
	///持仓量
	TUTLargeVolumeType	OpenInterest;
	///申买价一
	TUTIntPriceType	BidPrice1;
	///申卖价一
	TUTIntPriceType	AskPrice1;
	///申买量一
	TUTLargeVolumeType	BidVolume1;
	///申卖量一
	TUTLargeVolumeType	AskVolume1;
	///申买报单量一
	TUTVolumeType	BidOrderVolume1;
	///申卖报单量一
	TUTVolumeType	AskOrderVolume1;
};
///变动的行情
struct CUTVariableDepthMarketDataField
{
	///自然日
	TUTDateType	ActionDay;
	///最后修改时间
	TUTTimeType	UpdateTime;
	///今开盘
	TUTIntPriceType	OpenPrice;
	///今收盘
	TUTIntPriceType	ClosePrice;
	///本次结算价;基金为实时参考净值
	TUTIntPriceType	SettlementPrice;
	///最高价
	TUTIntPriceType	HighestPrice;
	///最低价
	TUTIntPriceType	LowestPrice;
	///合约交易状态
	TUTInstrumentStatusType	InstrumentStatus;
	///最新价
	TUTIntPriceType	LastPrice;
	///数量
	TUTLargeVolumeType	Volume;
	///成交金额
	TUTMoneyType	Turnover;
	///持仓量
	TUTLargeVolumeType	OpenInterest;
	///申买价一
	TUTIntPriceType	BidPrice1;
	///申卖价一
	TUTIntPriceType	AskPrice1;
	///申买量一
	TUTLargeVolumeType	BidVolume1;
	///申卖量一
	TUTLargeVolumeType	AskVolume1;
	///申买价二
	TUTIntPriceType	BidPrice2;
	///申卖价二
	TUTIntPriceType	AskPrice2;
	///申买量二
	TUTLargeVolumeType	BidVolume2;
	///申卖量二
	TUTLargeVolumeType	AskVolume2;
	///申买价三
	TUTIntPriceType	BidPrice3;
	///申卖价三
	TUTIntPriceType	AskPrice3;
	///申买量三
	TUTLargeVolumeType	BidVolume3;
	///申卖量三
	TUTLargeVolumeType	AskVolume3;
	///申买价四
	TUTIntPriceType	BidPrice4;
	///申卖价四
	TUTIntPriceType	AskPrice4;
	///申买量四
	TUTLargeVolumeType	BidVolume4;
	///申卖量四
	TUTLargeVolumeType	AskVolume4;
	///申买价五
	TUTIntPriceType	BidPrice5;
	///申卖价五
	TUTIntPriceType	AskPrice5;
	///申买量五
	TUTLargeVolumeType	BidVolume5;
	///申卖量五
	TUTLargeVolumeType	AskVolume5;
};
///交易中心
struct CUTCenterField
{
	///中心号
	TUTCenterIDType	CenterID;
	///中心名称
	TUTCenterNameType	CenterName;
};
///席位与交易中心对应关系
struct CUTTraderCenterField
{
	///交易所代码
	TUTExchangeIDType	ExchangeID;
	///交易所交易员代码
	TUTTraderIDType	TraderID;
	///中心号
	TUTCenterIDType	CenterID;
};
///资金分配
struct CUTFundDistributionField
{
	///投资者代码
	TUTInvestorIDType	InvestorID;
	///交易所代码
	TUTExchangeIDType	ExchangeID;
	///分配比例
	TUTRatioType	Ratio;
};
///税率
struct CUTTaxRateField
{
	///交易所代码
	TUTExchangeIDType	ExchangeID;
	///合约代码
	TUTInstrumentIDType	InstrumentID;
	///开仓税率
	TUTRatioType	OpenTaxRatioByMoney;
	///开仓税率
	TUTRatioType	OpenTaxRatioByVolume;
	///平仓税率
	TUTRatioType	CloseTaxRatioByMoney;
	///平仓税率
	TUTRatioType	CloseTaxRatioByVolume;
	///手续费按笔数
	TUTMoneyType	CommByOrder;
	///每笔报单最低手续费(不包含CommByOrder)
	TUTMoneyType	MinCommByOrder;
};
///投资者期权合约交易权限
struct CUTOptionInstrTradingRightField
{
	///交易所代码
	TUTExchangeIDType	ExchangeID;
	///合约代码
	TUTInstrumentIDType	InstrumentID;
	///投资者范围
	TUTInvestorRangeType	InvestorRange;
	///投资者代码
	TUTInvestorIDType	InvestorID;
	///投机套保标志
	TUTHedgeFlagType	HedgeFlag;
	///持仓方向
	TUTPosiDirectionType	PosiDirection;
	///交易权限
	TUTTradingRightType	TradingRight;
};
///期权保证金算法
struct CUTOptionMarginAlgoField
{
	///交易所代码
	TUTExchangeIDType	ExchangeID;
	///标的代码
	TUTInstrumentIDType	InstrumentID;
	///虚值额优惠比率,个股期权为参数1
	TUTRatioType	OutRatio;
	///最低保障系数,个股期权为参数2
	TUTRatioType	GuaranteeRatio;
};
///当前时间
struct CUTCurrentTimeField
{
	///当前日期
	TUTDateType	CurrDate;
	///当前时间
	TUTTimeType	CurrTime;
	///业务日期
	TUTDateType	ActionDay;
};
///响应信息
struct CUTRspInfoField
{
	///错误代码
	TUTErrorIDType	ErrorID;
	///错误信息
	TUTErrorMsgType	ErrorMsg;
};
///结算引用
struct CUTSettlementRefField
{
	///交易日
	TUTDateType	TradingDay;
};
///手工出入金
struct CUTSyncDepositField
{
	///出入金流水号
	TUTDepositSeqNoType	DepositSeqNo;
	///投资者代码
	TUTInvestorIDType	InvestorID;
	///入金金额
	TUTMoneyType	Deposit;
	///是否强制进行
	TUTBoolType	IsForce;
	///币种代码
	TUTCurrencyIDType	CurrencyID;
	///账户类型
	TUTAccTypeType	AccType;
};
///经纪公司用户功能权限
struct CUTBrokerUserFunctionField
{
	///用户代码
	TUTUserIDType	UserID;
	///经纪公司功能代码
	TUTBrokerFunctionCodeType	BrokerFunctionCode;
};
///交易日
struct CUTTradingDayField
{
	///交易日
	TUTDateType	TradingDay;
};
///同步持仓
struct CUTSyncInvestorPositionField
{
	///投资者代码
	TUTInvestorIDType	InvestorID;
	///交易所代码
	TUTExchangeIDType	ExchangeID;
	///合约代码
	TUTInstrumentIDType	InstrumentID;
	///投机套保标志
	TUTHedgeFlagType	HedgeFlag;
	///持仓多空方向
	TUTPosiDirectionType	PosiDirection;
	///昨持仓
	TUTLargeVolumeType	YdPosition;
};
///报单
struct CUTOrderField
{
	///投资者代码
	TUTInvestorIDType	InvestorID;
	///交易所代码
	TUTExchangeIDType	ExchangeID;
	///合约代码
	TUTInstrumentIDType	InstrumentID;
	///报单引用
	TUTOrderRefType	OrderRef;
	///买卖方向
	TUTDirectionType	Direction;
	///开平标志
	TUTOffsetFlagType	OffsetFlag;
	///投机套保标志
	TUTHedgeFlagType	HedgeFlag;
	///报单价格条件
	TUTOrderPriceTypeType	OrderPriceType;
	///数量
	TUTVolumeType	VolumeTotalOriginal;
	///价格
	TUTPriceType	LimitPrice;
	///有效期类型
	TUTTimeConditionType	TimeCondition;
	///成交量类型
	TUTVolumeConditionType	VolumeCondition;
	///触发条件
	TUTContingentConditionType	ContingentCondition;
	///GTD日期
	TUTDateType	GTDDate;
	///最小成交量
	TUTVolumeType	MinVolume;
	///自动挂起标志
	TUTBoolType	IsAutoSuspend;
	///用户强评标志
	TUTBoolType	UserForceClose;
	///止损价
	TUTPriceType	StopPrice;
	///互换单标志
	TUTBoolType	IsSwapOrder;
	///交易所交易员代码
	TUTTraderIDType	TraderID;
	///本地报单编号
	TUTOrderLocalIDType	OrderLocalID;
	///会员代码
	TUTParticipantIDType	ParticipantID;
	///客户代码
	TUTClientIDType	ClientID;
	///交易日
	TUTDateType	TradingDay;
	///用户端产品信息
	TUTProductInfoType	UserProductInfo;
	///营业部编号
	TUTBranchIDType	BranchID;
	///安装编号
	TUTInstallIDType	InstallID;
	///IP地址
	TUTIPAddressAsIntType	IPAddressAsInt;
	///Mac地址
	TUTMacAddressAsLongType	MacAddressAsLong;
	///报单编号
	TUTOrderSysIDType	OrderSysID;
	///报单状态
	TUTOrderStatusType	OrderStatus;
	///报单类型
	TUTOrderTypeType	OrderType;
	///今成交数量
	TUTVolumeType	VolumeTraded;
	///剩余数量
	TUTVolumeType	VolumeTotal;
	///报单日期
	TUTDateType	InsertDate;
	///委托时间
	TUTTimeType	InsertTime;
	///撤销时间
	TUTTimeType	CancelTime;
	///序号
	TUTSequenceNoType	SequenceNo;
	///前置编号
	TUTFrontIDType	FrontID;
	///会话编号
	TUTSessionIDType	SessionID;
	///交易所错误代码
	TUTExchangeErrorIDType	ExchangeErrorID;
};
///合约交易状态
struct CUTInstrumentStatusField
{
	///交易所代码
	TUTExchangeIDType	ExchangeID;
	///合约代码
	TUTInstrumentIDType	InstrumentID;
	///合约交易状态
	TUTInstrumentStatusType	InstrumentStatus;
	///进入本状态时间
	TUTTimeType	EnterTime;
	///进入本状态原因
	TUTInstStatusEnterReasonType	EnterReason;
	///序号
	TUTSequenceNoType	SequenceNo;
};
///成交
struct CUTTradeField
{
	///投资者代码
	TUTInvestorIDType	InvestorID;
	///交易所代码
	TUTExchangeIDType	ExchangeID;
	///合约代码
	TUTInstrumentIDType	InstrumentID;
	///报单引用
	TUTOrderRefType	OrderRef;
	///成交编号
	TUTTradeIDType	TradeID;
	///买卖方向
	TUTDirectionType	Direction;
	///报单编号
	TUTOrderSysIDType	OrderSysID;
	///客户代码
	TUTClientIDType	ClientID;
	///开平标志
	TUTOffsetFlagType	OffsetFlag;
	///投机套保标志
	TUTHedgeFlagType	HedgeFlag;
	///价格
	TUTPriceType	Price;
	///数量
	TUTVolumeType	Volume;
	///成交时期
	TUTDateType	TradeDate;
	///成交时间
	TUTTimeType	TradeTime;
	///成交类型
	TUTTradeTypeType	TradeType;
	///交易所交易员代码
	TUTTraderIDType	TraderID;
	///本地报单编号
	TUTOrderLocalIDType	OrderLocalID;
	///序号
	TUTSequenceNoType	SequenceNo;
	///交易日
	TUTDateType	TradingDay;
	///报盘安装编号
	TUTInstallIDType	InstallID;
	///前置编号
	TUTFrontIDType	FrontID;
	///会话编号
	TUTSessionIDType	SessionID;
};
///报单操作
struct CUTOrderActionField
{
	///报单操作引用
	TUTOrderRefType	OrderActionRef;
	///前置编号
	TUTFrontIDType	FrontID;
	///会话编号
	TUTSessionIDType	SessionID;
	///报单引用
	TUTOrderRefType	OrderRef;
	///操作标志
	TUTActionFlagType	ActionFlag;
	///价格
	TUTPriceType	LimitPrice;
	///数量变化
	TUTVolumeType	VolumeChange;
	///投资者代码
	TUTInvestorIDType	InvestorID;
	///交易所代码
	TUTExchangeIDType	ExchangeID;
	///报单编号
	TUTOrderSysIDType	OrderSysID;
	///合约代码
	TUTInstrumentIDType	InstrumentID;
	///操作日期
	TUTDateType	ActionDate;
	///操作时间
	TUTTimeType	ActionTime;
	///交易所交易员代码
	TUTTraderIDType	TraderID;
	///本地报单编号
	TUTOrderLocalIDType	OrderLocalID;
	///操作本地编号
	TUTOrderLocalIDType	ActionLocalID;
	///会员代码
	TUTParticipantIDType	ParticipantID;
	///客户代码
	TUTClientIDType	ClientID;
	///报单操作状态
	TUTOrderActionStatusType	OrderActionStatus;
	///买卖方向
	TUTDirectionType	Direction;
	///营业部编号
	TUTBranchIDType	BranchID;
	///报单类型
	TUTOrderTypeType	OrderType;
	///安装编号
	TUTInstallIDType	InstallID;
	///交易所错误信息
	TUTExchangeErrorIDType	ExchangeErrorID;
	///撤单前置编号
	TUTFrontIDType	ActionFrontID;
	///撤单会话编号
	TUTSessionIDType	ActionSessionID;
	///IP地址
	TUTIPAddressAsIntType	IPAddressAsInt;
	///Mac地址
	TUTMacAddressAsLongType	MacAddressAsLong;
};
///输入报单
struct CUTInputOrderField
{
	///投资者代码
	TUTInvestorIDType	InvestorID;
	///交易所代码
	TUTExchangeIDType	ExchangeID;
	///合约代码
	TUTInstrumentIDType	InstrumentID;
	///报单引用
	TUTOrderRefType	OrderRef;
	///买卖方向
	TUTDirectionType	Direction;
	///开平标志
	TUTOffsetFlagType	OffsetFlag;
	///投机套保标志
	TUTHedgeFlagType	HedgeFlag;
	///报单价格条件
	TUTOrderPriceTypeType	OrderPriceType;
	///数量
	TUTVolumeType	VolumeTotalOriginal;
	///价格
	TUTPriceType	LimitPrice;
	///有效期类型
	TUTTimeConditionType	TimeCondition;
	///成交量类型
	TUTVolumeConditionType	VolumeCondition;
	///触发条件
	TUTContingentConditionType	ContingentCondition;
	///GTD日期
	TUTDateType	GTDDate;
	///最小成交量
	TUTVolumeType	MinVolume;
	///自动挂起标志
	TUTBoolType	IsAutoSuspend;
	///用户强评标志
	TUTBoolType	UserForceClose;
	///止损价
	TUTPriceType	StopPrice;
	///互换单标志
	TUTBoolType	IsSwapOrder;
	///IP地址
	TUTIPAddressAsIntType	IPAddressAsInt;
	///Mac地址
	TUTMacAddressAsLongType	MacAddressAsLong;
};
///输入报单
struct CUTInputOrderActionField
{
	///报单操作引用
	TUTOrderRefType	OrderActionRef;
	///前置编号
	TUTFrontIDType	FrontID;
	///会话编号
	TUTSessionIDType	SessionID;
	///报单引用
	TUTOrderRefType	OrderRef;
	///操作标志
	TUTActionFlagType	ActionFlag;
	///价格
	TUTPriceType	LimitPrice;
	///数量变化
	TUTVolumeType	VolumeChange;
	///IP地址
	TUTIPAddressAsIntType	IPAddressAsInt;
	///Mac地址
	TUTMacAddressAsLongType	MacAddressAsLong;
};
///用户会话
struct CUTUserSessionField
{
	///用户代码
	TUTUserIDType	UserID;
	///密码
	TUTPasswordType	Password;
	///用户端产品信息
	TUTProductInfoType	UserProductInfo;
	///用户端认证码
	TUTPasswordType	UserProductPassword;
	///动态密码
	TUTPasswordType	OneTimePassword;
	///登录备注
	TUTLoginRemarkType	LoginRemark;
	///Mac地址
	TUTMacAddressType	MacAddress;
	///终端IP地址
	TUTIPAddressType	IPAddress;
	///私有流序号
	TUTSequenceNoType	PrivateSeq;
	///公有流序号
	TUTSequenceNoType	PublicSeq;
	///私有流交易日
	TUTDateType	TradingDay;
	///前置编号
	TUTFrontIDType	FrontID;
	///会话编号
	TUTSessionIDType	SessionID;
	///登录时间
	TUTTimeType	LoginTime;
	///系统名称
	TUTSystemNameType	SystemName;
	///用户类型
	TUTUserTypeType	UserType;
	///是否已登录
	TUTBoolType	IsLogin;
	///端口
	TUTIPPortType	Port;
	///终端信息(硬盘序列号32+内网IP15)
	TUTOriTerminalInfoType	OriTerminalInfo;
};
///用户登录应答
struct CUTRspLoginField
{
	///交易日
	TUTDateType	TradingDay;
	///登录成功时间
	TUTTimeType	LoginTime;
	///用户代码
	TUTUserIDType	UserID;
	///交易系统名称
	TUTSystemNameType	SystemName;
	///前置编号
	TUTFrontIDType	FrontID;
	///会话编号
	TUTSessionIDType	SessionID;
	///私有流序号
	TUTSequenceNoType	PrivateSeq;
	///公有流序号
	TUTSequenceNoType	PublicSeq;
	///组播地址
	TUTMultiAddressType	MultiAddress;
};
///订阅的合约
struct CUTSubInstrumentField
{
	///交易所代码
	TUTExchangeIDType	ExchangeID;
	///合约代码
	TUTInstrumentIDType	InstrumentID;
};
///指定录入
struct CUTInputDesignateField
{
	///投资者代码
	TUTInvestorIDType	InvestorID;
	///交易所代码
	TUTExchangeIDType	ExchangeID;
	///指定登记引用
	TUTOrderRefType	DesignateRef;
	///指定方向
	TUTDesignateTypeType	DesignateType;
	///交易所交易员代码
	TUTTraderIDType	TraderID;
	///深圳转托管转入交易员代码
	TUTTraderIDType	TransfereeTraderID;
	///深圳撤销转托管本地号
	TUTTraderIDType	OriDesignateLocalID;
};
///指定
struct CUTDesignateField
{
	///投资者代码
	TUTInvestorIDType	InvestorID;
	///交易所代码
	TUTExchangeIDType	ExchangeID;
	///指定登记引用
	TUTOrderRefType	DesignateRef;
	///指定方向
	TUTDesignateTypeType	DesignateType;
	///交易所交易员代码
	TUTTraderIDType	TraderID;
	///本地指定编号
	TUTOrderLocalIDType	DesignateLocalID;
	///会员代码
	TUTParticipantIDType	ParticipantID;
	///客户代码
	TUTClientIDType	ClientID;
	///指定/转托管状态
	TUTDesignateStatusType	DesignateStatus;
	///交易日
	TUTDateType	TradingDay;
	///报单日期
	TUTDateType	InsertDate;
	///插入时间
	TUTTimeType	InsertTime;
	///前置编号
	TUTFrontIDType	FrontID;
	///会话编号
	TUTSessionIDType	SessionID;
	///交易所错误代码
	TUTExchangeErrorIDType	ExchangeErrorID;
	///营业部编号
	TUTBranchIDType	BranchID;
	///序号
	TUTSequenceNoType	SequenceNo;
	///安装编号
	TUTInstallIDType	InstallID;
	///深圳转托管转入交易员代码
	TUTTraderIDType	TransfereeTraderID;
	///深圳被撤销转托管本地号
	TUTOrderLocalIDType	OriDesignateLocalID;
};
///用户登出请求
struct CUTReqLogoutField
{
	///用户代码
	TUTUserIDType	UserID;
};
///交易所返回报单
struct CUTExchangeOrderField
{
	///交易所代码
	TUTExchangeIDType	ExchangeID;
	///交易所交易员代码
	TUTTraderIDType	TraderID;
	///本地报单编号
	TUTOrderLocalIDType	OrderLocalID;
	///买卖方向
	TUTDirectionType	Direction;
	///报单编号
	TUTOrderSysIDType	OrderSysID;
	///报单状态
	TUTOrderStatusType	OrderStatus;
	///剩余数量
	TUTVolumeType	VolumeTotal;
	///报单日期
	TUTDateType	InsertDate;
	///委托时间
	TUTTimeType	InsertTime;
	///交易所错误信息
	TUTExchangeErrorIDType	ExchangeErrorID;
	///安装编号
	TUTInstallIDType	InstallID;
	///序号
	TUTSequenceNoType	SequenceNo;
	///价格
	TUTPriceType	LimitPrice;
};
///交易所返回报单操作
struct CUTExchangeOrderActionField
{
	///交易所代码
	TUTExchangeIDType	ExchangeID;
	///交易所交易员代码
	TUTTraderIDType	TraderID;
	///本地报单编号
	TUTOrderLocalIDType	ActionLocalID;
	///交易所错误代码
	TUTExchangeErrorIDType	ExchangeErrorID;
};
///交易所返回指定
struct CUTExchangeDesignateField
{
	///交易所代码
	TUTExchangeIDType	ExchangeID;
	///交易所交易员代码
	TUTTraderIDType	TraderID;
	///本地指定编号
	TUTOrderLocalIDType	DesignateLocalID;
	///指定状态
	TUTDesignateStatusType	DesignateStatus;
	///报单日期
	TUTDateType	InsertDate;
	///委托时间
	TUTTimeType	InsertTime;
	///序号
	TUTSequenceNoType	SequenceNo;
	///交易所错误代码
	TUTExchangeErrorIDType	ExchangeErrorID;
	///安装编号
	TUTInstallIDType	InstallID;
};
///禁止登录用户IP
struct CUTLoginForbiddenUserIPField
{
	///用户代码
	TUTUserIDType	UserID;
	///IP地址
	TUTIPAddressType	IPAddress;
};
///IP列表
struct CUTIPListField
{
	///IP地址
	TUTIPAddressType	IPAddress;
	///是否白名单
	TUTBoolType	IsWhite;
};
///同步随机串
struct CUTSyncRandomStringField
{
	///随机串
	TUTRandomStringType	RandomString;
	///随机串类别
	TUTRandomStringTypeType	RandomStringType;
};
///强制用户登出
struct CUTForceUserLogoutField
{
	///用户代码
	TUTUserIDType	UserID;
	///前置编号
	TUTFrontIDType	FrontID;
	///会话编号
	TUTSessionIDType	SessionID;
	///是否允许重新登录
	TUTBoolType	EnableRelogin;
};
///用户会话引用
struct CUTUserSessionRefField
{
	///前置编号
	TUTFrontIDType	FrontID;
	///会话编号
	TUTSessionIDType	SessionID;
};
///用户连续登录失败次数
struct CUTUserLoginFailedNumField
{
	///用户代码
	TUTUserIDType	UserID;
	///IP地址
	TUTIPAddressType	IPAddress;
	///连续登录失败次数
	TUTVolumeType	Volume;
};
///IP登录失败次数
struct CUTIPLoginFailedNumField
{
	///IP地址
	TUTIPAddressType	IPAddress;
	///连续登录失败次数
	TUTVolumeType	Volume;
};
///用户口令变更
struct CUTUserPasswordUpdateField
{
	///用户代码
	TUTUserIDType	UserID;
	///原来的口令
	TUTPasswordType	OldPassword;
	///新的口令
	TUTPasswordType	NewPassword;
};
///输入转账
struct CUTInputTransferField
{
	///投资者代码
	TUTInvestorIDType	InvestorID;
	///转账引用
	TUTOrderRefType	TransferRef;
	///转账类型
	TUTTransferTypeType	TransferType;
	///金额
	TUTMoneyType	Deposit;
	///币种代码
	TUTCurrencyIDType	CurrencyID;
	///账户类型
	TUTAccTypeType	AccType;
	///银行代码
	TUTBankIDType	BankID;
	///资金密码
	TUTPasswordType	FundPassword;
	///银行密码
	TUTPasswordType	BankPassword;
};
///转账
struct CUTTransferField
{
	///投资者代码
	TUTInvestorIDType	InvestorID;
	///转账引用
	TUTOrderRefType	TransferRef;
	///转账类型
	TUTTransferTypeType	TransferType;
	///金额
	TUTMoneyType	Deposit;
	///币种代码
	TUTCurrencyIDType	CurrencyID;
	///账户类型
	TUTAccTypeType	AccType;
	///银行代码
	TUTBankIDType	BankID;
	///资金密码
	TUTPasswordType	FundPassword;
	///银行密码
	TUTPasswordType	BankPassword;
	///前置编号
	TUTFrontIDType	FrontID;
	///会话编号
	TUTSessionIDType	SessionID;
	///本地转账号
	TUTOrderLocalIDType	TransferLocalID;
	///转账系统号
	TUTOrderSysIDType	TransferSysID;
	///转账状态
	TUTTransferStatusType	TransferStatus;
	///交易所错误代码
	TUTExchangeErrorIDType	ExchangeErrorID;
	///转账日期
	TUTDateType	InsertDate;
	///转账时间
	TUTTimeType	InsertTime;
};
///交易所返回转账
struct CUTExchangeTransferField
{
	///本地转账号
	TUTOrderLocalIDType	TransferLocalID;
	///转账系统号
	TUTOrderSysIDType	TransferSysID;
	///转账状态
	TUTTransferStatusType	TransferStatus;
	///交易所错误代码
	TUTExchangeErrorIDType	ExchangeErrorID;
};
///订阅主题
struct CUTSubTopicField
{
	///主题
	TUTSubjectIDType	SubjectID;
	///序号
	TUTSequenceNoType	SequeceNo;
	///交易日
	TUTDateType	TradingDay;
};
///订阅行情主题
struct CUTSubMDTopicField
{
	///交易所代码
	TUTExchangeIDType	ExchangeID;
	///合约代码
	TUTInstrumentIDType	InstrumentID;
	///订阅的数据类型,可使用|连接
	TUTSubDataTypeType	SubDataType;
};
///监控指标
struct CUTMonitorIndexField
{
	///未知单延时ns(3秒采样一次)
	TUTLargeVolumeType	DelayTimeUnknown;
	///已报单延时ns(3秒采样一次)
	TUTLargeVolumeType	DelayTimeQueued;
	///错误报单数
	TUTLargeVolumeType	ErrOrderVolume;
	///错误撤单数
	TUTLargeVolumeType	ErrOrderActionVolume;
	///错误报单投资者代码
	TUTInvestorIDType	ErrOrderInvestorID;
	///错误撤单投资者代码
	TUTInvestorIDType	ErrOrderActionInvestorID;
	///延时的时间戳
	TUTTimeType	Time;
};
///终端信息录入
struct CUTSubmitTerminalInfoField
{
	///用户代码
	TUTUserIDType	UserID;
	///登录序号,从1开始编号;操作员做中转时在报单录入中也需指定
	TUTSequenceNoType	LoginSeq;
	///终端信息(MA;LIP=XXX)
	TUTTerminalInfoType	TerminalInfo;
};
///终端信息
struct CUTTerminalInfoField
{
	///前置编号
	TUTFrontIDType	FrontID;
	///会话编号
	TUTSessionIDType	SessionID;
	///用户代码
	TUTUserIDType	UserID;
	///登录序号
	TUTSequenceNoType	LoginSeq;
	///终端信息(#OSTPMA;IIP=XXX)
	TUTTerminalInfoType	TerminalInfo;
};
///查询最大下单量
struct CUTMaxOrderVolumeField
{
	///投资者代码
	TUTInvestorIDType	InvestorID;
	///交易所代码
	TUTExchangeIDType	ExchangeID;
	///合约代码
	TUTInstrumentIDType	InstrumentID;
	///投机套保标志
	TUTHedgeFlagType	HedgeFlag;
	///买卖方向
	TUTDirectionType	Direction;
	///开平标志
	TUTOffsetFlagType	OffsetFlag;
	///报单价格
	TUTPriceType	Price;
	///最大允许报单数量
	TUTVolumeType	MaxVolume;
	///原始最大允许报单数量
	TUTLargeVolumeType	MaxVolumeOri;
};
///输入直接还款
struct CUTInputFundPaybackField
{
	///投资者代码
	TUTInvestorIDType	InvestorID;
	///币种代码
	TUTCurrencyIDType	CurrencyID;
	///直接还款引用
	TUTOrderRefType	FundPaybackRef;
	///还款金额
	TUTMoneyType	Amount;
	///IP地址
	TUTIPAddressAsIntType	IPAddressAsInt;
	///Mac地址
	TUTMacAddressAsLongType	MacAddressAsLong;
};
///直接还款
struct CUTFundPaybackField
{
	///投资者代码
	TUTInvestorIDType	InvestorID;
	///币种代码
	TUTCurrencyIDType	CurrencyID;
	///直接还款引用
	TUTOrderRefType	FundPaybackRef;
	///还款金额
	TUTMoneyType	Amount;
	///前置编号
	TUTFrontIDType	FrontID;
	///会话编号
	TUTSessionIDType	SessionID;
	///本地转账号
	TUTOrderLocalIDType	FundPaybackLocalID;
	///直接还款日期
	TUTDateType	InsertDate;
	///直接还款时间
	TUTTimeType	InsertTime;
	///IP地址
	TUTIPAddressAsIntType	IPAddressAsInt;
	///Mac地址
	TUTMacAddressAsLongType	MacAddressAsLong;
};
///输入直接还券
struct CUTInputStockPaybackField
{
	///投资者代码
	TUTInvestorIDType	InvestorID;
	///交易所代码
	TUTExchangeIDType	ExchangeID;
	///合约代码
	TUTInstrumentIDType	InstrumentID;
	///直接还券引用
	TUTOrderRefType	StockPaybackRef;
	///直接还券数量
	TUTLargeVolumeType	Volume;
	///IP地址
	TUTIPAddressAsIntType	IPAddressAsInt;
	///Mac地址
	TUTMacAddressAsLongType	MacAddressAsLong;
};
///直接还券
struct CUTStockPaybackField
{
	///投资者代码
	TUTInvestorIDType	InvestorID;
	///交易所代码
	TUTExchangeIDType	ExchangeID;
	///合约代码
	TUTInstrumentIDType	InstrumentID;
	///直接还券引用
	TUTOrderRefType	StockPaybackRef;
	///直接还券数量
	TUTLargeVolumeType	Volume;
	///前置编号
	TUTFrontIDType	FrontID;
	///会话编号
	TUTSessionIDType	SessionID;
	///交易所交易员代码
	TUTTraderIDType	TraderID;
	///本地直接还券号
	TUTOrderLocalIDType	StockPaybackLocalID;
	///客户代码
	TUTClientIDType	ClientID;
	///安装编号
	TUTInstallIDType	InstallID;
	///直接还券日期
	TUTDateType	InsertDate;
	///直接还券时间
	TUTTimeType	InsertTime;
	///直接还券系统号
	TUTOrderSysIDType	StockPaybackSysID;
	///直接还券状态
	TUTOrderActionStatusType	StockPaybackStatus;
	///交易所错误代码
	TUTExchangeErrorIDType	ExchangeErrorID;
	///营业部编号
	TUTBranchIDType	BranchID;
	///IP地址
	TUTIPAddressAsIntType	IPAddressAsInt;
	///Mac地址
	TUTMacAddressAsLongType	MacAddressAsLong;
};
///交易所返回直接还券
struct CUTExchangeStockPaybackField
{
	///交易所代码
	TUTExchangeIDType	ExchangeID;
	///交易所交易员代码
	TUTTraderIDType	TraderID;
	///本地直接还券号
	TUTOrderLocalIDType	StockPaybackLocalID;
	///直接还券系统号
	TUTOrderSysIDType	StockPaybackSysID;
	///直接还券状态
	TUTOrderActionStatusType	StockPaybackStatus;
	///交易所错误代码
	TUTExchangeErrorIDType	ExchangeErrorID;
	///安装编号
	TUTInstallIDType	InstallID;
};
///公有融资额度
struct CUTPublicCreditFundField
{
	///公有融资额度
	TUTMoneyType	TotalAmount;
	///已占用额度
	TUTMoneyType	FrozenAmount;
};
///浮动盈亏
struct CUTPositionProfitForKernelField
{
	///资金安装编号
	TUTInstallIDType	AccountInstallID;
	///持仓盈亏,个股期权为实时保证金
	TUTMoneyType	PositionProfit;
};
///投资者融资明细
struct CUTCreditFundDetailField
{
	///投资者代码
	TUTInvestorIDType	InvestorID;
	///交易所代码
	TUTExchangeIDType	ExchangeID;
	///合约代码
	TUTInstrumentIDType	InstrumentID;
	///融资日期
	TUTDateType	OpenDate;
	///流水号
	TUTTradeIDType	TradeID;
	///到期日
	TUTDateType	ExpireDate;
	///融资金额
	TUTMoneyType	Amount;
	///已归还融资金额
	TUTMoneyType	AmountPayback;
	///融资买入数量
	TUTVolumeType	Volume;
	///已归还融资数量
	TUTMoneyType	VolumePayback;
	///昨归还融资金额
	TUTMoneyType	YdAmountPayback;
	///今日手续费(不可还)
	TUTMoneyType	Commission;
	///今日卖券还款金额
	TUTMoneyType	CreditAmountPayback;
	///今日直接还款金额
	TUTMoneyType	FundAmountPayback;
};
///投资者融券明细
struct CUTCreditStockDetailField
{
	///投资者代码
	TUTInvestorIDType	InvestorID;
	///交易所代码
	TUTExchangeIDType	ExchangeID;
	///合约代码
	TUTInstrumentIDType	InstrumentID;
	///融券日期
	TUTDateType	OpenDate;
	///流水号
	TUTTradeIDType	TradeID;
	///到期日
	TUTDateType	ExpireDate;
	///融券数量
	TUTVolumeType	Volume;
	///已归还融券数量
	TUTVolumeType	VolumePayback;
	///融券卖出金额
	TUTMoneyType	Amount;
	///已归还融券金额
	TUTMoneyType	AmountPayback;
};
///信用合约属性
struct CUTCreditInstrumentField
{
	///交易所代码
	TUTExchangeIDType	ExchangeID;
	///合约代码
	TUTInstrumentIDType	InstrumentID;
	///股票折算率
	TUTRatioType	ConvertRate;
	///是否可融资
	TUTBoolType	IsCreditFund;
	///是否可融券
	TUTBoolType	IsCreditStock;
	///是否担保品
	TUTBoolType	IsGuarantee;
	///是否高流通证券
	TUTBoolType	IsLiquid;
	///集中度分组代码
	TUTInstrumentIDType	ConcentrationGroupID;
	///公允价格
	TUTMoneyType	AssetPrice;
	///融券公允价格
	TUTMoneyType	AssetPriceCreditStock;
};
///投资者信用信息
struct CUTCreditInvestorField
{
	///投资者代码
	TUTInvestorIDType	InvestorID;
	///融资保证金率
	TUTRatioType	FundRate;
	///融券保证金率
	TUTRatioType	StockRate;
	///维持担保率
	TUTRatioType	GuaranteeRate;
	///融资融券总额度
	TUTMoneyType	TotalLimit;
	///融券额度
	TUTMoneyType	StockLimit;
	///融资额度
	TUTMoneyType	FundLimit;
	///私有融资额度
	TUTMoneyType	PrivateCreditFund;
};
///私有融券额度
struct CUTPrivateCreditStockField
{
	///投资者代码
	TUTInvestorIDType	InvestorID;
	///交易所代码
	TUTExchangeIDType	ExchangeID;
	///合约代码
	TUTInstrumentIDType	InstrumentID;
	///可融券数量
	TUTLargeVolumeType	Volume;
	///开始日期
	TUTDateType	BeginDate;
	///结束日期
	TUTDateType	EndDate;
	///可融券数量(含到期)
	TUTLargeVolumeType	ReserveVolume;
};
///信用账户和普通账户对应表
struct CUTCreditToNormalInvestorField
{
	///投资者代码
	TUTInvestorIDType	InvestorID;
	///交易所代码
	TUTExchangeIDType	ExchangeID;
	///普通投资者代码
	TUTInvestorIDType	NormalInvestorID;
	///普通客户代码
	TUTClientIDType	NormalClientID;
};
///集中度参数
struct CUTCreditConcentrationField
{
	///投资者代码
	TUTInvestorIDType	InvestorID;
	///集中度业务类型
	TUTConcentrationBizTypeType	ConcentrationBizType;
	///集中度合约类型
	TUTConcentrationInstrTypeType	ConcentrationInstrType;
	///交易所代码
	TUTExchangeIDType	ExchangeID;
	///合约代码(小类/分组)
	TUTInstrumentIDType	InstrumentID;
	///维持担保率下限
	TUTRatioType	GuaranteeRateLower;
	///维持担保率上限
	TUTRatioType	GuaranteeRateUpper;
	///集中度
	TUTRatioType	ConcentrationRate;
};
///ETF申赎信息
struct CUTETFInfoField
{
	///交易所代码
	TUTExchangeIDType	ExchangeID;
	///合约代码
	TUTInstrumentIDType	InstrumentID;
	///一级市场申赎代码
	TUTFundIDType	RedemptionID;
	///每个篮子对应的ETF份数,申赎必须整数倍
	TUTVolumeType	CreationRedemptionUnit;
	///最大现金替代比例
	TUTRatioType	MaxCashRatio;
	///是否需要发布IOPV
	TUTBoolType	PublishIOPV;
	///是否可申购
	TUTBoolType	Creation;
	///是否可赎回
	TUTBoolType	Redemption;
	///成分证券数量
	TUTVolumeType	RecordNum;
	///T日每个篮子的预估现金差额
	TUTMoneyType	EstimateCashComponent;
	///前一日最小申赎单位净值
	TUTMoneyType	NAVperCU;
	///前一日基金份额净值
	TUTMoneyType	NAV;
	///必须现金替代金额
	TUTMoneyType	SubstituteAmount;
	///赎回成分股股数
	TUTVolumeType	RedemptionStockVolume;
};
///ETF成分股
struct CUTETFComponentField
{
	///交易所代码
	TUTExchangeIDType	ExchangeID;
	///ETF代码
	TUTFundIDType	ETFID;
	///成分股合约代码
	TUTInstrumentIDType	InstrumentID;
	///成分股交易所代码
	TUTExchangeIDType	ComponentExchangeID;
	///证券数量
	TUTVolumeType	Volume;
	///替代标志
	TUTSubstituteFlagType	SubstituteFlag;
	///申购溢价比例
	TUTRatioType	CreationPremiumRate;
	///赎回折价比例
	TUTRatioType	RedemptionDiscountRate;
	///申购替代金额
	TUTMoneyType	CreationCashSubstitute;
	///赎回替代金额
	TUTMoneyType	RedemptionCashSubstitute;
};
///浮动盈亏引用
struct CUTPositionProfitForKernelRefField
{
	///资金安装编号
	TUTInstallIDType	AccountInstallID;
	///证券市值
	TUTMoneyType	CreditTotalValue;
	///融券市值
	TUTMoneyType	CreditStockValue;
	///保证金余额变量
	TUTMoneyType	CreditAvailableParam;
};
///浮动盈亏引用1
struct CUTPositionProfitForKernelRef1Field
{
	///安装编号
	TUTInstallIDType	PositionInstallID;
	///证券市值
	TUTMoneyType	Value;
};
///集中度持仓
struct CUTConcentrationPositionField
{
	///投资者代码
	TUTInvestorIDType	InvestorID;
	///交易所代码
	TUTExchangeIDType	ExchangeID;
	///合约代码
	TUTInstrumentIDType	InstrumentID;
	///投机套保标志
	TUTHedgeFlagType	HedgeFlag;
	///集中度合约类型
	TUTConcentrationInstrTypeType	ConcentrationInstrType;
	///市值(含冻结市值)
	TUTMoneyType	Value;
};
///行情最新价引用
struct CUTMDLastPriceRefField
{
	///行情索引
	TUTVolumeType	MDInstallID;
	///最新价
	TUTVolumeType	LastPrice;
};
///重复组
struct CUTDuplicateCountField
{
	///个数
	TUTVolumeType	DuplicateCount;
};
///同步公有融资额度
struct CUTSyncPublicCreditFundField
{
	///公有融资额度增量
	TUTMoneyType	Amount;
};
///LocalID
struct CUTLocalIDField
{
	///本地转账号
	TUTOrderLocalIDType	TransferLocalID;
	///本地直接还款号
	TUTOrderLocalIDType	FundPaybackLocalID;
};
///打板投资者
struct CUTBoardInvestorField
{
	///投资者代码
	TUTInvestorIDType	InvestorID;
	///交易所代码
	TUTExchangeIDType	ExchangeID;
	///占用网关数量
	TUTVolumeType	Volume;
};
///保证金可用余额明细
struct CUTCreditAvailableDetailField
{
	///投资者帐号
	TUTAccountIDType	AccountID;
	///担保品折算
	TUTMoneyType	CreditCollateralValue;
	///融资盈亏
	TUTMoneyType	CreditFundProfit;
	///融券盈亏
	TUTMoneyType	CreditStockProfit;
};
///深圳网关连接
struct CUTGatewayField
{
	///网关位置(目前只返回未连接的网关)
	TUTLocationType	Location;
	///交易所代码
	TUTExchangeIDType	ExchangeID;
};
///投资者分级
struct CUTInvestorLevelField
{
	///投资者代码
	TUTInvestorIDType	InvestorID;
	///交易所代码
	TUTExchangeIDType	ExchangeID;
	///投资者分级类型
	TUTVolumeType	Level;
};
///系统名称
struct CUTSystemNameField
{
	///系统名称
	TUTSystemNameType	SystemName;
};
///输入锁定
struct CUTInputLockField
{
	///投资者代码
	TUTInvestorIDType	InvestorID;
	///交易所代码
	TUTExchangeIDType	ExchangeID;
	///合约代码
	TUTInstrumentIDType	InstrumentID;
	///锁定引用
	TUTOrderRefType	LockRef;
	///数量
	TUTVolumeType	Volume;
	///锁定类型
	TUTLockTypeType	LockType;
	///IP地址
	TUTIPAddressAsIntType	IPAddressAsInt;
	///Mac地址
	TUTMacAddressAsLongType	MacAddressAsLong;
};
///锁定
struct CUTLockField
{
	///投资者代码
	TUTInvestorIDType	InvestorID;
	///交易所代码
	TUTExchangeIDType	ExchangeID;
	///合约代码
	TUTInstrumentIDType	InstrumentID;
	///锁定引用
	TUTOrderRefType	LockRef;
	///数量
	TUTVolumeType	Volume;
	///锁定类型
	TUTLockTypeType	LockType;
	///交易所交易员代码
	TUTTraderIDType	TraderID;
	///本地锁定编号
	TUTOrderLocalIDType	LockLocalID;
	///客户代码
	TUTClientIDType	ClientID;
	///交易日
	TUTDateType	TradingDay;
	///营业部编号
	TUTBranchIDType	BranchID;
	///安装编号
	TUTInstallIDType	InstallID;
	///IP地址
	TUTIPAddressAsIntType	IPAddressAsInt;
	///Mac地址
	TUTMacAddressAsLongType	MacAddressAsLong;
	///锁定编号
	TUTOrderSysIDType	LockSysID;
	///锁定状态
	TUTOrderActionStatusType	LockStatus;
	///报单日期
	TUTDateType	InsertDate;
	///委托时间
	TUTTimeType	InsertTime;
	///撤销时间
	TUTTimeType	CancelTime;
	///序号
	TUTSequenceNoType	SequenceNo;
	///前置编号
	TUTFrontIDType	FrontID;
	///会话编号
	TUTSessionIDType	SessionID;
	///交易所错误代码
	TUTExchangeErrorIDType	ExchangeErrorID;
};
///交易所返回锁定
struct CUTExchangeLockField
{
	///交易所代码
	TUTExchangeIDType	ExchangeID;
	///交易所交易员代码
	TUTTraderIDType	TraderID;
	///本地报单编号
	TUTOrderLocalIDType	LockLocalID;
	///报单编号
	TUTOrderSysIDType	LockSysID;
	///锁定状态
	TUTOrderActionStatusType	LockStatus;
	///报单日期
	TUTDateType	InsertDate;
	///委托时间
	TUTTimeType	InsertTime;
	///交易所错误信息
	TUTExchangeErrorIDType	ExchangeErrorID;
	///安装编号
	TUTInstallIDType	InstallID;
	///序号
	TUTSequenceNoType	SequenceNo;
};
///输入行权
struct CUTInputExecOrderField
{
	///投资者代码
	TUTInvestorIDType	InvestorID;
	///交易所代码
	TUTExchangeIDType	ExchangeID;
	///合约代码;合并行权可填写P and C
	TUTInstrumentIDType	InstrumentID;
	///报单引用
	TUTOrderRefType	ExecOrderRef;
	///数量
	TUTVolumeType	Volume;
	///IP地址
	TUTIPAddressAsIntType	IPAddressAsInt;
	///Mac地址
	TUTMacAddressAsLongType	MacAddressAsLong;
};
///行权
struct CUTExecOrderField
{
	///投资者代码
	TUTInvestorIDType	InvestorID;
	///交易所代码
	TUTExchangeIDType	ExchangeID;
	///合约代码;合并行权可填写P and C
	TUTInstrumentIDType	InstrumentID;
	///报单引用
	TUTOrderRefType	ExecOrderRef;
	///数量
	TUTVolumeType	Volume;
	///交易所交易员代码
	TUTTraderIDType	TraderID;
	///本地报单编号
	TUTOrderLocalIDType	ExecOrderLocalID;
	///客户代码
	TUTClientIDType	ClientID;
	///交易日
	TUTDateType	TradingDay;
	///营业部编号
	TUTBranchIDType	BranchID;
	///安装编号
	TUTInstallIDType	InstallID;
	///IP地址
	TUTIPAddressAsIntType	IPAddressAsInt;
	///Mac地址
	TUTMacAddressAsLongType	MacAddressAsLong;
	///行权编号
	TUTOrderSysIDType	ExecOrderSysID;
	///执行结果
	TUTExecResultType	ExecResult;
	///报单日期
	TUTDateType	InsertDate;
	///委托时间
	TUTTimeType	InsertTime;
	///撤销时间
	TUTTimeType	CancelTime;
	///序号
	TUTSequenceNoType	SequenceNo;
	///前置编号
	TUTFrontIDType	FrontID;
	///会话编号
	TUTSessionIDType	SessionID;
	///交易所错误代码
	TUTExchangeErrorIDType	ExchangeErrorID;
};
///交易所返回行权
struct CUTExchangeExecOrderField
{
	///交易所代码
	TUTExchangeIDType	ExchangeID;
	///交易所交易员代码
	TUTTraderIDType	TraderID;
	///本地报单编号
	TUTOrderLocalIDType	ExecOrderLocalID;
	///报单编号
	TUTOrderSysIDType	ExecOrderSysID;
	///执行结果
	TUTExecResultType	ExecResult;
	///报单日期
	TUTDateType	InsertDate;
	///委托时间
	TUTTimeType	InsertTime;
	///交易所错误信息
	TUTExchangeErrorIDType	ExchangeErrorID;
	///安装编号
	TUTInstallIDType	InstallID;
	///序号
	TUTSequenceNoType	SequenceNo;
};
///持仓冻结
struct CUTPosiFreezeField
{
	///交易编码
	TUTClientIDType	ClientID;
	///交易所代码
	TUTExchangeIDType	ExchangeID;
	///合约代码
	TUTInstrumentIDType	InstrumentID;
	///交易所交易员代码
	TUTTraderIDType	TraderID;
	///本地报单编号
	TUTPosiFreezeLocalIDType	PosiFreezeLocalID;
	///数量
	TUTLargeVolumeType	Volume;
	///冻结原因
	TUTFreezeReasonType	FreezeReason;
	///冻结类型
	TUTFreezeTypeType	FreezeType;
	///流水中的序号
	TUTSequenceNoType	SequenceNo;
};
///锁定的证券持仓
struct CUTLockPositionField
{
	///投资者代码
	TUTInvestorIDType	InvestorID;
	///交易所代码
	TUTExchangeIDType	ExchangeID;
	///合约代码
	TUTInstrumentIDType	InstrumentID;
	///数量
	TUTLargeVolumeType	Volume;
	///冻结数量,解锁未知单也会冻结该数量
	TUTLargeVolumeType	FrozenVolume;
};
///行权操作
struct CUTExecOrderActionField
{
	///行权操作引用
	TUTOrderRefType	ExecOrderActionRef;
	///前置编号
	TUTFrontIDType	FrontID;
	///会话编号
	TUTSessionIDType	SessionID;
	///行权引用
	TUTOrderRefType	ExecOrderRef;
	///投资者代码
	TUTInvestorIDType	InvestorID;
	///交易所代码
	TUTExchangeIDType	ExchangeID;
	///报单编号
	TUTOrderSysIDType	ExecOrderSysID;
	///合约代码
	TUTInstrumentIDType	InstrumentID;
	///操作日期
	TUTDateType	ActionDate;
	///操作时间
	TUTTimeType	ActionTime;
	///交易所交易员代码
	TUTTraderIDType	TraderID;
	///本地报单编号
	TUTOrderLocalIDType	ExecOrderLocalID;
	///操作本地编号
	TUTOrderLocalIDType	ActionLocalID;
	///客户代码
	TUTClientIDType	ClientID;
	///报单操作状态
	TUTOrderActionStatusType	OrderActionStatus;
	///营业部编号
	TUTBranchIDType	BranchID;
	///安装编号
	TUTInstallIDType	InstallID;
	///交易所错误信息
	TUTExchangeErrorIDType	ExchangeErrorID;
	///撤单前置编号
	TUTFrontIDType	ActionFrontID;
	///撤单会话编号
	TUTSessionIDType	ActionSessionID;
	///IP地址
	TUTIPAddressAsIntType	IPAddressAsInt;
	///Mac地址
	TUTMacAddressAsLongType	MacAddressAsLong;
};
///输入行权操作
struct CUTInputExecOrderActionField
{
	///行权操作引用
	TUTOrderRefType	ExecOrderActionRef;
	///前置编号
	TUTFrontIDType	FrontID;
	///会话编号
	TUTSessionIDType	SessionID;
	///行权引用
	TUTOrderRefType	ExecOrderRef;
	///IP地址
	TUTIPAddressAsIntType	IPAddressAsInt;
	///Mac地址
	TUTMacAddressAsLongType	MacAddressAsLong;
};
///交易所持仓冻结
struct CUTExchangePosiFreezeField
{
	///交易所代码
	TUTExchangeIDType	ExchangeID;
	///交易所交易员代码
	TUTTraderIDType	TraderID;
	///本地持仓冻结编号
	TUTPosiFreezeLocalIDType	PosiFreezeLocalID;
	///冻结原因
	TUTFreezeReasonType	FreezeReason;
	///交易所错误代码
	TUTExchangeErrorIDType	ExchangeErrorID;
};
///交易所返回行权操作
struct CUTExchangeExecOrderActionField
{
	///交易所代码
	TUTExchangeIDType	ExchangeID;
	///交易所交易员代码
	TUTTraderIDType	TraderID;
	///本地报单编号
	TUTOrderLocalIDType	ActionLocalID;
	///交易所错误代码
	TUTExchangeErrorIDType	ExchangeErrorID;
};
///期权限仓冻结
struct CUTOptPosiLimitField
{
	///投资者代码
	TUTInvestorIDType	InvestorID;
	///交易所代码
	TUTExchangeIDType	ExchangeID;
	///合约代码
	TUTInstrumentIDType	InstrumentID;
	///总数量限制
	TUTLargeVolumeType	TotalVolume;
	///多头数量限制
	TUTLargeVolumeType	LongVolume;
	///当日开仓数量限制
	TUTLargeVolumeType	OpenVolume;
	///当日多头开仓数量限制
	TUTLargeVolumeType	LongOpenVolume;
	///总数量冻结
	TUTLargeVolumeType	TotalVolumeFrozen;
	///多头数量冻结
	TUTLargeVolumeType	LongVolumeFrozen;
	///当日开仓数量冻结
	TUTLargeVolumeType	OpenVolumeFrozen;
	///当日多头开仓数量限制
	TUTLargeVolumeType	LongOpenVolumeFrozen;
};
///期权金额限制冻结
struct CUTOptAmountLimitField
{
	///投资者代码
	TUTInvestorIDType	InvestorID;
	///交易所代码
	TUTExchangeIDType	ExchangeID;
	///多头持仓金额限制
	TUTMoneyType	LongAmount;
	///多头持仓金额冻结
	TUTMoneyType	LongAmountFrozen;
};
///Dll设置
struct CUTDllSettingField
{
	///Dll名称
	TUTDllNameType	DllName;
	///是否启用
	TUTBoolType	Enable;
	///错误信息
	TUTErrorMsgType	ErrorMsg;
};
///Dll更新
struct CUTDllUpdateField
{
	///Dll名称
	TUTDllNameType	DllName;
	///序列号
	TUTSequenceNoType	SequenceNo;
	///内容
	TUTContentType	Content;
	///长度
	TUTVolumeType	Size;
	///错误信息
	TUTErrorMsgType	ErrorMsg;
};
///导出内存数据库
struct CUTDataDumpField
{
	///错误信息
	TUTErrorMsgType	ErrorMsg;
};
///合约查询
struct CUTQryInstrumentField
{
	///交易所代码
	TUTExchangeIDType	ExchangeID;
	///合约代码
	TUTInstrumentIDType	InstrumentID;
};
///行情查询
struct CUTQryDepthMarketDataField
{
	///交易所代码
	TUTExchangeIDType	ExchangeID;
	///合约代码
	TUTInstrumentIDType	InstrumentID;
};
///投资者持仓查询
struct CUTQryInvestorPositionField
{
	///投资者代码
	TUTInvestorIDType	InvestorID;
	///交易所代码
	TUTExchangeIDType	ExchangeID;
	///合约代码
	TUTInstrumentIDType	InstrumentID;
};
///资金账号查询
struct CUTQryTradingAccountField
{
	///投资者代码
	TUTInvestorIDType	InvestorID;
	///币种代码
	TUTCurrencyIDType	CurrencyID;
	///账户类型
	TUTAccTypeType	AccType;
};
///报单查询
struct CUTQryOrderField
{
	///投资者代码
	TUTInvestorIDType	InvestorID;
	///交易所代码
	TUTExchangeIDType	ExchangeID;
	///合约代码
	TUTInstrumentIDType	InstrumentID;
	///起始编号
	TUTSequenceNoType	SequenceNo;
	///从SequenceNo开始,查询Limit条记录
	TUTVolumeType	Limit;
	///报单状态,查询时增加三种状态未完成(h),已完成(i),有成交(j):
	TUTOrderStatusType	OrderStatus;
};
///成交查询
struct CUTQryTradeField
{
	///投资者代码
	TUTInvestorIDType	InvestorID;
	///交易所代码
	TUTExchangeIDType	ExchangeID;
	///合约代码
	TUTInstrumentIDType	InstrumentID;
	///起始编号(仅供查询)
	TUTSequenceNoType	SequenceNo;
	///从SequenceNo开始,查询Limit条记录
	TUTVolumeType	Limit;
};
///交易员报盘机查询
struct CUTQryTraderField
{
	///交易所代码
	TUTExchangeIDType	ExchangeID;
	///交易所交易员代码
	TUTTraderIDType	TraderID;
};
///期权合约每手保证金率查询
struct CUTQryOptionInstrMarginByVolumeField
{
	///投资者代码
	TUTInvestorIDType	InvestorID;
	///交易所代码
	TUTExchangeIDType	ExchangeID;
	///合约代码
	TUTInstrumentIDType	InstrumentID;
};
///期权合约每手保证金率
struct CUTOptionInstrMarginByVolumeField
{
	///投资者代码
	TUTInvestorIDType	InvestorID;
	///交易所代码
	TUTExchangeIDType	ExchangeID;
	///合约代码
	TUTInstrumentIDType	InstrumentID;
	///投机套保标志
	TUTHedgeFlagType	HedgeFlag;
	///每手合约保证金
	TUTMoneyType	MarginByVolume;
};
///期权手续费率查询
struct CUTQryOptionInstrCommRateField
{
	///投资者代码
	TUTInvestorIDType	InvestorID;
	///交易所代码
	TUTExchangeIDType	ExchangeID;
	///合约代码
	TUTInstrumentIDType	InstrumentID;
};
///出入金流水查询
struct CUTQrySyncDepositField
{
	///出入金流水号
	TUTDepositSeqNoType	DepositSeqNo;
};
///经纪公司用户权限查询
struct CUTQryBrokerUserFunctionField
{
	///用户代码
	TUTUserIDType	UserID;
};
///手续费率查询
struct CUTQryInstrumentCommissionRateField
{
	///投资者代码
	TUTInvestorIDType	InvestorID;
	///交易所代码
	TUTExchangeIDType	ExchangeID;
	///合约代码
	TUTInstrumentIDType	InstrumentID;
};
///投资者查询
struct CUTQryInvestorField
{
	///投资者代码
	TUTInvestorIDType	InvestorID;
};
///用户会话查询
struct CUTQryUserSessionField
{
	///用户代码
	TUTUserIDType	UserID;
	///前置编号
	TUTFrontIDType	FrontID;
	///会话编号
	TUTSessionIDType	SessionID;
};
///转账查询
struct CUTQryTransferField
{
	///投资者代码
	TUTInvestorIDType	InvestorID;
};
///用户密码查询
struct CUTQryBrokerUserPasswordField
{
	///用户代码
	TUTUserIDType	UserID;
};
///查询交易编码
struct CUTQryTradingCodeField
{
	///投资者代码
	TUTInvestorIDType	InvestorID;
};
///查询投资者合约交易权限
struct CUTQryInstrumentTradingRightField
{
	///投资者代码
	TUTInvestorIDType	InvestorID;
};
///查询认证口令
struct CUTQryAuthPasswordField
{
	///用户端产品信息
	TUTProductInfoType	UserProductInfo;
};
///查询客户端认证授权表
struct CUTQryAuthInvestorField
{
	///投资者代码
	TUTInvestorIDType	InvestorID;
	///用户端产品信息
	TUTProductInfoType	UserProductInfo;
};
///查询终端IP限制表
struct CUTQryAuthIPField
{
	///用户端产品信息
	TUTProductInfoType	UserProductInfo;
};
///查询逐笔行情
struct CUTQryL2OrderTradeField
{
	///交易所代码
	TUTExchangeIDType	ExchangeID;
	///逐笔行情频道
	TUTChannelNoType	ChannelNo;
	///开始序号
	TUTSequenceNoType	SequenceNoBegin;
	///结束序号
	TUTSequenceNoType	SequenceNoEnd;
};
///查询指定
struct CUTQryDesignateField
{
	///投资者代码
	TUTInvestorIDType	InvestorID;
};
///查询报单操作
struct CUTQryOrderActionField
{
	///投资者代码
	TUTInvestorIDType	InvestorID;
	///交易所代码
	TUTExchangeIDType	ExchangeID;
	///合约代码
	TUTInstrumentIDType	InstrumentID;
};
///查询禁止登录用户IP
struct CUTQryLoginForbiddenUserIPField
{
	///用户代码
	TUTUserIDType	UserID;
};
///查询IP列表
struct CUTQryIPListField
{
	///IP地址
	TUTIPAddressType	IPAddress;
};
///查询监控指标
struct CUTQryMonitorIndexField
{
	///时间
	TUTTimeType	Time;
};
///查询终端信息
struct CUTQryTerminalInfoField
{
	///前置编号
	TUTFrontIDType	FrontID;
	///会话编号
	TUTSessionIDType	SessionID;
	///登录序号
	TUTSequenceNoType	LoginSeq;
};
///查询最大下单量
struct CUTQryMaxOrderVolumeField
{
	///投资者代码
	TUTInvestorIDType	InvestorID;
	///交易所代码
	TUTExchangeIDType	ExchangeID;
	///合约代码
	TUTInstrumentIDType	InstrumentID;
	///投机套保标志
	TUTHedgeFlagType	HedgeFlag;
	///买卖方向
	TUTDirectionType	Direction;
	///开平标志
	TUTOffsetFlagType	OffsetFlag;
	///报单价格
	TUTPriceType	Price;
};
///信用合约属性查询
struct CUTQryCreditInstrumentField
{
	///交易所代码
	TUTExchangeIDType	ExchangeID;
	///合约代码
	TUTInstrumentIDType	InstrumentID;
};
///信用账户和普通账户对应表查询
struct CUTQryCreditToNormalInvestorField
{
	///投资者代码
	TUTInvestorIDType	InvestorID;
};
///投资者信用信息查询
struct CUTQryCreditInvestorField
{
	///投资者代码
	TUTInvestorIDType	InvestorID;
};
///私有融券额度查询
struct CUTQryPrivateCreditStockField
{
	///投资者代码
	TUTInvestorIDType	InvestorID;
};
///集中度参数查询
struct CUTQryCreditConcentrationField
{
	///投资者代码
	TUTInvestorIDType	InvestorID;
};
///投资者融资明细查询
struct CUTQryCreditFundDetailField
{
	///投资者代码
	TUTInvestorIDType	InvestorID;
};
///投资者融券明细查询
struct CUTQryCreditStockDetailField
{
	///投资者代码
	TUTInvestorIDType	InvestorID;
};
///投资者直接还款查询
struct CUTQryFundPaybackField
{
	///投资者代码
	TUTInvestorIDType	InvestorID;
};
///投资者直接还券查询
struct CUTQryStockPaybackField
{
	///投资者代码
	TUTInvestorIDType	InvestorID;
};
///公有融资额度查询
struct CUTQryPublicCreditFundField
{
	///时间
	TUTTimeType	Time;
};
///ETF申赎信息查询
struct CUTQryETFInfoField
{
	///交易所代码
	TUTExchangeIDType	ExchangeID;
	///合约代码
	TUTInstrumentIDType	InstrumentID;
};
///ETF成分股查询
struct CUTQryETFComponentField
{
	///交易所代码
	TUTExchangeIDType	ExchangeID;
	///ETF代码
	TUTFundIDType	ETFID;
	///合约代码
	TUTInstrumentIDType	InstrumentID;
};
///MDB查询
struct CUTQryMDBField
{
	///合约代码
	TUTInstrumentIDType	InstrumentID;
};
///集中度持仓查询
struct CUTQryConcentrationPositionField
{
	///投资者代码
	TUTInvestorIDType	InvestorID;
};
///查询保证金可用余额明细
struct CUTQryCreditAvailableDetailField
{
	///投资者帐号
	TUTAccountIDType	AccountID;
};
///深圳网关连接查询
struct CUTQryGatewayField
{
	///时间
	TUTTimeType	Time;
};
///查询投资者分级
struct CUTQryInvestorLevelField
{
	///投资者代码
	TUTInvestorIDType	InvestorID;
};
///查询投资者期权合约交易权限
struct CUTQryOptionInstrTradingRightField
{
	///投资者代码
	TUTInvestorIDType	InvestorID;
};
///系统名称查询
struct CUTQrySystemNameField
{
	///系统名称
	TUTSystemNameType	SystemName;
};
///锁定查询
struct CUTQryLockField
{
	///投资者代码
	TUTInvestorIDType	InvestorID;
};
///行权查询
struct CUTQryExecOrderField
{
	///投资者代码
	TUTInvestorIDType	InvestorID;
	///交易所代码
	TUTExchangeIDType	ExchangeID;
	///合约代码
	TUTInstrumentIDType	InstrumentID;
};
///持仓冻结查询
struct CUTQryLockPositionField
{
	///投资者代码
	TUTInvestorIDType	InvestorID;
};
///期权限仓冻结查询
struct CUTQryOptPosiLimitField
{
	///投资者代码
	TUTInvestorIDType	InvestorID;
};
///期权限额冻结查询
struct CUTQryOptAmountLimitField
{
	///投资者代码
	TUTInvestorIDType	InvestorID;
};
///行权操作查询
struct CUTQryExecOrderActionField
{
	///投资者代码
	TUTInvestorIDType	InvestorID;
	///交易所代码
	TUTExchangeIDType	ExchangeID;
	///合约代码
	TUTInstrumentIDType	InstrumentID;
};
///期权保证金算法查询
struct CUTQryOptionMarginAlgoField
{
	///交易所代码
	TUTExchangeIDType	ExchangeID;
	///标的代码
	TUTInstrumentIDType	InstrumentID;
};


//L2买卖盘
struct TUTL2BidAskType
{
	///申买价
	TUTPriceType	BidPrice;
	///申卖价
	TUTPriceType	AskPrice;
	///申买量
	TUTLargeVolumeType	BidVolume;
	///申卖量
	TUTLargeVolumeType	AskVolume;
	///申买报单量
	TUTVolumeType	BidOrderVolume;
	///申卖报单量
	TUTVolumeType	AskOrderVolume;
};

///10档行情
struct CUTL2DepthMarketDataField
{
	///交易所代码
	TUTExchangeIDType	ExchangeID;
	///合约代码
	TUTInstrumentIDType	InstrumentID;
	///交易日
	TUTDateType	TradingDay;
	///上次结算价;基金为上一日净值
	TUTPriceType	PreSettlementPrice;
	///昨收盘
	TUTPriceType	PreClosePrice;
	///昨持仓量
	TUTLargeVolumeType	PreOpenInterest;
	///涨停板价
	TUTPriceType	UpperLimitPrice;
	///跌停板价
	TUTPriceType	LowerLimitPrice;
	///自然日
	TUTDateType	ActionDay;
	///最后修改时间
	TUTTimeType	UpdateTime;
	///今开盘
	TUTPriceType	OpenPrice;
	///今收盘
	TUTPriceType	ClosePrice;
	///本次结算价;基金为实时参考净值
	TUTPriceType	SettlementPrice;
	///最高价
	TUTPriceType	HighestPrice;
	///最低价
	TUTPriceType	LowestPrice;
	///合约交易状态
	TUTInstrumentStatusType	InstrumentStatus;
	///最新价
	TUTPriceType	LastPrice;
	///数量
	TUTLargeVolumeType	Volume;
	///成交金额
	TUTMoneyType	Turnover;
	///持仓量
	TUTLargeVolumeType	OpenInterest;
	//买卖盘
	TUTL2BidAskType BidAsk[10];
};

//L2委托笔数揭示类型
struct TUTL2OrderVolumeType
{
	///申买委托笔数
	TUTVolumeType	BidOrderVolume;
	///申卖委托笔数
	TUTVolumeType	AskOrderVolume;
};

///L2最优价委托明细
struct CUTL2BestOrderField
{
	///交易所代码
	TUTExchangeIDType	ExchangeID;
	///合约代码
	TUTInstrumentIDType	InstrumentID;
	///自然日
	TUTDateType	ActionDay;
	///最后修改时间
	TUTTimeType	UpdateTime;
	///最优申买价
	TUTPriceType	BidPrice;
	///最优申卖价
	TUTPriceType	AskPrice;
	///揭示委托明细笔数
	TUTPriceLevelNumType	OrderNum;
	//委托笔数揭示
	TUTL2OrderVolumeType OrderVolume[50];
};

///用户登录请求
struct CUTReqLoginField
{
	///用户代码
	TUTUserIDType	UserID;
	///密码
	TUTPasswordType	Password;
	///用户端产品信息
	TUTProductInfoType	UserProductInfo;
	///用户端认证码
	TUTPasswordType	UserProductPassword;
	///动态密码
	TUTPasswordType	OneTimePassword;
	///登录备注
	TUTLoginRemarkType	LoginRemark;
};
