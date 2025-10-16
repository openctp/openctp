/////////////////////////////////////////////////////////////////////////
///@system ��һ��������ϵͳ
///@company �Ϻ��ڻ���Ϣ�������޹�˾
///@file ThostFtdcUserApiStruct.h
///@brief �����˿ͻ��˽ӿ�ʹ�õ�ҵ�����ݽṹ
///@history 
///20060106	�Ժ��		�������ļ�
/////////////////////////////////////////////////////////////////////////

#if !defined(SOPT_THOST_FTDCSTRUCT_H)
#define SOPT_THOST_FTDCSTRUCT_H

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


#include "ThostFtdcUserApiDataType.h"


namespace ctp_sopt
{
///��Ϣ�ַ�
struct CThostFtdcDisseminationField
{
	///����ϵ�к�
	TThostFtdcSequenceSeriesType	SequenceSeries;
	///���к�
	TThostFtdcSequenceNoType	SequenceNo;
};

///�û���¼����
struct CThostFtdcReqUserLoginField
{
	///������
	TThostFtdcDateType	TradingDay;
	///���͹�˾����
	TThostFtdcBrokerIDType	BrokerID;
	///�û�����
	TThostFtdcUserIDType	UserID;
	///����
	TThostFtdcPasswordType	Password;
	///�û��˲�Ʒ��Ϣ
	TThostFtdcProductInfoType	UserProductInfo;
	///�ӿڶ˲�Ʒ��Ϣ
	TThostFtdcProductInfoType	InterfaceProductInfo;
	///Э����Ϣ
	TThostFtdcProtocolInfoType	ProtocolInfo;
	///Mac��ַ
	TThostFtdcMacAddressType	MacAddress;
	///��̬����
	TThostFtdcPasswordType	OneTimePassword;
	///��������Ч�ֶ�
	TThostFtdcOldIPAddressType	reserve1;
	///��¼��ע
	TThostFtdcLoginRemarkType	LoginRemark;
	///�ն�IP�˿�
	TThostFtdcIPPortType	ClientIPPort;
	///�ն�IP��ַ
	TThostFtdcIPAddressType	ClientIPAddress;
};

///�û���¼Ӧ��
struct CThostFtdcRspUserLoginField
{
	///������
	TThostFtdcDateType	TradingDay;
	///��¼�ɹ�ʱ��
	TThostFtdcTimeType	LoginTime;
	///���͹�˾����
	TThostFtdcBrokerIDType	BrokerID;
	///�û�����
	TThostFtdcUserIDType	UserID;
	///����ϵͳ����
	TThostFtdcSystemNameType	SystemName;
	///ǰ�ñ��
	TThostFtdcFrontIDType	FrontID;
	///�Ự���
	TThostFtdcSessionIDType	SessionID;
	///��󱨵�����
	TThostFtdcOrderRefType	MaxOrderRef;
	///������ʱ��
	TThostFtdcTimeType	SHFETime;
	///������ʱ��
	TThostFtdcTimeType	DCETime;
	///֣����ʱ��
	TThostFtdcTimeType	CZCETime;
	///�н���ʱ��
	TThostFtdcTimeType	FFEXTime;
	///��Դ����ʱ��
	TThostFtdcTimeType	INETime;
};

///�û��ǳ�����
struct CThostFtdcUserLogoutField
{
	///���͹�˾����
	TThostFtdcBrokerIDType	BrokerID;
	///�û�����
	TThostFtdcUserIDType	UserID;
};

///ǿ�ƽ���Ա�˳�
struct CThostFtdcForceUserLogoutField
{
	///���͹�˾����
	TThostFtdcBrokerIDType	BrokerID;
	///�û�����
	TThostFtdcUserIDType	UserID;
};

///�ͻ�����֤����
struct CThostFtdcReqAuthenticateField
{
	///���͹�˾����
	TThostFtdcBrokerIDType	BrokerID;
	///�û�����
	TThostFtdcUserIDType	UserID;
	///�û��˲�Ʒ��Ϣ
	TThostFtdcProductInfoType	UserProductInfo;
	///��֤��
	TThostFtdcAuthCodeType	AuthCode;
	///App����
	TThostFtdcAppIDType	AppID;
};

///�ͻ�����֤��Ӧ
struct CThostFtdcRspAuthenticateField
{
	///���͹�˾����
	TThostFtdcBrokerIDType	BrokerID;
	///�û�����
	TThostFtdcUserIDType	UserID;
	///�û��˲�Ʒ��Ϣ
	TThostFtdcProductInfoType	UserProductInfo;
	///App����
	TThostFtdcAppIDType	AppID;
	///App����
	TThostFtdcAppTypeType	AppType;
};

///�ͻ�����֤��Ϣ
struct CThostFtdcAuthenticationInfoField
{
	///���͹�˾����
	TThostFtdcBrokerIDType	BrokerID;
	///�û�����
	TThostFtdcUserIDType	UserID;
	///�û��˲�Ʒ��Ϣ
	TThostFtdcProductInfoType	UserProductInfo;
	///��֤��Ϣ
	TThostFtdcAuthInfoType	AuthInfo;
	///�Ƿ�Ϊ��֤���
	TThostFtdcBoolType	IsResult;
	///App����
	TThostFtdcAppIDType	AppID;
	///App����
	TThostFtdcAppTypeType	AppType;
	///�ն�IP��ַ
	TThostFtdcIPAddressType	ClientIPAddress;
};

///��ȫ�û���¼Ӧ��
struct CThostFtdcRspUserLoginSafelyField
{
	///������
	TThostFtdcDateType	TradingDay;
	///��¼�ɹ�ʱ��
	TThostFtdcTimeType	LoginTime;
	///���͹�˾����
	TThostFtdcBrokerIDType	BrokerID;
	///�û�����
	TThostFtdcUserIDType	UserID;
	///����ϵͳ����
	TThostFtdcSystemNameType	SystemName;
	///ǰ�ñ��
	TThostFtdcFrontIDType	FrontID;
	///�Ự���
	TThostFtdcSessionIDType	SessionID;
	///��󱨵�����
	TThostFtdcOrderRefType	MaxOrderRef;
	///������ʱ��
	TThostFtdcTimeType	SHFETime;
	///������ʱ��
	TThostFtdcTimeType	DCETime;
	///֣����ʱ��
	TThostFtdcTimeType	CZCETime;
	///�н���ʱ��
	TThostFtdcTimeType	FFEXTime;
	///��Դ����ʱ��
	TThostFtdcTimeType	INETime;
	///�����
	TThostFtdcRandomStringType	RandomString;
};

///����ת�ʱ���ͷ
struct CThostFtdcTransferHeaderField
{
	///�汾�ţ�������1.0
	TThostFtdcVersionType	Version;
	///���״��룬����
	TThostFtdcTradeCodeType	TradeCode;
	///�������ڣ������ʽ��yyyymmdd
	TThostFtdcTradeDateType	TradeDate;
	///����ʱ�䣬�����ʽ��hhmmss
	TThostFtdcTradeTimeType	TradeTime;
	///������ˮ�ţ�N/A
	TThostFtdcTradeSerialType	TradeSerial;
	///�ڻ���˾���룬����
	TThostFtdcFutureIDType	FutureID;
	///���д��룬���ݲ�ѯ���еõ�������
	TThostFtdcBankIDType	BankID;
	///���з����Ĵ��룬���ݲ�ѯ���еõ�������
	TThostFtdcBankBrchIDType	BankBrchID;
	///����Ա��N/A
	TThostFtdcOperNoType	OperNo;
	///�����豸���ͣ�N/A
	TThostFtdcDeviceIDType	DeviceID;
	///��¼����N/A
	TThostFtdcRecordNumType	RecordNum;
	///�Ự��ţ�N/A
	TThostFtdcSessionIDType	SessionID;
	///�����ţ�N/A
	TThostFtdcRequestIDType	RequestID;
};

///�����ʽ�ת�ڻ�����TradeCode=202001
struct CThostFtdcTransferBankToFutureReqField
{
	///�ڻ��ʽ��˻�
	TThostFtdcAccountIDType	FutureAccount;
	///�����־
	TThostFtdcFuturePwdFlagType	FuturePwdFlag;
	///����
	TThostFtdcFutureAccPwdType	FutureAccPwd;
	///ת�˽��
	TThostFtdcMoneyType	TradeAmt;
	///�ͻ�������
	TThostFtdcMoneyType	CustFee;
	///���֣�RMB-����� USD-��Բ HKD-��Ԫ
	TThostFtdcCurrencyCodeType	CurrencyCode;
};

///�����ʽ�ת�ڻ�������Ӧ
struct CThostFtdcTransferBankToFutureRspField
{
	///��Ӧ����
	TThostFtdcRetCodeType	RetCode;
	///��Ӧ��Ϣ
	TThostFtdcRetInfoType	RetInfo;
	///�ʽ��˻�
	TThostFtdcAccountIDType	FutureAccount;
	///ת�ʽ��
	TThostFtdcMoneyType	TradeAmt;
	///Ӧ�տͻ�������
	TThostFtdcMoneyType	CustFee;
	///����
	TThostFtdcCurrencyCodeType	CurrencyCode;
};

///�ڻ��ʽ�ת��������TradeCode=202002
struct CThostFtdcTransferFutureToBankReqField
{
	///�ڻ��ʽ��˻�
	TThostFtdcAccountIDType	FutureAccount;
	///�����־
	TThostFtdcFuturePwdFlagType	FuturePwdFlag;
	///����
	TThostFtdcFutureAccPwdType	FutureAccPwd;
	///ת�˽��
	TThostFtdcMoneyType	TradeAmt;
	///�ͻ�������
	TThostFtdcMoneyType	CustFee;
	///���֣�RMB-����� USD-��Բ HKD-��Ԫ
	TThostFtdcCurrencyCodeType	CurrencyCode;
};

///�ڻ��ʽ�ת����������Ӧ
struct CThostFtdcTransferFutureToBankRspField
{
	///��Ӧ����
	TThostFtdcRetCodeType	RetCode;
	///��Ӧ��Ϣ
	TThostFtdcRetInfoType	RetInfo;
	///�ʽ��˻�
	TThostFtdcAccountIDType	FutureAccount;
	///ת�ʽ��
	TThostFtdcMoneyType	TradeAmt;
	///Ӧ�տͻ�������
	TThostFtdcMoneyType	CustFee;
	///����
	TThostFtdcCurrencyCodeType	CurrencyCode;
};

///��ѯ�����ʽ�����TradeCode=204002
struct CThostFtdcTransferQryBankReqField
{
	///�ڻ��ʽ��˻�
	TThostFtdcAccountIDType	FutureAccount;
	///�����־
	TThostFtdcFuturePwdFlagType	FuturePwdFlag;
	///����
	TThostFtdcFutureAccPwdType	FutureAccPwd;
	///���֣�RMB-����� USD-��Բ HKD-��Ԫ
	TThostFtdcCurrencyCodeType	CurrencyCode;
};

///��ѯ�����ʽ�������Ӧ
struct CThostFtdcTransferQryBankRspField
{
	///��Ӧ����
	TThostFtdcRetCodeType	RetCode;
	///��Ӧ��Ϣ
	TThostFtdcRetInfoType	RetInfo;
	///�ʽ��˻�
	TThostFtdcAccountIDType	FutureAccount;
	///�������
	TThostFtdcMoneyType	TradeAmt;
	///���п������
	TThostFtdcMoneyType	UseAmt;
	///���п�ȡ���
	TThostFtdcMoneyType	FetchAmt;
	///����
	TThostFtdcCurrencyCodeType	CurrencyCode;
};

///��ѯ���н�����ϸ����TradeCode=204999
struct CThostFtdcTransferQryDetailReqField
{
	///�ڻ��ʽ��˻�
	TThostFtdcAccountIDType	FutureAccount;
};

///��ѯ���н�����ϸ������Ӧ
struct CThostFtdcTransferQryDetailRspField
{
	///��������
	TThostFtdcDateType	TradeDate;
	///����ʱ��
	TThostFtdcTradeTimeType	TradeTime;
	///���״���
	TThostFtdcTradeCodeType	TradeCode;
	///�ڻ���ˮ��
	TThostFtdcTradeSerialNoType	FutureSerial;
	///�ڻ���˾����
	TThostFtdcFutureIDType	FutureID;
	///�ʽ��ʺ�
	TThostFtdcFutureAccountType	FutureAccount;
	///������ˮ��
	TThostFtdcTradeSerialNoType	BankSerial;
	///���д���
	TThostFtdcBankIDType	BankID;
	///���з����Ĵ���
	TThostFtdcBankBrchIDType	BankBrchID;
	///�����˺�
	TThostFtdcBankAccountType	BankAccount;
	///֤������
	TThostFtdcCertCodeType	CertCode;
	///���Ҵ���
	TThostFtdcCurrencyCodeType	CurrencyCode;
	///�������
	TThostFtdcMoneyType	TxAmount;
	///��Ч��־
	TThostFtdcTransferValidFlagType	Flag;
};

///��Ӧ��Ϣ
struct CThostFtdcRspInfoField
{
	///�������
	TThostFtdcErrorIDType	ErrorID;
	///������Ϣ
	TThostFtdcErrorMsgType	ErrorMsg;
};

///������
struct CThostFtdcExchangeField
{
	///����������
	TThostFtdcExchangeIDType	ExchangeID;
	///����������
	TThostFtdcExchangeNameType	ExchangeName;
	///����������
	TThostFtdcExchangePropertyType	ExchangeProperty;
};

///��Ʒ
struct CThostFtdcProductField
{
	///��Ʒ����
	TThostFtdcInstrumentIDType	ProductID;
	///��Ʒ����
	TThostFtdcProductNameType	ProductName;
	///����������
	TThostFtdcExchangeIDType	ExchangeID;
	///��Ʒ����
	TThostFtdcProductClassType	ProductClass;
	///��Լ��������
	TThostFtdcVolumeMultipleType	VolumeMultiple;
	///��С�䶯��λ
	TThostFtdcPriceType	PriceTick;
	///�м۵�����µ���
	TThostFtdcVolumeType	MaxMarketOrderVolume;
	///�м۵���С�µ���
	TThostFtdcVolumeType	MinMarketOrderVolume;
	///�޼۵�����µ���
	TThostFtdcVolumeType	MaxLimitOrderVolume;
	///�޼۵���С�µ���
	TThostFtdcVolumeType	MinLimitOrderVolume;
	///�ֲ�����
	TThostFtdcPositionTypeType	PositionType;
	///�ֲ���������
	TThostFtdcPositionDateTypeType	PositionDateType;
	///ƽ�ִ�������
	TThostFtdcCloseDealTypeType	CloseDealType;
	///���ױ�������
	TThostFtdcCurrencyIDType	TradeCurrencyID;
	///��Ѻ�ʽ���÷�Χ
	TThostFtdcMortgageFundUseRangeType	MortgageFundUseRange;
	///��������Ʒ����
	TThostFtdcInstrumentIDType	ExchangeProductID;
	///��Լ������Ʒ����
	TThostFtdcUnderlyingMultipleType	UnderlyingMultiple;
};

///��Լ
struct CThostFtdcInstrumentField
{
	///��Լ����
	TThostFtdcInstrumentIDType	InstrumentID;
	///����������
	TThostFtdcExchangeIDType	ExchangeID;
	///��Լ����
	TThostFtdcOldInstrumentNameType	OldInstrumentName;
	///��Լ�ڽ������Ĵ���
	TThostFtdcExchangeInstIDType	ExchangeInstID;
	///��Ʒ����
	TThostFtdcInstrumentIDType	ProductID;
	///��Ʒ����
	TThostFtdcProductClassType	ProductClass;
	///�������
	TThostFtdcYearType	DeliveryYear;
	///������
	TThostFtdcMonthType	DeliveryMonth;
	///�м۵�����µ���
	TThostFtdcVolumeType	MaxMarketOrderVolume;
	///�м۵���С�µ���
	TThostFtdcVolumeType	MinMarketOrderVolume;
	///�޼۵�����µ���
	TThostFtdcVolumeType	MaxLimitOrderVolume;
	///�޼۵���С�µ���
	TThostFtdcVolumeType	MinLimitOrderVolume;
	///��Լ��������
	TThostFtdcVolumeMultipleType	VolumeMultiple;
	///��С�䶯��λ
	TThostFtdcPriceType	PriceTick;
	///������
	TThostFtdcDateType	CreateDate;
	///������
	TThostFtdcDateType	OpenDate;
	///������
	TThostFtdcDateType	ExpireDate;
	///��ʼ������
	TThostFtdcDateType	StartDelivDate;
	///����������
	TThostFtdcDateType	EndDelivDate;
	///��Լ��������״̬
	TThostFtdcInstLifePhaseType	InstLifePhase;
	///��ǰ�Ƿ���
	TThostFtdcBoolType	IsTrading;
	///�ֲ�����
	TThostFtdcPositionTypeType	PositionType;
	///�ֲ���������
	TThostFtdcPositionDateTypeType	PositionDateType;
	///��ͷ��֤����
	TThostFtdcRatioType	LongMarginRatio;
	///��ͷ��֤����
	TThostFtdcRatioType	ShortMarginRatio;
	///�Ƿ�ʹ�ô��߱�֤���㷨
	TThostFtdcMaxMarginSideAlgorithmType	MaxMarginSideAlgorithm;
	///������Ʒ����
	TThostFtdcInstrumentIDType	UnderlyingInstrID;
	///ִ�м�
	TThostFtdcPriceType	StrikePrice;
	///��Ȩ����
	TThostFtdcOptionsTypeType	OptionsType;
	///��Լ������Ʒ����
	TThostFtdcUnderlyingMultipleType	UnderlyingMultiple;
	///�������
	TThostFtdcCombinationTypeType	CombinationType;
	///��С���µ���λ
	TThostFtdcVolumeType	MinBuyVolume;
	///��С���µ���λ
	TThostFtdcVolumeType	MinSellVolume;
	///��Լ��ʶ��
	TThostFtdcInstrumentCodeType	InstrumentCode;
	///��Լ����
	TThostFtdcInstrumentNameType	InstrumentName;
};

///���͹�˾
struct CThostFtdcBrokerField
{
	///���͹�˾����
	TThostFtdcBrokerIDType	BrokerID;
	///���͹�˾���
	TThostFtdcBrokerAbbrType	BrokerAbbr;
	///���͹�˾����
	TThostFtdcBrokerNameType	BrokerName;
	///�Ƿ��Ծ
	TThostFtdcBoolType	IsActive;
};

///����������Ա
struct CThostFtdcTraderField
{
	///����������
	TThostFtdcExchangeIDType	ExchangeID;
	///����������Ա����
	TThostFtdcTraderIDType	TraderID;
	///��Ա����
	TThostFtdcParticipantIDType	ParticipantID;
	///����
	TThostFtdcPasswordType	Password;
	///��װ����
	TThostFtdcInstallCountType	InstallCount;
	///���͹�˾����
	TThostFtdcBrokerIDType	BrokerID;
};

///Ͷ����
struct CThostFtdcInvestorField
{
	///Ͷ���ߴ���
	TThostFtdcInvestorIDType	InvestorID;
	///���͹�˾����
	TThostFtdcBrokerIDType	BrokerID;
	///Ͷ���߷������
	TThostFtdcInvestorIDType	InvestorGroupID;
	///Ͷ��������
	TThostFtdcPartyNameType	InvestorName;
	///֤������
	TThostFtdcIdCardTypeType	IdentifiedCardType;
	///֤������
	TThostFtdcIdentifiedCardNoType	IdentifiedCardNo;
	///�Ƿ��Ծ
	TThostFtdcBoolType	IsActive;
	///��ϵ�绰
	TThostFtdcTelephoneType	Telephone;
	///ͨѶ��ַ
	TThostFtdcAddressType	Address;
	///��������
	TThostFtdcDateType	OpenDate;
	///�ֻ�
	TThostFtdcMobileType	Mobile;
	///��������ģ�����
	TThostFtdcInvestorIDType	CommModelID;
	///��֤����ģ�����
	TThostFtdcInvestorIDType	MarginModelID;
};

///���ױ���
struct CThostFtdcTradingCodeField
{
	///Ͷ���ߴ���
	TThostFtdcInvestorIDType	InvestorID;
	///���͹�˾����
	TThostFtdcBrokerIDType	BrokerID;
	///����������
	TThostFtdcExchangeIDType	ExchangeID;
	///�ͻ�����
	TThostFtdcClientIDType	ClientID;
	///�Ƿ��Ծ
	TThostFtdcBoolType	IsActive;
	///���ױ�������
	TThostFtdcClientIDTypeType	ClientIDType;
	///Ӫҵ�����
	TThostFtdcBranchIDType	BranchID;
	///ҵ������
	TThostFtdcBizTypeType	BizType;
	///Ͷ�ʵ�Ԫ����
	TThostFtdcInvestUnitIDType	InvestUnitID;
};

///��Ա����;��͹�˾������ձ�
struct CThostFtdcPartBrokerField
{
	///���͹�˾����
	TThostFtdcBrokerIDType	BrokerID;
	///����������
	TThostFtdcExchangeIDType	ExchangeID;
	///��Ա����
	TThostFtdcParticipantIDType	ParticipantID;
	///�Ƿ��Ծ
	TThostFtdcBoolType	IsActive;
};

///�����û�
struct CThostFtdcSuperUserField
{
	///�û�����
	TThostFtdcUserIDType	UserID;
	///�û�����
	TThostFtdcUserNameType	UserName;
	///����
	TThostFtdcPasswordType	Password;
	///�Ƿ��Ծ
	TThostFtdcBoolType	IsActive;
};

///�����û�����Ȩ��
struct CThostFtdcSuperUserFunctionField
{
	///�û�����
	TThostFtdcUserIDType	UserID;
	///���ܴ���
	TThostFtdcFunctionCodeType	FunctionCode;
};

///Ͷ������
struct CThostFtdcInvestorGroupField
{
	///���͹�˾����
	TThostFtdcBrokerIDType	BrokerID;
	///Ͷ���߷������
	TThostFtdcInvestorIDType	InvestorGroupID;
	///Ͷ���߷�������
	TThostFtdcInvestorGroupNameType	InvestorGroupName;
};

///�ʽ��˻�
struct CThostFtdcTradingAccountField
{
	///���͹�˾����
	TThostFtdcBrokerIDType	BrokerID;
	///Ͷ�����ʺ�
	TThostFtdcAccountIDType	AccountID;
	///�ϴ���Ѻ���
	TThostFtdcMoneyType	PreMortgage;
	///�ϴ����ö��
	TThostFtdcMoneyType	PreCredit;
	///�ϴδ���
	TThostFtdcMoneyType	PreDeposit;
	///�ϴν���׼����
	TThostFtdcMoneyType	PreBalance;
	///�ϴ�ռ�õı�֤��
	TThostFtdcMoneyType	PreMargin;
	///��Ϣ����
	TThostFtdcMoneyType	InterestBase;
	///��Ϣ����
	TThostFtdcMoneyType	Interest;
	///�����
	TThostFtdcMoneyType	Deposit;
	///������
	TThostFtdcMoneyType	Withdraw;
	///����ı�֤��
	TThostFtdcMoneyType	FrozenMargin;
	///������ʽ�
	TThostFtdcMoneyType	FrozenCash;
	///�����������
	TThostFtdcMoneyType	FrozenCommission;
	///��ǰ��֤���ܶ�
	TThostFtdcMoneyType	CurrMargin;
	///�ʽ���
	TThostFtdcMoneyType	CashIn;
	///������
	TThostFtdcMoneyType	Commission;
	///ƽ��ӯ��
	TThostFtdcMoneyType	CloseProfit;
	///�ֲ�ӯ��
	TThostFtdcMoneyType	PositionProfit;
	///�ڻ�����׼����
	TThostFtdcMoneyType	Balance;
	///�����ʽ�
	TThostFtdcMoneyType	Available;
	///��ȡ�ʽ�
	TThostFtdcMoneyType	WithdrawQuota;
	///����׼����
	TThostFtdcMoneyType	Reserve;
	///������
	TThostFtdcDateType	TradingDay;
	///������
	TThostFtdcSettlementIDType	SettlementID;
	///���ö��
	TThostFtdcMoneyType	Credit;
	///��Ѻ���
	TThostFtdcMoneyType	Mortgage;
	///��������֤��
	TThostFtdcMoneyType	ExchangeMargin;
	///Ͷ���߽��֤��
	TThostFtdcMoneyType	DeliveryMargin;
	///���������֤��
	TThostFtdcMoneyType	ExchangeDeliveryMargin;
	///�����ڻ�����׼����
	TThostFtdcMoneyType	ReserveBalance;
	///���ִ���
	TThostFtdcCurrencyIDType	CurrencyID;
	///�ϴλ���������
	TThostFtdcMoneyType	PreFundMortgageIn;
	///�ϴλ����ʳ����
	TThostFtdcMoneyType	PreFundMortgageOut;
	///����������
	TThostFtdcMoneyType	FundMortgageIn;
	///�����ʳ����
	TThostFtdcMoneyType	FundMortgageOut;
	///������Ѻ���
	TThostFtdcMoneyType	FundMortgageAvailable;
	///����Ѻ���ҽ��
	TThostFtdcMoneyType	MortgageableFund;
	///�����Ʒռ�ñ�֤��
	TThostFtdcMoneyType	SpecProductMargin;
	///�����Ʒ���ᱣ֤��
	TThostFtdcMoneyType	SpecProductFrozenMargin;
	///�����Ʒ������
	TThostFtdcMoneyType	SpecProductCommission;
	///�����Ʒ����������
	TThostFtdcMoneyType	SpecProductFrozenCommission;
	///�����Ʒ�ֲ�ӯ��
	TThostFtdcMoneyType	SpecProductPositionProfit;
	///�����Ʒƽ��ӯ��
	TThostFtdcMoneyType	SpecProductCloseProfit;
	///���ݳֲ�ӯ���㷨����������Ʒ�ֲ�ӯ��
	TThostFtdcMoneyType	SpecProductPositionProfitByAlg;
	///�����Ʒ��������֤��
	TThostFtdcMoneyType	SpecProductExchangeMargin;
	///ҵ������
	TThostFtdcBizTypeType	BizType;
	///��ʱ���㶳����
	TThostFtdcMoneyType	FrozenSwap;
	///ʣ�໻����
	TThostFtdcMoneyType	RemainSwap;
	///��ֵ
	TThostFtdcMoneyType	OptionValue;
};

///Ͷ���ֲ߳�
struct CThostFtdcInvestorPositionField
{
	///��Լ����
	TThostFtdcInstrumentIDType	InstrumentID;
	///���͹�˾����
	TThostFtdcBrokerIDType	BrokerID;
	///Ͷ���ߴ���
	TThostFtdcInvestorIDType	InvestorID;
	///�ֲֶ�շ���
	TThostFtdcPosiDirectionType	PosiDirection;
	///Ͷ���ױ���־
	TThostFtdcHedgeFlagType	HedgeFlag;
	///�ֲ�����
	TThostFtdcPositionDateType	PositionDate;
	///���ճֲ�
	TThostFtdcVolumeType	YdPosition;
	///���ճֲ�
	TThostFtdcVolumeType	Position;
	///��ͷ����
	TThostFtdcVolumeType	LongFrozen;
	///��ͷ����
	TThostFtdcVolumeType	ShortFrozen;
	///���ֶ�����
	TThostFtdcMoneyType	LongFrozenAmount;
	///���ֶ�����
	TThostFtdcMoneyType	ShortFrozenAmount;
	///������
	TThostFtdcVolumeType	OpenVolume;
	///ƽ����
	TThostFtdcVolumeType	CloseVolume;
	///���ֽ��
	TThostFtdcMoneyType	OpenAmount;
	///ƽ�ֽ��
	TThostFtdcMoneyType	CloseAmount;
	///�ֲֳɱ�
	TThostFtdcMoneyType	PositionCost;
	///�ϴ�ռ�õı�֤��
	TThostFtdcMoneyType	PreMargin;
	///ռ�õı�֤��
	TThostFtdcMoneyType	UseMargin;
	///����ı�֤��
	TThostFtdcMoneyType	FrozenMargin;
	///������ʽ�
	TThostFtdcMoneyType	FrozenCash;
	///�����������
	TThostFtdcMoneyType	FrozenCommission;
	///�ʽ���
	TThostFtdcMoneyType	CashIn;
	///������
	TThostFtdcMoneyType	Commission;
	///ƽ��ӯ��
	TThostFtdcMoneyType	CloseProfit;
	///�ֲ�ӯ��
	TThostFtdcMoneyType	PositionProfit;
	///�ϴν����
	TThostFtdcPriceType	PreSettlementPrice;
	///���ν����
	TThostFtdcPriceType	SettlementPrice;
	///������
	TThostFtdcDateType	TradingDay;
	///������
	TThostFtdcSettlementIDType	SettlementID;
	///���ֳɱ�
	TThostFtdcMoneyType	OpenCost;
	///��������֤��
	TThostFtdcMoneyType	ExchangeMargin;
	///��ϳɽ��γɵĳֲ�
	TThostFtdcVolumeType	CombPosition;
	///��϶�ͷ����
	TThostFtdcVolumeType	CombLongFrozen;
	///��Ͽ�ͷ����
	TThostFtdcVolumeType	CombShortFrozen;
	///���ն���ƽ��ӯ��
	TThostFtdcMoneyType	CloseProfitByDate;
	///��ʶԳ�ƽ��ӯ��
	TThostFtdcMoneyType	CloseProfitByTrade;
	///���ճֲ�
	TThostFtdcVolumeType	TodayPosition;
	///��֤����
	TThostFtdcRatioType	MarginRateByMoney;
	///��֤����(������)
	TThostFtdcRatioType	MarginRateByVolume;
	///ִ�ж���
	TThostFtdcVolumeType	StrikeFrozen;
	///ִ�ж�����
	TThostFtdcMoneyType	StrikeFrozenAmount;
	///����ִ�ж���
	TThostFtdcVolumeType	AbandonFrozen;
	///����������
	TThostFtdcExchangeIDType	ExchangeID;
	///ִ�ж�������
	TThostFtdcVolumeType	YdStrikeFrozen;
	///Ͷ�ʵ�Ԫ����
	TThostFtdcInvestUnitIDType	InvestUnitID;
	///��ֵ
	TThostFtdcMoneyType	OptionValue;
};

///��Լ��֤����
struct CThostFtdcInstrumentMarginRateField
{
	///��Լ����
	TThostFtdcInstrumentIDType	InstrumentID;
	///Ͷ���߷�Χ
	TThostFtdcInvestorRangeType	InvestorRange;
	///���͹�˾����
	TThostFtdcBrokerIDType	BrokerID;
	///Ͷ���ߴ���
	TThostFtdcInvestorIDType	InvestorID;
	///Ͷ���ױ���־
	TThostFtdcHedgeFlagType	HedgeFlag;
	///��ͷ��֤����
	TThostFtdcRatioType	LongMarginRatioByMoney;
	///��ͷ��֤���
	TThostFtdcMoneyType	LongMarginRatioByVolume;
	///��ͷ��֤����
	TThostFtdcRatioType	ShortMarginRatioByMoney;
	///��ͷ��֤���
	TThostFtdcMoneyType	ShortMarginRatioByVolume;
	///�Ƿ���Խ�������ȡ
	TThostFtdcBoolType	IsRelative;
	///����������
	TThostFtdcExchangeIDType	ExchangeID;
	///Ͷ�ʵ�Ԫ����
	TThostFtdcInvestUnitIDType	InvestUnitID;
};

///��Լ��������
struct CThostFtdcInstrumentCommissionRateField
{
	///��Լ����
	TThostFtdcInstrumentIDType	InstrumentID;
	///Ͷ���߷�Χ
	TThostFtdcInvestorRangeType	InvestorRange;
	///���͹�˾����
	TThostFtdcBrokerIDType	BrokerID;
	///Ͷ���ߴ���
	TThostFtdcInvestorIDType	InvestorID;
	///������������
	TThostFtdcRatioType	OpenRatioByMoney;
	///����������
	TThostFtdcRatioType	OpenRatioByVolume;
	///ƽ����������
	TThostFtdcRatioType	CloseRatioByMoney;
	///ƽ��������
	TThostFtdcRatioType	CloseRatioByVolume;
	///ƽ����������
	TThostFtdcRatioType	CloseTodayRatioByMoney;
	///ƽ��������
	TThostFtdcRatioType	CloseTodayRatioByVolume;
	///����������
	TThostFtdcExchangeIDType	ExchangeID;
	///ҵ������
	TThostFtdcBizTypeType	BizType;
	///Ͷ�ʵ�Ԫ����
	TThostFtdcInvestUnitIDType	InvestUnitID;
};

///�������
struct CThostFtdcDepthMarketDataField
{
	///������
	TThostFtdcDateType	TradingDay;
	///��Լ����
	TThostFtdcInstrumentIDType	InstrumentID;
	///����������
	TThostFtdcExchangeIDType	ExchangeID;
	///��Լ�ڽ������Ĵ���
	TThostFtdcExchangeInstIDType	ExchangeInstID;
	///���¼�
	TThostFtdcPriceType	LastPrice;
	///�ϴν����
	TThostFtdcPriceType	PreSettlementPrice;
	///������
	TThostFtdcPriceType	PreClosePrice;
	///��ֲ���
	TThostFtdcLargeVolumeType	PreOpenInterest;
	///����
	TThostFtdcPriceType	OpenPrice;
	///��߼�
	TThostFtdcPriceType	HighestPrice;
	///��ͼ�
	TThostFtdcPriceType	LowestPrice;
	///����
	TThostFtdcVolumeType	Volume;
	///�ɽ����
	TThostFtdcMoneyType	Turnover;
	///�ֲ���
	TThostFtdcLargeVolumeType	OpenInterest;
	///������
	TThostFtdcPriceType	ClosePrice;
	///���ν����
	TThostFtdcPriceType	SettlementPrice;
	///��ͣ���
	TThostFtdcPriceType	UpperLimitPrice;
	///��ͣ���
	TThostFtdcPriceType	LowerLimitPrice;
	///����ʵ��
	TThostFtdcRatioType	PreDelta;
	///����ʵ��
	TThostFtdcRatioType	CurrDelta;
	///����޸�ʱ��
	TThostFtdcTimeType	UpdateTime;
	///����޸ĺ���
	TThostFtdcMillisecType	UpdateMillisec;
	///�����һ
	TThostFtdcPriceType	BidPrice1;
	///������һ
	TThostFtdcVolumeType	BidVolume1;
	///������һ
	TThostFtdcPriceType	AskPrice1;
	///������һ
	TThostFtdcVolumeType	AskVolume1;
	///����۶�
	TThostFtdcPriceType	BidPrice2;
	///��������
	TThostFtdcVolumeType	BidVolume2;
	///�����۶�
	TThostFtdcPriceType	AskPrice2;
	///��������
	TThostFtdcVolumeType	AskVolume2;
	///�������
	TThostFtdcPriceType	BidPrice3;
	///��������
	TThostFtdcVolumeType	BidVolume3;
	///��������
	TThostFtdcPriceType	AskPrice3;
	///��������
	TThostFtdcVolumeType	AskVolume3;
	///�������
	TThostFtdcPriceType	BidPrice4;
	///��������
	TThostFtdcVolumeType	BidVolume4;
	///��������
	TThostFtdcPriceType	AskPrice4;
	///��������
	TThostFtdcVolumeType	AskVolume4;
	///�������
	TThostFtdcPriceType	BidPrice5;
	///��������
	TThostFtdcVolumeType	BidVolume5;
	///��������
	TThostFtdcPriceType	AskPrice5;
	///��������
	TThostFtdcVolumeType	AskVolume5;
	///���վ���
	TThostFtdcPriceType	AveragePrice;
	///ҵ������
	TThostFtdcDateType	ActionDay;
	///�۶ϲο���
	TThostFtdcPriceType	CircuitRefPrice;
	///���鷢��ʱ��
	TThostFtdcSendingTimeType	SendingTime;
	///�ɽ�����long long��
	TThostFtdcBigVolumeType	BigVolume;
};

///Ͷ���ߺ�Լ����Ȩ��
struct CThostFtdcInstrumentTradingRightField
{
	///��Լ����
	TThostFtdcInstrumentIDType	InstrumentID;
	///Ͷ���߷�Χ
	TThostFtdcInvestorRangeType	InvestorRange;
	///���͹�˾����
	TThostFtdcBrokerIDType	BrokerID;
	///Ͷ���ߴ���
	TThostFtdcInvestorIDType	InvestorID;
	///����Ȩ��
	TThostFtdcTradingRightType	TradingRight;
	///����������
	TThostFtdcExchangeIDType	ExchangeID;
	///ҵ������
	TThostFtdcBizTypeType	BizType;
};

///���͹�˾�û�
struct CThostFtdcBrokerUserField
{
	///���͹�˾����
	TThostFtdcBrokerIDType	BrokerID;
	///�û�����
	TThostFtdcUserIDType	UserID;
	///�û�����
	TThostFtdcUserNameType	UserName;
	///�û�����
	TThostFtdcUserTypeType	UserType;
	///�Ƿ��Ծ
	TThostFtdcBoolType	IsActive;
	///�Ƿ�ʹ������
	TThostFtdcBoolType	IsUsingOTP;
	///�Ƿ�ǿ���ն���֤
	TThostFtdcBoolType	IsAuthForce;
};

///���͹�˾�û�����
struct CThostFtdcBrokerUserPasswordField
{
	///���͹�˾����
	TThostFtdcBrokerIDType	BrokerID;
	///�û�����
	TThostFtdcUserIDType	UserID;
	///����
	TThostFtdcPasswordType	Password;
	///�ϴ��޸�ʱ��
	TThostFtdcDateTimeType	LastUpdateTime;
	///�ϴε�½ʱ��
	TThostFtdcDateTimeType	LastLoginTime;
	///�������ʱ��
	TThostFtdcDateType	ExpireDate;
	///���������ʱ��
	TThostFtdcDateType	WeakExpireDate;
};

///���͹�˾�û�����Ȩ��
struct CThostFtdcBrokerUserFunctionField
{
	///���͹�˾����
	TThostFtdcBrokerIDType	BrokerID;
	///�û�����
	TThostFtdcUserIDType	UserID;
	///���͹�˾���ܴ���
	TThostFtdcBrokerFunctionCodeType	BrokerFunctionCode;
};

///����������Ա���̻�
struct CThostFtdcTraderOfferField
{
	///����������
	TThostFtdcExchangeIDType	ExchangeID;
	///����������Ա����
	TThostFtdcTraderIDType	TraderID;
	///��Ա����
	TThostFtdcParticipantIDType	ParticipantID;
	///����
	TThostFtdcPasswordType	Password;
	///��װ���
	TThostFtdcInstallIDType	InstallID;
	///���ر������
	TThostFtdcOrderLocalIDType	OrderLocalID;
	///����������Ա����״̬
	TThostFtdcTraderConnectStatusType	TraderConnectStatus;
	///�����������������
	TThostFtdcDateType	ConnectRequestDate;
	///�������������ʱ��
	TThostFtdcTimeType	ConnectRequestTime;
	///�ϴα�������
	TThostFtdcDateType	LastReportDate;
	///�ϴα���ʱ��
	TThostFtdcTimeType	LastReportTime;
	///�����������
	TThostFtdcDateType	ConnectDate;
	///�������ʱ��
	TThostFtdcTimeType	ConnectTime;
	///��������
	TThostFtdcDateType	StartDate;
	///����ʱ��
	TThostFtdcTimeType	StartTime;
	///������
	TThostFtdcDateType	TradingDay;
	///���͹�˾����
	TThostFtdcBrokerIDType	BrokerID;
	///��ϯλ���ɽ����
	TThostFtdcTradeIDType	MaxTradeID;
	///��ϯλ��󱨵�����
	TThostFtdcReturnCodeType	MaxOrderMessageReference;
	///ҵ������
	TThostFtdcBizTypeType	BizType;
	///PBU���
	TThostFtdcPbuSequenceIDType	PbuSequenceID;
};

///Ͷ���߽�����
struct CThostFtdcSettlementInfoField
{
	///������
	TThostFtdcDateType	TradingDay;
	///������
	TThostFtdcSettlementIDType	SettlementID;
	///���͹�˾����
	TThostFtdcBrokerIDType	BrokerID;
	///Ͷ���ߴ���
	TThostFtdcInvestorIDType	InvestorID;
	///���
	TThostFtdcSequenceNoType	SequenceNo;
	///��Ϣ����
	TThostFtdcContentType	Content;
	///Ͷ�����ʺ�
	TThostFtdcAccountIDType	AccountID;
	///���ִ���
	TThostFtdcCurrencyIDType	CurrencyID;
};

///��Լ��֤���ʵ���
struct CThostFtdcInstrumentMarginRateAdjustField
{
	///��Լ����
	TThostFtdcInstrumentIDType	InstrumentID;
	///Ͷ���߷�Χ
	TThostFtdcInvestorRangeType	InvestorRange;
	///���͹�˾����
	TThostFtdcBrokerIDType	BrokerID;
	///Ͷ���ߴ���
	TThostFtdcInvestorIDType	InvestorID;
	///Ͷ���ױ���־
	TThostFtdcHedgeFlagType	HedgeFlag;
	///��ͷ��֤����
	TThostFtdcRatioType	LongMarginRatioByMoney;
	///��ͷ��֤���
	TThostFtdcMoneyType	LongMarginRatioByVolume;
	///��ͷ��֤����
	TThostFtdcRatioType	ShortMarginRatioByMoney;
	///��ͷ��֤���
	TThostFtdcMoneyType	ShortMarginRatioByVolume;
	///�Ƿ���Խ�������ȡ
	TThostFtdcBoolType	IsRelative;
};

///��������֤����
struct CThostFtdcExchangeMarginRateField
{
	///���͹�˾����
	TThostFtdcBrokerIDType	BrokerID;
	///��Լ����
	TThostFtdcInstrumentIDType	InstrumentID;
	///Ͷ���ױ���־
	TThostFtdcHedgeFlagType	HedgeFlag;
	///��ͷ��֤����
	TThostFtdcRatioType	LongMarginRatioByMoney;
	///��ͷ��֤���
	TThostFtdcMoneyType	LongMarginRatioByVolume;
	///��ͷ��֤����
	TThostFtdcRatioType	ShortMarginRatioByMoney;
	///��ͷ��֤���
	TThostFtdcMoneyType	ShortMarginRatioByVolume;
	///����������
	TThostFtdcExchangeIDType	ExchangeID;
};

///��������֤���ʵ���
struct CThostFtdcExchangeMarginRateAdjustField
{
	///���͹�˾����
	TThostFtdcBrokerIDType	BrokerID;
	///��Լ����
	TThostFtdcInstrumentIDType	InstrumentID;
	///Ͷ���ױ���־
	TThostFtdcHedgeFlagType	HedgeFlag;
	///���潻����Ͷ���߶�ͷ��֤����
	TThostFtdcRatioType	LongMarginRatioByMoney;
	///���潻����Ͷ���߶�ͷ��֤���
	TThostFtdcMoneyType	LongMarginRatioByVolume;
	///���潻����Ͷ���߿�ͷ��֤����
	TThostFtdcRatioType	ShortMarginRatioByMoney;
	///���潻����Ͷ���߿�ͷ��֤���
	TThostFtdcMoneyType	ShortMarginRatioByVolume;
	///��������ͷ��֤����
	TThostFtdcRatioType	ExchLongMarginRatioByMoney;
	///��������ͷ��֤���
	TThostFtdcMoneyType	ExchLongMarginRatioByVolume;
	///��������ͷ��֤����
	TThostFtdcRatioType	ExchShortMarginRatioByMoney;
	///��������ͷ��֤���
	TThostFtdcMoneyType	ExchShortMarginRatioByVolume;
	///�����潻����Ͷ���߶�ͷ��֤����
	TThostFtdcRatioType	NoLongMarginRatioByMoney;
	///�����潻����Ͷ���߶�ͷ��֤���
	TThostFtdcMoneyType	NoLongMarginRatioByVolume;
	///�����潻����Ͷ���߿�ͷ��֤����
	TThostFtdcRatioType	NoShortMarginRatioByMoney;
	///�����潻����Ͷ���߿�ͷ��֤���
	TThostFtdcMoneyType	NoShortMarginRatioByVolume;
};

///����
struct CThostFtdcExchangeRateField
{
	///���͹�˾����
	TThostFtdcBrokerIDType	BrokerID;
	///Դ����
	TThostFtdcCurrencyIDType	FromCurrencyID;
	///Դ���ֵ�λ����
	TThostFtdcCurrencyUnitType	FromCurrencyUnit;
	///Ŀ�����
	TThostFtdcCurrencyIDType	ToCurrencyID;
	///����
	TThostFtdcExchangeRateType	ExchangeRate;
};

///��������
struct CThostFtdcSettlementRefField
{
	///������
	TThostFtdcDateType	TradingDay;
	///������
	TThostFtdcSettlementIDType	SettlementID;
};

///��ǰʱ��
struct CThostFtdcCurrentTimeField
{
	///��ǰ����
	TThostFtdcDateType	CurrDate;
	///��ǰʱ��
	TThostFtdcTimeType	CurrTime;
	///��ǰʱ�䣨���룩
	TThostFtdcMillisecType	CurrMillisec;
	///ҵ������
	TThostFtdcDateType	ActionDay;
};

///ͨѶ�׶�
struct CThostFtdcCommPhaseField
{
	///������
	TThostFtdcDateType	TradingDay;
	///ͨѶʱ�α��
	TThostFtdcCommPhaseNoType	CommPhaseNo;
	///ϵͳ���
	TThostFtdcSystemIDType	SystemID;
};

///��¼��Ϣ
struct CThostFtdcLoginInfoField
{
	///ǰ�ñ��
	TThostFtdcFrontIDType	FrontID;
	///�Ự���
	TThostFtdcSessionIDType	SessionID;
	///���͹�˾����
	TThostFtdcBrokerIDType	BrokerID;
	///�û�����
	TThostFtdcUserIDType	UserID;
	///��¼����
	TThostFtdcDateType	LoginDate;
	///��¼ʱ��
	TThostFtdcTimeType	LoginTime;
	///��������Ч�ֶ�
	TThostFtdcOldIPAddressType	reserve1;
	///�û��˲�Ʒ��Ϣ
	TThostFtdcProductInfoType	UserProductInfo;
	///�ӿڶ˲�Ʒ��Ϣ
	TThostFtdcProductInfoType	InterfaceProductInfo;
	///Э����Ϣ
	TThostFtdcProtocolInfoType	ProtocolInfo;
	///ϵͳ����
	TThostFtdcSystemNameType	SystemName;
	///����,������
	TThostFtdcPasswordType	PasswordDeprecated;
	///��󱨵�����
	TThostFtdcOrderRefType	MaxOrderRef;
	///������ʱ��
	TThostFtdcTimeType	SHFETime;
	///������ʱ��
	TThostFtdcTimeType	DCETime;
	///֣����ʱ��
	TThostFtdcTimeType	CZCETime;
	///�н���ʱ��
	TThostFtdcTimeType	FFEXTime;
	///Mac��ַ
	TThostFtdcMacAddressType	MacAddress;
	///��̬����
	TThostFtdcPasswordType	OneTimePassword;
	///��Դ����ʱ��
	TThostFtdcTimeType	INETime;
	///��ѯʱ�Ƿ���Ҫ����
	TThostFtdcBoolType	IsQryControl;
	///��¼��ע
	TThostFtdcLoginRemarkType	LoginRemark;
	///������֤��
	TThostFtdcSmsCodeType	SmsCode;
	///�����������,0�����ܣ�1������ܣ�2�򵥼���
	TThostFtdcPasswordEncryptTypeType	EncryptType;
	///IP��ַ
	TThostFtdcIPAddressType	IPAddress;
};

///��¼��Ϣ
struct CThostFtdcLogoutAllField
{
	///ǰ�ñ��
	TThostFtdcFrontIDType	FrontID;
	///�Ự���
	TThostFtdcSessionIDType	SessionID;
	///ϵͳ����
	TThostFtdcSystemNameType	SystemName;
};

///ǰ��״̬
struct CThostFtdcFrontStatusField
{
	///ǰ�ñ��
	TThostFtdcFrontIDType	FrontID;
	///�ϴα�������
	TThostFtdcDateType	LastReportDate;
	///�ϴα���ʱ��
	TThostFtdcTimeType	LastReportTime;
	///�Ƿ��Ծ
	TThostFtdcBoolType	IsActive;
};

///�û�������
struct CThostFtdcUserPasswordUpdateField
{
	///���͹�˾����
	TThostFtdcBrokerIDType	BrokerID;
	///�û�����
	TThostFtdcUserIDType	UserID;
	///ԭ���Ŀ���
	TThostFtdcPasswordType	OldPassword;
	///�µĿ���
	TThostFtdcPasswordType	NewPassword;
	///��������
	TThostFtdcPasswordEncryptTypeType	EncryptType;
};

///���뱨��
struct CThostFtdcInputOrderField
{
	///���͹�˾����
	TThostFtdcBrokerIDType	BrokerID;
	///Ͷ���ߴ���
	TThostFtdcInvestorIDType	InvestorID;
	///��Լ����
	TThostFtdcInstrumentIDType	InstrumentID;
	///��������
	TThostFtdcOrderRefType	OrderRef;
	///�û�����
	TThostFtdcUserIDType	UserID;
	///�����۸�����
	TThostFtdcOrderPriceTypeType	OrderPriceType;
	///��������
	TThostFtdcDirectionType	Direction;
	///��Ͽ�ƽ��־
	TThostFtdcCombOffsetFlagType	CombOffsetFlag;
	///���Ͷ���ױ���־
	TThostFtdcCombHedgeFlagType	CombHedgeFlag;
	///�۸�
	TThostFtdcPriceType	LimitPrice;
	///����
	TThostFtdcVolumeType	VolumeTotalOriginal;
	///��Ч������
	TThostFtdcTimeConditionType	TimeCondition;
	///GTD����
	TThostFtdcDateType	GTDDate;
	///�ɽ�������
	TThostFtdcVolumeConditionType	VolumeCondition;
	///��С�ɽ���
	TThostFtdcVolumeType	MinVolume;
	///��������
	TThostFtdcContingentConditionType	ContingentCondition;
	///ֹ���
	TThostFtdcPriceType	StopPrice;
	///ǿƽԭ��
	TThostFtdcForceCloseReasonType	ForceCloseReason;
	///�Զ������־
	TThostFtdcBoolType	IsAutoSuspend;
	///ҵ��Ԫ
	TThostFtdcBusinessUnitType	BusinessUnit;
	///������
	TThostFtdcRequestIDType	RequestID;
	///�û�ǿ����־
	TThostFtdcBoolType	UserForceClose;
	///��������־
	TThostFtdcBoolType	IsSwapOrder;
	///����������
	TThostFtdcExchangeIDType	ExchangeID;
	///Ͷ�ʵ�Ԫ����
	TThostFtdcInvestUnitIDType	InvestUnitID;
	///�ʽ��˺�
	TThostFtdcAccountIDType	AccountID;
	///���ִ���
	TThostFtdcCurrencyIDType	CurrencyID;
	///���ױ���
	TThostFtdcClientIDType	ClientID;
	///��������Ч�ֶ�
	TThostFtdcOldIPAddressType	reserve1;
	///Mac��ַ
	TThostFtdcMacAddressType	MacAddress;
	///��ϱ��
	TThostFtdcTradeIDType	ComTradeID;
	///IP��ַ
	TThostFtdcIPAddressType	IPAddress;
};

///����
struct CThostFtdcOrderField
{
	///���͹�˾����
	TThostFtdcBrokerIDType	BrokerID;
	///Ͷ���ߴ���
	TThostFtdcInvestorIDType	InvestorID;
	///��Լ����
	TThostFtdcInstrumentIDType	InstrumentID;
	///��������
	TThostFtdcOrderRefType	OrderRef;
	///�û�����
	TThostFtdcUserIDType	UserID;
	///�����۸�����
	TThostFtdcOrderPriceTypeType	OrderPriceType;
	///��������
	TThostFtdcDirectionType	Direction;
	///��Ͽ�ƽ��־
	TThostFtdcCombOffsetFlagType	CombOffsetFlag;
	///���Ͷ���ױ���־
	TThostFtdcCombHedgeFlagType	CombHedgeFlag;
	///�۸�
	TThostFtdcPriceType	LimitPrice;
	///����
	TThostFtdcVolumeType	VolumeTotalOriginal;
	///��Ч������
	TThostFtdcTimeConditionType	TimeCondition;
	///GTD����
	TThostFtdcDateType	GTDDate;
	///�ɽ�������
	TThostFtdcVolumeConditionType	VolumeCondition;
	///��С�ɽ���
	TThostFtdcVolumeType	MinVolume;
	///��������
	TThostFtdcContingentConditionType	ContingentCondition;
	///ֹ���
	TThostFtdcPriceType	StopPrice;
	///ǿƽԭ��
	TThostFtdcForceCloseReasonType	ForceCloseReason;
	///�Զ������־
	TThostFtdcBoolType	IsAutoSuspend;
	///ҵ��Ԫ
	TThostFtdcBusinessUnitType	BusinessUnit;
	///������
	TThostFtdcRequestIDType	RequestID;
	///���ر������
	TThostFtdcOrderLocalIDType	OrderLocalID;
	///����������
	TThostFtdcExchangeIDType	ExchangeID;
	///��Ա����
	TThostFtdcParticipantIDType	ParticipantID;
	///�ͻ�����
	TThostFtdcClientIDType	ClientID;
	///��Լ�ڽ������Ĵ���
	TThostFtdcExchangeInstIDType	ExchangeInstID;
	///����������Ա����
	TThostFtdcTraderIDType	TraderID;
	///��װ���
	TThostFtdcInstallIDType	InstallID;
	///�����ύ״̬
	TThostFtdcOrderSubmitStatusType	OrderSubmitStatus;
	///������ʾ���
	TThostFtdcSequenceNoType	NotifySequence;
	///������
	TThostFtdcDateType	TradingDay;
	///������
	TThostFtdcSettlementIDType	SettlementID;
	///�������
	TThostFtdcOrderSysIDType	OrderSysID;
	///������Դ
	TThostFtdcOrderSourceType	OrderSource;
	///����״̬
	TThostFtdcOrderStatusType	OrderStatus;
	///��������
	TThostFtdcOrderTypeType	OrderType;
	///��ɽ�����
	TThostFtdcVolumeType	VolumeTraded;
	///ʣ������
	TThostFtdcVolumeType	VolumeTotal;
	///��������
	TThostFtdcDateType	InsertDate;
	///ί��ʱ��
	TThostFtdcTimeType	InsertTime;
	///����ʱ��
	TThostFtdcTimeType	ActiveTime;
	///����ʱ��
	TThostFtdcTimeType	SuspendTime;
	///����޸�ʱ��
	TThostFtdcTimeType	UpdateTime;
	///����ʱ��
	TThostFtdcTimeType	CancelTime;
	///����޸Ľ���������Ա����
	TThostFtdcTraderIDType	ActiveTraderID;
	///�����Ա���
	TThostFtdcParticipantIDType	ClearingPartID;
	///���
	TThostFtdcSequenceNoType	SequenceNo;
	///ǰ�ñ��
	TThostFtdcFrontIDType	FrontID;
	///�Ự���
	TThostFtdcSessionIDType	SessionID;
	///�û��˲�Ʒ��Ϣ
	TThostFtdcProductInfoType	UserProductInfo;
	///״̬��Ϣ
	TThostFtdcErrorMsgType	StatusMsg;
	///�û�ǿ����־
	TThostFtdcBoolType	UserForceClose;
	///�����û�����
	TThostFtdcUserIDType	ActiveUserID;
	///���͹�˾�������
	TThostFtdcSequenceNoType	BrokerOrderSeq;
	///��ر���
	TThostFtdcOrderSysIDType	RelativeOrderSysID;
	///֣�����ɽ�����
	TThostFtdcVolumeType	ZCETotalTradedVolume;
	///��������־
	TThostFtdcBoolType	IsSwapOrder;
	///Ӫҵ�����
	TThostFtdcBranchIDType	BranchID;
	///Ͷ�ʵ�Ԫ����
	TThostFtdcInvestUnitIDType	InvestUnitID;
	///�ʽ��˺�
	TThostFtdcAccountIDType	AccountID;
	///���ִ���
	TThostFtdcCurrencyIDType	CurrencyID;
	///��������Ч�ֶ�
	TThostFtdcOldIPAddressType	reserve1;
	///Mac��ַ
	TThostFtdcMacAddressType	MacAddress;
	///����������
	TThostFtdcOwnerTypeType	OwnerType;
	///��ϱ��
	TThostFtdcTradeIDType	ComTradeID;
	///��½PBU
	TThostFtdcTraderIDType	LoginPBU;
	///IP��ַ
	TThostFtdcIPAddressType	IPAddress;
};

///����������
struct CThostFtdcExchangeOrderField
{
	///�����۸�����
	TThostFtdcOrderPriceTypeType	OrderPriceType;
	///��������
	TThostFtdcDirectionType	Direction;
	///��Ͽ�ƽ��־
	TThostFtdcCombOffsetFlagType	CombOffsetFlag;
	///���Ͷ���ױ���־
	TThostFtdcCombHedgeFlagType	CombHedgeFlag;
	///�۸�
	TThostFtdcPriceType	LimitPrice;
	///����
	TThostFtdcVolumeType	VolumeTotalOriginal;
	///��Ч������
	TThostFtdcTimeConditionType	TimeCondition;
	///GTD����
	TThostFtdcDateType	GTDDate;
	///�ɽ�������
	TThostFtdcVolumeConditionType	VolumeCondition;
	///��С�ɽ���
	TThostFtdcVolumeType	MinVolume;
	///��������
	TThostFtdcContingentConditionType	ContingentCondition;
	///ֹ���
	TThostFtdcPriceType	StopPrice;
	///ǿƽԭ��
	TThostFtdcForceCloseReasonType	ForceCloseReason;
	///�Զ������־
	TThostFtdcBoolType	IsAutoSuspend;
	///ҵ��Ԫ
	TThostFtdcBusinessUnitType	BusinessUnit;
	///������
	TThostFtdcRequestIDType	RequestID;
	///���ر������
	TThostFtdcOrderLocalIDType	OrderLocalID;
	///����������
	TThostFtdcExchangeIDType	ExchangeID;
	///��Ա����
	TThostFtdcParticipantIDType	ParticipantID;
	///�ͻ�����
	TThostFtdcClientIDType	ClientID;
	///��Լ�ڽ������Ĵ���
	TThostFtdcExchangeInstIDType	ExchangeInstID;
	///����������Ա����
	TThostFtdcTraderIDType	TraderID;
	///��װ���
	TThostFtdcInstallIDType	InstallID;
	///�����ύ״̬
	TThostFtdcOrderSubmitStatusType	OrderSubmitStatus;
	///������ʾ���
	TThostFtdcSequenceNoType	NotifySequence;
	///������
	TThostFtdcDateType	TradingDay;
	///������
	TThostFtdcSettlementIDType	SettlementID;
	///�������
	TThostFtdcOrderSysIDType	OrderSysID;
	///������Դ
	TThostFtdcOrderSourceType	OrderSource;
	///����״̬
	TThostFtdcOrderStatusType	OrderStatus;
	///��������
	TThostFtdcOrderTypeType	OrderType;
	///��ɽ�����
	TThostFtdcVolumeType	VolumeTraded;
	///ʣ������
	TThostFtdcVolumeType	VolumeTotal;
	///��������
	TThostFtdcDateType	InsertDate;
	///ί��ʱ��
	TThostFtdcTimeType	InsertTime;
	///����ʱ��
	TThostFtdcTimeType	ActiveTime;
	///����ʱ��
	TThostFtdcTimeType	SuspendTime;
	///����޸�ʱ��
	TThostFtdcTimeType	UpdateTime;
	///����ʱ��
	TThostFtdcTimeType	CancelTime;
	///����޸Ľ���������Ա����
	TThostFtdcTraderIDType	ActiveTraderID;
	///�����Ա���
	TThostFtdcParticipantIDType	ClearingPartID;
	///���
	TThostFtdcSequenceNoType	SequenceNo;
	///Ӫҵ�����
	TThostFtdcBranchIDType	BranchID;
	///��������Ч�ֶ�
	TThostFtdcOldIPAddressType	reserve1;
	///Mac��ַ
	TThostFtdcMacAddressType	MacAddress;
	///����������
	TThostFtdcOwnerTypeType	OwnerType;
	///��ϱ��
	TThostFtdcTradeIDType	ComTradeID;
	///��½PBU
	TThostFtdcTraderIDType	LoginPBU;
	///IP��ַ
	TThostFtdcIPAddressType	IPAddress;
};

///��������������ʧ��
struct CThostFtdcExchangeOrderInsertErrorField
{
	///����������
	TThostFtdcExchangeIDType	ExchangeID;
	///��Ա����
	TThostFtdcParticipantIDType	ParticipantID;
	///����������Ա����
	TThostFtdcTraderIDType	TraderID;
	///��װ���
	TThostFtdcInstallIDType	InstallID;
	///���ر������
	TThostFtdcOrderLocalIDType	OrderLocalID;
	///�������
	TThostFtdcErrorIDType	ErrorID;
	///������Ϣ
	TThostFtdcErrorMsgType	ErrorMsg;
};

///���뱨������
struct CThostFtdcInputOrderActionField
{
	///���͹�˾����
	TThostFtdcBrokerIDType	BrokerID;
	///Ͷ���ߴ���
	TThostFtdcInvestorIDType	InvestorID;
	///������������
	TThostFtdcOrderActionRefType	OrderActionRef;
	///��������
	TThostFtdcOrderRefType	OrderRef;
	///������
	TThostFtdcRequestIDType	RequestID;
	///ǰ�ñ��
	TThostFtdcFrontIDType	FrontID;
	///�Ự���
	TThostFtdcSessionIDType	SessionID;
	///����������
	TThostFtdcExchangeIDType	ExchangeID;
	///�������
	TThostFtdcOrderSysIDType	OrderSysID;
	///������־
	TThostFtdcActionFlagType	ActionFlag;
	///�۸�
	TThostFtdcPriceType	LimitPrice;
	///�����仯
	TThostFtdcVolumeType	VolumeChange;
	///�û�����
	TThostFtdcUserIDType	UserID;
	///��Լ����
	TThostFtdcInstrumentIDType	InstrumentID;
	///Ͷ�ʵ�Ԫ����
	TThostFtdcInvestUnitIDType	InvestUnitID;
	///��������Ч�ֶ�
	TThostFtdcOldIPAddressType	reserve1;
	///Mac��ַ
	TThostFtdcMacAddressType	MacAddress;
	///����������
	TThostFtdcOwnerTypeType	OwnerType;
	///��½PBU
	TThostFtdcTraderIDType	LoginPBU;
	///IP��ַ
	TThostFtdcIPAddressType	IPAddress;
};

///��������
struct CThostFtdcOrderActionField
{
	///���͹�˾����
	TThostFtdcBrokerIDType	BrokerID;
	///Ͷ���ߴ���
	TThostFtdcInvestorIDType	InvestorID;
	///������������
	TThostFtdcOrderActionRefType	OrderActionRef;
	///��������
	TThostFtdcOrderRefType	OrderRef;
	///������
	TThostFtdcRequestIDType	RequestID;
	///ǰ�ñ��
	TThostFtdcFrontIDType	FrontID;
	///�Ự���
	TThostFtdcSessionIDType	SessionID;
	///����������
	TThostFtdcExchangeIDType	ExchangeID;
	///�������
	TThostFtdcOrderSysIDType	OrderSysID;
	///������־
	TThostFtdcActionFlagType	ActionFlag;
	///�۸�
	TThostFtdcPriceType	LimitPrice;
	///�����仯
	TThostFtdcVolumeType	VolumeChange;
	///��������
	TThostFtdcDateType	ActionDate;
	///����ʱ��
	TThostFtdcTimeType	ActionTime;
	///����������Ա����
	TThostFtdcTraderIDType	TraderID;
	///��װ���
	TThostFtdcInstallIDType	InstallID;
	///���ر������
	TThostFtdcOrderLocalIDType	OrderLocalID;
	///�������ر��
	TThostFtdcOrderLocalIDType	ActionLocalID;
	///��Ա����
	TThostFtdcParticipantIDType	ParticipantID;
	///�ͻ�����
	TThostFtdcClientIDType	ClientID;
	///ҵ��Ԫ
	TThostFtdcBusinessUnitType	BusinessUnit;
	///��������״̬
	TThostFtdcOrderActionStatusType	OrderActionStatus;
	///�û�����
	TThostFtdcUserIDType	UserID;
	///״̬��Ϣ
	TThostFtdcErrorMsgType	StatusMsg;
	///��Լ����
	TThostFtdcInstrumentIDType	InstrumentID;
	///Ӫҵ�����
	TThostFtdcBranchIDType	BranchID;
	///Ͷ�ʵ�Ԫ����
	TThostFtdcInvestUnitIDType	InvestUnitID;
	///��������Ч�ֶ�
	TThostFtdcOldIPAddressType	reserve1;
	///Mac��ַ
	TThostFtdcMacAddressType	MacAddress;
	///����������
	TThostFtdcOwnerTypeType	OwnerType;
	///��½PBU
	TThostFtdcTraderIDType	LoginPBU;
	///IP��ַ
	TThostFtdcIPAddressType	IPAddress;
};

///��������������
struct CThostFtdcExchangeOrderActionField
{
	///����������
	TThostFtdcExchangeIDType	ExchangeID;
	///�������
	TThostFtdcOrderSysIDType	OrderSysID;
	///������־
	TThostFtdcActionFlagType	ActionFlag;
	///�۸�
	TThostFtdcPriceType	LimitPrice;
	///�����仯
	TThostFtdcVolumeType	VolumeChange;
	///��������
	TThostFtdcDateType	ActionDate;
	///����ʱ��
	TThostFtdcTimeType	ActionTime;
	///����������Ա����
	TThostFtdcTraderIDType	TraderID;
	///��װ���
	TThostFtdcInstallIDType	InstallID;
	///���ر������
	TThostFtdcOrderLocalIDType	OrderLocalID;
	///�������ر��
	TThostFtdcOrderLocalIDType	ActionLocalID;
	///��Ա����
	TThostFtdcParticipantIDType	ParticipantID;
	///�ͻ�����
	TThostFtdcClientIDType	ClientID;
	///ҵ��Ԫ
	TThostFtdcBusinessUnitType	BusinessUnit;
	///��������״̬
	TThostFtdcOrderActionStatusType	OrderActionStatus;
	///�û�����
	TThostFtdcUserIDType	UserID;
	///Ӫҵ�����
	TThostFtdcBranchIDType	BranchID;
	///��������Ч�ֶ�
	TThostFtdcOldIPAddressType	reserve1;
	///Mac��ַ
	TThostFtdcMacAddressType	MacAddress;
	///����������
	TThostFtdcOwnerTypeType	OwnerType;
	///��½PBU
	TThostFtdcTraderIDType	LoginPBU;
	///IP��ַ
	TThostFtdcIPAddressType	IPAddress;
};

///��������������ʧ��
struct CThostFtdcExchangeOrderActionErrorField
{
	///����������
	TThostFtdcExchangeIDType	ExchangeID;
	///�������
	TThostFtdcOrderSysIDType	OrderSysID;
	///����������Ա����
	TThostFtdcTraderIDType	TraderID;
	///��װ���
	TThostFtdcInstallIDType	InstallID;
	///���ر������
	TThostFtdcOrderLocalIDType	OrderLocalID;
	///�������ر��
	TThostFtdcOrderLocalIDType	ActionLocalID;
	///�������
	TThostFtdcErrorIDType	ErrorID;
	///������Ϣ
	TThostFtdcErrorMsgType	ErrorMsg;
	///���͹�˾����
	TThostFtdcBrokerIDType	BrokerID;
	///����ʱ��
	TThostFtdcTimeType	CancelTime;
	///�ͻ�����
	TThostFtdcClientIDType	ClientID;
	///��½PBU
	TThostFtdcTraderIDType	LoginPBU;
};

///�������ɽ�
struct CThostFtdcExchangeTradeField
{
	///����������
	TThostFtdcExchangeIDType	ExchangeID;
	///�ɽ����
	TThostFtdcTradeIDType	TradeID;
	///��������
	TThostFtdcDirectionType	Direction;
	///�������
	TThostFtdcOrderSysIDType	OrderSysID;
	///��Ա����
	TThostFtdcParticipantIDType	ParticipantID;
	///�ͻ�����
	TThostFtdcClientIDType	ClientID;
	///���׽�ɫ
	TThostFtdcTradingRoleType	TradingRole;
	///��Լ�ڽ������Ĵ���
	TThostFtdcExchangeInstIDType	ExchangeInstID;
	///��ƽ��־
	TThostFtdcOffsetFlagType	OffsetFlag;
	///Ͷ���ױ���־
	TThostFtdcHedgeFlagType	HedgeFlag;
	///�۸�
	TThostFtdcPriceType	Price;
	///����
	TThostFtdcVolumeType	Volume;
	///�ɽ�ʱ��
	TThostFtdcDateType	TradeDate;
	///�ɽ�ʱ��
	TThostFtdcTimeType	TradeTime;
	///�ɽ�����
	TThostFtdcTradeTypeType	TradeType;
	///�ɽ�����Դ
	TThostFtdcPriceSourceType	PriceSource;
	///����������Ա����
	TThostFtdcTraderIDType	TraderID;
	///���ر������
	TThostFtdcOrderLocalIDType	OrderLocalID;
	///�����Ա���
	TThostFtdcParticipantIDType	ClearingPartID;
	///ҵ��Ԫ
	TThostFtdcBusinessUnitType	BusinessUnit;
	///���
	TThostFtdcSequenceNoType	SequenceNo;
	///�ɽ���Դ
	TThostFtdcTradeSourceType	TradeSource;
	///����������
	TThostFtdcOwnerTypeType	OwnerType;
	///��ϱ��
	TThostFtdcTradeIDType	ComTradeID;
	///��½PBU
	TThostFtdcTraderIDType	LoginPBU;
};

///�ɽ�
struct CThostFtdcTradeField
{
	///���͹�˾����
	TThostFtdcBrokerIDType	BrokerID;
	///Ͷ���ߴ���
	TThostFtdcInvestorIDType	InvestorID;
	///��Լ����
	TThostFtdcInstrumentIDType	InstrumentID;
	///��������
	TThostFtdcOrderRefType	OrderRef;
	///�û�����
	TThostFtdcUserIDType	UserID;
	///����������
	TThostFtdcExchangeIDType	ExchangeID;
	///�ɽ����
	TThostFtdcTradeIDType	TradeID;
	///��������
	TThostFtdcDirectionType	Direction;
	///�������
	TThostFtdcOrderSysIDType	OrderSysID;
	///��Ա����
	TThostFtdcParticipantIDType	ParticipantID;
	///�ͻ�����
	TThostFtdcClientIDType	ClientID;
	///���׽�ɫ
	TThostFtdcTradingRoleType	TradingRole;
	///��Լ�ڽ������Ĵ���
	TThostFtdcExchangeInstIDType	ExchangeInstID;
	///��ƽ��־
	TThostFtdcOffsetFlagType	OffsetFlag;
	///Ͷ���ױ���־
	TThostFtdcHedgeFlagType	HedgeFlag;
	///�۸�
	TThostFtdcPriceType	Price;
	///����
	TThostFtdcVolumeType	Volume;
	///�ɽ�ʱ��
	TThostFtdcDateType	TradeDate;
	///�ɽ�ʱ��
	TThostFtdcTimeType	TradeTime;
	///�ɽ�����
	TThostFtdcTradeTypeType	TradeType;
	///�ɽ�����Դ
	TThostFtdcPriceSourceType	PriceSource;
	///����������Ա����
	TThostFtdcTraderIDType	TraderID;
	///���ر������
	TThostFtdcOrderLocalIDType	OrderLocalID;
	///�����Ա���
	TThostFtdcParticipantIDType	ClearingPartID;
	///ҵ��Ԫ
	TThostFtdcBusinessUnitType	BusinessUnit;
	///���
	TThostFtdcSequenceNoType	SequenceNo;
	///������
	TThostFtdcDateType	TradingDay;
	///������
	TThostFtdcSettlementIDType	SettlementID;
	///���͹�˾�������
	TThostFtdcSequenceNoType	BrokerOrderSeq;
	///�ɽ���Դ
	TThostFtdcTradeSourceType	TradeSource;
	///Ͷ�ʵ�Ԫ����
	TThostFtdcInvestUnitIDType	InvestUnitID;
	///����������
	TThostFtdcOwnerTypeType	OwnerType;
	///��ϱ��
	TThostFtdcTradeIDType	ComTradeID;
	///��½PBU
	TThostFtdcTraderIDType	LoginPBU;
};

///�û��Ự
struct CThostFtdcUserSessionField
{
	///ǰ�ñ��
	TThostFtdcFrontIDType	FrontID;
	///�Ự���
	TThostFtdcSessionIDType	SessionID;
	///���͹�˾����
	TThostFtdcBrokerIDType	BrokerID;
	///�û�����
	TThostFtdcUserIDType	UserID;
	///��¼����
	TThostFtdcDateType	LoginDate;
	///��¼ʱ��
	TThostFtdcTimeType	LoginTime;
	///��������Ч�ֶ�
	TThostFtdcOldIPAddressType	reserve1;
	///�û��˲�Ʒ��Ϣ
	TThostFtdcProductInfoType	UserProductInfo;
	///�ӿڶ˲�Ʒ��Ϣ
	TThostFtdcProductInfoType	InterfaceProductInfo;
	///Э����Ϣ
	TThostFtdcProtocolInfoType	ProtocolInfo;
	///Mac��ַ
	TThostFtdcMacAddressType	MacAddress;
	///��¼��ע
	TThostFtdcLoginRemarkType	LoginRemark;
	///IP��ַ
	TThostFtdcIPAddressType	IPAddress;
};

///��ѯ��󱨵�����
struct CThostFtdcQueryMaxOrderVolumeField
{
	///���͹�˾����
	TThostFtdcBrokerIDType	BrokerID;
	///Ͷ���ߴ���
	TThostFtdcInvestorIDType	InvestorID;
	///��Լ����
	TThostFtdcInstrumentIDType	InstrumentID;
	///��������
	TThostFtdcDirectionType	Direction;
	///��ƽ��־
	TThostFtdcOffsetFlagType	OffsetFlag;
	///Ͷ���ױ���־
	TThostFtdcHedgeFlagType	HedgeFlag;
	///�������������
	TThostFtdcVolumeType	MaxVolume;
	///����������
	TThostFtdcExchangeIDType	ExchangeID;
	///Ͷ�ʵ�Ԫ����
	TThostFtdcInvestUnitIDType	InvestUnitID;
};

///Ͷ���߽�����ȷ����Ϣ
struct CThostFtdcSettlementInfoConfirmField
{
	///���͹�˾����
	TThostFtdcBrokerIDType	BrokerID;
	///Ͷ���ߴ���
	TThostFtdcInvestorIDType	InvestorID;
	///ȷ������
	TThostFtdcDateType	ConfirmDate;
	///ȷ��ʱ��
	TThostFtdcTimeType	ConfirmTime;
	///������
	TThostFtdcSettlementIDType	SettlementID;
	///Ͷ�����ʺ�
	TThostFtdcAccountIDType	AccountID;
	///���ִ���
	TThostFtdcCurrencyIDType	CurrencyID;
};

///�����ͬ��
struct CThostFtdcSyncDepositField
{
	///�������ˮ��
	TThostFtdcDepositSeqNoType	DepositSeqNo;
	///���͹�˾����
	TThostFtdcBrokerIDType	BrokerID;
	///Ͷ���ߴ���
	TThostFtdcInvestorIDType	InvestorID;
	///�����
	TThostFtdcMoneyType	Deposit;
	///�Ƿ�ǿ�ƽ���
	TThostFtdcBoolType	IsForce;
	///���ִ���
	TThostFtdcCurrencyIDType	CurrencyID;
	///ҵ������
	TThostFtdcBizTypeType	BizType;
};

///������Ѻͬ��
struct CThostFtdcSyncFundMortgageField
{
	///������Ѻ��ˮ��
	TThostFtdcDepositSeqNoType	MortgageSeqNo;
	///���͹�˾����
	TThostFtdcBrokerIDType	BrokerID;
	///Ͷ���ߴ���
	TThostFtdcInvestorIDType	InvestorID;
	///Դ����
	TThostFtdcCurrencyIDType	FromCurrencyID;
	///��Ѻ���
	TThostFtdcMoneyType	MortgageAmount;
	///Ŀ�����
	TThostFtdcCurrencyIDType	ToCurrencyID;
};

///���͹�˾ͬ��
struct CThostFtdcBrokerSyncField
{
	///���͹�˾����
	TThostFtdcBrokerIDType	BrokerID;
};

///����ͬ���е�Ͷ����
struct CThostFtdcSyncingInvestorField
{
	///Ͷ���ߴ���
	TThostFtdcInvestorIDType	InvestorID;
	///���͹�˾����
	TThostFtdcBrokerIDType	BrokerID;
	///Ͷ���߷������
	TThostFtdcInvestorIDType	InvestorGroupID;
	///Ͷ��������
	TThostFtdcPartyNameType	InvestorName;
	///֤������
	TThostFtdcIdCardTypeType	IdentifiedCardType;
	///֤������
	TThostFtdcIdentifiedCardNoType	IdentifiedCardNo;
	///�Ƿ��Ծ
	TThostFtdcBoolType	IsActive;
	///��ϵ�绰
	TThostFtdcTelephoneType	Telephone;
	///ͨѶ��ַ
	TThostFtdcAddressType	Address;
	///��������
	TThostFtdcDateType	OpenDate;
	///�ֻ�
	TThostFtdcMobileType	Mobile;
	///��������ģ�����
	TThostFtdcInvestorIDType	CommModelID;
	///��֤����ģ�����
	TThostFtdcInvestorIDType	MarginModelID;
};

///����ͬ���еĽ��״���
struct CThostFtdcSyncingTradingCodeField
{
	///Ͷ���ߴ���
	TThostFtdcInvestorIDType	InvestorID;
	///���͹�˾����
	TThostFtdcBrokerIDType	BrokerID;
	///����������
	TThostFtdcExchangeIDType	ExchangeID;
	///�ͻ�����
	TThostFtdcClientIDType	ClientID;
	///�Ƿ��Ծ
	TThostFtdcBoolType	IsActive;
	///���ױ�������
	TThostFtdcClientIDTypeType	ClientIDType;
	///Ӫҵ�����
	TThostFtdcBranchIDType	BranchID;
};

///����ͬ���е�Ͷ���߷���
struct CThostFtdcSyncingInvestorGroupField
{
	///���͹�˾����
	TThostFtdcBrokerIDType	BrokerID;
	///Ͷ���߷������
	TThostFtdcInvestorIDType	InvestorGroupID;
	///Ͷ���߷�������
	TThostFtdcInvestorGroupNameType	InvestorGroupName;
};

///����ͬ���еĽ����˺�
struct CThostFtdcSyncingTradingAccountField
{
	///���͹�˾����
	TThostFtdcBrokerIDType	BrokerID;
	///Ͷ�����ʺ�
	TThostFtdcAccountIDType	AccountID;
	///�ϴ���Ѻ���
	TThostFtdcMoneyType	PreMortgage;
	///�ϴ����ö��
	TThostFtdcMoneyType	PreCredit;
	///�ϴδ���
	TThostFtdcMoneyType	PreDeposit;
	///�ϴν���׼����
	TThostFtdcMoneyType	PreBalance;
	///�ϴ�ռ�õı�֤��
	TThostFtdcMoneyType	PreMargin;
	///��Ϣ����
	TThostFtdcMoneyType	InterestBase;
	///��Ϣ����
	TThostFtdcMoneyType	Interest;
	///�����
	TThostFtdcMoneyType	Deposit;
	///������
	TThostFtdcMoneyType	Withdraw;
	///����ı�֤��
	TThostFtdcMoneyType	FrozenMargin;
	///������ʽ�
	TThostFtdcMoneyType	FrozenCash;
	///�����������
	TThostFtdcMoneyType	FrozenCommission;
	///��ǰ��֤���ܶ�
	TThostFtdcMoneyType	CurrMargin;
	///�ʽ���
	TThostFtdcMoneyType	CashIn;
	///������
	TThostFtdcMoneyType	Commission;
	///ƽ��ӯ��
	TThostFtdcMoneyType	CloseProfit;
	///�ֲ�ӯ��
	TThostFtdcMoneyType	PositionProfit;
	///�ڻ�����׼����
	TThostFtdcMoneyType	Balance;
	///�����ʽ�
	TThostFtdcMoneyType	Available;
	///��ȡ�ʽ�
	TThostFtdcMoneyType	WithdrawQuota;
	///����׼����
	TThostFtdcMoneyType	Reserve;
	///������
	TThostFtdcDateType	TradingDay;
	///������
	TThostFtdcSettlementIDType	SettlementID;
	///���ö��
	TThostFtdcMoneyType	Credit;
	///��Ѻ���
	TThostFtdcMoneyType	Mortgage;
	///��������֤��
	TThostFtdcMoneyType	ExchangeMargin;
	///Ͷ���߽��֤��
	TThostFtdcMoneyType	DeliveryMargin;
	///���������֤��
	TThostFtdcMoneyType	ExchangeDeliveryMargin;
	///�����ڻ�����׼����
	TThostFtdcMoneyType	ReserveBalance;
	///���ִ���
	TThostFtdcCurrencyIDType	CurrencyID;
	///�ϴλ���������
	TThostFtdcMoneyType	PreFundMortgageIn;
	///�ϴλ����ʳ����
	TThostFtdcMoneyType	PreFundMortgageOut;
	///����������
	TThostFtdcMoneyType	FundMortgageIn;
	///�����ʳ����
	TThostFtdcMoneyType	FundMortgageOut;
	///������Ѻ���
	TThostFtdcMoneyType	FundMortgageAvailable;
	///����Ѻ���ҽ��
	TThostFtdcMoneyType	MortgageableFund;
	///�����Ʒռ�ñ�֤��
	TThostFtdcMoneyType	SpecProductMargin;
	///�����Ʒ���ᱣ֤��
	TThostFtdcMoneyType	SpecProductFrozenMargin;
	///�����Ʒ������
	TThostFtdcMoneyType	SpecProductCommission;
	///�����Ʒ����������
	TThostFtdcMoneyType	SpecProductFrozenCommission;
	///�����Ʒ�ֲ�ӯ��
	TThostFtdcMoneyType	SpecProductPositionProfit;
	///�����Ʒƽ��ӯ��
	TThostFtdcMoneyType	SpecProductCloseProfit;
	///���ݳֲ�ӯ���㷨����������Ʒ�ֲ�ӯ��
	TThostFtdcMoneyType	SpecProductPositionProfitByAlg;
	///�����Ʒ��������֤��
	TThostFtdcMoneyType	SpecProductExchangeMargin;
	///��ʱ���㶳����
	TThostFtdcMoneyType	FrozenSwap;
	///ʣ�໻����
	TThostFtdcMoneyType	RemainSwap;
	///��ֵ
	TThostFtdcMoneyType	OptionValue;
};

///����ͬ���е�Ͷ���ֲ߳�
struct CThostFtdcSyncingInvestorPositionField
{
	///��Լ����
	TThostFtdcInstrumentIDType	InstrumentID;
	///���͹�˾����
	TThostFtdcBrokerIDType	BrokerID;
	///Ͷ���ߴ���
	TThostFtdcInvestorIDType	InvestorID;
	///�ֲֶ�շ���
	TThostFtdcPosiDirectionType	PosiDirection;
	///Ͷ���ױ���־
	TThostFtdcHedgeFlagType	HedgeFlag;
	///�ֲ�����
	TThostFtdcPositionDateType	PositionDate;
	///���ճֲ�
	TThostFtdcVolumeType	YdPosition;
	///���ճֲ�
	TThostFtdcVolumeType	Position;
	///��ͷ����
	TThostFtdcVolumeType	LongFrozen;
	///��ͷ����
	TThostFtdcVolumeType	ShortFrozen;
	///���ֶ�����
	TThostFtdcMoneyType	LongFrozenAmount;
	///���ֶ�����
	TThostFtdcMoneyType	ShortFrozenAmount;
	///������
	TThostFtdcVolumeType	OpenVolume;
	///ƽ����
	TThostFtdcVolumeType	CloseVolume;
	///���ֽ��
	TThostFtdcMoneyType	OpenAmount;
	///ƽ�ֽ��
	TThostFtdcMoneyType	CloseAmount;
	///�ֲֳɱ�
	TThostFtdcMoneyType	PositionCost;
	///�ϴ�ռ�õı�֤��
	TThostFtdcMoneyType	PreMargin;
	///ռ�õı�֤��
	TThostFtdcMoneyType	UseMargin;
	///����ı�֤��
	TThostFtdcMoneyType	FrozenMargin;
	///������ʽ�
	TThostFtdcMoneyType	FrozenCash;
	///�����������
	TThostFtdcMoneyType	FrozenCommission;
	///�ʽ���
	TThostFtdcMoneyType	CashIn;
	///������
	TThostFtdcMoneyType	Commission;
	///ƽ��ӯ��
	TThostFtdcMoneyType	CloseProfit;
	///�ֲ�ӯ��
	TThostFtdcMoneyType	PositionProfit;
	///�ϴν����
	TThostFtdcPriceType	PreSettlementPrice;
	///���ν����
	TThostFtdcPriceType	SettlementPrice;
	///������
	TThostFtdcDateType	TradingDay;
	///������
	TThostFtdcSettlementIDType	SettlementID;
	///���ֳɱ�
	TThostFtdcMoneyType	OpenCost;
	///��������֤��
	TThostFtdcMoneyType	ExchangeMargin;
	///��ϳɽ��γɵĳֲ�
	TThostFtdcVolumeType	CombPosition;
	///��϶�ͷ����
	TThostFtdcVolumeType	CombLongFrozen;
	///��Ͽ�ͷ����
	TThostFtdcVolumeType	CombShortFrozen;
	///���ն���ƽ��ӯ��
	TThostFtdcMoneyType	CloseProfitByDate;
	///��ʶԳ�ƽ��ӯ��
	TThostFtdcMoneyType	CloseProfitByTrade;
	///���ճֲ�
	TThostFtdcVolumeType	TodayPosition;
	///��֤����
	TThostFtdcRatioType	MarginRateByMoney;
	///��֤����(������)
	TThostFtdcRatioType	MarginRateByVolume;
	///ִ�ж���
	TThostFtdcVolumeType	StrikeFrozen;
	///ִ�ж�����
	TThostFtdcMoneyType	StrikeFrozenAmount;
	///����ִ�ж���
	TThostFtdcVolumeType	AbandonFrozen;
	///����������
	TThostFtdcExchangeIDType	ExchangeID;
	///ִ�ж�������
	TThostFtdcVolumeType	YdStrikeFrozen;
	///Ͷ�ʵ�Ԫ����
	TThostFtdcInvestUnitIDType	InvestUnitID;
	///��ֵ
	TThostFtdcMoneyType	OptionValue;
};

///����ͬ���еĺ�Լ��֤����
struct CThostFtdcSyncingInstrumentMarginRateField
{
	///��Լ����
	TThostFtdcInstrumentIDType	InstrumentID;
	///Ͷ���߷�Χ
	TThostFtdcInvestorRangeType	InvestorRange;
	///���͹�˾����
	TThostFtdcBrokerIDType	BrokerID;
	///Ͷ���ߴ���
	TThostFtdcInvestorIDType	InvestorID;
	///Ͷ���ױ���־
	TThostFtdcHedgeFlagType	HedgeFlag;
	///��ͷ��֤����
	TThostFtdcRatioType	LongMarginRatioByMoney;
	///��ͷ��֤���
	TThostFtdcMoneyType	LongMarginRatioByVolume;
	///��ͷ��֤����
	TThostFtdcRatioType	ShortMarginRatioByMoney;
	///��ͷ��֤���
	TThostFtdcMoneyType	ShortMarginRatioByVolume;
	///�Ƿ���Խ�������ȡ
	TThostFtdcBoolType	IsRelative;
};

///����ͬ���еĺ�Լ��������
struct CThostFtdcSyncingInstrumentCommissionRateField
{
	///��Լ����
	TThostFtdcInstrumentIDType	InstrumentID;
	///Ͷ���߷�Χ
	TThostFtdcInvestorRangeType	InvestorRange;
	///���͹�˾����
	TThostFtdcBrokerIDType	BrokerID;
	///Ͷ���ߴ���
	TThostFtdcInvestorIDType	InvestorID;
	///������������
	TThostFtdcRatioType	OpenRatioByMoney;
	///����������
	TThostFtdcRatioType	OpenRatioByVolume;
	///ƽ����������
	TThostFtdcRatioType	CloseRatioByMoney;
	///ƽ��������
	TThostFtdcRatioType	CloseRatioByVolume;
	///ƽ����������
	TThostFtdcRatioType	CloseTodayRatioByMoney;
	///ƽ��������
	TThostFtdcRatioType	CloseTodayRatioByVolume;
	///����������
	TThostFtdcExchangeIDType	ExchangeID;
};

///����ͬ���еĺ�Լ����Ȩ��
struct CThostFtdcSyncingInstrumentTradingRightField
{
	///��Լ����
	TThostFtdcInstrumentIDType	InstrumentID;
	///Ͷ���߷�Χ
	TThostFtdcInvestorRangeType	InvestorRange;
	///���͹�˾����
	TThostFtdcBrokerIDType	BrokerID;
	///Ͷ���ߴ���
	TThostFtdcInvestorIDType	InvestorID;
	///����Ȩ��
	TThostFtdcTradingRightType	TradingRight;
	///����������
	TThostFtdcExchangeIDType	ExchangeID;
};

///��ѯ����
struct CThostFtdcQryOrderField
{
	///���͹�˾����
	TThostFtdcBrokerIDType	BrokerID;
	///Ͷ���ߴ���
	TThostFtdcInvestorIDType	InvestorID;
	///��Լ����
	TThostFtdcInstrumentIDType	InstrumentID;
	///����������
	TThostFtdcExchangeIDType	ExchangeID;
	///�������
	TThostFtdcOrderSysIDType	OrderSysID;
	///��ʼʱ��
	TThostFtdcTimeType	InsertTimeStart;
	///����ʱ��
	TThostFtdcTimeType	InsertTimeEnd;
	///Ͷ�ʵ�Ԫ����
	TThostFtdcInvestUnitIDType	InvestUnitID;
};

///��ѯ�ɽ�
struct CThostFtdcQryTradeField
{
	///���͹�˾����
	TThostFtdcBrokerIDType	BrokerID;
	///Ͷ���ߴ���
	TThostFtdcInvestorIDType	InvestorID;
	///��Լ����
	TThostFtdcInstrumentIDType	InstrumentID;
	///����������
	TThostFtdcExchangeIDType	ExchangeID;
	///�ɽ����
	TThostFtdcTradeIDType	TradeID;
	///��ʼʱ��
	TThostFtdcTimeType	TradeTimeStart;
	///����ʱ��
	TThostFtdcTimeType	TradeTimeEnd;
	///Ͷ�ʵ�Ԫ����
	TThostFtdcInvestUnitIDType	InvestUnitID;
};

///��ѯͶ���ֲ߳�
struct CThostFtdcQryInvestorPositionField
{
	///���͹�˾����
	TThostFtdcBrokerIDType	BrokerID;
	///Ͷ���ߴ���
	TThostFtdcInvestorIDType	InvestorID;
	///��Լ����
	TThostFtdcInstrumentIDType	InstrumentID;
	///����������
	TThostFtdcExchangeIDType	ExchangeID;
	///Ͷ�ʵ�Ԫ����
	TThostFtdcInvestUnitIDType	InvestUnitID;
};

///��ѯ�ʽ��˻�
struct CThostFtdcQryTradingAccountField
{
	///���͹�˾����
	TThostFtdcBrokerIDType	BrokerID;
	///Ͷ���ߴ���
	TThostFtdcInvestorIDType	InvestorID;
	///���ִ���
	TThostFtdcCurrencyIDType	CurrencyID;
	///ҵ������
	TThostFtdcBizTypeType	BizType;
	///Ͷ�����ʺ�
	TThostFtdcAccountIDType	AccountID;
};

///��ѯͶ����
struct CThostFtdcQryInvestorField
{
	///���͹�˾����
	TThostFtdcBrokerIDType	BrokerID;
	///Ͷ���ߴ���
	TThostFtdcInvestorIDType	InvestorID;
};

///��ѯ���ױ���
struct CThostFtdcQryTradingCodeField
{
	///���͹�˾����
	TThostFtdcBrokerIDType	BrokerID;
	///Ͷ���ߴ���
	TThostFtdcInvestorIDType	InvestorID;
	///����������
	TThostFtdcExchangeIDType	ExchangeID;
	///�ͻ�����
	TThostFtdcClientIDType	ClientID;
	///���ױ�������
	TThostFtdcClientIDTypeType	ClientIDType;
	///Ͷ�ʵ�Ԫ����
	TThostFtdcInvestUnitIDType	InvestUnitID;
};

///��ѯͶ������
struct CThostFtdcQryInvestorGroupField
{
	///���͹�˾����
	TThostFtdcBrokerIDType	BrokerID;
};

///��ѯ��Լ��֤����
struct CThostFtdcQryInstrumentMarginRateField
{
	///���͹�˾����
	TThostFtdcBrokerIDType	BrokerID;
	///Ͷ���ߴ���
	TThostFtdcInvestorIDType	InvestorID;
	///��Լ����
	TThostFtdcInstrumentIDType	InstrumentID;
	///Ͷ���ױ���־
	TThostFtdcHedgeFlagType	HedgeFlag;
	///����������
	TThostFtdcExchangeIDType	ExchangeID;
	///Ͷ�ʵ�Ԫ����
	TThostFtdcInvestUnitIDType	InvestUnitID;
};

///��ѯ��������
struct CThostFtdcQryInstrumentCommissionRateField
{
	///���͹�˾����
	TThostFtdcBrokerIDType	BrokerID;
	///Ͷ���ߴ���
	TThostFtdcInvestorIDType	InvestorID;
	///��Լ����
	TThostFtdcInstrumentIDType	InstrumentID;
	///����������
	TThostFtdcExchangeIDType	ExchangeID;
	///Ͷ�ʵ�Ԫ����
	TThostFtdcInvestUnitIDType	InvestUnitID;
};

///��ѯ��Լ����Ȩ��
struct CThostFtdcQryInstrumentTradingRightField
{
	///���͹�˾����
	TThostFtdcBrokerIDType	BrokerID;
	///Ͷ���ߴ���
	TThostFtdcInvestorIDType	InvestorID;
	///��Լ����
	TThostFtdcInstrumentIDType	InstrumentID;
	///����������
	TThostFtdcExchangeIDType	ExchangeID;
};

///��ѯ���͹�˾
struct CThostFtdcQryBrokerField
{
	///���͹�˾����
	TThostFtdcBrokerIDType	BrokerID;
};

///��ѯ����Ա
struct CThostFtdcQryTraderField
{
	///����������
	TThostFtdcExchangeIDType	ExchangeID;
	///��Ա����
	TThostFtdcParticipantIDType	ParticipantID;
	///����������Ա����
	TThostFtdcTraderIDType	TraderID;
};

///��ѯ�����û�����Ȩ��
struct CThostFtdcQrySuperUserFunctionField
{
	///�û�����
	TThostFtdcUserIDType	UserID;
};

///��ѯ�û��Ự
struct CThostFtdcQryUserSessionField
{
	///ǰ�ñ��
	TThostFtdcFrontIDType	FrontID;
	///�Ự���
	TThostFtdcSessionIDType	SessionID;
	///���͹�˾����
	TThostFtdcBrokerIDType	BrokerID;
	///�û�����
	TThostFtdcUserIDType	UserID;
};

///��ѯ���͹�˾��Ա����
struct CThostFtdcQryPartBrokerField
{
	///����������
	TThostFtdcExchangeIDType	ExchangeID;
	///���͹�˾����
	TThostFtdcBrokerIDType	BrokerID;
	///��Ա����
	TThostFtdcParticipantIDType	ParticipantID;
};

///��ѯǰ��״̬
struct CThostFtdcQryFrontStatusField
{
	///ǰ�ñ��
	TThostFtdcFrontIDType	FrontID;
};

///��ѯ����������
struct CThostFtdcQryExchangeOrderField
{
	///��Ա����
	TThostFtdcParticipantIDType	ParticipantID;
	///�ͻ�����
	TThostFtdcClientIDType	ClientID;
	///��Լ�ڽ������Ĵ���
	TThostFtdcExchangeInstIDType	ExchangeInstID;
	///����������
	TThostFtdcExchangeIDType	ExchangeID;
	///����������Ա����
	TThostFtdcTraderIDType	TraderID;
};

///��ѯ��������
struct CThostFtdcQryOrderActionField
{
	///���͹�˾����
	TThostFtdcBrokerIDType	BrokerID;
	///Ͷ���ߴ���
	TThostFtdcInvestorIDType	InvestorID;
	///����������
	TThostFtdcExchangeIDType	ExchangeID;
};

///��ѯ��������������
struct CThostFtdcQryExchangeOrderActionField
{
	///��Ա����
	TThostFtdcParticipantIDType	ParticipantID;
	///�ͻ�����
	TThostFtdcClientIDType	ClientID;
	///����������
	TThostFtdcExchangeIDType	ExchangeID;
	///����������Ա����
	TThostFtdcTraderIDType	TraderID;
};

///��ѯ�����û�
struct CThostFtdcQrySuperUserField
{
	///�û�����
	TThostFtdcUserIDType	UserID;
};

///��ѯ������
struct CThostFtdcQryExchangeField
{
	///����������
	TThostFtdcExchangeIDType	ExchangeID;
};

///��ѯ��Ʒ
struct CThostFtdcQryProductField
{
	///��Ʒ����
	TThostFtdcInstrumentIDType	ProductID;
	///��Ʒ����
	TThostFtdcProductClassType	ProductClass;
	///����������
	TThostFtdcExchangeIDType	ExchangeID;
};

///��ѯ��Լ
struct CThostFtdcQryInstrumentField
{
	///��Լ����
	TThostFtdcInstrumentIDType	InstrumentID;
	///����������
	TThostFtdcExchangeIDType	ExchangeID;
	///��Լ�ڽ������Ĵ���
	TThostFtdcExchangeInstIDType	ExchangeInstID;
	///��Ʒ����
	TThostFtdcInstrumentIDType	ProductID;
};

///��ѯ����
struct CThostFtdcQryDepthMarketDataField
{
	///��Լ����
	TThostFtdcInstrumentIDType	InstrumentID;
	///����������
	TThostFtdcExchangeIDType	ExchangeID;
};

///��ѯ���͹�˾�û�
struct CThostFtdcQryBrokerUserField
{
	///���͹�˾����
	TThostFtdcBrokerIDType	BrokerID;
	///�û�����
	TThostFtdcUserIDType	UserID;
};

///��ѯ���͹�˾�û�Ȩ��
struct CThostFtdcQryBrokerUserFunctionField
{
	///���͹�˾����
	TThostFtdcBrokerIDType	BrokerID;
	///�û�����
	TThostFtdcUserIDType	UserID;
};

///���������۳����ر�
struct CThostFtdcExchangeQuoteActionErrorField
{
	///����������
	TThostFtdcExchangeIDType	ExchangeID;
	///���۱��
	TThostFtdcOrderSysIDType	QuoteSysID;
	///����������Ա����
	TThostFtdcTraderIDType	TraderID;
	///��װ���
	TThostFtdcInstallIDType	InstallID;
	///����ִ��������
	TThostFtdcOrderLocalIDType	QuoteLocalID;
	///�������ر��
	TThostFtdcOrderLocalIDType	ActionLocalID;
	///�������
	TThostFtdcErrorIDType	ErrorID;
	///������Ϣ
	TThostFtdcErrorMsgType	ErrorMsg;
	///�򱨵����ر�����
	TThostFtdcOrderLocalIDType	BidOrderLocalID;
	///���������ر�����
	TThostFtdcOrderLocalIDType	AskOrderLocalID;
	///��Լ�ڽ������Ĵ���
	TThostFtdcExchangeInstIDType	ExchangeInstID;
	///�ͻ�����
	TThostFtdcClientIDType	ClientID;
	///��½PBU
	TThostFtdcTraderIDType	LoginPBU;
};

///��ѯ����Ա���̻�
struct CThostFtdcQryTraderOfferField
{
	///����������
	TThostFtdcExchangeIDType	ExchangeID;
	///��Ա����
	TThostFtdcParticipantIDType	ParticipantID;
	///����������Ա����
	TThostFtdcTraderIDType	TraderID;
};

///��ѯ�������ˮ
struct CThostFtdcQrySyncDepositField
{
	///���͹�˾����
	TThostFtdcBrokerIDType	BrokerID;
	///�������ˮ��
	TThostFtdcDepositSeqNoType	DepositSeqNo;
};

///��ѯͶ���߽�����
struct CThostFtdcQrySettlementInfoField
{
	///���͹�˾����
	TThostFtdcBrokerIDType	BrokerID;
	///Ͷ���ߴ���
	TThostFtdcInvestorIDType	InvestorID;
	///������
	TThostFtdcDateType	TradingDay;
	///Ͷ�����ʺ�
	TThostFtdcAccountIDType	AccountID;
	///���ִ���
	TThostFtdcCurrencyIDType	CurrencyID;
};

///��ѯ��������֤����
struct CThostFtdcQryExchangeMarginRateField
{
	///���͹�˾����
	TThostFtdcBrokerIDType	BrokerID;
	///��Լ����
	TThostFtdcInstrumentIDType	InstrumentID;
	///Ͷ���ױ���־
	TThostFtdcHedgeFlagType	HedgeFlag;
	///����������
	TThostFtdcExchangeIDType	ExchangeID;
};

///��ѯ������������֤����
struct CThostFtdcQryExchangeMarginRateAdjustField
{
	///���͹�˾����
	TThostFtdcBrokerIDType	BrokerID;
	///��Լ����
	TThostFtdcInstrumentIDType	InstrumentID;
	///Ͷ���ױ���־
	TThostFtdcHedgeFlagType	HedgeFlag;
};

///��ѯ����
struct CThostFtdcQryExchangeRateField
{
	///���͹�˾����
	TThostFtdcBrokerIDType	BrokerID;
	///Դ����
	TThostFtdcCurrencyIDType	FromCurrencyID;
	///Ŀ�����
	TThostFtdcCurrencyIDType	ToCurrencyID;
};

///��ѯ������Ѻ��ˮ
struct CThostFtdcQrySyncFundMortgageField
{
	///���͹�˾����
	TThostFtdcBrokerIDType	BrokerID;
	///������Ѻ��ˮ��
	TThostFtdcDepositSeqNoType	MortgageSeqNo;
};

///��ѯ����
struct CThostFtdcQryHisOrderField
{
	///���͹�˾����
	TThostFtdcBrokerIDType	BrokerID;
	///Ͷ���ߴ���
	TThostFtdcInvestorIDType	InvestorID;
	///��Լ����
	TThostFtdcInstrumentIDType	InstrumentID;
	///����������
	TThostFtdcExchangeIDType	ExchangeID;
	///�������
	TThostFtdcOrderSysIDType	OrderSysID;
	///��ʼʱ��
	TThostFtdcTimeType	InsertTimeStart;
	///����ʱ��
	TThostFtdcTimeType	InsertTimeEnd;
	///������
	TThostFtdcDateType	TradingDay;
	///������
	TThostFtdcSettlementIDType	SettlementID;
};

///��ǰ��Ȩ��Լ��С��֤��
struct CThostFtdcOptionInstrMiniMarginField
{
	///��Լ����
	TThostFtdcInstrumentIDType	InstrumentID;
	///Ͷ���߷�Χ
	TThostFtdcInvestorRangeType	InvestorRange;
	///���͹�˾����
	TThostFtdcBrokerIDType	BrokerID;
	///Ͷ���ߴ���
	TThostFtdcInvestorIDType	InvestorID;
	///��λ���֣���Ȩ��Լ��С��֤��
	TThostFtdcMoneyType	MinMargin;
	///ȡֵ��ʽ
	TThostFtdcValueMethodType	ValueMethod;
	///�Ƿ���潻������ȡ
	TThostFtdcBoolType	IsRelative;
	///����������
	TThostFtdcExchangeIDType	ExchangeID;
};

///��ǰ��Ȩ��Լ��֤�����ϵ��
struct CThostFtdcOptionInstrMarginAdjustField
{
	///��Լ����
	TThostFtdcInstrumentIDType	InstrumentID;
	///Ͷ���߷�Χ
	TThostFtdcInvestorRangeType	InvestorRange;
	///���͹�˾����
	TThostFtdcBrokerIDType	BrokerID;
	///Ͷ���ߴ���
	TThostFtdcInvestorIDType	InvestorID;
	///Ͷ����ͷ��֤�����ϵ��
	TThostFtdcRatioType	SShortMarginRatioByMoney;
	///Ͷ����ͷ��֤�����ϵ��
	TThostFtdcMoneyType	SShortMarginRatioByVolume;
	///��ֵ��ͷ��֤�����ϵ��
	TThostFtdcRatioType	HShortMarginRatioByMoney;
	///��ֵ��ͷ��֤�����ϵ��
	TThostFtdcMoneyType	HShortMarginRatioByVolume;
	///������ͷ��֤�����ϵ��
	TThostFtdcRatioType	AShortMarginRatioByMoney;
	///������ͷ��֤�����ϵ��
	TThostFtdcMoneyType	AShortMarginRatioByVolume;
	///�Ƿ���潻������ȡ
	TThostFtdcBoolType	IsRelative;
	///����������
	TThostFtdcExchangeIDType	ExchangeID;
	///�����̿�ͷ��֤�����ϵ��
	TThostFtdcRatioType	MShortMarginRatioByMoney;
	///�����̿�ͷ��֤�����ϵ��
	TThostFtdcMoneyType	MShortMarginRatioByVolume;
};

///��ǰ��Ȩ��Լ�����ѵ���ϸ����
struct CThostFtdcOptionInstrCommRateField
{
	///��Լ����
	TThostFtdcInstrumentIDType	InstrumentID;
	///Ͷ���߷�Χ
	TThostFtdcInvestorRangeType	InvestorRange;
	///���͹�˾����
	TThostFtdcBrokerIDType	BrokerID;
	///Ͷ���ߴ���
	TThostFtdcInvestorIDType	InvestorID;
	///������������
	TThostFtdcRatioType	OpenRatioByMoney;
	///����������
	TThostFtdcRatioType	OpenRatioByVolume;
	///ƽ����������
	TThostFtdcRatioType	CloseRatioByMoney;
	///ƽ��������
	TThostFtdcRatioType	CloseRatioByVolume;
	///ƽ����������
	TThostFtdcRatioType	CloseTodayRatioByMoney;
	///ƽ��������
	TThostFtdcRatioType	CloseTodayRatioByVolume;
	///ִ����������
	TThostFtdcRatioType	StrikeRatioByMoney;
	///ִ��������
	TThostFtdcRatioType	StrikeRatioByVolume;
	///����������
	TThostFtdcExchangeIDType	ExchangeID;
	///Ͷ�ʵ�Ԫ����
	TThostFtdcInvestUnitIDType	InvestUnitID;
};

///��Ȩ���׳ɱ�
struct CThostFtdcOptionInstrTradeCostField
{
	///���͹�˾����
	TThostFtdcBrokerIDType	BrokerID;
	///Ͷ���ߴ���
	TThostFtdcInvestorIDType	InvestorID;
	///��Լ����
	TThostFtdcInstrumentIDType	InstrumentID;
	///Ͷ���ױ���־
	TThostFtdcHedgeFlagType	HedgeFlag;
	///��Ȩ��Լ��֤�𲻱䲿��
	TThostFtdcMoneyType	FixedMargin;
	///��Ȩ��Լ��С��֤��
	TThostFtdcMoneyType	MiniMargin;
	///��Ȩ��ԼȨ����
	TThostFtdcMoneyType	Royalty;
	///��������Ȩ��Լ��֤�𲻱䲿��
	TThostFtdcMoneyType	ExchFixedMargin;
	///��������Ȩ��Լ��С��֤��
	TThostFtdcMoneyType	ExchMiniMargin;
	///����������
	TThostFtdcExchangeIDType	ExchangeID;
	///Ͷ�ʵ�Ԫ����
	TThostFtdcInvestUnitIDType	InvestUnitID;
};

///��Ȩ���׳ɱ���ѯ
struct CThostFtdcQryOptionInstrTradeCostField
{
	///���͹�˾����
	TThostFtdcBrokerIDType	BrokerID;
	///Ͷ���ߴ���
	TThostFtdcInvestorIDType	InvestorID;
	///��Լ����
	TThostFtdcInstrumentIDType	InstrumentID;
	///Ͷ���ױ���־
	TThostFtdcHedgeFlagType	HedgeFlag;
	///��Ȩ��Լ����
	TThostFtdcPriceType	InputPrice;
	///��ļ۸�,��0����������
	TThostFtdcPriceType	UnderlyingPrice;
	///����������
	TThostFtdcExchangeIDType	ExchangeID;
	///Ͷ�ʵ�Ԫ����
	TThostFtdcInvestUnitIDType	InvestUnitID;
};

///��Ȩ�������ʲ�ѯ
struct CThostFtdcQryOptionInstrCommRateField
{
	///���͹�˾����
	TThostFtdcBrokerIDType	BrokerID;
	///Ͷ���ߴ���
	TThostFtdcInvestorIDType	InvestorID;
	///��Լ����
	TThostFtdcInstrumentIDType	InstrumentID;
	///����������
	TThostFtdcExchangeIDType	ExchangeID;
	///Ͷ�ʵ�Ԫ����
	TThostFtdcInvestUnitIDType	InvestUnitID;
};

///��ָ�ֻ�ָ��
struct CThostFtdcIndexPriceField
{
	///���͹�˾����
	TThostFtdcBrokerIDType	BrokerID;
	///��Լ����
	TThostFtdcInstrumentIDType	InstrumentID;
	///ָ���ֻ����̼�
	TThostFtdcPriceType	ClosePrice;
	///����������
	TThostFtdcExchangeIDType	ExchangeID;
};

///�����ִ������
struct CThostFtdcInputExecOrderField
{
	///���͹�˾����
	TThostFtdcBrokerIDType	BrokerID;
	///Ͷ���ߴ���
	TThostFtdcInvestorIDType	InvestorID;
	///��Լ����
	TThostFtdcInstrumentIDType	InstrumentID;
	///ִ����������
	TThostFtdcOrderRefType	ExecOrderRef;
	///�û�����
	TThostFtdcUserIDType	UserID;
	///����
	TThostFtdcVolumeType	Volume;
	///������
	TThostFtdcRequestIDType	RequestID;
	///ҵ��Ԫ
	TThostFtdcBusinessUnitType	BusinessUnit;
	///��ƽ��־
	TThostFtdcOffsetFlagType	OffsetFlag;
	///Ͷ���ױ���־
	TThostFtdcHedgeFlagType	HedgeFlag;
	///ִ������
	TThostFtdcActionTypeType	ActionType;
	///����ͷ������ĳֲַ���
	TThostFtdcPosiDirectionType	PosiDirection;
	///��Ȩ��Ȩ���Ƿ����ڻ�ͷ��ı��,���ֶ��ѷ���
	TThostFtdcExecOrderPositionFlagType	ReservePositionFlag;
	///��Ȩ��Ȩ�����ɵ�ͷ���Ƿ��Զ�ƽ��
	TThostFtdcExecOrderCloseFlagType	CloseFlag;
	///����������
	TThostFtdcExchangeIDType	ExchangeID;
	///Ͷ�ʵ�Ԫ����
	TThostFtdcInvestUnitIDType	InvestUnitID;
	///�ʽ��˺�
	TThostFtdcAccountIDType	AccountID;
	///���ִ���
	TThostFtdcCurrencyIDType	CurrencyID;
	///���ױ���
	TThostFtdcClientIDType	ClientID;
	///��������Ч�ֶ�
	TThostFtdcOldIPAddressType	reserve1;
	///Mac��ַ
	TThostFtdcMacAddressType	MacAddress;
	///IP��ַ
	TThostFtdcIPAddressType	IPAddress;
};

///����ִ���������
struct CThostFtdcInputExecOrderActionField
{
	///���͹�˾����
	TThostFtdcBrokerIDType	BrokerID;
	///Ͷ���ߴ���
	TThostFtdcInvestorIDType	InvestorID;
	///ִ�������������
	TThostFtdcOrderActionRefType	ExecOrderActionRef;
	///ִ����������
	TThostFtdcOrderRefType	ExecOrderRef;
	///������
	TThostFtdcRequestIDType	RequestID;
	///ǰ�ñ��
	TThostFtdcFrontIDType	FrontID;
	///�Ự���
	TThostFtdcSessionIDType	SessionID;
	///����������
	TThostFtdcExchangeIDType	ExchangeID;
	///ִ������������
	TThostFtdcExecOrderSysIDType	ExecOrderSysID;
	///������־
	TThostFtdcActionFlagType	ActionFlag;
	///�û�����
	TThostFtdcUserIDType	UserID;
	///��Լ����
	TThostFtdcInstrumentIDType	InstrumentID;
	///Ͷ�ʵ�Ԫ����
	TThostFtdcInvestUnitIDType	InvestUnitID;
	///��������Ч�ֶ�
	TThostFtdcOldIPAddressType	reserve1;
	///Mac��ַ
	TThostFtdcMacAddressType	MacAddress;
	///����������
	TThostFtdcOwnerTypeType	OwnerType;
	///��½PBU
	TThostFtdcTraderIDType	LoginPBU;
	///IP��ַ
	TThostFtdcIPAddressType	IPAddress;
};

///ִ������
struct CThostFtdcExecOrderField
{
	///���͹�˾����
	TThostFtdcBrokerIDType	BrokerID;
	///Ͷ���ߴ���
	TThostFtdcInvestorIDType	InvestorID;
	///��Լ����
	TThostFtdcInstrumentIDType	InstrumentID;
	///ִ����������
	TThostFtdcOrderRefType	ExecOrderRef;
	///�û�����
	TThostFtdcUserIDType	UserID;
	///����
	TThostFtdcVolumeType	Volume;
	///������
	TThostFtdcRequestIDType	RequestID;
	///ҵ��Ԫ
	TThostFtdcBusinessUnitType	BusinessUnit;
	///��ƽ��־
	TThostFtdcOffsetFlagType	OffsetFlag;
	///Ͷ���ױ���־
	TThostFtdcHedgeFlagType	HedgeFlag;
	///ִ������
	TThostFtdcActionTypeType	ActionType;
	///����ͷ������ĳֲַ���
	TThostFtdcPosiDirectionType	PosiDirection;
	///��Ȩ��Ȩ���Ƿ����ڻ�ͷ��ı��,���ֶ��ѷ���
	TThostFtdcExecOrderPositionFlagType	ReservePositionFlag;
	///��Ȩ��Ȩ�����ɵ�ͷ���Ƿ��Զ�ƽ��
	TThostFtdcExecOrderCloseFlagType	CloseFlag;
	///����ִ��������
	TThostFtdcOrderLocalIDType	ExecOrderLocalID;
	///����������
	TThostFtdcExchangeIDType	ExchangeID;
	///��Ա����
	TThostFtdcParticipantIDType	ParticipantID;
	///�ͻ�����
	TThostFtdcClientIDType	ClientID;
	///��Լ�ڽ������Ĵ���
	TThostFtdcExchangeInstIDType	ExchangeInstID;
	///����������Ա����
	TThostFtdcTraderIDType	TraderID;
	///��װ���
	TThostFtdcInstallIDType	InstallID;
	///ִ�������ύ״̬
	TThostFtdcOrderSubmitStatusType	OrderSubmitStatus;
	///������ʾ���
	TThostFtdcSequenceNoType	NotifySequence;
	///������
	TThostFtdcDateType	TradingDay;
	///������
	TThostFtdcSettlementIDType	SettlementID;
	///ִ��������
	TThostFtdcExecOrderSysIDType	ExecOrderSysID;
	///��������
	TThostFtdcDateType	InsertDate;
	///����ʱ��
	TThostFtdcTimeType	InsertTime;
	///����ʱ��
	TThostFtdcTimeType	CancelTime;
	///ִ�н��
	TThostFtdcExecResultType	ExecResult;
	///�����Ա���
	TThostFtdcParticipantIDType	ClearingPartID;
	///���
	TThostFtdcSequenceNoType	SequenceNo;
	///ǰ�ñ��
	TThostFtdcFrontIDType	FrontID;
	///�Ự���
	TThostFtdcSessionIDType	SessionID;
	///�û��˲�Ʒ��Ϣ
	TThostFtdcProductInfoType	UserProductInfo;
	///״̬��Ϣ
	TThostFtdcErrorMsgType	StatusMsg;
	///�����û�����
	TThostFtdcUserIDType	ActiveUserID;
	///���͹�˾�������
	TThostFtdcSequenceNoType	BrokerExecOrderSeq;
	///Ӫҵ�����
	TThostFtdcBranchIDType	BranchID;
	///Ͷ�ʵ�Ԫ����
	TThostFtdcInvestUnitIDType	InvestUnitID;
	///�ʽ��˺�
	TThostFtdcAccountIDType	AccountID;
	///���ִ���
	TThostFtdcCurrencyIDType	CurrencyID;
	///��������Ч�ֶ�
	TThostFtdcOldIPAddressType	reserve1;
	///Mac��ַ
	TThostFtdcMacAddressType	MacAddress;
	///����������
	TThostFtdcOwnerTypeType	OwnerType;
	///��½PBU
	TThostFtdcTraderIDType	LoginPBU;
	///IP��ַ
	TThostFtdcIPAddressType	IPAddress;
};

///ִ���������
struct CThostFtdcExecOrderActionField
{
	///���͹�˾����
	TThostFtdcBrokerIDType	BrokerID;
	///Ͷ���ߴ���
	TThostFtdcInvestorIDType	InvestorID;
	///ִ�������������
	TThostFtdcOrderActionRefType	ExecOrderActionRef;
	///ִ����������
	TThostFtdcOrderRefType	ExecOrderRef;
	///������
	TThostFtdcRequestIDType	RequestID;
	///ǰ�ñ��
	TThostFtdcFrontIDType	FrontID;
	///�Ự���
	TThostFtdcSessionIDType	SessionID;
	///����������
	TThostFtdcExchangeIDType	ExchangeID;
	///ִ������������
	TThostFtdcExecOrderSysIDType	ExecOrderSysID;
	///������־
	TThostFtdcActionFlagType	ActionFlag;
	///��������
	TThostFtdcDateType	ActionDate;
	///����ʱ��
	TThostFtdcTimeType	ActionTime;
	///����������Ա����
	TThostFtdcTraderIDType	TraderID;
	///��װ���
	TThostFtdcInstallIDType	InstallID;
	///����ִ��������
	TThostFtdcOrderLocalIDType	ExecOrderLocalID;
	///�������ر��
	TThostFtdcOrderLocalIDType	ActionLocalID;
	///��Ա����
	TThostFtdcParticipantIDType	ParticipantID;
	///�ͻ�����
	TThostFtdcClientIDType	ClientID;
	///ҵ��Ԫ
	TThostFtdcBusinessUnitType	BusinessUnit;
	///��������״̬
	TThostFtdcOrderActionStatusType	OrderActionStatus;
	///�û�����
	TThostFtdcUserIDType	UserID;
	///ִ������
	TThostFtdcActionTypeType	ActionType;
	///״̬��Ϣ
	TThostFtdcErrorMsgType	StatusMsg;
	///��Լ����
	TThostFtdcInstrumentIDType	InstrumentID;
	///Ӫҵ�����
	TThostFtdcBranchIDType	BranchID;
	///Ͷ�ʵ�Ԫ����
	TThostFtdcInvestUnitIDType	InvestUnitID;
	///��������Ч�ֶ�
	TThostFtdcOldIPAddressType	reserve1;
	///Mac��ַ
	TThostFtdcMacAddressType	MacAddress;
	///����������
	TThostFtdcOwnerTypeType	OwnerType;
	///��½PBU
	TThostFtdcTraderIDType	LoginPBU;
	///IP��ַ
	TThostFtdcIPAddressType	IPAddress;
};

///ִ�������ѯ
struct CThostFtdcQryExecOrderField
{
	///���͹�˾����
	TThostFtdcBrokerIDType	BrokerID;
	///Ͷ���ߴ���
	TThostFtdcInvestorIDType	InvestorID;
	///��Լ����
	TThostFtdcInstrumentIDType	InstrumentID;
	///����������
	TThostFtdcExchangeIDType	ExchangeID;
	///ִ��������
	TThostFtdcExecOrderSysIDType	ExecOrderSysID;
	///��ʼʱ��
	TThostFtdcTimeType	InsertTimeStart;
	///����ʱ��
	TThostFtdcTimeType	InsertTimeEnd;
};

///������ִ��������Ϣ
struct CThostFtdcExchangeExecOrderField
{
	///����
	TThostFtdcVolumeType	Volume;
	///������
	TThostFtdcRequestIDType	RequestID;
	///ҵ��Ԫ
	TThostFtdcBusinessUnitType	BusinessUnit;
	///��ƽ��־
	TThostFtdcOffsetFlagType	OffsetFlag;
	///Ͷ���ױ���־
	TThostFtdcHedgeFlagType	HedgeFlag;
	///ִ������
	TThostFtdcActionTypeType	ActionType;
	///����ͷ������ĳֲַ���
	TThostFtdcPosiDirectionType	PosiDirection;
	///��Ȩ��Ȩ���Ƿ����ڻ�ͷ��ı��,���ֶ��ѷ���
	TThostFtdcExecOrderPositionFlagType	ReservePositionFlag;
	///��Ȩ��Ȩ�����ɵ�ͷ���Ƿ��Զ�ƽ��
	TThostFtdcExecOrderCloseFlagType	CloseFlag;
	///����ִ��������
	TThostFtdcOrderLocalIDType	ExecOrderLocalID;
	///����������
	TThostFtdcExchangeIDType	ExchangeID;
	///��Ա����
	TThostFtdcParticipantIDType	ParticipantID;
	///�ͻ�����
	TThostFtdcClientIDType	ClientID;
	///��Լ�ڽ������Ĵ���
	TThostFtdcExchangeInstIDType	ExchangeInstID;
	///����������Ա����
	TThostFtdcTraderIDType	TraderID;
	///��װ���
	TThostFtdcInstallIDType	InstallID;
	///ִ�������ύ״̬
	TThostFtdcOrderSubmitStatusType	OrderSubmitStatus;
	///������ʾ���
	TThostFtdcSequenceNoType	NotifySequence;
	///������
	TThostFtdcDateType	TradingDay;
	///������
	TThostFtdcSettlementIDType	SettlementID;
	///ִ��������
	TThostFtdcExecOrderSysIDType	ExecOrderSysID;
	///��������
	TThostFtdcDateType	InsertDate;
	///����ʱ��
	TThostFtdcTimeType	InsertTime;
	///����ʱ��
	TThostFtdcTimeType	CancelTime;
	///ִ�н��
	TThostFtdcExecResultType	ExecResult;
	///�����Ա���
	TThostFtdcParticipantIDType	ClearingPartID;
	///���
	TThostFtdcSequenceNoType	SequenceNo;
	///Ӫҵ�����
	TThostFtdcBranchIDType	BranchID;
	///��������Ч�ֶ�
	TThostFtdcOldIPAddressType	reserve1;
	///Mac��ַ
	TThostFtdcMacAddressType	MacAddress;
	///����������
	TThostFtdcOwnerTypeType	OwnerType;
	///��½PBU
	TThostFtdcTraderIDType	LoginPBU;
	///IP��ַ
	TThostFtdcIPAddressType	IPAddress;
};

///������ִ�������ѯ
struct CThostFtdcQryExchangeExecOrderField
{
	///��Ա����
	TThostFtdcParticipantIDType	ParticipantID;
	///�ͻ�����
	TThostFtdcClientIDType	ClientID;
	///��Լ�ڽ������Ĵ���
	TThostFtdcExchangeInstIDType	ExchangeInstID;
	///����������
	TThostFtdcExchangeIDType	ExchangeID;
	///����������Ա����
	TThostFtdcTraderIDType	TraderID;
};

///ִ�����������ѯ
struct CThostFtdcQryExecOrderActionField
{
	///���͹�˾����
	TThostFtdcBrokerIDType	BrokerID;
	///Ͷ���ߴ���
	TThostFtdcInvestorIDType	InvestorID;
	///����������
	TThostFtdcExchangeIDType	ExchangeID;
};

///������ִ���������
struct CThostFtdcExchangeExecOrderActionField
{
	///����������
	TThostFtdcExchangeIDType	ExchangeID;
	///ִ������������
	TThostFtdcExecOrderSysIDType	ExecOrderSysID;
	///������־
	TThostFtdcActionFlagType	ActionFlag;
	///��������
	TThostFtdcDateType	ActionDate;
	///����ʱ��
	TThostFtdcTimeType	ActionTime;
	///����������Ա����
	TThostFtdcTraderIDType	TraderID;
	///��װ���
	TThostFtdcInstallIDType	InstallID;
	///����ִ��������
	TThostFtdcOrderLocalIDType	ExecOrderLocalID;
	///�������ر��
	TThostFtdcOrderLocalIDType	ActionLocalID;
	///��Ա����
	TThostFtdcParticipantIDType	ParticipantID;
	///�ͻ�����
	TThostFtdcClientIDType	ClientID;
	///ҵ��Ԫ
	TThostFtdcBusinessUnitType	BusinessUnit;
	///��������״̬
	TThostFtdcOrderActionStatusType	OrderActionStatus;
	///�û�����
	TThostFtdcUserIDType	UserID;
	///ִ������
	TThostFtdcActionTypeType	ActionType;
	///Ӫҵ�����
	TThostFtdcBranchIDType	BranchID;
	///��������Ч�ֶ�
	TThostFtdcOldIPAddressType	reserve1;
	///Mac��ַ
	TThostFtdcMacAddressType	MacAddress;
	///����������
	TThostFtdcOwnerTypeType	OwnerType;
	///��½PBU
	TThostFtdcTraderIDType	LoginPBU;
	///IP��ַ
	TThostFtdcIPAddressType	IPAddress;
};

///������ִ�����������ѯ
struct CThostFtdcQryExchangeExecOrderActionField
{
	///��Ա����
	TThostFtdcParticipantIDType	ParticipantID;
	///�ͻ�����
	TThostFtdcClientIDType	ClientID;
	///����������
	TThostFtdcExchangeIDType	ExchangeID;
	///����������Ա����
	TThostFtdcTraderIDType	TraderID;
};

///����ִ������
struct CThostFtdcErrExecOrderField
{
	///���͹�˾����
	TThostFtdcBrokerIDType	BrokerID;
	///Ͷ���ߴ���
	TThostFtdcInvestorIDType	InvestorID;
	///��Լ����
	TThostFtdcInstrumentIDType	InstrumentID;
	///ִ����������
	TThostFtdcOrderRefType	ExecOrderRef;
	///�û�����
	TThostFtdcUserIDType	UserID;
	///����
	TThostFtdcVolumeType	Volume;
	///������
	TThostFtdcRequestIDType	RequestID;
	///ҵ��Ԫ
	TThostFtdcBusinessUnitType	BusinessUnit;
	///��ƽ��־
	TThostFtdcOffsetFlagType	OffsetFlag;
	///Ͷ���ױ���־
	TThostFtdcHedgeFlagType	HedgeFlag;
	///ִ������
	TThostFtdcActionTypeType	ActionType;
	///����ͷ������ĳֲַ���
	TThostFtdcPosiDirectionType	PosiDirection;
	///��Ȩ��Ȩ���Ƿ����ڻ�ͷ��ı��,���ֶ��ѷ���
	TThostFtdcExecOrderPositionFlagType	ReservePositionFlag;
	///��Ȩ��Ȩ�����ɵ�ͷ���Ƿ��Զ�ƽ��
	TThostFtdcExecOrderCloseFlagType	CloseFlag;
	///����������
	TThostFtdcExchangeIDType	ExchangeID;
	///Ͷ�ʵ�Ԫ����
	TThostFtdcInvestUnitIDType	InvestUnitID;
	///�ʽ��˺�
	TThostFtdcAccountIDType	AccountID;
	///���ִ���
	TThostFtdcCurrencyIDType	CurrencyID;
	///���ױ���
	TThostFtdcClientIDType	ClientID;
	///��������Ч�ֶ�
	TThostFtdcOldIPAddressType	reserve1;
	///Mac��ַ
	TThostFtdcMacAddressType	MacAddress;
	///�������
	TThostFtdcErrorIDType	ErrorID;
	///������Ϣ
	TThostFtdcErrorMsgType	ErrorMsg;
	///IP��ַ
	TThostFtdcIPAddressType	IPAddress;
};

///��ѯ����ִ������
struct CThostFtdcQryErrExecOrderField
{
	///���͹�˾����
	TThostFtdcBrokerIDType	BrokerID;
	///Ͷ���ߴ���
	TThostFtdcInvestorIDType	InvestorID;
};

///����ִ���������
struct CThostFtdcErrExecOrderActionField
{
	///���͹�˾����
	TThostFtdcBrokerIDType	BrokerID;
	///Ͷ���ߴ���
	TThostFtdcInvestorIDType	InvestorID;
	///ִ�������������
	TThostFtdcOrderActionRefType	ExecOrderActionRef;
	///ִ����������
	TThostFtdcOrderRefType	ExecOrderRef;
	///������
	TThostFtdcRequestIDType	RequestID;
	///ǰ�ñ��
	TThostFtdcFrontIDType	FrontID;
	///�Ự���
	TThostFtdcSessionIDType	SessionID;
	///����������
	TThostFtdcExchangeIDType	ExchangeID;
	///ִ������������
	TThostFtdcExecOrderSysIDType	ExecOrderSysID;
	///������־
	TThostFtdcActionFlagType	ActionFlag;
	///�û�����
	TThostFtdcUserIDType	UserID;
	///��Լ����
	TThostFtdcInstrumentIDType	InstrumentID;
	///Ͷ�ʵ�Ԫ����
	TThostFtdcInvestUnitIDType	InvestUnitID;
	///��������Ч�ֶ�
	TThostFtdcOldIPAddressType	reserve1;
	///Mac��ַ
	TThostFtdcMacAddressType	MacAddress;
	///�������
	TThostFtdcErrorIDType	ErrorID;
	///������Ϣ
	TThostFtdcErrorMsgType	ErrorMsg;
	///IP��ַ
	TThostFtdcIPAddressType	IPAddress;
};

///��ѯ����ִ���������
struct CThostFtdcQryErrExecOrderActionField
{
	///���͹�˾����
	TThostFtdcBrokerIDType	BrokerID;
	///Ͷ���ߴ���
	TThostFtdcInvestorIDType	InvestorID;
};

///Ͷ������Ȩ��Լ����Ȩ��
struct CThostFtdcOptionInstrTradingRightField
{
	///��Լ����
	TThostFtdcInstrumentIDType	InstrumentID;
	///Ͷ���߷�Χ
	TThostFtdcInvestorRangeType	InvestorRange;
	///���͹�˾����
	TThostFtdcBrokerIDType	BrokerID;
	///Ͷ���ߴ���
	TThostFtdcInvestorIDType	InvestorID;
	///��������
	TThostFtdcDirectionType	Direction;
	///����Ȩ��
	TThostFtdcTradingRightType	TradingRight;
	///����������
	TThostFtdcExchangeIDType	ExchangeID;
	///Ͷ���ױ���־
	TThostFtdcHedgeFlagType	HedgeFlag;
};

///��ѯ��Ȩ��Լ����Ȩ��
struct CThostFtdcQryOptionInstrTradingRightField
{
	///���͹�˾����
	TThostFtdcBrokerIDType	BrokerID;
	///Ͷ���ߴ���
	TThostFtdcInvestorIDType	InvestorID;
	///��Լ����
	TThostFtdcInstrumentIDType	InstrumentID;
	///��������
	TThostFtdcDirectionType	Direction;
	///����������
	TThostFtdcExchangeIDType	ExchangeID;
};

///�����ѯ��
struct CThostFtdcInputForQuoteField
{
	///���͹�˾����
	TThostFtdcBrokerIDType	BrokerID;
	///Ͷ���ߴ���
	TThostFtdcInvestorIDType	InvestorID;
	///��Լ����
	TThostFtdcInstrumentIDType	InstrumentID;
	///ѯ������
	TThostFtdcOrderRefType	ForQuoteRef;
	///�û�����
	TThostFtdcUserIDType	UserID;
	///����������
	TThostFtdcExchangeIDType	ExchangeID;
	///Ͷ�ʵ�Ԫ����
	TThostFtdcInvestUnitIDType	InvestUnitID;
	///��������Ч�ֶ�
	TThostFtdcOldIPAddressType	reserve1;
	///Mac��ַ
	TThostFtdcMacAddressType	MacAddress;
	///Ӫҵ�����
	TThostFtdcBranchIDType	BranchID;
	///��½PBU
	TThostFtdcTraderIDType	LoginPBU;
	///IP��ַ
	TThostFtdcIPAddressType	IPAddress;
};

///ѯ��
struct CThostFtdcForQuoteField
{
	///���͹�˾����
	TThostFtdcBrokerIDType	BrokerID;
	///Ͷ���ߴ���
	TThostFtdcInvestorIDType	InvestorID;
	///��Լ����
	TThostFtdcInstrumentIDType	InstrumentID;
	///ѯ������
	TThostFtdcOrderRefType	ForQuoteRef;
	///�û�����
	TThostFtdcUserIDType	UserID;
	///����ѯ�۱��
	TThostFtdcOrderLocalIDType	ForQuoteLocalID;
	///����������
	TThostFtdcExchangeIDType	ExchangeID;
	///��Ա����
	TThostFtdcParticipantIDType	ParticipantID;
	///�ͻ�����
	TThostFtdcClientIDType	ClientID;
	///��Լ�ڽ������Ĵ���
	TThostFtdcExchangeInstIDType	ExchangeInstID;
	///����������Ա����
	TThostFtdcTraderIDType	TraderID;
	///��װ���
	TThostFtdcInstallIDType	InstallID;
	///��������
	TThostFtdcDateType	InsertDate;
	///����ʱ��
	TThostFtdcTimeType	InsertTime;
	///ѯ��״̬
	TThostFtdcForQuoteStatusType	ForQuoteStatus;
	///ǰ�ñ��
	TThostFtdcFrontIDType	FrontID;
	///�Ự���
	TThostFtdcSessionIDType	SessionID;
	///״̬��Ϣ
	TThostFtdcErrorMsgType	StatusMsg;
	///�����û�����
	TThostFtdcUserIDType	ActiveUserID;
	///���͹�˾ѯ�۱��
	TThostFtdcSequenceNoType	BrokerForQutoSeq;
	///Ͷ�ʵ�Ԫ����
	TThostFtdcInvestUnitIDType	InvestUnitID;
	///��������Ч�ֶ�
	TThostFtdcOldIPAddressType	reserve1;
	///Mac��ַ
	TThostFtdcMacAddressType	MacAddress;
	///Ӫҵ�����
	TThostFtdcBranchIDType	BranchID;
	///��½PBU
	TThostFtdcTraderIDType	LoginPBU;
	///IP��ַ
	TThostFtdcIPAddressType	IPAddress;
};

///ѯ�۲�ѯ
struct CThostFtdcQryForQuoteField
{
	///���͹�˾����
	TThostFtdcBrokerIDType	BrokerID;
	///Ͷ���ߴ���
	TThostFtdcInvestorIDType	InvestorID;
	///��Լ����
	TThostFtdcInstrumentIDType	InstrumentID;
	///����������
	TThostFtdcExchangeIDType	ExchangeID;
	///��ʼʱ��
	TThostFtdcTimeType	InsertTimeStart;
	///����ʱ��
	TThostFtdcTimeType	InsertTimeEnd;
	///Ͷ�ʵ�Ԫ����
	TThostFtdcInvestUnitIDType	InvestUnitID;
};

///������ѯ����Ϣ
struct CThostFtdcExchangeForQuoteField
{
	///����ѯ�۱��
	TThostFtdcOrderLocalIDType	ForQuoteLocalID;
	///����������
	TThostFtdcExchangeIDType	ExchangeID;
	///��Ա����
	TThostFtdcParticipantIDType	ParticipantID;
	///�ͻ�����
	TThostFtdcClientIDType	ClientID;
	///��Լ�ڽ������Ĵ���
	TThostFtdcExchangeInstIDType	ExchangeInstID;
	///����������Ա����
	TThostFtdcTraderIDType	TraderID;
	///��װ���
	TThostFtdcInstallIDType	InstallID;
	///��������
	TThostFtdcDateType	InsertDate;
	///����ʱ��
	TThostFtdcTimeType	InsertTime;
	///ѯ��״̬
	TThostFtdcForQuoteStatusType	ForQuoteStatus;
	///��������Ч�ֶ�
	TThostFtdcOldIPAddressType	reserve1;
	///Mac��ַ
	TThostFtdcMacAddressType	MacAddress;
	///Ӫҵ�����
	TThostFtdcBranchIDType	BranchID;
	///��½PBU
	TThostFtdcTraderIDType	LoginPBU;
	///IP��ַ
	TThostFtdcIPAddressType	IPAddress;
};

///������ѯ�۲�ѯ
struct CThostFtdcQryExchangeForQuoteField
{
	///��Ա����
	TThostFtdcParticipantIDType	ParticipantID;
	///�ͻ�����
	TThostFtdcClientIDType	ClientID;
	///��Լ�ڽ������Ĵ���
	TThostFtdcExchangeInstIDType	ExchangeInstID;
	///����������
	TThostFtdcExchangeIDType	ExchangeID;
	///����������Ա����
	TThostFtdcTraderIDType	TraderID;
};

///����ı���
struct CThostFtdcInputQuoteField
{
	///���͹�˾����
	TThostFtdcBrokerIDType	BrokerID;
	///Ͷ���ߴ���
	TThostFtdcInvestorIDType	InvestorID;
	///��Լ����
	TThostFtdcInstrumentIDType	InstrumentID;
	///��������
	TThostFtdcOrderRefType	QuoteRef;
	///�û�����
	TThostFtdcUserIDType	UserID;
	///���۸�
	TThostFtdcPriceType	AskPrice;
	///��۸�
	TThostFtdcPriceType	BidPrice;
	///������
	TThostFtdcVolumeType	AskVolume;
	///������
	TThostFtdcVolumeType	BidVolume;
	///������
	TThostFtdcRequestIDType	RequestID;
	///ҵ��Ԫ
	TThostFtdcBusinessUnitType	BusinessUnit;
	///����ƽ��־
	TThostFtdcOffsetFlagType	AskOffsetFlag;
	///��ƽ��־
	TThostFtdcOffsetFlagType	BidOffsetFlag;
	///��Ͷ���ױ���־
	TThostFtdcHedgeFlagType	AskHedgeFlag;
	///��Ͷ���ױ���־
	TThostFtdcHedgeFlagType	BidHedgeFlag;
	///��������������
	TThostFtdcOrderRefType	AskOrderRef;
	///�����򱨵�����
	TThostFtdcOrderRefType	BidOrderRef;
	///Ӧ�۱��
	TThostFtdcOrderSysIDType	ForQuoteSysID;
	///����������
	TThostFtdcExchangeIDType	ExchangeID;
	///Ͷ�ʵ�Ԫ����
	TThostFtdcInvestUnitIDType	InvestUnitID;
	///���ױ���
	TThostFtdcClientIDType	ClientID;
	///��������Ч�ֶ�
	TThostFtdcOldIPAddressType	reserve1;
	///Mac��ַ
	TThostFtdcMacAddressType	MacAddress;
	///IP��ַ
	TThostFtdcIPAddressType	IPAddress;
};

///���뱨�۲���
struct CThostFtdcInputQuoteActionField
{
	///���͹�˾����
	TThostFtdcBrokerIDType	BrokerID;
	///Ͷ���ߴ���
	TThostFtdcInvestorIDType	InvestorID;
	///���۲�������
	TThostFtdcOrderActionRefType	QuoteActionRef;
	///��������
	TThostFtdcOrderRefType	QuoteRef;
	///������
	TThostFtdcRequestIDType	RequestID;
	///ǰ�ñ��
	TThostFtdcFrontIDType	FrontID;
	///�Ự���
	TThostFtdcSessionIDType	SessionID;
	///����������
	TThostFtdcExchangeIDType	ExchangeID;
	///���۲������
	TThostFtdcOrderSysIDType	QuoteSysID;
	///������־
	TThostFtdcActionFlagType	ActionFlag;
	///�û�����
	TThostFtdcUserIDType	UserID;
	///��Լ����
	TThostFtdcInstrumentIDType	InstrumentID;
	///Ͷ�ʵ�Ԫ����
	TThostFtdcInvestUnitIDType	InvestUnitID;
	///���ױ���
	TThostFtdcClientIDType	ClientID;
	///��������Ч�ֶ�
	TThostFtdcOldIPAddressType	reserve1;
	///Mac��ַ
	TThostFtdcMacAddressType	MacAddress;
	///������
	TThostFtdcVolumeType	AskVolume;
	///������
	TThostFtdcVolumeType	BidVolume;
	///IP��ַ
	TThostFtdcIPAddressType	IPAddress;
};

///����
struct CThostFtdcQuoteField
{
	///���͹�˾����
	TThostFtdcBrokerIDType	BrokerID;
	///Ͷ���ߴ���
	TThostFtdcInvestorIDType	InvestorID;
	///��Լ����
	TThostFtdcInstrumentIDType	InstrumentID;
	///��������
	TThostFtdcOrderRefType	QuoteRef;
	///�û�����
	TThostFtdcUserIDType	UserID;
	///���۸�
	TThostFtdcPriceType	AskPrice;
	///��۸�
	TThostFtdcPriceType	BidPrice;
	///������
	TThostFtdcVolumeType	AskVolume;
	///������
	TThostFtdcVolumeType	BidVolume;
	///������
	TThostFtdcRequestIDType	RequestID;
	///ҵ��Ԫ
	TThostFtdcBusinessUnitType	BusinessUnit;
	///����ƽ��־
	TThostFtdcOffsetFlagType	AskOffsetFlag;
	///��ƽ��־
	TThostFtdcOffsetFlagType	BidOffsetFlag;
	///��Ͷ���ױ���־
	TThostFtdcHedgeFlagType	AskHedgeFlag;
	///��Ͷ���ױ���־
	TThostFtdcHedgeFlagType	BidHedgeFlag;
	///���ر��۱��
	TThostFtdcOrderLocalIDType	QuoteLocalID;
	///����������
	TThostFtdcExchangeIDType	ExchangeID;
	///��Ա����
	TThostFtdcParticipantIDType	ParticipantID;
	///�ͻ�����
	TThostFtdcClientIDType	ClientID;
	///��Լ�ڽ������Ĵ���
	TThostFtdcExchangeInstIDType	ExchangeInstID;
	///����������Ա����
	TThostFtdcTraderIDType	TraderID;
	///��װ���
	TThostFtdcInstallIDType	InstallID;
	///������ʾ���
	TThostFtdcSequenceNoType	NotifySequence;
	///�����ύ״̬
	TThostFtdcOrderSubmitStatusType	OrderSubmitStatus;
	///������
	TThostFtdcDateType	TradingDay;
	///������
	TThostFtdcSettlementIDType	SettlementID;
	///���۱��
	TThostFtdcOrderSysIDType	QuoteSysID;
	///��������
	TThostFtdcDateType	InsertDate;
	///����ʱ��
	TThostFtdcTimeType	InsertTime;
	///����ʱ��
	TThostFtdcTimeType	CancelTime;
	///����״̬
	TThostFtdcOrderStatusType	QuoteStatus;
	///�����Ա���
	TThostFtdcParticipantIDType	ClearingPartID;
	///���
	TThostFtdcSequenceNoType	SequenceNo;
	///�����������
	TThostFtdcOrderSysIDType	AskOrderSysID;
	///�򷽱������
	TThostFtdcOrderSysIDType	BidOrderSysID;
	///ǰ�ñ��
	TThostFtdcFrontIDType	FrontID;
	///�Ự���
	TThostFtdcSessionIDType	SessionID;
	///�û��˲�Ʒ��Ϣ
	TThostFtdcProductInfoType	UserProductInfo;
	///״̬��Ϣ
	TThostFtdcErrorMsgType	StatusMsg;
	///�����û�����
	TThostFtdcUserIDType	ActiveUserID;
	///���͹�˾���۱��
	TThostFtdcSequenceNoType	BrokerQuoteSeq;
	///��������������
	TThostFtdcOrderRefType	AskOrderRef;
	///�����򱨵�����
	TThostFtdcOrderRefType	BidOrderRef;
	///Ӧ�۱��
	TThostFtdcOrderSysIDType	ForQuoteSysID;
	///Ӫҵ�����
	TThostFtdcBranchIDType	BranchID;
	///Ͷ�ʵ�Ԫ����
	TThostFtdcInvestUnitIDType	InvestUnitID;
	///�ʽ��˺�
	TThostFtdcAccountIDType	AccountID;
	///���ִ���
	TThostFtdcCurrencyIDType	CurrencyID;
	///��������Ч�ֶ�
	TThostFtdcOldIPAddressType	reserve1;
	///Mac��ַ
	TThostFtdcMacAddressType	MacAddress;
	///��½PBU
	TThostFtdcTraderIDType	LoginPBU;
	///IP��ַ
	TThostFtdcIPAddressType	IPAddress;
};

///���۲���
struct CThostFtdcQuoteActionField
{
	///���͹�˾����
	TThostFtdcBrokerIDType	BrokerID;
	///Ͷ���ߴ���
	TThostFtdcInvestorIDType	InvestorID;
	///���۲�������
	TThostFtdcOrderActionRefType	QuoteActionRef;
	///��������
	TThostFtdcOrderRefType	QuoteRef;
	///������
	TThostFtdcRequestIDType	RequestID;
	///ǰ�ñ��
	TThostFtdcFrontIDType	FrontID;
	///�Ự���
	TThostFtdcSessionIDType	SessionID;
	///����������
	TThostFtdcExchangeIDType	ExchangeID;
	///���۲������
	TThostFtdcOrderSysIDType	QuoteSysID;
	///������־
	TThostFtdcActionFlagType	ActionFlag;
	///��������
	TThostFtdcDateType	ActionDate;
	///����ʱ��
	TThostFtdcTimeType	ActionTime;
	///����������Ա����
	TThostFtdcTraderIDType	TraderID;
	///��װ���
	TThostFtdcInstallIDType	InstallID;
	///���ر��۱��
	TThostFtdcOrderLocalIDType	QuoteLocalID;
	///�������ر��
	TThostFtdcOrderLocalIDType	ActionLocalID;
	///��Ա����
	TThostFtdcParticipantIDType	ParticipantID;
	///�ͻ�����
	TThostFtdcClientIDType	ClientID;
	///ҵ��Ԫ
	TThostFtdcBusinessUnitType	BusinessUnit;
	///��������״̬
	TThostFtdcOrderActionStatusType	OrderActionStatus;
	///�û�����
	TThostFtdcUserIDType	UserID;
	///״̬��Ϣ
	TThostFtdcErrorMsgType	StatusMsg;
	///��Լ����
	TThostFtdcInstrumentIDType	InstrumentID;
	///Ӫҵ�����
	TThostFtdcBranchIDType	BranchID;
	///Ͷ�ʵ�Ԫ����
	TThostFtdcInvestUnitIDType	InvestUnitID;
	///��������Ч�ֶ�
	TThostFtdcOldIPAddressType	reserve1;
	///Mac��ַ
	TThostFtdcMacAddressType	MacAddress;
	///������
	TThostFtdcVolumeType	AskVolume;
	///������
	TThostFtdcVolumeType	BidVolume;
	///��½PBU
	TThostFtdcTraderIDType	LoginPBU;
	///IP��ַ
	TThostFtdcIPAddressType	IPAddress;
};

///���۲�ѯ
struct CThostFtdcQryQuoteField
{
	///���͹�˾����
	TThostFtdcBrokerIDType	BrokerID;
	///Ͷ���ߴ���
	TThostFtdcInvestorIDType	InvestorID;
	///��Լ����
	TThostFtdcInstrumentIDType	InstrumentID;
	///����������
	TThostFtdcExchangeIDType	ExchangeID;
	///���۱��
	TThostFtdcOrderSysIDType	QuoteSysID;
	///��ʼʱ��
	TThostFtdcTimeType	InsertTimeStart;
	///����ʱ��
	TThostFtdcTimeType	InsertTimeEnd;
	///Ͷ�ʵ�Ԫ����
	TThostFtdcInvestUnitIDType	InvestUnitID;
};

///������������Ϣ
struct CThostFtdcExchangeQuoteField
{
	///���۸�
	TThostFtdcPriceType	AskPrice;
	///��۸�
	TThostFtdcPriceType	BidPrice;
	///������
	TThostFtdcVolumeType	AskVolume;
	///������
	TThostFtdcVolumeType	BidVolume;
	///������
	TThostFtdcRequestIDType	RequestID;
	///ҵ��Ԫ
	TThostFtdcBusinessUnitType	BusinessUnit;
	///����ƽ��־
	TThostFtdcOffsetFlagType	AskOffsetFlag;
	///��ƽ��־
	TThostFtdcOffsetFlagType	BidOffsetFlag;
	///��Ͷ���ױ���־
	TThostFtdcHedgeFlagType	AskHedgeFlag;
	///��Ͷ���ױ���־
	TThostFtdcHedgeFlagType	BidHedgeFlag;
	///���ر��۱��
	TThostFtdcOrderLocalIDType	QuoteLocalID;
	///����������
	TThostFtdcExchangeIDType	ExchangeID;
	///��Ա����
	TThostFtdcParticipantIDType	ParticipantID;
	///�ͻ�����
	TThostFtdcClientIDType	ClientID;
	///��Լ�ڽ������Ĵ���
	TThostFtdcExchangeInstIDType	ExchangeInstID;
	///����������Ա����
	TThostFtdcTraderIDType	TraderID;
	///��װ���
	TThostFtdcInstallIDType	InstallID;
	///������ʾ���
	TThostFtdcSequenceNoType	NotifySequence;
	///�����ύ״̬
	TThostFtdcOrderSubmitStatusType	OrderSubmitStatus;
	///������
	TThostFtdcDateType	TradingDay;
	///������
	TThostFtdcSettlementIDType	SettlementID;
	///���۱��
	TThostFtdcOrderSysIDType	QuoteSysID;
	///��������
	TThostFtdcDateType	InsertDate;
	///����ʱ��
	TThostFtdcTimeType	InsertTime;
	///����ʱ��
	TThostFtdcTimeType	CancelTime;
	///����״̬
	TThostFtdcOrderStatusType	QuoteStatus;
	///�����Ա���
	TThostFtdcParticipantIDType	ClearingPartID;
	///���
	TThostFtdcSequenceNoType	SequenceNo;
	///�����������
	TThostFtdcOrderSysIDType	AskOrderSysID;
	///�򷽱������
	TThostFtdcOrderSysIDType	BidOrderSysID;
	///Ӧ�۱��
	TThostFtdcOrderSysIDType	ForQuoteSysID;
	///Ӫҵ�����
	TThostFtdcBranchIDType	BranchID;
	///��������Ч�ֶ�
	TThostFtdcOldIPAddressType	reserve1;
	///Mac��ַ
	TThostFtdcMacAddressType	MacAddress;
	///��½PBU
	TThostFtdcTraderIDType	LoginPBU;
	///IP��ַ
	TThostFtdcIPAddressType	IPAddress;
};

///���������۲�ѯ
struct CThostFtdcQryExchangeQuoteField
{
	///��Ա����
	TThostFtdcParticipantIDType	ParticipantID;
	///�ͻ�����
	TThostFtdcClientIDType	ClientID;
	///��Լ�ڽ������Ĵ���
	TThostFtdcExchangeInstIDType	ExchangeInstID;
	///����������
	TThostFtdcExchangeIDType	ExchangeID;
	///����������Ա����
	TThostFtdcTraderIDType	TraderID;
};

///���۲�����ѯ
struct CThostFtdcQryQuoteActionField
{
	///���͹�˾����
	TThostFtdcBrokerIDType	BrokerID;
	///Ͷ���ߴ���
	TThostFtdcInvestorIDType	InvestorID;
	///����������
	TThostFtdcExchangeIDType	ExchangeID;
};

///���������۲���
struct CThostFtdcExchangeQuoteActionField
{
	///����������
	TThostFtdcExchangeIDType	ExchangeID;
	///���۲������
	TThostFtdcOrderSysIDType	QuoteSysID;
	///������־
	TThostFtdcActionFlagType	ActionFlag;
	///��������
	TThostFtdcDateType	ActionDate;
	///����ʱ��
	TThostFtdcTimeType	ActionTime;
	///����������Ա����
	TThostFtdcTraderIDType	TraderID;
	///��װ���
	TThostFtdcInstallIDType	InstallID;
	///���ر��۱��
	TThostFtdcOrderLocalIDType	QuoteLocalID;
	///�������ر��
	TThostFtdcOrderLocalIDType	ActionLocalID;
	///��Ա����
	TThostFtdcParticipantIDType	ParticipantID;
	///�ͻ�����
	TThostFtdcClientIDType	ClientID;
	///ҵ��Ԫ
	TThostFtdcBusinessUnitType	BusinessUnit;
	///��������״̬
	TThostFtdcOrderActionStatusType	OrderActionStatus;
	///�û�����
	TThostFtdcUserIDType	UserID;
	///��������Ч�ֶ�
	TThostFtdcOldIPAddressType	reserve1;
	///Mac��ַ
	TThostFtdcMacAddressType	MacAddress;
	///Ӫҵ�����
	TThostFtdcBranchIDType	BranchID;
	///������
	TThostFtdcVolumeType	AskVolume;
	///������
	TThostFtdcVolumeType	BidVolume;
	///��½PBU
	TThostFtdcTraderIDType	LoginPBU;
	///IP��ַ
	TThostFtdcIPAddressType	IPAddress;
};

///���������۲�����ѯ
struct CThostFtdcQryExchangeQuoteActionField
{
	///��Ա����
	TThostFtdcParticipantIDType	ParticipantID;
	///�ͻ�����
	TThostFtdcClientIDType	ClientID;
	///����������
	TThostFtdcExchangeIDType	ExchangeID;
	///����������Ա����
	TThostFtdcTraderIDType	TraderID;
};

///��Ȩ��Լdeltaֵ
struct CThostFtdcOptionInstrDeltaField
{
	///��Լ����
	TThostFtdcInstrumentIDType	InstrumentID;
	///Ͷ���߷�Χ
	TThostFtdcInvestorRangeType	InvestorRange;
	///���͹�˾����
	TThostFtdcBrokerIDType	BrokerID;
	///Ͷ���ߴ���
	TThostFtdcInvestorIDType	InvestorID;
	///Deltaֵ
	TThostFtdcRatioType	Delta;
	///����������
	TThostFtdcExchangeIDType	ExchangeID;
};

///���������̵�ѯ������
struct CThostFtdcForQuoteRspField
{
	///������
	TThostFtdcDateType	TradingDay;
	///��Լ����
	TThostFtdcInstrumentIDType	InstrumentID;
	///ѯ�۱��
	TThostFtdcOrderSysIDType	ForQuoteSysID;
	///ѯ��ʱ��
	TThostFtdcTimeType	ForQuoteTime;
	///ҵ������
	TThostFtdcDateType	ActionDay;
	///����������
	TThostFtdcExchangeIDType	ExchangeID;
};

///��ǰ��Ȩ��Լִ��ƫ��ֵ����ϸ����
struct CThostFtdcStrikeOffsetField
{
	///��Լ����
	TThostFtdcInstrumentIDType	InstrumentID;
	///Ͷ���߷�Χ
	TThostFtdcInvestorRangeType	InvestorRange;
	///���͹�˾����
	TThostFtdcBrokerIDType	BrokerID;
	///Ͷ���ߴ���
	TThostFtdcInvestorIDType	InvestorID;
	///ִ��ƫ��ֵ
	TThostFtdcMoneyType	Offset;
	///��Ȩƫ������
	TThostFtdcStrikeOffsetTypeType	OffsetType;
	///����������
	TThostFtdcExchangeIDType	ExchangeID;
};

///��Ȩִ��ƫ��ֵ��ѯ
struct CThostFtdcQryStrikeOffsetField
{
	///���͹�˾����
	TThostFtdcBrokerIDType	BrokerID;
	///Ͷ���ߴ���
	TThostFtdcInvestorIDType	InvestorID;
	///��Լ����
	TThostFtdcInstrumentIDType	InstrumentID;
};

///¼������
struct CThostFtdcInputLockField
{
	///���͹�˾����
	TThostFtdcBrokerIDType	BrokerID;
	///Ͷ���ߴ���
	TThostFtdcInvestorIDType	InvestorID;
	///��Լ����
	TThostFtdcInstrumentIDType	InstrumentID;
	///��������
	TThostFtdcOrderRefType	LockRef;
	///�û�����
	TThostFtdcUserIDType	UserID;
	///����
	TThostFtdcVolumeType	Volume;
	///������
	TThostFtdcRequestIDType	RequestID;
	///ҵ��Ԫ
	TThostFtdcBusinessUnitType	BusinessUnit;
	///��������
	TThostFtdcLockTypeType	LockType;
	///����������
	TThostFtdcExchangeIDType	ExchangeID;
	///��������Ч�ֶ�
	TThostFtdcOldIPAddressType	reserve1;
	///Mac��ַ
	TThostFtdcMacAddressType	MacAddress;
	///IP��ַ
	TThostFtdcIPAddressType	IPAddress;
};

///����
struct CThostFtdcLockField
{
	///���͹�˾����
	TThostFtdcBrokerIDType	BrokerID;
	///Ͷ���ߴ���
	TThostFtdcInvestorIDType	InvestorID;
	///��Լ����
	TThostFtdcInstrumentIDType	InstrumentID;
	///��������
	TThostFtdcOrderRefType	LockRef;
	///�û�����
	TThostFtdcUserIDType	UserID;
	///����
	TThostFtdcVolumeType	Volume;
	///������
	TThostFtdcRequestIDType	RequestID;
	///ҵ��Ԫ
	TThostFtdcBusinessUnitType	BusinessUnit;
	///��������
	TThostFtdcLockTypeType	LockType;
	///�����������
	TThostFtdcOrderLocalIDType	LockLocalID;
	///����������
	TThostFtdcExchangeIDType	ExchangeID;
	///��Ա����
	TThostFtdcParticipantIDType	ParticipantID;
	///�ͻ�����
	TThostFtdcClientIDType	ClientID;
	///��Լ�ڽ������Ĵ���
	TThostFtdcExchangeInstIDType	ExchangeInstID;
	///����������Ա����
	TThostFtdcTraderIDType	TraderID;
	///��װ���
	TThostFtdcInstallIDType	InstallID;
	///ִ�������ύ״̬
	TThostFtdcOrderSubmitStatusType	OrderSubmitStatus;
	///������ʾ���
	TThostFtdcSequenceNoType	NotifySequence;
	///������
	TThostFtdcDateType	TradingDay;
	///������
	TThostFtdcSettlementIDType	SettlementID;
	///�������
	TThostFtdcOrderSysIDType	LockSysID;
	///��������
	TThostFtdcDateType	InsertDate;
	///����ʱ��
	TThostFtdcTimeType	InsertTime;
	///����ʱ��
	TThostFtdcTimeType	CancelTime;
	///����״̬
	TThostFtdcOrderActionStatusType	LockStatus;
	///�����Ա���
	TThostFtdcParticipantIDType	ClearingPartID;
	///���
	TThostFtdcSequenceNoType	SequenceNo;
	///ǰ�ñ��
	TThostFtdcFrontIDType	FrontID;
	///�Ự���
	TThostFtdcSessionIDType	SessionID;
	///�û��˲�Ʒ��Ϣ
	TThostFtdcProductInfoType	UserProductInfo;
	///״̬��Ϣ
	TThostFtdcErrorMsgType	StatusMsg;
	///�����û�����
	TThostFtdcUserIDType	ActiveUserID;
	///���͹�˾�������
	TThostFtdcSequenceNoType	BrokerLockSeq;
	///Ӫҵ�����
	TThostFtdcBranchIDType	BranchID;
	///��������Ч�ֶ�
	TThostFtdcOldIPAddressType	reserve1;
	///Mac��ַ
	TThostFtdcMacAddressType	MacAddress;
	///��½PBU
	TThostFtdcTraderIDType	LoginPBU;
	///IP��ַ
	TThostFtdcIPAddressType	IPAddress;
};

///��ѯ����
struct CThostFtdcQryLockField
{
	///���͹�˾����
	TThostFtdcBrokerIDType	BrokerID;
	///Ͷ���ߴ���
	TThostFtdcInvestorIDType	InvestorID;
	///��Լ����
	TThostFtdcInstrumentIDType	InstrumentID;
	///����������
	TThostFtdcExchangeIDType	ExchangeID;
	///�������
	TThostFtdcOrderSysIDType	LockSysID;
	///��ʼʱ��
	TThostFtdcTimeType	InsertTimeStart;
	///����ʱ��
	TThostFtdcTimeType	InsertTimeEnd;
};

///����֤ȯ��λ
struct CThostFtdcLockPositionField
{
	///���͹�˾����
	TThostFtdcBrokerIDType	BrokerID;
	///Ͷ���ߴ���
	TThostFtdcInvestorIDType	InvestorID;
	///��Լ����
	TThostFtdcInstrumentIDType	InstrumentID;
	///����������
	TThostFtdcExchangeIDType	ExchangeID;
	///����
	TThostFtdcVolumeType	Volume;
	///��������
	TThostFtdcVolumeType	FrozenVolume;
	///������������
	TThostFtdcVolumeType	TodayVolume;
};

///��ѯ����֤ȯ��λ
struct CThostFtdcQryLockPositionField
{
	///���͹�˾����
	TThostFtdcBrokerIDType	BrokerID;
	///Ͷ���ߴ���
	TThostFtdcInvestorIDType	InvestorID;
	///��Լ����
	TThostFtdcInstrumentIDType	InstrumentID;
	///����������
	TThostFtdcExchangeIDType	ExchangeID;
};

///��ǰETF��Ȩ��Լ�����ѵ���ϸ����
struct CThostFtdcETFOptionInstrCommRateField
{
	///��Լ����
	TThostFtdcInstrumentIDType	InstrumentID;
	///Ͷ���߷�Χ
	TThostFtdcInvestorRangeType	InvestorRange;
	///���͹�˾����
	TThostFtdcBrokerIDType	BrokerID;
	///Ͷ���ߴ���
	TThostFtdcInvestorIDType	InvestorID;
	///������������
	TThostFtdcRatioType	OpenRatioByMoney;
	///����������
	TThostFtdcRatioType	OpenRatioByVolume;
	///ƽ����������
	TThostFtdcRatioType	CloseRatioByMoney;
	///ƽ��������
	TThostFtdcRatioType	CloseRatioByVolume;
	///ƽ����������
	TThostFtdcRatioType	CloseTodayRatioByMoney;
	///ƽ��������
	TThostFtdcRatioType	CloseTodayRatioByVolume;
	///ִ����������
	TThostFtdcRatioType	StrikeRatioByMoney;
	///ִ��������
	TThostFtdcRatioType	StrikeRatioByVolume;
	///����������
	TThostFtdcExchangeIDType	ExchangeID;
	///Ͷ���ױ���־
	TThostFtdcHedgeFlagType	HedgeFlag;
	///�ֲַ���
	TThostFtdcPosiDirectionType	PosiDirection;
};

///ETF��Ȩ�������ʲ�ѯ
struct CThostFtdcQryETFOptionInstrCommRateField
{
	///���͹�˾����
	TThostFtdcBrokerIDType	BrokerID;
	///Ͷ���ߴ���
	TThostFtdcInvestorIDType	InvestorID;
	///��Լ����
	TThostFtdcInstrumentIDType	InstrumentID;
	///����������
	TThostFtdcExchangeIDType	ExchangeID;
};

///����ĳֲֶ���
struct CThostFtdcPosiFreezeField
{
	///���͹�˾����
	TThostFtdcBrokerIDType	BrokerID;
	///Ͷ���ߴ���
	TThostFtdcInvestorIDType	InvestorID;
	///��Լ����
	TThostFtdcInstrumentIDType	InstrumentID;
	///����������
	TThostFtdcExchangeIDType	ExchangeID;
	///���ر������
	TThostFtdcOrderLocalIDType	OrderLocalID;
	///����������Ա����
	TThostFtdcTraderIDType	TraderID;
	///��Ա����
	TThostFtdcParticipantIDType	ParticipantID;
	///��װ���
	TThostFtdcInstallIDType	InstallID;
	///����
	TThostFtdcVolumeType	Volume;
	///����ԭ��
	TThostFtdcFreezeReasonTypeType	FreezeReasonType;
	///��������
	TThostFtdcFreezeTypeType	FreezeType;
	///��½PBU
	TThostFtdcTraderIDType	LoginPBU;
};

///��ѯ����
struct CThostFtdcQryExchangeLockField
{
	///��Ա����
	TThostFtdcParticipantIDType	ParticipantID;
	///�ͻ�����
	TThostFtdcClientIDType	ClientID;
	///��Լ�ڽ������Ĵ���
	TThostFtdcExchangeInstIDType	ExchangeInstID;
	///����������
	TThostFtdcExchangeIDType	ExchangeID;
	///����������Ա����
	TThostFtdcTraderIDType	TraderID;
};

///����������
struct CThostFtdcExchangeLockField
{
	///����
	TThostFtdcVolumeType	Volume;
	///������
	TThostFtdcRequestIDType	RequestID;
	///ҵ��Ԫ
	TThostFtdcBusinessUnitType	BusinessUnit;
	///��������
	TThostFtdcLockTypeType	LockType;
	///�����������
	TThostFtdcOrderLocalIDType	LockLocalID;
	///����������
	TThostFtdcExchangeIDType	ExchangeID;
	///��Ա����
	TThostFtdcParticipantIDType	ParticipantID;
	///�ͻ�����
	TThostFtdcClientIDType	ClientID;
	///��Լ�ڽ������Ĵ���
	TThostFtdcExchangeInstIDType	ExchangeInstID;
	///����������Ա����
	TThostFtdcTraderIDType	TraderID;
	///��װ���
	TThostFtdcInstallIDType	InstallID;
	///ִ�������ύ״̬
	TThostFtdcOrderSubmitStatusType	OrderSubmitStatus;
	///������ʾ���
	TThostFtdcSequenceNoType	NotifySequence;
	///������
	TThostFtdcDateType	TradingDay;
	///������
	TThostFtdcSettlementIDType	SettlementID;
	///�������
	TThostFtdcOrderSysIDType	LockSysID;
	///��������
	TThostFtdcDateType	InsertDate;
	///����ʱ��
	TThostFtdcTimeType	InsertTime;
	///����ʱ��
	TThostFtdcTimeType	CancelTime;
	///����״̬
	TThostFtdcOrderActionStatusType	LockStatus;
	///�����Ա���
	TThostFtdcParticipantIDType	ClearingPartID;
	///���
	TThostFtdcSequenceNoType	SequenceNo;
	///Ӫҵ�����
	TThostFtdcBranchIDType	BranchID;
	///��������Ч�ֶ�
	TThostFtdcOldIPAddressType	reserve1;
	///Mac��ַ
	TThostFtdcMacAddressType	MacAddress;
	///��½PBU
	TThostFtdcTraderIDType	LoginPBU;
	///IP��ַ
	TThostFtdcIPAddressType	IPAddress;
};

///��������������
struct CThostFtdcExchangeExecOrderActionErrorField
{
	///����������
	TThostFtdcExchangeIDType	ExchangeID;
	///ִ��������
	TThostFtdcExecOrderSysIDType	ExecOrderSysID;
	///����������Ա����
	TThostFtdcTraderIDType	TraderID;
	///��װ���
	TThostFtdcInstallIDType	InstallID;
	///����ִ��������
	TThostFtdcOrderLocalIDType	ExecOrderLocalID;
	///�������ر��
	TThostFtdcOrderLocalIDType	ActionLocalID;
	///�������
	TThostFtdcErrorIDType	ErrorID;
	///������Ϣ
	TThostFtdcErrorMsgType	ErrorMsg;
	///���͹�˾����
	TThostFtdcBrokerIDType	BrokerID;
	///�ͻ�����
	TThostFtdcClientIDType	ClientID;
	///��½PBU
	TThostFtdcTraderIDType	LoginPBU;
};

///����������������
struct CThostFtdcInputBatchOrderActionField
{
	///���͹�˾����
	TThostFtdcBrokerIDType	BrokerID;
	///Ͷ���ߴ���
	TThostFtdcInvestorIDType	InvestorID;
	///������������
	TThostFtdcOrderActionRefType	OrderActionRef;
	///������
	TThostFtdcRequestIDType	RequestID;
	///ǰ�ñ��
	TThostFtdcFrontIDType	FrontID;
	///�Ự���
	TThostFtdcSessionIDType	SessionID;
	///����������
	TThostFtdcExchangeIDType	ExchangeID;
	///�û�����
	TThostFtdcUserIDType	UserID;
	///Ͷ�ʵ�Ԫ����
	TThostFtdcInvestUnitIDType	InvestUnitID;
	///��������Ч�ֶ�
	TThostFtdcOldIPAddressType	reserve1;
	///Mac��ַ
	TThostFtdcMacAddressType	MacAddress;
	///IP��ַ
	TThostFtdcIPAddressType	IPAddress;
};

///������������
struct CThostFtdcBatchOrderActionField
{
	///���͹�˾����
	TThostFtdcBrokerIDType	BrokerID;
	///Ͷ���ߴ���
	TThostFtdcInvestorIDType	InvestorID;
	///������������
	TThostFtdcOrderActionRefType	OrderActionRef;
	///������
	TThostFtdcRequestIDType	RequestID;
	///ǰ�ñ��
	TThostFtdcFrontIDType	FrontID;
	///�Ự���
	TThostFtdcSessionIDType	SessionID;
	///����������
	TThostFtdcExchangeIDType	ExchangeID;
	///��������
	TThostFtdcDateType	ActionDate;
	///����ʱ��
	TThostFtdcTimeType	ActionTime;
	///����������Ա����
	TThostFtdcTraderIDType	TraderID;
	///��װ���
	TThostFtdcInstallIDType	InstallID;
	///�������ر��
	TThostFtdcOrderLocalIDType	ActionLocalID;
	///��Ա����
	TThostFtdcParticipantIDType	ParticipantID;
	///�ͻ�����
	TThostFtdcClientIDType	ClientID;
	///ҵ��Ԫ
	TThostFtdcBusinessUnitType	BusinessUnit;
	///��������״̬
	TThostFtdcOrderActionStatusType	OrderActionStatus;
	///�û�����
	TThostFtdcUserIDType	UserID;
	///״̬��Ϣ
	TThostFtdcErrorMsgType	StatusMsg;
	///Ͷ�ʵ�Ԫ����
	TThostFtdcInvestUnitIDType	InvestUnitID;
	///��������Ч�ֶ�
	TThostFtdcOldIPAddressType	reserve1;
	///Mac��ַ
	TThostFtdcMacAddressType	MacAddress;
	///IP��ַ
	TThostFtdcIPAddressType	IPAddress;
};

///������������������
struct CThostFtdcExchangeBatchOrderActionField
{
	///����������
	TThostFtdcExchangeIDType	ExchangeID;
	///��������
	TThostFtdcDateType	ActionDate;
	///����ʱ��
	TThostFtdcTimeType	ActionTime;
	///����������Ա����
	TThostFtdcTraderIDType	TraderID;
	///��װ���
	TThostFtdcInstallIDType	InstallID;
	///�������ر��
	TThostFtdcOrderLocalIDType	ActionLocalID;
	///��Ա����
	TThostFtdcParticipantIDType	ParticipantID;
	///�ͻ�����
	TThostFtdcClientIDType	ClientID;
	///ҵ��Ԫ
	TThostFtdcBusinessUnitType	BusinessUnit;
	///��������״̬
	TThostFtdcOrderActionStatusType	OrderActionStatus;
	///�û�����
	TThostFtdcUserIDType	UserID;
	///��������Ч�ֶ�
	TThostFtdcOldIPAddressType	reserve1;
	///Mac��ַ
	TThostFtdcMacAddressType	MacAddress;
	///IP��ַ
	TThostFtdcIPAddressType	IPAddress;
};

///��ѯ������������
struct CThostFtdcQryBatchOrderActionField
{
	///���͹�˾����
	TThostFtdcBrokerIDType	BrokerID;
	///Ͷ���ߴ���
	TThostFtdcInvestorIDType	InvestorID;
	///����������
	TThostFtdcExchangeIDType	ExchangeID;
};

///Ͷ���ֲ߳�����
struct CThostFtdcLimitPosiField
{
	///���͹�˾����
	TThostFtdcBrokerIDType	BrokerID;
	///Ͷ���ߴ���
	TThostFtdcInvestorIDType	InvestorID;
	///��Լ����
	TThostFtdcInstrumentIDType	InstrumentID;
	///����������
	TThostFtdcExchangeIDType	ExchangeID;
	///����������
	TThostFtdcVolumeType	TotalVolume;
	///��ͷ��������
	TThostFtdcVolumeType	LongVolume;
	///���ն�ͷ������������
	TThostFtdcVolumeType	OpenVolume;
	///��ͷ�ֲֽ������,����ʹ��
	TThostFtdcMoneyType	LongAmount;
	///����������
	TThostFtdcVolumeType	TotalVolumeFrozen;
	///��ͷ��������
	TThostFtdcVolumeType	LongVolumeFrozen;
	///���տ�����������
	TThostFtdcVolumeType	OpenVolumeFrozen;
	///��ͷ�ֲֽ���,����ʹ��
	TThostFtdcMoneyType	LongAmountFrozen;
};

///��ѯͶ���ֲ߳�����
struct CThostFtdcQryLimitPosiField
{
	///���͹�˾����
	TThostFtdcBrokerIDType	BrokerID;
	///Ͷ���ߴ���
	TThostFtdcInvestorIDType	InvestorID;
	///��Լ����
	TThostFtdcInstrumentIDType	InstrumentID;
	///����������
	TThostFtdcExchangeIDType	ExchangeID;
};

///���͹�˾�ֲ�����
struct CThostFtdcBrokerLimitPosiField
{
	///���͹�˾����
	TThostFtdcBrokerIDType	BrokerID;
	///��Լ����
	TThostFtdcInstrumentIDType	InstrumentID;
	///����������
	TThostFtdcExchangeIDType	ExchangeID;
	///����������
	TThostFtdcLargeVolumeType	TotalVolume;
	///��ͷ��������
	TThostFtdcLargeVolumeType	LongVolume;
	///����������
	TThostFtdcLargeVolumeType	TotalVolumeFrozen;
	///��ͷ��������
	TThostFtdcLargeVolumeType	LongVolumeFrozen;
};

///��ѯ���͹�˾�ֲ�����
struct CThostFtdcQryBrokerLimitPosiField
{
	///���͹�˾����
	TThostFtdcBrokerIDType	BrokerID;
	///��Լ����
	TThostFtdcInstrumentIDType	InstrumentID;
	///����������
	TThostFtdcExchangeIDType	ExchangeID;
};

///Ͷ����֤ȯ�ֲ�����
struct CThostFtdcLimitPosiSField
{
	///���͹�˾����
	TThostFtdcBrokerIDType	BrokerID;
	///Ͷ���ߴ���
	TThostFtdcInvestorIDType	InvestorID;
	///��Լ����
	TThostFtdcInstrumentIDType	InstrumentID;
	///����������
	TThostFtdcExchangeIDType	ExchangeID;
	///����������
	TThostFtdcVolumeType	TotalVolume;
	///���տ�����������
	TThostFtdcVolumeType	OpenVolume;
	///����������
	TThostFtdcVolumeType	TotalVolumeFrozen;
	///���տ�����������
	TThostFtdcVolumeType	OpenVolumeFrozen;
};

///��ѯͶ����֤ȯ�ֲ�����
struct CThostFtdcQryLimitPosiSField
{
	///���͹�˾����
	TThostFtdcBrokerIDType	BrokerID;
	///Ͷ���ߴ���
	TThostFtdcInvestorIDType	InvestorID;
	///��Լ����
	TThostFtdcInstrumentIDType	InstrumentID;
	///����������
	TThostFtdcExchangeIDType	ExchangeID;
};

///Ͷ���ֲ߳����Ʋ���
struct CThostFtdcLimitPosiParamField
{
	///��Լ����
	TThostFtdcInstrumentIDType	InstrumentID;
	///Ͷ���߷�Χ
	TThostFtdcInvestorRangeType	InvestorRange;
	///���͹�˾����
	TThostFtdcBrokerIDType	BrokerID;
	///Ͷ���ߴ���
	TThostFtdcInvestorIDType	InvestorID;
	///����������
	TThostFtdcExchangeIDType	ExchangeID;
	///����������
	TThostFtdcVolumeType	TotalVolume;
	///��ͷ��������
	TThostFtdcVolumeType	LongVolume;
	///���տ�����������
	TThostFtdcVolumeType	OpenVolume;
	///��ͷ�ֲֽ������,����ʹ��
	TThostFtdcMoneyType	LongAmount;
};

///���͹�˾�ֲ����Ʋ���
struct CThostFtdcBrokerLimitPosiParamField
{
	///���͹�˾����
	TThostFtdcBrokerIDType	BrokerID;
	///��Լ����
	TThostFtdcInstrumentIDType	InstrumentID;
	///����������
	TThostFtdcExchangeIDType	ExchangeID;
	///����������
	TThostFtdcLargeVolumeType	TotalVolume;
	///��ͷ��������
	TThostFtdcLargeVolumeType	LongVolume;
};

///Ͷ����֤ȯ�ֲ����Ʋ���
struct CThostFtdcLimitPosiParamSField
{
	///��Լ����
	TThostFtdcInstrumentIDType	InstrumentID;
	///Ͷ���߷�Χ
	TThostFtdcInvestorRangeType	InvestorRange;
	///���͹�˾����
	TThostFtdcBrokerIDType	BrokerID;
	///Ͷ���ߴ���
	TThostFtdcInvestorIDType	InvestorID;
	///����������
	TThostFtdcExchangeIDType	ExchangeID;
	///����������
	TThostFtdcVolumeType	TotalVolume;
	///���տ�����������
	TThostFtdcVolumeType	OpenVolume;
};

///����֤ȯ���ò���
struct CThostFtdcInputStockDisposalActionField
{
	///���͹�˾����
	TThostFtdcBrokerIDType	BrokerID;
	///Ͷ���ߴ���
	TThostFtdcInvestorIDType	InvestorID;
	///֤ȯ���ò�������
	TThostFtdcOrderActionRefType	StockDisposalActionRef;
	///֤ȯ��������
	TThostFtdcOrderRefType	StockDisposalRef;
	///������
	TThostFtdcRequestIDType	RequestID;
	///ǰ�ñ��
	TThostFtdcFrontIDType	FrontID;
	///�Ự���
	TThostFtdcSessionIDType	SessionID;
	///����������
	TThostFtdcExchangeIDType	ExchangeID;
	///֤ȯ���ò������
	TThostFtdcStockDisposalSysIDType	StockDisposalSysID;
	///������־
	TThostFtdcActionFlagType	ActionFlag;
	///�û�����
	TThostFtdcUserIDType	UserID;
	///��Լ����
	TThostFtdcInstrumentIDType	InstrumentID;
};

///֤ȯ���ò���
struct CThostFtdcStockDisposalActionField
{
	///���͹�˾����
	TThostFtdcBrokerIDType	BrokerID;
	///Ͷ���ߴ���
	TThostFtdcInvestorIDType	InvestorID;
	///֤ȯ���ò�������
	TThostFtdcOrderActionRefType	StockDisposalActionRef;
	///֤ȯ��������
	TThostFtdcOrderRefType	StockDisposalRef;
	///������
	TThostFtdcRequestIDType	RequestID;
	///ǰ�ñ��
	TThostFtdcFrontIDType	FrontID;
	///�Ự���
	TThostFtdcSessionIDType	SessionID;
	///����������
	TThostFtdcExchangeIDType	ExchangeID;
	///֤ȯ���ò������
	TThostFtdcStockDisposalSysIDType	StockDisposalSysID;
	///������־
	TThostFtdcActionFlagType	ActionFlag;
	///��������
	TThostFtdcDateType	ActionDate;
	///����ʱ��
	TThostFtdcTimeType	ActionTime;
	///����������Ա����
	TThostFtdcTraderIDType	TraderID;
	///��װ���
	TThostFtdcInstallIDType	InstallID;
	///����֤ȯ���ñ��
	TThostFtdcOrderLocalIDType	StockDisposalLocalID;
	///�������ر��
	TThostFtdcOrderLocalIDType	ActionLocalID;
	///��Ա����
	TThostFtdcParticipantIDType	ParticipantID;
	///�ͻ�����
	TThostFtdcClientIDType	ClientID;
	///ҵ��Ԫ
	TThostFtdcBusinessUnitType	BusinessUnit;
	///��������״̬
	TThostFtdcOrderActionStatusType	OrderActionStatus;
	///�û�����
	TThostFtdcUserIDType	UserID;
	///ִ������
	TThostFtdcActionTypeType	ActionType;
	///״̬��Ϣ
	TThostFtdcErrorMsgType	StatusMsg;
	///��Լ����
	TThostFtdcInstrumentIDType	InstrumentID;
	///Ӫҵ�����
	TThostFtdcBranchIDType	BranchID;
	///��½PBU
	TThostFtdcTraderIDType	LoginPBU;
};

///֤ȯ���ò�����ѯ
struct CThostFtdcQryStockDisposalActionField
{
	///���͹�˾����
	TThostFtdcBrokerIDType	BrokerID;
	///Ͷ���ߴ���
	TThostFtdcInvestorIDType	InvestorID;
	///����������
	TThostFtdcExchangeIDType	ExchangeID;
};

///������֤ȯ���ò���
struct CThostFtdcExchangeStockDisposalActionField
{
	///����������
	TThostFtdcExchangeIDType	ExchangeID;
	///֤ȯ���ò������
	TThostFtdcStockDisposalSysIDType	StockDisposalSysID;
	///������־
	TThostFtdcActionFlagType	ActionFlag;
	///��������
	TThostFtdcDateType	ActionDate;
	///����ʱ��
	TThostFtdcTimeType	ActionTime;
	///����������Ա����
	TThostFtdcTraderIDType	TraderID;
	///��װ���
	TThostFtdcInstallIDType	InstallID;
	///����֤ȯ���ñ��
	TThostFtdcOrderLocalIDType	StockDisposalLocalID;
	///�������ر��
	TThostFtdcOrderLocalIDType	ActionLocalID;
	///��Ա����
	TThostFtdcParticipantIDType	ParticipantID;
	///�ͻ�����
	TThostFtdcClientIDType	ClientID;
	///ҵ��Ԫ
	TThostFtdcBusinessUnitType	BusinessUnit;
	///��������״̬
	TThostFtdcOrderActionStatusType	OrderActionStatus;
	///�û�����
	TThostFtdcUserIDType	UserID;
	///ִ������
	TThostFtdcActionTypeType	ActionType;
	///Ӫҵ�����
	TThostFtdcBranchIDType	BranchID;
	///��½PBU
	TThostFtdcTraderIDType	LoginPBU;
};

///����֤ȯ���ò���
struct CThostFtdcQryExchangeStockDisposalActionField
{
	///��Ա����
	TThostFtdcParticipantIDType	ParticipantID;
	///�ͻ�����
	TThostFtdcClientIDType	ClientID;
	///����������
	TThostFtdcExchangeIDType	ExchangeID;
	///����������Ա����
	TThostFtdcTraderIDType	TraderID;
};

///��ѯ����֤ȯ���ò���
struct CThostFtdcQryErrStockDisposalActionField
{
	///���͹�˾����
	TThostFtdcBrokerIDType	BrokerID;
	///Ͷ���ߴ���
	TThostFtdcInvestorIDType	InvestorID;
};

///������֤ȯ���ò�������
struct CThostFtdcExchangeStockDisposalActionErrorField
{
	///����������
	TThostFtdcExchangeIDType	ExchangeID;
	///֤ȯ���ñ��
	TThostFtdcStockDisposalSysIDType	StockDisposalSysID;
	///����������Ա����
	TThostFtdcTraderIDType	TraderID;
	///��װ���
	TThostFtdcInstallIDType	InstallID;
	///����֤ȯ���ñ��
	TThostFtdcOrderLocalIDType	StockDisposalLocalID;
	///�������ر��
	TThostFtdcOrderLocalIDType	ActionLocalID;
	///�������
	TThostFtdcErrorIDType	ErrorID;
	///������Ϣ
	TThostFtdcErrorMsgType	ErrorMsg;
	///���͹�˾����
	TThostFtdcBrokerIDType	BrokerID;
	///�ͻ�����
	TThostFtdcClientIDType	ClientID;
	///��½PBU
	TThostFtdcTraderIDType	LoginPBU;
};

///����֤ȯ���ò���
struct CThostFtdcErrStockDisposalActionField
{
	///���͹�˾����
	TThostFtdcBrokerIDType	BrokerID;
	///Ͷ���ߴ���
	TThostFtdcInvestorIDType	InvestorID;
	///֤ȯ���ò�������
	TThostFtdcOrderActionRefType	StockDisposalActionRef;
	///֤ȯ��������
	TThostFtdcOrderRefType	StockDisposalRef;
	///������
	TThostFtdcRequestIDType	RequestID;
	///ǰ�ñ��
	TThostFtdcFrontIDType	FrontID;
	///�Ự���
	TThostFtdcSessionIDType	SessionID;
	///����������
	TThostFtdcExchangeIDType	ExchangeID;
	///֤ȯ���ò������
	TThostFtdcStockDisposalSysIDType	StockDisposalSysID;
	///������־
	TThostFtdcActionFlagType	ActionFlag;
	///�û�����
	TThostFtdcUserIDType	UserID;
	///��Լ����
	TThostFtdcInstrumentIDType	InstrumentID;
	///�������
	TThostFtdcErrorIDType	ErrorID;
	///������Ϣ
	TThostFtdcErrorMsgType	ErrorMsg;
};

///Ͷ���߷ּ�
struct CThostFtdcInvestorLevelField
{
	///���͹�˾����
	TThostFtdcBrokerIDType	BrokerID;
	///Ͷ���ߴ���
	TThostFtdcInvestorIDType	InvestorID;
	///����������
	TThostFtdcExchangeIDType	ExchangeID;
	///Ͷ���߷ּ�����
	TThostFtdcLevelTypeType	LevelType;
};

///��Ϻ�Լ��ȫϵ��
struct CThostFtdcCombInstrumentGuardField
{
	///���͹�˾����
	TThostFtdcBrokerIDType	BrokerID;
	///��Լ����
	TThostFtdcInstrumentIDType	InstrumentID;
	///
	TThostFtdcRatioType	GuarantRatio;
	///����������
	TThostFtdcExchangeIDType	ExchangeID;
};

///��Ϻ�Լ��ȫϵ����ѯ
struct CThostFtdcQryCombInstrumentGuardField
{
	///���͹�˾����
	TThostFtdcBrokerIDType	BrokerID;
	///��Լ����
	TThostFtdcInstrumentIDType	InstrumentID;
	///����������
	TThostFtdcExchangeIDType	ExchangeID;
};

///������������
struct CThostFtdcInputCombActionField
{
	///���͹�˾����
	TThostFtdcBrokerIDType	BrokerID;
	///Ͷ���ߴ���
	TThostFtdcInvestorIDType	InvestorID;
	///��Լ����
	TThostFtdcInstrumentIDType	InstrumentID;
	///�������
	TThostFtdcOrderRefType	CombActionRef;
	///�û�����
	TThostFtdcUserIDType	UserID;
	///��������
	TThostFtdcDirectionType	Direction;
	///����
	TThostFtdcVolumeType	Volume;
	///���ָ���
	TThostFtdcCombDirectionType	CombDirection;
	///Ͷ���ױ���־
	TThostFtdcHedgeFlagType	HedgeFlag;
	///����������
	TThostFtdcExchangeIDType	ExchangeID;
	///��������Ч�ֶ�
	TThostFtdcOldIPAddressType	reserve1;
	///Mac��ַ
	TThostFtdcMacAddressType	MacAddress;
	///Ͷ�ʵ�Ԫ����
	TThostFtdcInvestUnitIDType	InvestUnitID;
	///�����ϱ��
	TThostFtdcTradeIDType	ComTradeID;
	///IP��ַ
	TThostFtdcIPAddressType	IPAddress;
};

///�������
struct CThostFtdcCombActionField
{
	///���͹�˾����
	TThostFtdcBrokerIDType	BrokerID;
	///Ͷ���ߴ���
	TThostFtdcInvestorIDType	InvestorID;
	///��Լ����
	TThostFtdcInstrumentIDType	InstrumentID;
	///�������
	TThostFtdcOrderRefType	CombActionRef;
	///�û�����
	TThostFtdcUserIDType	UserID;
	///��������
	TThostFtdcDirectionType	Direction;
	///����
	TThostFtdcVolumeType	Volume;
	///���ָ���
	TThostFtdcCombDirectionType	CombDirection;
	///Ͷ���ױ���־
	TThostFtdcHedgeFlagType	HedgeFlag;
	///����������ϱ��
	TThostFtdcOrderLocalIDType	ActionLocalID;
	///����������
	TThostFtdcExchangeIDType	ExchangeID;
	///��Ա����
	TThostFtdcParticipantIDType	ParticipantID;
	///�ͻ�����
	TThostFtdcClientIDType	ClientID;
	///��Լ�ڽ������Ĵ���
	TThostFtdcExchangeInstIDType	ExchangeInstID;
	///����������Ա����
	TThostFtdcTraderIDType	TraderID;
	///��װ���
	TThostFtdcInstallIDType	InstallID;
	///���״̬
	TThostFtdcOrderActionStatusType	ActionStatus;
	///������ʾ���
	TThostFtdcSequenceNoType	NotifySequence;
	///������
	TThostFtdcDateType	TradingDay;
	///������
	TThostFtdcSettlementIDType	SettlementID;
	///���
	TThostFtdcSequenceNoType	SequenceNo;
	///ǰ�ñ��
	TThostFtdcFrontIDType	FrontID;
	///�Ự���
	TThostFtdcSessionIDType	SessionID;
	///�û��˲�Ʒ��Ϣ
	TThostFtdcProductInfoType	UserProductInfo;
	///״̬��Ϣ
	TThostFtdcErrorMsgType	StatusMsg;
	///��������Ч�ֶ�
	TThostFtdcOldIPAddressType	reserve1;
	///Mac��ַ
	TThostFtdcMacAddressType	MacAddress;
	///��ϱ��
	TThostFtdcTradeIDType	ComTradeID;
	///Ӫҵ�����
	TThostFtdcBranchIDType	BranchID;
	///Ͷ�ʵ�Ԫ����
	TThostFtdcInvestUnitIDType	InvestUnitID;
	///����������
	TThostFtdcOwnerTypeType	OwnerType;
	///����ʱ��
	TThostFtdcTimeType	ActionTime;
	///��½PBU
	TThostFtdcTraderIDType	LoginPBU;
	///IP��ַ
	TThostFtdcIPAddressType	IPAddress;
};

///������ϲ�ѯ
struct CThostFtdcQryCombActionField
{
	///���͹�˾����
	TThostFtdcBrokerIDType	BrokerID;
	///Ͷ���ߴ���
	TThostFtdcInvestorIDType	InvestorID;
	///��Լ����
	TThostFtdcInstrumentIDType	InstrumentID;
	///����������
	TThostFtdcExchangeIDType	ExchangeID;
	///Ͷ�ʵ�Ԫ����
	TThostFtdcInvestUnitIDType	InvestUnitID;
};

///���������������Ϣ
struct CThostFtdcExchangeCombActionField
{
	///��������
	TThostFtdcDirectionType	Direction;
	///����
	TThostFtdcVolumeType	Volume;
	///���ָ���
	TThostFtdcCombDirectionType	CombDirection;
	///Ͷ���ױ���־
	TThostFtdcHedgeFlagType	HedgeFlag;
	///����������ϱ��
	TThostFtdcOrderLocalIDType	ActionLocalID;
	///����������
	TThostFtdcExchangeIDType	ExchangeID;
	///��Ա����
	TThostFtdcParticipantIDType	ParticipantID;
	///�ͻ�����
	TThostFtdcClientIDType	ClientID;
	///��Լ�ڽ������Ĵ���
	TThostFtdcExchangeInstIDType	ExchangeInstID;
	///����������Ա����
	TThostFtdcTraderIDType	TraderID;
	///��װ���
	TThostFtdcInstallIDType	InstallID;
	///���״̬
	TThostFtdcOrderActionStatusType	ActionStatus;
	///������ʾ���
	TThostFtdcSequenceNoType	NotifySequence;
	///������
	TThostFtdcDateType	TradingDay;
	///������
	TThostFtdcSettlementIDType	SettlementID;
	///���
	TThostFtdcSequenceNoType	SequenceNo;
	///��������Ч�ֶ�
	TThostFtdcOldIPAddressType	reserve1;
	///Mac��ַ
	TThostFtdcMacAddressType	MacAddress;
	///��ϱ��
	TThostFtdcTradeIDType	ComTradeID;
	///Ӫҵ�����
	TThostFtdcBranchIDType	BranchID;
	///����������
	TThostFtdcOwnerTypeType	OwnerType;
	///����ʱ��
	TThostFtdcTimeType	ActionTime;
	///��½PBU
	TThostFtdcTraderIDType	LoginPBU;
	///IP��ַ
	TThostFtdcIPAddressType	IPAddress;
};

///������������ϲ�ѯ
struct CThostFtdcQryExchangeCombActionField
{
	///��Ա����
	TThostFtdcParticipantIDType	ParticipantID;
	///�ͻ�����
	TThostFtdcClientIDType	ClientID;
	///��Լ�ڽ������Ĵ���
	TThostFtdcExchangeInstIDType	ExchangeInstID;
	///����������
	TThostFtdcExchangeIDType	ExchangeID;
	///����������Ա����
	TThostFtdcTraderIDType	TraderID;
};

///��Ʒ���ۻ���
struct CThostFtdcProductExchRateField
{
	///��Ʒ����
	TThostFtdcInstrumentIDType	ProductID;
	///���۱�������
	TThostFtdcCurrencyIDType	QuoteCurrencyID;
	///����
	TThostFtdcExchangeRateType	ExchangeRate;
	///����������
	TThostFtdcExchangeIDType	ExchangeID;
};

///��Ʒ���ۻ��ʲ�ѯ
struct CThostFtdcQryProductExchRateField
{
	///��Ʒ����
	TThostFtdcInstrumentIDType	ProductID;
	///����������
	TThostFtdcExchangeIDType	ExchangeID;
};

///�����ָ��
struct CThostFtdcInputDesignateField
{
	///���͹�˾����
	TThostFtdcBrokerIDType	BrokerID;
	///Ͷ���ߴ���
	TThostFtdcInvestorIDType	InvestorID;
	///ָ���Ǽ�����
	TThostFtdcOrderRefType	DesignateRef;
	///�û�����
	TThostFtdcUserIDType	UserID;
	///ָ������
	TThostFtdcDesignateTypeType	DesignateType;
	///����������
	TThostFtdcExchangeIDType	ExchangeID;
	///���������׵�Ԫ
	TThostFtdcTraderIDType	PBU;
};

///ָ��
struct CThostFtdcDesignateField
{
	///���͹�˾����
	TThostFtdcBrokerIDType	BrokerID;
	///Ͷ���ߴ���
	TThostFtdcInvestorIDType	InvestorID;
	///ָ���Ǽ�����
	TThostFtdcOrderRefType	DesignateRef;
	///�û�����
	TThostFtdcUserIDType	UserID;
	///ָ������
	TThostFtdcDesignateTypeType	DesignateType;
	///����ָ�����
	TThostFtdcOrderLocalIDType	DesignateLocalID;
	///����������
	TThostFtdcExchangeIDType	ExchangeID;
	///��Ա����
	TThostFtdcParticipantIDType	ParticipantID;
	///�ͻ�����
	TThostFtdcClientIDType	ClientID;
	///����������Ա����
	TThostFtdcTraderIDType	TraderID;
	///��װ���
	TThostFtdcInstallIDType	InstallID;
	///ָ��״̬
	TThostFtdcOrderActionStatusType	DesignateStatus;
	///������ʾ���
	TThostFtdcSequenceNoType	NotifySequence;
	///������
	TThostFtdcDateType	TradingDay;
	///������
	TThostFtdcSettlementIDType	SettlementID;
	///��������
	TThostFtdcDateType	InsertDate;
	///����ʱ��
	TThostFtdcTimeType	InsertTime;
	///ǰ�ñ��
	TThostFtdcFrontIDType	FrontID;
	///�Ự���
	TThostFtdcSessionIDType	SessionID;
	///�û��˲�Ʒ��Ϣ
	TThostFtdcProductInfoType	UserProductInfo;
	///״̬��Ϣ
	TThostFtdcErrorMsgType	StatusMsg;
	///Ӫҵ�����
	TThostFtdcBranchIDType	BranchID;
	///���������׵�Ԫ
	TThostFtdcTraderIDType	PBU;
	///��½PBU
	TThostFtdcTraderIDType	LoginPBU;
};

///����ָ��
struct CThostFtdcQryDesignateField
{
	///���͹�˾����
	TThostFtdcBrokerIDType	BrokerID;
	///Ͷ���ߴ���
	TThostFtdcInvestorIDType	InvestorID;
	///����������
	TThostFtdcExchangeIDType	ExchangeID;
};

///������ָ����Ϣ
struct CThostFtdcExchangeDesignateField
{
	///ָ������
	TThostFtdcDesignateTypeType	DesignateType;
	///����ָ�����
	TThostFtdcOrderLocalIDType	DesignateLocalID;
	///����������
	TThostFtdcExchangeIDType	ExchangeID;
	///��Ա����
	TThostFtdcParticipantIDType	ParticipantID;
	///�ͻ�����
	TThostFtdcClientIDType	ClientID;
	///����������Ա����
	TThostFtdcTraderIDType	TraderID;
	///��װ���
	TThostFtdcInstallIDType	InstallID;
	///ָ��״̬
	TThostFtdcOrderActionStatusType	DesignateStatus;
	///������ʾ���
	TThostFtdcSequenceNoType	NotifySequence;
	///������
	TThostFtdcDateType	TradingDay;
	///������
	TThostFtdcSettlementIDType	SettlementID;
	///��������
	TThostFtdcDateType	InsertDate;
	///����ʱ��
	TThostFtdcTimeType	InsertTime;
	///Ӫҵ�����
	TThostFtdcBranchIDType	BranchID;
	///��½PBU
	TThostFtdcTraderIDType	LoginPBU;
};

///�����֤ȯ����
struct CThostFtdcInputStockDisposalField
{
	///���͹�˾����
	TThostFtdcBrokerIDType	BrokerID;
	///Ͷ���ߴ���
	TThostFtdcInvestorIDType	InvestorID;
	///֤ȯ���õǼ�����
	TThostFtdcOrderRefType	StockDisposalRef;
	///�û�����
	TThostFtdcUserIDType	UserID;
	///��Լ����
	TThostFtdcInstrumentIDType	InstrumentID;
	///����
	TThostFtdcVolumeType	Volume;
	///֤ȯ���÷���
	TThostFtdcStockDisposalTypeType	StockDisposalType;
	///����������
	TThostFtdcExchangeIDType	ExchangeID;
};

///֤ȯ����
struct CThostFtdcStockDisposalField
{
	///���͹�˾����
	TThostFtdcBrokerIDType	BrokerID;
	///Ͷ���ߴ���
	TThostFtdcInvestorIDType	InvestorID;
	///֤ȯ���õǼ�����
	TThostFtdcOrderRefType	StockDisposalRef;
	///�û�����
	TThostFtdcUserIDType	UserID;
	///��Լ����
	TThostFtdcInstrumentIDType	InstrumentID;
	///����
	TThostFtdcVolumeType	Volume;
	///֤ȯ���÷���
	TThostFtdcStockDisposalTypeType	StockDisposalType;
	///����֤ȯ���ñ��
	TThostFtdcOrderLocalIDType	StockDisposalLocalID;
	///����������
	TThostFtdcExchangeIDType	ExchangeID;
	///��Լ�ڽ������Ĵ���
	TThostFtdcExchangeInstIDType	ExchangeInstID;
	///��Ա����
	TThostFtdcParticipantIDType	ParticipantID;
	///�ͻ�����
	TThostFtdcClientIDType	ClientID;
	///����������Ա����
	TThostFtdcTraderIDType	TraderID;
	///��װ���
	TThostFtdcInstallIDType	InstallID;
	///֤ȯ����״̬
	TThostFtdcStockDisposalStatusType	StockDisposalStatus;
	///������ʾ���
	TThostFtdcSequenceNoType	NotifySequence;
	///������
	TThostFtdcDateType	TradingDay;
	///������
	TThostFtdcSettlementIDType	SettlementID;
	///��������
	TThostFtdcDateType	InsertDate;
	///����ʱ��
	TThostFtdcTimeType	InsertTime;
	///ǰ�ñ��
	TThostFtdcFrontIDType	FrontID;
	///�Ự���
	TThostFtdcSessionIDType	SessionID;
	///�û��˲�Ʒ��Ϣ
	TThostFtdcProductInfoType	UserProductInfo;
	///״̬��Ϣ
	TThostFtdcErrorMsgType	StatusMsg;
	///Ӫҵ�����
	TThostFtdcBranchIDType	BranchID;
	///֤ȯ���ò������
	TThostFtdcStockDisposalSysIDType	StockDisposalSysID;
	///ҵ��Ԫ
	TThostFtdcBusinessUnitType	BusinessUnit;
	///��½PBU
	TThostFtdcTraderIDType	LoginPBU;
};

///����֤ȯ����
struct CThostFtdcQryStockDisposalField
{
	///���͹�˾����
	TThostFtdcBrokerIDType	BrokerID;
	///Ͷ���ߴ���
	TThostFtdcInvestorIDType	InvestorID;
	///����������
	TThostFtdcExchangeIDType	ExchangeID;
};

///������֤ȯ������Ϣ
struct CThostFtdcExchangeStockDisposalField
{
	///����
	TThostFtdcVolumeType	Volume;
	///֤ȯ���÷���
	TThostFtdcStockDisposalTypeType	StockDisposalType;
	///����֤ȯ���ñ��
	TThostFtdcOrderLocalIDType	StockDisposalLocalID;
	///����������
	TThostFtdcExchangeIDType	ExchangeID;
	///��Լ�ڽ������Ĵ���
	TThostFtdcExchangeInstIDType	ExchangeInstID;
	///��Ա����
	TThostFtdcParticipantIDType	ParticipantID;
	///�ͻ�����
	TThostFtdcClientIDType	ClientID;
	///����������Ա����
	TThostFtdcTraderIDType	TraderID;
	///��װ���
	TThostFtdcInstallIDType	InstallID;
	///֤ȯ����״̬
	TThostFtdcStockDisposalStatusType	StockDisposalStatus;
	///������ʾ���
	TThostFtdcSequenceNoType	NotifySequence;
	///������
	TThostFtdcDateType	TradingDay;
	///������
	TThostFtdcSettlementIDType	SettlementID;
	///��������
	TThostFtdcDateType	InsertDate;
	///����ʱ��
	TThostFtdcTimeType	InsertTime;
	///Ӫҵ�����
	TThostFtdcBranchIDType	BranchID;
	///֤ȯ���ò������
	TThostFtdcStockDisposalSysIDType	StockDisposalSysID;
	///ҵ��Ԫ
	TThostFtdcBusinessUnitType	BusinessUnit;
	///��½PBU
	TThostFtdcTraderIDType	LoginPBU;
};

///��ѯͶ���߷ּ�
struct CThostFtdcQryInvestorLevelField
{
	///���͹�˾����
	TThostFtdcBrokerIDType	BrokerID;
	///Ͷ���ߴ���
	TThostFtdcInvestorIDType	InvestorID;
	///����������
	TThostFtdcExchangeIDType	ExchangeID;
};

///��ѯѯ�ۼ۲����
struct CThostFtdcQryForQuoteParamField
{
	///���͹�˾����
	TThostFtdcBrokerIDType	BrokerID;
	///��Լ����
	TThostFtdcInstrumentIDType	InstrumentID;
	///����������
	TThostFtdcExchangeIDType	ExchangeID;
};

///ѯ�ۼ۲����
struct CThostFtdcForQuoteParamField
{
	///���͹�˾����
	TThostFtdcBrokerIDType	BrokerID;
	///��Լ����
	TThostFtdcInstrumentIDType	InstrumentID;
	///����������
	TThostFtdcExchangeIDType	ExchangeID;
	///���¼�
	TThostFtdcPriceType	LastPrice;
	///�۲�
	TThostFtdcPriceType	PriceInterval;
};

///��ѯ��Ȩ����
struct CThostFtdcQryExecFreezeField
{
	///���͹�˾����
	TThostFtdcBrokerIDType	BrokerID;
	///Ͷ���ߴ���
	TThostFtdcInvestorIDType	InvestorID;
	///��Լ����
	TThostFtdcInstrumentIDType	InstrumentID;
	///����������
	TThostFtdcExchangeIDType	ExchangeID;
};

///��Ȩ����
struct CThostFtdcExecFreezeField
{
	///��ĺ�Լ����
	TThostFtdcInstrumentIDType	InstrumentID;
	///����������
	TThostFtdcExchangeIDType	ExchangeID;
	///���͹�˾����
	TThostFtdcBrokerIDType	BrokerID;
	///Ͷ���ߴ���
	TThostFtdcInvestorIDType	InvestorID;
	///�ֲֶ�շ���
	TThostFtdcPosiDirectionType	PosiDirection;
	///��Ȩ����
	TThostFtdcOptionsTypeType	OptionsType;
	///���������_��λ��
	TThostFtdcVolumeType	Volume;
	///������
	TThostFtdcMoneyType	FrozenAmount;
};

///��ǰ��������Ȩ��Լ�����ѵ���ϸ����
struct CThostFtdcMMOptionInstrCommRateField
{
	///��Լ����
	TThostFtdcInstrumentIDType	InstrumentID;
	///Ͷ���߷�Χ
	TThostFtdcInvestorRangeType	InvestorRange;
	///���͹�˾����
	TThostFtdcBrokerIDType	BrokerID;
	///Ͷ���ߴ���
	TThostFtdcInvestorIDType	InvestorID;
	///������������
	TThostFtdcRatioType	OpenRatioByMoney;
	///����������
	TThostFtdcRatioType	OpenRatioByVolume;
	///ƽ����������
	TThostFtdcRatioType	CloseRatioByMoney;
	///ƽ��������
	TThostFtdcRatioType	CloseRatioByVolume;
	///ƽ����������
	TThostFtdcRatioType	CloseTodayRatioByMoney;
	///ƽ��������
	TThostFtdcRatioType	CloseTodayRatioByVolume;
	///ִ����������
	TThostFtdcRatioType	StrikeRatioByMoney;
	///ִ��������
	TThostFtdcRatioType	StrikeRatioByVolume;
	///����������
	TThostFtdcExchangeIDType	ExchangeID;
};

///��������Ȩ�������ʲ�ѯ
struct CThostFtdcQryMMOptionInstrCommRateField
{
	///���͹�˾����
	TThostFtdcBrokerIDType	BrokerID;
	///Ͷ���ߴ���
	TThostFtdcInvestorIDType	InvestorID;
	///��Լ����
	TThostFtdcInstrumentIDType	InstrumentID;
	///����������
	TThostFtdcExchangeIDType	ExchangeID;
};

///�����̺�Լ��������
struct CThostFtdcMMInstrumentCommissionRateField
{
	///��Լ����
	TThostFtdcInstrumentIDType	InstrumentID;
	///Ͷ���߷�Χ
	TThostFtdcInvestorRangeType	InvestorRange;
	///���͹�˾����
	TThostFtdcBrokerIDType	BrokerID;
	///Ͷ���ߴ���
	TThostFtdcInvestorIDType	InvestorID;
	///������������
	TThostFtdcRatioType	OpenRatioByMoney;
	///����������
	TThostFtdcRatioType	OpenRatioByVolume;
	///ƽ����������
	TThostFtdcRatioType	CloseRatioByMoney;
	///ƽ��������
	TThostFtdcRatioType	CloseRatioByVolume;
	///ƽ����������
	TThostFtdcRatioType	CloseTodayRatioByMoney;
	///ƽ��������
	TThostFtdcRatioType	CloseTodayRatioByVolume;
	///����������
	TThostFtdcExchangeIDType	ExchangeID;
};

///��ѯ�����̺�Լ��������
struct CThostFtdcQryMMInstrumentCommissionRateField
{
	///���͹�˾����
	TThostFtdcBrokerIDType	BrokerID;
	///Ͷ���ߴ���
	TThostFtdcInvestorIDType	InvestorID;
	///��Լ����
	TThostFtdcInstrumentIDType	InstrumentID;
	///����������
	TThostFtdcExchangeIDType	ExchangeID;
};

///��ǰ���������ѵ���ϸ����
struct CThostFtdcInstrumentOrderCommRateField
{
	///��Լ����
	TThostFtdcInstrumentIDType	InstrumentID;
	///Ͷ���߷�Χ
	TThostFtdcInvestorRangeType	InvestorRange;
	///���͹�˾����
	TThostFtdcBrokerIDType	BrokerID;
	///Ͷ���ߴ���
	TThostFtdcInvestorIDType	InvestorID;
	///Ͷ���ױ���־
	TThostFtdcHedgeFlagType	HedgeFlag;
	///����������
	TThostFtdcRatioType	OrderCommByVolume;
	///����������
	TThostFtdcRatioType	OrderActionCommByVolume;
	///����������
	TThostFtdcExchangeIDType	ExchangeID;
	///Ͷ�ʵ�Ԫ����
	TThostFtdcInvestUnitIDType	InvestUnitID;
};

///�����������ʲ�ѯ
struct CThostFtdcQryInstrumentOrderCommRateField
{
	///���͹�˾����
	TThostFtdcBrokerIDType	BrokerID;
	///Ͷ���ߴ���
	TThostFtdcInvestorIDType	InvestorID;
	///��Լ����
	TThostFtdcInstrumentIDType	InstrumentID;
	///����������
	TThostFtdcExchangeIDType	ExchangeID;
};

///Ͷ���߽������
struct CThostFtdcLimitAmountField
{
	///���͹�˾����
	TThostFtdcBrokerIDType	BrokerID;
	///Ͷ���ߴ���
	TThostFtdcInvestorIDType	InvestorID;
	///����������
	TThostFtdcExchangeIDType	ExchangeID;
	///��ͷ�ֲֽ������
	TThostFtdcMoneyType	LongAmount;
	///��ͷ�ֲֽ���
	TThostFtdcMoneyType	LongAmountFrozen;
};

///��ѯͶ���߽������
struct CThostFtdcQryLimitAmountField
{
	///���͹�˾����
	TThostFtdcBrokerIDType	BrokerID;
	///Ͷ���ߴ���
	TThostFtdcInvestorIDType	InvestorID;
	///����������
	TThostFtdcExchangeIDType	ExchangeID;
};

///Ͷ���߽�����Ʋ���
struct CThostFtdcLimitAmountParamField
{
	///Ͷ���߷�Χ
	TThostFtdcInvestorRangeType	InvestorRange;
	///���͹�˾����
	TThostFtdcBrokerIDType	BrokerID;
	///Ͷ���ߴ���
	TThostFtdcInvestorIDType	InvestorID;
	///����������
	TThostFtdcExchangeIDType	ExchangeID;
	///��ͷ�ֲֽ������
	TThostFtdcMoneyType	LongAmount;
};

///��ǰ��Ȩ��Լ��֤����ϵ��
struct CThostFtdcOptionInstrMarginGuardField
{
	///��Լ����
	TThostFtdcInstrumentIDType	InstrumentID;
	///Ͷ���߷�Χ
	TThostFtdcInvestorRangeType	InvestorRange;
	///���͹�˾����
	TThostFtdcBrokerIDType	BrokerID;
	///Ͷ���ߴ���
	TThostFtdcInvestorIDType	InvestorID;
	///Ͷ����ͷ��֤�����ϵ��
	TThostFtdcRatioType	SShortMarginRatioByMoney;
	///Ͷ����ͷ��֤�����ϵ��
	TThostFtdcMoneyType	SShortMarginRatioByVolume;
	///��ֵ��ͷ��֤�����ϵ��
	TThostFtdcRatioType	HShortMarginRatioByMoney;
	///��ֵ��ͷ��֤�����ϵ��
	TThostFtdcMoneyType	HShortMarginRatioByVolume;
	///������ͷ��֤�����ϵ��
	TThostFtdcRatioType	AShortMarginRatioByMoney;
	///������ͷ��֤�����ϵ��
	TThostFtdcMoneyType	AShortMarginRatioByVolume;
	///�Ƿ���潻������ȡ
	TThostFtdcBoolType	IsRelative;
	///����������
	TThostFtdcExchangeIDType	ExchangeID;
};

///���ײ���
struct CThostFtdcTradeParamField
{
	///���͹�˾����
	TThostFtdcBrokerIDType	BrokerID;
	///��������
	TThostFtdcTradeParamIDType	TradeParamID;
	///��������ֵ
	TThostFtdcSettlementParamValueType	TradeParamValue;
	///��ע
	TThostFtdcMemoType	Memo;
};

///��֤��
struct CThostFtdcAuthenticationCodeField
{
	///���͹�˾����
	TThostFtdcBrokerIDType	BrokerID;
	///�û��˲�Ʒ��Ϣ
	TThostFtdcProductInfoType	UserProductInfo;
	///��֤��
	TThostFtdcAuthCodeType	AuthCode;
	///����֤��
	TThostFtdcAuthCodeType	PreAuthCode;
};

///���ɶ�����֤������
struct CThostFtdcReqSmsCodeGenerateField
{
	///���͹�˾����
	TThostFtdcBrokerIDType	BrokerID;
	///�û�����
	TThostFtdcUserIDType	UserID;
	///����
	TThostFtdcPasswordType	Password;
	///�û��˲�Ʒ��Ϣ
	TThostFtdcProductInfoType	UserProductInfo;
	///Mac��ַ
	TThostFtdcMacAddressType	MacAddress;
	///�ն�IP��ַ
	TThostFtdcIPAddressType	ClientIPAddress;
};

///���ɶ�����֤��Ӧ��
struct CThostFtdcRspSmsCodeGenerateField
{
	///���͹�˾����
	TThostFtdcBrokerIDType	BrokerID;
	///�û�����
	TThostFtdcUserIDType	UserID;
};

///�û���֤��ʽ
struct CThostFtdcBrokerUserAuthMethodField
{
	///���͹�˾����
	TThostFtdcBrokerIDType	BrokerID;
	///�û�����
	TThostFtdcUserIDType	UserID;
	///�Ƿ����ö�����֤��
	TThostFtdcBoolType	IsSms;
};

///���͹�˾�û�������֤��
struct CThostFtdcBrokerUserSmsCodeField
{
	///���͹�˾����
	TThostFtdcBrokerIDType	BrokerID;
	///�û�����
	TThostFtdcUserIDType	UserID;
	///�ֻ�
	TThostFtdcMobileType	Mobile;
	///������֤��
	TThostFtdcSmsCodeType	SmsCode;
	///���к�
	TThostFtdcSeqNoType	SeqNo;
	///����״̬
	TThostFtdcSmsCodeStatusType	Status;
};

///��Լ��֤���ʵ���
struct CThostFtdcInstrumentMarginRateULField
{
	///��Լ����
	TThostFtdcInstrumentIDType	InstrumentID;
	///Ͷ���߷�Χ
	TThostFtdcInvestorRangeType	InvestorRange;
	///���͹�˾����
	TThostFtdcBrokerIDType	BrokerID;
	///Ͷ���ߴ���
	TThostFtdcInvestorIDType	InvestorID;
	///Ͷ���ױ���־
	TThostFtdcHedgeFlagType	HedgeFlag;
	///��ͷ��֤����
	TThostFtdcRatioType	LongMarginRatioByMoney;
	///��ͷ��֤���
	TThostFtdcMoneyType	LongMarginRatioByVolume;
	///��ͷ��֤����
	TThostFtdcRatioType	ShortMarginRatioByMoney;
	///��ͷ��֤���
	TThostFtdcMoneyType	ShortMarginRatioByVolume;
};

///�ڻ��ֲ����Ʋ���
struct CThostFtdcFutureLimitPosiParamField
{
	///Ͷ���߷�Χ
	TThostFtdcInvestorRangeType	InvestorRange;
	///���͹�˾����
	TThostFtdcBrokerIDType	BrokerID;
	///Ͷ���ߴ���
	TThostFtdcInvestorIDType	InvestorID;
	///��Ʒ����
	TThostFtdcInstrumentIDType	ProductID;
	///����������
	TThostFtdcExchangeIDType	ExchangeID;
	///����Ͷ��������������
	TThostFtdcVolumeType	SpecOpenVolume;
	///��������������������
	TThostFtdcVolumeType	ArbiOpenVolume;
	///����Ͷ��+����������������
	TThostFtdcVolumeType	OpenVolume;
};

///��ֹ��¼IP
struct CThostFtdcLoginForbiddenIPField
{
	///��������Ч�ֶ�
	TThostFtdcOldIPAddressType	reserve1;
	///IP��ַ
	TThostFtdcIPAddressType	IPAddress;
};

///IP�б�
struct CThostFtdcIPListField
{
	///��������Ч�ֶ�
	TThostFtdcOldIPAddressType	reserve1;
	///�Ƿ������
	TThostFtdcBoolType	IsWhite;
	///IP��ַ
	TThostFtdcIPAddressType	IPAddress;
};

///�������Ȩ�ԶԳ�
struct CThostFtdcInputOptionSelfCloseField
{
	///���͹�˾����
	TThostFtdcBrokerIDType	BrokerID;
	///Ͷ���ߴ���
	TThostFtdcInvestorIDType	InvestorID;
	///��Լ����
	TThostFtdcInstrumentIDType	InstrumentID;
	///��Ȩ�ԶԳ�����
	TThostFtdcOrderRefType	OptionSelfCloseRef;
	///�û�����
	TThostFtdcUserIDType	UserID;
	///����
	TThostFtdcVolumeType	Volume;
	///������
	TThostFtdcRequestIDType	RequestID;
	///ҵ��Ԫ
	TThostFtdcBusinessUnitType	BusinessUnit;
	///Ͷ���ױ���־
	TThostFtdcHedgeFlagType	HedgeFlag;
	///��Ȩ��Ȩ��ͷ���Ƿ��ԶԳ�
	TThostFtdcOptSelfCloseFlagType	OptSelfCloseFlag;
	///����������
	TThostFtdcExchangeIDType	ExchangeID;
	///Ͷ�ʵ�Ԫ����
	TThostFtdcInvestUnitIDType	InvestUnitID;
	///�ʽ��˺�
	TThostFtdcAccountIDType	AccountID;
	///���ִ���
	TThostFtdcCurrencyIDType	CurrencyID;
	///���ױ���
	TThostFtdcClientIDType	ClientID;
	///IP��ַ
	TThostFtdcIPAddressType	IPAddress;
	///Mac��ַ
	TThostFtdcMacAddressType	MacAddress;
};

///������Ȩ�ԶԳ����
struct CThostFtdcInputOptionSelfCloseActionField
{
	///���͹�˾����
	TThostFtdcBrokerIDType	BrokerID;
	///Ͷ���ߴ���
	TThostFtdcInvestorIDType	InvestorID;
	///��Ȩ�ԶԳ��������
	TThostFtdcOrderActionRefType	OptionSelfCloseActionRef;
	///��Ȩ�ԶԳ�����
	TThostFtdcOrderRefType	OptionSelfCloseRef;
	///������
	TThostFtdcRequestIDType	RequestID;
	///ǰ�ñ��
	TThostFtdcFrontIDType	FrontID;
	///�Ự���
	TThostFtdcSessionIDType	SessionID;
	///����������
	TThostFtdcExchangeIDType	ExchangeID;
	///��Ȩ�ԶԳ�������
	TThostFtdcOrderSysIDType	OptionSelfCloseSysID;
	///������־
	TThostFtdcActionFlagType	ActionFlag;
	///�û�����
	TThostFtdcUserIDType	UserID;
	///��Լ����
	TThostFtdcInstrumentIDType	InstrumentID;
	///Ͷ�ʵ�Ԫ����
	TThostFtdcInvestUnitIDType	InvestUnitID;
	///IP��ַ
	TThostFtdcIPAddressType	IPAddress;
	///Mac��ַ
	TThostFtdcMacAddressType	MacAddress;
};

///��Ȩ�ԶԳ�
struct CThostFtdcOptionSelfCloseField
{
	///���͹�˾����
	TThostFtdcBrokerIDType	BrokerID;
	///Ͷ���ߴ���
	TThostFtdcInvestorIDType	InvestorID;
	///��Լ����
	TThostFtdcInstrumentIDType	InstrumentID;
	///��Ȩ�ԶԳ�����
	TThostFtdcOrderRefType	OptionSelfCloseRef;
	///�û�����
	TThostFtdcUserIDType	UserID;
	///����
	TThostFtdcVolumeType	Volume;
	///������
	TThostFtdcRequestIDType	RequestID;
	///ҵ��Ԫ
	TThostFtdcBusinessUnitType	BusinessUnit;
	///Ͷ���ױ���־
	TThostFtdcHedgeFlagType	HedgeFlag;
	///��Ȩ��Ȩ��ͷ���Ƿ��ԶԳ�
	TThostFtdcOptSelfCloseFlagType	OptSelfCloseFlag;
	///������Ȩ�ԶԳ���
	TThostFtdcOrderLocalIDType	OptionSelfCloseLocalID;
	///����������
	TThostFtdcExchangeIDType	ExchangeID;
	///��Ա����
	TThostFtdcParticipantIDType	ParticipantID;
	///�ͻ�����
	TThostFtdcClientIDType	ClientID;
	///��Լ�ڽ������Ĵ���
	TThostFtdcExchangeInstIDType	ExchangeInstID;
	///����������Ա����
	TThostFtdcTraderIDType	TraderID;
	///��װ���
	TThostFtdcInstallIDType	InstallID;
	///��Ȩ�ԶԳ��ύ״̬
	TThostFtdcOrderSubmitStatusType	OrderSubmitStatus;
	///������ʾ���
	TThostFtdcSequenceNoType	NotifySequence;
	///������
	TThostFtdcDateType	TradingDay;
	///������
	TThostFtdcSettlementIDType	SettlementID;
	///��Ȩ�ԶԳ���
	TThostFtdcOrderSysIDType	OptionSelfCloseSysID;
	///��������
	TThostFtdcDateType	InsertDate;
	///����ʱ��
	TThostFtdcTimeType	InsertTime;
	///����ʱ��
	TThostFtdcTimeType	CancelTime;
	///�ԶԳ���
	TThostFtdcOrderActionStatusType	OptionSelfCloseStatus;
	///�����Ա���
	TThostFtdcParticipantIDType	ClearingPartID;
	///���
	TThostFtdcSequenceNoType	SequenceNo;
	///ǰ�ñ��
	TThostFtdcFrontIDType	FrontID;
	///�Ự���
	TThostFtdcSessionIDType	SessionID;
	///�û��˲�Ʒ��Ϣ
	TThostFtdcProductInfoType	UserProductInfo;
	///״̬��Ϣ
	TThostFtdcErrorMsgType	StatusMsg;
	///�����û�����
	TThostFtdcUserIDType	ActiveUserID;
	///���͹�˾�������
	TThostFtdcSequenceNoType	BrokerOptionSelfCloseSeq;
	///Ӫҵ�����
	TThostFtdcBranchIDType	BranchID;
	///Ͷ�ʵ�Ԫ����
	TThostFtdcInvestUnitIDType	InvestUnitID;
	///�ʽ��˺�
	TThostFtdcAccountIDType	AccountID;
	///���ִ���
	TThostFtdcCurrencyIDType	CurrencyID;
	///IP��ַ
	TThostFtdcIPAddressType	IPAddress;
	///Mac��ַ
	TThostFtdcMacAddressType	MacAddress;
};

///��Ȩ�ԶԳ����
struct CThostFtdcOptionSelfCloseActionField
{
	///���͹�˾����
	TThostFtdcBrokerIDType	BrokerID;
	///Ͷ���ߴ���
	TThostFtdcInvestorIDType	InvestorID;
	///��Ȩ�ԶԳ��������
	TThostFtdcOrderActionRefType	OptionSelfCloseActionRef;
	///��Ȩ�ԶԳ�����
	TThostFtdcOrderRefType	OptionSelfCloseRef;
	///������
	TThostFtdcRequestIDType	RequestID;
	///ǰ�ñ��
	TThostFtdcFrontIDType	FrontID;
	///�Ự���
	TThostFtdcSessionIDType	SessionID;
	///����������
	TThostFtdcExchangeIDType	ExchangeID;
	///��Ȩ�ԶԳ�������
	TThostFtdcOrderSysIDType	OptionSelfCloseSysID;
	///������־
	TThostFtdcActionFlagType	ActionFlag;
	///��������
	TThostFtdcDateType	ActionDate;
	///����ʱ��
	TThostFtdcTimeType	ActionTime;
	///����������Ա����
	TThostFtdcTraderIDType	TraderID;
	///��װ���
	TThostFtdcInstallIDType	InstallID;
	///������Ȩ�ԶԳ���
	TThostFtdcOrderLocalIDType	OptionSelfCloseLocalID;
	///�������ر��
	TThostFtdcOrderLocalIDType	ActionLocalID;
	///��Ա����
	TThostFtdcParticipantIDType	ParticipantID;
	///�ͻ�����
	TThostFtdcClientIDType	ClientID;
	///ҵ��Ԫ
	TThostFtdcBusinessUnitType	BusinessUnit;
	///��������״̬
	TThostFtdcOrderActionStatusType	OrderActionStatus;
	///�û�����
	TThostFtdcUserIDType	UserID;
	///״̬��Ϣ
	TThostFtdcErrorMsgType	StatusMsg;
	///��Լ����
	TThostFtdcInstrumentIDType	InstrumentID;
	///Ӫҵ�����
	TThostFtdcBranchIDType	BranchID;
	///Ͷ�ʵ�Ԫ����
	TThostFtdcInvestUnitIDType	InvestUnitID;
	///IP��ַ
	TThostFtdcIPAddressType	IPAddress;
	///Mac��ַ
	TThostFtdcMacAddressType	MacAddress;
};

///��Ȩ�ԶԳ��ѯ
struct CThostFtdcQryOptionSelfCloseField
{
	///���͹�˾����
	TThostFtdcBrokerIDType	BrokerID;
	///Ͷ���ߴ���
	TThostFtdcInvestorIDType	InvestorID;
	///��Լ����
	TThostFtdcInstrumentIDType	InstrumentID;
	///����������
	TThostFtdcExchangeIDType	ExchangeID;
	///��Ȩ�ԶԳ���
	TThostFtdcOrderSysIDType	OptionSelfCloseSysID;
	///��ʼʱ��
	TThostFtdcTimeType	InsertTimeStart;
	///����ʱ��
	TThostFtdcTimeType	InsertTimeEnd;
};

///��������Ȩ�ԶԳ���Ϣ
struct CThostFtdcExchangeOptionSelfCloseField
{
	///����
	TThostFtdcVolumeType	Volume;
	///������
	TThostFtdcRequestIDType	RequestID;
	///ҵ��Ԫ
	TThostFtdcBusinessUnitType	BusinessUnit;
	///Ͷ���ױ���־
	TThostFtdcHedgeFlagType	HedgeFlag;
	///��Ȩ��Ȩ��ͷ���Ƿ��ԶԳ�
	TThostFtdcOptSelfCloseFlagType	OptSelfCloseFlag;
	///������Ȩ�ԶԳ���
	TThostFtdcOrderLocalIDType	OptionSelfCloseLocalID;
	///����������
	TThostFtdcExchangeIDType	ExchangeID;
	///��Ա����
	TThostFtdcParticipantIDType	ParticipantID;
	///�ͻ�����
	TThostFtdcClientIDType	ClientID;
	///��Լ�ڽ������Ĵ���
	TThostFtdcExchangeInstIDType	ExchangeInstID;
	///����������Ա����
	TThostFtdcTraderIDType	TraderID;
	///��װ���
	TThostFtdcInstallIDType	InstallID;
	///��Ȩ�ԶԳ��ύ״̬
	TThostFtdcOrderSubmitStatusType	OrderSubmitStatus;
	///������ʾ���
	TThostFtdcSequenceNoType	NotifySequence;
	///������
	TThostFtdcDateType	TradingDay;
	///������
	TThostFtdcSettlementIDType	SettlementID;
	///��Ȩ�ԶԳ���
	TThostFtdcOrderSysIDType	OptionSelfCloseSysID;
	///��������
	TThostFtdcDateType	InsertDate;
	///����ʱ��
	TThostFtdcTimeType	InsertTime;
	///����ʱ��
	TThostFtdcTimeType	CancelTime;
	///�ԶԳ���
	TThostFtdcOrderActionStatusType	OptionSelfCloseStatus;
	///�����Ա���
	TThostFtdcParticipantIDType	ClearingPartID;
	///���
	TThostFtdcSequenceNoType	SequenceNo;
	///Ӫҵ�����
	TThostFtdcBranchIDType	BranchID;
	///IP��ַ
	TThostFtdcIPAddressType	IPAddress;
	///Mac��ַ
	TThostFtdcMacAddressType	MacAddress;
};

///��Ȩ�ԶԳ������ѯ
struct CThostFtdcQryOptionSelfCloseActionField
{
	///���͹�˾����
	TThostFtdcBrokerIDType	BrokerID;
	///Ͷ���ߴ���
	TThostFtdcInvestorIDType	InvestorID;
	///����������
	TThostFtdcExchangeIDType	ExchangeID;
};

///��������Ȩ�ԶԳ����
struct CThostFtdcExchangeOptionSelfCloseActionField
{
	///����������
	TThostFtdcExchangeIDType	ExchangeID;
	///��Ȩ�ԶԳ�������
	TThostFtdcOrderSysIDType	OptionSelfCloseSysID;
	///������־
	TThostFtdcActionFlagType	ActionFlag;
	///��������
	TThostFtdcDateType	ActionDate;
	///����ʱ��
	TThostFtdcTimeType	ActionTime;
	///����������Ա����
	TThostFtdcTraderIDType	TraderID;
	///��װ���
	TThostFtdcInstallIDType	InstallID;
	///������Ȩ�ԶԳ���
	TThostFtdcOrderLocalIDType	OptionSelfCloseLocalID;
	///�������ر��
	TThostFtdcOrderLocalIDType	ActionLocalID;
	///��Ա����
	TThostFtdcParticipantIDType	ParticipantID;
	///�ͻ�����
	TThostFtdcClientIDType	ClientID;
	///ҵ��Ԫ
	TThostFtdcBusinessUnitType	BusinessUnit;
	///��������״̬
	TThostFtdcOrderActionStatusType	OrderActionStatus;
	///�û�����
	TThostFtdcUserIDType	UserID;
	///Ӫҵ�����
	TThostFtdcBranchIDType	BranchID;
	///IP��ַ
	TThostFtdcIPAddressType	IPAddress;
	///Mac��ַ
	TThostFtdcMacAddressType	MacAddress;
};

///��ʱ����ͬ��
struct CThostFtdcSyncDelaySwapField
{
	///������ˮ��
	TThostFtdcDepositSeqNoType	DelaySwapSeqNo;
	///���͹�˾����
	TThostFtdcBrokerIDType	BrokerID;
	///Ͷ���ߴ���
	TThostFtdcInvestorIDType	InvestorID;
	///Դ����
	TThostFtdcCurrencyIDType	FromCurrencyID;
	///Դ���
	TThostFtdcMoneyType	FromAmount;
	///Դ���㶳����
	TThostFtdcMoneyType	FromFrozenSwap;
	///Ŀ�����
	TThostFtdcCurrencyIDType	ToCurrencyID;
	///Ŀ����
	TThostFtdcMoneyType	ToAmount;
	///Ŀ�껻�㶳����
	TThostFtdcMoneyType	ToFrozenSwap;
};

///��ѯ��ʱ����ͬ��
struct CThostFtdcQrySyncDelaySwapField
{
	///���͹�˾����
	TThostFtdcBrokerIDType	BrokerID;
	///��ʱ������ˮ��
	TThostFtdcDepositSeqNoType	DelaySwapSeqNo;
};

///Ͷ�ʵ�Ԫ
struct CThostFtdcInvestUnitField
{
	///���͹�˾����
	TThostFtdcBrokerIDType	BrokerID;
	///Ͷ���ߴ���
	TThostFtdcInvestorIDType	InvestorID;
	///Ͷ�ʵ�Ԫ����
	TThostFtdcInvestUnitIDType	InvestUnitID;
	///Ͷ���ߵ�Ԫ����
	TThostFtdcPartyNameType	InvestorUnitName;
	///Ͷ���߷������
	TThostFtdcInvestorIDType	InvestorGroupID;
	///��������ģ�����
	TThostFtdcInvestorIDType	CommModelID;
	///��֤����ģ�����
	TThostFtdcInvestorIDType	MarginModelID;
	///�ʽ��˺�
	TThostFtdcAccountIDType	AccountID;
	///���ִ���
	TThostFtdcCurrencyIDType	CurrencyID;
};

///��ѯͶ�ʵ�Ԫ
struct CThostFtdcQryInvestUnitField
{
	///���͹�˾����
	TThostFtdcBrokerIDType	BrokerID;
	///Ͷ���ߴ���
	TThostFtdcInvestorIDType	InvestorID;
	///Ͷ�ʵ�Ԫ����
	TThostFtdcInvestUnitIDType	InvestUnitID;
};

///�г�����
struct CThostFtdcMarketDataField
{
	///������
	TThostFtdcDateType	TradingDay;
	///��Լ����
	TThostFtdcInstrumentIDType	InstrumentID;
	///����������
	TThostFtdcExchangeIDType	ExchangeID;
	///��Լ�ڽ������Ĵ���
	TThostFtdcExchangeInstIDType	ExchangeInstID;
	///���¼�
	TThostFtdcPriceType	LastPrice;
	///�ϴν����
	TThostFtdcPriceType	PreSettlementPrice;
	///������
	TThostFtdcPriceType	PreClosePrice;
	///��ֲ���
	TThostFtdcLargeVolumeType	PreOpenInterest;
	///����
	TThostFtdcPriceType	OpenPrice;
	///��߼�
	TThostFtdcPriceType	HighestPrice;
	///��ͼ�
	TThostFtdcPriceType	LowestPrice;
	///����
	TThostFtdcVolumeType	Volume;
	///�ɽ����
	TThostFtdcMoneyType	Turnover;
	///�ֲ���
	TThostFtdcLargeVolumeType	OpenInterest;
	///������
	TThostFtdcPriceType	ClosePrice;
	///���ν����
	TThostFtdcPriceType	SettlementPrice;
	///��ͣ���
	TThostFtdcPriceType	UpperLimitPrice;
	///��ͣ���
	TThostFtdcPriceType	LowerLimitPrice;
	///����ʵ��
	TThostFtdcRatioType	PreDelta;
	///����ʵ��
	TThostFtdcRatioType	CurrDelta;
	///����޸�ʱ��
	TThostFtdcTimeType	UpdateTime;
	///����޸ĺ���
	TThostFtdcMillisecType	UpdateMillisec;
	///ҵ������
	TThostFtdcDateType	ActionDay;
	///���鷢��ʱ��
	TThostFtdcSendingTimeType	SendingTime;
	///�ɽ���(long long�ͣ�
	TThostFtdcBigVolumeType	BigVolume;
};

///�����������
struct CThostFtdcMarketDataBaseField
{
	///������
	TThostFtdcDateType	TradingDay;
	///�ϴν����
	TThostFtdcPriceType	PreSettlementPrice;
	///������
	TThostFtdcPriceType	PreClosePrice;
	///��ֲ���
	TThostFtdcLargeVolumeType	PreOpenInterest;
	///����ʵ��
	TThostFtdcRatioType	PreDelta;
};

///���龲̬����
struct CThostFtdcMarketDataStaticField
{
	///����
	TThostFtdcPriceType	OpenPrice;
	///��߼�
	TThostFtdcPriceType	HighestPrice;
	///��ͼ�
	TThostFtdcPriceType	LowestPrice;
	///������
	TThostFtdcPriceType	ClosePrice;
	///��ͣ���
	TThostFtdcPriceType	UpperLimitPrice;
	///��ͣ���
	TThostFtdcPriceType	LowerLimitPrice;
	///���ν����
	TThostFtdcPriceType	SettlementPrice;
	///����ʵ��
	TThostFtdcRatioType	CurrDelta;
};

///�������³ɽ�����
struct CThostFtdcMarketDataLastMatchField
{
	///���¼�
	TThostFtdcPriceType	LastPrice;
	///����
	TThostFtdcVolumeType	Volume;
	///�ɽ����
	TThostFtdcMoneyType	Turnover;
	///�ֲ���
	TThostFtdcLargeVolumeType	OpenInterest;
	///����(long long)
	TThostFtdcBigVolumeType	BigVolume;
};

///�������ż�����
struct CThostFtdcMarketDataBestPriceField
{
	///�����һ
	TThostFtdcPriceType	BidPrice1;
	///������һ
	TThostFtdcVolumeType	BidVolume1;
	///������һ
	TThostFtdcPriceType	AskPrice1;
	///������һ
	TThostFtdcVolumeType	AskVolume1;
	///�۶ϲο���
	TThostFtdcPriceType	CircuitRefPrice;
};

///�����������������
struct CThostFtdcMarketDataBid23Field
{
	///����۶�
	TThostFtdcPriceType	BidPrice2;
	///��������
	TThostFtdcVolumeType	BidVolume2;
	///�������
	TThostFtdcPriceType	BidPrice3;
	///��������
	TThostFtdcVolumeType	BidVolume3;
};

///������������������
struct CThostFtdcMarketDataAsk23Field
{
	///�����۶�
	TThostFtdcPriceType	AskPrice2;
	///��������
	TThostFtdcVolumeType	AskVolume2;
	///��������
	TThostFtdcPriceType	AskPrice3;
	///��������
	TThostFtdcVolumeType	AskVolume3;
};

///���������ġ�������
struct CThostFtdcMarketDataBid45Field
{
	///�������
	TThostFtdcPriceType	BidPrice4;
	///��������
	TThostFtdcVolumeType	BidVolume4;
	///�������
	TThostFtdcPriceType	BidPrice5;
	///��������
	TThostFtdcVolumeType	BidVolume5;
};

///���������ġ�������
struct CThostFtdcMarketDataAsk45Field
{
	///��������
	TThostFtdcPriceType	AskPrice4;
	///��������
	TThostFtdcVolumeType	AskVolume4;
	///��������
	TThostFtdcPriceType	AskPrice5;
	///��������
	TThostFtdcVolumeType	AskVolume5;
};

///�������ʱ������
struct CThostFtdcMarketDataUpdateTimeField
{
	///��Լ����
	TThostFtdcInstrumentIDType	InstrumentID;
	///����޸�ʱ��
	TThostFtdcTimeType	UpdateTime;
	///����޸ĺ���
	TThostFtdcMillisecType	UpdateMillisec;
	///ҵ������
	TThostFtdcDateType	ActionDay;
	///����������
	TThostFtdcExchangeIDType	ExchangeID;
	///���鷢��ʱ��
	TThostFtdcSendingTimeType	SendingTime;
};

///���齻������������
struct CThostFtdcMarketDataExchangeField
{
	///����������
	TThostFtdcExchangeIDType	ExchangeID;
};

///ָ���ĺ�Լ
struct CThostFtdcSpecificInstrumentField
{
	///��Լ����
	TThostFtdcInstrumentIDType	InstrumentID;
};

///��Լ״̬
struct CThostFtdcInstrumentStatusField
{
	///����������
	TThostFtdcExchangeIDType	ExchangeID;
	///��Լ�ڽ������Ĵ���
	TThostFtdcExchangeInstIDType	ExchangeInstID;
	///���������
	TThostFtdcSettlementGroupIDType	SettlementGroupID;
	///��Լ����
	TThostFtdcInstrumentIDType	InstrumentID;
	///��Լ����״̬
	TThostFtdcInstrumentStatusType	InstrumentStatus;
	///���׽׶α��
	TThostFtdcTradingSegmentSNType	TradingSegmentSN;
	///���뱾״̬ʱ��
	TThostFtdcTimeType	EnterTime;
	///���뱾״̬ԭ��
	TThostFtdcInstStatusEnterReasonType	EnterReason;
};

///��ѯ��Լ״̬
struct CThostFtdcQryInstrumentStatusField
{
	///����������
	TThostFtdcExchangeIDType	ExchangeID;
	///��Լ�ڽ������Ĵ���
	TThostFtdcExchangeInstIDType	ExchangeInstID;
};

///Ͷ�����˻�
struct CThostFtdcInvestorAccountField
{
	///���͹�˾����
	TThostFtdcBrokerIDType	BrokerID;
	///Ͷ���ߴ���
	TThostFtdcInvestorIDType	InvestorID;
	///Ͷ�����ʺ�
	TThostFtdcAccountIDType	AccountID;
	///���ִ���
	TThostFtdcCurrencyIDType	CurrencyID;
	///ҵ������
	TThostFtdcBizTypeType	BizType;
};

///����ӯ���㷨
struct CThostFtdcPositionProfitAlgorithmField
{
	///���͹�˾����
	TThostFtdcBrokerIDType	BrokerID;
	///Ͷ�����ʺ�
	TThostFtdcAccountIDType	AccountID;
	///ӯ���㷨
	TThostFtdcAlgorithmType	Algorithm;
	///��ע
	TThostFtdcMemoType	Memo;
	///���ִ���
	TThostFtdcCurrencyIDType	CurrencyID;
};

///��Ա�ʽ��ۿ�
struct CThostFtdcDiscountField
{
	///���͹�˾����
	TThostFtdcBrokerIDType	BrokerID;
	///Ͷ���߷�Χ
	TThostFtdcInvestorRangeType	InvestorRange;
	///Ͷ���ߴ���
	TThostFtdcInvestorIDType	InvestorID;
	///�ʽ��ۿ۱���
	TThostFtdcRatioType	Discount;
};

///��ѯת������
struct CThostFtdcQryTransferBankField
{
	///���д���
	TThostFtdcBankIDType	BankID;
	///���з����Ĵ���
	TThostFtdcBankBrchIDType	BankBrchID;
};

///ת������
struct CThostFtdcTransferBankField
{
	///���д���
	TThostFtdcBankIDType	BankID;
	///���з����Ĵ���
	TThostFtdcBankBrchIDType	BankBrchID;
	///��������
	TThostFtdcBankNameType	BankName;
	///�Ƿ��Ծ
	TThostFtdcBoolType	IsActive;
};

///��ѯͶ���ֲ߳���ϸ
struct CThostFtdcQryInvestorPositionDetailField
{
	///���͹�˾����
	TThostFtdcBrokerIDType	BrokerID;
	///Ͷ���ߴ���
	TThostFtdcInvestorIDType	InvestorID;
	///��Լ����
	TThostFtdcInstrumentIDType	InstrumentID;
	///����������
	TThostFtdcExchangeIDType	ExchangeID;
	///Ͷ�ʵ�Ԫ����
	TThostFtdcInvestUnitIDType	InvestUnitID;
};

///Ͷ���ֲ߳���ϸ
struct CThostFtdcInvestorPositionDetailField
{
	///��Լ����
	TThostFtdcInstrumentIDType	InstrumentID;
	///���͹�˾����
	TThostFtdcBrokerIDType	BrokerID;
	///Ͷ���ߴ���
	TThostFtdcInvestorIDType	InvestorID;
	///Ͷ���ױ���־
	TThostFtdcHedgeFlagType	HedgeFlag;
	///����
	TThostFtdcDirectionType	Direction;
	///��������
	TThostFtdcDateType	OpenDate;
	///�ɽ����
	TThostFtdcTradeIDType	TradeID;
	///����
	TThostFtdcVolumeType	Volume;
	///���ּ�
	TThostFtdcPriceType	OpenPrice;
	///������
	TThostFtdcDateType	TradingDay;
	///������
	TThostFtdcSettlementIDType	SettlementID;
	///�ɽ�����
	TThostFtdcTradeTypeType	TradeType;
	///��Ϻ�Լ����
	TThostFtdcInstrumentIDType	CombInstrumentID;
	///����������
	TThostFtdcExchangeIDType	ExchangeID;
	///���ն���ƽ��ӯ��
	TThostFtdcMoneyType	CloseProfitByDate;
	///��ʶԳ�ƽ��ӯ��
	TThostFtdcMoneyType	CloseProfitByTrade;
	///���ն��гֲ�ӯ��
	TThostFtdcMoneyType	PositionProfitByDate;
	///��ʶԳ�ֲ�ӯ��
	TThostFtdcMoneyType	PositionProfitByTrade;
	///Ͷ���߱�֤��
	TThostFtdcMoneyType	Margin;
	///��������֤��
	TThostFtdcMoneyType	ExchMargin;
	///��֤����
	TThostFtdcRatioType	MarginRateByMoney;
	///��֤����(������)
	TThostFtdcRatioType	MarginRateByVolume;
	///������
	TThostFtdcPriceType	LastSettlementPrice;
	///�����
	TThostFtdcPriceType	SettlementPrice;
	///ƽ����
	TThostFtdcVolumeType	CloseVolume;
	///ƽ�ֽ��
	TThostFtdcMoneyType	CloseAmount;
	///Ͷ�ʵ�Ԫ����
	TThostFtdcInvestUnitIDType	InvestUnitID;
};

///�ʽ��˻�������
struct CThostFtdcTradingAccountPasswordField
{
	///���͹�˾����
	TThostFtdcBrokerIDType	BrokerID;
	///Ͷ�����ʺ�
	TThostFtdcAccountIDType	AccountID;
	///����
	TThostFtdcPasswordType	Password;
	///���ִ���
	TThostFtdcCurrencyIDType	CurrencyID;
};

///���������鱨�̻�
struct CThostFtdcMDTraderOfferField
{
	///����������
	TThostFtdcExchangeIDType	ExchangeID;
	///����������Ա����
	TThostFtdcTraderIDType	TraderID;
	///��Ա����
	TThostFtdcParticipantIDType	ParticipantID;
	///����
	TThostFtdcPasswordType	Password;
	///��װ���
	TThostFtdcInstallIDType	InstallID;
	///���ر������
	TThostFtdcOrderLocalIDType	OrderLocalID;
	///����������Ա����״̬
	TThostFtdcTraderConnectStatusType	TraderConnectStatus;
	///�����������������
	TThostFtdcDateType	ConnectRequestDate;
	///�������������ʱ��
	TThostFtdcTimeType	ConnectRequestTime;
	///�ϴα�������
	TThostFtdcDateType	LastReportDate;
	///�ϴα���ʱ��
	TThostFtdcTimeType	LastReportTime;
	///�����������
	TThostFtdcDateType	ConnectDate;
	///�������ʱ��
	TThostFtdcTimeType	ConnectTime;
	///��������
	TThostFtdcDateType	StartDate;
	///����ʱ��
	TThostFtdcTimeType	StartTime;
	///������
	TThostFtdcDateType	TradingDay;
	///���͹�˾����
	TThostFtdcBrokerIDType	BrokerID;
	///��ϯλ���ɽ����
	TThostFtdcTradeIDType	MaxTradeID;
	///��ϯλ��󱨵�����
	TThostFtdcReturnCodeType	MaxOrderMessageReference;
	///ҵ������
	TThostFtdcBizTypeType	BizType;
	///PBU���
	TThostFtdcPbuSequenceIDType	PbuSequenceID;
};

///��ѯ���鱨�̻�
struct CThostFtdcQryMDTraderOfferField
{
	///����������
	TThostFtdcExchangeIDType	ExchangeID;
	///��Ա����
	TThostFtdcParticipantIDType	ParticipantID;
	///����������Ա����
	TThostFtdcTraderIDType	TraderID;
};

///��ѯ�ͻ�֪ͨ
struct CThostFtdcQryNoticeField
{
	///���͹�˾����
	TThostFtdcBrokerIDType	BrokerID;
};

///�ͻ�֪ͨ
struct CThostFtdcNoticeField
{
	///���͹�˾����
	TThostFtdcBrokerIDType	BrokerID;
	///��Ϣ����
	TThostFtdcContentType	Content;
	///���͹�˾֪ͨ�������к�
	TThostFtdcSequenceLabelType	SequenceLabel;
};

///�û�Ȩ��
struct CThostFtdcUserRightField
{
	///���͹�˾����
	TThostFtdcBrokerIDType	BrokerID;
	///�û�����
	TThostFtdcUserIDType	UserID;
	///�ͻ�Ȩ������
	TThostFtdcUserRightTypeType	UserRightType;
	///�Ƿ��ֹ
	TThostFtdcBoolType	IsForbidden;
};

///��ѯ������Ϣȷ����
struct CThostFtdcQrySettlementInfoConfirmField
{
	///���͹�˾����
	TThostFtdcBrokerIDType	BrokerID;
	///Ͷ���ߴ���
	TThostFtdcInvestorIDType	InvestorID;
	///Ͷ�����ʺ�
	TThostFtdcAccountIDType	AccountID;
	///���ִ���
	TThostFtdcCurrencyIDType	CurrencyID;
};

///װ�ؽ�����Ϣ
struct CThostFtdcLoadSettlementInfoField
{
	///���͹�˾����
	TThostFtdcBrokerIDType	BrokerID;
};

///���͹�˾�����ʽ��㷨��
struct CThostFtdcBrokerWithdrawAlgorithmField
{
	///���͹�˾����
	TThostFtdcBrokerIDType	BrokerID;
	///�����ʽ��㷨
	TThostFtdcAlgorithmType	WithdrawAlgorithm;
	///�ʽ�ʹ����
	TThostFtdcRatioType	UsingRatio;
	///�����Ƿ����ƽ��ӯ��
	TThostFtdcIncludeCloseProfitType	IncludeCloseProfit;
	///�����޲����޳ɽ��ͻ��Ƿ��ܿ����������
	TThostFtdcAllWithoutTradeType	AllWithoutTrade;
	///�����Ƿ����ƽ��ӯ��
	TThostFtdcIncludeCloseProfitType	AvailIncludeCloseProfit;
	///�Ƿ������û��¼�
	TThostFtdcBoolType	IsBrokerUserEvent;
	///���ִ���
	TThostFtdcCurrencyIDType	CurrencyID;
	///������Ѻ����
	TThostFtdcRatioType	FundMortgageRatio;
	///Ȩ���㷨
	TThostFtdcBalanceAlgorithmType	BalanceAlgorithm;
};

///�ʽ��˻���������
struct CThostFtdcTradingAccountPasswordUpdateV1Field
{
	///���͹�˾����
	TThostFtdcBrokerIDType	BrokerID;
	///Ͷ���ߴ���
	TThostFtdcInvestorIDType	InvestorID;
	///ԭ���Ŀ���
	TThostFtdcPasswordType	OldPassword;
	///�µĿ���
	TThostFtdcPasswordType	NewPassword;
};

///�ʽ��˻���������
struct CThostFtdcTradingAccountPasswordUpdateField
{
	///���͹�˾����
	TThostFtdcBrokerIDType	BrokerID;
	///Ͷ�����ʺ�
	TThostFtdcAccountIDType	AccountID;
	///ԭ���Ŀ���
	TThostFtdcPasswordType	OldPassword;
	///�µĿ���
	TThostFtdcPasswordType	NewPassword;
	///���ִ���
	TThostFtdcCurrencyIDType	CurrencyID;
};

///��ѯ��Ϻ�Լ����
struct CThostFtdcQryCombinationLegField
{
	///��Ϻ�Լ����
	TThostFtdcInstrumentIDType	CombInstrumentID;
	///���ȱ��
	TThostFtdcLegIDType	LegID;
	///���Ⱥ�Լ����
	TThostFtdcInstrumentIDType	LegInstrumentID;
};

///��ѯ��Ϻ�Լ����
struct CThostFtdcQrySyncStatusField
{
	///������
	TThostFtdcDateType	TradingDay;
};

///��Ͻ��׺�Լ�ĵ���
struct CThostFtdcCombinationLegField
{
	///��Ϻ�Լ����
	TThostFtdcInstrumentIDType	CombInstrumentID;
	///���ȱ��
	TThostFtdcLegIDType	LegID;
	///���Ⱥ�Լ����
	TThostFtdcInstrumentIDType	LegInstrumentID;
	///��������
	TThostFtdcDirectionType	Direction;
	///���ȳ���
	TThostFtdcLegMultipleType	LegMultiple;
	///��������
	TThostFtdcImplyLevelType	ImplyLevel;
};

///����ͬ��״̬
struct CThostFtdcSyncStatusField
{
	///������
	TThostFtdcDateType	TradingDay;
	///����ͬ��״̬
	TThostFtdcDataSyncStatusType	DataSyncStatus;
};

///��ѯ��ϵ��
struct CThostFtdcQryLinkManField
{
	///���͹�˾����
	TThostFtdcBrokerIDType	BrokerID;
	///Ͷ���ߴ���
	TThostFtdcInvestorIDType	InvestorID;
};

///��ϵ��
struct CThostFtdcLinkManField
{
	///���͹�˾����
	TThostFtdcBrokerIDType	BrokerID;
	///Ͷ���ߴ���
	TThostFtdcInvestorIDType	InvestorID;
	///��ϵ������
	TThostFtdcPersonTypeType	PersonType;
	///֤������
	TThostFtdcIdCardTypeType	IdentifiedCardType;
	///֤������
	TThostFtdcIdentifiedCardNoType	IdentifiedCardNo;
	///����
	TThostFtdcPartyNameType	PersonName;
	///��ϵ�绰
	TThostFtdcTelephoneType	Telephone;
	///ͨѶ��ַ
	TThostFtdcAddressType	Address;
	///��������
	TThostFtdcZipCodeType	ZipCode;
	///���ȼ�
	TThostFtdcPriorityType	Priority;
	///������������
	TThostFtdcUOAZipCodeType	UOAZipCode;
	///ȫ��
	TThostFtdcInvestorFullNameType	PersonFullName;
};

///��ѯ���͹�˾�û��¼�
struct CThostFtdcQryBrokerUserEventField
{
	///���͹�˾����
	TThostFtdcBrokerIDType	BrokerID;
	///�û�����
	TThostFtdcUserIDType	UserID;
	///�û��¼�����
	TThostFtdcUserEventTypeType	UserEventType;
};

///��ѯ���͹�˾�û��¼�
struct CThostFtdcBrokerUserEventField
{
	///���͹�˾����
	TThostFtdcBrokerIDType	BrokerID;
	///�û�����
	TThostFtdcUserIDType	UserID;
	///�û��¼�����
	TThostFtdcUserEventTypeType	UserEventType;
	///�û��¼����
	TThostFtdcSequenceNoType	EventSequenceNo;
	///�¼���������
	TThostFtdcDateType	EventDate;
	///�¼�����ʱ��
	TThostFtdcTimeType	EventTime;
	///�û��¼���Ϣ
	TThostFtdcUserEventInfoType	UserEventInfo;
	///Ͷ���ߴ���
	TThostFtdcInvestorIDType	InvestorID;
	///��Լ����
	TThostFtdcInstrumentIDType	InstrumentID;
	///����������
	TThostFtdcExchangeIDType	ExchangeID;
};

///��ѯǩԼ��������
struct CThostFtdcQryContractBankField
{
	///���͹�˾����
	TThostFtdcBrokerIDType	BrokerID;
	///���д���
	TThostFtdcBankIDType	BankID;
	///���з����Ĵ���
	TThostFtdcBankBrchIDType	BankBrchID;
};

///��ѯǩԼ������Ӧ
struct CThostFtdcContractBankField
{
	///���͹�˾����
	TThostFtdcBrokerIDType	BrokerID;
	///���д���
	TThostFtdcBankIDType	BankID;
	///���з����Ĵ���
	TThostFtdcBankBrchIDType	BankBrchID;
	///��������
	TThostFtdcBankNameType	BankName;
};

///Ͷ������ϳֲ���ϸ
struct CThostFtdcInvestorPositionCombineDetailField
{
	///������
	TThostFtdcDateType	TradingDay;
	///��������
	TThostFtdcDateType	OpenDate;
	///����������
	TThostFtdcExchangeIDType	ExchangeID;
	///������
	TThostFtdcSettlementIDType	SettlementID;
	///���͹�˾����
	TThostFtdcBrokerIDType	BrokerID;
	///Ͷ���ߴ���
	TThostFtdcInvestorIDType	InvestorID;
	///��ϱ��
	TThostFtdcTradeIDType	ComTradeID;
	///��ϱ��
	TThostFtdcTradeIDType	TradeID;
	///��Լ����
	TThostFtdcInstrumentIDType	InstrumentID;
	///Ͷ���ױ���־
	TThostFtdcHedgeFlagType	HedgeFlag;
	///����
	TThostFtdcDirectionType	Direction;
	///�ֲ���
	TThostFtdcVolumeType	TotalAmt;
	///Ͷ���߱�֤��
	TThostFtdcMoneyType	Margin;
	///��������֤��
	TThostFtdcMoneyType	ExchMargin;
	///��֤����
	TThostFtdcRatioType	MarginRateByMoney;
	///��֤����(������)
	TThostFtdcRatioType	MarginRateByVolume;
	///���ȱ��
	TThostFtdcLegIDType	LegID;
	///���ȳ���
	TThostFtdcLegMultipleType	LegMultiple;
	///��ϳֲֺ�Լ����
	TThostFtdcInstrumentIDType	CombInstrumentID;
	///�ɽ����
	TThostFtdcTradeGroupIDType	TradeGroupID;
	///Ͷ�ʵ�Ԫ����
	TThostFtdcInvestUnitIDType	InvestUnitID;
	///���ƽ�ֶ���
	TThostFtdcVolumeType	CombCloseFrozen;
};

///Ԥ��
struct CThostFtdcParkedOrderField
{
	///���͹�˾����
	TThostFtdcBrokerIDType	BrokerID;
	///Ͷ���ߴ���
	TThostFtdcInvestorIDType	InvestorID;
	///��Լ����
	TThostFtdcInstrumentIDType	InstrumentID;
	///��������
	TThostFtdcOrderRefType	OrderRef;
	///�û�����
	TThostFtdcUserIDType	UserID;
	///�����۸�����
	TThostFtdcOrderPriceTypeType	OrderPriceType;
	///��������
	TThostFtdcDirectionType	Direction;
	///��Ͽ�ƽ��־
	TThostFtdcCombOffsetFlagType	CombOffsetFlag;
	///���Ͷ���ױ���־
	TThostFtdcCombHedgeFlagType	CombHedgeFlag;
	///�۸�
	TThostFtdcPriceType	LimitPrice;
	///����
	TThostFtdcVolumeType	VolumeTotalOriginal;
	///��Ч������
	TThostFtdcTimeConditionType	TimeCondition;
	///GTD����
	TThostFtdcDateType	GTDDate;
	///�ɽ�������
	TThostFtdcVolumeConditionType	VolumeCondition;
	///��С�ɽ���
	TThostFtdcVolumeType	MinVolume;
	///��������
	TThostFtdcContingentConditionType	ContingentCondition;
	///ֹ���
	TThostFtdcPriceType	StopPrice;
	///ǿƽԭ��
	TThostFtdcForceCloseReasonType	ForceCloseReason;
	///�Զ������־
	TThostFtdcBoolType	IsAutoSuspend;
	///ҵ��Ԫ
	TThostFtdcBusinessUnitType	BusinessUnit;
	///������
	TThostFtdcRequestIDType	RequestID;
	///�û�ǿ����־
	TThostFtdcBoolType	UserForceClose;
	///����������
	TThostFtdcExchangeIDType	ExchangeID;
	///Ԥ�񱨵����
	TThostFtdcParkedOrderIDType	ParkedOrderID;
	///�û�����
	TThostFtdcUserTypeType	UserType;
	///Ԥ��״̬
	TThostFtdcParkedOrderStatusType	Status;
	///�������
	TThostFtdcErrorIDType	ErrorID;
	///������Ϣ
	TThostFtdcErrorMsgType	ErrorMsg;
	///��������־
	TThostFtdcBoolType	IsSwapOrder;
	///�ʽ��˺�
	TThostFtdcAccountIDType	AccountID;
	///���ִ���
	TThostFtdcCurrencyIDType	CurrencyID;
	///���ױ���
	TThostFtdcClientIDType	ClientID;
	///Ͷ�ʵ�Ԫ����
	TThostFtdcInvestUnitIDType	InvestUnitID;
	///��������Ч�ֶ�
	TThostFtdcOldIPAddressType	reserve1;
	///Mac��ַ
	TThostFtdcMacAddressType	MacAddress;
	///����������
	TThostFtdcOwnerTypeType	OwnerType;
	///��ϱ��
	TThostFtdcTradeIDType	ComTradeID;
	///��½PBU
	TThostFtdcTraderIDType	LoginPBU;
	///IP��ַ
	TThostFtdcIPAddressType	IPAddress;
};

///����Ԥ�񵥲���
struct CThostFtdcParkedOrderActionField
{
	///���͹�˾����
	TThostFtdcBrokerIDType	BrokerID;
	///Ͷ���ߴ���
	TThostFtdcInvestorIDType	InvestorID;
	///������������
	TThostFtdcOrderActionRefType	OrderActionRef;
	///��������
	TThostFtdcOrderRefType	OrderRef;
	///������
	TThostFtdcRequestIDType	RequestID;
	///ǰ�ñ��
	TThostFtdcFrontIDType	FrontID;
	///�Ự���
	TThostFtdcSessionIDType	SessionID;
	///����������
	TThostFtdcExchangeIDType	ExchangeID;
	///�������
	TThostFtdcOrderSysIDType	OrderSysID;
	///������־
	TThostFtdcActionFlagType	ActionFlag;
	///�۸�
	TThostFtdcPriceType	LimitPrice;
	///�����仯
	TThostFtdcVolumeType	VolumeChange;
	///�û�����
	TThostFtdcUserIDType	UserID;
	///��Լ����
	TThostFtdcInstrumentIDType	InstrumentID;
	///Ԥ�񳷵������
	TThostFtdcParkedOrderActionIDType	ParkedOrderActionID;
	///�û�����
	TThostFtdcUserTypeType	UserType;
	///Ԥ�񳷵�״̬
	TThostFtdcParkedOrderStatusType	Status;
	///�������
	TThostFtdcErrorIDType	ErrorID;
	///������Ϣ
	TThostFtdcErrorMsgType	ErrorMsg;
	///Ͷ�ʵ�Ԫ����
	TThostFtdcInvestUnitIDType	InvestUnitID;
	///��������Ч�ֶ�
	TThostFtdcOldIPAddressType	reserve1;
	///Mac��ַ
	TThostFtdcMacAddressType	MacAddress;
	///IP��ַ
	TThostFtdcIPAddressType	IPAddress;
};

///��ѯԤ��
struct CThostFtdcQryParkedOrderField
{
	///���͹�˾����
	TThostFtdcBrokerIDType	BrokerID;
	///Ͷ���ߴ���
	TThostFtdcInvestorIDType	InvestorID;
	///��Լ����
	TThostFtdcInstrumentIDType	InstrumentID;
	///����������
	TThostFtdcExchangeIDType	ExchangeID;
	///Ͷ�ʵ�Ԫ����
	TThostFtdcInvestUnitIDType	InvestUnitID;
};

///��ѯԤ�񳷵�
struct CThostFtdcQryParkedOrderActionField
{
	///���͹�˾����
	TThostFtdcBrokerIDType	BrokerID;
	///Ͷ���ߴ���
	TThostFtdcInvestorIDType	InvestorID;
	///��Լ����
	TThostFtdcInstrumentIDType	InstrumentID;
	///����������
	TThostFtdcExchangeIDType	ExchangeID;
	///Ͷ�ʵ�Ԫ����
	TThostFtdcInvestUnitIDType	InvestUnitID;
};

///ɾ��Ԥ��
struct CThostFtdcRemoveParkedOrderField
{
	///���͹�˾����
	TThostFtdcBrokerIDType	BrokerID;
	///Ͷ���ߴ���
	TThostFtdcInvestorIDType	InvestorID;
	///Ԥ�񱨵����
	TThostFtdcParkedOrderIDType	ParkedOrderID;
	///Ͷ�ʵ�Ԫ����
	TThostFtdcInvestUnitIDType	InvestUnitID;
};

///ɾ��Ԥ�񳷵�
struct CThostFtdcRemoveParkedOrderActionField
{
	///���͹�˾����
	TThostFtdcBrokerIDType	BrokerID;
	///Ͷ���ߴ���
	TThostFtdcInvestorIDType	InvestorID;
	///Ԥ�񳷵����
	TThostFtdcParkedOrderActionIDType	ParkedOrderActionID;
	///Ͷ�ʵ�Ԫ����
	TThostFtdcInvestUnitIDType	InvestUnitID;
};

///���͹�˾�����ʽ��㷨��
struct CThostFtdcInvestorWithdrawAlgorithmField
{
	///���͹�˾����
	TThostFtdcBrokerIDType	BrokerID;
	///Ͷ���߷�Χ
	TThostFtdcInvestorRangeType	InvestorRange;
	///Ͷ���ߴ���
	TThostFtdcInvestorIDType	InvestorID;
	///�����ʽ����
	TThostFtdcRatioType	UsingRatio;
	///���ִ���
	TThostFtdcCurrencyIDType	CurrencyID;
	///������Ѻ����
	TThostFtdcRatioType	FundMortgageRatio;
};

///��ѯ��ϳֲ���ϸ
struct CThostFtdcQryInvestorPositionCombineDetailField
{
	///���͹�˾����
	TThostFtdcBrokerIDType	BrokerID;
	///Ͷ���ߴ���
	TThostFtdcInvestorIDType	InvestorID;
	///��ϳֲֺ�Լ����
	TThostFtdcInstrumentIDType	CombInstrumentID;
	///����������
	TThostFtdcExchangeIDType	ExchangeID;
	///Ͷ�ʵ�Ԫ����
	TThostFtdcInvestUnitIDType	InvestUnitID;
};

///�ɽ�����
struct CThostFtdcMarketDataAveragePriceField
{
	///���վ���
	TThostFtdcPriceType	AveragePrice;
};

///У��Ͷ��������
struct CThostFtdcVerifyInvestorPasswordField
{
	///���͹�˾����
	TThostFtdcBrokerIDType	BrokerID;
	///Ͷ���ߴ���
	TThostFtdcInvestorIDType	InvestorID;
	///����
	TThostFtdcPasswordType	Password;
};

///�û�IP
struct CThostFtdcUserIPField
{
	///���͹�˾����
	TThostFtdcBrokerIDType	BrokerID;
	///�û�����
	TThostFtdcUserIDType	UserID;
	///��������Ч�ֶ�
	TThostFtdcOldIPAddressType	reserve1;
	///��������Ч�ֶ�
	TThostFtdcOldIPAddressType	reserve2;
	///Mac��ַ
	TThostFtdcMacAddressType	MacAddress;
	///IP��ַ
	TThostFtdcIPAddressType	IPAddress;
	///IP��ַ����
	TThostFtdcIPAddressType	IPMask;
};

///�û��¼�֪ͨ��Ϣ
struct CThostFtdcTradingNoticeInfoField
{
	///���͹�˾����
	TThostFtdcBrokerIDType	BrokerID;
	///Ͷ���ߴ���
	TThostFtdcInvestorIDType	InvestorID;
	///����ʱ��
	TThostFtdcTimeType	SendTime;
	///��Ϣ����
	TThostFtdcContentType	FieldContent;
	///����ϵ�к�
	TThostFtdcSequenceSeriesType	SequenceSeries;
	///���к�
	TThostFtdcSequenceNoType	SequenceNo;
	///Ͷ�ʵ�Ԫ����
	TThostFtdcInvestUnitIDType	InvestUnitID;
};

///�û��¼�֪ͨ
struct CThostFtdcTradingNoticeField
{
	///���͹�˾����
	TThostFtdcBrokerIDType	BrokerID;
	///Ͷ���߷�Χ
	TThostFtdcInvestorRangeType	InvestorRange;
	///Ͷ���ߴ���
	TThostFtdcInvestorIDType	InvestorID;
	///����ϵ�к�
	TThostFtdcSequenceSeriesType	SequenceSeries;
	///�û�����
	TThostFtdcUserIDType	UserID;
	///����ʱ��
	TThostFtdcTimeType	SendTime;
	///���к�
	TThostFtdcSequenceNoType	SequenceNo;
	///��Ϣ����
	TThostFtdcContentType	FieldContent;
	///Ͷ�ʵ�Ԫ����
	TThostFtdcInvestUnitIDType	InvestUnitID;
};

///��ѯ�����¼�֪ͨ
struct CThostFtdcQryTradingNoticeField
{
	///���͹�˾����
	TThostFtdcBrokerIDType	BrokerID;
	///Ͷ���ߴ���
	TThostFtdcInvestorIDType	InvestorID;
	///Ͷ�ʵ�Ԫ����
	TThostFtdcInvestUnitIDType	InvestUnitID;
};

///��ѯ���󱨵�
struct CThostFtdcQryErrOrderField
{
	///���͹�˾����
	TThostFtdcBrokerIDType	BrokerID;
	///Ͷ���ߴ���
	TThostFtdcInvestorIDType	InvestorID;
};

///���󱨵�
struct CThostFtdcErrOrderField
{
	///���͹�˾����
	TThostFtdcBrokerIDType	BrokerID;
	///Ͷ���ߴ���
	TThostFtdcInvestorIDType	InvestorID;
	///��Լ����
	TThostFtdcInstrumentIDType	InstrumentID;
	///��������
	TThostFtdcOrderRefType	OrderRef;
	///�û�����
	TThostFtdcUserIDType	UserID;
	///�����۸�����
	TThostFtdcOrderPriceTypeType	OrderPriceType;
	///��������
	TThostFtdcDirectionType	Direction;
	///��Ͽ�ƽ��־
	TThostFtdcCombOffsetFlagType	CombOffsetFlag;
	///���Ͷ���ױ���־
	TThostFtdcCombHedgeFlagType	CombHedgeFlag;
	///�۸�
	TThostFtdcPriceType	LimitPrice;
	///����
	TThostFtdcVolumeType	VolumeTotalOriginal;
	///��Ч������
	TThostFtdcTimeConditionType	TimeCondition;
	///GTD����
	TThostFtdcDateType	GTDDate;
	///�ɽ�������
	TThostFtdcVolumeConditionType	VolumeCondition;
	///��С�ɽ���
	TThostFtdcVolumeType	MinVolume;
	///��������
	TThostFtdcContingentConditionType	ContingentCondition;
	///ֹ���
	TThostFtdcPriceType	StopPrice;
	///ǿƽԭ��
	TThostFtdcForceCloseReasonType	ForceCloseReason;
	///�Զ������־
	TThostFtdcBoolType	IsAutoSuspend;
	///ҵ��Ԫ
	TThostFtdcBusinessUnitType	BusinessUnit;
	///������
	TThostFtdcRequestIDType	RequestID;
	///�û�ǿ����־
	TThostFtdcBoolType	UserForceClose;
	///�������
	TThostFtdcErrorIDType	ErrorID;
	///������Ϣ
	TThostFtdcErrorMsgType	ErrorMsg;
	///��������־
	TThostFtdcBoolType	IsSwapOrder;
	///����������
	TThostFtdcExchangeIDType	ExchangeID;
	///Ͷ�ʵ�Ԫ����
	TThostFtdcInvestUnitIDType	InvestUnitID;
	///�ʽ��˺�
	TThostFtdcAccountIDType	AccountID;
	///���ִ���
	TThostFtdcCurrencyIDType	CurrencyID;
	///���ױ���
	TThostFtdcClientIDType	ClientID;
	///��������Ч�ֶ�
	TThostFtdcOldIPAddressType	reserve1;
	///Mac��ַ
	TThostFtdcMacAddressType	MacAddress;
	///��ϱ��
	TThostFtdcTradeIDType	ComTradeID;
	///IP��ַ
	TThostFtdcIPAddressType	IPAddress;
};

///��ѯ���󱨵�����
struct CThostFtdcErrorConditionalOrderField
{
	///���͹�˾����
	TThostFtdcBrokerIDType	BrokerID;
	///Ͷ���ߴ���
	TThostFtdcInvestorIDType	InvestorID;
	///��Լ����
	TThostFtdcInstrumentIDType	InstrumentID;
	///��������
	TThostFtdcOrderRefType	OrderRef;
	///�û�����
	TThostFtdcUserIDType	UserID;
	///�����۸�����
	TThostFtdcOrderPriceTypeType	OrderPriceType;
	///��������
	TThostFtdcDirectionType	Direction;
	///��Ͽ�ƽ��־
	TThostFtdcCombOffsetFlagType	CombOffsetFlag;
	///���Ͷ���ױ���־
	TThostFtdcCombHedgeFlagType	CombHedgeFlag;
	///�۸�
	TThostFtdcPriceType	LimitPrice;
	///����
	TThostFtdcVolumeType	VolumeTotalOriginal;
	///��Ч������
	TThostFtdcTimeConditionType	TimeCondition;
	///GTD����
	TThostFtdcDateType	GTDDate;
	///�ɽ�������
	TThostFtdcVolumeConditionType	VolumeCondition;
	///��С�ɽ���
	TThostFtdcVolumeType	MinVolume;
	///��������
	TThostFtdcContingentConditionType	ContingentCondition;
	///ֹ���
	TThostFtdcPriceType	StopPrice;
	///ǿƽԭ��
	TThostFtdcForceCloseReasonType	ForceCloseReason;
	///�Զ������־
	TThostFtdcBoolType	IsAutoSuspend;
	///ҵ��Ԫ
	TThostFtdcBusinessUnitType	BusinessUnit;
	///������
	TThostFtdcRequestIDType	RequestID;
	///���ر������
	TThostFtdcOrderLocalIDType	OrderLocalID;
	///����������
	TThostFtdcExchangeIDType	ExchangeID;
	///��Ա����
	TThostFtdcParticipantIDType	ParticipantID;
	///�ͻ�����
	TThostFtdcClientIDType	ClientID;
	///��Լ�ڽ������Ĵ���
	TThostFtdcExchangeInstIDType	ExchangeInstID;
	///����������Ա����
	TThostFtdcTraderIDType	TraderID;
	///��װ���
	TThostFtdcInstallIDType	InstallID;
	///�����ύ״̬
	TThostFtdcOrderSubmitStatusType	OrderSubmitStatus;
	///������ʾ���
	TThostFtdcSequenceNoType	NotifySequence;
	///������
	TThostFtdcDateType	TradingDay;
	///������
	TThostFtdcSettlementIDType	SettlementID;
	///�������
	TThostFtdcOrderSysIDType	OrderSysID;
	///������Դ
	TThostFtdcOrderSourceType	OrderSource;
	///����״̬
	TThostFtdcOrderStatusType	OrderStatus;
	///��������
	TThostFtdcOrderTypeType	OrderType;
	///��ɽ�����
	TThostFtdcVolumeType	VolumeTraded;
	///ʣ������
	TThostFtdcVolumeType	VolumeTotal;
	///��������
	TThostFtdcDateType	InsertDate;
	///ί��ʱ��
	TThostFtdcTimeType	InsertTime;
	///����ʱ��
	TThostFtdcTimeType	ActiveTime;
	///����ʱ��
	TThostFtdcTimeType	SuspendTime;
	///����޸�ʱ��
	TThostFtdcTimeType	UpdateTime;
	///����ʱ��
	TThostFtdcTimeType	CancelTime;
	///����޸Ľ���������Ա����
	TThostFtdcTraderIDType	ActiveTraderID;
	///�����Ա���
	TThostFtdcParticipantIDType	ClearingPartID;
	///���
	TThostFtdcSequenceNoType	SequenceNo;
	///ǰ�ñ��
	TThostFtdcFrontIDType	FrontID;
	///�Ự���
	TThostFtdcSessionIDType	SessionID;
	///�û��˲�Ʒ��Ϣ
	TThostFtdcProductInfoType	UserProductInfo;
	///״̬��Ϣ
	TThostFtdcErrorMsgType	StatusMsg;
	///�û�ǿ����־
	TThostFtdcBoolType	UserForceClose;
	///�����û�����
	TThostFtdcUserIDType	ActiveUserID;
	///���͹�˾�������
	TThostFtdcSequenceNoType	BrokerOrderSeq;
	///��ر���
	TThostFtdcOrderSysIDType	RelativeOrderSysID;
	///֣�����ɽ�����
	TThostFtdcVolumeType	ZCETotalTradedVolume;
	///�������
	TThostFtdcErrorIDType	ErrorID;
	///������Ϣ
	TThostFtdcErrorMsgType	ErrorMsg;
	///��������־
	TThostFtdcBoolType	IsSwapOrder;
	///Ӫҵ�����
	TThostFtdcBranchIDType	BranchID;
	///Ͷ�ʵ�Ԫ����
	TThostFtdcInvestUnitIDType	InvestUnitID;
	///�ʽ��˺�
	TThostFtdcAccountIDType	AccountID;
	///���ִ���
	TThostFtdcCurrencyIDType	CurrencyID;
	///��������Ч�ֶ�
	TThostFtdcOldIPAddressType	reserve1;
	///Mac��ַ
	TThostFtdcMacAddressType	MacAddress;
	///��ϱ��
	TThostFtdcTradeIDType	ComTradeID;
	///����������
	TThostFtdcOwnerTypeType	OwnerType;
	///��½PBU
	TThostFtdcTraderIDType	LoginPBU;
	///IP��ַ
	TThostFtdcIPAddressType	IPAddress;
};

///��ѯ���󱨵�����
struct CThostFtdcQryErrOrderActionField
{
	///���͹�˾����
	TThostFtdcBrokerIDType	BrokerID;
	///Ͷ���ߴ���
	TThostFtdcInvestorIDType	InvestorID;
};

///���󱨵�����
struct CThostFtdcErrOrderActionField
{
	///���͹�˾����
	TThostFtdcBrokerIDType	BrokerID;
	///Ͷ���ߴ���
	TThostFtdcInvestorIDType	InvestorID;
	///������������
	TThostFtdcOrderActionRefType	OrderActionRef;
	///��������
	TThostFtdcOrderRefType	OrderRef;
	///������
	TThostFtdcRequestIDType	RequestID;
	///ǰ�ñ��
	TThostFtdcFrontIDType	FrontID;
	///�Ự���
	TThostFtdcSessionIDType	SessionID;
	///����������
	TThostFtdcExchangeIDType	ExchangeID;
	///�������
	TThostFtdcOrderSysIDType	OrderSysID;
	///������־
	TThostFtdcActionFlagType	ActionFlag;
	///�۸�
	TThostFtdcPriceType	LimitPrice;
	///�����仯
	TThostFtdcVolumeType	VolumeChange;
	///��������
	TThostFtdcDateType	ActionDate;
	///����ʱ��
	TThostFtdcTimeType	ActionTime;
	///����������Ա����
	TThostFtdcTraderIDType	TraderID;
	///��װ���
	TThostFtdcInstallIDType	InstallID;
	///���ر������
	TThostFtdcOrderLocalIDType	OrderLocalID;
	///�������ر��
	TThostFtdcOrderLocalIDType	ActionLocalID;
	///��Ա����
	TThostFtdcParticipantIDType	ParticipantID;
	///�ͻ�����
	TThostFtdcClientIDType	ClientID;
	///ҵ��Ԫ
	TThostFtdcBusinessUnitType	BusinessUnit;
	///��������״̬
	TThostFtdcOrderActionStatusType	OrderActionStatus;
	///�û�����
	TThostFtdcUserIDType	UserID;
	///״̬��Ϣ
	TThostFtdcErrorMsgType	StatusMsg;
	///��Լ����
	TThostFtdcInstrumentIDType	InstrumentID;
	///Ӫҵ�����
	TThostFtdcBranchIDType	BranchID;
	///Ͷ�ʵ�Ԫ����
	TThostFtdcInvestUnitIDType	InvestUnitID;
	///��������Ч�ֶ�
	TThostFtdcOldIPAddressType	reserve1;
	///Mac��ַ
	TThostFtdcMacAddressType	MacAddress;
	///�������
	TThostFtdcErrorIDType	ErrorID;
	///������Ϣ
	TThostFtdcErrorMsgType	ErrorMsg;
	///����������
	TThostFtdcOwnerTypeType	OwnerType;
	///IP��ַ
	TThostFtdcIPAddressType	IPAddress;
};

///��ѯ������״̬
struct CThostFtdcQryExchangeSequenceField
{
	///����������
	TThostFtdcExchangeIDType	ExchangeID;
};

///������״̬
struct CThostFtdcExchangeSequenceField
{
	///����������
	TThostFtdcExchangeIDType	ExchangeID;
	///���
	TThostFtdcSequenceNoType	SequenceNo;
	///��Լ����״̬
	TThostFtdcInstrumentStatusType	MarketStatus;
};

///���ݼ۸��ѯ��󱨵�����
struct CThostFtdcQueryMaxOrderVolumeWithPriceField
{
	///���͹�˾����
	TThostFtdcBrokerIDType	BrokerID;
	///Ͷ���ߴ���
	TThostFtdcInvestorIDType	InvestorID;
	///��Լ����
	TThostFtdcInstrumentIDType	InstrumentID;
	///��������
	TThostFtdcDirectionType	Direction;
	///��ƽ��־
	TThostFtdcOffsetFlagType	OffsetFlag;
	///Ͷ���ױ���־
	TThostFtdcHedgeFlagType	HedgeFlag;
	///�������������
	TThostFtdcVolumeType	MaxVolume;
	///�����۸�
	TThostFtdcPriceType	Price;
	///����������
	TThostFtdcExchangeIDType	ExchangeID;
	///Ͷ�ʵ�Ԫ����
	TThostFtdcInvestUnitIDType	InvestUnitID;
};

///��ѯ���͹�˾���ײ���
struct CThostFtdcQryBrokerTradingParamsField
{
	///���͹�˾����
	TThostFtdcBrokerIDType	BrokerID;
	///Ͷ���ߴ���
	TThostFtdcInvestorIDType	InvestorID;
	///���ִ���
	TThostFtdcCurrencyIDType	CurrencyID;
	///Ͷ�����ʺ�
	TThostFtdcAccountIDType	AccountID;
};

///���͹�˾���ײ���
struct CThostFtdcBrokerTradingParamsField
{
	///���͹�˾����
	TThostFtdcBrokerIDType	BrokerID;
	///Ͷ���ߴ���
	TThostFtdcInvestorIDType	InvestorID;
	///��֤��۸�����
	TThostFtdcMarginPriceTypeType	MarginPriceType;
	///ӯ���㷨
	TThostFtdcAlgorithmType	Algorithm;
	///�����Ƿ����ƽ��ӯ��
	TThostFtdcIncludeCloseProfitType	AvailIncludeCloseProfit;
	///���ִ���
	TThostFtdcCurrencyIDType	CurrencyID;
	///��ȨȨ����۸�����
	TThostFtdcOptionRoyaltyPriceTypeType	OptionRoyaltyPriceType;
	///Ͷ�����ʺ�
	TThostFtdcAccountIDType	AccountID;
};

///��ѯ���͹�˾�����㷨
struct CThostFtdcQryBrokerTradingAlgosField
{
	///���͹�˾����
	TThostFtdcBrokerIDType	BrokerID;
	///����������
	TThostFtdcExchangeIDType	ExchangeID;
	///��Լ����
	TThostFtdcInstrumentIDType	InstrumentID;
};

///���͹�˾�����㷨
struct CThostFtdcBrokerTradingAlgosField
{
	///���͹�˾����
	TThostFtdcBrokerIDType	BrokerID;
	///����������
	TThostFtdcExchangeIDType	ExchangeID;
	///��Լ����
	TThostFtdcInstrumentIDType	InstrumentID;
	///�ֲִ����㷨���
	TThostFtdcHandlePositionAlgoIDType	HandlePositionAlgoID;
	///Ѱ�ұ�֤�����㷨���
	TThostFtdcFindMarginRateAlgoIDType	FindMarginRateAlgoID;
	///�ʽ����㷨���
	TThostFtdcHandleTradingAccountAlgoIDType	HandleTradingAccountAlgoID;
};

///��ѯ���͹�˾�ʽ�
struct CThostFtdcQueryBrokerDepositField
{
	///���͹�˾����
	TThostFtdcBrokerIDType	BrokerID;
	///����������
	TThostFtdcExchangeIDType	ExchangeID;
};

///���͹�˾�ʽ�
struct CThostFtdcBrokerDepositField
{
	///��������
	TThostFtdcTradeDateType	TradingDay;
	///���͹�˾����
	TThostFtdcBrokerIDType	BrokerID;
	///��Ա����
	TThostFtdcParticipantIDType	ParticipantID;
	///����������
	TThostFtdcExchangeIDType	ExchangeID;
	///�ϴν���׼����
	TThostFtdcMoneyType	PreBalance;
	///��ǰ��֤���ܶ�
	TThostFtdcMoneyType	CurrMargin;
	///ƽ��ӯ��
	TThostFtdcMoneyType	CloseProfit;
	///�ڻ�����׼����
	TThostFtdcMoneyType	Balance;
	///�����
	TThostFtdcMoneyType	Deposit;
	///������
	TThostFtdcMoneyType	Withdraw;
	///�����ʽ�
	TThostFtdcMoneyType	Available;
	///����׼����
	TThostFtdcMoneyType	Reserve;
	///����ı�֤��
	TThostFtdcMoneyType	FrozenMargin;
};

///��ѯ��֤����ϵͳ���͹�˾��Կ
struct CThostFtdcQryCFMMCBrokerKeyField
{
	///���͹�˾����
	TThostFtdcBrokerIDType	BrokerID;
};

///��֤����ϵͳ���͹�˾��Կ
struct CThostFtdcCFMMCBrokerKeyField
{
	///���͹�˾����
	TThostFtdcBrokerIDType	BrokerID;
	///���͹�˾ͳһ����
	TThostFtdcParticipantIDType	ParticipantID;
	///��Կ��������
	TThostFtdcDateType	CreateDate;
	///��Կ����ʱ��
	TThostFtdcTimeType	CreateTime;
	///��Կ���
	TThostFtdcSequenceNoType	KeyID;
	///��̬��Կ
	TThostFtdcCFMMCKeyType	CurrentKey;
	///��̬��Կ����
	TThostFtdcCFMMCKeyKindType	KeyKind;
};

///��֤����ϵͳ���͹�˾�ʽ��˻���Կ
struct CThostFtdcCFMMCTradingAccountKeyField
{
	///���͹�˾����
	TThostFtdcBrokerIDType	BrokerID;
	///���͹�˾ͳһ����
	TThostFtdcParticipantIDType	ParticipantID;
	///Ͷ�����ʺ�
	TThostFtdcAccountIDType	AccountID;
	///��Կ���
	TThostFtdcSequenceNoType	KeyID;
	///��̬��Կ
	TThostFtdcCFMMCKeyType	CurrentKey;
};

///�����ѯ��֤����ϵͳ���͹�˾�ʽ��˻���Կ
struct CThostFtdcQryCFMMCTradingAccountKeyField
{
	///���͹�˾����
	TThostFtdcBrokerIDType	BrokerID;
	///Ͷ���ߴ���
	TThostFtdcInvestorIDType	InvestorID;
};

///�û���̬���Ʋ���
struct CThostFtdcBrokerUserOTPParamField
{
	///���͹�˾����
	TThostFtdcBrokerIDType	BrokerID;
	///�û�����
	TThostFtdcUserIDType	UserID;
	///��̬�����ṩ��
	TThostFtdcOTPVendorsIDType	OTPVendorsID;
	///��̬�������к�
	TThostFtdcSerialNumberType	SerialNumber;
	///������Կ
	TThostFtdcAuthKeyType	AuthKey;
	///Ư��ֵ
	TThostFtdcLastDriftType	LastDrift;
	///�ɹ�ֵ
	TThostFtdcLastSuccessType	LastSuccess;
	///��̬��������
	TThostFtdcOTPTypeType	OTPType;
};

///�ֹ�ͬ���û���̬����
struct CThostFtdcManualSyncBrokerUserOTPField
{
	///���͹�˾����
	TThostFtdcBrokerIDType	BrokerID;
	///�û�����
	TThostFtdcUserIDType	UserID;
	///��̬��������
	TThostFtdcOTPTypeType	OTPType;
	///��һ����̬����
	TThostFtdcPasswordType	FirstOTP;
	///�ڶ�����̬����
	TThostFtdcPasswordType	SecondOTP;
};

///Ͷ������������ģ��
struct CThostFtdcCommRateModelField
{
	///���͹�˾����
	TThostFtdcBrokerIDType	BrokerID;
	///��������ģ�����
	TThostFtdcInvestorIDType	CommModelID;
	///ģ������
	TThostFtdcCommModelNameType	CommModelName;
};

///�����ѯͶ������������ģ��
struct CThostFtdcQryCommRateModelField
{
	///���͹�˾����
	TThostFtdcBrokerIDType	BrokerID;
	///��������ģ�����
	TThostFtdcInvestorIDType	CommModelID;
};

///Ͷ���߱�֤����ģ��
struct CThostFtdcMarginModelField
{
	///���͹�˾����
	TThostFtdcBrokerIDType	BrokerID;
	///��֤����ģ�����
	TThostFtdcInvestorIDType	MarginModelID;
	///ģ������
	TThostFtdcCommModelNameType	MarginModelName;
};

///�����ѯͶ���߱�֤����ģ��
struct CThostFtdcQryMarginModelField
{
	///���͹�˾����
	TThostFtdcBrokerIDType	BrokerID;
	///��֤����ģ�����
	TThostFtdcInvestorIDType	MarginModelID;
};

///�ֵ��۵���Ϣ
struct CThostFtdcEWarrantOffsetField
{
	///��������
	TThostFtdcTradeDateType	TradingDay;
	///���͹�˾����
	TThostFtdcBrokerIDType	BrokerID;
	///Ͷ���ߴ���
	TThostFtdcInvestorIDType	InvestorID;
	///����������
	TThostFtdcExchangeIDType	ExchangeID;
	///��Լ����
	TThostFtdcInstrumentIDType	InstrumentID;
	///��������
	TThostFtdcDirectionType	Direction;
	///Ͷ���ױ���־
	TThostFtdcHedgeFlagType	HedgeFlag;
	///����
	TThostFtdcVolumeType	Volume;
	///Ͷ�ʵ�Ԫ����
	TThostFtdcInvestUnitIDType	InvestUnitID;
};

///��ѯ�ֵ��۵���Ϣ
struct CThostFtdcQryEWarrantOffsetField
{
	///���͹�˾����
	TThostFtdcBrokerIDType	BrokerID;
	///Ͷ���ߴ���
	TThostFtdcInvestorIDType	InvestorID;
	///����������
	TThostFtdcExchangeIDType	ExchangeID;
	///��Լ����
	TThostFtdcInstrumentIDType	InstrumentID;
	///Ͷ�ʵ�Ԫ����
	TThostFtdcInvestUnitIDType	InvestUnitID;
};

///��ѯͶ����Ʒ��/��Ʒ�ֱ�֤��
struct CThostFtdcQryInvestorProductGroupMarginField
{
	///���͹�˾����
	TThostFtdcBrokerIDType	BrokerID;
	///Ͷ���ߴ���
	TThostFtdcInvestorIDType	InvestorID;
	///Ʒ��/��Ʒ�ֱ�ʾ
	TThostFtdcInstrumentIDType	ProductGroupID;
	///Ͷ���ױ���־
	TThostFtdcHedgeFlagType	HedgeFlag;
	///����������
	TThostFtdcExchangeIDType	ExchangeID;
	///Ͷ�ʵ�Ԫ����
	TThostFtdcInvestUnitIDType	InvestUnitID;
};

///Ͷ����Ʒ��/��Ʒ�ֱ�֤��
struct CThostFtdcInvestorProductGroupMarginField
{
	///Ʒ��/��Ʒ�ֱ�ʾ
	TThostFtdcInstrumentIDType	ProductGroupID;
	///���͹�˾����
	TThostFtdcBrokerIDType	BrokerID;
	///Ͷ���ߴ���
	TThostFtdcInvestorIDType	InvestorID;
	///������
	TThostFtdcDateType	TradingDay;
	///������
	TThostFtdcSettlementIDType	SettlementID;
	///����ı�֤��
	TThostFtdcMoneyType	FrozenMargin;
	///��ͷ����ı�֤��
	TThostFtdcMoneyType	LongFrozenMargin;
	///��ͷ����ı�֤��
	TThostFtdcMoneyType	ShortFrozenMargin;
	///ռ�õı�֤��
	TThostFtdcMoneyType	UseMargin;
	///��ͷ��֤��
	TThostFtdcMoneyType	LongUseMargin;
	///��ͷ��֤��
	TThostFtdcMoneyType	ShortUseMargin;
	///��������֤��
	TThostFtdcMoneyType	ExchMargin;
	///��������ͷ��֤��
	TThostFtdcMoneyType	LongExchMargin;
	///��������ͷ��֤��
	TThostFtdcMoneyType	ShortExchMargin;
	///ƽ��ӯ��
	TThostFtdcMoneyType	CloseProfit;
	///�����������
	TThostFtdcMoneyType	FrozenCommission;
	///������
	TThostFtdcMoneyType	Commission;
	///������ʽ�
	TThostFtdcMoneyType	FrozenCash;
	///�ʽ���
	TThostFtdcMoneyType	CashIn;
	///�ֲ�ӯ��
	TThostFtdcMoneyType	PositionProfit;
	///�۵��ܽ��
	TThostFtdcMoneyType	OffsetAmount;
	///��ͷ�۵��ܽ��
	TThostFtdcMoneyType	LongOffsetAmount;
	///��ͷ�۵��ܽ��
	TThostFtdcMoneyType	ShortOffsetAmount;
	///�������۵��ܽ��
	TThostFtdcMoneyType	ExchOffsetAmount;
	///��������ͷ�۵��ܽ��
	TThostFtdcMoneyType	LongExchOffsetAmount;
	///��������ͷ�۵��ܽ��
	TThostFtdcMoneyType	ShortExchOffsetAmount;
	///Ͷ���ױ���־
	TThostFtdcHedgeFlagType	HedgeFlag;
	///����������
	TThostFtdcExchangeIDType	ExchangeID;
	///Ͷ�ʵ�Ԫ����
	TThostFtdcInvestUnitIDType	InvestUnitID;
};

///��ѯ��������û�����
struct CThostFtdcQueryCFMMCTradingAccountTokenField
{
	///���͹�˾����
	TThostFtdcBrokerIDType	BrokerID;
	///Ͷ���ߴ���
	TThostFtdcInvestorIDType	InvestorID;
	///Ͷ�ʵ�Ԫ����
	TThostFtdcInvestUnitIDType	InvestUnitID;
};

///��������û�����
struct CThostFtdcCFMMCTradingAccountTokenField
{
	///���͹�˾����
	TThostFtdcBrokerIDType	BrokerID;
	///���͹�˾ͳһ����
	TThostFtdcParticipantIDType	ParticipantID;
	///Ͷ�����ʺ�
	TThostFtdcAccountIDType	AccountID;
	///��Կ���
	TThostFtdcSequenceNoType	KeyID;
	///��̬����
	TThostFtdcCFMMCTokenType	Token;
};

///Ͷ����ָ��Ȩ��
struct CThostFtdcInstructionRightField
{
	///���͹�˾����
	TThostFtdcBrokerIDType	BrokerID;
	///����������
	TThostFtdcExchangeIDType	ExchangeID;
	///Ͷ���ߴ���
	TThostFtdcInvestorIDType	InvestorID;
	///ָ��Ȩ������
	TThostFtdcInstructionRightTypeType	InstructionRight;
	///�Ƿ��ֹ
	TThostFtdcBoolType	IsForbidden;
};

///��ѯ��Ʒ��
struct CThostFtdcQryProductGroupField
{
	///��Ʒ����
	TThostFtdcInstrumentIDType	ProductID;
	///����������
	TThostFtdcExchangeIDType	ExchangeID;
};

///Ͷ����Ʒ��/��Ʒ�ֱ�֤���Ʒ��
struct CThostFtdcProductGroupField
{
	///��Ʒ����
	TThostFtdcInstrumentIDType	ProductID;
	///����������
	TThostFtdcExchangeIDType	ExchangeID;
	///��Ʒ�����
	TThostFtdcInstrumentIDType	ProductGroupID;
};

///����������
struct CThostFtdcBulletinField
{
	///����������
	TThostFtdcExchangeIDType	ExchangeID;
	///������
	TThostFtdcDateType	TradingDay;
	///������
	TThostFtdcBulletinIDType	BulletinID;
	///���к�
	TThostFtdcSequenceNoType	SequenceNo;
	///��������
	TThostFtdcNewsTypeType	NewsType;
	///�����̶�
	TThostFtdcNewsUrgencyType	NewsUrgency;
	///����ʱ��
	TThostFtdcTimeType	SendTime;
	///��ϢժҪ
	TThostFtdcAbstractType	Abstract;
	///��Ϣ��Դ
	TThostFtdcComeFromType	ComeFrom;
	///��Ϣ����
	TThostFtdcContentType	Content;
	///WEB��ַ
	TThostFtdcURLLinkType	URLLink;
	///�г�����
	TThostFtdcMarketIDType	MarketID;
};

///��ѯ����������
struct CThostFtdcQryBulletinField
{
	///����������
	TThostFtdcExchangeIDType	ExchangeID;
	///������
	TThostFtdcBulletinIDType	BulletinID;
	///���к�
	TThostFtdcSequenceNoType	SequenceNo;
	///��������
	TThostFtdcNewsTypeType	NewsType;
	///�����̶�
	TThostFtdcNewsUrgencyType	NewsUrgency;
};

///ת�ʿ�������
struct CThostFtdcReqOpenAccountField
{
	///ҵ������
	TThostFtdcTradeCodeType	TradeCode;
	///���д���
	TThostFtdcBankIDType	BankID;
	///���з�֧��������
	TThostFtdcBankBrchIDType	BankBranchID;
	///���̴���
	TThostFtdcBrokerIDType	BrokerID;
	///���̷�֧��������
	TThostFtdcFutureBranchIDType	BrokerBranchID;
	///��������
	TThostFtdcTradeDateType	TradeDate;
	///����ʱ��
	TThostFtdcTradeTimeType	TradeTime;
	///������ˮ��
	TThostFtdcBankSerialType	BankSerial;
	///����ϵͳ���� 
	TThostFtdcTradeDateType	TradingDay;
	///����ƽ̨��Ϣ��ˮ��
	TThostFtdcSerialType	PlateSerial;
	///����Ƭ��־
	TThostFtdcLastFragmentType	LastFragment;
	///�Ự��
	TThostFtdcSessionIDType	SessionID;
	///�ͻ�����
	TThostFtdcIndividualNameType	CustomerName;
	///֤������
	TThostFtdcIdCardTypeType	IdCardType;
	///֤������
	TThostFtdcIdentifiedCardNoType	IdentifiedCardNo;
	///�Ա�
	TThostFtdcGenderType	Gender;
	///���Ҵ���
	TThostFtdcCountryCodeType	CountryCode;
	///�ͻ�����
	TThostFtdcCustTypeType	CustType;
	///��ַ
	TThostFtdcAddressType	Address;
	///�ʱ�
	TThostFtdcZipCodeType	ZipCode;
	///�绰����
	TThostFtdcTelephoneType	Telephone;
	///�ֻ�
	TThostFtdcMobilePhoneType	MobilePhone;
	///����
	TThostFtdcFaxType	Fax;
	///�����ʼ�
	TThostFtdcEMailType	EMail;
	///�ʽ��˻�״̬
	TThostFtdcMoneyAccountStatusType	MoneyAccountStatus;
	///�����ʺ�
	TThostFtdcBankAccountType	BankAccount;
	///��������
	TThostFtdcPasswordType	BankPassWord;
	///Ͷ�����ʺ�
	TThostFtdcAccountIDType	AccountID;
	///�ڻ�����
	TThostFtdcPasswordType	Password;
	///��װ���
	TThostFtdcInstallIDType	InstallID;
	///��֤�ͻ�֤�������־
	TThostFtdcYesNoIndicatorType	VerifyCertNoFlag;
	///���ִ���
	TThostFtdcCurrencyIDType	CurrencyID;
	///�㳮��־
	TThostFtdcCashExchangeCodeType	CashExchangeCode;
	///ժҪ
	TThostFtdcDigestType	Digest;
	///�����ʺ�����
	TThostFtdcBankAccTypeType	BankAccType;
	///������־
	TThostFtdcDeviceIDType	DeviceID;
	///�ڻ���λ�ʺ�����
	TThostFtdcBankAccTypeType	BankSecuAccType;
	///�ڻ���˾���б���
	TThostFtdcBankCodingForFutureType	BrokerIDByBank;
	///�ڻ���λ�ʺ�
	TThostFtdcBankAccountType	BankSecuAcc;
	///���������־
	TThostFtdcPwdFlagType	BankPwdFlag;
	///�ڻ��ʽ�����˶Ա�־
	TThostFtdcPwdFlagType	SecuPwdFlag;
	///���׹�Ա
	TThostFtdcOperNoType	OperNo;
	///����ID
	TThostFtdcTIDType	TID;
	///�û���ʶ
	TThostFtdcUserIDType	UserID;
	///֤ȯ�ʽ��ճ����
	TThostFtdcTradeAmountType	SecDaBeBl;
	///����ת��ͨ��
	TThostFtdcBankChannelType	BankChal;
};

///ת����������
struct CThostFtdcReqCancelAccountField
{
	///ҵ������
	TThostFtdcTradeCodeType	TradeCode;
	///���д���
	TThostFtdcBankIDType	BankID;
	///���з�֧��������
	TThostFtdcBankBrchIDType	BankBranchID;
	///���̴���
	TThostFtdcBrokerIDType	BrokerID;
	///���̷�֧��������
	TThostFtdcFutureBranchIDType	BrokerBranchID;
	///��������
	TThostFtdcTradeDateType	TradeDate;
	///����ʱ��
	TThostFtdcTradeTimeType	TradeTime;
	///������ˮ��
	TThostFtdcBankSerialType	BankSerial;
	///����ϵͳ���� 
	TThostFtdcTradeDateType	TradingDay;
	///����ƽ̨��Ϣ��ˮ��
	TThostFtdcSerialType	PlateSerial;
	///����Ƭ��־
	TThostFtdcLastFragmentType	LastFragment;
	///�Ự��
	TThostFtdcSessionIDType	SessionID;
	///�ͻ�����
	TThostFtdcIndividualNameType	CustomerName;
	///֤������
	TThostFtdcIdCardTypeType	IdCardType;
	///֤������
	TThostFtdcIdentifiedCardNoType	IdentifiedCardNo;
	///�Ա�
	TThostFtdcGenderType	Gender;
	///���Ҵ���
	TThostFtdcCountryCodeType	CountryCode;
	///�ͻ�����
	TThostFtdcCustTypeType	CustType;
	///��ַ
	TThostFtdcAddressType	Address;
	///�ʱ�
	TThostFtdcZipCodeType	ZipCode;
	///�绰����
	TThostFtdcTelephoneType	Telephone;
	///�ֻ�
	TThostFtdcMobilePhoneType	MobilePhone;
	///����
	TThostFtdcFaxType	Fax;
	///�����ʼ�
	TThostFtdcEMailType	EMail;
	///�ʽ��˻�״̬
	TThostFtdcMoneyAccountStatusType	MoneyAccountStatus;
	///�����ʺ�
	TThostFtdcBankAccountType	BankAccount;
	///��������
	TThostFtdcPasswordType	BankPassWord;
	///Ͷ�����ʺ�
	TThostFtdcAccountIDType	AccountID;
	///�ڻ�����
	TThostFtdcPasswordType	Password;
	///��װ���
	TThostFtdcInstallIDType	InstallID;
	///��֤�ͻ�֤�������־
	TThostFtdcYesNoIndicatorType	VerifyCertNoFlag;
	///���ִ���
	TThostFtdcCurrencyIDType	CurrencyID;
	///�㳮��־
	TThostFtdcCashExchangeCodeType	CashExchangeCode;
	///ժҪ
	TThostFtdcDigestType	Digest;
	///�����ʺ�����
	TThostFtdcBankAccTypeType	BankAccType;
	///������־
	TThostFtdcDeviceIDType	DeviceID;
	///�ڻ���λ�ʺ�����
	TThostFtdcBankAccTypeType	BankSecuAccType;
	///�ڻ���˾���б���
	TThostFtdcBankCodingForFutureType	BrokerIDByBank;
	///�ڻ���λ�ʺ�
	TThostFtdcBankAccountType	BankSecuAcc;
	///���������־
	TThostFtdcPwdFlagType	BankPwdFlag;
	///�ڻ��ʽ�����˶Ա�־
	TThostFtdcPwdFlagType	SecuPwdFlag;
	///���׹�Ա
	TThostFtdcOperNoType	OperNo;
	///����ID
	TThostFtdcTIDType	TID;
	///�û���ʶ
	TThostFtdcUserIDType	UserID;
	///֤ȯ�ʽ��ճ����
	TThostFtdcTradeAmountType	SecDaBeBl;
	///����ת��ͨ��
	TThostFtdcBankChannelType	BankChal;
};

///��������˻�����
struct CThostFtdcReqChangeAccountField
{
	///ҵ������
	TThostFtdcTradeCodeType	TradeCode;
	///���д���
	TThostFtdcBankIDType	BankID;
	///���з�֧��������
	TThostFtdcBankBrchIDType	BankBranchID;
	///���̴���
	TThostFtdcBrokerIDType	BrokerID;
	///���̷�֧��������
	TThostFtdcFutureBranchIDType	BrokerBranchID;
	///��������
	TThostFtdcTradeDateType	TradeDate;
	///����ʱ��
	TThostFtdcTradeTimeType	TradeTime;
	///������ˮ��
	TThostFtdcBankSerialType	BankSerial;
	///����ϵͳ���� 
	TThostFtdcTradeDateType	TradingDay;
	///����ƽ̨��Ϣ��ˮ��
	TThostFtdcSerialType	PlateSerial;
	///����Ƭ��־
	TThostFtdcLastFragmentType	LastFragment;
	///�Ự��
	TThostFtdcSessionIDType	SessionID;
	///�ͻ�����
	TThostFtdcIndividualNameType	CustomerName;
	///֤������
	TThostFtdcIdCardTypeType	IdCardType;
	///֤������
	TThostFtdcIdentifiedCardNoType	IdentifiedCardNo;
	///�Ա�
	TThostFtdcGenderType	Gender;
	///���Ҵ���
	TThostFtdcCountryCodeType	CountryCode;
	///�ͻ�����
	TThostFtdcCustTypeType	CustType;
	///��ַ
	TThostFtdcAddressType	Address;
	///�ʱ�
	TThostFtdcZipCodeType	ZipCode;
	///�绰����
	TThostFtdcTelephoneType	Telephone;
	///�ֻ�
	TThostFtdcMobilePhoneType	MobilePhone;
	///����
	TThostFtdcFaxType	Fax;
	///�����ʼ�
	TThostFtdcEMailType	EMail;
	///�ʽ��˻�״̬
	TThostFtdcMoneyAccountStatusType	MoneyAccountStatus;
	///�����ʺ�
	TThostFtdcBankAccountType	BankAccount;
	///��������
	TThostFtdcPasswordType	BankPassWord;
	///�������ʺ�
	TThostFtdcBankAccountType	NewBankAccount;
	///����������
	TThostFtdcPasswordType	NewBankPassWord;
	///Ͷ�����ʺ�
	TThostFtdcAccountIDType	AccountID;
	///�ڻ�����
	TThostFtdcPasswordType	Password;
	///�����ʺ�����
	TThostFtdcBankAccTypeType	BankAccType;
	///��װ���
	TThostFtdcInstallIDType	InstallID;
	///��֤�ͻ�֤�������־
	TThostFtdcYesNoIndicatorType	VerifyCertNoFlag;
	///���ִ���
	TThostFtdcCurrencyIDType	CurrencyID;
	///�ڻ���˾���б���
	TThostFtdcBankCodingForFutureType	BrokerIDByBank;
	///���������־
	TThostFtdcPwdFlagType	BankPwdFlag;
	///�ڻ��ʽ�����˶Ա�־
	TThostFtdcPwdFlagType	SecuPwdFlag;
	///����ID
	TThostFtdcTIDType	TID;
	///ժҪ
	TThostFtdcDigestType	Digest;
};

///ת������
struct CThostFtdcReqTransferField
{
	///ҵ������
	TThostFtdcTradeCodeType	TradeCode;
	///���д���
	TThostFtdcBankIDType	BankID;
	///���з�֧��������
	TThostFtdcBankBrchIDType	BankBranchID;
	///���̴���
	TThostFtdcBrokerIDType	BrokerID;
	///���̷�֧��������
	TThostFtdcFutureBranchIDType	BrokerBranchID;
	///��������
	TThostFtdcTradeDateType	TradeDate;
	///����ʱ��
	TThostFtdcTradeTimeType	TradeTime;
	///������ˮ��
	TThostFtdcBankSerialType	BankSerial;
	///����ϵͳ���� 
	TThostFtdcTradeDateType	TradingDay;
	///����ƽ̨��Ϣ��ˮ��
	TThostFtdcSerialType	PlateSerial;
	///����Ƭ��־
	TThostFtdcLastFragmentType	LastFragment;
	///�Ự��
	TThostFtdcSessionIDType	SessionID;
	///�ͻ�����
	TThostFtdcIndividualNameType	CustomerName;
	///֤������
	TThostFtdcIdCardTypeType	IdCardType;
	///֤������
	TThostFtdcIdentifiedCardNoType	IdentifiedCardNo;
	///�ͻ�����
	TThostFtdcCustTypeType	CustType;
	///�����ʺ�
	TThostFtdcBankAccountType	BankAccount;
	///��������
	TThostFtdcPasswordType	BankPassWord;
	///Ͷ�����ʺ�
	TThostFtdcAccountIDType	AccountID;
	///�ڻ�����
	TThostFtdcPasswordType	Password;
	///��װ���
	TThostFtdcInstallIDType	InstallID;
	///�ڻ���˾��ˮ��
	TThostFtdcFutureSerialType	FutureSerial;
	///�û���ʶ
	TThostFtdcUserIDType	UserID;
	///��֤�ͻ�֤�������־
	TThostFtdcYesNoIndicatorType	VerifyCertNoFlag;
	///���ִ���
	TThostFtdcCurrencyIDType	CurrencyID;
	///ת�ʽ��
	TThostFtdcTradeAmountType	TradeAmount;
	///�ڻ���ȡ���
	TThostFtdcTradeAmountType	FutureFetchAmount;
	///����֧����־
	TThostFtdcFeePayFlagType	FeePayFlag;
	///Ӧ�տͻ�����
	TThostFtdcCustFeeType	CustFee;
	///Ӧ���ڻ���˾����
	TThostFtdcFutureFeeType	BrokerFee;
	///���ͷ������շ�����Ϣ
	TThostFtdcAddInfoType	Message;
	///ժҪ
	TThostFtdcDigestType	Digest;
	///�����ʺ�����
	TThostFtdcBankAccTypeType	BankAccType;
	///������־
	TThostFtdcDeviceIDType	DeviceID;
	///�ڻ���λ�ʺ�����
	TThostFtdcBankAccTypeType	BankSecuAccType;
	///�ڻ���˾���б���
	TThostFtdcBankCodingForFutureType	BrokerIDByBank;
	///�ڻ���λ�ʺ�
	TThostFtdcBankAccountType	BankSecuAcc;
	///���������־
	TThostFtdcPwdFlagType	BankPwdFlag;
	///�ڻ��ʽ�����˶Ա�־
	TThostFtdcPwdFlagType	SecuPwdFlag;
	///���׹�Ա
	TThostFtdcOperNoType	OperNo;
	///������
	TThostFtdcRequestIDType	RequestID;
	///����ID
	TThostFtdcTIDType	TID;
	///ת�˽���״̬
	TThostFtdcTransferStatusType	TransferStatus;
};

///���з��������ʽ�ת�ڻ���Ӧ
struct CThostFtdcRspTransferField
{
	///ҵ������
	TThostFtdcTradeCodeType	TradeCode;
	///���д���
	TThostFtdcBankIDType	BankID;
	///���з�֧��������
	TThostFtdcBankBrchIDType	BankBranchID;
	///���̴���
	TThostFtdcBrokerIDType	BrokerID;
	///���̷�֧��������
	TThostFtdcFutureBranchIDType	BrokerBranchID;
	///��������
	TThostFtdcTradeDateType	TradeDate;
	///����ʱ��
	TThostFtdcTradeTimeType	TradeTime;
	///������ˮ��
	TThostFtdcBankSerialType	BankSerial;
	///����ϵͳ���� 
	TThostFtdcTradeDateType	TradingDay;
	///����ƽ̨��Ϣ��ˮ��
	TThostFtdcSerialType	PlateSerial;
	///����Ƭ��־
	TThostFtdcLastFragmentType	LastFragment;
	///�Ự��
	TThostFtdcSessionIDType	SessionID;
	///�ͻ�����
	TThostFtdcIndividualNameType	CustomerName;
	///֤������
	TThostFtdcIdCardTypeType	IdCardType;
	///֤������
	TThostFtdcIdentifiedCardNoType	IdentifiedCardNo;
	///�ͻ�����
	TThostFtdcCustTypeType	CustType;
	///�����ʺ�
	TThostFtdcBankAccountType	BankAccount;
	///��������
	TThostFtdcPasswordType	BankPassWord;
	///Ͷ�����ʺ�
	TThostFtdcAccountIDType	AccountID;
	///�ڻ�����
	TThostFtdcPasswordType	Password;
	///��װ���
	TThostFtdcInstallIDType	InstallID;
	///�ڻ���˾��ˮ��
	TThostFtdcFutureSerialType	FutureSerial;
	///�û���ʶ
	TThostFtdcUserIDType	UserID;
	///��֤�ͻ�֤�������־
	TThostFtdcYesNoIndicatorType	VerifyCertNoFlag;
	///���ִ���
	TThostFtdcCurrencyIDType	CurrencyID;
	///ת�ʽ��
	TThostFtdcTradeAmountType	TradeAmount;
	///�ڻ���ȡ���
	TThostFtdcTradeAmountType	FutureFetchAmount;
	///����֧����־
	TThostFtdcFeePayFlagType	FeePayFlag;
	///Ӧ�տͻ�����
	TThostFtdcCustFeeType	CustFee;
	///Ӧ���ڻ���˾����
	TThostFtdcFutureFeeType	BrokerFee;
	///���ͷ������շ�����Ϣ
	TThostFtdcAddInfoType	Message;
	///ժҪ
	TThostFtdcDigestType	Digest;
	///�����ʺ�����
	TThostFtdcBankAccTypeType	BankAccType;
	///������־
	TThostFtdcDeviceIDType	DeviceID;
	///�ڻ���λ�ʺ�����
	TThostFtdcBankAccTypeType	BankSecuAccType;
	///�ڻ���˾���б���
	TThostFtdcBankCodingForFutureType	BrokerIDByBank;
	///�ڻ���λ�ʺ�
	TThostFtdcBankAccountType	BankSecuAcc;
	///���������־
	TThostFtdcPwdFlagType	BankPwdFlag;
	///�ڻ��ʽ�����˶Ա�־
	TThostFtdcPwdFlagType	SecuPwdFlag;
	///���׹�Ա
	TThostFtdcOperNoType	OperNo;
	///������
	TThostFtdcRequestIDType	RequestID;
	///����ID
	TThostFtdcTIDType	TID;
	///ת�˽���״̬
	TThostFtdcTransferStatusType	TransferStatus;
	///�������
	TThostFtdcErrorIDType	ErrorID;
	///������Ϣ
	TThostFtdcErrorMsgType	ErrorMsg;
};

///��������
struct CThostFtdcReqRepealField
{
	///����ʱ����
	TThostFtdcRepealTimeIntervalType	RepealTimeInterval;
	///�Ѿ���������
	TThostFtdcRepealedTimesType	RepealedTimes;
	///���г�����־
	TThostFtdcBankRepealFlagType	BankRepealFlag;
	///���̳�����־
	TThostFtdcBrokerRepealFlagType	BrokerRepealFlag;
	///������ƽ̨��ˮ��
	TThostFtdcPlateSerialType	PlateRepealSerial;
	///������������ˮ��
	TThostFtdcBankSerialType	BankRepealSerial;
	///�������ڻ���ˮ��
	TThostFtdcFutureSerialType	FutureRepealSerial;
	///ҵ������
	TThostFtdcTradeCodeType	TradeCode;
	///���д���
	TThostFtdcBankIDType	BankID;
	///���з�֧��������
	TThostFtdcBankBrchIDType	BankBranchID;
	///���̴���
	TThostFtdcBrokerIDType	BrokerID;
	///���̷�֧��������
	TThostFtdcFutureBranchIDType	BrokerBranchID;
	///��������
	TThostFtdcTradeDateType	TradeDate;
	///����ʱ��
	TThostFtdcTradeTimeType	TradeTime;
	///������ˮ��
	TThostFtdcBankSerialType	BankSerial;
	///����ϵͳ���� 
	TThostFtdcTradeDateType	TradingDay;
	///����ƽ̨��Ϣ��ˮ��
	TThostFtdcSerialType	PlateSerial;
	///����Ƭ��־
	TThostFtdcLastFragmentType	LastFragment;
	///�Ự��
	TThostFtdcSessionIDType	SessionID;
	///�ͻ�����
	TThostFtdcIndividualNameType	CustomerName;
	///֤������
	TThostFtdcIdCardTypeType	IdCardType;
	///֤������
	TThostFtdcIdentifiedCardNoType	IdentifiedCardNo;
	///�ͻ�����
	TThostFtdcCustTypeType	CustType;
	///�����ʺ�
	TThostFtdcBankAccountType	BankAccount;
	///��������
	TThostFtdcPasswordType	BankPassWord;
	///Ͷ�����ʺ�
	TThostFtdcAccountIDType	AccountID;
	///�ڻ�����
	TThostFtdcPasswordType	Password;
	///��װ���
	TThostFtdcInstallIDType	InstallID;
	///�ڻ���˾��ˮ��
	TThostFtdcFutureSerialType	FutureSerial;
	///�û���ʶ
	TThostFtdcUserIDType	UserID;
	///��֤�ͻ�֤�������־
	TThostFtdcYesNoIndicatorType	VerifyCertNoFlag;
	///���ִ���
	TThostFtdcCurrencyIDType	CurrencyID;
	///ת�ʽ��
	TThostFtdcTradeAmountType	TradeAmount;
	///�ڻ���ȡ���
	TThostFtdcTradeAmountType	FutureFetchAmount;
	///����֧����־
	TThostFtdcFeePayFlagType	FeePayFlag;
	///Ӧ�տͻ�����
	TThostFtdcCustFeeType	CustFee;
	///Ӧ���ڻ���˾����
	TThostFtdcFutureFeeType	BrokerFee;
	///���ͷ������շ�����Ϣ
	TThostFtdcAddInfoType	Message;
	///ժҪ
	TThostFtdcDigestType	Digest;
	///�����ʺ�����
	TThostFtdcBankAccTypeType	BankAccType;
	///������־
	TThostFtdcDeviceIDType	DeviceID;
	///�ڻ���λ�ʺ�����
	TThostFtdcBankAccTypeType	BankSecuAccType;
	///�ڻ���˾���б���
	TThostFtdcBankCodingForFutureType	BrokerIDByBank;
	///�ڻ���λ�ʺ�
	TThostFtdcBankAccountType	BankSecuAcc;
	///���������־
	TThostFtdcPwdFlagType	BankPwdFlag;
	///�ڻ��ʽ�����˶Ա�־
	TThostFtdcPwdFlagType	SecuPwdFlag;
	///���׹�Ա
	TThostFtdcOperNoType	OperNo;
	///������
	TThostFtdcRequestIDType	RequestID;
	///����ID
	TThostFtdcTIDType	TID;
	///ת�˽���״̬
	TThostFtdcTransferStatusType	TransferStatus;
};

///������Ӧ
struct CThostFtdcRspRepealField
{
	///����ʱ����
	TThostFtdcRepealTimeIntervalType	RepealTimeInterval;
	///�Ѿ���������
	TThostFtdcRepealedTimesType	RepealedTimes;
	///���г�����־
	TThostFtdcBankRepealFlagType	BankRepealFlag;
	///���̳�����־
	TThostFtdcBrokerRepealFlagType	BrokerRepealFlag;
	///������ƽ̨��ˮ��
	TThostFtdcPlateSerialType	PlateRepealSerial;
	///������������ˮ��
	TThostFtdcBankSerialType	BankRepealSerial;
	///�������ڻ���ˮ��
	TThostFtdcFutureSerialType	FutureRepealSerial;
	///ҵ������
	TThostFtdcTradeCodeType	TradeCode;
	///���д���
	TThostFtdcBankIDType	BankID;
	///���з�֧��������
	TThostFtdcBankBrchIDType	BankBranchID;
	///���̴���
	TThostFtdcBrokerIDType	BrokerID;
	///���̷�֧��������
	TThostFtdcFutureBranchIDType	BrokerBranchID;
	///��������
	TThostFtdcTradeDateType	TradeDate;
	///����ʱ��
	TThostFtdcTradeTimeType	TradeTime;
	///������ˮ��
	TThostFtdcBankSerialType	BankSerial;
	///����ϵͳ���� 
	TThostFtdcTradeDateType	TradingDay;
	///����ƽ̨��Ϣ��ˮ��
	TThostFtdcSerialType	PlateSerial;
	///����Ƭ��־
	TThostFtdcLastFragmentType	LastFragment;
	///�Ự��
	TThostFtdcSessionIDType	SessionID;
	///�ͻ�����
	TThostFtdcIndividualNameType	CustomerName;
	///֤������
	TThostFtdcIdCardTypeType	IdCardType;
	///֤������
	TThostFtdcIdentifiedCardNoType	IdentifiedCardNo;
	///�ͻ�����
	TThostFtdcCustTypeType	CustType;
	///�����ʺ�
	TThostFtdcBankAccountType	BankAccount;
	///��������
	TThostFtdcPasswordType	BankPassWord;
	///Ͷ�����ʺ�
	TThostFtdcAccountIDType	AccountID;
	///�ڻ�����
	TThostFtdcPasswordType	Password;
	///��װ���
	TThostFtdcInstallIDType	InstallID;
	///�ڻ���˾��ˮ��
	TThostFtdcFutureSerialType	FutureSerial;
	///�û���ʶ
	TThostFtdcUserIDType	UserID;
	///��֤�ͻ�֤�������־
	TThostFtdcYesNoIndicatorType	VerifyCertNoFlag;
	///���ִ���
	TThostFtdcCurrencyIDType	CurrencyID;
	///ת�ʽ��
	TThostFtdcTradeAmountType	TradeAmount;
	///�ڻ���ȡ���
	TThostFtdcTradeAmountType	FutureFetchAmount;
	///����֧����־
	TThostFtdcFeePayFlagType	FeePayFlag;
	///Ӧ�տͻ�����
	TThostFtdcCustFeeType	CustFee;
	///Ӧ���ڻ���˾����
	TThostFtdcFutureFeeType	BrokerFee;
	///���ͷ������շ�����Ϣ
	TThostFtdcAddInfoType	Message;
	///ժҪ
	TThostFtdcDigestType	Digest;
	///�����ʺ�����
	TThostFtdcBankAccTypeType	BankAccType;
	///������־
	TThostFtdcDeviceIDType	DeviceID;
	///�ڻ���λ�ʺ�����
	TThostFtdcBankAccTypeType	BankSecuAccType;
	///�ڻ���˾���б���
	TThostFtdcBankCodingForFutureType	BrokerIDByBank;
	///�ڻ���λ�ʺ�
	TThostFtdcBankAccountType	BankSecuAcc;
	///���������־
	TThostFtdcPwdFlagType	BankPwdFlag;
	///�ڻ��ʽ�����˶Ա�־
	TThostFtdcPwdFlagType	SecuPwdFlag;
	///���׹�Ա
	TThostFtdcOperNoType	OperNo;
	///������
	TThostFtdcRequestIDType	RequestID;
	///����ID
	TThostFtdcTIDType	TID;
	///ת�˽���״̬
	TThostFtdcTransferStatusType	TransferStatus;
	///�������
	TThostFtdcErrorIDType	ErrorID;
	///������Ϣ
	TThostFtdcErrorMsgType	ErrorMsg;
};

///��ѯ�˻���Ϣ����
struct CThostFtdcReqQueryAccountField
{
	///ҵ������
	TThostFtdcTradeCodeType	TradeCode;
	///���д���
	TThostFtdcBankIDType	BankID;
	///���з�֧��������
	TThostFtdcBankBrchIDType	BankBranchID;
	///���̴���
	TThostFtdcBrokerIDType	BrokerID;
	///���̷�֧��������
	TThostFtdcFutureBranchIDType	BrokerBranchID;
	///��������
	TThostFtdcTradeDateType	TradeDate;
	///����ʱ��
	TThostFtdcTradeTimeType	TradeTime;
	///������ˮ��
	TThostFtdcBankSerialType	BankSerial;
	///����ϵͳ���� 
	TThostFtdcTradeDateType	TradingDay;
	///����ƽ̨��Ϣ��ˮ��
	TThostFtdcSerialType	PlateSerial;
	///����Ƭ��־
	TThostFtdcLastFragmentType	LastFragment;
	///�Ự��
	TThostFtdcSessionIDType	SessionID;
	///�ͻ�����
	TThostFtdcIndividualNameType	CustomerName;
	///֤������
	TThostFtdcIdCardTypeType	IdCardType;
	///֤������
	TThostFtdcIdentifiedCardNoType	IdentifiedCardNo;
	///�ͻ�����
	TThostFtdcCustTypeType	CustType;
	///�����ʺ�
	TThostFtdcBankAccountType	BankAccount;
	///��������
	TThostFtdcPasswordType	BankPassWord;
	///Ͷ�����ʺ�
	TThostFtdcAccountIDType	AccountID;
	///�ڻ�����
	TThostFtdcPasswordType	Password;
	///�ڻ���˾��ˮ��
	TThostFtdcFutureSerialType	FutureSerial;
	///��װ���
	TThostFtdcInstallIDType	InstallID;
	///�û���ʶ
	TThostFtdcUserIDType	UserID;
	///��֤�ͻ�֤�������־
	TThostFtdcYesNoIndicatorType	VerifyCertNoFlag;
	///���ִ���
	TThostFtdcCurrencyIDType	CurrencyID;
	///ժҪ
	TThostFtdcDigestType	Digest;
	///�����ʺ�����
	TThostFtdcBankAccTypeType	BankAccType;
	///������־
	TThostFtdcDeviceIDType	DeviceID;
	///�ڻ���λ�ʺ�����
	TThostFtdcBankAccTypeType	BankSecuAccType;
	///�ڻ���˾���б���
	TThostFtdcBankCodingForFutureType	BrokerIDByBank;
	///�ڻ���λ�ʺ�
	TThostFtdcBankAccountType	BankSecuAcc;
	///���������־
	TThostFtdcPwdFlagType	BankPwdFlag;
	///�ڻ��ʽ�����˶Ա�־
	TThostFtdcPwdFlagType	SecuPwdFlag;
	///���׹�Ա
	TThostFtdcOperNoType	OperNo;
	///������
	TThostFtdcRequestIDType	RequestID;
	///����ID
	TThostFtdcTIDType	TID;
};

///��ѯ�˻���Ϣ��Ӧ
struct CThostFtdcRspQueryAccountField
{
	///ҵ������
	TThostFtdcTradeCodeType	TradeCode;
	///���д���
	TThostFtdcBankIDType	BankID;
	///���з�֧��������
	TThostFtdcBankBrchIDType	BankBranchID;
	///���̴���
	TThostFtdcBrokerIDType	BrokerID;
	///���̷�֧��������
	TThostFtdcFutureBranchIDType	BrokerBranchID;
	///��������
	TThostFtdcTradeDateType	TradeDate;
	///����ʱ��
	TThostFtdcTradeTimeType	TradeTime;
	///������ˮ��
	TThostFtdcBankSerialType	BankSerial;
	///����ϵͳ���� 
	TThostFtdcTradeDateType	TradingDay;
	///����ƽ̨��Ϣ��ˮ��
	TThostFtdcSerialType	PlateSerial;
	///����Ƭ��־
	TThostFtdcLastFragmentType	LastFragment;
	///�Ự��
	TThostFtdcSessionIDType	SessionID;
	///�ͻ�����
	TThostFtdcIndividualNameType	CustomerName;
	///֤������
	TThostFtdcIdCardTypeType	IdCardType;
	///֤������
	TThostFtdcIdentifiedCardNoType	IdentifiedCardNo;
	///�ͻ�����
	TThostFtdcCustTypeType	CustType;
	///�����ʺ�
	TThostFtdcBankAccountType	BankAccount;
	///��������
	TThostFtdcPasswordType	BankPassWord;
	///Ͷ�����ʺ�
	TThostFtdcAccountIDType	AccountID;
	///�ڻ�����
	TThostFtdcPasswordType	Password;
	///�ڻ���˾��ˮ��
	TThostFtdcFutureSerialType	FutureSerial;
	///��װ���
	TThostFtdcInstallIDType	InstallID;
	///�û���ʶ
	TThostFtdcUserIDType	UserID;
	///��֤�ͻ�֤�������־
	TThostFtdcYesNoIndicatorType	VerifyCertNoFlag;
	///���ִ���
	TThostFtdcCurrencyIDType	CurrencyID;
	///ժҪ
	TThostFtdcDigestType	Digest;
	///�����ʺ�����
	TThostFtdcBankAccTypeType	BankAccType;
	///������־
	TThostFtdcDeviceIDType	DeviceID;
	///�ڻ���λ�ʺ�����
	TThostFtdcBankAccTypeType	BankSecuAccType;
	///�ڻ���˾���б���
	TThostFtdcBankCodingForFutureType	BrokerIDByBank;
	///�ڻ���λ�ʺ�
	TThostFtdcBankAccountType	BankSecuAcc;
	///���������־
	TThostFtdcPwdFlagType	BankPwdFlag;
	///�ڻ��ʽ�����˶Ա�־
	TThostFtdcPwdFlagType	SecuPwdFlag;
	///���׹�Ա
	TThostFtdcOperNoType	OperNo;
	///������
	TThostFtdcRequestIDType	RequestID;
	///����ID
	TThostFtdcTIDType	TID;
	///���п��ý��
	TThostFtdcTradeAmountType	BankUseAmount;
	///���п�ȡ���
	TThostFtdcTradeAmountType	BankFetchAmount;
};

///����ǩ��ǩ��
struct CThostFtdcFutureSignIOField
{
	///ҵ������
	TThostFtdcTradeCodeType	TradeCode;
	///���д���
	TThostFtdcBankIDType	BankID;
	///���з�֧��������
	TThostFtdcBankBrchIDType	BankBranchID;
	///���̴���
	TThostFtdcBrokerIDType	BrokerID;
	///���̷�֧��������
	TThostFtdcFutureBranchIDType	BrokerBranchID;
	///��������
	TThostFtdcTradeDateType	TradeDate;
	///����ʱ��
	TThostFtdcTradeTimeType	TradeTime;
	///������ˮ��
	TThostFtdcBankSerialType	BankSerial;
	///����ϵͳ���� 
	TThostFtdcTradeDateType	TradingDay;
	///����ƽ̨��Ϣ��ˮ��
	TThostFtdcSerialType	PlateSerial;
	///����Ƭ��־
	TThostFtdcLastFragmentType	LastFragment;
	///�Ự��
	TThostFtdcSessionIDType	SessionID;
	///��װ���
	TThostFtdcInstallIDType	InstallID;
	///�û���ʶ
	TThostFtdcUserIDType	UserID;
	///ժҪ
	TThostFtdcDigestType	Digest;
	///���ִ���
	TThostFtdcCurrencyIDType	CurrencyID;
	///������־
	TThostFtdcDeviceIDType	DeviceID;
	///�ڻ���˾���б���
	TThostFtdcBankCodingForFutureType	BrokerIDByBank;
	///���׹�Ա
	TThostFtdcOperNoType	OperNo;
	///������
	TThostFtdcRequestIDType	RequestID;
	///����ID
	TThostFtdcTIDType	TID;
};

///����ǩ����Ӧ
struct CThostFtdcRspFutureSignInField
{
	///ҵ������
	TThostFtdcTradeCodeType	TradeCode;
	///���д���
	TThostFtdcBankIDType	BankID;
	///���з�֧��������
	TThostFtdcBankBrchIDType	BankBranchID;
	///���̴���
	TThostFtdcBrokerIDType	BrokerID;
	///���̷�֧��������
	TThostFtdcFutureBranchIDType	BrokerBranchID;
	///��������
	TThostFtdcTradeDateType	TradeDate;
	///����ʱ��
	TThostFtdcTradeTimeType	TradeTime;
	///������ˮ��
	TThostFtdcBankSerialType	BankSerial;
	///����ϵͳ���� 
	TThostFtdcTradeDateType	TradingDay;
	///����ƽ̨��Ϣ��ˮ��
	TThostFtdcSerialType	PlateSerial;
	///����Ƭ��־
	TThostFtdcLastFragmentType	LastFragment;
	///�Ự��
	TThostFtdcSessionIDType	SessionID;
	///��װ���
	TThostFtdcInstallIDType	InstallID;
	///�û���ʶ
	TThostFtdcUserIDType	UserID;
	///ժҪ
	TThostFtdcDigestType	Digest;
	///���ִ���
	TThostFtdcCurrencyIDType	CurrencyID;
	///������־
	TThostFtdcDeviceIDType	DeviceID;
	///�ڻ���˾���б���
	TThostFtdcBankCodingForFutureType	BrokerIDByBank;
	///���׹�Ա
	TThostFtdcOperNoType	OperNo;
	///������
	TThostFtdcRequestIDType	RequestID;
	///����ID
	TThostFtdcTIDType	TID;
	///�������
	TThostFtdcErrorIDType	ErrorID;
	///������Ϣ
	TThostFtdcErrorMsgType	ErrorMsg;
	///PIN��Կ
	TThostFtdcPasswordKeyType	PinKey;
	///MAC��Կ
	TThostFtdcPasswordKeyType	MacKey;
};

///����ǩ������
struct CThostFtdcReqFutureSignOutField
{
	///ҵ������
	TThostFtdcTradeCodeType	TradeCode;
	///���д���
	TThostFtdcBankIDType	BankID;
	///���з�֧��������
	TThostFtdcBankBrchIDType	BankBranchID;
	///���̴���
	TThostFtdcBrokerIDType	BrokerID;
	///���̷�֧��������
	TThostFtdcFutureBranchIDType	BrokerBranchID;
	///��������
	TThostFtdcTradeDateType	TradeDate;
	///����ʱ��
	TThostFtdcTradeTimeType	TradeTime;
	///������ˮ��
	TThostFtdcBankSerialType	BankSerial;
	///����ϵͳ���� 
	TThostFtdcTradeDateType	TradingDay;
	///����ƽ̨��Ϣ��ˮ��
	TThostFtdcSerialType	PlateSerial;
	///����Ƭ��־
	TThostFtdcLastFragmentType	LastFragment;
	///�Ự��
	TThostFtdcSessionIDType	SessionID;
	///��װ���
	TThostFtdcInstallIDType	InstallID;
	///�û���ʶ
	TThostFtdcUserIDType	UserID;
	///ժҪ
	TThostFtdcDigestType	Digest;
	///���ִ���
	TThostFtdcCurrencyIDType	CurrencyID;
	///������־
	TThostFtdcDeviceIDType	DeviceID;
	///�ڻ���˾���б���
	TThostFtdcBankCodingForFutureType	BrokerIDByBank;
	///���׹�Ա
	TThostFtdcOperNoType	OperNo;
	///������
	TThostFtdcRequestIDType	RequestID;
	///����ID
	TThostFtdcTIDType	TID;
};

///����ǩ����Ӧ
struct CThostFtdcRspFutureSignOutField
{
	///ҵ������
	TThostFtdcTradeCodeType	TradeCode;
	///���д���
	TThostFtdcBankIDType	BankID;
	///���з�֧��������
	TThostFtdcBankBrchIDType	BankBranchID;
	///���̴���
	TThostFtdcBrokerIDType	BrokerID;
	///���̷�֧��������
	TThostFtdcFutureBranchIDType	BrokerBranchID;
	///��������
	TThostFtdcTradeDateType	TradeDate;
	///����ʱ��
	TThostFtdcTradeTimeType	TradeTime;
	///������ˮ��
	TThostFtdcBankSerialType	BankSerial;
	///����ϵͳ���� 
	TThostFtdcTradeDateType	TradingDay;
	///����ƽ̨��Ϣ��ˮ��
	TThostFtdcSerialType	PlateSerial;
	///����Ƭ��־
	TThostFtdcLastFragmentType	LastFragment;
	///�Ự��
	TThostFtdcSessionIDType	SessionID;
	///��װ���
	TThostFtdcInstallIDType	InstallID;
	///�û���ʶ
	TThostFtdcUserIDType	UserID;
	///ժҪ
	TThostFtdcDigestType	Digest;
	///���ִ���
	TThostFtdcCurrencyIDType	CurrencyID;
	///������־
	TThostFtdcDeviceIDType	DeviceID;
	///�ڻ���˾���б���
	TThostFtdcBankCodingForFutureType	BrokerIDByBank;
	///���׹�Ա
	TThostFtdcOperNoType	OperNo;
	///������
	TThostFtdcRequestIDType	RequestID;
	///����ID
	TThostFtdcTIDType	TID;
	///�������
	TThostFtdcErrorIDType	ErrorID;
	///������Ϣ
	TThostFtdcErrorMsgType	ErrorMsg;
};

///��ѯָ����ˮ�ŵĽ��׽������
struct CThostFtdcReqQueryTradeResultBySerialField
{
	///ҵ������
	TThostFtdcTradeCodeType	TradeCode;
	///���д���
	TThostFtdcBankIDType	BankID;
	///���з�֧��������
	TThostFtdcBankBrchIDType	BankBranchID;
	///���̴���
	TThostFtdcBrokerIDType	BrokerID;
	///���̷�֧��������
	TThostFtdcFutureBranchIDType	BrokerBranchID;
	///��������
	TThostFtdcTradeDateType	TradeDate;
	///����ʱ��
	TThostFtdcTradeTimeType	TradeTime;
	///������ˮ��
	TThostFtdcBankSerialType	BankSerial;
	///����ϵͳ���� 
	TThostFtdcTradeDateType	TradingDay;
	///����ƽ̨��Ϣ��ˮ��
	TThostFtdcSerialType	PlateSerial;
	///����Ƭ��־
	TThostFtdcLastFragmentType	LastFragment;
	///�Ự��
	TThostFtdcSessionIDType	SessionID;
	///��ˮ��
	TThostFtdcSerialType	Reference;
	///����ˮ�ŷ����ߵĻ�������
	TThostFtdcInstitutionTypeType	RefrenceIssureType;
	///����ˮ�ŷ����߻�������
	TThostFtdcOrganCodeType	RefrenceIssure;
	///�ͻ�����
	TThostFtdcIndividualNameType	CustomerName;
	///֤������
	TThostFtdcIdCardTypeType	IdCardType;
	///֤������
	TThostFtdcIdentifiedCardNoType	IdentifiedCardNo;
	///�ͻ�����
	TThostFtdcCustTypeType	CustType;
	///�����ʺ�
	TThostFtdcBankAccountType	BankAccount;
	///��������
	TThostFtdcPasswordType	BankPassWord;
	///Ͷ�����ʺ�
	TThostFtdcAccountIDType	AccountID;
	///�ڻ�����
	TThostFtdcPasswordType	Password;
	///���ִ���
	TThostFtdcCurrencyIDType	CurrencyID;
	///ת�ʽ��
	TThostFtdcTradeAmountType	TradeAmount;
	///ժҪ
	TThostFtdcDigestType	Digest;
};

///��ѯָ����ˮ�ŵĽ��׽����Ӧ
struct CThostFtdcRspQueryTradeResultBySerialField
{
	///ҵ������
	TThostFtdcTradeCodeType	TradeCode;
	///���д���
	TThostFtdcBankIDType	BankID;
	///���з�֧��������
	TThostFtdcBankBrchIDType	BankBranchID;
	///���̴���
	TThostFtdcBrokerIDType	BrokerID;
	///���̷�֧��������
	TThostFtdcFutureBranchIDType	BrokerBranchID;
	///��������
	TThostFtdcTradeDateType	TradeDate;
	///����ʱ��
	TThostFtdcTradeTimeType	TradeTime;
	///������ˮ��
	TThostFtdcBankSerialType	BankSerial;
	///����ϵͳ���� 
	TThostFtdcTradeDateType	TradingDay;
	///����ƽ̨��Ϣ��ˮ��
	TThostFtdcSerialType	PlateSerial;
	///����Ƭ��־
	TThostFtdcLastFragmentType	LastFragment;
	///�Ự��
	TThostFtdcSessionIDType	SessionID;
	///�������
	TThostFtdcErrorIDType	ErrorID;
	///������Ϣ
	TThostFtdcErrorMsgType	ErrorMsg;
	///��ˮ��
	TThostFtdcSerialType	Reference;
	///����ˮ�ŷ����ߵĻ�������
	TThostFtdcInstitutionTypeType	RefrenceIssureType;
	///����ˮ�ŷ����߻�������
	TThostFtdcOrganCodeType	RefrenceIssure;
	///ԭʼ���ش���
	TThostFtdcReturnCodeType	OriginReturnCode;
	///ԭʼ����������
	TThostFtdcDescrInfoForReturnCodeType	OriginDescrInfoForReturnCode;
	///�����ʺ�
	TThostFtdcBankAccountType	BankAccount;
	///��������
	TThostFtdcPasswordType	BankPassWord;
	///Ͷ�����ʺ�
	TThostFtdcAccountIDType	AccountID;
	///�ڻ�����
	TThostFtdcPasswordType	Password;
	///���ִ���
	TThostFtdcCurrencyIDType	CurrencyID;
	///ת�ʽ��
	TThostFtdcTradeAmountType	TradeAmount;
	///ժҪ
	TThostFtdcDigestType	Digest;
};

///�����ļ���������
struct CThostFtdcReqDayEndFileReadyField
{
	///ҵ������
	TThostFtdcTradeCodeType	TradeCode;
	///���д���
	TThostFtdcBankIDType	BankID;
	///���з�֧��������
	TThostFtdcBankBrchIDType	BankBranchID;
	///���̴���
	TThostFtdcBrokerIDType	BrokerID;
	///���̷�֧��������
	TThostFtdcFutureBranchIDType	BrokerBranchID;
	///��������
	TThostFtdcTradeDateType	TradeDate;
	///����ʱ��
	TThostFtdcTradeTimeType	TradeTime;
	///������ˮ��
	TThostFtdcBankSerialType	BankSerial;
	///����ϵͳ���� 
	TThostFtdcTradeDateType	TradingDay;
	///����ƽ̨��Ϣ��ˮ��
	TThostFtdcSerialType	PlateSerial;
	///����Ƭ��־
	TThostFtdcLastFragmentType	LastFragment;
	///�Ự��
	TThostFtdcSessionIDType	SessionID;
	///�ļ�ҵ����
	TThostFtdcFileBusinessCodeType	FileBusinessCode;
	///��װ���
	TThostFtdcInstallIDType	InstallID;
	///�û���ʶ
	TThostFtdcUserIDType	UserID;
	///ժҪ
	TThostFtdcDigestType	Digest;
	///���ִ���
	TThostFtdcCurrencyIDType	CurrencyID;
	///������־
	TThostFtdcDeviceIDType	DeviceID;
	///�ڻ���˾���б���
	TThostFtdcBankCodingForFutureType	BrokerIDByBank;
	///���׹�Ա
	TThostFtdcOperNoType	OperNo;
	///������
	TThostFtdcRequestIDType	RequestID;
	///����ID
	TThostFtdcTIDType	TID;
};

///�����ļ�������Ӧ
struct CThostFtdcRspDayEndFileReadyField
{
	///ҵ������
	TThostFtdcTradeCodeType	TradeCode;
	///���д���
	TThostFtdcBankIDType	BankID;
	///���з�֧��������
	TThostFtdcBankBrchIDType	BankBranchID;
	///���̴���
	TThostFtdcBrokerIDType	BrokerID;
	///���̷�֧��������
	TThostFtdcFutureBranchIDType	BrokerBranchID;
	///��������
	TThostFtdcTradeDateType	TradeDate;
	///����ʱ��
	TThostFtdcTradeTimeType	TradeTime;
	///������ˮ��
	TThostFtdcBankSerialType	BankSerial;
	///����ϵͳ���� 
	TThostFtdcTradeDateType	TradingDay;
	///����ƽ̨��Ϣ��ˮ��
	TThostFtdcSerialType	PlateSerial;
	///����Ƭ��־
	TThostFtdcLastFragmentType	LastFragment;
	///�Ự��
	TThostFtdcSessionIDType	SessionID;
	///�ļ�ҵ����
	TThostFtdcFileBusinessCodeType	FileBusinessCode;
	///��װ���
	TThostFtdcInstallIDType	InstallID;
	///�û���ʶ
	TThostFtdcUserIDType	UserID;
	///ժҪ
	TThostFtdcDigestType	Digest;
	///���ִ���
	TThostFtdcCurrencyIDType	CurrencyID;
	///������־
	TThostFtdcDeviceIDType	DeviceID;
	///�ڻ���˾���б���
	TThostFtdcBankCodingForFutureType	BrokerIDByBank;
	///���׹�Ա
	TThostFtdcOperNoType	OperNo;
	///������
	TThostFtdcRequestIDType	RequestID;
	///����ID
	TThostFtdcTIDType	TID;
	///�������
	TThostFtdcErrorIDType	ErrorID;
	///������Ϣ
	TThostFtdcErrorMsgType	ErrorMsg;
};

///�����ļ�������Ӧ
struct CThostFtdcDayEndFileReadyField
{
	///ҵ������
	TThostFtdcTradeCodeType	TradeCode;
	///���д���
	TThostFtdcBankIDType	BankID;
	///���з�֧��������
	TThostFtdcBankBrchIDType	BankBranchID;
	///���̴���
	TThostFtdcBrokerIDType	BrokerID;
	///���̷�֧��������
	TThostFtdcFutureBranchIDType	BrokerBranchID;
	///��������
	TThostFtdcTradeDateType	TradeDate;
	///����ʱ��
	TThostFtdcTradeTimeType	TradeTime;
	///������ˮ��
	TThostFtdcBankSerialType	BankSerial;
	///����ϵͳ���� 
	TThostFtdcTradeDateType	TradingDay;
	///����ƽ̨��Ϣ��ˮ��
	TThostFtdcSerialType	PlateSerial;
	///����Ƭ��־
	TThostFtdcLastFragmentType	LastFragment;
	///�Ự��
	TThostFtdcSessionIDType	SessionID;
	///�ļ�ҵ����
	TThostFtdcFileBusinessCodeType	FileBusinessCode;
	///��װ���
	TThostFtdcInstallIDType	InstallID;
	///�û���ʶ
	TThostFtdcUserIDType	UserID;
	///ժҪ
	TThostFtdcDigestType	Digest;
	///���ִ���
	TThostFtdcCurrencyIDType	CurrencyID;
	///������־
	TThostFtdcDeviceIDType	DeviceID;
	///�ڻ���˾���б���
	TThostFtdcBankCodingForFutureType	BrokerIDByBank;
	///���׹�Ա
	TThostFtdcOperNoType	OperNo;
	///������
	TThostFtdcRequestIDType	RequestID;
	///����ID
	TThostFtdcTIDType	TID;
	///�������
	TThostFtdcErrorIDType	ErrorID;
	///������Ϣ
	TThostFtdcErrorMsgType	ErrorMsg;
};

///���ؽ��
struct CThostFtdcReturnResultField
{
	///���ش���
	TThostFtdcReturnCodeType	ReturnCode;
	///����������
	TThostFtdcDescrInfoForReturnCodeType	DescrInfoForReturnCode;
};

///��֤�ڻ��ʽ�����
struct CThostFtdcVerifyFuturePasswordField
{
	///ҵ������
	TThostFtdcTradeCodeType	TradeCode;
	///���д���
	TThostFtdcBankIDType	BankID;
	///���з�֧��������
	TThostFtdcBankBrchIDType	BankBranchID;
	///���̴���
	TThostFtdcBrokerIDType	BrokerID;
	///���̷�֧��������
	TThostFtdcFutureBranchIDType	BrokerBranchID;
	///��������
	TThostFtdcTradeDateType	TradeDate;
	///����ʱ��
	TThostFtdcTradeTimeType	TradeTime;
	///������ˮ��
	TThostFtdcBankSerialType	BankSerial;
	///����ϵͳ���� 
	TThostFtdcTradeDateType	TradingDay;
	///����ƽ̨��Ϣ��ˮ��
	TThostFtdcSerialType	PlateSerial;
	///����Ƭ��־
	TThostFtdcLastFragmentType	LastFragment;
	///�Ự��
	TThostFtdcSessionIDType	SessionID;
	///Ͷ�����ʺ�
	TThostFtdcAccountIDType	AccountID;
	///�ڻ�����
	TThostFtdcPasswordType	Password;
	///�����ʺ�
	TThostFtdcBankAccountType	BankAccount;
	///��������
	TThostFtdcPasswordType	BankPassWord;
	///��װ���
	TThostFtdcInstallIDType	InstallID;
	///����ID
	TThostFtdcTIDType	TID;
	///���ִ���
	TThostFtdcCurrencyIDType	CurrencyID;
};

///��֤�ͻ���Ϣ
struct CThostFtdcVerifyCustInfoField
{
	///�ͻ�����
	TThostFtdcIndividualNameType	CustomerName;
	///֤������
	TThostFtdcIdCardTypeType	IdCardType;
	///֤������
	TThostFtdcIdentifiedCardNoType	IdentifiedCardNo;
	///�ͻ�����
	TThostFtdcCustTypeType	CustType;
};

///��֤�ڻ��ʽ�����Ϳͻ���Ϣ
struct CThostFtdcVerifyFuturePasswordAndCustInfoField
{
	///�ͻ�����
	TThostFtdcIndividualNameType	CustomerName;
	///֤������
	TThostFtdcIdCardTypeType	IdCardType;
	///֤������
	TThostFtdcIdentifiedCardNoType	IdentifiedCardNo;
	///�ͻ�����
	TThostFtdcCustTypeType	CustType;
	///Ͷ�����ʺ�
	TThostFtdcAccountIDType	AccountID;
	///�ڻ�����
	TThostFtdcPasswordType	Password;
	///���ִ���
	TThostFtdcCurrencyIDType	CurrencyID;
};

///��֤�ڻ��ʽ�����Ϳͻ���Ϣ
struct CThostFtdcDepositResultInformField
{
	///�������ˮ�ţ�����ˮ��Ϊ���ڱ��̷��ص���ˮ��
	TThostFtdcDepositSeqNoType	DepositSeqNo;
	///���͹�˾����
	TThostFtdcBrokerIDType	BrokerID;
	///Ͷ���ߴ���
	TThostFtdcInvestorIDType	InvestorID;
	///�����
	TThostFtdcMoneyType	Deposit;
	///������
	TThostFtdcRequestIDType	RequestID;
	///���ش���
	TThostFtdcReturnCodeType	ReturnCode;
	///����������
	TThostFtdcDescrInfoForReturnCodeType	DescrInfoForReturnCode;
};

///���׺��������ڱ��̷�����Կͬ������
struct CThostFtdcReqSyncKeyField
{
	///ҵ������
	TThostFtdcTradeCodeType	TradeCode;
	///���д���
	TThostFtdcBankIDType	BankID;
	///���з�֧��������
	TThostFtdcBankBrchIDType	BankBranchID;
	///���̴���
	TThostFtdcBrokerIDType	BrokerID;
	///���̷�֧��������
	TThostFtdcFutureBranchIDType	BrokerBranchID;
	///��������
	TThostFtdcTradeDateType	TradeDate;
	///����ʱ��
	TThostFtdcTradeTimeType	TradeTime;
	///������ˮ��
	TThostFtdcBankSerialType	BankSerial;
	///����ϵͳ���� 
	TThostFtdcTradeDateType	TradingDay;
	///����ƽ̨��Ϣ��ˮ��
	TThostFtdcSerialType	PlateSerial;
	///����Ƭ��־
	TThostFtdcLastFragmentType	LastFragment;
	///�Ự��
	TThostFtdcSessionIDType	SessionID;
	///��װ���
	TThostFtdcInstallIDType	InstallID;
	///�û���ʶ
	TThostFtdcUserIDType	UserID;
	///���׺��ĸ����ڱ��̵���Ϣ
	TThostFtdcAddInfoType	Message;
	///������־
	TThostFtdcDeviceIDType	DeviceID;
	///�ڻ���˾���б���
	TThostFtdcBankCodingForFutureType	BrokerIDByBank;
	///���׹�Ա
	TThostFtdcOperNoType	OperNo;
	///������
	TThostFtdcRequestIDType	RequestID;
	///����ID
	TThostFtdcTIDType	TID;
};

///���׺��������ڱ��̷�����Կͬ����Ӧ
struct CThostFtdcRspSyncKeyField
{
	///ҵ������
	TThostFtdcTradeCodeType	TradeCode;
	///���д���
	TThostFtdcBankIDType	BankID;
	///���з�֧��������
	TThostFtdcBankBrchIDType	BankBranchID;
	///���̴���
	TThostFtdcBrokerIDType	BrokerID;
	///���̷�֧��������
	TThostFtdcFutureBranchIDType	BrokerBranchID;
	///��������
	TThostFtdcTradeDateType	TradeDate;
	///����ʱ��
	TThostFtdcTradeTimeType	TradeTime;
	///������ˮ��
	TThostFtdcBankSerialType	BankSerial;
	///����ϵͳ���� 
	TThostFtdcTradeDateType	TradingDay;
	///����ƽ̨��Ϣ��ˮ��
	TThostFtdcSerialType	PlateSerial;
	///����Ƭ��־
	TThostFtdcLastFragmentType	LastFragment;
	///�Ự��
	TThostFtdcSessionIDType	SessionID;
	///��װ���
	TThostFtdcInstallIDType	InstallID;
	///�û���ʶ
	TThostFtdcUserIDType	UserID;
	///���׺��ĸ����ڱ��̵���Ϣ
	TThostFtdcAddInfoType	Message;
	///������־
	TThostFtdcDeviceIDType	DeviceID;
	///�ڻ���˾���б���
	TThostFtdcBankCodingForFutureType	BrokerIDByBank;
	///���׹�Ա
	TThostFtdcOperNoType	OperNo;
	///������
	TThostFtdcRequestIDType	RequestID;
	///����ID
	TThostFtdcTIDType	TID;
	///�������
	TThostFtdcErrorIDType	ErrorID;
	///������Ϣ
	TThostFtdcErrorMsgType	ErrorMsg;
};

///��ѯ�˻���Ϣ֪ͨ
struct CThostFtdcNotifyQueryAccountField
{
	///ҵ������
	TThostFtdcTradeCodeType	TradeCode;
	///���д���
	TThostFtdcBankIDType	BankID;
	///���з�֧��������
	TThostFtdcBankBrchIDType	BankBranchID;
	///���̴���
	TThostFtdcBrokerIDType	BrokerID;
	///���̷�֧��������
	TThostFtdcFutureBranchIDType	BrokerBranchID;
	///��������
	TThostFtdcTradeDateType	TradeDate;
	///����ʱ��
	TThostFtdcTradeTimeType	TradeTime;
	///������ˮ��
	TThostFtdcBankSerialType	BankSerial;
	///����ϵͳ���� 
	TThostFtdcTradeDateType	TradingDay;
	///����ƽ̨��Ϣ��ˮ��
	TThostFtdcSerialType	PlateSerial;
	///����Ƭ��־
	TThostFtdcLastFragmentType	LastFragment;
	///�Ự��
	TThostFtdcSessionIDType	SessionID;
	///�ͻ�����
	TThostFtdcIndividualNameType	CustomerName;
	///֤������
	TThostFtdcIdCardTypeType	IdCardType;
	///֤������
	TThostFtdcIdentifiedCardNoType	IdentifiedCardNo;
	///�ͻ�����
	TThostFtdcCustTypeType	CustType;
	///�����ʺ�
	TThostFtdcBankAccountType	BankAccount;
	///��������
	TThostFtdcPasswordType	BankPassWord;
	///Ͷ�����ʺ�
	TThostFtdcAccountIDType	AccountID;
	///�ڻ�����
	TThostFtdcPasswordType	Password;
	///�ڻ���˾��ˮ��
	TThostFtdcFutureSerialType	FutureSerial;
	///��װ���
	TThostFtdcInstallIDType	InstallID;
	///�û���ʶ
	TThostFtdcUserIDType	UserID;
	///��֤�ͻ�֤�������־
	TThostFtdcYesNoIndicatorType	VerifyCertNoFlag;
	///���ִ���
	TThostFtdcCurrencyIDType	CurrencyID;
	///ժҪ
	TThostFtdcDigestType	Digest;
	///�����ʺ�����
	TThostFtdcBankAccTypeType	BankAccType;
	///������־
	TThostFtdcDeviceIDType	DeviceID;
	///�ڻ���λ�ʺ�����
	TThostFtdcBankAccTypeType	BankSecuAccType;
	///�ڻ���˾���б���
	TThostFtdcBankCodingForFutureType	BrokerIDByBank;
	///�ڻ���λ�ʺ�
	TThostFtdcBankAccountType	BankSecuAcc;
	///���������־
	TThostFtdcPwdFlagType	BankPwdFlag;
	///�ڻ��ʽ�����˶Ա�־
	TThostFtdcPwdFlagType	SecuPwdFlag;
	///���׹�Ա
	TThostFtdcOperNoType	OperNo;
	///������
	TThostFtdcRequestIDType	RequestID;
	///����ID
	TThostFtdcTIDType	TID;
	///���п��ý��
	TThostFtdcTradeAmountType	BankUseAmount;
	///���п�ȡ���
	TThostFtdcTradeAmountType	BankFetchAmount;
	///�������
	TThostFtdcErrorIDType	ErrorID;
	///������Ϣ
	TThostFtdcErrorMsgType	ErrorMsg;
};

///����ת�˽�����ˮ��
struct CThostFtdcTransferSerialField
{
	///ƽ̨��ˮ��
	TThostFtdcPlateSerialType	PlateSerial;
	///���׷�������
	TThostFtdcTradeDateType	TradeDate;
	///��������
	TThostFtdcDateType	TradingDay;
	///����ʱ��
	TThostFtdcTradeTimeType	TradeTime;
	///���״���
	TThostFtdcTradeCodeType	TradeCode;
	///�Ự���
	TThostFtdcSessionIDType	SessionID;
	///���б���
	TThostFtdcBankIDType	BankID;
	///���з�֧��������
	TThostFtdcBankBrchIDType	BankBranchID;
	///�����ʺ�����
	TThostFtdcBankAccTypeType	BankAccType;
	///�����ʺ�
	TThostFtdcBankAccountType	BankAccount;
	///������ˮ��
	TThostFtdcBankSerialType	BankSerial;
	///�ڻ���˾����
	TThostFtdcBrokerIDType	BrokerID;
	///���̷�֧��������
	TThostFtdcFutureBranchIDType	BrokerBranchID;
	///�ڻ���˾�ʺ�����
	TThostFtdcFutureAccTypeType	FutureAccType;
	///Ͷ�����ʺ�
	TThostFtdcAccountIDType	AccountID;
	///Ͷ���ߴ���
	TThostFtdcInvestorIDType	InvestorID;
	///�ڻ���˾��ˮ��
	TThostFtdcFutureSerialType	FutureSerial;
	///֤������
	TThostFtdcIdCardTypeType	IdCardType;
	///֤������
	TThostFtdcIdentifiedCardNoType	IdentifiedCardNo;
	///���ִ���
	TThostFtdcCurrencyIDType	CurrencyID;
	///���׽��
	TThostFtdcTradeAmountType	TradeAmount;
	///Ӧ�տͻ�����
	TThostFtdcCustFeeType	CustFee;
	///Ӧ���ڻ���˾����
	TThostFtdcFutureFeeType	BrokerFee;
	///��Ч��־
	TThostFtdcAvailabilityFlagType	AvailabilityFlag;
	///����Ա
	TThostFtdcOperatorCodeType	OperatorCode;
	///�������ʺ�
	TThostFtdcBankAccountType	BankNewAccount;
	///�������
	TThostFtdcErrorIDType	ErrorID;
	///������Ϣ
	TThostFtdcErrorMsgType	ErrorMsg;
};

///�����ѯת����ˮ
struct CThostFtdcQryTransferSerialField
{
	///���͹�˾����
	TThostFtdcBrokerIDType	BrokerID;
	///Ͷ�����ʺ�
	TThostFtdcAccountIDType	AccountID;
	///���б���
	TThostFtdcBankIDType	BankID;
	///���ִ���
	TThostFtdcCurrencyIDType	CurrencyID;
};

///����ǩ��֪ͨ
struct CThostFtdcNotifyFutureSignInField
{
	///ҵ������
	TThostFtdcTradeCodeType	TradeCode;
	///���д���
	TThostFtdcBankIDType	BankID;
	///���з�֧��������
	TThostFtdcBankBrchIDType	BankBranchID;
	///���̴���
	TThostFtdcBrokerIDType	BrokerID;
	///���̷�֧��������
	TThostFtdcFutureBranchIDType	BrokerBranchID;
	///��������
	TThostFtdcTradeDateType	TradeDate;
	///����ʱ��
	TThostFtdcTradeTimeType	TradeTime;
	///������ˮ��
	TThostFtdcBankSerialType	BankSerial;
	///����ϵͳ���� 
	TThostFtdcTradeDateType	TradingDay;
	///����ƽ̨��Ϣ��ˮ��
	TThostFtdcSerialType	PlateSerial;
	///����Ƭ��־
	TThostFtdcLastFragmentType	LastFragment;
	///�Ự��
	TThostFtdcSessionIDType	SessionID;
	///��װ���
	TThostFtdcInstallIDType	InstallID;
	///�û���ʶ
	TThostFtdcUserIDType	UserID;
	///ժҪ
	TThostFtdcDigestType	Digest;
	///���ִ���
	TThostFtdcCurrencyIDType	CurrencyID;
	///������־
	TThostFtdcDeviceIDType	DeviceID;
	///�ڻ���˾���б���
	TThostFtdcBankCodingForFutureType	BrokerIDByBank;
	///���׹�Ա
	TThostFtdcOperNoType	OperNo;
	///������
	TThostFtdcRequestIDType	RequestID;
	///����ID
	TThostFtdcTIDType	TID;
	///�������
	TThostFtdcErrorIDType	ErrorID;
	///������Ϣ
	TThostFtdcErrorMsgType	ErrorMsg;
	///PIN��Կ
	TThostFtdcPasswordKeyType	PinKey;
	///MAC��Կ
	TThostFtdcPasswordKeyType	MacKey;
};

///����ǩ��֪ͨ
struct CThostFtdcNotifyFutureSignOutField
{
	///ҵ������
	TThostFtdcTradeCodeType	TradeCode;
	///���д���
	TThostFtdcBankIDType	BankID;
	///���з�֧��������
	TThostFtdcBankBrchIDType	BankBranchID;
	///���̴���
	TThostFtdcBrokerIDType	BrokerID;
	///���̷�֧��������
	TThostFtdcFutureBranchIDType	BrokerBranchID;
	///��������
	TThostFtdcTradeDateType	TradeDate;
	///����ʱ��
	TThostFtdcTradeTimeType	TradeTime;
	///������ˮ��
	TThostFtdcBankSerialType	BankSerial;
	///����ϵͳ���� 
	TThostFtdcTradeDateType	TradingDay;
	///����ƽ̨��Ϣ��ˮ��
	TThostFtdcSerialType	PlateSerial;
	///����Ƭ��־
	TThostFtdcLastFragmentType	LastFragment;
	///�Ự��
	TThostFtdcSessionIDType	SessionID;
	///��װ���
	TThostFtdcInstallIDType	InstallID;
	///�û���ʶ
	TThostFtdcUserIDType	UserID;
	///ժҪ
	TThostFtdcDigestType	Digest;
	///���ִ���
	TThostFtdcCurrencyIDType	CurrencyID;
	///������־
	TThostFtdcDeviceIDType	DeviceID;
	///�ڻ���˾���б���
	TThostFtdcBankCodingForFutureType	BrokerIDByBank;
	///���׹�Ա
	TThostFtdcOperNoType	OperNo;
	///������
	TThostFtdcRequestIDType	RequestID;
	///����ID
	TThostFtdcTIDType	TID;
	///�������
	TThostFtdcErrorIDType	ErrorID;
	///������Ϣ
	TThostFtdcErrorMsgType	ErrorMsg;
};

///���׺��������ڱ��̷�����Կͬ����������֪ͨ
struct CThostFtdcNotifySyncKeyField
{
	///ҵ������
	TThostFtdcTradeCodeType	TradeCode;
	///���д���
	TThostFtdcBankIDType	BankID;
	///���з�֧��������
	TThostFtdcBankBrchIDType	BankBranchID;
	///���̴���
	TThostFtdcBrokerIDType	BrokerID;
	///���̷�֧��������
	TThostFtdcFutureBranchIDType	BrokerBranchID;
	///��������
	TThostFtdcTradeDateType	TradeDate;
	///����ʱ��
	TThostFtdcTradeTimeType	TradeTime;
	///������ˮ��
	TThostFtdcBankSerialType	BankSerial;
	///����ϵͳ���� 
	TThostFtdcTradeDateType	TradingDay;
	///����ƽ̨��Ϣ��ˮ��
	TThostFtdcSerialType	PlateSerial;
	///����Ƭ��־
	TThostFtdcLastFragmentType	LastFragment;
	///�Ự��
	TThostFtdcSessionIDType	SessionID;
	///��װ���
	TThostFtdcInstallIDType	InstallID;
	///�û���ʶ
	TThostFtdcUserIDType	UserID;
	///���׺��ĸ����ڱ��̵���Ϣ
	TThostFtdcAddInfoType	Message;
	///������־
	TThostFtdcDeviceIDType	DeviceID;
	///�ڻ���˾���б���
	TThostFtdcBankCodingForFutureType	BrokerIDByBank;
	///���׹�Ա
	TThostFtdcOperNoType	OperNo;
	///������
	TThostFtdcRequestIDType	RequestID;
	///����ID
	TThostFtdcTIDType	TID;
	///�������
	TThostFtdcErrorIDType	ErrorID;
	///������Ϣ
	TThostFtdcErrorMsgType	ErrorMsg;
};

///�����ѯ����ǩԼ��ϵ
struct CThostFtdcQryAccountregisterField
{
	///���͹�˾����
	TThostFtdcBrokerIDType	BrokerID;
	///Ͷ�����ʺ�
	TThostFtdcAccountIDType	AccountID;
	///���б���
	TThostFtdcBankIDType	BankID;
	///���з�֧��������
	TThostFtdcBankBrchIDType	BankBranchID;
	///���ִ���
	TThostFtdcCurrencyIDType	CurrencyID;
};

///�ͻ���������Ϣ��
struct CThostFtdcAccountregisterField
{
	///��������
	TThostFtdcTradeDateType	TradeDay;
	///���б���
	TThostFtdcBankIDType	BankID;
	///���з�֧��������
	TThostFtdcBankBrchIDType	BankBranchID;
	///�����ʺ�
	TThostFtdcBankAccountType	BankAccount;
	///�ڻ���˾����
	TThostFtdcBrokerIDType	BrokerID;
	///�ڻ���˾��֧��������
	TThostFtdcFutureBranchIDType	BrokerBranchID;
	///Ͷ�����ʺ�
	TThostFtdcAccountIDType	AccountID;
	///֤������
	TThostFtdcIdCardTypeType	IdCardType;
	///֤������
	TThostFtdcIdentifiedCardNoType	IdentifiedCardNo;
	///�ͻ�����
	TThostFtdcIndividualNameType	CustomerName;
	///���ִ���
	TThostFtdcCurrencyIDType	CurrencyID;
	///���������
	TThostFtdcOpenOrDestroyType	OpenOrDestroy;
	///ǩԼ����
	TThostFtdcTradeDateType	RegDate;
	///��Լ����
	TThostFtdcTradeDateType	OutDate;
	///����ID
	TThostFtdcTIDType	TID;
	///�ͻ�����
	TThostFtdcCustTypeType	CustType;
	///�����ʺ�����
	TThostFtdcBankAccTypeType	BankAccType;
};

///���ڿ�����Ϣ
struct CThostFtdcOpenAccountField
{
	///ҵ������
	TThostFtdcTradeCodeType	TradeCode;
	///���д���
	TThostFtdcBankIDType	BankID;
	///���з�֧��������
	TThostFtdcBankBrchIDType	BankBranchID;
	///���̴���
	TThostFtdcBrokerIDType	BrokerID;
	///���̷�֧��������
	TThostFtdcFutureBranchIDType	BrokerBranchID;
	///��������
	TThostFtdcTradeDateType	TradeDate;
	///����ʱ��
	TThostFtdcTradeTimeType	TradeTime;
	///������ˮ��
	TThostFtdcBankSerialType	BankSerial;
	///����ϵͳ���� 
	TThostFtdcTradeDateType	TradingDay;
	///����ƽ̨��Ϣ��ˮ��
	TThostFtdcSerialType	PlateSerial;
	///����Ƭ��־
	TThostFtdcLastFragmentType	LastFragment;
	///�Ự��
	TThostFtdcSessionIDType	SessionID;
	///�ͻ�����
	TThostFtdcIndividualNameType	CustomerName;
	///֤������
	TThostFtdcIdCardTypeType	IdCardType;
	///֤������
	TThostFtdcIdentifiedCardNoType	IdentifiedCardNo;
	///�Ա�
	TThostFtdcGenderType	Gender;
	///���Ҵ���
	TThostFtdcCountryCodeType	CountryCode;
	///�ͻ�����
	TThostFtdcCustTypeType	CustType;
	///��ַ
	TThostFtdcAddressType	Address;
	///�ʱ�
	TThostFtdcZipCodeType	ZipCode;
	///�绰����
	TThostFtdcTelephoneType	Telephone;
	///�ֻ�
	TThostFtdcMobilePhoneType	MobilePhone;
	///����
	TThostFtdcFaxType	Fax;
	///�����ʼ�
	TThostFtdcEMailType	EMail;
	///�ʽ��˻�״̬
	TThostFtdcMoneyAccountStatusType	MoneyAccountStatus;
	///�����ʺ�
	TThostFtdcBankAccountType	BankAccount;
	///��������
	TThostFtdcPasswordType	BankPassWord;
	///Ͷ�����ʺ�
	TThostFtdcAccountIDType	AccountID;
	///�ڻ�����
	TThostFtdcPasswordType	Password;
	///��װ���
	TThostFtdcInstallIDType	InstallID;
	///��֤�ͻ�֤�������־
	TThostFtdcYesNoIndicatorType	VerifyCertNoFlag;
	///���ִ���
	TThostFtdcCurrencyIDType	CurrencyID;
	///�㳮��־
	TThostFtdcCashExchangeCodeType	CashExchangeCode;
	///ժҪ
	TThostFtdcDigestType	Digest;
	///�����ʺ�����
	TThostFtdcBankAccTypeType	BankAccType;
	///������־
	TThostFtdcDeviceIDType	DeviceID;
	///�ڻ���λ�ʺ�����
	TThostFtdcBankAccTypeType	BankSecuAccType;
	///�ڻ���˾���б���
	TThostFtdcBankCodingForFutureType	BrokerIDByBank;
	///�ڻ���λ�ʺ�
	TThostFtdcBankAccountType	BankSecuAcc;
	///���������־
	TThostFtdcPwdFlagType	BankPwdFlag;
	///�ڻ��ʽ�����˶Ա�־
	TThostFtdcPwdFlagType	SecuPwdFlag;
	///���׹�Ա
	TThostFtdcOperNoType	OperNo;
	///����ID
	TThostFtdcTIDType	TID;
	///�û���ʶ
	TThostFtdcUserIDType	UserID;
	///�������
	TThostFtdcErrorIDType	ErrorID;
	///������Ϣ
	TThostFtdcErrorMsgType	ErrorMsg;
	///֤ȯ�ʽ��ճ����
	TThostFtdcTradeAmountType	SecDaBeBl;
	///����ת��ͨ��
	TThostFtdcBankChannelType	BankChal;
};

///����������Ϣ
struct CThostFtdcCancelAccountField
{
	///ҵ������
	TThostFtdcTradeCodeType	TradeCode;
	///���д���
	TThostFtdcBankIDType	BankID;
	///���з�֧��������
	TThostFtdcBankBrchIDType	BankBranchID;
	///���̴���
	TThostFtdcBrokerIDType	BrokerID;
	///���̷�֧��������
	TThostFtdcFutureBranchIDType	BrokerBranchID;
	///��������
	TThostFtdcTradeDateType	TradeDate;
	///����ʱ��
	TThostFtdcTradeTimeType	TradeTime;
	///������ˮ��
	TThostFtdcBankSerialType	BankSerial;
	///����ϵͳ���� 
	TThostFtdcTradeDateType	TradingDay;
	///����ƽ̨��Ϣ��ˮ��
	TThostFtdcSerialType	PlateSerial;
	///����Ƭ��־
	TThostFtdcLastFragmentType	LastFragment;
	///�Ự��
	TThostFtdcSessionIDType	SessionID;
	///�ͻ�����
	TThostFtdcIndividualNameType	CustomerName;
	///֤������
	TThostFtdcIdCardTypeType	IdCardType;
	///֤������
	TThostFtdcIdentifiedCardNoType	IdentifiedCardNo;
	///�Ա�
	TThostFtdcGenderType	Gender;
	///���Ҵ���
	TThostFtdcCountryCodeType	CountryCode;
	///�ͻ�����
	TThostFtdcCustTypeType	CustType;
	///��ַ
	TThostFtdcAddressType	Address;
	///�ʱ�
	TThostFtdcZipCodeType	ZipCode;
	///�绰����
	TThostFtdcTelephoneType	Telephone;
	///�ֻ�
	TThostFtdcMobilePhoneType	MobilePhone;
	///����
	TThostFtdcFaxType	Fax;
	///�����ʼ�
	TThostFtdcEMailType	EMail;
	///�ʽ��˻�״̬
	TThostFtdcMoneyAccountStatusType	MoneyAccountStatus;
	///�����ʺ�
	TThostFtdcBankAccountType	BankAccount;
	///��������
	TThostFtdcPasswordType	BankPassWord;
	///Ͷ�����ʺ�
	TThostFtdcAccountIDType	AccountID;
	///�ڻ�����
	TThostFtdcPasswordType	Password;
	///��װ���
	TThostFtdcInstallIDType	InstallID;
	///��֤�ͻ�֤�������־
	TThostFtdcYesNoIndicatorType	VerifyCertNoFlag;
	///���ִ���
	TThostFtdcCurrencyIDType	CurrencyID;
	///�㳮��־
	TThostFtdcCashExchangeCodeType	CashExchangeCode;
	///ժҪ
	TThostFtdcDigestType	Digest;
	///�����ʺ�����
	TThostFtdcBankAccTypeType	BankAccType;
	///������־
	TThostFtdcDeviceIDType	DeviceID;
	///�ڻ���λ�ʺ�����
	TThostFtdcBankAccTypeType	BankSecuAccType;
	///�ڻ���˾���б���
	TThostFtdcBankCodingForFutureType	BrokerIDByBank;
	///�ڻ���λ�ʺ�
	TThostFtdcBankAccountType	BankSecuAcc;
	///���������־
	TThostFtdcPwdFlagType	BankPwdFlag;
	///�ڻ��ʽ�����˶Ա�־
	TThostFtdcPwdFlagType	SecuPwdFlag;
	///���׹�Ա
	TThostFtdcOperNoType	OperNo;
	///����ID
	TThostFtdcTIDType	TID;
	///�û���ʶ
	TThostFtdcUserIDType	UserID;
	///֤ȯ�ʽ��ճ����
	TThostFtdcTradeAmountType	SecDaBeBl;
	///����ת��ͨ��
	TThostFtdcBankChannelType	BankChal;
	///�������
	TThostFtdcErrorIDType	ErrorID;
	///������Ϣ
	TThostFtdcErrorMsgType	ErrorMsg;
};

///���ڱ�������˺���Ϣ
struct CThostFtdcChangeAccountField
{
	///ҵ������
	TThostFtdcTradeCodeType	TradeCode;
	///���д���
	TThostFtdcBankIDType	BankID;
	///���з�֧��������
	TThostFtdcBankBrchIDType	BankBranchID;
	///���̴���
	TThostFtdcBrokerIDType	BrokerID;
	///���̷�֧��������
	TThostFtdcFutureBranchIDType	BrokerBranchID;
	///��������
	TThostFtdcTradeDateType	TradeDate;
	///����ʱ��
	TThostFtdcTradeTimeType	TradeTime;
	///������ˮ��
	TThostFtdcBankSerialType	BankSerial;
	///����ϵͳ���� 
	TThostFtdcTradeDateType	TradingDay;
	///����ƽ̨��Ϣ��ˮ��
	TThostFtdcSerialType	PlateSerial;
	///����Ƭ��־
	TThostFtdcLastFragmentType	LastFragment;
	///�Ự��
	TThostFtdcSessionIDType	SessionID;
	///�ͻ�����
	TThostFtdcIndividualNameType	CustomerName;
	///֤������
	TThostFtdcIdCardTypeType	IdCardType;
	///֤������
	TThostFtdcIdentifiedCardNoType	IdentifiedCardNo;
	///�Ա�
	TThostFtdcGenderType	Gender;
	///���Ҵ���
	TThostFtdcCountryCodeType	CountryCode;
	///�ͻ�����
	TThostFtdcCustTypeType	CustType;
	///��ַ
	TThostFtdcAddressType	Address;
	///�ʱ�
	TThostFtdcZipCodeType	ZipCode;
	///�绰����
	TThostFtdcTelephoneType	Telephone;
	///�ֻ�
	TThostFtdcMobilePhoneType	MobilePhone;
	///����
	TThostFtdcFaxType	Fax;
	///�����ʼ�
	TThostFtdcEMailType	EMail;
	///�ʽ��˻�״̬
	TThostFtdcMoneyAccountStatusType	MoneyAccountStatus;
	///�����ʺ�
	TThostFtdcBankAccountType	BankAccount;
	///��������
	TThostFtdcPasswordType	BankPassWord;
	///�������ʺ�
	TThostFtdcBankAccountType	NewBankAccount;
	///����������
	TThostFtdcPasswordType	NewBankPassWord;
	///Ͷ�����ʺ�
	TThostFtdcAccountIDType	AccountID;
	///�ڻ�����
	TThostFtdcPasswordType	Password;
	///�����ʺ�����
	TThostFtdcBankAccTypeType	BankAccType;
	///��װ���
	TThostFtdcInstallIDType	InstallID;
	///��֤�ͻ�֤�������־
	TThostFtdcYesNoIndicatorType	VerifyCertNoFlag;
	///���ִ���
	TThostFtdcCurrencyIDType	CurrencyID;
	///�ڻ���˾���б���
	TThostFtdcBankCodingForFutureType	BrokerIDByBank;
	///���������־
	TThostFtdcPwdFlagType	BankPwdFlag;
	///�ڻ��ʽ�����˶Ա�־
	TThostFtdcPwdFlagType	SecuPwdFlag;
	///����ID
	TThostFtdcTIDType	TID;
	///ժҪ
	TThostFtdcDigestType	Digest;
	///�������
	TThostFtdcErrorIDType	ErrorID;
	///������Ϣ
	TThostFtdcErrorMsgType	ErrorMsg;
};

///�����������Ա����Ȩ��
struct CThostFtdcSecAgentACIDMapField
{
	///���͹�˾����
	TThostFtdcBrokerIDType	BrokerID;
	///�û�����
	TThostFtdcUserIDType	UserID;
	///�ʽ��˻�
	TThostFtdcAccountIDType	AccountID;
	///����
	TThostFtdcCurrencyIDType	CurrencyID;
	///�����н�����ʽ��ʺ�
	TThostFtdcAccountIDType	BrokerSecAgentID;
};

///�����������Ա����Ȩ�޲�ѯ
struct CThostFtdcQrySecAgentACIDMapField
{
	///���͹�˾����
	TThostFtdcBrokerIDType	BrokerID;
	///�û�����
	TThostFtdcUserIDType	UserID;
	///�ʽ��˻�
	TThostFtdcAccountIDType	AccountID;
	///����
	TThostFtdcCurrencyIDType	CurrencyID;
};

///�ֱ����Ľ���Ȩ��
struct CThostFtdcUserRightsAssignField
{
	///Ӧ�õ�Ԫ����
	TThostFtdcBrokerIDType	BrokerID;
	///�û�����
	TThostFtdcUserIDType	UserID;
	///�������Ĵ���
	TThostFtdcDRIdentityIDType	DRIdentityID;
};

///���ù�˾�Ƿ����ڱ���ʾ�Ľ���Ȩ��
struct CThostFtdcBrokerUserRightAssignField
{
	///Ӧ�õ�Ԫ����
	TThostFtdcBrokerIDType	BrokerID;
	///�������Ĵ���
	TThostFtdcDRIdentityIDType	DRIdentityID;
	///�ܷ���
	TThostFtdcBoolType	Tradeable;
};

///�ֱ�����ת������
struct CThostFtdcDRTransferField
{
	///ԭ�������Ĵ���
	TThostFtdcDRIdentityIDType	OrigDRIdentityID;
	///Ŀ�꽻�����Ĵ���
	TThostFtdcDRIdentityIDType	DestDRIdentityID;
	///ԭӦ�õ�Ԫ����
	TThostFtdcBrokerIDType	OrigBrokerID;
	///Ŀ�����õ�Ԫ����
	TThostFtdcBrokerIDType	DestBrokerID;
};

///Fens�û���Ϣ
struct CThostFtdcFensUserInfoField
{
	///���͹�˾����
	TThostFtdcBrokerIDType	BrokerID;
	///�û�����
	TThostFtdcUserIDType	UserID;
	///��¼ģʽ
	TThostFtdcLoginModeType	LoginMode;
};

///��ǰ����������������
struct CThostFtdcCurrTransferIdentityField
{
	///�������Ĵ���
	TThostFtdcDRIdentityIDType	IdentityID;
};

///��ֹ��¼�û�
struct CThostFtdcLoginForbiddenUserField
{
	///���͹�˾����
	TThostFtdcBrokerIDType	BrokerID;
	///�û�����
	TThostFtdcUserIDType	UserID;
	///��������Ч�ֶ�
	TThostFtdcOldIPAddressType	reserve1;
	///IP��ַ
	TThostFtdcIPAddressType	IPAddress;
};

///��ѯ��ֹ��¼�û�
struct CThostFtdcQryLoginForbiddenUserField
{
	///���͹�˾����
	TThostFtdcBrokerIDType	BrokerID;
	///�û�����
	TThostFtdcUserIDType	UserID;
};

///UDP�鲥����Ϣ
struct CThostFtdcMulticastGroupInfoField
{
	///�鲥��IP��ַ
	TThostFtdcIPAddressType	GroupIP;
	///�鲥��IP�˿�
	TThostFtdcIPPortType	GroupPort;
	///Դ��ַ
	TThostFtdcIPAddressType	SourceIP;
};

///�ʽ��˻�����׼����
struct CThostFtdcTradingAccountReserveField
{
	///���͹�˾����
	TThostFtdcBrokerIDType	BrokerID;
	///Ͷ�����ʺ�
	TThostFtdcAccountIDType	AccountID;
	///����׼����
	TThostFtdcMoneyType	Reserve;
	///���ִ���
	TThostFtdcCurrencyIDType	CurrencyID;
};

///��ѯ��ֹ��¼IP
struct CThostFtdcQryLoginForbiddenIPField
{
	///��������Ч�ֶ�
	TThostFtdcOldIPAddressType	reserve1;
	///IP��ַ
	TThostFtdcIPAddressType	IPAddress;
};

///��ѯIP�б�
struct CThostFtdcQryIPListField
{
	///��������Ч�ֶ�
	TThostFtdcOldIPAddressType	reserve1;
	///IP��ַ
	TThostFtdcIPAddressType	IPAddress;
};

///��ѯ�û��µ�Ȩ�޷����
struct CThostFtdcQryUserRightsAssignField
{
	///Ӧ�õ�Ԫ����
	TThostFtdcBrokerIDType	BrokerID;
	///�û�����
	TThostFtdcUserIDType	UserID;
};

///DBF��¼
struct CThostFtdcDBFRecordField
{
	///DBF��������
	TThostFtdcDBFComdTypeType	DBFComdType;
	///DBFʱ������
	TThostFtdcDBFComTimeType	DBFComTime;
	///DBFԭʼ��ˮ������
	TThostFtdcDBFComNoType	DBFOComNo;
	///DBF��ˮ������
	TThostFtdcDBFComNoType	DBFComNo;
	///DBF�ֶ�����
	TThostFtdcDBFFdNameType	DBFFdName1;
	///DBF�ֶ���������
	TThostFtdcDBFFdContentType	DBFFdContent1;
	///DBF�ֶ�����
	TThostFtdcDBFFdNameType	DBFFdName2;
	///DBF�ֶ���������
	TThostFtdcDBFFdContentType	DBFFdContent2;
	///DBF�ֶ�����
	TThostFtdcDBFFdNameType	DBFFdName3;
	///DBF�ֶ���������
	TThostFtdcDBFFdContentType	DBFFdContent3;
	///DBF�ֶ�����
	TThostFtdcDBFFdNameType	DBFFdName4;
	///DBF�ֶ���������
	TThostFtdcDBFFdContentType	DBFFdContent4;
};

///�����˻�����
struct CThostFtdcAccountPropertyField
{
	///���͹�˾����
	TThostFtdcBrokerIDType	BrokerID;
	///Ͷ�����ʺ�
	TThostFtdcAccountIDType	AccountID;
	///����ͳһ��ʶ����
	TThostFtdcBankIDType	BankID;
	///�����˻�
	TThostFtdcBankAccountType	BankAccount;
	///�����˻��Ŀ���������
	TThostFtdcInvestorFullNameType	OpenName;
	///�����˻��Ŀ�����
	TThostFtdcOpenBankType	OpenBank;
	///�Ƿ��Ծ
	TThostFtdcBoolType	IsActive;
	///�˻���Դ
	TThostFtdcAccountSourceTypeType	AccountSourceType;
	///��������
	TThostFtdcDateType	OpenDate;
	///ע������
	TThostFtdcDateType	CancelDate;
	///¼��Ա����
	TThostFtdcOperatorIDType	OperatorID;
	///¼������
	TThostFtdcDateType	OperateDate;
	///¼��ʱ��
	TThostFtdcTimeType	OperateTime;
	///���ִ���
	TThostFtdcCurrencyIDType	CurrencyID;
};

///��ѯ��ǰ��������
struct CThostFtdcQryCurrDRIdentityField
{
	///�������Ĵ���
	TThostFtdcDRIdentityIDType	DRIdentityID;
};

///��ǰ��������
struct CThostFtdcCurrDRIdentityField
{
	///�������Ĵ���
	TThostFtdcDRIdentityIDType	DRIdentityID;
};

///���������ҵ�񿪻�Ԥָ������
struct CThostFtdcReqReserveOpenAccountTpdField
{
	///ҵ������
	TThostFtdcTradeCodeType	TradeCode;
	///���д���
	TThostFtdcBankIDType	BankID;
	///���з�֧��������
	TThostFtdcBankBrchIDType	BankBranchID;
	///���̴���
	TThostFtdcBrokerIDType	BrokerID;
	///���̷�֧��������
	TThostFtdcFutureBranchIDType	BrokerBranchID;
	///��������
	TThostFtdcTradeDateType	TradeDate;
	///����ʱ��
	TThostFtdcTradeTimeType	TradeTime;
	///������ˮ��
	TThostFtdcBankSerialType	BankSerial;
	///����ϵͳ���� 
	TThostFtdcTradeDateType	TradingDay;
	///����ƽ̨��Ϣ��ˮ��
	TThostFtdcSerialType	PlateSerial;
	///����Ƭ��־
	TThostFtdcLastFragmentType	LastFragment;
	///�Ự��
	TThostFtdcSessionIDType	SessionID;
	///�ͻ�����
	TThostFtdcIndividualNameType	CustomerName;
	///֤������
	TThostFtdcIdCardTypeType	IdCardType;
	///֤������
	TThostFtdcIdentifiedCardNoType	IdentifiedCardNo;
	///�Ա�
	TThostFtdcGenderType	Gender;
	///���Ҵ���
	TThostFtdcCountryCodeType	CountryCode;
	///�ͻ�����
	TThostFtdcCustTypeType	CustType;
	///��ַ
	TThostFtdcAddressType	Address;
	///�ʱ�
	TThostFtdcZipCodeType	ZipCode;
	///�绰����
	TThostFtdcTelephoneType	Telephone;
	///�ֻ�
	TThostFtdcMobilePhoneType	MobilePhone;
	///����
	TThostFtdcFaxType	Fax;
	///�����ʼ�
	TThostFtdcEMailType	EMail;
	///�ʽ��˻�״̬
	TThostFtdcMoneyAccountStatusType	MoneyAccountStatus;
	///�����ʺ�
	TThostFtdcBankAccountType	BankAccount;
	///��������
	TThostFtdcPasswordType	BankPassWord;
	///Ͷ�����ʺ�
	TThostFtdcAccountIDType	AccountID;
	///�ڻ�����
	TThostFtdcPasswordType	Password;
	///��װ���
	TThostFtdcInstallIDType	InstallID;
	///��֤�ͻ�֤�������־
	TThostFtdcYesNoIndicatorType	VerifyCertNoFlag;
	///���ִ���
	TThostFtdcCurrencyIDType	CurrencyID;
	///�㳮��־
	TThostFtdcCashExchangeCodeType	CashExchangeCode;
	///ժҪ
	TThostFtdcDigestType	Digest;
	///�����ʺ�����
	TThostFtdcBankAccTypeType	BankAccType;
	///������־
	TThostFtdcDeviceIDType	DeviceID;
	///�ڻ���λ�ʺ�����
	TThostFtdcBankAccTypeType	BankSecuAccType;
	///�ڻ���˾���б���
	TThostFtdcBankCodingForFutureType	BrokerIDByBank;
	///�ڻ���λ�ʺ�
	TThostFtdcBankAccountType	BankSecuAcc;
	///���������־
	TThostFtdcPwdFlagType	BankPwdFlag;
	///�ڻ��ʽ�����˶Ա�־
	TThostFtdcPwdFlagType	SecuPwdFlag;
	///���׹�Ա
	TThostFtdcOperNoType	OperNo;
	///����ID
	TThostFtdcTIDType	TID;
	///�û���ʶ
	TThostFtdcUserIDType	UserID;
	///֤ȯ�ʽ��ճ����
	TThostFtdcTradeAmountType	SecDaBeBl;
	///����ת��ͨ��
	TThostFtdcBankChannelType	BankChal;
};

///���������ҵ�񿪻�Ԥָ��
struct CThostFtdcReserveOpenAccountTpdField
{
	///ҵ������
	TThostFtdcTradeCodeType	TradeCode;
	///���д���
	TThostFtdcBankIDType	BankID;
	///���з�֧��������
	TThostFtdcBankBrchIDType	BankBranchID;
	///���̴���
	TThostFtdcBrokerIDType	BrokerID;
	///���̷�֧��������
	TThostFtdcFutureBranchIDType	BrokerBranchID;
	///��������
	TThostFtdcTradeDateType	TradeDate;
	///����ʱ��
	TThostFtdcTradeTimeType	TradeTime;
	///������ˮ��
	TThostFtdcBankSerialType	BankSerial;
	///����ϵͳ���� 
	TThostFtdcTradeDateType	TradingDay;
	///����ƽ̨��Ϣ��ˮ��
	TThostFtdcSerialType	PlateSerial;
	///����Ƭ��־
	TThostFtdcLastFragmentType	LastFragment;
	///�Ự��
	TThostFtdcSessionIDType	SessionID;
	///�ͻ�����
	TThostFtdcIndividualNameType	CustomerName;
	///֤������
	TThostFtdcIdCardTypeType	IdCardType;
	///֤������
	TThostFtdcIdentifiedCardNoType	IdentifiedCardNo;
	///�Ա�
	TThostFtdcGenderType	Gender;
	///���Ҵ���
	TThostFtdcCountryCodeType	CountryCode;
	///�ͻ�����
	TThostFtdcCustTypeType	CustType;
	///��ַ
	TThostFtdcAddressType	Address;
	///�ʱ�
	TThostFtdcZipCodeType	ZipCode;
	///�绰����
	TThostFtdcTelephoneType	Telephone;
	///�ֻ�
	TThostFtdcMobilePhoneType	MobilePhone;
	///����
	TThostFtdcFaxType	Fax;
	///�����ʼ�
	TThostFtdcEMailType	EMail;
	///�ʽ��˻�״̬
	TThostFtdcMoneyAccountStatusType	MoneyAccountStatus;
	///�����ʺ�
	TThostFtdcBankAccountType	BankAccount;
	///��������
	TThostFtdcPasswordType	BankPassWord;
	///Ͷ�����ʺ�
	TThostFtdcAccountIDType	AccountID;
	///�ڻ�����
	TThostFtdcPasswordType	Password;
	///��װ���
	TThostFtdcInstallIDType	InstallID;
	///��֤�ͻ�֤�������־
	TThostFtdcYesNoIndicatorType	VerifyCertNoFlag;
	///���ִ���
	TThostFtdcCurrencyIDType	CurrencyID;
	///�㳮��־
	TThostFtdcCashExchangeCodeType	CashExchangeCode;
	///ժҪ
	TThostFtdcDigestType	Digest;
	///�����ʺ�����
	TThostFtdcBankAccTypeType	BankAccType;
	///������־
	TThostFtdcDeviceIDType	DeviceID;
	///�ڻ���λ�ʺ�����
	TThostFtdcBankAccTypeType	BankSecuAccType;
	///�ڻ���˾���б���
	TThostFtdcBankCodingForFutureType	BrokerIDByBank;
	///�ڻ���λ�ʺ�
	TThostFtdcBankAccountType	BankSecuAcc;
	///���������־
	TThostFtdcPwdFlagType	BankPwdFlag;
	///�ڻ��ʽ�����˶Ա�־
	TThostFtdcPwdFlagType	SecuPwdFlag;
	///���׹�Ա
	TThostFtdcOperNoType	OperNo;
	///����ID
	TThostFtdcTIDType	TID;
	///�û���ʶ
	TThostFtdcUserIDType	UserID;
	///֤ȯ�ʽ��ճ����
	TThostFtdcTradeAmountType	SecDaBeBl;
	///����ת��ͨ��
	TThostFtdcBankChannelType	BankChal;
	///ԤԼ����״̬
	TThostFtdcReserveOpenAccStasType	ReserveOpenAccStas;
	///�������
	TThostFtdcErrorIDType	ErrorID;
	///������Ϣ
	TThostFtdcErrorMsgType	ErrorMsg;
};

///���������ҵ�񿪻�ȷ������
struct CThostFtdcReqResOpenAccConfirmTpdField
{
	///ҵ������
	TThostFtdcTradeCodeType	TradeCode;
	///���д���
	TThostFtdcBankIDType	BankID;
	///���з�֧��������
	TThostFtdcBankBrchIDType	BankBranchID;
	///���̴���
	TThostFtdcBrokerIDType	BrokerID;
	///���̷�֧��������
	TThostFtdcFutureBranchIDType	BrokerBranchID;
	///��������
	TThostFtdcTradeDateType	TradeDate;
	///����ʱ��
	TThostFtdcTradeTimeType	TradeTime;
	///������ˮ��
	TThostFtdcBankSerialType	BankSerial;
	///����ϵͳ���� 
	TThostFtdcTradeDateType	TradingDay;
	///����ƽ̨��Ϣ��ˮ��
	TThostFtdcSerialType	PlateSerial;
	///����Ƭ��־
	TThostFtdcLastFragmentType	LastFragment;
	///�Ự��
	TThostFtdcSessionIDType	SessionID;
	///�ͻ�����
	TThostFtdcIndividualNameType	CustomerName;
	///֤������
	TThostFtdcIdCardTypeType	IdCardType;
	///֤������
	TThostFtdcIdentifiedCardNoType	IdentifiedCardNo;
	///�Ա�
	TThostFtdcGenderType	Gender;
	///���Ҵ���
	TThostFtdcCountryCodeType	CountryCode;
	///�ͻ�����
	TThostFtdcCustTypeType	CustType;
	///��ַ
	TThostFtdcAddressType	Address;
	///�ʱ�
	TThostFtdcZipCodeType	ZipCode;
	///�绰����
	TThostFtdcTelephoneType	Telephone;
	///�ֻ�
	TThostFtdcMobilePhoneType	MobilePhone;
	///����
	TThostFtdcFaxType	Fax;
	///�����ʼ�
	TThostFtdcEMailType	EMail;
	///�ʽ��˻�״̬
	TThostFtdcMoneyAccountStatusType	MoneyAccountStatus;
	///�����ʺ�
	TThostFtdcBankAccountType	BankAccount;
	///��������
	TThostFtdcPasswordType	BankPassWord;
	///Ͷ�����ʺ�
	TThostFtdcAccountIDType	AccountID;
	///�ڻ�����
	TThostFtdcPasswordType	Password;
	///�����ʺ�����
	TThostFtdcBankAccTypeType	BankAccType;
	///��װ���
	TThostFtdcInstallIDType	InstallID;
	///��֤�ͻ�֤�������־
	TThostFtdcYesNoIndicatorType	VerifyCertNoFlag;
	///���ִ���
	TThostFtdcCurrencyIDType	CurrencyID;
	///�㳮��־
	TThostFtdcCashExchangeCodeType	CashExchangeCode;
	///�ڻ���˾���б���
	TThostFtdcBankCodingForFutureType	BrokerIDByBank;
	///�ڻ���λ�ʺ�����
	TThostFtdcBankAccTypeType	BankSecuAccType;
	///�ڻ���λ�ʺ�
	TThostFtdcBankAccountType	BankSecuAcc;
	///���������־
	TThostFtdcPwdFlagType	BankPwdFlag;
	///�ڻ��ʽ�����˶Ա�־
	TThostFtdcPwdFlagType	SecuPwdFlag;
	///������־
	TThostFtdcDeviceIDType	DeviceID;
	///���׹�Ա
	TThostFtdcOperNoType	OperNo;
	///�û���ʶ
	TThostFtdcUserIDType	UserID;
	///����ID
	TThostFtdcTIDType	TID;
	///ժҪ
	TThostFtdcDigestType	Digest;
};

///���������ҵ�񿪻�ȷ��
struct CThostFtdcResOpenAccConfirmTpdField
{
	///ҵ������
	TThostFtdcTradeCodeType	TradeCode;
	///���д���
	TThostFtdcBankIDType	BankID;
	///���з�֧��������
	TThostFtdcBankBrchIDType	BankBranchID;
	///���̴���
	TThostFtdcBrokerIDType	BrokerID;
	///���̷�֧��������
	TThostFtdcFutureBranchIDType	BrokerBranchID;
	///��������
	TThostFtdcTradeDateType	TradeDate;
	///����ʱ��
	TThostFtdcTradeTimeType	TradeTime;
	///������ˮ��
	TThostFtdcBankSerialType	BankSerial;
	///����ϵͳ���� 
	TThostFtdcTradeDateType	TradingDay;
	///����ƽ̨��Ϣ��ˮ��
	TThostFtdcSerialType	PlateSerial;
	///����Ƭ��־
	TThostFtdcLastFragmentType	LastFragment;
	///�Ự��
	TThostFtdcSessionIDType	SessionID;
	///�ͻ�����
	TThostFtdcIndividualNameType	CustomerName;
	///֤������
	TThostFtdcIdCardTypeType	IdCardType;
	///֤������
	TThostFtdcIdentifiedCardNoType	IdentifiedCardNo;
	///�Ա�
	TThostFtdcGenderType	Gender;
	///���Ҵ���
	TThostFtdcCountryCodeType	CountryCode;
	///�ͻ�����
	TThostFtdcCustTypeType	CustType;
	///��ַ
	TThostFtdcAddressType	Address;
	///�ʱ�
	TThostFtdcZipCodeType	ZipCode;
	///�绰����
	TThostFtdcTelephoneType	Telephone;
	///�ֻ�
	TThostFtdcMobilePhoneType	MobilePhone;
	///����
	TThostFtdcFaxType	Fax;
	///�����ʼ�
	TThostFtdcEMailType	EMail;
	///�ʽ��˻�״̬
	TThostFtdcMoneyAccountStatusType	MoneyAccountStatus;
	///�����ʺ�
	TThostFtdcBankAccountType	BankAccount;
	///��������
	TThostFtdcPasswordType	BankPassWord;
	///Ͷ�����ʺ�
	TThostFtdcAccountIDType	AccountID;
	///�ڻ�����
	TThostFtdcPasswordType	Password;
	///�����ʺ�����
	TThostFtdcBankAccTypeType	BankAccType;
	///��װ���
	TThostFtdcInstallIDType	InstallID;
	///��֤�ͻ�֤�������־
	TThostFtdcYesNoIndicatorType	VerifyCertNoFlag;
	///���ִ���
	TThostFtdcCurrencyIDType	CurrencyID;
	///�㳮��־
	TThostFtdcCashExchangeCodeType	CashExchangeCode;
	///�ڻ���˾���б���
	TThostFtdcBankCodingForFutureType	BrokerIDByBank;
	///�ڻ���λ�ʺ�����
	TThostFtdcBankAccTypeType	BankSecuAccType;
	///�ڻ���λ�ʺ�
	TThostFtdcBankAccountType	BankSecuAcc;
	///���������־
	TThostFtdcPwdFlagType	BankPwdFlag;
	///�ڻ��ʽ�����˶Ա�־
	TThostFtdcPwdFlagType	SecuPwdFlag;
	///������־
	TThostFtdcDeviceIDType	DeviceID;
	///���׹�Ա
	TThostFtdcOperNoType	OperNo;
	///�û���ʶ
	TThostFtdcUserIDType	UserID;
	///����ID
	TThostFtdcTIDType	TID;
	///ժҪ
	TThostFtdcDigestType	Digest;
	///�������
	TThostFtdcErrorIDType	ErrorID;
	///������Ϣ
	TThostFtdcErrorMsgType	ErrorMsg;
};

///���������֤ȯ�ʽ��Ϣ����
struct CThostFtdcReqSecuritiesDepositInterestField
{
	///ҵ������
	TThostFtdcTradeCodeType	TradeCode;
	///���д���
	TThostFtdcBankIDType	BankID;
	///���з�֧��������
	TThostFtdcBankBrchIDType	BankBranchID;
	///���̴���
	TThostFtdcBrokerIDType	BrokerID;
	///���̷�֧��������
	TThostFtdcFutureBranchIDType	BrokerBranchID;
	///��������
	TThostFtdcTradeDateType	TradeDate;
	///����ʱ��
	TThostFtdcTradeTimeType	TradeTime;
	///������ˮ��
	TThostFtdcBankSerialType	BankSerial;
	///����ϵͳ���� 
	TThostFtdcTradeDateType	TradingDay;
	///����ƽ̨��Ϣ��ˮ��
	TThostFtdcSerialType	PlateSerial;
	///����Ƭ��־
	TThostFtdcLastFragmentType	LastFragment;
	///�Ự��
	TThostFtdcSessionIDType	SessionID;
	///�ͻ�����
	TThostFtdcIndividualNameType	CustomerName;
	///֤������
	TThostFtdcIdCardTypeType	IdCardType;
	///֤������
	TThostFtdcIdentifiedCardNoType	IdentifiedCardNo;
	///�Ա�
	TThostFtdcGenderType	Gender;
	///���Ҵ���
	TThostFtdcCountryCodeType	CountryCode;
	///�ͻ�����
	TThostFtdcCustTypeType	CustType;
	///��ַ
	TThostFtdcAddressType	Address;
	///�ʱ�
	TThostFtdcZipCodeType	ZipCode;
	///�绰����
	TThostFtdcTelephoneType	Telephone;
	///�ֻ�
	TThostFtdcMobilePhoneType	MobilePhone;
	///����
	TThostFtdcFaxType	Fax;
	///�����ʼ�
	TThostFtdcEMailType	EMail;
	///�ʽ��˻�״̬
	TThostFtdcMoneyAccountStatusType	MoneyAccountStatus;
	///�����ʺ�
	TThostFtdcBankAccountType	BankAccount;
	///��������
	TThostFtdcPasswordType	BankPassWord;
	///Ͷ�����ʺ�
	TThostFtdcAccountIDType	AccountID;
	///�ڻ�����
	TThostFtdcPasswordType	Password;
	///��װ���
	TThostFtdcInstallIDType	InstallID;
	///�ڻ���˾��ˮ��
	TThostFtdcFutureSerialType	FutureSerial;
	///��֤�ͻ�֤�������־
	TThostFtdcYesNoIndicatorType	VerifyCertNoFlag;
	///���ִ���
	TThostFtdcCurrencyIDType	CurrencyID;
	///�㳮��־
	TThostFtdcCashExchangeCodeType	CashExchangeCode;
	///ժҪ
	TThostFtdcDigestType	Digest;
	///�����ʺ�����
	TThostFtdcBankAccTypeType	BankAccType;
	///������־
	TThostFtdcDeviceIDType	DeviceID;
	///�ڻ���λ�ʺ�����
	TThostFtdcBankAccTypeType	BankSecuAccType;
	///�ڻ���˾���б���
	TThostFtdcBankCodingForFutureType	BrokerIDByBank;
	///�ڻ���λ�ʺ�
	TThostFtdcBankAccountType	BankSecuAcc;
	///���������־
	TThostFtdcPwdFlagType	BankPwdFlag;
	///�ڻ��ʽ�����˶Ա�־
	TThostFtdcPwdFlagType	SecuPwdFlag;
	///���׹�Ա
	TThostFtdcOperNoType	OperNo;
	///����ID
	TThostFtdcTIDType	TID;
	///�û���ʶ
	TThostFtdcUserIDType	UserID;
	///��Ϣ����
	TThostFtdcTradeAmountType	DepositInterest;
};

///���������֤ȯ�ʽ��Ϣ
struct CThostFtdcSecuritiesDepositInterestField
{
	///ҵ������
	TThostFtdcTradeCodeType	TradeCode;
	///���д���
	TThostFtdcBankIDType	BankID;
	///���з�֧��������
	TThostFtdcBankBrchIDType	BankBranchID;
	///���̴���
	TThostFtdcBrokerIDType	BrokerID;
	///���̷�֧��������
	TThostFtdcFutureBranchIDType	BrokerBranchID;
	///��������
	TThostFtdcTradeDateType	TradeDate;
	///����ʱ��
	TThostFtdcTradeTimeType	TradeTime;
	///������ˮ��
	TThostFtdcBankSerialType	BankSerial;
	///����ϵͳ���� 
	TThostFtdcTradeDateType	TradingDay;
	///����ƽ̨��Ϣ��ˮ��
	TThostFtdcSerialType	PlateSerial;
	///����Ƭ��־
	TThostFtdcLastFragmentType	LastFragment;
	///�Ự��
	TThostFtdcSessionIDType	SessionID;
	///�ͻ�����
	TThostFtdcIndividualNameType	CustomerName;
	///֤������
	TThostFtdcIdCardTypeType	IdCardType;
	///֤������
	TThostFtdcIdentifiedCardNoType	IdentifiedCardNo;
	///�Ա�
	TThostFtdcGenderType	Gender;
	///���Ҵ���
	TThostFtdcCountryCodeType	CountryCode;
	///�ͻ�����
	TThostFtdcCustTypeType	CustType;
	///��ַ
	TThostFtdcAddressType	Address;
	///�ʱ�
	TThostFtdcZipCodeType	ZipCode;
	///�绰����
	TThostFtdcTelephoneType	Telephone;
	///�ֻ�
	TThostFtdcMobilePhoneType	MobilePhone;
	///����
	TThostFtdcFaxType	Fax;
	///�����ʼ�
	TThostFtdcEMailType	EMail;
	///�ʽ��˻�״̬
	TThostFtdcMoneyAccountStatusType	MoneyAccountStatus;
	///�����ʺ�
	TThostFtdcBankAccountType	BankAccount;
	///��������
	TThostFtdcPasswordType	BankPassWord;
	///Ͷ�����ʺ�
	TThostFtdcAccountIDType	AccountID;
	///�ڻ�����
	TThostFtdcPasswordType	Password;
	///��װ���
	TThostFtdcInstallIDType	InstallID;
	///�ڻ���˾��ˮ��
	TThostFtdcFutureSerialType	FutureSerial;
	///��֤�ͻ�֤�������־
	TThostFtdcYesNoIndicatorType	VerifyCertNoFlag;
	///���ִ���
	TThostFtdcCurrencyIDType	CurrencyID;
	///�㳮��־
	TThostFtdcCashExchangeCodeType	CashExchangeCode;
	///ժҪ
	TThostFtdcDigestType	Digest;
	///�����ʺ�����
	TThostFtdcBankAccTypeType	BankAccType;
	///������־
	TThostFtdcDeviceIDType	DeviceID;
	///�ڻ���λ�ʺ�����
	TThostFtdcBankAccTypeType	BankSecuAccType;
	///�ڻ���˾���б���
	TThostFtdcBankCodingForFutureType	BrokerIDByBank;
	///�ڻ���λ�ʺ�
	TThostFtdcBankAccountType	BankSecuAcc;
	///���������־
	TThostFtdcPwdFlagType	BankPwdFlag;
	///�ڻ��ʽ�����˶Ա�־
	TThostFtdcPwdFlagType	SecuPwdFlag;
	///���׹�Ա
	TThostFtdcOperNoType	OperNo;
	///����ID
	TThostFtdcTIDType	TID;
	///�û���ʶ
	TThostFtdcUserIDType	UserID;
	///��Ϣ����
	TThostFtdcTradeAmountType	DepositInterest;
	///��Ϣ����
	TThostFtdcSFInterestTypeType	InterestType;
	///�������
	TThostFtdcErrorIDType	ErrorID;
	///������Ϣ
	TThostFtdcErrorMsgType	ErrorMsg;
};

///���͹�˾�ǽ���ʱ���
struct CThostFtdcBrokerBreakSectionField
{
	///����������
	TThostFtdcExchangeIDType	ExchangeID;
	///���͹�˾����
	TThostFtdcBrokerIDType	BrokerID;
	///��ʼʱ��
	TThostFtdcTimeType	TimeStart;
	///����ʱ��
	TThostFtdcTimeType	TimeEnd;
	///���
	TThostFtdcSequenceNoType	SequenceNo;
};

///���͹�˾�����ͻ���ȯ
struct CThostFtdcBrokerLockInvestorStockField
{
	///����������
	TThostFtdcExchangeIDType	ExchangeID;
	///���͹�˾����
	TThostFtdcBrokerIDType	BrokerID;
	///Ͷ���ߴ���
	TThostFtdcInvestorIDType	InvestorID;
	///��ĺ�Լ����
	TThostFtdcInstrumentIDType	InstrumentID;
	///����
	TThostFtdcVolumeType	Volume;
};

///��ѯ���͹�˾�����ͻ���ȯ
struct CThostFtdcQryBrokerLockInvestorStockField
{
	///����������
	TThostFtdcExchangeIDType	ExchangeID;
	///���͹�˾����
	TThostFtdcBrokerIDType	BrokerID;
	///Ͷ���ߴ���
	TThostFtdcInvestorIDType	InvestorID;
	///��Լ����
	TThostFtdcInstrumentIDType	InstrumentID;
};

///��Ȩʱ�Ƿ�������ȯ
struct CThostFtdcExecIsCheckUnderlyingField
{
	///����������
	TThostFtdcExchangeIDType	ExchangeID;
	///������Ʒ����
	TThostFtdcInstrumentIDType	UnderlyingInstrID;
	///�Ƿ���
	TThostFtdcBoolType	IsCheck;
};

///��ѯ��Ȩʱ�Ƿ�������ȯ
struct CThostFtdcQryExecIsCheckUnderlyingField
{
	///����������
	TThostFtdcExchangeIDType	ExchangeID;
	///������Ʒ����
	TThostFtdcInstrumentIDType	UnderlyingInstrID;
};

///Ͷ������PBUָ����ϵ
struct CThostFtdcPBUInvestorMapField
{
	///���͹�˾����
	TThostFtdcBrokerIDType	BrokerID;
	///����������
	TThostFtdcExchangeIDType	ExchangeID;
	///Ͷ���ߴ���
	TThostFtdcInvestorIDType	InvestorID;
	///ָ�����׵�Ԫ��
	TThostFtdcTraderIDType	PBU;
	///֤ȯ�˻�
	TThostFtdcClientIDType	ClientID;
	///����
	TThostFtdcDateType	OperationDate;
	///ʱ��
	TThostFtdcTimeType	OperationTime;
};

///�������Ȩָ��ϲ�
struct CThostFtdcInputExecCombineOrderField
{
	///���͹�˾����
	TThostFtdcBrokerIDType	BrokerID;
	///Ͷ���ߴ���
	TThostFtdcInvestorIDType	InvestorID;
	///���Ǻ�Լ����
	TThostFtdcInstrumentIDType	CallInstrumentID;
	///������Լ����
	TThostFtdcInstrumentIDType	PutInstrumentID;
	///ִ������ϲ�����
	TThostFtdcOrderRefType	ExecCombineOrderRef;
	///�û�����
	TThostFtdcUserIDType	UserID;
	///����
	TThostFtdcVolumeType	Volume;
	///������
	TThostFtdcRequestIDType	RequestID;
	///ҵ��Ԫ
	TThostFtdcBusinessUnitType	BusinessUnit;
	///ִ������
	TThostFtdcActionTypeType	ActionType;
	///����������
	TThostFtdcExchangeIDType	ExchangeID;
	///Ͷ�ʵ�Ԫ����
	TThostFtdcInvestUnitIDType	InvestUnitID;
	///���ױ���
	TThostFtdcClientIDType	ClientID;
	///��������Ч�ֶ�
	TThostFtdcOldIPAddressType	reserve1;
	///Mac��ַ
	TThostFtdcMacAddressType	MacAddress;
	///IP��ַ
	TThostFtdcIPAddressType	IPAddress;
};

///������Ȩָ��ϲ�����
struct CThostFtdcInputExecCombineOrderActionField
{
	///���͹�˾����
	TThostFtdcBrokerIDType	BrokerID;
	///Ͷ���ߴ���
	TThostFtdcInvestorIDType	InvestorID;
	///ִ������ϲ���������
	TThostFtdcOrderActionRefType	ExecCombineOrderActionRef;
	///ִ������ϲ�����
	TThostFtdcOrderRefType	ExecCombineOrderRef;
	///������
	TThostFtdcRequestIDType	RequestID;
	///ǰ�ñ��
	TThostFtdcFrontIDType	FrontID;
	///�Ự���
	TThostFtdcSessionIDType	SessionID;
	///����������
	TThostFtdcExchangeIDType	ExchangeID;
	///ִ������ϲ��������
	TThostFtdcExecOrderSysIDType	ExecCombineOrderSysID;
	///������־
	TThostFtdcActionFlagType	ActionFlag;
	///�û�����
	TThostFtdcUserIDType	UserID;
	///Ͷ�ʵ�Ԫ����
	TThostFtdcInvestUnitIDType	InvestUnitID;
	///��������Ч�ֶ�
	TThostFtdcOldIPAddressType	reserve1;
	///Mac��ַ
	TThostFtdcMacAddressType	MacAddress;
	///IP��ַ
	TThostFtdcIPAddressType	IPAddress;
};

///��Ȩָ��ϲ�
struct CThostFtdcExecCombineOrderField
{
	///���͹�˾����
	TThostFtdcBrokerIDType	BrokerID;
	///Ͷ���ߴ���
	TThostFtdcInvestorIDType	InvestorID;
	///���Ǻ�Լ����
	TThostFtdcInstrumentIDType	CallInstrumentID;
	///������Լ����
	TThostFtdcInstrumentIDType	PutInstrumentID;
	///ִ������ϲ�����
	TThostFtdcOrderRefType	ExecCombineOrderRef;
	///�û�����
	TThostFtdcUserIDType	UserID;
	///����
	TThostFtdcVolumeType	Volume;
	///������
	TThostFtdcRequestIDType	RequestID;
	///ҵ��Ԫ
	TThostFtdcBusinessUnitType	BusinessUnit;
	///ִ������
	TThostFtdcActionTypeType	ActionType;
	///����ִ������ϲ����
	TThostFtdcOrderLocalIDType	ExecCombineOrderLocalID;
	///����������
	TThostFtdcExchangeIDType	ExchangeID;
	///��Ա����
	TThostFtdcParticipantIDType	ParticipantID;
	///�ͻ�����
	TThostFtdcClientIDType	ClientID;
	///��ĺ�Լ�ڽ������Ĵ���
	TThostFtdcExchangeInstIDType	UnderlyingInstrID;
	///���Ǻ�Լ�ڽ������Ĵ���
	TThostFtdcExchangeInstIDType	ExchangeCallInstID;
	///������Լ�ڽ������Ĵ���
	TThostFtdcExchangeInstIDType	ExchangePutInstID;
	///����������Ա����
	TThostFtdcTraderIDType	TraderID;
	///��װ���
	TThostFtdcInstallIDType	InstallID;
	///ִ������ϲ��ύ״̬
	TThostFtdcOrderSubmitStatusType	OrderSubmitStatus;
	///������ʾ���
	TThostFtdcSequenceNoType	NotifySequence;
	///������
	TThostFtdcDateType	TradingDay;
	///������
	TThostFtdcSettlementIDType	SettlementID;
	///ִ������ϲ����
	TThostFtdcExecOrderSysIDType	ExecCombineOrderSysID;
	///��������
	TThostFtdcDateType	InsertDate;
	///����ʱ��
	TThostFtdcTimeType	InsertTime;
	///����ʱ��
	TThostFtdcTimeType	CancelTime;
	///ִ�н��
	TThostFtdcExecResultType	ExecResult;
	///�����Ա���
	TThostFtdcParticipantIDType	ClearingPartID;
	///���
	TThostFtdcSequenceNoType	SequenceNo;
	///ǰ�ñ��
	TThostFtdcFrontIDType	FrontID;
	///�Ự���
	TThostFtdcSessionIDType	SessionID;
	///�û��˲�Ʒ��Ϣ
	TThostFtdcProductInfoType	UserProductInfo;
	///״̬��Ϣ
	TThostFtdcErrorMsgType	StatusMsg;
	///�����û�����
	TThostFtdcUserIDType	ActiveUserID;
	///���͹�˾�������
	TThostFtdcSequenceNoType	BrokerExecCombineOrderSeq;
	///Ӫҵ�����
	TThostFtdcBranchIDType	BranchID;
	///Ͷ�ʵ�Ԫ����
	TThostFtdcInvestUnitIDType	InvestUnitID;
	///�ʽ��˺�
	TThostFtdcAccountIDType	AccountID;
	///���ִ���
	TThostFtdcCurrencyIDType	CurrencyID;
	///��������Ч�ֶ�
	TThostFtdcOldIPAddressType	reserve1;
	///Mac��ַ
	TThostFtdcMacAddressType	MacAddress;
	///����������
	TThostFtdcOwnerTypeType	OwnerType;
	///��½PBU
	TThostFtdcTraderIDType	LoginPBU;
	///IP��ַ
	TThostFtdcIPAddressType	IPAddress;
};

///��Ȩָ��ϲ�����
struct CThostFtdcExecCombineOrderActionField
{
	///���͹�˾����
	TThostFtdcBrokerIDType	BrokerID;
	///Ͷ���ߴ���
	TThostFtdcInvestorIDType	InvestorID;
	///ִ������ϲ���������
	TThostFtdcOrderActionRefType	ExecCombineOrderActionRef;
	///ִ������ϲ�����
	TThostFtdcOrderRefType	ExecCombineOrderRef;
	///������
	TThostFtdcRequestIDType	RequestID;
	///ǰ�ñ��
	TThostFtdcFrontIDType	FrontID;
	///�Ự���
	TThostFtdcSessionIDType	SessionID;
	///����������
	TThostFtdcExchangeIDType	ExchangeID;
	///ִ������ϲ��������
	TThostFtdcExecOrderSysIDType	ExecCombineOrderSysID;
	///������־
	TThostFtdcActionFlagType	ActionFlag;
	///��������
	TThostFtdcDateType	ActionDate;
	///����ʱ��
	TThostFtdcTimeType	ActionTime;
	///����������Ա����
	TThostFtdcTraderIDType	TraderID;
	///��װ���
	TThostFtdcInstallIDType	InstallID;
	///����ִ������ϲ����
	TThostFtdcOrderLocalIDType	ExecCombineOrderLocalID;
	///�������ر��
	TThostFtdcOrderLocalIDType	ActionLocalID;
	///��Ա����
	TThostFtdcParticipantIDType	ParticipantID;
	///�ͻ�����
	TThostFtdcClientIDType	ClientID;
	///ҵ��Ԫ
	TThostFtdcBusinessUnitType	BusinessUnit;
	///��������״̬
	TThostFtdcOrderActionStatusType	OrderActionStatus;
	///�û�����
	TThostFtdcUserIDType	UserID;
	///ִ������
	TThostFtdcActionTypeType	ActionType;
	///״̬��Ϣ
	TThostFtdcErrorMsgType	StatusMsg;
	///���Ǻ�Լ����
	TThostFtdcInstrumentIDType	CallInstrumentID;
	///������Լ����
	TThostFtdcInstrumentIDType	PutInstrumentID;
	///Ӫҵ�����
	TThostFtdcBranchIDType	BranchID;
	///Ͷ�ʵ�Ԫ����
	TThostFtdcInvestUnitIDType	InvestUnitID;
	///��������Ч�ֶ�
	TThostFtdcOldIPAddressType	reserve1;
	///Mac��ַ
	TThostFtdcMacAddressType	MacAddress;
	///����������
	TThostFtdcOwnerTypeType	OwnerType;
	///��½PBU
	TThostFtdcTraderIDType	LoginPBU;
	///IP��ַ
	TThostFtdcIPAddressType	IPAddress;
};

///��Ȩָ��ϲ���ѯ
struct CThostFtdcQryExecCombineOrderField
{
	///���͹�˾����
	TThostFtdcBrokerIDType	BrokerID;
	///Ͷ���ߴ���
	TThostFtdcInvestorIDType	InvestorID;
	///���Ǻ�Լ����
	TThostFtdcInstrumentIDType	CallInstrumentID;
	///������Լ����
	TThostFtdcInstrumentIDType	PutInstrumentID;
	///����������
	TThostFtdcExchangeIDType	ExchangeID;
	///ִ������ϲ����
	TThostFtdcExecOrderSysIDType	ExecCombineOrderSysID;
	///��ʼʱ��
	TThostFtdcTimeType	InsertTimeStart;
	///����ʱ��
	TThostFtdcTimeType	InsertTimeEnd;
};

///�û�ϵͳ��Ϣ
struct CThostFtdcUserSystemInfoField
{
	///���͹�˾����
	TThostFtdcBrokerIDType	BrokerID;
	///�û�����
	TThostFtdcUserIDType	UserID;
	///�û���ϵͳ�ڲ���Ϣ����
	TThostFtdcSystemInfoLenType	ClientSystemInfoLen;
	///�û���ϵͳ�ڲ���Ϣ
	TThostFtdcClientSystemInfoType	ClientSystemInfo;
	///��������Ч�ֶ�
	TThostFtdcOldIPAddressType	reserve1;
	///�ն�IP�˿�
	TThostFtdcIPPortType	ClientIPPort;
	///��¼�ɹ�ʱ��
	TThostFtdcTimeType	ClientLoginTime;
	///App����
	TThostFtdcAppIDType	ClientAppID;
	///�û�����IP
	TThostFtdcIPAddressType	ClientPublicIP;
	///�ͻ���¼��ע2
	TThostFtdcClientLoginRemarkType	ClientLoginRemark;
};

///api��������
struct CThostFtdcReqApiHandshakeField
{
	///api��frontͨ����Կ�汾��
	TThostFtdcCryptoKeyVersionType	CryptoKeyVersion;
};

///front����api�����ֻظ�
struct CThostFtdcRspApiHandshakeField
{
	///���ֻظ����ݳ���
	TThostFtdcHandshakeDataLenType	FrontHandshakeDataLen;
	///���ֻظ�����
	TThostFtdcHandshakeDataType	FrontHandshakeData;
	///API��֤�Ƿ���
	TThostFtdcBoolType	IsApiAuthEnabled;
};

///api��front����֤key������
struct CThostFtdcReqVerifyApiKeyField
{
	///���ֻظ����ݳ���
	TThostFtdcHandshakeDataLenType	ApiHandshakeDataLen;
	///���ֻظ�����
	TThostFtdcHandshakeDataType	ApiHandshakeData;
};

///App�ͻ���Ȩ�޷���
struct CThostFtdcAppIDAuthAssignField
{
	///���͹�˾����
	TThostFtdcBrokerIDType	BrokerID;
	///App����
	TThostFtdcAppIDType	AppID;
	///�������Ĵ���
	TThostFtdcDRIdentityIDType	DRIdentityID;
};

///App��֤��
struct CThostFtdcAppAuthenticationCodeField
{
	///���͹�˾����
	TThostFtdcBrokerIDType	BrokerID;
	///App����
	TThostFtdcAppIDType	AppID;
	///��֤��
	TThostFtdcAuthCodeType	AuthCode;
	///����֤��
	TThostFtdcAuthCodeType	PreAuthCode;
	///App����
	TThostFtdcAppTypeType	AppType;
};

///��ѯƵ�ʣ�ÿ���ѯ����
struct CThostFtdcQueryFreqField
{
	///��ѯƵ��
	TThostFtdcQueryFreqType	QueryFreq;
};

///�ϲ���Ȩʱ���
struct CThostFtdcExecCombineTimeSectionField
{
	///���͹�˾����
	TThostFtdcBrokerIDType	BrokerID;
	///����������
	TThostFtdcExchangeIDType	ExchangeID;
	///��ʼʱ��
	TThostFtdcTimeType	StartTime;
	///����ʱ��
	TThostFtdcTimeType	EndTime;
	///�ҵ�������Ȩ��ʼʱ��
	TThostFtdcTimeType	CloseFrozExecTime;
};

///��������������
struct CThostFtdcExchangeExecCombineOrderActionErrorField
{
	///���͹�˾����
	TThostFtdcBrokerIDType	BrokerID;
	///����������
	TThostFtdcExchangeIDType	ExchangeID;
	///ִ������ϲ����
	TThostFtdcExecOrderSysIDType	ExecCombineOrderSysID;
	///����������Ա����
	TThostFtdcTraderIDType	TraderID;
	///��װ���
	TThostFtdcInstallIDType	InstallID;
	///����ִ������ϲ����
	TThostFtdcOrderLocalIDType	ExecCombineOrderLocalID;
	///�������ر��
	TThostFtdcOrderLocalIDType	ActionLocalID;
	///�������
	TThostFtdcErrorIDType	ErrorID;
	///������Ϣ
	TThostFtdcErrorMsgType	ErrorMsg;
	///�ͻ�����
	TThostFtdcClientIDType	ClientID;
	///��½PBU
	TThostFtdcTraderIDType	LoginPBU;
};

///Ͷ���߳��򻯱�ʶ
struct CThostFtdcInvestorProgrammingTypeField
{
	///���͹�˾����
	TThostFtdcBrokerIDType	BrokerID;
	///Ͷ���ߴ���
	TThostFtdcInvestorIDType	InvestorID;
	///����������
	TThostFtdcExchangeIDType	ExchangeID;
	///Ͷ���߳��򻯱�־
	TThostFtdcInvestorProgrammingTypeType	InvestorProgrammingType;
	///Ͷ���߿ͻ���
	TThostFtdcClientNameType	Client;
};

///��ѯͶ���߳��򻯱�ʶ
struct CThostFtdcQryInvestorProgrammingTypeField
{
	///���͹�˾����
	TThostFtdcBrokerIDType	BrokerID;
	///Ͷ���ߴ���
	TThostFtdcInvestorIDType	InvestorID;
	///����������
	TThostFtdcExchangeIDType	ExchangeID;
};

///������ָ���������
struct CThostFtdcExchangeDesignateInsertErrorField
{
	///����������
	TThostFtdcExchangeIDType	ExchangeID;
	///��Ա����
	TThostFtdcParticipantIDType	ParticipantID;
	///����������Ա����
	TThostFtdcTraderIDType	TraderID;
	///��װ���
	TThostFtdcInstallIDType	InstallID;
	///����ָ�����
	TThostFtdcOrderLocalIDType	DesignateLocalID;
	///�������
	TThostFtdcErrorIDType	ErrorID;
	///������Ϣ
	TThostFtdcErrorMsgType	ErrorMsg;
	///�ͻ�����
	TThostFtdcClientIDType	ClientID;
	///ָ������
	TThostFtdcDesignateTypeType	DesignateType;
	///��½PBU
	TThostFtdcTraderIDType	LoginPBU;
	///��������
	TThostFtdcDateType	InsertDate;
	///����ʱ��
	TThostFtdcTimeType	InsertTime;
};

///������֤ȯ���ò������
struct CThostFtdcExchangeStockDisposalInsertErrorField
{
	///����������
	TThostFtdcExchangeIDType	ExchangeID;
	///��Ա����
	TThostFtdcParticipantIDType	ParticipantID;
	///����������Ա����
	TThostFtdcTraderIDType	TraderID;
	///��װ���
	TThostFtdcInstallIDType	InstallID;
	///����֤ȯ���ñ��
	TThostFtdcOrderLocalIDType	StockDisposalLocalID;
	///�������
	TThostFtdcErrorIDType	ErrorID;
	///������Ϣ
	TThostFtdcErrorMsgType	ErrorMsg;
	///֤ȯ���ò������
	TThostFtdcStockDisposalSysIDType	StockDisposalSysID;
	///�ͻ�����
	TThostFtdcClientIDType	ClientID;
	///��Լ����
	TThostFtdcInstrumentIDType	InstrumentID;
	///����
	TThostFtdcVolumeType	Volume;
	///֤ȯ���÷���
	TThostFtdcStockDisposalTypeType	StockDisposalType;
	///����ʱ��
	TThostFtdcTimeType	InsertTime;
	///��½PBU
	TThostFtdcTraderIDType	LoginPBU;
};

///�ֻ���ĺ�Լ�������ʲ�ѯ
struct CThostFtdcQryStockInstrCommissionRateField
{
	///���͹�˾����
	TThostFtdcBrokerIDType	BrokerID;
	///Ͷ���ߴ���
	TThostFtdcInvestorIDType	InvestorID;
	///��Լ����
	TThostFtdcInstrumentIDType	InstrumentID;
	///����������
	TThostFtdcExchangeIDType	ExchangeID;
};

///�ֻ���ĺ�Լ��������
struct CThostFtdcStockInstrCommissionRateField
{
	///����������
	TThostFtdcExchangeIDType	ExchangeID;
	///��Լ����
	TThostFtdcInstrumentIDType	InstrumentID;
	///Ͷ���߷�Χ
	TThostFtdcInvestorRangeType	InvestorRange;
	///���͹�˾����
	TThostFtdcBrokerIDType	BrokerID;
	///Ͷ���ߴ���
	TThostFtdcInvestorIDType	InvestorID;
	///�����������
	TThostFtdcMoneyType	MinBuyCommission;
	///�����������
	TThostFtdcMoneyType	MinSellCommission;
	///��Լ���������������
	TThostFtdcRatioType	BuyCommissionRateByMoney;
	///��Լ���������������
	TThostFtdcRatioType	SellCommissionRateByMoney;
	///��Լ����������������
	TThostFtdcRatioType	BuyCommissionRateByVolume;
	///��Լ����������������
	TThostFtdcRatioType	SellCommissionRateByVolume;
};

///�Գɽ�����
struct CThostFtdcSelfTradeField
{
	///���͹�˾����
	TThostFtdcBrokerIDType	BrokerID;
	///Ͷ���ߴ���
	TThostFtdcInvestorIDType	InvestorID;
	///�Ƿ�֧���Գɽ�
	TThostFtdcBoolType	SuportSelfTrade;
};

///�ͻ�����֤��Ȩ
struct CThostFtdcAuthInvestorField
{
	///Ͷ���߷�Χ
	TThostFtdcInvestorRangeType	InvestorRange;
	///���͹�˾����
	TThostFtdcBrokerIDType	BrokerID;
	///Ͷ���ߴ���
	TThostFtdcInvestorIDType	InvestorID;
	///�û��˲�Ʒ��Ϣ
	TThostFtdcProductInfoType	UserProductInfo;
};

///�ʽ���ת����
struct CThostFtdcInputInternalTransferField
{
	///Ͷ�����ʽ���ת����
	TThostFtdcDepositSeqNoType	InternalTransferRef;
	///��Ȩ���͹�˾����
	TThostFtdcBrokerIDType	BrokerID;
	///�û�����
	TThostFtdcUserIDType	UserID;
	///��Ʊ��ȨͶ���ߴ���
	TThostFtdcInvestorIDType	InvestorID;
	///��Ʊ��Ȩ�ʽ�����
	TThostFtdcPasswordType	OpPassWord;
	///�ڻ����͹�˾����
	TThostFtdcBrokerIDType	FuBrokerID;
	///�ڻ�Ͷ���ߴ���
	TThostFtdcInvestorIDType	FuInvestorID;
	///�ڻ��ʽ�����
	TThostFtdcPasswordType	FuPassWord;
	///��ת���
	TThostFtdcMoneyType	Amount;
	///���ִ���
	TThostFtdcCurrencyIDType	CurrencyID;
	///�ʽ���ת����
	TThostFtdcInternalFundDirectionType	Direction;
};

///�ʽ���ת
struct CThostFtdcInternalTransferField
{
	///ǰ�ñ��
	TThostFtdcFrontIDType	FrontID;
	///�Ự���
	TThostFtdcSessionIDType	SessionID;
	///Ͷ�����ʽ���ת����
	TThostFtdcDepositSeqNoType	InternalTransferRef;
	///��Ȩ���͹�˾����
	TThostFtdcBrokerIDType	BrokerID;
	///�û�����
	TThostFtdcUserIDType	UserID;
	///��Ʊ��ȨͶ���ߴ���
	TThostFtdcInvestorIDType	InvestorID;
	///��Ʊ��Ȩ�ʽ�����
	TThostFtdcPasswordType	OpPassWord;
	///�ڻ����͹�˾����
	TThostFtdcBrokerIDType	FuBrokerID;
	///�ڻ�Ͷ���ߴ���
	TThostFtdcInvestorIDType	FuInvestorID;
	///�ڻ��ʽ�����
	TThostFtdcPasswordType	FuPassWord;
	///��ת���
	TThostFtdcMoneyType	Amount;
	///���ִ���
	TThostFtdcCurrencyIDType	CurrencyID;
	///�ʽ���ת����
	TThostFtdcInternalFundDirectionType	Direction;
	///������
	TThostFtdcDateType	TradingDay;
	///�ʽ���ת��ˮ��
	TThostFtdcDepositSeqNoType	DepositSeqNo;
	///��ת����ʱ��
	TThostFtdcTimeType	TransferReqTime;
	///��ת��Ӧʱ��
	TThostFtdcTimeType	TransferRspTime;
	///�ظ���ˮ��־
	TThostFtdcFundServerRedoFlagType	FundServerRedoFlag;
	///��Ȩ���ʽ�״̬
	TThostFtdcInternalTransferStatusType	Status;
	///��Ȩ����Ӧ��Ϣ
	TThostFtdcErrorMsgType	StatusMsg;
	///�ڻ����ʽ�״̬
	TThostFtdcInternalTransferStatusType	FuStatus;
	///�ڻ�����Ӧ��Ϣ
	TThostFtdcErrorMsgType	FuStatusMsg;
	///�ʽ������װ���
	TThostFtdcInstallIDType	InstallID;
};

///�ʽ���ת
struct CThostFtdcRtnInternalTransferField
{
	///ǰ�ñ��
	TThostFtdcFrontIDType	FrontID;
	///�Ự���
	TThostFtdcSessionIDType	SessionID;
	///Ͷ�����ʽ���ת����
	TThostFtdcDepositSeqNoType	InternalTransferRef;
	///��Ȩ���͹�˾����
	TThostFtdcBrokerIDType	BrokerID;
	///�û�����
	TThostFtdcUserIDType	UserID;
	///��Ʊ��ȨͶ���ߴ���
	TThostFtdcInvestorIDType	InvestorID;
	///��Ʊ��Ȩ�ʽ�����
	TThostFtdcPasswordType	OpPassWord;
	///�ڻ����͹�˾����
	TThostFtdcBrokerIDType	FuBrokerID;
	///�ڻ�Ͷ���ߴ���
	TThostFtdcInvestorIDType	FuInvestorID;
	///�ڻ��ʽ�����
	TThostFtdcPasswordType	FuPassWord;
	///��ת���
	TThostFtdcMoneyType	Amount;
	///���ִ���
	TThostFtdcCurrencyIDType	CurrencyID;
	///�ʽ���ת����
	TThostFtdcInternalFundDirectionType	Direction;
	///������
	TThostFtdcDateType	TradingDay;
	///�ʽ���ת��ˮ��
	TThostFtdcDepositSeqNoType	DepositSeqNo;
	///��ת����ʱ��
	TThostFtdcTimeType	TransferReqTime;
	///��ת��Ӧʱ��
	TThostFtdcTimeType	TransferRspTime;
	///�ظ���ˮ��־
	TThostFtdcFundServerRedoFlagType	FundServerRedoFlag;
	///��Ȩ���ʽ�״̬
	TThostFtdcInternalTransferStatusType	Status;
	///��Ȩ����Ӧ��Ϣ
	TThostFtdcErrorMsgType	StatusMsg;
	///�ڻ����ʽ�״̬
	TThostFtdcInternalTransferStatusType	FuStatus;
	///�ڻ�����Ӧ��Ϣ
	TThostFtdcErrorMsgType	FuStatusMsg;
	///�ʽ������װ���
	TThostFtdcInstallIDType	InstallID;
};

///�ʽ���ת�����ѯ
struct CThostFtdcReqQryInternalFundServerField
{
	///��װ���
	TThostFtdcInstallIDType	InstallID;
	///���͹�˾����
	TThostFtdcBrokerIDType	BrokerID;
};

///�ʽ���ת�����ѯ��Ӧ
struct CThostFtdcInternalFundServerField
{
	///��װ���
	TThostFtdcInstallIDType	InstallID;
	///brokerid
	TThostFtdcBrokerIDType	BrokerID;
	///FundServer����״̬
	TThostFtdcFundServerStatusType	FundServerStatus;
	///�ϴα�������
	TThostFtdcDateType	LastReportDate;
	///�ϴα���ʱ��
	TThostFtdcTimeType	LastReportTime;
	///�����������
	TThostFtdcDateType	ConnectDate;
	///�������ʱ��
	TThostFtdcTimeType	ConnectTime;
	///��������
	TThostFtdcDateType	StartDate;
	///����ʱ��
	TThostFtdcTimeType	StartTime;
	///������
	TThostFtdcDateType	TradingDay;
	///��ǰ�����ˮ��
	TThostFtdcDepositSeqNoType	MaxDepositSeqNo;
};

///�ʽ���ת��¼��ѯ
struct CThostFtdcQryInternalTransferField
{
	///���͹�˾����
	TThostFtdcBrokerIDType	BrokerID;
	///Ͷ���ߴ���
	TThostFtdcInvestorIDType	InvestorID;
	///Ͷ�����ʽ���ת����
	TThostFtdcDepositSeqNoType	InternalTransferRef;
	///��ʼʱ��
	TThostFtdcTimeType	TransferReqTimeStart;
	///����ʱ��
	TThostFtdcTimeType	TransferReqTimeEnd;
};

///�ڻ���ȨͶ�����˻���Ӧ��ϵ
struct CThostFtdcQryOptFutInvestorMapField
{
	///��Ȩ���͹�˾����
	TThostFtdcBrokerIDType	OptBrokerID;
	///��ȨͶ���ߴ���
	TThostFtdcInvestorIDType	OptInvestorID;
};

///�ڻ���ȨͶ�����˻���Ӧ��ϵ
struct CThostFtdcOptFutInvestorMapField
{
	///��Ȩ���͹�˾���
	TThostFtdcBrokerIDType	OptBrokerID;
	///�ڻ����͹�˾���
	TThostFtdcBrokerIDType	FutBrokerID;
	///��ȨͶ���ߴ���
	TThostFtdcInvestorIDType	OptInvestorID;
	///�ڻ�Ͷ���ߴ���
	TThostFtdcInvestorIDType	FutInvestorID;
};

///��ѯ��Ӧ���ڻ��ʽ��˻�
struct CThostFtdcQryFutureTradingAccountField
{
	///��Ʊ��Ȩ���͹�˾����
	TThostFtdcBrokerIDType	BrokerID;
	///��Ʊ��ȨͶ���ߴ���
	TThostFtdcInvestorIDType	InvestorID;
	///�ڻ��˾��͹�˾����
	TThostFtdcBrokerIDType	FuBrokerID;
	///�ڻ���Ͷ���ߴ���
	TThostFtdcInvestorIDType	FuInvestorID;
	///���ִ���
	TThostFtdcCurrencyIDType	CurrencyID;
	///��װ���
	TThostFtdcInstallIDType	InstallID;
	///�û�����
	TThostFtdcUserIDType	UserID;
};

///��Ӧ���ڻ��ʽ��˻�
struct CThostFtdcNtfQryFutureTradingAccountField
{
	///���͹�˾����
	TThostFtdcBrokerIDType	FuBrokerID;
	///Ͷ�����ʺ�
	TThostFtdcAccountIDType	FuAccountID;
	///�����
	TThostFtdcMoneyType	Deposit;
	///������
	TThostFtdcMoneyType	Withdraw;
	///�����ʽ�
	TThostFtdcMoneyType	Available;
	///��ȡ�ʽ�
	TThostFtdcMoneyType	WithdrawQuota;
	///����׼����
	TThostFtdcMoneyType	Reserve;
	///������
	TThostFtdcDateType	TradingDay;
	///������
	TThostFtdcSettlementIDType	SettlementID;
	///���ִ���
	TThostFtdcCurrencyIDType	CurrencyID;
	///��Ʊ��Ȩ���͹�˾����
	TThostFtdcBrokerIDType	BrokerID;
	///��Ʊ��Ȩ�û�����
	TThostFtdcUserIDType	UserID;
	///��Ʊ��ȨͶ���ߴ���
	TThostFtdcInvestorIDType	InvestorID;
	///�������
	TThostFtdcErrorIDType	ErrorID;
	///������Ϣ
	TThostFtdcErrorMsgType	ErrorMsg;
	///ǰ�ñ��
	TThostFtdcFrontIDType	FrontID;
	///�Ự���
	TThostFtdcSessionIDType	SessionID;
	///������
	TThostFtdcRequestIDType	RequestID;
};


}

using namespace ctp_sopt;
#endif
