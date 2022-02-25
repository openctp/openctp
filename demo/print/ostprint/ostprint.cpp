
#include <stdio.h>
#include <string>

#include <thread>
#include <mutex>
#include <functional>
#include <condition_variable>

#include "./OST/UTApi.h"
#pragma comment (lib, "./OST/utapi.lib")		//x64

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

class CApplication : public CUTSpi
{
public:
	CApplication(std::string host, /*std::string broker, */std::string user, std::string password, std::string appid = "", std::string authcode = "") :
		m_host(host),
		//m_broker(broker),
		m_user(user),
		m_password(password),
		m_appid(appid),
		m_authcode(authcode)
	{
		m_pUserApi = CUTApi::CreateApi();
		m_pUserApi->RegisterSpi(this);
	}

	~CApplication()
	{
	}

	const std::string direction_to_string(TUTDirectionType Direction)
	{
		std::string str = Direction == UT_D_Buy ? "买" : "卖";
		return std::move(str);
	}

	const std::string posidirection_to_string(TUTPosiDirectionType Direction)
	{
		std::string str = Direction == UT_PD_Long ? "买" : "卖";
		return std::move(str);
	}

	double double_format(double value)
	{
		return value==DBL_MAX?0.0:value;
	}

	int Run()
	{
		m_pUserApi->RegisterFront((char*)m_host.c_str());
		m_pUserApi->SubscribePrivateTopic(UT_TERT_QUICK);
		//暂时没有公有流
		//m_pUserApi->SubscribePublicTopic(UT_TERT_QUICK);
		m_pUserApi->Init();

		return 0;
	}

	// 下单
	int OrderInsert(const char* ExchangeID, const char* InstrumentID, TUTDirectionType Direction, TUTOffsetFlagType OffsetFlag, double Price, unsigned int Qty)
	{
		CUTInputOrderField Req;

		memset(&Req, 0x00, sizeof(CUTInputOrderField));
		strncpy_s(Req.InvestorID, m_user.c_str(), sizeof(Req.InvestorID) - 1);
		strncpy_s(Req.InstrumentID, InstrumentID, sizeof(Req.InstrumentID) - 1);
		Req.ExchangeID = UT_EXG_SSE;  //SSE
		//OrderRef必须设置,同一会话内必须递增,可以不连续
		Req.OrderRef = ++m_nOrderRef;
		Req.OrderPriceType = UT_OPT_LimitPrice;
		Req.Direction = Direction;		//UT_D_Buy
		Req.OffsetFlag = OffsetFlag;	// UT_OF_Open
		Req.HedgeFlag = UT_HF_Speculation;
		Req.VolumeTotalOriginal = Qty;	//100
		Req.LimitPrice = Price;
		Req.TimeCondition = UT_TC_GFD;
		if (Req.OrderPriceType == UT_OPT_AnyPrice)
			Req.TimeCondition = UT_TC_IOC;
		Req.VolumeCondition = UT_VC_AV;
		Req.MinVolume = 1;
		Req.ContingentCondition = UT_CC_Immediately;
		Req.StopPrice = 0;
		Req.IsAutoSuspend = 0;
		Req.UserForceClose = 0;

		return m_pUserApi->ReqOrderInsert(&Req, 0);
	}

	// 撤单
	int OrderCancel(int FrontID, long long SessionID, int OrderRef)
	{
		CUTInputOrderActionField Req;

		memset(&Req, 0x00, sizeof(CUTInputOrderActionField));
		Req.FrontID = FrontID;			// m_frontid
		Req.SessionID = SessionID; // m_sessionid
		Req.OrderRef = OrderRef;
		Req.OrderActionRef = ++m_nOrderRef;
		Req.ActionFlag = UT_AF_Delete;

		return m_pUserApi->ReqOrderAction(&Req, 0);
	}



	//连接成功
	void OnFrontConnected()
	{
		printf("Connected.\n");

		//登录请求
		CUTReqLoginField Req;
		memset(&Req, 0x00, sizeof(CUTReqLoginField));

		strncpy_s(Req.UserID, m_user.c_str(), sizeof(Req.UserID) - 1);
		strncpy_s(Req.Password, m_password.c_str(), sizeof(Req.Password) - 1);
		strncpy_s(Req.UserProductInfo, m_appid.c_str(), sizeof(Req.UserProductInfo) - 1);
		strncpy_s(Req.UserProductPassword, m_authcode.c_str(), sizeof(Req.UserProductPassword) - 1);

		m_pUserApi->ReqLogin(&Req, 0);
	}

	//连接断开
	void OnFrontDisconnected(int nReason)
	{
		printf("Disconnected.\n");
	}

	//登录应答
	void OnRspLogin(CUTRspLoginField *pRspUserLogin, CUTRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
	{
		if (pRspInfo && pRspInfo->ErrorID != 0) {
			printf("Login failed. %d - %s\n", pRspInfo->ErrorID, pRspInfo->ErrorMsg);
			return;
		}

		printf("Login succeeded.TradingDay:%d,LoginTime:%d,FrontID=%d,SessionID=%lld\n", 
			pRspUserLogin->TradingDay, pRspUserLogin->LoginTime, pRspUserLogin->FrontID, pRspUserLogin->SessionID);

		m_frontid = pRspUserLogin->FrontID;		//前置
		m_sessionid = pRspUserLogin->SessionID;		//会话

		_semaphore.signal();
	}

	/*投资者手续费率查询应答*/
	void OnRspQryInstrumentCommissionRate(CUTInstrumentCommissionRateField *pInstrumentCommissionRate, CUTRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
	{
		if (pInstrumentCommissionRate)
			printf("OnRspQryInstrumentCommissionRate:ExchangeID:%s,InstrumentID:%s,OpenRatioByMoney:%lf,CloseRatioByMoney:%lf,CloseTodayRatioByMoney:%lf,OpenRatioByVolume:%lf,CloseRatioByVolume:%lf,CloseTodayRatioByVolume:%lf\n", 
				(pInstrumentCommissionRate->ExchangeID == UT_EXG_SSE) ? "SSE" : "SZSE", pInstrumentCommissionRate->InstrumentID,
				pInstrumentCommissionRate->OpenRatioByMoney, pInstrumentCommissionRate->CloseRatioByMoney, pInstrumentCommissionRate->CloseTodayRatioByMoney,
				pInstrumentCommissionRate->OpenRatioByVolume, pInstrumentCommissionRate->CloseRatioByVolume, pInstrumentCommissionRate->CloseTodayRatioByVolume);

		if (bIsLast) {
			_semaphore.signal();
		}
	}

	// 查询合约列表
	void OnRspQryInstrument(CUTInstrumentField *pInstrument, CUTRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
	{
		if (pInstrument)
			printf("OnRspQryInstrument:InstrumentID:%s,InstrumentName:%s,ProductID:%s,PriceTick:%lf,UnderlyingInstrID:%s,StrikePrice:%lf,ExchangeID:%s\n", 
				pInstrument->InstrumentID, pInstrument->InstrumentName, pInstrument->ProductID, pInstrument->PriceTick, pInstrument->UnderlyingInstrID, pInstrument->StrikePrice, (pInstrument->ExchangeID == UT_EXG_SSE) ? "SSE" : "SZSE");		//简化处理：交易所只打印上证/深证

		if (bIsLast) {
			_semaphore.signal();
		}
	}

	// 查询行情列表
	void OnRspQryDepthMarketData(CUTDepthMarketDataField *pDepthMarketData, CUTRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
	{
		if (pRspInfo && pRspInfo->ErrorID != 0) {
			printf("OnRspQryDepthMarketData. %d - %s\n", pRspInfo->ErrorID, pRspInfo->ErrorMsg);
			return;
		}

		printf("OnRspQryDepthMarketData:InstrumentID:%s,LastPrice:%lf,Volume:%lld,Turnover:%lf,OpenPrice:%lf,HighestPrice:%lf,LowestPrice:%lf,UpperLimitPrice:%lf,LowerLimitPrice:%lf,OpenInterest:%lld,PreClosePrice:%lf,PreSettlementPrice:%lf,SettlementPrice:%lf,UpdateTime:%d,ActionDay:%d,TradingDay:%d,ExchangeID:%s\n",
			pDepthMarketData->InstrumentID, double_format(pDepthMarketData->LastPrice), pDepthMarketData->Volume, double_format(pDepthMarketData->Turnover), double_format(pDepthMarketData->OpenPrice),
			double_format(pDepthMarketData->HighestPrice), double_format(pDepthMarketData->LowestPrice), double_format(pDepthMarketData->UpperLimitPrice), double_format(pDepthMarketData->LowerLimitPrice),
			pDepthMarketData->OpenInterest, double_format(pDepthMarketData->PreClosePrice), double_format(pDepthMarketData->PreSettlementPrice),
			double_format(pDepthMarketData->SettlementPrice), pDepthMarketData->UpdateTime, pDepthMarketData->ActionDay, pDepthMarketData->TradingDay, (pDepthMarketData->ExchangeID == UT_EXG_SSE) ? "SSE" : "SZSE");

		if (bIsLast) {
			_semaphore.signal();
		}
	}

	// 查询委托列表
	void OnRspQryOrder(CUTOrderField *pOrder, CUTRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
	{
		if (pRspInfo && pRspInfo->ErrorID != 0) {
			printf("OnRspQryOrder. %d - %s\n", pRspInfo->ErrorID, pRspInfo->ErrorMsg);
			return;
		}

		if(pOrder)
			printf("OnRspQryOrder:FrontID:%d,SessionID:%lld,OrderLocalID:%s,InstrumentID:%s,Direction:%s,VolumeTotalOriginal:%d,LimitPrice:%lf,VolumeTraded:%d,VolumeTotal:%d,OrderSysID:%s,OrderRef:%d,OrderStatus:%c,ExchangeID:%s,InsertTime:%d,ClientID:%s\n",
				pOrder->FrontID, pOrder->SessionID, pOrder->OrderLocalID, pOrder->InstrumentID, direction_to_string(pOrder->Direction).c_str(), pOrder->VolumeTotalOriginal, pOrder->LimitPrice, pOrder->VolumeTraded, pOrder->VolumeTotal, pOrder->OrderSysID, 
				pOrder->OrderRef, pOrder->OrderStatus, (pOrder->ExchangeID == UT_EXG_SSE) ? "SSE" : "SZSE", pOrder->InsertTime,pOrder->ClientID);

		if (bIsLast) {
			_semaphore.signal();
		}
	}

	// 查询成交列表
	void OnRspQryTrade(CUTTradeField *pTrade, CUTRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
	{
		if (pRspInfo && pRspInfo->ErrorID != 0) {
			printf("OnRspQryTrade. %d - %s\n", pRspInfo->ErrorID, pRspInfo->ErrorMsg);
			return;
		}

		if(pTrade)
			printf("OnRspQryTrade:FrontID:%d,SessionID:%lld,OrderLocalID:%s,InstrumentID:%s,Direction:%s,Volume:%d,Price:%lf,OrderSysID:%s,OrderRef:%d,ExchangeID:%s,TradeDate:%d,TradeTime:%d,ClientID:%s\n",
				pTrade->FrontID, pTrade->SessionID, pTrade->OrderLocalID, pTrade->InstrumentID, direction_to_string(pTrade->Direction).c_str(), pTrade->Volume, pTrade->Price, pTrade->OrderSysID, pTrade->OrderRef, 
				(pTrade->ExchangeID == UT_EXG_SSE) ? "SSE" : "SZSE", pTrade->TradeDate, pTrade->TradeTime,pTrade->ClientID);

		if (bIsLast) {
			_semaphore.signal();
		}
	}

	// 查询持仓
	void OnRspQryInvestorPosition(CUTInvestorPositionField *pInvestorPosition, CUTRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
	{
		if (pRspInfo && pRspInfo->ErrorID != 0) {
			printf("OnRspQryInvestorPosition. %d - %s\n", pRspInfo->ErrorID, pRspInfo->ErrorMsg);
			return;
		}

		if (pInvestorPosition)
			printf("OnRspQryInvestorPosition:InstrumentID:%s,PosiDirection:%s,HedgeFlag:%c,Position:%lld,YdPosition:%lld,TodayPosition:%lld,PositionCost:%lf,OpenCost:%lf,ExchangeID:%s\n",
				pInvestorPosition->InstrumentID, posidirection_to_string(pInvestorPosition->PosiDirection).c_str(), pInvestorPosition->HedgeFlag, pInvestorPosition->Position, 
				pInvestorPosition->YdPosition, pInvestorPosition->TodayPosition, pInvestorPosition->PositionCost, pInvestorPosition->OpenCost, (pInvestorPosition->ExchangeID == UT_EXG_SSE) ? "SSE" : "SZSE");

		if (bIsLast) {
			_semaphore.signal();
		}
	}

	//求查询资金账户响应
	void OnRspQryTradingAccount(CUTTradingAccountField *pTradingAccount, CUTRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
	{
		if (pTradingAccount)
			printf("OnRspQryTradingAccount:AccountID:%s,Available:%lf,FrozenCash:%lf,FrozenCommission:%lf\n",
				pTradingAccount->AccountID, pTradingAccount->Available, pTradingAccount->FrozenCash, pTradingAccount->FrozenCommission);

		if (bIsLast)
			_semaphore.signal();
			printf("Query completed.\n");
	}
	
	// 委托回报
	void OnRtnOrder(CUTOrderField *pOrder)
	{
		printf("OnRtnOrder:FrontID:%d,SessionID:%lld,OrderLocalID:%s,InstrumentID:%s,Direction:%s,VolumeTotalOriginal:%d,LimitPrice:%lf,VolumeTraded:%d,VolumeTotal:%d,OrderSysID:%s,OrderRef:%d,OrderStatus:%c,ExchangeID:%s,InsertTime:%d,ClientID:%s\n",
			pOrder->FrontID, pOrder->SessionID, pOrder->OrderLocalID, pOrder->InstrumentID, direction_to_string(pOrder->Direction).c_str(), pOrder->VolumeTotalOriginal, pOrder->LimitPrice, pOrder->VolumeTraded, pOrder->VolumeTotal, pOrder->OrderSysID, 
			pOrder->OrderRef, pOrder->OrderStatus, (pOrder->ExchangeID == UT_EXG_SSE) ? "SSE" : "SZSE", pOrder->InsertTime,pOrder->ClientID);
	}

	// 成交回报
	void OnRtnTrade(CUTTradeField *pTrade)
	{
		printf("OnRtnTrade:FrontID:%d,SessionID:%lld,OrderLocalID:%s,InstrumentID:%s,Direction:%s,Volume:%d,Price:%lf,OrderSysID:%s,OrderRef:%d,ExchangeID:%s,TradeTime:%d,ClientID:%s\n",
			pTrade->FrontID, pTrade->SessionID, pTrade->OrderLocalID, pTrade->InstrumentID, direction_to_string(pTrade->Direction).c_str(), pTrade->Volume, pTrade->Price, pTrade->OrderSysID, pTrade->OrderRef,
			(pTrade->ExchangeID == UT_EXG_SSE) ? "SSE" : "SZSE", pTrade->TradeTime,pTrade->ClientID);
	}
	   

	// 报单错误
	void OnRspOrderInsert(CUTInputOrderField *pInputOrder, CUTRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
	{
		if (pRspInfo && pRspInfo->ErrorID != 0)
			printf("OnRspOrderInsert. %d - %s\n", pRspInfo->ErrorID, pRspInfo->ErrorMsg);

		if(pInputOrder)
			printf("OnRspOrderInsert:OrderRef:%d,InstrumentID:%s,Direction:%s,VolumeTotalOriginal:%d,LimitPrice:%lf,ExchangeID:%s\n",
				pInputOrder->OrderRef, pInputOrder->InstrumentID, direction_to_string(pInputOrder->Direction).c_str(), pInputOrder->VolumeTotalOriginal, pInputOrder->LimitPrice, 
				(pInputOrder->ExchangeID == UT_EXG_SSE) ? "SSE" : "SZSE");
	}

	// 撤单错误回报 被UT打回时的响应;正确时不会产生该响应,而是回调OnRtnOrder
	void OnRspOrderAction(CUTInputOrderActionField *pInputOrderAction, CUTRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
	{
		if (pRspInfo && pRspInfo->ErrorID != 0)
			printf("OnRspOrderAction. %d - %s\n", pRspInfo->ErrorID, pRspInfo->ErrorMsg);

		if (pInputOrderAction)
			printf("OnRspOrderAction:FrontID:%d,SessionID:%lld,OrderRef:%d,OrderActionRef:%d,VolumeChange:%d,LimitPrice:%lf\n",
				pInputOrderAction->FrontID, pInputOrderAction->SessionID, pInputOrderAction->OrderRef, pInputOrderAction->OrderActionRef, pInputOrderAction->VolumeChange, pInputOrderAction->LimitPrice);
	}

	// 撤单错误回报 被交易所打回时的回报
	void OnErrRtnOrderAction(CUTOrderActionField *pOrderAction)
	{
		if (pOrderAction)
			printf("OnErrRtnOrderAction:FrontID:%d,SessionID:%lld,OrderRef:%d,InstrumentID:%s,OrderActionRef:%d,OrderSysID:%s,LimitPrice:%lf,ExchangeID:%s\n",
				pOrderAction->FrontID, pOrderAction->SessionID, pOrderAction->OrderRef, pOrderAction->InstrumentID, pOrderAction->OrderActionRef, pOrderAction->OrderSysID, pOrderAction->LimitPrice, 
				(pOrderAction->ExchangeID == UT_EXG_SSE) ? "SSE" : "SZSE");
	}

	int GetForntID() { return m_frontid; }
	long long GetSessionId() { return m_sessionid; }

public:
	std::string m_host;
	//std::string m_broker;		//no borker item
	std::string m_user;
	std::string m_password;
	std::string m_appid;			//UserProductInfo
	std::string m_authcode;		//UserProductPassword
	unsigned int m_nOrderRef;

	int m_frontid;		//前置
	long long m_sessionid;		//会话

	CUTApi* m_pUserApi;
};


void display_usage()
{
	printf("usage:ostprint host user password\n");
	printf("example:ostprint tcp://XXX.XXX.XXX.XXX:XXX 000001 888888\n");
}


int main(int argc, char* argv[])
{
	if (argc <= 4) {
		display_usage();
		return -1;
	}

	std::string host(argv[1]), user(argv[2]), password(argv[3]);		/*, appid(argv[4]), authcode(argv[5])*/

	CApplication Spi(host, user, password);

	// 启动
	if (Spi.Run() < 0)
		return -1;

	// 等待登录完成
	_semaphore.wait();

	// 查询投资者手续费率
	std::this_thread::sleep_for(std::chrono::milliseconds(1000));
	printf("查询投资者手续费率 ...\n");
	CUTQryInstrumentCommissionRateField QryInstrumentCommissionRate = { 0 };
	strncpy(QryInstrumentCommissionRate.InvestorID, user.c_str(), sizeof(QryInstrumentCommissionRate.InvestorID) - 1);
	QryInstrumentCommissionRate.ExchangeID = UT_EXG_SSE;
	strncpy(QryInstrumentCommissionRate.InstrumentID, "600000", sizeof(QryInstrumentCommissionRate.InstrumentID) - 1);
	Spi.m_pUserApi->ReqQryInstrumentCommissionRate(&QryInstrumentCommissionRate, 0);
	
	// 等待查询投资者手续费率完成
	_semaphore.wait();

	// 查询合约
	std::this_thread::sleep_for(std::chrono::milliseconds(1000));
	printf("查询合约 ...\n");
	CUTQryInstrumentField QryInstrument = { 0 };
	Spi.m_pUserApi->ReqQryInstrument(&QryInstrument, 0);

	// 等待查询合约完成
	_semaphore.wait();

	// 查询行情
	std::this_thread::sleep_for(std::chrono::milliseconds(1000));
	printf("查询行情 ...\n");
	CUTQryDepthMarketDataField QryDepthMarketData = { 0 };
	Spi.m_pUserApi->ReqQryDepthMarketData(&QryDepthMarketData, 0);

	// 等待查询行情完成
	_semaphore.wait();

	// 查询订单
	std::this_thread::sleep_for(std::chrono::milliseconds(1000));
	printf("查询订单 ...\n");
	CUTQryOrderField QryOrder = { 0 };
	Spi.m_pUserApi->ReqQryOrder(&QryOrder, 0);

	// 等待查询订单完成
	_semaphore.wait();

	// 查询成交
	std::this_thread::sleep_for(std::chrono::milliseconds(1000));
	printf("查询成交 ...\n");
	CUTQryTradeField QryTrade = { 0 };
	Spi.m_pUserApi->ReqQryTrade(&QryTrade, 0);

	// 等待查询成交完成
	_semaphore.wait();

	// 查询持仓
	std::this_thread::sleep_for(std::chrono::milliseconds(1000));
	printf("查询持仓 ...\n");
	CUTQryInvestorPositionField QryInvestorPosition = { 0 };
	Spi.m_pUserApi->ReqQryInvestorPosition(&QryInvestorPosition, 0);

	// 等待查询持仓完成
	_semaphore.wait();

	// 查询资金
	std::this_thread::sleep_for(std::chrono::milliseconds(1000));
	printf("查询资金 ...\n");
	CUTQryTradingAccountField QryTradingAccount = { 0 };
	Spi.m_pUserApi->ReqQryTradingAccount(&QryTradingAccount, 0);

	// 等待查询资金完成
	_semaphore.wait();

	 //如需下单、撤单，放开下面的代码即可
	//std::this_thread::sleep_for(std::chrono::milliseconds(1000));
	//printf("按任意键下单 ...\n");
	//getchar();
	//Spi.OrderInsert("SSE", "600000", UT_D_Buy, UT_OF_Open, 8.5, 100);	//1手

	//std::this_thread::sleep_for(std::chrono::milliseconds(1000));
	//printf("按任意键下单 ...\n");
	//getchar();
	//Spi.OrderInsert("SZSE", "000001", UT_D_Sell, UT_OF_Close, 16.0, 100);		//1手

	//std::this_thread::sleep_for(std::chrono::milliseconds(1000));
	//printf("按任意键撤单 ...\n");
	//getchar();
	//Spi.OrderCancel(Spi.GetForntID(), Spi.GetSessionId(), 1);		//假设订单的OrderRef为 1，实际需要填入下单返回的OrderRef

	std::this_thread::sleep_for(std::chrono::milliseconds(1000));
	printf("按任意键退出 ...\n");
	getchar();

	return 0;
}
