/////////////////////////////////////////////////////////////////////////
///@author 中泰证券股份有限公司
///@file algo_api_struct.h
///@brief 定义业务公共数据结构
/////////////////////////////////////////////////////////////////////////
#ifndef _XTP_ALGO_API_STRUCT_H_
#define _XTP_ALGO_API_STRUCT_H_

#include "algo_data_type.h"
#include "xtp_api_struct_common.h"

#pragma pack(8)

///策略信息结构体
typedef struct XTPStrategyInfoStruct
{
	uint16_t				m_strategy_type;		///< 策略类型
	XTPStrategyStateType	m_strategy_state;		///< 策略状态
	uint64_t				m_client_strategy_id;	///< 客户策略id
	uint64_t				m_xtp_strategy_id;		///< xtp策略id
} XTPStrategyInfoStruct;

///策略中指定证券信息结构体
typedef struct XTPStrategySymbolInfoStruct
{
	XTPStrategyInfoStruct	m_strategy_info;			///< 策略信息
	char					m_ticker[XTP_TICKER_LEN];	///< 证券代码
	XTP_MARKET_TYPE			m_market;					///< 市场
} XTPStrategySymbolInfo;

///策略状态结构体
typedef struct XTPStrategyStateReportStruct
{
	XTPStrategyInfoStruct		m_strategy_info;			///< 策略信息	
	int64_t						m_strategy_qty;				///< 策略总量
	int64_t						m_strategy_ordered_qty;		///< 策略已委托数量
	int64_t						m_strategy_cancelled_qty;	///< 策略已撤单数量
	int64_t						m_strategy_execution_qty;	///< 策略已成交数量
	int64_t						m_strategy_unclosed_qty;	///< 策略未平仓数量(T0卖出数量-买入数量)
	double						m_strategy_asset;			///< 策略总金额
	double						m_strategy_ordered_asset;	///< 策略已委托金额
	double						m_strategy_execution_asset;	///< 策略已成交金额
	double						m_strategy_execution_price;	///< 策略执行价格
	double						m_strategy_market_price;	///< 策略市场价
	double						m_strategy_price_diff;		///< 策略执行价差	
	double						m_strategy_asset_diff;		///< 策略执行绩效(T0资金预净收入)
	XTPRI						m_error_info;				///< 错误信息
} XTPStrategyStateReport;

///指定策略指定证券的请求结构体
typedef struct XTPStrategySymbolReqStruct
{
	uint64_t		m_xtp_strategy_id;			///< xtp策略id
	char			m_ticker[XTP_TICKER_LEN];	///< 证券代码
	XTP_MARKET_TYPE m_market;					///< 市场
} XTPStrategySymbolReq;

///策略中指定证券的算法执行状态结构体
typedef struct XTPStrategySymbolStateReportStruct
{
	XTPStrategyInfoStruct		m_strategy_info;			///< 策略信息
	char						m_ticker[XTP_TICKER_LEN];	///< 证券代码
	XTP_MARKET_TYPE				m_market;					///< 市场
	XTP_SIDE_TYPE				m_side;						///< 买卖方向，=0时为T0单
	int64_t						m_strategy_qty;				///< 策略总量
	int64_t						m_strategy_ordered_qty;		///< 策略已委托数量
	int64_t						m_strategy_cancelled_qty;	///< 策略已撤单数量
	int64_t						m_strategy_execution_qty;	///< 策略已成交数量
	int64_t						m_strategy_buy_qty;			///< 策略已买入数量(T0)
	int64_t						m_strategy_sell_qty;		///< 策略已卖出数量(T0)
	int64_t						m_strategy_unclosed_qty;	///< 策略未平仓数量(T0卖出数量-买入数量)
	double						m_strategy_asset;			///< 策略总金额
	double						m_strategy_ordered_asset;	///< 策略已委托金额
	double						m_strategy_execution_asset;	///< 策略已成交金额
	double						m_strategy_buy_asset;		///< 策略买入金额(T0)
	double						m_strategy_sell_asset;		///< 策略卖出金额(TO)
	double						m_strategy_unclosed_asset;	///< 策略未平仓金额(T0)
	double						m_strategy_asset_diff;		///< 策略毛收益增强金额(T0)
	double						m_strategy_execution_price;	///< 策略执行价格
	double						m_strategy_market_price;	///< 策略市场价
	double						m_strategy_price_diff;		///< 策略执行价差(T0时为毛增强收益率)	
	XTPRI						m_error_info;				///< 错误信息
} XTPStrategySymbolStateReport;

///推荐算法结构体
typedef struct XTPStrategyRecommendationInfoStruct
{
	uint16_t					m_strategy_type;			///< 策略类型
	XTP_MARKET_TYPE				m_market;					///< 交易市场
	char						m_ticker[XTP_TICKER_LEN];	///< 证券代码
	char						m_reserved[64];				///< 保留域
} XTPStrategyRecommendationInfo;

#pragma pack()

#endif //_XTP_ALGO_API_STRUCT_H_
