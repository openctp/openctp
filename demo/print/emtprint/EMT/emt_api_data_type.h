/////////////////////////////////////////////////////////////////////////
///@author 东方财富证券股份有限公司
///@file emt_api_data_type.h
///@brief 定义兼容数据基本类型
/////////////////////////////////////////////////////////////////////////
#ifndef _EMT_API_DATA_TYPE_H_
#define _EMT_API_DATA_TYPE_H_

#include <inttypes.h>

#pragma pack(1)

///错误信息的字符串长度
#define EMT_ERR_MSG_LEN             124
/// 可交易日字符串长度
#define EMT_TRADING_DAY_LEN         9
/// 存放证券代码的字符串长度
#define EMT_TICKER_LEN              16
/// 存放证券名称的字符串长度
#define EMT_TICKER_NAME_LEN         64
/// 本地报单编号的字符串长度
#define EMT_LOCAL_ORDER_LEN         11
/// 交易所单号的字符串长度
#define EMT_ORDER_EXCH_LEN          17
/// 成交执行编号的字符串长度
#define EMT_EXEC_ID_LEN             18
/// 交易所交易员代码字符串长度
#define EMT_BRANCH_PBU_LEN          7
/// 用户资金账户的字符串长度
#define EMT_ACCOUNT_NAME_LEN        16
/// 信用业务合约负债编号长度
#define EMT_CREDIT_DEBT_ID_LEN      33
/// IP地址的字符串长度
#define EMT_INET_ADDRESS_STR_LEN    64
/// MAC地址的字符串长度
#define EMT_MAC_ADDRESS_LEN         16
/// 硬盘序列号的字符串长度
#define EMT_HARDDISK_SN_LEN         24
/// MacOS系统序列号的字符串长度
#define EMT_MACOS_SNO_LEN           21
///用户资金账户的密码字符串长度
#define EMT_ACCOUNT_PASSWORD_LEN    64

/// 期权组合策略最多腿数
#define EMT_STRATEGE_LEG_NUM        4
/// 期权组合策略代码字符串长度
#define EMT_STRATEGY_ID_LEN         10
/// 期权组合策略名称字符串长度
#define EMT_STRATEGY_NAME_LEN       32
/// 期权组合策略组合编码字符串长度
#define EMT_SECONDARY_ORDER_ID_LEN  18

/// 期权合约可支持的组合策略列表字符串长度
#define EMT_CNTRT_COMB_STRA_LIST_LEN         2048

/////////////////////////////////////////////////////////////////////////
///@brief EMT_LOG_LEVEL是日志输出级别类型
/////////////////////////////////////////////////////////////////////////
typedef enum EMT_LOG_LEVEL
{
    EMT_LOG_LEVEL_FATAL,     ///<严重错误级别
    EMT_LOG_LEVEL_ERROR,     ///<错误级别
    EMT_LOG_LEVEL_WARNING,   ///<警告级别
    EMT_LOG_LEVEL_INFO,      ///<info级别
    EMT_LOG_LEVEL_DEBUG,     ///<debug级别
    EMT_LOG_LEVEL_TRACE      ///<trace级别
}EMT_LOG_LEVEL;

/////////////////////////////////////////////////////////////////////////
///@brief EMT_PROTOCOL_TYPE是通讯传输协议方式
/////////////////////////////////////////////////////////////////////////
typedef enum EMT_PROTOCOL_TYPE
{
    EMT_PROTOCOL_TCP = 1,        ///<采用TCP方式传输
    EMT_PROTOCOL_UDP = 2,        ///<采用UDP方式传输
    EMT_PROTOCOL_UNKNOWN = 9     ///<未知传输协议
}EMT_PROTOCOL_TYPE;

/////////////////////////////////////////////////////////////////////////
///@brief EMT_EXCHANGE_TYPE是交易所类型，行情里使用
/////////////////////////////////////////////////////////////////////////
typedef enum EMT_EXCHANGE_TYPE
{
    EMT_EXCHANGE_SH = 1,        ///<上证
    EMT_EXCHANGE_SZ,            ///<深证
    EMT_EXCHANGE_BJ,            ///<北京证券交易所
    EMT_EXCHANGE_UNKNOWN = 100  ///<不存在的交易所类型
}EMT_EXCHANGE_TYPE;

//////////////////////////////////////////////////////////////////////////
///@brief EMT_MARKET_TYPE市场类型，交易里使用
//////////////////////////////////////////////////////////////////////////
typedef enum EMT_MARKET_TYPE
{
    EMT_MKT_INIT = 0,      ///<初始化值或者未知
    EMT_MKT_SZ_A = 1,      ///<深圳A股
    EMT_MKT_SH_A,          ///<上海A股
    EMT_MKT_SZ_HK_CONNECT, ///<深港通(深港股票市场交易互联互通机制)
    EMT_MKT_SH_HK_CONNECT, ///<沪港通(沪港股票市场交易互联互通机制)
    EMT_MKT_BJ_A,          ///<北京A股
    EMT_MKT_UNKNOWN = 99   ///<未知交易市场类型
}EMT_MARKET_TYPE;

/////////////////////////////////////////////////////////////////////////
///@brief EMT_PRICE_TYPE是价格类型
/////////////////////////////////////////////////////////////////////////
typedef enum EMT_PRICE_TYPE
{
    EMT_PRICE_LIMIT = 1,           ///<限价单-沪 / 深 / 沪期权 / 深期权 （除普通股票业务外，其余未特指的业务均使用此种类型）
    EMT_PRICE_BEST_OR_CANCEL,      ///<即时成交剩余转撤销，市价单-深 / 沪期权 / 深期权
    EMT_PRICE_BEST5_OR_LIMIT,      ///<最优五档即时成交剩余转限价，市价单-沪
    EMT_PRICE_BEST5_OR_CANCEL,     ///<最优五档即时成交剩余转撤销，市价单-沪深 / 深期权
    EMT_PRICE_ALL_OR_CANCEL,       ///<全部成交或撤销,市价单-深 / 沪期权 / 深期权
    EMT_PRICE_FORWARD_BEST,        ///<本方最优，市价单-沪 / 深 / 深期权
    EMT_PRICE_REVERSE_BEST_LIMIT,  ///<对方最优剩余转限价，市价单-沪 / 深 / 沪期权 / 深期权
    EMT_PRICE_LIMIT_OR_CANCEL,     ///<期权限价申报FOK
    EMT_PRICE_HK_LIMIT_BIDDING,    ///<港股通竞价限价
    EMT_PRICE_HK_LIMIT_ENHANCED,   ///<港股通增强限价
    EMT_PRICE_TYPE_UNKNOWN,        ///<未知或者无效价格类型
}EMT_PRICE_TYPE;

/////////////////////////////////////////////////////////////////////////
///@brief EMT_DEBT_TYPE是合约类型
/////////////////////////////////////////////////////////////////////////
typedef enum EMT_DEBT_TYPE
{
    EMT_DEBT_TYPE_MONEY = 0,           ///融资
    EMT_DEBT_TYPE_STOCK,               ///融券
    EMT_DEBT_TYPE_UNKNOWN,               ///未知
}EMT_DEBT_TYPE;

/////////////////////////////////////////////////////////////////////////
///@brief EMT_SIDE_TYPE是买卖方向类型
/////////////////////////////////////////////////////////////////////////
typedef uint8_t EMT_SIDE_TYPE;

///买（新股申购，ETF买，配股，信用交易中担保品买）
#define EMT_SIDE_BUY            1
///卖（逆回购，ETF卖，信用交易中担保品卖）
#define EMT_SIDE_SELL           2
///申购
#define EMT_SIDE_PURCHASE       7
///赎回
#define EMT_SIDE_REDEMPTION     8
///拆分
#define EMT_SIDE_SPLIT          9
///合并
#define EMT_SIDE_MERGE          10
///备兑
#define EMT_SIDE_COVER          11
///改版之后的side锁定（对应开平标识为开）/解锁（对应开平标识为平）
#define EMT_SIDE_FREEZE         12
/// 融资买入
#define EMT_SIDE_MARGIN_TRADE    21
/// 融券卖出
#define EMT_SIDE_SHORT_SELL        22
/// 卖券还款
#define EMT_SIDE_REPAY_MARGIN    23
/// 买券还券
#define EMT_SIDE_REPAY_STOCK    24
/// 现金还款（不放在普通订单协议，另加请求和查询协议）
//#define EMT_SIDE_CASH_REPAY_MARGIN    25
/// 现券还券
#define EMT_SIDE_STOCK_REPAY_STOCK    26
/// 余券划转
#define EMT_SIDE_SURSTK_TRANS       27
/// 担保品转入
#define EMT_SIDE_GRTSTK_TRANSIN     28
/// 担保品转出
#define EMT_SIDE_GRTSTK_TRANSOUT    29

///组合策略的组合
#define EMT_SIDE_OPT_COMBINE        31
///组合策略的拆分
#define EMT_SIDE_OPT_SPLIT          32
///组合策略的管理员强制拆分
#define EMT_SIDE_OPT_SPLIT_FORCE    33
///组合策略的交易所强制拆分
#define EMT_SIDE_OPT_SPLIT_FORCE_EXCH    34

///未知或者无效买卖方向
#define EMT_SIDE_UNKNOWN        50


/////////////////////////////////////////////////////////////////////////
///@brief EMT_POSITION_EFFECT_TYPE是开平标识类型
/////////////////////////////////////////////////////////////////////////
typedef uint8_t EMT_POSITION_EFFECT_TYPE;

/// 初始值或未知值开平标识，除期权外，均使用此值
#define EMT_POSITION_EFFECT_INIT                0
/// 开
#define EMT_POSITION_EFFECT_OPEN                1
/// 平
#define EMT_POSITION_EFFECT_CLOSE               2
/// 强平
#define EMT_POSITION_EFFECT_FORCECLOSE          3
/// 平今
#define EMT_POSITION_EFFECT_CLOSETODAY          4
/// 平昨
#define EMT_POSITION_EFFECT_CLOSEYESTERDAY      5
/// 强减
#define EMT_POSITION_EFFECT_FORCEOFF            6
/// 本地强平
#define EMT_POSITION_EFFECT_LOCALFORCECLOSE     7
/// 信用业务追保强平
#define EMT_POSITION_EFFECT_CREDIT_FORCE_COVER  8
/// 信用业务清偿强平
#define EMT_POSITION_EFFECT_CREDIT_FORCE_CLEAR  9
/// 信用业务合约到期强平
#define EMT_POSITION_EFFECT_CREDIT_FORCE_DEBT   10
/// 信用业务无条件强平
#define EMT_POSITION_EFFECT_CREDIT_FORCE_UNCOND 11
/// 未知的开平标识类型
#define EMT_POSITION_EFFECT_UNKNOWN             12


/////////////////////////////////////////////////////////////////////////
///@brief EMT_ORDER_ACTION_STATUS_TYPE是报单操作状态类型
/////////////////////////////////////////////////////////////////////////
typedef enum EMT_ORDER_ACTION_STATUS_TYPE
{
    EMT_ORDER_ACTION_STATUS_SUBMITTED = 1,    ///<已经提交
    EMT_ORDER_ACTION_STATUS_ACCEPTED,        ///<已经接受
    EMT_ORDER_ACTION_STATUS_REJECTED        ///<已经被拒绝
}EMT_ORDER_ACTION_STATUS_TYPE;

/////////////////////////////////////////////////////////////////////////
///@brief EMT_ORDER_STATUS_TYPE是报单状态类型
/////////////////////////////////////////////////////////////////////////
typedef enum EMT_ORDER_STATUS_TYPE
{
    EMT_ORDER_STATUS_INIT = 0,                ///<初始化
    EMT_ORDER_STATUS_ALLTRADED = 1,           ///<全部成交
    EMT_ORDER_STATUS_PARTTRADEDQUEUEING,      ///<部分成交
    EMT_ORDER_STATUS_PARTTRADEDNOTQUEUEING,   ///<部分撤单
    EMT_ORDER_STATUS_NOTRADEQUEUEING,         ///<未成交
    EMT_ORDER_STATUS_CANCELED,                ///<已撤单
    EMT_ORDER_STATUS_REJECTED,                ///<已拒绝
    EMT_ORDER_STATUS_UNKNOWN                  ///<未知订单状态
}EMT_ORDER_STATUS_TYPE;

/////////////////////////////////////////////////////////////////////////
///@brief EMT_ORDER_SUBMIT_STATUS_TYPE是报单提交状态类型
/////////////////////////////////////////////////////////////////////////
typedef enum EMT_ORDER_SUBMIT_STATUS_TYPE
{
    EMT_ORDER_SUBMIT_STATUS_INIT = 0,              ///<订单初始状态
    EMT_ORDER_SUBMIT_STATUS_INSERT_SUBMITTED = 1, ///<订单已经提交
    EMT_ORDER_SUBMIT_STATUS_INSERT_ACCEPTED,      ///<订单已经被接受
    EMT_ORDER_SUBMIT_STATUS_INSERT_REJECTED,      ///<订单已经被拒绝
    EMT_ORDER_SUBMIT_STATUS_CANCEL_SUBMITTED,      ///<撤单已经提交
    EMT_ORDER_SUBMIT_STATUS_CANCEL_REJECTED,      ///<撤单已经被拒绝
    EMT_ORDER_SUBMIT_STATUS_CANCEL_ACCEPTED          ///<撤单已经被接受
} EMT_ORDER_SUBMIT_STATUS_TYPE;

/////////////////////////////////////////////////////////////////////////
///@brief EMT_TE_RESUME_TYPE是公有流（订单响应、成交回报）重传方式
/////////////////////////////////////////////////////////////////////////
typedef enum EMT_TE_RESUME_TYPE
{
    EMT_TERT_RESTART = 0,    ///<从本交易日开始重传
    EMT_TERT_RESUME,        ///<从从上次收到的续传（暂未支持）
    EMT_TERT_QUICK            ///<只传送登录后公有流（订单响应、成交回报）的内容
}EMT_TE_RESUME_TYPE;

//////////////////////////////////////////////////////////////////////////
///@brief ETF_REPLACE_TYPE现金替代标识定义
//////////////////////////////////////////////////////////////////////////
typedef enum ETF_REPLACE_TYPE
{
    ERT_CASH_FORBIDDEN = 0,             ///<禁止现金替代
    ERT_CASH_OPTIONAL,                  ///<可以现金替代
    ERT_CASH_MUST,                      ///<必须现金替代
    EPT_INVALID = 9                     ///<无效值
}ETF_REPLACE_TYPE;

//////////////////////////////////////////////////////////////////////////
///@brief EMT_TICKER_TYPE证券类型
//////////////////////////////////////////////////////////////////////////
typedef enum EMT_TICKER_TYPE
{
    EMT_TICKER_TYPE_STOCK = 0,            ///<普通股票
    EMT_TICKER_TYPE_INDEX,                ///<指数
    EMT_TICKER_TYPE_FUND,                 ///<基金
    EMT_TICKER_TYPE_BOND,                 ///<债券
    EMT_TICKER_TYPE_OPTION,               ///<期权
    EMT_TICKER_TYPE_TECH_STOCK,           ///<科创板股票（上海）
    EMT_TICKER_TYPE_REPURCHASE,           ///<质押式回购
    EMT_TICKER_TYPE_WARRANT,              ///<权证
    EMT_TICKER_TYPE_UNKNOWN               ///<未知类型

}EMT_TICKER_TYPE;

//////////////////////////////////////////////////////////////////////////
///@brief EMT_BUSINESS_TYPE_EXT证券业务扩展类型
//////////////////////////////////////////////////////////////////////////
typedef uint8_t EMT_BUSINESS_TYPE_EXT;

#define EMT_BUSINESS_TYPE_CASH                                  0         ///<普通股票业务（股票买卖，ETF买卖，沪市交易型货币基金等）
#define EMT_BUSINESS_TYPE_IPOS                                  1         ///<新股申购业务（对应的price type需选择限价类型）
#define EMT_BUSINESS_TYPE_REPO                                  2         ///<回购业务（国债逆回购业务对应的price type填为限价，side填为卖）
#define EMT_BUSINESS_TYPE_ETF                                   3         ///<ETF申赎业务
#define EMT_BUSINESS_TYPE_MARGIN                                4         ///<融资融券业务
#define EMT_BUSINESS_TYPE_DESIGNATION                           5         ///<转托管（未支持）
#define EMT_BUSINESS_TYPE_ALLOTMENT                             6         ///<配股业务（对应的price type需选择限价类型,side填为买）
#define EMT_BUSINESS_TYPE_STRUCTURED_FUND_PURCHASE_REDEMPTION   7         ///<分级基金申赎业务
#define EMT_BUSINESS_TYPE_STRUCTURED_FUND_SPLIT_MERGE           8         ///<分级基金拆分合并业务
#define EMT_BUSINESS_TYPE_MONEY_FUND                            9         ///<货币基金申赎业务（暂未支持，沪市交易型货币基金的买卖请使用普通股票业务）
#define EMT_BUSINESS_TYPE_OPTION                                10        ///<期权业务
#define EMT_BUSINESS_TYPE_EXECUTE                               11        ///<行权
#define EMT_BUSINESS_TYPE_FREEZE                                12        ///<锁定解锁
#define EMT_BUSINESS_TYPE_OPTION_COMBINE                        13        ///<期权组合策略 组合和拆分业务
#define EMT_BUSINESS_TYPE_FIXPRICE                              14        ///<盘后固定定价交易
#define EMT_BUSINESS_TYPE_EXECUTE_COMBINE                       15        ///<期权行权合并业务
#define EMT_BUSINESS_TYPE_BES_OFFER                             16        ///<可转换债转股
#define EMT_BUSINESS_TYPE_OTC_BOOKKEEPING                       17        ///<场外簿记
#define EMT_BUSINESS_TYPE_UNKNOWN                               255       ///<未知类型

//////////////////////////////////////////////////////////////////////////
///@brief EMT_ACCOUNT_TYPE账户类型
//////////////////////////////////////////////////////////////////////////
typedef enum EMT_ACCOUNT_TYPE
{
    EMT_ACCOUNT_NORMAL = 0,    ///<普通账户
    EMT_ACCOUNT_CREDIT,        ///<信用账户
    EMT_ACCOUNT_DERIVE,        ///<衍生品账户
    EMT_ACCOUNT_UNKNOWN        ///<未知账户类型
}EMT_ACCOUNT_TYPE;

/////////////////////////////////////////////////////////////////////////
///@brief EMT_QUOTA_TRANSFER_TYPE是融资信用额度调拨方向类型
/////////////////////////////////////////////////////////////////////////
typedef enum EMT_QUOTA_TRANSFER_TYPE
{
    EMT_STK_QUOTA_TRANSFER_OUT = 0,        ///<融券额度划出
    EMT_STK_QUOTA_TRANSFER_IN,             ///<融券额度划入
    EMT_FUND_QUOTA_TRANSFER_OUT,           ///<融资额度划出 暂不支持
    EMT_FUND_QUOTA_TRANSFER_IN,            ///<融资额度划入 暂不支持
    EMT_QUOTA_TRANSFER_UNKNOWN             ///<未知类型
}EMT_QUOTA_TRANSFER_TYPE;

/////////////////////////////////////////////////////////////////////////
///@brief EMT_QUOTA_OPER_STATUS 融资融券额度调拨操作结果
/////////////////////////////////////////////////////////////////////////
typedef enum EMT_QUOTA_OPER_STATUS {
    EMT_QUOTA_OPER_PROCESSING = 0,     ///<EMT已收到，正在处理中
    EMT_QUOTA_OPER_SUCCESS,            ///<成功
    EMT_QUOTA_OPER_FAILED,             ///<失败
    EMT_QUOTA_OPER_SUBMITTED,          ///<已提交到对应核心处理
    EMT_QUOTA_OPER_UNKNOWN             ///<未知
}EMT_QUOTA_OPER_STATUS;

/////////////////////////////////////////////////////////////////////////
///@brief EMT_FUND_TRANSFER_TYPE是资金流转方向类型
/////////////////////////////////////////////////////////////////////////
typedef enum EMT_FUND_TRANSFER_TYPE
{
    EMT_FUND_TRANSFER_OUT = 0,        ///<转出 从EMT转出到柜台
    EMT_FUND_TRANSFER_IN,             ///<转入 从柜台转入EMT
    EMT_FUND_INTER_TRANSFER_OUT,      ///<跨节点转出 从本EMT节点1，转出到对端EMT节点2，EMT服务器之间划拨，只能跨账户用户使用
    EMT_FUND_INTER_TRANSFER_IN,       ///<跨节点转入 从对端EMT节点2，转入到本EMT节点1，EMT服务器之间划拨，只能跨账户用户使用
    EMT_FUND_TRANSFER_UNKNOWN         ///<未知类型
}EMT_FUND_TRANSFER_TYPE;


 typedef enum EMT_FUND_QUERY_TYPE
 {
     EMT_FUND_QUERY_JZ = 0,      ///<查询主柜台可转资金（暂未支持）
     EMT_FUND_QUERY_INTERNAL,    ///<查询一账号两中心设置时，对方节点的资金
     EMT_FUND_QUERY_UNKNOWN      ///<未知类型
 }EMT_FUND_QUERY_TYPE;

/////////////////////////////////////////////////////////////////////////
///@brief EMT_FUND_OPER_STATUS柜台资金操作结果
/////////////////////////////////////////////////////////////////////////
typedef enum EMT_FUND_OPER_STATUS {
    EMT_FUND_OPER_PROCESSING = 0,     ///<EMT已收到，正在处理中
    EMT_FUND_OPER_SUCCESS,            ///<成功
    EMT_FUND_OPER_FAILED,             ///<失败
    EMT_FUND_OPER_SUBMITTED,          ///<已提交到集中柜台处理
    EMT_FUND_OPER_UNKNOWN             ///<未知
}EMT_FUND_OPER_STATUS;

/////////////////////////////////////////////////////////////////////////
///@brief EMT_DEBT_EXTEND_OPER_STATUS柜台负债展期操作状态
/////////////////////////////////////////////////////////////////////////
typedef enum EMT_DEBT_EXTEND_OPER_STATUS {
    EMT_DEBT_EXTEND_OPER_PROCESSING = 0,      ///<EMT已收到，正在处理中
    EMT_DEBT_EXTEND_OPER_SUBMITTED,           ///<已提交到集中柜台处理
    EMT_DEBT_EXTEND_OPER_SUCCESS,             ///<成功
    EMT_DEBT_EXTEND_OPER_FAILED,              ///<失败
    EMT_DEBT_EXTEND_OPER_UNKNOWN              ///<未知
}EMT_DEBT_EXTEND_OPER_STATUS;

/////////////////////////////////////////////////////////////////////////
///@brief EMT_SPLIT_MERGE_STATUS是一个基金当天拆分合并状态类型
/////////////////////////////////////////////////////////////////////////
typedef enum EMT_SPLIT_MERGE_STATUS {
    EMT_SPLIT_MERGE_STATUS_ALLOW = 0,      ///<允许拆分和合并
    EMT_SPLIT_MERGE_STATUS_ONLY_SPLIT,     ///<只允许拆分，不允许合并
    EMT_SPLIT_MERGE_STATUS_ONLY_MERGE,     ///<只允许合并，不允许拆分
    EMT_SPLIT_MERGE_STATUS_FORBIDDEN       ///<不允许拆分合并
}EMT_SPLIT_MERGE_STATUS;

/////////////////////////////////////////////////////////////////////////
///@brief EMT_TBT_TYPE是一个逐笔回报类型
/////////////////////////////////////////////////////////////////////////
typedef enum EMT_TBT_TYPE {
    EMT_TBT_ENTRUST = 1,      ///<逐笔委托
    EMT_TBT_TRADE = 2,        ///<逐笔成交
}EMT_TBT_TYPE;

/////////////////////////////////////////////////////////////////////////
///@brief EMT_OPT_CALL_OR_PUT_TYPE是一个认沽或认购类型
/////////////////////////////////////////////////////////////////////////
typedef enum EMT_OPT_CALL_OR_PUT_TYPE {
    EMT_OPT_CALL = 1,        ///<认购
    EMT_OPT_PUT = 2,         ///<认沽
}EMT_OPT_CALL_OR_PUT_TYPE;

/////////////////////////////////////////////////////////////////////////
///@brief EMT_OPT_EXERCISE_TYPE_TYPE是一个行权方式类型
/////////////////////////////////////////////////////////////////////////
typedef enum EMT_OPT_EXERCISE_TYPE_TYPE {
    EMT_OPT_EXERCISE_TYPE_EUR = 1,        ///<欧式
    EMT_OPT_EXERCISE_TYPE_AME = 2,        ///<美式
}EMT_OPT_EXERCISE_TYPE_TYPE;

/////////////////////////////////////////////////////////////////////////
///@brief EMT_POSITION_DIRECTION_TYPE是一个持仓方向类型
/////////////////////////////////////////////////////////////////////////
typedef enum EMT_POSITION_DIRECTION_TYPE {
    EMT_POSITION_DIRECTION_NET = 0,        ///<净
    EMT_POSITION_DIRECTION_LONG,           ///<多（期权则为权利方）
    EMT_POSITION_DIRECTION_SHORT,          ///<空（期权则为义务方）
    EMT_POSITION_DIRECTION_COVERED,        ///<备兑（期权则为备兑义务方）
}EMT_POSITION_DIRECTION_TYPE;

/////////////////////////////////////////////////////////////////////////
///@brief EMT_OPT_COVERED_OR_UNCOVERED是否备兑的标签
/////////////////////////////////////////////////////////////////////////
typedef enum EMT_OPT_COVERED_OR_UNCOVERED {
    EMT_POSITION_UNCOVERED = 0,     ///<非备兑
    EMT_POSITION_COVERED,           ///<备兑
}EMT_OPT_COVERED_OR_UNCOVERED;


/////////////////////////////////////////////////////////////////////////
///@brief EMT_CRD_CASH_REPAY_STATUS是一个融资融券直接还款状态类型
/////////////////////////////////////////////////////////////////////////
typedef enum EMT_CRD_CR_STATUS {
    EMT_CRD_CR_INIT = 0,        ///< 初始、未处理状态
    EMT_CRD_CR_SUCCESS,         ///< 已成功处理状态
    EMT_CRD_CR_FAILED,          ///< 处理失败状态
} EMT_CRD_CR_STATUS;

/////////////////////////////////////////////////////////////////////////
///@brief EMT_OPT_POSITION_TYPE是一个期权持仓类型
/////////////////////////////////////////////////////////////////////////
typedef enum EMT_OPT_POSITION_TYPE
{
    EMT_OPT_POSITION_TYPE_CONTRACT = 0,     ///< 单合约持仓
    EMT_OPT_POSITION_TYPE_COMBINED = 1      ///< 组合策略持仓
}EMT_OPT_POSITION_TYPE;

/////////////////////////////////////////////////////////////////////////
///@brief EMT_ORDER_TYPE是一个订单的类型
/////////////////////////////////////////////////////////////////////////
enum EMT_ORDER_DETAIL_TYPE
{
    EMT_ORDER_DETAIL_TYPE_NEW_ORDER = 0,                 ///< 新订单
    EMT_ORDER_DETAIL_TYPE_CANCEL_ORDER = 1,              ///< 新订单撤单
    EMT_ORDER_DETAIL_TYPE_OPT_COMB_NEW_ORDER = 2,        ///< 组合订单
    EMT_ORDER_DETAIL_TYPE_OPT_COMB_CANCEL_ORDER = 3      ///< 组合订单撤单
};

/////////////////////////////////////////////////////////////////////////
///TEMTTradeTypeType是成交类型
/////////////////////////////////////////////////////////////////////////
typedef char TEMTTradeTypeType;

///普通成交
#define EMT_TRDT_COMMON '0'
///现金替代成交
#define EMT_TRDT_CASH '1'
///成分股成交
#define EMT_TRDT_COMPONENT '2'
///申赎成交
#define EMT_TRDT_PRIMARY '3'

/////////////////////////////////////////////////////////////////////////
///TEMTOrderTypeType是报单类型
/////////////////////////////////////////////////////////////////////////
typedef char TEMTOrderTypeType;

///正常
#define EMT_ORDT_Normal '0'
///报价衍生
#define EMT_ORDT_DeriveFromQuote '1'
///组合衍生
#define EMT_ORDT_DeriveFromCombination '2'
///组合报单
#define EMT_ORDT_Combination '3'
///条件单
#define EMT_ORDT_ConditionalOrder '4'
///互换单
#define EMT_ORDT_Swap '5'

/////////////////////////////////////////////////////////////////////////
/// TEMTOrderSourceType是委托来源类型
/////////////////////////////////////////////////////////////////////////
typedef uint8_t TEMTOrderSourceType;

///自研API(托管TCP)
#define EMT_ORDER_SOURCE_API_TCP_HOSTING           '1'
///自研API(托管UDP)
#define EMT_ORDER_SOURCE_API_UDP_HOSTING           '2'
///DMA交易
#define EMT_ORDER_SOURCE_DMA                       '5'
///EMC普通交易
#define EMT_ORDER_SOURCE_EMC_TRADE                 '8'
///EMC文件单
#define EMT_ORDER_SOURCE_EMC_FILE_SCAN             '9'
///EMC算法交易
#define EMT_ORDER_SOURCE_EMC_STRATEGY              'A'
///EMC场外
#define EMT_ORDER_SOURCE_EMC_OTC                   'B'
///EMC量化
#define EMT_ORDER_SOURCE_EMC_QUANT                 'C'
///私募通交易
#define EMT_ORDER_SOURCE_SMT                       'D'
///EMC增强交易
#define EMT_ORDER_SOURCE_EMC_ENHANCED_TRADE        'F'
///EMC IOS端
#define EMT_ORDER_SOURCE_EMC_IOS                   'G'
///EMC Android端
#define EMT_ORDER_SOURCE_EMC_ANDROID               'H'
///EMC篮子交易
#define EMT_ORDER_SOURCE_EMC_BASKET                'I'
///三方算法(算法API)
#define EMT_ORDER_SOURCE_THIRDPARTY_STRATEGY       'J'
///三方算法(机构交易终端)
#define EMT_ORDER_SOURCE_THIRDPARTY_STRATEGY_TRDCLIENT 'L'

//////////////////////////////////////////////////////////////////////////
///@brief EMTTerminalType是一种终端类型枚举，仅供授权系统使用
//////////////////////////////////////////////////////////////////////////
enum EMTTerminalType
{
    EMT_TERMINAL_PC = 1,            ///<"PC",PC-windows及MacOS
    EMT_TERMINAL_ANDROID,           ///<"MA",Mobile-Android
    EMT_TERMINAL_IOS,               ///<"MI",Mobile-Ios
    EMT_TERMINAL_WP,                ///<"MW",Mobile-Windows Phone
    EMT_TERMINAL_STATION,           ///<"WP",无盘站
    EMT_TERMINAL_TEL,               ///<"TO",电话委托
    EMT_TERMINAL_PC_LINUX           ///<"OH",PC-linux及其他终端
};

/////////////////////////////////////////////////////////////////////////
///@brief EMT_EXPIRE_DATE_TYPE是一个期权组合策略合约到期日要求类型
/////////////////////////////////////////////////////////////////////////
typedef enum EMT_EXPIRE_DATE_TYPE {
    EMT_EXP_DATE_SAME = 0,     ///< 相同到期日
    EMT_EXP_DATE_DIFF,         ///< 不同到期日
    EMT_EXP_DATE_NON           ///< 无到期日要求
}EMT_EXPIRE_DATE_TYPE;

/////////////////////////////////////////////////////////////////////////
///@brief EMT_UNDERLYING_TYPE是一个期权组合策略标的要求类型
/////////////////////////////////////////////////////////////////////////
typedef enum EMT_UNDERLYING_TYPE {
    EMT_UNDERLYING_SAME = 0,      ///<相同标的
    EMT_UNDERLYING_DIFF,          ///<不同标的
    EMT_UNDERLYING_NON            ///<无标的要求
}EMT_UNDERLYING_TYPE;

/////////////////////////////////////////////////////////////////////////
///@brief EMT_AUTO_SPLIT_TYPE是一个期权组合策略自动解除枚举类型
/////////////////////////////////////////////////////////////////////////
typedef enum EMT_AUTO_SPLIT_TYPE {
    EMT_AUTO_SPLIT_EXPDAY = 0,     ///<到期日自动解除
    EMT_AUTO_SPLIT_PREDAY,         ///<E-1日自动解除
    EMT_AUTO_SPLIT_PRE2DAY,        ///<E-2日自动解除
    EMT_AUTO_SPLIT_NON             ///<无效值
}EMT_AUTO_SPLIT_TYPE;


///行权价顺序类型， 从1开始，1表示行权价最高，2次之。如果行权价相同，则填写相同数字，用A表示行权价大于等于B，B大于等于C依次类推（C、D）
typedef char TEMTExerciseSeqType;

/////////////////////////////////////////////////////////////////////////
///@brief EMT_QUALIFICATION_TYPE是一个证券适当性枚举类型
/////////////////////////////////////////////////////////////////////////
typedef enum  EMT_QUALIFICATION_TYPE
{
    EMT_QUALIFICATION_PUBLIC = 0,              ///<公众投资者，合格投资者与机构投资者均可
    EMT_QUALIFICATION_COMMON = 1,              ///<仅合格投资者与公众投资者
    EMT_QUALIFICATION_ORGANIZATION = 2,        ///<仅限机构投资者
    EMT_QUALIFICATION_UNKNOWN = 3              ///<未知，期权等可能为此种类型
}EMT_QUALIFICATION_TYPE;

/////////////////////////////////////////////////////////////////////////
///@brief EMT_SECURITY_TYPE是一个证券详细分类枚举类型
/////////////////////////////////////////////////////////////////////////
typedef enum EMT_SECURITY_TYPE {
    /// 主板股票
    EMT_SECURITY_MAIN_BOARD = 0,
    /// 中小板股票
    EMT_SECURITY_SECOND_BOARD,
    /// 创业板股票
    EMT_SECURITY_STARTUP_BOARD,
    /// 指数
    EMT_SECURITY_INDEX,
    /// 科创板股票(上海)
    EMT_SECURITY_TECH_BOARD = 4,
    /// 国债
    EMT_SECURITY_STATE_BOND = 5,
    /// 企业债
    EMT_SECURITY_ENTERPRICE_BOND = 6,
    /// 公司债
    EMT_SECURITY_COMPANEY_BOND = 7,
    /// 转换债券
    EMT_SECURITY_CONVERTABLE_BOND = 8,
    /// 国债逆回购
    EMT_SECURITY_NATIONAL_BOND_REVERSE_REPO = 12,
    /// 本市场股票 ETF
    EMT_SECURITY_ETF_SINGLE_MARKET_STOCK = 14,
    /// 跨市场股票 ETF
    EMT_SECURITY_ETF_INTER_MARKET_STOCK,
    /// 本市场实物债券 ETF
    EMT_SECURITY_ETF_SINGLE_MARKET_BOND = 17,
    /// 黄金 ETF
    EMT_SECURITY_ETF_GOLD = 19,
    /// 分级基金子基金
    EMT_SECURITY_STRUCTURED_FUND_CHILD = 24,
    /// 深交所仅申赎基金
    EMT_SECURITY_SZSE_RECREATION_FUND = 26,
    /// 个股期权
    EMT_SECURITY_STOCK_OPTION = 29,
    /// ETF期权
    EMT_SECURITY_ETF_OPTION = 30,
    /// 配股
    EMT_SECURITY_ALLOTMENT = 100,

    /// 上交所申赎型货币基金
    EMT_SECURITY_MONETARY_FUND_SHCR = 110,
    /// 上交所交易型货币基金
    EMT_SECURITY_MONETARY_FUND_SHTR = 111,
    /// 深交所货币基金
    EMT_SECURITY_MONETARY_FUND_SZ = 112,

    /// 其他
    EMT_SECURITY_OTHERS = 255
}EMT_SECURITY_TYPE;

/////////////////////////////////////////////////////////////////////////
///@brief EMT_CREDIT_FUND_CTRL_TYPE 融资状态枚举类型
/////////////////////////////////////////////////////////////////////////
typedef enum EMT_CREDIT_FUND_CTRL_TYPE
{
    EMT_CREDIT_FUND_CTRL_PERMIT = 0, ///< 融资状态
    EMT_CREDIT_FUND_CTRL_FORBID,
} EMT_CREDIT_FUND_CTRL_TYPE;

/////////////////////////////////////////////////////////////////////////
///@brief EMT_CREDIT_STK_CTRL_TYPE 融券状态枚举类型
/////////////////////////////////////////////////////////////////////////
typedef enum EMT_CREDIT_STK_CTRL_TYPE
{
    EMT_CREDIT_STK_CTRL_PERMIT = 0, ///< 融券状态
    EMT_CREDIT_STK_CTRL_FORBID,
} EMT_CREDIT_STK_CTRL_TYPE;

/////////////////////////////////////////////////////////////////////////
///@brief EMT_HOLDING_CHANGE_TYPE 持仓变动通知枚举类型
/////////////////////////////////////////////////////////////////////////
typedef enum EMT_HOLDING_CHANGE_TYPE
{
    EMT_HOLDING_CHANGE_TYPE_MARGIN_TRD = 0,            ///< 融资融券担保品划转
    EMT_HOLDING_CHANGE_TYPE_OPTION_TRD,                ///< 期权锁定解锁
    EMT_HOLDING_CHANGE_TYPE_COMP_TRD,                  ///< 综合业务
    EMT_HOLDING_CHANGE_TYPE_SYS_CORRECT_MAINTENANCE,   ///< 系统冲正
    EMT_HOLDING_CHANGE_TYPE_OTHER = 9,                 ///< 其它
} EMT_HOLDING_CHANGE_TYPE;

#pragma pack()

#endif
