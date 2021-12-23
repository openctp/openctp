#include <stdio.h>
#include <string>
#include "./CTP/ThostFtdcTraderApi.h"

#include <thread>
#include <mutex>
#include <functional>
#include <condition_variable>

#pragma comment (lib, "./CTP/thosttraderapi_se.lib")

class semaphore
{
public:
	semaphore(int value = 1) :count(value) {}

	void wait()
	{
		std::unique_lock<std::mutex> lck(mt);
		if (--count < 0)//资源不足挂起线程
			cv.wait(lck);
	}

	void signal()
	{
		std::unique_lock<std::mutex> lck(mt);
		if (++count <= 0)//有线程挂起，唤醒一个
			cv.notify_one();
	}

private:
	int count;
	std::mutex mt;
	std::condition_variable cv;
};

semaphore _semaphore(0);

class CApplication : public CThostFtdcTraderSpi
{
public:
	CApplication(std::string host, std::string broker, std::string user, std::string password, std::string appid, std::string authcode) :
		m_host(host),
		m_broker(broker),
		m_user(user),
		m_password(password),
		m_appid(appid),
		m_authcode(authcode)
	{
		m_pUserApi = CThostFtdcTraderApi::CreateFtdcTraderApi();
		m_pUserApi->RegisterSpi(this);
	}

	~CApplication()
	{
	}

	const std::string direction_to_string(TThostFtdcDirectionType Direction)
	{
		std::string str = Direction == THOST_FTDC_D_Buy ? "买" : "卖";
		return std::move(str);
	}

	const std::string posidirection_to_string(TThostFtdcPosiDirectionType Direction)
	{
		std::string str = Direction == THOST_FTDC_PD_Long ? "买" : "卖";
		return std::move(str);
	}

	double double_format(double value)
	{
		return value==DBL_MAX?0.0:value;
	}

	int Run()
	{
		m_pUserApi->RegisterFront((char*)m_host.c_str());
		m_pUserApi->SubscribePrivateTopic(THOST_TERT_QUICK);
		m_pUserApi->SubscribePublicTopic(THOST_TERT_QUICK);
		m_pUserApi->Init();

		return 0;
	}

	//连接成功
	void OnFrontConnected()
	{
		printf("Connected.\n");
		CThostFtdcReqAuthenticateField Req;
		memset(&Req, 0x00, sizeof(Req));
		strncpy_s(Req.BrokerID, m_broker.c_str(), sizeof(Req.BrokerID) - 1);
		strncpy_s(Req.UserID, m_user.c_str(), sizeof(Req.UserID) - 1);
		strncpy_s(Req.AuthCode, m_authcode.c_str(), sizeof(Req.AuthCode) - 1);
		strncpy_s(Req.AppID, m_appid.c_str(), sizeof(Req.AppID) - 1);
		m_pUserApi->ReqAuthenticate(&Req, 0);
	}

	//连接断开
	void OnFrontDisconnected(int nReason)
	{
		printf("Disconnected.\n");
	}


	///认证响应
	void OnRspAuthenticate(CThostFtdcRspAuthenticateField* pRspAuthenticateField, CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast)
	{
		if (pRspInfo->ErrorID != 0)
			printf("终端认证失败:%s\n", pRspInfo->ErrorMsg);
		else
			printf("终端认证成功.\n");

		// 登录
		printf("登录 ...\n");
		CThostFtdcReqUserLoginField Req;

		memset(&Req, 0x00, sizeof(Req));
		strncpy_s(Req.BrokerID, m_broker.c_str(), sizeof(Req.BrokerID) - 1);
		strncpy_s(Req.UserID, m_user.c_str(), sizeof(Req.UserID) - 1);
		strncpy_s(Req.Password, m_password.c_str(), sizeof(Req.Password) - 1);
		m_pUserApi->ReqUserLogin(&Req, 0);
	}


	//登录应答
	void OnRspUserLogin(CThostFtdcRspUserLoginField* pRspUserLogin, CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast)
	{
		if (pRspInfo && pRspInfo->ErrorID != 0) {
			printf("Login failed. %d - %s\n", pRspInfo->ErrorID, pRspInfo->ErrorMsg);
			return;
		}
		printf("Login succeeded.TradingDay:%s,FrontID=%d,SessionID=%d\n", pRspUserLogin->TradingDay, pRspUserLogin->FrontID, pRspUserLogin->SessionID);

		// 确认结算单
		CThostFtdcSettlementInfoConfirmField SettlementInfoConfirmField;

		memset(&SettlementInfoConfirmField, 0x00, sizeof(SettlementInfoConfirmField));
		strncpy_s(SettlementInfoConfirmField.BrokerID, pRspUserLogin->BrokerID, sizeof(SettlementInfoConfirmField.BrokerID) - 1);
		strncpy_s(SettlementInfoConfirmField.InvestorID, pRspUserLogin->UserID, sizeof(SettlementInfoConfirmField.InvestorID) - 1);
		strncpy_s(SettlementInfoConfirmField.ConfirmDate, pRspUserLogin->TradingDay, sizeof(SettlementInfoConfirmField.ConfirmDate) - 1);
		strncpy_s(SettlementInfoConfirmField.ConfirmTime, pRspUserLogin->LoginTime, sizeof(SettlementInfoConfirmField.ConfirmTime) - 1);
		m_pUserApi->ReqSettlementInfoConfirm(&SettlementInfoConfirmField, 0);

		_semaphore.signal();
	}

	// 查询合约列表
	void OnRspQryInstrument(CThostFtdcInstrumentField* pInstrument, CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast)
	{
		if (pInstrument)
			printf("InstrumentID:%s,InstrumentName:%s,ProductID:%s,PriceTick:%lf,UnderlyingInstrID:%s,StrikePrice:%lf,ExchangeID:%s\n", pInstrument->InstrumentID, pInstrument->InstrumentName, pInstrument->ProductID, pInstrument->PriceTick, pInstrument->UnderlyingInstrID, pInstrument->StrikePrice, pInstrument->ExchangeID);

		if (bIsLast) {
			_semaphore.signal();
		}
	}

	// 查询行情列表
	void OnRspQryDepthMarketData(CThostFtdcDepthMarketDataField* pDepthMarketData, CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast)
	{
		if (pRspInfo && pRspInfo->ErrorID != 0) {
			printf("查询行情失败. %d - %s\n", pRspInfo->ErrorID, pRspInfo->ErrorMsg);
			return;
		}

		printf("InstrumentID:%s,LastPrice:%lf,Volume:%d,Turnover:%lf,OpenPrice:%lf,HighestPrice:%lf,LowestPrice:%lf,UpperLimitPrice:%lf,LowerLimitPrice:%lf,OpenInterest:%lf,PreClosePrice:%lf,PreSettlementPrice:%lf,SettlementPrice:%lf,UpdateTime:%s,ActionDay:%s,TradingDay:%s,ExchangeID:%s\n",
			pDepthMarketData->InstrumentID, double_format(pDepthMarketData->LastPrice), pDepthMarketData->Volume, double_format(pDepthMarketData->Turnover), double_format(pDepthMarketData->OpenPrice),
			double_format(pDepthMarketData->HighestPrice), double_format(pDepthMarketData->LowestPrice), double_format(pDepthMarketData->UpperLimitPrice), double_format(pDepthMarketData->LowerLimitPrice),
			double_format(pDepthMarketData->OpenInterest), double_format(pDepthMarketData->PreClosePrice), double_format(pDepthMarketData->PreSettlementPrice),
			double_format(pDepthMarketData->SettlementPrice), pDepthMarketData->UpdateTime, pDepthMarketData->ActionDay, pDepthMarketData->TradingDay, pDepthMarketData->ExchangeID);

		if (bIsLast) {
			_semaphore.signal();
		}
	}

	// 查询委托列表
	void OnRspQryOrder(CThostFtdcOrderField* pOrder, CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast)
	{
		if (pRspInfo && pRspInfo->ErrorID != 0) {
			printf("查询订单失败. %d - %s\n", pRspInfo->ErrorID, pRspInfo->ErrorMsg);
			return;
		}

		if(pOrder)
			printf("OrderLocalID:%s,InstrumentID:%s,Direction:%s,VolumeTotalOriginal:%d,LimitPrice:%lf,VolumeTraded:%d,VolumeTotal:%d,OrderSysID:%s,FrontID:%d,SessionID:%d,OrderRef:%s,OrderStatus:%c,StatusMsg:%s,ExchangeID:%s,InsertTime:%s\n",
				pOrder->OrderLocalID, pOrder->InstrumentID, direction_to_string(pOrder->Direction).c_str(), pOrder->VolumeTotalOriginal, pOrder->LimitPrice, pOrder->VolumeTraded, pOrder->VolumeTotal, pOrder->OrderSysID, pOrder->FrontID, pOrder->SessionID, pOrder->OrderRef, pOrder->OrderStatus, pOrder->StatusMsg, pOrder->ExchangeID, pOrder->InsertTime);

		if (bIsLast) {
			_semaphore.signal();
		}
	}

	// 查询成交列表
	void OnRspQryTrade(CThostFtdcTradeField* pTrade, CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast)
	{
		if (pRspInfo && pRspInfo->ErrorID != 0) {
			printf("查询成交失败. %d - %s\n", pRspInfo->ErrorID, pRspInfo->ErrorMsg);
			return;
		}

		if(pTrade)
			printf("OrderLocalID:%s,InstrumentID:%s,Direction:%s,Volume:%d,Price:%lf,OrderSysID:%s,OrderRef:%s,ExchangeID:%s,TradeTime:%s\n",
				pTrade->OrderLocalID, pTrade->InstrumentID, direction_to_string(pTrade->Direction).c_str(), pTrade->Volume, pTrade->Price, pTrade->OrderSysID, pTrade->OrderRef, pTrade->ExchangeID, pTrade->TradeTime);

		if (bIsLast) {
			_semaphore.signal();
		}
	}

	// 查询持仓
	void OnRspQryInvestorPosition(CThostFtdcInvestorPositionField* pInvestorPosition, CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast)
	{
		if (pRspInfo && pRspInfo->ErrorID != 0) {
			printf("查询持仓失败. %d - %s\n", pRspInfo->ErrorID, pRspInfo->ErrorMsg);
			return;
		}

		if (pInvestorPosition)
			printf("InstrumentID:%s,PosiDirection:%s,HedgeFlag:%c,Position:%d,YdPosition:%d,TodayPosition:%d,PositionCost:%lf,OpenCost:%lf,ExchangeID:%s\n",
				pInvestorPosition->InstrumentID, posidirection_to_string(pInvestorPosition->PosiDirection).c_str(), pInvestorPosition->HedgeFlag, pInvestorPosition->Position, pInvestorPosition->YdPosition, pInvestorPosition->TodayPosition, pInvestorPosition->PositionCost, pInvestorPosition->OpenCost, pInvestorPosition->ExchangeID);

		if (bIsLast) {
			_semaphore.signal();
		}
	}


	// 查询持仓明细
	void OnRspQryInvestorPositionDetail(CThostFtdcInvestorPositionDetailField* pInvestorPositionDetail, CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast)
	{
		if (pRspInfo && pRspInfo->ErrorID != 0) {
			printf("查询持仓明细失败. %d - %s\n", pRspInfo->ErrorID, pRspInfo->ErrorMsg);
			return;
		}

		if (pInvestorPositionDetail)
			printf("InstrumentID:%s,Direction:%s,HedgeFlag:%c,Volume:%d,OpenDate:%s,OpenPrice:%lf,Margin:%lf,ExchangeID:%s\n",
				pInvestorPositionDetail->InstrumentID, direction_to_string(pInvestorPositionDetail->Direction).c_str(), pInvestorPositionDetail->HedgeFlag, pInvestorPositionDetail->Volume, pInvestorPositionDetail->OpenDate, pInvestorPositionDetail->OpenPrice, pInvestorPositionDetail->Margin, pInvestorPositionDetail->ExchangeID);

		if (bIsLast) {
			_semaphore.signal();
		}
	}

	///请求查询资金账户响应
	void OnRspQryTradingAccount(CThostFtdcTradingAccountField* pTradingAccount, CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast)
	{
		if (pTradingAccount)
			printf("AccountID:%s,Available:%lf,FrozenCash:%lf,FrozenCommission:%lf\n",
				pTradingAccount->AccountID, pTradingAccount->Available, pTradingAccount->FrozenCash, pTradingAccount->FrozenCommission);

		if (bIsLast)
			printf("Query completed.\n");
	}


	// 委托回报
	void OnRtnOrder(CThostFtdcOrderField* pOrder)
	{
		printf("OrderLocalID:%s,InstrumentID:%s,Direction:%s,VolumeTotalOriginal:%d,LimitPrice:%lf,VolumeTraded:%d,VolumeTotal:%d,OrderSysID:%s,FrontID:%d,SessionID:%d,OrderRef:%s,OrderStatus:%c,StatusMsg:%s,ExchangeID:%s,InsertTime:%s\n",
			pOrder->OrderLocalID, pOrder->InstrumentID, direction_to_string(pOrder->Direction).c_str(), pOrder->VolumeTotalOriginal, pOrder->LimitPrice, pOrder->VolumeTraded, pOrder->VolumeTotal, pOrder->OrderSysID, pOrder->FrontID, pOrder->SessionID, pOrder->OrderRef, pOrder->OrderStatus, pOrder->StatusMsg, pOrder->ExchangeID, pOrder->InsertTime);
	}

	// 成交回报
	void OnRtnTrade(CThostFtdcTradeField* pTrade)
	{
		printf("OrderLocalID:%s,InstrumentID:%s,Direction:%s,Volume:%d,Price:%lf,OrderSysID:%s,OrderRef:%s,ExchangeID:%s,TradeTime:%s\n",
			pTrade->OrderLocalID, pTrade->InstrumentID, direction_to_string(pTrade->Direction).c_str(), pTrade->Volume, pTrade->Price, pTrade->OrderSysID, pTrade->OrderRef, pTrade->ExchangeID, pTrade->TradeTime);
	}

	// 报单错误
	void OnErrRtnOrderInsert(CThostFtdcInputOrderField* pInputOrder, CThostFtdcRspInfoField* pRspInfo)
	{
		if (pRspInfo && pRspInfo->ErrorID != 0)
			printf("报单失败. %d - %s\n", pRspInfo->ErrorID, pRspInfo->ErrorMsg);

		if(pInputOrder)
			printf("OrderRef:%s,InstrumentID:%s,Direction:%s,VolumeTotalOriginal:%d,LimitPrice:%lf,ExchangeID:%s\n",
				pInputOrder->OrderRef, pInputOrder->InstrumentID, direction_to_string(pInputOrder->Direction).c_str(), pInputOrder->VolumeTotalOriginal, pInputOrder->LimitPrice, pInputOrder->ExchangeID);
	}


	// 撤单错误回报
	void OnErrRtnOrderAction(CThostFtdcOrderActionField* pOrderAction, CThostFtdcRspInfoField* pRspInfo)
	{
		if (pRspInfo && pRspInfo->ErrorID != 0)
			printf("撤单失败. %d - %s\n", pRspInfo->ErrorID, pRspInfo->ErrorMsg);

		if (pOrderAction)
			printf("FrontID:%d,SessionID:%d,OrderRef:%s,InstrumentID:%s,OrderActionRef:%d,OrderSysID:%s,LimitPrice:%lf,ExchangeID:%s\n",
				pOrderAction->FrontID, pOrderAction->SessionID, pOrderAction->OrderRef, pOrderAction->InstrumentID, pOrderAction->OrderActionRef, pOrderAction->OrderSysID, pOrderAction->LimitPrice, pOrderAction->ExchangeID);
	}

public:
	std::string m_host;
	std::string m_broker;
	std::string m_user;
	std::string m_password;
	std::string m_appid;
	std::string m_authcode;

	CThostFtdcTraderApi* m_pUserApi;
};


void display_usage()
{
	printf("usage:ctpprint host broker user password appid authcode\n");
	printf("example:ctpprint tcp://180.168.146.187:10130 9999 000001 888888 simnow_client_test 0000000000000000\n");
}


int main(int argc, char* argv[])
{
	if (argc != 7) {
		display_usage();
		return -1;
	}

	CApplication Spi(argv[1], argv[2], argv[3], argv[4], argv[5], argv[6]);

	// 启动
	if (Spi.Run() < 0)
		return -1;

	// 等待登录完成
	_semaphore.wait();

	// 查询合约
	printf("查询合约 ...\n");
	CThostFtdcQryInstrumentField QryInstrument = { 0 };
	Spi.m_pUserApi->ReqQryInstrument(&QryInstrument, 0);
	_semaphore.wait();

	// 查询行情
	std::this_thread::sleep_for(std::chrono::milliseconds(1000));
	printf("查询行情 ...\n");
	CThostFtdcQryDepthMarketDataField QryDepthMarketData = { 0 };
	Spi.m_pUserApi->ReqQryDepthMarketData(&QryDepthMarketData, 0);
	_semaphore.wait();

	// 查询订单
	std::this_thread::sleep_for(std::chrono::milliseconds(1000));
	printf("查询订单 ...\n");
	CThostFtdcQryOrderField QryOrder = { 0 };
	Spi.m_pUserApi->ReqQryOrder(&QryOrder, 0);
	_semaphore.wait();

	// 查询成交
	std::this_thread::sleep_for(std::chrono::milliseconds(1000));
	printf("查询成交 ...\n");
	CThostFtdcQryTradeField QryTrade = { 0 };
	Spi.m_pUserApi->ReqQryTrade(&QryTrade, 0);
	_semaphore.wait();

	// 查询持仓
	std::this_thread::sleep_for(std::chrono::milliseconds(1000));
	printf("查询持仓 ...\n");
	CThostFtdcQryInvestorPositionField QryInvestorPosition = { 0 };
	Spi.m_pUserApi->ReqQryInvestorPosition(&QryInvestorPosition, 0);
	_semaphore.wait();

	// 持仓明细
	std::this_thread::sleep_for(std::chrono::milliseconds(1000));
	printf("持仓明细 ...\n");
	CThostFtdcQryInvestorPositionDetailField QryInvestorPositionDetail = { 0 };
	Spi.m_pUserApi->ReqQryInvestorPositionDetail(&QryInvestorPositionDetail, 0);
	_semaphore.wait();

	// 查询资金
	std::this_thread::sleep_for(std::chrono::milliseconds(1000));
	printf("查询资金 ...\n");
	CThostFtdcQryTradingAccountField QryTradingAccount = { 0 };
	Spi.m_pUserApi->ReqQryTradingAccount(&QryTradingAccount, 0);

	getchar();

	return 0;
}
