#include "FtdcMdApiImpl.h"

#define EXCHANGE_SSE "SSE"
#define EXCHANGE_SZSE "SZSE"
#define EXCHANGE_BSE "BSE"
#define EXCHANGE_HKEX "HKEX"
#define EXCHANGE_NASD "NASD"


CThostFtdcMdApi* CThostFtdcMdApi::CreateFtdcMdApi(const char* pszFlowPath, const bool bIsUsingUdp, const bool bIsMulticast)
{
	return new CFtdcMdApiImpl();
}

const char *CThostFtdcMdApi::GetApiVersion()
{
#ifdef V6_7_2
    return "openctp-qq v6.7.2";
#elif V6_7_1
    return "openctp-qq v6.7.1";
#elif V6_7_0
    return "openctp-qq v6.7.0";
#elif V6_6_9
    return "openctp-qq v6.6.9";
#elif V6_6_7
    return "openctp-qq v6.6.7";
#elif V6_6_5_P1
    return "openctp-qq v6.6.5_P1";
#elif V6_6_1_P1
    return "openctp-qq v6.6.1_P1";
#elif V6_5_1
    return "openctp-qq v6.5.1";
#elif V6_3_19
    return "openctp-qq v6.3.19_P1";
#else
    return "openctp-qq v6.3.15";
#endif
}


CFtdcMdApiImpl::CFtdcMdApiImpl():resolver_(net::make_strand(ioc_))
, stream_(net::make_strand(ioc_))
, m_snap_timer(ioc_)
{
    m_snaptime = 100; // ms
    m_cursor = 0;
    m_window = 100;
    url_ = "qt.gtimg.cn";
    port_ = "80";
	memset(&TradingDay, 0, sizeof(TradingDay));
	m_pSpi = NULL;
    m_snap_timer.expires_from_now(boost::posix_time::milliseconds(m_snaptime));
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

///�û���¼����
int CFtdcMdApiImpl::ReqUserLogin(CThostFtdcReqUserLoginField *pReqUserLogin, int nRequestID)
{
	memset(&ThostRspUserLogin,0x00,sizeof(ThostRspUserLogin));
	strncpy(ThostRspUserLogin.UserID,pReqUserLogin->UserID,sizeof(ThostRspUserLogin.UserID)-1);
	memset(&ThostRspInfo, 0x00, sizeof(ThostRspInfo));
    ioc_.post(boost::bind(&CThostFtdcMdSpi::OnRspUserLogin, m_pSpi, &ThostRspUserLogin, &ThostRspInfo, nRequestID, true));

	return 0; 
}

///��������
int CFtdcMdApiImpl::SubscribeMarketData(char* ppInstrumentID[], int nCount)
{
    std::vector<std::string> vInstruments;
	for (int i = 0; i < nCount; i++) {
        vInstruments.push_back(ppInstrumentID[i]);
	}
    ioc_.post(boost::bind(&CFtdcMdApiImpl::SubscribeMarketData, this, vInstruments));
    return 0;
}

void CFtdcMdApiImpl::SubscribeMarketData(const std::vector<std::string>& vInstruments)
{
    for (auto& iter: vInstruments) {
        if (m_mInstruments.find(iter) != m_mInstruments.end())
            continue;
        m_vInstruments.push_back(iter);
        m_mInstruments[iter] = 0;
    }
}

///�˶�����
int CFtdcMdApiImpl::UnSubscribeMarketData(char* ppInstrumentID[], int nCount)
{
    std::vector<std::string> vInstruments;
    for (int i = 0; i < nCount; i++) {
        vInstruments.push_back(ppInstrumentID[i]);
    }
    ioc_.post(boost::bind(&CFtdcMdApiImpl::UnSubscribeMarketData, this, vInstruments));
    return 0;
}

void CFtdcMdApiImpl::UnSubscribeMarketData(const std::vector<std::string>& vInstruments)
{
    for (auto& iter : vInstruments) {
        auto iterInstrument = m_mInstruments.find(iter);
        if (iterInstrument == m_mInstruments.end())
            continue;

        for (auto iter2 = m_vInstruments.begin(); iter2 != m_vInstruments.end(); iter2++) {
            if (*iter2 == iter) {
                m_vInstruments.erase(iter2);
                break;
            }
        }

        m_mInstruments.erase(iterInstrument);
    }
}


///�û��˳�����
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
            if (vFields.size() < 50) // ����Ҫ��50���ֶ�
                return;

            // ������
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

            // ��Լ
            strncpy(DepthMarketData.InstrumentID, vFields[2].c_str(), sizeof(DepthMarketData.InstrumentID) - 1);
            char* p = strchr(DepthMarketData.InstrumentID, '.');
            if (p)
                *p = '\0';
            strncpy(DepthMarketData.ExchangeInstID, DepthMarketData.InstrumentID, sizeof(DepthMarketData.ExchangeInstID) - 1);

            // ���¼�
            DepthMarketData.LastPrice = atof(vFields[3].c_str());

            // ��
            DepthMarketData.OpenPrice = atof(vFields[5].c_str());

            // ��
            DepthMarketData.HighestPrice = atof(vFields[33].c_str());

            // ��
            DepthMarketData.LowestPrice = atof(vFields[34].c_str());

            // ����
            DepthMarketData.PreClosePrice = atof(vFields[4].c_str());

            // �ɽ���
            DepthMarketData.Volume = atol(vFields[6].c_str());

            // �ɽ���
            DepthMarketData.Turnover = atof(vFields[37].c_str());

            // ��һ
            DepthMarketData.BidPrice1 = atof(vFields[9].c_str());
            DepthMarketData.BidVolume1 = atol(vFields[10].c_str());

            // ���
            DepthMarketData.BidPrice2 = atof(vFields[11].c_str());
            DepthMarketData.BidVolume2 = atol(vFields[12].c_str());

            // ����
            DepthMarketData.BidPrice3 = atof(vFields[13].c_str());
            DepthMarketData.BidVolume3 = atol(vFields[14].c_str());

            // ����
            DepthMarketData.BidPrice4 = atof(vFields[15].c_str());
            DepthMarketData.BidVolume4 = atol(vFields[16].c_str());

            // ����
            DepthMarketData.BidPrice5 = atof(vFields[17].c_str());
            DepthMarketData.BidVolume5 = atol(vFields[18].c_str());

            // ��һ
            DepthMarketData.AskPrice1 = atof(vFields[19].c_str());
            DepthMarketData.AskVolume1 = atol(vFields[20].c_str());

            // ����
            DepthMarketData.AskPrice2 = atof(vFields[21].c_str());
            DepthMarketData.AskVolume2 = atol(vFields[22].c_str());

            // ����
            DepthMarketData.AskPrice3 = atof(vFields[23].c_str());
            DepthMarketData.AskVolume3 = atol(vFields[24].c_str());

            // ����
            DepthMarketData.AskPrice4 = atof(vFields[25].c_str());
            DepthMarketData.AskVolume4 = atol(vFields[26].c_str());

            // ����
            DepthMarketData.AskPrice5 = atof(vFields[27].c_str());
            DepthMarketData.AskVolume5 = atol(vFields[28].c_str());

            if (vFields[0] == "100" || vFields[0] == "200") {
                // �����ɵ��ֶβ�һ��
                // ��ͣ
                DepthMarketData.UpperLimitPrice = atof(vFields[48].c_str());

                // ��ͣ
                DepthMarketData.LowerLimitPrice = atof(vFields[49].c_str());

                // ʱ��
                sprintf(DepthMarketData.ActionDay, "%4.4s%2.2s%2.2s", vFields[30].c_str(), vFields[30].c_str() + 5, vFields[30].c_str() + 8);
                sprintf(DepthMarketData.UpdateTime, "%2.2s:%2.2s:%2.2s", vFields[30].c_str() + 11, vFields[30].c_str() + 14, vFields[30].c_str() + 17);
                sprintf(DepthMarketData.TradingDay, "%4.4s%2.2s%2.2s", vFields[30].c_str(), vFields[30].c_str() + 5, vFields[30].c_str() + 8);
            }
            else {
                // ��ͣ
                DepthMarketData.UpperLimitPrice = atof(vFields[47].c_str());

                // ��ͣ
                DepthMarketData.LowerLimitPrice = atof(vFields[48].c_str());

                // ʱ��
                sprintf(DepthMarketData.ActionDay, "%4.4s%2.2s%2.2s", vFields[30].c_str(), vFields[30].c_str() + 4, vFields[30].c_str() + 6);
                sprintf(DepthMarketData.UpdateTime, "%2.2s:%2.2s:%2.2s", vFields[30].c_str() + 8, vFields[30].c_str() + 10, vFields[30].c_str() + 12);
                sprintf(DepthMarketData.TradingDay, "%4.4s%2.2s%2.2s", vFields[30].c_str(), vFields[30].c_str() + 4, vFields[30].c_str() + 6);

                // ���ƴ���������Ҫ����100
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
    size_t count = 0;
    for (auto iter = m_vInstruments.begin()+m_cursor; iter != m_vInstruments.end(); iter++) {
        if (querystr != prefix)
            querystr += ",";
        if((*iter).length()==5 && isdigit(*(*iter).c_str()))
            querystr += "hk";
        else if (memcmp((*iter).c_str(), "60", 2) == 0
        	|| memcmp((*iter).c_str(), "11", 2) == 0
        	|| memcmp((*iter).c_str(), "50", 2) == 0
        	|| memcmp((*iter).c_str(), "51", 2) == 0
        	|| memcmp((*iter).c_str(), "56", 2) == 0
        	|| memcmp((*iter).c_str(), "58", 2) == 0
        	|| memcmp((*iter).c_str(), "60", 2) == 0
        	|| memcmp((*iter).c_str(), "68", 2) == 0)
            querystr += "sh";
        else if (memcmp((*iter).c_str(), "00", 2) == 0
        	|| memcmp((*iter).c_str(), "12", 2) == 0
        	|| memcmp((*iter).c_str(), "15", 2) == 0
        	|| memcmp((*iter).c_str(), "16", 2) == 0
        	|| memcmp((*iter).c_str(), "30", 2) == 0)
            querystr += "sz";
        else if(memcmp((*iter).c_str(), "43", 2) == 0
            || memcmp((*iter).c_str(), "82", 2) == 0
            || memcmp((*iter).c_str(), "83", 2) == 0
            || memcmp((*iter).c_str(), "87", 2) == 0
            || memcmp((*iter).c_str(), "88", 2) == 0)
            querystr += "bj";
        else
            querystr += "us";
        querystr += (*iter);

        count++;
        if (count >= m_window)
            break;
    }
    query(querystr.c_str());

    m_snap_timer.expires_from_now(boost::posix_time::milliseconds(m_snaptime));
    m_snap_timer.async_wait(boost::bind(&CFtdcMdApiImpl::OnSnapTime, this, boost::asio::placeholders::error));
}
