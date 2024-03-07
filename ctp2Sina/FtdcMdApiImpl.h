#if !defined(_FTDCMDAPIIMPL_H)
#define _FTDCMDAPIIMPL_H

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <vector>
#include <string>
#include <map>

#include <boost/asio.hpp>

#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <boost/beast/version.hpp>

#include <boost/algorithm/string/classification.hpp>
#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string/trim.hpp>

#include <boost/thread.hpp>
#include <boost/typeof/typeof.hpp>

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
///API接口实现
class CFtdcMdApiImpl : public CThostFtdcMdApi
{
public:	
	///构造函数
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
			instrument.erase(vTemp[i].size() - 1); // 去掉=
			instrument.erase(0,instrument.find("hq_str_")+7); // 去掉var hq_str_
			vPrices.push_back(instrument+","+vTemp[i + 1]);
		}
		HandleMarketData(vPrices);


		// 使用短连接机制，接收完成后关闭连接
		// Gracefully close the socket
		stream_.socket().shutdown(tcp::socket::shutdown_both, ec);

		// not_connected happens sometimes so don't bother reporting it.
		if(ec && ec != beast::errc::not_connected)
		    return fail(ec, "shutdown");

		// If we get here then the connection is closed gracefully
	}

	///获取API的版本信息
	///@retrun 获取到的版本号
	//const char *GetApiVersion(){return 0;};

	///删除接口对象本身
	///@remark 不再使用本接口对象时,调用该函数删除接口对象
	virtual void Release();
	
	///初始化
	///@remark 初始化运行环境,只有调用后,接口才开始工作
	virtual void Init();
	
	///等待接口线程结束运行
	///@return 线程退出代码
	virtual int Join();
	
	///获取当前交易日
	///@retrun 获取到的交易日
	///@remark 只有登录成功后,才能得到正确的交易日
	virtual const char *GetTradingDay();
	
	///注册前置机网络地址
	///@param pszFrontAddress：前置机网络地址。
	///@remark 网络地址的格式为：“protocol://ipaddress:port”，如：”tcp://127.0.0.1:17001”。 
	///@remark “tcp”代表传输协议，“127.0.0.1”代表服务器地址。”17001”代表服务器端口号。
	virtual void RegisterFront(char *pszFrontAddress);
	
	///注册名字服务器网络地址
	///@param pszNsAddress：名字服务器网络地址。
	///@remark 网络地址的格式为：“protocol://ipaddress:port”，如：”tcp://127.0.0.1:12001”。 
	///@remark “tcp”代表传输协议，“127.0.0.1”代表服务器地址。”12001”代表服务器端口号。
	///@remark RegisterFront优先于RegisterNameServer
	virtual void RegisterNameServer(char *pszNsAddress);

	///注册回调接口
	///@param pSpi 派生自回调接口类的实例
	virtual void RegisterSpi(CThostFtdcMdSpi *pSpi);

	///用户登录请求
	virtual int ReqUserLogin(CThostFtdcReqUserLoginField *pReqUserLogin, int nRequestID);

	///用户退出请求
	virtual int ReqUserLogout(CThostFtdcUserLogoutField *pUserLogout, int nRequestID);

	///订阅行情。
	///@param ppInstrumentID 合约ID  
	///@param nCount 要订阅/退订行情的合约个数
	///@remark 
	virtual int SubscribeMarketData(char* ppInstrumentID[], int nCount);

	///退订行情。
	///@param ppInstrumentID 合约ID  
	///@param nCount 要订阅/退订行情的合约个数
	///@remark 
	virtual int UnSubscribeMarketData(char* ppInstrumentID[], int nCount);


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///暂时不实现的接口

	///注册名字服务器用户信息
	///@param pFensUserInfo：用户信息。
	virtual void RegisterFensUserInfo(CThostFtdcFensUserInfoField * pFensUserInfo){return;};

	///订阅询价。
	///@param ppInstrumentID 合约ID  
	///@param nCount 要订阅/退订行情的合约个数
	///@remark 
	virtual int SubscribeForQuoteRsp(char* ppInstrumentID[], int nCount) { return -3; }

	///退订询价。
	///@param ppInstrumentID 合约ID  
	///@param nCount 要订阅/退订行情的合约个数
	///@remark 
	virtual int UnSubscribeForQuoteRsp(char* ppInstrumentID[], int nCount) { return -3; }

#if defined(V6_3_19) || defined(V6_5_1) || defined(V6_6_1_P1) || defined(V6_6_7)
	///请求查询组播合约
	virtual int ReqQryMulticastInstrument(CThostFtdcQryMulticastInstrumentField *pQryMulticastInstrument, int nRequestID) { return -3; }
#endif

public:
	CThostFtdcMdSpi *m_pSpi;
	CThostFtdcRspUserLoginField ThostRspUserLogin;
	CThostFtdcUserLogoutField ThostUserLogout;
	CThostFtdcRspInfoField ThostRspInfo;
	TThostFtdcDateType TradingDay;
	boost::asio::deadline_timer m_snap_timer;
};


#endif
