#include "./IB/EWrapper.h"
#include "./IB/EReaderOSSignal.h"
#include "./IB/EReader.h"
#include "./IB/EClientSocket.h"
#include "./IB/Contract.h"
#include "./IB/Order.h"
#include "./IB/OrderState.h"

#include <thread>
#include <mutex>
#include <functional>
#include <condition_variable>

#pragma comment (lib, "./IB/TwsSocketClient.lib")

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

class AccountSummaryTags {
public:
	static std::string AccountType;
	static std::string NetLiquidation;
	static std::string TotalCashValue;
	static std::string SettledCash;
	static std::string AccruedCash;
	static std::string BuyingPower;
	static std::string EquityWithLoanValue;
	static std::string PreviousEquityWithLoanValue;
	static std::string GrossPositionValue;
	static std::string ReqTEquity;
	static std::string ReqTMargin;
	static std::string SMA;
	static std::string InitMarginReq;
	static std::string MaintMarginReq;
	static std::string AvailableFunds;
	static std::string ExcessLiquidity;
	static std::string Cushion;
	static std::string FullInitMarginReq;
	static std::string FullMaintMarginReq;
	static std::string FullAvailableFunds;
	static std::string FullExcessLiquidity;
	static std::string LookAheadNextChange;
	static std::string LookAheadInitMarginReq;
	static std::string LookAheadMaintMarginReq;
	static std::string LookAheadAvailableFunds;
	static std::string LookAheadExcessLiquidity;
	static std::string HighestSeverity;
	static std::string DayTradesRemaining;
	static std::string Leverage;

	static std::string getAllTags();
};
std::string AccountSummaryTags::AccountType = "AccountType";
std::string AccountSummaryTags::NetLiquidation = "NetLiquidation";
std::string AccountSummaryTags::TotalCashValue = "TotalCashValue";
std::string AccountSummaryTags::SettledCash = "SettledCash";
std::string AccountSummaryTags::AccruedCash = "AccruedCash";
std::string AccountSummaryTags::BuyingPower = "BuyingPower";
std::string AccountSummaryTags::EquityWithLoanValue = "EquityWithLoanValue";
std::string AccountSummaryTags::PreviousEquityWithLoanValue = "PreviousEquityWithLoanValue";
std::string AccountSummaryTags::GrossPositionValue = "GrossPositionValue";
std::string AccountSummaryTags::ReqTEquity = "ReqTEquity";
std::string AccountSummaryTags::ReqTMargin = "ReqTMargin";
std::string AccountSummaryTags::SMA = "SMA";
std::string AccountSummaryTags::InitMarginReq = "InitMarginReq";
std::string AccountSummaryTags::MaintMarginReq = "MaintMarginReq";
std::string AccountSummaryTags::AvailableFunds = "AvailableFunds";
std::string AccountSummaryTags::ExcessLiquidity = "ExcessLiquidity";
std::string AccountSummaryTags::Cushion = "Cushion";
std::string AccountSummaryTags::FullInitMarginReq = "FullInitMarginReq";
std::string AccountSummaryTags::FullMaintMarginReq = "FullMaintMarginReq";
std::string AccountSummaryTags::FullAvailableFunds = "FullAvailableFunds";
std::string AccountSummaryTags::FullExcessLiquidity = "FullExcessLiquidity";
std::string AccountSummaryTags::LookAheadNextChange = "LookAheadNextChange";
std::string AccountSummaryTags::LookAheadInitMarginReq = "LookAheadInitMarginReq";
std::string AccountSummaryTags::LookAheadMaintMarginReq = "LookAheadMaintMarginReq";
std::string AccountSummaryTags::LookAheadAvailableFunds = "LookAheadAvailableFunds";
std::string AccountSummaryTags::LookAheadExcessLiquidity = "LookAheadExcessLiquidity";
std::string AccountSummaryTags::HighestSeverity = "HighestSeverity";
std::string AccountSummaryTags::DayTradesRemaining = "DayTradesRemaining";
std::string AccountSummaryTags::Leverage = "Leverage";

std::string AccountSummaryTags::getAllTags() 
{
	return AccountType + "," + NetLiquidation + "," + TotalCashValue + "," + SettledCash + "," + AccruedCash + "," + BuyingPower + "," + EquityWithLoanValue + "," + PreviousEquityWithLoanValue + "," + GrossPositionValue + "," + ReqTEquity
		+ "," + ReqTMargin + "," + SMA + "," + InitMarginReq + "," + MaintMarginReq + "," + AvailableFunds + "," + ExcessLiquidity + "," + Cushion + "," + FullInitMarginReq + "," + FullMaintMarginReq + "," + FullAvailableFunds + "," + FullExcessLiquidity
		+ "," + LookAheadNextChange + "," + LookAheadInitMarginReq + "," + LookAheadMaintMarginReq + "," + LookAheadAvailableFunds + "," + LookAheadExcessLiquidity + "," + HighestSeverity + "," + DayTradesRemaining + "," + Leverage;
}

class CIBSpiImp : public EWrapper
{
public:
	CIBSpiImp(std::string host, int port, int clientid) :
		m_host(host),
		m_port(port),
		m_clientid(clientid),
		m_osSignal(2000),
		m_pClient(new EClientSocket(this, &m_osSignal)),
		m_orderId(0),
		m_pReader(nullptr),
		m_bFlag(false),
		m_bQuit(false)
	{
	}
	~CIBSpiImp()
	{
		if (m_pReader)
			delete m_pReader;
		m_pReader = nullptr;
		delete m_pClient;
		m_pClient = nullptr;
	}
public:
	bool connect(const char * host, int port, int clientId = 0)
	{
		bool bRes = m_pClient->eConnect(host, port, clientId, false);
		if (bRes)
		{
			printf("Connected to %s:%d clientId:%d\n", m_pClient->host().c_str(), m_pClient->port(), clientId);
			m_pReader = new EReader(m_pClient, &m_osSignal);
			m_pReader->start();
			m_spWorkThread.reset(new std::thread(&CIBSpiImp::threadFunc, this));
		}
		else
			printf("Cannot connect to %s:%d clientId:%d\n", m_pClient->host().c_str(), m_pClient->port(), clientId);

		return bRes;
	}
	bool isConnected() const
	{
		return m_pClient->isConnected();
	}
	void disconnect() const
	{
		m_pClient->eDisconnect();
		printf("Disconnected\n");
	}
	void run()
	{
		connect(m_host.c_str(), m_port, m_clientid);
	}
	void threadFunc()
	{
		if (m_pClient)
		{
			while (m_pClient->isConnected())
			{
				m_osSignal.waitForSignal();
				if (m_pReader)
				{
					m_pReader->processMsgs();
				}
			}
		}
	}
public:
	void orderStatus(OrderId orderId, const std::string& status, double filled,
		double remaining, double avgFillPrice, int permId, int parentId,
		double lastFillPrice, int clientId, const std::string& whyHeld, double mktCapPrice) 
	{
		printf("OrderStatus. Id: %ld, Status: %s, Filled: %g, Remaining: %g, AvgFillPrice: %g, PermId: %d, LastFillPrice: %g, ClientId: %d, WhyHeld: %s, MktCapPrice: %g\n", orderId, status.c_str(), filled, remaining, avgFillPrice, permId, lastFillPrice, clientId, whyHeld.c_str(), mktCapPrice);
	}
	void openOrder(OrderId orderId, const Contract& contract, const Order& order, const OrderState& orderState)
	{
		printf("OpenOrder. PermId: %ld, ClientId: %ld, OrderId: %ld, Account: %s, Symbol: %s, SecType: %s, Exchange: %s:, Action: %s, OrderType:%s, TotalQty: %g, CashQty: %g, "
			"LmtPrice: %g, AuxPrice: %g, Status: %s\n",
			order.permId, order.clientId, orderId, order.account.c_str(), contract.symbol.c_str(), contract.secType.c_str(), contract.exchange.c_str(),
			order.action.c_str(), order.orderType.c_str(), order.totalQuantity, order.cashQty == UNSET_DOUBLE ? 0 : order.cashQty, order.lmtPrice, order.auxPrice, orderState.status.c_str());
	}
	void openOrderEnd() 
	{
		printf("openOrderEnd\n");
		if (m_bFlag)
		{
			_semaphore.signal();
		}
	}
	void nextValidId(OrderId orderId) 
	{
		printf("Next Valid Id: %ld\n", orderId);
		m_orderId = orderId;
		m_bFlag = true;
		_semaphore.signal();
	}
	void contractDetails(int reqId, const ContractDetails& contractDetails)
	{
		printf("ContractDetails begin. ReqId: %d\n", reqId);
		printContractMsg(contractDetails.contract);
		printContractDetailsMsg(contractDetails);
		printf("ContractDetails end. ReqId: %d\n", reqId);
	}
	void contractDetailsEnd(int reqId) 
	{
		printf("ContractDetailsEnd. %d\n", reqId);
		_semaphore.signal();
	}
	void error(int id, int errorCode, const std::string& errorString)
	{
		printf("Error. Id: %d, Code: %d, Msg: %s\n", id, errorCode, errorString.c_str());
	}
	void managedAccounts(const std::string& accountsList) 
	{
		printf("Account List: %s\n", accountsList.c_str());
	}
	void position(const std::string& account, const Contract& contract, double position, double avgCost)
	{
		printf("Position. %s - Symbol: %s, SecType: %s, Currency: %s, Position: %g, Avg Cost: %g\n", account.c_str(), contract.symbol.c_str(), contract.secType.c_str(), contract.currency.c_str(), position, avgCost);
	}
	void positionEnd()
	{
		printf("PositionEnd\n");
		_semaphore.signal();
	}
	void accountSummary(int reqId, const std::string& account, const std::string& tag, const std::string& value, const std::string& currency) 
	{
		printf("Acct Summary. ReqId: %d, Account: %s, Tag: %s, Value: %s, Currency: %s\n", reqId, account.c_str(), tag.c_str(), value.c_str(), currency.c_str());
	}
	void accountSummaryEnd(int reqId)
	{
		printf("AccountSummaryEnd. Req Id: %d\n", reqId);
		_semaphore.signal();
	}
	void connectAck()
	{
		printf("connectAck\n");
		if (m_pClient->asyncEConnect())
			m_pClient->startApi();
	}
	void completedOrder(const Contract& contract, const Order& order, const OrderState& orderState)
	{
		printf("CompletedOrder. PermId: %ld, ParentPermId: %lld, Account: %s, Symbol: %s, SecType: %s, Exchange: %s:, Action: %s, OrderType: %s, TotalQty: %g, CashQty: %g, FilledQty: %g, "
			"LmtPrice: %g, AuxPrice: %g, Status: %s, CompletedTime: %s, CompletedStatus: %s\n",
			order.permId, order.parentPermId == UNSET_LONG ? 0 : order.parentPermId, order.account.c_str(), contract.symbol.c_str(), contract.secType.c_str(), contract.exchange.c_str(),
			order.action.c_str(), order.orderType.c_str(), order.totalQuantity, order.cashQty == UNSET_DOUBLE ? 0 : order.cashQty, order.filledQuantity,
			order.lmtPrice, order.auxPrice, orderState.status.c_str(), orderState.completedTime.c_str(), orderState.completedStatus.c_str());
	}
	void completedOrdersEnd() 
	{
		printf("CompletedOrdersEnd\n");
		_semaphore.signal();
	}
public:
	void reqQryInstrument()
	{
		printf("查询某个合约详细信息:\n");
		m_pClient->reqContractDetails(213, IBKRStk());
	}
	void reqQryOrer()
	{
		printf("查询所有报单:\n");
		m_pClient->reqAllOpenOrders();
	}
	void reqQryPosition()
	{
		printf("查询所有持仓:\n");
		m_pClient->reqPositions();
	}
	void reqQryAccount()
	{
		printf("查询账户资金信息:\n");
		m_pClient->reqAccountSummary(9001, "All", AccountSummaryTags::getAllTags());
	}
	void reqQryTrade()
	{
		printf("查询所有成交:\n");
		m_pClient->reqCompletedOrders(false);
	}
	void reqOrderInsert()
	{
		printf("开始下单:\n");
		m_pClient->placeOrder(m_orderId++, USStock(), LimitOrder("SELL", 1, 76.75));
		std::this_thread::sleep_for(std::chrono::seconds(2));
	}
	void reqCancelOrder()
	{
		printf("撤单:\n");
		m_pClient->cancelOrder(m_orderId - 1);
	}
	void quit()
	{
		if (m_spWorkThread->joinable())
			m_spWorkThread->join();
	}
private:
	void printContractMsg(const Contract& contract)
	{
		printf("\tConId: %ld\n", contract.conId);
		printf("\tSymbol: %s\n", contract.symbol.c_str());
		printf("\tSecType: %s\n", contract.secType.c_str());
		printf("\tLastTradeDateOrContractMonth: %s\n", contract.lastTradeDateOrContractMonth.c_str());
		printf("\tStrike: %g\n", contract.strike);
		printf("\tRight: %s\n", contract.right.c_str());
		printf("\tMultiplier: %s\n", contract.multiplier.c_str());
		printf("\tExchange: %s\n", contract.exchange.c_str());
		printf("\tPrimaryExchange: %s\n", contract.primaryExchange.c_str());
		printf("\tCurrency: %s\n", contract.currency.c_str());
		printf("\tLocalSymbol: %s\n", contract.localSymbol.c_str());
		printf("\tTradingClass: %s\n", contract.tradingClass.c_str());
	}
	void printContractDetailsMsg(const ContractDetails& contractDetails) {
		printf("\tMarketName: %s\n", contractDetails.marketName.c_str());
		printf("\tMinTick: %g\n", contractDetails.minTick);
		printf("\tPriceMagnifier: %ld\n", contractDetails.priceMagnifier);
		printf("\tOrderTypes: %s\n", contractDetails.orderTypes.c_str());
		printf("\tValidExchanges: %s\n", contractDetails.validExchanges.c_str());
		printf("\tUnderConId: %d\n", contractDetails.underConId);
		printf("\tLongName: %s\n", contractDetails.longName.c_str());
		printf("\tContractMonth: %s\n", contractDetails.contractMonth.c_str());
		printf("\tIndystry: %s\n", contractDetails.industry.c_str());
		printf("\tCategory: %s\n", contractDetails.category.c_str());
		printf("\tSubCategory: %s\n", contractDetails.subcategory.c_str());
		printf("\tTimeZoneId: %s\n", contractDetails.timeZoneId.c_str());
		printf("\tTradingHours: %s\n", contractDetails.tradingHours.c_str());
		printf("\tLiquidHours: %s\n", contractDetails.liquidHours.c_str());
		printf("\tEvRule: %s\n", contractDetails.evRule.c_str());
		printf("\tEvMultiplier: %g\n", contractDetails.evMultiplier);
		printf("\tMdSizeMultiplier: %d\n", contractDetails.mdSizeMultiplier);
		printf("\tAggGroup: %d\n", contractDetails.aggGroup);
		printf("\tUnderSymbol: %s\n", contractDetails.underSymbol.c_str());
		printf("\tUnderSecType: %s\n", contractDetails.underSecType.c_str());
		printf("\tMarketRuleIds: %s\n", contractDetails.marketRuleIds.c_str());
		printf("\tRealExpirationDate: %s\n", contractDetails.realExpirationDate.c_str());
		printf("\tLastTradeTime: %s\n", contractDetails.lastTradeTime.c_str());
		printContractDetailsSecIdList(contractDetails.secIdList);
	}
	void printContractDetailsSecIdList(const TagValueListSPtr &secIdList) {
		const int secIdListCount = secIdList.get() ? secIdList->size() : 0;
		if (secIdListCount > 0) {
			printf("\tSecIdList: {");
			for (int i = 0; i < secIdListCount; ++i) {
				const TagValue* tagValue = ((*secIdList)[i]).get();
				printf("%s=%s;", tagValue->tag.c_str(), tagValue->value.c_str());
			}
			printf("}\n");
		}
	}
	Contract IBKRStk()
	{
		Contract contract;
		contract.symbol = "IBKR";
		contract.secType = "STK";
		contract.currency = "USD";
		contract.exchange = "SMART";
		return contract;
	}
	Contract USStock() {
		Contract contract;
		contract.symbol = "IBKR";
		contract.secType = "STK";
		contract.currency = "USD";
		contract.exchange = "ISLAND";
		return contract;
	}
	Order LimitOrder(std::string action, double quantity, double limitPrice)
	{
		Order order;
		order.action = action;
		order.orderType = "LMT";
		order.totalQuantity = quantity;
		order.lmtPrice = limitPrice;
		return order;
	}
private:
	EReaderOSSignal		m_osSignal;
	EClientSocket*		m_pClient;
	OrderId				m_orderId;
	EReader*			m_pReader;
	//回调函数的线程需要自行创建
	std::unique_ptr<std::thread>     m_spWorkThread;
	bool				m_bFlag;
	bool				m_bQuit;
	std::string 		m_host;
	int 				m_port;
	int		 			m_clientid;
};

void display_usage()
{
	printf("usage:IB host port clientid\n");
	printf("example:IB 127.0.0.1 7497 0\n");
}

int main(int argc, char** argv)
{
	if (argc != 4) {
		display_usage();
		return -1;
	}
	std::string host(argv[1]);
	int port(atoi(argv[2])), clientid(atoi(argv[3]));
	CIBSpiImp client(host, port, clientid);
	client.run();
	//等待初始化完成
	_semaphore.wait();

	client.reqQryAccount();
	_semaphore.wait();

	client.reqQryInstrument();
	_semaphore.wait();

	client.reqQryOrer();
	_semaphore.wait();

	//如果账户没有成交 不会有任何回调 所以账户没有成交的时候将查询成交注释掉
	//client.reqQryTrade();
	//_semaphore.wait();

	client.reqQryPosition();
	_semaphore.wait();
	
	// 如需下单、撤单，放开下面的代码即可
	/*
	printf("按任意键下单 ...\n");
	getchar();
	client.reqOrderInsert();
	std::this_thread::sleep_for(std::chrono::milliseconds(2000));
	printf("按任意键撤单 ...\n");
	getchar();
	client.reqCancelOrder();
	*/
	client.quit();
	return 0;
}