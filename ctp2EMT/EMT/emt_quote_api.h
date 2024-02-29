#pragma once

/////////////////////////////////////////////////////////////////////////
///@author 东方财富证券股份有限公司
///@file emt_quote_api.h
///@brief 定义客户端行情接口
/////////////////////////////////////////////////////////////////////////
#ifdef _WIN32
#define QUOTE_API_ _declspec(dllexport)
#else
#define QUOTE_API_  _declspec(dllimport)
#endif // _WIN32

#include "emt_quote_struct.h"
/*!
* \class EMT::API::QuoteSpi
*
* \brief 行情接口响应类
*
* \author 东方财富证券股份有限公司
* \date 六月 2020
*/
namespace EMT {
	namespace API {
		/**
		*   行情回调类
		*/
		class QuoteSpi
		{
		public:
			virtual ~QuoteSpi()
			{

			};

			/**
			*   当客户端与行情后台通信连接断开时，该方法被调用
			*   @attention					api不会自动重连，当断线发生时，请用户自行选择后续操作。可以在此函数中调用Login重新登录。注意用户重新登录后，需要重新订阅
			*   @param reason				错误原因
			*   @return						该函数返回为void
			*/
			virtual void OnDisconnected(int reason) {};

			/**
			*   错误应答
			*   @attention					此函数只有在服务器发生错误时才会调用，一般无需用户处理
			*   @param error_info			当服务器响应发生错误时的具体错误内容
			*   @return						该函数返回为void
			*/
			virtual void OnError(EMTRspInfoStruct* error_info) {};

			/**
			*   指数行情通知
			*   @attention					需要快速返回，否则阻塞后续消息，导致延时，当阻塞严重时，会触发断线
			*   @param index_data			指数行情数据，只有指数行情数据相关字段
			*/
			virtual void OnIndexData(EMTIndexDataStruct* index_data) {};

			/**
			*   深度行情通知，包含买一卖一队列
			*   @attention					需要快速返回，否则会堵塞后续消息，当堵塞严重时，会触发断线
			*   @param market_data			行情数据
			*   @param bid1_qty				买一队列数据
			*   @param bid1_count			买一队列的有效委托笔数
			*   @param max_bid1_count		买一队列总委托笔数
			*   @param ask1_qty				卖一队列数据
			*   @param ask1_count			卖一队列的有效委托笔数
			*   @param max_ask1_count		卖一队列总委托笔数
			*/
			virtual void OnDepthMarketData(EMTMarketDataStruct* market_data, int64_t bid1_qty[], int32_t bid1_count, int32_t max_bid1_count, int64_t ask1_qty[], int32_t ask1_count, int32_t max_ask1_count) {};

			/**
			*   逐笔行情通知，包括股票，基金，权证，债券和质押式回购
			*   @attention					每条订阅的合约均对应一条订阅应答，需要快速返回，否则会阻塞后续消息，当阻塞严重时，会触发断线
			*   @param tbt_data				逐笔行情数据，包括逐笔委托和逐笔成交，此为共用结构体，需要根据type来区分是逐笔委托还是逐笔成交
			*/
			virtual void OnTickByTick(EMTTickByTickStruct* tbt_data) {};
			
			/**
			*   行情订单簿通知
			*   @param order_book			行情订单簿数据，需要快速返回，否则会堵塞后续消息，当堵塞严重时，会触发断线
			*/
			virtual void OnOrderBook(EMTOrderBookStruct* order_book) {};
			
			/**
			*   分时行情通知
			*   @param minute_info			分时行情数据，需要快速返回，否则会堵塞后续消息，当堵塞严重时，会触发断线
			*/
			virtual void OnMinuteInfo(EMTMinuteInfo* minute_info) {};

			/**
			*   订阅全市场的指数行情应答
			*   @attention					需要快速返回
			*   @param exchange_id			表示当前全部订阅的市场，如果为ALL，表示沪深全市场，SH表示为上海全市场，SZ表示为深圳全市场
			*	@param error_info			订阅合约时发生错误时返回的错误信息，当error_info为空，或者error_info.error_id为0时，表明没有错误
			*/
			virtual void OnSubscribeAllIndexData(EMT_EXCHANGE_TYPE exchange_id, EMTRspInfoStruct* error_info) {};

			/**
			*   退订全市场的指数行情应答
			*   @attention					需要快速返回
			*   @param exchange_id			表示当前全部退订的市场，如果为ALL，表示沪深全市场，SH表示为上海全市场，SZ表示为深圳全市场
			*	@param error_info			取消订阅合约时发生错误时返回的错误信息，当error_info为空，或者error_info.error_id为0时，表明没有错误
			*/
			virtual void OnUnSubscribeAllIndexData(EMT_EXCHANGE_TYPE exchange_id, EMTRspInfoStruct* error_info) {};

			/**
			*   订阅指数行情应答
			*   @attention					每条订阅的合约对应一条订阅应答，需要快速返回，否则会阻塞后续消息，当阻塞严重时，会触发断线
			*   @param ticker				表示当前全阅的市场，SH表示为上海全市场，SZ表示为深圳全市场
			*   @param error_info			订阅的合约编号代码
			*	@param is_last				是否此次订阅的最后一个应答，当为最后一个的时候为true，如果为false，表示还有其他后续消息响应
			*/
			virtual void OnSubIndexData(EMTSpecificTickerStruct* ticker, EMTRspInfoStruct* error_info, bool is_last) {};
			
			/**
			*   退订指数行情应答
			*   @attention					每条订阅的合约对应一条退订应答，需要快速返回，否则会阻塞后续消息，当阻塞严重时，会触发断线
			*   @param ticker				订阅的合约编号代码
			*   @param error_info			取消订阅合约发生错误时的错误信息，当error_info为空，或者error_info.error_id为0时，表明没有错误
			*	@param is_last				是否此次取消订阅的最后一个应答，当为最后一个的时候为true，如果为false，表示还有其他后续消息响应
			*/
			virtual void OnUnSubIndexData(EMTSpecificTickerStruct* ticker, EMTRspInfoStruct* error_info, bool is_last) {};

			/**
			*   订阅全市场股票快照行情应答
			*   @attention					需要快速返回
			*   @param exchange_id			表示当前全订阅的市场，如果为ALL，表示沪深全市场，SH表示为上海全市场，SZ表示为深圳全市场
			*	@param error_info
			*/
			virtual void OnSubscribeAllMarketData(EMT_EXCHANGE_TYPE exchange_id, EMTRspInfoStruct* error_info) {};

			/**
			*   退订全市场的股票快照行情应答
			*   @attention					需要快速返回
			*   @param exchange_id			表示当前全退订的市场，如果为ALL，表示沪深全市场，SH表示为上海全市场，SZ表示为深圳全市场
			*	@param error_info			取消订阅合约时发生错误时返回的错误信息，当error_info为空，或者error_info.error_id为0时，表明没有错误
			*/
			virtual void OnUnSubscribeAllMarketData(EMT_EXCHANGE_TYPE exchange_id, EMTRspInfoStruct* error_info) {};

			/**
			*   订阅快照行情应答，包括股票，基金，债券，权证和质押式回购
			*   @attention					每条订阅的合约对应一条订阅应答，需要快速返回，否则会阻塞后续消息，当阻塞严重时，会触发断线
			*   @param ticker				表示当前全阅的市场，SH表示为上海全市场，SZ表示为深圳全市场
			*   @param error_info			订阅的合约编号代码
			*	@param is_last				是否此次订阅的最后一个应答，当为最后一个的时候为true，如果为false，表示还有其他后续消息响应
			*/
			virtual void OnSubMarketData(EMTSpecificTickerStruct* ticker, EMTRspInfoStruct* error_info, bool is_last) {};

			/**
			*   退订快照行情应答，包括股票，基金，债券，权证和质押式回购
			*   @attention					每条订阅的合约对应一条订阅应答，需要快速返回，否则会阻塞后续消息，当阻塞严重时，会触发断线
			*   @param ticker				订阅的合约编号代码
			*   @param error_info			取消订阅合约发生错误时的错误信息，当error_info为空，或者error_info.error_id为0时，表明没有错误
			*	@param is_last				是否此次取消订阅的最后一个应答，当为最后一个的时候为true，如果为false，表示还有其他后续消息响应
			*/
			virtual void OnUnSubMarketData(EMTSpecificTickerStruct* ticker, EMTRspInfoStruct* error_info, bool is_last) {};

			/**
			*   订阅全市场的逐笔行情应答
			*   @attention					需要快速返回
			*   @param exchange_id			表示当前全订阅的市场，如果为ALL，表示沪深全市场，SH表示为上海全市场，SZ表示为深圳全市场
			*	@param error_info			订阅合约时发生错误时返回的错误信息，当error_info为空，或者error_info.error_id为0时，表明没有错误
			*/
			virtual void OnSubscribeAllTickByTick(EMT_EXCHANGE_TYPE exchange_id, EMTRspInfoStruct* error_info) {};

			/**
			*   退订全市场的逐笔行情应答
			*   @attention					需要快速返回
			*   @param exchange_id			表示当前全订阅的市场，如果为ALL，表示沪深全市场，SH表示为上海全市场，SZ表示为深圳全市场
			*	@param error_info			取消订阅合约时发生错误时返回的错误信息，当error_info为空，或者error_info.error_id为0时，表明没有错误
			*/
			virtual void OnUnSubscribeAllTickByTick(EMT_EXCHANGE_TYPE exchange_id, EMTRspInfoStruct* error_info) {};

			/**
			*   订阅逐笔行情应答，包括股票，基金，债券和权证
			*   @attention					每条订阅的合约均对应一条订阅应答，需要快速返回，否则会阻塞后续消息，当阻塞严重时，会触发断线
			*   @param ticker				订阅的合约代码编号
			*   @param error_info			订阅合约发生错误时的错误信息，当error_info为空，或者error_info.error_id为0时，表明没有错误
			*	@param is_last				是否此次订阅的最后一个应答，当为最后一个的时候为true，如果为false，表示还有其他后续消息响应
			*/
			virtual void OnSubTickByTick(EMTSpecificTickerStruct* ticker, EMTRspInfoStruct* error_info, bool is_last) {};

			/**
			*   退订逐笔行情应答，包括股票，基金，债券和权证
			*   @attention					每条订阅的合约均对应一条订阅应答，需要快速返回，否则会阻塞后续消息，当阻塞严重时，会触发断线
			*   @param ticker				订阅的合约代码编号
			*   @param error_info			取消订阅合约时发生错误时返回的错误信息，当error_info为空，或者error_info.error_id为0时，表明没有错误
			*	@param is_last				是否此次取消订阅的最后一个应答，当为最后一个的时候为true，如果为false，表示还有其他后续消息响应
			*/
			virtual void OnUnSubTickByTick(EMTSpecificTickerStruct* ticker, EMTRspInfoStruct* error_info, bool is_last) {};

			/**
			*   订阅行情订单簿应答
			*   @attention                  需要快速返回
			*   @param exchange_id          表示当前全订阅的市场，如果为EMT_EXCHANGE_UNKNOWN，表示沪深全市场，EMT_EXCHANGE_SH表示为上海全市场，EMT_EXCHANGE_SZ表示为深圳全市场
			*   @param error_info           订阅合约时发生错误时返回的错误信息，当error_info为空，或者error_info.error_id为0时，表明没有错误*/
			virtual void OnSubscribeAllOrderBook(EMT_EXCHANGE_TYPE exchange_id, EMTRspInfoStruct* error_info) {};

			/**
			*   退订全市场的股票行情订单簿应答
			*   @attention                  需要快速返回
			*   @param exchange_id          表示当前全退订的市场，如果为EMT_EXCHANGE_UNKNOWN，表示沪深全市场，EMT_EXCHANGE_SH表示为上海全市场，EMT_EXCHANGE_SZ表示为深圳全市场
			*   @param error_info           取消订阅合约时发生错误时返回的错误信息，当error_info为空，或者error_info.error_id为0时，表明没有错误
			*/
			virtual void OnUnSubscribeAllOrderBook(EMT_EXCHANGE_TYPE exchange_id, EMTRspInfoStruct* error_info) {};

			/**
			*   订阅行情订单簿应答
			*   @attention                  每条订阅的合约均对应一条订阅应答，需要快速返回，否则会堵塞后续消息，当堵塞严重时，会触发断线
			*   @param ticker               详细的合约订阅情况
			*   @param error_info           订阅合约发生错误时的错误信息，当error_info为空，或者error_info.error_id为0时，表明没有错误
			*   @param is_last              是否此次订阅的最后一个应答，当为最后一个的时候为true，如果为false，表示还有其他后续消息响应
			*/
			virtual void OnSubOrderBook(EMTSpecificTickerStruct* ticker, EMTRspInfoStruct* error_info, bool is_last) {};

			/**
			*   退订行情订单簿应答
			*   @attention                  每条取消订阅的合约均对应一条取消订阅应答，需要快速返回，否则会堵塞后续消息，当堵塞严重时，会触发断线
			*   @param ticker               详细的合约订阅情况
			*   @param error_info           订阅合约发生错误时的错误信息，当error_info为空，或者error_info.error_id为0时，表明没有错误
			*   @param is_last              是否此次订阅的最后一个应答，当为最后一个的时候为true，如果为false，表示还有其他后续消息响应
			*/
			virtual void OnUnSubOrderBook(EMTSpecificTickerStruct* ticker, EMTRspInfoStruct* error_info, bool is_last) {};

			/**
			*   订阅全市场分时行情
			*   @attention                  需要快速返回
			*   @param exchange_id          表示当前全订阅的市场，如果为EMT_EXCHANGE_UNKNOWN，表示沪深全市场，EMT_EXCHANGE_SH表示为上海全市场，EMT_EXCHANGE_SZ表示为深圳全市场
			*   @param error_info           订阅合约时发生错误时返回的错误信息，当error_info为空，或者error_info.error_id为0时，表明没有错误
			*/
			virtual void OnSubscribeAllMinuteInfo(EMT_EXCHANGE_TYPE exchange_id, EMTRspInfoStruct* error_info) {};
			
			/**
			*   退订全市场分时行情
			*   @attention                  需要快速返回
			*   @param exchange_id          表示当前全退订的市场，如果为EMT_EXCHANGE_UNKNOWN，表示沪深全市场，EMT_EXCHANGE_SH表示为上海全市场，EMT_EXCHANGE_SZ表示为深圳全市场
			*   @param error_info           取消订阅合约时发生错误时返回的错误信息，当error_info为空，或者error_info.error_id为0时，表明没有错误
			*/
			virtual void OnUnSubscribeAllMinuteInfo(EMT_EXCHANGE_TYPE exchange_id, EMTRspInfoStruct* error_info) {};
			
			/**
			*   订阅分时行情
			*   @attention                  每条订阅的合约均对应一条订阅应答，需要快速返回，否则会堵塞后续消息，当堵塞严重时，会触发断线
			*   @param ticker               详细的合约订阅情况
			*   @param error_info           订阅合约发生错误时的错误信息，当error_info为空，或者error_info.error_id为0时，表明没有错误
			*   @param is_last              是否此次订阅的最后一个应答，当为最后一个的时候为true，如果为false，表示还有其他后续消息响应
			*/
			virtual void OnSubMinuteInfo(EMTSpecificTickerStruct* ticker, EMTRspInfoStruct* error_info, bool is_last) {};
			
			/**
			*   退订分时行情
			*   @attention                  每条取消订阅的合约均对应一条取消订阅应答，需要快速返回，否则会堵塞后续消息，当堵塞严重时，会触发断线
			*   @param ticker               详细的合约订阅情况
			*   @param error_info           订阅合约发生错误时的错误信息，当error_info为空，或者error_info.error_id为0时，表明没有错误
			*   @param is_last              是否此次取消订阅的最后一个应答，当为最后一个的时候为true，如果为false，表示还有其他后续消息响应
			*/
			virtual void OnUnSubMinuteInfo(EMTSpecificTickerStruct* ticker, EMTRspInfoStruct* error_info, bool is_last) {};

			/**
			*   查询全市场合约部分静态信息的应答
			*   @attention					需要使用合约部分静态信息结构体EMTQuoteStaticInfo
			*   @param qsi					合约部分静态信息结构体
			*   @param error_info			订阅合约发生错误时的错误信息，当error_info为空，或者error_info.error_id为0时，表明没有错误
			*   @param is_last				是否此次退订的最后一个应答，当为最后一个的时候为true，如果为false，表示还有其他后续消息响应
			*   @return						该函数返回为void
			*/
			virtual void OnQueryAllTickers(EMTQuoteStaticInfo* qsi, EMTRspInfoStruct* error_info, bool is_last) {};

			/**
			*   查询全市场合约完整静态信息的应答
			*   @attention					需要使用合约完整静态信息结构体EMTQutoFullInfo
			*   @param qfi					合约完整静态信息结构体
			*   @param error_info			订阅合约发生错误时的错误信息，当error_info为空，或者error_info.error_id为0时，表明没有错误
			*   @param is_last				是否此次退订的最后一个应答，当为最后一个的时候为true，如果为false，表示还有其他后续消息响应
			*   @return						该函数返回为void
			*/
			virtual void OnQueryAllTickersFullInfo(EMTQuoteFullInfo* qfi, EMTRspInfoStruct* error_info, bool is_last) {};

			/**
			*   查询合约最新指数的应答
			*   @attention					需要使用最新数据结构体EMTIndexDataStruct
			*   @param index_data			最新指数数据
			*   @param error_info			订阅合约发生错误时的错误信息，当error_info为空，或者error_info.error_id为0时，表明没有错误
			*   @param is_last				是否此次退订的最后一个应答，当为最后一个的时候为true，如果为false，表示还有其他后续消息响应
			*   @return						该函数返回为void
			*/
			virtual void OnQueryLatestIndexData(EMTIndexDataStruct* index_data, EMTRspInfoStruct* error_info, bool is_last) {};

			/**
			*   查询合约最新现货快照的应答
			*   @attention					需要使用最新数据结构体EMTIndexDataStruct
			*   @param market_data			最新现货快照数据
			*   @param error_info			订阅合约发生错误时的错误信息，当error_info为空，或者error_info.error_id为0时，表明没有错误
			*   @param is_last				是否此次退订的最后一个应答，当为最后一个的时候为true，如果为false，表示还有其他后续消息响应
			*   @return						该函数返回为void
			*/
			virtual void OnQueryLatestMarketData(EMTMarketDataStruct* market_data, EMTRspInfoStruct* error_info, bool is_last) {};

			/**
			*   查询分时数据的应答
			*   @attention					需要使用分时结构体EMTMinuteInfo
			*   @param minute_info			最新快照数据
			*   @param error_info			订阅合约发生错误时的错误信息，当error_info为空，或者error_info.error_id为0时，表明没有错误
			*   @param is_last				是否此次退订的最后一个应答，当为最后一个的时候为true，如果为false，表示还有其他后续消息响应
			*   @return						该函数返回为void
			*/
			virtual void OnQueryMinuteInfo(EMTMinuteInfo* minute_info, EMTRspInfoStruct* error_info, bool is_last) {};

			/**
			*   查询历史分时数据的应答
			*   @attention					需要使用分时结构体EMTMinuteInfo
			*   @param minute_info			最新快照数据
			*   @param error_info			订阅合约发生错误时的错误信息，当error_info为空，或者error_info.error_id为0时，表明没有错误
			*   @param is_last				是否此次退订的最后一个应答，当为最后一个的时候为true，如果为false，表示还有其他后续消息响应
			*   @return						该函数返回为void
			*/
			virtual void OnQueryMinHistoryInfo(EMTMinuteInfo* minute_info, EMTRspInfoStruct* error_info, bool is_last) {};

			/*
			* 查询最新价
			* @attention		
			* @param price_info		价格信息
			* @param error_info		
			* @param is_last		
			* @return				该函数返回为void
			*/
			virtual void OnQueryTickersPriceInfo(EMTTickerPriceInfo* price_info, EMTRspInfoStruct* error_info, bool is_last) {};

		private:

		};
	}
}

/*!
* \class EMT::API::QuoteApi
*
* \brief 行情接口类
*
* \author 东方财富证券股份有限公司
* \date 十月 2020
*/
namespace EMT {
	namespace API {

		/**
		*   行情订阅接口
		*/
#ifdef _WIN32
		class QUOTE_API_ QuoteApi
#else
		class QuoteApi
#endif // _WIN32
		{

		public:
			static QuoteApi* CreateQuoteApi(uint8_t client_id, const char* save_file_path, EMT_LOG_LEVEL log_level = EMT_LOG_LEVEL_DEBUG);

			/**
			*   删除接口对象本身
			*   @attention						不再使用本接口对象时，调用该函数删除接口对象
			*/
			virtual void Release() = 0;

			/**
			*   获取API的发行版本号
			*   @return 返回api发行版本号
			*/
			virtual const char* GetApiVersion() = 0;

			/**
			*   用户登录请求
			*   @attention						此函数为同步阻塞模式，不需要异步等待登录成功，当函数返回即可进行后续操作，此api只能有一个连接
			*   @param ip						服务器ip地址，类似"127.0.0.1"
			*   @param port						服务器端口号
			*   @param user						用户登录名，用户的唯一标识
			*   @param pwd						用户登密码
			*   @param sock_type				登录方式："EMT_PROTOCOL_TCP"为TCP登录，"EMT_PROTOCOL_UDP"为UDP登录
			*   @param local_ip					行情接收网卡IP
			*   @return							登录是否成功，"0"表示登录成功，"-1"表示连接服务器出错，"-2"表示登录失败，可能是重复登录，或者是当前账号没有注册，如果是重复登录的话，请先Logout
			*/
			virtual int Login(const char* ip, int port, const char* user, const char* pwd, EMT_PROTOCOL_TYPE sock_type, const char* local_ip = nullptr) = 0;

			/**
		    *   登出请求
		    *   @attention						此函数为同步阻塞模式，不需要异步等待登录成功，当函数返回即可进行后续操作
		    *   @return							登出是否成功，"0"表示登出成功，随后的操作都将会是无效的
		    */
			virtual int Logout() = 0;

			/**
			*   注册回调接口
			*   @param spi						派生自回调接口类的实例，请在登录之前完成设定
			*/
			virtual void RegisterSpi(QuoteSpi* spi) = 0;


			/**
			*   设置采用UDP方式连接时的接收缓冲区大小
			*   @attention						需要在Login之前调用，默认大小和最小设置均为64MB。此缓存大小单位为MB，请输入2的次方数，例如128MB请输入128。
			*   @param buff_size				缓冲区大小
			*/
			virtual void SetUDPBufferSize(uint32_t buff_size) = 0;

			/**
			*   使用UDP接收行情时，设置接收行情线程绑定的cpu
			*   @attention						此函数可不调用，如果调用则必须在Login之前调用，否则不会生效
			*   @param cpu_no					设置绑定的cpu，例如绑定cpu 0，可以设置0，绑定cpu 2，可以设置2，建议绑定后面的cpu
			*/
			virtual void SetUDPRecvThreadAffinity(int32_t cpu_no) = 0;

			/**
			*   使用UDP接收行情时，设置解析行情线程绑定的cpu
			*   @attention						此函数可不调用，如果调用则必须在Login之前调用，否则不会生效
			*   @param cpu_no					设置绑定的cpu，例如绑定cpu 0，可以设置0，绑定cpu 2，可以设置2，建议绑定后面的cpu
			*/
			virtual void SetUDPParseThreadAffinity(int32_t cpu_no) = 0;
			/**
			*   设定UDP收行情时是否输出异步日志
			*   @attention						此函数可不调用，如果调用则必须在Login之前调用，否则不会生效
			*   @param   flag					是否输出标识，默认为true，如果不想输出“udpseq”开头的异步日志，请设置此参数为false
			*/
			virtual void SetUDPSeqLogOutPutFlag(bool flag = true) = 0;

			/**
			*   设置心跳检测时间间隔，单位为秒
			*   @attention						此函数必须在Login之前调用
			*   @param interval					心跳检测时间间隔，单位为秒
			*/
			virtual void SetHeartBeatInterval(uint32_t interval = 5) = 0;

			/**
			*   订阅全市场指数快照行情
			*   @attention                      需要与取消订阅全市场指数行情接口配套使用
			*   @param exchange_id              表示当前订阅的市场，如果为ALL，表示沪深全市场，SH表示上海全市场，SZ表示深证全市场
			*   @return                         订阅全市场指数快照行情接口调用是否成功，"0"表示接口调用成功，非"0"表示接口调用出错
			*/
			virtual int SubscribeAllIndexData(EMT_EXCHANGE_TYPE exchange_id = EMT_EXCHANGE_UNKNOWN) = 0;

			/**
			*   取消订阅全市场指数快照行情
			*   @attention                      需要与订阅全市场指数行情接口配套使用
			*   @param exchange_id              表示当前取消订阅的市场，如果为ALL，表示沪深全市场，SH表示上海全市场，SZ表示深证全市场
			*   @return                         取消订阅全市场指数快照行情接口调用是否成功，"0"表示接口调用成功，非"0"表示接口调用出错
			*/
			virtual int UnSubscribeAllIndexData(EMT_EXCHANGE_TYPE exchange_id = EMT_EXCHANGE_UNKNOWN) = 0;

			/**
			*   订阅指数快照行情
			*   @attention                      可一次性订阅同一证券交易所的多个指数，无论用户因为何种问题需要重新登录行情服务器，都需要重新订阅
			*   @param tickers                  指数代码数组，注意指数代码必须以"\0"结尾，不包括空格
			*   @param count                    需要订阅行情的指数个数
			*   @param exchange_id              交易所代码，如果是SH表示上海全市场，SZ表示深证全市场
			*   @return                         订阅接口调用是否成功，"0"表示接口调用成功，非"0"表示接口调用出错
			*/
			virtual int SubscribeIndexData(char* tickers[], int count, EMT_EXCHANGE_TYPE exchange_id = EMT_EXCHANGE_UNKNOWN) = 0;
			/**
			*   取消订阅指数快照行情
			*   @attention                      可一次性取消订阅同一证券交易所的多个指数，无论用户因为何种问题需要重新登录行情服务器，都需要重新订阅
			*   @param tickers                  指数代码数组，注意指数代码必须以"\0"结尾，不包括空格
			*   @param count                    需要订阅行情的指数个数
			*   @param exchange_id              交易所代码，如果是SH表示上海全市场，SZ表示深证全市场
			*   @return                         取消订阅接口调用是否成功，"0"表示接口调用成功，非"0"表示接口调用出错
			*/
			virtual int UnSubscribeIndexData(char* tickers[], int count, EMT_EXCHANGE_TYPE exchange_id = EMT_EXCHANGE_UNKNOWN) = 0;

			/**
			*   订阅全市场合约快照行情
			*   @attention                      需要与全市场退订行情接口配套使用
			*   @param exchange_id              表示当前全订阅的市场，如果为ALL，表示沪深全市场，SH表示上海全市场，SZ表示深证全市场
			*   @return                         订阅全市场行情接口调用是否成功，"0"表示接口调用成功，非"0"表示接口调用出错
			*/
			virtual int SubscribeAllMarketData(EMT_EXCHANGE_TYPE exchange_id = EMT_EXCHANGE_UNKNOWN) = 0;

			/**
			*   退订全市场合约快照行情
			*   @attention                      需要与全市场订阅行情接口配套使用
			*   @param exchange_id              表示当前全订阅的市场，如果为ALL，表示沪深全市场，SH表示上海全市场，SZ表示深证全市场
			*   @return                         退订全市场行情接口调用是否成功，"0"表示接口调用成功，非"0"表示接口调用出错
			*/
			virtual int UnSubscribeAllMarketData(EMT_EXCHANGE_TYPE exchange_id = EMT_EXCHANGE_UNKNOWN) = 0;

			/**
			*   订阅快照行情，包括股票，基金，债券，权证和质押式回购
			*   @attention                      可一次性订阅同一证券交易所的多个合约，无论用户因为何种问题需要重新登录行情服务器，都需要重新订阅
			*   @param tickers                  合约代码数组，注意合约代码必须以"\0"结尾，不包括空格
			*   @param count                    需要订阅行情的合约个数
			*   @param exchange_id              交易所代码，如果是SH表示上海全市场，SZ表示深证全市场
			*   @return                         订阅接口调用是否成功，"0"表示接口调用成功，非"0"表示接口调用出错
			*/
			virtual int SubscribeMarketData(char* tickers[], int count, EMT_EXCHANGE_TYPE exchange_id = EMT_EXCHANGE_UNKNOWN) = 0;

			/**
			*   取消订阅快照行情，包括股票，基金，债券，权证和质押式回购
			*   @attention                      可一次性取消订阅同一证券交易所的多个合约，无论用户因为何种问题需要重新登录行情服务器，都需要重新订阅
			*   @param exchange_id              交易所代码，如果是SH表示上海全市场，SZ表示深证全市场
			*   @param tickers                  合约代码数组，注意合约代码必须以"\0"结尾，不包括空格
			*   @param count                    需要订阅行情的合约个数
			*   @return                         取消订阅接口调用是否成功，"0"表示接口调用成功，非"0"表示接口调用出错
			*/
			virtual int UnSubscribeMarketData(char* tickers[], int count, EMT_EXCHANGE_TYPE exchange_id = EMT_EXCHANGE_UNKNOWN) = 0;

			/**
			*   订阅全市场股票逐笔行情
			*   @attention                      需要与全市场退订逐笔行情接口配套使用
			*   @param exchange_id              表示当前全订阅的市场，如果为ALL，表示沪深全市场，SH表示上海全市场，SZ表示深证全市场
			*   @return                         订阅全市场逐笔行情接口调用是否成功，"0"表示接口调用成功，非"0"表示接口调用出错
			*/
			virtual int SubscribeAllTickByTick(EMT_EXCHANGE_TYPE exchange_id = EMT_EXCHANGE_UNKNOWN) = 0;

			/**
			*   退订全市场股票逐笔行情
			*   @attention                      需要与订阅全市场逐笔行情接口配套使用
			*   @param exchange_id              表示当前全订阅的市场，如果为ALL，表示沪深全市场，SH表示上海全市场，SZ表示深证全市场
			*   @return                         退订阅全市场逐笔行情接口调用是否成功，"0"表示接口调用成功，非"0"表示接口调用出错
			*/
			virtual int UnSubscribeAllTickByTick(EMT_EXCHANGE_TYPE exchange_id = EMT_EXCHANGE_UNKNOWN) = 0;

			/**
			*   订阅逐笔行情，包括股票，基金，债券，权证和质押式回购
			*   @attention                      可一次性订阅同一证券交易所的多个合约，无论用户因为何种问题需要重新登录行情服务器，都需要重新订阅
			*   @param tickers                  合约代码数组，注意合约代码必须以"\0"结尾，不包括空格
			*   @param count                    需要订阅行情的合约个数
			*   @param exchange_id              交易所代码，如果是SH表示上海全市场，SZ表示深证全市场
			*   @return                         订阅逐笔行情接口调用是否成功，"0"表示接口调用成功，非"0"表示接口调用出错
			*/
			virtual int SubscribeTickByTick(char* tickers[], int count, EMT_EXCHANGE_TYPE exchange_id = EMT_EXCHANGE_UNKNOWN) = 0;

			/**
			*   退订逐笔行情，包括股票，基金，债券，权证和质押式回购
			*   @attention                      可一次性取消订阅同一证券交易所的多个合约，无论用户因为何种问题需要重新登录行情服务器，都需要重新订阅
			*   @param tickers                  合约代码数组，注意合约代码必须以"\0"结尾，不包括空格
			*   @param count                    需要订阅行情的合约个数
			*   @param exchange_id              交易所代码，如果是SH表示上海全市场，SZ表示深证全市场
			*   @return                         取消订阅接口调用是否成功，"0"表示接口调用成功，非"0"表示接口调用出错
			*/
			virtual int UnSubscribeTickByTick(char* tickers[], int count, EMT_EXCHANGE_TYPE exchange_id = EMT_EXCHANGE_UNKNOWN) = 0;

			/**
			*   订阅全市场的股票行情订单簿
			*   @attention                      需要与全市场退订行情订单簿接口配套使用
			*   @param exchange_id              表示当前全订阅的市场，如果为EMT_EXCHANGE_UNKNOWN，表示沪深全市场，EMT_EXCHANGE_SH表示为上海全市场，EMT_EXCHANGE_SZ表示为深圳全市场
			*   @return                         订阅全市场行情订单簿接口调用是否成功，“0”表示接口调用成功，非“0”表示接口调用出错
			*/
			virtual int SubscribeAllOrderBook(EMT_EXCHANGE_TYPE exchange_id = EMT_EXCHANGE_UNKNOWN) = 0;

			/**
			*   退订全市场的股票行情订单簿
			*   @attention                      需要与订阅全市场行情订单簿接口配套使用
			*   @param exchange_id              表示当前退订的市场，如果为EMT_EXCHANGE_UNKNOWN，表示沪深全市场，EMT_EXCHANGE_SH表示为上海全市场，EMT_EXCHANGE_SZ表示为深圳全市场
			*   @return                         取消订阅全市场行情订单簿接口调用是否成功，“0”表示接口调用成功，非“0”表示接口调用出错
			*/
			virtual int UnSubscribeAllOrderBook(EMT_EXCHANGE_TYPE exchange_id = EMT_EXCHANGE_UNKNOWN) = 0;

			/**
			*   订阅行情订单簿
			*   @attention                      可以一次性订阅同一证券交易所的多个合约，无论用户因为何种问题需要重新登录行情服务器，都需要重新订阅行情(仅支持深交所)
			*   @param tickers                  合约ID数组，注意合约代码必须以'\0'结尾，不包含空格
			*   @param count                    要订阅/退订行情订单簿的合约个数
			*   @param exchange_id              交易所代码
			*   @return                         订阅行情订单簿接口调用是否成功，“0”表示接口调用成功，非“0”表示接口调用出错
			*/
			virtual int SubscribeOrderBook(char* tickers[], int count, EMT_EXCHANGE_TYPE exchange_id) = 0;

			/**
			*   退订行情订单簿
			*   @attention                      可以一次性取消订阅同一证券交易所的多个合约，需要与订阅行情订单簿接口配套使用
			*   @param tickers                  合约ID数组，注意合约代码必须以'\0'结尾，不包含空格
			*   @param count                    要订阅/退订行情订单簿的合约个数
			*   @param exchange_id              交易所代码
			*   @return                         取消订阅行情订单簿接口调用是否成功，“0”表示接口调用成功，非“0”表示接口调用出错
			*/
			virtual int UnSubscribeOrderBook(char* tickers[], int count, EMT_EXCHANGE_TYPE exchange_id) = 0;

			/**
			*   订阅全市场的分时行情
			*   @attention                      需要与退订全市场分时行情接口配套使用
			*   @param exchange_id              表示当前全订阅的市场，如果为EMT_EXCHANGE_UNKNOWN，表示沪深全市场，EMT_EXCHANGE_SH表示为上海全市场，EMT_EXCHANGE_SZ表示为深圳全市场
			*   @return                         订阅全市场的分时行情接口调用是否成功，“0”表示接口调用成功，非“0”表示接口调用出错
			*/
			virtual int SubscribeAllMinuteInfo(EMT_EXCHANGE_TYPE exchange_id = EMT_EXCHANGE_UNKNOWN) = 0;

			/**
			*   退订全市场的分时行情
			*   @attention                      需要与订阅全市场分时行情接口配套使用
			*   @param exchange_id              表示当前退订的市场，如果为EMT_EXCHANGE_UNKNOWN，表示沪深全市场，EMT_EXCHANGE_SH表示为上海全市场，EMT_EXCHANGE_SZ表示为深圳全市场
			*   @return                         取消订阅全市场的分时行情接口调用是否成功，“0”表示接口调用成功，非“0”表示接口调用出错
			*/
			virtual int UnSubscribeAllMinuteInfo(EMT_EXCHANGE_TYPE exchange_id = EMT_EXCHANGE_UNKNOWN) = 0;

			/**
			*   订阅分时行情
			*   @attention                      可一次性订阅同一证券交易所的多个合约，无论用户因为何种问题需要重新登录行情服务器，都需要重新订阅
			*   @param exchange_id              交易所代码，如果是SH表示上海全市场，SZ表示深证全市场
			*   @param tickers                  合约代码数组，注意合约代码必须以"\0"结尾，不包括空格
			*   @param count                    需要订阅行情的合约个数
			*   @return                         订阅分时行情接口调用是否成功，"0"表示接口调用成功，非"0"表示接口调用出错
			*/
			virtual int SubscribeMinuteInfo(char* tickers[], int count, EMT_EXCHANGE_TYPE exchange_id = EMT_EXCHANGE_UNKNOWN) = 0;

			/**
			*   退订分时行情
			*   @attention                      可一次性取消订阅同一证券交易所的多个合约，无论用户因为何种问题需要重新登录行情服务器，都需要重新订阅
			*   @param tickers                  合约代码数组，注意合约代码必须以"\0"结尾，不包括空格
			*   @param count                    需要订阅行情的合约个数
			*   @param exchange_id              交易所代码，如果是SH表示上海全市场，SZ表示深证全市场
			*   @return                         取消订阅接口调用是否成功，"0"表示接口调用成功，非"0"表示接口调用出错
			*/
			virtual int UnSubscribeMinuteInfo(char* tickers[], int count, EMT_EXCHANGE_TYPE exchange_id = EMT_EXCHANGE_UNKNOWN) = 0;

			/**
			*   获取所有合约的部分静态信息，包括全市场所有合约的部分静态信息
			*   @param exchange_id              交易所代码，必须提供1-上海 2-深证
			*   @return                         发送查询请求是否成功，"0"表示发送查询请求成功，非"0"表示发送查询请求不成功
			 */
			virtual int QueryAllTickers(EMT_EXCHANGE_TYPE exchange_id = EMT_EXCHANGE_UNKNOWN) = 0;

			/**
			*   获取所有合约的完整静态信息，包括全市场所有合约的完整静态信息
			*   @param exchange_id              交易所代码，必须提供1-上海 2-深证
			*   @return                         发送查询请求是否成功，"0"表示发送查询请求成功，非"0"表示发送查询请求不成功
			 */
			virtual int QueryAllTickersFullInfo(EMT_EXCHANGE_TYPE exchange_id = EMT_EXCHANGE_UNKNOWN) = 0;

			/**
			*   获取最新快照信息
			*	@param tickers					合约ID数组，注意合约代码必须以'\0'结尾，不包含空格
			*	@param count					合约个数，为0表示查询交易所所有合约
			*	@param ticker_type				合约类型
			*   @param exchange_id              交易所代码，必须提供1-上海 2-深证
			*   @return                         发送查询请求是否成功，"0"表示发送查询请求成功，非"0"表示发送查询请求不成功
			 */
			virtual int QueryLatestInfo(char* tickers[], int count, EMT_TICKER_TYPE ticker_type, EMT_EXCHANGE_TYPE exchange_id) = 0;

			/**
			*   获取所有合约的分时快照信息
			*	@param tickers					合约ID数组，注意合约代码必须以'\0'结尾，不包含空格
			*	@param count					合约个数，为0表示查询交易所所有合约
			*	@param ticker_type				合约类型
			*   @param exchange_id              交易所代码，必须提供1-上海 2-深证
			*   @return                         发送查询请求是否成功，"0"表示发送查询请求成功，非"0"表示发送查询请求不成功
			 */
			virtual int QueryMinuteInfo(char* tickers[], int count, EMT_TICKER_TYPE ticker_type, EMT_EXCHANGE_TYPE exchange_id) = 0;

			/**
			*   获取所有合约的历史分时快照信息
			*	@param tickers					合约ID数组，注意合约代码必须以'\0'结尾，不包含空格
			*	@param count					合约个数，为0表示查询交易所所有合约
			*   @param datetime                 历史分时数据的具体日期yyyyMMdd，如：20210101
			*	@param ticker_type				合约类型
			*   @param exchange_id              交易所代码，必须提供1-上海 2-深证
			*   @return                         发送查询请求是否成功，"0"表示发送查询请求成功，非"0"表示发送查询请求不成功
			 */
			virtual int QueryMinHistoryInfo(char* tickers[], int count,int datetime, EMT_TICKER_TYPE ticker_type, EMT_EXCHANGE_TYPE exchange_id) = 0;
			

			/*
			* 获取最新价
			* @param tickers			合约ID数组，注意合约代码必须以'\0'结尾，不包含空格
			* @param count				合约个数，为0表示查询交易所所有合约
			* @param exchange_id		交易所代码，必须提供1-上海 2-深证
			* @return					发送查询请求是否成功，"0"表示发送查询请求成功，非"0"表示发送查询请求不成功
			*/
			virtual int QueryTickersPriceInfo(char* tickers[], int count, EMT_EXCHANGE_TYPE exchange_id) = 0;

			/**
			*   获取API的系统错误
			*   @return							返回的错误信息，可以在Login、Logout、订阅、取消订阅失败时调用，获取失败的原因
			*   @attention						可以在调用api接口失败时调用，例如login失败时
			*/
			virtual EMTRspInfoStruct* GetApiLastError() = 0;

		protected:
			~QuoteApi() {};

		};
	}
}
