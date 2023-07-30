#include <iostream>
#include <chrono>
#include <thread>
#ifdef _WIN32
#include "win/getopt.h"
#else
#include <unistd.h>
#endif
#include "ThostFtdcMdApi.h"
#include "ThostFtdcTraderApi.h"

auto reqtime = std::chrono::steady_clock::now();

class CMarketSpi :public CThostFtdcMdSpi
{
public:
	CMarketSpi(CThostFtdcMdApi* pApi):m_pApi(pApi)
	{
		pApi->RegisterSpi(this);
	}

	void OnFrontConnected()
	{
		std::cout << "connected." << std::endl;

		reqtime = std::chrono::steady_clock::now();
		CThostFtdcReqUserLoginField Req = {0};
		m_pApi->ReqUserLogin(&Req, 0);
	}

	void OnFrontDisconnected(int nReason)
	{
		std::cout << "disconnected." << std::endl;
		exit(0);
	}

	void OnRspUserLogin(CThostFtdcRspUserLoginField* pRspUserLogin, CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast)
	{
		auto rsptime = std::chrono::steady_clock::now();
		auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(rsptime - reqtime);

		std::cout << "response time: " << duration.count() << " milliseconds" << std::endl;
		exit(0);
	}

	CThostFtdcMdApi* m_pApi;
};

class CTradeSpi :public CThostFtdcTraderSpi
{
public:
	CTradeSpi(CThostFtdcTraderApi* pApi) :m_pApi(pApi)
	{
		pApi->RegisterSpi(this);
	}

	void OnFrontConnected()
	{
		std::cout << "connected." << std::endl;

		reqtime = std::chrono::steady_clock::now();
		CThostFtdcReqUserLoginField Req = { 0 };
		m_pApi->ReqUserLogin(&Req, 0);
	}

	void OnFrontDisconnected(int nReason)
	{
		std::cout << "disconnected." << std::endl;
		exit(0);
	}

	void OnRspUserLogin(CThostFtdcRspUserLoginField* pRspUserLogin, CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast)
	{
		auto rsptime = std::chrono::steady_clock::now();
		auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(rsptime - reqtime);

		std::cout << "response time: " << duration.count() << " milliseconds" << std::endl;
		exit(0);
	}

	CThostFtdcTraderApi* m_pApi;
};

void print_usage()
{
	std::cout << "usage:ctpping [-t] [-m] address" << std::endl;
	std::cout << "example:ctpping tcp://180.168.146.187:10130" << std::endl;
	std::cout << "example:ctpping -m tcp://180.168.146.187:10131" << std::endl;
	std::cout << "example:ctpping -t tcp://180.168.146.187:10130" << std::endl;
}
int main(int argc,char *argv[])
{
	bool use_trade = false;
	int ch;
	while ((ch = getopt(argc, argv, "tm")) != -1)
	{
		switch (ch) {
		case 't':
			use_trade = true;
			break;
		case 'm':
			break;
		case '?':
			print_usage();
			return -1;
		default:
			print_usage();
			return -1;
		}
	}

	if (optind >= argc) {
		print_usage();
		return -1;
	}

	if (use_trade) {
		std::cout << "version:" << CThostFtdcTraderApi::GetApiVersion() << std::endl;

		CThostFtdcTraderApi* pApi = CThostFtdcTraderApi::CreateFtdcTraderApi();
		CTradeSpi Spi(pApi);
		pApi->RegisterFront(argv[optind]);
		pApi->Init();
		std::this_thread::sleep_for(std::chrono::seconds(5));
	}
	else {
		std::cout << "version:" << CThostFtdcMdApi::GetApiVersion() << std::endl;

		CThostFtdcMdApi* pApi = CThostFtdcMdApi::CreateFtdcMdApi();
		CMarketSpi Spi(pApi);
		pApi->RegisterFront(argv[optind]);
		pApi->Init();
		std::this_thread::sleep_for(std::chrono::seconds(5));
	}

	std::cout << "time out." << std::endl;

	return 0;
}
