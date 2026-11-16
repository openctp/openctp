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
#include "CLI.hpp"
#include "tinyxml2.h"
#include "json.hpp"
#include "ThostFtdcTraderApi.h"

#define CTPCMD_ERR_CODE_DEFAULT 9999
#define CTPCMD_PRICE_VERSION "1.0.0"

enum CTPCMD
{
	CTPCMD_SettlementInfoConfirm,
	CTPCMD_QryTradingAccount
};

// GBK -> UTF-8
std::string GBKToUTF8(const std::string& gbk)
{
	if (gbk.empty()) return std::string();

#ifdef _WIN32
	// ---- Windows: 用 WideChar 作为中转 (GBK -> UTF-16 -> UTF-8) ----
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
	// ---- Linux/macOS: 用 iconv ----
	iconv_t cd = iconv_open("UTF-8", "GBK");
	if (cd == (iconv_t)-1) return std::string();

	// 输出缓冲区：GBK 每字符最多 2 字节，UTF-8 最多 3 字节，留足空间
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

std::string error_message(int rsp_code, const char* rsp_message)
{
	using json = nlohmann::ordered_json;

	json msg;
	msg["rsp_code"] = rsp_code;
	msg["rsp_message"] = GBKToUTF8(rsp_message);

	return msg.dump();
}


class CCTPTdSpiImpl :public CThostFtdcTraderSpi
{
public:
	CCTPTdSpiImpl(CThostFtdcTraderApi* pTdApi, std::string BrokerID, std::string AppID, std::string AuthCode, std::string UserProductInfo, std::string UserID, std::string Password, CTPCMD cmd):
		m_pTdApi(pTdApi),
		m_BrokerID(std::move(BrokerID)),
		m_AppID(std::move(AppID)),
		m_AuthCode(std::move(AuthCode)),
		m_UserProductInfo(std::move(UserProductInfo)),
		m_UserID(std::move(UserID)),
		m_Password(std::move(Password)),
		m_cmd(cmd)
	{
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
		strcpy(Req.AuthCode, m_AuthCode.c_str()); // XTP的认证Key超长，需要借用到后一字段（AppID）的空间
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

	void OnRspUserLogin(CThostFtdcRspUserLoginField* pRspUserLogin, CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast)
	{
		if (pRspInfo && pRspInfo->ErrorID != 0) {
			std::cout << error_message(pRspInfo->ErrorID, pRspInfo->ErrorMsg) << std::endl;
			exit(0);
		}

		strncpy(m_TradingDay, pRspUserLogin->TradingDay, sizeof(m_TradingDay) - 1);

		switch (m_cmd)
		{
		case CTPCMD_SettlementInfoConfirm:
		{
			CThostFtdcSettlementInfoConfirmField SettlementInfoConfirm{};

			strncpy(SettlementInfoConfirm.BrokerID, m_BrokerID.c_str(), sizeof(SettlementInfoConfirm.BrokerID) - 1);
			strncpy(SettlementInfoConfirm.InvestorID, m_UserID.c_str(), sizeof(SettlementInfoConfirm.InvestorID) - 1);
			strncpy(SettlementInfoConfirm.ConfirmDate, pRspUserLogin->TradingDay, sizeof(SettlementInfoConfirm.ConfirmDate) - 1);

			if (m_pTdApi->ReqSettlementInfoConfirm(&SettlementInfoConfirm, 0) != 0) {
				std::cout << error_message(CTPCMD_ERR_CODE_DEFAULT, "SettlementInfoConfirm failed.") << std::endl;
				exit(0);
			}
		}
		break;
		case CTPCMD_QryTradingAccount:
		{
			CThostFtdcQryTradingAccountField QryTradingAccount{};

			strncpy(QryTradingAccount.BrokerID, m_BrokerID.c_str(), sizeof(QryTradingAccount.BrokerID) - 1);
			strncpy(QryTradingAccount.InvestorID, m_UserID.c_str(), sizeof(QryTradingAccount.InvestorID) - 1);

			if (m_pTdApi->ReqQryTradingAccount(&QryTradingAccount, 0) != 0) {
				std::cout << error_message(CTPCMD_ERR_CODE_DEFAULT, "QryTradingAccount failed.") << std::endl;
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

	void OnRspSettlementInfoConfirm(CThostFtdcSettlementInfoConfirmField* pSettlementInfoConfirm, CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast)
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

		std::cout << msg.dump() << std::endl;

		exit(0);
	}

	void OnRspQryTradingAccount(CThostFtdcTradingAccountField* pTradingAccount, CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast)
	{
		if (m_cmd != CTPCMD_QryTradingAccount)
			return;
		if (pRspInfo && pRspInfo->ErrorID != 0) {
			std::cout << error_message(pRspInfo->ErrorID, pRspInfo->ErrorMsg) << std::endl;
			exit(0);
		}

		using json = nlohmann::ordered_json;

		json msg;
		msg["rsp_code"] = 0;
		msg["rsp_message"] = "";

		json rsp;
		rsp["BrokerID"] = pTradingAccount->BrokerID;
		rsp["AccountID"] = pTradingAccount->AccountID;
		rsp["PreMortgage"] = pTradingAccount->PreMortgage;
		rsp["PreCredit"] = pTradingAccount->PreCredit;
		rsp["PreDeposit"] = pTradingAccount->PreDeposit;
		rsp["PreBalance"] = pTradingAccount->PreBalance;
		rsp["PreMargin"] = pTradingAccount->PreMargin;
		rsp["InterestBase"] = pTradingAccount->InterestBase;
		rsp["Interest"] = pTradingAccount->Interest;
		rsp["Deposit"] = pTradingAccount->Deposit;
		rsp["Withdraw"] = pTradingAccount->Withdraw;
		rsp["FrozenMargin"] = pTradingAccount->FrozenMargin;
		rsp["FrozenCash"] = pTradingAccount->FrozenCash;
		rsp["FrozenCommission"] = pTradingAccount->FrozenCommission;
		rsp["CurrMargin"] = pTradingAccount->CurrMargin;
		rsp["CashIn"] = pTradingAccount->CashIn;
		rsp["Commission"] = pTradingAccount->Commission;
		rsp["CloseProfit"] = pTradingAccount->CloseProfit;
		rsp["PositionProfit"] = pTradingAccount->PositionProfit;
		rsp["Balance"] = pTradingAccount->Balance;
		rsp["Available"] = pTradingAccount->Available;
		rsp["WithdrawQuota"] = pTradingAccount->WithdrawQuota;
		rsp["Reserve"] = pTradingAccount->Reserve;
		rsp["TradingDay"] = pTradingAccount->TradingDay;
		rsp["SettlementID"] = pTradingAccount->SettlementID;
		rsp["Credit"] = pTradingAccount->Credit;
		rsp["Mortgage"] = pTradingAccount->Mortgage;
		rsp["ExchangeMargin"] = pTradingAccount->ExchangeMargin;
		rsp["DeliveryMargin"] = pTradingAccount->DeliveryMargin;
		rsp["ExchangeDeliveryMargin"] = pTradingAccount->ExchangeDeliveryMargin;
		rsp["ReserveBalance"] = pTradingAccount->ReserveBalance;
		rsp["CurrencyID"] = pTradingAccount->CurrencyID;
		rsp["PreFundMortgageIn"] = pTradingAccount->PreFundMortgageIn;
		rsp["PreFundMortgageOut"] = pTradingAccount->PreFundMortgageOut;
		rsp["FundMortgageIn"] = pTradingAccount->FundMortgageIn;
		rsp["FundMortgageOut"] = pTradingAccount->FundMortgageOut;
		rsp["FundMortgageAvailable"] = pTradingAccount->FundMortgageAvailable;
		rsp["MortgageableFund"] = pTradingAccount->MortgageableFund;
		rsp["SpecProductMargin"] = pTradingAccount->SpecProductMargin;
		rsp["SpecProductFrozenMargin"] = pTradingAccount->SpecProductFrozenMargin;
		rsp["SpecProductCommission"] = pTradingAccount->SpecProductCommission;
		rsp["SpecProductFrozenCommission"] = pTradingAccount->SpecProductFrozenCommission;
		rsp["SpecProductPositionProfit"] = pTradingAccount->SpecProductPositionProfit;
		rsp["SpecProductCloseProfit"] = pTradingAccount->SpecProductCloseProfit;
		rsp["SpecProductPositionProfitByAlg"] = pTradingAccount->SpecProductPositionProfitByAlg;
		rsp["SpecProductExchangeMargin"] = pTradingAccount->SpecProductExchangeMargin;
		rsp["BizType"] = pTradingAccount->BizType;
		rsp["FrozenSwap"] = pTradingAccount->FrozenSwap;
		rsp["RemainSwap"] = pTradingAccount->RemainSwap;

		msg["data"].push_back(rsp);

		std::cout << msg.dump() << std::endl;

		exit(0);
	}

	CThostFtdcTraderApi* m_pTdApi;
	std::string m_BrokerID;
	std::string m_AppID;
	std::string m_AuthCode;
	std::string m_UserProductInfo;
	std::string m_UserID;
	std::string m_Password;
	CTPCMD m_cmd;

	TThostFtdcDateType	m_TradingDay;
};


int main(int argc, char** argv)
{
	CLI::App app{ "ctpprice -- price command" };
	CTPCMD cmd;
	std::string config{ "brokers.xml" };
	std::string channel;
	std::string user;
	std::string password;
	std::string BrokerID;
	std::string AppID;
	std::string AuthCode;
	std::string UserProductInfo;
	std::string NameServer;
	std::vector<std::string> Hosts;

	app.add_option("--config", config, "config file[brokers.xml]");
	app.add_option("--channel", channel, "channel name")->required();
	app.add_option("--user", user);
	app.add_option("--password", password);
	app.require_subcommand(1);

	std::string instrument_list;
	auto cmd_query = app.add_subcommand("confirm_settlement", "SettlementInfoConfirm");
	cmd_query->callback([&]() {
		cmd = CTPCMD_SettlementInfoConfirm;
		});

	auto cmd_subscribe = app.add_subcommand("query_account", "QryTradingAccount");
	cmd_subscribe->callback([&]() {
		cmd = CTPCMD_QryTradingAccount;
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

	CThostFtdcTraderApi* pTdApi = CThostFtdcTraderApi::CreateFtdcTraderApi();
	CCTPTdSpiImpl Spi(pTdApi, BrokerID, AppID, AuthCode, UserProductInfo, user, password, cmd);
	pTdApi->RegisterSpi(&Spi);
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
