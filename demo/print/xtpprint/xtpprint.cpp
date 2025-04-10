#include <stdio.h>
#include <string>
#include "xtp_trader_api.h"

using namespace XTP::API;
#define XTP_CLIENT_ID 83

class CApplication : public TraderSpi
{
public:
	CApplication(std::string host, std::string user, std::string password, std::string authcode):
		m_host(host),
		m_user(user),
		m_password(password),
		m_authcode(authcode)
	{
		m_pUserApi = TraderApi::CreateTraderApi(XTP_CLIENT_ID, ".", XTP_LOG_LEVEL_WARNING);
		m_pUserApi->RegisterSpi(this);
		m_pUserApi->SetSoftwareVersion("1.0"); //设定此软件的开发版本号，用户自定义
		m_pUserApi->SetSoftwareKey(m_authcode.c_str());//设定用户的开发代码，在XTP申请开户时，由xtp人员提供
		m_pUserApi->SetHeartBeatInterval(16);//设定交易服务器超时时间，单位为秒，此为1.1.16新增接口
	}

	~CApplication()
	{
	}

	const std::string time_to_string(int64_t tm)
	{
		std::string d,t,dt;
		d = std::to_string(tm / 1000000000);
		tm %= 1000000000;
		tm /= 1000;
		t = std::to_string(tm/10000)+":"+std::to_string(tm%10000/100) + ":" + std::to_string(tm % 100);
		dt = d + " " + t;
		return std::move(dt);
	}
	int Run()
	{
		std::string ip = m_host.substr(0, m_host.find(':'));
		std::string port = m_host.substr(m_host.find(':')+1);
		m_session_id = m_pUserApi->Login(ip.c_str(), atol(port.c_str()), m_user.c_str(), m_password.c_str(), XTP_PROTOCOL_TCP);
		if (!m_session_id) {
			printf("Login failed.\n");
			OnError(m_pUserApi->GetApiLastError());
			return -1;
		}
		printf("Login succeeded.\n");

		// 查询订单
		printf("Query Order ...\n");
		XTPQueryOrderReq Req = { 0 };
		m_pUserApi->QueryOrders(&Req, m_session_id, 0);

		return 0;
	}

	virtual void OnDisconnected(uint64_t session_id, int reason)
	{
		printf("Disconnected.\n");
	}

	///错误响应
	virtual void OnError(XTPRI* error_info)
	{
		if (!error_info)
			return;
		printf("Error: %d - %s\n",error_info->error_id, error_info->error_msg);
	}

	virtual void OnQueryOrder(XTPQueryOrderRsp* order_info, XTPRI* error_info, int request_id, bool is_last, uint64_t session_id)
	{
		if (error_info && error_info->error_id != 0)
		{
			if (error_info->error_id == 11000350) {
				// 没有记录
				printf("Query Trade ...\n");
				XTPQueryTraderReq Req = { 0 };
				if (m_pUserApi->QueryTrades(&Req, m_session_id, 0)) {
					OnError(m_pUserApi->GetApiLastError());
					return;
				}

				return;
			}
			OnError(error_info);
			return;
		}
		printf("order_xtp_id:%I64u,order_client_id:%u,ticker:%s,quantity:%I64d,price:%lf,qty_left:%I64d,order_status:%s,insert_time:%s\n", order_info->order_xtp_id, order_info->order_client_id, order_info->ticker, order_info->quantity, order_info->price, order_info->qty_left, order_status_desc[order_info->order_status], time_to_string(order_info->insert_time).c_str());

		if (is_last) {
			printf("Query Trade ...\n");
			XTPQueryTraderReq Req = { 0 };
			if (m_pUserApi->QueryTrades(&Req, m_session_id, 0)) {
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
				printf("Query Position ...\n");
				if (m_pUserApi->QueryPosition(NULL, m_session_id, 0)) {
					OnError(m_pUserApi->GetApiLastError());
					return;
				}
			}
			OnError(error_info);
			return;
		}
		printf("order_xtp_id:%I64u,ticker:%s,quantity:%I64d,price:%lf,exec_id:%s,trade_time:%s\n", trade_info->order_xtp_id, trade_info->ticker, trade_info->quantity, trade_info->price, trade_info->exec_id, time_to_string(trade_info->trade_time).c_str());

		if (is_last) {
			printf("Query Position ...\n");
			if (m_pUserApi->QueryPosition(NULL, m_session_id, 0)) {
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
				printf("Query Asset ...\n");
				if (m_pUserApi->QueryAsset(m_session_id, 0)) {
					OnError(m_pUserApi->GetApiLastError());
					return;
				}
			}
			OnError(error_info);
			return;
		}
		printf("ticker:%s,total_qty:%I64d,sellable_qty:%I64d,avg_price:%lf,yesterday_position:%I64d\n", investor_position->ticker, investor_position->total_qty, investor_position->sellable_qty, investor_position->avg_price, investor_position->yesterday_position);
		if (is_last) {
			printf("Query Asset ...\n");
			if (m_pUserApi->QueryAsset(m_session_id, 0)) {
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
				printf("Query completed.\n");
				return;
			}
			OnError(error_info);
			return;
		}
		printf("banlance:%lf,buying_power:%lf,withholding_amount:%lf\n", trading_account->banlance, trading_account->buying_power, trading_account->withholding_amount);
		if (is_last)
			printf("Query completed.\n");
	}

	const char* order_status_desc[XTP_ORDER_STATUS_UNKNOWN+1] = {"初始化","全部成交","部分成交","部分撤单","未成交","已撤单","已拒绝","未知订单状态"};

	// 报单通知
	virtual void OnOrderEvent(XTPOrderInfo* order_info, XTPRI* error_info, uint64_t session_id)
	{
		printf("order_xtp_id:%I64u,order_client_id:%u,ticker:%s,quantity:%I64d,price:%lf,qty_left:%I64d,order_status:%s,insert_time:%s\n", order_info->order_xtp_id, order_info->order_client_id, order_info->ticker, order_info->quantity, order_info->price, order_info->qty_left, order_status_desc[order_info->order_status], time_to_string(order_info->insert_time).c_str());
	}

	// 成交通知
	virtual void OnTradeEvent(XTPTradeReport* trade_info, uint64_t session_id)
	{
		printf("order_xtp_id:%I64u,ticker:%s,quantity:%I64d,price:%lf,exec_id:%s,trade_time:%I64d\n", trade_info->order_xtp_id, trade_info->ticker, trade_info->quantity, trade_info->price, trade_info->exec_id, trade_info->trade_time);
	}

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
};


void display_usage()
{
	printf("usage:xtpprint host user password authcode\n");
	printf("example:xtpprint 122.112.139.0:6101 000001 888888 b8aa7173bba3470e390d787219b2112e\n");
}


int main(int argc, char* argv[])
{
	if (argc != 5) {
		display_usage();
		return -1;
	}

	CApplication Spi(argv[1], argv[2], argv[3], argv[4]);

	// 启动
	if (Spi.Run() < 0)
		return -1;

	getchar();

	return 0;
}
