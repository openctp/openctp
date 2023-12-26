#include <iostream>
#include <fstream>
#include "FtdcTraderApiImpl.h"
#include "boost/algorithm/string.hpp"

#define XTP_CLIENT_ID 80
#define XTP_RECONNECT_TIME 3 // seconds

#define EXCHANGE_SH "SSE"
#define EXCHANGE_SZ "SZSE"

CThostFtdcTraderApi *CThostFtdcTraderApi::CreateFtdcTraderApi(const char *pszFlowPath)
{
	return new CFtdcTraderApiImpl(pszFlowPath);
}

const char *CThostFtdcTraderApi::GetApiVersion()
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

CFtdcTraderApiImpl::CFtdcTraderApiImpl(const char *pszFlowPath)
{
	m_pUserApi = NULL;
	m_pSpi = NULL;
	memset(TradingDay, 0x00, sizeof(TradingDay));
	memset(m_BrokerID,0x00,sizeof(m_BrokerID));
	memset(m_UserID, 0x00, sizeof(m_UserID));
	memset(m_InvestorID, 0x00, sizeof(m_InvestorID));
	ThostRspInfoNotSupported.ErrorID = 99;
	strncpy(ThostRspInfoNotSupported.ErrorMsg, "Not supported",sizeof(ThostRspInfoNotSupported.ErrorMsg)-1);
	m_pthread = NULL;
	m_logined = false;
	m_ctp_sys_orderref = 1;
	m_ctp_sessionid = 0; // 虚拟ID
	m_ctp_orderref = 1;
	m_xtp_sessionid = 0;
	memset(m_ip, 0x00, sizeof(m_ip));
	m_port = 0;
	const char* path = ".";
	if (pszFlowPath && *pszFlowPath != 0)
		path = pszFlowPath;
	m_pUserApi = XTP::API::TraderApi::CreateTraderApi(XTP_CLIENT_ID, path, XTP_LOG_LEVEL_WARNING);
	m_pUserApi->RegisterSpi(this);
}

const std::string CFtdcTraderApiImpl::time_to_string(int64_t tm)
{
	tm %= 1000000000;
	tm /= 1000;
	uint32_t t=tm;
	char str[9];
	sprintf(str, "%02u:%02u:%02u", t / 10000, t % 10000 / 100, t % 100);
	std::string s = str;
	return std::move(s);
}

void CFtdcTraderApiImpl::Init()
{
	m_pTimer = new boost::asio::deadline_timer(m_io_service, boost::posix_time::seconds(XTP_RECONNECT_TIME)); // 毫秒
	m_pTimer->expires_from_now(boost::posix_time::seconds(XTP_RECONNECT_TIME));
	m_pTimer->async_wait(boost::bind(&CFtdcTraderApiImpl::OnTime, this, boost::asio::placeholders::error));
	m_pthread = new std::thread(boost::bind(&boost::asio::io_service::run, &m_io_service));
	m_io_service.post(boost::bind(&CThostFtdcTraderSpi::OnFrontConnected, m_pSpi));
}

int CFtdcTraderApiImpl::Join()
{
	m_pthread->join();
	return 0;
}

void CFtdcTraderApiImpl::Release()
{
	m_pSpi = NULL;
	m_io_service.stop();
	m_pUserApi->Release();
	m_pUserApi = NULL;
	delete this;
}

const char *CFtdcTraderApiImpl::GetTradingDay()
{
	return m_pUserApi->GetTradingDay();
}

void CFtdcTraderApiImpl::RegisterFront(char *pszFrontAddress)
{
	// tcp://ip:port
	// 例：tcp://122.112.139.0:6101

	strncpy(m_ip, pszFrontAddress + 6, strchr(pszFrontAddress + 6, ':') - (pszFrontAddress + 6));
	m_port = atol(strchr(pszFrontAddress + 6, ':') + 1);
	if (strncmp(pszFrontAddress, "udp://", 6) == 0)
		m_protocol = XTP_PROTOCOL_UDP;
	else
		m_protocol = XTP_PROTOCOL_TCP;
}

void CFtdcTraderApiImpl::RegisterNameServer(char *pszNsAddress)
{
}

void CFtdcTraderApiImpl::RegisterSpi(CThostFtdcTraderSpi *pSpi)
{
	m_pSpi = pSpi;
	if(!pSpi && m_pUserApi)
		m_pUserApi->RegisterSpi(NULL);
}

void CFtdcTraderApiImpl::SubscribePrivateTopic(THOST_TE_RESUME_TYPE nResumeType)
{
}

void CFtdcTraderApiImpl::SubscribePublicTopic(THOST_TE_RESUME_TYPE nResumeType)
{
	m_pUserApi->SubscribePublicTopic((XTP_TE_RESUME_TYPE)nResumeType);
}

void CFtdcTraderApiImpl::OnTime(const boost::system::error_code& err)
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
	m_pTimer->async_wait(boost::bind(&CFtdcTraderApiImpl::OnTime, this, boost::asio::placeholders::error));
}

///用户登录请求
int CFtdcTraderApiImpl::ReqUserLogin(CThostFtdcReqUserLoginField *pReqUserLogin, int nRequestID)
{
	m_io_service.post(boost::bind(&CFtdcTraderApiImpl::HandleReqUserLogin, this, *pReqUserLogin, nRequestID));

	return 0;
}

void CFtdcTraderApiImpl::HandleReqUserLogin(CThostFtdcReqUserLoginField& ReqUserLogin, int nRequestID)
{
	CThostFtdcRspUserLoginField RspUserLogin = { 0 };
	CThostFtdcRspInfoField RspInfo = { 0 };

	strncpy(RspUserLogin.UserID, ReqUserLogin.UserID, sizeof(RspUserLogin.UserID) - 1);
	strncpy(RspUserLogin.BrokerID, ReqUserLogin.BrokerID, sizeof(RspUserLogin.BrokerID) - 1);
	if (!m_pUserApi) {
		// 需要先调用Auth接口
		RspInfo.ErrorID = 1;
		strncpy(RspInfo.ErrorMsg, "请先调用ReqAuthenticate接口进行终端验证", sizeof(RspInfo.ErrorMsg) - 1);
		m_pSpi->OnRspUserLogin(&RspUserLogin, &RspInfo, nRequestID, true);
		return;
	}
	if ((m_xtp_sessionid = m_pUserApi->Login(m_ip, m_port, ReqUserLogin.UserID, ReqUserLogin.Password, m_protocol)) == 0) {
		// 登录失败
		if (m_pSpi) {
			XTPRI* err = m_pUserApi->GetApiLastError();
			RspInfo.ErrorID = err->error_id;
			strncpy(RspInfo.ErrorMsg, err->error_msg, sizeof(RspInfo.ErrorMsg) - 1);
			m_pSpi->OnRspUserLogin(&RspUserLogin, &RspInfo, nRequestID, true);

			m_pSpi->OnFrontDisconnected(0);

			// 重连定时器
			m_pTimer->expires_from_now(boost::posix_time::seconds(3));
			m_pTimer->async_wait(boost::bind(&CFtdcTraderApiImpl::OnTime, this, boost::asio::placeholders::error));
		}
		return;
	}

	// 登录成功
	m_logined = true;

	strncpy(m_BrokerID, ReqUserLogin.BrokerID, sizeof(m_BrokerID) - 1);
	strncpy(m_UserID, ReqUserLogin.UserID, sizeof(m_UserID) - 1);
	strncpy(m_InvestorID, ReqUserLogin.UserID, sizeof(m_InvestorID) - 1);
	m_ctp_orderref = 1;
	m_ctp_sessionid++;

	struct tm* t;
	time_t tt;
	tt = time(NULL);
	t = localtime(&tt);
	strncpy(TradingDay, m_pUserApi->GetTradingDay(), sizeof(TradingDay) - 1);
	//snprintf(TradingDay, sizeof(TradingDay), "%04d%02d%02d", t->tm_year + 1900, t->tm_mon + 1, t->tm_mday);

	if (m_pSpi) {
		strncpy(RspUserLogin.BrokerID, ReqUserLogin.BrokerID, sizeof(RspUserLogin.BrokerID) - 1);
		strncpy(RspUserLogin.UserID, ReqUserLogin.UserID, sizeof(RspUserLogin.UserID) - 1);
		strcpy(RspUserLogin.TradingDay, TradingDay);
		snprintf(RspUserLogin.LoginTime, sizeof(RspUserLogin.LoginTime), "%02d:%02d:%02d", t->tm_hour, t->tm_min, t->tm_sec);
		strncpy(RspUserLogin.CZCETime, RspUserLogin.LoginTime, sizeof(RspUserLogin.CZCETime) - 1);
		strncpy(RspUserLogin.SHFETime, RspUserLogin.LoginTime, sizeof(RspUserLogin.SHFETime) - 1);
		strncpy(RspUserLogin.DCETime, RspUserLogin.LoginTime, sizeof(RspUserLogin.DCETime) - 1);
		strncpy(RspUserLogin.FFEXTime, RspUserLogin.LoginTime, sizeof(RspUserLogin.FFEXTime) - 1);
		strncpy(RspUserLogin.INETime, RspUserLogin.LoginTime, sizeof(RspUserLogin.INETime) - 1);
		RspUserLogin.FrontID = 0;
		RspUserLogin.SessionID = m_ctp_sessionid;
		strncpy(RspUserLogin.MaxOrderRef, "1", sizeof(RspUserLogin.MaxOrderRef) - 1);
		strncpy(RspUserLogin.SystemName, "XTP", sizeof(RspUserLogin.SystemName) - 1);
		m_pSpi->OnRspUserLogin(&RspUserLogin, &RspInfo, nRequestID, true);
	}
}

///用户退出请求
int CFtdcTraderApiImpl::ReqUserLogout(CThostFtdcUserLogoutField *pUserLogout, int nRequestID)
{
	m_io_service.post(boost::bind(&CFtdcTraderApiImpl::HandleReqUserLogout, this, *pUserLogout, nRequestID));

	return 0;
}

void CFtdcTraderApiImpl::HandleReqUserLogout(CThostFtdcUserLogoutField& UserLogout, int nRequestID)
{
	m_pUserApi->Logout(m_xtp_sessionid);
	if (m_pSpi) {
		CThostFtdcUserLogoutField RspUserLogout = { 0 };
		CThostFtdcRspInfoField RspInfo = { 0 };
		strncpy(RspUserLogout.UserID, UserLogout.UserID, sizeof(RspUserLogout.UserID) - 1);
		strncpy(RspUserLogout.BrokerID, UserLogout.BrokerID, sizeof(RspUserLogout.BrokerID) - 1);
		m_pSpi->OnRspUserLogout(&RspUserLogout, &RspInfo, nRequestID, true);
	}
}

///用户密码修改请求
int CFtdcTraderApiImpl::ReqUserPasswordUpdate(CThostFtdcUserPasswordUpdateField *pUserPasswordUpdate, int nRequestID)
{
	m_io_service.post(boost::bind(&CFtdcTraderApiImpl::HandleReqUserPasswordUpdate, this, *pUserPasswordUpdate, nRequestID));

	return 0;
}
void CFtdcTraderApiImpl::HandleReqUserPasswordUpdate(CThostFtdcUserPasswordUpdateField& UserPasswordUpdate, int nRequestID)
{
	if(m_pSpi)
		m_pSpi->OnRspUserPasswordUpdate(&UserPasswordUpdate, &ThostRspInfoNotSupported, nRequestID, true);
}

///报单录入请求
int CFtdcTraderApiImpl::ReqOrderInsert(CThostFtdcInputOrderField* pInputOrder, int nRequestID)
{
	m_io_service.post(boost::bind(&CFtdcTraderApiImpl::HandleReqOrderInsert, this, *pInputOrder, nRequestID));
	return 0;
}
void CFtdcTraderApiImpl::HandleReqOrderInsert(CThostFtdcInputOrderField& InputOrder, int nRequestID)
{
	XTPOrderInsertInfo Req;
	memset(&Req, 0, sizeof(Req));
	if (strcmp(InputOrder.ExchangeID, "SSE") == 0) {
		Req.market = XTP_MKT_SH_A;
	}
	else if (strcmp(InputOrder.ExchangeID, "SZSE") == 0) {
		Req.market = XTP_MKT_SZ_A;
	}

	strncpy(Req.ticker, InputOrder.InstrumentID,sizeof(Req.ticker)-1);
	Req.order_client_id = atol(InputOrder.OrderRef);
	Req.price_type = InputOrder.OrderPriceType == THOST_FTDC_OPT_AnyPrice ? XTP_PRICE_BEST5_OR_CANCEL : XTP_PRICE_LIMIT;
	Req.side = InputOrder.Direction== THOST_FTDC_D_Buy? XTP_SIDE_BUY : XTP_SIDE_SELL;
	Req.price = InputOrder.LimitPrice;
	Req.quantity = InputOrder.VolumeTotalOriginal;
	Req.business_type = XTP_BUSINESS_TYPE_CASH;
	Req.position_effect = XTP_POSITION_EFFECT_INIT;

	uint64_t xtp_order_id = m_pUserApi->InsertOrder(&Req, m_xtp_sessionid);
	if (xtp_order_id == 0) {
		// 下单失败
		if (m_pSpi) {
			CThostFtdcRspInfoField  RspInfo;

			memset(&RspInfo, 0, sizeof(RspInfo));
			XTPRI* err = m_pUserApi->GetApiLastError();
			RspInfo.ErrorID = err->error_id;
			strncpy(RspInfo.ErrorMsg, err->error_msg, sizeof(RspInfo.ErrorMsg) - 1);

			m_pSpi->OnRspOrderInsert(&InputOrder, &RspInfo, nRequestID, true);
		}
		return;
	}
	// 下单成功，返回单号
	uint32_t OrderRef = atol(InputOrder.OrderRef);
	if (OrderRef == 0) {
		// 自动编号
		OrderRef=m_ctp_orderref++;
	}
	uint64_t ctp_order_id = m_ctp_sessionid;
	ctp_order_id = ctp_order_id << 32;
	ctp_order_id += OrderRef;
	m_mOrderRefToXtpID[ctp_order_id] = xtp_order_id;
	m_mXtpIDToOrderRef[xtp_order_id] = ctp_order_id;
}

///报单操作请求
int CFtdcTraderApiImpl::ReqOrderAction(CThostFtdcInputOrderActionField* pOrderAction, int nRequestID)
{
	m_io_service.post(boost::bind(&CFtdcTraderApiImpl::HandleReqOrderAction, this, *pOrderAction, nRequestID));
	return 0;
}
void CFtdcTraderApiImpl::HandleReqOrderAction(CThostFtdcInputOrderActionField& InputOrderAction, int nRequestID)
{
	uint64_t xtp_order_id = atoll(InputOrderAction.OrderSysID);
	if (xtp_order_id == 0) {
		// 使用FrontID+SessionID+OrderRef==>XtpOrderID
		uint64_t ctp_order_id = InputOrderAction.SessionID;
		ctp_order_id = ctp_order_id << 32;
		ctp_order_id += atol(InputOrderAction.OrderRef);
		auto iter = m_mOrderRefToXtpID.find(ctp_order_id);
		if (iter == m_mOrderRefToXtpID.end())
			return; // 找不到订单
		xtp_order_id = iter->second;
	}
	if (m_pUserApi->CancelOrder(xtp_order_id, m_xtp_sessionid) == 0) {
		// 撤单失败
		if (m_pSpi) {
			CThostFtdcRspInfoField RspInfo;

			memset(&RspInfo, 0, sizeof(RspInfo));
			XTPRI* err = m_pUserApi->GetApiLastError();
			RspInfo.ErrorID = err->error_id;
			strncpy(RspInfo.ErrorMsg, err->error_msg, sizeof(RspInfo.ErrorMsg) - 1);

			m_pSpi->OnRspOrderAction(&InputOrderAction, &RspInfo, nRequestID, true);
		}
		return;
	}
	// 撤单发送成功
}

void CFtdcTraderApiImpl::OnCancelOrderError(XTPOrderCancelInfo* cancel_info, XTPRI* error_info, uint64_t session_id)
{
	if (error_info && error_info->error_id != 0) {
		
		CThostFtdcInputOrderActionField OrderAction = { 0 };
		CThostFtdcInputOrderActionField* pOrderAction = NULL;
		if (cancel_info) {
			strncpy(OrderAction.OrderSysID, std::to_string(cancel_info->order_xtp_id).c_str(),sizeof(OrderAction.OrderSysID));
			OrderAction.OrderActionRef = cancel_info->order_cancel_xtp_id;
			pOrderAction = &OrderAction;
		}

		CThostFtdcRspInfoField RspInfo = { 0 };
		RspInfo.ErrorID = error_info->error_id;
		strncpy(RspInfo.ErrorMsg, error_info->error_msg, sizeof(RspInfo.ErrorMsg) - 1);

		m_pSpi->OnRspOrderAction(pOrderAction, &RspInfo, 0, true);
	}
}

///报单查询请求
int CFtdcTraderApiImpl::ReqQryOrder(CThostFtdcQryOrderField *pQryOrder, int nRequestID)
{
	XTPQueryOrderReq Req = { 0 };
	strncpy(Req.ticker, pQryOrder->InstrumentID, sizeof(Req.ticker) - 1);

	return m_pUserApi->QueryOrders(&Req, m_xtp_sessionid, nRequestID);
}

///成交单查询请求
int CFtdcTraderApiImpl::ReqQryTrade(CThostFtdcQryTradeField *pQryTrade, int nRequestID)
{	
	XTPQueryTraderReq Req = { 0 };
	strncpy(Req.ticker, pQryTrade->InstrumentID, sizeof(Req.ticker) - 1);

	return m_pUserApi->QueryTrades(&Req, m_xtp_sessionid, nRequestID);
}

///可用投资者账户查询请求
int CFtdcTraderApiImpl::ReqQryInvestor(CThostFtdcQryInvestorField* pQryInvestor, int nRequestID)
{
	CThostFtdcInvestorField  ThostInvestor;
	memset(&ThostInvestor, 0, sizeof(CThostFtdcInvestorField));
	strncpy(ThostInvestor.BrokerID, m_BrokerID, sizeof(ThostInvestor.BrokerID) - 1);
	strncpy(ThostInvestor.InvestorID, m_UserID, sizeof(ThostInvestor.InvestorID) - 1);
	strncpy(ThostInvestor.InvestorName, m_UserID, sizeof(ThostInvestor.InvestorName) - 1);
	ThostInvestor.IsActive = 1;

	memset(&ThostRspInfo, 0, sizeof(ThostRspInfo));

	m_io_service.post(boost::bind(&CThostFtdcTraderSpi::OnRspQryInvestor, m_pSpi, &ThostInvestor, &ThostRspInfo, nRequestID, true));
	return 0;
}

///投资者资金账户查询请求
int CFtdcTraderApiImpl::ReqQryTradingAccount(CThostFtdcQryTradingAccountField *pQryTradingAccount, int nRequestID)
{
	return m_pUserApi->QueryAsset(m_xtp_sessionid, nRequestID);
}

//资金账户查询
void CFtdcTraderApiImpl::OnQueryAsset(XTPQueryAssetRsp* trading_account, XTPRI* error_info, int request_id, bool is_last, uint64_t session_id)
{
	if (m_pSpi)
	{
		CThostFtdcTradingAccountField* pCTPTradingAccount = NULL;
		CThostFtdcTradingAccountField CTPTradingAccount;
		if (trading_account &&  trading_account->account_type == XTP_ACCOUNT_NORMAL)
		{
			memset(&CTPTradingAccount, 0, sizeof(CTPTradingAccount));
			strncpy(CTPTradingAccount.AccountID, m_InvestorID, sizeof(CTPTradingAccount.AccountID) - 1);
			CTPTradingAccount.Available = trading_account->buying_power;
			CTPTradingAccount.Withdraw = 0;
			CTPTradingAccount.Deposit = 0;
			strcpy(CTPTradingAccount.CurrencyID, "CNY");
			CTPTradingAccount.FrozenCash = trading_account->withholding_amount;
			CTPTradingAccount.FrozenCommission = 0;
			CTPTradingAccount.WithdrawQuota = trading_account->preferred_amount;
			pCTPTradingAccount = &CTPTradingAccount;
		}
		CThostFtdcRspInfoField* pThostRspInfo = NULL;
		CThostFtdcRspInfoField  ThostRspInfo;
		if (NULL != error_info)
		{
			memset(&ThostRspInfo, 0, sizeof(CThostFtdcRspInfoField));
			ThostRspInfo.ErrorID = error_info->error_id;
			strncpy(ThostRspInfo.ErrorMsg, error_info->error_msg, sizeof(ThostRspInfo.ErrorMsg) - 1);
			pThostRspInfo = &ThostRspInfo;
		}

		m_pSpi->OnRspQryTradingAccount(pCTPTradingAccount, pThostRspInfo, request_id, is_last);
	}
}

///合约查询请求
int CFtdcTraderApiImpl::ReqQryInstrument(CThostFtdcQryInstrumentField *pQryInstrument, int nRequestID)
{
	m_io_service.post(boost::bind(&CFtdcTraderApiImpl::HandleReqQryInstrument, this, *pQryInstrument, nRequestID));

	return 0;
}

///合约查询请求
void CFtdcTraderApiImpl::HandleReqQryInstrument(CThostFtdcQryInstrumentField& QryInstrument, int nRequestID)
{
	try {
		std::ifstream infile("dict.csv");
		std::string line;
		std::vector<std::string> lines;
		while (std::getline(infile, line)) {
			if(line.length())
				lines.push_back(line);
		}
		for (auto iterLine = lines.begin(); iterLine != lines.end(); iterLine++) {
			CThostFtdcInstrumentField* pThostInstrument = NULL;
			CThostFtdcInstrumentField  ThostInstrument;
			memset(&ThostInstrument, 0, sizeof(CThostFtdcInstrumentField));
			std::vector<std::string> fields;
			boost::split(fields, *iterLine, boost::is_any_of(","), boost::token_compress_off);
			size_t col = 0;
			for (auto iter=fields.begin(); iter != fields.end(); iter++) {
				switch (col) {
				case 0:
					strncpy(ThostInstrument.ExchangeID, iter->c_str(), sizeof(ThostInstrument.ExchangeID) - 1);
					break;
				case 1:
					ThostInstrument.ProductClass = *iter->c_str();
					break;
				case 2:
					strncpy(ThostInstrument.InstrumentID, iter->c_str(), sizeof(ThostInstrument.InstrumentID) - 1);
					strncpy(ThostInstrument.ExchangeInstID, iter->c_str(), sizeof(ThostInstrument.ExchangeInstID) - 1);
					break;
				case 3:
					strncpy(ThostInstrument.InstrumentName, iter->c_str(), sizeof(ThostInstrument.InstrumentName) - 1);
					break;
				case 4:
					ThostInstrument.PriceTick = std::stod(*iter);
					break;
				}
				col++;
			}

			ThostInstrument.VolumeMultiple = 1;
			ThostInstrument.IsTrading = true;
			ThostInstrument.PositionType = THOST_FTDC_PT_Net;
			ThostInstrument.PositionDateType = THOST_FTDC_PDT_UseHistory;
			ThostInstrument.OptionsType = THOST_FTDC_CP_CallOptions;
			ThostInstrument.InstLifePhase = '1';
			ThostInstrument.MaxMarginSideAlgorithm = THOST_FTDC_MMSA_NO;
			ThostInstrument.CombinationType = THOST_FTDC_COMBT_Future;
			ThostInstrument.LongMarginRatio = 1.0;
			ThostInstrument.ShortMarginRatio = 1.0;
			strcpy(ThostInstrument.OpenDate, "");
			ThostInstrument.MaxLimitOrderVolume = 0;
			ThostInstrument.MinLimitOrderVolume = 0;
			ThostInstrument.MaxMarketOrderVolume = 0;
			ThostInstrument.MinMarketOrderVolume = 0;
			pThostInstrument = &ThostInstrument;

			m_pSpi->OnRspQryInstrument(pThostInstrument, NULL, nRequestID, iterLine+1 == lines.end());
		}
		infile.close();
	}
	catch (...) {
		CThostFtdcRspInfoField  RspInfo;

		memset(&RspInfo, 0, sizeof(RspInfo));
		ThostRspInfo.ErrorID = 1;
		strncpy(ThostRspInfo.ErrorMsg, "加载合约字典失败！[dict.json]", sizeof(ThostRspInfo.ErrorMsg) - 1);
		m_pSpi->OnRspQryInstrument(nullptr, &RspInfo, nRequestID, true);
		return;
	}
}


///交易所查询请求
int CFtdcTraderApiImpl::ReqQryExchange(CThostFtdcQryExchangeField* pQryExchange, int nRequestID)
{
	m_io_service.post(boost::bind(&CFtdcTraderApiImpl::HandleReqQryExchange, this, *pQryExchange, nRequestID));
	return 0;
}

///交易所查询请求
void CFtdcTraderApiImpl::HandleReqQryExchange(CThostFtdcQryExchangeField& QryExchange, int nRequestID)
{
	CThostFtdcExchangeField  ThostRspExchange[2] = {
		{"SSE","SSE",THOST_FTDC_EXP_Normal},
		{"SZSE","SZSE",THOST_FTDC_EXP_Normal}};
	for (int i = 0; i < 2; i++)
		m_pSpi->OnRspQryExchange(&ThostRspExchange[i], NULL, nRequestID, i == 1);
}

///投资者持仓查询请求
int CFtdcTraderApiImpl::ReqQryInvestorPosition(CThostFtdcQryInvestorPositionField *pQryInvestorPosition, int nRequestID)
{
	XTP_MARKET_TYPE ExchangeID = XTP_MKT_INIT;
	if (strcmp(pQryInvestorPosition->ExchangeID, "SSE") == 0)
		ExchangeID = XTP_MKT_SZ_A;
	else if (strcmp(pQryInvestorPosition->ExchangeID, "SZSE") == 0)
		ExchangeID = XTP_MKT_SH_A;

	const char* InstrumentID = NULL;
	if (*pQryInvestorPosition->InstrumentID != 0)
		InstrumentID = pQryInvestorPosition->InstrumentID;

	return m_pUserApi->QueryPosition(InstrumentID, m_xtp_sessionid, ExchangeID);
}

///投资者手续费率查询请求
int CFtdcTraderApiImpl::ReqQryInstrumentCommissionRate(CThostFtdcQryInstrumentCommissionRateField *pQryInstrumentCommissionRate, int nRequestID)
{
	static CThostFtdcInstrumentCommissionRateField  ThostInvestorFee;
	memset(&ThostInvestorFee,0x00,sizeof(ThostInvestorFee));
	strncpy(ThostInvestorFee.BrokerID,m_BrokerID,sizeof(ThostInvestorFee.BrokerID)-1);
	strncpy(ThostInvestorFee.InvestorID,m_InvestorID,sizeof(ThostInvestorFee.InvestorID)-1);
	strncpy(ThostInvestorFee.ExchangeID, pQryInstrumentCommissionRate->ExchangeID, sizeof(ThostInvestorFee.ExchangeID) - 1);
	strncpy(ThostInvestorFee.InstrumentID,pQryInstrumentCommissionRate->InstrumentID,sizeof(ThostInvestorFee.InstrumentID)-1);
	strncpy(ThostInvestorFee.InvestUnitID, pQryInstrumentCommissionRate->InvestUnitID, sizeof(ThostInvestorFee.InvestUnitID) - 1);
	ThostInvestorFee.OpenRatioByMoney=0.0001;
	ThostInvestorFee.CloseRatioByMoney=0.0001;
	ThostInvestorFee.CloseTodayRatioByMoney=0.0001;
	m_io_service.post(boost::bind(&CThostFtdcTraderSpi::OnRspQryInstrumentCommissionRate, m_pSpi, &ThostInvestorFee, nullptr, nRequestID, true));
	return 0;
}

///投资者保证金率查询请求
int CFtdcTraderApiImpl::ReqQryInstrumentMarginRate(CThostFtdcQryInstrumentMarginRateField *pQryInstrumentMarginRate, int nRequestID)
{
	static CThostFtdcInstrumentMarginRateField ThostInvestorMargin;
	memset(&ThostInvestorMargin,0x00,sizeof(ThostInvestorMargin));
	strncpy(ThostInvestorMargin.BrokerID, pQryInstrumentMarginRate->BrokerID,sizeof(ThostInvestorMargin.BrokerID)-1);
	strncpy(ThostInvestorMargin.InvestorID, pQryInstrumentMarginRate->InvestorID,sizeof(ThostInvestorMargin.InvestorID)-1);
	strncpy(ThostInvestorMargin.InstrumentID,pQryInstrumentMarginRate->InstrumentID,sizeof(ThostInvestorMargin.InstrumentID)-1);
	strncpy(ThostInvestorMargin.ExchangeID, pQryInstrumentMarginRate->ExchangeID, sizeof(ThostInvestorMargin.ExchangeID) - 1);
	strncpy(ThostInvestorMargin.InvestUnitID, pQryInstrumentMarginRate->InvestUnitID, sizeof(ThostInvestorMargin.InvestUnitID) - 1);
	ThostInvestorMargin.HedgeFlag = pQryInstrumentMarginRate->HedgeFlag;
	ThostInvestorMargin.LongMarginRatioByMoney=1.0;
	ThostInvestorMargin.ShortMarginRatioByMoney=1.0;
	m_io_service.post(boost::bind(&CThostFtdcTraderSpi::OnRspQryInstrumentMarginRate, m_pSpi, &ThostInvestorMargin, nullptr, nRequestID, true));
	return 0;
}

///投资者结算结果确认
int CFtdcTraderApiImpl::ReqSettlementInfoConfirm(CThostFtdcSettlementInfoConfirmField *pSettlementInfoConfirm, int nRequestID)
{
	static CThostFtdcSettlementInfoConfirmField ThostSettlementInfoConfirmField;
	memcpy(&ThostSettlementInfoConfirmField,pSettlementInfoConfirm,sizeof(ThostSettlementInfoConfirmField));

	strncpy(ThostSettlementInfoConfirmField.BrokerID,m_BrokerID,sizeof(ThostSettlementInfoConfirmField.BrokerID)-1);
	strncpy(ThostSettlementInfoConfirmField.InvestorID,m_InvestorID,sizeof(ThostSettlementInfoConfirmField.InvestorID)-1);
	strncpy(ThostSettlementInfoConfirmField.AccountID,pSettlementInfoConfirm->AccountID,sizeof(ThostSettlementInfoConfirmField.AccountID)-1);
	struct tm *t;
	time_t tt;
	tt=time(NULL);
	t=localtime(&tt);
	snprintf(ThostSettlementInfoConfirmField.ConfirmDate,sizeof(ThostSettlementInfoConfirmField.ConfirmDate),"%04d%02d%02d", t->tm_year + 1900, t->tm_mon + 1, t->tm_mday);
	snprintf(ThostSettlementInfoConfirmField.ConfirmTime,sizeof(ThostSettlementInfoConfirmField.ConfirmTime),"%02d:%02d:%02d",t->tm_hour,t->tm_min,t->tm_sec);

	m_io_service.post(boost::bind(&CThostFtdcTraderSpi::OnRspSettlementInfoConfirm, m_pSpi, &ThostSettlementInfoConfirmField, nullptr, nRequestID, true));
	return 0;	
}

int CFtdcTraderApiImpl::ReqQryDepthMarketData(CThostFtdcQryDepthMarketDataField *pQryDepthMarketData, int nRequestID)
{
	m_io_service.post(boost::bind(&CThostFtdcTraderSpi::OnRspQryDepthMarketData, m_pSpi, nullptr, &ThostRspInfoNotSupported, nRequestID, true));
	return 0;
}

///产品查询
int CFtdcTraderApiImpl::ReqQryProduct(CThostFtdcQryProductField *pQryProduct, int nRequestID)
{
	m_io_service.post(boost::bind(&CThostFtdcTraderSpi::OnRspQryProduct, m_pSpi, nullptr, nullptr, nRequestID, true));

	return 0;
}

int CFtdcTraderApiImpl::ReqQryBrokerTradingParams(CThostFtdcQryBrokerTradingParamsField *pQryBrokerTradingParams, int nRequestID)
{
	memset(&BrokerTradingParamsField, 0, sizeof(BrokerTradingParamsField));

	strncpy(BrokerTradingParamsField.BrokerID, m_BrokerID, sizeof(BrokerTradingParamsField.BrokerID)-1);
	strncpy(BrokerTradingParamsField.InvestorID, m_UserID, sizeof(BrokerTradingParamsField.InvestorID) - 1);
	strncpy(BrokerTradingParamsField.CurrencyID, "CNY", sizeof(BrokerTradingParamsField.CurrencyID) - 1);

	BrokerTradingParamsField.MarginPriceType = THOST_FTDC_MPT_OpenPrice;
	BrokerTradingParamsField.OptionRoyaltyPriceType = THOST_FTDC_MPT_OpenPrice;
	BrokerTradingParamsField.Algorithm = THOST_FTDC_AG_OnlyLost;

	memset(&ThostRspInfo, 0, sizeof(ThostRspInfo));

	m_io_service.post(boost::bind(&CThostFtdcTraderSpi::OnRspQryBrokerTradingParams, m_pSpi, &BrokerTradingParamsField, &ThostRspInfo, nRequestID, true));

	return 0;	
}

int CFtdcTraderApiImpl::ReqQryInvestorPositionDetail(CThostFtdcQryInvestorPositionDetailField *pQryInvestorPositionDetail, int nRequestID)
{
	m_io_service.post(boost::bind(&CThostFtdcTraderSpi::OnRspQryInvestorPositionDetail, m_pSpi, nullptr, nullptr, nRequestID, true));
	return 0;
}

///询价录入请求
int CFtdcTraderApiImpl::ReqForQuoteInsert(CThostFtdcInputForQuoteField *pInputForQuote, int nRequestID)
{
	m_io_service.post(boost::bind(&CThostFtdcTraderSpi::OnRspForQuoteInsert, m_pSpi, pInputForQuote, &ThostRspInfoNotSupported, nRequestID, true));
	return 0;
}

///报价录入请求
int CFtdcTraderApiImpl::ReqQuoteInsert(CThostFtdcInputQuoteField *pInputQuote, int nRequestID)
{
	m_io_service.post(boost::bind(&CThostFtdcTraderSpi::OnRspQuoteInsert, m_pSpi, pInputQuote, &ThostRspInfoNotSupported, nRequestID, true));
	return 0;
}

///报价操作请求
int CFtdcTraderApiImpl::ReqQuoteAction(CThostFtdcInputQuoteActionField *pInputQuoteAction, int nRequestID)
{
	m_io_service.post(boost::bind(&CThostFtdcTraderSpi::OnRspQuoteAction, m_pSpi, pInputQuoteAction, &ThostRspInfoNotSupported, nRequestID, true));
	return 0;
}


int CFtdcTraderApiImpl::ReqQryInvestorPositionCombineDetail(CThostFtdcQryInvestorPositionCombineDetailField *pQryInvestorPositionCombineDetail, int nRequestID)
{
	m_io_service.post(boost::bind(&CThostFtdcTraderSpi::OnRspQryInvestorPositionCombineDetail, m_pSpi, nullptr, nullptr, nRequestID, true));
	return 0;
}

int CFtdcTraderApiImpl::ReqQrySettlementInfoConfirm(CThostFtdcQrySettlementInfoConfirmField *pQrySettlementInfoConfirm, int nRequestID)
{
	memset(&SettlementInfoConfirmField, 0, sizeof(CThostFtdcSettlementInfoConfirmField));
	strncpy(SettlementInfoConfirmField.BrokerID, pQrySettlementInfoConfirm->BrokerID, sizeof(SettlementInfoConfirmField.BrokerID)-1);
	strncpy(SettlementInfoConfirmField.InvestorID, pQrySettlementInfoConfirm->InvestorID, sizeof(SettlementInfoConfirmField.InvestorID) - 1);
	strncpy(SettlementInfoConfirmField.AccountID, pQrySettlementInfoConfirm->AccountID, sizeof(SettlementInfoConfirmField.AccountID) - 1);
	strncpy(SettlementInfoConfirmField.CurrencyID, pQrySettlementInfoConfirm->CurrencyID, sizeof(SettlementInfoConfirmField.CurrencyID) - 1);
	struct tm* t;
	time_t tt;
	tt = time(NULL);
	t = localtime(&tt);
	snprintf(SettlementInfoConfirmField.ConfirmDate, sizeof(SettlementInfoConfirmField.ConfirmDate), "%04d%02d%02d", t->tm_year + 1900, t->tm_mon + 1, t->tm_mday);
	snprintf(SettlementInfoConfirmField.ConfirmTime, sizeof(SettlementInfoConfirmField.ConfirmTime), "%02d:%02d:%02d", t->tm_hour, t->tm_min, t->tm_sec);

	memset(&ThostRspInfo, 0x00, sizeof(ThostRspInfo));
	m_io_service.post(boost::bind(&CThostFtdcTraderSpi::OnRspQrySettlementInfoConfirm, m_pSpi, &SettlementInfoConfirmField, &ThostRspInfo, nRequestID, true));
	return 0;
}

int CFtdcTraderApiImpl::ReqQrySettlementInfo(CThostFtdcQrySettlementInfoField *pQrySettlementInfo, int nRequestID)
{
	return ReqQrySettlementInfoConfirm(NULL, nRequestID);
}

 int CFtdcTraderApiImpl::ReqQryProductGroup(CThostFtdcQryProductGroupField *pQryProductGroup, int nRequestID)
 {
	m_io_service.post(boost::bind(&CThostFtdcTraderSpi::OnRspQryProductGroup, m_pSpi, nullptr, nullptr, nRequestID, true));
 	return 0;
 }

int CFtdcTraderApiImpl::ReqQryTransferSerial(CThostFtdcQryTransferSerialField *pQryTransferSerial, int nRequestID)
{
	m_io_service.post(boost::bind(&CThostFtdcTraderSpi::OnRspQryTransferSerial, m_pSpi, nullptr, nullptr, nRequestID, true));
	return 0;
}

int CFtdcTraderApiImpl::ReqQryTransferBank(CThostFtdcQryTransferBankField *pQryTransferBank, int nRequestID)
{
	m_io_service.post(boost::bind(&CThostFtdcTraderSpi::OnRspQryTransferBank, m_pSpi, nullptr, nullptr, nRequestID, true));
	return 0;
}

int CFtdcTraderApiImpl::ReqQryForQuote(CThostFtdcQryForQuoteField *pQryForQuote, int nRequestID)
{
	m_io_service.post(boost::bind(&CThostFtdcTraderSpi::OnRspQryForQuote, m_pSpi, nullptr, nullptr, nRequestID, true));
	return 0;
};

int CFtdcTraderApiImpl::ReqQryNotice(CThostFtdcQryNoticeField *pQryNotice, int nRequestID)
{	
	m_io_service.post(boost::bind(&CThostFtdcTraderSpi::OnRspQryNotice,m_pSpi,nullptr, nullptr, nRequestID, true));
	return 0;
}

int CFtdcTraderApiImpl::ReqAuthenticate(CThostFtdcReqAuthenticateField *pReqAuthenticateField, int nRequestID)
{
	m_io_service.post(boost::bind(&CFtdcTraderApiImpl::HandleReqAuthenticate, this, *pReqAuthenticateField, nRequestID));
	return 0;
}
void CFtdcTraderApiImpl::HandleReqAuthenticate(CThostFtdcReqAuthenticateField& AuthenticateField, int nRequestID)
{
	// 创建Api实例
	// XTP要求的key填在AuthCode中，由于Key长度超过了33字节，需要越界到AppID字段。
	m_pUserApi->SetSoftwareKey(AuthenticateField.AuthCode);

	memset(&RspAuthenticateField, 0x00, sizeof(RspAuthenticateField));
	strncpy(RspAuthenticateField.BrokerID, AuthenticateField.BrokerID, sizeof(RspAuthenticateField.BrokerID) - 1);
	strncpy(RspAuthenticateField.UserID, AuthenticateField.UserID, sizeof(RspAuthenticateField.UserID) - 1);
	strncpy(RspAuthenticateField.UserProductInfo, AuthenticateField.UserProductInfo, sizeof(RspAuthenticateField.UserProductInfo) - 1);
	memset(&ThostRspInfo, 0x00, sizeof(ThostRspInfo));
	m_io_service.post(boost::bind(&CThostFtdcTraderSpi::OnRspAuthenticate, m_pSpi, &RspAuthenticateField, &ThostRspInfo, nRequestID, true));
}

int CFtdcTraderApiImpl::ReqQryAccountregister(CThostFtdcQryAccountregisterField *pQryAccountregister, int nRequestID)
{
	m_io_service.post(boost::bind(&CThostFtdcTraderSpi::OnRspQryAccountregister, m_pSpi, nullptr, nullptr, nRequestID, true));
	return 0;
}

int CFtdcTraderApiImpl::ReqQryContractBank(CThostFtdcQryContractBankField *pQryContractBank, int nRequestID)
{
	m_io_service.post(boost::bind(&CThostFtdcTraderSpi::OnRspQryContractBank, m_pSpi, nullptr, nullptr, nRequestID, true));
	return 0;
}

int CFtdcTraderApiImpl::ReqQryTradingNotice(CThostFtdcQryTradingNoticeField *pQryContractBank, int nRequestID)
{
	m_io_service.post(boost::bind(&CThostFtdcTraderSpi::OnRspQryTradingNotice, m_pSpi, nullptr, nullptr, nRequestID, true));
	return 0;
}

void CFtdcTraderApiImpl::OnDisconnected(uint64_t session_id, int reason)
{
	m_logined = false;

	if (m_pSpi) {
		m_pSpi->OnFrontDisconnected(reason);

		// 断线立即重连
		m_pSpi->OnFrontConnected();
	}
}


//投资者持仓查询
void CFtdcTraderApiImpl::OnQueryPosition(XTPQueryStkPositionRsp* position, XTPRI* error_info, int request_id, bool is_last, uint64_t session_id)
{
	if (m_pSpi)
	{
		CThostFtdcRspInfoField* pThostRspInfo = NULL;
		CThostFtdcRspInfoField  ThostRspInfo;

		if (error_info && error_info->error_id!= 11000350)
		{
			memset(&ThostRspInfo, 0, sizeof(ThostRspInfo));
			ThostRspInfo.ErrorID = error_info->error_id;
			strncpy(ThostRspInfo.ErrorMsg, error_info->error_msg, sizeof(ThostRspInfo.ErrorMsg) - 1);
			pThostRspInfo = &ThostRspInfo;
		}

		CThostFtdcInvestorPositionField* pThostRspInvestorPosition = NULL;
		CThostFtdcInvestorPositionField  ThostRspInvestorPosition;

		if (position)
		{
			memset(&ThostRspInvestorPosition, 0, sizeof(ThostRspInvestorPosition));
			strncpy(ThostRspInvestorPosition.BrokerID, m_BrokerID, sizeof(ThostRspInvestorPosition.BrokerID) - 1);
			strncpy(ThostRspInvestorPosition.InvestorID, m_UserID, sizeof(ThostRspInvestorPosition.InvestorID) - 1);
			if (position->market == XTP_MKT_SH_A)
				strncpy(ThostRspInvestorPosition.ExchangeID, EXCHANGE_SH, sizeof(ThostRspInvestorPosition.ExchangeID) - 1);
			else if (position->market == XTP_MKT_SZ_A)
				strncpy(ThostRspInvestorPosition.ExchangeID, EXCHANGE_SZ, sizeof(ThostRspInvestorPosition.ExchangeID) - 1);

			strncpy(ThostRspInvestorPosition.InstrumentID, position->ticker, sizeof(ThostRspInvestorPosition.InstrumentID) - 1);
			strncpy(ThostRspInvestorPosition.TradingDay, TradingDay, sizeof(ThostRspInvestorPosition.TradingDay) - 1);
			ThostRspInvestorPosition.HedgeFlag = THOST_FTDC_HF_Speculation;
			ThostRspInvestorPosition.UseMargin = 0;
			ThostRspInvestorPosition.FrozenMargin = 0;

			//上海期货交易所的持仓有两条，分为昨持仓和今持仓
			ThostRspInvestorPosition.PosiDirection = THOST_FTDC_PD_Long; // A股只有多仓
			ThostRspInvestorPosition.Position = position->total_qty;
			ThostRspInvestorPosition.PositionCost = position->buy_cost;
			ThostRspInvestorPosition.YdPosition = position->yesterday_position;
			ThostRspInvestorPosition.LongFrozen = 0;
			ThostRspInvestorPosition.ShortFrozen = position->total_qty - position->sellable_qty;
			ThostRspInvestorPosition.PositionDate = THOST_FTDC_PSD_Today;
			ThostRspInvestorPosition.OpenVolume = 0;
			ThostRspInvestorPosition.CloseVolume = 0;
			ThostRspInvestorPosition.OpenCost = position->buy_cost;
			ThostRspInvestorPosition.PositionProfit = 0;
			ThostRspInvestorPosition.CloseProfit = 0;
			ThostRspInvestorPosition.TodayPosition = position->total_qty - position->yesterday_position;
			m_pSpi->OnRspQryInvestorPosition(&ThostRspInvestorPosition, pThostRspInfo, request_id, is_last);
		}
		else {
			m_pSpi->OnRspQryInvestorPosition(pThostRspInvestorPosition, pThostRspInfo, request_id, is_last);
		}
	}
}

//报单查询
void CFtdcTraderApiImpl::OnQueryOrder(XTPQueryOrderRsp* order_info, XTPRI* error_info, int request_id, bool is_last, uint64_t session_id)
{
	if (m_pSpi)
	{
		CThostFtdcOrderField* pThostOrder = NULL;
		CThostFtdcOrderField  ThostOrder;
		if (order_info)
		{
			memset(&ThostOrder, 0x00, sizeof(ThostOrder));
			strncpy(ThostOrder.UserID, m_UserID, sizeof(ThostOrder.UserID) - 1);
			strncpy(ThostOrder.AccountID, m_InvestorID, sizeof(ThostOrder.AccountID) - 1);
			strncpy(ThostOrder.InvestorID, m_InvestorID, sizeof(ThostOrder.InvestorID) - 1);
			strncpy(ThostOrder.InstrumentID, order_info->ticker, sizeof(ThostOrder.InstrumentID) - 1);
			if (order_info->market == XTP_MKT_SH_A)
				strncpy(ThostOrder.ExchangeID, EXCHANGE_SH, sizeof(ThostOrder.ExchangeID) - 1);
			else if (order_info->market == XTP_MKT_SZ_A)
				strncpy(ThostOrder.ExchangeID, EXCHANGE_SZ, sizeof(ThostOrder.ExchangeID) - 1);
			ThostOrder.VolumeTotal = order_info->qty_left;
			ThostOrder.VolumeTotalOriginal = order_info->quantity;
			ThostOrder.VolumeTraded = order_info->qty_traded;
			ThostOrder.LimitPrice = order_info->price;
			ThostOrder.OrderPriceType = order_info->order_type == XTP_PRICE_LIMIT ? THOST_FTDC_OPT_LimitPrice : THOST_FTDC_OPT_AnyPrice;
			ThostOrder.Direction = order_info->side == XTP_SIDE_BUY ? THOST_FTDC_D_Buy : THOST_FTDC_D_Sell;
			ThostOrder.CombOffsetFlag[0] = order_info->side == XTP_SIDE_BUY ? THOST_FTDC_OF_Open : THOST_FTDC_OF_Close;
			ThostOrder.CombHedgeFlag[0] = THOST_FTDC_HF_Speculation;
			ThostOrder.FrontID = 0;
			ThostOrder.SessionID = 0;
			strncpy(ThostOrder.OrderSysID, std::to_string(order_info->order_xtp_id).c_str(), sizeof(ThostOrder.OrderSysID) - 1);
			uint64_t ctp_order_id;
			uint32_t OrderRef;
			auto iter = m_mXtpIDToOrderRef.find(order_info->order_xtp_id);
			if (iter == m_mXtpIDToOrderRef.end()) {
				OrderRef = m_ctp_sys_orderref++;
				ctp_order_id = OrderRef; // 系统生成的OrderRef对应的SessionID为0
				m_mXtpIDToOrderRef[order_info->order_xtp_id] = ctp_order_id;
				m_mOrderRefToXtpID[ctp_order_id] = order_info->order_xtp_id;
			}
			else {
				OrderRef = iter->second << 32 >> 32;
				ThostOrder.SessionID = iter->second >> 32;
			}
			snprintf(ThostOrder.OrderRef, sizeof(ThostOrder.OrderRef), "%u", OrderRef);


			switch (order_info->order_status)
			{
			case XTP_ORDER_STATUS_ALLTRADED:
				ThostOrder.OrderStatus = THOST_FTDC_OST_AllTraded;
				strncpy(ThostOrder.StatusMsg, "全部成交", sizeof(ThostOrder.StatusMsg) - 1);
				break;
			case XTP_ORDER_STATUS_PARTTRADEDQUEUEING:
				ThostOrder.OrderStatus = THOST_FTDC_OST_PartTradedQueueing;
				strncpy(ThostOrder.StatusMsg, "部分成交", sizeof(ThostOrder.StatusMsg) - 1);
				break;
			case XTP_ORDER_STATUS_PARTTRADEDNOTQUEUEING:
			case XTP_ORDER_STATUS_CANCELED:
			case XTP_ORDER_STATUS_REJECTED:
				ThostOrder.OrderStatus = THOST_FTDC_OST_Canceled;
				strncpy(ThostOrder.StatusMsg, "已撤消", sizeof(ThostOrder.StatusMsg) - 1);
				break;
			case XTP_ORDER_STATUS_NOTRADEQUEUEING:
				ThostOrder.OrderStatus = THOST_FTDC_OST_NoTradeQueueing;
				strncpy(ThostOrder.StatusMsg, "未成交", sizeof(ThostOrder.StatusMsg) - 1);
				break;
			default:
				ThostOrder.OrderStatus = THOST_FTDC_OST_Unknown;
				strncpy(ThostOrder.StatusMsg, "未知", sizeof(ThostOrder.StatusMsg) - 1);
				break;
			}
			ThostOrder.OrderSubmitStatus = THOST_FTDC_OSS_Accepted;
			strncpy(ThostOrder.InsertDate, std::to_string(order_info->insert_time / 1000 / 1000000).c_str(), sizeof(ThostOrder.InsertDate) - 1);
			strncpy(ThostOrder.InsertTime, time_to_string(order_info->insert_time).c_str(), sizeof(ThostOrder.InsertTime) - 1);
			strncpy(ThostOrder.CancelTime, time_to_string(order_info->cancel_time).c_str(), sizeof(ThostOrder.CancelTime) - 1);
			strncpy(ThostOrder.OrderLocalID, std::to_string(order_info->order_xtp_id).c_str(), sizeof(ThostOrder.OrderLocalID) - 1);
			pThostOrder = &ThostOrder;
		}
		CThostFtdcRspInfoField* pThostRspInfo = NULL;
		CThostFtdcRspInfoField  ThostRspInfo;
		if (error_info && error_info->error_id != 11000350)
		{
			memset(&ThostRspInfo, 0, sizeof(ThostRspInfo));
			ThostRspInfo.ErrorID = error_info->error_id;
			strncpy(ThostRspInfo.ErrorMsg, error_info->error_msg, sizeof(ThostRspInfo.ErrorMsg) - 1);
			pThostRspInfo = &ThostRspInfo;
		}

		m_pSpi->OnRspQryOrder(pThostOrder, pThostRspInfo, request_id, is_last);
	}
}


//成交查询
void CFtdcTraderApiImpl::OnQueryTrade(XTPQueryTradeRsp* trade_info, XTPRI* error_info, int request_id, bool is_last, uint64_t session_idt)
{
	if (m_pSpi)
	{
		CThostFtdcTradeField* pThostTrade = NULL;
		CThostFtdcTradeField  ThostTrade;
		if (trade_info)
		{
			memset(&ThostTrade, 0, sizeof(CThostFtdcTradeField));
			strncpy(ThostTrade.UserID, m_UserID, sizeof(ThostTrade.UserID) - 1);
			strncpy(ThostTrade.InvestorID, m_InvestorID, sizeof(ThostTrade.InvestorID) - 1);
			strncpy(ThostTrade.InstrumentID, trade_info->ticker, sizeof(ThostTrade.InstrumentID) - 1);
			if (trade_info->market == XTP_MKT_SH_A)
				strncpy(ThostTrade.ExchangeID, EXCHANGE_SH, sizeof(ThostTrade.ExchangeID) - 1);
			else if (trade_info->market == XTP_MKT_SZ_A)
				strncpy(ThostTrade.ExchangeID, EXCHANGE_SZ, sizeof(ThostTrade.ExchangeID) - 1);
			strncpy(ThostTrade.TradeID, trade_info->exec_id, sizeof(ThostTrade.TradeID) - 1);
			strncpy(ThostTrade.OrderSysID, std::to_string(trade_info->order_xtp_id).c_str(), sizeof(ThostTrade.OrderSysID) - 1);
			uint64_t ctp_order_id;
			uint32_t OrderRef;
			auto iter = m_mXtpIDToOrderRef.find(trade_info->order_xtp_id);
			if (iter == m_mXtpIDToOrderRef.end()) {
				OrderRef = m_ctp_sys_orderref++;
				ctp_order_id = OrderRef; // 系统生成的OrderRef对应的SessionID为0
				m_mXtpIDToOrderRef[trade_info->order_xtp_id] = ctp_order_id;
				m_mOrderRefToXtpID[ctp_order_id] = trade_info->order_xtp_id;
			}
			else {
				OrderRef = iter->second << 32 >> 32;
			}
			snprintf(ThostTrade.OrderRef, sizeof(ThostTrade.OrderRef), "%u", OrderRef);
			ThostTrade.Direction = trade_info->side == XTP_SIDE_BUY ? THOST_FTDC_D_Buy : THOST_FTDC_D_Sell;
			ThostTrade.OffsetFlag = trade_info->side == XTP_SIDE_BUY ? THOST_FTDC_OF_Open : THOST_FTDC_OF_Close;
			ThostTrade.HedgeFlag = THOST_FTDC_HF_Speculation;
			ThostTrade.Price = trade_info->price;
			ThostTrade.Volume = trade_info->quantity;
			strncpy(ThostTrade.OrderLocalID, std::to_string(trade_info->order_xtp_id).c_str(), sizeof(ThostTrade.OrderLocalID) - 1);
			strncpy(ThostTrade.TradeDate, std::to_string(trade_info->trade_time / 1000 / 1000000).c_str(), sizeof(ThostTrade.TradeDate) - 1);
			strncpy(ThostTrade.TradeTime, time_to_string(trade_info->trade_time).c_str(), sizeof(ThostTrade.TradeTime) - 1);
			strncpy(ThostTrade.TradingDay, TradingDay, sizeof(ThostTrade.TradingDay) - 1);
			ThostTrade.TradeType = THOST_FTDC_TRDT_Common;
			strncpy(ThostTrade.TraderID, trade_info->branch_pbu, sizeof(ThostTrade.TraderID) - 1);

			pThostTrade = &ThostTrade;
		}

		CThostFtdcRspInfoField* pThostRspInfo = NULL;
		CThostFtdcRspInfoField  ThostRspInfo;
		if (error_info && error_info->error_id != 11000350)
		{
			memset(&ThostRspInfo, 0, sizeof(ThostRspInfo));
			ThostRspInfo.ErrorID = error_info->error_id;
			strncpy(ThostRspInfo.ErrorMsg, error_info->error_msg, sizeof(ThostRspInfo.ErrorMsg) - 1);
			pThostRspInfo = &ThostRspInfo;
		}

		m_pSpi->OnRspQryTrade(pThostTrade, pThostRspInfo, request_id, is_last);
	}
}

//报单回报
void CFtdcTraderApiImpl::OnOrderEvent(XTPOrderInfo* order_info, XTPRI* error_info, uint64_t session_id)
{
	if (m_pSpi) {
		CThostFtdcOrderField ThostOrder;
		memset(&ThostOrder, 0x00, sizeof(ThostOrder));
		strncpy(ThostOrder.UserID, m_UserID, sizeof(ThostOrder.UserID) - 1);
		strncpy(ThostOrder.AccountID, m_InvestorID, sizeof(ThostOrder.AccountID) - 1);
		strncpy(ThostOrder.InvestorID, m_InvestorID, sizeof(ThostOrder.InvestorID) - 1);
		strncpy(ThostOrder.InstrumentID, order_info->ticker, sizeof(ThostOrder.InstrumentID) - 1);
		if (order_info->market == XTP_MKT_SH_A)
			strncpy(ThostOrder.ExchangeID, EXCHANGE_SH, sizeof(ThostOrder.ExchangeID) - 1);
		else if (order_info->market == XTP_MKT_SZ_A)
			strncpy(ThostOrder.ExchangeID, EXCHANGE_SZ, sizeof(ThostOrder.ExchangeID) - 1);
		ThostOrder.VolumeTotal = order_info->qty_left;
		ThostOrder.VolumeTotalOriginal = order_info->quantity;
		ThostOrder.VolumeTraded = order_info->qty_traded;
		ThostOrder.LimitPrice = order_info->price;
		ThostOrder.OrderPriceType = order_info->order_type == XTP_PRICE_LIMIT ? THOST_FTDC_OPT_LimitPrice : THOST_FTDC_OPT_AnyPrice;
		ThostOrder.Direction = order_info->side == XTP_SIDE_BUY ? THOST_FTDC_D_Buy : THOST_FTDC_D_Sell;
		ThostOrder.CombOffsetFlag[0] = order_info->side == XTP_SIDE_BUY ? THOST_FTDC_OF_Open : THOST_FTDC_OF_Close;
		ThostOrder.CombHedgeFlag[0] = THOST_FTDC_HF_Speculation;
		ThostOrder.FrontID = 0;
		ThostOrder.SessionID = 0;
		strncpy(ThostOrder.OrderSysID, std::to_string(order_info->order_xtp_id).c_str(), sizeof(ThostOrder.OrderSysID) - 1);
		uint64_t ctp_order_id;
		uint32_t OrderRef;
		auto iter = m_mXtpIDToOrderRef.find(order_info->order_xtp_id);
		if (iter == m_mXtpIDToOrderRef.end()) {
			OrderRef = m_ctp_sys_orderref++;
			ctp_order_id = OrderRef; // 系统生成的OrderRef对应的SessionID为0
			m_mXtpIDToOrderRef[order_info->order_xtp_id] = ctp_order_id;
			m_mOrderRefToXtpID[ctp_order_id] = order_info->order_xtp_id;
		}
		else {
			OrderRef = iter->second << 32 >> 32;
			ThostOrder.SessionID = iter->second >> 32;
		}
		snprintf(ThostOrder.OrderRef, sizeof(ThostOrder.OrderRef), "%u", OrderRef);

		switch (order_info->order_status)
		{
		case XTP_ORDER_STATUS_ALLTRADED:
			ThostOrder.OrderStatus = THOST_FTDC_OST_AllTraded;
			strncpy(ThostOrder.StatusMsg, "全部成交", sizeof(ThostOrder.StatusMsg) - 1);
			break;
		case XTP_ORDER_STATUS_PARTTRADEDQUEUEING:
			ThostOrder.OrderStatus = THOST_FTDC_OST_PartTradedQueueing;
			strncpy(ThostOrder.StatusMsg, "部分成交", sizeof(ThostOrder.StatusMsg) - 1);
			break;
		case XTP_ORDER_STATUS_PARTTRADEDNOTQUEUEING:
		case XTP_ORDER_STATUS_CANCELED:
		case XTP_ORDER_STATUS_REJECTED:
			ThostOrder.OrderStatus = THOST_FTDC_OST_Canceled;
			strncpy(ThostOrder.StatusMsg, "已撤消", sizeof(ThostOrder.StatusMsg) - 1);
			break;
		case XTP_ORDER_STATUS_NOTRADEQUEUEING:
			ThostOrder.OrderStatus = THOST_FTDC_OST_NoTradeQueueing;
			strncpy(ThostOrder.StatusMsg, "未成交", sizeof(ThostOrder.StatusMsg) - 1);
			break;
		default:
			ThostOrder.OrderStatus = THOST_FTDC_OST_Unknown;
			strncpy(ThostOrder.StatusMsg, "未知", sizeof(ThostOrder.StatusMsg) - 1);
			break;
		}
		ThostOrder.OrderSubmitStatus = THOST_FTDC_OSS_Accepted;
		strncpy(ThostOrder.InsertDate, std::to_string(order_info->insert_time / 1000 / 1000000).c_str(), sizeof(ThostOrder.InsertDate) - 1);
		strncpy(ThostOrder.InsertTime, time_to_string(order_info->insert_time).c_str(), sizeof(ThostOrder.InsertTime) - 1);
		strncpy(ThostOrder.CancelTime, time_to_string(order_info->cancel_time).c_str(), sizeof(ThostOrder.CancelTime) - 1);
		strncpy(ThostOrder.OrderLocalID, std::to_string(order_info->order_xtp_id).c_str(), sizeof(ThostOrder.OrderLocalID) - 1);

		m_pSpi->OnRtnOrder(&ThostOrder);
	}	
}

//成交回报
void CFtdcTraderApiImpl::OnTradeEvent(XTPTradeReport* trade_info, uint64_t session_id)
{
	if (m_pSpi)
	{
		CThostFtdcTradeField  ThostTrade;

		memset(&ThostTrade, 0, sizeof(CThostFtdcTradeField));
		strncpy(ThostTrade.UserID, m_UserID, sizeof(ThostTrade.UserID) - 1);
		strncpy(ThostTrade.InvestorID, m_InvestorID, sizeof(ThostTrade.InvestorID) - 1);
		strncpy(ThostTrade.InstrumentID, trade_info->ticker, sizeof(ThostTrade.InstrumentID) - 1);
		if (trade_info->market == XTP_MKT_SH_A)
			strncpy(ThostTrade.ExchangeID, EXCHANGE_SH, sizeof(ThostTrade.ExchangeID) - 1);
		else if (trade_info->market == XTP_MKT_SZ_A)
			strncpy(ThostTrade.ExchangeID, EXCHANGE_SZ, sizeof(ThostTrade.ExchangeID) - 1);
		strncpy(ThostTrade.TradeID, trade_info->exec_id, sizeof(ThostTrade.TradeID) - 1);
		strncpy(ThostTrade.OrderSysID, std::to_string(trade_info->order_xtp_id).c_str(), sizeof(ThostTrade.OrderSysID) - 1);
		uint64_t ctp_order_id;
		uint32_t OrderRef;
		auto iter = m_mXtpIDToOrderRef.find(trade_info->order_xtp_id);
		if (iter == m_mXtpIDToOrderRef.end()) {
			OrderRef = m_ctp_sys_orderref++;
			ctp_order_id = OrderRef; // 系统生成的OrderRef对应的SessionID为0
			m_mXtpIDToOrderRef[trade_info->order_xtp_id] = ctp_order_id;
			m_mOrderRefToXtpID[ctp_order_id] = trade_info->order_xtp_id;
		}
		else {
			OrderRef = iter->second << 32 >> 32;
		}
		snprintf(ThostTrade.OrderRef, sizeof(ThostTrade.OrderRef), "%u", OrderRef);
		ThostTrade.Direction = trade_info->side == XTP_SIDE_BUY ? THOST_FTDC_D_Buy : THOST_FTDC_D_Sell;
		ThostTrade.OffsetFlag = trade_info->side == XTP_SIDE_BUY ? THOST_FTDC_OF_Open : THOST_FTDC_OF_Close;
		ThostTrade.HedgeFlag = THOST_FTDC_HF_Speculation;
		ThostTrade.Price = trade_info->price;
		ThostTrade.Volume = trade_info->quantity;
		strncpy(ThostTrade.OrderLocalID, std::to_string(trade_info->order_xtp_id).c_str(), sizeof(ThostTrade.OrderLocalID) - 1);
		strncpy(ThostTrade.TradeDate, std::to_string(trade_info->trade_time / 1000 / 1000000).c_str(), sizeof(ThostTrade.TradeDate) - 1);
		strncpy(ThostTrade.TradeTime, time_to_string(trade_info->trade_time).c_str(), sizeof(ThostTrade.TradeTime) - 1);
		strncpy(ThostTrade.TradingDay, TradingDay, sizeof(ThostTrade.TradingDay) - 1);
		ThostTrade.TradeType = THOST_FTDC_TRDT_Common;
		strncpy(ThostTrade.TraderID, trade_info->branch_pbu, sizeof(ThostTrade.TraderID) - 1);

		m_pSpi->OnRtnTrade(&ThostTrade);
	}
}

///报价查询请求
int CFtdcTraderApiImpl::ReqQryQuote(CThostFtdcQryQuoteField* pQryQuote, int nRequestID)
{
	m_io_service.post(boost::bind(&CThostFtdcTraderSpi::OnRspQryQuote, m_pSpi, nullptr, nullptr, nRequestID, true));
	return 0;
}

///执行宣告查询请求
int CFtdcTraderApiImpl::ReqQryExecOrder(CThostFtdcQryExecOrderField* pQryExecOrder, int nRequestID)
{
	m_io_service.post(boost::bind(&CThostFtdcTraderSpi::OnRspQryExecOrder, m_pSpi, nullptr, nullptr, nRequestID, true));
	return 0;
}

///期权自对冲查询请求
int CFtdcTraderApiImpl::ReqQryOptionSelfClose(CThostFtdcQryOptionSelfCloseField* pQryOptionSelfClose, int nRequestID)
{
	m_io_service.post(boost::bind(&CThostFtdcTraderSpi::OnRspQryOptionSelfClose, m_pSpi, nullptr, nullptr, nRequestID, true));
	return 0;
}

///期权自对冲录入请求
int CFtdcTraderApiImpl::ReqOptionSelfCloseInsert(CThostFtdcInputOptionSelfCloseField* pInputOptionSelfClose, int nRequestID)
{
	m_io_service.post(boost::bind(&CThostFtdcTraderSpi::OnRspOptionSelfCloseInsert, m_pSpi, nullptr, nullptr, nRequestID, true));
	return 0;
}

///期权自对冲操作请求
int CFtdcTraderApiImpl::ReqOptionSelfCloseAction(CThostFtdcInputOptionSelfCloseActionField* pInputOptionSelfCloseAction, int nRequestID)
{
	m_io_service.post(boost::bind(&CThostFtdcTraderSpi::OnRspOptionSelfCloseAction, m_pSpi, nullptr, nullptr, nRequestID, true));
	return 0;
}

///执行宣告录入请求
int CFtdcTraderApiImpl::ReqExecOrderInsert(CThostFtdcInputExecOrderField* pInputExecOrder, int nRequestID)
{
	m_io_service.post(boost::bind(&CThostFtdcTraderSpi::OnRspExecOrderInsert, m_pSpi, pInputExecOrder, &ThostRspInfoNotSupported, nRequestID, true));
	return 0;
}

///执行宣告操作请求
int CFtdcTraderApiImpl::ReqExecOrderAction(CThostFtdcInputExecOrderActionField* pInputExecOrderAction, int nRequestID)
{
	m_io_service.post(boost::bind(&CThostFtdcTraderSpi::OnRspExecOrderAction, m_pSpi, pInputExecOrderAction, &ThostRspInfoNotSupported, nRequestID, true));
	return 0;
}

int CFtdcTraderApiImpl::ReqQryCFMMCTradingAccountKey(CThostFtdcQryCFMMCTradingAccountKeyField* pQryCFMMCTradingAccountKey, int nRequestID)
{
	m_io_service.post(boost::bind(&CThostFtdcTraderSpi::OnRspQryCFMMCTradingAccountKey, m_pSpi, nullptr, nullptr, nRequestID, true));
	return 0;
}

int CFtdcTraderApiImpl::ReqQryParkedOrder(CThostFtdcQryParkedOrderField* pQryParkedOrder, int nRequestID)
{
	m_io_service.post(boost::bind(&CThostFtdcTraderSpi::OnRspQryParkedOrder, m_pSpi, nullptr, nullptr, nRequestID, true));
	return 0;
}

///请求查询预埋撤单
int CFtdcTraderApiImpl::ReqQryParkedOrderAction(CThostFtdcQryParkedOrderActionField* pQryParkedOrderAction, int nRequestID)
{
	m_io_service.post(boost::bind(&CThostFtdcTraderSpi::OnRspQryParkedOrderAction, m_pSpi, nullptr, nullptr, nRequestID, true));
	return 0;
}

///请求查询交易所保证金率
int CFtdcTraderApiImpl::ReqQryExchangeMarginRate(CThostFtdcQryExchangeMarginRateField* pQryExchangeMarginRate, int nRequestID)
{
	m_io_service.post(boost::bind(&CThostFtdcTraderSpi::OnRspQryExchangeMarginRate, m_pSpi, nullptr, nullptr, nRequestID, true));
	return 0;
}

///请求查询期权交易成本
int CFtdcTraderApiImpl::ReqQryOptionInstrTradeCost(CThostFtdcQryOptionInstrTradeCostField* pQryOptionInstrTradeCost, int nRequestID)
{
	m_io_service.post(boost::bind(&CThostFtdcTraderSpi::OnRspQryOptionInstrTradeCost, m_pSpi, nullptr, nullptr, nRequestID, true));
	return 0;
}

///请求查询期权合约手续费
int CFtdcTraderApiImpl::ReqQryOptionInstrCommRate(CThostFtdcQryOptionInstrCommRateField* pQryOptionInstrCommRate, int nRequestID)
{
	m_io_service.post(boost::bind(&CThostFtdcTraderSpi::OnRspQryOptionInstrCommRate, m_pSpi, nullptr, nullptr, nRequestID, true));
	return 0;
}

///请求查询报单手续费
int CFtdcTraderApiImpl::ReqQryInstrumentOrderCommRate(CThostFtdcQryInstrumentOrderCommRateField* pQryInstrumentOrderCommRate, int nRequestID)
{
	m_io_service.post(boost::bind(&CThostFtdcTraderSpi::OnRspQryInstrumentOrderCommRate, m_pSpi, nullptr, nullptr, nRequestID, true));
	return 0;
}

///请求查询交易编码
int CFtdcTraderApiImpl::ReqQryTradingCode(CThostFtdcQryTradingCodeField* pQryTradingCode, int nRequestID)
{
	m_io_service.post(boost::bind(&CThostFtdcTraderSpi::OnRspQryTradingCode, m_pSpi, nullptr, nullptr, nRequestID, true));
	return 0;
}

///请求查询投资单元
int CFtdcTraderApiImpl::ReqQryInvestUnit(CThostFtdcQryInvestUnitField* pQryInvestUnit, int nRequestID)
{
	m_io_service.post(boost::bind(&CThostFtdcTraderSpi::OnRspQryInvestUnit, m_pSpi, nullptr, nullptr, nRequestID, true));
	return 0;
}

///请求查询组合合约安全系数
int CFtdcTraderApiImpl::ReqQryCombInstrumentGuard(CThostFtdcQryCombInstrumentGuardField* pQryCombInstrumentGuard, int nRequestID)
{
	m_io_service.post(boost::bind(&CThostFtdcTraderSpi::OnRspQryCombInstrumentGuard, m_pSpi, nullptr, nullptr, nRequestID, true));
	return 0;
}

///请求查询申请组合
int CFtdcTraderApiImpl::ReqQryCombAction(CThostFtdcQryCombActionField* pQryCombAction, int nRequestID)
{
	m_io_service.post(boost::bind(&CThostFtdcTraderSpi::OnRspQryCombAction, m_pSpi, nullptr, nullptr, nRequestID, true));
	return 0;
}

///请求查询经纪公司交易算法
int CFtdcTraderApiImpl::ReqQryBrokerTradingAlgos(CThostFtdcQryBrokerTradingAlgosField* pQryBrokerTradingAlgos, int nRequestID)
{
	m_io_service.post(boost::bind(&CThostFtdcTraderSpi::OnRspQryBrokerTradingAlgos, m_pSpi, nullptr, nullptr, nRequestID, true));
	return 0;
}

///请求查询监控中心用户令牌
int CFtdcTraderApiImpl::ReqQueryCFMMCTradingAccountToken(CThostFtdcQueryCFMMCTradingAccountTokenField* pQueryCFMMCTradingAccountToken, int nRequestID)
{
	m_io_service.post(boost::bind(&CThostFtdcTraderSpi::OnRspQueryCFMMCTradingAccountToken, m_pSpi, nullptr, nullptr, nRequestID, true));
	return 0;
}

///期货发起查询银行余额请求
int CFtdcTraderApiImpl::ReqQueryBankAccountMoneyByFuture(CThostFtdcReqQueryAccountField* pReqQueryAccount, int nRequestID)
{
	m_io_service.post(boost::bind(&CThostFtdcTraderSpi::OnRspQueryBankAccountMoneyByFuture, m_pSpi, nullptr, nullptr, nRequestID, true));
	return 0;
}

///查询用户当前支持的认证模式
int CFtdcTraderApiImpl::ReqUserAuthMethod(CThostFtdcReqUserAuthMethodField* pReqUserAuthMethod, int nRequestID)
{
	static CThostFtdcRspUserAuthMethodField UserAuthMethodField;
	memset(&UserAuthMethodField, 0x00, sizeof(UserAuthMethodField));
	UserAuthMethodField.UsableAuthMethod = 0;

	m_io_service.post(boost::bind(&CThostFtdcTraderSpi::OnRspUserAuthMethod, m_pSpi, &UserAuthMethodField, nullptr, nRequestID, true));
	return 0;
}

///请求查询二级代理商信息
int CFtdcTraderApiImpl::ReqQrySecAgentTradeInfo(CThostFtdcQrySecAgentTradeInfoField* pQrySecAgentTradeInfo, int nRequestID)
{
	m_io_service.post(boost::bind(&CThostFtdcTraderSpi::OnRspQrySecAgentTradeInfo, m_pSpi, nullptr, nullptr, nRequestID, true));
	return 0;
}

#ifdef V6_5_1
///查询最大报单数量请求
int CFtdcTraderApiImpl::ReqQryMaxOrderVolume(CThostFtdcQryMaxOrderVolumeField* pQryMaxOrderVolume, int nRequestID)
{
	m_io_service.post(boost::bind(&CFtdcTraderApiImpl::HandleReqQryMaxOrderVolume, this, *pQryMaxOrderVolume, nRequestID));
	return 0;
}
void CFtdcTraderApiImpl::HandleReqQryMaxOrderVolume(CThostFtdcQryMaxOrderVolumeField& QryMaxOrderVolume, int nRequestID)
{
	CThostFtdcQryMaxOrderVolumeField MaxOrderVolume = { 0 };
	strncpy(MaxOrderVolume.BrokerID, QryMaxOrderVolume.BrokerID, sizeof(MaxOrderVolume.BrokerID) - 1);
	strncpy(MaxOrderVolume.InvestorID, QryMaxOrderVolume.InvestorID, sizeof(MaxOrderVolume.InvestorID) - 1);
	strncpy(MaxOrderVolume.ExchangeID, QryMaxOrderVolume.ExchangeID, sizeof(MaxOrderVolume.ExchangeID) - 1);
	strncpy(MaxOrderVolume.InstrumentID, QryMaxOrderVolume.InstrumentID, sizeof(MaxOrderVolume.InstrumentID) - 1);
	MaxOrderVolume.Direction = QryMaxOrderVolume.Direction;
	MaxOrderVolume.HedgeFlag = QryMaxOrderVolume.HedgeFlag;
	MaxOrderVolume.OffsetFlag = QryMaxOrderVolume.OffsetFlag;
	MaxOrderVolume.MaxVolume = INT32_MAX;
	strncpy(MaxOrderVolume.InvestUnitID, QryMaxOrderVolume.InvestUnitID, sizeof(MaxOrderVolume.InvestUnitID) - 1);

	if (m_pSpi) {
		m_pSpi->OnRspQryMaxOrderVolume(&MaxOrderVolume, nullptr, nRequestID, true);
	}
}

///请求查询分类合约
int CFtdcTraderApiImpl::ReqQryClassifiedInstrument(CThostFtdcQryClassifiedInstrumentField* pQryClassifiedInstrument, int nRequestID)
{
	m_io_service.post(boost::bind(&CThostFtdcTraderSpi::OnRspQryClassifiedInstrument, m_pSpi, nullptr, nullptr, nRequestID, true));
	return 0;
}

///请求组合优惠比例
int CFtdcTraderApiImpl::ReqQryCombPromotionParam(CThostFtdcQryCombPromotionParamField* pQryCombPromotionParam, int nRequestID)
{
	m_io_service.post(boost::bind(&CThostFtdcTraderSpi::OnRspQryCombPromotionParam, m_pSpi, nullptr, nullptr, nRequestID, true));
	return 0;
}

#endif


#ifdef V6_6_1_P1

///投资者风险结算持仓查询
int CFtdcTraderApiImpl::ReqQryRiskSettleInvstPosition(CThostFtdcQryRiskSettleInvstPositionField* pQryRiskSettleInvstPosition, int nRequestID)
{
	m_io_service.post(boost::bind(&CThostFtdcTraderSpi::OnRspQryRiskSettleInvstPosition, m_pSpi, nullptr, nullptr, nRequestID, true));
	return 0;
}

///风险结算产品查询
int CFtdcTraderApiImpl::ReqQryRiskSettleProductStatus(CThostFtdcQryRiskSettleProductStatusField* pQryRiskSettleProductStatus, int nRequestID)
{
	m_io_service.post(boost::bind(&CThostFtdcTraderSpi::OnRspQryRiskSettleProductStatus, m_pSpi, nullptr, nullptr, nRequestID, true));
	return 0;
}

#endif


#if defined(V6_6_7) || defined(V6_6_5_P1)

int CFtdcTraderApiImpl::ReqQryTraderOffer(CThostFtdcQryTraderOfferField* pQryTraderOffer, int nRequestID)
{
	m_io_service.post(boost::bind(&CThostFtdcTraderSpi::OnRspQryTraderOffer, m_pSpi, nullptr, nullptr, nRequestID, true));
	return 0;
}
#endif

#if defined(V6_6_9)
///SPBM期货合约参数查询
int CFtdcTraderApiImpl::ReqQrySPBMFutureParameter(CThostFtdcQrySPBMFutureParameterField* pQrySPBMFutureParameter, int nRequestID)
{
	m_io_service.post(boost::bind(&CThostFtdcTraderSpi::OnRspQrySPBMFutureParameter, m_pSpi, nullptr, nullptr, nRequestID, true));
	return 0;
}

///SPBM期权合约参数查询
int CFtdcTraderApiImpl::ReqQrySPBMOptionParameter(CThostFtdcQrySPBMOptionParameterField* pQrySPBMOptionParameter, int nRequestID)
{
	m_io_service.post(boost::bind(&CThostFtdcTraderSpi::OnRspQrySPBMOptionParameter, m_pSpi, nullptr, nullptr, nRequestID, true));
	return 0;
}

///SPBM品种内对锁仓折扣参数查询
int CFtdcTraderApiImpl::ReqQrySPBMIntraParameter(CThostFtdcQrySPBMIntraParameterField* pQrySPBMIntraParameter, int nRequestID)
{
	m_io_service.post(boost::bind(&CThostFtdcTraderSpi::OnRspQrySPBMIntraParameter, m_pSpi, nullptr, nullptr, nRequestID, true));
	return 0;
}

///SPBM跨品种抵扣参数查询
int CFtdcTraderApiImpl::ReqQrySPBMInterParameter(CThostFtdcQrySPBMInterParameterField* pQrySPBMInterParameter, int nRequestID)
{
	m_io_service.post(boost::bind(&CThostFtdcTraderSpi::OnRspQrySPBMInterParameter, m_pSpi, nullptr, nullptr, nRequestID, true));
	return 0;
}

///SPBM组合保证金套餐查询
int CFtdcTraderApiImpl::ReqQrySPBMPortfDefinition(CThostFtdcQrySPBMPortfDefinitionField* pQrySPBMPortfDefinition, int nRequestID)
{
	m_io_service.post(boost::bind(&CThostFtdcTraderSpi::OnRspQrySPBMPortfDefinition, m_pSpi, nullptr, nullptr, nRequestID, true));
	return 0;
}

///投资者SPBM套餐选择查询
int CFtdcTraderApiImpl::ReqQrySPBMInvestorPortfDef(CThostFtdcQrySPBMInvestorPortfDefField* pQrySPBMInvestorPortfDef, int nRequestID)
{
	m_io_service.post(boost::bind(&CThostFtdcTraderSpi::OnRspQrySPBMInvestorPortfDef, m_pSpi, nullptr, nullptr, nRequestID, true));
	return 0;
}

///投资者新型组合保证金系数查询
int CFtdcTraderApiImpl::ReqQryInvestorPortfMarginRatio(CThostFtdcQryInvestorPortfMarginRatioField* pQryInvestorPortfMarginRatio, int nRequestID)
{
	m_io_service.post(boost::bind(&CThostFtdcTraderSpi::OnRspQryInvestorPortfMarginRatio, m_pSpi, nullptr, nullptr, nRequestID, true));
	return 0;
}

///投资者产品SPBM明细查询
int CFtdcTraderApiImpl::ReqQryInvestorProdSPBMDetail(CThostFtdcQryInvestorProdSPBMDetailField* pQryInvestorProdSPBMDetail, int nRequestID)
{
	m_io_service.post(boost::bind(&CThostFtdcTraderSpi::OnRspQryInvestorProdSPBMDetail, m_pSpi, nullptr, nullptr, nRequestID, true));
	return 0;
}
#endif
