#pragma once
/////////////////////////////////////////////////////////////////////////
///@author 东方财富证券股份有限公司
///@file emt_quote_struct.h
///@brief 定义行情业务数据结构
/////////////////////////////////////////////////////////////////////////

#ifndef __EMT_MARKETDATA_H__
#define __EMT_MARKETDATA_H__ extern "C" _declspec(dllimport)

#include "emt_api_data_type.h"
#include <inttypes.h>

#pragma pack(1)  // 内存以1字节为单位对齐

#define MAX_LEVEL_NUM		10                      /// 最大买卖盘数量
#define MAX_LEVEL_ORDERS_NUM	50                  /// 最大价位揭示委托笔数
#define EMT_ERR_MSG_LEN  124                        /// 错误信息的字符串长度

/// 指定的合约
typedef struct _EMTSpecificTickerStruct
{
    /// 交易所代码 
	EMT_EXCHANGE_TYPE exchange_id;
    /// 合约代码（不包含交易所信息）例如"600000"，不带空格，以'\0'结尾 
	char ticker[EMT_TICKER_LEN];
}EMTSpecificTickerStruct;

/// 响应信息
typedef struct _EMTRspInfoStruct
{
    /// 错误代码
	int32_t error_id; 
    /// 错误信息
	char    error_msg[EMT_ERR_MSG_LEN];
}EMTRspInfoStruct;

/// 指数行情结构体
typedef struct _EMTIndexDataStruct
{
    /// 交易所代码
	EMT_EXCHANGE_TYPE exchange_id;
	/// 合约代码(不包含交易所信息)，不带空格，以"\0"结尾
    char ticker[EMT_TICKER_LEN];
    /// 行情时间，格式为YYYYMMDDHHMMSSssss
	int64_t data_time;
    /// 昨日收盘价
	double pre_close_price;
    /// 今日开盘价
	double open_price;
    /// 最新价
	double last_price;
    /// 最高价
	double high_price;
    /// 最低价
	double low_price;
    /// 数量，为总成交量(单位股，与交易所一致)
	int64_t qty;
    /// 成交金额，为总成交金额(单位元，与交易所一致)
	double turnover;

}EMTIndexDataStruct;

/// 基金额外数据结构体
typedef struct _EMTMarketDataFundExData
{
	/// 基金实时参考净值(SH,SZ) 
	double iopv;
	/// ETF申购笔数(SH)	
	int32_t etf_buy_count;
	/// ETF赎回笔数(SH)
	int32_t etf_sell_count;
	/// ETF申购数量(SH)	
	double etf_buy_qty;
	/// ETF申购金额(SH)
	double etf_buy_money;
	/// ETF赎回数量(SH)
	double etf_sell_qty;
	/// ETF赎回金额(SH)
	double etf_sell_money;
	/// 基金T-1日净值(SZ) 
	double pre_iopv;
}EMTMarketDataFundExData;


/// 债券额外数据结构体
typedef struct _EMTMarketDataBondExData
{
	/// 债券加权平均委买价格(SH)
	double ma_bond_bid_price;
	/// 债券加权平均委卖价格(SH)
	double ma_bond_ask_price;
	/// 债券到期收益率(SH)
	double yield_to_maturity;
}EMTMarketDataBondExData;

/// 权证额外数据
typedef struct _EMTMarketDataWarrantExData
{
	/// 权证执行的总数量(SH)
	double total_warrant_exec_qty;
	/// 权证跌停价格（元）(SH)
	double warrant_lower_price;
	/// 权证涨停价格（元）(SH)
	double warrant_upper_price; 
}EMTMarketDataWarrantExData;

/// 期权额外数据
typedef struct _EMTMarketDataOptionExData
{
	/// 波段性中断参考价(SH)
	double auction_price;
	/// 波段性中断集合竞价虚拟匹配量(SH)
	int64_t auction_qty;
	/// 最近询价时间(SH)
	int64_t last_enquiry_time;

	// 期权数据
	/// 昨日持仓量(张)(目前未填写)
	int64_t pre_total_long_positon;
	/// 持仓量(张)(目前未填写)
	int64_t total_long_positon;
	/// 昨日结算价(目前未填写)
	double pre_settl_price;
	/// 今日结算价(目前未填写)
	double settl_price;
}EMTMarketDataOptionExData;

/// 快照行情结构体
typedef struct _EMTMarketDataStruct
{
	/// 交易所代码
	EMT_EXCHANGE_TYPE exchange_id;
	/// 合约代码(不包含交易所信息)，不带空格。以"\0"结尾
	char ticker[EMT_TICKER_LEN];

	// 价格
	/// 最新价
	double last_price;
	/// 昨日收盘价
	double pre_close_price;
	/// 今开盘价
	double open_price;
	/// 最高价
	double high_price;
	/// 最低价
	double low_price;
	/// 今收盘价(SH)
	double close_price;

	// 涨跌停
	/// 涨停价(SZ)
	double upper_limit_price;
	/// 跌停价(SZ)
	double lower_limit_price;	
	/// 行情时间，格式为YYYYMMDDHHMMSSssss
	int64_t data_time;

	// 量额数据
	/// 数量，为总成交量(单位股，与交易所一致)
	int64_t qty;
	/// 成交金额，为总成交金额(单位元，与交易所一致)
	double turnover;
	/// 当日均价=(turnover/qty)	
	double avg_price;

	// 买卖盘
	/// 十档申买价
	double bid[10];
	/// 十档申卖价
	double ask[10];
	/// 十档申买量
	int64_t bid_qty[10];
	/// 十档申卖量
	int64_t ask_qty[10];

	/// 成交笔数
	int64_t trades_count;
	/// 当前交易状态说明(SH)
	char ticker_status[8];

	/// 委托买入总量(SH,SZ)
	int64_t total_bid_qty;
	/// 委托卖出总量(SH,SZ)
	int64_t total_ask_qty;
	/// 加权平均委买价格(SH,SZ)
	double ma_bid_price;
	/// 加权平均委卖价格(SH,SZ)
	double ma_ask_price;

	/// 买入撤单笔数(SH)
	int32_t cancel_buy_count;
	/// 卖出撤单笔数(SH)
	int32_t cancel_sell_count;
	/// 买入撤单数量(SH)
	double cancel_buy_qty;
	/// 卖出撤单数量(SH)
	double cancel_sell_qty;
	/// 买入撤单金额(SH)
	double cancel_buy_money;
	/// 卖出撤单金额(SH)
	double cancel_sell_money;
	/// 买入总笔数(SH)
	int64_t total_buy_count;
	/// 卖出总笔数(SH) 
	int64_t total_sell_count;
	/// 买入委托成交最大等待时间(SH)
	int32_t duration_after_buy;
	/// 卖出委托成交最大等待时间(SH)
	int32_t duration_after_sell;
	/// 买方委托价位数(SH) 
	int32_t num_bid_orders;
	/// 卖方委托价位数(SH)
	int32_t num_ask_orders;
	///  额外数据联合体
	union {
		/// 债券额外数据
		EMTMarketDataBondExData bond;
		/// 基金额外数据
		EMTMarketDataFundExData fund;
		/// 权证额外数据
		EMTMarketDataWarrantExData warrant;
		/// 期权额外数据
		EMTMarketDataOptionExData opt;
	};
	/// 证券类别；1：股票,基金,债券,权证,质押式回购；2：期权；决定了union是哪种数据类型
	EMT_TICKER_TYPE data_type;

}EMTMarketDataStruct;

/// 逐笔委托数据(当前仅适用深交所)
typedef struct _EMTTickByTickEntrust
{
	/// 频道代码
	int32_t channel_no;
	/// 买卖方向：1"：买；"2"：卖；"G"：借入；"F"：出借
	char side;
	/// 订单类别:"1"：市价；"2"：限价；"U"：本方最优
	char ord_type;
	/// 填充字段
	char __filler[2];
	/// 委托序号(在同一个channel_no内唯一，从1开始连续)
	int64_t seq;
	/// 委托价格
	double price;
	/// 委托数量
	int64_t qty;
}EMTTickByTickEntrust;

/// 逐笔成交数据
typedef struct _EMTTickByTickTrade
{
	/// 成交通道(SH)；频道代码(SZ)
	int32_t channel_no;
	/// SH：内外盘标识('B'：主动买； 'S'：主动卖； 'N'：未知)；SZ：成交类别('4'：Cancelled，表示已撤销；'F'：Trade，表示已成交)
	char trade_flag;
	/// 填充字段
	char __filler[3];
	/// 成交序号(SH)；消息记录号(SZ)(在同一个channel_no内唯一，从1开始连续)
	int64_t seq;
	/// 买方订单号(SH)；买方委托索引(SZ)
	int64_t bid_no;
	/// 卖方订单号(SH)；卖方委托索引(SZ)
	int64_t ask_no;
	/// 成交价格(元)
	double price;
	/// 成交量（股票：股；债券：手）
	int64_t qty;
	/// 成交金额（元；仅适用于上交所；等于成交价格*成交数量）
	double money;

}EMTTickByTickTrade;

/// 逐笔数据信息
typedef struct _EMTTickByTickStruct
{
	/// 委托时间or成交时间
	int64_t data_time;
	/// 消息记录号,从1开始
	int64_t seq;
	/// 交易所代码
	EMT_EXCHANGE_TYPE exchange_id;
	/// 合约代码(不包含交易所信息)，不带空格，以"\0"结尾
	char ticker[EMT_TICKER_LEN];
	/// 逐笔类型；"1"：逐笔委托；"2"：逐笔成交
	EMT_TBT_TYPE type;
	
	///  额外数据联合体
	union {
		EMTTickByTickEntrust entrust;
		EMTTickByTickTrade trade;
	};

}EMTTickByTickStruct;

/// 股票行情静态信息
typedef struct _EMTQuoteStaticInfo {
	/// 交易所代码
	EMT_EXCHANGE_TYPE exchange_id;
	/// 合约代码（不包含交易所信息），不带空格，以'\0'结尾
	char ticker[EMT_TICKER_LEN];
	/// 合约名称
	char ticker_name[EMT_TICKER_NAME_LEN];
	/// 合约类型
	EMT_TICKER_TYPE ticker_type;
	/// 昨收盘 
	double  pre_close_price; 
	/// 涨停板价
	double  upper_limit_price;
	/// 跌停板价
	double  lower_limit_price;
	/// 最小变动价位
	double  price_tick;
	/// 合约最小交易量(买)
	int32_t  buy_qty_unit;
	/// 合约最小交易量(卖) 
	int32_t sell_qty_unit;
}EMTQuoteStaticInfo;

/// 股票行情全量静态信息
typedef struct _EMTQuoteFullInfo {
	/// 交易所代码 
	EMT_EXCHANGE_TYPE exchange_id;
	/// 证券代码
	char ticker[EMT_TICKER_LEN];
	/// 证券名称
	char ticker_name[EMT_TICKER_NAME_LEN];
	/// 合约详细类型
	EMT_SECURITY_TYPE security_type;
	/// 合约适当性类别
	EMT_QUALIFICATION_TYPE ticker_qualification_class;
	/// 是否注册制(仅适用创业板股票，创新企业股票及存托凭证)
	bool is_registration;
	/// 是否具有协议控制架构(仅适用创业板股票，创新企业股票及存托凭证)
	bool is_VIE;
	/// 是否尚未盈利(仅适用创业板股票，创新企业股票及存托凭证)
	bool is_noprofit; 
	/// 是否存在投票权差异(仅适用创业板股票，创新企业股票及存托凭证)
	bool is_weighted_voting_rights;
	/// 是否有涨跌幅限制(注：不提供具体幅度，可通过涨跌停价和昨收价来计算幅度)
	bool is_have_price_limit;
	/// 涨停价（仅在有涨跌幅限制时有效）
	double upper_limit_price; 
	/// 跌停价（仅在有涨跌幅限制时有效）
	double lower_limit_price;
	/// 昨收价
	double pre_close_price;
	/// 价格最小变动价位
	double price_tick;
	/// 限价买委托数量上限
	int32_t bid_qty_upper_limit;
	/// 限价买委托数量下限
	int32_t bid_qty_lower_limit;
	/// 限价买数量单位
	int32_t bid_qty_unit;
	/// 限价卖委托数量上限
	int32_t ask_qty_upper_limit; 
	/// 限价卖委托数量下限
	int32_t ask_qty_lower_limit; 
	/// 限价卖数量单位
	int32_t ask_qty_unit;      
	/// 市价买委托数量上限
	int32_t market_bid_qty_upper_limit; 
	/// 市价买委托数量下限 
	int32_t market_bid_qty_lower_limit; 
	/// 市价买数量单位
	int32_t market_bid_qty_unit;
	/// 市价卖委托数量上限
	int32_t market_ask_qty_upper_limit;
	/// 市价卖委托数量下限
	int32_t market_ask_qty_lower_limit;
	/// 市价卖数量单位
	int32_t market_ask_qty_unit;
	/// 保留字段
	uint64_t unknown[4];
}EMTQuoteFullInfo;

/// 订单簿
typedef struct _EMTOrderBookStruct {
	///交易所代码
	EMT_EXCHANGE_TYPE exchange_id;
	/// 合约代码（不包含交易所信息），不带空格，以'\0'结尾
	char ticker[EMT_TICKER_LEN];

	/// 最新价
	double last_price;
	/// 数量，为总成交量
	int64_t qty;          
	/// 成交金额，为总成交金额
	double  turnover;    
	/// 成交笔数
	int64_t trades_count;

	// 买卖盘
	/// 十档申买价
	double bid[10];
	/// 十档申卖价
	double  ask[10];
	/// 十档申买量 
	int64_t bid_qty[10];
	/// 十档申卖量
	int64_t ask_qty[10];
	/// 时间类
	int64_t data_time;
} EMTOrderBookStruct;

/// 现货（股票、基金、债券）和期权分时快照
typedef struct _EMTMinuteInfo {
	/// 交易所代码
	EMT_EXCHANGE_TYPE exchange_type;
	/// 合约类型
	EMT_TICKER_TYPE ticker_type;
	/// 合约代码（不包含交易所信息），不带空格，以'\0'结尾
	char ticker[EMT_TICKER_LEN];
	/// 时间，格式为YYYYMMDDHHMMSSsss
	int64_t data_time;
	/// 最新价
	double last_price;
	/// 一分钟内成交总量，单位：股
	int64_t volume_trade;
	/// 一分钟内成交总金额，单位：元
	double value_trade;
	/// 均价，单位：元
	double avg_price;
}EMTMinuteInfo;

/// 最新价 
typedef struct _EMTTickerPriceInfo
{
	/// 交易所代码
	EMT_EXCHANGE_TYPE exchange_type;
	/// 合约代码（不包含交易所信息），不带空格，以'\0'结尾
	char ticker[EMT_TICKER_LEN];
	/// 最新价
	double last_price;
} EMTTickerPriceInfo;

#pragma pack()			// 恢复默认内存对齐方式

#endif // !__EMT_MARKETDATA_H__