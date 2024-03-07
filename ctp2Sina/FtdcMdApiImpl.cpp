#include "FtdcMdApiImpl.h"
#include <boost/algorithm/string.hpp>

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
    url_ = "hq.sinajs.cn";
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
        std::string InstrumentID = ppInstrumentID[i];
        boost::algorithm::to_lower(InstrumentID);
        _mInstruments[InstrumentID] = 0;
	}
	return 0;
}

///退订行情
int CFtdcMdApiImpl::UnSubscribeMarketData(char* ppInstrumentID[], int nCount)
{
	for (int i = 0; i < nCount; i++) {
        std::string InstrumentID = ppInstrumentID[i];
        boost::algorithm::to_lower(InstrumentID);
        auto iter = _mInstruments.find(InstrumentID);
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
            boost::split(vFields, *iter, boost::is_any_of(","));
            if (vFields.size() < 10) // 至少要有10个字段
                return;

            // 交易所
            // 合约
            if (vFields[0].compare(0, 2, "hk") == 0) {
                // 港股
                strncpy(DepthMarketData.ExchangeID, EXCHANGE_HKEX, sizeof(DepthMarketData.ExchangeID) - 1);
                strncpy(DepthMarketData.InstrumentID, vFields[0].c_str() + 2, sizeof(DepthMarketData.InstrumentID) - 1);
                strncpy(DepthMarketData.ExchangeInstID, DepthMarketData.InstrumentID, sizeof(DepthMarketData.ExchangeInstID) - 1);

                // 最新价
                DepthMarketData.LastPrice = atof(vFields[7].c_str());

                // 开
                DepthMarketData.OpenPrice = atof(vFields[3].c_str());

                // 高
                DepthMarketData.HighestPrice = atof(vFields[5].c_str());

                // 低
                DepthMarketData.LowestPrice = atof(vFields[6].c_str());

                // 昨收
                DepthMarketData.PreClosePrice = atof(vFields[4].c_str());

                // 成交量
                DepthMarketData.Volume = atol(vFields[13].c_str());

                // 成交额
                DepthMarketData.Turnover = atof(vFields[12].c_str());

                // 买一
                DepthMarketData.BidPrice1 = atof(vFields[10].c_str());

                // 卖一
                DepthMarketData.AskPrice1 = atof(vFields[11].c_str());

                // 时间
                sprintf(DepthMarketData.ActionDay, "%4.4s%2.2s%2.2s", vFields[18].c_str(), vFields[18].c_str() + 5, vFields[18].c_str() + 8);
                sprintf(DepthMarketData.UpdateTime, "%s:00", vFields[19].c_str());
                sprintf(DepthMarketData.TradingDay, "%4.4s%2.2s%2.2s", vFields[18].c_str(), vFields[18].c_str() + 5, vFields[18].c_str() + 8);
            }
            else if (vFields[0].compare(0, 3, "gb_") == 0) {
                // 美股
                boost::algorithm::to_upper(vFields[0]); // 合约号改为大写美股

                strncpy(DepthMarketData.ExchangeID, EXCHANGE_NASD, sizeof(DepthMarketData.ExchangeID) - 1);
                strncpy(DepthMarketData.InstrumentID, vFields[0].c_str()+3, sizeof(DepthMarketData.InstrumentID) - 1);
                strncpy(DepthMarketData.ExchangeInstID, DepthMarketData.InstrumentID, sizeof(DepthMarketData.ExchangeInstID) - 1);

                // 最新价
                DepthMarketData.LastPrice = atof(vFields[2].c_str());

                // 开
                DepthMarketData.OpenPrice = atof(vFields[6].c_str());

                // 高
                DepthMarketData.HighestPrice = atof(vFields[7].c_str());

                // 低
                DepthMarketData.LowestPrice = atof(vFields[8].c_str());

                // 昨收
                DepthMarketData.PreClosePrice = atof(vFields[27].c_str());

                // 成交量
                DepthMarketData.Volume = atol(vFields[11].c_str());

                // 成交额
                DepthMarketData.Turnover = atof(vFields[31].c_str());

                // 时间
                sprintf(DepthMarketData.ActionDay, "%4.4s%2.2s%2.2s", vFields[4].c_str(), vFields[4].c_str() + 5, vFields[4].c_str() + 8);
                strncpy(DepthMarketData.UpdateTime, vFields[4].c_str()+11, sizeof(DepthMarketData.UpdateTime)-1);
                sprintf(DepthMarketData.TradingDay, "%4.4s%2.2s%2.2s", vFields[4].c_str(), vFields[4].c_str() + 5, vFields[4].c_str() + 8);
            }
            else if(vFields[0].compare(0, 3, "nf_") == 0) {
                // 期货
                strncpy(DepthMarketData.ExchangeID, "", sizeof(DepthMarketData.ExchangeID) - 1);
                strncpy(DepthMarketData.InstrumentID, vFields[0].c_str()+3, sizeof(DepthMarketData.InstrumentID) - 1);
                strncpy(DepthMarketData.ExchangeInstID, DepthMarketData.InstrumentID, sizeof(DepthMarketData.ExchangeInstID) - 1);

                // 最新价
                DepthMarketData.LastPrice = atof(vFields[9].c_str());

                // 开
                DepthMarketData.OpenPrice = atof(vFields[3].c_str());

                // 高
                DepthMarketData.HighestPrice = atof(vFields[4].c_str());

                // 低
                DepthMarketData.LowestPrice = atof(vFields[5].c_str());

                // 昨收
                DepthMarketData.PreClosePrice = atof(vFields[11].c_str());

                // 成交量
                DepthMarketData.Volume = atol(vFields[15].c_str());

                // 买一
                DepthMarketData.BidPrice1 = atof(vFields[7].c_str());
                DepthMarketData.BidVolume1 = atol(vFields[12].c_str());

                // 卖一
                DepthMarketData.AskPrice1 = atof(vFields[8].c_str());
                DepthMarketData.AskVolume1 = atol(vFields[13].c_str());
                sprintf(DepthMarketData.ActionDay, "%4.4s%2.2s%2.2s", vFields[18].c_str(), vFields[18].c_str() + 5, vFields[18].c_str() + 8);
                // strncpy(DepthMarketData.UpdateTime, vFields[18].c_str()+11, sizeof(DepthMarketData.UpdateTime)-1);
                sprintf(DepthMarketData.TradingDay, "%4.4s%2.2s%2.2s", vFields[18].c_str(), vFields[18].c_str() + 5, vFields[18].c_str() + 8);
            }
            else {
                // A股
                if (vFields[0].compare(0, 2, "sh") == 0) {
                    strncpy(DepthMarketData.ExchangeID, EXCHANGE_SSE, sizeof(DepthMarketData.ExchangeID) - 1);
                }
                else if (vFields[0].compare(0, 2, "sz") == 0) {
                    strncpy(DepthMarketData.ExchangeID, EXCHANGE_SZSE, sizeof(DepthMarketData.ExchangeID) - 1);
                }
                else if (vFields[0].compare(0, 2, "bj") == 0) {
                    strncpy(DepthMarketData.ExchangeID, EXCHANGE_BSE, sizeof(DepthMarketData.ExchangeID) - 1);
                }
                strncpy(DepthMarketData.InstrumentID, vFields[0].c_str() + 2, sizeof(DepthMarketData.InstrumentID) - 1);
                strncpy(DepthMarketData.ExchangeInstID, DepthMarketData.InstrumentID, sizeof(DepthMarketData.ExchangeInstID) - 1);

                // 最新价
                DepthMarketData.LastPrice = atof(vFields[4].c_str());

                // 开
                DepthMarketData.OpenPrice = atof(vFields[2].c_str());

                // 高
                DepthMarketData.HighestPrice = atof(vFields[5].c_str());

                // 低
                DepthMarketData.LowestPrice = atof(vFields[6].c_str());

                // 昨收
                DepthMarketData.PreClosePrice = atof(vFields[3].c_str());

                // 成交量
                DepthMarketData.Volume = atol(vFields[9].c_str());

                // 成交额
                DepthMarketData.Turnover = atof(vFields[10].c_str());

                // 买一
                DepthMarketData.BidPrice1 = atof(vFields[12].c_str());
                DepthMarketData.BidVolume1 = atol(vFields[11].c_str());

                // 买二
                DepthMarketData.BidPrice2 = atof(vFields[14].c_str());
                DepthMarketData.BidVolume2 = atol(vFields[13].c_str());

                // 买三
                DepthMarketData.BidPrice3 = atof(vFields[16].c_str());
                DepthMarketData.BidVolume3 = atol(vFields[15].c_str());

                // 买四
                DepthMarketData.BidPrice4 = atof(vFields[18].c_str());
                DepthMarketData.BidVolume4 = atol(vFields[17].c_str());

                // 买五
                DepthMarketData.BidPrice5 = atof(vFields[20].c_str());
                DepthMarketData.BidVolume5 = atol(vFields[19].c_str());

                // 卖一
                DepthMarketData.AskPrice1 = atof(vFields[22].c_str());
                DepthMarketData.AskVolume1 = atol(vFields[21].c_str());

                // 卖二
                DepthMarketData.AskPrice2 = atof(vFields[24].c_str());
                DepthMarketData.AskVolume2 = atol(vFields[23].c_str());

                // 卖三
                DepthMarketData.AskPrice3 = atof(vFields[26].c_str());
                DepthMarketData.AskVolume3 = atol(vFields[25].c_str());

                // 卖四
                DepthMarketData.AskPrice4 = atof(vFields[28].c_str());
                DepthMarketData.AskVolume4 = atol(vFields[27].c_str());

                // 卖五
                DepthMarketData.AskPrice5 = atof(vFields[30].c_str());
                DepthMarketData.AskVolume5 = atol(vFields[29].c_str());

                // 时间
                sprintf(DepthMarketData.ActionDay, "%4.4s%2.2s%2.2s", vFields[31].c_str(), vFields[31].c_str() + 5, vFields[31].c_str() + 8);
                strncpy(DepthMarketData.UpdateTime, vFields[32].c_str(), sizeof(DepthMarketData.UpdateTime) - 1);
                sprintf(DepthMarketData.TradingDay, "%4.4s%2.2s%2.2s", vFields[31].c_str(), vFields[31].c_str() + 5, vFields[31].c_str() + 8);
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
    std::string prefix = "/list=";
    std::string querystr = prefix; // "/list=sh600000,sz000001,bj833266,hk00700,gb_aapl,ag2404"
    
    for (auto iter = _mInstruments.begin(); iter != _mInstruments.end(); iter++) {
        bool need_upper = false;
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
        // first char is a-z or A-Z last is a digit
        else if(isalpha(*iter->first.c_str()) && isdigit(*(iter->first.c_str()+2))){
            querystr += "nf_";
            need_upper = true;
        }
        else 
            querystr += "gb_";
        std::string may_upper = iter->first;
        boost::algorithm::to_upper(may_upper);
        querystr += need_upper? may_upper : iter->first;

    }

    query(querystr.c_str());

    m_snap_timer.expires_from_now(boost::posix_time::milliseconds(snaptime * 1000));
    m_snap_timer.async_wait(boost::bind(&CFtdcMdApiImpl::OnSnapTime, this, boost::asio::placeholders::error));
}