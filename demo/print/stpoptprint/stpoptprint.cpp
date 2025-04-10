#include <stdio.h>
#include <string>
#include "TORATstpSPTraderApi.h"

using namespace TORASPAPI;

class CApplication : public CTORATstpSPTraderSpi
{
public:
	CApplication(std::string host, std::string user, std::string password) :
		m_host(host),
		m_user(user),
		m_password(password)
	{
		m_pUserApi = CTORATstpSPTraderApi::CreateTstpSPTraderApi();
		m_pUserApi->RegisterSpi(this);
	}

	~CApplication()
	{
	}

	const std::string direction_to_string(TTORATstpSPDirectionType Direction)
	{
		std::string str = Direction == TORA_TSTP_SP_D_Buy ? "买" : "卖";
		return std::move(str);
	}

	int Run()
	{
		m_pUserApi->RegisterFront((char*)m_host.c_str());
		m_pUserApi->SubscribePrivateTopic(TORA_TERT_QUICK);
		m_pUserApi->SubscribePublicTopic(TORA_TERT_QUICK);
		m_pUserApi->Init();

		return 0;
	}

	void OnFrontConnected()
	{
		printf("Connected.\n");
		CTORATstpSPReqUserLoginField LoginReq = { 0 };

		LoginReq.LogInAccountType = TORA_TSTP_SP_LACT_UserID;
		strncpy(LoginReq.LogInAccount, m_user.c_str(), sizeof(LoginReq.LogInAccount) - 1);
		strncpy(LoginReq.Password, m_password.c_str(), sizeof(LoginReq.Password) - 1);
		strncpy(LoginReq.UserProductInfo, "openctp", sizeof(LoginReq.UserProductInfo) - 1);
		m_pUserApi->ReqUserLogin(&LoginReq, 0);
	}

	void OnFrontDisconnected(int nReason)
	{
		printf("Disconnected.\n");
	}

	///用户登录应答
	void OnRspUserLogin(CTORATstpSPRspUserLoginField* pRspUserLoginField, CTORATstpSPRspInfoField* pRspInfo, int nRequestID)
	{
		if (pRspInfo && pRspInfo->ErrorID!=0) {
			printf("Login failed. %d - %s\n",pRspInfo->ErrorID,pRspInfo->ErrorMsg);
			return;
		}
		printf("Login succeeded.TradingDay:%s,FrontID=%d,SessionID=%d\n",pRspUserLoginField->TradingDay,pRspUserLoginField->FrontID,pRspUserLoginField->SessionID);

		// 查询股东账号
		printf("查询股东账号 ...\n");
		CTORATstpSPQryShareholderAccountField Req = { 0 };
		m_pUserApi->ReqQryShareholderAccount(&Req, 0);
	}

	//查询股东账户
	void OnRspQryShareholderAccount(CTORATstpSPShareholderAccountField* pShareholderAccount, CTORATstpSPRspInfoField* pRspInfo, int nRequestID, bool bIsLast)
	{
		if (pShareholderAccount) {
			switch (pShareholderAccount->ExchangeID) {
			case TORA_TSTP_SP_EXD_SSE:
				printf("SSE.ShareholderID=%s\n", pShareholderAccount->ShareholderID);
				break;
			case TORA_TSTP_SP_EXD_SZSE:
				printf("SZSE.ShareholderID=%s\n", pShareholderAccount->ShareholderID);
				break;
			case TORA_TSTP_SP_EXD_HK:
				printf("HK.ShareholderID=%s\n", pShareholderAccount->ShareholderID);
				break;
			default:
				break;
			}
		}

		if (bIsLast) {
			// 查询合约
			printf("查询合约 ...\n");
			CTORATstpSPQrySecurityField Req = { 0 };
			m_pUserApi->ReqQrySecurity(&Req, nRequestID);
		}
	}

	///合约查询应答
	void OnRspQrySecurity(CTORATstpSPSecurityField* pSecurity, CTORATstpSPRspInfoField* pRspInfo, int nRequestID, bool bIsLast)
	{
		if (pSecurity)
			printf("SecurityID:%s,SecurityName:%s,PriceTick:%lf,PreClosePrice:%lf,MarketID:%c\n", pSecurity->SecurityID, pSecurity->SecurityName, pSecurity->PriceTick, pSecurity->PreClosePrice, pSecurity->MarketID);

		if (bIsLast) {
			// 查询订单
			printf("查询订单 ...\n");
			CTORATstpSPQryOrderField Req = { 0 };
			m_pUserApi->ReqQryOrder(&Req, 0);
		}
	}

	//订单查询
	void OnRspQryOrder(CTORATstpSPOrderField* pOrder, CTORATstpSPRspInfoField* pRspInfo, int nRequestID, bool bIsLast)
	{
		if (pOrder)
			printf("OrderLocalID:%s,SecurityID:%s,Direction:%s,VolumeTotalOriginal:%d,Price:%lf,VolumeTraded:%d,VolumeCanceled:%d,OrderSysID:%s,FrontID:%d,SessionID:%d,OrderRef:%d,OrderStatus:%c,StatusMsg:%s,InsertTime:%s\n",
				pOrder->OrderLocalID, pOrder->SecurityID, direction_to_string(pOrder->Direction).c_str(), pOrder->VolumeTotalOriginal, pOrder->Price, pOrder->VolumeTraded, pOrder->VolumeCanceled, pOrder->OrderSysID, pOrder->FrontID, pOrder->SessionID, pOrder->OrderRef, pOrder->OrderStatus, pOrder->StatusMsg, pOrder->InsertTime);

		if (bIsLast) {
			// 查询成交
			printf("查询成交 ...\n");
			CTORATstpSPQryTradeField Req = { 0 };
			m_pUserApi->ReqQryTrade(&Req, 0);
		}
	}

	//成交查询
	void OnRspQryTrade(CTORATstpSPTradeField* pTrade, CTORATstpSPRspInfoField* pRspInfo, int nRequestID, bool bIsLast)
	{
		if (pTrade)
			printf("OrderLocalID:%s,SecurityID:%s,Direction:%s,Volume:%d,Price:%lf,OrderSysID:%s,OrderRef:%d,TradeTime:%s\n",
				pTrade->OrderLocalID, pTrade->SecurityID, direction_to_string(pTrade->Direction).c_str(), pTrade->Volume, pTrade->Price, pTrade->OrderSysID, pTrade->OrderRef, pTrade->TradeTime);

		if (bIsLast) {
			// 查询持仓
			printf("查询持仓 ...\n");
			CTORATstpSPQryPositionField Req = { 0 };
			m_pUserApi->ReqQryPosition(&Req, 0);
		}
	}

	//持仓查询
	void OnRspQryPosition(CTORATstpSPPositionField* pPosition, CTORATstpSPRspInfoField* pRspInfo, int nRequestID, bool bIsLast)
	{
		if (pPosition)
			printf("SecurityID:%s,TodayPos:%d,TodayPosFrozen:%d,HistoryPos:%d,HistoryPosFrozen:%d,OpenPosCost:%lf,TotalPosCost:%lf,PrePosition:%d\n",
				pPosition->SecurityID, pPosition->TodayPos, pPosition->TodayPosFrozen, pPosition->HistoryPos, pPosition->HistoryPosFrozen, pPosition->OpenPosCost, pPosition->TotalPosCost, pPosition->PrePosition);
		if (bIsLast) {
			// 查询资金
			printf("查询资金 ...\n");
			CTORATstpSPQryTradingAccountField Req = { 0 };
			m_pUserApi->ReqQryTradingAccount(&Req, 0);
		}
	}

	//资金查询
	void OnRspQryTradingAccount(CTORATstpSPTradingAccountField* pTradingAccount, CTORATstpSPRspInfoField* pRspInfo, int nRequestID, bool bIsLast)
	{
		if (pTradingAccount)
			printf("AccountID:%s,UsefulMoney:%lf,FrozenCash:%lf,FrozenCommission:%lf\n",
				pTradingAccount->AccountID, pTradingAccount->UsefulMoney, pTradingAccount->FrozenCash, pTradingAccount->FrozenCommission);

		if (bIsLast)
			printf("Query completed.\n");
	}

	//订单回报
	void OnRtnOrder(CTORATstpSPOrderField* pOrder)
	{
		printf("OrderLocalID:%s,SecurityID:%s,Direction:%s,VolumeTotalOriginal:%d,Price:%lf,VolumeTraded:%d,VolumeCanceled:%d,OrderSysID:%s,FrontID:%d,SessionID:%d,OrderRef:%d,OrderStatus:%c,StatusMsg:%s,InsertTime:%s\n",
			pOrder->OrderLocalID, pOrder->SecurityID, direction_to_string(pOrder->Direction).c_str(), pOrder->VolumeTotalOriginal, pOrder->Price,pOrder->VolumeTraded, pOrder->VolumeCanceled, pOrder->OrderSysID, pOrder->FrontID, pOrder->SessionID, pOrder->OrderRef, pOrder->OrderStatus, pOrder->StatusMsg, pOrder->InsertTime);
	}

	//成交回报
	void OnRtnTrade(CTORATstpSPTradeField* pTrade)
	{
		printf("OrderLocalID:%s,SecurityID:%s,Direction:%s,Volume:%d,Price:%lf,OrderSysID:%s,OrderRef:%d,TradeTime:%s\n",
			pTrade->OrderLocalID, pTrade->SecurityID, direction_to_string(pTrade->Direction).c_str(), pTrade->Volume, pTrade->Price, pTrade->OrderSysID, pTrade->OrderRef, pTrade->TradeTime);
	}

private:
	std::string m_host;
	std::string m_user;
	std::string m_password;

	CTORATstpSPTraderApi* m_pUserApi;
};


void display_usage()
{
	printf("usage:stpprint host user password\n");
	printf("example:stpprint tcp://210.14.72.16:15500 000001 888888\n");
}


int main(int argc, char* argv[])
{
	if (argc != 4) {
		display_usage();
		return -1;
	}

	CApplication Spi(argv[1], argv[2], argv[3]);

	// 启动
	if (Spi.Run() < 0)
		return -1;


	getchar();

	return 0;
}
