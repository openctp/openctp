/*
 * Copyright (c) 2026 openctp
 * BSD 3-Clause License, see LICENSE file for full terms.
 * https://github.com/openctp/openctp/tree/master/tools/ctpcmd/ctpcmd
 */

#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <algorithm>
#include <utility>
#ifdef _WIN32
#include <Windows.h>
#else
#include <iconv.h>
#endif
#include <regex>
#include "CLI.hpp"
#include "tinyxml2.h"
#include "json.hpp"
#include "ThostFtdcTraderApi.h"

#define CTPCMD_ERR_CODE_DEFAULT 9999
#define CTPCMD_VERSION "1.0.0"

enum CTPCMD
{
	CTPCMD_Subscribe,
	CTPCMD_QrySettlementInfo,
	CTPCMD_SettlementInfoConfirm,
	CTPCMD_QrySettlementInfoConfirm,
	CTPCMD_QryInvestor,
	CTPCMD_QryTradingCode,
	CTPCMD_QryTradingAccount,
	CTPCMD_QryInvestorPosition,
	CTPCMD_QryInvestorPositionDetail,
	CTPCMD_QryOrder,
	CTPCMD_QryTrade,
	CTPCMD_QryExchange,
	CTPCMD_QryProduct,
	CTPCMD_QryInstrument,
	CTPCMD_QryDepthMarketData,
	CTPCMD_QryInstrumentCommissionRate,
	CTPCMD_QryInstrumentOrderCommRate,
	CTPCMD_QryOptionInstrCommRate,
	CTPCMD_QryInstrumentMarginRate,
	CTPCMD_QryTransferSerial,
	CTPCMD_QryAccountregister,
	CTPCMD_QryTransferBank,
	CTPCMD_Buy,
	CTPCMD_Sell,
	CTPCMD_Cancel
};

struct CTPCMD_Parameters {
	std::string InstrumentID;
	std::string ExchangeID;
	std::string ProductID;
	std::string OrderSysID;
	std::string TradingDay;
	TThostFtdcOffsetFlagType OffsetFlag;
	TThostFtdcHedgeFlagType HedgeFlag;
	TThostFtdcOrderPriceTypeType OrderPriceType;
	double Price;
	int Volume;
};

// GBK -> UTF-8
std::string GBKToUTF8(const std::string& gbk)
{
	if (gbk.empty()) return std::string();

#ifdef _WIN32
	// ---- Windows: (GBK -> UTF-16 -> UTF-8) ----
	// 1. GBK -> UTF-16
	int wlen = MultiByteToWideChar(936, 0, gbk.c_str(), (int)gbk.size(), nullptr, 0);
	if (wlen <= 0) return std::string();

	std::wstring wstr(wlen, L'\0');
	MultiByteToWideChar(936, 0, gbk.c_str(), (int)gbk.size(), &wstr[0], wlen);

	// 2. UTF-16 -> UTF-8
	int ulen = WideCharToMultiByte(CP_UTF8, 0, wstr.c_str(), wlen, nullptr, 0, nullptr, nullptr);
	if (ulen <= 0) return std::string();

	std::string utf8(ulen, '\0');
	WideCharToMultiByte(CP_UTF8, 0, wstr.c_str(), wlen, &utf8[0], ulen, nullptr, nullptr);
	return utf8;

#else
	// ---- Linux/macOS: iconv ----
	iconv_t cd = iconv_open("UTF-8", "GBK");
	if (cd == (iconv_t)-1) return std::string();

	size_t inLeft = gbk.size();
	size_t outLeft = gbk.size() * 4 + 4;
	std::string utf8(outLeft, '\0');

	char* inBuf = const_cast<char*>(gbk.data());
	char* outBuf = &utf8[0];

	size_t ret = iconv(cd, &inBuf, &inLeft, &outBuf, &outLeft);
	iconv_close(cd);

	if (ret == (size_t)-1) return std::string();

	utf8.resize(utf8.size() - outLeft);
	return utf8;
#endif
}

std::string StringJoin(const std::vector<std::string>& vec, const std::string& sep = " ")
{
	if (vec.empty()) return "";
	std::ostringstream oss;
	oss << vec[0];
	for (size_t i = 1; i < vec.size(); ++i)
		oss << sep << vec[i];
	return oss.str();
}

#define DBLMAX_TO_NULL(value) ((value) == DBL_MAX ? json(nullptr) : json(value))
#define ZERO_TO_EMPTY_STR(value) ((value) == '\0' ? json("") : json(std::string(1, value)))

using namespace ctp_sopt;

class CCTPTdSpiImpl :public CThostFtdcTraderSpi
{
public:
	CCTPTdSpiImpl(CThostFtdcTraderApi* pTdApi, std::string BrokerID, std::string AppID, std::string AuthCode, std::string UserProductInfo, std::string UserID, std::string Password, CTPCMD cmd, CTPCMD_Parameters params, bool pretty_print):
		m_pTdApi(pTdApi),
		m_BrokerID(std::move(BrokerID)),
		m_AppID(std::move(AppID)),
		m_AuthCode(std::move(AuthCode)),
		m_UserProductInfo(std::move(UserProductInfo)),
		m_UserID(std::move(UserID)),
		m_Password(std::move(Password)),
		m_cmd(cmd),
		m_params(params)
	{
		if (pretty_print)
			m_json_indent = 2;
		else
			m_json_indent = -1;
	}

	std::string error_message(int rsp_code, const char* rsp_message)
	{
		using json = nlohmann::ordered_json;

		json msg;
		msg["rsp_code"] = rsp_code;
		msg["rsp_message"] = GBKToUTF8(rsp_message);

		return msg.dump(m_json_indent);
	}

	void OnFrontDisconnected(int nReason)
	{
		std::cout << error_message(CTPCMD_ERR_CODE_DEFAULT, "Disconnected.") << std::endl;
		exit(0);
	}

	void OnFrontConnected()
	{
		CThostFtdcReqAuthenticateField Req{};
		strncpy(Req.BrokerID, m_BrokerID.c_str(), sizeof(Req.BrokerID) - 1);
		strncpy(Req.UserID, m_UserID.c_str(), sizeof(Req.UserID) - 1);
		strncpy(Req.UserProductInfo, m_UserProductInfo.c_str(), sizeof(Req.UserProductInfo) - 1);
		strncpy(Req.AppID, m_AppID.c_str(), sizeof(Req.AppID) - 1);
		strncpy(Req.AuthCode, m_AuthCode.c_str(), sizeof(Req.AuthCode) - 1);
		if (m_pTdApi->ReqAuthenticate(&Req, 0) != 0) {
			std::cout << error_message(CTPCMD_ERR_CODE_DEFAULT, "Authenticate failed.") << std::endl;
			exit(0);
		}
	}

	void OnRspAuthenticate(CThostFtdcRspAuthenticateField* pRspAuthenticateField, CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast)
	{
		if (pRspInfo && pRspInfo->ErrorID != 0) {
			std::cout << error_message(pRspInfo->ErrorID, pRspInfo->ErrorMsg) << std::endl;
			exit(0);
		}

		CThostFtdcReqUserLoginField Req{};
		strncpy(Req.BrokerID, m_BrokerID.c_str(), sizeof(Req.BrokerID) - 1);
		strncpy(Req.UserID, m_UserID.c_str(), sizeof(Req.UserID) - 1);
		strncpy(Req.Password, m_Password.c_str(), sizeof(Req.Password) - 1);
		strncpy(Req.UserProductInfo, m_UserProductInfo.c_str(), sizeof(Req.UserProductInfo) - 1);

#ifdef __APPLE__	/* Apple Mac OS X */
		TThostFtdcSystemInfoLenType SystemInfoLen = 0;
		TThostFtdcClientSystemInfoType ClientSystemInfo = { 0 };
		if (m_pTdApi->ReqUserLogin(&Req, 0, SystemInfoLen, ClientSystemInfo) != 0) {
#else
		if (m_pTdApi->ReqUserLogin(&Req, 0) != 0) {
#endif
			std::cout << error_message(CTPCMD_ERR_CODE_DEFAULT, "Login failed.") << std::endl;
			exit(0);
		}
		}

	void OnRspUserLogin(CThostFtdcRspUserLoginField * pRspUserLogin, CThostFtdcRspInfoField * pRspInfo, int nRequestID, bool bIsLast)
	{
		if (pRspInfo && pRspInfo->ErrorID != 0) {
			std::cout << error_message(pRspInfo->ErrorID, pRspInfo->ErrorMsg) << std::endl;
			exit(0);
		}

		strncpy(m_TradingDay, pRspUserLogin->TradingDay, sizeof(m_TradingDay) - 1);
		m_FrontID = pRspUserLogin->FrontID;
		m_SessionID = pRspUserLogin->SessionID;

		switch (m_cmd)
		{
		case CTPCMD_Subscribe:
			break;
		case CTPCMD_QrySettlementInfo:
		{
			CThostFtdcQrySettlementInfoField Req{};

			strncpy(Req.BrokerID, m_BrokerID.c_str(), sizeof(Req.BrokerID) - 1);
			strncpy(Req.InvestorID, m_UserID.c_str(), sizeof(Req.InvestorID) - 1);
			strncpy(Req.TradingDay, m_params.TradingDay.c_str(), sizeof(Req.TradingDay) - 1);

			if (m_pTdApi->ReqQrySettlementInfo(&Req, 0) != 0) {
				std::cout << error_message(CTPCMD_ERR_CODE_DEFAULT, "QrySettlementInfo failed.") << std::endl;
				exit(0);
			}
		}
		break;
		case CTPCMD_SettlementInfoConfirm:
		{
			CThostFtdcSettlementInfoConfirmField Req{};

			strncpy(Req.BrokerID, m_BrokerID.c_str(), sizeof(Req.BrokerID) - 1);
			strncpy(Req.InvestorID, m_UserID.c_str(), sizeof(Req.InvestorID) - 1);
			strncpy(Req.ConfirmDate, pRspUserLogin->TradingDay, sizeof(Req.ConfirmDate) - 1);

			if (m_pTdApi->ReqSettlementInfoConfirm(&Req, 0) != 0) {
				std::cout << error_message(CTPCMD_ERR_CODE_DEFAULT, "SettlementInfoConfirm failed.") << std::endl;
				exit(0);
			}
		}
		break;
		case CTPCMD_QrySettlementInfoConfirm:
		{
			CThostFtdcQrySettlementInfoConfirmField Req{};

			strncpy(Req.BrokerID, m_BrokerID.c_str(), sizeof(Req.BrokerID) - 1);
			strncpy(Req.InvestorID, m_UserID.c_str(), sizeof(Req.InvestorID) - 1);

			if (m_pTdApi->ReqQrySettlementInfoConfirm(&Req, 0) != 0) {
				std::cout << error_message(CTPCMD_ERR_CODE_DEFAULT, "QrySettlementInfoConfirm failed.") << std::endl;
				exit(0);
			}
		}
		break;
		case CTPCMD_QryInvestor:
		{
			CThostFtdcQryInvestorField Req{};

			strncpy(Req.BrokerID, m_BrokerID.c_str(), sizeof(Req.BrokerID) - 1);
			strncpy(Req.InvestorID, m_UserID.c_str(), sizeof(Req.InvestorID) - 1);

			if (m_pTdApi->ReqQryInvestor(&Req, 0) != 0) {
				std::cout << error_message(CTPCMD_ERR_CODE_DEFAULT, "QryInvestor failed.") << std::endl;
				exit(0);
			}
		}
		break;
		case CTPCMD_QryTradingCode:
		{
			CThostFtdcQryTradingCodeField Req{};

			strncpy(Req.BrokerID, m_BrokerID.c_str(), sizeof(Req.BrokerID) - 1);
			strncpy(Req.InvestorID, m_UserID.c_str(), sizeof(Req.InvestorID) - 1);

			if (m_pTdApi->ReqQryTradingCode(&Req, 0) != 0) {
				std::cout << error_message(CTPCMD_ERR_CODE_DEFAULT, "QryTradingCode failed.") << std::endl;
				exit(0);
			}
		}
		break;
		case CTPCMD_QryTradingAccount:
		{
			CThostFtdcQryTradingAccountField Req{};

			strncpy(Req.BrokerID, m_BrokerID.c_str(), sizeof(Req.BrokerID) - 1);
			strncpy(Req.InvestorID, m_UserID.c_str(), sizeof(Req.InvestorID) - 1);

			if (m_pTdApi->ReqQryTradingAccount(&Req, 0) != 0) {
				std::cout << error_message(CTPCMD_ERR_CODE_DEFAULT, "QryTradingAccount failed.") << std::endl;
				exit(0);
			}
		}
		break;
		case CTPCMD_QryInvestorPosition:
		{
			CThostFtdcQryInvestorPositionField Req{};

			strncpy(Req.BrokerID, m_BrokerID.c_str(), sizeof(Req.BrokerID) - 1);
			strncpy(Req.InvestorID, m_UserID.c_str(), sizeof(Req.InvestorID) - 1);
			strncpy(Req.ExchangeID, m_params.ExchangeID.c_str(), sizeof(Req.ExchangeID) - 1);
			strncpy(Req.InstrumentID, m_params.InstrumentID.c_str(), sizeof(Req.InstrumentID) - 1);

			if (m_pTdApi->ReqQryInvestorPosition(&Req, 0) != 0) {
				std::cout << error_message(CTPCMD_ERR_CODE_DEFAULT, "QryInvestorPosition failed.") << std::endl;
				exit(0);
			}
		}
		break;
		case CTPCMD_QryInvestorPositionDetail:
		{
			CThostFtdcQryInvestorPositionDetailField Req{};

			strncpy(Req.BrokerID, m_BrokerID.c_str(), sizeof(Req.BrokerID) - 1);
			strncpy(Req.InvestorID, m_UserID.c_str(), sizeof(Req.InvestorID) - 1);
			strncpy(Req.ExchangeID, m_params.ExchangeID.c_str(), sizeof(Req.ExchangeID) - 1);
			strncpy(Req.InstrumentID, m_params.InstrumentID.c_str(), sizeof(Req.InstrumentID) - 1);

			if (m_pTdApi->ReqQryInvestorPositionDetail(&Req, 0) != 0) {
				std::cout << error_message(CTPCMD_ERR_CODE_DEFAULT, "QryInvestorPositionDetail failed.") << std::endl;
				exit(0);
			}
		}
		break;
		case CTPCMD_QryOrder:
		{
			CThostFtdcQryOrderField Req{};

			strncpy(Req.BrokerID, m_BrokerID.c_str(), sizeof(Req.BrokerID) - 1);
			strncpy(Req.InvestorID, m_UserID.c_str(), sizeof(Req.InvestorID) - 1);
			strncpy(Req.ExchangeID, m_params.ExchangeID.c_str(), sizeof(Req.ExchangeID) - 1);
			strncpy(Req.InstrumentID, m_params.InstrumentID.c_str(), sizeof(Req.InstrumentID) - 1);
			strncpy(Req.OrderSysID, m_params.OrderSysID.c_str(), sizeof(Req.OrderSysID) - 1);

			if (m_pTdApi->ReqQryOrder(&Req, 0) != 0) {
				std::cout << error_message(CTPCMD_ERR_CODE_DEFAULT, "QryOrder failed.") << std::endl;
				exit(0);
			}
		}
		break;
		case CTPCMD_QryTrade:
		{
			CThostFtdcQryTradeField Req{};

			strncpy(Req.BrokerID, m_BrokerID.c_str(), sizeof(Req.BrokerID) - 1);
			strncpy(Req.InvestorID, m_UserID.c_str(), sizeof(Req.InvestorID) - 1);
			strncpy(Req.ExchangeID, m_params.ExchangeID.c_str(), sizeof(Req.ExchangeID) - 1);
			strncpy(Req.InstrumentID, m_params.InstrumentID.c_str(), sizeof(Req.InstrumentID) - 1);

			if (m_pTdApi->ReqQryTrade(&Req, 0) != 0) {
				std::cout << error_message(CTPCMD_ERR_CODE_DEFAULT, "QryTrade failed.") << std::endl;
				exit(0);
			}
		}
		break;
		case CTPCMD_QryExchange:
		{
			CThostFtdcQryExchangeField Req{};

			strncpy(Req.ExchangeID, m_params.ExchangeID.c_str(), sizeof(Req.ExchangeID) - 1);

			if (m_pTdApi->ReqQryExchange(&Req, 0) != 0) {
				std::cout << error_message(CTPCMD_ERR_CODE_DEFAULT, "QryExchange failed.") << std::endl;
				exit(0);
			}
		}
		break;
		case CTPCMD_QryProduct:
		{
			CThostFtdcQryProductField Req{};

			strncpy(Req.ExchangeID, m_params.ExchangeID.c_str(), sizeof(Req.ExchangeID) - 1);
			strncpy(Req.ProductID, m_params.ProductID.c_str(), sizeof(Req.ProductID) - 1);

			if (m_pTdApi->ReqQryProduct(&Req, 0) != 0) {
				std::cout << error_message(CTPCMD_ERR_CODE_DEFAULT, "QryProduct failed.") << std::endl;
				exit(0);
			}
		}
		break;
		case CTPCMD_QryInstrument:
		{
			CThostFtdcQryInstrumentField Req{};

			strncpy(Req.ExchangeID, m_params.ExchangeID.c_str(), sizeof(Req.ExchangeID) - 1);
			strncpy(Req.ProductID, m_params.ProductID.c_str(), sizeof(Req.ProductID) - 1);
			strncpy(Req.InstrumentID, m_params.InstrumentID.c_str(), sizeof(Req.InstrumentID) - 1);

			if (m_pTdApi->ReqQryInstrument(&Req, 0) != 0) {
				std::cout << error_message(CTPCMD_ERR_CODE_DEFAULT, "QryInstrument failed.") << std::endl;
				exit(0);
			}
		}
		break;
		case CTPCMD_QryDepthMarketData:
		{
			CThostFtdcQryDepthMarketDataField Req{};

			strncpy(Req.ExchangeID, m_params.ExchangeID.c_str(), sizeof(Req.ExchangeID) - 1);
			strncpy(Req.InstrumentID, m_params.InstrumentID.c_str(), sizeof(Req.InstrumentID) - 1);

			if (m_pTdApi->ReqQryDepthMarketData(&Req, 0) != 0) {
				std::cout << error_message(CTPCMD_ERR_CODE_DEFAULT, "QryDepthMarketData failed.") << std::endl;
				exit(0);
			}
		}
		break;
		case CTPCMD_QryInstrumentCommissionRate:
		{
			CThostFtdcQryInstrumentCommissionRateField Req{};

			strncpy(Req.BrokerID, m_BrokerID.c_str(), sizeof(Req.BrokerID) - 1);
			strncpy(Req.InvestorID, m_UserID.c_str(), sizeof(Req.InvestorID) - 1);
			strncpy(Req.ExchangeID, m_params.ExchangeID.c_str(), sizeof(Req.ExchangeID) - 1);
			strncpy(Req.InstrumentID, m_params.InstrumentID.c_str(), sizeof(Req.InstrumentID) - 1);

			if (m_pTdApi->ReqQryInstrumentCommissionRate(&Req, 0) != 0) {
				std::cout << error_message(CTPCMD_ERR_CODE_DEFAULT, "QryInstrumentCommissionRate failed.") << std::endl;
				exit(0);
			}
		}
		break;
		case CTPCMD_QryInstrumentOrderCommRate:
		{
			CThostFtdcQryInstrumentOrderCommRateField Req{};

			strncpy(Req.BrokerID, m_BrokerID.c_str(), sizeof(Req.BrokerID) - 1);
			strncpy(Req.InvestorID, m_UserID.c_str(), sizeof(Req.InvestorID) - 1);
			strncpy(Req.InstrumentID, m_params.InstrumentID.c_str(), sizeof(Req.InstrumentID) - 1);

			if (m_pTdApi->ReqQryInstrumentOrderCommRate(&Req, 0) != 0) {
				std::cout << error_message(CTPCMD_ERR_CODE_DEFAULT, "QryInstrumentOrderCommRate failed.") << std::endl;
				exit(0);
			}
		}
		break;
		case CTPCMD_QryOptionInstrCommRate:
		{
			CThostFtdcQryOptionInstrCommRateField Req{};

			strncpy(Req.BrokerID, m_BrokerID.c_str(), sizeof(Req.BrokerID) - 1);
			strncpy(Req.InvestorID, m_UserID.c_str(), sizeof(Req.InvestorID) - 1);
			strncpy(Req.ExchangeID, m_params.ExchangeID.c_str(), sizeof(Req.ExchangeID) - 1);
			strncpy(Req.InstrumentID, m_params.InstrumentID.c_str(), sizeof(Req.InstrumentID) - 1);

			if (m_pTdApi->ReqQryOptionInstrCommRate(&Req, 0) != 0) {
				std::cout << error_message(CTPCMD_ERR_CODE_DEFAULT, "QryOptionInstrCommRate failed.") << std::endl;
				exit(0);
			}
		}
		break;
		case CTPCMD_QryInstrumentMarginRate:
		{
			CThostFtdcQryInstrumentMarginRateField Req{};

			strncpy(Req.BrokerID, m_BrokerID.c_str(), sizeof(Req.BrokerID) - 1);
			strncpy(Req.InvestorID, m_UserID.c_str(), sizeof(Req.InvestorID) - 1);
			strncpy(Req.ExchangeID, m_params.ExchangeID.c_str(), sizeof(Req.ExchangeID) - 1);
			strncpy(Req.InstrumentID, m_params.InstrumentID.c_str(), sizeof(Req.InstrumentID) - 1);

			if (m_pTdApi->ReqQryInstrumentMarginRate(&Req, 0) != 0) {
				std::cout << error_message(CTPCMD_ERR_CODE_DEFAULT, "QryInstrumentMarginRate failed.") << std::endl;
				exit(0);
			}
		}
		break;
		case CTPCMD_QryTransferSerial:
		{
			CThostFtdcQryTransferSerialField Req{};

			strncpy(Req.BrokerID, m_BrokerID.c_str(), sizeof(Req.BrokerID) - 1);

			if (m_pTdApi->ReqQryTransferSerial(&Req, 0) != 0) {
				std::cout << error_message(CTPCMD_ERR_CODE_DEFAULT, "QryTransferSerial failed.") << std::endl;
				exit(0);
			}
		}
		break;
		case CTPCMD_QryAccountregister:
		{
			CThostFtdcQryAccountregisterField Req{};

			strncpy(Req.BrokerID, m_BrokerID.c_str(), sizeof(Req.BrokerID) - 1);

			if (m_pTdApi->ReqQryAccountregister(&Req, 0) != 0) {
				std::cout << error_message(CTPCMD_ERR_CODE_DEFAULT, "QryAccountregister failed.") << std::endl;
				exit(0);
			}
		}
		break;
		case CTPCMD_QryTransferBank:
		{
			CThostFtdcQryTransferBankField Req{};

			if (m_pTdApi->ReqQryTransferBank(&Req, 0) != 0) {
				std::cout << error_message(CTPCMD_ERR_CODE_DEFAULT, "QryTransferBank failed.") << std::endl;
				exit(0);
			}
		}
		break;
		case CTPCMD_Buy:
		{
			CThostFtdcInputOrderField Req{};

			strncpy(Req.BrokerID, m_BrokerID.c_str(), sizeof(Req.BrokerID) - 1);
			strncpy(Req.InvestorID, m_UserID.c_str(), sizeof(Req.InvestorID) - 1);
			strncpy(Req.UserID, m_UserID.c_str(), sizeof(Req.UserID) - 1);
			strncpy(Req.ExchangeID, m_params.ExchangeID.c_str(), sizeof(Req.ExchangeID) - 1);
			strncpy(Req.InstrumentID, m_params.InstrumentID.c_str(), sizeof(Req.InstrumentID) - 1);
			Req.Direction = THOST_FTDC_D_Buy;
			Req.CombOffsetFlag[0] = m_params.OffsetFlag;
			Req.CombHedgeFlag[0] = m_params.HedgeFlag;
			Req.VolumeTotalOriginal = m_params.Volume;
			Req.LimitPrice = m_params.Price;
			Req.OrderPriceType = m_params.OrderPriceType;
			strncpy(Req.OrderRef, "1", sizeof(Req.OrderRef) - 1);
			Req.TimeCondition = THOST_FTDC_TC_GFD;
			Req.VolumeCondition = THOST_FTDC_VC_AV;
			Req.MinVolume = 1;
			Req.ContingentCondition = THOST_FTDC_CC_Immediately;
			Req.ForceCloseReason = THOST_FTDC_FCC_NotForceClose;
			Req.IsAutoSuspend = 0;
			Req.UserForceClose = 0;

			if (m_pTdApi->ReqOrderInsert(&Req, 0) != 0) {
				std::cout << error_message(CTPCMD_ERR_CODE_DEFAULT, "OrderInsert failed.") << std::endl;
				exit(0);
			}
		}
		break;
		case CTPCMD_Sell:
		{
			CThostFtdcInputOrderField Req{};

			strncpy(Req.BrokerID, m_BrokerID.c_str(), sizeof(Req.BrokerID) - 1);
			strncpy(Req.InvestorID, m_UserID.c_str(), sizeof(Req.InvestorID) - 1);
			strncpy(Req.UserID, m_UserID.c_str(), sizeof(Req.UserID) - 1);
			strncpy(Req.ExchangeID, m_params.ExchangeID.c_str(), sizeof(Req.ExchangeID) - 1);
			strncpy(Req.InstrumentID, m_params.InstrumentID.c_str(), sizeof(Req.InstrumentID) - 1);
			Req.Direction = THOST_FTDC_D_Sell;
			Req.CombOffsetFlag[0] = m_params.OffsetFlag;
			Req.CombHedgeFlag[0] = m_params.HedgeFlag;
			Req.VolumeTotalOriginal = m_params.Volume;
			Req.LimitPrice = m_params.Price;
			Req.OrderPriceType = m_params.OrderPriceType;
			strncpy(Req.OrderRef, "1", sizeof(Req.OrderRef) - 1);
			Req.TimeCondition = THOST_FTDC_TC_GFD;
			Req.VolumeCondition = THOST_FTDC_VC_AV;
			Req.MinVolume = 1;
			Req.ContingentCondition = THOST_FTDC_CC_Immediately;
			Req.ForceCloseReason = THOST_FTDC_FCC_NotForceClose;
			Req.IsAutoSuspend = 0;
			Req.UserForceClose = 0;

			if (m_pTdApi->ReqOrderInsert(&Req, 0) != 0) {
				std::cout << error_message(CTPCMD_ERR_CODE_DEFAULT, "OrderInsert failed.") << std::endl;
				exit(0);
			}
		}
		break;
		case CTPCMD_Cancel:
		{
			CThostFtdcInputOrderActionField Req{};

			strncpy(Req.BrokerID, m_BrokerID.c_str(), sizeof(Req.BrokerID) - 1);
			strncpy(Req.InvestorID, m_UserID.c_str(), sizeof(Req.InvestorID) - 1);
			strncpy(Req.UserID, m_UserID.c_str(), sizeof(Req.UserID) - 1);
			strncpy(Req.ExchangeID, m_params.ExchangeID.c_str(), sizeof(Req.ExchangeID) - 1);
			strncpy(Req.InstrumentID, m_params.InstrumentID.c_str(), sizeof(Req.InstrumentID) - 1);
			strncpy(Req.OrderSysID, m_params.OrderSysID.c_str(), sizeof(Req.OrderSysID) - 1);
			Req.ActionFlag = THOST_FTDC_AF_Delete;
			Req.OrderActionRef = 1;

			if (m_pTdApi->ReqOrderAction(&Req, 0) != 0) {
				std::cout << error_message(CTPCMD_ERR_CODE_DEFAULT, "OrderAction failed.") << std::endl;
				exit(0);
			}
		}
		break;
		default:
			std::cout << error_message(CTPCMD_ERR_CODE_DEFAULT, "No cmd.") << std::endl;
			exit(0);
			break;
		}
	}

	void OnRspError(CThostFtdcRspInfoField * pRspInfo, int nRequestID, bool bIsLast)
	{
		if (pRspInfo && pRspInfo->ErrorID != 0) {
			std::cout << error_message(pRspInfo->ErrorID, pRspInfo->ErrorMsg) << std::endl;
			exit(0);
		}
	}

	void OnRspQrySettlementInfo(CThostFtdcSettlementInfoField * pSettlementInfo, CThostFtdcRspInfoField * pRspInfo, int nRequestID, bool bIsLast)
	{
		if (pRspInfo && pRspInfo->ErrorID != 0) {
			std::cout << error_message(pRspInfo->ErrorID, pRspInfo->ErrorMsg) << std::endl;
			exit(0);
		}

		if (pSettlementInfo)
			m_vSettlementInfo.push_back(*pSettlementInfo);

		if (bIsLast) {
			using json = nlohmann::ordered_json;

			json msg;
			msg["rsp_code"] = 0;
			msg["rsp_message"] = "";

			json rsp;
			std::string FullContent;
			for (auto item : m_vSettlementInfo) {
				if (rsp.size() == 0) {
					rsp["TradingDay"] = item.TradingDay;
					rsp["SettlementID"] = item.SettlementID;
					rsp["BrokerID"] = item.BrokerID;
					rsp["InvestorID"] = item.InvestorID;
					rsp["SequenceNo"] = item.SequenceNo;
					FullContent = item.Content;
					rsp["AccountID"] = item.AccountID;
					rsp["CurrencyID"] = item.CurrencyID;
				}
				else {
					FullContent += item.Content;
				}
			}
			rsp["Content"] = GBKToUTF8(FullContent);

			msg["data"] = rsp;

			std::cout << msg.dump(m_json_indent) << std::endl;

			exit(0);
		}
	}

	void OnRspSettlementInfoConfirm(CThostFtdcSettlementInfoConfirmField * pSettlementInfoConfirm, CThostFtdcRspInfoField * pRspInfo, int nRequestID, bool bIsLast)
	{
		if (pRspInfo && pRspInfo->ErrorID != 0) {
			std::cout << error_message(pRspInfo->ErrorID, pRspInfo->ErrorMsg) << std::endl;
			exit(0);
		}

		using json = nlohmann::ordered_json;

		json msg;
		msg["rsp_code"] = 0;
		msg["rsp_message"] = "";

		json rsp;
		rsp["BrokerID"] = pSettlementInfoConfirm->BrokerID;
		rsp["InvestorID"] = pSettlementInfoConfirm->InvestorID;
		rsp["ConfirmDate"] = pSettlementInfoConfirm->ConfirmDate;
		rsp["ConfirmTime"] = pSettlementInfoConfirm->ConfirmTime;
		rsp["SettlementID"] = pSettlementInfoConfirm->SettlementID;
		rsp["AccountID"] = pSettlementInfoConfirm->AccountID;
		rsp["CurrencyID"] = pSettlementInfoConfirm->CurrencyID;

		msg["data"] = rsp;

		std::cout << msg.dump(m_json_indent) << std::endl;

		exit(0);
	}

	void OnRspQrySettlementInfoConfirm(CThostFtdcSettlementInfoConfirmField * pSettlementInfoConfirm, CThostFtdcRspInfoField * pRspInfo, int nRequestID, bool bIsLast)
	{
		if (pRspInfo && pRspInfo->ErrorID != 0) {
			std::cout << error_message(pRspInfo->ErrorID, pRspInfo->ErrorMsg) << std::endl;
			exit(0);
		}

		if (pSettlementInfoConfirm)
			m_vSettlementInfoConfirm.push_back(*pSettlementInfoConfirm);

		if (bIsLast) {
			using json = nlohmann::ordered_json;

			json msg;
			msg["rsp_code"] = 0;
			msg["rsp_message"] = "";

			msg["data"] = json::array();
			for (auto item : m_vSettlementInfoConfirm) {
				json rsp;
				rsp["BrokerID"] = item.BrokerID;
				rsp["InvestorID"] = item.InvestorID;
				rsp["ConfirmDate"] = item.ConfirmDate;
				rsp["ConfirmTime"] = item.ConfirmTime;
				rsp["SettlementID"] = item.SettlementID;
				rsp["AccountID"] = item.AccountID;
				rsp["CurrencyID"] = item.CurrencyID;

				msg["data"].push_back(rsp);
			}

			std::cout << msg.dump(m_json_indent) << std::endl;

			exit(0);
		}
	}

	void OnRspQryInvestor(CThostFtdcInvestorField * pInvestor, CThostFtdcRspInfoField * pRspInfo, int nRequestID, bool bIsLast)
	{
		if (pRspInfo && pRspInfo->ErrorID != 0) {
			std::cout << error_message(pRspInfo->ErrorID, pRspInfo->ErrorMsg) << std::endl;
			exit(0);
		}

		if (pInvestor)
			m_vInvestor.push_back(*pInvestor);

		if (bIsLast) {
			using json = nlohmann::ordered_json;

			json msg;
			msg["rsp_code"] = 0;
			msg["rsp_message"] = "";

			msg["data"] = json::array();
			for (auto item : m_vInvestor) {
				json rsp;
				rsp["InvestorID"] = item.InvestorID;
				rsp["BrokerID"] = item.BrokerID;
				rsp["InvestorGroupID"] = item.InvestorGroupID;
				rsp["InvestorName"] = GBKToUTF8(item.InvestorName);
				rsp["IdentifiedCardType"] = ZERO_TO_EMPTY_STR(item.IdentifiedCardType);
				rsp["IdentifiedCardNo"] = item.IdentifiedCardNo;
				rsp["IsActive"] = item.IsActive;
				rsp["Telephone"] = item.Telephone;
				rsp["Address"] = GBKToUTF8(item.Address);
				rsp["OpenDate"] = item.OpenDate;
				rsp["Mobile"] = item.Mobile;
				rsp["CommModelID"] = item.CommModelID;
				rsp["MarginModelID"] = item.MarginModelID;

				msg["data"].push_back(rsp);
			}

			std::cout << msg.dump(m_json_indent) << std::endl;

			exit(0);
		}
	}

	void OnRspQryTradingCode(CThostFtdcTradingCodeField * pTradingCode, CThostFtdcRspInfoField * pRspInfo, int nRequestID, bool bIsLast)
	{
		if (pRspInfo && pRspInfo->ErrorID != 0) {
			std::cout << error_message(pRspInfo->ErrorID, pRspInfo->ErrorMsg) << std::endl;
			exit(0);
		}

		if (pTradingCode)
			m_vTradingCode.push_back(*pTradingCode);

		if (bIsLast) {
			using json = nlohmann::ordered_json;

			json msg;
			msg["rsp_code"] = 0;
			msg["rsp_message"] = "";

			msg["data"] = json::array();
			for (auto item : m_vTradingCode) {
				json rsp;
				rsp["InvestorID"] = item.InvestorID;
				rsp["BrokerID"] = item.BrokerID;
				rsp["ExchangeID"] = item.ExchangeID;
				rsp["ClientID"] = item.ClientID;
				rsp["IsActive"] = item.IsActive;
				rsp["ClientIDType"] = ZERO_TO_EMPTY_STR(item.ClientIDType);
				rsp["BranchID"] = item.BranchID;
				rsp["BizType"] = ZERO_TO_EMPTY_STR(item.BizType);
				rsp["InvestUnitID"] = item.InvestUnitID;

				msg["data"].push_back(rsp);
			}

			std::cout << msg.dump(m_json_indent) << std::endl;

			exit(0);
		}
	}

	void OnRspQryTradingAccount(CThostFtdcTradingAccountField * pTradingAccount, CThostFtdcRspInfoField * pRspInfo, int nRequestID, bool bIsLast)
	{
		if (pRspInfo && pRspInfo->ErrorID != 0) {
			std::cout << error_message(pRspInfo->ErrorID, pRspInfo->ErrorMsg) << std::endl;
			exit(0);
		}

		if (pTradingAccount)
			m_vTradingAccount.push_back(*pTradingAccount);

		if (bIsLast) {
			using json = nlohmann::ordered_json;

			json msg;
			msg["rsp_code"] = 0;
			msg["rsp_message"] = "";

			msg["data"] = json::array();
			for (auto item : m_vTradingAccount) {
				json rsp;
				rsp["BrokerID"] = item.BrokerID;
				rsp["AccountID"] = item.AccountID;
				rsp["PreMortgage"] = item.PreMortgage;
				rsp["PreCredit"] = item.PreCredit;
				rsp["PreDeposit"] = item.PreDeposit;
				rsp["PreBalance"] = item.PreBalance;
				rsp["PreMargin"] = item.PreMargin;
				rsp["InterestBase"] = item.InterestBase;
				rsp["Interest"] = item.Interest;
				rsp["Deposit"] = item.Deposit;
				rsp["Withdraw"] = item.Withdraw;
				rsp["FrozenMargin"] = item.FrozenMargin;
				rsp["FrozenCash"] = item.FrozenCash;
				rsp["FrozenCommission"] = item.FrozenCommission;
				rsp["CurrMargin"] = item.CurrMargin;
				rsp["CashIn"] = item.CashIn;
				rsp["Commission"] = item.Commission;
				rsp["CloseProfit"] = item.CloseProfit;
				rsp["PositionProfit"] = item.PositionProfit;
				rsp["Balance"] = item.Balance;
				rsp["Available"] = item.Available;
				rsp["WithdrawQuota"] = item.WithdrawQuota;
				rsp["Reserve"] = item.Reserve;
				rsp["TradingDay"] = item.TradingDay;
				rsp["SettlementID"] = item.SettlementID;
				rsp["Credit"] = item.Credit;
				rsp["Mortgage"] = item.Mortgage;
				rsp["ExchangeMargin"] = item.ExchangeMargin;
				rsp["DeliveryMargin"] = item.DeliveryMargin;
				rsp["ExchangeDeliveryMargin"] = item.ExchangeDeliveryMargin;
				rsp["ReserveBalance"] = item.ReserveBalance;
				rsp["CurrencyID"] = item.CurrencyID;
				rsp["PreFundMortgageIn"] = item.PreFundMortgageIn;
				rsp["PreFundMortgageOut"] = item.PreFundMortgageOut;
				rsp["FundMortgageIn"] = item.FundMortgageIn;
				rsp["FundMortgageOut"] = item.FundMortgageOut;
				rsp["FundMortgageAvailable"] = item.FundMortgageAvailable;
				rsp["MortgageableFund"] = item.MortgageableFund;
				rsp["SpecProductMargin"] = item.SpecProductMargin;
				rsp["SpecProductFrozenMargin"] = item.SpecProductFrozenMargin;
				rsp["SpecProductCommission"] = item.SpecProductCommission;
				rsp["SpecProductFrozenCommission"] = item.SpecProductFrozenCommission;
				rsp["SpecProductPositionProfit"] = item.SpecProductPositionProfit;
				rsp["SpecProductCloseProfit"] = item.SpecProductCloseProfit;
				rsp["SpecProductPositionProfitByAlg"] = item.SpecProductPositionProfitByAlg;
				rsp["SpecProductExchangeMargin"] = item.SpecProductExchangeMargin;
				rsp["BizType"] = ZERO_TO_EMPTY_STR(item.BizType);
				rsp["FrozenSwap"] = item.FrozenSwap;
				rsp["RemainSwap"] = item.RemainSwap;

				msg["data"].push_back(rsp);
			}

			std::cout << msg.dump(m_json_indent) << std::endl;

			exit(0);
		}
	}

	void OnRspQryInvestorPosition(CThostFtdcInvestorPositionField * pInvestorPosition, CThostFtdcRspInfoField * pRspInfo, int nRequestID, bool bIsLast)
	{
		if (pRspInfo && pRspInfo->ErrorID != 0) {
			std::cout << error_message(pRspInfo->ErrorID, pRspInfo->ErrorMsg) << std::endl;
			exit(0);
		}

		if (pInvestorPosition)
			m_vInvestorPosition.push_back(*pInvestorPosition);

		if (bIsLast) {
			using json = nlohmann::ordered_json;

			json msg;
			msg["rsp_code"] = 0;
			msg["rsp_message"] = "";

			msg["data"] = json::array();
			for (auto item : m_vInvestorPosition) {
				json rsp;
				rsp["BrokerID"] = item.BrokerID;
				rsp["InvestorID"] = item.InvestorID;
				rsp["PosiDirection"] = ZERO_TO_EMPTY_STR(item.PosiDirection);
				rsp["HedgeFlag"] = ZERO_TO_EMPTY_STR(item.HedgeFlag);
				rsp["PositionDate"] = ZERO_TO_EMPTY_STR(item.PositionDate);
				rsp["YdPosition"] = item.YdPosition;
				rsp["Position"] = item.Position;
				rsp["LongFrozen"] = item.LongFrozen;
				rsp["ShortFrozen"] = item.ShortFrozen;
				rsp["LongFrozenAmount"] = item.LongFrozenAmount;
				rsp["ShortFrozenAmount"] = item.ShortFrozenAmount;
				rsp["OpenVolume"] = item.OpenVolume;
				rsp["CloseVolume"] = item.CloseVolume;
				rsp["OpenAmount"] = item.OpenAmount;
				rsp["CloseAmount"] = item.CloseAmount;
				rsp["PositionCost"] = item.PositionCost;
				rsp["PreMargin"] = item.PreMargin;
				rsp["UseMargin"] = item.UseMargin;
				rsp["FrozenMargin"] = item.FrozenMargin;
				rsp["FrozenCash"] = item.FrozenCash;
				rsp["FrozenCommission"] = item.FrozenCommission;
				rsp["CashIn"] = item.CashIn;
				rsp["Commission"] = item.Commission;
				rsp["CloseProfit"] = item.CloseProfit;
				rsp["PositionProfit"] = item.PositionProfit;
				rsp["PreSettlementPrice"] = item.PreSettlementPrice;
				rsp["SettlementPrice"] = item.SettlementPrice;
				rsp["TradingDay"] = item.TradingDay;
				rsp["SettlementID"] = item.SettlementID;
				rsp["OpenCost"] = item.OpenCost;
				rsp["ExchangeMargin"] = item.ExchangeMargin;
				rsp["CombPosition"] = item.CombPosition;
				rsp["CombLongFrozen"] = item.CombLongFrozen;
				rsp["CombShortFrozen"] = item.CombShortFrozen;
				rsp["CloseProfitByDate"] = item.CloseProfitByDate;
				rsp["CloseProfitByTrade"] = item.CloseProfitByTrade;
				rsp["TodayPosition"] = item.TodayPosition;
				rsp["MarginRateByMoney"] = item.MarginRateByMoney;
				rsp["MarginRateByVolume"] = item.MarginRateByVolume;
				rsp["StrikeFrozen"] = item.StrikeFrozen;
				rsp["StrikeFrozenAmount"] = item.StrikeFrozenAmount;
				rsp["AbandonFrozen"] = item.AbandonFrozen;
				rsp["ExchangeID"] = item.ExchangeID;
				rsp["YdStrikeFrozen"] = item.YdStrikeFrozen;
				rsp["InvestUnitID"] = item.InvestUnitID;
				rsp["InstrumentID"] = item.InstrumentID;

				msg["data"].push_back(rsp);
			}

			std::cout << msg.dump(m_json_indent) << std::endl;

			exit(0);
		}
	}

	void OnRspQryInvestorPositionDetail(CThostFtdcInvestorPositionDetailField * pInvestorPositionDetail, CThostFtdcRspInfoField * pRspInfo, int nRequestID, bool bIsLast)
	{
		if (pRspInfo && pRspInfo->ErrorID != 0) {
			std::cout << error_message(pRspInfo->ErrorID, pRspInfo->ErrorMsg) << std::endl;
			exit(0);
		}

		if (pInvestorPositionDetail)
			m_vInvestorPositionDetail.push_back(*pInvestorPositionDetail);

		if (bIsLast) {
			using json = nlohmann::ordered_json;

			json msg;
			msg["rsp_code"] = 0;
			msg["rsp_message"] = "";

			msg["data"] = json::array();
			for (auto item : m_vInvestorPositionDetail) {
				json rsp;
				rsp["BrokerID"] = item.BrokerID;
				rsp["InvestorID"] = item.InvestorID;
				rsp["HedgeFlag"] = ZERO_TO_EMPTY_STR(item.HedgeFlag);
				rsp["Direction"] = ZERO_TO_EMPTY_STR(item.Direction);
				rsp["OpenDate"] = item.OpenDate;
				rsp["TradeID"] = item.TradeID;
				rsp["Volume"] = item.Volume;
				rsp["OpenPrice"] = item.OpenPrice;
				rsp["TradingDay"] = item.TradingDay;
				rsp["SettlementID"] = item.SettlementID;
				rsp["TradeType"] = ZERO_TO_EMPTY_STR(item.TradeType);
				rsp["ExchangeID"] = item.ExchangeID;
				rsp["CloseProfitByDate"] = item.CloseProfitByDate;
				rsp["CloseProfitByTrade"] = item.CloseProfitByTrade;
				rsp["PositionProfitByDate"] = item.PositionProfitByDate;
				rsp["PositionProfitByTrade"] = item.PositionProfitByTrade;
				rsp["Margin"] = item.Margin;
				rsp["ExchMargin"] = item.ExchMargin;
				rsp["MarginRateByMoney"] = item.MarginRateByMoney;
				rsp["MarginRateByVolume"] = item.MarginRateByVolume;
				rsp["LastSettlementPrice"] = item.LastSettlementPrice;
				rsp["SettlementPrice"] = item.SettlementPrice;
				rsp["CloseVolume"] = item.CloseVolume;
				rsp["CloseAmount"] = item.CloseAmount;
				rsp["InvestUnitID"] = item.InvestUnitID;
				rsp["InstrumentID"] = item.InstrumentID;
				rsp["CombInstrumentID"] = item.CombInstrumentID;

				msg["data"].push_back(rsp);
			}

			std::cout << msg.dump(m_json_indent) << std::endl;

			exit(0);
		}
	}

	void OnRspQryOrder(CThostFtdcOrderField * pOrder, CThostFtdcRspInfoField * pRspInfo, int nRequestID, bool bIsLast)
	{
		if (pRspInfo && pRspInfo->ErrorID != 0) {
			std::cout << error_message(pRspInfo->ErrorID, pRspInfo->ErrorMsg) << std::endl;
			exit(0);
		}

		if (pOrder)
			m_vOrder.push_back(*pOrder);

		if (bIsLast) {
			using json = nlohmann::ordered_json;

			json msg;
			msg["rsp_code"] = 0;
			msg["rsp_message"] = "";

			msg["data"] = json::array();
			for (auto item : m_vOrder) {
				json rsp;
				rsp["BrokerID"] = item.BrokerID;
				rsp["InvestorID"] = item.InvestorID;
				rsp["OrderRef"] = item.OrderRef;
				rsp["UserID"] = item.UserID;
				rsp["OrderPriceType"] = ZERO_TO_EMPTY_STR(item.OrderPriceType);
				rsp["Direction"] = ZERO_TO_EMPTY_STR(item.Direction);
				rsp["CombOffsetFlag"] = item.CombOffsetFlag;
				rsp["CombHedgeFlag"] = item.CombHedgeFlag;
				rsp["LimitPrice"] = item.LimitPrice;
				rsp["VolumeTotalOriginal"] = item.VolumeTotalOriginal;
				rsp["TimeCondition"] = ZERO_TO_EMPTY_STR(item.TimeCondition);
				rsp["GTDDate"] = item.GTDDate;
				rsp["VolumeCondition"] = ZERO_TO_EMPTY_STR(item.VolumeCondition);
				rsp["MinVolume"] = item.MinVolume;
				rsp["ContingentCondition"] = ZERO_TO_EMPTY_STR(item.ContingentCondition);
				rsp["StopPrice"] = item.StopPrice;
				rsp["ForceCloseReason"] = ZERO_TO_EMPTY_STR(item.ForceCloseReason);
				rsp["IsAutoSuspend"] = item.IsAutoSuspend;
				rsp["BusinessUnit"] = item.BusinessUnit;
				rsp["RequestID"] = item.RequestID;
				rsp["OrderLocalID"] = item.OrderLocalID;
				rsp["ExchangeID"] = item.ExchangeID;
				rsp["ParticipantID"] = item.ParticipantID;
				rsp["ClientID"] = item.ClientID;
				rsp["TraderID"] = item.TraderID;
				rsp["InstallID"] = item.InstallID;
				rsp["OrderSubmitStatus"] = ZERO_TO_EMPTY_STR(item.OrderSubmitStatus);
				rsp["NotifySequence"] = item.NotifySequence;
				rsp["TradingDay"] = item.TradingDay;
				rsp["SettlementID"] = item.SettlementID;
				rsp["OrderSysID"] = item.OrderSysID;
				rsp["OrderSource"] = ZERO_TO_EMPTY_STR(item.OrderSource);
				rsp["OrderStatus"] = ZERO_TO_EMPTY_STR(item.OrderStatus);
				rsp["OrderType"] = ZERO_TO_EMPTY_STR(item.OrderType);
				rsp["VolumeTraded"] = item.VolumeTraded;
				rsp["VolumeTotal"] = item.VolumeTotal;
				rsp["InsertDate"] = item.InsertDate;
				rsp["InsertTime"] = item.InsertTime;
				rsp["ActiveTime"] = item.ActiveTime;
				rsp["SuspendTime"] = item.SuspendTime;
				rsp["UpdateTime"] = item.UpdateTime;
				rsp["CancelTime"] = item.CancelTime;
				rsp["ActiveTraderID"] = item.ActiveTraderID;
				rsp["ClearingPartID"] = item.ClearingPartID;
				rsp["SequenceNo"] = item.SequenceNo;
				rsp["FrontID"] = item.FrontID;
				rsp["SessionID"] = item.SessionID;
				rsp["UserProductInfo"] = item.UserProductInfo;
				rsp["StatusMsg"] = GBKToUTF8(item.StatusMsg);
				rsp["UserForceClose"] = item.UserForceClose;
				rsp["ActiveUserID"] = item.ActiveUserID;
				rsp["BrokerOrderSeq"] = item.BrokerOrderSeq;
				rsp["RelativeOrderSysID"] = item.RelativeOrderSysID;
				rsp["ZCETotalTradedVolume"] = item.ZCETotalTradedVolume;
				rsp["IsSwapOrder"] = item.IsSwapOrder;
				rsp["BranchID"] = item.BranchID;
				rsp["InvestUnitID"] = item.InvestUnitID;
				rsp["AccountID"] = item.AccountID;
				rsp["CurrencyID"] = item.CurrencyID;
				rsp["MacAddress"] = item.MacAddress;
				rsp["InstrumentID"] = item.InstrumentID;
				rsp["ExchangeInstID"] = item.ExchangeInstID;
				rsp["IPAddress"] = item.IPAddress;

				msg["data"].push_back(rsp);
			}

			std::cout << msg.dump(m_json_indent) << std::endl;

			exit(0);
		}
	}

	void OnRspQryTrade(CThostFtdcTradeField * pTrade, CThostFtdcRspInfoField * pRspInfo, int nRequestID, bool bIsLast)
	{
		if (pRspInfo && pRspInfo->ErrorID != 0) {
			std::cout << error_message(pRspInfo->ErrorID, pRspInfo->ErrorMsg) << std::endl;
			exit(0);
		}

		if (pTrade)
			m_vTrade.push_back(*pTrade);

		if (bIsLast) {
			using json = nlohmann::ordered_json;

			json msg;
			msg["rsp_code"] = 0;
			msg["rsp_message"] = "";

			msg["data"] = json::array();
			for (auto item : m_vTrade) {
				json rsp;
				rsp["BrokerID"] = item.BrokerID;
				rsp["InvestorID"] = item.InvestorID;
				rsp["OrderRef"] = item.OrderRef;
				rsp["UserID"] = item.UserID;
				rsp["ExchangeID"] = item.ExchangeID;
				rsp["TradeID"] = item.TradeID;
				rsp["Direction"] = ZERO_TO_EMPTY_STR(item.Direction);
				rsp["OrderSysID"] = item.OrderSysID;
				rsp["ParticipantID"] = item.ParticipantID;
				rsp["ClientID"] = item.ClientID;
				rsp["TradingRole"] = ZERO_TO_EMPTY_STR(item.TradingRole);
				rsp["OffsetFlag"] = ZERO_TO_EMPTY_STR(item.OffsetFlag);
				rsp["HedgeFlag"] = ZERO_TO_EMPTY_STR(item.HedgeFlag);
				rsp["Price"] = item.Price;
				rsp["Volume"] = item.Volume;
				rsp["TradeDate"] = item.TradeDate;
				rsp["TradeTime"] = item.TradeTime;
				rsp["TradeType"] = ZERO_TO_EMPTY_STR(item.TradeType);
				rsp["PriceSource"] = ZERO_TO_EMPTY_STR(item.PriceSource);
				rsp["TraderID"] = item.TraderID;
				rsp["OrderLocalID"] = item.OrderLocalID;
				rsp["ClearingPartID"] = item.ClearingPartID;
				rsp["BusinessUnit"] = item.BusinessUnit;
				rsp["SequenceNo"] = item.SequenceNo;
				rsp["TradingDay"] = item.TradingDay;
				rsp["SettlementID"] = item.SettlementID;
				rsp["BrokerOrderSeq"] = item.BrokerOrderSeq;
				rsp["TradeSource"] = ZERO_TO_EMPTY_STR(item.TradeSource);
				rsp["InvestUnitID"] = item.InvestUnitID;
				rsp["InstrumentID"] = item.InstrumentID;
				rsp["ExchangeInstID"] = item.ExchangeInstID;

				msg["data"].push_back(rsp);
			}

			std::cout << msg.dump(m_json_indent) << std::endl;

			exit(0);
		}
	}

	void OnRspQryExchange(CThostFtdcExchangeField * pExchange, CThostFtdcRspInfoField * pRspInfo, int nRequestID, bool bIsLast)
	{
		if (pRspInfo && pRspInfo->ErrorID != 0) {
			std::cout << error_message(pRspInfo->ErrorID, pRspInfo->ErrorMsg) << std::endl;
			exit(0);
		}

		if (pExchange)
			m_vExchange.push_back(*pExchange);

		if (bIsLast) {
			using json = nlohmann::ordered_json;

			json msg;
			msg["rsp_code"] = 0;
			msg["rsp_message"] = "";

			msg["data"] = json::array();
			for (auto item : m_vExchange) {
				json rsp;
				rsp["ExchangeID"] = item.ExchangeID;
				rsp["ExchangeName"] = GBKToUTF8(item.ExchangeName);
				rsp["ExchangeProperty"] = ZERO_TO_EMPTY_STR(item.ExchangeProperty);

				msg["data"].push_back(rsp);
			}

			std::cout << msg.dump(m_json_indent) << std::endl;

			exit(0);
		}
	}

	void OnRspQryProduct(CThostFtdcProductField * pProduct, CThostFtdcRspInfoField * pRspInfo, int nRequestID, bool bIsLast)
	{
		if (pRspInfo && pRspInfo->ErrorID != 0) {
			std::cout << error_message(pRspInfo->ErrorID, pRspInfo->ErrorMsg) << std::endl;
			exit(0);
		}

		if (pProduct)
			m_vProduct.push_back(*pProduct);

		if (bIsLast) {
			using json = nlohmann::ordered_json;

			json msg;
			msg["rsp_code"] = 0;
			msg["rsp_message"] = "";

			msg["data"] = json::array();
			for (auto item : m_vProduct) {
				json rsp;
				rsp["ProductName"] = GBKToUTF8(item.ProductName);
				rsp["ExchangeID"] = item.ExchangeID;
				rsp["ProductClass"] = ZERO_TO_EMPTY_STR(item.ProductClass);
				rsp["VolumeMultiple"] = item.VolumeMultiple;
				rsp["PriceTick"] = item.PriceTick;
				rsp["MaxMarketOrderVolume"] = item.MaxMarketOrderVolume;
				rsp["MinMarketOrderVolume"] = item.MinMarketOrderVolume;
				rsp["MaxLimitOrderVolume"] = item.MaxLimitOrderVolume;
				rsp["MinLimitOrderVolume"] = item.MinLimitOrderVolume;
				rsp["PositionType"] = ZERO_TO_EMPTY_STR(item.PositionType);
				rsp["PositionDateType"] = ZERO_TO_EMPTY_STR(item.PositionDateType);
				rsp["CloseDealType"] = ZERO_TO_EMPTY_STR(item.CloseDealType);
				rsp["TradeCurrencyID"] = item.TradeCurrencyID;
				rsp["MortgageFundUseRange"] = ZERO_TO_EMPTY_STR(item.MortgageFundUseRange);
				rsp["UnderlyingMultiple"] = item.UnderlyingMultiple;
				rsp["ProductID"] = item.ProductID;
				rsp["ExchangeProductID"] = item.ExchangeProductID;

				msg["data"].push_back(rsp);
			}

			std::cout << msg.dump(m_json_indent) << std::endl;

			exit(0);
		}
	}

	void OnRspQryInstrument(CThostFtdcInstrumentField * pInstrument, CThostFtdcRspInfoField * pRspInfo, int nRequestID, bool bIsLast)
	{
		if (pRspInfo && pRspInfo->ErrorID != 0) {
			std::cout << error_message(pRspInfo->ErrorID, pRspInfo->ErrorMsg) << std::endl;
			exit(0);
		}

		if (pInstrument)
			m_vInstrument.push_back(*pInstrument);

		if (bIsLast) {
			using json = nlohmann::ordered_json;

			json msg;
			msg["rsp_code"] = 0;
			msg["rsp_message"] = "";

			msg["data"] = json::array();
			for (auto item : m_vInstrument) {
				json rsp;

				rsp["ExchangeID"] = item.ExchangeID;
				rsp["InstrumentName"] = GBKToUTF8(item.InstrumentName);
				rsp["ProductClass"] = ZERO_TO_EMPTY_STR(item.ProductClass);
				rsp["DeliveryYear"] = item.DeliveryYear;
				rsp["DeliveryMonth"] = item.DeliveryMonth;
				rsp["MaxMarketOrderVolume"] = item.MaxMarketOrderVolume;
				rsp["MinMarketOrderVolume"] = item.MinMarketOrderVolume;
				rsp["MaxLimitOrderVolume"] = item.MaxLimitOrderVolume;
				rsp["MinLimitOrderVolume"] = item.MinLimitOrderVolume;
				rsp["VolumeMultiple"] = item.VolumeMultiple;
				rsp["PriceTick"] = item.PriceTick;
				rsp["CreateDate"] = item.CreateDate;
				rsp["OpenDate"] = item.OpenDate;
				rsp["ExpireDate"] = item.ExpireDate;
				rsp["StartDelivDate"] = item.StartDelivDate;
				rsp["EndDelivDate"] = item.EndDelivDate;
				rsp["InstLifePhase"] = ZERO_TO_EMPTY_STR(item.InstLifePhase);
				rsp["IsTrading"] = item.IsTrading;
				rsp["PositionType"] = ZERO_TO_EMPTY_STR(item.PositionType);
				rsp["PositionDateType"] = ZERO_TO_EMPTY_STR(item.PositionDateType);
				rsp["LongMarginRatio"] = DBLMAX_TO_NULL(item.LongMarginRatio);
				rsp["ShortMarginRatio"] = DBLMAX_TO_NULL(item.ShortMarginRatio);
				rsp["MaxMarginSideAlgorithm"] = ZERO_TO_EMPTY_STR(item.MaxMarginSideAlgorithm);
				rsp["StrikePrice"] = DBLMAX_TO_NULL(item.StrikePrice);
				rsp["OptionsType"] = ZERO_TO_EMPTY_STR(item.OptionsType);
				rsp["UnderlyingMultiple"] = item.UnderlyingMultiple;
				rsp["CombinationType"] = ZERO_TO_EMPTY_STR(item.CombinationType);
				rsp["InstrumentID"] = item.InstrumentID;
				rsp["ExchangeInstID"] = item.ExchangeInstID;
				rsp["ProductID"] = item.ProductID;
				rsp["UnderlyingInstrID"] = item.UnderlyingInstrID;

				msg["data"].push_back(rsp);
			}

			std::cout << msg.dump(m_json_indent) << std::endl;

			exit(0);
		}
	}

	void OnRspQryDepthMarketData(CThostFtdcDepthMarketDataField * pDepthMarketData, CThostFtdcRspInfoField * pRspInfo, int nRequestID, bool bIsLast)
	{
		if (pRspInfo && pRspInfo->ErrorID != 0) {
			std::cout << error_message(pRspInfo->ErrorID, pRspInfo->ErrorMsg) << std::endl;
			exit(0);
		}

		if (pDepthMarketData)
			m_vDepthMarketData.push_back(*pDepthMarketData);

		if (bIsLast) {
			using json = nlohmann::ordered_json;

			json msg;
			msg["rsp_code"] = 0;
			msg["rsp_message"] = "";

			msg["data"] = json::array();
			for (auto item : m_vDepthMarketData) {
				json rsp;
				rsp["TradingDay"] = item.TradingDay;
				rsp["ExchangeID"] = item.ExchangeID;
				rsp["LastPrice"] = DBLMAX_TO_NULL(item.LastPrice);
				rsp["PreSettlementPrice"] = DBLMAX_TO_NULL(item.PreSettlementPrice);
				rsp["PreClosePrice"] = DBLMAX_TO_NULL(item.PreClosePrice);
				rsp["PreOpenInterest"] = DBLMAX_TO_NULL(item.PreOpenInterest);
				rsp["OpenPrice"] = DBLMAX_TO_NULL(item.OpenPrice);
				rsp["HighestPrice"] = DBLMAX_TO_NULL(item.HighestPrice);
				rsp["LowestPrice"] = DBLMAX_TO_NULL(item.LowestPrice);
				rsp["Volume"] = item.Volume;
				rsp["Turnover"] = DBLMAX_TO_NULL(item.Turnover);
				rsp["OpenInterest"] = DBLMAX_TO_NULL(item.OpenInterest);
				rsp["ClosePrice"] = DBLMAX_TO_NULL(item.ClosePrice);
				rsp["SettlementPrice"] = DBLMAX_TO_NULL(item.SettlementPrice);
				rsp["UpperLimitPrice"] = DBLMAX_TO_NULL(item.UpperLimitPrice);
				rsp["LowerLimitPrice"] = DBLMAX_TO_NULL(item.LowerLimitPrice);
				rsp["PreDelta"] = DBLMAX_TO_NULL(item.PreDelta);
				rsp["CurrDelta"] = DBLMAX_TO_NULL(item.CurrDelta);
				rsp["UpdateTime"] = item.UpdateTime;
				rsp["UpdateMillisec"] = item.UpdateMillisec;
				rsp["BidPrice1"] = DBLMAX_TO_NULL(item.BidPrice1);
				rsp["BidVolume1"] = item.BidVolume1;
				rsp["AskPrice1"] = DBLMAX_TO_NULL(item.AskPrice1);
				rsp["AskVolume1"] = item.AskVolume1;
				rsp["BidPrice2"] = DBLMAX_TO_NULL(item.BidPrice2);
				rsp["BidVolume2"] = item.BidVolume2;
				rsp["AskPrice2"] = DBLMAX_TO_NULL(item.AskPrice2);
				rsp["AskVolume2"] = item.AskVolume2;
				rsp["BidPrice3"] = DBLMAX_TO_NULL(item.BidPrice3);
				rsp["BidVolume3"] = item.BidVolume3;
				rsp["AskPrice3"] = DBLMAX_TO_NULL(item.AskPrice3);
				rsp["AskVolume3"] = item.AskVolume3;
				rsp["BidPrice4"] = DBLMAX_TO_NULL(item.BidPrice4);
				rsp["BidVolume4"] = item.BidVolume4;
				rsp["AskPrice4"] = DBLMAX_TO_NULL(item.AskPrice4);
				rsp["AskVolume4"] = item.AskVolume4;
				rsp["BidPrice5"] = DBLMAX_TO_NULL(item.BidPrice5);
				rsp["BidVolume5"] = item.BidVolume5;
				rsp["AskPrice5"] = DBLMAX_TO_NULL(item.AskPrice5);
				rsp["AskVolume5"] = item.AskVolume5;
				rsp["AveragePrice"] = DBLMAX_TO_NULL(item.AveragePrice);
				rsp["ActionDay"] = item.ActionDay;
				rsp["InstrumentID"] = item.InstrumentID;
				rsp["ExchangeInstID"] = item.ExchangeInstID;

				msg["data"].push_back(rsp);
			}

			std::cout << msg.dump(m_json_indent) << std::endl;

			exit(0);
		}
	}

	void OnRspQryInstrumentCommissionRate(CThostFtdcInstrumentCommissionRateField * pInstrumentCommissionRate, CThostFtdcRspInfoField * pRspInfo, int nRequestID, bool bIsLast)
	{
		if (pRspInfo && pRspInfo->ErrorID != 0) {
			std::cout << error_message(pRspInfo->ErrorID, pRspInfo->ErrorMsg) << std::endl;
			exit(0);
		}

		if (pInstrumentCommissionRate)
			m_vInstrumentCommissionRate.push_back(*pInstrumentCommissionRate);

		if (bIsLast) {
			using json = nlohmann::ordered_json;

			json msg;
			msg["rsp_code"] = 0;
			msg["rsp_message"] = "";

			msg["data"] = json::array();
			for (auto item : m_vInstrumentCommissionRate) {
				json rsp;
				rsp["InvestorRange"] = ZERO_TO_EMPTY_STR(item.InvestorRange);
				rsp["BrokerID"] = item.BrokerID;
				rsp["InvestorID"] = item.InvestorID;
				rsp["OpenRatioByMoney"] = item.OpenRatioByMoney;
				rsp["OpenRatioByVolume"] = item.OpenRatioByVolume;
				rsp["CloseRatioByMoney"] = item.CloseRatioByMoney;
				rsp["CloseRatioByVolume"] = item.CloseRatioByVolume;
				rsp["CloseTodayRatioByMoney"] = item.CloseTodayRatioByMoney;
				rsp["CloseTodayRatioByVolume"] = item.CloseTodayRatioByVolume;
				rsp["ExchangeID"] = item.ExchangeID;
				rsp["BizType"] = ZERO_TO_EMPTY_STR(item.BizType);
				rsp["InvestUnitID"] = item.InvestUnitID;
				rsp["InstrumentID"] = item.InstrumentID;

				msg["data"].push_back(rsp);
			}

			std::cout << msg.dump(m_json_indent) << std::endl;

			exit(0);
		}
	}

	void OnRspQryOptionInstrCommRate(CThostFtdcOptionInstrCommRateField * pOptionInstrCommRate, CThostFtdcRspInfoField * pRspInfo, int nRequestID, bool bIsLast)
	{
		if (pRspInfo && pRspInfo->ErrorID != 0) {
			std::cout << error_message(pRspInfo->ErrorID, pRspInfo->ErrorMsg) << std::endl;
			exit(0);
		}

		if (pOptionInstrCommRate)
			m_vOptionInstrCommRate.push_back(*pOptionInstrCommRate);

		if (bIsLast) {
			using json = nlohmann::ordered_json;

			json msg;
			msg["rsp_code"] = 0;
			msg["rsp_message"] = "";

			msg["data"] = json::array();
			for (auto item : m_vOptionInstrCommRate) {
				json rsp;
				rsp["InvestorRange"] = ZERO_TO_EMPTY_STR(item.InvestorRange);
				rsp["BrokerID"] = item.BrokerID;
				rsp["InvestorID"] = item.InvestorID;
				rsp["OpenRatioByMoney"] = item.OpenRatioByMoney;
				rsp["OpenRatioByVolume"] = item.OpenRatioByVolume;
				rsp["CloseRatioByMoney"] = item.CloseRatioByMoney;
				rsp["CloseRatioByVolume"] = item.CloseRatioByVolume;
				rsp["CloseTodayRatioByMoney"] = item.CloseTodayRatioByMoney;
				rsp["CloseTodayRatioByVolume"] = item.CloseTodayRatioByVolume;
				rsp["StrikeRatioByMoney"] = item.StrikeRatioByMoney;
				rsp["StrikeRatioByVolume"] = item.StrikeRatioByVolume;
				rsp["ExchangeID"] = item.ExchangeID;
				rsp["InvestUnitID"] = item.InvestUnitID;
				rsp["InstrumentID"] = item.InstrumentID;

				msg["data"].push_back(rsp);
			}

			std::cout << msg.dump(m_json_indent) << std::endl;

			exit(0);
		}
	}

	void OnRspQryInstrumentOrderCommRate(CThostFtdcInstrumentOrderCommRateField * pInstrumentOrderCommRate, CThostFtdcRspInfoField * pRspInfo, int nRequestID, bool bIsLast)
	{
		if (pRspInfo && pRspInfo->ErrorID != 0) {
			std::cout << error_message(pRspInfo->ErrorID, pRspInfo->ErrorMsg) << std::endl;
			exit(0);
		}

		if (pInstrumentOrderCommRate)
			m_vInstrumentOrderCommRate.push_back(*pInstrumentOrderCommRate);

		if (bIsLast) {
			using json = nlohmann::ordered_json;

			json msg;
			msg["rsp_code"] = 0;
			msg["rsp_message"] = "";

			msg["data"] = json::array();
			for (auto item : m_vInstrumentOrderCommRate) {
				json rsp;
				rsp["InvestorRange"] = ZERO_TO_EMPTY_STR(item.InvestorRange);
				rsp["BrokerID"] = item.BrokerID;
				rsp["InvestorID"] = item.InvestorID;
				rsp["HedgeFlag"] = ZERO_TO_EMPTY_STR(item.HedgeFlag);
				rsp["OrderCommByVolume"] = item.OrderCommByVolume;
				rsp["OrderActionCommByVolume"] = item.OrderActionCommByVolume;
				rsp["ExchangeID"] = item.ExchangeID;
				rsp["InvestUnitID"] = item.InvestUnitID;
				rsp["InstrumentID"] = item.InstrumentID;

				msg["data"].push_back(rsp);
			}

			std::cout << msg.dump(m_json_indent) << std::endl;

			exit(0);
		}
	}

	void OnRspQryInstrumentMarginRate(CThostFtdcInstrumentMarginRateField * pInstrumentMarginRate, CThostFtdcRspInfoField * pRspInfo, int nRequestID, bool bIsLast)
	{
		if (pRspInfo && pRspInfo->ErrorID != 0) {
			std::cout << error_message(pRspInfo->ErrorID, pRspInfo->ErrorMsg) << std::endl;
			exit(0);
		}

		if (pInstrumentMarginRate)
			m_vInstrumentMarginRate.push_back(*pInstrumentMarginRate);

		if (bIsLast) {
			using json = nlohmann::ordered_json;

			json msg;
			msg["rsp_code"] = 0;
			msg["rsp_message"] = "";

			msg["data"] = json::array();
			for (auto item : m_vInstrumentMarginRate) {
				json rsp;
				rsp["InvestorRange"] = ZERO_TO_EMPTY_STR(item.InvestorRange);
				rsp["BrokerID"] = item.BrokerID;
				rsp["InvestorID"] = item.InvestorID;
				rsp["HedgeFlag"] = ZERO_TO_EMPTY_STR(item.HedgeFlag);
				rsp["LongMarginRatioByMoney"] = item.LongMarginRatioByMoney;
				rsp["LongMarginRatioByVolume"] = item.LongMarginRatioByVolume;
				rsp["ShortMarginRatioByMoney"] = item.ShortMarginRatioByMoney;
				rsp["ShortMarginRatioByVolume"] = item.ShortMarginRatioByVolume;
				rsp["IsRelative"] = item.IsRelative;
				rsp["ExchangeID"] = item.ExchangeID;
				rsp["InvestUnitID"] = item.InvestUnitID;
				rsp["InstrumentID"] = item.InstrumentID;
				msg["data"].push_back(rsp);
			}

			std::cout << msg.dump(m_json_indent) << std::endl;

			exit(0);
		}
	}

	void OnRspQryTransferSerial(CThostFtdcTransferSerialField * pTransferSerial, CThostFtdcRspInfoField * pRspInfo, int nRequestID, bool bIsLast)
	{
		if (pRspInfo && pRspInfo->ErrorID != 0) {
			std::cout << error_message(pRspInfo->ErrorID, pRspInfo->ErrorMsg) << std::endl;
			exit(0);
		}

		if (pTransferSerial)
			m_vTransferSerial.push_back(*pTransferSerial);

		if (bIsLast) {
			using json = nlohmann::ordered_json;

			json msg;
			msg["rsp_code"] = 0;
			msg["rsp_message"] = "";

			msg["data"] = json::array();
			for (auto item : m_vTransferSerial) {
				json rsp;
				rsp["PlateSerial"] = item.PlateSerial;
				rsp["TradeDate"] = item.TradeDate;
				rsp["TradingDay"] = item.TradingDay;
				rsp["TradeTime"] = item.TradeTime;
				rsp["TradeCode"] = item.TradeCode;
				rsp["SessionID"] = item.SessionID;
				rsp["BankID"] = item.BankID;
				rsp["BankBranchID"] = item.BankBranchID;
				rsp["BankAccType"] = ZERO_TO_EMPTY_STR(item.BankAccType);
				rsp["BankAccount"] = item.BankAccount;
				rsp["BankSerial"] = item.BankSerial;
				rsp["BrokerID"] = item.BrokerID;
				rsp["BrokerBranchID"] = item.BrokerBranchID;
				rsp["FutureAccType"] = ZERO_TO_EMPTY_STR(item.FutureAccType);
				rsp["AccountID"] = item.AccountID;
				rsp["InvestorID"] = item.InvestorID;
				rsp["FutureSerial"] = item.FutureSerial;
				rsp["IdCardType"] = ZERO_TO_EMPTY_STR(item.IdCardType);
				rsp["IdentifiedCardNo"] = item.IdentifiedCardNo;
				rsp["CurrencyID"] = item.CurrencyID;
				rsp["TradeAmount"] = item.TradeAmount;
				rsp["CustFee"] = item.CustFee;
				rsp["BrokerFee"] = item.BrokerFee;
				rsp["AvailabilityFlag"] = ZERO_TO_EMPTY_STR(item.AvailabilityFlag);
				rsp["OperatorCode"] = item.OperatorCode;
				rsp["BankNewAccount"] = item.BankNewAccount;
				rsp["ErrorID"] = item.ErrorID;
				rsp["ErrorMsg"] = item.ErrorMsg;

				msg["data"].push_back(rsp);
			}

			std::cout << msg.dump(m_json_indent) << std::endl;

			exit(0);
		}
	}

	void OnRspQryAccountregister(CThostFtdcAccountregisterField * pAccountregister, CThostFtdcRspInfoField * pRspInfo, int nRequestID, bool bIsLast)
	{
		if (pRspInfo && pRspInfo->ErrorID != 0) {
			std::cout << error_message(pRspInfo->ErrorID, pRspInfo->ErrorMsg) << std::endl;
			exit(0);
		}

		if (pAccountregister)
			m_vAccountregister.push_back(*pAccountregister);

		if (bIsLast) {
			using json = nlohmann::ordered_json;

			json msg;
			msg["rsp_code"] = 0;
			msg["rsp_message"] = "";

			msg["data"] = json::array();
			for (auto item : m_vAccountregister) {
				json rsp;
				rsp["TradeDay"] = item.TradeDay;
				rsp["BankID"] = item.BankID;
				rsp["BankBranchID"] = item.BankBranchID;
				rsp["BankAccount"] = item.BankAccount;
				rsp["BrokerID"] = item.BrokerID;
				rsp["BrokerBranchID"] = item.BrokerBranchID;
				rsp["AccountID"] = item.AccountID;
				rsp["IdCardType"] = ZERO_TO_EMPTY_STR(item.IdCardType);
				rsp["IdentifiedCardNo"] = item.IdentifiedCardNo;
				rsp["CustomerName"] = GBKToUTF8(item.CustomerName);
				rsp["CurrencyID"] = item.CurrencyID;
				rsp["OpenOrDestroy"] = ZERO_TO_EMPTY_STR(item.OpenOrDestroy);
				rsp["RegDate"] = item.RegDate;
				rsp["OutDate"] = item.OutDate;
				rsp["TID"] = item.TID;
				rsp["CustType"] = ZERO_TO_EMPTY_STR(item.CustType);
				rsp["BankAccType"] = ZERO_TO_EMPTY_STR(item.BankAccType);

				msg["data"].push_back(rsp);
			}

			std::cout << msg.dump(m_json_indent) << std::endl;

			exit(0);
		}
	}

	void OnRspQryTransferBank(CThostFtdcTransferBankField * pTransferBank, CThostFtdcRspInfoField * pRspInfo, int nRequestID, bool bIsLast)
	{
		if (pRspInfo && pRspInfo->ErrorID != 0) {
			std::cout << error_message(pRspInfo->ErrorID, pRspInfo->ErrorMsg) << std::endl;
			exit(0);
		}

		if (pTransferBank)
			m_vTransferBank.push_back(*pTransferBank);

		if (bIsLast) {
			using json = nlohmann::ordered_json;

			json msg;
			msg["rsp_code"] = 0;
			msg["rsp_message"] = "";

			msg["data"] = json::array();
			for (auto item : m_vTransferBank) {
				json rsp;
				rsp["BankID"] = item.BankID;
				rsp["BankBrchID"] = item.BankBrchID;
				rsp["BankName"] = GBKToUTF8(item.BankName);
				rsp["IsActive"] = item.IsActive;

				msg["data"].push_back(rsp);
			}

			std::cout << msg.dump(m_json_indent) << std::endl;

			exit(0);
		}
	}

	void OnRtnOrder(CThostFtdcOrderField * pOrder)
	{
		switch (m_cmd)
		{
		case CTPCMD_Buy:
		case CTPCMD_Sell:
		case CTPCMD_Cancel:
			break;
		case CTPCMD_Subscribe:
			break;
		default:
			return;
		}

		if (m_cmd == CTPCMD_Buy || m_cmd == CTPCMD_Sell) {
			// Ignore other orders
			if (pOrder->FrontID != m_FrontID || pOrder->SessionID != m_SessionID)
				return;

			if (pOrder->OrderStatus == THOST_FTDC_OST_Canceled) {
				// rejected
				std::cout << error_message(CTPCMD_ERR_CODE_DEFAULT, pOrder->StatusMsg) << std::endl;
				exit(0);
			}
			else if (strlen(pOrder->OrderSysID) > 0) {
				using json = nlohmann::ordered_json;

				json msg;
				msg["rsp_code"] = 0;
				msg["rsp_message"] = "";

				json rsp;
				rsp["BrokerID"] = pOrder->BrokerID;
				rsp["UserID"] = pOrder->UserID;
				rsp["InvestorID"] = pOrder->InvestorID;
				rsp["ExchangeID"] = pOrder->ExchangeID;
				rsp["InstrumentID"] = pOrder->InstrumentID;
				rsp["FrontID"] = pOrder->FrontID;
				rsp["SessionID"] = pOrder->SessionID;
				rsp["OrderRef"] = pOrder->OrderRef;
				rsp["OrderSysID"] = pOrder->OrderSysID;

				msg["data"] = rsp;

				std::cout << msg.dump(m_json_indent) << std::endl;

				exit(0);
			}
			else {
				return;
			}
		}
		else if (m_cmd == CTPCMD_Cancel) {
			if (strcmp(pOrder->ExchangeID, m_params.ExchangeID.c_str()) != 0 || strcmp(pOrder->OrderSysID, m_params.OrderSysID.c_str()) != 0)
				return;

			if (pOrder->OrderStatus == THOST_FTDC_OST_Canceled) {
				using json = nlohmann::ordered_json;

				json msg;
				msg["rsp_code"] = 0;
				msg["rsp_message"] = "";

				json rsp;
				rsp["BrokerID"] = pOrder->BrokerID;
				rsp["UserID"] = pOrder->UserID;
				rsp["InvestorID"] = pOrder->InvestorID;
				rsp["ExchangeID"] = pOrder->ExchangeID;
				rsp["InstrumentID"] = pOrder->InstrumentID;
				rsp["FrontID"] = pOrder->FrontID;
				rsp["SessionID"] = pOrder->SessionID;
				rsp["OrderRef"] = pOrder->OrderRef;
				rsp["OrderSysID"] = pOrder->OrderSysID;
				rsp["VolumeTraded"] = pOrder->VolumeTraded;
				rsp["VolumeTotal"] = pOrder->VolumeTotal;
				rsp["OrderStatus"] = ZERO_TO_EMPTY_STR(pOrder->OrderStatus);
				rsp["StatusMsg"] = GBKToUTF8(pOrder->StatusMsg);

				msg["data"] = rsp;

				std::cout << msg.dump(m_json_indent) << std::endl;

				exit(0);
			}
			else {
				return;
			}
		}

		using json = nlohmann::ordered_json;

		json msg;
		msg["event"] = "Order";

		json rsp;
		rsp["BrokerID"] = pOrder->BrokerID;
		rsp["InvestorID"] = pOrder->InvestorID;
		rsp["OrderRef"] = pOrder->OrderRef;
		rsp["UserID"] = pOrder->UserID;
		rsp["OrderPriceType"] = ZERO_TO_EMPTY_STR(pOrder->OrderPriceType);
		rsp["Direction"] = ZERO_TO_EMPTY_STR(pOrder->Direction);
		rsp["CombOffsetFlag"] = pOrder->CombOffsetFlag;
		rsp["CombHedgeFlag"] = pOrder->CombHedgeFlag;
		rsp["LimitPrice"] = pOrder->LimitPrice;
		rsp["VolumeTotalOriginal"] = pOrder->VolumeTotalOriginal;
		rsp["TimeCondition"] = ZERO_TO_EMPTY_STR(pOrder->TimeCondition);
		rsp["GTDDate"] = pOrder->GTDDate;
		rsp["VolumeCondition"] = ZERO_TO_EMPTY_STR(pOrder->VolumeCondition);
		rsp["MinVolume"] = pOrder->MinVolume;
		rsp["ContingentCondition"] = ZERO_TO_EMPTY_STR(pOrder->ContingentCondition);
		rsp["StopPrice"] = pOrder->StopPrice;
		rsp["ForceCloseReason"] = ZERO_TO_EMPTY_STR(pOrder->ForceCloseReason);
		rsp["IsAutoSuspend"] = pOrder->IsAutoSuspend;
		rsp["BusinessUnit"] = pOrder->BusinessUnit;
		rsp["RequestID"] = pOrder->RequestID;
		rsp["OrderLocalID"] = pOrder->OrderLocalID;
		rsp["ExchangeID"] = pOrder->ExchangeID;
		rsp["ParticipantID"] = pOrder->ParticipantID;
		rsp["ClientID"] = pOrder->ClientID;
		rsp["TraderID"] = pOrder->TraderID;
		rsp["InstallID"] = pOrder->InstallID;
		rsp["OrderSubmitStatus"] = ZERO_TO_EMPTY_STR(pOrder->OrderSubmitStatus);
		rsp["NotifySequence"] = pOrder->NotifySequence;
		rsp["TradingDay"] = pOrder->TradingDay;
		rsp["SettlementID"] = pOrder->SettlementID;
		rsp["OrderSysID"] = pOrder->OrderSysID;
		rsp["OrderSource"] = ZERO_TO_EMPTY_STR(pOrder->OrderSource);
		rsp["OrderStatus"] = ZERO_TO_EMPTY_STR(pOrder->OrderStatus);
		rsp["OrderType"] = ZERO_TO_EMPTY_STR(pOrder->OrderType);
		rsp["VolumeTraded"] = pOrder->VolumeTraded;
		rsp["VolumeTotal"] = pOrder->VolumeTotal;
		rsp["InsertDate"] = pOrder->InsertDate;
		rsp["InsertTime"] = pOrder->InsertTime;
		rsp["ActiveTime"] = pOrder->ActiveTime;
		rsp["SuspendTime"] = pOrder->SuspendTime;
		rsp["UpdateTime"] = pOrder->UpdateTime;
		rsp["CancelTime"] = pOrder->CancelTime;
		rsp["ActiveTraderID"] = pOrder->ActiveTraderID;
		rsp["ClearingPartID"] = pOrder->ClearingPartID;
		rsp["SequenceNo"] = pOrder->SequenceNo;
		rsp["FrontID"] = pOrder->FrontID;
		rsp["SessionID"] = pOrder->SessionID;
		rsp["UserProductInfo"] = pOrder->UserProductInfo;
		rsp["StatusMsg"] = GBKToUTF8(pOrder->StatusMsg);
		rsp["UserForceClose"] = pOrder->UserForceClose;
		rsp["ActiveUserID"] = pOrder->ActiveUserID;
		rsp["BrokerOrderSeq"] = pOrder->BrokerOrderSeq;
		rsp["RelativeOrderSysID"] = pOrder->RelativeOrderSysID;
		rsp["ZCETotalTradedVolume"] = pOrder->ZCETotalTradedVolume;
		rsp["IsSwapOrder"] = pOrder->IsSwapOrder;
		rsp["BranchID"] = pOrder->BranchID;
		rsp["InvestUnitID"] = pOrder->InvestUnitID;
		rsp["AccountID"] = pOrder->AccountID;
		rsp["CurrencyID"] = pOrder->CurrencyID;
		rsp["MacAddress"] = pOrder->MacAddress;
		rsp["InstrumentID"] = pOrder->InstrumentID;
		rsp["ExchangeInstID"] = pOrder->ExchangeInstID;
		rsp["IPAddress"] = pOrder->IPAddress;

		msg["data"] = rsp;

		std::cout << msg.dump(m_json_indent) << std::endl;
	}

	void OnRtnTrade(CThostFtdcTradeField * pTrade)
	{
		switch (m_cmd)
		{
		case CTPCMD_Subscribe:
			break;
		default:
			return;
		}

		using json = nlohmann::ordered_json;

		json msg;
		msg["event"] = "Trade";

		json rsp;
		rsp["BrokerID"] = pTrade->BrokerID;
		rsp["InvestorID"] = pTrade->InvestorID;
		rsp["OrderRef"] = pTrade->OrderRef;
		rsp["UserID"] = pTrade->UserID;
		rsp["ExchangeID"] = pTrade->ExchangeID;
		rsp["TradeID"] = pTrade->TradeID;
		rsp["Direction"] = ZERO_TO_EMPTY_STR(pTrade->Direction);
		rsp["OrderSysID"] = pTrade->OrderSysID;
		rsp["ParticipantID"] = pTrade->ParticipantID;
		rsp["ClientID"] = pTrade->ClientID;
		rsp["TradingRole"] = ZERO_TO_EMPTY_STR(pTrade->TradingRole);
		rsp["OffsetFlag"] = ZERO_TO_EMPTY_STR(pTrade->OffsetFlag);
		rsp["HedgeFlag"] = ZERO_TO_EMPTY_STR(pTrade->HedgeFlag);
		rsp["Price"] = pTrade->Price;
		rsp["Volume"] = pTrade->Volume;
		rsp["TradeDate"] = pTrade->TradeDate;
		rsp["TradeTime"] = pTrade->TradeTime;
		rsp["TradeType"] = ZERO_TO_EMPTY_STR(pTrade->TradeType);
		rsp["PriceSource"] = ZERO_TO_EMPTY_STR(pTrade->PriceSource);
		rsp["TraderID"] = pTrade->TraderID;
		rsp["OrderLocalID"] = pTrade->OrderLocalID;
		rsp["ClearingPartID"] = pTrade->ClearingPartID;
		rsp["BusinessUnit"] = pTrade->BusinessUnit;
		rsp["SequenceNo"] = pTrade->SequenceNo;
		rsp["TradingDay"] = pTrade->TradingDay;
		rsp["SettlementID"] = pTrade->SettlementID;
		rsp["BrokerOrderSeq"] = pTrade->BrokerOrderSeq;
		rsp["TradeSource"] = ZERO_TO_EMPTY_STR(pTrade->TradeSource);
		rsp["InvestUnitID"] = pTrade->InvestUnitID;
		rsp["InstrumentID"] = pTrade->InstrumentID;
		rsp["ExchangeInstID"] = pTrade->ExchangeInstID;

		msg["data"] = rsp;

		std::cout << msg.dump(m_json_indent) << std::endl;
	}

	void OnErrRtnOrderInsert(CThostFtdcInputOrderField * pInputOrder, CThostFtdcRspInfoField * pRspInfo)
	{
		switch (m_cmd)
		{
		case CTPCMD_Buy:
		case CTPCMD_Sell:
			return; // Ignore OnErrRtnOrderInsert event, use OnRtnOrder to handle rejection.
		case CTPCMD_Subscribe:
			break;
		default:
			return;
		}

		using json = nlohmann::ordered_json;

		json msg;
		msg["event"] = "ErrOrderInsert";
		msg["rsp_code"] = pRspInfo->ErrorID;
		msg["rsp_message"] = GBKToUTF8(pRspInfo->ErrorMsg);

		json rsp;
		rsp["BrokerID"] = pInputOrder->BrokerID;
		rsp["InvestorID"] = pInputOrder->InvestorID;
		rsp["OrderRef"] = pInputOrder->OrderRef;
		rsp["UserID"] = pInputOrder->UserID;
		rsp["OrderPriceType"] = ZERO_TO_EMPTY_STR(pInputOrder->OrderPriceType);
		rsp["Direction"] = ZERO_TO_EMPTY_STR(pInputOrder->Direction);
		rsp["CombOffsetFlag"] = pInputOrder->CombOffsetFlag;
		rsp["CombHedgeFlag"] = pInputOrder->CombHedgeFlag;
		rsp["LimitPrice"] = pInputOrder->LimitPrice;
		rsp["VolumeTotalOriginal"] = pInputOrder->VolumeTotalOriginal;
		rsp["TimeCondition"] = ZERO_TO_EMPTY_STR(pInputOrder->TimeCondition);
		rsp["GTDDate"] = pInputOrder->GTDDate;
		rsp["VolumeCondition"] = ZERO_TO_EMPTY_STR(pInputOrder->VolumeCondition);
		rsp["MinVolume"] = pInputOrder->MinVolume;
		rsp["ContingentCondition"] = ZERO_TO_EMPTY_STR(pInputOrder->ContingentCondition);
		rsp["StopPrice"] = pInputOrder->StopPrice;
		rsp["ForceCloseReason"] = ZERO_TO_EMPTY_STR(pInputOrder->ForceCloseReason);
		rsp["IsAutoSuspend"] = pInputOrder->IsAutoSuspend;
		rsp["BusinessUnit"] = pInputOrder->BusinessUnit;
		rsp["RequestID"] = pInputOrder->RequestID;
		rsp["UserForceClose"] = pInputOrder->UserForceClose;
		rsp["IsSwapOrder"] = pInputOrder->IsSwapOrder;
		rsp["ExchangeID"] = pInputOrder->ExchangeID;
		rsp["InvestUnitID"] = pInputOrder->InvestUnitID;
		rsp["AccountID"] = pInputOrder->AccountID;
		rsp["CurrencyID"] = pInputOrder->CurrencyID;
		rsp["ClientID"] = pInputOrder->ClientID;
		rsp["MacAddress"] = pInputOrder->MacAddress;
		rsp["InstrumentID"] = pInputOrder->InstrumentID;
		rsp["IPAddress"] = pInputOrder->IPAddress;

		msg["data"] = rsp;

		std::cout << msg.dump(m_json_indent) << std::endl;
	}

	void OnErrRtnOrderAction(CThostFtdcOrderActionField * pOrderAction, CThostFtdcRspInfoField * pRspInfo)
	{
		switch (m_cmd)
		{
		case CTPCMD_Cancel:
			break;
		case CTPCMD_Subscribe:
			break;
		default:
			return;
		}

		if (m_cmd == CTPCMD_Cancel) {
			if (strcmp(pOrderAction->ExchangeID, m_params.ExchangeID.c_str()) != 0 || strcmp(pOrderAction->OrderSysID, m_params.OrderSysID.c_str()) != 0)
				return;



			if (pRspInfo && pRspInfo->ErrorID) {
				// rejected
				std::cout << error_message(pRspInfo->ErrorID, pRspInfo->ErrorMsg) << std::endl;
				exit(0);
			}
			else {
				std::cout << error_message(CTPCMD_ERR_CODE_DEFAULT, "cancel action rejected") << std::endl;
				exit(0);
			}
		}

		using json = nlohmann::ordered_json;

		json msg;
		msg["event"] = "ErrOrderAction";
		msg["rsp_code"] = pRspInfo->ErrorID;
		msg["rsp_message"] = GBKToUTF8(pRspInfo->ErrorMsg);

		json rsp;
		rsp["BrokerID"] = pOrderAction->BrokerID;
		rsp["InvestorID"] = pOrderAction->InvestorID;
		rsp["OrderActionRef"] = pOrderAction->OrderActionRef;
		rsp["OrderRef"] = pOrderAction->OrderRef;
		rsp["RequestID"] = pOrderAction->RequestID;
		rsp["FrontID"] = pOrderAction->FrontID;
		rsp["SessionID"] = pOrderAction->SessionID;
		rsp["ExchangeID"] = pOrderAction->ExchangeID;
		rsp["OrderSysID"] = pOrderAction->OrderSysID;
		rsp["ActionFlag"] = ZERO_TO_EMPTY_STR(pOrderAction->ActionFlag);
		rsp["LimitPrice"] = pOrderAction->LimitPrice;
		rsp["VolumeChange"] = pOrderAction->VolumeChange;
		rsp["ActionDate"] = pOrderAction->ActionDate;
		rsp["ActionTime"] = pOrderAction->ActionTime;
		rsp["TraderID"] = pOrderAction->TraderID;
		rsp["InstallID"] = pOrderAction->InstallID;
		rsp["OrderLocalID"] = pOrderAction->OrderLocalID;
		rsp["ActionLocalID"] = pOrderAction->ActionLocalID;
		rsp["ParticipantID"] = pOrderAction->ParticipantID;
		rsp["ClientID"] = pOrderAction->ClientID;
		rsp["BusinessUnit"] = pOrderAction->BusinessUnit;
		rsp["OrderActionStatus"] = ZERO_TO_EMPTY_STR(pOrderAction->OrderActionStatus);
		rsp["UserID"] = pOrderAction->UserID;
		rsp["StatusMsg"] = GBKToUTF8(pOrderAction->StatusMsg);
		rsp["BranchID"] = pOrderAction->BranchID;
		rsp["InvestUnitID"] = pOrderAction->InvestUnitID;
		rsp["MacAddress"] = pOrderAction->MacAddress;
		rsp["InstrumentID"] = pOrderAction->InstrumentID;
		rsp["IPAddress"] = pOrderAction->IPAddress;

		msg["data"] = rsp;

		std::cout << msg.dump(m_json_indent) << std::endl;
	}

	void OnRtnInstrumentStatus(CThostFtdcInstrumentStatusField * pInstrumentStatus)
	{
		switch (m_cmd)
		{
		case CTPCMD_Subscribe:
			break;
		default:
			return;
		}

		using json = nlohmann::ordered_json;

		json msg;
		msg["event"] = "InstrumentStatus";

		json rsp;
		rsp["ExchangeID"] = pInstrumentStatus->ExchangeID;
		rsp["SettlementGroupID"] = pInstrumentStatus->SettlementGroupID;
		rsp["InstrumentStatus"] = ZERO_TO_EMPTY_STR(pInstrumentStatus->InstrumentStatus);
		rsp["TradingSegmentSN"] = pInstrumentStatus->TradingSegmentSN;
		rsp["EnterTime"] = pInstrumentStatus->EnterTime;
		rsp["EnterReason"] = ZERO_TO_EMPTY_STR(pInstrumentStatus->EnterReason);
		rsp["ExchangeInstID"] = pInstrumentStatus->ExchangeInstID;
		rsp["InstrumentID"] = pInstrumentStatus->InstrumentID;

		msg["data"] = rsp;

		std::cout << msg.dump(m_json_indent) << std::endl;
	}

	void OnRspOrderInsert(CThostFtdcInputOrderField* pInputOrder, CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast)
	{
		if (pRspInfo && pRspInfo->ErrorID != 0) {
			std::cout << error_message(pRspInfo->ErrorID, pRspInfo->ErrorMsg) << std::endl;
			exit(0);
		}
	}

	void OnRspOrderAction(CThostFtdcInputOrderActionField* pInputOrderAction, CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast)
	{
		if (pRspInfo && pRspInfo->ErrorID != 0) {
			std::cout << error_message(pRspInfo->ErrorID, pRspInfo->ErrorMsg) << std::endl;
			exit(0);
		}
	}


	CThostFtdcTraderApi* m_pTdApi;
	std::string m_BrokerID;
	std::string m_AppID;
	std::string m_AuthCode;
	std::string m_UserProductInfo;
	std::string m_UserID;
	std::string m_Password;
	TThostFtdcFrontIDType m_FrontID;
	TThostFtdcSessionIDType m_SessionID;

	CTPCMD m_cmd;
	CTPCMD_Parameters m_params;
	int m_json_indent;

	TThostFtdcDateType	m_TradingDay;
	std::vector<CThostFtdcTradingAccountField> m_vTradingAccount;
	std::vector<CThostFtdcOrderField> m_vOrder;
	std::vector<CThostFtdcTradeField> m_vTrade;
	std::vector<CThostFtdcInvestorPositionField> m_vInvestorPosition;
	std::vector<CThostFtdcInvestorField> m_vInvestor;
	std::vector<CThostFtdcTradingCodeField> m_vTradingCode;
	std::vector<CThostFtdcInstrumentField> m_vInstrument;
	std::vector<CThostFtdcDepthMarketDataField> m_vDepthMarketData;
	std::vector<CThostFtdcInstrumentMarginRateField> m_vInstrumentMarginRate;
	std::vector<CThostFtdcInstrumentCommissionRateField> m_vInstrumentCommissionRate;
	std::vector<CThostFtdcOptionInstrCommRateField> m_vOptionInstrCommRate;
	std::vector<CThostFtdcExchangeField> m_vExchange;
	std::vector<CThostFtdcProductField> m_vProduct;
	std::vector<CThostFtdcTransferSerialField> m_vTransferSerial;
	std::vector<CThostFtdcAccountregisterField> m_vAccountregister;
	std::vector<CThostFtdcSettlementInfoField> m_vSettlementInfo;
	std::vector<CThostFtdcTransferBankField> m_vTransferBank;
	std::vector<CThostFtdcInvestorPositionDetailField> m_vInvestorPositionDetail;
	std::vector<CThostFtdcSettlementInfoConfirmField> m_vSettlementInfoConfirm;
	std::vector<CThostFtdcInstrumentOrderCommRateField> m_vInstrumentOrderCommRate;
};


int main(int argc, char** argv)
{
	CLI::App app{ "ctpoptorder -- ctpopt command-line trading tool" };
	app.set_help_flag("-h,--help", "Show this help message");
	app.set_help_all_flag("--help-all", "Show full help of all subcommands");
	app.set_version_flag("-v,--version", CTPCMD_VERSION, "show program's version and exit");

	CTPCMD cmd;
	CTPCMD_Parameters params;
	bool no_pretty_print = false;

	std::string flowpath{ "" };
	std::string config{ "brokers_opt.xml" };
	std::string channel;
	std::string user;
	std::string password;
	std::string BrokerID;
	std::string AppID;
	std::string AuthCode;
	std::string UserProductInfo;
	std::string NameServer;
	std::vector<std::string> Hosts;

	app.add_flag("--no-pretty", no_pretty_print, "no pretty json");
	app.add_option("--flowpath", flowpath, "flow path")->envname("CTPCMD_FLOWPATH");
	app.add_option("--config", config, "config file[brokers_opt.xml]")->envname("CTPCMD_CONFIG");
	app.add_option("--channel", channel, "channel name")->envname("CTPCMD_CHANNEL")->required();
	app.add_option("--user", user)->envname("CTPCMD_USER")->required();
	app.add_option("--password", password)->envname("CTPCMD_PASSWORD")->required();
	app.require_subcommand(1);

	THOST_TE_RESUME_TYPE nResumeType;
	std::string ResumeType = "quick";
	auto cmdSubscribe = app.add_subcommand("subscribe", "Subscribe events");
	cmdSubscribe->add_option("mode", ResumeType, "Subscribe Mode[restart/resume/quick]")->required();
	cmdSubscribe->callback([&]() {
		cmd = CTPCMD_Subscribe;

		if (ResumeType == "restart")
			nResumeType = THOST_TERT_RESTART;
		else if (ResumeType == "resume")
			nResumeType = THOST_TERT_RESUME;
		else if (ResumeType == "quick")
			nResumeType = THOST_TERT_QUICK;
		else {
			std::cout << "Invalid subscribe mode, valid mode: restart/resume/quick" << std::endl;
			exit(-1);
		}
		});

	auto cmdQrySettlementInfo = app.add_subcommand("query_settlement", "QrySettlementInfo");
	cmdQrySettlementInfo->add_option("--tradingday", params.TradingDay, "TradingDay");
	cmdQrySettlementInfo->callback([&]() {
		cmd = CTPCMD_QrySettlementInfo;
		});

	app.add_subcommand("confirm_settlement", "SettlementInfoConfirm")->callback([&]() {
		cmd = CTPCMD_SettlementInfoConfirm;
		});

	app.add_subcommand("query_confirm", "QrySettlementInfoConfirm")->callback([&]() {
		cmd = CTPCMD_QrySettlementInfoConfirm;
		});

	app.add_subcommand("query_investor", "QryInvestor")->callback([&]() {
		cmd = CTPCMD_QryInvestor;
		});

	app.add_subcommand("query_code", "QryTradingCode")->callback([&]() {
		cmd = CTPCMD_QryTradingCode;
		});

	app.add_subcommand("query_account", "QryTradingAccount")->callback([&]() {
		cmd = CTPCMD_QryTradingAccount;
		});

	auto cmdQryInvestorPosition = app.add_subcommand("query_position", "QryInvestorPosition");
	cmdQryInvestorPosition->add_option("--exchange", params.ExchangeID, "ExchangeID");
	cmdQryInvestorPosition->add_option("--instrument", params.InstrumentID, "InstrumentID");
	cmdQryInvestorPosition->callback([&]() {
		cmd = CTPCMD_QryInvestorPosition;
		});

	auto cmdQryPositionDetail = app.add_subcommand("query_detail", "QryInvestorPositionDetail");
	cmdQryPositionDetail->add_option("--exchange", params.ExchangeID, "ExchangeID");
	cmdQryPositionDetail->add_option("--instrument", params.InstrumentID, "InstrumentID");
	cmdQryPositionDetail->callback([&]() {
		cmd = CTPCMD_QryInvestorPositionDetail;
		});

	auto cmdQryOrder = app.add_subcommand("query_order", "QryOrder");
	cmdQryOrder->add_option("--exchange", params.ExchangeID, "ExchangeID");
	cmdQryOrder->add_option("--instrument", params.InstrumentID, "InstrumentID");
	cmdQryOrder->add_option("--orderid", params.OrderSysID, "OrderSysID");
	cmdQryOrder->callback([&]() {
		cmd = CTPCMD_QryOrder;
		});

	auto cmdQryTrade = app.add_subcommand("query_trade", "QryTrade");
	cmdQryTrade->add_option("--exchange", params.ExchangeID, "ExchangeID");
	cmdQryTrade->add_option("--instrument", params.InstrumentID, "InstrumentID");
	cmdQryTrade->callback([&]() {
		cmd = CTPCMD_QryTrade;
		});

	auto cmdQryExchange = app.add_subcommand("query_exchange", "QryExchange");
	cmdQryExchange->add_option("--exchange", params.ExchangeID, "ExchangeID");
	cmdQryExchange->callback([&]() {
		cmd = CTPCMD_QryExchange;
		});

	auto cmdQryProduct = app.add_subcommand("query_product", "QryProduct");
	cmdQryProduct->add_option("--exchange", params.ExchangeID, "ExchangeID");
	cmdQryProduct->add_option("--product", params.ProductID, "ProductID");
	cmdQryProduct->callback([&]() {
		cmd = CTPCMD_QryProduct;
		});

	auto cmdQryInstrument = app.add_subcommand("query_instrument", "QryInstrument");
	cmdQryInstrument->add_option("--exchange", params.ExchangeID, "ExchangeID");
	cmdQryInstrument->add_option("--product", params.ProductID, "ProductID");
	cmdQryInstrument->add_option("--instrument", params.InstrumentID, "InstrumentID");
	cmdQryInstrument->callback([&]() {
		cmd = CTPCMD_QryInstrument;
		});

	auto cmdQryDepthMarketData = app.add_subcommand("query_price", "QryDepthMarketData");
	cmdQryDepthMarketData->add_option("--exchange", params.ExchangeID, "ExchangeID");
	cmdQryDepthMarketData->add_option("--instrument", params.InstrumentID, "InstrumentID");
	cmdQryDepthMarketData->callback([&]() {
		cmd = CTPCMD_QryDepthMarketData;
		});

	auto cmdQryInstrumentCommissionRate = app.add_subcommand("query_fee", "QryInstrumentCommissionRate");
	cmdQryInstrumentCommissionRate->add_option("--exchange", params.ExchangeID, "ExchangeID");
	cmdQryInstrumentCommissionRate->add_option("--instrument", params.InstrumentID, "InstrumentID");
	cmdQryInstrumentCommissionRate->callback([&]() {
		cmd = CTPCMD_QryInstrumentCommissionRate;
		});

	auto cmdQryOptionInstrCommRate = app.add_subcommand("query_optionfee", "QryOptionInstrCommRate");
	cmdQryOptionInstrCommRate->add_option("--exchange", params.ExchangeID, "ExchangeID");
	cmdQryOptionInstrCommRate->add_option("--instrument", params.InstrumentID, "InstrumentID");
	cmdQryOptionInstrCommRate->callback([&]() {
		cmd = CTPCMD_QryOptionInstrCommRate;
		});

	auto cmdQryInstrumentOrderCommRate = app.add_subcommand("query_orderfee", "QryInstrumentOrderCommRate");
	cmdQryInstrumentOrderCommRate->add_option("--exchange", params.ExchangeID, "ExchangeID");
	cmdQryInstrumentOrderCommRate->callback([&]() {
		cmd = CTPCMD_QryInstrumentOrderCommRate;
		});

	auto cmdQryInstrumentMarginRate = app.add_subcommand("query_margin", "QryInstrumentMarginRate");
	cmdQryInstrumentMarginRate->add_option("--exchange", params.ExchangeID, "ExchangeID");
	cmdQryInstrumentMarginRate->add_option("--instrument", params.InstrumentID, "InstrumentID");
	cmdQryInstrumentMarginRate->callback([&]() {
		cmd = CTPCMD_QryInstrumentMarginRate;
		});

	app.add_subcommand("query_cashflow", "QryTransferSerial")->callback([&]() {
		cmd = CTPCMD_QryTransferSerial;
		});

	app.add_subcommand("query_register", "QryAccountRegister")->callback([&]() {
		cmd = CTPCMD_QryAccountregister;
		});

	app.add_subcommand("query_bank", "QryTransferBank")->callback([&]() {
		cmd = CTPCMD_QryTransferBank;
		});

	/*
	* order command format :
	*
	* <buy|sell> <open|close|closetoday> [hedge|arbi] <num> share[s] of <exchange.instrument> at <price>
	*
	* example:
	* buy open 5 shares of SHFE.ag2701 at 10000
	* buy close 3 shares of SHFE.ag2701 at market
	* sell closetoday 1 share of SHFE.ag2701 at 9950.5
	*/

	auto cmdbuy = app.add_subcommand("buy", "Order Buy");
	std::vector<std::string> buy_tokens;
	std::string cmdbuy_parameters;
	cmdbuy->allow_extras();
	cmdbuy->callback([&]() {
		cmd = CTPCMD_Buy;
		buy_tokens = cmdbuy->remaining();
		cmdbuy_parameters = StringJoin(buy_tokens);
		std::regex reg("(open|close|closetoday)?\\s*(hedge)?\\s+(\\d+)\\s+share[s]?\\s+of\\s+(\\S+)\\.(\\S+)\\s+at\\s+(market|-?\\d+|-?\\d+\\.\\d+)");
		std::smatch m;
		if (!std::regex_match(cmdbuy_parameters, m, reg)) {
			std::cout << "invalid order parameters:" << cmdbuy_parameters << std::endl;
			exit(-1);
		}

		// open|close
		if (m[1] == "open") {
			params.OffsetFlag = THOST_FTDC_OF_Open;
		}
		else if (m[1] == "close") {
			params.OffsetFlag = THOST_FTDC_OF_Close;
		}
		else if (m[1] == "closetoday") {
			params.OffsetFlag = THOST_FTDC_OF_CloseToday;
		}
		else {
			std::cout << "invalid open|close parameters:" << cmdbuy_parameters << std::endl;
			exit(-1);
		}

		// hedge
		if (m[2] == "") {
			params.HedgeFlag = THOST_FTDC_HF_Speculation;
		}
		else if (m[2] == "hedge") {
			params.HedgeFlag = THOST_FTDC_HF_Hedge;
		}
		else if (m[2] == "arbi") {
			params.HedgeFlag = THOST_FTDC_HF_Arbitrage;
		}
		else {
			std::cout << "invalid hedge parameters:" << cmdbuy_parameters << std::endl;
			exit(-1);
		}

		// Volume
		params.Volume = std::stoi(m[3]);

		// Price
		if (m[6] == "market") {
			params.OrderPriceType = THOST_FTDC_OPT_AnyPrice;
			params.Price = 0;
		}
		else {
			params.OrderPriceType = THOST_FTDC_OPT_LimitPrice;
			params.Price = std::stod(m[6]);
		}

		// ExchangeID
		params.ExchangeID = m[4];

		// Instrument
		params.InstrumentID = m[5];
		});

	auto cmdsell = app.add_subcommand("sell", "Order Sell");
	std::vector<std::string> sell_tokens;
	std::string cmdsell_parameters;
	cmdsell->allow_extras();
	cmdsell->callback([&]() {
		cmd = CTPCMD_Sell;
		sell_tokens = cmdsell->remaining();
		cmdsell_parameters = StringJoin(sell_tokens);
		std::regex reg("(open|close|closetoday)?\\s*(hedge)?\\s+(\\d+)\\s+share[s]?\\s+of\\s+(\\S+)\\.(\\S+)\\s+at\\s+(market|-?\\d+|-?\\d+\\.\\d+)");
		std::smatch m;
		if (!std::regex_match(cmdsell_parameters, m, reg)) {
			std::cout << "invalid order parameters:" << cmdsell_parameters << std::endl;
			exit(-1);
		}

		// open|close
		if (m[1] == "open") {
			params.OffsetFlag = THOST_FTDC_OF_Open;
		}
		else if (m[1] == "close") {
			params.OffsetFlag = THOST_FTDC_OF_Close;
		}
		else if (m[1] == "closetoday") {
			params.OffsetFlag = THOST_FTDC_OF_CloseToday;
		}
		else {
			std::cout << "invalid open|close parameters:" << cmdbuy_parameters << std::endl;
			exit(-1);
		}

		// hedge
		if (m[2] == "") {
			params.HedgeFlag = THOST_FTDC_HF_Speculation;
		}
		else if (m[2] == "hedge") {
			params.HedgeFlag = THOST_FTDC_HF_Hedge;
		}
		else if (m[2] == "arbi") {
			params.HedgeFlag = THOST_FTDC_HF_Arbitrage;
		}
		else {
			std::cout << "invalid open|close parameters:" << cmdbuy_parameters << std::endl;
			exit(-1);
		}

		// Volume
		params.Volume = std::stoi(m[3]);

		// Price
		if (m[6] == "market") {
			params.OrderPriceType = THOST_FTDC_OPT_AnyPrice;
			params.Price = 0;
		}
		else {
			params.OrderPriceType = THOST_FTDC_OPT_LimitPrice;
			params.Price = std::stod(m[6]);
		}

		// ExchangeID
		params.ExchangeID = m[4];

		// Instrument
		params.InstrumentID = m[5];
		});

	/*
	* cancel command format :
	*
	* cancel <id> of <exchange.instrument>
	*
	* example:
	* cancel 12388 of SHFE.ag2701
	* cancel "    12388" of SHFE.ag2701 (Don't miss the space chars of OrderSysID on ctp.)
	*/
	auto cmdcancel = app.add_subcommand("cancel", "Order Cancel");
	std::vector<std::string> cancel_tokens;
	std::string cmdcancel_parameters;
	cmdcancel->allow_extras();
	cmdcancel->callback([&]() {
		cmd = CTPCMD_Cancel;
		cancel_tokens = cmdcancel->remaining();
		cmdcancel_parameters = StringJoin(cancel_tokens);
		std::regex reg("(\\s*\\S+)\\s+of\\s+(\\S+)\\.(\\S+)");
		std::smatch m;
		if (!std::regex_match(cmdcancel_parameters, m, reg)) {
			std::cout << "invalid cancel parameters:" << cmdcancel_parameters << std::endl;
			exit(-1);
		}

		// OrderSysID
		params.OrderSysID = m[1];

		// ExchangeID
		params.ExchangeID = m[2];

		// Instrument
		params.InstrumentID = m[3];
		});

	try { app.parse(argc, argv); }
	catch (const CLI::ParseError& e) { return app.exit(e); }

	tinyxml2::XMLDocument doc;
	if (doc.LoadFile(config.c_str()) != tinyxml2::XML_SUCCESS) {
		std::cout<<"Failed to load config file: "<< config << std::endl;
		return -1;
	}

	tinyxml2::XMLElement* element;
	element = doc.FirstChildElement("brokers")->FirstChildElement("broker");
	while (element) {
		std::string BrokerName = element->Attribute("name");
		if (channel != BrokerName) {
			element = element->NextSiblingElement();
			continue;
		}

		BrokerID = element->FirstChildElement("BrokerID") && element->FirstChildElement("BrokerID")->GetText() ? element->FirstChildElement("BrokerID")->GetText() : "";
		AppID = element->FirstChildElement("AppID") && element->FirstChildElement("AppID")->GetText() ? element->FirstChildElement("AppID")->GetText() : "";
		AuthCode = element->FirstChildElement("AuthCode") && element->FirstChildElement("AuthCode")->GetText() ? element->FirstChildElement("AuthCode")->GetText() : "";
		UserProductInfo = element->FirstChildElement("UserProductInfo") && element->FirstChildElement("UserProductInfo")->GetText() ? element->FirstChildElement("UserProductInfo")->GetText() : "";

		tinyxml2::XMLElement* pNameServerElement = element->FirstChildElement("NameServer");
		if (pNameServerElement) {
			NameServer = pNameServerElement->GetText();
		}

		tinyxml2::XMLElement* front = element->FirstChildElement("tradefront");
		tinyxml2::XMLElement* address = front->FirstChildElement("addresses")->FirstChildElement("address");
		while (address) {
			std::string Host = address->GetText();
			Hosts.push_back(Host);
			address = address->NextSiblingElement();
		}
		break;
	}

	CThostFtdcTraderApi* pTdApi = CThostFtdcTraderApi::CreateFtdcTraderApi(flowpath.c_str());
	CCTPTdSpiImpl Spi(pTdApi, BrokerID, AppID, AuthCode, UserProductInfo, user, password, cmd, params, !no_pretty_print);
	pTdApi->RegisterSpi(&Spi);

	// THOST_TERT_NONE is not supported on both topics
	switch (cmd)
	{
	case CTPCMD_Buy:
	case CTPCMD_Sell:
	case CTPCMD_Cancel:
		pTdApi->SubscribePrivateTopic(THOST_TERT_QUICK);
		pTdApi->SubscribePublicTopic(THOST_TERT_QUICK);
		break;
	case CTPCMD_Subscribe:
		pTdApi->SubscribePrivateTopic(nResumeType);
		pTdApi->SubscribePublicTopic(nResumeType);
		break;
	default:
		pTdApi->SubscribePrivateTopic(THOST_TERT_QUICK);
		pTdApi->SubscribePublicTopic(THOST_TERT_QUICK);
		break;
	}

	if (Hosts.size() == 0) {
		std::cout << "No host found for channel: " << channel << std::endl;
		return -1;
	}
	for(auto host:Hosts)
		pTdApi->RegisterFront((char*)host.c_str());
	pTdApi->Init();

	getchar();

	return 0;
}
