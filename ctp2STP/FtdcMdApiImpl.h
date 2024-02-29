#if !defined(_FTDCMDAPIIMPL_H)
#define _FTDCMDAPIIMPL_H

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "TORATstpXMdApi.h"
#include "ThostFtdcMdApi.h"

using namespace TORALEV1API;

///API接口实现
class CFtdcMdApiImpl : public CThostFtdcMdApi, public CTORATstpXMdSpi
{
public:	
	///构造函数
	CFtdcMdApiImpl();

	///获取API的版本信息
	///@retrun 获取到的版本号
	//const char *GetApiVersion(){return 0;};

	///删除接口对象本身
	///@remark 不再使用本接口对象时,调用该函数删除接口对象
	virtual void Release();
	
	///初始化
	///@remark 初始化运行环境,只有调用后,接口才开始工作
	virtual void Init();
	
	///等待接口线程结束运行
	///@return 线程退出代码
	virtual int Join();
	
	///获取当前交易日
	///@retrun 获取到的交易日
	///@remark 只有登录成功后,才能得到正确的交易日
	virtual const char *GetTradingDay();
	
	///注册前置机网络地址
	///@param pszFrontAddress：前置机网络地址。
	///@remark 网络地址的格式为：“protocol://ipaddress:port”，如：”tcp://127.0.0.1:17001”。 
	///@remark “tcp”代表传输协议，“127.0.0.1”代表服务器地址。”17001”代表服务器端口号。
	virtual void RegisterFront(char *pszFrontAddress);
	
	///注册名字服务器网络地址
	///@param pszNsAddress：名字服务器网络地址。
	///@remark 网络地址的格式为：“protocol://ipaddress:port”，如：”tcp://127.0.0.1:12001”。 
	///@remark “tcp”代表传输协议，“127.0.0.1”代表服务器地址。”12001”代表服务器端口号。
	///@remark RegisterFront优先于RegisterNameServer
	virtual void RegisterNameServer(char *pszNsAddress);

	///注册回调接口
	///@param pSpi 派生自回调接口类的实例
	virtual void RegisterSpi(CThostFtdcMdSpi *pSpi);

	///用户登录请求
	virtual int ReqUserLogin(CThostFtdcReqUserLoginField *pReqUserLogin, int nRequestID);

	///用户退出请求
	virtual int ReqUserLogout(CThostFtdcUserLogoutField *pUserLogout, int nRequestID);

	///订阅行情。
	///@param ppInstrumentID 合约ID  
	///@param nCount 要订阅/退订行情的合约个数
	///@remark 
	virtual int SubscribeMarketData(char* ppInstrumentID[], int nCount);

	///退订行情。
	///@param ppInstrumentID 合约ID  
	///@param nCount 要订阅/退订行情的合约个数
	///@remark 
	virtual int UnSubscribeMarketData(char* ppInstrumentID[], int nCount);


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///暂时不实现的接口

	///注册名字服务器用户信息
	///@param pFensUserInfo：用户信息。
	virtual void RegisterFensUserInfo(CThostFtdcFensUserInfoField * pFensUserInfo){return;};

	///订阅询价。
	///@param ppInstrumentID 合约ID  
	///@param nCount 要订阅/退订行情的合约个数
	///@remark 
	virtual int SubscribeForQuoteRsp(char* ppInstrumentID[], int nCount) { return -3; }

	///退订询价。
	///@param ppInstrumentID 合约ID  
	///@param nCount 要订阅/退订行情的合约个数
	///@remark 
	virtual int UnSubscribeForQuoteRsp(char* ppInstrumentID[], int nCount) { return -3; }

#if defined(V6_3_19) || defined(V6_5_1) || defined(V6_6_1_P1) || defined(V6_6_7) || defined(V6_6_9)
	///请求查询组播合约
	virtual int ReqQryMulticastInstrument(CThostFtdcQryMulticastInstrumentField *pQryMulticastInstrument, int nRequestID) { return -3; }
#endif

private:
	//连接建立通知
	/* 说明：
		1. 此连接为系统连接，即便没有任何用户登录，该连接依然会维持在线状态
	*/
	virtual void OnFrontConnected();

	//连接断开通知，用户无需处理，API会自动重连
	/* 说明：
		1. 连接断开后，所有在此连接上登录的用户均处于离线状态，重新连接后均需要重新发送登录请求
	*/
	virtual void OnFrontDisconnected(int nReason);

	/*登录应答*/
	virtual void OnRspUserLogin(CTORATstpRspUserLoginField* pRspUserLoginField, CTORATstpRspInfoField* pRspInfoField, int nRequestID);

	/*登出应答*/
	virtual void OnRspUserLogout(CTORATstpUserLogoutField* pUserLogoutField, CTORATstpRspInfoField* pRspInfoField, int nRequestID);

	/*行情订阅应答*/
	virtual void OnRspSubMarketData(CTORATstpSpecificSecurityField* pSpecificSecurity, CTORATstpRspInfoField* pRspInfo);

	/*行情退订应答*/
	virtual void OnRspUnSubMarketData(CTORATstpSpecificSecurityField* pSpecificSecurity, CTORATstpRspInfoField* pRspInfo);

	/*行情通知*/
	virtual void OnRtnMarketData(CTORATstpMarketDataField* pDepthMarketData);

	///订阅期权行情应答
	virtual void OnRspSubSPMarketData(CTORATstpSpecificSecurityField* pSpecificSecurityField, CTORATstpRspInfoField* pRspInfoField);

	///退订期权行情应答
	virtual void OnRspUnSubSPMarketData(CTORATstpSpecificSecurityField* pSpecificSecurityField, CTORATstpRspInfoField* pRspInfoField);

	///期权行情通知
	virtual void OnRtnSPMarketData(CTORATstpMarketDataField* pMarketDataField);
public:
	CTORATstpXMdApi*m_pUserApi;
	CThostFtdcMdSpi *m_pSpi;
	TThostFtdcDateType TradingDay;
};


#endif
