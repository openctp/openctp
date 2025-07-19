#include <stdio.h>
#include <string>
#include "TORATstpTraderApi.h"

using namespace TORASTOCKAPI;

class CApplication : public CTORATstpTraderSpi
{
public:
	CApplication(std::string host, std::string user, std::string password) :
		m_host(host),
		m_user(user),
		m_password(password)
	{
		m_pUserApi = CTORATstpTraderApi::CreateTstpTraderApi();
		m_pUserApi->RegisterSpi(this);
	}

	~CApplication()
	{
	}

	const std::string direction_to_string(TTORATstpDirectionType Direction)
	{
		std::string str = Direction == TORA_TSTP_D_Buy ? "买" : "卖";
		return std::move(str);
	}

	const std::string exchange_to_string(TTORATstpExchangeIDType	ExchangeID)
	{
		std::string exchange;

		switch (ExchangeID)
		{
		case TORA_TSTP_EXD_SSE: ///上海交易所
			exchange = "SSE";
			break;
		case TORA_TSTP_EXD_SZSE: ///深圳交易所
			exchange = "SZSE";
			break;
		case TORA_TSTP_EXD_HK: ///香港交易所
			exchange = "HKSE";
			break;
		case TORA_TSTP_EXD_BSE: ///北京证券交易所
			exchange = "BSE";
			break;
		default:
			exchange = "";
			break;
		}

		return exchange;
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
		CTORATstpReqUserLoginField LoginReq = { 0 };

		LoginReq.LogInAccountType = TORA_TSTP_LACT_AccountID;
		strncpy(LoginReq.LogInAccount, m_user.c_str(), sizeof(LoginReq.LogInAccount) - 1);
		strncpy(LoginReq.Password, m_password.c_str(), sizeof(LoginReq.Password) - 1);
		m_pUserApi->ReqUserLogin(&LoginReq, 0);
	}

	void OnFrontDisconnected(int nReason)
	{
		printf("Disconnected.\n");
	}


	///用户登录应答
	void OnRspUserLogin(CTORATstpRspUserLoginField* pRspUserLoginField, CTORATstpRspInfoField* pRspInfo, int nRequestID)
	{
		if (pRspInfo && pRspInfo->ErrorID!=0) {
			printf("Login failed. %d - %s\n",pRspInfo->ErrorID,pRspInfo->ErrorMsg);
			return;
		}
		printf("Login succeeded.TradingDay:%s,FrontID=%d,SessionID=%d\n",pRspUserLoginField->TradingDay,pRspUserLoginField->FrontID,pRspUserLoginField->SessionID);

		// 查询股东账号
		printf("查询股东账号 ...\n");
		CTORATstpQryShareholderAccountField Req = { 0 };
		m_pUserApi->ReqQryShareholderAccount(&Req, 0);
	}

	//查询股东账户
	void OnRspQryShareholderAccount(CTORATstpShareholderAccountField* pShareholderAccount, CTORATstpRspInfoField* pRspInfo, int nRequestID, bool bIsLast)
	{
		if (pShareholderAccount) {
			switch (pShareholderAccount->ExchangeID) {
			case TORA_TSTP_EXD_SSE:
				printf("SSE.ShareholderID=%s\n", pShareholderAccount->ShareholderID);
				break;
			case TORA_TSTP_EXD_SZSE:
				printf("SZSE.ShareholderID=%s\n", pShareholderAccount->ShareholderID);
				break;
			case TORA_TSTP_EXD_BSE:
				printf("BSE.ShareholderID=%s\n", pShareholderAccount->ShareholderID);
				break;
			case TORA_TSTP_EXD_HK:
				printf("HK.ShareholderID=%s\n", pShareholderAccount->ShareholderID);
				break;
			default:
				break;
			}
		}

		if (bIsLast) {
			// 查询合约
			printf("查询合约 ...\n");
			CTORATstpQrySecurityField Req = { 0 };
			m_pUserApi->ReqQrySecurity(&Req, nRequestID);
		}
	}

	///合约查询应答
	void OnRspQrySecurity(CTORATstpSecurityField* pSecurity, CTORATstpRspInfoField* pRspInfo, int nRequestID, bool bIsLast)
	{
		if (pSecurity)
			printf("OnRspQrySecurity:SecurityID:%s,SecurityName:%s,ExchangeID:%s,PriceTick:%lf,PreClosePrice:%lf,MarketID:%c\n", pSecurity->SecurityID, pSecurity->SecurityName, exchange_to_string(pSecurity->ExchangeID).c_str(), pSecurity->PriceTick, pSecurity->PreClosePrice, pSecurity->MarketID);

		if (bIsLast) {
			// 查询佣金费率
			printf("查询佣金费率 ...\n");
			CTORATstpQryInvestorTradingFeeField Req = { 0 };
			m_pUserApi->ReqQryInvestorTradingFee(&Req, 0);
		}
	}

	// 查询手续费应答
	void OnRspQryInvestorTradingFee(CTORATstpInvestorTradingFeeField* pInvestorTradingFeeField, CTORATstpRspInfoField* pRspInfoField, int nRequestID, bool bIsLast)
	{
		if (pInvestorTradingFeeField)
			printf("OnRspQryInvestorTradingFee:SecurityID:%s,ExchangeID:%s,SecurityType='%c',ProductID='%c',FeeByVolume:%lf,RatioByAmt:%lf,FeeMin:%lf,BizClass:'%c',InvestorID:%s\n", pInvestorTradingFeeField->SecurityID, exchange_to_string(pInvestorTradingFeeField->ExchangeID).c_str(), pInvestorTradingFeeField->SecurityType, pInvestorTradingFeeField->ProductID, pInvestorTradingFeeField->FeeByVolume, pInvestorTradingFeeField->RatioByAmt, pInvestorTradingFeeField->FeeMin, pInvestorTradingFeeField->BizClass, pInvestorTradingFeeField->InvestorID);

		
		if (bIsLast) {
			// 查询订单
			printf("查询订单 ...\n");
			CTORATstpQryOrderField Req = { 0 };
			m_pUserApi->ReqQryOrder(&Req, 0);
		}
	}

	//订单查询应答
	void OnRspQryOrder(CTORATstpOrderField* pOrder, CTORATstpRspInfoField* pRspInfo, int nRequestID, bool bIsLast)
	{
		if (pOrder)
			printf("OnRspQryOrder:OrderLocalID:%s,SecurityID:%s,Direction:%s,VolumeTotalOriginal:%d,LimitPrice:%lf,VolumeTraded:%d,VolumeCanceled:%d,OrderSysID:%s,FrontID:%d,SessionID:%d,OrderRef:%d,OrderStatus:%c,StatusMsg:%s,InsertTime:%s\n",
				pOrder->OrderLocalID, pOrder->SecurityID, direction_to_string(pOrder->Direction).c_str(), pOrder->VolumeTotalOriginal, pOrder->LimitPrice, pOrder->VolumeTraded, pOrder->VolumeCanceled, pOrder->OrderSysID, pOrder->FrontID, pOrder->SessionID, pOrder->OrderRef, pOrder->OrderStatus, pOrder->StatusMsg, pOrder->InsertTime);

		if (bIsLast) {
			// 查询成交
			printf("查询成交 ...\n");
			CTORATstpQryTradeField Req = { 0 };
			m_pUserApi->ReqQryTrade(&Req, 0);
		}
	}

	//成交查询
	void OnRspQryTrade(CTORATstpTradeField* pTrade, CTORATstpRspInfoField* pRspInfo, int nRequestID, bool bIsLast)
	{
		if (pTrade)
			printf("OrderLocalID:%s,SecurityID:%s,Direction:%s,Volume:%d,Price:%lf,OrderSysID:%s,OrderRef:%d,TradeTime:%s\n",
				pTrade->OrderLocalID, pTrade->SecurityID, direction_to_string(pTrade->Direction).c_str(), pTrade->Volume, pTrade->Price, pTrade->OrderSysID, pTrade->OrderRef, pTrade->TradeTime);

		if (bIsLast) {
			// 查询持仓
			printf("查询持仓 ...\n");
			CTORATstpQryPositionField Req = { 0 };
			m_pUserApi->ReqQryPosition(&Req, 0);
		}
	}

	//持仓查询应答
	void OnRspQryPosition(CTORATstpPositionField* pPosition, CTORATstpRspInfoField* pRspInfo, int nRequestID, bool bIsLast)
	{
		if (pPosition)
			printf("SecurityID:%s,CurrentPosition:%d,OpenPosCost:%lf,TotalPosCost:%lf,PrePosition:%d,HistoryPosFrozen:%d\n",
				pPosition->SecurityID, pPosition->CurrentPosition, pPosition->OpenPosCost, pPosition->TotalPosCost, pPosition->PrePosition, pPosition->HistoryPosFrozen);
		if (bIsLast) {
			// 查询资金
			printf("查询资金 ...\n");
			CTORATstpQryTradingAccountField Req = { 0 };
			m_pUserApi->ReqQryTradingAccount(&Req, 0);
		}
	}

	//资金查询应答
	void OnRspQryTradingAccount(CTORATstpTradingAccountField* pTradingAccount, CTORATstpRspInfoField* pRspInfo, int nRequestID, bool bIsLast)
	{
		if (pTradingAccount)
			printf("AccountID:%s,UsefulMoney:%lf,FrozenCash:%lf,FrozenCommission:%lf\n",
				pTradingAccount->AccountID, pTradingAccount->UsefulMoney, pTradingAccount->FrozenCash, pTradingAccount->FrozenCommission);

		if (bIsLast)
			printf("Query completed.\n");
	}

	//订单回报
	void OnRtnOrder(CTORATstpOrderField* pOrder)
	{
		printf("OrderLocalID:%s,SecurityID:%s,Direction:%s,VolumeTotalOriginal:%d,LimitPrice:%lf,VolumeTraded:%d,VolumeCanceled:%d,OrderSysID:%s,FrontID:%d,SessionID:%d,OrderRef:%d,OrderStatus:%c,StatusMsg:%s,InsertTime:%s\n",
			pOrder->OrderLocalID, pOrder->SecurityID, direction_to_string(pOrder->Direction).c_str(), pOrder->VolumeTotalOriginal, pOrder->LimitPrice,pOrder->VolumeTraded, pOrder->VolumeCanceled, pOrder->OrderSysID, pOrder->FrontID, pOrder->SessionID, pOrder->OrderRef, pOrder->OrderStatus, pOrder->StatusMsg, pOrder->InsertTime);
	}

	//成交回报
	void OnRtnTrade(CTORATstpTradeField* pTrade)
	{
		printf("OrderLocalID:%s,SecurityID:%s,Direction:%s,Volume:%d,Price:%lf,OrderSysID:%s,OrderRef:%d,TradeTime:%s\n",
			pTrade->OrderLocalID, pTrade->SecurityID, direction_to_string(pTrade->Direction).c_str(), pTrade->Volume, pTrade->Price, pTrade->OrderSysID, pTrade->OrderRef, pTrade->TradeTime);
	}

private:
	std::string m_host;
	std::string m_user;
	std::string m_password;

	CTORATstpTraderApi* m_pUserApi;
};


void display_usage()
{
	printf("usage:stpprint host user password\n");
	printf("example:stpprint tcp://210.14.72.16:9500 000001 888888\n");
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
