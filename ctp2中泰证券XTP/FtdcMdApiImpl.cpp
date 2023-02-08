#include "FtdcMdApiImpl.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

#define XTP_CLIENT_ID 80
#define XTP_RECONNECT_TIME 3 // seconds

CThostFtdcMdApi* CThostFtdcMdApi::CreateFtdcMdApi(const char* pszFlowPath, const bool bIsUsingUdp, const bool bIsMulticast)
{
	return new CFtdcMdApiImpl(pszFlowPath);
}

const char *CThostFtdcMdApi::GetApiVersion()
{
#ifdef V6_6_9
	return "V6_6_9";
#elif V6_6_7
	return "V6_6_7";
#elif V6_6_1_P1
	return "V6_6_1_P1";
#elif V6_5_1
	return "6.5.1";
#elif V6_3_19
	return "6.3.19_P1";
#else
	return "6.3.15";
#endif
}

CFtdcMdApiImpl::CFtdcMdApiImpl(const char* pszFlowPath)
{
	memset(&TradingDay, 0, sizeof(TradingDay));
	m_pUserApi = NULL;
	m_pSpi = NULL;
	m_pThread = NULL;
	m_logined = false;
	memset(m_ip, 0x00, sizeof(m_ip));
	m_port = 0;
	const char* path = ".";
	if (pszFlowPath && *pszFlowPath != 0)
		path = pszFlowPath;
	m_pUserApi = XTP::API::QuoteApi::CreateQuoteApi(XTP_CLIENT_ID, path, XTP_LOG_LEVEL_INFO);
	m_pUserApi->RegisterSpi(this);
}

void CFtdcMdApiImpl::Init()
{
	m_pTimer = new boost::asio::deadline_timer(m_io_service, boost::posix_time::seconds(XTP_RECONNECT_TIME)); // 毫秒
	m_pTimer->expires_from_now(boost::posix_time::seconds(XTP_RECONNECT_TIME));
	m_pTimer->async_wait(boost::bind(&CFtdcMdApiImpl::OnTime, this, boost::asio::placeholders::error));
	m_pThread = new std::thread(boost::bind(&boost::asio::io_service::run, &m_io_service));
	if(m_pSpi)
		m_io_service.post(boost::bind(&CThostFtdcMdSpi::OnFrontConnected, m_pSpi));
}

int CFtdcMdApiImpl::Join()
{
	m_pThread->join();
	return 0;
}

void CFtdcMdApiImpl::Release()
{
	m_pSpi = NULL;
	m_io_service.stop();
	m_pUserApi->Release();
	m_pUserApi = NULL;
	delete this;
}

const char *CFtdcMdApiImpl::GetTradingDay()
{
	return m_pUserApi->GetTradingDay();
}

void CFtdcMdApiImpl::RegisterFront(char *pszFrontAddress)
{
	// tcp://ip:port
	// 例：tcp://192.168.1.100:6001

	strncpy(m_ip, pszFrontAddress + 6, strchr(pszFrontAddress + 6, ':') - (pszFrontAddress + 6));
	m_port = atol(strchr(pszFrontAddress + 6, ':') + 1);
	if (strncmp(pszFrontAddress, "udp://", 6) == 0)
		m_protocol = XTP_PROTOCOL_UDP;
	else
		m_protocol = XTP_PROTOCOL_TCP;
}

void CFtdcMdApiImpl::RegisterNameServer(char *pszNsAddress)
{
}

void CFtdcMdApiImpl::RegisterSpi(CThostFtdcMdSpi *pSpi)
{
	m_pSpi = pSpi;
	if (!pSpi)
		m_pUserApi->RegisterSpi(NULL);
}

void CFtdcMdApiImpl::OnTime(const boost::system::error_code& err)
{
	// This function will be called when timer is canceled or time changed.
	if (err) {
		if (err == boost::asio::error::operation_aborted) {
			return;
		}
	}

	if (!m_logined) {
		// 重连
		m_pSpi->OnFrontConnected();
	}

	m_pTimer->expires_from_now(boost::posix_time::seconds(XTP_RECONNECT_TIME));
	m_pTimer->async_wait(boost::bind(&CFtdcMdApiImpl::OnTime, this, boost::asio::placeholders::error));
}

///用户登录请求
int CFtdcMdApiImpl::ReqUserLogin(CThostFtdcReqUserLoginField *pReqUserLogin, int nRequestID)
{
	m_io_service.post(boost::bind(&CFtdcMdApiImpl::HandleReqUserLogin, this, *pReqUserLogin, nRequestID));

	return 0;
}
void CFtdcMdApiImpl::HandleReqUserLogin(CThostFtdcReqUserLoginField& ReqUserLogin, int nRequestID)
{
	CThostFtdcRspUserLoginField RspUserLogin = { 0 };
	CThostFtdcRspInfoField RspInfo = { 0 };

	if (m_pUserApi->Login(m_ip, m_port, ReqUserLogin.UserID, ReqUserLogin.Password, m_protocol) != 0) {
		// 登录失败
		if (m_pSpi) {
			XTPRI* err = m_pUserApi->GetApiLastError();
			RspInfo.ErrorID = err->error_id;
			strncpy(RspInfo.ErrorMsg, err->error_msg, sizeof(RspInfo.ErrorMsg) - 1);
			m_pSpi->OnRspUserLogin(&RspUserLogin, &RspInfo, nRequestID, true);

			m_pSpi->OnFrontDisconnected(0);

			// 重连定时器
			m_pTimer->expires_from_now(boost::posix_time::seconds(XTP_RECONNECT_TIME));
			m_pTimer->async_wait(boost::bind(&CFtdcMdApiImpl::OnTime, this, boost::asio::placeholders::error));
		}
		return;
	}

	// 登录成功
	m_logined = true;

	struct tm* t;
	time_t tt;
	tt = time(NULL);
	t = localtime(&tt);
	strncpy(TradingDay, m_pUserApi->GetTradingDay(), sizeof(TradingDay) - 1);
	//snprintf(TradingDay, sizeof(TradingDay), "%04d%02d%02d", t->tm_year + 1900, t->tm_mon + 1, t->tm_mday);

	if (m_pSpi) {
		strncpy(RspUserLogin.UserID, ReqUserLogin.UserID, sizeof(RspUserLogin.UserID) - 1);
		strcpy(RspUserLogin.TradingDay, TradingDay);
		snprintf(RspUserLogin.LoginTime, sizeof(RspUserLogin.LoginTime), "%02d:%02d:%02d", t->tm_hour, t->tm_min, t->tm_sec);
		strncpy(RspUserLogin.CZCETime, RspUserLogin.LoginTime, sizeof(RspUserLogin.CZCETime) - 1);
		strncpy(RspUserLogin.SHFETime, RspUserLogin.LoginTime, sizeof(RspUserLogin.SHFETime) - 1);
		strncpy(RspUserLogin.DCETime, RspUserLogin.LoginTime, sizeof(RspUserLogin.DCETime) - 1);
		strncpy(RspUserLogin.FFEXTime, RspUserLogin.LoginTime, sizeof(RspUserLogin.FFEXTime) - 1);
		strncpy(RspUserLogin.INETime, RspUserLogin.LoginTime, sizeof(RspUserLogin.INETime) - 1);
		RspUserLogin.FrontID = 0;
		RspUserLogin.SessionID = 0;
		strncpy(RspUserLogin.BrokerID, ReqUserLogin.BrokerID, sizeof(RspUserLogin.BrokerID) - 1);
		strncpy(RspUserLogin.MaxOrderRef, "1", sizeof(RspUserLogin.MaxOrderRef) - 1);
		strncpy(RspUserLogin.SystemName, "XTP", sizeof(RspUserLogin.SystemName) - 1);
		m_pSpi->OnRspUserLogin(&RspUserLogin, &RspInfo, nRequestID, true);
	}
}

///订阅行情
int CFtdcMdApiImpl::SubscribeMarketData(char* ppInstrumentID[], int nCount)
{
	int r = 0;

	for (int i = 0; i < nCount; i++) {
		char* InstrumentID[1] = { ppInstrumentID[i] };
		if (memcmp(InstrumentID[0], "60", 2) == 0
			|| memcmp(InstrumentID[0], "68", 2) == 0
			|| memcmp(InstrumentID[0], "50", 2) == 0
			|| memcmp(InstrumentID[0], "51", 2) == 0
			|| memcmp(InstrumentID[0], "56", 2) == 0
			|| memcmp(InstrumentID[0], "58", 2) == 0)
			r = m_pUserApi->SubscribeMarketData(InstrumentID, 1, XTP_EXCHANGE_SH);
		else if (memcmp(InstrumentID[0], "00", 2) == 0
			|| memcmp(InstrumentID[0], "30", 2) == 0
			|| memcmp(InstrumentID[0], "159", 3) == 0)
			r = m_pUserApi->SubscribeMarketData(InstrumentID, 1, XTP_EXCHANGE_SZ);
		else {
			r = m_pUserApi->SubscribeMarketData(InstrumentID, 1, XTP_EXCHANGE_SH);
			r = m_pUserApi->SubscribeMarketData(InstrumentID, 1, XTP_EXCHANGE_SZ);
		}
	}
	return r;
}

///退订行情
int CFtdcMdApiImpl::UnSubscribeMarketData(char* ppInstrumentID[], int nCount)
{
	int r = 0;

	for (int i = 0; i < nCount; i++) {
		char* InstrumentID[1] = { ppInstrumentID[i] };
		if (memcmp(InstrumentID[0], "60", 2) == 0
			|| memcmp(InstrumentID[0], "68", 2) == 0
			|| memcmp(InstrumentID[0], "50", 2) == 0
			|| memcmp(InstrumentID[0], "51", 2) == 0
			|| memcmp(InstrumentID[0], "56", 2) == 0
			|| memcmp(InstrumentID[0], "58", 2) == 0)
			r=m_pUserApi->UnSubscribeMarketData(InstrumentID, 1, XTP_EXCHANGE_SH);
		else if (memcmp(InstrumentID[0], "00", 2) == 0
			|| memcmp(InstrumentID[0], "30", 2) == 0
			|| memcmp(InstrumentID[0], "159", 3) == 0)
			r = m_pUserApi->UnSubscribeMarketData(InstrumentID, 1, XTP_EXCHANGE_SZ);
		else {
			r = m_pUserApi->UnSubscribeMarketData(InstrumentID, 1, XTP_EXCHANGE_SH);
			r = m_pUserApi->UnSubscribeMarketData(InstrumentID, 1, XTP_EXCHANGE_SZ);
		}
	}
	return r;
}

///用户退出请求
int CFtdcMdApiImpl::ReqUserLogout(CThostFtdcUserLogoutField *pUserLogout, int nRequestID)
{
	m_io_service.post(boost::bind(&CFtdcMdApiImpl::HandleReqUserLogout, this, *pUserLogout, nRequestID));

	return 0;
}

void CFtdcMdApiImpl::HandleReqUserLogout(CThostFtdcUserLogoutField& UserLogout, int nRequestID)
{
	m_pUserApi->Logout();
	if (m_pSpi) {
		CThostFtdcUserLogoutField RspUserLogout = { 0 };
		CThostFtdcRspInfoField RspInfo = { 0 };
		strncpy(RspUserLogout.UserID, UserLogout.UserID, sizeof(RspUserLogout.UserID) - 1);
		strncpy(RspUserLogout.BrokerID, UserLogout.BrokerID, sizeof(RspUserLogout.BrokerID) - 1);
		m_pSpi->OnRspUserLogout(&RspUserLogout, &RspInfo, nRequestID, true);
	}
}

void CFtdcMdApiImpl::OnDisconnected(int reason)
{
	m_logined = false;

	if (m_pSpi) {
		m_pSpi->OnFrontDisconnected(reason);

		// 断线立即重连
		m_pSpi->OnFrontConnected();
	}
}

///行情订阅应答
void CFtdcMdApiImpl::OnSubMarketData(XTPST* ticker, XTPRI* error_info, bool is_last)
{
	if(m_pSpi)
	{

		CThostFtdcRspInfoField*  pThostRspInfo=NULL;
		CThostFtdcRspInfoField  ThostRspInfo;

		if(error_info)
		{
			memset(&ThostRspInfo,0,sizeof(ThostRspInfo));
			ThostRspInfo.ErrorID = error_info->error_id;
			strncpy(ThostRspInfo.ErrorMsg,error_info->error_msg,sizeof(ThostRspInfo.ErrorMsg)-1);
			pThostRspInfo = &ThostRspInfo;
		}

		CThostFtdcSpecificInstrumentField*  pThostSpecificInstrument =NULL;
		CThostFtdcSpecificInstrumentField  ThostSpecificInstrument;
		if(ticker)
		{		
			memset(&ThostSpecificInstrument,0,sizeof(ThostSpecificInstrument));
			strncpy(ThostSpecificInstrument.InstrumentID, ticker->ticker,sizeof(ThostSpecificInstrument.InstrumentID)-1);
			pThostSpecificInstrument = &ThostSpecificInstrument;
		}

		m_pSpi->OnRspSubMarketData(pThostSpecificInstrument, pThostRspInfo, 0, true);
	}
}

///行情退订应答
void CFtdcMdApiImpl::OnUnSubMarketData(XTPST* ticker, XTPRI* error_info, bool is_last)
{
	if (m_pSpi)
	{

		CThostFtdcRspInfoField* pThostRspInfo = NULL;
		CThostFtdcRspInfoField  ThostRspInfo;

		if (error_info)
		{
			memset(&ThostRspInfo, 0, sizeof(ThostRspInfo));
			ThostRspInfo.ErrorID = error_info->error_id;
			strncpy(ThostRspInfo.ErrorMsg, error_info->error_msg, sizeof(ThostRspInfo.ErrorMsg) - 1);
			pThostRspInfo = &ThostRspInfo;
		}

		CThostFtdcSpecificInstrumentField* pThostSpecificInstrument = NULL;
		CThostFtdcSpecificInstrumentField  ThostSpecificInstrument;
		if (ticker)
		{
			memset(&ThostSpecificInstrument, 0, sizeof(ThostSpecificInstrument));
			strncpy(ThostSpecificInstrument.InstrumentID, ticker->ticker, sizeof(ThostSpecificInstrument.InstrumentID) - 1);
			pThostSpecificInstrument = &ThostSpecificInstrument;
		}

		m_pSpi->OnRspUnSubMarketData(pThostSpecificInstrument, pThostRspInfo, 0, true);
	}
}

///行情退订应答
void CFtdcMdApiImpl::OnDepthMarketData(XTPMD* market_data, int64_t bid1_qty[], int32_t bid1_count, int32_t max_bid1_count, int64_t ask1_qty[], int32_t ask1_count, int32_t max_ask1_count)
{
	if (m_pSpi)
	{
		CThostFtdcDepthMarketDataField  ThostDepthMarketData;
		memset(&ThostDepthMarketData, 0, sizeof(ThostDepthMarketData));
		strncpy(ThostDepthMarketData.InstrumentID, market_data->ticker, sizeof(ThostDepthMarketData.InstrumentID) - 1);
		if (market_data->exchange_id == XTP_EXCHANGE_SH)
			strncpy(ThostDepthMarketData.ExchangeID, "SSE", sizeof(ThostDepthMarketData.ExchangeID) - 1);
		else if (market_data->exchange_id == XTP_EXCHANGE_SZ)
			strncpy(ThostDepthMarketData.ExchangeID, "SZSE", sizeof(ThostDepthMarketData.ExchangeID) - 1);
		ThostDepthMarketData.LastPrice = market_data->last_price;
		ThostDepthMarketData.Volume = market_data->qty;
		ThostDepthMarketData.Turnover = market_data->turnover;
		ThostDepthMarketData.OpenPrice = market_data->open_price;
		ThostDepthMarketData.HighestPrice = market_data->high_price;
		ThostDepthMarketData.LowestPrice = market_data->low_price;
		ThostDepthMarketData.UpperLimitPrice = market_data->upper_limit_price;
		ThostDepthMarketData.LowerLimitPrice = market_data->lower_limit_price;
		ThostDepthMarketData.OpenInterest = market_data->total_long_positon;
		ThostDepthMarketData.PreClosePrice = market_data->pre_close_price;
		ThostDepthMarketData.SettlementPrice = market_data->settl_price;
		ThostDepthMarketData.PreSettlementPrice = market_data->pre_settl_price;
		ThostDepthMarketData.PreOpenInterest = market_data->pre_total_long_positon;
		ThostDepthMarketData.ClosePrice = market_data->close_price;
		ThostDepthMarketData.AveragePrice = market_data->avg_price;
		ThostDepthMarketData.BidPrice1 = market_data->bid[0];
		ThostDepthMarketData.BidVolume1 = market_data->bid_qty[0];
		ThostDepthMarketData.AskPrice1 = market_data->ask[0];
		ThostDepthMarketData.AskVolume1 = market_data->ask_qty[0];
		int day = market_data->data_time / 1000000000;
		int t = market_data->data_time % 1000000000 / 1000;
		ThostDepthMarketData.UpdateMillisec = market_data->data_time % 1000;
		snprintf(ThostDepthMarketData.ActionDay, sizeof(ThostDepthMarketData.ActionDay), "%d", day);
		snprintf(ThostDepthMarketData.UpdateTime, sizeof(ThostDepthMarketData.UpdateTime), "%02d:%02d:%02d", t/10000, t%10000/100, t%100);
		strncpy(ThostDepthMarketData.TradingDay, ThostDepthMarketData.ActionDay, sizeof(ThostDepthMarketData.TradingDay) - 1);
		ThostDepthMarketData.BidPrice2 = market_data->bid[1];
		ThostDepthMarketData.BidVolume2 = market_data->bid_qty[1];
		ThostDepthMarketData.AskPrice2 = market_data->ask[1];
		ThostDepthMarketData.AskVolume2 = market_data->ask_qty[1];
		ThostDepthMarketData.BidPrice3 = market_data->bid[2];
		ThostDepthMarketData.BidVolume3 = market_data->bid_qty[2];
		ThostDepthMarketData.AskPrice3 = market_data->ask[2];
		ThostDepthMarketData.AskVolume3 = market_data->ask_qty[2];
		ThostDepthMarketData.BidPrice4 = market_data->bid[3];
		ThostDepthMarketData.BidVolume4 = market_data->bid_qty[3];
		ThostDepthMarketData.AskPrice4 = market_data->ask[3];
		ThostDepthMarketData.AskVolume4 = market_data->ask_qty[3];
		ThostDepthMarketData.BidPrice5 = market_data->bid[4];
		ThostDepthMarketData.BidVolume5 = market_data->bid_qty[4];
		ThostDepthMarketData.AskPrice5 = market_data->ask[4];
		ThostDepthMarketData.AskVolume5 = market_data->ask_qty[4];
		m_pSpi->OnRtnDepthMarketData(&ThostDepthMarketData);
	}
}
