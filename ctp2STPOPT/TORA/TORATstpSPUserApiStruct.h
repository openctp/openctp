/////////////////////////////////////////////////////////////////////////
///@company 上海泰琰信息科技有限公司
///@file TORATstpSPUserApiStruct.h
///@brief 定义了客户端接口使用的业务数据结构
///@history 
/////////////////////////////////////////////////////////////////////////

#if !defined(_TORA_TSTPSPUSERAPISTRUCT_H)
#define _TORA_TSTPSPUSERAPISTRUCT_H

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "TORATstpSPUserApiDataType.h"

namespace TORASPAPI
{

	/// fens用户信息
	struct CTORATstpSPFensUserInfoField
	{
		 
		///登录账户
		TTORATstpSPLogInAccountType	LogInAccount;

		///登录账户类型
		TTORATstpSPLogInAccountTypeType	LogInAccountType;

	};

	/// 连接信息
	struct CTORATstpSPConnectionInfoField
	{
		 
		///内网IP地址
		TTORATstpSPIPAddressType	InnerIPAddress;

		///内网端口号
		TTORATstpSPPortType	InnerPort;

		///外网IP地址
		TTORATstpSPIPAddressType	OuterIPAddress;

		///外网端口号
		TTORATstpSPPortType	OuterPort;

		///MAC地址
		TTORATstpSPMacAddressType	MacAddress;

	};

	/// 登录请求
	struct CTORATstpSPReqUserLoginField
	{
		 
		///登录账户
		TTORATstpSPLogInAccountType	LogInAccount;

		///登录账户类型
		TTORATstpSPLogInAccountTypeType	LogInAccountType;

		///密码
		TTORATstpSPPasswordType	Password;

		///用户端产品信息
		TTORATstpSPProductInfoType	UserProductInfo;

		///协议信息
		TTORATstpSPProtocolInfoType	ProtocolInfo;

		///Mac地址
		TTORATstpSPMacAddressType	MacAddress;

		///动态密码
		TTORATstpSPPasswordType	OneTimePassword;

		///内网IP地址
		TTORATstpSPIPAddressType	InnerIPAddress;

		///接口语言
		TTORATstpSPLangType	Lang;

		///终端信息
		TTORATstpSPTerminalInfoType	TerminalInfo;

		///网关Mac地址
		TTORATstpSPMacAddressType	GWMacAddress;

		///网关内网IP地址
		TTORATstpSPIPAddressType	GWInnerIPAddress;

		///网关外网IP地址
		TTORATstpSPIPAddressType	GWOuterIPAddress;

		///经纪公司部门代码（以资金账号方式登录时必填）
		TTORATstpSPDepartmentIDType	DepartmentID;

		///硬盘序列号（用户填入）
		TTORATstpSPHDSerialType	HDSerial;

		///认证方式(指纹或钥匙串认证时必填)
		TTORATstpSPAuthModeType	AuthMode;

		///设备标识(指纹认证时必填)
		TTORATstpSPDeviceIDType	DeviceID;

		///认证序列号(指纹或钥匙串认证时必填)
		TTORATstpSPCertSerialType	CertSerial;

		///移动设备手机号
		TTORATstpSPMobileType	Mobile;

		///外网IP地址
		TTORATstpSPIPAddressType	OuterIPAddress;

		///外网端口号
		TTORATstpSPPortType	OuterPort;

		///设备类别(指纹或钥匙串认证时必填)
		TTORATstpSPDeviceTypeType	DeviceType;

	};

	/// 登录应答
	struct CTORATstpSPRspUserLoginField
	{
		 
		///登录成功时间
		TTORATstpSPTimeType	LoginTime;

		///登录账户
		TTORATstpSPLogInAccountType	LogInAccount;

		///登录账户类型
		TTORATstpSPLogInAccountTypeType	LogInAccountType;

		///交易系统名称
		TTORATstpSPSystemNameType	SystemName;

		///前置编号
		TTORATstpSPFrontIDType	FrontID;

		///会话编号
		TTORATstpSPSessionIDType	SessionID;

		///最大报单引用
		TTORATstpSPOrderRefType	MaxOrderRef;

		///私有流长度
		TTORATstpSPVolumeType	PrivateFlowCount;

		///公有流长度
		TTORATstpSPVolumeType	PublicFlowCount;

		///用户请求编号
		TTORATstpSPRequestIDType	RequestID;

		///交易发生的日期
		TTORATstpSPDateType	TradingDay;

		///用户代码
		TTORATstpSPUserIDType	UserID;

		///用户名称
		TTORATstpSPUserNameType	UserName;

		///用户类型
		TTORATstpSPUserTypeType	UserType;

		///经纪公司部门代码
		TTORATstpSPDepartmentIDType	DepartmentID;

		///内部IP地址
		TTORATstpSPIPAddressType	InnerIPAddress;

		///Mac地址
		TTORATstpSPMacAddressType	MacAddress;

		///硬盘序列号
		TTORATstpSPHDSerialType	HDSerial;

		///报单流控
		TTORATstpSPCommFluxType	OrderInsertCommFlux;

		///撤单流控
		TTORATstpSPCommFluxType	OrderActionCommFlux;

		///移动设备手机号
		TTORATstpSPMobileType	Mobile;

		///密码修改周期(天),置为0表永久有效
		TTORATstpSPCountType	PasswordUpdatePeriod;

		///密码有效剩余天数
		TTORATstpSPCountType	PasswordRemainDays;

		///是否需要改密
		TTORATstpSPBoolType	NeedUpdatePassword;

		///上证报单流控
		TTORATstpSPCommFluxType	SSEOrderInsertCommFlux;

		///上证撤单流控
		TTORATstpSPCommFluxType	SSEOrderActionCommFlux;

		///深证报单流控
		TTORATstpSPCommFluxType	SZSEOrderInsertCommFlux;

		///深证撤单流控
		TTORATstpSPCommFluxType	SZSEOrderActionCommFlux;

		///外网IP地址
		TTORATstpSPIPAddressType	OuterIPAddress;

		///外网端口号
		TTORATstpSPPortType	OuterPort;

		///认证序列号
		TTORATstpSPCertSerialType	CertSerial;

	};

	/// 响应信息
	struct CTORATstpSPRspInfoField
	{
		 
		///错误代码
		TTORATstpSPErrorIDType	ErrorID;

		///错误信息
		TTORATstpSPErrorMsgType	ErrorMsg;

	};

	/// 用户登出
	struct CTORATstpSPUserLogoutField
	{
		 
		///用户代码
		TTORATstpSPUserIDType	UserID;

	};

	/// 重置用户密码
	struct CTORATstpSPUserPasswordUpdateField
	{
		 
		///用户代码
		TTORATstpSPUserIDType	UserID;

		///旧密码
		TTORATstpSPPasswordType	OldPassword;

		///新密码
		TTORATstpSPPasswordType	NewPassword;

	};

	/// 请求录入设备序列
	struct CTORATstpSPReqInputDeviceSerialField
	{
		 
		///用户代码
		TTORATstpSPUserIDType	UserID;

		///设备标识
		TTORATstpSPDeviceIDType	DeviceID;

		///设备序列号
		TTORATstpSPCertSerialType	CertSerial;

		///设备类别
		TTORATstpSPDeviceTypeType	DeviceType;

	};

	/// 请求录入设备序列应答
	struct CTORATstpSPRspInputDeviceSerialField
	{
		 
		///用户请求编号
		TTORATstpSPRequestIDType	RequestID;

		///用户代码
		TTORATstpSPUserIDType	UserID;

	};

	/// 输入报单
	struct CTORATstpSPInputOrderField
	{
		 
		///合约在系统中的编号
		TTORATstpSPSecurityIDType	SecurityID;

		///投资者说明的对报单的唯一引用
		TTORATstpSPOrderRefType	OrderRef;

		///限价单或市价单
		TTORATstpSPOrderPriceTypeType	OrderPriceType;

		///买、卖
		TTORATstpSPDirectionType	Direction;

		///按字节表示各单个合约的开平方向
		TTORATstpSPCombOffsetFlagType	CombOffsetFlag;

		///按字节表示各单个合约的组合套保标志
		TTORATstpSPCombHedgeFlagType	CombHedgeFlag;

		///限价单价格
		TTORATstpSPPriceType	LimitPrice;

		///报单数量
		TTORATstpSPVolumeType	VolumeTotalOriginal;

		///IOC、GFS、GFD、GTD、GTC、GFA
		TTORATstpSPTimeConditionType	TimeCondition;

		///AV、MV、CV
		TTORATstpSPVolumeConditionType	VolumeCondition;

		///当成交量类型为MV时有效
		TTORATstpSPVolumeType	MinVolume;

		///强平原因
		TTORATstpSPForceCloseReasonType	ForceCloseReason;

		///用户强评标志
		TTORATstpSPBoolType	UserForceClose;

		///投资者代码
		TTORATstpSPInvestorIDType	InvestorID;

		///一个交易所的编号
		TTORATstpSPExchangeIDType	ExchangeID;

		///目前该字段存放的是上证所和深圳的股东代码。
		TTORATstpSPShareholderIDType	ShareholderID;

		///投资单元代码
		TTORATstpSPBusinessUnitIDType	BusinessUnitID;

		///资金账户
		TTORATstpSPAccountIDType	AccountID;

		///内网IP地址
		TTORATstpSPIPAddressType	InnerIPAddress;

		///Mac地址
		TTORATstpSPMacAddressType	MacAddress;

		///报单编号
		TTORATstpSPOrderSysIDType	OrderSysID;

		///终端信息
		TTORATstpSPTerminalInfoType	TerminalInfo;

		///长字符串附加信息
		TTORATstpSPBigsInfoType	BInfo;

		///短字符串附加信息
		TTORATstpSPShortsInfoType	SInfo;

		///整形附加信息
		TTORATstpSPIntInfoType	IInfo;

		///委托方式
		TTORATstpSPOperwayType	Operway;

		///硬盘序列号
		TTORATstpSPHDSerialType	HDSerial;

		///条件检查
		TTORATstpSPCondCheckType	CondCheck;

		///交易所组合编码(单边平仓必填)
		TTORATstpSPExchangeCombIDType	ExchangeCombID;

		///外网IP地址
		TTORATstpSPIPAddressType	OuterIPAddress;

		///外网端口号
		TTORATstpSPPortType	OuterPort;

	};

	/// 报单
	struct CTORATstpSPOrderField
	{
		 
		///交易日
		TTORATstpSPDateType	TradingDay;

		///交易所代码
		TTORATstpSPExchangeIDType	ExchangeID;

		///合约在系统中的编号
		TTORATstpSPSecurityIDType	SecurityID;

		///前置编号
		TTORATstpSPFrontIDType	FrontID;

		///每一位交易员或其它登录者登录系统获得的会话编号，当前时刻唯一
		TTORATstpSPSessionIDType	SessionID;

		///投资者说明的对报单的唯一引用
		TTORATstpSPOrderRefType	OrderRef;

		///报单编号
		TTORATstpSPOrderSysIDType	OrderSysID;

		///交易单元代码
		TTORATstpSPPbuIDType	PbuID;

		///本地报单顺序号
		TTORATstpSPOrderLocalIDType	OrderLocalID;

		///限价单或市价单
		TTORATstpSPOrderPriceTypeType	OrderPriceType;

		///买、卖
		TTORATstpSPDirectionType	Direction;

		///按字节表示各单个合约的开平方向
		TTORATstpSPCombOffsetFlagType	CombOffsetFlag;

		///按字节表示各单个合约的组合套保标志
		TTORATstpSPCombHedgeFlagType	CombHedgeFlag;

		///限价单价格
		TTORATstpSPPriceType	Price;

		///报单数量
		TTORATstpSPVolumeType	VolumeTotalOriginal;

		///IOC、GFS、GFD、GTD、GTC、GFA
		TTORATstpSPTimeConditionType	TimeCondition;

		///AV、MV、CV
		TTORATstpSPVolumeConditionType	VolumeCondition;

		///当成交量类型为MV时有效
		TTORATstpSPVolumeType	MinVolume;

		///请求编号
		TTORATstpSPRequestIDType	RequestID;

		///交易所下的交易市场，如沪A、沪B市场
		TTORATstpSPMarketIDType	MarketID;

		///客户在系统中的编号，编号唯一且遵循交易所制定的编码规则
		TTORATstpSPShareholderIDType	ShareholderID;

		///报单操作状态
		TTORATstpSPOrderOperateStatusType	OrderOperateStatus;

		///核心已处理、交易所已接收、部分成交、全部成交、部撤、全撤、废单等
		TTORATstpSPOrderStatusType	OrderStatus;

		///报单完成数量
		TTORATstpSPVolumeType	VolumeTraded;

		///报单日期
		TTORATstpSPDateType	InsertDate;

		///委托时间
		TTORATstpSPTimeType	InsertTime;

		///交易所接收时间
		TTORATstpSPTimeType	AcceptTime;

		///撤销时间
		TTORATstpSPTimeType	CancelTime;

		///投资者代码
		TTORATstpSPInvestorIDType	InvestorID;

		///状态信息
		TTORATstpSPStatusMsgType	StatusMsg;

		///用户强评标志
		TTORATstpSPBoolType	UserForceClose;

		///申报操作员
		TTORATstpSPUserIDType	InsertUserID;

		///申报撤销操作员
		TTORATstpSPUserIDType	CancelUserID;

		///投资单元代码
		TTORATstpSPBusinessUnitIDType	BusinessUnitID;

		///经纪公司部门代码
		TTORATstpSPDepartmentIDType	DepartmentID;

		///资金账户
		TTORATstpSPAccountIDType	AccountID;

		///币种
		TTORATstpSPCurrencyIDType	CurrencyID;

		///内网IP地址
		TTORATstpSPIPAddressType	InnerIPAddress;

		///Mac地址
		TTORATstpSPMacAddressType	MacAddress;

		///长字符串附加信息
		TTORATstpSPBigsInfoType	BInfo;

		///短字符串附加信息
		TTORATstpSPShortsInfoType	SInfo;

		///整形附加信息
		TTORATstpSPIntInfoType	IInfo;

		///强平原因
		TTORATstpSPForceCloseReasonType	ForceCloseReason;

		///终端信息
		TTORATstpSPTerminalInfoType	TerminalInfo;

		///委托方式
		TTORATstpSPOperwayType	Operway;

		///硬盘序列号
		TTORATstpSPHDSerialType	HDSerial;

		///交易所返回的撤单数量
		TTORATstpSPVolumeType	VolumeCanceled;

		///交易所组合编码(单边平仓必填)
		TTORATstpSPExchangeCombIDType	ExchangeCombID;

		///外网IP地址
		TTORATstpSPIPAddressType	OuterIPAddress;

		///外网端口号
		TTORATstpSPPortType	OuterPort;

		///成交金额
		TTORATstpSPMoneyType	TradeAmount;

	};

	/// 用户标识
	struct CTORATstpSPUserRefField
	{
		 
		///用户代码
		TTORATstpSPUserIDType	UserID;

	};

	/// 输入撤单操作
	struct CTORATstpSPInputOrderActionField
	{
		 
		///投资者代码
		TTORATstpSPInvestorIDType	InvestorID;

		///投资者说明的对报单操作的唯一引用
		TTORATstpSPOrderRefType	OrderActionRef;

		///投资者说明的对报单的唯一引用
		TTORATstpSPOrderRefType	OrderRef;

		///前置编号
		TTORATstpSPFrontIDType	FrontID;

		///每一位交易员或其它登录者登录系统获得的会话编号，当前时刻唯一
		TTORATstpSPSessionIDType	SessionID;

		///一个交易所的编号
		TTORATstpSPExchangeIDType	ExchangeID;

		///报单编号
		TTORATstpSPOrderSysIDType	OrderSysID;

		///委托操作标志
		TTORATstpSPOrderActionFlagType	OrderActionFlag;

		///合约在系统中的编号
		TTORATstpSPSecurityIDType	SecurityID;

		///内网IP地址
		TTORATstpSPIPAddressType	InnerIPAddress;

		///Mac地址
		TTORATstpSPMacAddressType	MacAddress;

		///全系统的唯一报单编号。
		TTORATstpSPOrderLocalIDType	CancelOrderLocalID;

		///终端信息
		TTORATstpSPTerminalInfoType	TerminalInfo;

		///长字符串附加信息
		TTORATstpSPBigsInfoType	BInfo;

		///短字符串附加信息
		TTORATstpSPShortsInfoType	SInfo;

		///整形附加信息
		TTORATstpSPIntInfoType	IInfo;

		///委托方式
		TTORATstpSPOperwayType	Operway;

		///硬盘序列号
		TTORATstpSPHDSerialType	HDSerial;

		///外网IP地址
		TTORATstpSPIPAddressType	OuterIPAddress;

		///外网端口号
		TTORATstpSPPortType	OuterPort;

	};

	/// 成交
	struct CTORATstpSPTradeField
	{
		 
		///投资者代码
		TTORATstpSPInvestorIDType	InvestorID;

		///合约在系统中的编号
		TTORATstpSPSecurityIDType	SecurityID;

		///用户代码
		TTORATstpSPUserIDType	InsertUserID;

		///交易所代码
		TTORATstpSPExchangeIDType	ExchangeID;

		///成交编号
		TTORATstpSPTradeIDType	TradeID;

		///买、卖
		TTORATstpSPDirectionType	Direction;

		///报单编号
		TTORATstpSPOrderSysIDType	OrderSysID;

		///交易所下的交易市场，如沪A、沪B市场
		TTORATstpSPMarketIDType	MarketID;

		///客户在系统中的编号，编号唯一且遵循交易所制定的编码规则
		TTORATstpSPShareholderIDType	ShareholderID;

		///开仓、平仓等
		TTORATstpSPOffsetFlagType	OffsetFlag;

		///投机、套利等
		TTORATstpSPHedgeFlagType	HedgeFlag;

		///成交价格
		TTORATstpSPPriceType	Price;

		///成交数量
		TTORATstpSPVolumeType	Volume;

		///成交日期
		TTORATstpSPDateType	TradeDate;

		///成交时间
		TTORATstpSPTimeType	TradeTime;

		///交易所交易单元代码
		TTORATstpSPPbuIDType	PbuID;

		///本地报单顺序号
		TTORATstpSPOrderLocalIDType	OrderLocalID;

		///交易发生的日期
		TTORATstpSPDateType	TradingDay;

		///投资单元代码
		TTORATstpSPBusinessUnitIDType	BusinessUnitID;

		///资金账户
		TTORATstpSPAccountIDType	AccountID;

		///币种
		TTORATstpSPCurrencyIDType	CurrencyID;

		///报单引用
		TTORATstpSPOrderRefType	OrderRef;

		///经纪公司部门代码
		TTORATstpSPDepartmentIDType	DepartmentID;

	};

	/// 行权输入
	struct CTORATstpSPInputExerciseField
	{
		 
		///投资者代码
		TTORATstpSPInvestorIDType	InvestorID;

		///合约在系统中的编号
		TTORATstpSPSecurityIDType	SecurityID;

		///投资者说明的对行权的唯一引用
		TTORATstpSPOrderRefType	ExerciseRef;

		///行权数量
		TTORATstpSPVolumeType	Volume;

		///投资单元代码
		TTORATstpSPBusinessUnitIDType	BusinessUnitID;

		///执行类型
		TTORATstpSPExerciseTypeType	ExerciseType;

		///交易所代码
		TTORATstpSPExchangeIDType	ExchangeID;

		///目前该字段存放的是上证所和深圳的股东代码。
		TTORATstpSPShareholderIDType	ShareholderID;

		///资金账户
		TTORATstpSPAccountIDType	AccountID;

		///内网IP地址
		TTORATstpSPIPAddressType	InnerIPAddress;

		///Mac地址
		TTORATstpSPMacAddressType	MacAddress;

		///系统行权编号
		TTORATstpSPOrderSysIDType	ExerciseSysID;

		///终端信息
		TTORATstpSPTerminalInfoType	TerminalInfo;

		///长字符串附加信息
		TTORATstpSPBigsInfoType	BInfo;

		///短字符串附加信息
		TTORATstpSPShortsInfoType	SInfo;

		///整形附加信息
		TTORATstpSPIntInfoType	IInfo;

		///委托方式
		TTORATstpSPOperwayType	Operway;

		///硬盘序列号
		TTORATstpSPHDSerialType	HDSerial;

		///外网IP地址
		TTORATstpSPIPAddressType	OuterIPAddress;

		///外网端口号
		TTORATstpSPPortType	OuterPort;

	};

	/// 行权回报
	struct CTORATstpSPExerciseField
	{
		 
		///交易日
		TTORATstpSPDateType	TradingDay;

		///交易所代码
		TTORATstpSPExchangeIDType	ExchangeID;

		///合约在系统中的编号
		TTORATstpSPSecurityIDType	SecurityID;

		///前置编号
		TTORATstpSPFrontIDType	FrontID;

		///会话编号
		TTORATstpSPSessionIDType	SessionID;

		///投资者说明的对报单的唯一引用
		TTORATstpSPOrderRefType	ExerciseRef;

		///全系统的唯一报单编号
		TTORATstpSPOrderSysIDType	ExerciseSysID;

		///交易单元代码
		TTORATstpSPPbuIDType	PbuID;

		///本地报单编号
		TTORATstpSPOrderLocalIDType	ExerciseLocalID;

		///执行类型
		TTORATstpSPExerciseTypeType	ExerciseType;

		///投资者代码
		TTORATstpSPInvestorIDType	InvestorID;

		///投资单元代码
		TTORATstpSPBusinessUnitIDType	BusinessUnitID;

		///行权数量
		TTORATstpSPVolumeType	Volume;

		///交易所返回的撤单数量
		TTORATstpSPVolumeType	VolumeCanceled;

		///市场代码
		TTORATstpSPMarketIDType	MarketID;

		///目前该字段存放的是上证所和深圳的股东代码。
		TTORATstpSPShareholderIDType	ShareholderID;

		///a：普通，b：信用，c：衍生品
		TTORATstpSPShareholderIDTypeType	ShareholderIDType;

		///经纪公司部门代码
		TTORATstpSPDepartmentIDType	DepartmentID;

		///资金账户
		TTORATstpSPAccountIDType	AccountID;

		///币种
		TTORATstpSPCurrencyIDType	CurrencyID;

		///行权状态
		TTORATstpSPExerciseStatusType	ExerciseStatus;

		///行权操作状态
		TTORATstpSPOrderOperateStatusType	ExerciseOperateStatus;

		///状态信息
		TTORATstpSPStatusMsgType	StatusMsg;

		///系统错误代码
		TTORATstpSPErrorIDType	ErrorID;

		///交易所为营业部分配的代码
		TTORATstpSPBranchIDType	BranchID;

		///报单申报用户
		TTORATstpSPUserIDType	InsertUserID;

		///申报日期
		TTORATstpSPDateType	InsertDate;

		///申报时间
		TTORATstpSPTimeType	InsertTime;

		///申报时间(毫秒)
		TTORATstpSPMillisecType	InsertMillisec;

		///交易所接收时间
		TTORATstpSPTimeType	AcceptTime;

		///撤销时间
		TTORATstpSPTimeType	CancelTime;

		///撤销申报用户
		TTORATstpSPUserIDType	CancelUserID;

		///现货仓位行权冻结流水号
		TTORATstpSPIntSerialType	StockPositionExerciseSerial;

		///现货系统仓位调拨流水号
		TTORATstpSPIntSerialType	StockPositionSerial;

		///内网IP地址
		TTORATstpSPIPAddressType	InnerIPAddress;

		///Mac地址
		TTORATstpSPMacAddressType	MacAddress;

		///请求编号
		TTORATstpSPRequestIDType	RequestID;

		///终端信息
		TTORATstpSPTerminalInfoType	TerminalInfo;

		///记录序号(仅上证报盘使用)
		TTORATstpSPSequenceNoType	RecordNumber;

		///长字符串附加信息
		TTORATstpSPBigsInfoType	BInfo;

		///短字符串附加信息
		TTORATstpSPShortsInfoType	SInfo;

		///整形附加信息
		TTORATstpSPIntInfoType	IInfo;

		///委托方式
		TTORATstpSPOperwayType	Operway;

		///硬盘序列号
		TTORATstpSPHDSerialType	HDSerial;

		///移动设备手机号
		TTORATstpSPMobileType	Mobile;

		///外网IP地址
		TTORATstpSPIPAddressType	OuterIPAddress;

		///外网端口号
		TTORATstpSPPortType	OuterPort;

	};

	/// 行权操作输入
	struct CTORATstpSPInputExerciseActionField
	{
		 
		///投资者代码
		TTORATstpSPInvestorIDType	InvestorID;

		///报单操作引用
		TTORATstpSPOrderRefType	ExerciseActionRef;

		///报单引用
		TTORATstpSPOrderRefType	ExerciseRef;

		///前置编号
		TTORATstpSPFrontIDType	FrontID;

		///会话编号
		TTORATstpSPSessionIDType	SessionID;

		///交易所代码
		TTORATstpSPExchangeIDType	ExchangeID;

		///全系统的唯一报单编号。
		TTORATstpSPOrderSysIDType	ExerciseSysID;

		///操作标志
		TTORATstpSPOrderActionFlagType	ExerciseActionFlag;

		///合约在系统中的编号
		TTORATstpSPSecurityIDType	SecurityID;

		///内网IP地址
		TTORATstpSPIPAddressType	InnerIPAddress;

		///Mac地址
		TTORATstpSPMacAddressType	MacAddress;

		///全系统的唯一报单编号。
		TTORATstpSPOrderLocalIDType	CancelExerciseLocalID;

		///终端信息
		TTORATstpSPTerminalInfoType	TerminalInfo;

		///长字符串附加信息
		TTORATstpSPBigsInfoType	BInfo;

		///短字符串附加信息
		TTORATstpSPShortsInfoType	SInfo;

		///整形附加信息
		TTORATstpSPIntInfoType	IInfo;

		///委托方式
		TTORATstpSPOperwayType	Operway;

		///硬盘序列号
		TTORATstpSPHDSerialType	HDSerial;

		///外网IP地址
		TTORATstpSPIPAddressType	OuterIPAddress;

		///外网端口号
		TTORATstpSPPortType	OuterPort;

	};

	/// 输入锁定
	struct CTORATstpSPInputLockField
	{
		 
		///合约在系统中的编号
		TTORATstpSPSecurityIDType	SecurityID;

		///投资者说明的对锁定的唯一引用
		TTORATstpSPOrderRefType	LockRef;

		///锁定类别
		TTORATstpSPLockTypeType	LockType;

		///报单数量
		TTORATstpSPVolumeType	Volume;

		///投资者代码
		TTORATstpSPInvestorIDType	InvestorID;

		///一个交易所的编号
		TTORATstpSPExchangeIDType	ExchangeID;

		///目前该字段存放的是上证所和深圳的股东代码
		TTORATstpSPShareholderIDType	ShareholderID;

		///投资单元代码
		TTORATstpSPBusinessUnitIDType	BusinessUnitID;

		///内网IP地址
		TTORATstpSPIPAddressType	InnerIPAddress;

		///Mac地址
		TTORATstpSPMacAddressType	MacAddress;

		///终端信息
		TTORATstpSPTerminalInfoType	TerminalInfo;

		///锁定编号
		TTORATstpSPOrderSysIDType	LockSysID;

		///长字符串附加信息
		TTORATstpSPBigsInfoType	BInfo;

		///短字符串附加信息
		TTORATstpSPShortsInfoType	SInfo;

		///整形附加信息
		TTORATstpSPIntInfoType	IInfo;

		///委托方式
		TTORATstpSPOperwayType	Operway;

		///硬盘序列号
		TTORATstpSPHDSerialType	HDSerial;

		///外网IP地址
		TTORATstpSPIPAddressType	OuterIPAddress;

		///外网端口号
		TTORATstpSPPortType	OuterPort;

	};

	/// 锁定委托
	struct CTORATstpSPLockField
	{
		 
		///交易日
		TTORATstpSPDateType	TradingDay;

		///交易所代码
		TTORATstpSPExchangeIDType	ExchangeID;

		///合约在系统中的编号
		TTORATstpSPSecurityIDType	SecurityID;

		///前置编号
		TTORATstpSPFrontIDType	FrontID;

		///每一位交易员或其它登录者登录系统获得的会话编号，当前时刻唯一
		TTORATstpSPSessionIDType	SessionID;

		///投资者说明的对锁定的唯一引用
		TTORATstpSPOrderRefType	LockRef;

		///报单编号
		TTORATstpSPOrderSysIDType	LockSysID;

		///交易单元代码
		TTORATstpSPPbuIDType	PbuID;

		///本地报单顺序号
		TTORATstpSPOrderLocalIDType	LockLocalID;

		///锁定类别
		TTORATstpSPLockTypeType	LockType;

		///报单数量
		TTORATstpSPVolumeType	Volume;

		///交易所返回的撤单数量
		TTORATstpSPVolumeType	VolumeCanceled;

		///请求编号
		TTORATstpSPRequestIDType	RequestID;

		///交易所下的交易市场，如沪A、沪B市场
		TTORATstpSPMarketIDType	MarketID;

		///客户在系统中的编号，编号唯一且遵循交易所制定的编码规则
		TTORATstpSPShareholderIDType	ShareholderID;

		///普通、信用、衍生品
		TTORATstpSPShareholderIDTypeType	ShareholderIDType;

		///锁定状态
		TTORATstpSPLockStatusType	LockStatus;

		///报单日期
		TTORATstpSPDateType	InsertDate;

		///申报时间
		TTORATstpSPTimeType	InsertTime;

		///交易所接收时间
		TTORATstpSPTimeType	AcceptTime;

		///撤单时间
		TTORATstpSPTimeType	CancelTime;

		///交易所营业部编码
		TTORATstpSPBranchIDType	BranchID;

		///投资者代码
		TTORATstpSPInvestorIDType	InvestorID;

		///投资单元代码
		TTORATstpSPBusinessUnitIDType	BusinessUnitID;

		///报盘错误代码
		TTORATstpSPErrorIDType	ErrorID;

		///状态信息
		TTORATstpSPStatusMsgType	StatusMsg;

		///申报操作员
		TTORATstpSPUserIDType	InsertUserID;

		///撤销申报用户
		TTORATstpSPUserIDType	CancelUserID;

		///现货仓位锁定流水号
		TTORATstpSPIntSerialType	StockPositionLockSerial;

		///现货系统仓位调拨流水号
		TTORATstpSPIntSerialType	StockPositionSerial;

		///内网IP地址
		TTORATstpSPIPAddressType	InnerIPAddress;

		///Mac地址
		TTORATstpSPMacAddressType	MacAddress;

		///终端信息
		TTORATstpSPTerminalInfoType	TerminalInfo;

		///长字符串附加信息
		TTORATstpSPBigsInfoType	BInfo;

		///短字符串附加信息
		TTORATstpSPShortsInfoType	SInfo;

		///整形附加信息
		TTORATstpSPIntInfoType	IInfo;

		///记录序号(仅上证报盘使用)
		TTORATstpSPSequenceNoType	RecordNumber;

		///委托方式
		TTORATstpSPOperwayType	Operway;

		///硬盘序列号
		TTORATstpSPHDSerialType	HDSerial;

		///移动设备手机号
		TTORATstpSPMobileType	Mobile;

		///外网IP地址
		TTORATstpSPIPAddressType	OuterIPAddress;

		///外网端口号
		TTORATstpSPPortType	OuterPort;

	};

	/// 行权操作输入
	struct CTORATstpSPInputLockActionField
	{
		 
		///投资者代码
		TTORATstpSPInvestorIDType	InvestorID;

		///锁定操作引用
		TTORATstpSPOrderRefType	LockActionRef;

		///锁定引用
		TTORATstpSPOrderRefType	LockRef;

		///前置编号
		TTORATstpSPFrontIDType	FrontID;

		///会话编号
		TTORATstpSPSessionIDType	SessionID;

		///交易所代码
		TTORATstpSPExchangeIDType	ExchangeID;

		///全系统的唯一报单编号。
		TTORATstpSPOrderSysIDType	LockSysID;

		///操作标志
		TTORATstpSPOrderActionFlagType	LockActionFlag;

		///合约在系统中的编号
		TTORATstpSPSecurityIDType	SecurityID;

		///内网IP地址
		TTORATstpSPIPAddressType	InnerIPAddress;

		///Mac地址
		TTORATstpSPMacAddressType	MacAddress;

		///全系统的唯一报单编号。
		TTORATstpSPOrderLocalIDType	CancelLockLocalID;

		///终端信息
		TTORATstpSPTerminalInfoType	TerminalInfo;

		///长字符串附加信息
		TTORATstpSPBigsInfoType	BInfo;

		///短字符串附加信息
		TTORATstpSPShortsInfoType	SInfo;

		///整形附加信息
		TTORATstpSPIntInfoType	IInfo;

		///委托方式
		TTORATstpSPOperwayType	Operway;

		///硬盘序列号
		TTORATstpSPHDSerialType	HDSerial;

		///外网IP地址
		TTORATstpSPIPAddressType	OuterIPAddress;

		///外网端口号
		TTORATstpSPPortType	OuterPort;

	};

	/// 证券处置表
	struct CTORATstpSPStockDisposalField
	{
		 
		///交易日
		TTORATstpSPDateType	TradingDay;

		///交易所代码
		TTORATstpSPExchangeIDType	ExchangeID;

		///个股期权标的合约代码
		TTORATstpSPSecurityIDType	SecurityID;

		///前置编号
		TTORATstpSPFrontIDType	FrontID;

		///会话编号
		TTORATstpSPSessionIDType	SessionID;

		///投资者说明的对证券处置的唯一引用
		TTORATstpSPOrderRefType	StockDisposalRef;

		///系统证券处置编号
		TTORATstpSPOrderSysIDType	StockDisposalSysID;

		///交易单元代码
		TTORATstpSPPbuIDType	PbuID;

		///本地证券处置编号
		TTORATstpSPOrderLocalIDType	StockDisposalLocalID;

		///证券处置类别
		TTORATstpSPStockDisposalTypeType	StockDisposalType;

		///投资者代码
		TTORATstpSPInvestorIDType	InvestorID;

		///投资单元代码
		TTORATstpSPBusinessUnitIDType	BusinessUnitID;

		///证券处置数量
		TTORATstpSPVolumeType	Volume;

		///证券处置撤销数量
		TTORATstpSPVolumeType	VolumeCanceled;

		///市场代码
		TTORATstpSPMarketIDType	MarketID;

		///目前该字段存放的是上证所和深圳的股东代码。
		TTORATstpSPShareholderIDType	ShareholderID;

		///普通、信用、衍生品
		TTORATstpSPShareholderIDTypeType	ShareholderIDType;

		///经纪公司部门代码
		TTORATstpSPDepartmentIDType	DepartmentID;

		///证券处置状态
		TTORATstpSPStockDisposalStatusType	StockDisposalStatus;

		///证券处置操作状态
		TTORATstpSPOrderOperateStatusType	StockDisposalOperateStatus;

		///状态信息
		TTORATstpSPStatusMsgType	StatusMsg;

		///系统错误代码
		TTORATstpSPErrorIDType	ErrorID;

		///交易所为营业部分配的代码
		TTORATstpSPBranchIDType	BranchID;

		///报单申报用户
		TTORATstpSPUserIDType	InsertUserID;

		///申报日期
		TTORATstpSPDateType	InsertDate;

		///申报时间
		TTORATstpSPTimeType	InsertTime;

		///申报时间(毫秒)
		TTORATstpSPMillisecType	InsertMillisec;

		///交易所接收时间
		TTORATstpSPTimeType	AcceptTime;

		///撤销时间
		TTORATstpSPTimeType	CancelTime;

		///撤销申报用户
		TTORATstpSPUserIDType	CancelUserID;

		///内网IP地址
		TTORATstpSPIPAddressType	InnerIPAddress;

		///Mac地址
		TTORATstpSPMacAddressType	MacAddress;

		///请求编号
		TTORATstpSPRequestIDType	RequestID;

		///终端信息
		TTORATstpSPTerminalInfoType	TerminalInfo;

		///记录序号(仅上证报盘使用)
		TTORATstpSPSequenceNoType	RecordNumber;

		///长字符串附加信息
		TTORATstpSPBigsInfoType	BInfo;

		///短字符串附加信息
		TTORATstpSPShortsInfoType	SInfo;

		///整形附加信息
		TTORATstpSPIntInfoType	IInfo;

		///委托方式
		TTORATstpSPOperwayType	Operway;

		///硬盘序列号
		TTORATstpSPHDSerialType	HDSerial;

		///移动设备手机号
		TTORATstpSPMobileType	Mobile;

		///外网IP地址
		TTORATstpSPIPAddressType	OuterIPAddress;

		///外网端口号
		TTORATstpSPPortType	OuterPort;

	};

	/// 组合委托输入
	struct CTORATstpSPInputCombOrderField
	{
		 
		///组合合约代码
		TTORATstpSPSecurityIDType	SecurityID;

		///投资者说明的对组合的唯一引用
		TTORATstpSPOrderRefType	CombOrderRef;

		///组合策略
		TTORATstpSPCombinationStrategyType	CombinationStrategy;

		///组合报单类别
		TTORATstpSPCombDirectionType	CombDirection;

		///交易所组合编码(拆分时必填)
		TTORATstpSPExchangeCombIDType	ExchangeCombID;

		///报单数量
		TTORATstpSPVolumeType	Volume;

		///投资者代码
		TTORATstpSPInvestorIDType	InvestorID;

		///一个交易所的编号
		TTORATstpSPExchangeIDType	ExchangeID;

		///目前该字段存放的是上证所和深圳的股东代码
		TTORATstpSPShareholderIDType	ShareholderID;

		///投资单元代码
		TTORATstpSPBusinessUnitIDType	BusinessUnitID;

		///资金账户
		TTORATstpSPAccountIDType	AccountID;

		///内网IP地址
		TTORATstpSPIPAddressType	InnerIPAddress;

		///Mac地址
		TTORATstpSPMacAddressType	MacAddress;

		///终端信息
		TTORATstpSPTerminalInfoType	TerminalInfo;

		///组合系统编号
		TTORATstpSPOrderSysIDType	CombOrderSysID;

		///长字符串附加信息
		TTORATstpSPBigsInfoType	BInfo;

		///短字符串附加信息
		TTORATstpSPShortsInfoType	SInfo;

		///整形附加信息
		TTORATstpSPIntInfoType	IInfo;

		///委托方式
		TTORATstpSPOperwayType	Operway;

		///硬盘序列号
		TTORATstpSPHDSerialType	HDSerial;

		///外网IP地址
		TTORATstpSPIPAddressType	OuterIPAddress;

		///外网端口号
		TTORATstpSPPortType	OuterPort;

	};

	/// 证券组合委托
	struct CTORATstpSPCombOrderField
	{
		 
		///交易日
		TTORATstpSPDateType	TradingDay;

		///交易所代码
		TTORATstpSPExchangeIDType	ExchangeID;

		///组合合约代码
		TTORATstpSPSecurityIDType	SecurityID;

		///组合策略
		TTORATstpSPCombinationStrategyType	CombinationStrategy;

		///组合报单类别
		TTORATstpSPCombDirectionType	CombDirection;

		///前置编号
		TTORATstpSPFrontIDType	FrontID;

		///每一位交易员或其它登录者登录系统获得的会话编号，当前时刻唯一
		TTORATstpSPSessionIDType	SessionID;

		///投资者说明的对组合的唯一引用
		TTORATstpSPOrderRefType	CombOrderRef;

		///组合系统编号
		TTORATstpSPOrderSysIDType	CombOrderSysID;

		///交易单元代码
		TTORATstpSPPbuIDType	PbuID;

		///本地组合报单编号
		TTORATstpSPOrderLocalIDType	CombOrderLocalID;

		///报单数量
		TTORATstpSPVolumeType	Volume;

		///交易所返回的撤单数量
		TTORATstpSPVolumeType	VolumeCanceled;

		///请求编号
		TTORATstpSPRequestIDType	RequestID;

		///交易所下的交易市场，如沪A、沪B市场
		TTORATstpSPMarketIDType	MarketID;

		///客户在系统中的编号，编号唯一且遵循交易所制定的编码规则
		TTORATstpSPShareholderIDType	ShareholderID;

		///普通、信用、衍生品
		TTORATstpSPShareholderIDTypeType	ShareholderIDType;

		///组合委托状态
		TTORATstpSPOrderStatusType	CombOrderStatus;

		///组合委托操作状态
		TTORATstpSPOrderOperateStatusType	CombOrderOperateStatus;

		///经纪公司部门代码
		TTORATstpSPDepartmentIDType	DepartmentID;

		///资金账户
		TTORATstpSPAccountIDType	AccountID;

		///币种
		TTORATstpSPCurrencyIDType	CurrencyID;

		///交易所组合编码
		TTORATstpSPExchangeCombIDType	ExchangeCombID;

		///报单日期
		TTORATstpSPDateType	InsertDate;

		///申报时间
		TTORATstpSPTimeType	InsertTime;

		///申报时间(毫秒)
		TTORATstpSPMillisecType	InsertMillisec;

		///交易所接收时间
		TTORATstpSPTimeType	AcceptTime;

		///撤单时间
		TTORATstpSPTimeType	CancelTime;

		///交易所营业部编码
		TTORATstpSPBranchIDType	BranchID;

		///投资者代码
		TTORATstpSPInvestorIDType	InvestorID;

		///投资单元代码
		TTORATstpSPBusinessUnitIDType	BusinessUnitID;

		///报盘错误代码
		TTORATstpSPErrorIDType	ErrorID;

		///状态信息
		TTORATstpSPStatusMsgType	StatusMsg;

		///申报操作员
		TTORATstpSPUserIDType	InsertUserID;

		///撤销申报用户
		TTORATstpSPUserIDType	CancelUserID;

		///内网IP地址
		TTORATstpSPIPAddressType	InnerIPAddress;

		///Mac地址
		TTORATstpSPMacAddressType	MacAddress;

		///终端信息
		TTORATstpSPTerminalInfoType	TerminalInfo;

		///记录序号(仅上证报盘使用)
		TTORATstpSPSequenceNoType	RecordNumber;

		///长字符串附加信息
		TTORATstpSPBigsInfoType	BInfo;

		///短字符串附加信息
		TTORATstpSPShortsInfoType	SInfo;

		///整形附加信息
		TTORATstpSPIntInfoType	IInfo;

		///委托方式
		TTORATstpSPOperwayType	Operway;

		///硬盘序列号
		TTORATstpSPHDSerialType	HDSerial;

		///移动设备手机号
		TTORATstpSPMobileType	Mobile;

		///外网IP地址
		TTORATstpSPIPAddressType	OuterIPAddress;

		///外网端口号
		TTORATstpSPPortType	OuterPort;

	};

	/// 组合委托操作输入
	struct CTORATstpSPInputCombOrderActionField
	{
		 
		///投资者代码
		TTORATstpSPInvestorIDType	InvestorID;

		///组合报单操作引用
		TTORATstpSPOrderRefType	CombOrderActionRef;

		///组合报单引用
		TTORATstpSPOrderRefType	CombOrderRef;

		///前置编号
		TTORATstpSPFrontIDType	FrontID;

		///会话编号
		TTORATstpSPSessionIDType	SessionID;

		///交易所代码
		TTORATstpSPExchangeIDType	ExchangeID;

		///全系统的唯一组合报单编号。
		TTORATstpSPOrderSysIDType	CombOrderSysID;

		///组合报单操作标志
		TTORATstpSPOrderActionFlagType	CombOrderActionFlag;

		///组合合约在系统中的编号
		TTORATstpSPSecurityIDType	SecurityID;

		///内网IP地址
		TTORATstpSPIPAddressType	InnerIPAddress;

		///Mac地址
		TTORATstpSPMacAddressType	MacAddress;

		///全系统的唯一的组合报单撤单编号
		TTORATstpSPOrderLocalIDType	CancelCombOrderLocalID;

		///终端信息
		TTORATstpSPTerminalInfoType	TerminalInfo;

		///长字符串附加信息
		TTORATstpSPBigsInfoType	BInfo;

		///短字符串附加信息
		TTORATstpSPShortsInfoType	SInfo;

		///整形附加信息
		TTORATstpSPIntInfoType	IInfo;

		///委托方式
		TTORATstpSPOperwayType	Operway;

		///硬盘序列号
		TTORATstpSPHDSerialType	HDSerial;

		///外网IP地址
		TTORATstpSPIPAddressType	OuterIPAddress;

		///外网端口号
		TTORATstpSPPortType	OuterPort;

	};

	/// 条件单录入域
	struct CTORATstpSPInputCondOrderField
	{
		 
		///合约在系统中的编号
		TTORATstpSPSecurityIDType	SecurityID;

		///投资者说明的对条件单的唯一引用
		TTORATstpSPOrderRefType	CondOrderRef;

		///限价单或市价单
		TTORATstpSPOrderPriceTypeType	OrderPriceType;

		///买、卖
		TTORATstpSPDirectionType	Direction;

		///按字节表示各单个合约的开平方向
		TTORATstpSPCombOffsetFlagType	CombOffsetFlag;

		///按字节表示各单个合约的组合套保标志
		TTORATstpSPCombHedgeFlagType	CombHedgeFlag;

		///限价单价格
		TTORATstpSPPriceType	LimitPrice;

		///报单数量
		TTORATstpSPVolumeType	VolumeTotalOriginal;

		///IOC、GFS、GFD、GTD、GTC、GFA
		TTORATstpSPTimeConditionType	TimeCondition;

		///AV、MV、CV
		TTORATstpSPVolumeConditionType	VolumeCondition;

		///当成交量类型为MV时有效
		TTORATstpSPVolumeType	MinVolume;

		///强平原因
		TTORATstpSPForceCloseReasonType	ForceCloseReason;

		///用户强评标志
		TTORATstpSPBoolType	UserForceClose;

		///投资者代码
		TTORATstpSPInvestorIDType	InvestorID;

		///一个交易所的编号
		TTORATstpSPExchangeIDType	ExchangeID;

		///目前该字段存放的是上证所和深圳的股东代码
		TTORATstpSPShareholderIDType	ShareholderID;

		///投资单元代码
		TTORATstpSPBusinessUnitIDType	BusinessUnitID;

		///资金账户
		TTORATstpSPAccountIDType	AccountID;

		///内网IP地址
		TTORATstpSPIPAddressType	InnerIPAddress;

		///Mac地址
		TTORATstpSPMacAddressType	MacAddress;

		///报单编号
		TTORATstpSPCondOrderIDType	CondOrderID;

		///终端信息
		TTORATstpSPTerminalInfoType	TerminalInfo;

		///长字符串附加信息
		TTORATstpSPBigsInfoType	BInfo;

		///短字符串附加信息
		TTORATstpSPShortsInfoType	SInfo;

		///整形附加信息
		TTORATstpSPIntInfoType	IInfo;

		///报单数量类型
		TTORATstpSPOrderVolumeTypeType	OrderVolumeType;

		///条件单触发条件
		TTORATstpSPContingentConditionType	ContingentCondition;

		///条件价
		TTORATstpSPPriceType	ConditionPrice;

		///价格浮动tick数,大于0向上浮动,小于0向下浮动,=0不浮动
		TTORATstpSPVolumeType	PriceTicks;

		///数量浮动倍数,必须>=0
		TTORATstpSPVolumeMultipleType	VolumeMultiple;

		///相关前置编号
		TTORATstpSPFrontIDType	RelativeFrontID;

		///相关会话编号
		TTORATstpSPSessionIDType	RelativeSessionID;

		///相关条件参数,可能为OrderRef、OrderSysID、Time和SecurityID
		TTORATstpSPRelativeCondParamType	RelativeParam;

		///附加触发条件
		TTORATstpSPContingentConditionType	AppendContingentCondition;

		///附加条件价
		TTORATstpSPPriceType	AppendConditionPrice;

		///附加相关前置编号
		TTORATstpSPFrontIDType	AppendRelativeFrontID;

		///附加相关会话编号
		TTORATstpSPSessionIDType	AppendRelativeSessionID;

		///附加相关条件参数,可能为OrderRef、OrderSysID、Time和SecurityID
		TTORATstpSPRelativeCondParamType	AppendRelativeParam;

		///委托方式
		TTORATstpSPOperwayType	Operway;

		///硬盘序列号
		TTORATstpSPHDSerialType	HDSerial;

		///外网IP地址
		TTORATstpSPIPAddressType	OuterIPAddress;

		///外网端口号
		TTORATstpSPPortType	OuterPort;

	};

	/// 条件单域
	struct CTORATstpSPConditionOrderField
	{
		 
		///交易日
		TTORATstpSPDateType	TradingDay;

		///合约在系统中的编号
		TTORATstpSPSecurityIDType	SecurityID;

		///投资者说明的对条件单的唯一引用
		TTORATstpSPOrderRefType	CondOrderRef;

		///限价单或市价单
		TTORATstpSPOrderPriceTypeType	OrderPriceType;

		///买、卖
		TTORATstpSPDirectionType	Direction;

		///按字节表示各单个合约的开平方向
		TTORATstpSPCombOffsetFlagType	CombOffsetFlag;

		///按字节表示各单个合约的组合套保标志
		TTORATstpSPCombHedgeFlagType	CombHedgeFlag;

		///限价单价格
		TTORATstpSPPriceType	LimitPrice;

		///报单数量
		TTORATstpSPVolumeType	VolumeTotalOriginal;

		///IOC、GFS、GFD、GTD、GTC、GFA
		TTORATstpSPTimeConditionType	TimeCondition;

		///AV、MV、CV
		TTORATstpSPVolumeConditionType	VolumeCondition;

		///当成交量类型为MV时有效
		TTORATstpSPVolumeType	MinVolume;

		///强平原因
		TTORATstpSPForceCloseReasonType	ForceCloseReason;

		///请求编号
		TTORATstpSPRequestIDType	RequestID;

		///用户强评标志
		TTORATstpSPBoolType	UserForceClose;

		///投资者代码
		TTORATstpSPInvestorIDType	InvestorID;

		///一个交易所的编号
		TTORATstpSPExchangeIDType	ExchangeID;

		///目前该字段存放的是上证所和深圳的股东代码
		TTORATstpSPShareholderIDType	ShareholderID;

		///投资单元代码
		TTORATstpSPBusinessUnitIDType	BusinessUnitID;

		///资金账户
		TTORATstpSPAccountIDType	AccountID;

		///内网IP地址
		TTORATstpSPIPAddressType	InnerIPAddress;

		///Mac地址
		TTORATstpSPMacAddressType	MacAddress;

		///报单编号
		TTORATstpSPCondOrderIDType	CondOrderID;

		///终端信息
		TTORATstpSPTerminalInfoType	TerminalInfo;

		///长字符串附加信息
		TTORATstpSPBigsInfoType	BInfo;

		///短字符串附加信息
		TTORATstpSPShortsInfoType	SInfo;

		///整形附加信息
		TTORATstpSPIntInfoType	IInfo;

		///报单数量类型
		TTORATstpSPOrderVolumeTypeType	OrderVolumeType;

		///条件单触发条件
		TTORATstpSPContingentConditionType	ContingentCondition;

		///条件价
		TTORATstpSPPriceType	ConditionPrice;

		///价格浮动tick数,大于0向上浮动,小于0向下浮动,=0不浮动
		TTORATstpSPVolumeType	PriceTicks;

		///数量浮动倍数,必须>=0
		TTORATstpSPVolumeMultipleType	VolumeMultiple;

		///相关前置编号
		TTORATstpSPFrontIDType	RelativeFrontID;

		///相关会话编号
		TTORATstpSPSessionIDType	RelativeSessionID;

		///相关条件参数,可能为OrderRef、OrderSysID、Time和SecurityID
		TTORATstpSPRelativeCondParamType	RelativeParam;

		///附加触发条件
		TTORATstpSPContingentConditionType	AppendContingentCondition;

		///附加条件价
		TTORATstpSPPriceType	AppendConditionPrice;

		///附加相关前置编号
		TTORATstpSPFrontIDType	AppendRelativeFrontID;

		///附加相关会话编号
		TTORATstpSPSessionIDType	AppendRelativeSessionID;

		///附加相关条件参数,可能为OrderRef、OrderSysID、Time和SecurityID
		TTORATstpSPRelativeCondParamType	AppendRelativeParam;

		///前置编号
		TTORATstpSPFrontIDType	FrontID;

		///会话编号
		TTORATstpSPSessionIDType	SessionID;

		///经纪公司部门代码
		TTORATstpSPDepartmentIDType	DepartmentID;

		///条件单状态
		TTORATstpSPCondOrderStatusType	CondOrderStatus;

		///状态信息
		TTORATstpSPErrorMsgType	StatusMsg;

		///报单申报用户
		TTORATstpSPUserIDType	InsertUserID;

		///报单日期
		TTORATstpSPDateType	InsertDate;

		///委托时间
		TTORATstpSPTimeType	InsertTime;

		///申报时间(毫秒)
		TTORATstpSPMillisecType	InsertMillisec;

		///撤销时间
		TTORATstpSPTimeType	CancelTime;

		///撤销用户
		TTORATstpSPUserIDType	CancelUserID;

		///触发时间
		TTORATstpSPTimeType	ActiveTime;

		///委托方式
		TTORATstpSPOperwayType	Operway;

		///硬盘序列号
		TTORATstpSPHDSerialType	HDSerial;

		///外网IP地址
		TTORATstpSPIPAddressType	OuterIPAddress;

		///外网端口号
		TTORATstpSPPortType	OuterPort;

	};

	/// 条件单操作录入
	struct CTORATstpSPInputCondOrderActionField
	{
		 
		///一个交易所的编号
		TTORATstpSPExchangeIDType	ExchangeID;

		///条件单操作引用
		TTORATstpSPOrderRefType	CondOrderActionRef;

		///条件单引用
		TTORATstpSPOrderRefType	CondOrderRef;

		///前置编号
		TTORATstpSPFrontIDType	FrontID;

		///会话编号
		TTORATstpSPSessionIDType	SessionID;

		///报单编号
		TTORATstpSPCondOrderIDType	CondOrderID;

		///委托操作标志
		TTORATstpSPOrderActionFlagType	OrderActionFlag;

		///投资者代码
		TTORATstpSPInvestorIDType	InvestorID;

		///合约在系统中的编号
		TTORATstpSPSecurityIDType	SecurityID;

		///内网IP地址
		TTORATstpSPIPAddressType	InnerIPAddress;

		///Mac地址
		TTORATstpSPMacAddressType	MacAddress;

		///条件单撤单编号
		TTORATstpSPCondOrderIDType	CancelCondOrderID;

		///终端信息
		TTORATstpSPTerminalInfoType	TerminalInfo;

		///长字符串附加信息
		TTORATstpSPBigsInfoType	BInfo;

		///短字符串附加信息
		TTORATstpSPShortsInfoType	SInfo;

		///整形附加信息
		TTORATstpSPIntInfoType	IInfo;

		///委托方式
		TTORATstpSPOperwayType	Operway;

		///硬盘序列号
		TTORATstpSPHDSerialType	HDSerial;

		///外网IP地址
		TTORATstpSPIPAddressType	OuterIPAddress;

		///外网端口号
		TTORATstpSPPortType	OuterPort;

	};

	/// 组合行权输入
	struct CTORATstpSPInputCombExerciseField
	{
		 
		///投资者代码
		TTORATstpSPInvestorIDType	InvestorID;

		///认购合约代码
		TTORATstpSPSecurityIDType	CallSecurityID;

		///认沽合约代码
		TTORATstpSPSecurityIDType	PutSecurityID;

		///投资者说明的对行权的唯一引用
		TTORATstpSPOrderRefType	CombExerciseRef;

		///行权数量
		TTORATstpSPVolumeType	Volume;

		///投资单元代码
		TTORATstpSPBusinessUnitIDType	BusinessUnitID;

		///交易所代码
		TTORATstpSPExchangeIDType	ExchangeID;

		///股东代码
		TTORATstpSPShareholderIDType	ShareholderID;

		///资金账户
		TTORATstpSPAccountIDType	AccountID;

		///内网IP地址
		TTORATstpSPIPAddressType	InnerIPAddress;

		///Mac地址
		TTORATstpSPMacAddressType	MacAddress;

		///系统组合行权编号
		TTORATstpSPOrderSysIDType	CombExerciseSysID;

		///终端信息
		TTORATstpSPTerminalInfoType	TerminalInfo;

		///长字符串附加信息
		TTORATstpSPBigsInfoType	BInfo;

		///短字符串附加信息
		TTORATstpSPShortsInfoType	SInfo;

		///整形附加信息
		TTORATstpSPIntInfoType	IInfo;

		///委托方式
		TTORATstpSPOperwayType	Operway;

		///硬盘序列号
		TTORATstpSPHDSerialType	HDSerial;

		///外网IP地址
		TTORATstpSPIPAddressType	OuterIPAddress;

		///外网端口号
		TTORATstpSPPortType	OuterPort;

	};

	/// 组合行权回报
	struct CTORATstpSPCombExerciseField
	{
		 
		///交易日
		TTORATstpSPDateType	TradingDay;

		///交易所代码
		TTORATstpSPExchangeIDType	ExchangeID;

		///认购合约代码
		TTORATstpSPSecurityIDType	CallSecurityID;

		///认沽合约代码
		TTORATstpSPSecurityIDType	PutSecurityID;

		///前置编号
		TTORATstpSPFrontIDType	FrontID;

		///会话编号
		TTORATstpSPSessionIDType	SessionID;

		///合并行权引用
		TTORATstpSPOrderRefType	CombExerciseRef;

		///系统合并行权编号
		TTORATstpSPOrderSysIDType	CombExerciseSysID;

		///交易单元代码
		TTORATstpSPPbuIDType	PbuID;

		///本地合并行权编号
		TTORATstpSPOrderLocalIDType	CombExerciseLocalID;

		///投资者代码
		TTORATstpSPInvestorIDType	InvestorID;

		///投资单元代码
		TTORATstpSPBusinessUnitIDType	BusinessUnitID;

		///行权数量
		TTORATstpSPVolumeType	Volume;

		///交易所返回的撤单数量
		TTORATstpSPVolumeType	VolumeCanceled;

		///市场代码
		TTORATstpSPMarketIDType	MarketID;

		///目前该字段存放的是上证所和深圳的股东代码。
		TTORATstpSPShareholderIDType	ShareholderID;

		///a：普通，b：信用，c：衍生品
		TTORATstpSPShareholderIDTypeType	ShareholderIDType;

		///经纪公司部门代码
		TTORATstpSPDepartmentIDType	DepartmentID;

		///资金账户
		TTORATstpSPAccountIDType	AccountID;

		///币种
		TTORATstpSPCurrencyIDType	CurrencyID;

		///行权状态
		TTORATstpSPExerciseStatusType	ExerciseStatus;

		///行权操作状态
		TTORATstpSPOrderOperateStatusType	ExerciseOperateStatus;

		///状态信息
		TTORATstpSPStatusMsgType	StatusMsg;

		///系统错误代码
		TTORATstpSPErrorIDType	ErrorID;

		///交易所为营业部分配的代码
		TTORATstpSPBranchIDType	BranchID;

		///报单申报用户
		TTORATstpSPUserIDType	InsertUserID;

		///申报日期
		TTORATstpSPDateType	InsertDate;

		///申报时间
		TTORATstpSPTimeType	InsertTime;

		///申报时间(毫秒)
		TTORATstpSPMillisecType	InsertMillisec;

		///交易所接收时间
		TTORATstpSPTimeType	AcceptTime;

		///撤销时间
		TTORATstpSPTimeType	CancelTime;

		///撤销申报用户
		TTORATstpSPUserIDType	CancelUserID;

		///内网IP地址
		TTORATstpSPIPAddressType	InnerIPAddress;

		///Mac地址
		TTORATstpSPMacAddressType	MacAddress;

		///请求编号
		TTORATstpSPRequestIDType	RequestID;

		///终端信息
		TTORATstpSPTerminalInfoType	TerminalInfo;

		///记录序号(仅上证报盘使用)
		TTORATstpSPSequenceNoType	RecordNumber;

		///长字符串附加信息
		TTORATstpSPBigsInfoType	BInfo;

		///短字符串附加信息
		TTORATstpSPShortsInfoType	SInfo;

		///整形附加信息
		TTORATstpSPIntInfoType	IInfo;

		///委托方式
		TTORATstpSPOperwayType	Operway;

		///硬盘序列号
		TTORATstpSPHDSerialType	HDSerial;

		///移动设备手机号
		TTORATstpSPMobileType	Mobile;

		///外网IP地址
		TTORATstpSPIPAddressType	OuterIPAddress;

		///外网端口号
		TTORATstpSPPortType	OuterPort;

	};

	/// 组合行权操作输入
	struct CTORATstpSPInputCombExerciseActionField
	{
		 
		///投资者代码
		TTORATstpSPInvestorIDType	InvestorID;

		///组合行权操作引用
		TTORATstpSPOrderRefType	CombExerciseActionRef;

		///组合行权引用
		TTORATstpSPOrderRefType	CombExerciseRef;

		///前置编号
		TTORATstpSPFrontIDType	FrontID;

		///会话编号
		TTORATstpSPSessionIDType	SessionID;

		///交易所代码
		TTORATstpSPExchangeIDType	ExchangeID;

		///系统组合行权编号
		TTORATstpSPOrderSysIDType	CombExerciseSysID;

		///操作标志
		TTORATstpSPOrderActionFlagType	ExerciseActionFlag;

		///认购合约代码
		TTORATstpSPSecurityIDType	CallSecurityID;

		///认沽合约代码
		TTORATstpSPSecurityIDType	PutSecurityID;

		///内网IP地址
		TTORATstpSPIPAddressType	InnerIPAddress;

		///Mac地址
		TTORATstpSPMacAddressType	MacAddress;

		///本地组合行权撤单编号
		TTORATstpSPOrderLocalIDType	CancelCombExerciseLocalID;

		///终端信息
		TTORATstpSPTerminalInfoType	TerminalInfo;

		///长字符串附加信息
		TTORATstpSPBigsInfoType	BInfo;

		///短字符串附加信息
		TTORATstpSPShortsInfoType	SInfo;

		///整形附加信息
		TTORATstpSPIntInfoType	IInfo;

		///委托方式
		TTORATstpSPOperwayType	Operway;

		///硬盘序列号
		TTORATstpSPHDSerialType	HDSerial;

		///外网IP地址
		TTORATstpSPIPAddressType	OuterIPAddress;

		///外网端口号
		TTORATstpSPPortType	OuterPort;

	};

	/// 查询最大可锁定数量请求
	struct CTORATstpSPReqInquiryMaxLockVolumeField
	{
		 
		///投资者代码
		TTORATstpSPInvestorIDType	InvestorID;

		///交易所下的交易市场
		TTORATstpSPMarketIDType	MarketID;

		///交易账户代码
		TTORATstpSPShareholderIDType	ShareholderID;

		///交易所代码
		TTORATstpSPExchangeIDType	ExchangeID;

		///现货证券代码
		TTORATstpSPSecurityIDType	SecurityID;

	};

	/// 查询最大可锁定数量应答
	struct CTORATstpSPRspInquiryMaxLockVolumeField
	{
		 
		///投资者代码
		TTORATstpSPInvestorIDType	InvestorID;

		///交易所下的交易市场
		TTORATstpSPMarketIDType	MarketID;

		///交易账户代码
		TTORATstpSPShareholderIDType	ShareholderID;

		///交易所代码
		TTORATstpSPExchangeIDType	ExchangeID;

		///现货证券代码
		TTORATstpSPSecurityIDType	SecurityID;

		///可锁定数量
		TTORATstpSPVolumeType	Volume;

		///用户请求编号
		TTORATstpSPRequestIDType	RequestID;

	};

	/// 查询最大可备兑现货数量请求
	struct CTORATstpSPReqInquiryMaxCoverVolumeField
	{
		 
		///投资者代码
		TTORATstpSPInvestorIDType	InvestorID;

		///交易所下的交易市场
		TTORATstpSPMarketIDType	MarketID;

		///交易账户代码
		TTORATstpSPShareholderIDType	ShareholderID;

		///交易所代码
		TTORATstpSPExchangeIDType	ExchangeID;

		///现货证券代码
		TTORATstpSPSecurityIDType	SecurityID;

	};

	/// 查询最大可备兑现货数量应答
	struct CTORATstpSPRspInquiryMaxCoverVolumeField
	{
		 
		///投资者代码
		TTORATstpSPInvestorIDType	InvestorID;

		///交易所下的交易市场
		TTORATstpSPMarketIDType	MarketID;

		///交易账户代码
		TTORATstpSPShareholderIDType	ShareholderID;

		///交易所代码
		TTORATstpSPExchangeIDType	ExchangeID;

		///现货证券代码
		TTORATstpSPSecurityIDType	SecurityID;

		///可备兑现货数量
		TTORATstpSPVolumeType	Volume;

		///用户请求编号
		TTORATstpSPRequestIDType	RequestID;

	};

	/// 查询拆分组合合约后保证金差额变动请求
	struct CTORATstpSPReqInquirySplitCombMarginDifferenceField
	{
		 
		///投资者代码
		TTORATstpSPInvestorIDType	InvestorID;

		///投资单元代码
		TTORATstpSPBusinessUnitIDType	BusinessUnitID;

		///交易所代码
		TTORATstpSPExchangeIDType	ExchangeID;

		///组合合约代码
		TTORATstpSPSecurityIDType	CombSecurityID;

		///交易所组合编码
		TTORATstpSPExchangeCombIDType	ExchangeCombID;

		///目前该字段存放的是上证所和深圳的股东代码
		TTORATstpSPShareholderIDType	ShareholderID;

		///组合策略
		TTORATstpSPCombinationStrategyType	CombinationStrategy;

		///报单数量
		TTORATstpSPVolumeType	Volume;

	};

	/// 查询拆分组合合约后保证金差额变动请求响应
	struct CTORATstpSPRspInquirySplitCombMarginDifferenceField
	{
		 
		///投资者代码
		TTORATstpSPInvestorIDType	InvestorID;

		///投资单元代码
		TTORATstpSPBusinessUnitIDType	BusinessUnitID;

		///交易所代码
		TTORATstpSPExchangeIDType	ExchangeID;

		///组合合约代码
		TTORATstpSPSecurityIDType	CombSecurityID;

		///交易所组合编码
		TTORATstpSPExchangeCombIDType	ExchangeCombID;

		///目前该字段存放的是上证所和深圳的股东代码
		TTORATstpSPShareholderIDType	ShareholderID;

		///组合策略
		TTORATstpSPCombinationStrategyType	CombinationStrategy;

		///报单数量
		TTORATstpSPVolumeType	Volume;

		///用户请求编号
		TTORATstpSPRequestIDType	RequestID;

		///左腿合约占用保证金
		TTORATstpSPPriceType	LeftLegPosMargin;

		///左腿合约占用实时保证金
		TTORATstpSPPriceType	LeftLegPosLiveMargin;

		///右腿合约占用保证金额
		TTORATstpSPPriceType	RightLegPosMargin;

		///右腿合约占用实时保证金额
		TTORATstpSPPriceType	RightLegPosLiveMargin;

		///组合仓位占用的保证金
		TTORATstpSPPriceType	CombPosMargin;

		///组合仓位占用的实时保证金
		TTORATstpSPPriceType	CombPosLiveMargin;

		///保证金差额（组合合约拆分后与拆分前保证金的差额）
		TTORATstpSPPriceType	MarginDifference;

		///实时保证金差额（组合合约拆分后与拆分前保证金的差额）
		TTORATstpSPPriceType	LiveMarginDifference;

	};

	/// 资金转移
	struct CTORATstpSPInputTransferFundField
	{
		 
		///申请流水号
		TTORATstpSPIntSerialType	ApplySerial;

		///资金账户
		TTORATstpSPAccountIDType	AccountID;

		///币种
		TTORATstpSPCurrencyIDType	CurrencyID;

		///转移方向
		TTORATstpSPTransferDirectionType	TransferDirection;

		///转账金额
		TTORATstpSPMoneyType	Amount;

		///经纪公司部门代码
		TTORATstpSPDepartmentIDType	DepartmentID;

		///资金密码
		TTORATstpSPPasswordType	TradingAccountPassword;

		///银行代码
		TTORATstpSPBankIDType	BankID;

		///银行账户密码
		TTORATstpSPPasswordType	BankAccountPassword;

	};

	/// 资金转移回报
	struct CTORATstpSPTransferFundField
	{
		 
		///转账流水号(后台编号)
		TTORATstpSPIntSerialType	FundSerial;

		///申请流水号
		TTORATstpSPIntSerialType	ApplySerial;

		///前置编号
		TTORATstpSPFrontIDType	FrontID;

		///会话编号
		TTORATstpSPSessionIDType	SessionID;

		///资金账户代码
		TTORATstpSPAccountIDType	AccountID;

		///币种代码
		TTORATstpSPCurrencyIDType	CurrencyID;

		///转移方向
		TTORATstpSPTransferDirectionType	TransferDirection;

		///资金账户当日出入金金额
		TTORATstpSPMoneyType	Amount;

		///转移状态
		TTORATstpSPTransferStatusType	TransferStatus;

		///操作人员
		TTORATstpSPUserIDType	OperatorID;

		///操作日期
		TTORATstpSPDateType	OperateDate;

		///操作时间
		TTORATstpSPTimeType	OperateTime;

		///经纪公司部门代码
		TTORATstpSPDepartmentIDType	DepartmentID;

		///签约银行账户
		TTORATstpSPBankAccountIDType	BankAccountID;

		///银行代码
		TTORATstpSPBankIDType	BankID;

	};

	/// 仓位转移回报
	struct CTORATstpSPTransferPositionField
	{
		 
		///仓位转移流水号
		TTORATstpSPIntSerialType	PositionSerial;

		///申请流水号
		TTORATstpSPIntSerialType	ApplySerial;

		///前置编号
		TTORATstpSPFrontIDType	FrontID;

		///会话编号
		TTORATstpSPSessionIDType	SessionID;

		///投资者代码
		TTORATstpSPInvestorIDType	InvestorID;

		///投资单元代码
		TTORATstpSPBusinessUnitIDType	BusinessUnitID;

		///交易所代码
		TTORATstpSPExchangeIDType	ExchangeID;

		///目前该字段存放的是上证所和深圳的股东代码。
		TTORATstpSPShareholderIDType	ShareholderID;

		///交易所下的交易市场，如沪A、沪B市场
		TTORATstpSPMarketIDType	MarketID;

		///多、空
		TTORATstpSPPosiDirectionType	PosiDirection;

		///投机套保标志
		TTORATstpSPHedgeFlagType	HedgeFlag;

		///证券代码
		TTORATstpSPSecurityIDType	SecurityID;

		///交易日
		TTORATstpSPDateType	TradingDay;

		///转移方向
		TTORATstpSPTransferDirectionType	TransferDirection;

		///转移持仓类型
		TTORATstpSPTransferPositionTypeType	TransferPositionType;

		///昨日仓位转入转出数量。
		TTORATstpSPVolumeType	HistoryVolume;

		///今日仓位转入转出数量。
		TTORATstpSPVolumeType	TodayVolume;

		///转移状态：0：正常，1：已冲正
		TTORATstpSPTransferStatusType	TransferStatus;

		///操作人员
		TTORATstpSPUserIDType	OperatorID;

		///操作日期
		TTORATstpSPDateType	OperateDate;

		///操作时间
		TTORATstpSPTimeType	OperateTime;

	};

	/// 仓位转移
	struct CTORATstpSPInputTransferPositionField
	{
		 
		///申请流水号
		TTORATstpSPIntSerialType	ApplySerial;

		///投资者代码
		TTORATstpSPInvestorIDType	InvestorID;

		///投资单元代码
		TTORATstpSPBusinessUnitIDType	BusinessUnitID;

		///交易所代码
		TTORATstpSPExchangeIDType	ExchangeID;

		///交易所下的交易市场，如沪A、沪B市场
		TTORATstpSPMarketIDType	MarketID;

		///目前该字段存放的是上证所和深圳的股东代码。
		TTORATstpSPShareholderIDType	ShareholderID;

		///合约代码
		TTORATstpSPSecurityIDType	SecurityID;

		///转移方向
		TTORATstpSPTransferDirectionType	TransferDirection;

		///数量
		TTORATstpSPVolumeType	Volume;

		///转移持仓类型
		TTORATstpSPTransferPositionTypeType	TransferPositionType;

		///多、空
		TTORATstpSPPosiDirectionType	PosiDirection;

		///投机套保标志
		TTORATstpSPHedgeFlagType	HedgeFlag;

		///用户请求编号
		TTORATstpSPRequestIDType	RequestID;

	};

	/// 证券仓位转移请求
	struct CTORATstpSPInputTransferStockPositionField
	{
		 
		///申请流水号
		TTORATstpSPIntSerialType	ApplySerial;

		///投资者代码
		TTORATstpSPInvestorIDType	InvestorID;

		///投资单元代码
		TTORATstpSPBusinessUnitIDType	BusinessUnitID;

		///交易所代码
		TTORATstpSPExchangeIDType	ExchangeID;

		///交易所下的交易市场，如沪A、沪B市场
		TTORATstpSPMarketIDType	MarketID;

		///目前该字段存放的是上证所和深圳的股东代码。
		TTORATstpSPShareholderIDType	ShareholderID;

		///合约代码
		TTORATstpSPSecurityIDType	SecurityID;

		///个股期权标的现货转移原因
		TTORATstpSPSPStockTransferReasonType	SPStockTransferReason;

		///数量
		TTORATstpSPVolumeType	Volume;

		///转移持仓类型
		TTORATstpSPTransferPositionTypeType	TransferPositionType;

	};

	/// 证券仓位转移回报
	struct CTORATstpSPTransferStockPositionField
	{
		 
		///仓位转移流水号
		TTORATstpSPIntSerialType	PositionSerial;

		///申请流水号
		TTORATstpSPIntSerialType	ApplySerial;

		///前置编号
		TTORATstpSPFrontIDType	FrontID;

		///会话编号
		TTORATstpSPSessionIDType	SessionID;

		///投资者代码
		TTORATstpSPInvestorIDType	InvestorID;

		///投资单元代码
		TTORATstpSPBusinessUnitIDType	BusinessUnitID;

		///交易所代码
		TTORATstpSPExchangeIDType	ExchangeID;

		///目前该字段存放的是上证所和深圳的股东代码。
		TTORATstpSPShareholderIDType	ShareholderID;

		///交易所下的交易市场，如沪A、沪B市场
		TTORATstpSPMarketIDType	MarketID;

		///证券代码
		TTORATstpSPSecurityIDType	SecurityID;

		///交易日
		TTORATstpSPDateType	TradingDay;

		///个股期权标的现货转移原因
		TTORATstpSPSPStockTransferReasonType	SPStockTransferReason;

		///转移持仓类型
		TTORATstpSPTransferPositionTypeType	TransferPositionType;

		///昨日仓位转入转出数量
		TTORATstpSPVolumeType	HistoryVolume;

		///今日买卖仓位转入转出数量
		TTORATstpSPVolumeType	TodayBSVolume;

		///今日申赎仓位转入转出数量
		TTORATstpSPVolumeType	TodayPRVolume;

		///正在处理、失败等
		TTORATstpSPTransferStatusType	TransferStatus;

		///操作人员
		TTORATstpSPUserIDType	OperatorID;

		///操作日期
		TTORATstpSPDateType	OperateDate;

		///操作时间
		TTORATstpSPTimeType	OperateTime;

	};

	/// 查询集中交易系统资金请求
	struct CTORATstpSPReqInquiryJZFundField
	{
		 
		///资金账户
		TTORATstpSPAccountIDType	AccountID;

		///币种
		TTORATstpSPCurrencyIDType	CurrencyID;

		///经纪公司部门代码
		TTORATstpSPDepartmentIDType	DepartmentID;

	};

	/// 查询集中交易系统资金响应
	struct CTORATstpSPRspInquiryJZFundField
	{
		 
		///资金账户
		TTORATstpSPAccountIDType	AccountID;

		///币种
		TTORATstpSPCurrencyIDType	CurrencyID;

		///可用金额
		TTORATstpSPMoneyType	UsefulMoney;

		///可取额度
		TTORATstpSPMoneyType	FetchLimit;

		///用户请求编号
		TTORATstpSPRequestIDType	RequestID;

		///经纪公司部门代码
		TTORATstpSPDepartmentIDType	DepartmentID;

	};

	/// 查询银行账户余额请求
	struct CTORATstpSPReqInquiryBankAccountFundField
	{
		 
		///资金账户
		TTORATstpSPAccountIDType	AccountID;

		///币种
		TTORATstpSPCurrencyIDType	CurrencyID;

		///经纪公司部门代码
		TTORATstpSPDepartmentIDType	DepartmentID;

		///银行账户密码
		TTORATstpSPPasswordType	BankAccountPassword;

	};

	/// 查询银行账户余额响应
	struct CTORATstpSPRspInquiryBankAccountFundField
	{
		 
		///资金账户
		TTORATstpSPAccountIDType	AccountID;

		///币种
		TTORATstpSPCurrencyIDType	CurrencyID;

		///账户余额
		TTORATstpSPMoneyType	Balance;

		///用户请求编号
		TTORATstpSPRequestIDType	RequestID;

		///经纪公司部门代码
		TTORATstpSPDepartmentIDType	DepartmentID;

		///银行代码
		TTORATstpSPBankIDType	BankID;

		///签约银行账户
		TTORATstpSPBankAccountIDType	BankAccountID;

	};

	/// 查询现货系统仓位请求
	struct CTORATstpSPReqInquiryStockPositionField
	{
		 
		///投资者代码
		TTORATstpSPInvestorIDType	InvestorID;

		///投资单元代码
		TTORATstpSPBusinessUnitIDType	BusinessUnitID;

		///交易所下的交易市场
		TTORATstpSPMarketIDType	MarketID;

		///交易账户代码
		TTORATstpSPShareholderIDType	ShareholderID;

		///交易日期
		TTORATstpSPDateType	TradingDay;

		///交易所代码
		TTORATstpSPExchangeIDType	ExchangeID;

		///现货证券代码
		TTORATstpSPSecurityIDType	SecurityID;

	};

	/// 查询现货系统仓位响应
	struct CTORATstpSPRspInquiryStockPositionField
	{
		 
		///投资者代码
		TTORATstpSPInvestorIDType	InvestorID;

		///投资单元代码
		TTORATstpSPBusinessUnitIDType	BusinessUnitID;

		///交易所下的交易市场，如沪A、沪B市场
		TTORATstpSPMarketIDType	MarketID;

		///交易账户代码
		TTORATstpSPShareholderIDType	ShareholderID;

		///交易日期
		TTORATstpSPDateType	TradingDay;

		///交易所代码
		TTORATstpSPExchangeIDType	ExchangeID;

		///证券代码
		TTORATstpSPSecurityIDType	SecurityID;

		///昨日持仓（包含昨日持仓冻结数量）
		TTORATstpSPVolumeType	HistoryPos;

		///昨日持仓冻结
		TTORATstpSPVolumeType	HistoryPosFrozen;

		///今日买卖持仓（包含今日买卖持仓冻结数量）
		TTORATstpSPVolumeType	TodayBSPos;

		///今日买卖持仓冻结
		TTORATstpSPVolumeType	TodayBSPosFrozen;

		///今日申赎持仓（包含今日申赎持仓冻结数量）
		TTORATstpSPVolumeType	TodayPRPos;

		///今日申赎持仓冻结
		TTORATstpSPVolumeType	TodayPRPosFrozen;

		///今日拆分合并持仓（包含今日拆分合并持仓冻结数量）
		TTORATstpSPVolumeType	TodaySMPos;

		///今日拆分合并持仓冻结
		TTORATstpSPVolumeType	TodaySMPosFrozen;

		///昨日持仓成本价
		TTORATstpSPMoneyType	HistoryPosCost;

		///总持仓成本
		TTORATstpSPMoneyType	TotalPosCost;

		///融资仓位
		TTORATstpSPVolumeType	MarginBuyPos;

		///融券仓位（包含今日融券仓位）
		TTORATstpSPVolumeType	ShortSellPos;

		///今日融券仓位
		TTORATstpSPVolumeType	TodayShortSellPos;

		///上次余额(盘中不变)
		TTORATstpSPVolumeType	PrePosition;

		///股份可用
		TTORATstpSPVolumeType	AvailablePosition;

		///股份余额
		TTORATstpSPVolumeType	CurrentPosition;

		///用户请求编号
		TTORATstpSPRequestIDType	RequestID;

	};

	/// 订阅行情
	struct CTORATstpSPSpecificSecurityField
	{
		 
		///交易所代码
		TTORATstpSPExchangeIDType	ExchangeID;

		///合约代码
		TTORATstpSPSecurityIDType	SecurityID;

	};

	/// 深度行情通知
	struct CTORATstpSPMarketDataField
	{
		 
		///证券代码
		TTORATstpSPSecurityIDType	SecurityID;

		///交易所代码
		TTORATstpSPExchangeIDType	ExchangeID;

		///交易日
		TTORATstpSPDateType	TradingDay;

		///证券名称
		TTORATstpSPSecurityNameType	SecurityName;

		///上一日收盘价
		TTORATstpSPPriceType	PreClosePrice;

		///今日开盘价
		TTORATstpSPPriceType	OpenPrice;

		///涨停价格
		TTORATstpSPPriceType	UpperLimitPrice;

		///跌停价格
		TTORATstpSPPriceType	LowerLimitPrice;

		///该证券在当日的成交数量
		TTORATstpSPLongVolumeType	Volume;

		///该证券在当日的成交金额
		TTORATstpSPMoneyType	Turnover;

		///该证券在当日的成交笔数
		TTORATstpSPLongVolumeType	TradingCount;

		///当日该证券交易期间的最新成交价格
		TTORATstpSPPriceType	LastPrice;

		///收盘价格
		TTORATstpSPPriceType	ClosePrice;

		///一定时间内该证券成交价中的最高成交价格
		TTORATstpSPPriceType	HighestPrice;

		///一定时间内该证券成交价中的最低成交价格
		TTORATstpSPPriceType	LowestPrice;

		///指该证券当前的市盈率
		TTORATstpSPRatioType	PERatio1;

		///指该证券当前的市盈率
		TTORATstpSPRatioType	PERatio2;

		///最新价-前收盘价格
		TTORATstpSPPriceType	PriceUpDown1;

		///最新价-上笔成交价格
		TTORATstpSPPriceType	PriceUpDown2;

		///持仓量
		TTORATstpSPLargeVolumeType	OpenInterest;

		///该证券当前最优申买价格
		TTORATstpSPPriceType	BidPrice1;

		///该证券当前最优申卖价格
		TTORATstpSPPriceType	AskPrice1;

		///该证券当前最优价位申请买入的数量
		TTORATstpSPLongVolumeType	BidVolume1;

		///该证券当前最优价位申请卖出的数量
		TTORATstpSPLongVolumeType	AskVolume1;

		///该证券当前第二优申买价格
		TTORATstpSPPriceType	BidPrice2;

		///该证券当前第二优价位申请买入的数量
		TTORATstpSPLongVolumeType	BidVolume2;

		///该证券当前第二优申卖价格
		TTORATstpSPPriceType	AskPrice2;

		///该证券当前第二优价位申请卖出的数量
		TTORATstpSPLongVolumeType	AskVolume2;

		///该证券当前第三优申买价格
		TTORATstpSPPriceType	BidPrice3;

		///该证券当前第三优价位申请买入的数量
		TTORATstpSPLongVolumeType	BidVolume3;

		///该证券当前第三优申卖价格
		TTORATstpSPPriceType	AskPrice3;

		///该证券当前第三优价位申请卖出的数量
		TTORATstpSPLongVolumeType	AskVolume3;

		///该证券当前第四优申买价格
		TTORATstpSPPriceType	BidPrice4;

		///该证券当前第四优价位申请买入的数量
		TTORATstpSPLongVolumeType	BidVolume4;

		///该证券当前第四优申卖价格
		TTORATstpSPPriceType	AskPrice4;

		///该证券当前第四优价位申请卖出的数量
		TTORATstpSPLongVolumeType	AskVolume4;

		///该证券当前第五优申买价格
		TTORATstpSPPriceType	BidPrice5;

		///该证券当前第五优价位申请买入的数量
		TTORATstpSPLongVolumeType	BidVolume5;

		///该证券当前第五优申卖价格
		TTORATstpSPPriceType	AskPrice5;

		///该证券当前第五优价位申请卖出的数量
		TTORATstpSPLongVolumeType	AskVolume5;

		///最后修改时间
		TTORATstpSPTimeType	UpdateTime;

		///最后修改毫秒
		TTORATstpSPMillisecType	UpdateMillisec;

		///行情产品实时状态
		TTORATstpSPMDSecurityStatType	MDSecurityStat;

		///合约结算价
		TTORATstpSPPriceType	SettlementPrice;

	};

	/// 市场状态
	struct CTORATstpSPMarketStatusField
	{
		 
		///交易所下的交易市场，如沪A、沪B市场
		TTORATstpSPMarketIDType	MarketID;

		///市场状态
		TTORATstpSPMarketStatusType	MarketStatus;

	};

	/// 交易通知
	struct CTORATstpSPTradingNoticeField
	{
		 
		///通知流水号
		TTORATstpSPSerialType	NoticeSerial;

		///通知日期
		TTORATstpSPDateType	InsertDate;

		///通知时间
		TTORATstpSPTimeType	InsertTime;

		///投资者代码
		TTORATstpSPInvestorIDType	InvestorID;

		///投资单元代码
		TTORATstpSPBusinessUnitIDType	BusinessUnitID;

		///通知消息内容
		TTORATstpSPMessageType	Content;

		///操作员
		TTORATstpSPUserIDType	OperatorID;

	};

	/// 查询交易所
	struct CTORATstpSPQryExchangeField
	{
		 
		///交易所代码
		TTORATstpSPExchangeIDType	ExchangeID;

	};

	/// 交易所
	struct CTORATstpSPExchangeField
	{
		 
		///
		TTORATstpSPExchangeIDType	ExchangeID;

		///
		TTORATstpSPNameType	ExchangeName;

		///
		TTORATstpSPDateType	TradingDay;

		///
		TTORATstpSPDataSyncStatusType	DataSyncStatus;

	};

	/// 查询实时行情
	struct CTORATstpSPQryMarketDataField
	{
		 
		///证券代码
		TTORATstpSPSecurityIDType	SecurityID;

		///交易所代码
		TTORATstpSPExchangeIDType	ExchangeID;

	};

	/// 查询合约信息
	struct CTORATstpSPQrySecurityField
	{
		 
		///合约代码
		TTORATstpSPSecurityIDType	SecurityID;

		///交易所代码
		TTORATstpSPExchangeIDType	ExchangeID;

	};

	/// 合约信息
	struct CTORATstpSPSecurityField
	{
		 
		///交易所代码
		TTORATstpSPExchangeIDType	ExchangeID;

		///合约代码
		TTORATstpSPSecurityIDType	SecurityID;

		///交易所合约代码
		TTORATstpSPExchSecurityIDType	ExchSecurityID;

		///合约名称
		TTORATstpSPSecurityNameType	SecurityName;

		///基础证券代码
		TTORATstpSPSecurityIDType	UnderlyingSecurityID;

		///基础证券名称
		TTORATstpSPSecurityNameType	UnderlyingSecurityName;

		///合约基础商品乘数
		TTORATstpSPVolumeMultipleType	UnderlyingMultiple;

		///执行方式
		TTORATstpSPStrikeModeType	StrikeMode;

		///期权类型
		TTORATstpSPOptionsTypeType	OptionsType;

		///市场代码
		TTORATstpSPMarketIDType	MarketID;

		///产品代码
		TTORATstpSPProductIDType	ProductID;

		///证券类别代码
		TTORATstpSPSecurityTypeType	SecurityType;

		///申报单位
		TTORATstpSPOrderUnitType	OrderUnit;

		///买入交易单位
		TTORATstpSPTradingUnitType	BuyTradingUnit;

		///卖出交易单位
		TTORATstpSPTradingUnitType	SellTradingUnit;

		///市价单买最大下单量
		TTORATstpSPVolumeType	MaxMarketOrderBuyVolume;

		///市价单买最小下单量
		TTORATstpSPVolumeType	MinMarketOrderBuyVolume;

		///限价单买最大下单量
		TTORATstpSPVolumeType	MaxLimitOrderBuyVolume;

		///限价单买最小下单量
		TTORATstpSPVolumeType	MinLimitOrderBuyVolume;

		///市价单卖最大下单量
		TTORATstpSPVolumeType	MaxMarketOrderSellVolume;

		///市价单卖最小下单量
		TTORATstpSPVolumeType	MinMarketOrderSellVolume;

		///限价单卖最大下单量
		TTORATstpSPVolumeType	MaxLimitOrderSellVolume;

		///限价单卖最小下单量
		TTORATstpSPVolumeType	MinLimitOrderSellVolume;

		///数量乘数
		TTORATstpSPVolumeMultipleType	VolumeMultiple;

		///最小变动价位
		TTORATstpSPPriceTickType	PriceTick;

		///持仓类型
		TTORATstpSPPositionTypeType	PositionType;

		///证券状态
		TTORATstpSPSecurityStatusType	SecurityStatus;

		///执行价
		TTORATstpSPPriceType	StrikePrice;

		///首交易日
		TTORATstpSPDateType	FirstDate;

		///最后交易日
		TTORATstpSPDateType	LastDate;

		///行权日
		TTORATstpSPDateType	StrikeDate;

		///到期日
		TTORATstpSPDateType	ExpireDate;

		///交割日
		TTORATstpSPDateType	DelivDate;

		///是否有涨跌幅限制
		TTORATstpSPBoolType	IsUpDownLimit;

		///期权单位保证金
		TTORATstpSPPriceType	MarginUnit;

		///合约前结算价
		TTORATstpSPPriceType	PreSettlementPrice;

		///合约前收盘价
		TTORATstpSPPriceType	PreClosePrice;

		///标的合约前收盘价
		TTORATstpSPPriceType	UnderlyingPreClosePrice;

		///合约前持仓量
		TTORATstpSPVolumeType	PreOpenInterest;

		///报价买最大下单量
		TTORATstpSPVolumeType	MaxQuoteOrderBuyVolume;

		///报价买最小下单量
		TTORATstpSPVolumeType	MinQuoteOrderBuyVolume;

		///报价卖最大下单量
		TTORATstpSPVolumeType	MaxQuoteOrderSellVolume;

		///报价卖最小下单量
		TTORATstpSPVolumeType	MinQuoteOrderSellVolume;

		///涨停价格
		TTORATstpSPPriceType	UpperLimitPrice;

		///跌停价格
		TTORATstpSPPriceType	LowerLimitPrice;

	};

	/// 查询经纪公司用户与投资者关系
	struct CTORATstpSPQryBUProxyField
	{
		 
		///投资者代码
		TTORATstpSPInvestorIDType	InvestorID;

		///交易用户代码
		TTORATstpSPUserIDType	UserID;

		///投资单元代码
		TTORATstpSPBusinessUnitIDType	BusinessUnitID;

	};

	/// 经纪公司用户与投资者关系
	struct CTORATstpSPBUProxyField
	{
		 
		///投资者代码
		TTORATstpSPInvestorIDType	InvestorID;

		///用户代码
		TTORATstpSPUserIDType	UserID;

		///投资单元代码
		TTORATstpSPBusinessUnitIDType	BusinessUnitID;

		///经纪公司部门代码
		TTORATstpSPDepartmentIDType	DepartmentID;

	};

	/// 查询User
	struct CTORATstpSPQryUserField
	{
		 
		///用户代码
		TTORATstpSPUserIDType	UserID;

		///用户类型
		TTORATstpSPUserTypeType	UserType;

	};

	/// User
	struct CTORATstpSPUserField
	{
		 
		///用户代码
		TTORATstpSPUserIDType	UserID;

		///用户名称
		TTORATstpSPUserNameType	UserName;

		///用户类型
		TTORATstpSPUserTypeType	UserType;

		///经纪公司部门代码
		TTORATstpSPDepartmentIDType	DepartmentID;

		///登录限制
		TTORATstpSPLoginLimitType	LoginLimit;

		///密码连续输入错误限制
		TTORATstpSPLoginLimitType	PasswordFailLimit;

		///状态
		TTORATstpSPActiveStatusType	Status;

		///联系人
		TTORATstpSPContacterType	Contacter;

		///传真
		TTORATstpSPFaxType	Fax;

		///联系电话
		TTORATstpSPTelephoneType	Telephone;

		///电子邮件
		TTORATstpSPEmailType	Email;

		///通讯地址
		TTORATstpSPAddressType	Address;

		///邮政编码
		TTORATstpSPZipCodeType	ZipCode;

		///开户日期
		TTORATstpSPDateType	OpenDate;

		///销户日期
		TTORATstpSPDateType	CloseDate;

		///通讯流量
		TTORATstpSPCommFluxType	OrderInsertCommFlux;

		///撤单流控
		TTORATstpSPCommFluxType	OrderActionCommFlux;

		///上证通讯流量
		TTORATstpSPCommFluxType	SSEOrderInsertCommFlux;

		///上证撤单流控
		TTORATstpSPCommFluxType	SSEOrderActionCommFlux;

		///深证通讯流量
		TTORATstpSPCommFluxType	SZSEOrderInsertCommFlux;

		///深证撤单流控
		TTORATstpSPCommFluxType	SZSEOrderActionCommFlux;

	};

	/// 查询投资者
	struct CTORATstpSPQryInvestorField
	{
		 
		///投资者代码
		TTORATstpSPInvestorIDType	InvestorID;

	};

	/// 投资者
	struct CTORATstpSPInvestorField
	{
		 
		///投资者代码
		TTORATstpSPInvestorIDType	InvestorID;

		///经纪公司部门代码
		TTORATstpSPDepartmentIDType	DepartmentID;

		///投资者类型
		TTORATstpSPInvestorTypeType	InvestorType;

		///投资者名称
		TTORATstpSPInvestorNameType	InvestorName;

		///证件类型
		TTORATstpSPIdCardTypeType	IdCardType;

		///证件号码
		TTORATstpSPIdCardNoType	IdCardNo;

		///合同编号
		TTORATstpSPContractNoType	ContractNo;

		///开户日期
		TTORATstpSPDateType	OpenDate;

		///销户日期
		TTORATstpSPDateType	CloseDate;

		///状态
		TTORATstpSPActiveStatusType	TradeStatus;

		///预留字段1
		TTORATstpSPBranchIDType	Reserve1;

		///投资者分级类别
		TTORATstpSPInvestorLevelType	InvestorLevel;

		///手机
		TTORATstpSPMobileType	Mobile;

		///联系电话
		TTORATstpSPTelephoneType	Telephone;

		///电子邮件
		TTORATstpSPEmailType	Email;

		///传真
		TTORATstpSPFaxType	Fax;

		///通讯地址
		TTORATstpSPAddressType	Address;

		///邮政编码
		TTORATstpSPZipCodeType	ZipCode;

		///预留字段2
		TTORATstpSPRemarkType	Reserve2;

		///委托方式
		TTORATstpSPOperwaysType	Operways;

		///登录状态
		TTORATstpSPActiveStatusType	ActiveStatus;

		///登录限制
		TTORATstpSPLoginLimitType	LoginLimit;

		///投资者保证金提取比例
		TTORATstpSPRatioType	MarginFetchRatio;

	};

	/// 查询股东账户
	struct CTORATstpSPQryShareholderAccountField
	{
		 
		///投资者代码
		TTORATstpSPInvestorIDType	InvestorID;

		///交易所代码
		TTORATstpSPExchangeIDType	ExchangeID;

		///交易所下的交易市场，如沪A、沪B市场
		TTORATstpSPMarketIDType	MarketID;

		///目前该字段存放的是上证所和深圳的股东代码。
		TTORATstpSPShareholderIDType	ShareholderID;

		///普通，信用，衍生品等
		TTORATstpSPShareholderIDTypeType	ShareholderIDType;

	};

	/// 股东账户
	struct CTORATstpSPShareholderAccountField
	{
		 
		///投资者代码
		TTORATstpSPInvestorIDType	InvestorID;

		///交易所代码
		TTORATstpSPExchangeIDType	ExchangeID;

		///客户代码
		TTORATstpSPShareholderIDType	ShareholderID;

		///交易编码类型
		TTORATstpSPShareholderIDTypeType	ShareholderIDType;

		///市场代码
		TTORATstpSPMarketIDType	MarketID;

	};

	/// 查询资金账户
	struct CTORATstpSPQryTradingAccountField
	{
		 
		///投资者代码
		TTORATstpSPInvestorIDType	InvestorID;

		///币种
		TTORATstpSPCurrencyIDType	CurrencyID;

		///资金账户
		TTORATstpSPAccountIDType	AccountID;

		///普通、信用、衍生品等
		TTORATstpSPAccountTypeType	AccountType;

		///经纪公司部门代码
		TTORATstpSPDepartmentIDType	DepartmentID;

	};

	/// 资金账户
	struct CTORATstpSPTradingAccountField
	{
		 
		///部门代码
		TTORATstpSPDepartmentIDType	DepartmentID;

		///资金账户代码
		TTORATstpSPAccountIDType	AccountID;

		///币种代码
		TTORATstpSPCurrencyIDType	CurrencyID;

		///资金账户类型
		TTORATstpSPAccountTypeType	AccountType;

		///上日结存
		TTORATstpSPMoneyType	PreDeposit;

		///昨行权待交收冻结资金
		TTORATstpSPMoneyType	PreFrozenCash;

		///可用资金
		TTORATstpSPMoneyType	UsefulMoney;

		///可取资金
		TTORATstpSPMoneyType	FetchLimit;

		///入金金额
		TTORATstpSPMoneyType	Deposit;

		///出金金额
		TTORATstpSPMoneyType	Withdraw;

		///冻结的保证金
		TTORATstpSPMoneyType	FrozenMargin;

		///冻结的资金
		TTORATstpSPMoneyType	FrozenCash;

		///冻结的手续费
		TTORATstpSPMoneyType	FrozenCommission;

		///当前保证金总额
		TTORATstpSPMoneyType	CurrMargin;

		///手续费
		TTORATstpSPMoneyType	Commission;

		///权利金收入
		TTORATstpSPMoneyType	RoyaltyIn;

		///权利金支出
		TTORATstpSPMoneyType	RoyaltyOut;

		///资金账户所属投资者代码
		TTORATstpSPInvestorIDType	AccountOwner;

		///签约银行账户
		TTORATstpSPBankAccountIDType	BankAccountID;

		///银行代码
		TTORATstpSPBankIDType	BankID;

		///当日行权待交收冻结资金
		TTORATstpSPMoneyType	ExcerciseFrozen;

		///公司实时风险度
		TTORATstpSPRatioType	RiskLivePercent;

		///实时风险级别
		TTORATstpSPRiskLevelType	RiskLiveLevel;

		///实时可用资金
		TTORATstpSPMoneyType	LiveUsefulMoney;

	};

	/// 查询报单
	struct CTORATstpSPQryOrderField
	{
		 
		///投资者代码
		TTORATstpSPInvestorIDType	InvestorID;

		///合约在系统中的编号
		TTORATstpSPSecurityIDType	SecurityID;

		///交易所代码
		TTORATstpSPExchangeIDType	ExchangeID;

		///交易所下的交易市场，如沪A、沪B市场
		TTORATstpSPMarketIDType	MarketID;

		///客户在系统中的编号，编号唯一且遵循交易所制定的编码规则
		TTORATstpSPShareholderIDType	ShareholderID;

		///报单编号
		TTORATstpSPOrderSysIDType	OrderSysID;

		///Time
		TTORATstpSPTimeType	InsertTimeStart;

		///Time
		TTORATstpSPTimeType	InsertTimeEnd;

		///投资单元代码
		TTORATstpSPBusinessUnitIDType	BusinessUnitID;

		///长字符串附加信息
		TTORATstpSPBigsInfoType	BInfo;

		///短字符串附加信息
		TTORATstpSPShortsInfoType	SInfo;

		///整形附加信息
		TTORATstpSPIntInfoType	IInfo;

		///交易所组合编码(单边平仓必填)
		TTORATstpSPExchangeCombIDType	ExchangeCombID;

	};

	/// 查询成交
	struct CTORATstpSPQryTradeField
	{
		 
		///投资者代码
		TTORATstpSPInvestorIDType	InvestorID;

		///合约在系统中的编号
		TTORATstpSPSecurityIDType	SecurityID;

		///交易所代码
		TTORATstpSPExchangeIDType	ExchangeID;

		///交易所下的交易市场，如沪A、沪B市场
		TTORATstpSPMarketIDType	MarketID;

		///客户在系统中的编号，编号唯一且遵循交易所制定的编码规则
		TTORATstpSPShareholderIDType	ShareholderID;

		///成交编号
		TTORATstpSPTradeIDType	TradeID;

		///Time
		TTORATstpSPTimeType	TradeTimeStart;

		///Time
		TTORATstpSPTimeType	TradeTimeEnd;

		///投资单元代码
		TTORATstpSPBusinessUnitIDType	BusinessUnitID;

	};

	/// 查询投资者持仓
	struct CTORATstpSPQryPositionField
	{
		 
		///投资者代码
		TTORATstpSPInvestorIDType	InvestorID;

		///证券代码
		TTORATstpSPSecurityIDType	SecurityID;

		///交易所代码
		TTORATstpSPExchangeIDType	ExchangeID;

		///交易所下的交易市场，如沪A、沪B市场
		TTORATstpSPMarketIDType	MarketID;

		///交易账户代码
		TTORATstpSPShareholderIDType	ShareholderID;

		///投资单元代码
		TTORATstpSPBusinessUnitIDType	BusinessUnitID;

		///多、空
		TTORATstpSPPosiDirectionType	PosiDirection;

		///投机套保标志
		TTORATstpSPHedgeFlagType	HedgeFlag;

	};

	/// 投资者持仓
	struct CTORATstpSPPositionField
	{
		 
		///投资者代码
		TTORATstpSPInvestorIDType	InvestorID;

		///投资单元代码
		TTORATstpSPBusinessUnitIDType	BusinessUnitID;

		///市场代码
		TTORATstpSPMarketIDType	MarketID;

		///客户代码
		TTORATstpSPShareholderIDType	ShareholderID;

		///交易日
		TTORATstpSPDateType	TradingDay;

		///交易所代码
		TTORATstpSPExchangeIDType	ExchangeID;

		///合约代码
		TTORATstpSPSecurityIDType	SecurityID;

		///持仓方向
		TTORATstpSPPosiDirectionType	PosiDirection;

		///持仓方向
		TTORATstpSPHedgeFlagType	HedgeFlag;

		///昨日持仓
		TTORATstpSPVolumeType	HistoryPos;

		///昨日持仓冻结
		TTORATstpSPVolumeType	HistoryPosFrozen;

		///今日买卖持仓
		TTORATstpSPVolumeType	TodayPos;

		///今日买卖持仓冻结
		TTORATstpSPVolumeType	TodayPosFrozen;

		///持仓成本
		TTORATstpSPMoneyType	TotalPosCost;

		///多头冻结（买入开仓+买入平仓）的持仓数量
		TTORATstpSPVolumeType	LongFrozen;

		///空头冻结（卖出开仓+卖出平仓）的持仓数量
		TTORATstpSPVolumeType	ShortFrozen;

		///多头报单冻结的金额（不包含手续费、保证金）
		TTORATstpSPMoneyType	LongFrozenAmount;

		///空头报单冻结的金额（不包含手续费、保证金
		TTORATstpSPMoneyType	ShortFrozenAmount;

		///开仓量
		TTORATstpSPVolumeType	OpenVolume;

		///平仓量
		TTORATstpSPVolumeType	CloseVolume;

		///开仓金额
		TTORATstpSPMoneyType	OpenAmount;

		///平仓金额
		TTORATstpSPMoneyType	CloseAmount;

		///占用的保证金
		TTORATstpSPMoneyType	Margin;

		///冻结的保证金
		TTORATstpSPMoneyType	FrozenMargin;

		///冻结的资金
		TTORATstpSPMoneyType	FrozenCash;

		///冻结的手续费
		TTORATstpSPMoneyType	FrozenCommission;

		///资金差额
		TTORATstpSPMoneyType	CashIn;

		///手续费
		TTORATstpSPMoneyType	Commission;

		///执行冻结
		TTORATstpSPVolumeType	StrikeFrozen;

		///执行冻结金额
		TTORATstpSPMoneyType	StrikeFrozenAmount;

		///上次余额(盘中不变)
		TTORATstpSPVolumeType	PrePosition;

		///最新价
		TTORATstpSPPriceType	LastPrice;

		///昨日持仓组合仓位
		TTORATstpSPVolumeType	HistoryCombPos;

		///今日持仓组合仓位
		TTORATstpSPVolumeType	TodayCombPos;

		///昨日组合持仓拆分冻结
		TTORATstpSPVolumeType	HistoryCombPosSplitFrozen;

		///今日组合持仓拆分冻结
		TTORATstpSPVolumeType	TodayCombPosSplitFrozen;

		///昨日持仓组合冻结
		TTORATstpSPVolumeType	HistoryPosCombFrozen;

		///今日持仓组合冻结
		TTORATstpSPVolumeType	TodayPosCombFrozen;

		///买入成本
		TTORATstpSPMoneyType	OpenPosCost;

		///昨日平仓盈亏
		TTORATstpSPMoneyType	PreCloseProfit;

		///当日平仓盈亏
		TTORATstpSPMoneyType	TodayCloseProfit;

		///合约单位
		TTORATstpSPVolumeMultipleType	UnderlyingMultiple;

		///占用买入额度
		TTORATstpSPMoneyType	BuyQuotaUsed;

	};

	/// 查询基础交易费率
	struct CTORATstpSPQryTradingFeeField
	{
		 
		///交易所代码
		TTORATstpSPExchangeIDType	ExchangeID;

	};

	/// 基础交易费率
	struct CTORATstpSPTradingFeeField
	{
		 
		///交易所代码
		TTORATstpSPExchangeIDType	ExchangeID;

		///产品代码
		TTORATstpSPProductIDType	ProductID;

		///证券类别代码
		TTORATstpSPSecurityTypeType	SecurityType;

		///合约代码
		TTORATstpSPSecurityIDType	SecurityID;

		///业务类别
		TTORATstpSPBusinessClassType	BusinessClass;

		///系统标识
		TTORATstpSPSystemFlagType	SystemFlag;

		///印花税按金额收取比例
		TTORATstpSPRatioType	StampTaxRatioByAmt;

		///印花税按面值收取比例
		TTORATstpSPRatioType	StampTaxRatioByPar;

		///印花税按数量收取金额
		TTORATstpSPMoneyType	StampTaxFeeByVolume;

		///印花税按笔收取金额
		TTORATstpSPMoneyType	StampTaxFeePerOrder;

		///印花税最低收取金额
		TTORATstpSPMoneyType	StampTaxFeeMin;

		///印花税最高收取金额
		TTORATstpSPMoneyType	StampTaxFeeMax;

		///过户费按金额收取比例
		TTORATstpSPRatioType	TransferRatioByAmt;

		///过户费按面值收取比例
		TTORATstpSPRatioType	TransferRatioByPar;

		///过户费按笔收取金额
		TTORATstpSPMoneyType	TransferFeePerOrder;

		///过户费按数量收取金额
		TTORATstpSPMoneyType	TransferFeeByVolume;

		///过户费最低收取金额
		TTORATstpSPMoneyType	TransferFeeMin;

		///过户费最高收取金额
		TTORATstpSPMoneyType	TransferFeeMax;

		///经手费按金额收取比例
		TTORATstpSPRatioType	HandlingRatioByAmt;

		///经手费按面值收取比例
		TTORATstpSPRatioType	HandlingRatioByPar;

		///经手费按笔收取金额
		TTORATstpSPMoneyType	HandlingFeePerOrder;

		///经手费按数量收取金额
		TTORATstpSPMoneyType	HandlingFeeByVolume;

		///经手费最低收取金额
		TTORATstpSPMoneyType	HandlingFeeMin;

		///经手费最高收取金额
		TTORATstpSPMoneyType	HandlingFeeMax;

		///证管费按金额收取比例
		TTORATstpSPRatioType	RegulateRatioByAmt;

		///证管费按面值收取比例
		TTORATstpSPRatioType	RegulateRatioByPar;

		///证管费按数量收取金额
		TTORATstpSPMoneyType	RegulateFeeByVolume;

		///证管费按笔收取金额
		TTORATstpSPMoneyType	RegulateFeePerOrder;

		///证管费最低收取金额
		TTORATstpSPMoneyType	RegulateFeeMin;

		///证管费最高收取金额
		TTORATstpSPMoneyType	RegulateFeeMax;

		///结算费按金额收取比例
		TTORATstpSPRatioType	SettlementRatioByAmt;

		///结算费按面值收取比例
		TTORATstpSPRatioType	SettlementRatioByPar;

		///结算费按笔收取金额
		TTORATstpSPMoneyType	SettlementFeePerOrder;

		///结算费按数量收取金额
		TTORATstpSPMoneyType	SettlementFeeByVolume;

		///结算费最低收取金额
		TTORATstpSPMoneyType	SettlementFeeMin;

		///结算费最高收取金额
		TTORATstpSPMoneyType	SettlementFeeMax;

	};

	/// 查询佣金费率
	struct CTORATstpSPQryInvestorTradingFeeField
	{
		 
		///投资者代码
		TTORATstpSPInvestorIDType	InvestorID;

		///交易所代码
		TTORATstpSPExchangeIDType	ExchangeID;

		///经纪公司部门代码
		TTORATstpSPDepartmentIDType	DepartmentID;

	};

	/// 佣金费率
	struct CTORATstpSPInvestorTradingFeeField
	{
		 
		///经纪公司部门代码
		TTORATstpSPDepartmentIDType	DepartmentID;

		///投资者代码
		TTORATstpSPInvestorIDType	InvestorID;

		///交易所代码
		TTORATstpSPExchangeIDType	ExchangeID;

		///产品代码
		TTORATstpSPProductIDType	ProductID;

		///证券类别代码
		TTORATstpSPSecurityTypeType	SecurityType;

		///合约代码
		TTORATstpSPSecurityIDType	SecurityID;

		///业务类别
		TTORATstpSPBusinessClassType	BusinessClass;

		///佣金类型
		TTORATstpSPBrokerageTypeType	BrokerageType;

		///佣金按金额收取比例
		TTORATstpSPRatioType	RatioByAmt;

		///佣金按面值收取比例
		TTORATstpSPRatioType	RatioByPar;

		///佣金按笔收取金额
		TTORATstpSPMoneyType	FeePerOrder;

		///佣金最低收取金额
		TTORATstpSPMoneyType	FeeMin;

		///佣金最高收取金额
		TTORATstpSPMoneyType	FeeMax;

		///佣金按数量收取金额
		TTORATstpSPMoneyType	FeeByVolume;

	};

	/// 查询保证金费率
	struct CTORATstpSPQryInvestorMarginFeeField
	{
		 
		///投资者代码
		TTORATstpSPInvestorIDType	InvestorID;

		///交易所代码
		TTORATstpSPExchangeIDType	ExchangeID;

		///经纪公司部门代码
		TTORATstpSPDepartmentIDType	DepartmentID;

		///产品代码
		TTORATstpSPProductIDType	ProductID;

		///证券类别代码
		TTORATstpSPSecurityTypeType	SecurityType;

		///业务类别
		TTORATstpSPBusinessClassType	BusinessClass;

		///合约代码
		TTORATstpSPSecurityIDType	SecurityID;

	};

	/// 保证金费率
	struct CTORATstpSPInvestorMarginFeeField
	{
		 
		///经纪公司部门代码
		TTORATstpSPDepartmentIDType	DepartmentID;

		///投资者代码
		TTORATstpSPInvestorIDType	InvestorID;

		///交易所代码
		TTORATstpSPExchangeIDType	ExchangeID;

		///产品代码
		TTORATstpSPProductIDType	ProductID;

		///证券类别代码
		TTORATstpSPSecurityTypeType	SecurityType;

		///合约代码
		TTORATstpSPSecurityIDType	SecurityID;

		///业务类别
		TTORATstpSPBusinessClassType	BusinessClass;

		///佣金按数量收取金额
		TTORATstpSPMoneyType	FeeByVolume;

		///上浮比率
		TTORATstpSPRatioType	UpperRatio;

	};

	/// 查询报单明细资金
	struct CTORATstpSPQryOrderFundDetailField
	{
		 
		///投资者代码
		TTORATstpSPInvestorIDType	InvestorID;

		///证券代码
		TTORATstpSPSecurityIDType	SecurityID;

		///交易所代码
		TTORATstpSPExchangeIDType	ExchangeID;

		///系统报单编号
		TTORATstpSPOrderSysIDType	OrderSysID;

		///投资单元代码
		TTORATstpSPBusinessUnitIDType	BusinessUnitID;

	};

	/// 报单明细资金
	struct CTORATstpSPOrderFundDetailField
	{
		 
		///交易日期
		TTORATstpSPDateType	TradingDay;

		///交易所代码
		TTORATstpSPExchangeIDType	ExchangeID;

		///系统报单编号
		TTORATstpSPOrderSysIDType	OrderSysID;

		///交易所交易单元代码
		TTORATstpSPPbuIDType	PbuID;

		///交易所交易单元代码
		TTORATstpSPOrderLocalIDType	OrderLocalID;

		///合约代码
		TTORATstpSPSecurityIDType	SecurityID;

		///资金账户代码
		TTORATstpSPAccountIDType	AccountID;

		///投资者代码
		TTORATstpSPInvestorIDType	InvestorID;

		///投资单元代码
		TTORATstpSPBusinessUnitIDType	BusinessUnitID;

		///成交金额
		TTORATstpSPMoneyType	TradeAmount;

		///印花税
		TTORATstpSPMoneyType	StampTaxFee;

		///过户费
		TTORATstpSPMoneyType	TransferFee;

		///经手费
		TTORATstpSPMoneyType	HandlingFee;

		///证管费
		TTORATstpSPMoneyType	RegulateFee;

		///佣金
		TTORATstpSPMoneyType	BrokerageFee;

		///结算费
		TTORATstpSPMoneyType	SettlementFee;

		///保证金
		TTORATstpSPMoneyType	Margin;

		///报单初始冻结金额
		TTORATstpSPMoneyType	OrderCashFrozen;

		///初始冻结费用合计
		TTORATstpSPMoneyType	TotalFeeFrozen;

		///申报金额
		TTORATstpSPMoneyType	OrderAmount;

		///买卖方向
		TTORATstpSPDirectionType	Direction;

	};

	/// 查询资金转移流水
	struct CTORATstpSPQryFundTransferDetailField
	{
		 
		///资金账户代码
		TTORATstpSPAccountIDType	AccountID;

		///币种
		TTORATstpSPCurrencyIDType	CurrencyID;

		///转移方向
		TTORATstpSPTransferDirectionType	TransferDirection;

		///经纪公司部门代码
		TTORATstpSPDepartmentIDType	DepartmentID;

	};

	/// 资金转移流水
	struct CTORATstpSPFundTransferDetailField
	{
		 
		///转账流水号
		TTORATstpSPIntSerialType	FundSerial;

		///申请流水号
		TTORATstpSPIntSerialType	ApplySerial;

		///前置编号
		TTORATstpSPFrontIDType	FrontID;

		///会话编号
		TTORATstpSPSessionIDType	SessionID;

		///经纪公司部门代码
		TTORATstpSPDepartmentIDType	DepartmentID;

		///资金账户代码
		TTORATstpSPAccountIDType	AccountID;

		///币种
		TTORATstpSPCurrencyIDType	CurrencyID;

		///转移方向
		TTORATstpSPTransferDirectionType	TransferDirection;

		///出入金金额
		TTORATstpSPMoneyType	Amount;

		///转移状态
		TTORATstpSPTransferStatusType	TransferStatus;

		///操作来源
		TTORATstpSPOperateSourceType	OperateSource;

		///操作人员
		TTORATstpSPUserIDType	OperatorID;

		///操作日期
		TTORATstpSPDateType	OperateDate;

		///操作时间
		TTORATstpSPTimeType	OperateTime;

		///状态信息
		TTORATstpSPErrorMsgType	StatusMsg;

		///签约银行账户
		TTORATstpSPBankAccountIDType	BankAccountID;

		///银行代码
		TTORATstpSPBankIDType	BankID;

	};

	/// 查询持仓转移流水
	struct CTORATstpSPQryPositionTransferDetailField
	{
		 
		///投资者代码
		TTORATstpSPInvestorIDType	InvestorID;

		///目前该字段存放的是上证所和深圳的股东代码。
		TTORATstpSPShareholderIDType	ShareholderID;

		///证券代码
		TTORATstpSPSecurityIDType	SecurityID;

		///转移方向
		TTORATstpSPTransferDirectionType	TransferDirection;

		///投资单元代码
		TTORATstpSPBusinessUnitIDType	BusinessUnitID;

		///多、空
		TTORATstpSPPosiDirectionType	PosiDirection;

		///投机套保标志
		TTORATstpSPHedgeFlagType	HedgeFlag;

	};

	/// 持仓转移流水
	struct CTORATstpSPPositionTransferDetailField
	{
		 
		///流水号
		TTORATstpSPIntSerialType	PositionSerial;

		///申请流水号
		TTORATstpSPIntSerialType	ApplySerial;

		///前置编号
		TTORATstpSPFrontIDType	FrontID;

		///会话编号
		TTORATstpSPSessionIDType	SessionID;

		///投资者代码
		TTORATstpSPInvestorIDType	InvestorID;

		///投资单元代码
		TTORATstpSPBusinessUnitIDType	BusinessUnitID;

		///交易所代码
		TTORATstpSPExchangeIDType	ExchangeID;

		///交易账户代码
		TTORATstpSPShareholderIDType	ShareholderID;

		///市场代码
		TTORATstpSPMarketIDType	MarketID;

		///持仓方向
		TTORATstpSPPosiDirectionType	PosiDirection;

		///投机套保标志
		TTORATstpSPHedgeFlagType	HedgeFlag;

		///证券代码
		TTORATstpSPSecurityIDType	SecurityID;

		///交易日期
		TTORATstpSPDateType	TradingDay;

		///转移方向
		TTORATstpSPTransferDirectionType	TransferDirection;

		///转移持仓类型
		TTORATstpSPTransferPositionTypeType	TransferPositionType;

		///昨日仓位数量
		TTORATstpSPVolumeType	HistoryVolume;

		///今日买卖仓位数量
		TTORATstpSPVolumeType	TodayVolume;

		///转移状态
		TTORATstpSPTransferStatusType	TransferStatus;

		///操作人员
		TTORATstpSPUserIDType	OperatorID;

		///操作日期
		TTORATstpSPDateType	OperateDate;

		///操作时间
		TTORATstpSPTimeType	OperateTime;

		///状态信息
		TTORATstpSPErrorMsgType	StatusMsg;

	};

	/// 查询撤单
	struct CTORATstpSPQryOrderActionField
	{
		 
		///投资者代码
		TTORATstpSPInvestorIDType	InvestorID;

		///交易所代码
		TTORATstpSPExchangeIDType	ExchangeID;

		///交易所下的交易市场，如沪A、沪B市场
		TTORATstpSPMarketIDType	MarketID;

		///目前该字段存放的是上证所和深圳的股东代码。
		TTORATstpSPShareholderIDType	ShareholderID;

		///投资单元代码
		TTORATstpSPBusinessUnitIDType	BusinessUnitID;

		///交易单元代码
		TTORATstpSPPbuIDType	PbuID;

		///全系统的唯一报单编号。
		TTORATstpSPOrderLocalIDType	CancelOrderLocalID;

		///本地报单编号
		TTORATstpSPOrderLocalIDType	OrderLocalID;

		///长字符串附加信息
		TTORATstpSPBigsInfoType	BInfo;

		///短字符串附加信息
		TTORATstpSPShortsInfoType	SInfo;

		///整形附加信息
		TTORATstpSPIntInfoType	IInfo;

	};

	/// 撤单
	struct CTORATstpSPOrderActionField
	{
		 
		///交易日
		TTORATstpSPDateType	TradingDay;

		///操作本地编号
		TTORATstpSPOrderLocalIDType	CancelOrderLocalID;

		///撤单前置编号
		TTORATstpSPFrontIDType	ActionFrontID;

		///撤单会话编号
		TTORATstpSPSessionIDType	ActionSessionID;

		///撤单引用
		TTORATstpSPOrderRefType	OrderActionRef;

		///本地被撤报单编号
		TTORATstpSPOrderLocalIDType	OrderLocalID;

		///报单编号
		TTORATstpSPOrderSysIDType	OrderSysID;

		///前置编号
		TTORATstpSPFrontIDType	FrontID;

		///会话编号
		TTORATstpSPSessionIDType	SessionID;

		///报单引用
		TTORATstpSPOrderRefType	OrderRef;

		///投资者代码
		TTORATstpSPInvestorIDType	InvestorID;

		///投资单元代码
		TTORATstpSPBusinessUnitIDType	BusinessUnitID;

		///市场代码
		TTORATstpSPMarketIDType	MarketID;

		///股东账户代码
		TTORATstpSPShareholderIDType	ShareholderID;

		///交易所代码
		TTORATstpSPExchangeIDType	ExchangeID;

		///合约代码
		TTORATstpSPSecurityIDType	SecurityID;

		///操作标志
		TTORATstpSPOrderActionFlagType	OrderActionFlag;

		///撤单状态
		TTORATstpSPCancelOrderStatusType	CancelOrderStatus;

		///撤单数量
		TTORATstpSPVolumeType	VolumeCanceled;

		///状态信息
		TTORATstpSPStatusMsgType	StatusMsg;

		///系统错误代码
		TTORATstpSPErrorIDType	ErrorID;

		///交易所营业部编码
		TTORATstpSPBranchIDType	BranchID;

		///交易所交易单元代码
		TTORATstpSPPbuIDType	PbuID;

		///报单申报用户
		TTORATstpSPUserIDType	InsertUserID;

		///操作日期
		TTORATstpSPDateType	InsertDate;

		///操作时间
		TTORATstpSPTimeType	InsertTime;

		///申报时间(毫秒)
		TTORATstpSPMillisecType	InsertMillisec;

		///内网IP地址
		TTORATstpSPIPAddressType	InnerIPAddress;

		///Mac地址
		TTORATstpSPMacAddressType	MacAddress;

		///请求编号
		TTORATstpSPRequestIDType	RequestID;

		///长字符串附加信息
		TTORATstpSPBigsInfoType	BInfo;

		///短字符串附加信息
		TTORATstpSPShortsInfoType	SInfo;

		///整形附加信息
		TTORATstpSPIntInfoType	IInfo;

		///委托方式
		TTORATstpSPOperwayType	Operway;

		///硬盘序列号
		TTORATstpSPHDSerialType	HDSerial;

		///移动设备手机号
		TTORATstpSPMobileType	Mobile;

		///外网IP地址
		TTORATstpSPIPAddressType	OuterIPAddress;

		///外网端口号
		TTORATstpSPPortType	OuterPort;

	};

	/// 查询投资者现货持仓
	struct CTORATstpSPQryStockPositionField
	{
		 
		///投资者代码
		TTORATstpSPInvestorIDType	InvestorID;

		///证券代码
		TTORATstpSPSecurityIDType	SecurityID;

		///交易所代码
		TTORATstpSPExchangeIDType	ExchangeID;

		///交易所下的交易市场，如沪A、沪B市场
		TTORATstpSPMarketIDType	MarketID;

		///交易账户代码
		TTORATstpSPShareholderIDType	ShareholderID;

		///投资单元代码
		TTORATstpSPBusinessUnitIDType	BusinessUnitID;

	};

	/// 投资者现货持仓
	struct CTORATstpSPStockPositionField
	{
		 
		///投资者代码
		TTORATstpSPInvestorIDType	InvestorID;

		///投资单元代码
		TTORATstpSPBusinessUnitIDType	BusinessUnitID;

		///市场代码
		TTORATstpSPMarketIDType	MarketID;

		///客户代码
		TTORATstpSPShareholderIDType	ShareholderID;

		///交易日
		TTORATstpSPDateType	TradingDay;

		///交易所代码
		TTORATstpSPExchangeIDType	ExchangeID;

		///合约代码
		TTORATstpSPSecurityIDType	SecurityID;

		///昨日持仓
		TTORATstpSPVolumeType	HistoryPos;

		///昨日持仓冻结
		TTORATstpSPVolumeType	HistoryPosFrozen;

		///今日买卖持仓
		TTORATstpSPVolumeType	TodayBSPos;

		///今日买卖持仓冻结
		TTORATstpSPVolumeType	TodayBSPosFrozen;

		///今日申赎持仓
		TTORATstpSPVolumeType	TodayPRPos;

		///今日申赎持仓冻结
		TTORATstpSPVolumeType	TodayPRPosFrozen;

	};

	/// 查询锁定委托
	struct CTORATstpSPQryLockField
	{
		 
		///投资者代码
		TTORATstpSPInvestorIDType	InvestorID;

		///合约在系统中的编号
		TTORATstpSPSecurityIDType	SecurityID;

		///交易所代码
		TTORATstpSPExchangeIDType	ExchangeID;

		///交易所下的交易市场，如沪A、沪B市场
		TTORATstpSPMarketIDType	MarketID;

		///客户在系统中的编号，编号唯一且遵循交易所制定的编码规则
		TTORATstpSPShareholderIDType	ShareholderID;

		///报单编号
		TTORATstpSPOrderSysIDType	LockSysID;

		///Time
		TTORATstpSPTimeType	InsertTimeStart;

		///Time
		TTORATstpSPTimeType	InsertTimeEnd;

		///投资单元代码
		TTORATstpSPBusinessUnitIDType	BusinessUnitID;

		///锁定类别
		TTORATstpSPLockTypeType	LockType;

		///长字符串附加信息
		TTORATstpSPBigsInfoType	BInfo;

		///短字符串附加信息
		TTORATstpSPShortsInfoType	SInfo;

		///整形附加信息
		TTORATstpSPIntInfoType	IInfo;

	};

	/// 查询行权委托
	struct CTORATstpSPQryExerciseField
	{
		 
		///投资者代码
		TTORATstpSPInvestorIDType	InvestorID;

		///合约在系统中的编号
		TTORATstpSPSecurityIDType	SecurityID;

		///交易所代码
		TTORATstpSPExchangeIDType	ExchangeID;

		///市场代码
		TTORATstpSPMarketIDType	MarketID;

		///目前该字段存放的是上证所和深圳的股东代码。
		TTORATstpSPShareholderIDType	ShareholderID;

		///全系统的唯一报单编号
		TTORATstpSPOrderSysIDType	ExerciseSysID;

		///Time
		TTORATstpSPTimeType	InsertTimeStart;

		///Time
		TTORATstpSPTimeType	InsertTimeEnd;

		///投资单元代码
		TTORATstpSPBusinessUnitIDType	BusinessUnitID;

		///长字符串附加信息
		TTORATstpSPBigsInfoType	BInfo;

		///短字符串附加信息
		TTORATstpSPShortsInfoType	SInfo;

		///整形附加信息
		TTORATstpSPIntInfoType	IInfo;

	};

	/// 查询投资者锁定持仓
	struct CTORATstpSPQryLockPositionField
	{
		 
		///投资者代码
		TTORATstpSPInvestorIDType	InvestorID;

		///证券代码
		TTORATstpSPSecurityIDType	SecurityID;

		///交易所代码
		TTORATstpSPExchangeIDType	ExchangeID;

		///交易所下的交易市场，如沪A、沪B市场
		TTORATstpSPMarketIDType	MarketID;

		///交易账户代码
		TTORATstpSPShareholderIDType	ShareholderID;

		///投资单元代码
		TTORATstpSPBusinessUnitIDType	BusinessUnitID;

	};

	/// 投资者锁定持仓
	struct CTORATstpSPLockPositionField
	{
		 
		///投资者代码
		TTORATstpSPInvestorIDType	InvestorID;

		///投资单元代码
		TTORATstpSPBusinessUnitIDType	BusinessUnitID;

		///市场代码
		TTORATstpSPMarketIDType	MarketID;

		///客户代码
		TTORATstpSPShareholderIDType	ShareholderID;

		///交易日
		TTORATstpSPDateType	TradingDay;

		///交易所代码
		TTORATstpSPExchangeIDType	ExchangeID;

		///合约代码
		TTORATstpSPSecurityIDType	SecurityID;

		///锁定持仓总数量
		TTORATstpSPVolumeType	Volume;

		///锁定持仓冻结数量
		TTORATstpSPVolumeType	FrozenVolume;

		///昨日持仓
		TTORATstpSPVolumeType	HistoryPos;

		///今日买卖持仓
		TTORATstpSPVolumeType	TodayBSPos;

		///今日申赎持仓
		TTORATstpSPVolumeType	TodayPRPos;

	};

	/// 查询行权撤单
	struct CTORATstpSPQryExerciseActionField
	{
		 
		///投资者代码
		TTORATstpSPInvestorIDType	InvestorID;

		///交易所代码
		TTORATstpSPExchangeIDType	ExchangeID;

		///交易所下的交易市场，如沪A、沪B市场
		TTORATstpSPMarketIDType	MarketID;

		///目前该字段存放的是上证所和深圳的股东代码。
		TTORATstpSPShareholderIDType	ShareholderID;

		///投资单元代码
		TTORATstpSPBusinessUnitIDType	BusinessUnitID;

		///交易单元代码
		TTORATstpSPPbuIDType	PbuID;

		///全系统的唯一报单编号。
		TTORATstpSPOrderLocalIDType	CancelExerciseLocalID;

		///本地报单编号
		TTORATstpSPOrderLocalIDType	ExerciseLocalID;

		///长字符串附加信息
		TTORATstpSPBigsInfoType	BInfo;

		///短字符串附加信息
		TTORATstpSPShortsInfoType	SInfo;

		///整形附加信息
		TTORATstpSPIntInfoType	IInfo;

	};

	/// 行权撤单
	struct CTORATstpSPExerciseActionField
	{
		 
		///交易日
		TTORATstpSPDateType	TradingDay;

		///交易所营业部编码
		TTORATstpSPBranchIDType	BranchID;

		///交易所交易单元代码
		TTORATstpSPPbuIDType	PbuID;

		///本地行权撤单编号
		TTORATstpSPOrderLocalIDType	CancelExerciseLocalID;

		///撤单前置编号
		TTORATstpSPFrontIDType	ActionFrontID;

		///撤单会话编号
		TTORATstpSPSessionIDType	ActionSessionID;

		///行权撤单引用
		TTORATstpSPOrderRefType	ExerciseActionRef;

		///被撤本地行权报单编号
		TTORATstpSPOrderLocalIDType	ExerciseLocalID;

		///被撤系统行权报单编号
		TTORATstpSPOrderSysIDType	ExerciseSysID;

		///前置编号
		TTORATstpSPFrontIDType	FrontID;

		///会话编号
		TTORATstpSPSessionIDType	SessionID;

		///行权引用
		TTORATstpSPOrderRefType	ExerciseRef;

		///投资者代码
		TTORATstpSPInvestorIDType	InvestorID;

		///投资单元代码
		TTORATstpSPBusinessUnitIDType	BusinessUnitID;

		///市场代码
		TTORATstpSPMarketIDType	MarketID;

		///股东账户代码
		TTORATstpSPShareholderIDType	ShareholderID;

		///交易所代码
		TTORATstpSPExchangeIDType	ExchangeID;

		///合约代码
		TTORATstpSPSecurityIDType	SecurityID;

		///委托操作标志
		TTORATstpSPOrderActionFlagType	ExerciseActionFlag;

		///撤单状态
		TTORATstpSPCancelOrderStatusType	CancelOrderStatus;

		///撤单数量
		TTORATstpSPVolumeType	VolumeCanceled;

		///状态信息
		TTORATstpSPStatusMsgType	StatusMsg;

		///系统错误代码
		TTORATstpSPErrorIDType	ErrorID;

		///报单申报用户
		TTORATstpSPUserIDType	InsertUserID;

		///操作日期
		TTORATstpSPDateType	InsertDate;

		///操作时间
		TTORATstpSPTimeType	InsertTime;

		///申报时间(毫秒)
		TTORATstpSPMillisecType	InsertMillisec;

		///内网IP地址
		TTORATstpSPIPAddressType	InnerIPAddress;

		///Mac地址
		TTORATstpSPMacAddressType	MacAddress;

		///请求编号
		TTORATstpSPRequestIDType	RequestID;

		///长字符串附加信息
		TTORATstpSPBigsInfoType	BInfo;

		///短字符串附加信息
		TTORATstpSPShortsInfoType	SInfo;

		///整形附加信息
		TTORATstpSPIntInfoType	IInfo;

		///委托方式
		TTORATstpSPOperwayType	Operway;

		///硬盘序列号
		TTORATstpSPHDSerialType	HDSerial;

		///移动设备手机号
		TTORATstpSPMobileType	Mobile;

		///外网IP地址
		TTORATstpSPIPAddressType	OuterIPAddress;

		///外网端口号
		TTORATstpSPPortType	OuterPort;

	};

	/// 查询锁定撤单
	struct CTORATstpSPQryLockActionField
	{
		 
		///投资者代码
		TTORATstpSPInvestorIDType	InvestorID;

		///交易所代码
		TTORATstpSPExchangeIDType	ExchangeID;

		///交易所下的交易市场，如沪A、沪B市场
		TTORATstpSPMarketIDType	MarketID;

		///目前该字段存放的是上证所和深圳的股东代码。
		TTORATstpSPShareholderIDType	ShareholderID;

		///投资单元代码
		TTORATstpSPBusinessUnitIDType	BusinessUnitID;

		///交易单元代码
		TTORATstpSPPbuIDType	PbuID;

		///全系统的唯一报单编号。
		TTORATstpSPOrderLocalIDType	CancelLockLocalID;

		///本地报单顺序号
		TTORATstpSPOrderLocalIDType	LockLocalID;

		///长字符串附加信息
		TTORATstpSPBigsInfoType	BInfo;

		///短字符串附加信息
		TTORATstpSPShortsInfoType	SInfo;

		///整形附加信息
		TTORATstpSPIntInfoType	IInfo;

	};

	/// 锁定撤单
	struct CTORATstpSPLockActionField
	{
		 
		///交易日
		TTORATstpSPDateType	TradingDay;

		///交易所营业部编码
		TTORATstpSPBranchIDType	BranchID;

		///交易所交易单元代码
		TTORATstpSPPbuIDType	PbuID;

		///本地锁定撤单编号
		TTORATstpSPOrderLocalIDType	CancelLockLocalID;

		///撤单前置编号
		TTORATstpSPFrontIDType	ActionFrontID;

		///撤单会话编号
		TTORATstpSPSessionIDType	ActionSessionID;

		///锁定撤单引用
		TTORATstpSPOrderRefType	LockActionRef;

		///被撤本地锁定报单编号
		TTORATstpSPOrderLocalIDType	LockLocalID;

		///被撤系统锁定报单编号
		TTORATstpSPOrderSysIDType	LockSysID;

		///前置编号
		TTORATstpSPFrontIDType	FrontID;

		///会话编号
		TTORATstpSPSessionIDType	SessionID;

		///锁定引用
		TTORATstpSPOrderRefType	LockRef;

		///投资者代码
		TTORATstpSPInvestorIDType	InvestorID;

		///投资单元代码
		TTORATstpSPBusinessUnitIDType	BusinessUnitID;

		///市场代码
		TTORATstpSPMarketIDType	MarketID;

		///股东账户代码
		TTORATstpSPShareholderIDType	ShareholderID;

		///交易所代码
		TTORATstpSPExchangeIDType	ExchangeID;

		///合约代码
		TTORATstpSPSecurityIDType	SecurityID;

		///锁定操作标志
		TTORATstpSPOrderActionFlagType	LockActionFlag;

		///撤单状态
		TTORATstpSPCancelOrderStatusType	CancelOrderStatus;

		///撤单数量
		TTORATstpSPVolumeType	VolumeCanceled;

		///状态信息
		TTORATstpSPStatusMsgType	StatusMsg;

		///系统错误代码
		TTORATstpSPErrorIDType	ErrorID;

		///报单申报用户
		TTORATstpSPUserIDType	InsertUserID;

		///操作日期
		TTORATstpSPDateType	InsertDate;

		///操作时间
		TTORATstpSPTimeType	InsertTime;

		///申报时间(毫秒)
		TTORATstpSPMillisecType	InsertMillisec;

		///内网IP地址
		TTORATstpSPIPAddressType	InnerIPAddress;

		///Mac地址
		TTORATstpSPMacAddressType	MacAddress;

		///请求编号
		TTORATstpSPRequestIDType	RequestID;

		///长字符串附加信息
		TTORATstpSPBigsInfoType	BInfo;

		///短字符串附加信息
		TTORATstpSPShortsInfoType	SInfo;

		///整形附加信息
		TTORATstpSPIntInfoType	IInfo;

		///委托方式
		TTORATstpSPOperwayType	Operway;

		///硬盘序列号
		TTORATstpSPHDSerialType	HDSerial;

		///移动设备手机号
		TTORATstpSPMobileType	Mobile;

		///外网IP地址
		TTORATstpSPIPAddressType	OuterIPAddress;

		///外网端口号
		TTORATstpSPPortType	OuterPort;

	};

	/// 查询现货持仓转移流水
	struct CTORATstpSPQryStockPositionTransferDetailField
	{
		 
		///投资者代码
		TTORATstpSPInvestorIDType	InvestorID;

		///目前该字段存放的是上证所和深圳的股东代码。
		TTORATstpSPShareholderIDType	ShareholderID;

		///证券代码
		TTORATstpSPSecurityIDType	SecurityID;

		///个股期权标的现货转移原因
		TTORATstpSPSPStockTransferReasonType	SPStockTransferReason;

		///投资单元代码
		TTORATstpSPBusinessUnitIDType	BusinessUnitID;

		///转移持仓类型
		TTORATstpSPTransferPositionTypeType	TransferPositionType;

	};

	/// 现货持仓转移流水
	struct CTORATstpSPStockPositionTransferDetailField
	{
		 
		///流水号
		TTORATstpSPIntSerialType	PositionSerial;

		///申请流水号
		TTORATstpSPIntSerialType	ApplySerial;

		///投资者代码
		TTORATstpSPInvestorIDType	InvestorID;

		///投资单元代码
		TTORATstpSPBusinessUnitIDType	BusinessUnitID;

		///交易账户代码
		TTORATstpSPShareholderIDType	ShareholderID;

		///现货系统投资者代码
		TTORATstpSPInvestorIDType	OuterInvestorID;

		///现货系统投资单元代码
		TTORATstpSPBusinessUnitIDType	OuterBusinessUnitID;

		///现货系统交易账户代码
		TTORATstpSPShareholderIDType	OuterShareholderID;

		///交易所代码
		TTORATstpSPExchangeIDType	ExchangeID;

		///市场代码
		TTORATstpSPMarketIDType	MarketID;

		///证券代码
		TTORATstpSPSecurityIDType	SecurityID;

		///交易日期
		TTORATstpSPDateType	TradingDay;

		///个股期权标的现货转移原因
		TTORATstpSPSPStockTransferReasonType	SPStockTransferReason;

		///转移持仓类型
		TTORATstpSPTransferPositionTypeType	TransferPositionType;

		///昨日仓位数量
		TTORATstpSPVolumeType	HistoryVolume;

		///今日买卖仓位数量
		TTORATstpSPVolumeType	TodayBSVolume;

		///今日申赎持仓数量
		TTORATstpSPVolumeType	TodayPRVolume;

		///转移状态
		TTORATstpSPTransferStatusType	TransferStatus;

		///操作人员
		TTORATstpSPUserIDType	OperatorID;

		///操作日期
		TTORATstpSPDateType	OperateDate;

		///操作时间
		TTORATstpSPTimeType	OperateTime;

		///状态信息
		TTORATstpSPErrorMsgType	StatusMsg;

		///仓位转移现货系统流水号
		TTORATstpSPIntSerialType	StockPositionSerial;

		///是否冲正
		TTORATstpSPBoolType	bRepeal;

		///原始仓位转移流水号
		TTORATstpSPIntSerialType	OriginPositionSerial;

		///操作来源
		TTORATstpSPOperateSourceType	OperateSource;

		///业务编号
		TTORATstpSPBizRefType	BizRef;

	};

	/// 查询交易通知
	struct CTORATstpSPQryTradingNoticeField
	{
		 
		///投资者代码
		TTORATstpSPInvestorIDType	InvestorID;

		///Date
		TTORATstpSPDateType	DateStart;

		///Date
		TTORATstpSPDateType	DateEnd;

		///Time
		TTORATstpSPTimeType	TimeStart;

		///Time
		TTORATstpSPTimeType	TimeEnd;

	};

	/// 查询证券处置
	struct CTORATstpSPQryStockDisposalField
	{
		 
		///投资者代码
		TTORATstpSPInvestorIDType	InvestorID;

		///个股期权标的合约代码
		TTORATstpSPSecurityIDType	SecurityID;

		///交易所代码
		TTORATstpSPExchangeIDType	ExchangeID;

		///市场代码
		TTORATstpSPMarketIDType	MarketID;

		///目前该字段存放的是上证所和深圳的股东代码。
		TTORATstpSPShareholderIDType	ShareholderID;

		///系统证券处置编号
		TTORATstpSPOrderSysIDType	StockDisposalSysID;

		///Time
		TTORATstpSPTimeType	InsertTimeStart;

		///Time
		TTORATstpSPTimeType	InsertTimeEnd;

		///投资单元代码
		TTORATstpSPBusinessUnitIDType	BusinessUnitID;

		///长字符串附加信息
		TTORATstpSPBigsInfoType	BInfo;

		///短字符串附加信息
		TTORATstpSPShortsInfoType	SInfo;

		///整形附加信息
		TTORATstpSPIntInfoType	IInfo;

	};

	/// 查询证券处置撤单
	struct CTORATstpSPQryStockDisposalActionField
	{
		 
		///投资者代码
		TTORATstpSPInvestorIDType	InvestorID;

		///交易所代码
		TTORATstpSPExchangeIDType	ExchangeID;

		///交易所下的交易市场，如沪A、沪B市场
		TTORATstpSPMarketIDType	MarketID;

		///目前该字段存放的是上证所和深圳的股东代码。
		TTORATstpSPShareholderIDType	ShareholderID;

		///投资单元代码
		TTORATstpSPBusinessUnitIDType	BusinessUnitID;

		///交易单元代码
		TTORATstpSPPbuIDType	PbuID;

		///全系统的唯一报单编号。
		TTORATstpSPOrderLocalIDType	CancelStockDisposalLocalID;

		///本地证券处置编号
		TTORATstpSPOrderLocalIDType	StockDisposalLocalID;

		///长字符串附加信息
		TTORATstpSPBigsInfoType	BInfo;

		///短字符串附加信息
		TTORATstpSPShortsInfoType	SInfo;

		///整形附加信息
		TTORATstpSPIntInfoType	IInfo;

	};

	/// 证券处置撤单
	struct CTORATstpSPStockDisposalActionField
	{
		 
		///交易日
		TTORATstpSPDateType	TradingDay;

		///交易所营业部编码
		TTORATstpSPBranchIDType	BranchID;

		///交易所交易单元代码
		TTORATstpSPPbuIDType	PbuID;

		///本地证券处置撤单编号
		TTORATstpSPOrderLocalIDType	CancelStockDisposalLocalID;

		///撤单前置编号
		TTORATstpSPFrontIDType	ActionFrontID;

		///撤单会话编号
		TTORATstpSPSessionIDType	ActionSessionID;

		///证券处置撤单引用
		TTORATstpSPOrderRefType	StockDisposalActionRef;

		///被撤本地证券处置报单编号
		TTORATstpSPOrderLocalIDType	StockDisposalLocalID;

		///被撤证券处置系统报单编号
		TTORATstpSPOrderSysIDType	StockDisposalSysID;

		///前置编号
		TTORATstpSPFrontIDType	FrontID;

		///会话编号
		TTORATstpSPSessionIDType	SessionID;

		///被撤证券处置引用
		TTORATstpSPOrderRefType	StockDisposalRef;

		///投资者代码
		TTORATstpSPInvestorIDType	InvestorID;

		///投资单元代码
		TTORATstpSPBusinessUnitIDType	BusinessUnitID;

		///市场代码
		TTORATstpSPMarketIDType	MarketID;

		///股东账户代码
		TTORATstpSPShareholderIDType	ShareholderID;

		///交易所代码
		TTORATstpSPExchangeIDType	ExchangeID;

		///合约代码
		TTORATstpSPSecurityIDType	SecurityID;

		///证券处置操作标志
		TTORATstpSPOrderActionFlagType	StockDisposalActionFlag;

		///撤单状态
		TTORATstpSPCancelOrderStatusType	CancelStockDisposalStatus;

		///撤单数量
		TTORATstpSPVolumeType	VolumeCanceled;

		///状态信息
		TTORATstpSPStatusMsgType	StatusMsg;

		///系统错误代码
		TTORATstpSPErrorIDType	ErrorID;

		///报单申报用户
		TTORATstpSPUserIDType	InsertUserID;

		///操作日期
		TTORATstpSPDateType	InsertDate;

		///操作时间
		TTORATstpSPTimeType	InsertTime;

		///申报时间(毫秒)
		TTORATstpSPMillisecType	InsertMillisec;

		///内网IP地址
		TTORATstpSPIPAddressType	InnerIPAddress;

		///Mac地址
		TTORATstpSPMacAddressType	MacAddress;

		///请求编号
		TTORATstpSPRequestIDType	RequestID;

		///长字符串附加信息
		TTORATstpSPBigsInfoType	BInfo;

		///短字符串附加信息
		TTORATstpSPShortsInfoType	SInfo;

		///整形附加信息
		TTORATstpSPIntInfoType	IInfo;

		///委托方式
		TTORATstpSPOperwayType	Operway;

		///硬盘序列号
		TTORATstpSPHDSerialType	HDSerial;

		///电话
		TTORATstpSPMobileType	Mobile;

		///外网IP地址
		TTORATstpSPIPAddressType	OuterIPAddress;

		///外网端口号
		TTORATstpSPPortType	OuterPort;

	};

	/// 查询条件单
	struct CTORATstpSPQryCondOrderField
	{
		 
		///投资者代码
		TTORATstpSPInvestorIDType	InvestorID;

		///合约代码
		TTORATstpSPSecurityIDType	SecurityID;

		///交易所代码
		TTORATstpSPExchangeIDType	ExchangeID;

		///目前该字段存放的是上证所和深圳的股东代码。
		TTORATstpSPShareholderIDType	ShareholderID;

		///报单编号
		TTORATstpSPCondOrderIDType	CondOrderID;

		///Time
		TTORATstpSPTimeType	InsertTimeStart;

		///Time
		TTORATstpSPTimeType	InsertTimeEnd;

		///投资单元代码
		TTORATstpSPBusinessUnitIDType	BusinessUnitID;

		///长字符串附加信息
		TTORATstpSPBigsInfoType	BInfo;

		///短字符串附加信息
		TTORATstpSPShortsInfoType	SInfo;

		///整形附加信息
		TTORATstpSPIntInfoType	IInfo;

	};

	/// 条件单
	struct CTORATstpSPCondOrderField
	{
		 
		///交易所代码
		TTORATstpSPExchangeIDType	ExchangeID;

		///投资者代码
		TTORATstpSPInvestorIDType	InvestorID;

		///投资单元代码
		TTORATstpSPBusinessUnitIDType	BusinessUnitID;

		///股东账户代码
		TTORATstpSPShareholderIDType	ShareholderID;

		///合约代码
		TTORATstpSPSecurityIDType	SecurityID;

		///买卖方向
		TTORATstpSPDirectionType	Direction;

		///条件单价格类型
		TTORATstpSPOrderPriceTypeType	OrderPriceType;

		///条件单数量类型
		TTORATstpSPOrderVolumeTypeType	OrderVolumeType;

		///有效期类型
		TTORATstpSPTimeConditionType	TimeCondition;

		///成交量类型
		TTORATstpSPVolumeConditionType	VolumeCondition;

		///最小成交量
		TTORATstpSPVolumeType	MinVolume;

		///强平原因
		TTORATstpSPForceCloseReasonType	ForceCloseReason;

		///报单价格
		TTORATstpSPPriceType	LimitPrice;

		///报单数量
		TTORATstpSPVolumeType	VolumeTotalOriginal;

		///组合开平标志
		TTORATstpSPCombOffsetFlagType	CombOffsetFlag;

		///组合投机套保标志
		TTORATstpSPCombHedgeFlagType	CombHedgeFlag;

		///条件报单引用
		TTORATstpSPOrderRefType	CondOrderRef;

		///资金账户代码
		TTORATstpSPAccountIDType	AccountID;

		///请求编号
		TTORATstpSPRequestIDType	RequestID;

		///内网IP地址
		TTORATstpSPIPAddressType	InnerIPAddress;

		///Mac地址
		TTORATstpSPMacAddressType	MacAddress;

		///条件报单编号
		TTORATstpSPCondOrderIDType	CondOrderID;

		///终端信息
		TTORATstpSPTerminalInfoType	TerminalInfo;

		///长字符串附加信息
		TTORATstpSPBigsInfoType	BInfo;

		///短字符串附加信息
		TTORATstpSPShortsInfoType	SInfo;

		///整形附加信息
		TTORATstpSPIntInfoType	IInfo;

		///触发条件
		TTORATstpSPContingentConditionType	ContingentCondition;

		///条件价
		TTORATstpSPPriceType	ConditionPrice;

		///价格浮动tick数
		TTORATstpSPVolumeType	PriceTicks;

		///数量浮动倍数
		TTORATstpSPVolumeMultipleType	VolumeMultiple;

		///相关前置编号
		TTORATstpSPFrontIDType	RelativeFrontID;

		///相关会话编号
		TTORATstpSPSessionIDType	RelativeSessionID;

		///相关条件参数
		TTORATstpSPRelativeCondParamType	RelativeParam;

		///附加触发条件
		TTORATstpSPContingentConditionType	AppendContingentCondition;

		///附加条件价
		TTORATstpSPPriceType	AppendConditionPrice;

		///附加相关前置编号
		TTORATstpSPFrontIDType	AppendRelativeFrontID;

		///附加相关会话编号
		TTORATstpSPSessionIDType	AppendRelativeSessionID;

		///附加相关条件参数
		TTORATstpSPRelativeCondParamType	AppendRelativeParam;

		///交易日
		TTORATstpSPDateType	TradingDay;

		///前置编号
		TTORATstpSPFrontIDType	FrontID;

		///会话编号
		TTORATstpSPSessionIDType	SessionID;

		///经纪公司部门代码
		TTORATstpSPDepartmentIDType	DepartmentID;

		///条件单状态
		TTORATstpSPCondOrderStatusType	CondOrderStatus;

		///状态信息
		TTORATstpSPStatusMsgType	StatusMsg;

		///报单申报用户
		TTORATstpSPUserIDType	InsertUserID;

		///报单日期
		TTORATstpSPDateType	InsertDate;

		///委托时间
		TTORATstpSPTimeType	InsertTime;

		///委托毫秒
		TTORATstpSPMillisecType	InsertMillisec;

		///撤销时间
		TTORATstpSPTimeType	CancelTime;

		///撤销用户
		TTORATstpSPUserIDType	CancelUserID;

		///触发时间
		TTORATstpSPTimeType	ActiveTime;

		///委托方式
		TTORATstpSPOperwayType	Operway;

		///硬盘序列号
		TTORATstpSPHDSerialType	HDSerial;

		///移动设备手机号
		TTORATstpSPMobileType	Mobile;

		///外网IP地址
		TTORATstpSPIPAddressType	OuterIPAddress;

		///外网端口号
		TTORATstpSPPortType	OuterPort;

	};

	/// 查询条件单撤单
	struct CTORATstpSPQryCondOrderActionField
	{
		 
		///投资者代码
		TTORATstpSPInvestorIDType	InvestorID;

		///一个交易所的编号
		TTORATstpSPExchangeIDType	ExchangeID;

		///股东账户代码
		TTORATstpSPShareholderIDType	ShareholderID;

		///长字符串附加信息
		TTORATstpSPBigsInfoType	BInfo;

		///短字符串附加信息
		TTORATstpSPShortsInfoType	SInfo;

		///整形附加信息
		TTORATstpSPIntInfoType	IInfo;

	};

	/// 条件单撤单
	struct CTORATstpSPCondOrderActionField
	{
		 
		///交易所代码
		TTORATstpSPExchangeIDType	ExchangeID;

		///请求编号
		TTORATstpSPRequestIDType	RequestID;

		///条件单操作引用
		TTORATstpSPOrderRefType	CondOrderActionRef;

		///条件单引用
		TTORATstpSPOrderRefType	CondOrderRef;

		///前置编号
		TTORATstpSPFrontIDType	FrontID;

		///会话编号
		TTORATstpSPSessionIDType	SessionID;

		///条件单编号
		TTORATstpSPCondOrderIDType	CondOrderID;

		///操作标志
		TTORATstpSPOrderActionFlagType	OrderActionFlag;

		///合约代码
		TTORATstpSPSecurityIDType	SecurityID;

		///条件单撤单编号
		TTORATstpSPCondOrderIDType	CancelCondOrderID;

		///IP地址
		TTORATstpSPIPAddressType	InnerIPAddress;

		///MAC地址
		TTORATstpSPMacAddressType	MacAddress;

		///终端信息
		TTORATstpSPTerminalInfoType	TerminalInfo;

		///长字符串附加信息
		TTORATstpSPBigsInfoType	BInfo;

		///短字符串附加信息
		TTORATstpSPShortsInfoType	SInfo;

		///整形附加信息
		TTORATstpSPIntInfoType	IInfo;

		///投资者代码
		TTORATstpSPInvestorIDType	InvestorID;

		///投资单元代码
		TTORATstpSPBusinessUnitIDType	BusinessUnitID;

		///股东账户代码
		TTORATstpSPShareholderIDType	ShareholderID;

		///申报用户
		TTORATstpSPUserIDType	InsertUserID;

		///申报日期
		TTORATstpSPDateType	InsertDate;

		///申报时间
		TTORATstpSPTimeType	InsertTime;

		///申报毫秒
		TTORATstpSPMillisecType	InsertMillisec;

		///委托方式
		TTORATstpSPOperwayType	Operway;

		///硬盘序列号
		TTORATstpSPHDSerialType	HDSerial;

		///移动设备手机号
		TTORATstpSPMobileType	Mobile;

		///外网IP地址
		TTORATstpSPIPAddressType	OuterIPAddress;

		///外网端口号
		TTORATstpSPPortType	OuterPort;

	};

	/// 查询投资者限仓额度
	struct CTORATstpSPQryInvestorLimitPositionField
	{
		 
		///投资者代码
		TTORATstpSPInvestorIDType	InvestorID;

		///交易所代码
		TTORATstpSPExchangeIDType	ExchangeID;

		///标的证券代码
		TTORATstpSPSecurityIDType	SecurityID;

	};

	/// 投资者限仓额度
	struct CTORATstpSPInvestorLimitPositionField
	{
		 
		///投资者代码
		TTORATstpSPInvestorIDType	InvestorID;

		///交易所代码
		TTORATstpSPExchangeIDType	ExchangeID;

		///标的证券代码
		TTORATstpSPSecurityIDType	SecurityID;

		///总持仓限额
		TTORATstpSPVolumeType	TotalPositionLimit;

		///多头持仓限额
		TTORATstpSPVolumeType	LongPositionLimit;

		///单日买入开仓限额
		TTORATstpSPVolumeType	TodayBuyOpenLimit;

		///单日卖出开仓限额
		TTORATstpSPVolumeType	TodaySellOpenLimit;

		///单日备兑开仓限额
		TTORATstpSPVolumeType	TodayCoveredOpenLimit;

		///单日开仓限额
		TTORATstpSPVolumeType	TodayOpenLimit;

		///认购多头持仓限额
		TTORATstpSPVolumeType	LongCallPositionLimit;

		///认沽多头持仓限额
		TTORATstpSPVolumeType	LongPutPositionLimit;

		///标的多头持仓限额
		TTORATstpSPVolumeType	LongUnderlyingPositionLimit;

		///标的空头持仓限额
		TTORATstpSPVolumeType	ShortUnderlyingPositionLimit;

		///总持仓冻结额度
		TTORATstpSPVolumeType	TotalPositionFrozen;

		///多头持仓冻结额度
		TTORATstpSPVolumeType	LongPositionFrozen;

		///单日买入开仓冻结额度
		TTORATstpSPVolumeType	TodayBuyOpenFrozen;

		///单日卖出开仓冻结额度
		TTORATstpSPVolumeType	TodaySellOpenFrozen;

		///单日备兑开仓冻结额度
		TTORATstpSPVolumeType	TodayCoveredOpenFrozen;

		///单日开仓冻结额度
		TTORATstpSPVolumeType	TodayOpenFrozen;

		///认购多头持仓冻结额度
		TTORATstpSPVolumeType	LongCallPositionFrozen;

		///认沽多头持仓冻结额度
		TTORATstpSPVolumeType	LongPutPositionFrozen;

		///标的多头持仓冻结额度
		TTORATstpSPVolumeType	LongUnderlyingPositionFrozen;

		///标的空头持仓冻结额度
		TTORATstpSPVolumeType	ShortUnderlyingPositionFrozen;

	};

	/// 查询投资者限额
	struct CTORATstpSPQryInvestorLimitAmountField
	{
		 
		///投资者代码
		TTORATstpSPInvestorIDType	InvestorID;

		///交易所代码
		TTORATstpSPExchangeIDType	ExchangeID;

	};

	/// 投资者限额
	struct CTORATstpSPInvestorLimitAmountField
	{
		 
		///投资者代码
		TTORATstpSPInvestorIDType	InvestorID;

		///多头金额限额
		TTORATstpSPMoneyType	LongAmountLimit;

		///多头金额冻结
		TTORATstpSPMoneyType	LongAmountFrozen;

		///市场代码
		TTORATstpSPMarketIDType	MarketID;

		///交易所代码
		TTORATstpSPExchangeIDType	ExchangeID;

	};

	/// 查询组合撤单
	struct CTORATstpSPQryCombOrderActionField
	{
		 
		///投资者代码
		TTORATstpSPInvestorIDType	InvestorID;

		///交易所代码
		TTORATstpSPExchangeIDType	ExchangeID;

		///交易所下的交易市场，如沪A、沪B市场
		TTORATstpSPMarketIDType	MarketID;

		///目前该字段存放的是上证所和深圳的股东代码。
		TTORATstpSPShareholderIDType	ShareholderID;

		///投资单元代码
		TTORATstpSPBusinessUnitIDType	BusinessUnitID;

		///交易单元代码
		TTORATstpSPPbuIDType	PbuID;

		///全系统的唯一的组合报单撤单编号
		TTORATstpSPOrderLocalIDType	CancelCombOrderLocalID;

		///本地组合报单编号
		TTORATstpSPOrderLocalIDType	CombOrderLocalID;

		///长字符串附加信息
		TTORATstpSPBigsInfoType	BInfo;

		///短字符串附加信息
		TTORATstpSPShortsInfoType	SInfo;

		///整形附加信息
		TTORATstpSPIntInfoType	IInfo;

	};

	/// 组合撤单
	struct CTORATstpSPCombOrderActionField
	{
		 
		///交易日
		TTORATstpSPDateType	TradingDay;

		///交易所营业部编码
		TTORATstpSPBranchIDType	BranchID;

		///交易单元代码
		TTORATstpSPPbuIDType	PbuID;

		///本地组合委托撤单编号
		TTORATstpSPOrderLocalIDType	CancelCombOrderLocalID;

		///组合撤单前置编号
		TTORATstpSPFrontIDType	ActionFrontID;

		///组合撤单会话编号
		TTORATstpSPSessionIDType	ActionSessionID;

		///组合撤单引用
		TTORATstpSPOrderRefType	CombOrderActionRef;

		///被撤本地组合委托报单编号
		TTORATstpSPOrderLocalIDType	CombOrderLocalID;

		///被撤系统组合报单编号
		TTORATstpSPOrderSysIDType	CombOrderSysID;

		///前置编号
		TTORATstpSPFrontIDType	FrontID;

		///会话编号
		TTORATstpSPSessionIDType	SessionID;

		///组合报单引用
		TTORATstpSPOrderRefType	OrderRef;

		///投资者代码
		TTORATstpSPInvestorIDType	InvestorID;

		///投资单元代码
		TTORATstpSPBusinessUnitIDType	BusinessUnitID;

		///市场代码
		TTORATstpSPMarketIDType	MarketID;

		///股东账户代码
		TTORATstpSPShareholderIDType	ShareholderID;

		///交易所代码
		TTORATstpSPExchangeIDType	ExchangeID;

		///组合代码
		TTORATstpSPSecurityIDType	SecurityID;

		///组合委托操作标志
		TTORATstpSPOrderActionFlagType	CombOrderActionFlag;

		///撤单状态
		TTORATstpSPCancelOrderStatusType	CancelOrderStatus;

		///撤单数量
		TTORATstpSPVolumeType	VolumeCanceled;

		///状态信息
		TTORATstpSPStatusMsgType	StatusMsg;

		///系统错误代码
		TTORATstpSPErrorIDType	ErrorID;

		///报单申报用户
		TTORATstpSPUserIDType	InsertUserID;

		///操作日期
		TTORATstpSPDateType	InsertDate;

		///操作时间
		TTORATstpSPTimeType	InsertTime;

		///申报时间(毫秒)
		TTORATstpSPMillisecType	InsertMillisec;

		///内网IP地址
		TTORATstpSPIPAddressType	InnerIPAddress;

		///Mac地址
		TTORATstpSPMacAddressType	MacAddress;

		///请求编号
		TTORATstpSPRequestIDType	RequestID;

		///终端信息
		TTORATstpSPTerminalInfoType	TerminalInfo;

		///长字符串附加信息
		TTORATstpSPBigsInfoType	BInfo;

		///短字符串附加信息
		TTORATstpSPShortsInfoType	SInfo;

		///整形附加信息
		TTORATstpSPIntInfoType	IInfo;

		///委托方式
		TTORATstpSPOperwayType	Operway;

		///硬盘序列号
		TTORATstpSPHDSerialType	HDSerial;

		///移动设备手机号
		TTORATstpSPMobileType	Mobile;

		///外网IP地址
		TTORATstpSPIPAddressType	OuterIPAddress;

		///外网端口号
		TTORATstpSPPortType	OuterPort;

	};

	/// 查询组合委托
	struct CTORATstpSPQryCombOrderField
	{
		 
		///投资者代码
		TTORATstpSPInvestorIDType	InvestorID;

		///组合合约代码
		TTORATstpSPSecurityIDType	SecurityID;

		///交易所代码
		TTORATstpSPExchangeIDType	ExchangeID;

		///交易所下的交易市场，如沪A、沪B市场
		TTORATstpSPMarketIDType	MarketID;

		///客户在系统中的编号，编号唯一且遵循交易所制定的编码规则
		TTORATstpSPShareholderIDType	ShareholderID;

		///组合系统编号
		TTORATstpSPOrderSysIDType	CombOrderSysID;

		///Time
		TTORATstpSPTimeType	InsertTimeStart;

		///Time
		TTORATstpSPTimeType	InsertTimeEnd;

		///投资单元代码
		TTORATstpSPBusinessUnitIDType	BusinessUnitID;

		///组合策略
		TTORATstpSPCombinationStrategyType	CombinationStrategy;

		///组合报单类别
		TTORATstpSPCombDirectionType	CombDirection;

		///长字符串附加信息
		TTORATstpSPBigsInfoType	BInfo;

		///短字符串附加信息
		TTORATstpSPShortsInfoType	SInfo;

		///整形附加信息
		TTORATstpSPIntInfoType	IInfo;

	};

	/// 查询投资者组合持仓
	struct CTORATstpSPQryCombPositionField
	{
		 
		///投资者代码
		TTORATstpSPInvestorIDType	InvestorID;

		///组合证券代码(A&B)
		TTORATstpSPSecurityIDType	SecurityID;

		///交易所代码
		TTORATstpSPExchangeIDType	ExchangeID;

		///交易所下的交易市场，如沪A、沪B市场
		TTORATstpSPMarketIDType	MarketID;

		///交易账户代码
		TTORATstpSPShareholderIDType	ShareholderID;

		///投资单元代码
		TTORATstpSPBusinessUnitIDType	BusinessUnitID;

		///组合策略(CNSJC/CXSJC/PXSJC/PNSJC/KS/KKS/ZBD)
		TTORATstpSPCombinationStrategyType	CombinationStrategy;

	};

	/// 投资者组合持仓
	struct CTORATstpSPCombPositionField
	{
		 
		///投资者代码
		TTORATstpSPInvestorIDType	InvestorID;

		///投资单元代码
		TTORATstpSPBusinessUnitIDType	BusinessUnitID;

		///市场代码
		TTORATstpSPMarketIDType	MarketID;

		///客户代码
		TTORATstpSPShareholderIDType	ShareholderID;

		///交易日
		TTORATstpSPDateType	TradingDay;

		///交易所代码
		TTORATstpSPExchangeIDType	ExchangeID;

		///组合证券代码
		TTORATstpSPSecurityIDType	SecurityID;

		///组合策略
		TTORATstpSPCombinationStrategyType	CombinationStrategy;

		///昨日持仓
		TTORATstpSPVolumeType	HistoryPos;

		///昨日持仓冻结
		TTORATstpSPVolumeType	HistoryPosFrozen;

		///今日买卖持仓
		TTORATstpSPVolumeType	TodayPos;

		///今日买卖持仓冻结
		TTORATstpSPVolumeType	TodayPosFrozen;

		///占用的保证金
		TTORATstpSPMoneyType	Margin;

		///冻结的保证金
		TTORATstpSPMoneyType	FrozenMargin;

		///冻结的手续费
		TTORATstpSPMoneyType	FrozenCommission;

		///手续费
		TTORATstpSPMoneyType	Commission;

		///上次余额(盘中不变)
		TTORATstpSPVolumeType	PrePosition;

	};

	/// 查询投资者组合持仓明细
	struct CTORATstpSPQryCombPosDetailField
	{
		 
		///投资者代码
		TTORATstpSPInvestorIDType	InvestorID;

		///组合合约代码
		TTORATstpSPSecurityIDType	CombSecurityID;

		///交易所代码
		TTORATstpSPExchangeIDType	ExchangeID;

		///市场代码
		TTORATstpSPMarketIDType	MarketID;

		///交易账户代码
		TTORATstpSPShareholderIDType	ShareholderID;

		///投资单元代码
		TTORATstpSPBusinessUnitIDType	BusinessUnitID;

		///组合策略
		TTORATstpSPCombinationStrategyType	CombinationStrategy;

		///交易所组合编码
		TTORATstpSPExchangeCombIDType	ExchangeCombID;

		///组合状态
		TTORATstpSPCombinationStatusType	CombinationStatus;

	};

	/// 投资者组合持仓明细
	struct CTORATstpSPCombPosDetailField
	{
		 
		///交易日
		TTORATstpSPDateType	TradingDay;

		///交易所组合编码
		TTORATstpSPExchangeCombIDType	ExchangeCombID;

		///组合策略
		TTORATstpSPCombinationStrategyType	CombinationStrategy;

		///组合证券代码
		TTORATstpSPSecurityIDType	CombSecurityID;

		///经纪公司部门代码
		TTORATstpSPDepartmentIDType	DepartmentID;

		///投资者代码
		TTORATstpSPInvestorIDType	InvestorID;

		///投资单元代码
		TTORATstpSPBusinessUnitIDType	BusinessUnitID;

		///市场代码
		TTORATstpSPMarketIDType	MarketID;

		///客户代码
		TTORATstpSPShareholderIDType	ShareholderID;

		///交易所代码
		TTORATstpSPExchangeIDType	ExchangeID;

		///昨日持仓
		TTORATstpSPVolumeType	HistoryPos;

		///今日买卖持仓
		TTORATstpSPVolumeType	TodayPos;

		///组合时期
		TTORATstpSPDateType	TradeDate;

		///组合时间
		TTORATstpSPTimeType	TradeTime;

		///组合状态
		TTORATstpSPCombinationStatusType	CombinationStatus;

		///成份合约个数，最多四条腿
		TTORATstpSPRecordCntType	NoLegs;

		///第一腿合约代码
		TTORATstpSPSecurityIDType	Leg1SecurityID;

		///第一腿昨日组合数量
		TTORATstpSPVolumeType	Leg1HistoryPos;

		///第一腿今日组合数量
		TTORATstpSPVolumeType	Leg1TodayPos;

		///第一腿持仓方向
		TTORATstpSPPosiDirectionType	Leg1PosiDirection;

		///第一腿期权类型
		TTORATstpSPOptionsTypeType	Leg1OptionsType;

		///第二腿合约代码
		TTORATstpSPSecurityIDType	Leg2SecurityID;

		///第二腿昨日组合数量
		TTORATstpSPVolumeType	Leg2HistoryPos;

		///第二腿今日组合数量
		TTORATstpSPVolumeType	Leg2TodayPos;

		///第二腿持仓方向
		TTORATstpSPPosiDirectionType	Leg2PosiDirection;

		///第二腿期权类型
		TTORATstpSPOptionsTypeType	Leg2OptionsType;

		///拆分冻结的昨日组合数量
		TTORATstpSPVolumeType	HistoryPosSplitFrozen;

		///拆分冻结的今日组合数量
		TTORATstpSPVolumeType	TodayPosSplitFrozen;

		///拆分冻结的第一腿昨日组合数量
		TTORATstpSPVolumeType	Leg1HistoryPosSplitFrozen;

		///拆分冻结的第一腿今日组合数量
		TTORATstpSPVolumeType	Leg1TodayPosSplitFrozen;

		///拆分冻结的第二腿昨日组合数量
		TTORATstpSPVolumeType	Leg2HistoryPosSplitFrozen;

		///拆分冻结的第二腿今日组合数量
		TTORATstpSPVolumeType	Leg2TodayPosSplitFrozen;

	};

	/// 查询行权指派明细
	struct CTORATstpSPQryExerciseAppointmentField
	{
		 
		///投资者代码
		TTORATstpSPInvestorIDType	InvestorID;

		///投资单元代码
		TTORATstpSPBusinessUnitIDType	BusinessUnitID;

		///交易所代码
		TTORATstpSPExchangeIDType	ExchangeID;

		///行权日期
		TTORATstpSPDateType	ExerciseDay;

		///交易单元代码
		TTORATstpSPPbuIDType	PbuID;

		///客户在系统中的编号，编号唯一且遵循交易所制定的编码规则
		TTORATstpSPShareholderIDType	ShareholderID;

		///资金账户
		TTORATstpSPAccountIDType	AccountID;

		///合约在系统中的编号
		TTORATstpSPSecurityIDType	SecurityID;

	};

	/// 行权指派明细
	struct CTORATstpSPExerciseAppointmentField
	{
		 
		///投资者行权指派明细
		TTORATstpSPInvestorIDType	InvestorID;

		///投资单元代码
		TTORATstpSPBusinessUnitIDType	BusinessUnitID;

		///交易所代码
		TTORATstpSPExchangeIDType	ExchangeID;

		///行权日期
		TTORATstpSPDateType	ExerciseDay;

		///交易所交易单元代码
		TTORATstpSPPbuIDType	PbuID;

		///股东账户代码
		TTORATstpSPShareholderIDType	ShareholderID;

		///资金账户代码
		TTORATstpSPAccountIDType	AccountID;

		///币种
		TTORATstpSPCurrencyIDType	CurrencyID;

		///合约代码
		TTORATstpSPSecurityIDType	SecurityID;

		///期权类型
		TTORATstpSPOptionsTypeType	OptionsType;

		///合约单位
		TTORATstpSPVolumeType	OptionUnit;

		///标的证券代码
		TTORATstpSPSecurityIDType	UnderlyingSecurityID;

		///行权数量
		TTORATstpSPVolumeType	ExerciseVolume;

		///行权价
		TTORATstpSPMoneyType	ExercisePrice;

		///行权方向
		TTORATstpSPExerciseDirectionType	ExerciseDirection;

		///备兑标志
		TTORATstpSPCoverFlagType	CoverFlag;

	};

	/// 查询备兑股份不足仓位
	struct CTORATstpSPQryInsufficientCoveredStockPositionField
	{
		 
		///投资者代码
		TTORATstpSPInvestorIDType	InvestorID;

		///标的证券代码
		TTORATstpSPSecurityIDType	SecurityID;

		///交易所代码
		TTORATstpSPExchangeIDType	ExchangeID;

		///市场代码
		TTORATstpSPMarketIDType	MarketID;

		///目前该字段存放的是上证所和深圳的股东代码。
		TTORATstpSPShareholderIDType	ShareholderID;

		///投资单元代码
		TTORATstpSPBusinessUnitIDType	BusinessUnitID;

	};

	/// 备兑股份不足仓位
	struct CTORATstpSPInsufficientCoveredStockPositionField
	{
		 
		///投资者代码
		TTORATstpSPInvestorIDType	InvestorID;

		///投资单元代码
		TTORATstpSPBusinessUnitIDType	BusinessUnitID;

		///市场代码
		TTORATstpSPMarketIDType	MarketID;

		///客户代码
		TTORATstpSPShareholderIDType	ShareholderID;

		///交易日
		TTORATstpSPDateType	TradingDay;

		///交易所代码
		TTORATstpSPExchangeIDType	ExchangeID;

		///证券代码
		TTORATstpSPSecurityIDType	SecurityID;

		///初始备兑股份不足数量
		TTORATstpSPVolumeType	TotalInsufficientVolume;

		///初始备兑股份预冻结数量
		TTORATstpSPVolumeType	PreFrozenVolume;

		///备兑平仓已偿还的备兑股份数量
		TTORATstpSPVolumeType	RepaidVolume;

	};

	/// 查询组合合约信息
	struct CTORATstpSPQryCombSecurityField
	{
		 
		///组合合约代码
		TTORATstpSPSecurityIDType	CombSecurityID;

		///交易所代码
		TTORATstpSPExchangeIDType	ExchangeID;

		///组合策略
		TTORATstpSPCombinationStrategyType	CombinationStrategy;

	};

	/// 组合合约信息
	struct CTORATstpSPCombSecurityField
	{
		 
		///交易所代码
		TTORATstpSPExchangeIDType	ExchangeID;

		///组合合约代码
		TTORATstpSPSecurityIDType	CombSecurityID;

		///组合策略
		TTORATstpSPCombinationStrategyType	CombinationStrategy;

		///成分一合约代码
		TTORATstpSPSecurityIDType	Leg1SecurityID;

		///成分一合约名称
		TTORATstpSPSecurityNameType	Leg1SecurityName;

		///策略要求的成分一合约多空方向
		TTORATstpSPPosiDirectionType	RequiredLeg1PosiDirection;

		///成分二合约代码
		TTORATstpSPSecurityIDType	Leg2SecurityID;

		///成分二合约名称
		TTORATstpSPSecurityNameType	Leg2SecurityName;

		///策略要求的成分二合约多空方向
		TTORATstpSPPosiDirectionType	RequiredLeg2PosiDirection;

	};

	/// 查询组合行权委托
	struct CTORATstpSPQryCombExerciseField
	{
		 
		///投资者代码
		TTORATstpSPInvestorIDType	InvestorID;

		///认购合约代码
		TTORATstpSPSecurityIDType	CallSecurityID;

		///认沽合约代码
		TTORATstpSPSecurityIDType	PutSecurityID;

		///交易所代码
		TTORATstpSPExchangeIDType	ExchangeID;

		///市场代码
		TTORATstpSPMarketIDType	MarketID;

		///目前该字段存放的是上证所和深圳的股东代码。
		TTORATstpSPShareholderIDType	ShareholderID;

		///系统合并行权编号
		TTORATstpSPOrderSysIDType	CombExerciseSysID;

		///Time
		TTORATstpSPTimeType	InsertTimeStart;

		///Time
		TTORATstpSPTimeType	InsertTimeEnd;

		///投资单元代码
		TTORATstpSPBusinessUnitIDType	BusinessUnitID;

		///长字符串附加信息
		TTORATstpSPBigsInfoType	BInfo;

		///短字符串附加信息
		TTORATstpSPShortsInfoType	SInfo;

		///整形附加信息
		TTORATstpSPIntInfoType	IInfo;

	};

	/// 查询合并行权撤单
	struct CTORATstpSPQryCombExerciseActionField
	{
		 
		///投资者代码
		TTORATstpSPInvestorIDType	InvestorID;

		///交易所代码
		TTORATstpSPExchangeIDType	ExchangeID;

		///交易所下的交易市场，如沪A、沪B市场
		TTORATstpSPMarketIDType	MarketID;

		///目前该字段存放的是上证所和深圳的股东代码。
		TTORATstpSPShareholderIDType	ShareholderID;

		///投资单元代码
		TTORATstpSPBusinessUnitIDType	BusinessUnitID;

		///交易单元代码
		TTORATstpSPPbuIDType	PbuID;

		///本地组合行权撤单编号
		TTORATstpSPOrderLocalIDType	CancelCombExerciseLocalID;

		///本地合并行权编号
		TTORATstpSPOrderLocalIDType	CombExerciseLocalID;

		///长字符串附加信息
		TTORATstpSPBigsInfoType	BInfo;

		///短字符串附加信息
		TTORATstpSPShortsInfoType	SInfo;

		///整形附加信息
		TTORATstpSPIntInfoType	IInfo;

	};

	/// 合并行权撤单
	struct CTORATstpSPCombExerciseActionField
	{
		 
		///交易日
		TTORATstpSPDateType	TradingDay;

		///交易所营业部编码
		TTORATstpSPBranchIDType	BranchID;

		///交易所交易单元代码
		TTORATstpSPPbuIDType	PbuID;

		///本地合并行权撤单编号
		TTORATstpSPOrderLocalIDType	CancelCombExerciseLocalID;

		///撤单前置编号
		TTORATstpSPFrontIDType	ActionFrontID;

		///撤单会话编号
		TTORATstpSPSessionIDType	ActionSessionID;

		///合并行权撤单引用
		TTORATstpSPOrderRefType	CombExerciseActionRef;

		///被撤本地合并行权报单编号
		TTORATstpSPOrderLocalIDType	CombExerciseLocalID;

		///被撤系统合并行权报单编号
		TTORATstpSPOrderSysIDType	CombExerciseSysID;

		///前置编号
		TTORATstpSPFrontIDType	FrontID;

		///会话编号
		TTORATstpSPSessionIDType	SessionID;

		///合并行权引用
		TTORATstpSPOrderRefType	CombExerciseRef;

		///投资者代码
		TTORATstpSPInvestorIDType	InvestorID;

		///投资单元代码
		TTORATstpSPBusinessUnitIDType	BusinessUnitID;

		///市场代码
		TTORATstpSPMarketIDType	MarketID;

		///股东账户代码
		TTORATstpSPShareholderIDType	ShareholderID;

		///交易所代码
		TTORATstpSPExchangeIDType	ExchangeID;

		///认购合约代码
		TTORATstpSPSecurityIDType	CallSecurityID;

		///认沽合约代码
		TTORATstpSPSecurityIDType	PutSecurityID;

		///操作标志
		TTORATstpSPOrderActionFlagType	ExerciseActionFlag;

		///撤单状态
		TTORATstpSPCancelOrderStatusType	CancelOrderStatus;

		///撤单数量
		TTORATstpSPVolumeType	VolumeCanceled;

		///状态信息
		TTORATstpSPStatusMsgType	StatusMsg;

		///系统错误代码
		TTORATstpSPErrorIDType	ErrorID;

		///报单申报用户
		TTORATstpSPUserIDType	InsertUserID;

		///操作日期
		TTORATstpSPDateType	InsertDate;

		///操作时间
		TTORATstpSPTimeType	InsertTime;

		///申报时间(毫秒)
		TTORATstpSPMillisecType	InsertMillisec;

		///内网IP地址
		TTORATstpSPIPAddressType	InnerIPAddress;

		///Mac地址
		TTORATstpSPMacAddressType	MacAddress;

		///请求编号
		TTORATstpSPRequestIDType	RequestID;

		///终端信息
		TTORATstpSPTerminalInfoType	TerminalInfo;

		///长字符串附加信息
		TTORATstpSPBigsInfoType	BInfo;

		///短字符串附加信息
		TTORATstpSPShortsInfoType	SInfo;

		///整形附加信息
		TTORATstpSPIntInfoType	IInfo;

		///委托方式
		TTORATstpSPOperwayType	Operway;

		///硬盘序列号
		TTORATstpSPHDSerialType	HDSerial;

		///移动设备手机号
		TTORATstpSPMobileType	Mobile;

		///外网IP地址
		TTORATstpSPIPAddressType	OuterIPAddress;

		///外网端口号
		TTORATstpSPPortType	OuterPort;

	};

}
#endif