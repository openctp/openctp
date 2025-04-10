/////////////////////////////////////////////////////////////////////////
///@author 东方财富证券股份有限公司
///@file eoms_api_struct.h
///@brief 定义交易类相关数据结构
/////////////////////////////////////////////////////////////////////////
#ifndef _EOMS_API_STRUCT_H_
#define _EOMS_API_STRUCT_H_

#include "emt_api_struct_common.h"
#include "stddef.h"

#pragma pack(1)

//=====================客户端接口定义=================================
///新订单请求
struct EMTOrderInsertInfo
{
    ///EMT系统订单ID，无需用户填写，在EMT系统中唯一
    uint64_t                order_emt_id;
    ///报单引用，由客户自定义
    uint32_t                order_client_id;
    ///合约代码 客户端请求不带空格，以'\0'结尾
    char                    ticker[EMT_TICKER_LEN];
    ///交易市场
    EMT_MARKET_TYPE         market;
    ///价格
    double                  price;
    ///止损价（保留字段）
    double                  stop_price;
    ///数量(股票单位为股，逆回购单位为张)
    int64_t                 quantity;
    ///价格类型
    EMT_PRICE_TYPE          price_type;
    ///买卖方向
    EMT_SIDE_TYPE           side;
    ///开平标志
    EMT_POSITION_EFFECT_TYPE position_effect;
    ///委托来源, 无需用户填写
    TEMTOrderSourceType     order_source;
    ///客户端id, 无需用户填写
    uint8_t                 client_id;
    ///业务类型
    EMT_BUSINESS_TYPE_EXT   business_type;
    ///算法类型, 无需用户填写
    uint8_t                 algorithm_type;
    ///保留字段
    char                    reserved[2];
 };

///撤单失败响应消息
struct EMTOrderCancelInfo
{
    ///撤单EMTID
    uint64_t                 order_cancel_emt_id;
    ///原始订单EMTID
    uint64_t                 order_emt_id;
};

///报单响应结构体
struct EMTOrderInfo
{
    ///EMT系统订单ID，在EMT系统中唯一
    uint64_t                order_emt_id;
    ///报单引用，用户自定义
    uint32_t                order_client_id;
    ///报单操作引用，用户自定义（暂未使用）
    uint32_t                order_cancel_client_id;
    ///撤单在EMT系统中的id，在EMT系统中唯一
    uint64_t                order_cancel_emt_id;
    ///合约代码
    char                    ticker[EMT_TICKER_LEN];
    ///交易市场
    EMT_MARKET_TYPE         market;
    ///价格
    double                  price;
    ///数量，此订单的报单数量
    int64_t                 quantity;
    ///报单价格条件
    EMT_PRICE_TYPE          price_type;
    ///买卖方向
    EMT_SIDE_TYPE           side;
    ///开平标志，期权用户关注字段，其余用户填0即可
    EMT_POSITION_EFFECT_TYPE position_effect;
    ///委托来源
    TEMTOrderSourceType     order_source;
    ///客户端id
    uint8_t                 client_id;
    ///业务类型
    EMT_BUSINESS_TYPE_EXT   business_type;
    ///算法类型, 无需用户填写
    uint8_t                 algorithm_type;
    ///保留字段
    char                    reserved[2];
    ///今成交数量，为此订单累计成交数量
    int64_t                 qty_traded;
    ///剩余数量，当撤单成功时，表示撤单数量
    int64_t                 qty_left;
    ///委托时间，格式为YYYYMMDDHHMMSSsss
    int64_t                 insert_time;
    ///最后修改时间，格式为YYYYMMDDHHMMSSsss
    int64_t                 update_time;
    ///撤销时间，格式为YYYYMMDDHHMMSSsss
    int64_t                 cancel_time;
    ///成交金额，为此订单的成交总金额
    double                  trade_amount;
    ///本地报单编号 OMS生成的单号，不等同于order_emt_id，为服务器传到报盘的单号
    char                    order_local_id[EMT_LOCAL_ORDER_LEN];
    ///报单状态，订单响应中没有部分成交状态的推送，在查询订单结果中，会有部分成交状态
    EMT_ORDER_STATUS_TYPE   order_status;
    ///报单提交状态，OMS内部使用，用户可用此字段来区分撤单和报单
    EMT_ORDER_SUBMIT_STATUS_TYPE   order_submit_status;
    ///报单类型
    TEMTOrderTypeType       order_type;
};

///报单成交结构体
struct EMTTradeReport
{
    ///EMT系统订单ID，此成交回报相关的订单ID，在EMT系统中唯一
    uint64_t                 order_emt_id;
    ///报单引用
    uint32_t                 order_client_id;
    ///合约代码
    char                     ticker[EMT_TICKER_LEN];
    ///交易市场
    EMT_MARKET_TYPE          market;
    union {
        ///订单号，引入EMTID后，该字段已废弃，接口中暂时保留
        uint64_t             local_order_id;
        struct {
            ///报单价格条件
            EMT_PRICE_TYPE   price_type;
            ///保留字段
            char             reserved[4];
        };
    };
    ///成交编号，与沪深交所每笔成交一一对应，当存在两笔成交回报exec_id相同，则可认为出现自成交
    char                     exec_id[EMT_EXEC_ID_LEN];
    ///价格，此次成交的价格
    double                   price;
    ///数量，此次成交的数量，不是累计数量
    int64_t                  quantity;
    ///成交时间，格式为YYYYMMDDHHMMSSsss
    int64_t                  trade_time;
    ///成交金额，此次成交的总金额 = price*quantity
    double                   trade_amount;
    ///成交序号，EMT内部回报序号，单地交易模式下保证每笔成交唯一，分仓模式下不保证唯一性
    uint64_t                 report_index;
    ///报单编号，交易所申报号，对应委托回报中本地报单编号order_local_id
    char                     order_exch_id[EMT_ORDER_EXCH_LEN];
    ///成交类型  --成交回报中的执行类型
    TEMTTradeTypeType        trade_type;
    ///买卖方向
    EMT_SIDE_TYPE            side;
    ///开平标志
    EMT_POSITION_EFFECT_TYPE position_effect;
    ///委托来源
    TEMTOrderSourceType      order_source;
    ///客户端id
    uint8_t                  client_id;
    ///业务类型
    EMT_BUSINESS_TYPE_EXT    business_type;
    ///算法类型, 无需用户填写
    uint8_t                  algorithm_type;
    ///保留字段
    char                     reserved2[2];
    ///交易所交易员代码
    char                     branch_pbu[EMT_BRANCH_PBU_LEN];
};


//////////////////////////////////////////////////////////////////////////
///报单查询请求-条件查询
//////////////////////////////////////////////////////////////////////////
struct EMTQueryOrderReq
{
    ///证券代码，可以为空，如果为空，则默认查询时间段内的所有成交回报
    char      ticker[EMT_TICKER_LEN];
    ///格式为YYYYMMDDHHMMSSsss，为0则默认当前交易日0点
    int64_t   begin_time;
    ///格式为YYYYMMDDHHMMSSsss，为0则默认当前时间
    int64_t   end_time;
};

///报单查询响应结构体
typedef struct EMTOrderInfo EMTQueryOrderRsp;

///通用分页查询请求
struct EMTQueryByPageReq
{
    ///需要查询的订单条数
    int64_t         req_count;
    ///上一次收到的查询订单结果中带回来的索引，如果是从头查询，请置0
    int64_t         reference;
    ///保留字段
    int64_t         reserved;
};

///查询信用账户负债合约信息-分页查询
struct EMTQueryCreditDebtInfoByPageReq
{
    ///需要查询的订单条数
    int64_t         req_count;
    ///上一次收到的查询订单结果中带回来的索引，如果是从头查询，请置0
    int64_t         reference;
    ///保留字段
    union {
        ///32位字段，用来兼容老版本api，用户无需关心
        uint64_t            u64;
        struct {
            //合约类型  0 : 全量查询  | 1 : 融资合约 | 2 : 融券合约
            uint8_t                     debttype;
            ///预留字段
            uint8_t                     reserved[7];
        };
    };
};

///查询订单请求-分页查询
typedef  EMTQueryByPageReq EMTQueryOrderByPageReq;
///查询成交回报请求-分页查询
typedef  EMTQueryByPageReq EMTQueryTraderByPageReq;
///查询信用账户持仓信息-分页查询
typedef  EMTQueryByPageReq EMTQueryPositionByPageReq;
///查询信用账户头寸信息-分页查询
typedef  EMTQueryByPageReq EMTQueryTickerAssignInfoByPageReq;
///查询标的基本信息请求-分页查询
typedef EMTQueryByPageReq EMTQuerySecurityByPageReq;
///查询ETF清单文件请求-分页查询
typedef EMTQueryByPageReq EMTQueryETFByPageReq;

//////////////////////////////////////////////////////////////////////////
///查询成交报告请求-根据执行编号查询（保留字段）
//////////////////////////////////////////////////////////////////////////
struct EMTQueryReportByExecIdReq
{
    ///EMT订单系统ID
    uint64_t  order_emt_id;
    ///成交执行编号
    char  exec_id[EMT_EXEC_ID_LEN];
};

///查询成交回报请求-查询条件
struct EMTQueryTraderReq
{
    ///证券代码，可以为空，如果为空，则默认查询时间段内的所有成交回报
    char      ticker[EMT_TICKER_LEN];
    ///开始时间，格式为YYYYMMDDHHMMSSsss，为0则默认当前交易日0点
    int64_t   begin_time;
    ///结束时间，格式为YYYYMMDDHHMMSSsss，为0则默认当前时间
    int64_t   end_time;
};

///成交回报查询响应结构体
typedef struct EMTTradeReport  EMTQueryTradeRsp;

//////////////////////////////////////////////////////////////////////////
///账户资金查询响应结构体
//////////////////////////////////////////////////////////////////////////
struct EMTQueryAssetRsp
{
    ///总资产（现货账户/期权账户参考公式：总资产 = 可用资金 + 证券资产（目前为0）+ 预扣的资金），（信用账户参考公式：总资产 = 可用资金 + 融券卖出所得资金余额 + 证券资产+ 预扣的资金）
    double total_asset;
    ///可用资金
    double buying_power;
    ///证券资产（保留字段，目前为0）
    double security_asset;
    ///累计买入成交证券占用资金（仅限现货账户/期权账户，信用账户暂不可用）
    double fund_buy_amount;
    ///累计买入成交交易费用（仅限现货账户/期权账户，信用账户暂不可用）
    double fund_buy_fee;
    ///累计卖出成交证券所得资金（仅限现货账户/期权账户，信用账户暂不可用）
    double fund_sell_amount;
    ///累计卖出成交交易费用（仅限现货账户/期权账户，信用账户暂不可用）
    double fund_sell_fee;
    ///EMT系统预扣的资金（包括买卖股票时预扣的交易资金+预扣手续费）
    double withholding_amount;
    ///账户类型
    EMT_ACCOUNT_TYPE account_type;

    ///冻结的保证金（仅限期权账户）
    double frozen_margin;
    ///行权冻结资金（仅限期权账户）
    double frozen_exec_cash;
    ///行权费用（仅限期权账户）
    double frozen_exec_fee;
    ///垫付资金（仅限期权账户）
    double pay_later;
    ///预垫付资金（仅限期权账户）
    double preadva_pay;
    ///昨日余额（仅限期权账户）
    double orig_banlance;
    ///当前余额（仅限期权账户）
    double banlance;
    ///当天出入金（仅限期权账户）
    double deposit_withdraw;
    ///当日交易资金轧差（仅限期权账户）
    double trade_netting;
    ///资金资产（仅限期权账户）
    double captial_asset;

    ///强锁资金（仅限期权账户）
    double force_freeze_amount;
    ///可取资金（仅限期权账户）
    double preferred_amount;

    // 信用业务新增字段开始（数量1）
    ///融券卖出所得资金余额（仅限信用账户，只能用于买券还券）
    double repay_stock_aval_banlance;

    // 信用业务新增字段结束（数量1）

    ///累计订单流量费
    double fund_order_data_charges;
    ///累计撤单流量费
    double fund_cancel_data_charges;
    //流量费统计新增字段结束（数量2）

    ///港股通可用资金(货币单位:人民币)
    double hkex_fund_available;
    ///港股通可用冻结金额(货币单位:人民币)
    double hkex_fund_frozen;

    ///(保留字段)
    uint64_t unknown[26];
};

//////////////////////////////////////////////////////////////////////////
///账户昨日资产查询响应结构体
//////////////////////////////////////////////////////////////////////////
struct EMTQueryYesterdayAssetRsp
{
    ///总资产
    double total_asset;
    ///净资产 （保留字段，目前为0）
    double pure_asset;
    ///资金资产
    double fund_asset;
    ///证券资产
    double security_asset;

    ///账户类型
    EMT_ACCOUNT_TYPE account_type;
};

//////////////////////////////////////////////////////////////////////////
///查询股票持仓情况请求结构体
//////////////////////////////////////////////////////////////////////////
struct EMTQueryStkPositionReq
{
    ///证券代码
    char                ticker[EMT_TICKER_LEN];
    ///交易市场
    EMT_MARKET_TYPE     market;
};

//////////////////////////////////////////////////////////////////////////
///查询股票持仓情况
//////////////////////////////////////////////////////////////////////////
struct EMTQueryStkPositionRsp
{
    ///证券代码
    char                ticker[EMT_TICKER_LEN];
    ///证券名称
    char                ticker_name[EMT_TICKER_NAME_LEN];
    ///交易市场
    EMT_MARKET_TYPE     market;
    ///总持仓
    int64_t             total_qty;
    ///可卖持仓
    int64_t                sellable_qty;
    ///持仓成本
    double              avg_price;
    ///浮动盈亏（保留字段）
    double              unrealized_pnl;
    ///昨日持仓
    int64_t             yesterday_position;
    ///今日申购赎回数量（申购和赎回数量不可能同时存在，因此可以共用一个字段）
    int64_t                purchase_redeemable_qty;

    //以下为期权用户关心字段
    /// 持仓方向
    EMT_POSITION_DIRECTION_TYPE      position_direction;
    ///保留字段1
    uint32_t            reserved1;
    /// 可行权合约
    int64_t             executable_option;
    /// 可锁定标的
    int64_t             lockable_position;
    /// 可行权标的
    int64_t             executable_underlying;
    /// 已锁定标的
    int64_t             locked_position;
    /// 可用已锁定标的
    int64_t             usable_locked_position;

    ///(保留字段)
    uint64_t unknown[50 - 6];
};

/////////////////////////////////////////////////////////////////////////
///用户展期请求的通知
/////////////////////////////////////////////////////////////////////////
struct EMTCreditDebtExtendNotice
{
    uint64_t    emtid;                                ///<EMT系统订单ID，无需用户填写，在EMT系统中唯一
    char        debt_id[EMT_CREDIT_DEBT_ID_LEN];    ///<负债合约编号
    EMT_DEBT_EXTEND_OPER_STATUS        oper_status;    ///<展期请求操作状态
    uint64_t    oper_time;                            ///<操作时间
};

/////////////////////////////////////////////////////////////////////////
///资金内转流水通知
/////////////////////////////////////////////////////////////////////////
struct EMTFundTransferNotice
{
    ///资金内转编号
    uint64_t                serial_id;
    ///内转类型
    EMT_FUND_TRANSFER_TYPE    transfer_type;
    ///金额
    double                    amount;
    ///操作结果
    EMT_FUND_OPER_STATUS    oper_status;
    ///操作时间
    uint64_t                transfer_time;
};

/////////////////////////////////////////////////////////////////////////
///两地分仓额度内转流水通知
/////////////////////////////////////////////////////////////////////////
struct EMTQuotaTransferNotice
{
    ///资金内转编号
    uint64_t                serial_id;
    ///内转类型
    EMT_QUOTA_TRANSFER_TYPE    transfer_type;
    ///金额
    double                    amount;
    ///操作结果
    EMT_QUOTA_OPER_STATUS    oper_status;
    ///操作时间
    uint64_t                transfer_time;
};

/////////////////////////////////////////////////////////////////////////
///资金内转流水查询请求与响应
/////////////////////////////////////////////////////////////////////////
struct EMTQueryFundTransferLogReq
{
    ///资金内转编号
    uint64_t    serial_id;
};

/////////////////////////////////////////////////////////////////////////
///融券额度调拨流水查询请求与响应
/////////////////////////////////////////////////////////////////////////
struct EMTQueryQuotaTransferLogReq {
    ///资金内转编号
    uint64_t    serial_id;

};

/////////////////////////////////////////////////////////////////////////
///资金内转流水记录结构体
/////////////////////////////////////////////////////////////////////////
typedef struct EMTFundTransferNotice EMTFundTransferLog;

//////////////////////////////////////////////////////////////////////////
///查询分级基金信息结构体
//////////////////////////////////////////////////////////////////////////
struct EMTQueryStructuredFundInfoReq
{
    EMT_EXCHANGE_TYPE   exchange_id;  ///<交易所代码，不可为空
    char                sf_ticker[EMT_TICKER_LEN];   ///<分级基金母基金代码，可以为空，如果为空，则默认查询所有的分级基金
};

//////////////////////////////////////////////////////////////////////////
///查询分级基金信息响应结构体
//////////////////////////////////////////////////////////////////////////
struct EMTStructuredFundInfo
{
    EMT_EXCHANGE_TYPE   exchange_id;  ///<交易所代码
    char                sf_ticker[EMT_TICKER_LEN];   ///<分级基金母基金代码
    char                sf_ticker_name[EMT_TICKER_NAME_LEN]; ///<分级基金母基金名称
    char                ticker[EMT_TICKER_LEN];   ///<分级基金子基金代码
    char                ticker_name[EMT_TICKER_NAME_LEN]; ///<分级基金子基金名称
    EMT_SPLIT_MERGE_STATUS    split_merge_status;   ///<基金允许拆分合并状态
    uint32_t            ratio; ///<拆分合并比例
    uint32_t            min_split_qty;///<最小拆分数量
    uint32_t            min_merge_qty; ///<最小合并数量
    double              net_price;///<基金净值
};

//////////////////////////////////////////////////////////////////////////
///查询股票ETF合约基本情况--请求结构体,请求参数为多条件参数:1,不填则返回所有市场的ETF合约信息。2,只填写market,返回该交易市场下结果 3,填写market及ticker参数,只返回该etf信息。
//////////////////////////////////////////////////////////////////////////
struct EMTQueryETFBaseReq
{
    ///交易市场
    EMT_MARKET_TYPE    market;
    ///ETF买卖代码
    char               ticker[EMT_TICKER_LEN];
};

//////////////////////////////////////////////////////////////////////////
///查询股票ETF合约基本情况--响应结构体
//////////////////////////////////////////////////////////////////////////
struct EMTQueryETFBaseRsp
{
    EMT_MARKET_TYPE     market;                                         ///<交易市场
    char                etf[EMT_TICKER_LEN];                            ///<etf代码,买卖,申赎统一使用该代码
    char                subscribe_redemption_ticker[EMT_TICKER_LEN];    ///<etf申购赎回代码
    int32_t             unit;                                           ///<最小申购赎回单位对应的ETF份数,例如上证"50ETF"就是900000
    int32_t             subscribe_status;                               ///<是否允许申购,1-允许,0-禁止
    int32_t             redemption_status;                              ///<是否允许赎回,1-允许,0-禁止
    double              max_cash_ratio;                                 ///<最大现金替代比例,小于1的数值   TODO 是否采用double
    double              estimate_amount;                                ///<T日预估金额
    double              cash_component;                                 ///<T-X日现金差额
    double              net_value;                                      ///<基金单位净值
    double              total_amount;                                   ///<最小申赎单位净值总金额=net_value*unit
    int32_t             rtgs_flag;                                      ///<是否rtgs,1-是, 0-否
    int32_t             day_trading;                                    ///<当日买进当日是否允许卖出(回转标志) 1-是,0-否
    int32_t             buy_to_redemption;                              ///<当日买进当日是否允许赎回 1-是,0-否
    int32_t             creation_to_sell;                               ///<当日申购当日是否允许卖出 1-是,0-否
    int32_t             creation_to_redemption;                         ///<当日申购当日是否允许赎回 1-是,0-否
};

//////////////////////////////////////////////////////////////////////////
///查询股票ETF合约成分股信息--请求结构体,请求参数为:交易市场+ETF买卖代码
//////////////////////////////////////////////////////////////////////////
struct EMTQueryETFComponentReq
{
    ///交易市场
    EMT_MARKET_TYPE     market;
    ///ETF买卖代码
    char                ticker[EMT_TICKER_LEN];
};

//////////////////////////////////////////////////////////////////////////
///查询股票ETF成分股信息--响应结构体，旧版本。
//////////////////////////////////////////////////////////////////////////
struct EMTQueryETFComponentRspV1
{
    ///交易市场
    EMT_MARKET_TYPE     market;
    ///ETF代码
    char                ticker[EMT_TICKER_LEN];
    ///成份股代码
    char                component_ticker[EMT_TICKER_LEN];
    ///成份股名称
    char                component_name[EMT_TICKER_NAME_LEN];
    ///成份股数量
    int64_t             quantity;
    ///成份股交易市场
    EMT_MARKET_TYPE     component_market;
    ///成份股替代标识
    ETF_REPLACE_TYPE    replace_type;
    ///溢价比例
    double              premium_ratio;
    ///成分股替代标识为必须现金替代时候的总金额
    double              amount;
};

//////////////////////////////////////////////////////////////////////////
///查询股票ETF成分股信息--响应结构体
//////////////////////////////////////////////////////////////////////////
struct EMTQueryETFComponentRsp
{
    ///交易市场
    EMT_MARKET_TYPE     market;
    ///ETF代码
    char                ticker[EMT_TICKER_LEN];
    ///成份股代码
    char                component_ticker[EMT_TICKER_LEN];
    ///成份股名称
    char                component_name[EMT_TICKER_NAME_LEN];
    ///成份股数量
    int64_t             quantity;
    ///成份股交易市场
    EMT_MARKET_TYPE     component_market;
    ///成份股替代标识
    ETF_REPLACE_TYPE    replace_type;
    ///溢价比例
    double              premium_ratio;
    ///成分股替代标识为必须现金替代时候的总金额
    double              amount;
    ///申购溢价比例
    double              creation_premium_ratio;
    ///赎回溢价比例
    double              redemption_discount_ratio;
    ///申购时，成分股替代标识为必须现金替代时候的总金额
    double              creation_amount;
    ///赎回时，成分股替代标识为必须现金替代时候的总金额
    double              redemption_amount;
};

//////////////////////////////////////////////////////////////////////////
///查询当日可申购新股信息
//////////////////////////////////////////////////////////////////////////
struct EMTQueryIPOTickerRsp
{
    ///交易市场
    EMT_MARKET_TYPE     market;
    ///申购代码
    char                ticker[EMT_TICKER_LEN];
    ///申购股票名称
    char                ticker_name[EMT_TICKER_NAME_LEN];
    /// 证券类别
    EMT_TICKER_TYPE     ticker_type;
    ///申购价格
    double              price;
    ///申购单元
    int32_t             unit;
    ///最大允许申购数量
    int32_t             qty_upper_limit;
};

//////////////////////////////////////////////////////////////////////////
///查询用户申购额度-包含创业板额度
//////////////////////////////////////////////////////////////////////////
struct EMTQueryIPOQuotaRsp
{
    ///交易市场
    EMT_MARKET_TYPE     market;
    ///可申购额度
    int32_t             quantity;
    /// 上海科创板额度
    int32_t             tech_quantity;
    /// 保留
    int32_t             unused;
};

//////////////////////////////////////////////////////////////////////////
///申报用户的ip和mac等信息，仅限授权用户使用
//////////////////////////////////////////////////////////////////////////
struct EMTUserTerminalInfoReq
{
    char  local_ip[EMT_INET_ADDRESS_STR_LEN];            ///<本地IP地址
    char  mac_addr[EMT_MAC_ADDRESS_LEN];                ///<MAC地址
    char  hd[EMT_HARDDISK_SN_LEN];                        ///<硬盘序列号
    EMTTerminalType term_type;                            ///<终端类型
    char  internet_ip[EMT_INET_ADDRESS_STR_LEN];        ///<公网IP地址
    int32_t internet_port;                                ///<公网端口号
    char  unused[64];                                    ///<预留
};

//////////////////////////////////////////////////////////////////////////
///查询期权竞价交易业务参考信息--请求结构体,请求参数为:交易市场+8位期权代码
//////////////////////////////////////////////////////////////////////////
struct EMTQueryOptionAuctionInfoReq
{
    ///交易市场
    EMT_MARKET_TYPE     market;
    ///8位期权合约代码
    char                ticker[EMT_TICKER_LEN];
};

//////////////////////////////////////////////////////////////////////////
///查询期权竞价交易业务参考信息
//////////////////////////////////////////////////////////////////////////
struct EMTQueryOptionAuctionInfoRsp
{
    char                ticker[EMT_TICKER_LEN];             ///<合约编码，报单ticker采用本字段
    EMT_MARKET_TYPE     security_id_source;                 ///<证券代码源
    char                symbol[EMT_TICKER_NAME_LEN];        ///<合约简称
    char                contract_id[EMT_TICKER_NAME_LEN];   ///<合约交易代码
    char                underlying_security_id[EMT_TICKER_LEN]; ///<基础证券代码
    EMT_MARKET_TYPE     underlying_security_id_source;      ///<基础证券代码源

    uint32_t            list_date;                          ///<上市日期，格式为YYYYMMDD
    uint32_t            last_trade_date;                    ///<最后交易日，格式为YYYYMMDD
    EMT_TICKER_TYPE     ticker_type;                        ///<证券类别
    int32_t             day_trading;                        ///<是否支持当日回转交易，1-允许，0-不允许

    EMT_OPT_CALL_OR_PUT_TYPE    call_or_put;                ///<认购或认沽
    uint32_t            delivery_day;                       ///<行权交割日，格式为YYYYMMDD
    uint32_t            delivery_month;                     ///<交割月份，格式为YYYYMM

    EMT_OPT_EXERCISE_TYPE_TYPE  exercise_type;              ///<行权方式
    uint32_t            exercise_begin_date;                ///<行权起始日期，格式为YYYYMMDD
    uint32_t            exercise_end_date;                  ///<行权结束日期，格式为YYYYMMDD
    double              exercise_price;                     ///<行权价格

    int64_t             qty_unit;                           ///<数量单位，对于某一证券申报的委托，其委托数量字段必须为该证券数量单位的整数倍
    int64_t             contract_unit;                      ///<合约单位
    int64_t             contract_position;                  ///<合约持仓量

    double              prev_close_price;                   ///<合约前收盘价
    double              prev_clearing_price;                ///<合约前结算价

    int64_t             lmt_buy_max_qty;                    ///<限价买最大量
    int64_t             lmt_buy_min_qty;                    ///<限价买最小量
    int64_t             lmt_sell_max_qty;                   ///<限价卖最大量
    int64_t             lmt_sell_min_qty;                   ///<限价卖最小量
    int64_t             mkt_buy_max_qty;                    ///<市价买最大量
    int64_t             mkt_buy_min_qty;                    ///<市价买最小量
    int64_t             mkt_sell_max_qty;                   ///<市价卖最大量
    int64_t             mkt_sell_min_qty;                   ///<市价卖最小量

    double              price_tick;                         ///<最小报价单位
    double              upper_limit_price;                  ///<涨停价
    double              lower_limit_price;                  ///<跌停价
    double              sell_margin;                        ///<今卖开每张保证金
    double              margin_ratio_param1;                ///<交易所保证金比例计算参数一
    double              margin_ratio_param2;                ///<交易所保证金比例计算参数二

    uint64_t            unknown[20];                        ///<（保留字段）
};

/// 期权组合策略撤单错误响应结构体
typedef struct EMTOrderCancelInfo EMTOptCombOrderCancelInfo;

/// 期权组合策略的成分合约信息
struct EMTCombLegStrategy
{
    EMT_OPT_CALL_OR_PUT_TYPE    call_or_put;        ///< 合约类型，认沽或认购
    EMT_POSITION_DIRECTION_TYPE position_side;      ///< 权利仓或者义务仓或备兑义务仓
    TEMTExerciseSeqType         exercise_price_seq; ///< 行权价顺序
    int32_t                     expire_date_seq;    ///< 到期日顺序
    int64_t                     leg_qty;            ///< 单份组合策略中包含的此合约张数
};

/// 查询期权组合策略信息的响应
struct EMTQueryCombineStrategyInfoRsp
{
    char                    strategy_id[EMT_STRATEGY_ID_LEN];        ///< 组合策略代码，CNSJC、PXSJC、PNSJC、CXSJC、KS、KKS
    char                    strategy_name[EMT_STRATEGY_NAME_LEN];    ///< 组合策略名称，认购牛市价差策略、认沽熊市价差策略、认沽牛市价差策略、认购熊市价差策略、跨式空头、宽跨式空头
    EMT_MARKET_TYPE         market;                                  ///< 交易市场

    int32_t                 leg_num;                                 ///< 成分合约个数，1-4个，即下面数组的实际大小
    EMTCombLegStrategy      leg_strategy[EMT_STRATEGE_LEG_NUM];      ///< 成分合约信息，最多四条腿

    EMT_EXPIRE_DATE_TYPE    expire_date_type;                        ///< 到期日要求。枚举值为：同到期日，不同到期日，无到期日要求
    EMT_UNDERLYING_TYPE     underlying_type;                         ///< 标的要求。枚举值为：相同标的，不同标的，无标的要求
    EMT_AUTO_SPLIT_TYPE     auto_sep_type;                           ///< 自动解除类型。枚举值为：-1：不适用；0：到期日自动解除；1：E-1日自动解除，依次类推

    uint64_t                reserved[10];                            ///< 预留的字段
};

/// 组合策略腿合约信息结构体
struct EMTOptCombLegInfo
{
    char                            leg_security_id[EMT_TICKER_LEN]; ///< 成分合约代码
    EMT_OPT_CALL_OR_PUT_TYPE        leg_cntr_type;                   ///< 合约类型，认沽或认购。
    EMT_POSITION_DIRECTION_TYPE     leg_side;                        ///< 持仓方向，权利方或义务方。
    EMT_OPT_COVERED_OR_UNCOVERED    leg_covered;                     ///< 备兑标签
    int32_t                         leg_qty;                         ///< 成分合约数量（张）
};

///期权组合策略报单附加信息结构体
struct EMTOptCombPlugin
{
    char                                strategy_id[EMT_STRATEGY_ID_LEN];               ///< 组合策略代码，比如CNSJC认购牛市价差策略等。
    char                                comb_num[EMT_SECONDARY_ORDER_ID_LEN];           ///< 组合编码，组合申报时，该字段为空；拆分申报时，填写拟拆分组合的组合编码。
    int32_t                             num_legs;                                       ///< 成分合约数
    EMTOptCombLegInfo                   leg_detail[EMT_STRATEGE_LEG_NUM];               ///< 成分合约数组，最多四条腿。
};

//////////////////////////////////////////////////////////////////////////
///查询期权组合策略持仓情况请求结构体
//////////////////////////////////////////////////////////////////////////
struct EMTQueryOptCombPositionReq
{
    ///组合编码
    char comb_num[EMT_SECONDARY_ORDER_ID_LEN];
    ///交易市场
    EMT_MARKET_TYPE     market;
};

/// 查询期权组合策略持仓信息的响应
struct EMTQueryOptCombPositionRsp
{
    char                    strategy_id[EMT_STRATEGY_ID_LEN];           ///< 组合策略代码
    char                    strategy_name[EMT_STRATEGY_NAME_LEN];       ///< 组合策略名称

    EMT_MARKET_TYPE         market;                                     ///< 交易市场
    int64_t                 total_qty;                                  ///< 总持仓
    int64_t                 available_qty;                              ///< 可拆分持仓
    int64_t                 yesterday_position;                         ///< 昨日持仓

    EMTOptCombPlugin        opt_comb_info;                              ///< 期权组合策略信息

    uint64_t                reserved[50];                               ///<保留字段
};

//////////////////////////////////////////////////////////////////////////
///融资融券直接还款响应信息
//////////////////////////////////////////////////////////////////////////
struct EMTCrdCashRepayRsp
{
    int64_t emt_id;             ///< 直接还款操作的EMTID
    double  request_amount;     ///< 直接还款的申请金额
    double  cash_repay_amount;  ///< 实际还款使用金额
};

//////////////////////////////////////////////////////////////////////////
///单条融资融券直接还款记录信息
//////////////////////////////////////////////////////////////////////////
struct EMTCrdCashRepayInfo
{
    int64_t                     emt_id;             ///< 直接还款操作的EMTID
    EMT_CRD_CR_STATUS           status;             ///< 直接还款处理状态
    double                      request_amount;     ///< 直接还款的申请金额
    double                      cash_repay_amount;  ///< 实际还款使用金额
    EMT_POSITION_EFFECT_TYPE    position_effect;    ///< 强平标志
    EMTRI                       error_info;            ///< 直接还款发生错误时的错误信息
};

//////////////////////////////////////////////////////////////////////////
///单条融资融券负债记录信息
//////////////////////////////////////////////////////////////////////////
struct EMTCrdDebtInfo
{
    int32_t             debt_type;              ///< 负债合约类型：0为融资，1为融券，2未知
    char                debt_id[33];            ///< 负债合约编号
    int64_t             position_id;            ///< 负债对应两融头寸编号
    uint64_t            order_emt_id;           ///< 生成负债的订单编号，非当日负债无此项
    int32_t             debt_status;            ///< 负债合约状态：0为未偿还或部分偿还，1为已偿还，2为过期未平仓，3未知
    EMT_MARKET_TYPE     market;                 ///< 市场
    char                ticker[EMT_TICKER_LEN]; ///< 证券代码
    uint64_t            order_date;             ///< 委托日期
    uint64_t            end_date;               ///< 负债截止日期
    uint64_t            orig_end_date;          ///< 负债原始截止日期
    bool                is_extended;            ///< 当日是否接收到展期请求：false为没收到，true为收到
    double              remain_amt;             ///< 未偿还金额
    int64_t             remain_qty;             ///< 未偿还融券数量
    double              remain_principal;       ///< 未偿还本金金额
    int64_t             due_right_qty;          ///< 应偿还权益数量
    double              trans_righs_amt;        ///< 在途权益金额
    int64_t             trans_righs_qty;        ///< 在途权益数量
};

//////////////////////////////////////////////////////////////////////////
///融资融券特有帐户数据
//////////////////////////////////////////////////////////////////////////
struct EMTCrdFundInfo
{
    double maintenance_ratio;       ///< 维持担保品比例
    double all_asset;               ///< 总资产
    double all_debt;                ///< 总负债
    double line_of_credit;          ///< 两融授信额度
    double guaranty;                ///< 两融保证金可用数
    double position_amount;         ///< 融资头寸可用金额，内部接口，正式版本需要删除
};

//////////////////////////////////////////////////////////////////////////
///融资融券指定证券上的负债未还数量请求结构体
//////////////////////////////////////////////////////////////////////////
struct EMTClientQueryCrdDebtStockReq
{
    EMT_MARKET_TYPE market;                 ///< 市场
    char            ticker[EMT_TICKER_LEN]; ///< 证券代码
};

//////////////////////////////////////////////////////////////////////////
///融资融券指定证券的融券负债相关信息
//////////////////////////////////////////////////////////////////////////
struct EMTCrdDebtStockInfo
{
    EMT_MARKET_TYPE market;                     ///< 市场
    char            ticker[EMT_TICKER_LEN];     ///< 证券代码
    int64_t         stock_repay_quantity;       ///< 融券负债可还券数量
    int64_t         stock_total_quantity;       ///< 融券负债未还总数量
};

//////////////////////////////////////////////////////////////////////////
///融券头寸证券查询请求结构体
//////////////////////////////////////////////////////////////////////////
struct EMTClientQueryCrdPositionStockReq
{
    EMT_MARKET_TYPE market;                 ///< 证券市场
    char            ticker[EMT_TICKER_LEN]; ///< 证券代码
};

//////////////////////////////////////////////////////////////////////////
///融券头寸证券信息
//////////////////////////////////////////////////////////////////////////
struct EMTClientQueryCrdPositionStkInfo
{
    EMT_MARKET_TYPE market;                 ///< 证券市场
    char            ticker[EMT_TICKER_LEN]; ///< 证券代码
    int64_t         limit_qty;              ///< 融券限量
    int64_t         yesterday_qty;          ///< 昨日日融券数量
    int64_t         left_qty;               ///< 剩余可融券数量
    int64_t         frozen_qty;             ///< 冻结融券数量
    int32_t         end_date;               ///< 融券头寸到期日
};

//////////////////////////////////////////////////////////////////////////
/// 信用业务余券查询请求结构体
//////////////////////////////////////////////////////////////////////////
struct EMTClientQueryCrdSurplusStkReqInfo
{
    EMT_MARKET_TYPE market;                 ///< 证券市场
    char            ticker[EMT_TICKER_LEN]; ///< 证券代码
};

//////////////////////////////////////////////////////////////////////////
///信用业务余券信息
//////////////////////////////////////////////////////////////////////////
struct EMTClientQueryCrdSurplusStkRspInfo
{
    EMT_MARKET_TYPE market;                 ///< 证券市场
    char            ticker[EMT_TICKER_LEN]; ///< 证券代码
    int64_t         transferable_quantity;  ///< 可划转数量
    int64_t         transferred_quantity;   ///< 已划转数量
};

/////////////////////////////////////////////////////////////////////////
///用户展期请求
/////////////////////////////////////////////////////////////////////////
struct EMTCreditDebtExtendReq
{
    uint64_t    emtid;                                ///<emtid
    char        debt_id[EMT_CREDIT_DEBT_ID_LEN];    ///<负债合约编号
    uint32_t    defer_days;                            ///<展期天数
    char        fund_account[EMT_ACCOUNT_NAME_LEN];    ///<资金账号
    char        password[EMT_ACCOUNT_PASSWORD_LEN];    ///<资金账号密码
};

/////////////////////////////////////////////////////////////////////////
///用户展期请求的响应结构
/////////////////////////////////////////////////////////////////////////
typedef struct EMTCreditDebtExtendNotice EMTCreditDebtExtendAck;

//////////////////////////////////////////////////////////////////////////
/// 融资融券帐户附加信息
//////////////////////////////////////////////////////////////////////////
struct EMTCrdFundExtraInfo
{
    double    mf_rs_avl_used;  ///<当前资金账户购买货币基金使用的融券卖出所得资金占用
    char      reserve[64];     ///<预留空间
};

//////////////////////////////////////////////////////////////////////////
///融资融券帐户持仓附加信息
//////////////////////////////////////////////////////////////////////////
struct EMTCrdPositionExtraInfo
{
    EMT_MARKET_TYPE market;                 ///<证券市场
    char            ticker[EMT_TICKER_LEN]; ///<证券代码
    double          mf_rs_avl_used;         ///<购买货币基金使用的融券卖出所得资金占用
    char            reserve[64];            ///<预留空间
};

//////////////////////////////////////////////////////////////////////////
///担保品折算率查询请求结构体
//////////////////////////////////////////////////////////////////////////
struct EMTClientQueryCreditPledgeStkRateReq
{
    EMT_MARKET_TYPE market;                 ///< 证券市场
    char            ticker[EMT_TICKER_LEN]; ///< 证券代码
};

//////////////////////////////////////////////////////////////////////////
///担保品折算率查询应答结构体
//////////////////////////////////////////////////////////////////////////
struct EMTClientQueryCreditPledgeStkRateRsp
{
    EMT_MARKET_TYPE market;      ///< 证券市场
    char ticker[EMT_TICKER_LEN]; ///< 证券代码
    double pledge_rate;          ///< 担保品折算率
};

//////////////////////////////////////////////////////////////////////////
///保证金率查询请求结构体
//////////////////////////////////////////////////////////////////////////
struct EMTClientQueryCreditMarginRateReq
{
    EMT_MARKET_TYPE market;                 ///< 证券市场
    char            ticker[EMT_TICKER_LEN]; ///< 证券代码
};

//////////////////////////////////////////////////////////////////////////
///保证金率查询应答结构体
//////////////////////////////////////////////////////////////////////////
struct EMTClientQueryCreditMarginRateRsp
{
    EMT_MARKET_TYPE market;                     ///< 证券市场
    char ticker[EMT_TICKER_LEN];                ///< 证券代码
    EMT_CREDIT_FUND_CTRL_TYPE  credit_fund_ctrl;///< 融资状态
    double margin_rate_fund;                    ///< 融资保证金比例
    EMT_CREDIT_STK_CTRL_TYPE   credit_stk_ctrl; ///< 融券状态
    double margin_rate_stk;                     ///< 融券保证金比例
};

//////////////////////////////////////////////////////////////////////////
///融券头寸全额占用费率查询请求结构体
//////////////////////////////////////////////////////////////////////////
struct EMTClientQueryCreditPositionFullRateReq
{
    EMT_MARKET_TYPE market;                     ///< 证券市场
    char            ticker[EMT_TICKER_LEN];     ///< 证券代码
};

//////////////////////////////////////////////////////////////////////////
///融券头寸全额占用费率查询应答结构体
//////////////////////////////////////////////////////////////////////////
struct EMTClientQueryCreditPositionFullRateRsp
{
    EMT_MARKET_TYPE market;                     ///< 证券市场
    char            ticker[EMT_TICKER_LEN];     ///< 证券代码
    double          fullrate;                   ///< 全额占用费率
    double          posistkprice;               ///< 首次调拨的收盘价
    char            reserve[56];                ///< 预留字段
};

//////////////////////////////////////////////////////////////////////////
///分页查询请求头
//////////////////////////////////////////////////////////////////////////
struct EMTPaginationReqHeader
{
    int32_t page;                               ///< 页码
    int32_t count;                              ///< 单次请求的数量
};

//////////////////////////////////////////////////////////////////////////
///分页查询应答头
//////////////////////////////////////////////////////////////////////////
struct EMTPaginationRspHeader
{
    int32_t total_pages;                        ///< 总页数   = 总记录数 / 当前每页请求数量
    int32_t page;                               ///< 当前页
    int32_t total_count;                        ///< 总记录数
    int32_t count;                              ///< 本次查询实际返回数量
};


struct EMTQueryByLocationIDRspHeader
{
    uint64_t m_nTotalCount;                         ///< 本次查询总数量
    uint64_t m_nCount;                              ///< 本次查询实际返回数量
    uint64_t m_nErrId;                              ///< errorid
};

//////////////////////////////////////////////////////////////////////////
///证券代码信息通用结构体
//////////////////////////////////////////////////////////////////////////
struct EMTClientQueryTickerInfo
{
    EMT_MARKET_TYPE market;                     ///< 交易市场
    char ticker[EMT_TICKER_LEN];                ///< 证券代码
};

//////////////////////////////////////////////////////////////////////////
///融资融券可担保证券查询请求结构体
//////////////////////////////////////////////////////////////////////////
typedef EMTQueryByPageReq EMTClientQueryCreditPledgeStkByPageReq;

//////////////////////////////////////////////////////////////////////////
///融资融券可担保证券查询应答结构体
//////////////////////////////////////////////////////////////////////////
struct EMTClientQueryCreditPledgeStkRsp
{
    EMT_MARKET_TYPE           market;                   ///< 交易市场
    char                      ticker[EMT_TICKER_LEN];   ///< 证券代码
};

//////////////////////////////////////////////////////////////////////////
///融资融券标的证券查询请求结构体
//////////////////////////////////////////////////////////////////////////
typedef EMTQueryByPageReq EMTClientQueryCreditTargetStkByPageReq;

//////////////////////////////////////////////////////////////////////////
///融资融券标的证券查询应答结构体
//////////////////////////////////////////////////////////////////////////
struct EMTClientQueryCreditTargetStkRsp
{
    EMT_MARKET_TYPE           market;                   ///< 交易市场
    char                      ticker[EMT_TICKER_LEN];   ///< 证券代码
    EMT_CREDIT_FUND_CTRL_TYPE credit_fund_ctrl;         ///< 融资状态
    EMT_CREDIT_STK_CTRL_TYPE  credit_stk_ctrl;          ///< 融券状态
};

///期权组合策略新订单请求
struct EMTOptCombOrderInsertInfo
{
    ///EMT系统订单ID，无需用户填写，在EMT系统中唯一
    uint64_t                order_emt_id;
    ///报单引用，由客户自定义
    uint32_t                order_client_id;
    ///交易市场
    EMT_MARKET_TYPE         market;
    ///数量(单位为份)
    int64_t                 quantity;

    ///组合方向
    EMT_SIDE_TYPE           side;

    ///业务类型
    EMT_BUSINESS_TYPE_EXT   business_type;
    ///算法类型, 无需用户填写
    uint8_t                 algorithm_type;
    ///保留字段
    char                    reserved[2];

    ///期权组合策略信息
    EMTOptCombPlugin        opt_comb_info;
};

///期权组合策略报单响应结构体
struct EMTOptCombOrderInfo
{
    ///EMT系统订单ID，在EMT系统中唯一
    uint64_t                order_emt_id;
    ///报单引用，用户自定义
    uint32_t                order_client_id;
    ///报单操作引用，用户自定义（暂未使用）
    uint32_t                order_cancel_client_id;
    ///撤单在EMT系统中的id，在EMT系统中唯一
    uint64_t                order_cancel_emt_id;
    ///证券代码
    ///char                    ticker[EMT_TICKER_LEN];
    ///交易市场
    EMT_MARKET_TYPE         market;
    ///数量，此订单的报单数量
    int64_t                 quantity;

    ///组合方向
    EMT_SIDE_TYPE               side;

    ///业务类型
    EMT_BUSINESS_TYPE_EXT   business_type;
    ///算法类型, 无需用户填写
    uint8_t                 algorithm_type;
    ///保留字段
    char                    reserved[2];
    ///今成交数量，为此订单累计成交数量
    int64_t                 qty_traded;
    ///剩余数量，当撤单成功时，表示撤单数量
    int64_t                 qty_left;
    ///委托时间，格式为YYYYMMDDHHMMSSsss
    int64_t                 insert_time;
    ///最后修改时间，格式为YYYYMMDDHHMMSSsss
    int64_t                 update_time;
    ///撤销时间，格式为YYYYMMDDHHMMSSsss
    int64_t                 cancel_time;
    ///成交金额，组合拆分涉及的保证金
    double                  trade_amount;
    ///本地报单编号 OMS生成的单号，不等同于order_emt_id，为服务器传到报盘的单号
    char                    order_local_id[EMT_LOCAL_ORDER_LEN];
    ///报单状态，订单响应中没有部分成交状态的推送，在查询订单结果中，会有部分成交状态
    EMT_ORDER_STATUS_TYPE   order_status;
    ///报单提交状态，OMS内部使用，用户无需关心
    EMT_ORDER_SUBMIT_STATUS_TYPE   order_submit_status;
    ///报单类型
    TEMTOrderTypeType       order_type;

    ///期权组合策略信息
    EMTOptCombPlugin        opt_comb_info;
};

///期权组合策略报单成交结构体
struct EMTOptCombTradeReport
{
    ///EMT系统订单ID，此成交回报相关的订单ID，在EMT系统中唯一
    uint64_t                 order_emt_id;
    ///报单引用
    uint32_t                 order_client_id;
    ///交易市场
    EMT_MARKET_TYPE          market;
    ///订单号，引入EMTID后，该字段实际和order_emt_id重复。接口中暂时保留。
    uint64_t                 local_order_id;
    ///成交编号，深交所唯一，上交所每笔交易唯一，当发现2笔成交回报拥有相同的exec_id，则可以认为此笔交易自成交
    char                     exec_id[EMT_EXEC_ID_LEN];
    ///数量，此次成交的数量，不是累计数量
    int64_t                  quantity;
    ///成交时间，格式为YYYYMMDDHHMMSSsss
    int64_t                  trade_time;
    ///成交金额，组合拆分涉及的保证金
    double                   trade_amount;
    ///成交序号 --回报记录号，每个交易所唯一,report_index+market字段可以组成唯一标识表示成交回报
    uint64_t                 report_index;
    ///报单编号 --交易所单号，上交所为空，深交所有此字段
    char                     order_exch_id[EMT_ORDER_EXCH_LEN];
    ///成交类型  --成交回报中的执行类型
    TEMTTradeTypeType        trade_type;
    ///组合方向
    EMT_SIDE_TYPE            side;
    ///业务类型
    EMT_BUSINESS_TYPE_EXT    business_type;
    ///算法类型, 无需用户填写
    uint8_t                  algorithm_type;
    ///保留字段
    char                     reserved[2];
    ///交易所交易员代码
    char                     branch_pbu[EMT_BRANCH_PBU_LEN];

    ///期权组合策略信息
    EMTOptCombPlugin         opt_comb_info;
};

//////////////////////////////////////////////////////////////////////////
///期权组合策略报单查询请求-条件查询
//////////////////////////////////////////////////////////////////////////
struct EMTQueryOptCombOrderReq
{
    ///组合编码（流水号），可以为空，如果为空，则默认查询时间段内的所有成交回报
    char      comb_num[EMT_SECONDARY_ORDER_ID_LEN];
    ///格式为YYYYMMDDHHMMSSsss，为0则默认当前交易日0点
    int64_t   begin_time;
    ///格式为YYYYMMDDHHMMSSsss，为0则默认当前时间
    int64_t   end_time;
};

///期权组合策略报单查询响应结构体
typedef struct EMTOptCombOrderInfo EMTQueryOptCombOrderRsp;

///查询期权组合策略订单请求-分页查询
struct EMTQueryOptCombOrderByPageReq
{
    ///需要查询的订单条数
    int64_t         req_count;
    ///上一次收到的查询订单结果中带回来的索引，如果是从头查询，请置0
    int64_t         reference;
    ///保留字段
    int64_t         reserved;
};

//////////////////////////////////////////////////////////////////////////
///查询期权组合策略成交报告请求-根据执行编号查询（保留字段）
//////////////////////////////////////////////////////////////////////////
struct EMTQueryOptCombReportByExecIdReq
{
    ///EMT订单系统ID
    uint64_t  order_emt_id;
    ///成交执行编号
    char  exec_id[EMT_EXEC_ID_LEN];
};

///查询期权组合策略成交回报请求-查询条件
struct EMTQueryOptCombTraderReq
{
    ///组合编码（流水号），可以为空，如果为空，则默认查询时间段内的所有成交回报
    char      comb_num[EMT_SECONDARY_ORDER_ID_LEN];
    ///开始时间，格式为YYYYMMDDHHMMSSsss，为0则默认当前交易日0点
    int64_t   begin_time;
    ///结束时间，格式为YYYYMMDDHHMMSSsss，为0则默认当前时间
    int64_t   end_time;
};

///成交回报查询响应结构体
typedef struct EMTOptCombTradeReport  EMTQueryOptCombTradeRsp;

///查询期权组合策略成交回报请求-分页查询
struct EMTQueryOptCombTraderByPageReq
{
    ///需要查询的成交回报条数
    int64_t         req_count;
    ///上一次收到的查询成交回报结果中带回来的索引，如果是从头查询，请置0
    int64_t         reference;
    ///保留字段
    int64_t         reserved;
};

// 期权行权/组合行权申报
struct EMTOptionExerciseOrderInsertInfo
{
    ///EMT系统订单ID，无需用户填写，在EMT系统中唯一
    uint64_t                order_emt_id;
    ///报单引用，由客户自定义
    uint32_t                order_client_id;
    ///客户端id, 无需用户填写
    uint8_t                 client_id;
    ///委托来源, 无需用户填写
    TEMTOrderSourceType     order_source;
    ///合约的张数
    int64_t                 quantity;
    ///业务类型 EMT_BUSINESS_TYPE_EXECUTE-行权 EMT_BUSINESS_TYPE_EXECUTE_COMBINE-组合行权
    EMT_BUSINESS_TYPE_EXT   business_type;
    ///算法类型, 无需用户填写
    uint8_t                 algorithm_type;
    ///保留字段
    char                    reserved[2];
    ///交易市场
    EMT_MARKET_TYPE         market;
    ///合约代码 客户端请求不带空格，以'\0'结尾 行权仅填写第一个，组合行权填写两个合约ID
    char                    ticker[2][EMT_TICKER_LEN];
};

///期权行权/组合行权申报响应结构体
struct EMTOptionExerciseOrderInfo
{
    ///EMT系统订单ID，在EMT系统中唯一
    uint64_t                order_emt_id;
    ///报单引用，用户自定义
    uint32_t                order_client_id;
    ///报单撤单引用，用户自定义（暂未使用）
    uint32_t                order_cancel_client_id;
    ///撤单在EMT系统中的id，在EMT系统中唯一
    uint64_t                order_cancel_emt_id;
    ///合约代码
    char                    ticker[2][EMT_TICKER_LEN];
    ///交易市场
    EMT_MARKET_TYPE         market;
    ///数量，此订单的报单数量
    int64_t                 quantity;
    ///委托来源
    TEMTOrderSourceType     order_source;
    ///客户端id
    uint8_t                 client_id;
    ///业务类型
    EMT_BUSINESS_TYPE_EXT   business_type;
    ///算法类型, 无需用户填写
    uint8_t                 algorithm_type;
    ///保留字段
    char                    reserved[2];
    ///剩余数量，当撤单成功时，表示撤单数量
    int64_t                 qty_left;
    ///委托时间，格式为YYYYMMDDHHMMSSsss
    int64_t                 insert_time;
    ///最后修改时间，格式为YYYYMMDDHHMMSSsss
    int64_t                 update_time;
    ///撤销时间，格式为YYYYMMDDHHMMSSsss
    int64_t                 cancel_time;
    ///本地报单编号 OMS生成的单号，不等同于order_emt_id，为服务器传到报盘的单号
    char                    order_local_id[EMT_LOCAL_ORDER_LEN];
    ///报单状态，订单响应中没有部分成交状态的推送，在查询订单结果中，会有部分成交状态
    EMT_ORDER_STATUS_TYPE   order_status;
    ///报单提交状态，OMS内部使用，用户可用此字段来区分撤单和报单
    EMT_ORDER_SUBMIT_STATUS_TYPE   order_submit_status;
    ///报单类型
    TEMTOrderTypeType       order_type;
};

///查询期权行权合并头寸请求结构体
struct EMTQueryOptCombExecPosReq
{
    ///市场
    EMT_MARKET_TYPE market;
    ///成分合约1代码
    char cntrt_code_1[EMT_TICKER_LEN];
    ///成分合约2代码
    char cntrt_code_2[EMT_TICKER_LEN];

};

///查询期权行权合并头寸的响应
struct EMTQueryOptCombExecPosRsp
{
    ///市场
    EMT_MARKET_TYPE                 market;
    ///成分合约1代码
    char                            cntrt_code_1[EMT_TICKER_LEN];
    ///成分合约1名称
    char                            cntrt_name_1[EMT_TICKER_NAME_LEN];
    ///成分合约1持仓方向
    EMT_POSITION_DIRECTION_TYPE     position_side_1;
    ///成分合约1类型
    EMT_OPT_CALL_OR_PUT_TYPE        call_or_put_1;
    ///成分合约1可用持仓数量
    int64_t                         avl_qty_1;
    ///成分合约1昨日持仓数量
    int64_t                         orig_own_qty_1;
    ///成分合约1当前持仓数量
    int64_t                         own_qty_1;
    ///成分合约2代码
    char                            cntrt_code_2[EMT_TICKER_LEN];
    ///成分合约2名称
    char                            cntrt_name_2[EMT_TICKER_NAME_LEN];
    ///成分合约2持仓方向
    EMT_POSITION_DIRECTION_TYPE     position_side_2;
    ///成分合约2类型
    EMT_OPT_CALL_OR_PUT_TYPE        call_or_put_2;
    ///成分合约2可用持仓数量
    int64_t                         avl_qty_2;
    ///成分合约2昨日持仓数量
    int64_t                         orig_own_qty_2;
    ///成分合约2当前持仓数量
    int64_t                         own_qty_2;
    ///权利仓净头寸
    int64_t                         net_qty;
    ///行权合并委托数量，不含已拒单已撤单
    int64_t                         order_qty;
    ///行权合并已确认数量
    int64_t                         confirm_qty;
    ///可行权合并数量
    int64_t                         avl_qty;
    ///保留字段
    uint64_t                        reserved[49];
};

//////////////////////////////////////////////////////////////////////////
///查询当日可申购配股配债信息
//////////////////////////////////////////////////////////////////////////
struct EMTQueryIssueTickerRsp {
    ///交易市场
    EMT_MARKET_TYPE     market;
    ///申购代码
    char                ticker[EMT_TICKER_LEN];
    ///申购股票名称
    char                ticker_name[EMT_TICKER_NAME_LEN];
    /// 证券类别
    EMT_TICKER_TYPE     ticker_type;
    ///基础证券代码
    char                under_ticker[EMT_TICKER_LEN];
    ///申购价格
    double              price;
    ///申购单元
    int32_t             unit;
    ///最大允许申购数量
    int32_t             qty_upper_limit;
};

//////////////////////////////////////////////////////////////////////////
///查询证券基础信息请求结构体
//////////////////////////////////////////////////////////////////////////
struct EMTQuerySecurityInfoReq
{
    ///证券代码
    char                ticker[EMT_TICKER_LEN];
    ///交易市场
    EMT_MARKET_TYPE     market;
};

//////////////////////////////////////////////////////////////////////////
///查询证券基础信息应答结构体
//////////////////////////////////////////////////////////////////////////
struct EMTQuerySecurityInfoRsp
{
    ///证券代码
    char                ticker[EMT_TICKER_LEN];
    ///证券名称
    char                ticker_name[EMT_TICKER_NAME_LEN];
    ///交易市场
    EMT_MARKET_TYPE     market;
    ///证券类别
    EMT_TICKER_TYPE     ticker_type;
    ///数量单位
    int64_t             qty_unit;
    ///是否支持当日回转交易，true:当日可回转交易；false:当日不可回转交易
    bool                day_trading;
    ///涨幅上限价格
    double              highest_price;
    ///跌幅下限价格
    double              minimum_price;
    ///应计利息(债券有意义)
    double              interest;
    ///价格单位
    double              price_unit;
};

//////////////////////////////////////////////////////////////////////////
///分页请求查询标的基础信息应答结构体
//////////////////////////////////////////////////////////////////////////
typedef EMTQuerySecurityInfoRsp EMTQuerySecurityByPageRsp;

//////////////////////////////////////////////////////////////////////////
///指定偿还负债请求结构体
//////////////////////////////////////////////////////////////////////////
struct EMTCrdRepaySpecifiedDebtReq
{
    ///EMT系统订单ID，无需用户填写，在EMT系统中唯一
    uint64_t            order_emt_id;
    ///申请偿还金额
    double              request_amount;
    ///开仓日期
    int32_t             order_date;
    ///负债合约编号
    char                debt_id[16];
    ///预留
    char                reserve[32];
};

//////////////////////////////////////////////////////////////////////////
///指定偿还负债应答结构体
//////////////////////////////////////////////////////////////////////////
struct EMTCrdRepaySpecifiedDebtRsp
{
    ///EMT订单系统ID
    uint64_t            order_emt_id;
    ///还款的申请金额
    double              request_amount;
    ///实际偿还使用金额
    double              cash_repay_amount;
    ///开仓日期
    int32_t             order_date;
    ///负债合约编号
    char                debt_id[16];
    ///预留字段
    char                reserved[16];
};

//////////////////////////////////////////////////////////////////////////
///查询港股通参考汇率信息响应结构体
//////////////////////////////////////////////////////////////////////////
struct EMTQueryHKConnectIndicativeExchangeRateInfoRsp{
    ///深港通买入参考汇率
    double sz_hk_connect_bid;
    ///深港通卖出参考汇率
    double sz_hk_connect_offer;
    ///沪港通买入参考汇率
    double sh_hk_connect_bid;
    ///沪港通卖出参考汇率
    double sh_hk_connect_offer;
};

//////////////////////////////////////////////////////////////////////////
///查询港股通最小价差信息请求结构体
//////////////////////////////////////////////////////////////////////////
struct EMTQueryHkConnectSpreadTableReq{
    ///证券类别
    EMT_TICKER_TYPE     ticker_type;
};

//////////////////////////////////////////////////////////////////////////
///查询港股通最小价差信息响应结构体
//////////////////////////////////////////////////////////////////////////
struct EMTQueryHkConnectSpreadTableRsp{
    ///证券类别
    EMT_TICKER_TYPE     ticker_type;
    ///当前价差对应最小报价(包括该最小报价)
    double              min_price;
    ///当前价差对应最大报价(不包括该最大报价)
    double              max_price;
    ///价差
    double              spread;
};

//////////////////////////////////////////////////////////////////////////
///持仓变动通知结构体
//////////////////////////////////////////////////////////////////////////
struct EMTHoldingChangeInfo{
    char ticker[EMT_TICKER_LEN];                ///< 证券代码
    EMT_MARKET_TYPE market;                     ///< 交易市场
    EMT_HOLDING_CHANGE_TYPE change_type;        ///< 变动类型
    int32_t change_time;                        ///< 变动时间，格式为HHMMSS
    int64_t total_change_qty;                   ///< 总变动数量(正数:增加; 负数:减少; 0:不变)
    int64_t avl_sell_change_qty;                ///< 可用变动数量(正数:增加; 负数:减少; 0:不变)
    int64_t avl_redemption_change_qty;          ///< 可赎回变动数量(正数:增加; 负数:减少; 0:不变)
    int64_t avl_component_change_qty;           ///< 可作为ETF成份证券变动数量(正数:增加; 负数:减少; 0:不变)
};

//////////////////////////////////////////////////////////////////////////
///融券负债当日应还查询请求结构体
//////////////////////////////////////////////////////////////////////////
struct EMTClientQueryCreditDebtToRepayTodayByPageReq{
    int64_t         req_count;                  ///< 需要查询的条数
    int64_t         reference;                  ///< 上一次收到的查询订单结果中带回来的索引，如果是从头查询，请置0
    EMT_MARKET_TYPE market;                     ///< 证券市场
    char            ticker[EMT_TICKER_LEN];     ///< 证券代码
    char            reserve[12];                ///< 预留字段
};

//////////////////////////////////////////////////////////////////////////
///融券负债当日应还查询应答结构体
//////////////////////////////////////////////////////////////////////////
struct EMTClientQueryCreditDebtToRepayTodayByPageRsp{
    EMT_MARKET_TYPE    market;                  ///< 证券市场
    char               ticker[EMT_TICKER_LEN];  ///< 证券代码
    int64_t            stk_repay_qty;           ///< 融券可还券数量
    int64_t            stk_repay_total;         ///< 融券未偿还数量
    int64_t            to_repay_today;          ///< 当日应还数量
    int64_t            repay_today;             ///< 当日已还数量
    int64_t            to_repay_today_left;     ///< 剩余当日应还数量
    char               reserve[36];             ///< 预留字段
};

#pragma pack()
#endif //_EOMS_API_STRUCT_H_

