#include <stdio.h>
#include <string>
#include "ydApi.h"

#include <thread>
#include <mutex>
#include <functional>
#include <condition_variable>

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

class CApplication : public YDListener, YDExtendedListener
{
public:
	CApplication(std::string user, std::string password, std::string appid, std::string authcode) :
		m_user(user),
		m_password(password),
		m_appid(appid),
		m_authcode(authcode)
	{
		m_pApi = makeYDExtendedApi("config.txt");
	}

	~CApplication()
	{
	}

	const std::string direction_to_string(char Direction)
	{
		std::string str = Direction == YD_D_Buy ? "买" : "卖";
		return std::move(str);
	}

	const std::string posidirection_to_string(char Direction)
	{
		std::string str = Direction == YD_PD_Long ? "买" : "卖";
		return std::move(str);
	}

	double double_format(double value)
	{
		return value==DBL_MAX?0.0:value;
	}

	int Run()
	{

		if (!m_pApi->start(this))
		{
			printf("can not start API\n");
			return 0;
		}

		return 0;
	}

	void notifyReadyForLogin(bool hasLoginFailed)
	{
		// 当API准备登录时，发出此消息，用户需要在此时发出登录指令
		// 如果发生了断线重连，也会发出此消息，让用户重新发出登录指令，但是此时不允许换成另外的用户登录
		if (!m_pApi->login(m_user.c_str(), m_password.c_str(), NULL, NULL))
		{
			printf("can not login\n");
			exit(1);
		}
		m_hasCaughtUp = false;
	}
	void notifyLogin(int errorNo, int maxOrderRef, bool isMonitor)
	{
		// 每次登录响应，都会获得此消息，用户应当根据errorNo来判断是否登录成功
		if (errorNo == 0)
		{
			// 登录成功后，应当记录当前的最大报单引用，在报单时用更大的数作为报单引用，以便程序通过报单引用来识别报单
			m_nOrderRef = maxOrderRef;
			printf("login successfully\n");
		}
		else
		{
			// 如果登录失败，有可能是服务器端尚未启动，所以可以选择不终止程序，但是不需要在这里再次发出登录请求。
			// Api会稍过一会儿再次给出notifyReadyForLogin消息，应当在那时发出登录请求
			printf("login failed, errorNo=%d\n", errorNo);
			exit(1);
		}

		_semaphore.signal();

	}
	void notifyFinishInit(void)
	{
		// notifyFinishInit是在第一次登录成功后一小段时间发出的消息，表示API已经收到了今天的所有初始化信息，
		// 包括所有的产品合约信息，昨行情和今日的固定行情（例如涨跌停板）信息，账号的日初信息，保证金率信息，
		// 手续费率信息，昨持仓信息，但是还没有获得登录前已经发生的报单和成交信息，日内的出入金信息
		// 这个时候，用户程序已经可以安全地访问所有API管理的数据结构了
		// 用户程序获得所有YDSystemParam，YDExchange，YDProduct，YDInstrument，YDCombPositionDef，YDAccount，
		// YDPrePosition，YDMarginRate，YDCommissionRate，YDAccountExchangeInfo，YDAccountProductInfo，
		// YDAccountInstrumentInfo和YDMarketData的指针，都可以在未来长期安全使用，API不会改变其地址
		// 但是API消息中的YDOrder、YDTrade、YDInputOrder、YDQuote、YDInputQuote和YDCombPosition的地址都是
		// 临时的，在该消息处理完成后将不再有效

		auto p = m_pApi->getInstrumentByID("au2409");
		if(p)
			m_pApi->subscribe(p);
	}
	void notifyCaughtUp(void)
	{
		// 收到这个消息，说明客户端已经追上了服务器端的最新信息
		// 如果中间发生断线，需要重新设置（见notifyReadyForLogin），确保再次追上
		printf("notifyCaughtUp\n");
	}
	void notifyEvent(int apiEvent)
	{
		printf("notifyEvent:%d\n", apiEvent);
	}

	void notifyMarketData(const YDMarketData* pMarketData)
	{
		printf("notifyMarketData: InstrumentID:%s, Price:%.2f, Volume:%u\n", pMarketData->m_pInstrument->InstrumentID, pMarketData->LastPrice, pMarketData->Volume);
	}

	// 委托回报
	void notifyOrder(const YDOrder* pOrder, const YDInstrument* pInstrument, const YDAccount* pAccount)
	{
		printf("OrderLocalID:%d,InstrumentID:%s,Direction:%s,OrderVolume:%d,Price:%lf,TradeVolume:%d,OrderSysID:%d,SessionID:%d,OrderRef:%d,OrderStatus:%d,InsertTime:%d\n",
			pOrder->OrderLocalID, pInstrument->InstrumentID, direction_to_string(pOrder->Direction).c_str(), pOrder->OrderVolume, pOrder->Price, pOrder->TradeVolume, pOrder->OrderSysID, pOrder->SessionID, pOrder->OrderRef, pOrder->OrderStatus, pOrder->InsertTime);
	}

	// 成交回报
	void notifyTrade(const YDTrade* pTrade, const YDInstrument* pInstrument, const YDAccount* pAccount)
	{
		printf("notifyTrade:OrderLocalID:%d,InstrumentID:%s,Direction:%s,Volume:%d,Price:%lf,OrderSysID:%d,TradeID:%d,OrderRef:%d,TradeTime:%d\n",
			pTrade->OrderLocalID, pInstrument->InstrumentID, direction_to_string(pTrade->Direction).c_str(), pTrade->Volume, pTrade->Price, pTrade->OrderSysID, pTrade->TradeID, pTrade->OrderRef, pTrade->TradeTime);
	}


public:
	std::string m_host;
	std::string m_broker;
	std::string m_user;
	std::string m_password;
	std::string m_appid;
	std::string m_authcode;
	int m_nOrderRef;
	bool m_hasCaughtUp;

	YDExtendedApi* m_pApi;
};


void display_usage()
{
	printf("usage:ydprint host user password appid authcode\n");
	printf("example:ydprint tcp://118.190.175.212 001 001 yd_dev_1.0 ecbf8f06469eba63\n");
}


int main(int argc, char* argv[])
{
	if (argc != 6) {
		display_usage();
		return -1;
	}

	std::string user(argv[2]), password(argv[3]), appid(argv[4]), authcode(argv[5]);

	CApplication App(user, password, appid, authcode);

	// 启动
	if (App.Run() < 0)
		return -1;

	// 等待登录完成
	_semaphore.wait();

	// 查询交易所
	printf("查询交易所 ...\n");
	for (int i = 0; i < App.m_pApi->getExchangeCount(); i++) {
		auto p = App.m_pApi->getExchange(i);
		printf("ExhangeID:%s, UseTodayPosition:%d, CloseTodayFirst:%d, SingleSideMargin:%d:\n", p->ExchangeID, p->UseTodayPosition, p->CloseTodayFirst, p->SingleSideMargin);
	}

	// 查询品种
	printf("查询品种 ...\n");
	for (int i = 0; i < App.m_pApi->getProductCount(); i++) {
		auto p = App.m_pApi->getProduct(i);
		printf("ExhangeID:%s, ProductID:%s, ProductClass:%d, Multiple:%d, Tick:%lf:\n", p->m_pExchange->ExchangeID, p->ProductID, p->ProductClass, p->m_pMarginProduct->Multiple, p->m_pMarginProduct->Tick);
	}

	// 查询合约
	std::this_thread::sleep_for(std::chrono::milliseconds(1000));
	printf("查询合约 ...\n");
	for (int i = 0; i < App.m_pApi->getInstrumentCount(); i++) {
		auto p = App.m_pApi->getInstrument(i);
		printf("ExhangeID:%s, InstrumentID:%s, ProductClass:%d, Multiple:%d, Tick:%lf:\n", p->m_pExchange->ExchangeID, p->InstrumentID, p->ProductClass, p->Multiple, p->Tick);
		auto pAccountInstrumentInfo = App.m_pApi->getAccountInstrumentInfo(p);
		// 手续费率
		auto pCommissionRate = pAccountInstrumentInfo->m_pCommissionRate[YD_HF_Speculation];
		printf("CommissionRate:ExchangeID:%s,InstrumentID:%s,OpenRatioByMoney:%lf,CloseRatioByMoney:%lf,CloseTodayRatioByMoney:%lf,OpenRatioByVolume:%lf,CloseRatioByVolume:%lf,CloseTodayRatioByVolume:%lf\n",
			p->m_pExchange->ExchangeID, p->InstrumentID,
			pCommissionRate->OpenRatioByMoney, pCommissionRate->CloseRatioByMoney, pCommissionRate->CloseTodayRatioByMoney,
			pCommissionRate->OpenRatioByVolume, pCommissionRate->CloseRatioByVolume, pCommissionRate->CloseTodayRatioByVolume);
		// 保证金率
		auto pMarginRate = pAccountInstrumentInfo->m_pMarginRate[YD_HF_Speculation];
		printf("MarginRate:ExchangeID:%s,InstrumentID:%s,LongMarginRatioByMoney:%lf,LongMarginRatioByVolume:%lf,ShortMarginRatioByMoney:%lf,ShortMarginRatioByVolume:%lf\n",
			p->m_pExchange->ExchangeID, p->InstrumentID,
			pMarginRate->LongMarginRatioByMoney, pMarginRate->LongMarginRatioByVolume, pMarginRate->ShortMarginRatioByMoney,
			pMarginRate->ShortMarginRatioByVolume);
	}

	// 查询资金
	printf("查询资金 ...\n");
	auto p = App.m_pApi->getExtendedAccount();
	printf("Account:Balance:%lf,Available:%lf,Margin:%lf,CloseProfit:%lf,PositionProfit:%lf\n",
			p->Balance, p->Available, p->Margin, p->CloseProfit, p->PositionProfit);

	std::this_thread::sleep_for(std::chrono::milliseconds(1000));
	printf("按任意键退出 ...\n");
	getchar();

	return 0;
}
