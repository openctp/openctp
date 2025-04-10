// author: krenx@openctp
// last modify: 2024/6/6

#include <stdio.h>
#include <string>
#include <thread>
#include <mutex>
#include <functional>
#include <condition_variable>
#include "QdpFtdcTraderApi.h"


class semaphore
{
public:
	semaphore(int value = 1) :count(value) {}

	void wait()
	{
		std::unique_lock<std::mutex> lck(mt);
		if (--count < 0)
			cv.wait(lck);
	}

	void signal()
	{
		std::unique_lock<std::mutex> lck(mt);
		if (++count <= 0)
			cv.notify_one();
	}

private:
	int count;
	std::mutex mt;
	std::condition_variable cv;
};

semaphore _semaphore(0);

class CApplication : public CQdpFtdcTraderSpi
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
		m_pUserApi = CQdpFtdcTraderApi::CreateFtdcTraderApi();
		m_pUserApi->RegisterSpi(this);
	}

	~CApplication()
	{
	}

	const std::string direction_to_string(TQdpFtdcDirectionType Direction)
	{
		std::string str = Direction == QDP_FTDC_D_Buy ? "买" : "卖";
		return std::move(str);
	}

	double double_format(double value)
	{
		return value==DBL_MAX?0.0:value;
	}

	int Run()
	{
		m_pUserApi->RegisterFront((char*)m_host.c_str());
		m_pUserApi->SubscribePrivateTopic(QDP_TERT_QUICK);
		m_pUserApi->SubscribePublicTopic(QDP_TERT_QUICK);
		m_pUserApi->Init();

		return 0;
	}

	// 下单
	int OrderInsert(const char* ExchangeID, const char* InstrumentID, TQdpFtdcDirectionType Direction, TQdpFtdcOffsetFlagType OffsetFlag, double Price, unsigned int Qty)
	{
		CQdpFtdcInputOrderField Req;

		memset(&Req, 0x00, sizeof(Req));
		strncpy_s(Req.UserID, m_user.c_str(), sizeof(Req.UserID) - 1);
		strncpy_s(Req.BrokerID, m_broker.c_str(), sizeof(Req.BrokerID) - 1);
		strncpy_s(Req.InvestorID, m_user.c_str(), sizeof(Req.InvestorID) - 1);
		strncpy_s(Req.InstrumentID, InstrumentID, sizeof(Req.InstrumentID) - 1);
		strncpy_s(Req.ExchangeID, ExchangeID, sizeof(Req.ExchangeID) - 1);
		Req.Direction = Direction;
		Req.OffsetFlag = OffsetFlag;
		Req.HedgeFlag = QDP_FTDC_CHF_Speculation;
		Req.Volume = Qty;
		Req.LimitPrice = Price;
		Req.OrderPriceType = QDP_FTDC_OPT_LimitPrice;
		Req.UserOrderLocalID = m_nOrderRef++;
		Req.TimeCondition = QDP_FTDC_TC_GFD;
		if (Req.OrderPriceType == QDP_FTDC_OPT_AnyPrice)
			Req.TimeCondition = QDP_FTDC_TC_IOC;
		Req.VolumeCondition = QDP_FTDC_VC_AV;
		Req.MinVolume = 1;
		Req.ForceCloseReason = QDP_FTDC_FCR_NotForceClose;
		Req.IsAutoSuspend = 0;
		strncpy_s(Req.UserCustom, "XXXX", sizeof(Req.UserCustom) - 1);

		return m_pUserApi->ReqOrderInsert(&Req, 0);
	}

	// 撤单
	int OrderCancel(const char* ExchangeID, const char* InstrumentID, const char* OrderSysID)
	{
		CQdpFtdcOrderActionField Req;

		memset(&Req, 0x00, sizeof(Req));
		strncpy_s(Req.BrokerID, m_broker.c_str(), sizeof(Req.BrokerID) - 1);
		strncpy_s(Req.InvestorID, m_user.c_str(), sizeof(Req.InvestorID) - 1);
		strncpy_s(Req.InstrumentID, InstrumentID, sizeof(Req.InstrumentID) - 1);
		strncpy_s(Req.ExchangeID, ExchangeID, sizeof(Req.ExchangeID) - 1);
		strncpy_s(Req.OrderSysID, OrderSysID, sizeof(Req.OrderSysID) - 1);
		//Req.FrontID = 1;
		//Req.SessionID = 1;
		//Req.UserOrderLocalID = 1;
		Req.ActionFlag = QDP_FTDC_AF_Delete;

		return m_pUserApi->ReqOrderAction(&Req, 0);
	}

	//连接成功
	void OnFrontConnected()
	{
		printf("Connected.\n");

		// 产品认证
		CQdpFtdcAuthenticateField Req;
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
	void OnRspAuthenticate(CQdpFtdcRtnAuthenticateField* pRtnAuthenticate, CQdpFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast)
	{
		if (pRspInfo->ErrorID != 0)
			printf("OnRspAuthenticate:%s\n", pRspInfo->ErrorMsg);
		else
			printf("Authenticate succeeded.\n");

		// 登录
		printf("Login ...\n");
		CQdpFtdcReqUserLoginField Req;

		memset(&Req, 0x00, sizeof(Req));
		strncpy_s(Req.BrokerID, m_broker.c_str(), sizeof(Req.BrokerID) - 1);
		strncpy_s(Req.UserID, m_user.c_str(), sizeof(Req.UserID) - 1);
		strncpy_s(Req.Password, m_password.c_str(), sizeof(Req.Password) - 1);
		m_pUserApi->ReqUserLogin(&Req, 0);
	}

	//登录应答
	void OnRspUserLogin(CQdpFtdcRspUserLoginField* pRspUserLogin, CQdpFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast)
	{
		if (pRspInfo && pRspInfo->ErrorID != 0) {
			printf("Login failed. %d - %s\n", pRspInfo->ErrorID, pRspInfo->ErrorMsg);
			return;
		}
		printf("Login succeeded.TradingDay:%s,FrontID=%d,SessionID=%d,MaxOrderLocalID=%d\n", pRspUserLogin->TradingDay, pRspUserLogin->FrontID, pRspUserLogin->SessionID, pRspUserLogin->MaxOrderLocalID);
		m_nOrderRef = 1;

		// 订阅推送信息（委托回报、市场状态通知等）
		CQdpFtdcFlowStatusField FlowStatus = { 0 };
		FlowStatus.SequenceSeries = QDP_TERT_PRIVATE;
		FlowStatus.bReady = true;
		m_pUserApi->ReqReady(&FlowStatus, 0);
		FlowStatus.SequenceSeries = QDP_TERT_PUBLIC;
		FlowStatus.bReady = true;
		m_pUserApi->ReqReady(&FlowStatus, 0);

		_semaphore.signal();
	}

	// 下单应答
	void OnRspOrderInsert(CQdpFtdcInputOrderField* pInputOrder, CQdpFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast)
	{
		if (pRspInfo && pRspInfo->ErrorID != 0) {
			printf("OnRspOrderInsert. %d - %s\n", pRspInfo->ErrorID, pRspInfo->ErrorMsg);
			return;
		}
		printf("OnRspOrderInsert:InstrumentID:%s,ExchangeID:%s,Direction:%s,OffsetFlag:%c,Volume:%d,LimitPrice:%lf,UserOrderLocalID:%d,OrderSysID=%s,UserCustom=%s\n", pInputOrder->InstrumentID, pInputOrder->ExchangeID, direction_to_string(pInputOrder->Direction).c_str(), pInputOrder->OffsetFlag, pInputOrder->Volume, pInputOrder->LimitPrice, pInputOrder->UserOrderLocalID, pInputOrder->OrderSysID, pInputOrder->UserCustom);
	}

	// 撤单应答
	void OnRspOrderAction(CQdpFtdcOrderActionField* pOrderAction, CQdpFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast)
	{
		if (pRspInfo && pRspInfo->ErrorID != 0) {
			printf("OnRspOrderAction. %d - %s\n", pRspInfo->ErrorID, pRspInfo->ErrorMsg);
			return;
		}
		printf("OnRspOrderAction:InstrumentID:%s,ExchangeID:%s,OrderSysID:%s,FrontID:%d,SessionID:%d,UserOrderLocalID:%d,UserOrderActionLocalID=%d\n", pOrderAction->InstrumentID, pOrderAction->ExchangeID, pOrderAction->OrderSysID, pOrderAction->FrontID, pOrderAction->SessionID, pOrderAction->UserOrderLocalID, pOrderAction->UserOrderActionLocalID);
	}

	/*可用投资者账户查询应答*/
	void OnRspQryUserInvestor(CQdpFtdcRspUserInvestorField* pRspUserInvestor, CQdpFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast)
	{
		if (pRspUserInvestor)
			printf("OnRspQryUserInvestor:BrokerID:%s,UserID:%s,InvestorID:%s\n", pRspUserInvestor->BrokerID, pRspUserInvestor->UserID, pRspUserInvestor->InvestorID);

		if (bIsLast) {
			_semaphore.signal();
		}
	}

	/*交易所查询应答*/
	void OnRspQryExchange(CQdpFtdcRspExchangeField* pRspExchange, CQdpFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast)
	{
		if (pRspExchange)
			printf("OnRspQryExchange:ExchangeID:%s,ExchangeName:%s\n", pRspExchange->ExchangeID, pRspExchange->ExchangeName);

		if (bIsLast) {
			_semaphore.signal();
		}
	}

	/*投资者手续费率查询应答*/
	void OnRspQryInvestorFee(CQdpFtdcInvestorFeeField* pInvestorFee, CQdpFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast)
	{
		if (pInvestorFee)
			printf("OnRspQryInvestorFee:InvestorID:%s,ExchangeID:%s,InstrumentID:%s,HedgeFlag:%c,OpenFeeRate:%lf,OpenFeeAmt:%lf,OTFeeRate:%lf,OTFeeAmt:%lf,OffsetFeeRate:%lf,OffsetFeeAmt:%lf\n", 
				pInvestorFee->InvestorID, pInvestorFee->ExchangeID, pInvestorFee->InstrumentID,pInvestorFee->HedgeFlag,
				pInvestorFee->OpenFeeRate, pInvestorFee->OpenFeeAmt, pInvestorFee->OTFeeRate,
				pInvestorFee->OTFeeAmt, pInvestorFee->OffsetFeeRate, pInvestorFee->OffsetFeeAmt);

		if (bIsLast) {
			_semaphore.signal();
		}
	}

	/*投资者保证金率查询应答*/
	void OnRspQryInvestorMargin(CQdpFtdcInvestorMarginField* pInvestorMargin, CQdpFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast)
	{
		if (pInvestorMargin)
			printf("OnRspQryInvestorMargin:InvestorID:%s,ExchangeID:%s,InstrumentID:%s,HedgeFlag:%c,LongMarginRate:%lf,LongMarginAmt:%lf,ShortMarginRate:%lf,ShortMarginAmt:%lf\n",
				pInvestorMargin->InvestorID, pInvestorMargin->ExchangeID, pInvestorMargin->InstrumentID,pInvestorMargin->HedgeFlag,
				pInvestorMargin->LongMarginRate, pInvestorMargin->LongMarginAmt, pInvestorMargin->ShortMarginRate,
				pInvestorMargin->ShortMarginAmt);

		if (bIsLast) {
			_semaphore.signal();
		}
	}

	// 查询合约列表
	void OnRspQryInstrument(CQdpFtdcRspInstrumentField* pRspInstrument, CQdpFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast)
	{
		if (pRspInstrument)
			printf("OnRspQryInstrument:InstrumentID:%s,InstrumentName:%s,ProductID:%s,PriceTick:%lf,UnderlyingInstrID:%s,StrikePrice:%lf,ExchangeID:%s\n", pRspInstrument->InstrumentID, pRspInstrument->InstrumentName, pRspInstrument->ProductID, pRspInstrument->PriceTick, pRspInstrument->UnderlyingInstrID, pRspInstrument->StrikePrice, pRspInstrument->ExchangeID);

		if (bIsLast) {
			_semaphore.signal();
		}
	}

	// 查询行情列表
	void OnRspQryMarketData(CQdpFtdcMarketDataField* pMarketData, CQdpFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast)
	{
		if (pRspInfo && pRspInfo->ErrorID != 0) {
			printf("OnRspQryDepthMarketData. %d - %s\n", pRspInfo->ErrorID, pRspInfo->ErrorMsg);
			return;
		}

		if(pMarketData)
			printf("OnRspQryDepthMarketData:InstrumentID:%s,LastPrice:%lf,Volume:%d,Turnover:%lf,OpenPrice:%lf,HighestPrice:%lf,LowestPrice:%lf,UpperLimitPrice:%lf,LowerLimitPrice:%lf,OpenInterest:%lf,PreClosePrice:%lf,PreSettlementPrice:%lf,SettlementPrice:%lf,UpdateTime:%s,TradingDay:%s,ExchangeID:%s\n",
				pMarketData->InstrumentID, double_format(pMarketData->LastPrice), pMarketData->Volume, double_format(pMarketData->Turnover), double_format(pMarketData->OpenPrice),
				double_format(pMarketData->HighestPrice), double_format(pMarketData->LowestPrice), double_format(pMarketData->UpperLimitPrice), double_format(pMarketData->LowerLimitPrice),
				double_format(pMarketData->OpenInterest), double_format(pMarketData->PreClosePrice), double_format(pMarketData->PreSettlementPrice),
				double_format(pMarketData->SettlementPrice), pMarketData->UpdateTime, pMarketData->TradingDay, pMarketData->ExchangeID);

		if (bIsLast) {
			_semaphore.signal();
		}
	}

	// 查询委托列表
	void OnRspQryOrder(CQdpFtdcOrderField* pOrder, CQdpFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast)
	{
		if (pRspInfo && pRspInfo->ErrorID != 0) {
			printf("OnRspQryOrder. %d - %s\n", pRspInfo->ErrorID, pRspInfo->ErrorMsg);
			return;
		}

		if(pOrder)
			printf("OnRspQryOrder:BrokerID:%s,InvestorID:%s,OrderLocalID:%s,InstrumentID:%s,Direction:%s,OffsetFlag:%c,Volume:%d,LimitPrice:%lf,VolumeTraded:%d,VolumeRemain:%d,OrderSysID:%s,FrontID:%d,SessionID:%d,UserOrderLocalID:%d,OrderStatus:%c,ExchangeID:%s,InsertTime:%s,ClientID:%s,UserCustom:%s\n",
				pOrder->BrokerID, pOrder->InvestorID, pOrder->OrderLocalID, pOrder->InstrumentID, direction_to_string(pOrder->Direction).c_str(), pOrder->OffsetFlag, pOrder->Volume, pOrder->LimitPrice, pOrder->VolumeTraded, pOrder->VolumeRemain, pOrder->OrderSysID, pOrder->FrontID, pOrder->SessionID, pOrder->UserOrderLocalID, pOrder->OrderStatus, pOrder->ExchangeID, pOrder->InsertTime,pOrder->ClientID,pOrder->UserCustom);

		if (bIsLast) {
			_semaphore.signal();
		}
	}

	// 查询成交列表
	void OnRspQryTrade(CQdpFtdcTradeField* pTrade, CQdpFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast)
	{
		if (pRspInfo && pRspInfo->ErrorID != 0) {
			printf("OnRspQryTrade. %d - %s\n", pRspInfo->ErrorID, pRspInfo->ErrorMsg);
			return;
		}

		if(pTrade)
			printf("OnRspQryTrade:BrokerID:%s,InvestorID:%s,InstrumentID:%s,Direction:%s,OffsetFlag:%c,TradeVolume:%d,TradePrice:%lf,OrderSysID:%s,TradeID:%s,UserOrderLocalID:%d,ExchangeID:%s,TradeTime:%s,ClientID:%s\n",
				pTrade->BrokerID, pTrade->InvestorID, pTrade->InstrumentID, direction_to_string(pTrade->Direction).c_str(), pTrade->OffsetFlag, pTrade->TradeVolume, pTrade->TradePrice, pTrade->OrderSysID, pTrade->TradeID, pTrade->UserOrderLocalID, pTrade->ExchangeID, pTrade->TradeTime,pTrade->ClientID);

		if (bIsLast) {
			_semaphore.signal();
		}
	}

	// 查询持仓
	void OnRspQryInvestorPosition(CQdpFtdcRspInvestorPositionField* pInvestorPosition, CQdpFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast)
	{
		if (pRspInfo && pRspInfo->ErrorID != 0) {
			printf("OnRspQryInvestorPosition. %d - %s\n", pRspInfo->ErrorID, pRspInfo->ErrorMsg);
			return;
		}

		if (pInvestorPosition)
			printf("OnRspQryInvestorPosition:InstrumentID:%s,BrokerID:%s,InvestorID:%s,Direction:%s,HedgeFlag:%c,Position:%d,YdPosition:%d,TodayPosition:%d,PositionCost:%lf,ExchangeID:%s\n",
				pInvestorPosition->InstrumentID, pInvestorPosition->BrokerID, pInvestorPosition->InvestorID, direction_to_string(pInvestorPosition->Direction).c_str(), pInvestorPosition->HedgeFlag, pInvestorPosition->Position, pInvestorPosition->YdPosition, pInvestorPosition->TodayPosition, pInvestorPosition->PositionCost, pInvestorPosition->ExchangeID);

		if (bIsLast) {
			_semaphore.signal();
		}
	}

	///请求查询资金账户响应
	void OnRspQryInvestorAccount(CQdpFtdcRspInvestorAccountField* pRspInvestorAccount, CQdpFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast)
	{
		if (pRspInvestorAccount)
			printf("OnRspQryInvestorAccount:InvestorID:%s,AccountID:%s,Balance:%lf,Available:%lf,Margin:%lf,Fee:%lf,FrozenMargin:%lf,FrozenFee:%lf,PreBalance:%lf\n",
				pRspInvestorAccount->InvestorID, pRspInvestorAccount->AccountID, pRspInvestorAccount->Balance,pRspInvestorAccount->Available, pRspInvestorAccount->Margin, pRspInvestorAccount->Fee, pRspInvestorAccount->FrozenMargin, pRspInvestorAccount->FrozenFee, pRspInvestorAccount->PreBalance);

		if (bIsLast)
			printf("Query completed.\n");
	}

	// 委托回报
	void OnRtnOrder(CQdpFtdcOrderField* pOrder)
	{
		printf("OnRtnOrder:BrokerID:%s,InvestorID:%s,OrderLocalID:%s,InstrumentID:%s,Direction:%s,OffsetFlag:%c,Volume:%d,LimitPrice:%lf,VolumeTraded:%d,VolumeRemain:%d,OrderSysID:%s,FrontID:%d,SessionID:%d,UserOrderLocalID:%d,OrderStatus:%c,ExchangeID:%s,InsertTime:%s,ClientID:%s,UserCustom:%s\n",
			pOrder->BrokerID, pOrder->InvestorID, pOrder->OrderLocalID, pOrder->InstrumentID, direction_to_string(pOrder->Direction).c_str(), pOrder->OffsetFlag, pOrder->Volume, pOrder->LimitPrice, pOrder->VolumeTraded, pOrder->VolumeRemain, pOrder->OrderSysID, pOrder->FrontID, pOrder->SessionID, pOrder->UserOrderLocalID, pOrder->OrderStatus, pOrder->ExchangeID, pOrder->InsertTime,pOrder->ClientID,pOrder->UserCustom);
	}

	// 成交回报
	void OnRtnTrade(CQdpFtdcTradeField* pTrade)
	{
		printf("OnRtnTrade:BrokerID:%s,InvestorID:%s,InstrumentID:%s,Direction:%s,OffsetFlag:%c,TradeVolume:%d,TradePrice:%lf,OrderSysID:%s,TradeID:%s,UserOrderLocalID:%d,ExchangeID:%s,TradeTime:%s,ClientID:%s\n",
			pTrade->BrokerID, pTrade->InvestorID, pTrade->InstrumentID, direction_to_string(pTrade->Direction).c_str(), pTrade->OffsetFlag, pTrade->TradeVolume, pTrade->TradePrice, pTrade->OrderSysID, pTrade->TradeID, pTrade->UserOrderLocalID, pTrade->ExchangeID, pTrade->TradeTime, pTrade->ClientID);
	}

	// 报单错误
	void OnErrRtnOrderInsert(CQdpFtdcInputOrderField* pInputOrder, CQdpFtdcRspInfoField* pRspInfo)
	{
		if (pRspInfo && pRspInfo->ErrorID != 0)
			printf("OnErrRtnOrderInsert. %d - %s\n", pRspInfo->ErrorID, pRspInfo->ErrorMsg);

		if(pInputOrder)
			printf("OnErrRtnOrderInsert:InvestorID:%s,InstrumentID:%s,ExchangeID:%s,Direction:%s,OffsetFlag:%c,Volume:%d,LimitPrice:%lf,UserOrderLocalID:%d,OrderSysID:%s,UserCustom:%s\n", pInputOrder->InvestorID, pInputOrder->InstrumentID, pInputOrder->ExchangeID, direction_to_string(pInputOrder->Direction).c_str(), pInputOrder->OffsetFlag, pInputOrder->Volume, pInputOrder->LimitPrice, pInputOrder->UserOrderLocalID, pInputOrder->OrderSysID, pInputOrder->UserCustom);
	}

	// 撤单错误回报
	void OnErrRtnOrderAction(CQdpFtdcOrderActionField* pOrderAction, CQdpFtdcRspInfoField* pRspInfo)
	{
		if (pRspInfo && pRspInfo->ErrorID != 0)
			printf("OnErrRtnOrderAction. %d - %s\n", pRspInfo->ErrorID, pRspInfo->ErrorMsg);

		if (pOrderAction)
			printf("OnErrRtnOrderAction:InvestorID:%s,InstrumentID:%s,ExchangeID:%s,OrderSysID:%s,FrontID:%d,SessionID:%d,UserOrderLocalID:%d,UserOrderActionLocalID=%d\n",pOrderAction->InvestorID, pOrderAction->InstrumentID, pOrderAction->ExchangeID, pOrderAction->OrderSysID, pOrderAction->FrontID, pOrderAction->SessionID, pOrderAction->UserOrderLocalID, pOrderAction->UserOrderActionLocalID);
	}

	void OnRtnInstrumentStatus(CQdpFtdcInstrumentStatusField* pInstrumentStatus)
	{
		printf("OnRtnInstrumentStatus:ExchangeID:%s,InstrumentID:%s,InstrumentStatus:%c\n", pInstrumentStatus->ExchangeID, pInstrumentStatus->InstrumentID, pInstrumentStatus->InstrumentStatus);
	}

public:
	std::string m_host;
	std::string m_broker;
	std::string m_user;
	std::string m_password;
	std::string m_appid;
	std::string m_authcode;
	unsigned int m_nOrderRef;

	CQdpFtdcTraderApi* m_pUserApi;
};


void display_usage()
{
	printf("usage:ctpprint host broker user password appid authcode\n");
	printf("example:ctpprint tcp://106.14.65.17:30005 ltkj 20210902 123456 quantdo_api_229 b827ef8a450041c85b1fa6ac1973e30a\n");
}


int main(int argc, char* argv[])
{
	if (argc != 7) {
		display_usage();
		return -1;
	}

	std::string host(argv[1]), broker(argv[2]), user(argv[3]), password(argv[4]), appid(argv[5]), authcode(argv[6]);

	CApplication Spi(host, broker, user, password, appid, authcode);

	// 启动
	if (Spi.Run() < 0)
		return -1;

	// 等待登录完成
	_semaphore.wait();

	// 查询投资者
	std::this_thread::sleep_for(std::chrono::milliseconds(1000));
	printf("查询投资者 ...\n");
	CQdpFtdcQryUserInvestorField QryUserInvestor = { 0 };
	strncpy(QryUserInvestor.BrokerID, broker.c_str(), sizeof(QryUserInvestor.BrokerID) - 1);
	Spi.m_pUserApi->ReqQryUserInvestor(&QryUserInvestor, 0);
	_semaphore.wait();

	// 查询交易所
	printf("查询交易所 ...\n");
	CQdpFtdcQryExchangeField QryExchange = { 0 };
	Spi.m_pUserApi->ReqQryExchange(&QryExchange, 0);
	_semaphore.wait();

	// 查询合约
	std::this_thread::sleep_for(std::chrono::milliseconds(1000));
	printf("查询合约 ...\n");
	CQdpFtdcQryInstrumentField QryInstrument = { 0 };
	Spi.m_pUserApi->ReqQryInstrument(&QryInstrument, 0);
	_semaphore.wait();

	// 查询行情
	std::this_thread::sleep_for(std::chrono::milliseconds(1000));
	printf("查询行情 ...\n");
	CQdpFtdcQryMarketDataField QryMarketData = { 0 };
	Spi.m_pUserApi->ReqQryMarketData(&QryMarketData, 0);
	_semaphore.wait();

	// 查询投资者手续费率
	std::this_thread::sleep_for(std::chrono::milliseconds(1000));
	printf("查询投资者手续费率 ...\n");
	CQdpFtdcQryInvestorFeeField QryInvestorFee = { 0 };
	strncpy(QryInvestorFee.BrokerID, broker.c_str(), sizeof(QryInvestorFee.BrokerID) - 1);
	strncpy(QryInvestorFee.InvestorID, user.c_str(), sizeof(QryInvestorFee.InvestorID) - 1);
	Spi.m_pUserApi->ReqQryInvestorFee(&QryInvestorFee, 0);
	_semaphore.wait();

	// 查询投资者保证金率
	std::this_thread::sleep_for(std::chrono::milliseconds(1000));
	printf("查询投资者保证金率 ...\n");
	CQdpFtdcQryInvestorMarginField QryInvestorMargin = { 0 };
	strncpy(QryInvestorMargin.BrokerID, broker.c_str(), sizeof(QryInvestorMargin.BrokerID) - 1);
	strncpy(QryInvestorMargin.InvestorID, user.c_str(), sizeof(QryInvestorMargin.InvestorID) - 1);
	Spi.m_pUserApi->ReqQryInvestorMargin(&QryInvestorMargin, 0);
	_semaphore.wait();

	// 查询订单
	std::this_thread::sleep_for(std::chrono::milliseconds(1000));
	printf("查询订单 ...\n");
	CQdpFtdcQryOrderField QryOrder = { 0 };
	strncpy(QryOrder.BrokerID, broker.c_str(), sizeof(QryOrder.BrokerID) - 1);
	strncpy(QryOrder.InvestorID, user.c_str(), sizeof(QryOrder.InvestorID) - 1);
	Spi.m_pUserApi->ReqQryOrder(&QryOrder, 0);
	_semaphore.wait();

	// 查询成交
	std::this_thread::sleep_for(std::chrono::milliseconds(1000));
	printf("查询成交 ...\n");
	CQdpFtdcQryTradeField QryTrade = { 0 };
	strncpy(QryTrade.BrokerID, broker.c_str(), sizeof(QryTrade.BrokerID) - 1);
	strncpy(QryTrade.InvestorID, user.c_str(), sizeof(QryTrade.InvestorID) - 1);
	Spi.m_pUserApi->ReqQryTrade(&QryTrade, 0);
	_semaphore.wait();

	// 查询持仓
	std::this_thread::sleep_for(std::chrono::milliseconds(1000));
	printf("查询持仓 ...\n");
	CQdpFtdcQryInvestorPositionField QryInvestorPosition = { 0 };
	strncpy(QryInvestorPosition.BrokerID, broker.c_str(), sizeof(QryInvestorPosition.BrokerID) - 1);
	strncpy(QryInvestorPosition.InvestorID, user.c_str(), sizeof(QryInvestorPosition.InvestorID) - 1);
	Spi.m_pUserApi->ReqQryInvestorPosition(&QryInvestorPosition, 0);
	_semaphore.wait();

	// 查询资金
	std::this_thread::sleep_for(std::chrono::milliseconds(1000));
	printf("查询资金 ...\n");
	CQdpFtdcQryInvestorAccountField QryInvestorAccount = { 0 };
	strncpy(QryInvestorAccount.BrokerID, broker.c_str(), sizeof(QryInvestorAccount.BrokerID) - 1);
	strncpy(QryInvestorAccount.InvestorID, user.c_str(), sizeof(QryInvestorAccount.InvestorID) - 1);
	Spi.m_pUserApi->ReqQryInvestorAccount(&QryInvestorAccount, 0);

	// 如需下单、撤单，放开下面的代码即可

	std::this_thread::sleep_for(std::chrono::milliseconds(1000));
	printf("按任意键下单 ...\n");
	getchar();
	Spi.OrderInsert("DCE", "c2809", QDP_FTDC_D_Buy, QDP_FTDC_OF_Open, 2400.0, 1);

	std::this_thread::sleep_for(std::chrono::milliseconds(1000));
	printf("按任意键下单 ...\n");
	getchar();
	Spi.OrderInsert("DCE", "i2207", QDP_FTDC_D_Sell, QDP_FTDC_OF_Open, 580.0, 1);

	std::this_thread::sleep_for(std::chrono::milliseconds(1000));
	printf("按任意键撤单 ...\n");
	getchar();
	Spi.OrderCancel("DCE", "i2207", "100027738");

	std::this_thread::sleep_for(std::chrono::milliseconds(1000));
	printf("按任意键退出 ...\n");
	getchar();

	return 0;
}
