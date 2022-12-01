#include "FtdcMdApiImpl.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

#define EXCHANGE_SH "SSE"
#define EXCHANGE_SZ "SZSE"
#define EXCHANGE_BSE "BSE"
#define EXCHANGE_HKEX "HKEX"

CThostFtdcMdApi* CThostFtdcMdApi::CreateFtdcMdApi(const char* pszFlowPath, const bool bIsUsingUdp, const bool bIsMulticast)
{
	return new CFtdcMdApiImpl();
}

const char *CThostFtdcMdApi::GetApiVersion()
{
#ifdef V6_6_7
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

CFtdcMdApiImpl::CFtdcMdApiImpl()
{
	memset(&TradingDay, 0, sizeof(TradingDay));
	m_pSpi = NULL;
	m_pUserApi = CTORATstpXMdApi::CreateTstpXMdApi();
	m_pUserApi->RegisterSpi(this);
}

void CFtdcMdApiImpl::Init()
{
	m_pUserApi->Init();
}

int CFtdcMdApiImpl::Join()
{
	return m_pUserApi->Join();
}

void CFtdcMdApiImpl::Release()
{
	m_pSpi = NULL;
	m_pUserApi->Release();
	m_pUserApi = NULL;
	delete this;
}

const char *CFtdcMdApiImpl::GetTradingDay()
{
	return TradingDay;
}

void CFtdcMdApiImpl::RegisterFront(char *pszFrontAddress)
{
	m_pUserApi->RegisterFront(pszFrontAddress); // tcp://ip:port
}

void CFtdcMdApiImpl::RegisterNameServer(char *pszNsAddress)
{
	m_pUserApi->RegisterNameServer(pszNsAddress); // tcp://ip:port
}

void CFtdcMdApiImpl::RegisterSpi(CThostFtdcMdSpi *pSpi)
{
	m_pSpi = pSpi;
}

///用户登录请求
int CFtdcMdApiImpl::ReqUserLogin(CThostFtdcReqUserLoginField *pReqUserLogin, int nRequestID)
{
	CTORATstpReqUserLoginField LoginReq;

	memset(&LoginReq,0x00,sizeof(LoginReq));
	LoginReq.LogInAccountType = TORA_TSTP_LACT_AccountID;
	strncpy(LoginReq.LogInAccount,pReqUserLogin->UserID,sizeof(LoginReq.LogInAccount)-1);
	strncpy(LoginReq.Password,pReqUserLogin->Password,sizeof(LoginReq.Password)-1);
	strncpy(LoginReq.DepartmentID, pReqUserLogin->BrokerID, sizeof(LoginReq.DepartmentID) - 1);
	return m_pUserApi->ReqUserLogin(&LoginReq, nRequestID); 
}

///订阅行情
int CFtdcMdApiImpl::SubscribeMarketData(char* ppInstrumentID[], int nCount)
{
	for (int i = 0; i < nCount; i++) {
		char* InstrumentID[1] = { ppInstrumentID[i] };
		if (memcmp(InstrumentID[0], "60", 2) == 0
			|| memcmp(InstrumentID[0], "11", 2) == 0
			|| memcmp(InstrumentID[0], "50", 2) == 0
			|| memcmp(InstrumentID[0], "51", 2) == 0
			|| memcmp(InstrumentID[0], "56", 2) == 0
			|| memcmp(InstrumentID[0], "58", 2) == 0
			|| memcmp(InstrumentID[0], "60", 2) == 0
			|| memcmp(InstrumentID[0], "68", 2) == 0)
			m_pUserApi->SubscribeMarketData(InstrumentID, 1, TORA_TSTP_EXD_SSE);
		else if (memcmp(InstrumentID[0], "00", 2) == 0
			|| memcmp(InstrumentID[0], "12", 2) == 0
			|| memcmp(InstrumentID[0], "15", 2) == 0
			|| memcmp(InstrumentID[0], "16", 2) == 0
			|| memcmp(InstrumentID[0], "30", 2) == 0)
			m_pUserApi->SubscribeMarketData(InstrumentID, 1, TORA_TSTP_EXD_SZSE);
		else if (memcmp(InstrumentID[0], "43", 2) == 0
			|| memcmp(InstrumentID[0], "82", 2) == 0
			|| memcmp(InstrumentID[0], "83", 2) == 0
			|| memcmp(InstrumentID[0], "87", 2) == 0
			|| memcmp(InstrumentID[0], "88", 2) == 0)
			m_pUserApi->SubscribeMarketData(InstrumentID, 1, TORA_TSTP_EXD_BSE);
		else
			m_pUserApi->SubscribeMarketData(InstrumentID, 1, TORA_TSTP_EXD_HK);
	}
	return 0;
}

///退订行情
int CFtdcMdApiImpl::UnSubscribeMarketData(char* ppInstrumentID[], int nCount)
{
	for (int i = 0; i < nCount; i++) {
		char* InstrumentID[1] = { ppInstrumentID[i] };
		if(memcmp(InstrumentID[0],"60",2)==0
			|| memcmp(InstrumentID[0], "11", 2) == 0
			|| memcmp(InstrumentID[0], "50", 2) == 0
			|| memcmp(InstrumentID[0], "51", 2) == 0
			|| memcmp(InstrumentID[0], "56", 2) == 0
			|| memcmp(InstrumentID[0], "58", 2) == 0
			|| memcmp(InstrumentID[0], "60", 2) == 0
			|| memcmp(InstrumentID[0], "68", 2) == 0)
			m_pUserApi->UnSubscribeMarketData(InstrumentID, 1, TORA_TSTP_EXD_SSE);
		else if(memcmp(InstrumentID[0], "00", 2) == 0
			|| memcmp(InstrumentID[0], "12", 2) == 0
			|| memcmp(InstrumentID[0], "15", 2) == 0
			|| memcmp(InstrumentID[0], "16", 2) == 0
			|| memcmp(InstrumentID[0], "30", 2) == 0)
			m_pUserApi->UnSubscribeMarketData(InstrumentID, 1, TORA_TSTP_EXD_SZSE);
		else if (memcmp(InstrumentID[0], "43", 2) == 0
			|| memcmp(InstrumentID[0], "82", 2) == 0
			|| memcmp(InstrumentID[0], "83", 2) == 0
			|| memcmp(InstrumentID[0], "87", 2) == 0
			|| memcmp(InstrumentID[0], "88", 2) == 0)
			m_pUserApi->UnSubscribeMarketData(InstrumentID, 1, TORA_TSTP_EXD_BSE);
		else
			m_pUserApi->UnSubscribeMarketData(InstrumentID, 1, TORA_TSTP_EXD_HK);
	}
	return 0;
}

///用户退出请求
int CFtdcMdApiImpl::ReqUserLogout(CThostFtdcUserLogoutField *pUserLogout, int nRequestID)
{
	CTORATstpUserLogoutField LogoutReq;

	memset(&LogoutReq,0x00,sizeof(LogoutReq));
	strncpy(LogoutReq.UserID, pUserLogout->UserID,sizeof(LogoutReq.UserID)-1);
	return m_pUserApi->ReqUserLogout(&LogoutReq, nRequestID);
}

void CFtdcMdApiImpl::OnFrontConnected()
{
	if(m_pSpi)
		m_pSpi->OnFrontConnected();
}

void CFtdcMdApiImpl::OnFrontDisconnected(int nReason)
{
	if(m_pSpi)
		m_pSpi->OnFrontDisconnected(nReason);
}


///用户登录应答
void CFtdcMdApiImpl::OnRspUserLogin(CTORATstpRspUserLoginField* pRspUserLogin, CTORATstpRspInfoField* pRspInfo, int nRequestID)
{
	if(m_pSpi)
	{
		CThostFtdcRspInfoField* pThostRspInfo = NULL;
		CThostFtdcRspInfoField ThostRspInfo;

		if (pRspInfo)
		{
			memset(&ThostRspInfo, 0, sizeof(CThostFtdcRspInfoField));
			ThostRspInfo.ErrorID = pRspInfo->ErrorID;
			strncpy(ThostRspInfo.ErrorMsg, pRspInfo->ErrorMsg, sizeof(ThostRspInfo.ErrorMsg) - 1);
			pThostRspInfo = &ThostRspInfo;
		}

		CThostFtdcRspUserLoginField*  pThostRspUserLogin=NULL;
		CThostFtdcRspUserLoginField ThostRspUserLogin;
					
		if(pRspUserLogin)
		{
			strncpy(TradingDay, pRspUserLogin->TradingDay, sizeof(TradingDay) - 1);

			memset(&ThostRspUserLogin,0,sizeof(CThostFtdcRspUserLoginField));
			strncpy(ThostRspUserLogin.TradingDay, pRspUserLogin->TradingDay, sizeof(ThostRspUserLogin.TradingDay)-1);
			strncpy(ThostRspUserLogin.BrokerID,pRspUserLogin->DepartmentID, sizeof(ThostRspUserLogin.BrokerID) - 1);
			strncpy(ThostRspUserLogin.UserID,pRspUserLogin->LogInAccount, sizeof(ThostRspUserLogin.UserID) - 1);
			strncpy(ThostRspUserLogin.LoginTime, pRspUserLogin->LoginTime,sizeof(ThostRspUserLogin.LoginTime)-1);
			snprintf(ThostRspUserLogin.MaxOrderRef, sizeof(ThostRspUserLogin.MaxOrderRef), "%d", pRspUserLogin->MaxOrderRef);
			strncpy(ThostRspUserLogin.SystemName, pRspUserLogin->SystemName, sizeof(ThostRspUserLogin.SystemName) - 1);
			strncpy(ThostRspUserLogin.CZCETime,ThostRspUserLogin.LoginTime, sizeof(ThostRspUserLogin.CZCETime) - 1);
			strncpy(ThostRspUserLogin.SHFETime,ThostRspUserLogin.LoginTime, sizeof(ThostRspUserLogin.SHFETime) - 1);
			strncpy(ThostRspUserLogin.DCETime,ThostRspUserLogin.LoginTime, sizeof(ThostRspUserLogin.DCETime) - 1);
			strncpy(ThostRspUserLogin.FFEXTime,ThostRspUserLogin.LoginTime, sizeof(ThostRspUserLogin.FFEXTime) - 1);
			strncpy(ThostRspUserLogin.INETime,ThostRspUserLogin.LoginTime, sizeof(ThostRspUserLogin.INETime) - 1);
			ThostRspUserLogin.FrontID = pRspUserLogin->FrontID;
			ThostRspUserLogin.SessionID = pRspUserLogin->SessionID;
			pThostRspUserLogin = &ThostRspUserLogin;
		}
	
		if(pRspInfo)
		{
			memset(&ThostRspInfo,0,sizeof(CThostFtdcRspInfoField));	
			ThostRspInfo.ErrorID = pRspInfo->ErrorID;
			strncpy(ThostRspInfo.ErrorMsg,pRspInfo->ErrorMsg,sizeof(ThostRspInfo.ErrorMsg) - 1);
		}
		m_pSpi->OnRspUserLogin(pThostRspUserLogin, &ThostRspInfo, 0, true);
	}
}

///用户退出应答
void CFtdcMdApiImpl::OnRspUserLogout(CTORATstpUserLogoutField* pUserLogout, CTORATstpRspInfoField* pRspInfo, int nRequestID)
{
	if(m_pSpi)
	{
		CThostFtdcUserLogoutField*  pThostRspUserLogout=NULL;
		CThostFtdcUserLogoutField  ThostRspUserLogout;			
		
		if(pUserLogout)
		{
			memset(&ThostRspUserLogout,0,sizeof(CThostFtdcUserLogoutField));
			strncpy(ThostRspUserLogout.UserID, pUserLogout->UserID,sizeof(ThostRspUserLogout.UserID)-1);
			pThostRspUserLogout = &ThostRspUserLogout;
		}

		CThostFtdcRspInfoField*  pThostRspInfo=NULL;
		CThostFtdcRspInfoField  ThostRspInfo;	
					
		if(pRspInfo)
		{
			memset(&ThostRspInfo,0,sizeof(CThostFtdcRspInfoField));
			ThostRspInfo.ErrorID = pRspInfo->ErrorID;
			strncpy(ThostRspInfo.ErrorMsg,pRspInfo->ErrorMsg,sizeof(ThostRspInfo.ErrorMsg)-1);
			pThostRspInfo = &ThostRspInfo;
		}
		m_pSpi->OnRspUserLogout(pThostRspUserLogout, pThostRspInfo, 0, true);
	}
}


///行情订阅应答
void CFtdcMdApiImpl::OnRspSubMarketData(CTORATstpSpecificSecurityField* pSpecificSecurity, CTORATstpRspInfoField* pRspInfo)
{
	if(m_pSpi)
	{

		CThostFtdcRspInfoField*  pThostRspInfo=NULL;
		CThostFtdcRspInfoField  ThostRspInfo;

		if(pRspInfo)
		{
			//CTP正确的订阅不回响应
			if (0 == pRspInfo->ErrorID)
			{
				return;
			}
			memset(&ThostRspInfo,0,sizeof(CThostFtdcRspInfoField));
			ThostRspInfo.ErrorID = pRspInfo->ErrorID;
			strncpy(ThostRspInfo.ErrorMsg,pRspInfo->ErrorMsg,sizeof(ThostRspInfo.ErrorMsg)-1);
			pThostRspInfo = &ThostRspInfo;
		}else{
			return;
		}

		CThostFtdcSpecificInstrumentField*  pThostSpecificInstrument =NULL;
		CThostFtdcSpecificInstrumentField  ThostSpecificInstrument;
		if(pSpecificSecurity)
		{		
			memset(&ThostSpecificInstrument,0,sizeof(ThostSpecificInstrument));
			strncpy(ThostSpecificInstrument.InstrumentID, pSpecificSecurity->SecurityID,sizeof(ThostSpecificInstrument.InstrumentID)-1);
			pThostSpecificInstrument = &ThostSpecificInstrument;
		}

		m_pSpi->OnRspSubMarketData(pThostSpecificInstrument, pThostRspInfo, 0, true);
	}
}

///行情退订应答
void CFtdcMdApiImpl::OnRspUnSubMarketData(CTORATstpSpecificSecurityField* pSpecificSecurity, CTORATstpRspInfoField* pRspInfo)
{
	if (m_pSpi)
	{

		CThostFtdcRspInfoField* pThostRspInfo = NULL;
		CThostFtdcRspInfoField  ThostRspInfo;

		if (pRspInfo)
		{
			//CTP正确的订阅不回响应
			if (0 == pRspInfo->ErrorID)
			{
				return;
			}
			memset(&ThostRspInfo, 0, sizeof(CThostFtdcRspInfoField));
			ThostRspInfo.ErrorID = pRspInfo->ErrorID;
			strncpy(ThostRspInfo.ErrorMsg, pRspInfo->ErrorMsg, sizeof(ThostRspInfo.ErrorMsg) - 1);
			pThostRspInfo = &ThostRspInfo;
		}
		else {
			return;
		}

		CThostFtdcSpecificInstrumentField* pThostSpecificInstrument = NULL;
		CThostFtdcSpecificInstrumentField  ThostSpecificInstrument;
		if (pSpecificSecurity)
		{
			memset(&ThostSpecificInstrument, 0, sizeof(ThostSpecificInstrument));
			strncpy(ThostSpecificInstrument.InstrumentID, pSpecificSecurity->SecurityID, sizeof(ThostSpecificInstrument.InstrumentID) - 1);
			pThostSpecificInstrument = &ThostSpecificInstrument;
		}

		m_pSpi->OnRspUnSubMarketData(pThostSpecificInstrument, pThostRspInfo, 0, true);
	}
}

///行情退订应答
void CFtdcMdApiImpl::OnRtnMarketData(CTORATstpMarketDataField* pDepthMarketData)
{
	if (m_pSpi)
	{
		CThostFtdcDepthMarketDataField  ThostDepthMarketData;
		memset(&ThostDepthMarketData, 0, sizeof(ThostDepthMarketData));
		strncpy(ThostDepthMarketData.InstrumentID, pDepthMarketData->SecurityID, sizeof(ThostDepthMarketData.InstrumentID) - 1);
		if (pDepthMarketData->ExchangeID == TORA_TSTP_EXD_SSE)
			strncpy(ThostDepthMarketData.ExchangeID, EXCHANGE_SH, sizeof(ThostDepthMarketData.ExchangeID) - 1);
		else if (pDepthMarketData->ExchangeID == TORA_TSTP_EXD_SZSE)
			strncpy(ThostDepthMarketData.ExchangeID, EXCHANGE_SZ, sizeof(ThostDepthMarketData.ExchangeID) - 1);
		else if (pDepthMarketData->ExchangeID == TORA_TSTP_EXD_BSE)
			strncpy(ThostDepthMarketData.ExchangeID, EXCHANGE_BSE, sizeof(ThostDepthMarketData.ExchangeID) - 1);
		else if (pDepthMarketData->ExchangeID == TORA_TSTP_EXD_HK)
			strncpy(ThostDepthMarketData.ExchangeID, EXCHANGE_HKEX, sizeof(ThostDepthMarketData.ExchangeID) - 1);
		ThostDepthMarketData.LastPrice = pDepthMarketData->LastPrice;
		ThostDepthMarketData.Volume = pDepthMarketData->Volume;
		ThostDepthMarketData.Turnover = pDepthMarketData->Turnover;
		ThostDepthMarketData.OpenPrice = pDepthMarketData->OpenPrice;
		ThostDepthMarketData.HighestPrice = pDepthMarketData->HighestPrice;
		ThostDepthMarketData.LowestPrice = pDepthMarketData->LowestPrice;
		ThostDepthMarketData.UpperLimitPrice = pDepthMarketData->UpperLimitPrice;
		ThostDepthMarketData.LowerLimitPrice = pDepthMarketData->LowerLimitPrice;
		ThostDepthMarketData.OpenInterest = pDepthMarketData->OpenInterest;
		ThostDepthMarketData.PreClosePrice = pDepthMarketData->PreClosePrice;
		ThostDepthMarketData.SettlementPrice = 0;
		ThostDepthMarketData.PreSettlementPrice = 0;
		ThostDepthMarketData.PreOpenInterest = pDepthMarketData->OpenInterest;
		ThostDepthMarketData.ClosePrice = pDepthMarketData->ClosePrice;
		ThostDepthMarketData.AveragePrice = 0;
		ThostDepthMarketData.BidPrice1 = pDepthMarketData->BidPrice1;
		ThostDepthMarketData.BidVolume1 = pDepthMarketData->BidVolume1;
		ThostDepthMarketData.AskPrice1 = pDepthMarketData->AskPrice1;
		ThostDepthMarketData.AskVolume1 = pDepthMarketData->AskVolume1;
		strncpy(ThostDepthMarketData.ActionDay, pDepthMarketData->TradingDay, sizeof(ThostDepthMarketData.ActionDay) - 1);
		strncpy(ThostDepthMarketData.UpdateTime, pDepthMarketData->UpdateTime, sizeof(ThostDepthMarketData.UpdateTime)-1);
		strncpy(ThostDepthMarketData.TradingDay, pDepthMarketData->TradingDay, sizeof(ThostDepthMarketData.TradingDay) - 1);
		ThostDepthMarketData.BidPrice2 = pDepthMarketData->BidPrice2;
		ThostDepthMarketData.BidVolume2 = pDepthMarketData->BidVolume2;
		ThostDepthMarketData.AskPrice2 = pDepthMarketData->AskPrice2;
		ThostDepthMarketData.AskVolume2 = pDepthMarketData->AskVolume2;
		ThostDepthMarketData.BidPrice3 = pDepthMarketData->BidPrice3;
		ThostDepthMarketData.BidVolume3 = pDepthMarketData->BidVolume3;
		ThostDepthMarketData.AskPrice3 = pDepthMarketData->AskPrice3;
		ThostDepthMarketData.AskVolume3 = pDepthMarketData->AskVolume3;
		ThostDepthMarketData.BidPrice4 = pDepthMarketData->BidPrice4;
		ThostDepthMarketData.BidVolume4 = pDepthMarketData->BidVolume4;
		ThostDepthMarketData.AskPrice4 = pDepthMarketData->AskPrice4;
		ThostDepthMarketData.AskVolume4 = pDepthMarketData->AskVolume4;
		ThostDepthMarketData.BidPrice5 = pDepthMarketData->BidPrice5;
		ThostDepthMarketData.BidVolume5 = pDepthMarketData->BidVolume5;
		ThostDepthMarketData.AskPrice5 = pDepthMarketData->AskPrice5;
		ThostDepthMarketData.AskVolume5 = pDepthMarketData->AskVolume5;
		m_pSpi->OnRtnDepthMarketData(&ThostDepthMarketData);
	}
}
