#include <iostream>
#include <chrono>
#include <thread>
#include "ThostFtdcMdApi.h"

auto reqtime = std::chrono::steady_clock::now();

class CMarketSpi :public CThostFtdcMdSpi
{
public:
	CMarketSpi(CThostFtdcMdApi* pApi):m_pMarketApi(pApi)
	{
		pApi->RegisterSpi(this);
	}

	void OnFrontConnected()
	{
		std::cout << "connected." << std::endl;

		reqtime = std::chrono::steady_clock::now();
		CThostFtdcReqUserLoginField Req = {0};
		m_pMarketApi->ReqUserLogin(&Req, 0);
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

	CThostFtdcMdApi* m_pMarketApi;
};

int main(int argc,char *argv[])
{
	if (argc != 2) {
		std::cout << "usage:ctpping address" << std::endl;
		std::cout << "example:ctpping tcp://180.168.146.187:10100" << std::endl;
		return 0;
	}
	std::cout << "version:" << CThostFtdcMdApi::GetApiVersion() << std::endl;

	CThostFtdcMdApi* pApi = CThostFtdcMdApi::CreateFtdcMdApi();
	CMarketSpi Spi(pApi);
	pApi->RegisterFront(argv[1]);
	pApi->Init();

	std::this_thread::sleep_for(std::chrono::seconds(5));
	std::cout << "time out." << std::endl;

	return 0;
}
