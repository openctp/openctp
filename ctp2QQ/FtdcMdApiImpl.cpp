#include "FtdcMdApiImpl.h"

#define EXCHANGE_SSE "SSE"
#define EXCHANGE_SZSE "SZSE"
#define EXCHANGE_BSE "BSE"
#define EXCHANGE_HKEX "HKEX"
#define EXCHANGE_NASD "NASD"

#define snaptime  3 // 秒


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


CFtdcMdApiImpl::CFtdcMdApiImpl():resolver_(net::make_strand(ioc_))
, stream_(net::make_strand(ioc_))
, m_snap_timer(ioc_)
{
    url_ = "qt.gtimg.cn";
    port_ = "80";
	memset(&TradingDay, 0, sizeof(TradingDay));
	m_pSpi = NULL;
    m_snap_timer.expires_from_now(boost::posix_time::milliseconds(snaptime * 1000));
    m_snap_timer.async_wait(boost::bind(&CFtdcMdApiImpl::OnSnapTime, this, boost::asio::placeholders::error));
    _pthread = NULL;
}

void CFtdcMdApiImpl::Init()
{
    _pthread = new boost::thread(boost::bind(&boost::asio::io_service::run, boost::ref(ioc_)));
    if (m_pSpi)
        ioc_.post(boost::bind(&CThostFtdcMdSpi::OnFrontConnected, m_pSpi));
}

int CFtdcMdApiImpl::Join()
{
    _pthread->join();

	return 0;
}

void CFtdcMdApiImpl::Release()
{
	m_pSpi = NULL;
    ioc_.stop();
    _pthread = NULL;
	delete this;
}

const char *CFtdcMdApiImpl::GetTradingDay()
{
	return TradingDay;
}

void CFtdcMdApiImpl::RegisterFront(char *pszFrontAddress)
{
}

void CFtdcMdApiImpl::RegisterNameServer(char *pszNsAddress)
{
}

void CFtdcMdApiImpl::RegisterSpi(CThostFtdcMdSpi *pSpi)
{
	m_pSpi = pSpi;
}

///用户登录请求
int CFtdcMdApiImpl::ReqUserLogin(CThostFtdcReqUserLoginField *pReqUserLogin, int nRequestID)
{
	memset(&ThostRspUserLogin,0x00,sizeof(ThostRspUserLogin));
	strncpy(ThostRspUserLogin.UserID,pReqUserLogin->UserID,sizeof(ThostRspUserLogin.UserID)-1);
	memset(&ThostRspInfo, 0x00, sizeof(ThostRspInfo));
    ioc_.post(boost::bind(&CThostFtdcMdSpi::OnRspUserLogin, m_pSpi, &ThostRspUserLogin, &ThostRspInfo, nRequestID, true));

	return 0; 
}

///订阅行情
int CFtdcMdApiImpl::SubscribeMarketData(char* ppInstrumentID[], int nCount)
{
	for (int i = 0; i < nCount; i++) {
        _mInstruments[ppInstrumentID[i]] = 0;
	}
	return 0;
}

///退订行情
int CFtdcMdApiImpl::UnSubscribeMarketData(char* ppInstrumentID[], int nCount)
{
	for (int i = 0; i < nCount; i++) {
        auto iter = _mInstruments.find(ppInstrumentID[i]);
        if (iter == _mInstruments.end())
            continue;
        _mInstruments.erase(iter);

	}
	return 0;
}

///用户退出请求
int CFtdcMdApiImpl::ReqUserLogout(CThostFtdcUserLogoutField *pUserLogout, int nRequestID)
{
	memset(&ThostUserLogout, 0x00, sizeof(ThostUserLogout));
	strncpy(ThostUserLogout.UserID, pUserLogout->UserID, sizeof(ThostUserLogout.UserID) - 1);
	memset(&ThostRspInfo, 0x00, sizeof(ThostRspInfo));
    ioc_.post(boost::bind(&CThostFtdcMdSpi::OnRspUserLogout, m_pSpi, &ThostUserLogout, &ThostRspInfo, nRequestID, true));
	return 0;
}

void CFtdcMdApiImpl::HandleMarketData(std::vector<std::string>& data)
{
    if (m_pSpi)
    {
        CThostFtdcDepthMarketDataField DepthMarketData;
        for (auto iter = data.begin(); iter != data.end(); iter++)
        {
            memset(&DepthMarketData, 0x00, sizeof(DepthMarketData));
            std::vector<std::string> vFields;
            boost::split(vFields, *iter, boost::is_any_of("~"));
            if (vFields.size() < 50) // 至少要有50个字段
                return;

            // 交易所
            if (vFields[0] == "1") {
                strncpy(DepthMarketData.ExchangeID, EXCHANGE_SSE, sizeof(DepthMarketData.ExchangeID) - 1);
            }
            else if (vFields[0] == "51") {
                strncpy(DepthMarketData.ExchangeID, EXCHANGE_SZSE, sizeof(DepthMarketData.ExchangeID) - 1);
            }
            else if (vFields[0] == "62") {
                strncpy(DepthMarketData.ExchangeID, EXCHANGE_BSE, sizeof(DepthMarketData.ExchangeID) - 1);
            }
            else if (vFields[0] == "100") {
                strncpy(DepthMarketData.ExchangeID, EXCHANGE_HKEX, sizeof(DepthMarketData.ExchangeID) - 1);
            }
            else if (vFields[0] == "200") {
                strncpy(DepthMarketData.ExchangeID, EXCHANGE_NASD, sizeof(DepthMarketData.ExchangeID) - 1);
            }

            // 合约
            strncpy(DepthMarketData.InstrumentID, vFields[2].c_str(), sizeof(DepthMarketData.InstrumentID) - 1);
            char* p = strchr(DepthMarketData.InstrumentID, '.');
            if (p)
                *p = '\0';
            strncpy(DepthMarketData.ExchangeInstID, DepthMarketData.InstrumentID, sizeof(DepthMarketData.ExchangeInstID) - 1);

            // 最新价
            DepthMarketData.LastPrice = atof(vFields[3].c_str());

            // 开
            DepthMarketData.OpenPrice = atof(vFields[5].c_str());

            // 高
            DepthMarketData.HighestPrice = atof(vFields[33].c_str());

            // 低
            DepthMarketData.LowestPrice = atof(vFields[34].c_str());

            // 昨收
            DepthMarketData.PreClosePrice = atof(vFields[4].c_str());

            // 成交量
            DepthMarketData.Volume = atol(vFields[6].c_str());

            // 成交额
            DepthMarketData.Turnover = atof(vFields[37].c_str());

            // 买一
            DepthMarketData.BidPrice1 = atof(vFields[9].c_str());
            DepthMarketData.BidVolume1 = atol(vFields[10].c_str());

            // 买二
            DepthMarketData.BidPrice2 = atof(vFields[11].c_str());
            DepthMarketData.BidVolume2 = atol(vFields[12].c_str());

            // 买三
            DepthMarketData.BidPrice3 = atof(vFields[13].c_str());
            DepthMarketData.BidVolume3 = atol(vFields[14].c_str());

            // 买四
            DepthMarketData.BidPrice4 = atof(vFields[15].c_str());
            DepthMarketData.BidVolume4 = atol(vFields[16].c_str());

            // 买五
            DepthMarketData.BidPrice5 = atof(vFields[17].c_str());
            DepthMarketData.BidVolume5 = atol(vFields[18].c_str());

            // 卖一
            DepthMarketData.AskPrice1 = atof(vFields[19].c_str());
            DepthMarketData.AskVolume1 = atol(vFields[20].c_str());

            // 卖二
            DepthMarketData.AskPrice2 = atof(vFields[21].c_str());
            DepthMarketData.AskVolume2 = atol(vFields[22].c_str());

            // 卖三
            DepthMarketData.AskPrice3 = atof(vFields[23].c_str());
            DepthMarketData.AskVolume3 = atol(vFields[24].c_str());

            // 卖四
            DepthMarketData.AskPrice4 = atof(vFields[25].c_str());
            DepthMarketData.AskVolume4 = atol(vFields[26].c_str());

            // 卖五
            DepthMarketData.AskPrice5 = atof(vFields[27].c_str());
            DepthMarketData.AskVolume5 = atol(vFields[28].c_str());

            if (vFields[0] == "100" || vFields[0] == "200") {
                // 港美股的字段不一样
                // 涨停
                DepthMarketData.UpperLimitPrice = atof(vFields[48].c_str());

                // 跌停
                DepthMarketData.LowerLimitPrice = atof(vFields[49].c_str());

                // 时间
                sprintf(DepthMarketData.ActionDay, "%4.4s%2.2s%2.2s", vFields[30].c_str(), vFields[30].c_str() + 5, vFields[30].c_str() + 8);
                sprintf(DepthMarketData.UpdateTime, "%2.2s:%2.2s:%2.2s", vFields[30].c_str() + 11, vFields[30].c_str() + 14, vFields[30].c_str() + 17);
                sprintf(DepthMarketData.TradingDay, "%4.4s%2.2s%2.2s", vFields[30].c_str(), vFields[30].c_str() + 5, vFields[30].c_str() + 8);
            }
            else {
                // 涨停
                DepthMarketData.UpperLimitPrice = atof(vFields[47].c_str());

                // 跌停
                DepthMarketData.LowerLimitPrice = atof(vFields[48].c_str());

                // 时间
                sprintf(DepthMarketData.ActionDay, "%4.4s%2.2s%2.2s", vFields[30].c_str(), vFields[30].c_str() + 4, vFields[30].c_str() + 6);
                sprintf(DepthMarketData.UpdateTime, "%2.2s:%2.2s:%2.2s", vFields[30].c_str() + 8, vFields[30].c_str() + 10, vFields[30].c_str() + 12);
                sprintf(DepthMarketData.TradingDay, "%4.4s%2.2s%2.2s", vFields[30].c_str(), vFields[30].c_str() + 4, vFields[30].c_str() + 6);

                // 除科创板外数量要乘以100
                if (strncmp(DepthMarketData.InstrumentID, "688", 3) != 0) {
                    DepthMarketData.Volume *= 100;
                    DepthMarketData.BidVolume1 *= 100;
                    DepthMarketData.BidVolume2 *= 100;
                    DepthMarketData.BidVolume3 *= 100;
                    DepthMarketData.BidVolume4 *= 100;
                    DepthMarketData.BidVolume5 *= 100;
                    DepthMarketData.AskVolume1 *= 100;
                    DepthMarketData.AskVolume2 *= 100;
                    DepthMarketData.AskVolume3 *= 100;
                    DepthMarketData.AskVolume4 *= 100;
                    DepthMarketData.AskVolume5 *= 100;
                }
            }
            m_pSpi->OnRtnDepthMarketData(&DepthMarketData);
        }
    }
}

void CFtdcMdApiImpl::OnSnapTime(const boost::system::error_code& error)
{
    if (error) {
        if (error == boost::asio::error::operation_aborted) {
            return;
        }
    }

    // make url
    std::string prefix = "/q=";
    std::string querystr = prefix; // "/q=sh600000,sz000001,hk00700,usAAPL"
    for (auto iter = _mInstruments.begin(); iter != _mInstruments.end(); iter++) {
        if (querystr != prefix)
            querystr += ",";
        if(iter->first.length()==5 && isdigit(*iter->first.c_str()))
            querystr += "hk";
        else if (memcmp(iter->first.c_str(), "60", 2) == 0
        	|| memcmp(iter->first.c_str(), "11", 2) == 0
        	|| memcmp(iter->first.c_str(), "50", 2) == 0
        	|| memcmp(iter->first.c_str(), "51", 2) == 0
        	|| memcmp(iter->first.c_str(), "56", 2) == 0
        	|| memcmp(iter->first.c_str(), "58", 2) == 0
        	|| memcmp(iter->first.c_str(), "60", 2) == 0
        	|| memcmp(iter->first.c_str(), "68", 2) == 0)
            querystr += "sh";
        else if (memcmp(iter->first.c_str(), "00", 2) == 0
        	|| memcmp(iter->first.c_str(), "12", 2) == 0
        	|| memcmp(iter->first.c_str(), "15", 2) == 0
        	|| memcmp(iter->first.c_str(), "16", 2) == 0
        	|| memcmp(iter->first.c_str(), "30", 2) == 0)
            querystr += "sz";
        else if(memcmp(iter->first.c_str(), "43", 2) == 0
            || memcmp(iter->first.c_str(), "82", 2) == 0
            || memcmp(iter->first.c_str(), "83", 2) == 0
            || memcmp(iter->first.c_str(), "87", 2) == 0
            || memcmp(iter->first.c_str(), "88", 2) == 0)
            querystr += "bj";
        else
            querystr += "us";
        querystr += iter->first;
    }
    query(querystr.c_str());

    m_snap_timer.expires_from_now(boost::posix_time::milliseconds(snaptime * 1000));
    m_snap_timer.async_wait(boost::bind(&CFtdcMdApiImpl::OnSnapTime, this, boost::asio::placeholders::error));
}
