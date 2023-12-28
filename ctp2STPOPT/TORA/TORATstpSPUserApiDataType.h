/////////////////////////////////////////////////////////////////////////
///@company 上海泰琰信息科技有限公司
///@file TORATstpSPUserApiDataType.h
///@brief 定义了客户端接口使用的业务数据类型
///@history 
/////////////////////////////////////////////////////////////////////////

#ifndef _TORA_TSTPSPUSERAPIDATATYPE_H
#define _TORA_TSTPSPUSERAPIDATATYPE_H

#include <limits.h>
#include <float.h>

namespace TORASPAPI
{
	///定义空值
	const int INT_NULL_VAL = INT_MAX;
	
	const double FLOAT_NULL_VAL = DBL_MAX;
	
	const char CHAR_NULL_VAL = 0;
	
	const short WORD_NULL_VAL = SHRT_MAX;
	
#ifdef WINDOWS
	const __int64 LONG_NULL_VAL = _I64_MAX;
#else
	const long long LONG_NULL_VAL = LLONG_MAX;
#endif
	
	///整型数据置空和判空
	inline void set_null(int &v)
	{
		v = INT_NULL_VAL;
	}
	inline bool is_null(const int &v)
	{
		return v == INT_NULL_VAL;
	}
	
	///浮点型数据置空和判空
	inline void set_null(double &v)
	{
		v = FLOAT_NULL_VAL;
	}
	inline bool is_null(const double &v)
	{
		return v == FLOAT_NULL_VAL;
	}
	
	///字符型数据置空和判空
	inline void set_null(char &v)
	{
		v = CHAR_NULL_VAL;
	}
	inline bool is_null(const char &v)
	{
		return v == CHAR_NULL_VAL;
	}
	
	///短整型数据置空和判空
	inline void set_null(short &v)
	{
		v = WORD_NULL_VAL;
	}
	inline bool is_null(const short &v)
	{
		return v == WORD_NULL_VAL;
	}
	
	///长整型数据置空和判空
	#ifdef WINDOWS
	inline void set_null(__int64 &v)
	#else
	inline void set_null(long long &v)
	#endif
	{
		v = LONG_NULL_VAL;
	}
	#ifdef WINDOWS
	inline bool is_null(const __int64 &v)
	#else
	inline bool is_null(const long long &v)
	#endif
	{
		return v == LONG_NULL_VAL;
	}
	
	///字符串型数据置空和判空
	inline void set_null(char *v)
	{
		v[0] = '\0';
	}
	inline bool is_null(const char *v)
	{
		const char *p=v;
		while (*p)
		{
			if (*p!=' ')
			{
				return false;
			}
			p++;
		}
		return true;
	}

	enum TORA_TE_RESUME_TYPE
	{
		TORA_TERT_RESTART = 0,
		TORA_TERT_RESUME,
		TORA_TERT_QUICK
	};


	/////////////////////////////////////////////////////////////////////////
	/// TTORATstpDateType是一个日期类型
	/////////////////////////////////////////////////////////////////////////
	typedef char TTORATstpSPDateType[9];

	/////////////////////////////////////////////////////////////////////////
	/// TTORATstpTimeType是一个时间类型
	/////////////////////////////////////////////////////////////////////////
	typedef char TTORATstpSPTimeType[9];

	/////////////////////////////////////////////////////////////////////////
	/// TTORATstpMillisecType是一个时间（毫秒）类型
	/////////////////////////////////////////////////////////////////////////
	typedef int TTORATstpSPMillisecType;

	/////////////////////////////////////////////////////////////////////////
	/// TTORATstpPriceType是一个价格类型
	/////////////////////////////////////////////////////////////////////////
	typedef double TTORATstpSPPriceType;

	/////////////////////////////////////////////////////////////////////////
	/// TTORATstpRatioType是一个比率类型
	/////////////////////////////////////////////////////////////////////////
	typedef double TTORATstpSPRatioType;

	/////////////////////////////////////////////////////////////////////////
	/// TTORATstpMoneyType是一个资金类型
	/////////////////////////////////////////////////////////////////////////
	typedef double TTORATstpSPMoneyType;

	/////////////////////////////////////////////////////////////////////////
	/// TTORATstpVolumeType是一个数量类型
	/////////////////////////////////////////////////////////////////////////
	typedef int TTORATstpSPVolumeType;

	/////////////////////////////////////////////////////////////////////////
	/// TTORATstpLargeVolumeType是一个大额数量类型
	/////////////////////////////////////////////////////////////////////////
	typedef double TTORATstpSPLargeVolumeType;

	/////////////////////////////////////////////////////////////////////////
	/// TTORATstpBoolType是一个布尔型类型
	/////////////////////////////////////////////////////////////////////////
	typedef int TTORATstpSPBoolType;

	/////////////////////////////////////////////////////////////////////////
	/// TTORATstpSequenceNoType是一个流水号类型
	/////////////////////////////////////////////////////////////////////////
	typedef int TTORATstpSPSequenceNoType;

	/////////////////////////////////////////////////////////////////////////
	/// TTORATstpSerialType是一个流水号类型
	/////////////////////////////////////////////////////////////////////////
	typedef char TTORATstpSPSerialType[31];

	/////////////////////////////////////////////////////////////////////////
	/// TTORATstpCommFluxType是一个通讯流量类型
	/////////////////////////////////////////////////////////////////////////
	typedef int TTORATstpSPCommFluxType;

	/////////////////////////////////////////////////////////////////////////
	/// TTORATstpExchangeIDType是一个交易所代码类型
	/////////////////////////////////////////////////////////////////////////
	///通用(内部使用)
	const char TORA_TSTP_SP_EXD_COMM = '0';
	///上海交易所
	const char TORA_TSTP_SP_EXD_SSE = '1';
	///深圳交易所
	const char TORA_TSTP_SP_EXD_SZSE = '2';
	///香港交易所
	const char TORA_TSTP_SP_EXD_HK = '3';
	typedef char TTORATstpSPExchangeIDType;

	/////////////////////////////////////////////////////////////////////////
	/// TTORATstpVolumeMultipleType是一个合约数量乘数类型
	/////////////////////////////////////////////////////////////////////////
	typedef int TTORATstpSPVolumeMultipleType;

	/////////////////////////////////////////////////////////////////////////
	/// TTORATstpIdCardNoType是一个证件编号类型
	/////////////////////////////////////////////////////////////////////////
	typedef char TTORATstpSPIdCardNoType[51];

	/////////////////////////////////////////////////////////////////////////
	/// TTORATstpUserIDType是一个交易用户代码类型
	/////////////////////////////////////////////////////////////////////////
	typedef char TTORATstpSPUserIDType[16];

	/////////////////////////////////////////////////////////////////////////
	/// TTORATstpTradeIDType是一个成交编号类型
	/////////////////////////////////////////////////////////////////////////
	typedef char TTORATstpSPTradeIDType[21];

	/////////////////////////////////////////////////////////////////////////
	/// TTORATstpOrderSysIDType是一个系统报单编号类型
	/////////////////////////////////////////////////////////////////////////
	typedef char TTORATstpSPOrderSysIDType[21];

	/////////////////////////////////////////////////////////////////////////
	/// TTORATstpExchangeCombIDType是一个交易所组合编码类型
	/////////////////////////////////////////////////////////////////////////
	typedef char TTORATstpSPExchangeCombIDType[21];

	/////////////////////////////////////////////////////////////////////////
	/// TTORATstpPasswordType是一个密码类型
	/////////////////////////////////////////////////////////////////////////
	typedef char TTORATstpSPPasswordType[41];

	/////////////////////////////////////////////////////////////////////////
	/// TTORATstpFrontIDType是一个前置编号类型
	/////////////////////////////////////////////////////////////////////////
	typedef int TTORATstpSPFrontIDType;

	/////////////////////////////////////////////////////////////////////////
	/// TTORATstpSessionIDType是一个会话编号类型
	/////////////////////////////////////////////////////////////////////////
	typedef int TTORATstpSPSessionIDType;

	/////////////////////////////////////////////////////////////////////////
	/// TTORATstpProductInfoType是一个产品信息类型
	/////////////////////////////////////////////////////////////////////////
	typedef char TTORATstpSPProductInfoType[11];

	/////////////////////////////////////////////////////////////////////////
	/// TTORATstpProtocolInfoType是一个协议信息类型
	/////////////////////////////////////////////////////////////////////////
	typedef char TTORATstpSPProtocolInfoType[11];

	/////////////////////////////////////////////////////////////////////////
	/// TTORATstpDataSyncStatusType是一个数据同步状态类型
	/////////////////////////////////////////////////////////////////////////
	///未同步
	const char TORA_TSTP_SP_DS_Asynchronous = '1';
	///同步中
	const char TORA_TSTP_SP_DS_Synchronizing = '2';
	///已同步
	const char TORA_TSTP_SP_DS_Synchronized = '3';
	///全部同步完成
	const char TORA_TSTP_SP_DS_AllSynchronized = '4';
	///预同步完成
	const char TORA_TSTP_SP_DS_PreSync = '5';
	typedef char TTORATstpSPDataSyncStatusType;

	/////////////////////////////////////////////////////////////////////////
	/// TTORATstpRecordCntType是一个记录个数类型
	/////////////////////////////////////////////////////////////////////////
	typedef int TTORATstpSPRecordCntType;

	/////////////////////////////////////////////////////////////////////////
	/// TTORATstpErrorIDType是一个错误代码类型
	/////////////////////////////////////////////////////////////////////////
	typedef int TTORATstpSPErrorIDType;

	/////////////////////////////////////////////////////////////////////////
	/// TTORATstpErrorMsgType是一个错误信息类型
	/////////////////////////////////////////////////////////////////////////
	typedef char TTORATstpSPErrorMsgType[81];

	/////////////////////////////////////////////////////////////////////////
	/// TTORATstpPositionTypeType是一个持仓类型类型
	/////////////////////////////////////////////////////////////////////////
	///净持仓
	const char TORA_TSTP_SP_PT_Net = '1';
	///综合持仓
	const char TORA_TSTP_SP_PT_Gross = '2';
	typedef char TTORATstpSPPositionTypeType;

	/////////////////////////////////////////////////////////////////////////
	/// TTORATstpCombinationStatusType是一个组合持仓状态类型
	/////////////////////////////////////////////////////////////////////////
	///组合
	const char TORA_TSTP_SP_CTS_Combined = '1';
	///拆分完成
	const char TORA_TSTP_SP_CTS_Splitted = '3';
	typedef char TTORATstpSPCombinationStatusType;

	/////////////////////////////////////////////////////////////////////////
	/// TTORATstpNameType是一个名称类型
	/////////////////////////////////////////////////////////////////////////
	typedef char TTORATstpSPNameType[61];

	/////////////////////////////////////////////////////////////////////////
	/// TTORATstpSecurityIDType是一个合约代码类型
	/////////////////////////////////////////////////////////////////////////
	typedef char TTORATstpSPSecurityIDType[31];

	/////////////////////////////////////////////////////////////////////////
	/// TTORATstpExchSecurityIDType是一个交易所合约代码类型
	/////////////////////////////////////////////////////////////////////////
	typedef char TTORATstpSPExchSecurityIDType[31];

	/////////////////////////////////////////////////////////////////////////
	/// TTORATstpPriceTickType是一个最小变动价位类型
	/////////////////////////////////////////////////////////////////////////
	typedef double TTORATstpSPPriceTickType;

	/////////////////////////////////////////////////////////////////////////
	/// TTORATstpTradingUnitType是一个交易单位类型
	/////////////////////////////////////////////////////////////////////////
	typedef int TTORATstpSPTradingUnitType;

	/////////////////////////////////////////////////////////////////////////
	/// TTORATstpSecurityStatusType是一个证券状态类型
	/////////////////////////////////////////////////////////////////////////
	typedef int TTORATstpSPSecurityStatusType;

	/////////////////////////////////////////////////////////////////////////
	/// TTORATstpAccountIDType是一个投资者资金帐号类型
	/////////////////////////////////////////////////////////////////////////
	typedef char TTORATstpSPAccountIDType[21];

	/////////////////////////////////////////////////////////////////////////
	/// TTORATstpBankAccountIDType是一个签约银行账号类型
	/////////////////////////////////////////////////////////////////////////
	typedef char TTORATstpSPBankAccountIDType[31];

	/////////////////////////////////////////////////////////////////////////
	/// TTORATstpInvestorIDType是一个投资者代码类型
	/////////////////////////////////////////////////////////////////////////
	typedef char TTORATstpSPInvestorIDType[13];

	/////////////////////////////////////////////////////////////////////////
	/// TTORATstpContacterType是一个联系人类型
	/////////////////////////////////////////////////////////////////////////
	typedef char TTORATstpSPContacterType[61];

	/////////////////////////////////////////////////////////////////////////
	/// TTORATstpFaxType是一个传真类型
	/////////////////////////////////////////////////////////////////////////
	typedef char TTORATstpSPFaxType[21];

	/////////////////////////////////////////////////////////////////////////
	/// TTORATstpEmailType是一个Email类型
	/////////////////////////////////////////////////////////////////////////
	typedef char TTORATstpSPEmailType[61];

	/////////////////////////////////////////////////////////////////////////
	/// TTORATstpAddressType是一个通讯地址类型
	/////////////////////////////////////////////////////////////////////////
	typedef char TTORATstpSPAddressType[101];

	/////////////////////////////////////////////////////////////////////////
	/// TTORATstpZipCodeType是一个邮政编码类型
	/////////////////////////////////////////////////////////////////////////
	typedef char TTORATstpSPZipCodeType[21];

	/////////////////////////////////////////////////////////////////////////
	/// TTORATstpDepartmentIDType是一个部门代码类型
	/////////////////////////////////////////////////////////////////////////
	typedef char TTORATstpSPDepartmentIDType[11];

	/////////////////////////////////////////////////////////////////////////
	/// TTORATstpBranchIDType是一个营业部类型
	/////////////////////////////////////////////////////////////////////////
	typedef char TTORATstpSPBranchIDType[11];

	/////////////////////////////////////////////////////////////////////////
	/// TTORATstpContractNoType是一个合同编号类型
	/////////////////////////////////////////////////////////////////////////
	typedef char TTORATstpSPContractNoType[31];

	/////////////////////////////////////////////////////////////////////////
	/// TTORATstpRemarkType是一个备注类型
	/////////////////////////////////////////////////////////////////////////
	typedef char TTORATstpSPRemarkType[513];

	/////////////////////////////////////////////////////////////////////////
	/// TTORATstpTerminalInfoType是一个终端信息类型
	/////////////////////////////////////////////////////////////////////////
	typedef char TTORATstpSPTerminalInfoType[256];

	/////////////////////////////////////////////////////////////////////////
	/// TTORATstpShareholderIDType是一个股东账户代码类型
	/////////////////////////////////////////////////////////////////////////
	typedef char TTORATstpSPShareholderIDType[11];

	/////////////////////////////////////////////////////////////////////////
	/// TTORATstpPbuIDType是一个交易单元代码类型
	/////////////////////////////////////////////////////////////////////////
	typedef char TTORATstpSPPbuIDType[11];

	/////////////////////////////////////////////////////////////////////////
	/// TTORATstpIPAddressType是一个IP地址类型
	/////////////////////////////////////////////////////////////////////////
	typedef char TTORATstpSPIPAddressType[16];

	/////////////////////////////////////////////////////////////////////////
	/// TTORATstpMacAddressType是一个Mac地址类型
	/////////////////////////////////////////////////////////////////////////
	typedef char TTORATstpSPMacAddressType[21];

	/////////////////////////////////////////////////////////////////////////
	/// TTORATstpPortType是一个端口号类型
	/////////////////////////////////////////////////////////////////////////
	typedef int TTORATstpSPPortType;

	/////////////////////////////////////////////////////////////////////////
	/// TTORATstpLangType是一个语言类型
	/////////////////////////////////////////////////////////////////////////
	///简体中文
	const char TORA_TSTP_SP_LGT_ZHCN = '0';
	///中文香港
	const char TORA_TSTP_SP_LGT_ZHHK = '1';
	///英文美国
	const char TORA_TSTP_SP_LGT_ENUS = '2';
	typedef char TTORATstpSPLangType;

	/////////////////////////////////////////////////////////////////////////
	/// TTORATstpOrderLocalIDType是一个本地报单编号类型
	/////////////////////////////////////////////////////////////////////////
	typedef char TTORATstpSPOrderLocalIDType[13];

	/////////////////////////////////////////////////////////////////////////
	/// TTORATstpBusinessUnitIDType是一个投资单元代码类型
	/////////////////////////////////////////////////////////////////////////
	typedef char TTORATstpSPBusinessUnitIDType[17];

	/////////////////////////////////////////////////////////////////////////
	/// TTORATstpSecurityNameType是一个证券名称类型
	/////////////////////////////////////////////////////////////////////////
	typedef char TTORATstpSPSecurityNameType[41];

	/////////////////////////////////////////////////////////////////////////
	/// TTORATstpOrderRefType是一个报单引用类型
	/////////////////////////////////////////////////////////////////////////
	typedef int TTORATstpSPOrderRefType;

	/////////////////////////////////////////////////////////////////////////
	/// TTORATstpRequestIDType是一个请求编号类型
	/////////////////////////////////////////////////////////////////////////
	typedef int TTORATstpSPRequestIDType;

	/////////////////////////////////////////////////////////////////////////
	/// TTORATstpIntSerialType是一个整数流水号类型
	/////////////////////////////////////////////////////////////////////////
	typedef int TTORATstpSPIntSerialType;

	/////////////////////////////////////////////////////////////////////////
	/// TTORATstpInvestorNameType是一个投资者名称类型
	/////////////////////////////////////////////////////////////////////////
	typedef char TTORATstpSPInvestorNameType[81];

	/////////////////////////////////////////////////////////////////////////
	/// TTORATstpUserNameType是一个用户名称类型
	/////////////////////////////////////////////////////////////////////////
	typedef char TTORATstpSPUserNameType[81];

	/////////////////////////////////////////////////////////////////////////
	/// TTORATstpLoginLimitType是一个登录限制类型
	/////////////////////////////////////////////////////////////////////////
	typedef int TTORATstpSPLoginLimitType;

	/////////////////////////////////////////////////////////////////////////
	/// TTORATstpBankIDType是一个银行代码类型
	/////////////////////////////////////////////////////////////////////////
	///中国建设银行
	const char TORA_TSTP_SP_BKID_CCB = '1';
	///中国农业银行
	const char TORA_TSTP_SP_BKID_ABC = '2';
	///中国工商银行
	const char TORA_TSTP_SP_BKID_ICBC = '3';
	///中国银行
	const char TORA_TSTP_SP_BKID_BOC = '4';
	///中国招商银行
	const char TORA_TSTP_SP_BKID_CMBC = '5';
	///中国交通银行
	const char TORA_TSTP_SP_BKID_BC = '6';
	///浦东发展银行
	const char TORA_TSTP_SP_BKID_SPDB = '7';
	///兴业银行
	const char TORA_TSTP_SP_BKID_CIB = '8';
	///中国光大银行
	const char TORA_TSTP_SP_BKID_CEB = '9';
	///广东发展银行
	const char TORA_TSTP_SP_BKID_GDB = 'a';
	///中信银行
	const char TORA_TSTP_SP_BKID_CITIC = 'b';
	///平安银行
	const char TORA_TSTP_SP_BKID_SPABANK = 'c';
	typedef char TTORATstpSPBankIDType;

	/////////////////////////////////////////////////////////////////////////
	/// TTORATstpCurrencyIDType是一个币种类型
	/////////////////////////////////////////////////////////////////////////
	///人民币
	const char TORA_TSTP_SP_CID_CNY = '1';
	///港币
	const char TORA_TSTP_SP_CID_HKD = '2';
	///美元
	const char TORA_TSTP_SP_CID_USD = '3';
	typedef char TTORATstpSPCurrencyIDType;

	/////////////////////////////////////////////////////////////////////////
	/// TTORATstpActiveStatusType是一个用户状态类型
	/////////////////////////////////////////////////////////////////////////
	///启用
	const char TORA_TSTP_SP_USTS_Enabled = '1';
	///禁用
	const char TORA_TSTP_SP_USTS_Disabled = '2';
	///锁定
	const char TORA_TSTP_SP_USTS_Locked = '3';
	typedef char TTORATstpSPActiveStatusType;

	/////////////////////////////////////////////////////////////////////////
	/// TTORATstpAuthModeType是一个认证方式类型
	/////////////////////////////////////////////////////////////////////////
	///密码
	const char TORA_TSTP_SP_AM_Password = '0';
	///指纹
	const char TORA_TSTP_SP_AM_FingerPrint = '1';
	///钥匙串
	const char TORA_TSTP_SP_AM_CertInfo = '2';
	typedef char TTORATstpSPAuthModeType;

	/////////////////////////////////////////////////////////////////////////
	/// TTORATstpDeviceTypeType是一个设备类别类型
	/////////////////////////////////////////////////////////////////////////
	///PC端
	const char TORA_TSTP_SP_DT_PC = '0';
	///移动端
	const char TORA_TSTP_SP_DT_Mobile = '1';
	typedef char TTORATstpSPDeviceTypeType;

	/////////////////////////////////////////////////////////////////////////
	/// TTORATstpDeviceIDType是一个设备标识类型
	/////////////////////////////////////////////////////////////////////////
	typedef char TTORATstpSPDeviceIDType[129];

	/////////////////////////////////////////////////////////////////////////
	/// TTORATstpCertSerialType是一个认证序列类型
	/////////////////////////////////////////////////////////////////////////
	typedef char TTORATstpSPCertSerialType[129];

	/////////////////////////////////////////////////////////////////////////
	/// TTORATstpCombOffsetFlagType是一个组合开平标志类型
	/////////////////////////////////////////////////////////////////////////
	typedef char TTORATstpSPCombOffsetFlagType[5];

	/////////////////////////////////////////////////////////////////////////
	/// TTORATstpCombHedgeFlagType是一个组合投机套保标志类型
	/////////////////////////////////////////////////////////////////////////
	typedef char TTORATstpSPCombHedgeFlagType[5];

	/////////////////////////////////////////////////////////////////////////
	/// TTORATstpTelephoneType是一个联系电话类型
	/////////////////////////////////////////////////////////////////////////
	typedef char TTORATstpSPTelephoneType[41];

	/////////////////////////////////////////////////////////////////////////
	/// TTORATstpMobileType是一个手机类型
	/////////////////////////////////////////////////////////////////////////
	typedef char TTORATstpSPMobileType[41];

	/////////////////////////////////////////////////////////////////////////
	/// TTORATstpLongVolumeType是一个LongVolume类型
	/////////////////////////////////////////////////////////////////////////
	typedef long long int TTORATstpSPLongVolumeType;

	/////////////////////////////////////////////////////////////////////////
	/// TTORATstpOrderUnitType是一个申报单位类型
	/////////////////////////////////////////////////////////////////////////
	///手
	const char TORA_TSTP_SP_OUT_Shou = '0';
	///股
	const char TORA_TSTP_SP_OUT_Gu = '1';
	///份
	const char TORA_TSTP_SP_OUT_Fen = '2';
	///张
	const char TORA_TSTP_SP_OUT_Zhang = '3';
	typedef char TTORATstpSPOrderUnitType;

	/////////////////////////////////////////////////////////////////////////
	/// TTORATstpInvestorTypeType是一个投资者类型类型
	/////////////////////////////////////////////////////////////////////////
	///个人
	const char TORA_TSTP_SP_CT_Person = '0';
	///机构
	const char TORA_TSTP_SP_CT_Company = '1';
	///自营
	const char TORA_TSTP_SP_CT_SelfOperate = '5';
	typedef char TTORATstpSPInvestorTypeType;

	/////////////////////////////////////////////////////////////////////////
	/// TTORATstpIdCardTypeType是一个证件类型类型
	/////////////////////////////////////////////////////////////////////////
	///组织机构代码
	const char TORA_TSTP_SP_ICT_EID = '0';
	///中国公民身份证
	const char TORA_TSTP_SP_ICT_IDCard = '1';
	///军官证
	const char TORA_TSTP_SP_ICT_OfficerIDCard = '2';
	///警官证
	const char TORA_TSTP_SP_ICT_PoliceIDCard = '3';
	///士兵证
	const char TORA_TSTP_SP_ICT_SoldierIDCard = '4';
	///户口簿
	const char TORA_TSTP_SP_ICT_HouseholdRegister = '5';
	///护照
	const char TORA_TSTP_SP_ICT_Passport = '6';
	///台胞证
	const char TORA_TSTP_SP_ICT_TaiwanCompatriotIDCard = '7';
	///回乡证
	const char TORA_TSTP_SP_ICT_HomeComingCard = '8';
	///营业执照号
	const char TORA_TSTP_SP_ICT_LicenseNo = '9';
	///税务登记号/当地纳税ID
	const char TORA_TSTP_SP_ICT_TaxNo = 'A';
	///港澳居民来往内地通行证
	const char TORA_TSTP_SP_ICT_HMMainlandTravelPermit = 'B';
	///台湾居民来往大陆通行证
	const char TORA_TSTP_SP_ICT_TwMainlandTravelPermit = 'C';
	///驾照
	const char TORA_TSTP_SP_ICT_DrivingLicense = 'D';
	///当地社保ID
	const char TORA_TSTP_SP_ICT_SocialID = 'F';
	///当地身份证
	const char TORA_TSTP_SP_ICT_LocalID = 'G';
	///商业登记证
	const char TORA_TSTP_SP_ICT_BusinessRegistration = 'H';
	///港澳永久性居民身份证
	const char TORA_TSTP_SP_ICT_HKMCIDCard = 'I';
	///人行开户许可证
	const char TORA_TSTP_SP_ICT_AccountsPermits = 'J';
	///其他证件
	const char TORA_TSTP_SP_ICT_OtherCard = 'x';
	typedef char TTORATstpSPIdCardTypeType;

	/////////////////////////////////////////////////////////////////////////
	/// TTORATstpAccountTypeType是一个资金账户类型类型
	/////////////////////////////////////////////////////////////////////////
	///普通
	const char TORA_TSTP_SP_FAT_Normal = '1';
	///信用
	const char TORA_TSTP_SP_FAT_Credit = '2';
	///衍生品
	const char TORA_TSTP_SP_FAT_Derivatives = '3';
	typedef char TTORATstpSPAccountTypeType;

	/////////////////////////////////////////////////////////////////////////
	/// TTORATstpDirectionType是一个报单方向类型
	/////////////////////////////////////////////////////////////////////////
	///买入
	const char TORA_TSTP_SP_D_Buy = '0';
	///卖出
	const char TORA_TSTP_SP_D_Sell = '1';
	///空（无意义)
	const char TORA_TSTP_SP_D_Non = '*';
	typedef char TTORATstpSPDirectionType;

	/////////////////////////////////////////////////////////////////////////
	/// TTORATstpCombDirectionType是一个组合报单方向类型
	/////////////////////////////////////////////////////////////////////////
	///组合
	const char TORA_TSTP_SP_CBD_Combine = '0';
	///拆分
	const char TORA_TSTP_SP_CBD_Split = '1';
	///强拆
	const char TORA_TSTP_SP_CBD_ForceSplit = '2';
	typedef char TTORATstpSPCombDirectionType;

	/////////////////////////////////////////////////////////////////////////
	/// TTORATstpBrokerageTypeType是一个佣金类型类型
	/////////////////////////////////////////////////////////////////////////
	///毛佣金
	const char TORA_TSTP_SP_BT_Gross = '0';
	///净佣金
	const char TORA_TSTP_SP_BT_Net = '1';
	typedef char TTORATstpSPBrokerageTypeType;

	/////////////////////////////////////////////////////////////////////////
	/// TTORATstpUserTypeType是一个用户类型类型
	/////////////////////////////////////////////////////////////////////////
	///经纪公司用户
	const char TORA_TSTP_SP_UTYPE_BrokerUser = '0';
	///超级用户
	const char TORA_TSTP_SP_UTYPE_SuperUser = '1';
	///投资者用户
	const char TORA_TSTP_SP_UTYPE_Investor = '2';
	typedef char TTORATstpSPUserTypeType;

	/////////////////////////////////////////////////////////////////////////
	/// TTORATstpOperateSourceType是一个操作来源类型
	/////////////////////////////////////////////////////////////////////////
	///实时上场
	const char TORA_TSTP_SP_OPRTSRC_DBCommand = '0';
	///API调用
	const char TORA_TSTP_SP_OPRTSRC_SyncAPI = '1';
	///实时模式自动触发
	const char TORA_TSTP_SP_OPRTSRC_RealTimeAuto = '2';
	typedef char TTORATstpSPOperateSourceType;

	/////////////////////////////////////////////////////////////////////////
	/// TTORATstpOperwayType是一个委托方式（枚举值仅供举例参考，需根据券商要求填写具体的字符）类型
	/////////////////////////////////////////////////////////////////////////
	///电话委托
	const char TORA_TSTP_SP_OPERW_Telephone = '0';
	///柜台委托
	const char TORA_TSTP_SP_OPERW_OTC = '1';
	///移动客户端委托
	const char TORA_TSTP_SP_OPERW_MobileClient = '2';
	///PC客户端委托
	const char TORA_TSTP_SP_OPERW_PCClient = '3';
	///TY委托
	const char TORA_TSTP_SP_OPERW_TY = '4';
	typedef char TTORATstpSPOperwayType;

	/////////////////////////////////////////////////////////////////////////
	/// TTORATstpOperwaysType是一个委托方式合集类型
	/////////////////////////////////////////////////////////////////////////
	typedef char TTORATstpSPOperwaysType[41];

	/////////////////////////////////////////////////////////////////////////
	/// TTORATstpOrderPriceTypeType是一个报单价格条件类型
	/////////////////////////////////////////////////////////////////////////
	///任意价
	const char TORA_TSTP_SP_OPT_AnyPrice = '1';
	///限价
	const char TORA_TSTP_SP_OPT_LimitPrice = '2';
	///最优价
	const char TORA_TSTP_SP_OPT_BestPrice = '3';
	///最新价
	const char TORA_TSTP_SP_OPT_LastPrice = '4';
	///相关价
	const char TORA_TSTP_SP_OPT_Relative = '5';
	///卖一价
	const char TORA_TSTP_SP_OPT_AskPrice1 = '8';
	///买一价
	const char TORA_TSTP_SP_OPT_BidPrice1 = 'C';
	///五档价
	const char TORA_TSTP_SP_OPT_FiveLevelPrice = 'G';
	///本方最优
	const char TORA_TSTP_SP_OPT_HomeBestPrice = 'a';
	typedef char TTORATstpSPOrderPriceTypeType;

	/////////////////////////////////////////////////////////////////////////
	/// TTORATstpTimeConditionType是一个有效期类型类型
	/////////////////////////////////////////////////////////////////////////
	///立即完成，否则撤销
	const char TORA_TSTP_SP_TC_IOC = '1';
	///本节有效
	const char TORA_TSTP_SP_TC_GFS = '2';
	///当日有效
	const char TORA_TSTP_SP_TC_GFD = '3';
	///指定日期前有效
	const char TORA_TSTP_SP_TC_GTD = '4';
	///撤销前有效
	const char TORA_TSTP_SP_TC_GTC = '5';
	///集合竞价有效
	const char TORA_TSTP_SP_TC_GFA = '6';
	typedef char TTORATstpSPTimeConditionType;

	/////////////////////////////////////////////////////////////////////////
	/// TTORATstpVolumeConditionType是一个成交量类型类型
	/////////////////////////////////////////////////////////////////////////
	///任何数量
	const char TORA_TSTP_SP_VC_AV = '1';
	///最小数量
	const char TORA_TSTP_SP_VC_MV = '2';
	///全部数量
	const char TORA_TSTP_SP_VC_CV = '3';
	typedef char TTORATstpSPVolumeConditionType;

	/////////////////////////////////////////////////////////////////////////
	/// TTORATstpForceCloseReasonType是一个强平原因类型
	/////////////////////////////////////////////////////////////////////////
	///非强平
	const char TORA_TSTP_SP_FCC_NotForceClose = '0';
	///资金不足
	const char TORA_TSTP_SP_FCC_LackDeposit = '1';
	///客户超仓
	const char TORA_TSTP_SP_FCC_ClientOverPositionLimit = '2';
	///会员超仓
	const char TORA_TSTP_SP_FCC_MemberOverPositionLimit = '3';
	///持仓非整数倍
	const char TORA_TSTP_SP_FCC_NotMultiple = '4';
	///违规
	const char TORA_TSTP_SP_FCC_Violation = '5';
	///其它
	const char TORA_TSTP_SP_FCC_Other = '6';
	typedef char TTORATstpSPForceCloseReasonType;

	/////////////////////////////////////////////////////////////////////////
	/// TTORATstpCancelOrderStatusType是一个撤单状态类型
	/////////////////////////////////////////////////////////////////////////
	///撤单已提交
	const char TORA_TSTP_SP_CORDS_Submitted = 'a';
	///撤单已成功
	const char TORA_TSTP_SP_CORDS_Canceled = 'b';
	///撤单失败
	const char TORA_TSTP_SP_CORDS_Fail = 'c';
	typedef char TTORATstpSPCancelOrderStatusType;

	/////////////////////////////////////////////////////////////////////////
	/// TTORATstpTransferDirectionType是一个转移方向类型
	/////////////////////////////////////////////////////////////////////////
	///蓝补
	const char TORA_TSTP_SP_TRNSD_In = '0';
	///红冲
	const char TORA_TSTP_SP_TRNSD_Out = '1';
	///调入
	const char TORA_TSTP_SP_TRNSD_MoveIn = '2';
	///调出
	const char TORA_TSTP_SP_TRNSD_MoveOut = '3';
	///冻结
	const char TORA_TSTP_SP_TRNSD_Freeze = '4';
	///解冻
	const char TORA_TSTP_SP_TRNSD_UnFreeze = '5';
	///银证转入
	const char TORA_TSTP_SP_TRNSD_TransferIn = '6';
	///银证转出
	const char TORA_TSTP_SP_TRNSD_TransferOut = '7';
	typedef char TTORATstpSPTransferDirectionType;

	/////////////////////////////////////////////////////////////////////////
	/// TTORATstpSPStockTransferReasonType是一个个股期权标的现货转移原因类型
	/////////////////////////////////////////////////////////////////////////
	///蓝补
	const char TORA_TSTP_SP_SSTR_In = '0';
	///红冲
	const char TORA_TSTP_SP_SSTR_Out = '1';
	///调入
	const char TORA_TSTP_SP_SSTR_MoveIn = 'a';
	///调出
	const char TORA_TSTP_SP_SSTR_MoveOut = 'b';
	///备兑锁定冻结
	const char TORA_TSTP_SP_SSTR_Lock = 'c';
	///备兑锁定冻结冲正
	const char TORA_TSTP_SP_SSTR_LockRepeal = 'k';
	///备兑锁定撤销解冻
	const char TORA_TSTP_SP_SSTR_LockCancel = 'q';
	///备兑解锁解冻
	const char TORA_TSTP_SP_SSTR_UnLock = 'd';
	///行权冻结
	const char TORA_TSTP_SP_SSTR_Exercise = 'e';
	///行权冻结冲正
	const char TORA_TSTP_SP_SSTR_ExerciseRepeal = 'l';
	///行权撤销解冻
	const char TORA_TSTP_SP_SSTR_ExerciseCancel = 'f';
	///保证金转备兑冻结
	const char TORA_TSTP_SP_SSTR_MarginToCover = 'h';
	///保证金转备兑冻结解冻
	const char TORA_TSTP_SP_SSTR_MarginToCoverRepeal = 'i';
	///保证金转备兑撤销解冻
	const char TORA_TSTP_SP_SSTR_MarginToCoverCancel = 'p';
	///备兑转保证金
	const char TORA_TSTP_SP_SSTR_CoverToMargin = 'j';
	///备兑开仓冻结
	const char TORA_TSTP_SP_SSTR_CoverOpen = 'm';
	///备兑开仓冻结冲正
	const char TORA_TSTP_SP_SSTR_CoverOpenRepeal = 'n';
	///备兑开仓撤销解冻
	const char TORA_TSTP_SP_SSTR_CoverOpenCancel = 'o';
	///备兑平仓解冻
	const char TORA_TSTP_SP_SSTR_CoverClose = 'g';
	typedef char TTORATstpSPSPStockTransferReasonType;

	/////////////////////////////////////////////////////////////////////////
	/// TTORATstpTransferStatusType是一个转移状态类型
	/////////////////////////////////////////////////////////////////////////
	///Transfer正在处理
	const char TORA_TSTP_SP_TRANST_TransferHandling = '0';
	///Transfer成功
	const char TORA_TSTP_SP_TRANST_TransferSuccess = '1';
	///Transfer失败
	const char TORA_TSTP_SP_TRANST_TransferFail = '2';
	///Repeal正在处理
	const char TORA_TSTP_SP_TRANST_RepealHandling = '3';
	///Repeal成功
	const char TORA_TSTP_SP_TRANST_RepealSuccess = '4';
	///Repeal失败
	const char TORA_TSTP_SP_TRANST_RepealFail = '5';
	///外部系统已接收
	const char TORA_TSTP_SP_TRANST_ExternalAccepted = '6';
	typedef char TTORATstpSPTransferStatusType;

	/////////////////////////////////////////////////////////////////////////
	/// TTORATstpTransferPositionTypeType是一个转移持仓类型类型
	/////////////////////////////////////////////////////////////////////////
	///任意仓
	const char TORA_TSTP_SP_TPT_ALL = '0';
	///昨仓
	const char TORA_TSTP_SP_TPT_History = '1';
	///今买卖仓
	const char TORA_TSTP_SP_TPT_TodayBS = '2';
	///今申赎仓
	const char TORA_TSTP_SP_TPT_TodayPR = '3';
	typedef char TTORATstpSPTransferPositionTypeType;

	/////////////////////////////////////////////////////////////////////////
	/// TTORATstpBizRefType是一个业务编号类型
	/////////////////////////////////////////////////////////////////////////
	typedef char TTORATstpSPBizRefType[41];

	/////////////////////////////////////////////////////////////////////////
	/// TTORATstpSystemNameType是一个系统名称类型
	/////////////////////////////////////////////////////////////////////////
	typedef char TTORATstpSPSystemNameType[41];

	/////////////////////////////////////////////////////////////////////////
	/// TTORATstpOrderStatusType是一个报单状态类型
	/////////////////////////////////////////////////////////////////////////
	///核心已处理
	const char TORA_TSTP_SP_OST_Handled = '0';
	///交易所已接收
	const char TORA_TSTP_SP_OST_Accepted = '1';
	///部分成交
	const char TORA_TSTP_SP_OST_PartTraded = '2';
	///全部成交
	const char TORA_TSTP_SP_OST_AllTraded = '3';
	///部撤
	const char TORA_TSTP_SP_OST_PartTradedCancelled = '4';
	///全撤
	const char TORA_TSTP_SP_OST_Cancelled = '5';
	///废单
	const char TORA_TSTP_SP_OST_Failed = '6';
	///预埋
	const char TORA_TSTP_SP_OST_Cached = '7';
	///发往现货系统处理
	const char TORA_TSTP_SP_OST_SendStock = '8';
	///发往交易核心处理
	const char TORA_TSTP_SP_OST_SendTradeKernel = '9';
	///空
	const char TORA_TSTP_SP_OST_NON = 'a';
	typedef char TTORATstpSPOrderStatusType;

	/////////////////////////////////////////////////////////////////////////
	/// TTORATstpOrderOperateStatusType是一个报单操作状态类型
	/////////////////////////////////////////////////////////////////////////
	///已经提交
	const char TORA_TSTP_SP_OOS_InsertSubmitted = '0';
	///撤单已经提交
	const char TORA_TSTP_SP_OOS_CancelSubmitted = '1';
	///已经接受
	const char TORA_TSTP_SP_OOS_Accepted = '2';
	///报单已经被拒绝
	const char TORA_TSTP_SP_OOS_InsertRejected = '3';
	///撤单已经被拒绝
	const char TORA_TSTP_SP_OOS_CancelRejected = '4';
	///未提交
	const char TORA_TSTP_SP_OOS_UnSubmitted = '5';
	typedef char TTORATstpSPOrderOperateStatusType;

	/////////////////////////////////////////////////////////////////////////
	/// TTORATstpOffsetFlagType是一个开平标志类型
	/////////////////////////////////////////////////////////////////////////
	///开仓
	const char TORA_TSTP_SP_OF_Open = '0';
	///平仓
	const char TORA_TSTP_SP_OF_Close = '1';
	///强平
	const char TORA_TSTP_SP_OF_ForceClose = '2';
	///平今
	const char TORA_TSTP_SP_OF_CloseToday = '3';
	///平昨
	const char TORA_TSTP_SP_OF_CloseYesterday = '4';
	///强减
	const char TORA_TSTP_SP_OF_ForceOff = '5';
	///本地强平
	const char TORA_TSTP_SP_OF_LocalForceClose = '6';
	///行权（内部使用）
	const char TORA_TSTP_SP_OF_Exercise = '7';
	///锁定（内部使用）
	const char TORA_TSTP_SP_OF_Lock = '8';
	///解锁（内部使用）
	const char TORA_TSTP_SP_OF_UnLock = '9';
	///组合（内部使用）
	const char TORA_TSTP_SP_OF_Combine = 'a';
	///拆分（内部使用）
	const char TORA_TSTP_SP_OF_Split = 'b';
	///单边平仓
	const char TORA_TSTP_SP_OF_UnilateralClose = 'e';
	typedef char TTORATstpSPOffsetFlagType;

	/////////////////////////////////////////////////////////////////////////
	/// TTORATstpCountType是一个计数类型
	/////////////////////////////////////////////////////////////////////////
	typedef int TTORATstpSPCountType;

	/////////////////////////////////////////////////////////////////////////
	/// TTORATstpHedgeFlagType是一个投机套保标志类型
	/////////////////////////////////////////////////////////////////////////
	///投机
	const char TORA_TSTP_SP_HF_Speculation = '1';
	///套利
	const char TORA_TSTP_SP_HF_Arbitrage = '2';
	///套保
	const char TORA_TSTP_SP_HF_Hedge = '3';
	///备兑
	const char TORA_TSTP_SP_HF_Covered = '4';
	///做市报价(内部使用)
	const char TORA_TSTP_SP_HF_MarketMaker = '5';
	typedef char TTORATstpSPHedgeFlagType;

	/////////////////////////////////////////////////////////////////////////
	/// TTORATstpOrderActionFlagType是一个委托操作标志类型
	/////////////////////////////////////////////////////////////////////////
	///撤单
	const char TORA_TSTP_SP_OAF_Delete = '0';
	///强制撤单
	const char TORA_TSTP_SP_OAF_ForceDelete = '1';
	typedef char TTORATstpSPOrderActionFlagType;

	/////////////////////////////////////////////////////////////////////////
	/// TTORATstpExerciseDirectionType是一个行权方向类型
	/////////////////////////////////////////////////////////////////////////
	///主动行权
	const char TORA_TSTP_SP_EXCD_Active = '0';
	///被动行权
	const char TORA_TSTP_SP_EXCD_Passive = '1';
	typedef char TTORATstpSPExerciseDirectionType;

	/////////////////////////////////////////////////////////////////////////
	/// TTORATstpCoverFlagType是一个备兑标志类型
	/////////////////////////////////////////////////////////////////////////
	///非备兑
	const char TORA_TSTP_SP_CVF_Uncovered = '0';
	///备兑
	const char TORA_TSTP_SP_CVF_Covered = '1';
	typedef char TTORATstpSPCoverFlagType;

	/////////////////////////////////////////////////////////////////////////
	/// TTORATstpMDSubModeType是一个行情订阅模式类型
	/////////////////////////////////////////////////////////////////////////
	///TCP连接模式
	const char TORA_TSTP_SP_MST_TCP = '0';
	///UDP单播模式
	const char TORA_TSTP_SP_MST_UDP = '1';
	///UDP组播模式
	const char TORA_TSTP_SP_MST_MCAST = '2';
	typedef char TTORATstpSPMDSubModeType;

	/////////////////////////////////////////////////////////////////////////
	/// TTORATstpShareholderIDTypeType是一个股东代码类型类型
	/////////////////////////////////////////////////////////////////////////
	///未知
	const char TORA_TSTP_SP_SHID_Unknown = '0';
	///普通
	const char TORA_TSTP_SP_SHID_Normal = '1';
	///信用
	const char TORA_TSTP_SP_SHID_Credit = '2';
	///衍生品
	const char TORA_TSTP_SP_SHID_Derivatives = '3';
	typedef char TTORATstpSPShareholderIDTypeType;

	/////////////////////////////////////////////////////////////////////////
	/// TTORATstpStrikeModeType是一个执行方式类型
	/////////////////////////////////////////////////////////////////////////
	///欧式
	const char TORA_TSTP_SP_STM_Continental = '0';
	///美式
	const char TORA_TSTP_SP_STM_American = '1';
	///百慕大
	const char TORA_TSTP_SP_STM_Bermuda = '2';
	typedef char TTORATstpSPStrikeModeType;

	/////////////////////////////////////////////////////////////////////////
	/// TTORATstpOptionsTypeType是一个期权类型类型
	/////////////////////////////////////////////////////////////////////////
	///看涨
	const char TORA_TSTP_SP_CP_CallOptions = '1';
	///看跌
	const char TORA_TSTP_SP_CP_PutOptions = '2';
	typedef char TTORATstpSPOptionsTypeType;

	/////////////////////////////////////////////////////////////////////////
	/// TTORATstpProductIDType是一个合约品种代码类型
	/////////////////////////////////////////////////////////////////////////
	///通用(内部使用)
	const char TORA_TSTP_SP_PID_COMMON = '0';
	///上海股票
	const char TORA_TSTP_SP_PID_SHStock = '1';
	///上海基金
	const char TORA_TSTP_SP_PID_SHFund = '3';
	///上海债券
	const char TORA_TSTP_SP_PID_SHBond = '4';
	///深圳股票
	const char TORA_TSTP_SP_PID_SZStock = '7';
	///深圳基金
	const char TORA_TSTP_SP_PID_SZFund = '9';
	///深圳债券
	const char TORA_TSTP_SP_PID_SZBond = 'a';
	///上海个股期权
	const char TORA_TSTP_SP_PID_SHStockOption = 'd';
	///深圳个股期权
	const char TORA_TSTP_SP_PID_SZStockOption = 'e';
	typedef char TTORATstpSPProductIDType;

	/////////////////////////////////////////////////////////////////////////
	/// TTORATstpSecurityTypeType是一个合约类别类型
	/////////////////////////////////////////////////////////////////////////
	///通用(内部使用)
	const char TORA_TSTP_SP_STP_COMMON = '0';
	///上海股票型看涨期权
	const char TORA_TSTP_SP_STP_SHCallAStockOption = '1';
	///上海股票型看跌期权
	const char TORA_TSTP_SP_STP_SHPullAStockOption = '2';
	///上海基金型看涨期权
	const char TORA_TSTP_SP_STP_SHCallFundStockOption = '3';
	///上海基金型看跌期权
	const char TORA_TSTP_SP_STP_SHPullFundStockOption = '4';
	///深圳股票型看涨期权
	const char TORA_TSTP_SP_STP_SZCallAStockOption = '5';
	///深圳股票型看跌期权
	const char TORA_TSTP_SP_STP_SZPullAStockOption = '6';
	///深圳基金型看涨期权
	const char TORA_TSTP_SP_STP_SZCallFundStockOption = '7';
	///深圳基金型看跌期权
	const char TORA_TSTP_SP_STP_SZPullFundStockOption = '8';
	///上海组合期权
	const char TORA_TSTP_SP_STP_SHCombOption = '9';
	///深圳组合期权
	const char TORA_TSTP_SP_STP_SZCombOption = 'a';
	typedef char TTORATstpSPSecurityTypeType;

	/////////////////////////////////////////////////////////////////////////
	/// TTORATstpBusinessClassType是一个业务类别类型
	/////////////////////////////////////////////////////////////////////////
	///买入开仓
	const char TORA_TSTP_SP_BC_BuyOpen = 'A';
	///买入平仓
	const char TORA_TSTP_SP_BC_BuyClose = 'B';
	///卖出开仓
	const char TORA_TSTP_SP_BC_SellOpen = 'C';
	///卖出平仓
	const char TORA_TSTP_SP_BC_SellClose = 'D';
	///备兑开仓
	const char TORA_TSTP_SP_BC_CoveredOpen = 'E';
	///备兑平仓
	const char TORA_TSTP_SP_BC_CoveredClose = 'F';
	///行权
	const char TORA_TSTP_SP_BC_ExecOrder = 'G';
	///单边平仓（单平义务仓）
	const char TORA_TSTP_SP_BC_UnilateralBuyClose = 'H';
	///无效
	const char TORA_TSTP_SP_BC_Invalid = 'I';
	///报价买入开仓
	const char TORA_TSTP_SP_BC_QuoteBuyOpen = 'J';
	///报价买入平仓
	const char TORA_TSTP_SP_BC_QuoteBuyClose = 'K';
	///报价卖出开仓
	const char TORA_TSTP_SP_BC_QuoteSellOpen = 'L';
	///报价卖出平仓
	const char TORA_TSTP_SP_BC_QuoteSellClose = 'M';
	typedef char TTORATstpSPBusinessClassType;

	/////////////////////////////////////////////////////////////////////////
	/// TTORATstpSystemFlagType是一个系统标识类型
	/////////////////////////////////////////////////////////////////////////
	///现货系统
	const char TORA_TSTP_SP_SFT_Stock = '0';
	///期权系统
	const char TORA_TSTP_SP_SFT_Option = '1';
	///两融系统
	const char TORA_TSTP_SP_SFT_Credit = '2';
	///行情系统
	const char TORA_TSTP_SP_SFT_MarketData = '3';
	///Lev2行情系统
	const char TORA_TSTP_SP_SFT_Lev2MarketData = '4';
	typedef char TTORATstpSPSystemFlagType;

	/////////////////////////////////////////////////////////////////////////
	/// TTORATstpPosiDirectionType是一个持仓多空方向类型
	/////////////////////////////////////////////////////////////////////////
	///净
	const char TORA_TSTP_SP_PD_Net = '1';
	///多头
	const char TORA_TSTP_SP_PD_Long = '2';
	///空头
	const char TORA_TSTP_SP_PD_Short = '3';
	typedef char TTORATstpSPPosiDirectionType;

	/////////////////////////////////////////////////////////////////////////
	/// TTORATstpMarketIDType是一个市场代码类型
	/////////////////////////////////////////////////////////////////////////
	///通用(内部使用)
	const char TORA_TSTP_SP_MKD_COMMON = '0';
	///上海A股
	const char TORA_TSTP_SP_MKD_SHA = '1';
	///深圳A股
	const char TORA_TSTP_SP_MKD_SZA = '2';
	///上海B股
	const char TORA_TSTP_SP_MKD_SHB = '3';
	///深圳B股
	const char TORA_TSTP_SP_MKD_SZB = '4';
	///深圳三版A股
	const char TORA_TSTP_SP_MKD_SZThreeA = '5';
	///深圳三版B股
	const char TORA_TSTP_SP_MKD_SZThreeB = '6';
	///境外市场
	const char TORA_TSTP_SP_MKD_Foreign = '7';
	typedef char TTORATstpSPMarketIDType;

	/////////////////////////////////////////////////////////////////////////
	/// TTORATstpLogInAccountType是一个登录账户类型
	/////////////////////////////////////////////////////////////////////////
	typedef char TTORATstpSPLogInAccountType[21];

	/////////////////////////////////////////////////////////////////////////
	/// TTORATstpLogInAccountTypeType是一个登录账户类型类型
	/////////////////////////////////////////////////////////////////////////
	///用户代码
	const char TORA_TSTP_SP_LACT_UserID = '0';
	///资金账号
	const char TORA_TSTP_SP_LACT_AccountID = '1';
	///上海A股
	const char TORA_TSTP_SP_LACT_SHAStock = '2';
	///深圳A股
	const char TORA_TSTP_SP_LACT_SZAStock = '3';
	///上海B股
	const char TORA_TSTP_SP_LACT_SHBStock = '4';
	///深圳B股
	const char TORA_TSTP_SP_LACT_SZBStock = '5';
	///三板A
	const char TORA_TSTP_SP_LACT_ThreeNewBoardA = '6';
	///三板B
	const char TORA_TSTP_SP_LACT_ThreeNewBoardB = '7';
	///港股
	const char TORA_TSTP_SP_LACT_HKStock = '8';
	///统一用户代码
	const char TORA_TSTP_SP_LACT_UnifiedUserID = '9';
	typedef char TTORATstpSPLogInAccountTypeType;

	/////////////////////////////////////////////////////////////////////////
	/// TTORATstpMarketStatusType是一个市场状态类型
	/////////////////////////////////////////////////////////////////////////
	///未知
	const char TORA_TSTP_SP_MST_UnKnown = '#';
	///开盘前
	const char TORA_TSTP_SP_MST_BeforeTrading = '0';
	///连续交易
	const char TORA_TSTP_SP_MST_Continous = '1';
	///收盘
	const char TORA_TSTP_SP_MST_Closed = '2';
	///开盘集合竞价
	const char TORA_TSTP_SP_MST_OpenCallAuction = '3';
	typedef char TTORATstpSPMarketStatusType;

	/////////////////////////////////////////////////////////////////////////
	/// TTORATstpBigsInfoType是一个长字符串附加信息类型
	/////////////////////////////////////////////////////////////////////////
	typedef char TTORATstpSPBigsInfoType[33];

	/////////////////////////////////////////////////////////////////////////
	/// TTORATstpShortsInfoType是一个短字符串附加信息类型
	/////////////////////////////////////////////////////////////////////////
	typedef char TTORATstpSPShortsInfoType[9];

	/////////////////////////////////////////////////////////////////////////
	/// TTORATstpIntInfoType是一个整形附加信息类型
	/////////////////////////////////////////////////////////////////////////
	typedef int TTORATstpSPIntInfoType;

	/////////////////////////////////////////////////////////////////////////
	/// TTORATstpApiGroupIDType是一个Api工作组号类型
	/////////////////////////////////////////////////////////////////////////
	typedef int TTORATstpSPApiGroupIDType;

	/////////////////////////////////////////////////////////////////////////
	/// TTORATstpApiRunModeType是一个Api运行模式类型
	/////////////////////////////////////////////////////////////////////////
	///单一
	const char TORA_TSTP_SP_ARM_Single = '0';
	///集群
	const char TORA_TSTP_SP_ARM_Group = '1';
	typedef char TTORATstpSPApiRunModeType;

	/////////////////////////////////////////////////////////////////////////
	/// TTORATstpInvestorLevelType是一个投资者分级类别类型
	/////////////////////////////////////////////////////////////////////////
	///不合格投资人
	const char TORA_TSTP_SP_IVL_Invalid = '0';
	///一级
	const char TORA_TSTP_SP_IVL_First = '1';
	///二级
	const char TORA_TSTP_SP_IVL_Second = '2';
	///三级
	const char TORA_TSTP_SP_IVL_Third = '3';
	typedef char TTORATstpSPInvestorLevelType;

	/////////////////////////////////////////////////////////////////////////
	/// TTORATstpCondCheckType是一个委托条件检查类型
	/////////////////////////////////////////////////////////////////////////
	///不做任何检查
	const char TORA_TSTP_SP_CCT_None = '0';
	///自成交检查
	const char TORA_TSTP_SP_CCT_SelfDeal = '1';
	typedef char TTORATstpSPCondCheckType;

	/////////////////////////////////////////////////////////////////////////
	/// TTORATstpHDSerialType是一个硬盘序列号类型
	/////////////////////////////////////////////////////////////////////////
	typedef char TTORATstpSPHDSerialType[33];

	/////////////////////////////////////////////////////////////////////////
	/// TTORATstpStatusMsgType是一个状态信息类型
	/////////////////////////////////////////////////////////////////////////
	typedef char TTORATstpSPStatusMsgType[121];

	/////////////////////////////////////////////////////////////////////////
	/// TTORATstpLockTypeType是一个锁定类别类型
	/////////////////////////////////////////////////////////////////////////
	///锁定
	const char TORA_TSTP_SP_LT_Lock = '0';
	///解锁
	const char TORA_TSTP_SP_LT_UnLock = '1';
	typedef char TTORATstpSPLockTypeType;

	/////////////////////////////////////////////////////////////////////////
	/// TTORATstpLockStatusType是一个锁定申报状态类型
	/////////////////////////////////////////////////////////////////////////
	///发往现货系统
	const char TORA_TSTP_SP_LST_SendStock = '0';
	///发往报盘
	const char TORA_TSTP_SP_LST_SendOffer = '2';
	///锁定/解锁失败
	const char TORA_TSTP_SP_LST_Fail = '3';
	///锁定/解锁成功
	const char TORA_TSTP_SP_LST_Success = '4';
	///强制撤销
	const char TORA_TSTP_SP_LST_ForceCancell = '5';
	typedef char TTORATstpSPLockStatusType;

	/////////////////////////////////////////////////////////////////////////
	/// TTORATstpExerciseTypeType是一个行权执行类型类型
	/////////////////////////////////////////////////////////////////////////
	///执行
	const char TORA_TSTP_SP_EXERT_Execute = '1';
	///放弃
	const char TORA_TSTP_SP_EXERT_Drop = '2';
	typedef char TTORATstpSPExerciseTypeType;

	/////////////////////////////////////////////////////////////////////////
	/// TTORATstpExerciseStatusType是一个行权执行状态类型
	/////////////////////////////////////////////////////////////////////////
	///发往现货系统
	const char TORA_TSTP_SP_EXERS_SendStock = '0';
	///发往报盘
	const char TORA_TSTP_SP_EXERS_SendOffer = '2';
	///行权失败
	const char TORA_TSTP_SP_EXERS_Fail = '3';
	///交易所已接收
	const char TORA_TSTP_SP_EXERS_Accepted = '4';
	///行权已撤销
	const char TORA_TSTP_SP_EXERS_Cancelled = '5';
	typedef char TTORATstpSPExerciseStatusType;

	/////////////////////////////////////////////////////////////////////////
	/// TTORATstpStockDisposalTypeType是一个证券处置类别类型
	/////////////////////////////////////////////////////////////////////////
	///划入到证券公司账户
	const char TORA_TSTP_SP_SDT_Broker = '1';
	///划入到投资者证券账户
	const char TORA_TSTP_SP_SDT_Investor = '2';
	typedef char TTORATstpSPStockDisposalTypeType;

	/////////////////////////////////////////////////////////////////////////
	/// TTORATstpStockDisposalStatusType是一个证券处置状态类型
	/////////////////////////////////////////////////////////////////////////
	///发往报盘
	const char TORA_TSTP_SP_SDS_SendOffer = '1';
	///失败
	const char TORA_TSTP_SP_SDS_Fail = '2';
	///交易所已接收
	const char TORA_TSTP_SP_SDS_Accepted = '3';
	///证券处置已撤销
	const char TORA_TSTP_SP_SDS_Cancelled = '4';
	typedef char TTORATstpSPStockDisposalStatusType;

	/////////////////////////////////////////////////////////////////////////
	/// TTORATstpCombinationStrategyType是一个组合策略类型
	/////////////////////////////////////////////////////////////////////////
	///认购牛市价差策略
	const char TORA_TSTP_SP_CBS_CNSJC = '1';
	///认购熊市价差策略
	const char TORA_TSTP_SP_CBS_CXSJC = '2';
	///认沽熊市价差策略
	const char TORA_TSTP_SP_CBS_PXSJC = '3';
	///认沽牛市价差策略
	const char TORA_TSTP_SP_CBS_PNSJC = '4';
	///跨式空头
	const char TORA_TSTP_SP_CBS_KS = '5';
	///宽跨式空头
	const char TORA_TSTP_SP_CBS_KKS = '6';
	///保证金开仓转备兑
	const char TORA_TSTP_SP_CBS_ZBD = '7';
	///备兑仓转普通
	const char TORA_TSTP_SP_CBS_ZXJ = '8';
	typedef char TTORATstpSPCombinationStrategyType;

	/////////////////////////////////////////////////////////////////////////
	/// TTORATstpMDSecurityStatType是一个行情证券状态类型
	/////////////////////////////////////////////////////////////////////////
	///开盘前
	const char TORA_TSTP_SP_MSST_PreOpen = '0';
	///集合竞价
	const char TORA_TSTP_SP_MSST_CallAuction = '1';
	///连续交易
	const char TORA_TSTP_SP_MSST_Continous = '2';
	///休市
	const char TORA_TSTP_SP_MSST_Pause = '3';
	///停牌
	const char TORA_TSTP_SP_MSST_Suspend = '4';
	///长期停牌
	const char TORA_TSTP_SP_MSST_LongSuspend = '5';
	///波动性中断
	const char TORA_TSTP_SP_MSST_UndulationInt = '6';
	///熔断可恢复
	const char TORA_TSTP_SP_MSST_CircuitBreak = '7';
	///熔断不可恢复
	const char TORA_TSTP_SP_MSST_CircuitBreakU = '8';
	///闭市
	const char TORA_TSTP_SP_MSST_Close = '9';
	///其它
	const char TORA_TSTP_SP_MSST_Other = 'a';
	///收盘集合竞价
	const char TORA_TSTP_SP_MSST_CloseCallAuction = 'b';
	typedef char TTORATstpSPMDSecurityStatType;

	/////////////////////////////////////////////////////////////////////////
	/// TTORATstpCondOrderIDType是一个条件报单编号类型
	/////////////////////////////////////////////////////////////////////////
	typedef int TTORATstpSPCondOrderIDType;

	/////////////////////////////////////////////////////////////////////////
	/// TTORATstpContingentConditionType是一个触发条件类型
	/////////////////////////////////////////////////////////////////////////
	///成交触发
	const char TORA_TSTP_SP_CC_TradeTouch = '0';
	///撤单触发
	const char TORA_TSTP_SP_CC_CancelTouch = '1';
	///时间触发
	const char TORA_TSTP_SP_CC_TimeTouch = '2';
	///交易时段触发
	const char TORA_TSTP_SP_CC_SegmentTouch = '3';
	///最新价大于等于条件价
	const char TORA_TSTP_SP_CC_LastPriceGreaterThanStopPrice = '4';
	///最新价小于等于条件价
	const char TORA_TSTP_SP_CC_LastPriceLesserThanStopPrice = '5';
	///卖一价大于等于条件价
	const char TORA_TSTP_SP_CC_AskPriceGreaterEqualStopPrice = '6';
	///卖一价小于等于条件价
	const char TORA_TSTP_SP_CC_AskPriceLesserEqualStopPrice = '7';
	///买一价大于等于条件价
	const char TORA_TSTP_SP_CC_BidPriceGreaterEqualStopPrice = '8';
	///买一价小于等于条件价
	const char TORA_TSTP_SP_CC_BidPriceLesserEqualStopPrice = '9';
	typedef char TTORATstpSPContingentConditionType;

	/////////////////////////////////////////////////////////////////////////
	/// TTORATstpOrderVolumeTypeType是一个报单数量类型类型
	/////////////////////////////////////////////////////////////////////////
	///自定义数量
	const char TORA_TSTP_SP_OVT_CustomVol = '1';
	///相关数量
	const char TORA_TSTP_SP_OVT_RelativeVol = '2';
	typedef char TTORATstpSPOrderVolumeTypeType;

	/////////////////////////////////////////////////////////////////////////
	/// TTORATstpCondOrderStatusType是一个条件单状态类型
	/////////////////////////////////////////////////////////////////////////
	///初始
	const char TORA_TSTP_SP_COST_Initial = '#';
	///未触发
	const char TORA_TSTP_SP_COST_NotTouched = '0';
	///已触发
	const char TORA_TSTP_SP_COST_Touched = '1';
	///已结束
	const char TORA_TSTP_SP_COST_Finished = '2';
	///已撤销
	const char TORA_TSTP_SP_COST_Cancel = '3';
	///触发失败
	const char TORA_TSTP_SP_COST_Failed = '4';
	typedef char TTORATstpSPCondOrderStatusType;

	/////////////////////////////////////////////////////////////////////////
	/// TTORATstpRelativeCondParamType是一个相关条件参数类型
	/////////////////////////////////////////////////////////////////////////
	typedef char TTORATstpSPRelativeCondParamType[31];

	/////////////////////////////////////////////////////////////////////////
	/// TTORATstpMessageType是一个通知消息类型
	/////////////////////////////////////////////////////////////////////////
	typedef char TTORATstpSPMessageType[513];

	/////////////////////////////////////////////////////////////////////////
	/// TTORATstpRiskLevelType是一个风险级别类型
	/////////////////////////////////////////////////////////////////////////
	///正常
	const char TORA_TSTP_SP_RL_None = '0';
	///警示
	const char TORA_TSTP_SP_RL_Warn = '1';
	///追保
	const char TORA_TSTP_SP_RL_Call = '2';
	///强平
	const char TORA_TSTP_SP_RL_Force = '3';
	///穿仓
	const char TORA_TSTP_SP_RL_Wear = '4';
	///异常
	const char TORA_TSTP_SP_RL_Exception = '5';
	typedef char TTORATstpSPRiskLevelType;
}
#endif