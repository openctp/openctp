#include <stdio.h>
#include <string>
#include <thread>
#include <mutex>
#include <functional>
#include <condition_variable>
#include <iostream>
#include "TapTradeAPI.h"
#include "TapAPIError.h"

#define TAP_AUTHCODE	("67EA896065459BECDFDB924B29CB7DF1946CED\
32E26C1EAC946CED32E26C1EAC946CED32E26C1EAC946CED32E26C1EAC5211AF9FEE\
541DDE41BCBAB68D525B0D111A0884D847D57163FF7F329FA574E7946CED32E26C1E\
AC946CED32E26C1EAC733827B0CE853869ABD9B8F170E14F8847D3EA0BF4E191F5D9\
7B3DFE4CCB1F01842DD2B3EA2F4B20CAD19B8347719B7E20EA1FA7A3D1BFEFF22290\
F4B5C43E6C520ED5A40EC1D50ACDF342F46A92CCF87AEE6D73542C42EC17818349C7\
DEDAB0E4DB16977714F873D505029E27B3D57EB92D5BEDA0A710197EB67F94BB1892\
B30F58A3F211D9C3B3839BE2D73FD08DD776B9188654853DDA57675EBB7D6FBBFC")

// 条件变量实现的信号量
class semaphore
{
public:
	semaphore(int value = 1) :count(value) {}

	void wait()
	{
		std::unique_lock<std::mutex> lck(lock);
		if (--count < 0)
			cv.wait(lck);
	}

	void signal()
	{
		std::unique_lock<std::mutex> lck(lock);
		if (++count <= 0)
			cv.notify_one();
	}

private:
	int count;
	std::mutex lock;
	std::condition_variable cv;
};

semaphore g_semaphore(0);

class CApplication : public ITapTradeAPINotify
{
public:
	CApplication(std::string host, std::string user, std::string password, std::string appid, std::string authcode) :
		m_host(host),
		m_user(user),
		m_password(password),
		m_appid(appid),
		m_authcode(authcode)
	{
		m_SessionID = 0;
		TAPIINT32 iResult = TAPIERROR_SUCCEED;
		TapAPIApplicationInfo stAppInfo;
		strcpy(stAppInfo.AuthCode, TAP_AUTHCODE);
		strcpy(stAppInfo.KeyOperationLogPath, "");
		m_pTdApi = CreateTapTradeAPI(&stAppInfo,iResult);
		m_pTdApi->SetAPINotify(this);
	}

	~CApplication()
	{
	}

	const std::string direction_to_string(TAPISideType Direction)
	{
		std::string str = Direction == TAPI_SIDE_BUY ? "买" : "卖";
		return std::move(str);
	}

	double double_format(double value)
	{
		return value==DBL_MAX?0.0:value;
	}

	int Run()
	{
		// host format: 123.161.206.213:6160
		const char* hoststr = m_host.c_str();
		char IP[16] = { 0 };
		const char* p=strchr(hoststr, ':');
		strncpy(IP, m_host.c_str(), p - hoststr);
		int port = atol(p + 1);
		m_pTdApi->SetHostAddress(IP,port);

		// 登录
		TapAPITradeLoginAuth Req;
		memset(&Req, 0, sizeof(Req));
		strcpy(Req.UserNo, m_user.c_str());
		strcpy(Req.Password, m_password.c_str());
		strcpy(Req.AuthCode, m_authcode.c_str());
		strcpy(Req.AppID, m_appid.c_str());
		Req.ISModifyPassword = APIYNFLAG_NO;
		Req.ISDDA = APIYNFLAG_NO;
		int r = m_pTdApi->Login(&Req);
		if (TAPIERROR_SUCCEED != r) {
			printf("Login error.[r=%d]\n", r);
			return -1;
		}

		return 0;
	}

	// 下单
	int OrderInsert(const char* ExchangeID, TAPICommodityType CommodityType, const char* CommodityNo, const char* InstrumentID, TAPISideType Direction, TAPIPositionEffectType PositionEffect, double Price, unsigned int Qty)
	{
		TapAPINewOrder Req = { 0 };

		strncpy_s(Req.AccountNo, m_user.c_str(), sizeof(Req.AccountNo) - 1);
		strncpy_s(Req.ExchangeNo, ExchangeID, sizeof(Req.ExchangeNo) - 1);
		Req.CommodityType = CommodityType;
		strncpy_s(Req.CommodityNo, CommodityNo, sizeof(Req.CommodityNo) - 1);
		strncpy_s(Req.ContractNo, InstrumentID, sizeof(Req.ContractNo) - 1);
		Req.OrderSide = Direction;
		Req.PositionEffect = PositionEffect;
		Req.HedgeFlag = TAPI_HEDGEFLAG_T;
		Req.OrderQty = Qty;
		Req.OrderPrice = Price;
		Req.OrderType = TAPI_ORDER_TYPE_LIMIT;
		Req.TimeInForce = TAPI_ORDER_TIMEINFORCE_GFD;
		Req.OrderMinQty = 1;

		Req.RefInt = 999;
		strncpy_s(Req.RefString, "xxx", sizeof(Req.RefString) - 1);

		Req.TriggerCondition = TAPI_TRIGGER_CONDITION_NONE;
		Req.CallOrPutFlag = TAPI_CALLPUT_FLAG_NONE;
		Req.CallOrPutFlag2 = TAPI_CALLPUT_FLAG_NONE;
		Req.PositionEffect2 = TAPI_PositionEffect_NONE;
		Req.HedgeFlag2 = TAPI_HEDGEFLAG_NONE;
		Req.IsRiskOrder = APIYNFLAG_NO;
		Req.OrderSource = TAPI_ORDER_SOURCE_ESUNNY_API;
		Req.AddOneIsValid = APIYNFLAG_NO;
		Req.TacticsType = TAPI_TACTICS_TYPE_NONE;
		Req.TriggerCondition = TAPI_TRIGGER_CONDITION_NONE;
		Req.TriggerPriceType = TAPI_TRIGGER_PRICE_NONE;
		Req.MarketLevel = TAPI_MARKET_LEVEL_0;
		Req.FutureAutoCloseFlag = APIYNFLAG_NO;

		int r = m_pTdApi->InsertOrder(&m_SessionID, &Req);
		if (r != 0) {
			std::cout << "InsertOrder failed. r=" << r << std::endl;
			return -1;
		}

		return 0;
	}

	// 撤单
	int OrderCancel(const char* OrderNo)
	{
		TapAPIOrderCancelReq Req = { 0 };

		//Req.ServerFlag = 'x';
		strncpy_s(Req.OrderNo, OrderNo, sizeof(Req.OrderNo) - 1);

		int r = m_pTdApi->CancelOrder(&m_SessionID, &Req);
		if (r != 0) {
			std::cout << "CancelOrder failed. r=" << r << std::endl;
			return -1;
		}

		return 0;
	}

	//连接成功
	void TAP_CDECL OnConnect()
	{
		printf("Connected.\n");
	}

	//连接断开
	void TAP_CDECL OnDisconnect(TAPIINT32 reasonCode)
	{
		printf("Disconnected.[%d]\n",reasonCode);
	}

	void TAP_CDECL OnAPIReady()
	{
		// wait for ready.
		g_semaphore.signal();
	}

	//登录应答
	void TAP_CDECL OnRspLogin(TAPIINT32 errorCode, const TapAPITradeLoginRspInfo* loginRspInfo)
	{
		if (TAPIERROR_SUCCEED != errorCode) {
			printf("Login failed. %d\n", errorCode);
			return;
		}
		printf("Login succeeded.TradingDay:%s\n", loginRspInfo->TradeDate);
	}

	// 报单操作应答（包括下单、撤单）
	void TAP_CDECL OnRspOrderAction(TAPIUINT32 sessionID, TAPIUINT32 errorCode, const TapAPIOrderActionRsp* info)
	{
		if (APIORDER_INSERT == info->ActionType) {
			if (TAPIERROR_SUCCEED != errorCode)
				printf("下单失败：errorCode=%d\n", errorCode);
			else
				printf("下单应答:ContractNo:%s,ExchangeNo:%s,OrderExchangeSystemNo:%s,ClientOrderNo:%s,OrderState='%c'\n", info->OrderInfo->ContractNo, info->OrderInfo->ExchangeNo, info->OrderInfo->OrderExchangeSystemNo, info->OrderInfo->ClientOrderNo, info->OrderInfo->OrderState);
		}
		else if(APIORDER_DELETE == info->ActionType) {
			if (TAPIERROR_SUCCEED != errorCode)
				printf("下单失败：errorCode=%d\n", errorCode);
			else
				printf("撤单应答:ContractNo:%s,ExchangeNo:%s,OrderExchangeSystemNo:%s,ClientOrderNo:%s,OrderState='%c'\n", info->OrderInfo->ContractNo, info->OrderInfo->ExchangeNo, info->OrderInfo->OrderExchangeSystemNo, info->OrderInfo->ClientOrderNo, info->OrderInfo->OrderState);
		}
	}

	/*产品查询应答*/
	void TAP_CDECL OnRspQryCommodity(TAPIUINT32 sessionID, TAPIINT32 errorCode, TAPIYNFLAG isLast, const TapAPICommodityInfo* info)
	{
		if (info)
			printf("OnRspQryCommodity:CommodityNo:%s,CommodityName:%s,CommodityType:'%c',ExchangeNo:%s\n", info->CommodityNo, info->CommodityName, info->CommodityType, info->ExchangeNo);

		if (APIYNFLAG_YES == isLast) {
			g_semaphore.signal();
		}
	}

	/*交易所查询应答*/
	void TAP_CDECL OnRspQryExchange(TAPIUINT32 sessionID, TAPIINT32 errorCode, TAPIYNFLAG isLast, const TapAPIExchangeInfo* info)
	{
		if (info)
			printf("OnRspQryExchange:ExchangeNo:%s,ExchangeName:%s\n", info->ExchangeNo, info->ExchangeName);

		if (APIYNFLAG_YES == isLast) {
			g_semaphore.signal();
		}
	}

	/*投资者手续费率查询应答*/
	void TAP_CDECL OnRspAccountRentInfo(TAPIUINT32 sessionID, TAPIINT32 errorCode, TAPIYNFLAG isLast, const TapAPIAccountRentInfo* info)
	{
		if (info)
			printf("OnRspAccountRentInfo:ExchangeNo:%s,ContractNo:%s,OpenTurnover:%lf,ClosedTurnover:%lf,CloseNewTurnover:%lf,OpenVolume:%lf,ClosedVolume:%lf,CloseNewVolume:%lf\n", 
				info->ExchangeNo, info->ContractNo,
				info->OpenTurnover, info->ClosedTurnover, info->CloseNewTurnover,
				info->OpenVolume, info->ClosedVolume, info->CloseNewVolume);

		if (APIYNFLAG_YES == isLast) {
			g_semaphore.signal();
		}
	}

	// 查询合约列表
	void TAP_CDECL OnRspQryContract(TAPIUINT32 sessionID, TAPIINT32 errorCode, TAPIYNFLAG isLast, const TapAPITradeContractInfo* info)
	{
		if (TAPIERROR_SUCCEED != errorCode) {
			printf("OnRspQryContract failed. %d\n", errorCode);
			return;
		}
		
		if (info)
			printf("OnRspQryContract:ContractNo1:%s,ContractName:%s,CommodityNo:%s,FutureContractNo:%s,StrikePrice1:%s,ExchangeNo:%s\n", info->ContractNo1, info->ContractName, info->CommodityNo, info->FutureContractNo, info->StrikePrice1, info->ExchangeNo);

		if (APIYNFLAG_YES == isLast) {
			g_semaphore.signal();
		}
	}

	// 查询行情列表
	void TAP_CDECL OnRspQryDeepQuote(TAPIUINT32 sessionID, TAPIINT32 errorCode, TAPIYNFLAG isLast, const TapAPIDeepQuoteQryRsp* info)
	{
		if (TAPIERROR_SUCCEED != errorCode) {
			printf("OnRspQryDeepQuote failed. %d\n", errorCode);
			return;
		}

		if(info)
			printf("OnRspQryDepthMarketData:InstrumentID:%s,Side:%s,Price:%lf,Qty:%u\n",
				info->Contract.ContractNo1, direction_to_string(info->DeepQuote.Side).c_str(), double_format(info->DeepQuote.Price), info->DeepQuote.Qty);

		if (APIYNFLAG_YES == isLast) {
			g_semaphore.signal();
		}
	}

	// 查询委托列表
	void TAP_CDECL OnRspQryOrder(TAPIUINT32 sessionID, TAPIINT32 errorCode, TAPIYNFLAG isLast, const TapAPIOrderInfo* info)
	{
		if (TAPIERROR_SUCCEED != errorCode) {
			printf("OnRspQryOrder failed. %d\n", errorCode);
			return;
		}

		if(info)
			printf("OnRspQryOrder:ParentAccountNo:%s,UpperUserNo:%s,OrderLocalNo:%s,ContractNo:%s,OrderNo:%s,Direction:%s,OrderQty:%d,OrderPrice:%lf,OrderMatchQty:%d,OrderExchangeSystemNo:%s,ClientOrderNo:%s,OrderState:%c,ExchangeNo:%s,OrderInsertTime:%s,RefInt:%d,RefString=%s,ServerFlag:%c,ErrorText:%s\n",
				info->ParentAccountNo, info->UpperUserNo, info->OrderLocalNo, info->ContractNo, info->OrderNo, direction_to_string(info->OrderSide).c_str(), info->OrderQty, info->OrderPrice, info->OrderMatchQty, info->OrderExchangeSystemNo, info->ClientOrderNo, info->OrderState, info->ExchangeNo, info->OrderInsertTime, info->RefInt, info->RefString, info->ServerFlag, info->ErrorText);

		if (APIYNFLAG_YES == isLast) {
			g_semaphore.signal();
		}
	}

	// 查询成交列表
	void TAP_CDECL OnRspQryFill(TAPIUINT32 sessionID, TAPIINT32 errorCode, TAPIYNFLAG isLast, const TapAPIFillInfo* info)
	{
		if (TAPIERROR_SUCCEED != errorCode) {
			printf("OnRspQryFill failed. %d\n", errorCode);
			return;
		}

		if(info)
			printf("OnRspQryFill:ParentAccountNo:%s,UpperUserNo:%s,OrderLocalNo:%s,ContractNo:%s,Direction:%s,MatchQty:%d,MatchPrice:%lf,OrderExchangeNo:%s,TradeNo:%s,ExchangeNo:%s,MatchDateTime:%s\n",
				info->ParentAccountNo, info->UpperUserNo, info->OrderLocalNo, info->ContractNo, direction_to_string(info->MatchSide).c_str(), info->MatchQty, info->MatchPrice, info->OrderExchangeNo, info->TradeNo, info->ExchangeNo, info->MatchDateTime);

		if (APIYNFLAG_YES == isLast) {
			g_semaphore.signal();
		}
	}

	// 查询持仓
	void TAP_CDECL OnRspQryPosition(TAPIUINT32 sessionID, TAPIINT32 errorCode, TAPIYNFLAG isLast, const TapAPIPositionInfo* info)
	{
		if (TAPIERROR_SUCCEED != errorCode) {
			printf("OnRspQryPosition failed. %d\n", errorCode);
			return;
		}

		if (info)
			printf("OnRspQryPosition:InstrumentID:%s,PosiDirection:%s,HedgeFlag:%c,PositionQty:%d,PositionPrice:%lf,ExchangeID:%s\n",
				info->ContractNo, direction_to_string(info->MatchSide).c_str(), info->HedgeFlag, info->PositionQty, info->PositionPrice, info->ExchangeNo);

		if (APIYNFLAG_YES == isLast) {
			g_semaphore.signal();
		}
	}

	///请求查询资金账户响应
	void TAP_CDECL OnRspQryFund(TAPIUINT32 sessionID, TAPIINT32 errorCode, TAPIYNFLAG isLast, const TapAPIFundData* info)
	{
		if (TAPIERROR_SUCCEED != errorCode) {
			printf("OnRspQryFund failed. %d\n", errorCode);
			return;
		}
		if (info)
			printf("OnRspQryFund:AccountNo:%s,PreEquity:%lf,Equity:%lf,Available:%lf,AccountMaintenanceMargin:%lf,FrozenDeposit:%lf,CloseProfit:%lf,PositionProfit:%lf,AccountFee:%lf\n",
				info->AccountNo, info->PreEquity, info->Equity, info->Available, info->AccountMaintenanceMargin, info->FrozenDeposit, info->CloseProfit, info->PositionProfit, info->AccountFee);

		if (APIYNFLAG_YES == isLast)
			printf("Query completed.\n");
	}

	// 委托回报
	void TAP_CDECL OnRtnOrder(const TapAPIOrderInfoNotice* info)
	{
		printf("OnRtnOrder:AccountNo:%s,ExchangeNo:%s,ContractNo:%s,OrderNo:%s,OrderSystemNo:%s,OrderExchangeSystemNo:%s,OrderSide:%s,OrderPrice:%lf,OrderQty:%u,OrderInsertTime:%s,ErrorText:%s,OrderState:%c,RefInt:%d,RefString=%s,ServerFlag:%c,OrderLocalNo=%s\n",
			info->OrderInfo->AccountNo, info->OrderInfo->ExchangeNo, info->OrderInfo->ContractNo, info->OrderInfo->OrderNo, info->OrderInfo->OrderSystemNo, info->OrderInfo->OrderExchangeSystemNo, direction_to_string(info->OrderInfo->OrderSide).c_str(), info->OrderInfo->OrderPrice, info->OrderInfo->OrderQty, info->OrderInfo->OrderInsertTime, info->OrderInfo->ErrorText, info->OrderInfo->OrderState, info->OrderInfo->RefInt, info->OrderInfo->RefString, info->OrderInfo->ServerFlag, info->OrderInfo->OrderLocalNo);
	}

	// 成交回报
	void TAP_CDECL OnRtnFill(const TapAPIFillInfo* info)
	{
		printf("OnRtnFill:AccountNo:%s,ExchangeNo:%s,ContractNo:%s,OrderNo:%s,OrderExchangeNo:%s,ExchangeMatchNo:%s,MatchSide:%s,MatchPrice:%lf,MatchQty:%u,MatchDateTime:%s,ServerFlag:%c,OrderLocalNo=%s\n",
			info->AccountNo, info->ExchangeNo, info->ContractNo, info->OrderNo, info->OrderExchangeNo, info->ExchangeMatchNo, direction_to_string(info->MatchSide).c_str(), info->MatchPrice, info->MatchQty, info->MatchDateTime, info->ServerFlag, info->OrderLocalNo);
	}

	void TAP_CDECL OnRtnPosition(const TapAPIPositionInfo* info)
	{
		if (info)
			printf("OnRtnPosition:InstrumentID:%s,PosiDirection:%s,HedgeFlag:%c,PositionQty:%d,PositionPrice:%lf,ExchangeID:%s\n",
				info->ContractNo, direction_to_string(info->MatchSide).c_str(), info->HedgeFlag, info->PositionQty, info->PositionPrice, info->ExchangeNo);
	}

	void TAP_CDECL OnRtnFund(const TapAPIFundData* info)
	{
		if (info)
			printf("OnRtnFund:AccountNo:%s,PreEquity:%lf,Equity:%lf,Available:%lf,AccountMaintenanceMargin:%lf,FrozenDeposit:%lf,CloseProfit:%lf,PositionProfit:%lf,AccountFee:%lf\n",
				info->AccountNo, info->PreEquity, info->Equity, info->Available, info->AccountMaintenanceMargin, info->FrozenDeposit, info->CloseProfit, info->PositionProfit, info->AccountFee);
	}

	void TAP_CDECL OnRtnContract(const TapAPITradeContractInfo* info)
	{
		if (info)
			printf("OnRtnContract:ContractNo1:%s,ContractName:%s,CommodityNo:%s,FutureContractNo:%s,StrikePrice1:%s,ExchangeNo:%s\n", info->ContractNo1, info->ContractName, info->CommodityNo, info->FutureContractNo, info->StrikePrice1, info->ExchangeNo);
	}

	void TAP_CDECL OnRtnClose(const TapAPICloseInfo* info)
	{
	}

	void TAP_CDECL OnRtnPositionProfit(const TapAPIPositionProfitNotice* info)
	{
		if (info)
			printf("OnRtnPositionProfit:PositionNo:%s,PositionProfit:%lf,FloatingPL:%lf\n",
				info->Data->PositionNo, info->Data->PositionProfit, info->Data->FloatingPL);
	}

	void TAP_CDECL OnRspChangePassword(TAPIUINT32 sessionID, TAPIINT32 errorCode) {}
	void TAP_CDECL OnRspSetReservedInfo(TAPIUINT32 sessionID, TAPIINT32 errorCode, const TAPISTR_50 info) {}
	void TAP_CDECL OnRspQryAccount(TAPIUINT32 sessionID, TAPIUINT32 errorCode, TAPIYNFLAG isLast, const TapAPIAccountInfo* info) {}
	void TAP_CDECL OnRspQryOrderProcess(TAPIUINT32 sessionID, TAPIINT32 errorCode, TAPIYNFLAG isLast, const TapAPIOrderInfo* info) {}
	void TAP_CDECL OnRspQryClose(TAPIUINT32 sessionID, TAPIINT32 errorCode, TAPIYNFLAG isLast, const TapAPICloseInfo* info) {}
	void TAP_CDECL OnRspQryExchangeStateInfo(TAPIUINT32 sessionID, TAPIINT32 errorCode, TAPIYNFLAG isLast, const TapAPIExchangeStateInfo* info) {}
	void TAP_CDECL OnRtnExchangeStateInfo(const TapAPIExchangeStateInfoNotice* info) {}
	void TAP_CDECL OnRtnReqQuoteNotice(const TapAPIReqQuoteNotice* info) {}

	void TAP_CDECL OnRspUpperChannelInfo(TAPIUINT32 sessionID, TAPIINT32 errorCode, TAPIYNFLAG isLast, const TapAPIUpperChannelInfo* info) {}
	void TAP_CDECL OnRspSubmitUserLoginInfo(TAPIUINT32 sessionID, TAPIINT32 errorCode, TAPIYNFLAG isLast, const TapAPISubmitUserLoginRspInfo* info) {}
	void TAP_CDECL OnRspQryBill(TAPIUINT32 sessionID, TAPIINT32 errorCode, TAPIYNFLAG isLast, const TapAPIBillQryRsp* info) {}
	void TAP_CDECL OnRspQryAccountStorage(TAPIUINT32 sessionID, TAPIINT32 errorCode, TAPIYNFLAG isLast, const TapAPIAccountStorageInfo* info) {}
	void TAP_CDECL OnRtnAccountStorage(const TapAPIAccountStorageInfo* info) {}

public:
	std::string m_host;
	std::string m_broker;
	std::string m_user;
	std::string m_password;
	std::string m_appid;
	std::string m_authcode;
	unsigned int m_nOrderRef;
	TAPIUINT32 m_SessionID;

	ITapTradeAPI* m_pTdApi;
};


void display_usage()
{
	printf("usage:esprint host user password appid authcode\n");
	printf("example:esprint 180.168.146.187:10130 000001 888888 simnow_client_test 0000000000000000\n");
}


int main(int argc, char* argv[])
{
	if (argc != 6) {
		display_usage();
		return -1;
	}

	std::string host(argv[1]), user(argv[2]), password(argv[3]), appid(argv[4]), authcode(argv[5]);

	CApplication Spi(host, user, password, appid, authcode);

	// 启动
	if (Spi.Run() < 0)
		return -1;

	// 等待登录完成
	g_semaphore.wait();

	// 查询交易所
	printf("查询交易所 ...\n");
	TAPIUINT32 SessionID=0;
	int r;
	if ((r = Spi.m_pTdApi->QryExchange(&SessionID)) != 0) {
		std::cout << "QryExchange failed. r=" << r << std::endl;
		return -1;
	}
	g_semaphore.wait();

	// 查询品种
	std::this_thread::sleep_for(std::chrono::milliseconds(1000));
	printf("查询品种 ...\n");
	Spi.m_pTdApi->QryCommodity(&SessionID);
	g_semaphore.wait();

	// 查询投资者手续费率
	std::this_thread::sleep_for(std::chrono::milliseconds(1000));
	printf("查询投资者手续费率 ...\n");
	TapAPIAccountRentQryReq AccountRentQryReq = { 0 };
	strncpy(AccountRentQryReq.AccountNo, user.c_str(), sizeof(AccountRentQryReq.AccountNo) - 1);
	Spi.m_pTdApi->QryAccountRent(&SessionID,&AccountRentQryReq);
	g_semaphore.wait();

	// 查询合约
	std::this_thread::sleep_for(std::chrono::milliseconds(1000));
	printf("查询合约 ...\n");
	TapAPICommodity Commodity = { 0 };
	Spi.m_pTdApi->QryContract(&SessionID, &Commodity);
	g_semaphore.wait();

	// 查询行情
	std::this_thread::sleep_for(std::chrono::milliseconds(1000));
	printf("查询行情 ...\n");
	TapAPIContract Contract = { 0 };
	Spi.m_pTdApi->QryDeepQuote(&SessionID, &Contract);
	g_semaphore.wait();

	// 查询订单
	std::this_thread::sleep_for(std::chrono::milliseconds(1000));
	printf("查询订单 ...\n");
	TapAPIOrderQryReq OrderQryReq = { 0 };
	OrderQryReq.OrderQryType = TAPI_ORDER_QRY_TYPE_ALL;
	Spi.m_pTdApi->QryOrder(&SessionID, &OrderQryReq);
	g_semaphore.wait();

	// 查询成交
	std::this_thread::sleep_for(std::chrono::milliseconds(1000));
	printf("查询成交 ...\n");
	TapAPIFillQryReq FillQryReq = { 0 };
	Spi.m_pTdApi->QryFill(&SessionID, &FillQryReq);
	g_semaphore.wait();

	// 查询持仓
	std::this_thread::sleep_for(std::chrono::milliseconds(1000));
	printf("查询持仓 ...\n");
	TapAPIPositionQryReq PositionQryReq;
	Spi.m_pTdApi->QryPosition(&SessionID, &PositionQryReq);
	g_semaphore.wait();

	// 查询资金
	std::this_thread::sleep_for(std::chrono::milliseconds(1000));
	printf("查询资金 ...\n");
	TapAPIFundReq FundReq = { 0 };
	Spi.m_pTdApi->QryFund(&SessionID, &FundReq);

	// 如需下单、撤单，放开下面的代码即可
	std::this_thread::sleep_for(std::chrono::milliseconds(1000));
	printf("按任意键下单 ...\n");
	getchar();
	Spi.OrderInsert("SHFE", TAPI_COMMODITY_TYPE_FUTURES, "AG", "2406", TAPI_SIDE_BUY, TAPI_PositionEffect_OPEN, 7100, 1);

	std::this_thread::sleep_for(std::chrono::milliseconds(1000));
	printf("按任意键撤单 ...\n");
	getchar();
	Spi.OrderCancel("2024050900000098558");

	std::this_thread::sleep_for(std::chrono::milliseconds(1000));
	printf("按任意键退出 ...\n");
	getchar();

	return 0;
}
