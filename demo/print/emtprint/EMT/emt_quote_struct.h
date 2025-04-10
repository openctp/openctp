#pragma once
/////////////////////////////////////////////////////////////////////////
///@author 东方财富证券股份有限公司
///@file emt_quote_struct.h
///@brief 定义行情业务数据结构
/////////////////////////////////////////////////////////////////////////

#ifndef __EMT_MARKETDATA_H__
#define __EMT_MARKETDATA_H__ extern "C" _declspec(dllimport)
#include <cstdint>
#include <cinttypes>

#include "emt_quote_data_type.h"
#include "sse_hpf_define.h"
#include "sze_hpf_define.h"

#pragma pack(1)  // 内存以1字节为单位对齐

#define MAX_LEVEL_NUM 10         /// 最大买卖盘数量
#define MAX_LEVEL_ORDERS_NUM 50  /// 最大价位揭示委托笔数
#define EMQ_ERR_MSG_LEN 124      /// 错误信息的字符串长度

/// 指定的合约
struct _EMTSpecificTickerStruct {
  /// 交易所代码
  EMQ_EXCHANGE_TYPE exchange_id;
  /// 合约代码（不包含交易所信息）例如"600000"，不带空格，以'\0'结尾
  char ticker[EMQ_TICKER_LEN];
};
using EMTSpecificTickerStruct = struct _EMTSpecificTickerStruct;

/// 指数行情结构体
struct _EMTIndexDataStruct {
  /// 交易所代码
  EMQ_EXCHANGE_TYPE exchange_id;
  /// 合约代码(不包含交易所信息)，不带空格，以"\0"结尾
  char ticker[EMQ_TICKER_LEN];
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
};
using EMTIndexDataStruct = struct _EMTIndexDataStruct;

/// 基金额外数据结构体
struct _EMTMarketDataFundExData {
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
};
using EMTMarketDataFundExData = struct _EMTMarketDataFundExData;

/// 债券额外数据结构体
struct _EMTMarketDataBondExData {
  /// 债券加权平均委买价格(SH)
  double ma_bond_bid_price;
  /// 债券加权平均委卖价格(SH)
  double ma_bond_ask_price;
  /// 债券到期收益率(SH)
  double yield_to_maturity;
};
using EMTMarketDataBondExData = struct _EMTMarketDataBondExData;

/// 权证额外数据
struct _EMTMarketDataWarrantExData {
  /// 权证执行的总数量(SH)
  double total_warrant_exec_qty;
  /// 权证跌停价格（元）(SH)
  double warrant_lower_price;
  /// 权证涨停价格（元）(SH)
  double warrant_upper_price;
};

using EMTMarketDataWarrantExData = struct _EMTMarketDataWarrantExData;

/// 期权额外数据
struct _EMTMarketDataOptionExData {
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
};

using EMTMarketDataOptionExData = struct _EMTMarketDataOptionExData;

/// 港股通额外扩展数据
struct _EMTMarketDataHkExData {
  /// 参考价
  double refer_price;
  /// 按盘价
  double nominal_price;
  /// 买盘上限价
  double buyside_up_limit_price;
  /// 买盘下限价
  double buyside_low_limit_price;
  /// 卖盘上限价
  double sellside_up_limit_price;
  /// 卖盘下限价
  double sellside_low_limit_price;
  /// 冷静期开始时间  HHmmssSSS
  int32_t complex_event_start_time;
  /// 冷静期结束时间 HHmmssSSS
  int32_t complex_event_end_time;
};

using EMTMarketDataHkExData = struct _EMTMarketDataHkExData;

/// 北交所股转额外扩展数据
struct _EMTMarketDataBJGZExData {
  /// 静态市盈率
  double LYR;
  /// 动态市盈率
  double TTM;
  /// 价格升跌一 较昨日收盘价涨跌
  double price_change1;
  /// 价格涨跌二 较上一笔成交涨跌
  double price_change2;
  /// 合约持仓量
  int64_t open_interest;
  /// 第一位 char 交易状态‘N’表示正常状态；‘Y’
  /// 表示首日挂牌/上市；‘D’表示新增股票交易；‘I’表示询价；‘F’表示申购 第二位
  /// char 证券级别
  /// ‘T’表示对应证券是挂牌/上市公司股票；‘B’表示对应证券是两网公司及退市公司股票；‘O’表示对应证券是仅提供行权功能的期权；‘P’表示对应证券是持有人数存在
  /// 200 人限制的证券;(优先股)‘R’表示对应证券是其他类型的业务；
  ///    ‘F’表示是发行业务;’C’表示对应证券是提供协议转让的可转换公司债券。
  /// 第三位 char 交易类型  ‘T’表示协议交易方式； *
  /// ‘M’表示做市交易方式；‘B’表示集合竞价+连续竞价交易方式； *
  /// ‘C’表示集合竞价交易方式；‘P’表示发行方式，‘O’表示其他类型。 第四位 char  *
  /// 停牌标志  *
  /// ‘F’表示正常交易；‘T’表示停牌，不接受申报；‘H’表示停牌，接受申报。 第五位
  /// char
  /// ‘0’-基础层，‘1’-创新层，‘2’-北交所。对于优先股、可转债、指数等无市场层级的，本字段填空格。(预留)
  char ticker_relevant_info[8];
};
using EMTMarketDataBJGZExData = struct _EMTMarketDataBJGZExData;

/// 快照行情结构体

struct _EMTMarketDataStruct {
  /// 交易所代码
  EMQ_EXCHANGE_TYPE exchange_id;
  /// 合约代码(不包含交易所信息)，不带空格。以"\0"结尾
  char ticker[EMQ_TICKER_LEN];

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
    /// 港股额外数据
    EMTMarketDataHkExData hk;
    /// 北交所股转额外数据
    EMTMarketDataBJGZExData bjgz;
  };
  /// 证券类别；1：股票,基金,债券,权证,质押式回购；2：期权；决定了union是哪种数据类型
  EMQ_TICKER_TYPE data_type;
};
using EMTMarketDataStruct = struct _EMTMarketDataStruct;

/// 股票行情静态信息
struct _EMTQuoteStaticInfo {
  /// 交易所代码
  EMQ_EXCHANGE_TYPE exchange_id;
  /// 合约代码（不包含交易所信息），不带空格，以'\0'结尾
  char ticker[EMQ_TICKER_LEN];
  /// 合约名称
  char ticker_name[EMQ_TICKER_NAME_LEN];
  /// 合约类型
  EMQ_TICKER_TYPE ticker_type;
  /// 昨收盘
  double pre_close_price;
  /// 涨停板价
  double upper_limit_price;
  /// 跌停板价
  double lower_limit_price;
  /// 最小变动价位
  double price_tick;
  /// 合约最小交易量(买)
  int32_t buy_qty_unit;
  /// 合约最小交易量(卖)
  int32_t sell_qty_unit;
};
using EMTQuoteStaticInfo = struct _EMTQuoteStaticInfo;

/// 股票行情全量静态信息
using EMTQuoteFullInfo = struct _EMTQuoteFullInfo {
  /// 交易所代码
  EMQ_EXCHANGE_TYPE exchange_id;
  /// 证券代码
  char ticker[EMQ_TICKER_LEN];
  /// 证券名称
  char ticker_name[EMQ_TICKER_NAME_LEN];
  /// 合约详细类型
  EMQ_SECURITY_TYPE security_type;
  /// 合约适当性类别
  EMQ_QUALIFICATION_TYPE ticker_qualification_class;
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
};

/// 最新价
struct _EMTTickerPriceInfo {
  /// 交易所代码
  EMQ_EXCHANGE_TYPE exchange_type;
  /// 合约代码（不包含交易所信息），不带空格，以'\0'结尾
  char ticker[EMQ_TICKER_LEN];
  /// 最新价
  double last_price;
};
using EMTTickerPriceInfo = struct _EMTTickerPriceInfo;

/// 港股静态信息数据
struct _EMTHKStaticInfo {
  /// 交易所代码
  EMQ_EXCHANGE_TYPE exchange_type;

  /// 证券类型
  EMQ_TICKER_TYPE ticker_type;

  /// 合约代码（不包含交易所信息），不带空格，以'\0'结尾
  char ticker[EMQ_HK_TICKER_LEN];

  /// ISIN 代码
  char isin_ticker[EMQ_TICKER_LEN];

  /// 英文证券名简称
  char short_form_ticke_en[EMQ_TICKER_LEN];

  /// 市场种类
  // MAIN- 主板 GEM-创业板
  // ETS-扩充交易证券 NASD-Nasdaq AMX 市场
  char market_type[4];

  /// 证券类别
  /// BOND	Bond 债券
  /// BWRT	Basket Warrant 一篮子权证
  /// EQTY	Equity  股本
  /// TRST	Trust  信托
  /// WRNT	Warrant  权证
  char symbol_type[4];

  /// 辅助证券代码  权证的正股代码
  char assist_symbol[5];

  /// 货币种类
  /// 港币：HKD； 美元：USD；人民币：CNY；澳币：AUD；加币：CAD ;
  /// 日圆：JPY;新加坡币：SGD ; 英镑 : GBP ; 欧元：EUR
  char currency_type[3];

  /// 货币单位
  /// 货币单位表示前收盘价格字段的单位，当货币单位取值为 0
  /// 时，前收盘价格=前收盘价格字段取值×10 的 0 次幂，当货币单位取值为 1
  /// 时，前收盘价格=前收盘价格字段取值×10 的 1 次幂，依次类推。
  char currency_unit;

  /// 面值货币种类 港币：HKD； 美元：USD；人民币：CNY
  char currency_denomination_type[3];

  /// 保留字段
  char reserved1[4];

  /// 上市日期 YYYYMMDD
  char issueDate[8];

  /// 买卖单位
  /// 整手数
  /// 买卖申报数量必须是该字段的整数倍。
  int32_t round_lot;

  /// 保留字段
  char reserved2[4];

  /// 面值 股票面值 单位：元
  double denomination;

  /// 利息  对于债券填写交收日利息 仅针对利息通过 CCASS 系统来结算的债券
  double interest;

  /// 前收盘价 当日除权（息）后收盘价格
  double pre_close_price;

  ///  保留字段
  char reserverd3[16];

  /// 第一位有效Y表示停牌 N表示非停牌
  /// 第二位有效 Y表示参与市场波动调节机制 N表示不参与
  /// 第三位有效 Y表示参与收市竞价交易时段 N表示不参与
  /// 第四位有效 Y表示参与开市前时段优化 N表示不参与
  /// 第五至六位有效 价差代码,不足两位左补零。
  /// 第七至八位有效 市场波动调节机制类别
  char text[64];

  /// 中文证券简称 GBK编码
  char ticker_name_zh[64];

  /// 英文证券全称
  char ticker_name_en[64];
};
using EMTHKStaticInfo = struct _EMTHKStaticInfo;

/// 股转静态信息数据
struct _EMTBJGZStaticInfo {
  /// 交易所代码
  EMQ_EXCHANGE_TYPE exchange_type;
  /// 证券类型
  EMQ_TICKER_TYPE ticker_type;
  /// 合约代码（不包含交易所信息），不带空格，以'\0'结尾
  char ticker[8];
  /// char[8] 证券简称 GBK
  char ticker_name[8];
  /// char[6]  行业种类
  /// 对于股票：左边第一位为字母，表示门类；左边第二、三位为数字，表示大类；其他位为空。
  /// 具体定义请参见中国证监会颁布的《上市公司行业分类指引》
  char industry_type[6];
  /// char[2]
  /// 货币种类‘00’人民币，‘02’美元
  char currency_type[2];
  /// double 面值
  /// 对于股票，每股面值为 1元；对于可转债，每张面值为 100 元
  double denomination;
  /// int64 总股本
  int64_t total_share_capital;
  /// int64 非限售股本
  int64_t nonrestricted_share_capital;
  /// double 上年每股收益
  /// 对于股票，存放上年每股利润
  double last_year_eps;
  ///  double 今年每股收益  预留
  double this_year_eps;
  /// double 经手费率
  /// 为全国股转公司及北交所本身收取或向投资者代收的交易费用费率，该费率仅为参考，实际费率以相关收费管理规定为准
  double transaction_rate;
  /// double 印花税率
  double stamp_duty_rate;
  /// double 过户费率
  double transfer_rate;
  /// int32 挂牌日期 CCYYMMDD
  int32_t list_date;
  /// int32  起息日 CCYYMMDD
  /// 对于优先股和可转债，该字段存放其起息日；对于要约业务，该字段存放其要约开始日期；对于发行业务，该字段存放其询价开始日期
  int32_t start_date;
  /// int32 到期日 CCYYMMDD
  /// 对于要约业务，该字段存放其要约结束日期；对于发行业务，该字段存放其询价结束日期
  int32_t end_date;
  /// int32  每笔限量 申报数量上限
  int32_t declare_upper_limit;
  /// int32 买数量单位
  int32_t buy_quantity_unit;
  /// int32 卖数量单位
  int32_t sell_quantity_unit;
  /// int32 最小申报数量
  /// 存放除做市商外其他投资者在正常交易时段的每笔最小申报数量
  int32_t min_declare_count;
  /// int32 限价参数类型
  /// 0 表示 限价参数的值为价格；1 为比例数
  int32_t param_type;
  /// double 价格挡位
  /// 申报价格的最小变动单位，例如 0.01 元 RMB。
  double tick_size;
  /// double 首笔交易限价参数
  /// 具体参考北交所接口文档
  double first_trade_limit_price_param;
  /// double 后续交易限价参数
  /// 具体参考北交所接口文档
  double sub_trade_limit_price_param;
  /// double 涨停价格
  /// 为申报有效价格范围的价格上限，如果 =99999.99（币种为人民币）或
  /// 99999.999（币种为美元），则相应的证券没有涨幅限制。对于要约业务，存放其收购/回购价格
  double upper_limit_price;
  /// double 跌停价格
  /// 为申报有效价格范围的价格下限
  /// 如果=0.000，则相应的证券没有跌幅限制。对于要约业务，存放其收购/回购价格
  double lower_limit_price;
  /// double 折合比例
  /// 对于优先股，该字段存放其票面股息率（%）；对于可转债，该字段存放票面利率（%）。
  double conv_ratio;
  /// char 成分股标志 预留
  char constituent_stock_flag;
  /// char 交易状态
  /// ‘N’表示正常状态；‘Y’表示首日挂牌/上市；‘D’表示新增股票交易；‘I’表示询价；‘F’表示申购
  char trade_status;
  /// char 证券级别
  /// ‘T’表示对应证券是挂牌/上市公司股票；‘B’表示对应证券是两网公司及退市公司股票；
  /// ‘O’表示对应证券是仅提供行权功能的期权；‘P’表示对应证券是持有人数存在 200
  /// 人限制的证券;(优先股) ‘R’表示对应证券是其他类型的业务；
  /// ‘F’表示是发行业务;’C’表示对应证券是提供协议转让的可转换公司债券。
  char symbol_type;
  ///  char 交易类型
  /// ‘T’表示协议交易方式；
  /// ‘M’表示做市交易方式；‘B’表示集合竞价+连续竞价交易方式；
  /// ‘C’表示集合竞价交易方式；‘P’表示发行方式，‘O’表示其他类型。
  char trade_type;
  /// char 停牌标志
  /// ‘F’表示正常交易；‘T’表示停牌，不接受申报；‘H’表示停牌，接受申报。
  char suspend_flag;
  ///  char 除权除息标志
  /// ‘N’表示正常状态；‘E’表示除权；‘D’表示除息；‘A’表示除权除息。
  char ex_divide_flag;
  /// char 网络投票标志 预留
  char network_note_flag;
  /// char 市场层级
  /// ‘0’-基础层，‘1’-创新层，‘2’-北交所。对于优先股、可转债、指数等无市场层级的，本字段填空格。(预留字段)
  char market_level;
  ///  char[2] 交易场所 预留
  char trading_ring[2];
  /// char 是否为融资标的 (预留字段)
  /// ‘Y’-是，‘N’-否
  char is_financing;
  /// char 是否为融券标的 (预留字段)
  /// ‘Y’-是，‘N’-否
  char is_securities_loan;
  /// char 是否当日可融资 (预留字段)
  /// ‘Y’-是，‘N’-否
  char is_financing_today;
  /// char 是否当日可融券 (预留字段)
  /// ‘Y’-是，‘N’-否
  char is_securities_loan_today;
  /// 预留字段
  char reserved[2];
  /// int32交易单位 申报数量的单位
  int32_t trade_unit;
  /// char[4] 其他业务状态
  /// 详见北交所NQXX接口文档
  char other_status[4];

  /// int32 做市商数量
  /// 对于有做市商提供做市服务的证券揭示其做市商数量，对于没有做市商提供做市服务的证券该字段的值默认为
  /// 0
  int32_t market_maker_count;
  /// int32
  /// 记录更新时间 HHMMSS
  int32_t update_time;
  /// double 大宗交易价格上限 预留
  double block_trade_upper_limit_price;
  /// double 大宗交易价格下限 预留
  double block_trade_lower_limit_price;
};
using EMTBJGZStaticInfo = struct _EMTBJGZStaticInfo;

/// 逐笔重建数据
struct _EMTRebuildData {
  union {
    sze_hpf_order_pkt sz_order;            /// /**< 深市逐笔委托*/
    sze_hpf_exe_pkt sz_exe;                /// /**< 深市逐笔成交*/
    sze_hpf_bond_order_pkt sz_bond_order;  /// /**< 深市债券逐笔委托*/
    sze_hpf_bond_exe_pkt sz_bond_exe;      /// /**< 深市债券逐笔成交*/

    sse_hpf_order_pkt sh_order;          /// /**< 沪市逐笔委托*/
    sse_hpf_exe_pkt sh_exe;              /// /**< 沪市逐笔成交*/
    sse_msg_bond_tick_pkt sh_bond_tick;  /// /**< 沪市债券逐笔*/
  };
};
using EMTRebuildData = struct _EMTRebuildData;

struct _EMTRebuildRespData {
  int8_t data_type;
  uint16_t channel;
  uint64_t sequence;
  uint64_t request_id;
  EMTRebuildData* data;
};
using EMTRebuildRespData = struct _EMTRebuildRespData;

/// 响应错误结构体
struct _EMTRspInfoStruct {
  /// 错误代码
  int32_t error_id;
  /// 错误信息
  char error_msg[EMQ_ERR_MSG_LEN];
};
using EMTRspInfoStruct = struct _EMTRspInfoStruct;

#pragma pack()  // 恢复默认内存对齐方式

#endif  // !__EMT_MARKETDATA_H__