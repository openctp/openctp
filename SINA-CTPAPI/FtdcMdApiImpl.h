#if !defined(_FTDCMDAPIIMPL_H)
#define _FTDCMDAPIIMPL_H

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <boost/asio.hpp>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <vector>
#include <string>
#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <boost/beast/version.hpp>
#include <boost/asio/strand.hpp>
#include <cstdlib>
#include <functional>
#include <iostream>
#include <memory>
#include <string>
#include <boost/algorithm/string/classification.hpp>
#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string/trim.hpp>
#include <boost/program_options.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp> 
#include <boost/typeof/typeof.hpp> 
#include <fstream>
#include <limits>
#include <boost/thread.hpp>
#include "ThostFtdcMdApi.h"

namespace beast = boost::beast;         // from <boost/beast.hpp>
namespace http = beast::http;           // from <boost/beast/http.hpp>
namespace net = boost::asio;            // from <boost/asio.hpp>
using tcp = boost::asio::ip::tcp;       // from <boost/asio/ip/tcp.hpp>

// Report a failure
void
fail(beast::error_code ec, char const* what)
{
	//std::cerr << what << ": " << ec.message() << "\n";
}
///API�ӿ�ʵ��
class CFtdcMdApiImpl : public CThostFtdcMdApi
{
public:	
	///���캯��
	CFtdcMdApiImpl();

	void OnSnapTime(const boost::system::error_code& error);
	void HandleMarketData(std::vector<std::string>& data);

	std::string url_;
	std::string port_;
	net::io_context ioc_;
	tcp::resolver resolver_;
	beast::tcp_stream stream_;
	beast::flat_buffer buffer_; // (Must persist between reads)
	http::request<http::empty_body> req_;
	http::response<http::string_body> res_;
	std::map<std::string, size_t> _mInstruments;
	boost::thread* _pthread;

	// Start the asynchronous operation
	void
		query(char const* target)
	{
		// Set up an HTTP GET request message
		req_.version(11);
		req_.method(http::verb::get);
		req_.target(target);
		req_.set(http::field::host, url_);
		req_.set(http::field::user_agent, BOOST_BEAST_VERSION_STRING);
		req_.set(http::field::referer, "http://finance.sina.com.cn");

		// Look up the domain name
		resolver_.async_resolve(
			url_,
			port_,
			beast::bind_front_handler(
				&CFtdcMdApiImpl::on_resolve,
				this));
	}

	void
		on_resolve(
			beast::error_code ec,
			tcp::resolver::results_type results)
	{
		if (ec) {
			// Look up the domain name
			resolver_.async_resolve(
				url_, port_,
				beast::bind_front_handler(
					&CFtdcMdApiImpl::on_resolve,
					this));
			return;
		}

		// Set a timeout on the operation
		stream_.expires_after(std::chrono::seconds(30));

		// Make the connection on the IP address we get from a lookup
		stream_.async_connect(
			results,
			beast::bind_front_handler(
				&CFtdcMdApiImpl::on_connect,
				this));
	}

	void
		on_connect(beast::error_code ec, tcp::resolver::results_type::endpoint_type)
	{
		if (ec) {
			// Look up the domain name
			resolver_.async_resolve(
				url_, port_,
				beast::bind_front_handler(
					&CFtdcMdApiImpl::on_resolve,
					this));
			return;
		}

		res_.body().clear();

		// Set a timeout on the operation
		stream_.expires_after(std::chrono::seconds(30));

		// Send the HTTP request to the remote host
		http::async_write(stream_, req_,
			beast::bind_front_handler(
				&CFtdcMdApiImpl::on_write,
				this));
	}

	void
		on_write(
			beast::error_code ec,
			std::size_t bytes_transferred)
	{
		boost::ignore_unused(bytes_transferred);

		if (ec)
			return fail(ec, "write");

		// Receive the HTTP response
		http::async_read(stream_, buffer_, res_,
			beast::bind_front_handler(
				&CFtdcMdApiImpl::on_read,
				this));
	}

	void
		on_read(
			beast::error_code ec,
			std::size_t bytes_transferred)
	{
		boost::ignore_unused(bytes_transferred);

		if (ec) {
			//if (m_pSpi)
			//	m_pSpi->OnFrontDisconnected(0);
			return fail(ec, "read");
		}

		// Write the message to standard out
		//std::cout << res_ << std::endl;
		std::vector<std::string> vTemp, vPrices;
		std::string pkg = res_.body();
		boost::split(vTemp, pkg, boost::is_any_of("\""));
		for (size_t i = 0; i + 1 < vTemp.size(); i += 2) {
			std::string instrument = vTemp[i];
			instrument.erase(vTemp[i].size() - 1); // ȥ��=
			instrument.erase(0,instrument.find("hq_str_")+7); // ȥ��var hq_str_
			vPrices.push_back(instrument+","+vTemp[i + 1]);
		}
		HandleMarketData(vPrices);


		// ʹ�ö����ӻ��ƣ�������ɺ�ر�����
		// Gracefully close the socket
		stream_.socket().shutdown(tcp::socket::shutdown_both, ec);

		// not_connected happens sometimes so don't bother reporting it.
		if(ec && ec != beast::errc::not_connected)
		    return fail(ec, "shutdown");

		// If we get here then the connection is closed gracefully
	}

	///��ȡAPI�İ汾��Ϣ
	///@retrun ��ȡ���İ汾��
	//const char *GetApiVersion(){return 0;};

	///ɾ���ӿڶ�����
	///@remark ����ʹ�ñ��ӿڶ���ʱ,���øú���ɾ���ӿڶ���
	virtual void Release();

	///��ʼ��
	///@remark ��ʼ�����л���,ֻ�е��ú�,�ӿڲſ�ʼ����
	virtual void Init();

	///�ȴ��ӿ��߳̽�������
	///@return �߳��˳�����
	virtual int Join();

	///��ȡ��ǰ������
	///@retrun ��ȡ���Ľ�����
	///@remark ֻ�е�¼�ɹ���,���ܵõ���ȷ�Ľ�����
	virtual const char* GetTradingDay();

	///ע��ǰ�û������ַ
	///@param pszFrontAddress��ǰ�û������ַ��
	///@remark �����ַ�ĸ�ʽΪ����protocol://ipaddress:port�����磺��tcp://127.0.0.1:17001���� 
	///@remark ��tcp��������Э�飬��127.0.0.1�������������ַ����17001������������˿ںš�
	virtual void RegisterFront(char* pszFrontAddress);

	///ע�����ַ����������ַ
	///@param pszNsAddress�����ַ����������ַ��
	///@remark �����ַ�ĸ�ʽΪ����protocol://ipaddress:port�����磺��tcp://127.0.0.1:12001���� 
	///@remark ��tcp��������Э�飬��127.0.0.1�������������ַ����12001������������˿ںš�
	///@remark RegisterFront������RegisterNameServer
	virtual void RegisterNameServer(char* pszNsAddress);

	///ע�����ַ������û���Ϣ
	///@param pFensUserInfo���û���Ϣ��
	virtual void RegisterFensUserInfo(CThostFtdcFensUserInfoField* pFensUserInfo) { return; }

	///ע��ص��ӿ�
	///@param pSpi �����Իص��ӿ����ʵ��
	virtual void RegisterSpi(CThostFtdcMdSpi* pSpi);

	///�������顣
	///@param ppInstrumentID ��ԼID  
	///@param nCount Ҫ����/�˶�����ĺ�Լ����
	///@remark 
	virtual int SubscribeMarketData(char* ppInstrumentID[], int nCount);
	void SubscribeMarketData(const std::vector<std::string>& vInstruments);

	///�˶����顣
	///@param ppInstrumentID ��ԼID  
	///@param nCount Ҫ����/�˶�����ĺ�Լ����
	///@remark 
	virtual int UnSubscribeMarketData(char* ppInstrumentID[], int nCount);
	void UnSubscribeMarketData(const std::vector<std::string>& vInstruments);

	///����ѯ�ۡ�
	///@param ppInstrumentID ��ԼID  
	///@param nCount Ҫ����/�˶�����ĺ�Լ����
	///@remark 
	virtual int SubscribeForQuoteRsp(char* ppInstrumentID[], int nCount) { return -3; }

	///�˶�ѯ�ۡ�
	///@param ppInstrumentID ��ԼID  
	///@param nCount Ҫ����/�˶�����ĺ�Լ����
	///@remark 
	virtual int UnSubscribeForQuoteRsp(char* ppInstrumentID[], int nCount) { return -3; }

	///�û���¼����
	virtual int ReqUserLogin(CThostFtdcReqUserLoginField* pReqUserLogin, int nRequestID);

	///�û��˳�����
	virtual int ReqUserLogout(CThostFtdcUserLogoutField* pUserLogout, int nRequestID);

#if defined(V6_3_19) || defined(V6_5_1) || defined(V6_6_1_P1) || defined(V6_6_7) || defined(V6_6_9) || defined(V6_7_0) || defined(V6_7_1) || defined(V6_7_2)
	///�����ѯ�鲥��Լ
	virtual int ReqQryMulticastInstrument(CThostFtdcQryMulticastInstrumentField* pQryMulticastInstrument, int nRequestID) { return -3; }
#endif

public:
	CThostFtdcMdSpi* m_pSpi;
	CThostFtdcRspUserLoginField ThostRspUserLogin;
	CThostFtdcUserLogoutField ThostUserLogout;
	CThostFtdcRspInfoField ThostRspInfo;
	TThostFtdcDateType TradingDay;
	boost::asio::deadline_timer m_snap_timer;
	std::map<std::string, size_t> m_mInstruments;
	std::vector<std::string> m_vInstruments;
	size_t m_snaptime; // ��ʱ��ʱ�䣨ms��
	size_t m_cursor; // �����α꣨0~m_vInstruments.size()-1��
	size_t m_window; // һ�ζ��ĵĺ�Լ����
};


#endif
