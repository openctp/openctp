/////////////////////////////////////////////////////////////////////////
///@company 上海泰琰信息科技有限公司
///@file TORATstpSPTraderApi.h
///@brief 定义了客户端接口
///@history 
/////////////////////////////////////////////////////////////////////////

#ifndef _TORA_TSTPSPTRADERAPI_H
#define _TORA_TSTPSPTRADERAPI_H

#include "TORATstpSPUserApiStruct.h"

#ifdef SPTRADER_API_EXPORT
#ifdef WINDOWS
#define SPTRADER_API_DLL_EXPORT __declspec(dllexport)
#else
#define SPTRADER_API_DLL_EXPORT __attribute__ ((visibility("default")))
#endif
#else
#define SPTRADER_API_DLL_EXPORT 
#endif

namespace TORASPAPI
{
	class CTORATstpSPTraderSpi
	{
	public:
		///当客户端与交易后台建立起通信连接时（还未登录前），该方法被调用。
		virtual void OnFrontConnected(){};
		
		///当客户端与交易后台通信连接断开时，该方法被调用。当发生这个情况后，API会自动重新连接，客户端可不做处理。
		///@param nReason 错误原因
		///        -3 连接已断开
		///        -4 网络读失败
		///        -5 网络写失败
		///        -6 订阅流错误
		///        -7 流序号错误
		///        -8 错误的心跳报文
		///        -9 错误的报文
		///		  -15 网络读失败
		///		  -16 网络写失败
		virtual void OnFrontDisconnected(int nReason){};
			
		///错误应答
		virtual void OnRspError(CTORATstpSPRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};
		
		///获取连接信息应答
		virtual void OnRspGetConnectionInfo(CTORATstpSPConnectionInfoField *pConnectionInfoField, CTORATstpSPRspInfoField *pRspInfoField, int nRequestID) {};
		
		
		//登录应答
		virtual void OnRspUserLogin(CTORATstpSPRspUserLoginField *pRspUserLoginField, CTORATstpSPRspInfoField *pRspInfo, int nRequestID) {};
		
		//登出应答
		virtual void OnRspUserLogout(CTORATstpSPUserLogoutField *pUserLogoutField, CTORATstpSPRspInfoField *pRspInfo, int nRequestID) {};
		
		//修改密码应答
		virtual void OnRspUserPasswordUpdate(CTORATstpSPUserPasswordUpdateField *pUserPasswordUpdateField, CTORATstpSPRspInfoField *pRspInfo, int nRequestID) {};
		
		//请求录入设备序列应答
		virtual void OnRspInputDeviceSerial(CTORATstpSPRspInputDeviceSerialField *pRspInputDeviceSerialField, CTORATstpSPRspInfoField *pRspInfo, int nRequestID) {};
		
		//报单录入应答
		virtual void OnRspOrderInsert(CTORATstpSPInputOrderField *pInputOrderField, CTORATstpSPRspInfoField *pRspInfo, int nRequestID) {};
		
		//报单回报
		virtual void OnRtnOrder(CTORATstpSPOrderField *pOrder) {};
		
		//报单错误回报
		virtual void OnErrRtnOrderInsert(CTORATstpSPInputOrderField *pInputOrder, CTORATstpSPRspInfoField *pRspInfo,int nRequestID) {};
		
		//撤单应答
		virtual void OnRspOrderAction(CTORATstpSPInputOrderActionField *pInputOrderActionField, CTORATstpSPRspInfoField *pRspInfo, int nRequestID) {};
		
		//撤单错误回报
		virtual void OnErrRtnOrderAction(CTORATstpSPInputOrderActionField *pInputOrderAction, CTORATstpSPRspInfoField *pRspInfo,int nRequestID) {};
		
		//成交回报
		virtual void OnRtnTrade(CTORATstpSPTradeField *pTrade) {};
		
		//行权请求响应
		virtual void OnRspExerciseInsert(CTORATstpSPInputExerciseField *pInputExerciseField, CTORATstpSPRspInfoField *pRspInfo, int nRequestID) {};
		
		//行权回报
		virtual void OnRtnExercise(CTORATstpSPExerciseField *pExercise) {};
		
		//行权请求错误回报
		virtual void OnErrRtnExerciseInsert(CTORATstpSPInputExerciseField *pInputExercise, CTORATstpSPRspInfoField *pRspInfo,int nRequestID) {};
		
		//行权操作响应
		virtual void OnRspExerciseAction(CTORATstpSPInputExerciseActionField *pInputExerciseActionField, CTORATstpSPRspInfoField *pRspInfo, int nRequestID) {};
		
		//行权操作错误回报
		virtual void OnErrRtnExerciseAction(CTORATstpSPInputExerciseActionField *pInputExerciseAction, CTORATstpSPRspInfoField *pRspInfo,int nRequestID) {};
		
		//锁定录入请求响应
		virtual void OnRspLockInsert(CTORATstpSPInputLockField *pInputLockField, CTORATstpSPRspInfoField *pRspInfo, int nRequestID) {};
		
		//锁定通知
		virtual void OnRtnLock(CTORATstpSPLockField *pLock) {};
		
		//锁定录入错误回报
		virtual void OnErrRtnLockInsert(CTORATstpSPInputLockField *pInputLock, CTORATstpSPRspInfoField *pRspInfo,int nRequestID) {};
		
		//锁定操作响应
		virtual void OnRspLockAction(CTORATstpSPInputLockActionField *pInputLockActionField, CTORATstpSPRspInfoField *pRspInfo, int nRequestID) {};
		
		//锁定操作错误回报
		virtual void OnErrRtnLockAction(CTORATstpSPInputLockActionField *pInputLockAction, CTORATstpSPRspInfoField *pRspInfo,int nRequestID) {};
		
		//证券处置回报
		virtual void OnRtnStockDisposal(CTORATstpSPStockDisposalField *pStockDisposal) {};
		
		//组合委托录入请求响应
		virtual void OnRspCombOrderInsert(CTORATstpSPInputCombOrderField *pInputCombOrderField, CTORATstpSPRspInfoField *pRspInfo, int nRequestID) {};
		
		//组合委托回报
		virtual void OnRtnCombOrder(CTORATstpSPCombOrderField *pCombOrder) {};
		
		//组合委托请求错误回报
		virtual void OnErrRtnCombOrderInsert(CTORATstpSPInputCombOrderField *pInputCombOrder, CTORATstpSPRspInfoField *pRspInfo,int nRequestID) {};
		
		//组合委托操作响应
		virtual void OnRspCombOrderAction(CTORATstpSPInputCombOrderActionField *pInputCombOrderActionField, CTORATstpSPRspInfoField *pRspInfo, int nRequestID) {};
		
		//组合委托操作错误回报
		virtual void OnErrRtnCombOrderAction(CTORATstpSPInputCombOrderActionField *pInputCombOrderAction, CTORATstpSPRspInfoField *pRspInfo,int nRequestID) {};
		
		//条件单录入请求响应
		virtual void OnRspCondOrderInsert(CTORATstpSPInputCondOrderField *pInputCondOrderField, CTORATstpSPRspInfoField *pRspInfo, int nRequestID) {};
		
		//条件单回报
		virtual void OnRtnCondOrder(CTORATstpSPConditionOrderField *pConditionOrder) {};
		
		//条件单错误回报
		virtual void OnErrRtnCondOrderInsert(CTORATstpSPInputCondOrderField *pInputCondOrder, CTORATstpSPRspInfoField *pRspInfo,int nRequestID) {};
		
		//条件单撤单应答
		virtual void OnRspCondOrderAction(CTORATstpSPInputCondOrderActionField *pInputCondOrderActionField, CTORATstpSPRspInfoField *pRspInfo, int nRequestID) {};
		
		//条件单撤单错误回报
		virtual void OnErrRtnCondOrderAction(CTORATstpSPInputCondOrderActionField *pInputCondOrderAction, CTORATstpSPRspInfoField *pRspInfo,int nRequestID) {};
		
		//合并行权请求响应
		virtual void OnRspCombExerciseInsert(CTORATstpSPInputCombExerciseField *pInputCombExerciseField, CTORATstpSPRspInfoField *pRspInfo, int nRequestID) {};
		
		//合并行权回报
		virtual void OnRtnCombExercise(CTORATstpSPCombExerciseField *pCombExercise) {};
		
		//合并行权请求错误回报
		virtual void OnErrRtnCombExerciseInsert(CTORATstpSPInputCombExerciseField *pInputCombExercise, CTORATstpSPRspInfoField *pRspInfo,int nRequestID) {};
		
		//合并行权操作响应
		virtual void OnRspCombExerciseAction(CTORATstpSPInputCombExerciseActionField *pInputCombExerciseActionField, CTORATstpSPRspInfoField *pRspInfo, int nRequestID) {};
		
		//合并行权操作错误回报
		virtual void OnErrRtnCombExerciseAction(CTORATstpSPInputCombExerciseActionField *pInputCombExerciseAction, CTORATstpSPRspInfoField *pRspInfo,int nRequestID) {};
		
		//查询最大可锁定数量响应
		virtual void OnRspInquiryMaxLockVolume(CTORATstpSPRspInquiryMaxLockVolumeField *pRspInquiryMaxLockVolumeField, CTORATstpSPRspInfoField *pRspInfo, int nRequestID) {};
		
		//查询最大可备兑现货数量响应
		virtual void OnRspInquiryMaxCoverVolume(CTORATstpSPRspInquiryMaxCoverVolumeField *pRspInquiryMaxCoverVolumeField, CTORATstpSPRspInfoField *pRspInfo, int nRequestID) {};
		
		//查询拆分组合合约后保证金差额变动请求响应
		virtual void OnRspInquirySplitCombMarginDifference(CTORATstpSPRspInquirySplitCombMarginDifferenceField *pRspInquirySplitCombMarginDifferenceField, CTORATstpSPRspInfoField *pRspInfo, int nRequestID) {};
		
		//资金转移请求应答
		virtual void OnRspTransferFund(CTORATstpSPInputTransferFundField *pInputTransferFundField, CTORATstpSPRspInfoField *pRspInfo, int nRequestID) {};
		
		//资金转移回报
		virtual void OnRtnTransferFund(CTORATstpSPTransferFundField *pTransferFund) {};
		
		//资金转移错误回报
		virtual void OnErrRtnTransferFund(CTORATstpSPInputTransferFundField *pInputTransferFund, CTORATstpSPRspInfoField *pRspInfo,int nRequestID) {};
		
		//仓位转移回报
		virtual void OnRtnTransferPosition(CTORATstpSPTransferPositionField *pTransferPosition) {};
		
		//仓位转移错误回报
		virtual void OnErrRtnTransferPosition(CTORATstpSPInputTransferPositionField *pInputTransferPosition, CTORATstpSPRspInfoField *pRspInfo,int nRequestID) {};
		
		//现货仓位转移请求响应
		virtual void OnRspTransferStockPosition(CTORATstpSPInputTransferStockPositionField *pInputTransferStockPositionField, CTORATstpSPRspInfoField *pRspInfo, int nRequestID) {};
		
		//现货仓位转移回报
		virtual void OnRtnTransferStockPosition(CTORATstpSPTransferStockPositionField *pTransferStockPosition) {};
		
		//现货仓位转移错误回报
		virtual void OnErrRtnTransferStockPosition(CTORATstpSPInputTransferStockPositionField *pInputTransferStockPosition, CTORATstpSPRspInfoField *pRspInfo,int nRequestID) {};
		
		//查询集中交易系统资金响应
		virtual void OnRspInquiryJZFund(CTORATstpSPRspInquiryJZFundField *pRspInquiryJZFundField, CTORATstpSPRspInfoField *pRspInfo, int nRequestID) {};
		
		//查询银行账户余额响应
		virtual void OnRspInquiryBankAccountFund(CTORATstpSPRspInquiryBankAccountFundField *pRspInquiryBankAccountFundField, CTORATstpSPRspInfoField *pRspInfo, int nRequestID) {};
		
		//查询现货系统现货持仓响应
		virtual void OnRspInquiryStockPosition(CTORATstpSPRspInquiryStockPositionField *pRspInquiryStockPositionField, CTORATstpSPRspInfoField *pRspInfo, int nRequestID) {};
		
		//市场状态通知
		virtual void OnRtnMarketStatus(CTORATstpSPMarketStatusField *pMarketStatus) {};
		
		//交易通知回报
		virtual void OnRtnTradingNotice(CTORATstpSPTradingNoticeField *pTradingNotice) {};
		
		//查询交易所
		virtual void OnRspQryExchange(CTORATstpSPExchangeField *pExchange, CTORATstpSPRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {}; 
		
		//查询实时行情
		virtual void OnRspQryMarketData(CTORATstpSPMarketDataField *pMarketData, CTORATstpSPRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {}; 
		
		//查询证券信息
		virtual void OnRspQrySecurity(CTORATstpSPSecurityField *pSecurity, CTORATstpSPRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {}; 
		
		//查询代理关系
		virtual void OnRspQryBUProxy(CTORATstpSPBUProxyField *pBUProxy, CTORATstpSPRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {}; 
		
		//查询User
		virtual void OnRspQryUser(CTORATstpSPUserField *pUser, CTORATstpSPRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {}; 
		
		//查询投资者
		virtual void OnRspQryInvestor(CTORATstpSPInvestorField *pInvestor, CTORATstpSPRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {}; 
		
		//查询股东账户
		virtual void OnRspQryShareholderAccount(CTORATstpSPShareholderAccountField *pShareholderAccount, CTORATstpSPRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {}; 
		
		//资金账户查询
		virtual void OnRspQryTradingAccount(CTORATstpSPTradingAccountField *pTradingAccount, CTORATstpSPRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {}; 
		
		//报单查询
		virtual void OnRspQryOrder(CTORATstpSPOrderField *pOrder, CTORATstpSPRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {}; 
		
		//成交查询
		virtual void OnRspQryTrade(CTORATstpSPTradeField *pTrade, CTORATstpSPRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {}; 
		
		//投资者持仓查询
		virtual void OnRspQryPosition(CTORATstpSPPositionField *pPosition, CTORATstpSPRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {}; 
		
		//查询基础交易费用
		virtual void OnRspQryTradingFee(CTORATstpSPTradingFeeField *pTradingFee, CTORATstpSPRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {}; 
		
		//查询佣金费率
		virtual void OnRspQryInvestorTradingFee(CTORATstpSPInvestorTradingFeeField *pInvestorTradingFee, CTORATstpSPRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {}; 
		
		//查询保证金费率
		virtual void OnRspQryInvestorMarginFee(CTORATstpSPInvestorMarginFeeField *pInvestorMarginFee, CTORATstpSPRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {}; 
		
		//报单明细资金查询
		virtual void OnRspQryOrderFundDetail(CTORATstpSPOrderFundDetailField *pOrderFundDetail, CTORATstpSPRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {}; 
		
		//查询资金转移流水
		virtual void OnRspQryFundTransferDetail(CTORATstpSPFundTransferDetailField *pFundTransferDetail, CTORATstpSPRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {}; 
		
		//查询持仓转移流水
		virtual void OnRspQryPositionTransferDetail(CTORATstpSPPositionTransferDetailField *pPositionTransferDetail, CTORATstpSPRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {}; 
		
		//查询撤单
		virtual void OnRspQryOrderAction(CTORATstpSPOrderActionField *pOrderAction, CTORATstpSPRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {}; 
		
		//查询现货持仓
		virtual void OnRspQryStockPosition(CTORATstpSPStockPositionField *pStockPosition, CTORATstpSPRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {}; 
		
		//查询锁定委托
		virtual void OnRspQryLock(CTORATstpSPLockField *pLock, CTORATstpSPRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {}; 
		
		//查询行权委托
		virtual void OnRspQryExercise(CTORATstpSPExerciseField *pExercise, CTORATstpSPRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {}; 
		
		//查询锁定持仓
		virtual void OnRspQryLockPosition(CTORATstpSPLockPositionField *pLockPosition, CTORATstpSPRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {}; 
		
		//查询行权撤单
		virtual void OnRspQryExerciseAction(CTORATstpSPExerciseActionField *pExerciseAction, CTORATstpSPRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {}; 
		
		//查询锁定撤单
		virtual void OnRspQryLockAction(CTORATstpSPLockActionField *pLockAction, CTORATstpSPRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {}; 
		
		//查询标的持仓转移明细
		virtual void OnRspQryStockPositionTransferDetail(CTORATstpSPStockPositionTransferDetailField *pStockPositionTransferDetail, CTORATstpSPRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {}; 
		
		//查询交易通知
		virtual void OnRspQryTradingNotice(CTORATstpSPTradingNoticeField *pTradingNotice, CTORATstpSPRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {}; 
		
		//查询证券处置
		virtual void OnRspQryStockDisposal(CTORATstpSPStockDisposalField *pStockDisposal, CTORATstpSPRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {}; 
		
		//查询证券处置撤单
		virtual void OnRspQryStockDisposalAction(CTORATstpSPStockDisposalActionField *pStockDisposalAction, CTORATstpSPRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {}; 
		
		//查询条件单
		virtual void OnRspQryCondOrder(CTORATstpSPCondOrderField *pCondOrder, CTORATstpSPRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {}; 
		
		//查询条件单撤单
		virtual void OnRspQryCondOrderAction(CTORATstpSPCondOrderActionField *pCondOrderAction, CTORATstpSPRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {}; 
		
		//查询投资者限仓
		virtual void OnRspQryInvestorLimitPosition(CTORATstpSPInvestorLimitPositionField *pInvestorLimitPosition, CTORATstpSPRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {}; 
		
		//查询投资者限额
		virtual void OnRspQryInvestorLimitAmount(CTORATstpSPInvestorLimitAmountField *pInvestorLimitAmount, CTORATstpSPRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {}; 
		
		//查询组合撤单
		virtual void OnRspQryCombOrderAction(CTORATstpSPCombOrderActionField *pCombOrderAction, CTORATstpSPRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {}; 
		
		//查询组合报单
		virtual void OnRspQryCombOrder(CTORATstpSPCombOrderField *pCombOrder, CTORATstpSPRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {}; 
		
		//查询组合持仓
		virtual void OnRspQryCombPosition(CTORATstpSPCombPositionField *pCombPosition, CTORATstpSPRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {}; 
		
		//查询组合持仓明细
		virtual void OnRspQryCombPosDetail(CTORATstpSPCombPosDetailField *pCombPosDetail, CTORATstpSPRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {}; 
		
		//查询投资者行权指派明细
		virtual void OnRspQryExerciseAppointment(CTORATstpSPExerciseAppointmentField *pExerciseAppointment, CTORATstpSPRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {}; 
		
		//查询备兑股份不足仓位
		virtual void OnRspQryInsufficientCoveredStockPosition(CTORATstpSPInsufficientCoveredStockPositionField *pInsufficientCoveredStockPosition, CTORATstpSPRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {}; 
		
		//查询组合合约信息
		virtual void OnRspQryCombSecurity(CTORATstpSPCombSecurityField *pCombSecurity, CTORATstpSPRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {}; 
		
		//查询合并行权委托
		virtual void OnRspQryCombExercise(CTORATstpSPCombExerciseField *pCombExercise, CTORATstpSPRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {}; 
		
		//查询合并行权撤单
		virtual void OnRspQryCombExerciseAction(CTORATstpSPCombExerciseActionField *pCombExerciseAction, CTORATstpSPRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {}; 
			
	};

	class SPTRADER_API_DLL_EXPORT CTORATstpSPTraderApi
	{
	public:
		///创建TraderApi
		///@param pszFlowPath 存贮订阅信息文件的目录，默认为当前目录
		///@param bEncrpyt 网络数据是否加密传输，默认不加密
		///@return 创建出的TraderApi
		static CTORATstpSPTraderApi *CreateTstpSPTraderApi(const char *pszFlowPath = "", bool bEncrypt = false);
		
		///获取API版本号
		///@return 版本号
		static const char* GetApiVersion();
		
		///删除接口对象本身
		///@remark 不再使用本接口对象时,调用该函数删除接口对象
		virtual void Release() = 0;
		
		///初始化
		///@remark 初始化运行环境,只有调用后,接口才开始工作
		virtual void Init() = 0;
		
		///等待接口线程结束运行
		///@return 线程退出代码
		virtual int Join() = 0;
		
		///注册前置机网络地址
		///@param pszFrontAddress：前置机网络地址。
		///@remark 网络地址的格式为：“protocol://ipaddress:port”，如：”tcp://127.0.0.1:17001”。 
		///@remark “tcp”代表传输协议，“127.0.0.1”代表服务器地址。”17001”代表服务器端口号。
		virtual void RegisterFront(char *pszFrontAddress) = 0;

		///注册名字服务器网络地址
		///@param pszNsAddress：名字服务器网络地址。
		///@remark 网络地址的格式为：“protocol://ipaddress:port”，如：”tcp://127.0.0.1:12001”。 
		///@remark “tcp”代表传输协议，“127.0.0.1”代表服务器地址。”12001”代表服务器端口号。
		///@remark RegisterNameServer和RegisterFront任选其一。
		virtual void RegisterNameServer(char *pszNsAddress) = 0;

		///注册回调接口
		///@param pSpi 派生自回调接口类的实例
		virtual void RegisterSpi(CTORATstpSPTraderSpi *pSpi) = 0;
		
		///订阅私有流。
		///@param nResumeType 私有流重传方式  
		///        TORA_TERT_RESTART:从本交易日开始重传
		///        TORA_TERT_RESUME:从上次收到的续传
		///        TORA_TERT_QUICK:只传送登录后私有流的内容
		///@remark 该方法要在Init方法前调用。若不调用则不会收到私有流的数据。
		virtual void SubscribePrivateTopic(TORA_TE_RESUME_TYPE nResumeType) = 0;
		
		///订阅公共流。
		///@param nResumeType 公共流重传方式  
		///        TORA_TERT_RESTART:从本交易日开始重传
		///        TORA_TERT_RESUME:从上次收到的续传
		///        TORA_TERT_QUICK:只传送登录后公共流的内容
		///@remark 该方法要在Init方法前调用。若不调用则不会收到公共流的数据。
		virtual void SubscribePublicTopic(TORA_TE_RESUME_TYPE nResumeType) = 0;
		
		///获取连接信息
		virtual int ReqGetConnectionInfo(int nRequestID) = 0;
		
		
		//登录请求
		virtual int ReqUserLogin(CTORATstpSPReqUserLoginField *pReqUserLoginField, int nRequestID) = 0;
		
		//登出请求
		virtual int ReqUserLogout(CTORATstpSPUserLogoutField *pUserLogoutField, int nRequestID) = 0;
		
		//修改密码请求
		virtual int ReqUserPasswordUpdate(CTORATstpSPUserPasswordUpdateField *pUserPasswordUpdateField, int nRequestID) = 0;
		
		//请求录入设备序列
		virtual int ReqInputDeviceSerial(CTORATstpSPReqInputDeviceSerialField *pReqInputDeviceSerialField, int nRequestID) = 0;
		
		//报单录入请求
		virtual int ReqOrderInsert(CTORATstpSPInputOrderField *pInputOrderField, int nRequestID) = 0;
		
		//撤单请求
		virtual int ReqOrderAction(CTORATstpSPInputOrderActionField *pInputOrderActionField, int nRequestID) = 0;
		
		//行权请求
		virtual int ReqExerciseInsert(CTORATstpSPInputExerciseField *pInputExerciseField, int nRequestID) = 0;
		
		//行权操作请求
		virtual int ReqExerciseAction(CTORATstpSPInputExerciseActionField *pInputExerciseActionField, int nRequestID) = 0;
		
		//锁定录入请求
		virtual int ReqLockInsert(CTORATstpSPInputLockField *pInputLockField, int nRequestID) = 0;
		
		//锁定操作请求
		virtual int ReqLockAction(CTORATstpSPInputLockActionField *pInputLockActionField, int nRequestID) = 0;
		
		//组合委托录入请求
		virtual int ReqCombOrderInsert(CTORATstpSPInputCombOrderField *pInputCombOrderField, int nRequestID) = 0;
		
		//组合委托操作请求
		virtual int ReqCombOrderAction(CTORATstpSPInputCombOrderActionField *pInputCombOrderActionField, int nRequestID) = 0;
		
		//条件单录入请求
		virtual int ReqCondOrderInsert(CTORATstpSPInputCondOrderField *pInputCondOrderField, int nRequestID) = 0;
		
		//条件单撤单请求
		virtual int ReqCondOrderAction(CTORATstpSPInputCondOrderActionField *pInputCondOrderActionField, int nRequestID) = 0;
		
		//合并行权请求
		virtual int ReqCombExerciseInsert(CTORATstpSPInputCombExerciseField *pInputCombExerciseField, int nRequestID) = 0;
		
		//合并行权操作请求
		virtual int ReqCombExerciseAction(CTORATstpSPInputCombExerciseActionField *pInputCombExerciseActionField, int nRequestID) = 0;
		
		//查询最大可锁定数量请求
		virtual int ReqInquiryMaxLockVolume(CTORATstpSPReqInquiryMaxLockVolumeField *pReqInquiryMaxLockVolumeField, int nRequestID) = 0;
		
		//查询最大可备兑现货数量请求
		virtual int ReqInquiryMaxCoverVolume(CTORATstpSPReqInquiryMaxCoverVolumeField *pReqInquiryMaxCoverVolumeField, int nRequestID) = 0;
		
		//查询拆分组合合约后保证金差额变动请求
		virtual int ReqInquirySplitCombMarginDifference(CTORATstpSPReqInquirySplitCombMarginDifferenceField *pReqInquirySplitCombMarginDifferenceField, int nRequestID) = 0;
		
		//资金转移请求
		virtual int ReqTransferFund(CTORATstpSPInputTransferFundField *pInputTransferFundField, int nRequestID) = 0;
		
		//现货仓位转移请求
		virtual int ReqTransferStockPosition(CTORATstpSPInputTransferStockPositionField *pInputTransferStockPositionField, int nRequestID) = 0;
		
		//查询集中交易系统资金请求
		virtual int ReqInquiryJZFund(CTORATstpSPReqInquiryJZFundField *pReqInquiryJZFundField, int nRequestID) = 0;
		
		//查询银行账户余额请求
		virtual int ReqInquiryBankAccountFund(CTORATstpSPReqInquiryBankAccountFundField *pReqInquiryBankAccountFundField, int nRequestID) = 0;
		
		//查询现货系统现货持仓请求
		virtual int ReqInquiryStockPosition(CTORATstpSPReqInquiryStockPositionField *pReqInquiryStockPositionField, int nRequestID) = 0;
		
		//查询交易所
		virtual int ReqQryExchange(CTORATstpSPQryExchangeField *pQryExchangeField, int nRequestID) = 0;
		
		//查询实时行情
		virtual int ReqQryMarketData(CTORATstpSPQryMarketDataField *pQryMarketDataField, int nRequestID) = 0;
		
		//查询证券信息
		virtual int ReqQrySecurity(CTORATstpSPQrySecurityField *pQrySecurityField, int nRequestID) = 0;
		
		//查询代理关系
		virtual int ReqQryBUProxy(CTORATstpSPQryBUProxyField *pQryBUProxyField, int nRequestID) = 0;
		
		//查询User
		virtual int ReqQryUser(CTORATstpSPQryUserField *pQryUserField, int nRequestID) = 0;
		
		//查询投资者
		virtual int ReqQryInvestor(CTORATstpSPQryInvestorField *pQryInvestorField, int nRequestID) = 0;
		
		//查询股东账户
		virtual int ReqQryShareholderAccount(CTORATstpSPQryShareholderAccountField *pQryShareholderAccountField, int nRequestID) = 0;
		
		//资金账户查询
		virtual int ReqQryTradingAccount(CTORATstpSPQryTradingAccountField *pQryTradingAccountField, int nRequestID) = 0;
		
		//报单查询
		virtual int ReqQryOrder(CTORATstpSPQryOrderField *pQryOrderField, int nRequestID) = 0;
		
		//成交查询
		virtual int ReqQryTrade(CTORATstpSPQryTradeField *pQryTradeField, int nRequestID) = 0;
		
		//投资者持仓查询
		virtual int ReqQryPosition(CTORATstpSPQryPositionField *pQryPositionField, int nRequestID) = 0;
		
		//查询基础交易费用
		virtual int ReqQryTradingFee(CTORATstpSPQryTradingFeeField *pQryTradingFeeField, int nRequestID) = 0;
		
		//查询佣金费率
		virtual int ReqQryInvestorTradingFee(CTORATstpSPQryInvestorTradingFeeField *pQryInvestorTradingFeeField, int nRequestID) = 0;
		
		//查询保证金费率
		virtual int ReqQryInvestorMarginFee(CTORATstpSPQryInvestorMarginFeeField *pQryInvestorMarginFeeField, int nRequestID) = 0;
		
		//报单明细资金查询
		virtual int ReqQryOrderFundDetail(CTORATstpSPQryOrderFundDetailField *pQryOrderFundDetailField, int nRequestID) = 0;
		
		//查询资金转移流水
		virtual int ReqQryFundTransferDetail(CTORATstpSPQryFundTransferDetailField *pQryFundTransferDetailField, int nRequestID) = 0;
		
		//查询持仓转移流水
		virtual int ReqQryPositionTransferDetail(CTORATstpSPQryPositionTransferDetailField *pQryPositionTransferDetailField, int nRequestID) = 0;
		
		//查询撤单
		virtual int ReqQryOrderAction(CTORATstpSPQryOrderActionField *pQryOrderActionField, int nRequestID) = 0;
		
		//查询现货持仓
		virtual int ReqQryStockPosition(CTORATstpSPQryStockPositionField *pQryStockPositionField, int nRequestID) = 0;
		
		//查询锁定委托
		virtual int ReqQryLock(CTORATstpSPQryLockField *pQryLockField, int nRequestID) = 0;
		
		//查询行权委托
		virtual int ReqQryExercise(CTORATstpSPQryExerciseField *pQryExerciseField, int nRequestID) = 0;
		
		//查询锁定持仓
		virtual int ReqQryLockPosition(CTORATstpSPQryLockPositionField *pQryLockPositionField, int nRequestID) = 0;
		
		//查询行权撤单
		virtual int ReqQryExerciseAction(CTORATstpSPQryExerciseActionField *pQryExerciseActionField, int nRequestID) = 0;
		
		//查询锁定撤单
		virtual int ReqQryLockAction(CTORATstpSPQryLockActionField *pQryLockActionField, int nRequestID) = 0;
		
		//查询标的持仓转移明细
		virtual int ReqQryStockPositionTransferDetail(CTORATstpSPQryStockPositionTransferDetailField *pQryStockPositionTransferDetailField, int nRequestID) = 0;
		
		//查询交易通知
		virtual int ReqQryTradingNotice(CTORATstpSPQryTradingNoticeField *pQryTradingNoticeField, int nRequestID) = 0;
		
		//查询证券处置
		virtual int ReqQryStockDisposal(CTORATstpSPQryStockDisposalField *pQryStockDisposalField, int nRequestID) = 0;
		
		//查询证券处置撤单
		virtual int ReqQryStockDisposalAction(CTORATstpSPQryStockDisposalActionField *pQryStockDisposalActionField, int nRequestID) = 0;
		
		//查询条件单
		virtual int ReqQryCondOrder(CTORATstpSPQryCondOrderField *pQryCondOrderField, int nRequestID) = 0;
		
		//查询条件单撤单
		virtual int ReqQryCondOrderAction(CTORATstpSPQryCondOrderActionField *pQryCondOrderActionField, int nRequestID) = 0;
		
		//查询投资者限仓
		virtual int ReqQryInvestorLimitPosition(CTORATstpSPQryInvestorLimitPositionField *pQryInvestorLimitPositionField, int nRequestID) = 0;
		
		//查询投资者限额
		virtual int ReqQryInvestorLimitAmount(CTORATstpSPQryInvestorLimitAmountField *pQryInvestorLimitAmountField, int nRequestID) = 0;
		
		//查询组合撤单
		virtual int ReqQryCombOrderAction(CTORATstpSPQryCombOrderActionField *pQryCombOrderActionField, int nRequestID) = 0;
		
		//查询组合报单
		virtual int ReqQryCombOrder(CTORATstpSPQryCombOrderField *pQryCombOrderField, int nRequestID) = 0;
		
		//查询组合持仓
		virtual int ReqQryCombPosition(CTORATstpSPQryCombPositionField *pQryCombPositionField, int nRequestID) = 0;
		
		//查询组合持仓明细
		virtual int ReqQryCombPosDetail(CTORATstpSPQryCombPosDetailField *pQryCombPosDetailField, int nRequestID) = 0;
		
		//查询投资者行权指派明细
		virtual int ReqQryExerciseAppointment(CTORATstpSPQryExerciseAppointmentField *pQryExerciseAppointmentField, int nRequestID) = 0;
		
		//查询备兑股份不足仓位
		virtual int ReqQryInsufficientCoveredStockPosition(CTORATstpSPQryInsufficientCoveredStockPositionField *pQryInsufficientCoveredStockPositionField, int nRequestID) = 0;
		
		//查询组合合约信息
		virtual int ReqQryCombSecurity(CTORATstpSPQryCombSecurityField *pQryCombSecurityField, int nRequestID) = 0;
		
		//查询合并行权委托
		virtual int ReqQryCombExercise(CTORATstpSPQryCombExerciseField *pQryCombExerciseField, int nRequestID) = 0;
		
		//查询合并行权撤单
		virtual int ReqQryCombExerciseAction(CTORATstpSPQryCombExerciseActionField *pQryCombExerciseActionField, int nRequestID) = 0;
		
		
	protected:
		~CTORATstpSPTraderApi(){};
	};
}
#endif // _TORA_TSTPSPTRADERAPI_H