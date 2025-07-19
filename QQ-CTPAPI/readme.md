# CTP程序接入腾讯行情（A股、港股、美股）

本接口底层直接腾讯行情服务器，通讯协议为http协议，相关协议说明网上有很多介绍，封装成CTP接口可以为CTP开发者们接股票行情节省很多时间。

调用订阅接口时还是同订阅期货合约行情一样，订阅股票合约代码即可，如下是demo程序接收的数据：

行情前置地址设置个空值即可，也可以不设置，接口内部会以腾讯的网址进行连接。

不必在登录响应后进行订阅，当然登录响应还是会被回调的，以便符合CTP程序本身的工作流程。

接口会每隔3秒钟发起一次http短连接行情查询。

接口so/dll文件下载：[腾讯行情CTPAPI接口下载](http://openctp.cn/QQ-CTPAPI.html)

**一个连接能够查询的股票数量是有限的，性能也不高，但是可以创建多个api实例并发工作，在每个实例中订阅一部分合约。**

demo代码：
```
#include <iostream>
#include <chrono>
#include "./ThostFtdcMdApi.h"
#pragma comment( lib, "thostmduserapi_se.lib" )

class CMarketSpi :public CThostFtdcMdSpi
{
public:
	CMarketSpi(CThostFtdcMdApi* pApi) :m_pMarketApi(pApi)
	{
		pApi->RegisterSpi(this);
	}

	void OnRtnDepthMarketData(CThostFtdcDepthMarketDataField* pDepthMarketData)
	{
		std::cout << pDepthMarketData->InstrumentID << " - " << pDepthMarketData->LastPrice << " - " << pDepthMarketData->Volume << std::endl;
	}

	CThostFtdcMdApi* m_pMarketApi;
};

int main(int argc, char* argv[])
{
	CThostFtdcMdApi* pApi = CThostFtdcMdApi::CreateFtdcMdApi();
	CMarketSpi Spi(pApi);
	pApi->Init();
	const char* symbols[4] = { "600000","000001","00700","AAPL" };
	pApi->SubscribeMarketData((char**)symbols, 4);
	getchar();

	return 0;
}
```

![ctp2QQ](https://user-images.githubusercontent.com/83346523/144754227-39c022a1-26b1-4735-9c28-128ec4e648f8.png)
