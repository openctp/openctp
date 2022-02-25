
#pragma once

#include "UTApiStruct.h"

#if defined(ISLIB) && defined(WIN32)
#define UT_API_EXPORT __declspec(dllexport)
#else
#define UT_API_EXPORT 
#endif

class CUTSpi
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
		
	//请求后台不支持的功能时调用
	virtual void OnRspError(CUTRspInfoField *pRspInfo, int nRequestID, bool bIsLast){};
	

	///报单
	virtual void OnRtnOrder(CUTOrderField *pOrder) {};

	///成交
	virtual void OnRtnTrade(CUTTradeField *pTrade) {};

	///报单操作回报
	virtual void OnErrRtnOrderAction(CUTOrderActionField *pOrderAction) {};
	

	///报单错误回报
	virtual void OnRspOrderInsert(CUTInputOrderField *pInputOrder, CUTRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};
	

	///报单操作回报
	virtual void OnRspOrderAction(CUTInputOrderActionField *pInputOrderAction, CUTRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};
	

	///用户登入应答
	virtual void OnRspLogin(CUTRspLoginField *pRspLogin, CUTRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};
	

	///密码修改应答
	virtual void OnRspUserPasswordUpdate(CUTUserPasswordUpdateField *pUserPasswordUpdate, CUTRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};
	

	///转账错误回报
	virtual void OnRspTransferInsert(CUTInputTransferField *pInputTransfer, CUTRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};
	

	///转账
	virtual void OnRtnTransfer(CUTTransferField *pTransfer) {};

	///直接还款错误回报
	virtual void OnRspFundPaybackInsert(CUTInputFundPaybackField *pInputFundPayback, CUTRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};
	

	///直接还款
	virtual void OnRtnFundPayback(CUTFundPaybackField *pFundPayback) {};

	///直接还券错误回报
	virtual void OnRspStockPaybackInsert(CUTInputStockPaybackField *pInputStockPayback, CUTRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};
	

	///直接还券
	virtual void OnRtnStockPayback(CUTStockPaybackField *pStockPayback) {};

	///同步组件返回的券源保底额度信息
	virtual void OnRtnPrivateCreditStock(CUTPrivateCreditStockField *pPrivateCreditStock) {};

	///锁定
	virtual void OnRtnLock(CUTLockField *pLock) {};

	///锁定错误回报
	virtual void OnRspLockInsert(CUTInputLockField *pInputLock, CUTRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};
	

	///行权
	virtual void OnRtnExecOrder(CUTExecOrderField *pExecOrder) {};

	///行权错误回报
	virtual void OnRspExecOrderInsert(CUTInputExecOrderField *pInputExecOrder, CUTRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};
	

	///行权操作回报
	virtual void OnRspExecOrderAction(CUTInputExecOrderActionField *pInputExecOrderAction, CUTRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};
	

	///行权操作回报
	virtual void OnErrRtnExecOrderAction(CUTExecOrderActionField *pExecOrderAction) {};
	

	///请求查询合约响应
	virtual void OnRspQryInstrument(CUTInstrumentField *pInstrument, CUTRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};
	

	///请求查询行情响应
	virtual void OnRspQryDepthMarketData(CUTDepthMarketDataField *pDepthMarketData, CUTRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};
	

	///请求查询持仓响应
	virtual void OnRspQryInvestorPosition(CUTInvestorPositionField *pInvestorPosition, CUTRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};
	

	///请求查询资金响应
	virtual void OnRspQryTradingAccount(CUTTradingAccountField *pTradingAccount, CUTRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};
	

	///请求查询期权合约每手保证金响应
	virtual void OnRspQryOptionInstrMarginByVolume(CUTOptionInstrMarginByVolumeField *pOptionInstrMarginByVolume, CUTRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};
	

	///请求查询期权手续费率响应
	virtual void OnRspQryOptionInstrCommRate(CUTOptionInstrCommRateField *pOptionInstrCommRate, CUTRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};
	

	///请求查询报单响应
	virtual void OnRspQryOrder(CUTOrderField *pOrder, CUTRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};
	

	///请求查询成交响应
	virtual void OnRspQryTrade(CUTTradeField *pTrade, CUTRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};
	

	///请求查询手续费率响应
	virtual void OnRspQryInstrumentCommissionRate(CUTInstrumentCommissionRateField *pInstrumentCommissionRate, CUTRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};
	

	///请求查询投资者响应
	virtual void OnRspQryInvestor(CUTInvestorField *pInvestor, CUTRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};
	

	///请求查询转账响应
	virtual void OnRspQryTransfer(CUTTransferField *pTransfer, CUTRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};
	

	///请求查询交易编码
	virtual void OnRspQryTradingCode(CUTTradingCodeField *pTradingCode, CUTRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};
	

	///查询最大下单量响应
	virtual void OnRspQryMaxOrderVolume(CUTMaxOrderVolumeField *pMaxOrderVolume, CUTRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};
	

	///请求查询信用合约属性响应
	virtual void OnRspQryCreditInstrument(CUTCreditInstrumentField *pCreditInstrument, CUTRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};
	

	///请求查询投资者信用信息响应
	virtual void OnRspQryCreditInvestor(CUTCreditInvestorField *pCreditInvestor, CUTRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};
	

	///请求查询投资者可融券响应
	virtual void OnRspQryPrivateCreditStock(CUTPrivateCreditStockField *pPrivateCreditStock, CUTRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};
	

	///请求查询集中度参数响应
	virtual void OnRspQryCreditConcentration(CUTCreditConcentrationField *pCreditConcentration, CUTRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};
	

	///请求查询投资者融资明细响应
	virtual void OnRspQryCreditFundDetail(CUTCreditFundDetailField *pCreditFundDetail, CUTRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};
	

	///请求查询投资者融券明细响应
	virtual void OnRspQryCreditStockDetail(CUTCreditStockDetailField *pCreditStockDetail, CUTRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};
	

	///请求查询投资者直接还款响应
	virtual void OnRspQryFundPayback(CUTFundPaybackField *pFundPayback, CUTRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};
	

	///请求查询投资者直接还券响应
	virtual void OnRspQryStockPayback(CUTStockPaybackField *pStockPayback, CUTRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};
	

	///请求查询公有融资额度响应
	virtual void OnRspQryPublicCreditFund(CUTPublicCreditFundField *pPublicCreditFund, CUTRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};
	

	///请求查询ETF信息响应
	virtual void OnRspQryETFInfo(CUTETFInfoField *pETFInfo, CUTRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};
	

	///请求查询ETF成分股响应
	virtual void OnRspQryETFComponent(CUTETFComponentField *pETFComponent, CUTRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};
	

	///请求查询保证金可用余额明细响应
	virtual void OnRspQryCreditAvailableDetail(CUTCreditAvailableDetailField *pCreditAvailableDetail, CUTRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};
	

	///请求查询锁定响应
	virtual void OnRspQryLock(CUTLockField *pLock, CUTRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};
	

	///请求查询行权响应
	virtual void OnRspQryExecOrder(CUTExecOrderField *pExecOrder, CUTRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};
	

	///请求查询锁定仓位响应
	virtual void OnRspQryLockPosition(CUTLockPositionField *pLockPosition, CUTRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};
	

	///请求查询期权限仓响应
	virtual void OnRspQryOptPosiLimit(CUTOptPosiLimitField *pOptPosiLimit, CUTRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};
	

	///请求查询期权限额响应
	virtual void OnRspQryOptAmountLimit(CUTOptAmountLimitField *pOptAmountLimit, CUTRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};
	
};

class UT_API_EXPORT CUTApi
{
public:
	///创建UserApi
	///@param pszFlowPath 存贮订阅信息文件的目录，默认为当前目录
	///nCPUID    绑定的CPU ID,默认不绑定
	static CUTApi *CreateApi(const char *pszFlowPath = "", int nCPUID = 0);
	
	///获取api版本
	static const char *GetApiVersion();
	
	///不再使用api时,需要调用该函数删除之
	virtual void Release() = 0;
	
	///初始化api,调用该函数后接口开始工作
	virtual void Init() = 0;
	
	///等待接口线程结束
	virtual int Join() = 0;
	
	///设置网关地址
	///pszFrontAddress前置地址;如tcp://127.0.0.1:8888,说明传输协议是tcp,ip地址是127.0.0.1，端口号是8888
	virtual void RegisterFront(char *pszFrontAddress) = 0;
	
	///注册回调接口
	///@param pSpi 派生自回调接口类的实例
	virtual void RegisterSpi(CUTSpi *pSpi) = 0;
	
	///订阅私有流,如报单回报,成交回报。该函数可能任何时候调用,若不调用则不会收到私有流的数据
	///nResumeType 订阅方式; UT_TERT_RESTART从头开始传,UT_TERT_RESUME续传,UT_TERT_QUICK只传登录后的流
	virtual void SubscribePrivateTopic(UT_TE_RESUME_TYPE nResumeType) = 0;
	
	///订阅公有流,暂时没有数据推送。该函数要在登录前调用,若不调用则不会收到公有流的数据
	///nResumeType 订阅方式; UT_TERT_RESTART从头开始传,UT_TERT_RESUME续传,UT_TERT_QUICK只传登录后的流
	virtual void SubscribePublicTopic(UT_TE_RESUME_TYPE nResumeType) = 0;
	
	///提交终端信息;登录后调用;非中转服务器不需要调用
	///pSubmitTerminalInfo 终端信息(格式"#OSTPMA;IIP=XXX;...")
	virtual void SubmitTerminalInfo(CUTSubmitTerminalInfoField* pSubmitTerminalInfo) = 0;
	
	///报单插入
	virtual int ReqOrderInsert(CUTInputOrderField *pInputOrder, int nRequestID) = 0;
	///报单操作
	virtual int ReqOrderAction(CUTInputOrderActionField *pInputOrderAction, int nRequestID) = 0;
	///用户登入请求
	virtual int ReqLogin(CUTReqLoginField *pReqLogin, int nRequestID) = 0;
	///登出请求
	virtual int ReqLogout(CUTReqLogoutField *pReqLogout, int nRequestID) = 0;
	///密码修改请求
	virtual int ReqUserPasswordUpdate(CUTUserPasswordUpdateField *pUserPasswordUpdate, int nRequestID) = 0;
	///转账插入
	virtual int ReqTransferInsert(CUTInputTransferField *pInputTransfer, int nRequestID) = 0;
	///直接还款插入
	virtual int ReqFundPaybackInsert(CUTInputFundPaybackField *pInputFundPayback, int nRequestID) = 0;
	///直接还券插入
	virtual int ReqStockPaybackInsert(CUTInputStockPaybackField *pInputStockPayback, int nRequestID) = 0;
	///锁定插入
	virtual int ReqLockInsert(CUTInputLockField *pInputLock, int nRequestID) = 0;
	///行权插入
	virtual int ReqExecOrderInsert(CUTInputExecOrderField *pInputExecOrder, int nRequestID) = 0;
	///行权操作
	virtual int ReqExecOrderAction(CUTInputExecOrderActionField *pInputExecOrderAction, int nRequestID) = 0;
	///批量报单插入
	virtual int ReqOrderInsert(CUTInputOrderField *pInputOrder, int nCount, int nRequestID) = 0;
	///批量报单操作
	virtual int ReqOrderAction(CUTInputOrderActionField *pInputOrderAction, int nCount, int nRequestID) = 0;
	///请求查询合约
	virtual int ReqQryInstrument(CUTQryInstrumentField *pQryInstrument, int nRequestID) = 0;
	///请求查询行情
	virtual int ReqQryDepthMarketData(CUTQryDepthMarketDataField *pQryDepthMarketData, int nRequestID) = 0;
	///请求查询持仓
	virtual int ReqQryInvestorPosition(CUTQryInvestorPositionField *pQryInvestorPosition, int nRequestID) = 0;
	///请求查询资金
	virtual int ReqQryTradingAccount(CUTQryTradingAccountField *pQryTradingAccount, int nRequestID) = 0;
	///请求查询报单
	virtual int ReqQryOrder(CUTQryOrderField *pQryOrder, int nRequestID) = 0;
	///请求查询成交
	virtual int ReqQryTrade(CUTQryTradeField *pQryTrade, int nRequestID) = 0;
	///请求查询期权合约每手保证金
	virtual int ReqQryOptionInstrMarginByVolume(CUTQryOptionInstrMarginByVolumeField *pQryOptionInstrMarginByVolume, int nRequestID) = 0;
	///请求查询期权手续费率
	virtual int ReqQryOptionInstrCommRate(CUTQryOptionInstrCommRateField *pQryOptionInstrCommRate, int nRequestID) = 0;
	///请求查询手续费率
	virtual int ReqQryInstrumentCommissionRate(CUTQryInstrumentCommissionRateField *pQryInstrumentCommissionRate, int nRequestID) = 0;
	///请求查询投资者
	virtual int ReqQryInvestor(CUTQryInvestorField *pQryInvestor, int nRequestID) = 0;
	///请求查询转账
	virtual int ReqQryTransfer(CUTQryTransferField *pQryTransfer, int nRequestID) = 0;
	///请求查询交易编码
	virtual int ReqQryTradingCode(CUTQryTradingCodeField *pQryTradingCode, int nRequestID) = 0;
	///请求查询最大下单量
	virtual int ReqQryMaxOrderVolume(CUTQryMaxOrderVolumeField *pQryMaxOrderVolume, int nRequestID) = 0;
	///请求查询信用合约属性
	virtual int ReqQryCreditInstrument(CUTQryCreditInstrumentField *pQryCreditInstrument, int nRequestID) = 0;
	///请求查询投资者信用信息
	virtual int ReqQryCreditInvestor(CUTQryCreditInvestorField *pQryCreditInvestor, int nRequestID) = 0;
	///请求查询投资者可融券
	virtual int ReqQryPrivateCreditStock(CUTQryPrivateCreditStockField *pQryPrivateCreditStock, int nRequestID) = 0;
	///请求查询集中度参数
	virtual int ReqQryCreditConcentration(CUTQryCreditConcentrationField *pQryCreditConcentration, int nRequestID) = 0;
	///请求查询投资者融资明细
	virtual int ReqQryCreditFundDetail(CUTQryCreditFundDetailField *pQryCreditFundDetail, int nRequestID) = 0;
	///请求查询投资者融券明细
	virtual int ReqQryCreditStockDetail(CUTQryCreditStockDetailField *pQryCreditStockDetail, int nRequestID) = 0;
	///请求查询投资者直接还款
	virtual int ReqQryFundPayback(CUTQryFundPaybackField *pQryFundPayback, int nRequestID) = 0;
	///请求查询投资者直接还券
	virtual int ReqQryStockPayback(CUTQryStockPaybackField *pQryStockPayback, int nRequestID) = 0;
	///请求查询公有融资额度
	virtual int ReqQryPublicCreditFund(CUTQryPublicCreditFundField *pQryPublicCreditFund, int nRequestID) = 0;
	///请求查询ETF信息
	virtual int ReqQryETFInfo(CUTQryETFInfoField *pQryETFInfo, int nRequestID) = 0;
	///请求查询ETF成分股
	virtual int ReqQryETFComponent(CUTQryETFComponentField *pQryETFComponent, int nRequestID) = 0;
	///请求查询保证金可用余额明细
	virtual int ReqQryCreditAvailableDetail(CUTQryCreditAvailableDetailField *pQryCreditAvailableDetail, int nRequestID) = 0;
	///请求查询锁定
	virtual int ReqQryLock(CUTQryLockField *pQryLock, int nRequestID) = 0;
	///请求查询行权
	virtual int ReqQryExecOrder(CUTQryExecOrderField *pQryExecOrder, int nRequestID) = 0;
	///请求查询锁定仓位
	virtual int ReqQryLockPosition(CUTQryLockPositionField *pQryLockPosition, int nRequestID) = 0;
	///请求查询期权限仓
	virtual int ReqQryOptPosiLimit(CUTQryOptPosiLimitField *pQryOptPosiLimit, int nRequestID) = 0;
	///请求查询期权限额
	virtual int ReqQryOptAmountLimit(CUTQryOptAmountLimitField *pQryOptAmountLimit, int nRequestID) = 0;


protected:
	~CUTApi(){};
};
