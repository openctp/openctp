#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <vector>
#include <locale>
#include <codecvt>
#include "EMT/emt_quote_api.h"
#pragma comment(lib,"EMT/emt_quote_api.lib")

#define EMT_CLIENT_ID 82

using namespace EMT::API;

class CApplication : public QuoteSpi
{
public:
	CApplication(std::string host, std::string user, std::string password) :
		m_host(host),
		m_user(user),
		m_password(password)
	{
		m_pUserApi = QuoteApi::CreateQuoteApi(EMT_CLIENT_ID, ".", EMT_LOG_LEVEL_WARNING);
		m_pUserApi->RegisterSpi(this);
		m_pUserApi->SetHeartBeatInterval(16);//设定交易服务器超时时间，单位为秒，此为1.1.16新增接口
	}

	~CApplication()
	{
	}

	void OnQueryAllTickers(EMTQuoteStaticInfo* ticker_info, EMTRspInfoStruct* error_info, bool is_last)
	{
		if (error_info && error_info->error_id != 0) {
			OnError(error_info);
			return;
		}
		if (ticker_info)
			m_vInstruments.push_back(*ticker_info);
		if (ticker_info->exchange_id == EMT_EXCHANGE_SH && is_last) {
			// 上海查完查深圳
			m_pUserApi->QueryAllTickers(EMT_EXCHANGE_SZ);
		}
		if (ticker_info->exchange_id == EMT_EXCHANGE_SZ && is_last) {
			// 深圳查完dump到文件
			printf("%u Instruments received.\n", (unsigned int)m_vInstruments.size());

			std::ofstream outfile;
			outfile.open("dict.csv", std::ios::out | std::ios::trunc);
			for (auto iter = m_vInstruments.begin(); iter != m_vInstruments.end(); iter++) {
				switch (iter->ticker_type) {
				case EMT_TICKER_TYPE_STOCK:
				case EMT_TICKER_TYPE_TECH_STOCK:
					break;
				case EMT_TICKER_TYPE_FUND:
					break;
				case EMT_TICKER_TYPE_BOND:
					break;
				case EMT_TICKER_TYPE_INDEX:
					break;
				default:
					continue;
				}
				outfile << GetExchangeID(iter->exchange_id) << "," << GetProductClass(iter->ticker_type) << "," << iter->ticker << "," << iter->ticker_name << "," << iter->price_tick << "," << iter->pre_close_price << std::endl;
			}
			
			outfile.close();
			printf("Dump completed.\n");
			//exit(0);
		}
	}


	const std::string GetExchangeID(EMT_EXCHANGE_TYPE exchange_id)
	{
		std::string str;

		switch (exchange_id) {
		case EMT_EXCHANGE_SH:
			str = "SSE";
			break;
		case EMT_EXCHANGE_SZ:
			str = "SZSE";
			break;
		default:
			break;
		}

		return std::move(str);
	}


	const std::string GetProductClass(EMT_TICKER_TYPE ticker_type)
	{
		std::string str;

		switch (ticker_type) {
		case EMT_TICKER_TYPE_STOCK:
		case EMT_TICKER_TYPE_TECH_STOCK:
			str = 'E';
			break;
		case EMT_TICKER_TYPE_BOND:
			str = 'B';
			break;
		case EMT_TICKER_TYPE_FUND:
			str = 'D';
			break;
		case EMT_TICKER_TYPE_INDEX:
			str = 'I';
			break;
		default:
			break;
		}

		return std::move(str);
	}

	int Run()
	{
		std::string ip = m_host.substr(0, m_host.find(':'));
		std::string port = m_host.substr(m_host.find(':') + 1);
		if (m_pUserApi->Login(ip.c_str(), atol(port.c_str()), m_user.c_str(), m_password.c_str(), EMT_PROTOCOL_TCP,"127.0.0.1")!=0) {
			printf("Login failed.\n");
			OnError(m_pUserApi->GetApiLastError());
			return -1;
		}
		printf("Login succeeded.\n");

		// 查询合约
		printf("Query Instruments ...\n");
		m_pUserApi->QueryAllTickers(EMT_EXCHANGE_SH);

		return 0;
	}

	virtual void OnDisconnected(uint64_t session_id, int reason)
	{
		printf("Disconnected.\n");
	}

	///错误响应
	virtual void OnError(EMTRspInfoStruct* error_info)
	{
		if (!error_info)
			return;
		printf("Error: %d - %s\n", error_info->error_id, error_info->error_msg);
	}


private:
	std::string m_host;
	std::string m_user;
	std::string m_password;
	std::vector<EMTQuoteStaticInfo> m_vInstruments;
	EMT::API::QuoteApi* m_pUserApi;
};

void display_usage()
{
	printf("usage:dictdump host user password\n");
	printf("example:dictdump 119.3.103.38:6002 000001 888888\n");
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
