// xtpdump.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <cstring>
#include <iomanip>
#include <stdio.h>
#include <time.h>
#include <sys/timeb.h>
#ifndef _WIN32
#include <sys/time.h>
#include <unistd.h>
#else
#include <windows.h>
#endif
#include <sstream>
#include <map>
#include "nlohmann/json.hpp"
#include "xtp_trader_api.h"

/////////////////// getopt //////////////////
#ifdef _WIN32
int	opterr = 1;
int	optind = 1;
int	optopt;
char* optarg;

int getopt(int argc, char** argv, const char *opts)
{
	static int sp = 1;
	register int c;
	register const char* cp;

	if (sp == 1)
		if (optind >= argc ||
			argv[optind][0] != '-' || argv[optind][1] == '\0')
			return(EOF);
		else if (strcmp(argv[optind], "--") == NULL) {
			optind++;
			return(EOF);
		}
	optopt = c = argv[optind][sp];
	if (c == ':' || (cp = strchr(opts, c)) == NULL) {
		// illegal option
		if (argv[optind][++sp] == '\0') {
			optind++;
			sp = 1;
		}
		return('?');
	}
	if (*++cp == ':') {
		if (argv[optind][sp + 1] != '\0')
			optarg = &argv[optind++][sp + 1];
		else if (++optind >= argc) {
			// option requires an argument
			sp = 1;
			return('?');
		}
		else
			optarg = argv[optind++];
		sp = 1;
	}
	else {
		if (argv[optind][++sp] == '\0') {
			sp = 1;
			optind++;
		}
		optarg = NULL;
	}
	return(c);
}
#else
#include <getopt.h>
#endif


using namespace std;

extern XTPOrderInsertInfo* orderList;

using namespace XTP::API;

class MyTraderSpi : public TraderSpi
{
public:
	MyTraderSpi(std::string host, std::string user, std::string password, std::string authcode):
		m_host(host),
		m_user(user),
		m_password(password),
		m_authcode(authcode)
	{
		m_pUserApi = XTP::API::TraderApi::CreateTraderApi(99, ".", XTP_LOG_LEVEL_WARNING);
		m_pUserApi->RegisterSpi(this);
		m_pUserApi->SetSoftwareVersion("1.0"); //设定此软件的开发版本号，用户自定义
		m_pUserApi->SetSoftwareKey(m_authcode.c_str());//设定用户的开发代码，在XTP申请开户时，由xtp人员提供
		m_pUserApi->SetHeartBeatInterval(16);//设定交易服务器超时时间，单位为秒，此为1.1.16新增接口
	}

	~MyTraderSpi()
	{
	}

	int Run()
	{
		std::string ip = m_host.substr(0, m_host.find(':'));
		std::string port = m_host.substr(m_host.find(':')+1);
		m_session_id = m_pUserApi->Login(ip.c_str(), atol(port.c_str()), m_user.c_str(), m_password.c_str(), XTP_PROTOCOL_TCP);
		if (!m_session_id) {
			OnError(m_pUserApi->GetApiLastError());
			std::cout << "Login failed." << std::endl;
			return -1;
		}
		std::cout << "Login succeeded." << std::endl;

		// 查询订单
		XTPQueryOrderReq Req = { 0 };
		m_pUserApi->QueryOrders(&Req, m_session_id, 0);

		return 0;
	}

	virtual void OnDisconnected(uint64_t session_id, int reason)
	{
		std::cout << "Disconnected." << endl;
	}

	///错误响应
	virtual void OnError(XTPRI* error_info)
	{
		if (!error_info)
			return;
		cout << "Error:" << error_info->error_id << " - " << error_info->error_msg << endl;
	}

	virtual void OnQueryOrder(XTPQueryOrderRsp* order_info, XTPRI* error_info, int request_id, bool is_last, uint64_t session_id)
	{
		if (error_info && error_info->error_id != 0)
		{
			if (error_info->error_id == 11000350) {
				// 没有记录
				XTPQueryTraderReq Req = { 0 };
				if (!m_pUserApi->QueryTrades(&Req, m_session_id, 0)) {
					OnError(m_pUserApi->GetApiLastError());
					return;
				}

				return;
			}
			OnError(error_info);
			return;
		}
		m_vOrders.push_back(*order_info);

		if (is_last) {
			XTPQueryTraderReq Req = { 0 };
			if (!m_pUserApi->QueryTrades(&Req, m_session_id, 0)) {
				OnError(m_pUserApi->GetApiLastError());
				return;
			}
		}
	}

	virtual void OnQueryTrade(XTPQueryTradeRsp* trade_info, XTPRI* error_info, int request_id, bool is_last, uint64_t session_idt)
	{
		if (error_info && error_info->error_id != 0)
		{
			if (error_info->error_id == 11000350) {
				// 没有记录
				if (!m_pUserApi->QueryPosition(NULL, m_session_id, 0)) {
					OnError(m_pUserApi->GetApiLastError());
					return;
				}
			}
			OnError(error_info);
			return;
		}
		m_vTrades.push_back(*trade_info);

		if (is_last) {
			if (!m_pUserApi->QueryPosition(NULL, m_session_id, 0)) {
				OnError(m_pUserApi->GetApiLastError());
				return;
			}
		}
	}

	virtual void OnQueryPosition(XTPQueryStkPositionRsp* investor_position, XTPRI* error_info, int request_id, bool is_last, uint64_t session_id)
	{
		if (error_info && error_info->error_id != 0)
		{
			if (error_info->error_id == 11000350) {
				// 没有记录
				if (!m_pUserApi->QueryAsset(m_session_id, 0)) {
					OnError(m_pUserApi->GetApiLastError());
					return;
				}
			}
			OnError(error_info);
			return;
		}
		m_vPositions.push_back(*investor_position);

		if (is_last) {
			if (!m_pUserApi->QueryAsset(m_session_id, 0)) {
				OnError(m_pUserApi->GetApiLastError());
				return;
			}
		}
	}

	virtual void OnQueryAsset(XTPQueryAssetRsp* trading_account, XTPRI* error_info, int request_id, bool is_last, uint64_t session_id)
	{
		if (error_info && error_info->error_id != 0)
		{
			if (error_info->error_id == 11000350) {
				// 没有记录
				std::cout << "Completed." << std::endl;
				return;
			}
			OnError(error_info);
			return;
		}
		m_vAccounts.push_back(*trading_account);
		if (is_last)
			std::cout << "Completed." << std::endl;
	}

	// 报单通知
	virtual void OnOrderEvent(XTPOrderInfo* order_info, XTPRI* error_info, uint64_t session_id) {}

	// 成交通知
	virtual void OnTradeEvent(XTPTradeReport* trade_info, uint64_t session_id) {}

	// 撤单错误应答
	virtual void OnCancelOrderError(XTPOrderCancelInfo* cancel_info, XTPRI* error_info, uint64_t session_id) {}

	virtual void OnQueryStructuredFund(XTPStructuredFundInfo* fund_info, XTPRI* error_info, int request_id, bool is_last, uint64_t session_id) {}

	virtual void OnQueryFundTransfer(XTPFundTransferNotice* fund_transfer_info, XTPRI* error_info, int request_id, bool is_last, uint64_t session_id) {}

	virtual void OnFundTransfer(XTPFundTransferNotice* fund_transfer_info, XTPRI* error_info, uint64_t session_id) {}

	virtual void OnQueryETF(XTPQueryETFBaseRsp* etf_info, XTPRI* error_info, int request_id, bool is_last, uint64_t session_id) {}

	virtual void OnQueryETFBasket(XTPQueryETFComponentRsp* etf_component_info, XTPRI* error_info, int request_id, bool is_last, uint64_t session_id) {}

	virtual void OnQueryIPOInfoList(XTPQueryIPOTickerRsp* ipo_info, XTPRI* error_info, int request_id, bool is_last, uint64_t session_id) {}

	virtual void OnQueryIPOQuotaInfo(XTPQueryIPOQuotaRsp* quota_info, XTPRI* error_info, int request_id, bool is_last, uint64_t session_id) {}

	virtual void OnQueryOptionAuctionInfo(XTPQueryOptionAuctionInfoRsp* option_info, XTPRI* error_info, int request_id, bool is_last, uint64_t session_id) {}

	virtual void OnCreditCashRepay(XTPCrdCashRepayRsp* cash_repay_info, XTPRI* error_info, uint64_t session_id) {}

	virtual void OnQueryCreditCashRepayInfo(XTPCrdCashRepayInfo* cash_repay_info, XTPRI* error_info, int request_id, bool is_last, uint64_t session_id) {}

	virtual void OnQueryCreditFundInfo(XTPCrdFundInfo* fund_info, XTPRI* error_info, int request_id, uint64_t session_id) {}

	virtual void OnQueryCreditDebtInfo(XTPCrdDebtInfo* debt_info, XTPRI* error_info, int request_id, bool is_last, uint64_t session_id) {}

	virtual void OnQueryCreditTickerDebtInfo(XTPCrdDebtStockInfo* debt_info, XTPRI* error_info, int request_id, bool is_last, uint64_t session_id) {}

	virtual void OnQueryCreditAssetDebtInfo(double remain_amount, XTPRI* error_info, int request_id, uint64_t session_id) {}

	virtual void OnQueryCreditTickerAssignInfo(XTPClientQueryCrdPositionStkInfo* assign_info, XTPRI* error_info, int request_id, bool is_last, uint64_t session_id) {}

	virtual void OnQueryCreditExcessStock(XTPClientQueryCrdSurplusStkRspInfo* stock_info, XTPRI* error_info, int request_id, uint64_t session_id) {}


private:
	std::string m_host;
	std::string m_user;
	std::string m_password;
	std::string m_authcode;
	uint64_t m_session_id;

	XTP::API::TraderApi* m_pUserApi;
	std::vector<XTPQueryOrderRsp> m_vOrders;
	std::vector<XTPQueryTradeRsp> m_vTrades;
	std::vector<XTPQueryStkPositionRsp> m_vPositions;
	std::vector<XTPQueryAssetRsp> m_vAccounts;
};


void display_usage()
{
	std::cout << "usage:xtpdump host user password authcode" << std::endl;
	std::cout << "example:xtpdump 122.112.139.0:6101 000001 888888 b8aa7173bba3470e390d787219b2112e" << std::endl;
}


int main(int argc, char* argv[])
{
	std::string host;
	std::string user;
	std::string password;
	std::string authcode;

	if (argc != 5) {
		display_usage();
		return -1;
	}

	int opt;
	while ((opt = getopt(argc, argv, "h:u:p:")) != -1)
	{
		switch (opt)
		{
		case 'h':
			host = optarg;
			break;
		case 'u':
			user = optarg;
			break;
		case 'p':
			password = optarg;
			break;
		case 'a':
			authcode = optarg;
			break;
		case '?':
			display_usage();
			return -1;
		default:
			display_usage();
			return -1;
		}
	}

	if (argc - optind != 4)
	{
		display_usage();
		return -1;
	}

	host = argv[optind++];
	user = argv[optind++];
	password = argv[optind++];
	authcode = argv[optind++];
	MyTraderSpi Spi(host, user, password, authcode);

	// 启动
	if (Spi.Run() < 0)
		return -1;

	getchar();

	return 0;
}
