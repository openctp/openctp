/////////////////////////////////////////////////////////////////////////
///@system QuantDo Platform
///@company 上海量投网络科技有限公司
///@file QdpFtdcTraderApi.h
///@brief 定义了客户端接口
///@history
///20150520	徐忠华	创建该文件
/////////////////////////////////////////////////////////////////////////

#if !defined(QDP_FTDCTRADERAPI_H)
#define QDP_FTDCTRADERAPI_H

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "QdpFtdcUserApiStruct.h"

#if defined(ISLIB) && defined(WIN32)
#ifdef LIB_TRADER_API_EXPORT
#define TRADER_API_EXPORT __declspec(dllexport)
#else
#define TRADER_API_EXPORT __declspec(dllimport)
#endif
#else
#define TRADER_API_EXPORT 
#endif

class CQdpFtdcTraderSpi
{
public:
	///当客户端与交易后台建立起通信连接时（还未登录前），该方法被调用。
	virtual void OnFrontConnected(){};
	
	///当客户端与交易后台通信连接断开时，该方法被调用。当发生这个情况后，API会自动重新连接，客户端可不做处理。
	///@param nReason 错误原因
	///        0x1001 网络读失败
	///        0x1002 网络写失败
	///        0x2001 接收心跳超时
	///        0x2002 发送心跳失败
	///        0x2003 收到错误报文
	virtual void OnFrontDisconnected(int nReason){};
		
	///心跳超时警告。当长时间未收到报文时，该方法被调用。
	///@param nTimeLapse 距离上次接收报文的时间
	virtual void OnHeartBeatWarning(int nTimeLapse){};
	
	///报文回调开始通知。当API收到一个报文后，首先调用本方法，然后是各数据域的回调，最后是报文回调结束通知。
	///@param nTopicID 主题代码（如私有流、公共流、行情流等）
	///@param nSequenceNo 报文序号
	virtual void OnPackageStart(int nTopicID, int nSequenceNo){};
	
	///报文回调结束通知。当API收到一个报文后，首先调用报文回调开始通知，然后是各数据域的回调，最后调用本方法。
	///@param nTopicID 主题代码（如私有流、公共流、行情流等）
	///@param nSequenceNo 报文序号
	virtual void OnPackageEnd(int nTopicID, int nSequenceNo){};


	///错误应答
	virtual void OnRspError(CQdpFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///用户登录应答
	virtual void OnRspUserLogin(CQdpFtdcRspUserLoginField *pRspUserLogin, CQdpFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///用户退出应答
	virtual void OnRspUserLogout(CQdpFtdcRspUserLogoutField *pRspUserLogout, CQdpFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///用户密码修改应答
	virtual void OnRspUserPasswordUpdate(CQdpFtdcUserPasswordUpdateField *pUserPasswordUpdate, CQdpFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///报单录入应答
	virtual void OnRspOrderInsert(CQdpFtdcInputOrderField *pInputOrder, CQdpFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///报单操作应答
	virtual void OnRspOrderAction(CQdpFtdcOrderActionField *pOrderAction, CQdpFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///客户信息量阈值设置应答
	virtual void OnRspSetClientMaxSigVol(CQdpFtdcClientMaxSigVolField *pClientMaxSigVol, CQdpFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///数据流回退通知
	virtual void OnRtnFlowMessageCancel(CQdpFtdcFlowMessageCancelField *pFlowMessageCancel) {};

	///成交回报
	virtual void OnRtnTrade(CQdpFtdcTradeField *pTrade) {};

	///报单回报
	virtual void OnRtnOrder(CQdpFtdcOrderField *pOrder) {};

	///报单录入错误回报
	virtual void OnErrRtnOrderInsert(CQdpFtdcInputOrderField *pInputOrder, CQdpFtdcRspInfoField *pRspInfo) {};

	///报单操作错误回报
	virtual void OnErrRtnOrderAction(CQdpFtdcOrderActionField *pOrderAction, CQdpFtdcRspInfoField *pRspInfo) {};

	///合约交易状态通知
	virtual void OnRtnInstrumentStatus(CQdpFtdcInstrumentStatusField *pInstrumentStatus) {};

	///账户出入金回报
	virtual void OnRtnInvestorAccountDeposit(CQdpFtdcInvestorAccountDepositResField *pInvestorAccountDepositRes) {};

	///QDP警告消息通知
	virtual void OnRtnMessageNotify(CQdpFtdcMessageNotifyInfoField *pMessageNotifyInfo) {};

	///金交所递延费率通知
	virtual void OnRtnSGEDeferRate(CQdpFtdcSGEDeferRateField *pSGEDeferRate) {};

	///报单查询应答
	virtual void OnRspQryOrder(CQdpFtdcOrderField *pOrder, CQdpFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///成交单查询应答
	virtual void OnRspQryTrade(CQdpFtdcTradeField *pTrade, CQdpFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///可用投资者账户查询应答
	virtual void OnRspQryUserInvestor(CQdpFtdcRspUserInvestorField *pRspUserInvestor, CQdpFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///投资者资金账户查询应答
	virtual void OnRspQryInvestorAccount(CQdpFtdcRspInvestorAccountField *pRspInvestorAccount, CQdpFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///合约查询应答
	virtual void OnRspQryInstrument(CQdpFtdcRspInstrumentField *pRspInstrument, CQdpFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///交易所查询应答
	virtual void OnRspQryExchange(CQdpFtdcRspExchangeField *pRspExchange, CQdpFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///投资者持仓查询应答
	virtual void OnRspQryInvestorPosition(CQdpFtdcRspInvestorPositionField *pRspInvestorPosition, CQdpFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///订阅主题应答
	virtual void OnRspSubscribeTopic(CQdpFtdcDisseminationField *pDissemination, CQdpFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///主题查询应答
	virtual void OnRspQryTopic(CQdpFtdcDisseminationField *pDissemination, CQdpFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///投资者手续费率查询应答
	virtual void OnRspQryInvestorFee(CQdpFtdcInvestorFeeField *pInvestorFee, CQdpFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///投资者保证金率查询应答
	virtual void OnRspQryInvestorMargin(CQdpFtdcInvestorMarginField *pInvestorMargin, CQdpFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///金交所递延费率查询应答
	virtual void OnRspQrySGEDeferRate(CQdpFtdcSGEDeferRateField *pSGEDeferRate, CQdpFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///投资者期权手续费率查询应答
	virtual void OnRspQryInvestorOptionFee(CQdpFtdcRspInvestorOptionFeeField *pRspInvestorOptionFee, CQdpFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///国际版投资者持仓限额查询应答
	virtual void OnRspQryInvestorPositionLimit(CQdpFtdcRspInvestorPositionLimitField *pRspInvestorPositionLimit, CQdpFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///国际版交易汇率查询应答
	virtual void OnRspQryExchangeRate(CQdpFtdcRspExchangeRateField *pRspExchangeRate, CQdpFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///实时行情查询应答
	virtual void OnRspQryMarketData(CQdpFtdcMarketDataField *pMarketData, CQdpFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///交易通道信息查询应答
	virtual void OnRspQryFrontInfo(CQdpFtdcFrontInfoField *pFrontInfo, CQdpFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///询价回报
	virtual void OnRtnForQuote(CQdpFtdcForQuoteRspField *pForQuoteRsp) {};

	///报价回报
	virtual void OnRtnQuote(CQdpFtdcQuoteField *pQuote) {};

	///询价查询应答
	virtual void OnRspQryForQuote(CQdpFtdcForQuoteField *pForQuote, CQdpFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///询价录入应答
	virtual void OnRspForQuoteInsert(CQdpFtdcInputForQuoteField *pInputForQuote, CQdpFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///报价录入应答
	virtual void OnRspQuoteInsert(CQdpFtdcInputQuoteField *pInputQuote, CQdpFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///报价操作应答
	virtual void OnRspQuoteAction(CQdpFtdcQuoteActionField *pQuoteAction, CQdpFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///登录认证应答
	virtual void OnRspAuthenticate(CQdpFtdcRtnAuthenticateField *pRtnAuthenticate, CQdpFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///订阅品种交易流水
	virtual void OnRspSubPrdTradeFlow(CQdpFtdcSpecificInstrumentField *pSpecificInstrument, CQdpFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///退订订阅品种交易流水
	virtual void OnRspUnSubPrdTradeFlow(CQdpFtdcSpecificInstrumentField *pSpecificInstrument, CQdpFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};
};

class TRADER_API_EXPORT CQdpFtdcTraderApi
{
public:
	///创建TraderApi
	///@param pszFlowPath 存贮订阅信息文件的目录，默认为当前目录
	///@return 创建出的UserApi
	static CQdpFtdcTraderApi *CreateFtdcTraderApi(const char *pszFlowPath = "");
	
	///获取系统版本号
	///@param nMajorVersion 主版本号
	///@param nMinorVersion 子版本号
	///@return 系统标识字符串
	static const char *GetVersion(int &nMajorVersion, int &nMinorVersion);
	
	///删除接口对象本身
	///@remark 不再使用本接口对象时,调用该函数删除接口对象
	virtual void Release() = 0;
	
	///初始化
	///@remark 初始化运行环境,只有调用后,接口才开始工作
	virtual void Init() = 0;
	
	///等待接口线程结束运行
	///@return 线程退出代码
	virtual int Join() = 0;
	
	///获取当前交易日
	///@retrun 获取到的交易日
	///@remark 只有登录成功后,才能得到正确的交易日
	virtual const char *GetTradingDay() = 0;
	
	///注册前置机网络地址
	///@param pszFrontAddress：前置机网络地址。
	///@remark 网络地址的格式为：“protocol://ipaddress:port”，如：”tcp://127.0.0.1:17001”。 
	///@remark “tcp”代表传输协议，“127.0.0.1”代表服务器地址。”17001”代表服务器端口号。
	virtual void RegisterFront(char *pszFrontAddress) = 0;
	
	///注册名字服务器网络地址
	///@param pszNsAddress：名字服务器网络地址。
	///@remark 网络地址的格式为：“protocol://ipaddress:port”，如：”tcp://127.0.0.1:12001”。 
	///@remark “tcp”代表传输协议，“127.0.0.1”代表服务器地址。”12001”代表服务器端口号。
	///@remark RegisterFront优先于RegisterNameServer
	virtual void RegisterNameServer(char *pszNsAddress) = 0;
	
	///注册回调接口
	///@param pSpi 派生自回调接口类的实例
	virtual void RegisterSpi(CQdpFtdcTraderSpi *pSpi) = 0;
	

	///订阅私有流。
	///@param nResumeType 私有流重传方式  
	///        QDP_TERT_RESTART:从本交易日开始重传
	///        QDP_TERT_RESUME:从上次收到的续传
	///        QDP_TERT_QUICK:只传送登录后私有流的内容
	///@remark 该方法要在Init方法前调用。若不调用则不会收到私有流的数据。
	virtual void SubscribePrivateTopic(QDP_TE_RESUME_TYPE nResumeType) = 0;
	
	///订阅公共流。
	///@param nResumeType 公共流重传方式  
	///        QDP_TERT_RESTART:从本交易日开始重传
	///        QDP_TERT_RESUME:从上次收到的续传
	///        QDP_TERT_QUICK:只传送登录后公共流的内容
	///@remark 该方法要在Init方法前调用。若不调用则不会收到公共流的数据。
	virtual void SubscribePublicTopic(QDP_TE_RESUME_TYPE nResumeType) = 0;

	///订阅交易员流。
	///@param nResumeType 交易员流重传方式  
	///        QDP_TERT_RESTART:从本交易日开始重传
	///        QDP_TERT_RESUME:从上次收到的续传
	///        QDP_TERT_QUICK:只传送登录后交易员流的内容
	///@remark 该方法要在Init方法前调用。若不调用则不会收到交易员流的数据。
	virtual void SubscribeUserTopic(QDP_TE_RESUME_TYPE nResumeType) = 0;
	
	///设置心跳超时时间。
	///@param timeout 心跳超时时间(秒)  
	virtual void SetHeartbeatTimeout(unsigned int timeout) = 0;
	
	///打开请求日志文件
	///@param pszReqLogFileName 请求日志文件名  
	///@return 0 操作成功
	///@return -1 打开日志文件失败
	virtual int OpenRequestLog(const char *pszReqLogFileName) = 0;

	///打开应答日志文件
	///@param pszRspLogFileName 应答日志文件名  
	///@return 0 操作成功
	///@return -1 打开日志文件失败
	virtual int OpenResponseLog(const char *pszRspLogFileName) = 0;


	///用户登录请求
	virtual int ReqUserLogin(CQdpFtdcReqUserLoginField *pReqUserLogin, int nRequestID) = 0;

	///用户退出请求
	virtual int ReqUserLogout(CQdpFtdcReqUserLogoutField *pReqUserLogout, int nRequestID) = 0;

	///用户密码修改请求
	virtual int ReqUserPasswordUpdate(CQdpFtdcUserPasswordUpdateField *pUserPasswordUpdate, int nRequestID) = 0;

	///报单录入请求
	virtual int ReqOrderInsert(CQdpFtdcInputOrderField *pInputOrder, int nRequestID) = 0;

	///报单操作请求
	virtual int ReqOrderAction(CQdpFtdcOrderActionField *pOrderAction, int nRequestID) = 0;

	///客户信息量阈值设置请求
	virtual int ReqSetClientMaxSigVol(CQdpFtdcClientMaxSigVolField *pClientMaxSigVol, int nRequestID) = 0;

	///报单查询请求
	virtual int ReqQryOrder(CQdpFtdcQryOrderField *pQryOrder, int nRequestID) = 0;

	///成交单查询请求
	virtual int ReqQryTrade(CQdpFtdcQryTradeField *pQryTrade, int nRequestID) = 0;

	///可用投资者账户查询请求
	virtual int ReqQryUserInvestor(CQdpFtdcQryUserInvestorField *pQryUserInvestor, int nRequestID) = 0;

	///投资者资金账户查询请求
	virtual int ReqQryInvestorAccount(CQdpFtdcQryInvestorAccountField *pQryInvestorAccount, int nRequestID) = 0;

	///合约查询请求
	virtual int ReqQryInstrument(CQdpFtdcQryInstrumentField *pQryInstrument, int nRequestID) = 0;

	///交易所查询请求
	virtual int ReqQryExchange(CQdpFtdcQryExchangeField *pQryExchange, int nRequestID) = 0;

	///投资者持仓查询请求
	virtual int ReqQryInvestorPosition(CQdpFtdcQryInvestorPositionField *pQryInvestorPosition, int nRequestID) = 0;

	///订阅主题请求
	virtual int ReqSubscribeTopic(CQdpFtdcDisseminationField *pDissemination, int nRequestID) = 0;

	///主题查询请求
	virtual int ReqQryTopic(CQdpFtdcDisseminationField *pDissemination, int nRequestID) = 0;

	///投资者手续费率查询请求
	virtual int ReqQryInvestorFee(CQdpFtdcQryInvestorFeeField *pQryInvestorFee, int nRequestID) = 0;

	///投资者保证金率查询请求
	virtual int ReqQryInvestorMargin(CQdpFtdcQryInvestorMarginField *pQryInvestorMargin, int nRequestID) = 0;

	///金交所递延费率查询请求
	virtual int ReqQrySGEDeferRate(CQdpFtdcQrySGEDeferRateField *pQrySGEDeferRate, int nRequestID) = 0;

	///投资者期权手续费率查询请求
	virtual int ReqQryInvestorOptionFee(CQdpFtdcQryInvestorOptionFeeField *pQryInvestorOptionFee, int nRequestID) = 0;

	///国际版投资者持仓限额查询请求
	virtual int ReqQryInvestorPositionLimit(CQdpFtdcQryInvestorPositionLimitField *pQryInvestorPositionLimit, int nRequestID) = 0;

	///国际版交易汇率查询请求
	virtual int ReqQryExchangeRate(CQdpFtdcQryExchangeRateField *pQryExchangeRate, int nRequestID) = 0;

	///实时行情查询请求
	virtual int ReqQryMarketData(CQdpFtdcQryMarketDataField *pQryMarketData, int nRequestID) = 0;

	///交易通道信息查询请求
	virtual int ReqQryFrontInfo(CQdpFtdcQryFrontInfoField *pQryFrontInfo, int nRequestID) = 0;

	///询价查询请求
	virtual int ReqQryForQuote(CQdpFtdcQryForQuoteField *pQryForQuote, int nRequestID) = 0;

	///询价录入请求
	virtual int ReqForQuoteInsert(CQdpFtdcInputForQuoteField *pInputForQuote, int nRequestID) = 0;

	///报价录入请求
	virtual int ReqQuoteInsert(CQdpFtdcInputQuoteField *pInputQuote, int nRequestID) = 0;

	///报价操作请求
	virtual int ReqQuoteAction(CQdpFtdcQuoteActionField *pQuoteAction, int nRequestID) = 0;

	///登录认证请求
	virtual int ReqAuthenticate(CQdpFtdcAuthenticateField *pAuthenticate, int nRequestID) = 0;

	///用户采集信息发送请求
	virtual int ReqSubmitUserSystemInfo(CQdpFtdcUserSystemInfoField *pUserSystemInfo, int nRequestID) = 0;

	///MarketData Inserting Request
	virtual int ReqMarketData(CQdpFtdcClientDepthMarketDataField *pClientDepthMarketData, int nRequestID) = 0;

	///订阅品种交易流水
	virtual int ReqSubPrdTradeFlow(CQdpFtdcSpecificInstrumentField *pSpecificInstrument, int nRequestID) = 0;

	///退订订阅品种交易流水
	virtual int ReqUnSubPrdTradeFlow(CQdpFtdcSpecificInstrumentField *pSpecificInstrument, int nRequestID) = 0;

	///准备就绪 QDP_TERT_PRIVATE 私有流; QDP_TERT_PUBLIC 公有流;
	virtual int ReqReady(CQdpFtdcFlowStatusField *pFlowStatus, int nRequestID) = 0;
protected:
	~CQdpFtdcTraderApi(){};
};

#endif
