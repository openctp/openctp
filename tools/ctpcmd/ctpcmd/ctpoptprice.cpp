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
#include "ThostFtdcMdApi.h"

#define CTPCMD_ERR_CODE_DEFAULT 9999
#define CTPCMD_OPTPRICE_VERSION "1.0.0"

enum CTPCMD
{
	CTPCMD_QUERY,
	CTPCMD_SUBSCRIBE
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

#define DBLMAX_TO_NULL(value) (value == DBL_MAX ? json(nullptr) : json(value))

using namespace ctp_sopt;

class CCTPMdSpiImpl :public CThostFtdcMdSpi
{
public:
	CCTPMdSpiImpl(CThostFtdcMdApi* pMdApi, std::string BrokerID, std::string UserID, std::string Password, CTPCMD cmd, std::vector<std::pair<std::string,std::string>> instruments, bool pretty_print):
		m_pMdApi(pMdApi),
		m_BrokerID(std::move(BrokerID)),
		m_UserID(std::move(UserID)),
		m_Password(std::move(Password)),
		m_cmd(cmd),
		m_instruments(std::move(instruments))
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
		CThostFtdcReqUserLoginField Req{};
		strncpy(Req.BrokerID, m_BrokerID.c_str(), sizeof(Req.BrokerID) - 1);
		strncpy(Req.UserID, m_UserID.c_str(), sizeof(Req.UserID) - 1);
		strncpy(Req.Password, m_Password.c_str(), sizeof(Req.Password) - 1);

		if (m_pMdApi->ReqUserLogin(&Req, 0) != 0) {
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

		// Subscribe
		TThostFtdcInstrumentIDType Instruments[100];
		char* ppInstrumentID[100];
		int count = 0;
		memset(Instruments, 0x00, sizeof(Instruments));
		for (auto& instrument : m_instruments) {
			strncpy(Instruments[count], instrument.second.c_str(), sizeof(TThostFtdcInstrumentIDType) - 1);
			ppInstrumentID[count] = Instruments[count];
			count++;
			if (count == sizeof(Instruments) / sizeof(TThostFtdcInstrumentIDType)) {
				if (m_pMdApi->SubscribeMarketData(ppInstrumentID, count)!=0) {
					std::cout << error_message(CTPCMD_ERR_CODE_DEFAULT, "Subscribe failed.") << std::endl;
					exit(0);
				}
				m_pMdApi->SubscribeMarketData(ppInstrumentID, count);
				count = 0;
			}
		}
		if (count) {
			if (m_pMdApi->SubscribeMarketData(ppInstrumentID, count) != 0) {
				std::cout << error_message(CTPCMD_ERR_CODE_DEFAULT, "Subscribe failed.") << std::endl;
				exit(0);
			}
		}
	}

	void OnRspSubMarketData(CThostFtdcSpecificInstrumentField* pSpecificInstrument, CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast)
	{
		if (m_cmd != CTPCMD_QUERY)
			return;
		if (pRspInfo && pRspInfo->ErrorID != 0) {
			if ( !pSpecificInstrument || strlen(pSpecificInstrument->InstrumentID)==0)
				return;
			CThostFtdcDepthMarketDataField DepthMarketData{};
			strncpy(DepthMarketData.InstrumentID, pSpecificInstrument->InstrumentID, sizeof(DepthMarketData.InstrumentID) - 1);
			m_prices[pSpecificInstrument->InstrumentID] = DepthMarketData;
			return;
		}
	}

	void OnRtnDepthMarketData(CThostFtdcDepthMarketDataField* pDepthMarketData)
	{
		using json = nlohmann::ordered_json;


		if (m_cmd == CTPCMD_QUERY) {
			m_prices[pDepthMarketData->InstrumentID] = *pDepthMarketData;

			if (m_prices.size() == m_instruments.size()) {
				// All instruments reponsed.
				json msg;
				msg["rsp_code"] = 0;
				msg["rsp_message"] = "";

				for (auto item : m_prices) {
					json price;
					price["ExchangeID"] = item.second.ExchangeID;
					price["InstrumentID"] = item.second.InstrumentID;
					price["LastPrice"] = DBLMAX_TO_NULL(item.second.LastPrice);
					price["OpenPrice"] = DBLMAX_TO_NULL(item.second.OpenPrice);
					price["HighestPrice"] = DBLMAX_TO_NULL(item.second.HighestPrice);
					price["LowestPrice"] = DBLMAX_TO_NULL(item.second.LowestPrice);
					price["ClosePrice"] = DBLMAX_TO_NULL(item.second.ClosePrice);
					price["SettlementPrice"] = DBLMAX_TO_NULL(item.second.SettlementPrice);
					price["AveragePrice"] = DBLMAX_TO_NULL(item.second.AveragePrice);
					price["Volume"] = item.second.Volume;
					price["Turnover"] = DBLMAX_TO_NULL(item.second.Turnover);
					price["OpenInterest"] = item.second.OpenInterest;
					price["PreSettlementPrice"] = DBLMAX_TO_NULL(item.second.PreSettlementPrice);
					price["PreClosePrice"] = DBLMAX_TO_NULL(item.second.PreClosePrice);
					price["PreOpenInterest"] = item.second.PreOpenInterest;
					price["UpperLimitPrice"] = DBLMAX_TO_NULL(item.second.UpperLimitPrice);
					price["LowerLimitPrice"] = DBLMAX_TO_NULL(item.second.LowerLimitPrice);
					price["ActionDay"] = item.second.ActionDay;
					price["UpdateTime"] = item.second.UpdateTime;
					price["UpdateMillisec"] = item.second.UpdateMillisec;
					price["TradingDay"] = item.second.TradingDay;

					price["BidPrice1"] = DBLMAX_TO_NULL(item.second.BidPrice1);
					price["BidVolume1"] = item.second.BidVolume1;
					price["BidPrice2"] = DBLMAX_TO_NULL(item.second.BidPrice2);
					price["BidVolume2"] = item.second.BidVolume2;
					price["BidPrice3"] = DBLMAX_TO_NULL(item.second.BidPrice3);
					price["BidVolume3"] = item.second.BidVolume3;
					price["BidPrice4"] = DBLMAX_TO_NULL(item.second.BidPrice4);
					price["BidVolume4"] = item.second.BidVolume4;
					price["BidPrice5"] = DBLMAX_TO_NULL(item.second.BidPrice5);
					price["BidVolume5"] = item.second.BidVolume5;

					price["AskPrice1"] = DBLMAX_TO_NULL(item.second.AskPrice1);
					price["AskVolume1"] = item.second.AskVolume1;
					price["AskPrice2"] = DBLMAX_TO_NULL(item.second.AskPrice2);
					price["AskVolume2"] = item.second.AskVolume2;
					price["AskPrice3"] = DBLMAX_TO_NULL(item.second.AskPrice3);
					price["AskVolume3"] = item.second.AskVolume3;
					price["AskPrice4"] = DBLMAX_TO_NULL(item.second.AskPrice4);
					price["AskVolume4"] = item.second.AskVolume4;
					price["AskPrice5"] = DBLMAX_TO_NULL(item.second.AskPrice5);
					price["AskVolume5"] = item.second.AskVolume5;

					msg["data"].push_back(price);
				}

				std::cout << msg.dump(m_json_indent) << std::endl;
				exit(0);
			}

			return;
		}

		json msg;
		msg["event"] = "DepthMarketData";

		json price;
		price["ExchangeID"] = pDepthMarketData->ExchangeID;
		price["InstrumentID"] = pDepthMarketData->InstrumentID;
		price["LastPrice"] = DBLMAX_TO_NULL(pDepthMarketData->LastPrice);
		price["OpenPrice"] = DBLMAX_TO_NULL(pDepthMarketData->OpenPrice);
		price["HighestPrice"] = DBLMAX_TO_NULL(pDepthMarketData->HighestPrice);
		price["LowestPrice"] = DBLMAX_TO_NULL(pDepthMarketData->LowestPrice);
		price["ClosePrice"] = DBLMAX_TO_NULL(pDepthMarketData->ClosePrice);
		price["SettlementPrice"] = DBLMAX_TO_NULL(pDepthMarketData->SettlementPrice);
		price["AveragePrice"] = DBLMAX_TO_NULL(pDepthMarketData->AveragePrice);
		price["Volume"] = pDepthMarketData->Volume;
		price["Turnover"] = DBLMAX_TO_NULL(pDepthMarketData->Turnover);
		price["OpenInterest"] = pDepthMarketData->OpenInterest;
		price["PreSettlementPrice"] = DBLMAX_TO_NULL(pDepthMarketData->PreSettlementPrice);
		price["PreClosePrice"] = DBLMAX_TO_NULL(pDepthMarketData->PreClosePrice);
		price["PreOpenInterest"] = pDepthMarketData->PreOpenInterest;
		price["UpperLimitPrice"] = DBLMAX_TO_NULL(pDepthMarketData->UpperLimitPrice);
		price["LowerLimitPrice"] = DBLMAX_TO_NULL(pDepthMarketData->LowerLimitPrice);

		price["ActionDay"] = pDepthMarketData->ActionDay;
		price["UpdateTime"] = pDepthMarketData->UpdateTime;
		price["UpdateMillisec"] = pDepthMarketData->UpdateMillisec;
		price["TradingDay"] = pDepthMarketData->TradingDay;

		price["BidPrice1"] = DBLMAX_TO_NULL(pDepthMarketData->BidPrice1);
		price["BidVolume1"] = pDepthMarketData->BidVolume1;
		price["BidPrice2"] = DBLMAX_TO_NULL(pDepthMarketData->BidPrice2);
		price["BidVolume2"] = pDepthMarketData->BidVolume2;
		price["BidPrice3"] = DBLMAX_TO_NULL(pDepthMarketData->BidPrice3);
		price["BidVolume3"] = pDepthMarketData->BidVolume3;
		price["BidPrice4"] = DBLMAX_TO_NULL(pDepthMarketData->BidPrice4);
		price["BidVolume4"] = pDepthMarketData->BidVolume4;
		price["BidPrice5"] = DBLMAX_TO_NULL(pDepthMarketData->BidPrice5);
		price["BidVolume5"] = pDepthMarketData->BidVolume5;

		price["AskPrice1"] = DBLMAX_TO_NULL(pDepthMarketData->AskPrice1);
		price["AskVolume1"] = pDepthMarketData->AskVolume1;
		price["AskPrice2"] = DBLMAX_TO_NULL(pDepthMarketData->AskPrice2);
		price["AskVolume2"] = pDepthMarketData->AskVolume2;
		price["AskPrice3"] = DBLMAX_TO_NULL(pDepthMarketData->AskPrice3);
		price["AskVolume3"] = pDepthMarketData->AskVolume3;
		price["AskPrice4"] = DBLMAX_TO_NULL(pDepthMarketData->AskPrice4);
		price["AskVolume4"] = pDepthMarketData->AskVolume4;
		price["AskPrice5"] = DBLMAX_TO_NULL(pDepthMarketData->AskPrice5);
		price["AskVolume5"] = pDepthMarketData->AskVolume5;

		msg["data"] = price;

		std::cout << msg.dump(m_json_indent) << std::endl;
	}


	CThostFtdcMdApi* m_pMdApi;
	std::string m_BrokerID;
	std::string m_UserID;
	std::string m_Password;
	CTPCMD m_cmd;
	int m_json_indent;

	std::vector<std::pair<std::string, std::string>> m_instruments;
	std::map<std::string, CThostFtdcDepthMarketDataField> m_prices;
};

std::vector<std::pair<std::string, std::string>> parse_instrument_list(const std::string& input)
{
	std::vector<std::pair<std::string, std::string>> result;
	std::stringstream ss(input);
	std::string token;

	while (std::getline(ss, token, ','))
	{
		size_t dot_pos = token.find('.');
		std::string exchange;
		std::string instrument;

		if (dot_pos != std::string::npos)
		{
			exchange = token.substr(0, dot_pos);
			instrument = token.substr(dot_pos + 1);
		}
		else
		{
			exchange = "";
			instrument = token;
		}
		result.emplace_back(exchange, instrument);
	}
	return result;
}


int main(int argc, char** argv)
{
	CLI::App app{ "ctpoptprice -- ctpopt command-line market tool" };
	CTPCMD cmd;
	bool no_pretty_print = false;

	std::string config{ "optbrokers.xml" };
	std::string channel;
	std::string user;
	std::string password;
	std::string BrokerID;
	std::string AppID;
	std::string AuthCode;
	std::string UserProductInfo;
	std::string NameServer;
	std::vector<std::string> Hosts;
	std::vector<std::pair<std::string, std::string>> instruments;

	app.add_option("--config", config, "config file[optbrokers.xml]");
	app.add_option("--channel", channel, "channel name")->required();
	app.add_option("--user", user);
	app.add_option("--password", password);
	app.add_flag("--no-pretty", no_pretty_print, "no pretty json");
	app.require_subcommand(1);

	std::string instrument_list;
	auto cmd_query = app.add_subcommand("query", "query prices");
	cmd_query->add_option("instruments", instrument_list, "instrument list")->required();
	cmd_query->callback([&]() {
		cmd = CTPCMD_QUERY;
		instruments = parse_instrument_list(instrument_list);
		});

	auto cmd_subscribe = app.add_subcommand("subscribe", "subscribe prices");
	cmd_subscribe->add_option("instruments", instrument_list, "instrument list")->required();
	cmd_subscribe->callback([&]() {
		cmd = CTPCMD_SUBSCRIBE;
		instruments = parse_instrument_list(instrument_list);
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

		tinyxml2::XMLElement* front = element->FirstChildElement("marketfront");
		tinyxml2::XMLElement* address = front->FirstChildElement("addresses")->FirstChildElement("address");
		while (address) {
			std::string Host = address->GetText();
			Hosts.push_back(Host);
			address = address->NextSiblingElement();
		}
		break;
	}

	CThostFtdcMdApi* pMdApi = CThostFtdcMdApi::CreateFtdcMdApi();
	CCTPMdSpiImpl Spi(pMdApi, BrokerID, user, password, cmd, instruments, !no_pretty_print);
	pMdApi->RegisterSpi(&Spi);
	if (Hosts.size() == 0) {
		std::cout << "No host found for channel: " << channel << std::endl;
		return -1;
	}
	for(auto host:Hosts)
		pMdApi->RegisterFront((char*)host.c_str());
	pMdApi->Init();

	getchar();

	return 0;
}
