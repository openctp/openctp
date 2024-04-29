//该文件定义了TapTradeAPI 使用的数据类型和数据结构
#ifndef TAP_TRADE_API_DATA_TYPE_H
#define TAP_TRADE_API_DATA_TYPE_H
#include "TapAPICommDef.h"

#pragma pack(push, 1)


//=============================================================================
/**
 *	\addtogroup G_DATATYPE_T_TAPIACCOUNTTYPE	账号类型
 *	@{
 */
//=============================================================================
//! 账号类型
typedef TAPICHAR			TAPIAccountType;
//! 个人客户
const TAPIAccountType		TAPI_ACCOUNT_TYPE_PERSON				= 'P';
//! 机构客户
const TAPIAccountType		TAPI_ACCOUNT_TYPE_ORGANIZATION		    = 'O';
/** @}*/

//=============================================================================
/**
*	\addtogroup G_DATATYPE_T_TAPIRIGHTIDTYPE	权限编码类型
*	@{
*/
//=============================================================================
//! 权限编码类型
typedef TAPIINT32			TAPIRightIDType;
//! 系统删单
const TAPIRightIDType		TAPI_RIGHT_ORDER_DEL	= 30001;
//! 订单审核
const TAPIRightIDType		TAPI_RIGHT_ORDER_CHECK	= 30002;
//! 只可查询
const TAPIRightIDType		TAPI_RIGHT_ONLY_QRY		= 31000;
//! 只可开仓
const TAPIRightIDType		TAPI_RIGHT_ONLY_OPEN	= 31001;
//! 上期查挂单
const TAPIRightIDType		TAPI_RIGHT_SHFE_QUOTE	= 31002;
/** @}*/

//=============================================================================
/**
 *	\addtogroup G_DATATYPE_T_TAPIUSERTYPETYPE	登录用户身份类型
 *	@{
 */
//=============================================================================
//! 登录用户身份类型
typedef TAPIINT32			TAPIUserTypeType;
//! 投资者用户
const TAPIUserTypeType		TAPI_USERTYPE_CLIENT					=10000;
//! 经纪人
const TAPIUserTypeType		TAPI_USERTYPE_BROKER					=20000;
//! 交易员
const TAPIUserTypeType		TAPI_USERTYPE_TRADER					=30000;
//! 风控
const TAPIUserTypeType		TAPI_USERTYPE_RISK						=40000;
//! 管理员
const TAPIUserTypeType		TAPI_USERTYPE_MANAGER					=50000;
//! 行情
const TAPIUserTypeType		TAPI_USERTYPE_QUOTE						=60000;
/** @}*/

//=============================================================================
/**
 *	\addtogroup G_DATATYPE_T_TAPIACCOUNTSTATE	账号状态
 *	@{
 */
//=============================================================================
//! 账号状态
typedef TAPICHAR			TAPIAccountState;
//! 正常
const TAPIAccountState		TAPI_ACCOUNT_STATE_NORMAL				= 'N';
//! 销户
const TAPIAccountState		TAPI_ACCOUNT_STATE_CANCEL				= 'C';
//! 休眠
const TAPIAccountState		TAPI_ACCOUNT_STATE_SLEEP               = 'S';
/** @}*/

//=============================================================================
/**
 *	\addtogroup G_DATATYPE_T_TAPIACCOUNTFAMILYTYPE	父子账户类型
 *	@{
 */
//=============================================================================
//! 父子账户类型
typedef TAPICHAR			TAPIAccountFamilyType;
//! 正常账号
const	TAPIAccountFamilyType	TAPI_ACCOUNT_FAMILYTYPE_NOMAL	='N';
//! 子账户
const	TAPIAccountFamilyType	TAPI_ACCOUNT_FAMILYTYPE_CHILD	='C';
/** @}*/

//=============================================================================
/**
 *	\addtogroup G_DATATYPE_T_TAPIORDERTYPETYPE	委托类型
 *	@{
 */
//=============================================================================
//! 委托类型
typedef TAPICHAR				TAPIOrderTypeType;
//! 市价
const TAPIOrderTypeType			TAPI_ORDER_TYPE_MARKET				= '1';
//! 限价
const TAPIOrderTypeType			TAPI_ORDER_TYPE_LIMIT				= '2';
//! 市价止损
const TAPIOrderTypeType			TAPI_ORDER_TYPE_STOP_MARKET			= '3';
//! 限价止损
const TAPIOrderTypeType			TAPI_ORDER_TYPE_STOP_LIMIT			= '4';
//! 期权行权
const TAPIOrderTypeType			TAPI_ORDER_TYPE_OPT_EXEC			= '5';
//! 期权弃权
const TAPIOrderTypeType			TAPI_ORDER_TYPE_OPT_ABANDON			= '6';
//! 询价
const TAPIOrderTypeType			TAPI_ORDER_TYPE_REQQUOT				= '7';
//! 应价
const TAPIOrderTypeType			TAPI_ORDER_TYPE_RSPQUOT				= '8';
//! 互换
const TAPIOrderTypeType			TAPI_ORDER_TYPE_SWAP				= '9';
//! 组合申请
const TAPIOrderTypeType			TAPI_ORDER_TYPE_COMB                = 'A';
//! 拆分申请
const TAPIOrderTypeType			TAPI_ORDER_TYPE_UNCOMB              = 'B';
//! 市价止盈
const TAPIOrderTypeType			TAPI_ORDER_TYPE_PROFIT_MARKET       = 'C';
//! 限价止盈
const TAPIOrderTypeType			TAPI_ORDER_TYPE_PROFIT_LIMIT        = 'D';
//! 套保申请
const TAPIOrderTypeType			TAPI_ORDER_TYPE_HEDGE               = 'E';
//! 期权自对冲
const TAPIOrderTypeType			TAPI_ORDER_TYPE_OPTION_AUTO_CLOSE   = 'F';
//! 履约期货自对冲
const TAPIOrderTypeType			TAPI_ORDER_TYPE_FUTURE_AUTO_CLOSE   = 'G';
//! 上期所做市商留仓申请
const TAPIOrderTypeType			TAPI_ORDER_TYPE_MARKET_POSITION_KEEP = 'H';
//! 大商所取消到日期自动行权
const TAPIOrderTypeType			TAPI_ORDER_TYPE_OPTION_AUTOEXEC_ABAND = 'I';
/** @}*/

//=============================================================================
/**
 *	\addtogroup G_DATATYPE_T_TAPIORDERSOURCETYPE	委托来源
 *	@{
 */
//=============================================================================
//! 委托来源
typedef TAPICHAR				TAPIOrderSourceType;
//! 自助电子单
const TAPIOrderSourceType		TAPI_ORDER_SOURCE_SELF_ETRADER			= '1';
//! 代理电子单
const TAPIOrderSourceType		TAPI_ORDER_SOURCE_PROXY_ETRADER			= '2';
//! 外部电子单(外部电子系统下单，本系统录入)
const TAPIOrderSourceType		TAPI_ORDER_SOURCE_JTRADER				= '3';
//! 人工录入单(外部其他方式下单，本系统录入)
const TAPIOrderSourceType		TAPI_ORDER_SOURCE_MANUAL				= '4';
//! carry单
const TAPIOrderSourceType		TAPI_ORDER_SOURCE_CARRY					= '5';
//! 程式化报单
const TAPIOrderSourceType		TAPI_ORDER_SOURCE_PROGRAM				= '6';
//! 交割行权
const TAPIOrderSourceType		TAPI_ORDER_SOURCE_DELIVERY				= '7';
//! 期权放弃
const TAPIOrderSourceType		TAPI_ORDER_SOURCE_ABANDON				= '8';
//! 通道费
const TAPIOrderSourceType		TAPI_ORDER_SOURCE_CHANNEL				= '9';
//! 易盛API
const TAPIOrderSourceType		TAPI_ORDER_SOURCE_ESUNNY_API			= 'A';
//! 易盛V8客户端
const TAPIOrderSourceType		TAPI_ORDER_SOURCE_ESV8CLIENT			= 'B';
//! 易盛极星客户端
const TAPIOrderSourceType		TAPI_ORDER_SOURCE_EPOLESTAR 			= 'F';
//! 易盛易星客户端
const TAPIOrderSourceType		TAPI_ORDER_SOURCE_ESTAR	    			= 'D';
//! 大商所期权行权后对冲
const TAPIOrderSourceType		TAPI_ORDER_SOURCE_DCEAFTEREX            = 'E';
//! 期权履约
const TAPIOrderSourceType		TAPI_ORDER_SOURCE_COMPLIANCE            = 'C';
//! 期权对冲
const TAPIOrderSourceType		TAPI_ORDER_SOURCE_OPTIONHEDGE           = 'I';
//! 期货对冲
const TAPIOrderSourceType		TAPI_ORDER_SOURCE_FUTUREHEDGE           = 'J';
//! 行权开仓
const TAPIOrderSourceType		TAPI_ORDER_SOURCE_OPTIONEXCE            = 'K';
//! 易盛api UDP方式
const TAPIOrderSourceType		TAPI_ORDER_SOURCE_ESUNNY_API_UDP        = 'G';
/** @}*/

//=============================================================================
/**
 *	\addtogroup G_DATATYPE_T_TAPITIMEINFORCETYPE	委托有效类型
 *	@{
 */
//=============================================================================
//! 委托有效类型
typedef TAPICHAR				TAPITimeInForceType;
//! 当日有效
const TAPITimeInForceType		TAPI_ORDER_TIMEINFORCE_GFD					= '0';
//! 取消前有效
const TAPITimeInForceType		TAPI_ORDER_TIMEINFORCE_GTC					= '1';
//! 指定日期前有效
const TAPITimeInForceType		TAPI_ORDER_TIMEINFORCE_GTD					= '2';
//! FAK或IOC
const TAPITimeInForceType		TAPI_ORDER_TIMEINFORCE_FAK					= '3';
//! FOK
const TAPITimeInForceType		TAPI_ORDER_TIMEINFORCE_FOK					= '4';
/** @}*/

//=============================================================================
/**
 *	\addtogroup G_DATATYPE_T_TAPISIDETYPE	买卖类型
 *	@{
 */
//=============================================================================
//! 买卖类型
typedef TAPICHAR				TAPISideType;
//! 无
const TAPISideType				TAPI_SIDE_NONE							= 'N';
//! 买入
const TAPISideType				TAPI_SIDE_BUY							= 'B';
//! 卖出
const TAPISideType				TAPI_SIDE_SELL							= 'S';
//! 双边
const TAPISideType				TAPI_SIDE_ALL    						= 'A';
/** @}*/

//=============================================================================
/**
 *	\addtogroup G_DATATYPE_T_TAPIPOSITIONEFFECTTYPE	开平类型
 *	@{
 */
//=============================================================================
//! 开平类型
typedef TAPICHAR				TAPIPositionEffectType;
//! 不分开平
const TAPIPositionEffectType	TAPI_PositionEffect_NONE				= 'N';
//! 开仓
const TAPIPositionEffectType	TAPI_PositionEffect_OPEN				= 'O';
//! 平仓
const TAPIPositionEffectType	TAPI_PositionEffect_COVER			= 'C';
//! 平当日
const TAPIPositionEffectType	TAPI_PositionEffect_COVER_TODAY		= 'T';
/** @}*/

//=============================================================================
/**
 *	\addtogroup G_DATATYPE_T_TAPIHEDGEFLAGTYPE	投机保值类型
 *	@{
 */
//=============================================================================
//! 投机保值类型
typedef TAPICHAR				TAPIHedgeFlagType;
//! 无
const TAPIHedgeFlagType			TAPI_HEDGEFLAG_NONE					= 'N';
//! 投机
const TAPIHedgeFlagType			TAPI_HEDGEFLAG_T					= 'T';
//! 保值
const TAPIHedgeFlagType			TAPI_HEDGEFLAG_B					= 'B';
//! 套利
const TAPIHedgeFlagType			TAPI_HEDGEFLAG_L					= 'L';
/** @}*/

//=============================================================================
/**
 *	\addtogroup G_DATATYPE_T_TAPIORDERSTATETYPE	委托状态类型
 *	@{
 */
//=============================================================================
//! 委托状态类型
typedef TAPICHAR				TAPIOrderStateType;
//! 终端提交
const TAPIOrderStateType		TAPI_ORDER_STATE_SUBMIT				= '0';
//! 已受理
const TAPIOrderStateType		TAPI_ORDER_STATE_ACCEPT				= '1';
//! 策略待触发
const TAPIOrderStateType		TAPI_ORDER_STATE_TRIGGERING			= '2';
//! 交易所待触发
const TAPIOrderStateType		TAPI_ORDER_STATE_EXCTRIGGERING		= '3';
//! 已排队
const TAPIOrderStateType		TAPI_ORDER_STATE_QUEUED				= '4';
//! 部分成交
const TAPIOrderStateType		TAPI_ORDER_STATE_PARTFINISHED		= '5';
//! 完全成交
const TAPIOrderStateType		TAPI_ORDER_STATE_FINISHED			= '6';
//! 待撤消(排队临时状态)
const TAPIOrderStateType		TAPI_ORDER_STATE_CANCELING			= '7';
//! 待修改(排队临时状态)
const TAPIOrderStateType		TAPI_ORDER_STATE_MODIFYING			= '8';
//! 完全撤单
const TAPIOrderStateType		TAPI_ORDER_STATE_CANCELED			= '9';
//! 已撤余单
const TAPIOrderStateType		TAPI_ORDER_STATE_LEFTDELETED		= 'A';
//! 指令失败
const TAPIOrderStateType		TAPI_ORDER_STATE_FAIL				= 'B';
//! 策略删除
const TAPIOrderStateType		TAPI_ORDER_STATE_DELETED			= 'C';
//! 已挂起
const TAPIOrderStateType		TAPI_ORDER_STATE_SUPPENDED			= 'D';
//! 到期删除
const TAPIOrderStateType		TAPI_ORDER_STATE_DELETEDFOREXPIRE	= 'E';
//! 已生效——询价成功
const TAPIOrderStateType		TAPI_ORDER_STATE_EFFECT				= 'F';
//! 已申请——行权、弃权、套利等申请成功
const TAPIOrderStateType		TAPI_ORDER_STATE_APPLY				= 'G';
//! 系统删除，已受理订单修改为系统删除
const TAPIOrderStateType		TAPI_ORDER_STATE_SYSTEMDELETED      = 'H';
//! 待审核
const TAPIOrderStateType		TAPI_ORDER_STATE_CHECKING			= 'I';
//! 闭市撤单
const TAPIOrderStateType		TAPI_ORDER_STATE_CLOSECANCELED      = 'J';
/** @}*/

//=============================================================================
/**
 *	\addtogroup G_DATATYPE_T_TAPICALCULATEMODETYPE	计算方式
 *	@{
 */
//=============================================================================
//! 计算方式
typedef TAPICHAR               TAPICalculateModeType;
//! 比例
const TAPICalculateModeType		TAPI_CALCULATE_MODE_PERCENTAGE          = '1';
//! 定额
const TAPICalculateModeType		TAPI_CALCULATE_MODE_QUOTA               = '2';
//! 绝对方式
const TAPICalculateModeType		TAPI_CALCULATE_MODE_ABSOLUTE		= '7';
/** @}*/

//=============================================================================
/**
 *	\addtogroup G_DATATYPE_T_TAPIMATCHSOURCETYPE	成交来源
 *	@{
 */
//=============================================================================
//! 成交来源
typedef TAPICHAR				TAPIMatchSourceType;
//! 全部
const TAPIMatchSourceType		TAPI_MATCH_SOURCE_ALL                   = '0';
//! 自助电子单
const TAPIMatchSourceType		TAPI_MATCH_SOURCE_SELF_ETRADER          = '1';
//! 代理电子单
const TAPIMatchSourceType		TAPI_MATCH_SOURCE_PROXY_ETRADER         = '2';
//! 外部电子单
const TAPIMatchSourceType		TAPI_MATCH_SOURCE_JTRADER				= '3';
//! 人工录入单
const TAPIMatchSourceType		TAPI_MATCH_SOURCE_MANUAL				= '4';
//! carry单
const TAPIMatchSourceType		TAPI_MATCH_SOURCE_CARRY					= '5';
//! 程式化单
const TAPIMatchSourceType		TAPI_MATCH_SOURCE_PROGRAM				= '6';
//! 交割行权
const TAPIMatchSourceType		TAPI_MATCH_SOURCE_DELIVERY				= '7';
//! 期权放弃
const TAPIMatchSourceType		TAPI_MATCH_SOURCE_ABANDON				= '8';
//! 通道费
const TAPIMatchSourceType		TAPI_MATCH_SOURCE_CHANNEL				= '9';
//! 易盛API
const TAPIMatchSourceType		TAPI_MATCH_SOURCE_ESUNNY_API			= 'A';
//! 易盛V8客户端
const TAPIMatchSourceType		TAPI_MATCH_SOURCE_ESV8CLIENT            = 'B';
//! 易盛极星客户端
const TAPIMatchSourceType		TAPI_MATCH_SOURCE_EPOLESTAR             = 'F';
//! 易盛易星客户端
const TAPIMatchSourceType		TAPI_MATCH_SOURCE_ESTAR                 = 'D';
//! 大商所期权行权后对冲
const TAPIMatchSourceType		TAPI_MATCH_SOURCE_DCEAFTEREX		    = 'E';
//! 期权履约
const TAPIMatchSourceType		TAPI_MATCH_SOURCE_COMPLIANCE			= 'C';
//! 期权对冲
const TAPIMatchSourceType		TAPI_MATCH_SOURCE_OPTIONHEDGE			= 'I';
//! 期货对冲
const TAPIMatchSourceType		TAPI_MATCH_SOURCE_FUTUREHEDGE			= 'J';
//! 行权开仓
const TAPIMatchSourceType		TAPI_MATCH_SOURCE_OPTIONEXCE			= 'K';
/** @}*/

//=============================================================================
/**
 *	\addtogroup G_DATATYPE_T_TAPIOPENCLOSEMODETYPE	开平方式
 *	@{
 */
//=============================================================================
//! 开平方式
typedef TAPICHAR				TAPIOpenCloseModeType;
//! 不区分开平
const TAPIOpenCloseModeType		TAPI_CLOSE_MODE_NONE				= 'N';
//! 平仓未了结
const TAPIOpenCloseModeType		TAPI_CLOSE_MODE_UNFINISHED			= 'U';
//! 区分开仓和平仓
const TAPIOpenCloseModeType		TAPI_CLOSE_MODE_OPENCOVER			= 'C';
//! 区分开仓、平仓和平今
const TAPIOpenCloseModeType		TAPI_CLOSE_MODE_CLOSETODAY			= 'T';
/** @}*/

//=============================================================================
/**
 *	\addtogroup G_DATATYPE_T_TAPIFUTUREALGTYPE	期货算法
 *	@{
 */
//=============================================================================
//! 期货算法
typedef TAPICHAR				TAPIFutureAlgType;
//! 逐笔
const TAPIFutureAlgType			TAPI_FUTURES_ALG_ZHUBI                  = '1';
//! 盯市
const TAPIFutureAlgType			TAPI_FUTURES_ALG_DINGSHI                = '2';
/** @}*/

//=============================================================================
/**
 *	\addtogroup G_DATATYPE_T_TAPIOPTIONALGTYPE	期权算法
 *	@{
 */
//=============================================================================
//! 期权算法
typedef TAPICHAR				TAPIOptionAlgType;
//! 期货方式
const TAPIOptionAlgType         TAPI_OPTION_ALG_FUTURES                 = '1';
//! 期权方式
const TAPIOptionAlgType         TAPI_OPTION_ALG_OPTION                  = '2';
/** @}*/

//=============================================================================
/**
 *	\addtogroup G_DATATYPE_T_TAPIBANKACCOUNTLWFLAGTYPE	本外币标识
 *	@{
 */
//=============================================================================
//! 本外币标识
typedef TAPICHAR				TAPIBankAccountLWFlagType;
//! 境内人民币账户
const TAPIBankAccountLWFlagType	TAPI_LWFlag_L					= 'L';
//! 客户境内外币账户
const TAPIBankAccountLWFlagType	TAPI_LWFlag_W					= 'W';
/** @}*/


//=============================================================================
/**
 *	\addtogroup G_DATATYPE_T_TAPIMARGINCALCULATEMODETYPE	期货保证金方式
 *	@{
 */
//=============================================================================
//! 期货保证金方式
typedef TAPICHAR				TAPIMarginCalculateModeType;
//! 分笔
const TAPIMarginCalculateModeType TAPI_DEPOSITCALCULATE_MODE_FEN     = '1';
//! 锁仓
const TAPIMarginCalculateModeType TAPI_DEPOSITCALCULATE_MODE_SUO     = '2';
/** @}*/

//=============================================================================
/**
 *	\addtogroup G_DATATYPE_T_TAPIOPTIONMARGINCALCULATEMODETYPE	期权保证金公式
 *	@{
 */
//=============================================================================
//! 期权保证金公式,据此判断该品种期权采用何种内置计算公式计算保证金
typedef TAPICHAR				TAPIOptionMarginCalculateModeType;
/** @}*/

//=============================================================================
/**
 *	\addtogroup G_DATATYPE_T_TAPICMBDIRECTTYPE	组合方向
 *	@{
 */
//=============================================================================
//! 组合方向,品种两腿组合合约的买卖方向和第几腿相同
typedef TAPICHAR				TAPICmbDirectType;
//! 和第一腿一致
const TAPICmbDirectType         TAPI_CMB_DIRECT_FIRST                    = '1';
//! 和第二腿一致
const TAPICmbDirectType         TAPI_CMB_DIRECT_SECOND                   = '2';
/** @}*/

//=============================================================================
/**
 *	\addtogroup G_DATATYPE_T_TAPIDELIVERYMODETYPE	交割行权方式
 *	@{
 */
//=============================================================================
//! 交割行权方式,期货和期权了结的方式
typedef TAPICHAR				TAPIDeliveryModeType;
//! 实物交割
const TAPIDeliveryModeType		TAPI_DELIVERY_MODE_GOODS			= 'G';
//! 现金交割
const TAPIDeliveryModeType		TAPI_DELIVERY_MODE_CASH				= 'C';
//! 期权行权
const TAPIDeliveryModeType		TAPI_DELIVERY_MODE_EXECUTE			= 'E';
//! 期权放弃
const TAPIDeliveryModeType		TAPI_DELIVERY_MODE_ABANDON			= 'A';
//! 港交所行权
const TAPIDeliveryModeType		TAPI_DELIVERY_MODE_HKF				= 'H';
/** @}*/

//=============================================================================
/**
 *	\addtogroup G_DATATYPE_T_TAPICONTRACTTYPETYPE	合约类型
 *	@{
 */
//=============================================================================
//! 合约类型
typedef TAPICHAR				TAPIContractTypeType;
//! 交易行情合约
const TAPIContractTypeType		TAPI_CONTRACT_TYPE_TRADEQUOTE		='1';
//! 行情合约
const TAPIContractTypeType		TAPI_CONTRACT_TYPE_QUOTE			='2';
/** @}*/

//=============================================================================
/**
 *	\addtogroup G_DATATYPE_T_TAPITACTICSTYPETYPE	策略单类型
 *	@{
 */
//=============================================================================
//! 策略单类型
typedef TAPICHAR					TAPITacticsTypeType;
//! 无
const TAPITacticsTypeType			TAPI_TACTICS_TYPE_NONE				= 'N';
//! 预备单(埋单)
const TAPITacticsTypeType			TAPI_TACTICS_TYPE_READY				= 'M';
//! 自动单
const TAPITacticsTypeType			TAPI_TACTICS_TYPE_ATUO				= 'A';
//! 条件单
const TAPITacticsTypeType			TAPI_TACTICS_TYPE_CONDITION			= 'C';
/** @}*/

//=============================================================================
/**
 *	\addtogroup G_DATATYPE_T_TAPIORDERACT	订单操作类型
 *	@{
 */
//=============================================================================
//! 订单操作类型
typedef TAPICHAR		TAPIORDERACT;
//! 报单
const TAPIORDERACT APIORDER_INSERT			= '1';
//! 改单
const TAPIORDERACT APIORDER_MODIFY			= '2';
//! 撤单
const TAPIORDERACT APIORDER_DELETE			= '3';
//! 挂起
const TAPIORDERACT APIORDER_SUSPEND			= '4';
//! 激活
const TAPIORDERACT APIORDER_ACTIVATE		= '5';
//! 删除
const TAPIORDERACT APIORDER_SYSTEM_DELETE	= '6';
/** @}*/

//=============================================================================
/**
 *	\addtogroup G_DATATYPE_T_TAPITRIGGERCONDITIONTYPE	触发条件类型
 *	@{
 */
//=============================================================================
//! 触发条件类型
typedef TAPICHAR				TAPITriggerConditionType;
//! 无
const TAPITriggerConditionType	TAPI_TRIGGER_CONDITION_NONE			= 'N';
//! 大于等于
const TAPITriggerConditionType	TAPI_TRIGGER_CONDITION_GREAT		= 'G';
//! 小于等于
const TAPITriggerConditionType	TAPI_TRIGGER_CONDITION_LITTLE		= 'L';
/** @}*/

//=============================================================================
/**
 *	\addtogroup G_DATATYPE_T_TAPITRIGGERPRICETYPETYPE	触发价格类型
 *	@{
 */
//=============================================================================
//! 触发价格类型
typedef TAPICHAR				TAPITriggerPriceTypeType;
//! 无
const TAPITriggerPriceTypeType	TAPI_TRIGGER_PRICE_NONE				= 'N';
//! 买价
const TAPITriggerPriceTypeType	TAPI_TRIGGER_PRICE_BUY				= 'B';
//! 卖价
const TAPITriggerPriceTypeType	TAPI_TRIGGER_PRICE_SELL				= 'S';
//! 最新价
const TAPITriggerPriceTypeType	TAPI_TRIGGER_PRICE_LAST				= 'L';
/** @}*/

//=============================================================================
/**
 *	\addtogroup G_DATATYPE_T_TAPIMARKETLEVELTYPE	市价撮合深度
 *	@{
 */
//=============================================================================
//! 市价撮合深度
typedef TAPIUINT8				TAPIMarketLevelType;
//! 任意价
const TAPIMarketLevelType	TAPI_MARKET_LEVEL_0						= 0;
//! 1档最优价
const TAPIMarketLevelType	TAPI_MARKET_LEVEL_1						= 1;
//! 5档
const TAPIMarketLevelType	TAPI_MARKET_LEVEL_5						= 5;
//! 10档
const TAPIMarketLevelType	TAPI_MARKET_LEVEL_10					= 10;
/** @}*/


//=============================================================================
/**
 *	\addtogroup G_DATATYPE_T_TAPITRADINGSTATETYPE	交易状态
 *	@{
 */
//=============================================================================
//! 交易状态
typedef TAPICHAR               TAPITradingStateType;
//! 集合竞价
const TAPITradingStateType      TAPI_TRADE_STATE_BID                = '1';
//! 集合竞价撮合
const TAPITradingStateType      TAPI_TRADE_STATE_MATCH              = '2';
//! 连续交易
const TAPITradingStateType      TAPI_TRADE_STATE_CONTINUOUS         = '3';
//! 交易暂停
const TAPITradingStateType      TAPI_TRADE_STATE_PAUSED             = '4';
//! 闭市
const TAPITradingStateType      TAPI_TRADE_STATE_CLOSE              = '5';
//! 闭市处理时间
const TAPITradingStateType      TAPI_TRADE_STATE_DEALLAST           = '6';
//! 网关未连
const TAPITradingStateType		TAPI_TRADE_STATE_GWDISCONNECT		= '0';
//! 未知状态
const TAPITradingStateType		TAPI_TRADE_STATE_UNKNOWN			= 'N';
//! 正初始化
const TAPITradingStateType		TAPI_TRADE_STATE_INITIALIZE			= 'I';
//! 准备就绪
const TAPITradingStateType		TAPI_TRADE_STATE_READY				= 'R';
/** @}*/



//=============================================================================
/**
 *	\addtogroup G_DATATYPE_T_TAPINOTICEIGNOREFLAGTYPE	忽略后台推送通知标记
 *	@{
 */
//=============================================================================
//! 忽略后台推送通知标记
typedef TAPIUINT32              TAPINoticeIgnoreFlagType;
//! 推送所有信息
const TAPINoticeIgnoreFlagType TAPI_NOTICE_IGNORE_NONE				= 0x00000000;
//! 忽略所有推送
const TAPINoticeIgnoreFlagType TAPI_NOTICE_IGNORE_ALL				= 0xFFFFFFFF;
//! 忽略资金推送:OnRtnFund
const TAPINoticeIgnoreFlagType TAPI_NOTICE_IGNORE_FUND				= 0x00000001;
//! 忽略委托推送:OnRtnOrder
const TAPINoticeIgnoreFlagType TAPI_NOTICE_IGNORE_ORDER				= 0x00000002;
//! 忽略成交推送:OnRtnFill
const TAPINoticeIgnoreFlagType TAPI_NOTICE_IGNORE_FILL				= 0x00000004;
//! 忽略持仓推送:OnRtnPosition
const TAPINoticeIgnoreFlagType TAPI_NOTICE_IGNORE_POSITION			= 0x00000008;
//! 忽略平仓推送:OnRtnClose
const TAPINoticeIgnoreFlagType TAPI_NOTICE_IGNORE_CLOSE				= 0x00000010;
//! 忽略持仓盈亏推送:OnRtnPositionProfit
const TAPINoticeIgnoreFlagType TAPI_NOTICE_IGNORE_POSITIONPROFIT	= 0x00000020;
/** @}*/


//=============================================================================
/**
 *	\addtogroup G_DATATYPE_T_TAPIORDERQRYTYPETYPE	委托查询类型
 *	@{
 */
//=============================================================================
//! 委托查询类型
typedef TAPICHAR              TAPIOrderQryTypeType;
//! 返回所有委托
const TAPIOrderQryTypeType TAPI_ORDER_QRY_TYPE_ALL				= 'A';
//! 只返回未结束的委托
const TAPIOrderQryTypeType TAPI_ORDER_QRY_TYPE_UNENDED			= 'U';
/** @}*/

//=============================================================================
/**
 *	\addtogroup G_DATATYPE_T_TAPIBILLTYPETYPE	账单类型
 *	@{
 */
//=============================================================================
//! 账单类型
typedef TAPICHAR						TAPIBillTypeType;
//! 日账单
const TAPIBillTypeType					TAPI_BILL_DATE			= 'D';
//! 月账单
const TAPIBillTypeType					TAPI_BILL_MONTH			= 'M';
/** @}*/

//=============================================================================
/**
 *	\addtogroup G_DATATYPE_T_TAPIBILLFILETYPETYPE	帐单文件类型
 *	@{
 */
//=============================================================================
//! 帐单文件类型
typedef TAPICHAR						TAPIBillFileTypeType;
//! txt格式文件
const TAPIBillFileTypeType				TAPI_BILL_FILE_TXT		= 'T';
//! pdf格式文件
const TAPIBillFileTypeType				TAPI_BILL_FILE_PDF		= 'F';
/** @}*/



//! ------------------------------------------------------------------------------------------

//! 登录认证信息
struct TapAPITradeLoginAuth
{
	TAPISTR_20					UserNo;					///< 用户名
	TAPISTR_50					AuthCode;				///< 授权码
	TAPISTR_30					AppID;					///< 程序版本号
	TAPIYNFLAG					ISModifyPassword;		///< 是否修改密码	
	TAPISTR_20					Password;				///< 密码
	TAPISTR_20					NewPassword;			///< 新密码
	TAPIYNFLAG					ISDDA;					///< 是否需要动态认证
	TAPISTR_30					DDASerialNo;			///< 动态认证码
	TAPINoticeIgnoreFlagType	NoticeIgnoreFlag;		///< 忽略推送通知标记
};

//! 登录反馈信息
struct TapAPITradeLoginRspInfo
{
	TAPISTR_20					UserNo;							///< 用户编号
	TAPIUserTypeType			UserType;						///< 用户类型
	TAPISTR_20					UserName;						///< 用户名
	TAPISTR_20					QuoteTempPassword;				///< 行情临时密码
	TAPISTR_50					ReservedInfo;					///< 预留信息
	TAPISTR_40					LastLoginIP;					///< 上次登录IP
	TAPIUINT32					LastLoginPort;					///< 上次登录端口
	TAPISTR_500                 LastLoginInfo;                  ///< 上次登录信息
	TAPIDATETIME				LastLoginTime;					///< 上次登录时间
	TAPIDATETIME				LastLogoutTime;					///< 上次退出时间
	TAPIDATE					TradeDate;						///< 当前交易日期
	TAPIDATETIME				LastSettleTime;					///< 上次结算时间
	TAPIDATETIME				StartTime;						///< 系统启动时间
	TAPIDATETIME				InitTime;						///< 系统初始化时间
	TAPIAuthTypeType			AuthType;						///< 用户授权类型
	TAPIDATETIME				AuthDate;						///< 用户授权到期日
	TAPIUINT64					UdpCertCode;					///< UDP报单认证码
};

//! 登录采集信息
struct TapAPISubmitUserLoginInfo
{
	TAPISTR_20					UserNo;								///< 登录用户名
	TAPISTR_500					GatherInfo;							///< 用户终端信息
	TAPISTR_40					ClientLoginIP;						///< 用户公网IP
	TAPIUINT32					ClientLoginPort;					///< 用户公网Port
	TAPIDATETIME				ClientLoginDateTime;				///< 用户登录时间
	TAPISTR_30					ClientAppID;						///< 用户AppID
	TAPIUINT32					AuthKeyVersion;						///< 用户终端信息加密密钥版本号
};

//! 登录采集信息应答
struct TapAPISubmitUserLoginRspInfo
{
	TAPISTR_20					UserNo;								///< 登录用户名
	TAPIUINT32					ErrorCode;				    		///< 错误码
	TAPISTR_50                  ErrorText;                          ///< 错误信息
};

//! 账号相关信息查询请求
struct TapAPIAccQryReq
{
	TAPISTR_20					AccountNo;						///< 资金账号				
};

//! 资金账号信息
struct TapAPIAccountInfo
{
	TAPISTR_20              AccountNo;                              ///< 资金账号
	TAPIAccountType			AccountType;                            ///< 账号类型
	TAPIAccountState		AccountState;                           ///< 账号状态
	TAPISTR_20				AccountShortName;                       ///< 账号简称
	TAPIYNFLAG				AccountIsDocHolder;                     ///< 是否持证者
	TAPIYNFLAG				IsMarketMaker;							///< 是否是做市商
	TAPIAccountFamilyType	AccountFamilyType;						///< 父子账号类型
};

//! 客户下单请求结构
struct TapAPINewOrder
{
	TAPISTR_20					AccountNo;						///< 客户资金帐号
	TAPISTR_10					ExchangeNo;						///< 交易所编号
	TAPICommodityType			CommodityType;					///< 品种类型
	TAPISTR_10					CommodityNo;					///< 品种编码类型
	TAPISTR_10					ContractNo;						///< 合约1
	TAPISTR_10					StrikePrice;					///< 执行价格1
	TAPICallOrPutFlagType		CallOrPutFlag;					///< 看张看跌1
	TAPISTR_10					ContractNo2;					///< 合约2
	TAPISTR_10					StrikePrice2;					///< 执行价格2
	TAPICallOrPutFlagType		CallOrPutFlag2;					///< 看张看跌2
	TAPIOrderTypeType			OrderType;						///< 委托类型
	TAPIOrderSourceType			OrderSource;					///< 委托来源
	TAPITimeInForceType			TimeInForce;					///< 委托有效类型
	TAPIDATETIME				ExpireTime;						///< 有效日期(GTD情况下使用)
	TAPIYNFLAG					IsRiskOrder;					///< 是否风险报单
	TAPISideType				OrderSide;						///< 买入卖出
	TAPIPositionEffectType		PositionEffect;					///< 开平标志1
	TAPIPositionEffectType		PositionEffect2;				///< 开平标志2
	TAPISTR_50					InquiryNo;						///< 询价号
	TAPIHedgeFlagType			HedgeFlag;						///< 投机保值
	TAPIREAL64					OrderPrice;						///< 委托价格1
	TAPIREAL64					OrderPrice2;					///< 委托价格2，做市商应价使用
	TAPIREAL64					StopPrice;						///< 触发价格
	TAPIUINT32					OrderQty;						///< 委托数量
	TAPIUINT32					OrderMinQty;					///< 最小成交量
	TAPIUINT32					MinClipSize;					///< 冰山单最小随机量
	TAPIUINT32					MaxClipSize;					///< 冰山单最大随机量
	TAPIINT32					RefInt;							///< 整型参考值
	TAPISTR_50					RefString;						///< 字符串参考值
	TAPITacticsTypeType			TacticsType;					///< 策略单类型
	TAPITriggerConditionType	TriggerCondition;				///< 触发条件
	TAPITriggerPriceTypeType	TriggerPriceType;				///< 触发价格类型	
	TAPIYNFLAG					AddOneIsValid;					///< 是否T+1有效
	TAPIUINT32					OrderQty2;						///< 委托数量2
	TAPIHedgeFlagType			HedgeFlag2;						///< 投机保值2
	TAPIMarketLevelType			MarketLevel;					///< 市价撮合深度
	TAPIYNFLAG					FutureAutoCloseFlag;		    ///< 行权后期货是否自对冲
	TAPISTR_10					UpperChannelNo;					///< 上手通道号
};

//! 委托类型查询应答
struct TapAPICommodityOrderTypeQryRsp
{
	TapAPICommodity			Commodity;							///< 品种信息
	TAPIINT32				Count;								///< 委托类型个数
	TAPIOrderTypeType*		OrderTypes;							///< 委托类型数组首地址
};

//! 委托有效类型查询应答
struct TapAPICommodityOrderTimeInForceQryRsp
{
	TapAPICommodity			Commodity;							///< 品种信息
	TAPIINT32				Count;								///< 委托有效类型个数
	TAPITimeInForceType*	OrderTimeInForces;					///< 委托有效类型数组首地址
};


//! 委托完整信息
struct TapAPIOrderInfo
{
	TAPISTR_20					AccountNo;						///< 客户资金帐号
	TAPISTR_10					ExchangeNo;						///< 交易所编号
	TAPICommodityType			CommodityType;					///< 品种类型
	TAPISTR_10					CommodityNo;					///< 品种编码类型
	TAPISTR_10					ContractNo;						///< 合约1
	TAPISTR_10					StrikePrice;					///< 执行价格1
	TAPICallOrPutFlagType		CallOrPutFlag;					///< 看张看跌1
	TAPISTR_10					ContractNo2;					///< 合约2
	TAPISTR_10					StrikePrice2;					///< 执行价格2
	TAPICallOrPutFlagType		CallOrPutFlag2;					///< 看张看跌2

	TAPIOrderTypeType			OrderType;						///< 委托类型
	TAPIOrderSourceType			OrderSource;					///< 委托来源
	TAPITimeInForceType			TimeInForce;					///< 委托有效类型
	TAPIDATETIME				ExpireTime;						///< 有效日期(GTD情况下使用)

	TAPIYNFLAG					IsRiskOrder;					///< 是否风险报单
	TAPISideType				OrderSide;						///< 买入卖出
	TAPIPositionEffectType		PositionEffect;					///< 开平标志1
	TAPIPositionEffectType		PositionEffect2;				///< 开平标志2
	TAPISTR_50					InquiryNo;						///< 询价号
	TAPIHedgeFlagType			HedgeFlag;						///< 投机保值
	TAPIREAL64					OrderPrice;						///< 委托价格1
	TAPIREAL64					OrderPrice2;					///< 委托价格2，做市商应价使用
	TAPIREAL64					StopPrice;						///< 触发价格
	TAPIUINT32					OrderQty;						///< 委托数量
	TAPIUINT32					OrderMinQty;					///< 最小成交量
	TAPIUINT32					OrderCanceledQty;				///< 撤单数量

	TAPIUINT32					MinClipSize;					///< 冰山单最小随机量
	TAPIUINT32					MaxClipSize;					///< 冰山单最大随机量
	TAPISTR_50					LicenseNo;						///< 软件授权号

	TAPIINT32					RefInt;							///< 整型参考值
	TAPISTR_50					RefString;						///< 字符串参考值
	TAPISTR_20					ParentAccountNo;				///< 上级资金账号

	TAPICHAR					ServerFlag;						///< 服务器标识
	TAPISTR_20					OrderNo;						///< 委托编码
	TAPISTR_50                  ClientOrderNo;					///< 客户端本地委托编号
	TAPISTR_20					OrderLocalNo;					///< 本地号
	TAPISTR_50					OrderSystemNo;					///< 系统号
	TAPISTR_50					OrderExchangeSystemNo;			///< 交易所系统号 
    TAPISTR_20					OrderParentNo;					///< 父单号
	TAPISTR_50					OrderParentSystemNo;			///< 父单系统号
	TAPISTR_10					TradeNo;						///< 交易编码

	TAPISTR_10					UpperNo;						///< 上手号
	TAPISTR_10					UpperChannelNo;					///< 上手通道号
	TAPISTR_20					UpperSettleNo;					///< 会员号和清算号
	TAPISTR_20					UpperUserNo;					///< 上手登录号
	TAPISTR_20					OrderInsertUserNo;				///< 下单人
	TAPIDATETIME				OrderInsertTime;				///< 下单时间
	TAPISTR_20					OrderCommandUserNo;				///< 录单操作人
	TAPISTR_20					OrderUpdateUserNo;				///< 委托更新人
	TAPIDATETIME				OrderUpdateTime;				///< 委托更新时间
	TAPIOrderStateType			OrderState;						///< 委托状态
	TAPIREAL64					OrderMatchPrice;				///< 成交价1
	TAPIREAL64					OrderMatchPrice2;				///< 成交价2
	TAPIUINT32					OrderMatchQty;					///< 成交量1
	TAPIUINT32					OrderMatchQty2;					///< 成交量2

	TAPIUINT32					ErrorCode;						///< 最后一次操作错误信息码
	TAPISTR_50					ErrorText;						///< 错误信息

	TAPIYNFLAG					IsBackInput;					///< 是否为录入委托单
	TAPIYNFLAG					IsDeleted;						///< 委托成交删除标
	TAPIYNFLAG					IsAddOne;						///< 是否为T+1单

	TAPIUINT32					OrderStreamID;					///< 委托流水号
	TAPIUINT32					UpperStreamID;					///< 上手流号

	TAPIREAL64					ContractSize;					///< 每手乘数，计算参数
	TAPIREAL64					ContractSize2;					///< 每手乘数，计算参数
	TAPISTR_10					CommodityCurrencyGroup;			///< 品种币种组
	TAPISTR_10					CommodityCurrency;				///< 品种币种
	TAPICalculateModeType		FeeMode;						///< 手续费计算方式
	TAPIREAL64					FeeParam;						///< 手续费参数值 冻结手续费均按照开仓手续费计算
	TAPISTR_10					FeeCurrencyGroup;				///< 客户手续费币种组
	TAPISTR_10					FeeCurrency;					///< 客户手续费币种
	TAPICalculateModeType		FeeMode2;						///< 手续费计算方式
	TAPIREAL64					FeeParam2;						///< 手续费参数值 冻结手续费均按照开仓手续费计算
	TAPISTR_10					FeeCurrencyGroup2;				///< 客户手续费币种组
	TAPISTR_10					FeeCurrency2;					///< 客户手续费币种
	TAPICalculateModeType		MarginMode;						///< 保证金计算方式
	TAPIREAL64					MarginParam;					///< 保证金参数值
	TAPICalculateModeType		MarginMode2;					///< 保证金计算方式
	TAPIREAL64					MarginParam2;					///< 保证金参数值
	TAPIREAL64					PreSettlePrice;					///< 昨结算价  比例方式的市价单和组合订单使用
	TAPIREAL64					PreSettlePrice2;				///< 昨结算价  比例方式的市价单和组合订单使用
	TAPIUINT32					OpenVol;						///< 预开仓数量 委托数量中的开仓部分
	TAPIUINT32					CoverVol;						///< 预平仓数量 委托数量中的平仓部分
	TAPIUINT32					OpenVol2;						///< 预开仓数量 委托数量中的开仓部分
	TAPIUINT32					CoverVol2;						///< 预平仓数量 委托数量中的平仓部分
	TAPIREAL64					FeeValue;						///< 冻结手续费
	TAPIREAL64					MarginValue;					///< 冻结保证金 合并计算的此项为0
	TAPITacticsTypeType			TacticsType;					///< 策略单类型
	TAPITriggerConditionType	TriggerCondition;				///< 触发条件
	TAPITriggerPriceTypeType	TriggerPriceType;				///< 触发价格类型
	TAPIYNFLAG					AddOneIsValid;					///< 是否T+1有效
	TAPIUINT32					OrderQty2;						///< 委托数量2
	TAPIHedgeFlagType			HedgeFlag2;						///< 投机保值2
	TAPIMarketLevelType			MarketLevel;					///< 市价撮合深度
	TAPIYNFLAG					OrderDeleteByDisConnFlag;		///< 心跳检测失败时，服务器自动撤单标识
};

//! 报单通知结构
struct TapAPIOrderInfoNotice
{
	TAPIUINT32					SessionID;						///< 会话ID
	TAPIUINT32					ErrorCode; 						///< 错误码
	TapAPIOrderInfo*			OrderInfo;						///< 委托完整信息
};

//! 报单操作应答结构
struct TapAPIOrderActionRsp
{
	TAPIORDERACT				ActionType;						///< 操作类型
	TapAPIOrderInfo*			OrderInfo;						///< 委托信息
};


//! 客户改单请求
struct TapAPIAmendOrder
{
    TapAPINewOrder              ReqData;                        ///< 报单请求数据
    TAPICHAR					ServerFlag;						///< 服务器标识
    TAPISTR_20                  OrderNo;                        ///< 委托编号
};

//! 客户撤单请求结构
struct TapAPIOrderCancelReq
{
	TAPIINT32					RefInt;							///< 整型参考值
	TAPISTR_50					RefString;						///< 字符串参考值
	TAPICHAR					ServerFlag;						///< 服务器标识
	TAPISTR_20					OrderNo;						///< 委托编码
};

//! 挂起委托请求结构
typedef TapAPIOrderCancelReq TapAPIOrderDeactivateReq;

//! 激活委托请求结构
typedef TapAPIOrderCancelReq TapAPIOrderActivateReq;

//! 删除委托请求结构
typedef TapAPIOrderCancelReq TapAPIOrderDeleteReq;

//! 委托查询请求结构
struct TapAPIOrderQryReq
{
	TAPIOrderQryTypeType	OrderQryType;	///< 委托查询类型
};

//! 委托流程查询
struct TapAPIOrderProcessQryReq
{
	TAPICHAR					ServerFlag;						///< 服务器标识
	TAPISTR_20					OrderNo;						///< 委托编码
};

//! 成交查询请求结构
struct TapAPIFillQryReq
{
	TAPIUINT32					StreamID;				    	///< 流水号
};

//! 成交信息
struct TapAPIFillInfo
{
	TAPISTR_20					AccountNo;						///< 客户资金帐号
	TAPISTR_20					ParentAccountNo;				///< 上级资金账号
	TAPISTR_10					ExchangeNo;						///< 交易所编号
	TAPICommodityType			CommodityType;					///< 品种类型
	TAPISTR_10					CommodityNo;					///< 品种编码类型
	TAPISTR_10					ContractNo;						///< 合约1
	TAPISTR_10					StrikePrice;					///< 执行价格
	TAPICallOrPutFlagType		CallOrPutFlag;					///< 看张看跌
	TAPISTR_10					ExchangeNoRef;					///< 交易所编号
	TAPICommodityType			CommodityTypeRef;				///< 品种类型
	TAPISTR_10					CommodityNoRef;					///< 品种编码类型
	TAPISTR_10					ContractNoRef;					///< 合约
	TAPISTR_10					StrikePriceRef;					///< 执行价格
	TAPICallOrPutFlagType		CallOrPutFlagRef;				///< 看张看跌
	TAPISTR_10					OrderExchangeNo;				///< 交易所编号
	TAPICommodityType			OrderCommodityType;				///< 品种类型
	TAPISTR_10					OrderCommodityNo;				///< 品种编码类型
	TAPIOrderTypeType			OrderType;						///< 委托类型
	TAPIMatchSourceType			MatchSource;					///< 委托来源
	TAPITimeInForceType			TimeInForce;					///< 委托有效类型
	TAPIDATETIME				ExpireTime;						///< 有效日期(GTD情况下使用)
	TAPIYNFLAG					IsRiskOrder;					///< 是否风险报单
	TAPISideType				MatchSide;						///< 买入卖出
	TAPIPositionEffectType		PositionEffect;					///< 开平标志1
	TAPIPositionEffectType		PositionEffectRef;				///< 开平标志2
	TAPIHedgeFlagType			HedgeFlag;						///< 投机保值
	TAPICHAR					ServerFlag;						///< 服务器标识
	TAPISTR_20					OrderNo;						///< 委托编码
	TAPISTR_20					OrderLocalNo;					///< 委托本地号
	TAPISTR_20					MatchNo;						///< 本地成交号
	TAPISTR_70					ExchangeMatchNo;				///< 交易所成交号
	TAPIDATETIME				MatchDateTime;					///< 成交时间
	TAPIDATETIME				UpperMatchDateTime;				///< 上手成交时间
	TAPISTR_10					UpperNo;						///< 上手号
	TAPISTR_10					UpperChannelNo;					///< 上手通道号
	TAPISTR_20					UpperSettleNo;					///< 会员号和清算代码
	TAPISTR_20					UpperUserNo;					///< 上手登录号
	TAPISTR_10					TradeNo;						///< 交易编码
	TAPIREAL64					MatchPrice;						///< 成交价
	TAPIUINT32					MatchQty;						///< 成交量
	TAPIYNFLAG					IsBackInput;					///< 是否为录入委托单
	TAPIYNFLAG					IsDeleted;						///< 委托成交删除标
	TAPIYNFLAG					IsAddOne;						///< 是否为T+1单
	TAPIUINT32					MatchStreamID;					///< 委托流水号
	TAPIUINT32					UpperStreamID;					///< 上手流号
	TAPIOpenCloseModeType		OpenCloseMode;                  ///< 开平方式
	TAPIREAL64					ContractSize;					///< 每手乘数，计算参数
	TAPISTR_10					CommodityCurrencyGroup;			///< 品种币种组
	TAPISTR_10					CommodityCurrency;				///< 品种币种
	TAPICalculateModeType		FeeMode;						///< 手续费计算方式
	TAPIREAL64					FeeParam;						///< 手续费参数值 冻结手续费均按照开仓手续费计算
	TAPISTR_10					FeeCurrencyGroup;				///< 客户手续费币种组
	TAPISTR_10					FeeCurrency;					///< 客户手续费币种
	TAPIREAL64					PreSettlePrice;					///< 昨结算价
	TAPIREAL64					FeeValue;						///< 手续费
	TAPIYNFLAG					IsManualFee;					///< 人工客户手续费标记
	TAPIREAL64					Turnover;						///< 成交金额
	TAPIREAL64					PremiumIncome;					///< 权利金收取
	TAPIREAL64					PremiumPay;						///< 权利金支付
	TAPISTR_20					OppoMatchNo;					///< 对手本地成交号（开仓和平仓对应编号）
	TAPIREAL64					CloseProfit;					///< 平仓盈亏
	TAPIREAL64					UnExpProfit;					///< 未到期平盈
	TAPIREAL64					UpperMatchPrice;				///< 上手成交价
	TAPIREAL64					QuotePrice;						///< 当前行情价
	TAPIREAL64					ClosePL;                        ///< 逐笔平盈
};

//! 平仓查询请求结构
struct TapAPICloseQryReq
{
};

//! 持仓查询请求结构
struct TapAPIPositionQryReq
{
};

//! 持仓信息
struct TapAPIPositionInfo
{
	TAPISTR_20					AccountNo;						///< 客户资金帐号
	TAPISTR_20					ParentAccountNo;				///< 上级资金账号
	TAPISTR_10					ExchangeNo;						///< 交易所编号
	TAPICommodityType			CommodityType;					///< 品种类型
	TAPISTR_10					CommodityNo;					///< 品种编码类型
	TAPISTR_10					ContractNo;						///< 合约1
	TAPISTR_10					StrikePrice;					///< 执行价格
	TAPICallOrPutFlagType		CallOrPutFlag;					///< 看张看跌
	TAPISTR_10					ExchangeNoRef;					///< 交易所编号
	TAPICommodityType			CommodityTypeRef;				///< 品种类型
	TAPISTR_10					CommodityNoRef;					///< 品种编码类型
	TAPISTR_10					ContractNoRef;					///< 合约
	TAPISTR_10					StrikePriceRef;					///< 执行价格
	TAPICallOrPutFlagType		CallOrPutFlagRef;				///< 看张看跌
	TAPISTR_10					OrderExchangeNo;				///< 交易所编号
	TAPICommodityType			OrderCommodityType;				///< 品种类型
	TAPISTR_10					OrderCommodityNo;				///< 品种编码类型
	TAPIOrderTypeType			OrderType;						///< 委托类型
	TAPIMatchSourceType			MatchSource;					///< 委托来源
	TAPITimeInForceType			TimeInForce;					///< 委托有效类型
	TAPIDATETIME				ExpireTime;						///< 有效日期(GTD情况下使用)
	TAPISideType				MatchSide;						///< 买入卖出
	TAPIHedgeFlagType			HedgeFlag;						///< 投机保值
	TAPISTR_70					PositionNo;						///< 本地持仓号，服务器编写
	TAPICHAR					ServerFlag;						///< 服务器标识
	TAPISTR_20					OrderNo;						///< 委托编码
	TAPISTR_20					MatchNo;						///< 本地成交号
	TAPISTR_70					ExchangeMatchNo;				///< 交易所成交号
	TAPIDATE					MatchDate;						///< 成交日期
	TAPIDATETIME				MatchTime;						///< 成交时间
	TAPIDATETIME				UpperMatchTime;					///< 上手成交时间
	TAPISTR_10					UpperNo;						///< 上手号
	TAPISTR_20					UpperSettleNo;					///< 会员号和清算代码
	TAPISTR_20					UpperUserNo;					///< 上手登录号
	TAPISTR_10					TradeNo;						///< 交易编码
	TAPIREAL64					PositionPrice;					///< 持仓价
	TAPIUINT32					PositionQty;					///< 持仓量
	TAPIYNFLAG					IsBackInput;					///< 是否为录入委托单
	TAPIYNFLAG					IsAddOne;						///< 是否为T+1单
	TAPIUINT32					MatchStreamID;					///< 成交流水号
    TAPIUINT32                  PositionStreamId;				///< 持仓流号
    TAPIOpenCloseModeType       OpenCloseMode;                  ///< 开平方式
	TAPIREAL64					ContractSize;					///< 每手乘数，计算参数
	TAPISTR_10					CommodityCurrencyGroup;			///< 品种币种组
	TAPISTR_10					CommodityCurrency;				///< 品种币种
	TAPIREAL64					PreSettlePrice;					///< 昨结算价
	TAPIREAL64					SettlePrice;					///< 当前计算价格
	TAPIREAL64					Turnover;						///< 持仓金额
	TAPICalculateModeType		AccountMarginMode;				///< 保证金计算方式
	TAPIREAL64					AccountMarginParam;				///< 保证金参数值
	TAPICalculateModeType		UpperMarginMode;				///< 保证金计算方式
	TAPIREAL64					UpperMarginParam;				///< 保证金参数值
	TAPIREAL64					AccountInitialMargin;			///< 客户初始保证金
	TAPIREAL64					AccountMaintenanceMargin;		///< 客户维持保证金
	TAPIREAL64					UpperInitialMargin;				///< 上手初始保证金
	TAPIREAL64					UpperMaintenanceMargin;			///< 上手维持保证金
	TAPIREAL64					PositionProfit;					///< 持仓盈亏
	TAPIREAL64					LMEPositionProfit;				///< LME持仓盈亏
	TAPIREAL64					OptionMarketValue;				///< 期权市值
	TAPISTR_20					MatchCmbNo;						///< 组合持仓号
	TAPIYNFLAG					IsHistory;						///< 是否历史持仓
	TAPIREAL64					FloatingPL;						///< 逐笔浮盈
};

//! 客户持仓盈亏
struct TapAPIPositionProfit
{
	TAPISTR_70					PositionNo;						///< 本地持仓号，服务器编写
	TAPIUINT32					PositionStreamId;				///< 持仓流号
	TAPIREAL64					PositionProfit;					///< 持仓盈亏
	TAPIREAL64					LMEPositionProfit;				///< LME持仓盈亏
	TAPIREAL64					OptionMarketValue;				///< 期权市值
	TAPIREAL64					CalculatePrice;					///< 计算价格
	TAPIREAL64					FloatingPL;						///< 逐笔浮盈
};

//! 客户持仓盈亏通知
struct TapAPIPositionProfitNotice
{
	TAPIYNFLAG					IsLast;							///< 是否最后一包
	TapAPIPositionProfit*		Data;							///< 客户持仓盈亏信息
};

//! 平仓信息
struct TapAPICloseInfo
{
	TAPISTR_20					AccountNo;						///< 客户资金帐号
	TAPISTR_20					ParentAccountNo;				///< 上级资金账号
	TAPISTR_10					ExchangeNo;						///< 交易所编号
	TAPICommodityType			CommodityType;					///< 品种类型
	TAPISTR_10					CommodityNo;					///< 品种编码类型
	TAPISTR_10					ContractNo;						///< 合约
	TAPISTR_10					StrikePrice;					///< 执行价格
	TAPICallOrPutFlagType		CallOrPutFlag;					///< 看张看跌
	TAPISTR_10					OpenOrderExchangeNo;			///< 交易所编号
	TAPICommodityType			OpenOrderCommodityType;			///< 品种类型
	TAPISTR_10					OpenOrderCommodityNo;			///< 品种编码类型
	TAPISTR_10					CloseOrderExchangeNo;			///< 交易所编号
	TAPICommodityType			CloseOrderCommodityType;		///< 品种类型
	TAPISTR_10					CloseOrderCommodityNo;			///< 品种编码类型
	TAPIMatchSourceType			OpenMatchSource;
	TAPIMatchSourceType			CloseMatchSource;
	TAPISideType				CloseSide;						///< 平仓一边的买入卖出
	TAPIUINT32					CloseQty;						///< 平仓成交量
	TAPIREAL64					OpenPrice;						///< 开仓成交价
	TAPIREAL64					ClosePrice;						///< 平仓成交价
	TAPICHAR					OpenServerFlag;					///< 服务器标识
	TAPISTR_20					OpenOrderNo;					///< 委托编码
	TAPISTR_20					OpenMatchNo;					///< 本地成交号
	TAPISTR_70					OpenExchangeMatchNo;			///< 交易所成交号
	TAPIDATETIME				OpenMatchDateTime;				///< 成交时间
	TAPICHAR					CloseServerFlag;				///< 服务器标识
	TAPISTR_20					CloseOrderNo;					///< 委托编码
	TAPISTR_20					CloseMatchNo;					///< 本地成交号
	TAPISTR_70					CloseExchangeMatchNo;			///< 交易所成交号
	TAPIDATETIME				CloseMatchDateTime;				///< 成交时间
    TAPIUINT32                  CloseStreamId;					///< 平仓流号
    TAPIOpenCloseModeType		OpenCloseMode;                  ///< 开平方式
	TAPIREAL64					ContractSize;					///< 每手乘数，计算参数
	TAPISTR_10					CommodityCurrencyGroup;			///< 品种币种组
	TAPISTR_10					CommodityCurrency;				///< 品种币种
	TAPIREAL64					PreSettlePrice;					///< 昨结算价
	TAPIREAL64					PremiumIncome;					///< 权利金收取
	TAPIREAL64					PremiumPay;						///< 权利金支付
	TAPIREAL64					CloseProfit;					///< 平仓盈亏
	TAPIREAL64					UnExpProfit;					///< 未到期平盈
	TAPIREAL64					ClosePL;                        ///< 逐笔平盈
};
//! 资金查询请求
struct TapAPIFundReq
{
	TAPISTR_20					AccountNo;						///< 客户资金帐号
};
//! 资金账号资金信息
struct TapAPIFundData
{
	TAPISTR_20					AccountNo;						///< 客户资金账号
	TAPISTR_20					ParentAccountNo;				///< 上级资金账号
	TAPISTR_10					CurrencyGroupNo;				///< 币种组号
	TAPISTR_10					CurrencyNo;						///< 币种号(为空表示币种组基币资金)
	TAPIREAL64					TradeRate;						///< 交易汇率
	TAPIFutureAlgType			FutureAlg;                      ///< 期货算法
	TAPIOptionAlgType			OptionAlg;                      ///< 期权算法
	TAPIREAL64					PreBalance;						///< 上日结存
	TAPIREAL64					PreUnExpProfit;					///< 上日未到期平盈
	TAPIREAL64					PreLMEPositionProfit;			///< 上日LME持仓平盈
	TAPIREAL64					PreEquity;						///< 上日权益
	TAPIREAL64					PreAvailable1;					///< 上日可用
	TAPIREAL64					PreMarketEquity;				///< 上日市值权益
	TAPIREAL64					CashInValue;					///< 入金
	TAPIREAL64					CashOutValue;					///< 出金
	TAPIREAL64					CashAdjustValue;				///< 资金调整
	TAPIREAL64					CashPledged;					///< 质押资金
	TAPIREAL64					FrozenFee;						///< 冻结手续费
	TAPIREAL64					FrozenDeposit;					///< 冻结保证金
	TAPIREAL64					AccountFee;						///< 客户手续费包含交割手续费
	TAPIREAL64					ExchangeFee;					///< 汇兑手续费
	TAPIREAL64					AccountDeliveryFee;				///< 客户交割手续费
	TAPIREAL64					PremiumIncome;					///< 权利金收取
	TAPIREAL64					PremiumPay;						///< 权利金支付
	TAPIREAL64					CloseProfit;					///< 平仓盈亏
	TAPIREAL64					DeliveryProfit;					///< 交割盈亏
	TAPIREAL64					UnExpProfit;					///< 未到期平盈
	TAPIREAL64					ExpProfit;						///< 到期平仓盈亏
	TAPIREAL64					PositionProfit;					///< 不含LME持仓盈亏 
	TAPIREAL64					LmePositionProfit;				///< LME持仓盈亏
	TAPIREAL64					OptionMarketValue;				///< 期权市值
	TAPIREAL64					AccountIntialMargin;			///< 客户初始保证金
	TAPIREAL64					AccountMaintenanceMargin;		///< 客户维持保证金
	TAPIREAL64					UpperInitalMargin;				///< 上手初始保证金
	TAPIREAL64					UpperMaintenanceMargin;			///< 上手维持保证金
	TAPIREAL64					Discount;						///< LME贴现
	TAPIREAL64					Balance;						///< 当日结存
	TAPIREAL64					Equity;							///< 当日权益
	TAPIREAL64					Available;						///< 当日可用
	TAPIREAL64					CanDraw;						///< 可提取
	TAPIREAL64					MarketEquity;					///< 账户市值
	TAPIREAL64					OriginalCashInOut;				///< 币种原始出入金
	TAPIREAL64					FloatingPL;						///< 逐笔浮盈
	TAPIREAL64					FrozenRiskFundValue;			///< 风险冻结资金
	TAPIREAL64					ClosePL;						///< 逐笔平盈
	TAPIREAL64					NoCurrencyPledgeValue;          ///< 非货币质押
	TAPIREAL64					PrePledgeValue;                 ///< 期初质押
	TAPIREAL64					PledgeIn;                       ///< 质入
	TAPIREAL64					PledgeOut;                      ///< 质出
	TAPIREAL64					PledgeValue;                    ///< 质押余额
	TAPIREAL64					BorrowValue;                    ///< 借用金额
	TAPIREAL64					SpecialAccountFrozenMargin;     ///< 特殊产品冻结保证金
	TAPIREAL64					SpecialAccountMargin;           ///< 特殊产品保证金   
	TAPIREAL64					SpecialAccountFrozenFee;        ///< 特殊产品冻结手续费
	TAPIREAL64					SpecialAccountFee;              ///< 特殊产品手续费
	TAPIREAL64					SpecialFloatProfit;             ///< 特殊产品浮盈
	TAPIREAL64					SpecialCloseProfit;             ///< 特殊产品平盈
	TAPIREAL64					SpecialFloatPL;                 ///< 特殊产品逐笔浮盈
	TAPIREAL64					SpecialClosePL;                 ///< 特殊产品逐笔平盈
};

//! 交易品种信息
struct TapAPICommodityInfo
{
	TAPISTR_10				ExchangeNo;						///< 交易所编码
	TAPICommodityType		CommodityType;					///< 品种类型
	TAPISTR_10				CommodityNo;					///< 品种编号
	TAPISTR_20				CommodityName;					///< 品种名称
	TAPISTR_30				CommodityEngName;				///< 品种英文名称
	TAPISTR_10				RelateExchangeNo;				///< 关联品种交易所编码
	TAPICommodityType		RelateCommodityType;			///< 关联品种品种类型
	TAPISTR_10				RelateCommodityNo;				///< 关联品种品种编号
	TAPISTR_10				RelateExchangeNo2;				///< 关联品种2交易所编码
	TAPICommodityType		RelateCommodityType2;			///< 关联品种2品种类型
	TAPISTR_10				RelateCommodityNo2;				///< 关联品种2品种编号
	TAPISTR_10				TradeCurrency;					///< 交易币种
	TAPISTR_10				SettleCurrency;					///< 结算币种
	TAPIREAL64				ContractSize;					///< 每手乘数
	TAPIMarginCalculateModeType			MarginCalculateMode;			///< 期货保证金方式,分笔'1',锁仓'2'
	TAPIOptionMarginCalculateModeType	OptionMarginCalculateMode;		///< 期权保证金公式
	TAPIOpenCloseModeType				OpenCloseMode;					///< 开平方式
	TAPIREAL64				StrikePriceTimes;				///< 执行价格倍数
	TAPIYNFLAG				IsOnlyQuoteCommodity;			///< 单行情品种
	TAPIREAL64				CommodityTickSize;				///< 最小变动价位
	TAPIINT32				CommodityDenominator;			///< 报价分母
	TAPICmbDirectType		CmbDirect;						///< 组合方向
	TAPIINT32				OnlyCanCloseDays;				///< 只可平仓提前天数
	TAPIDeliveryModeType	DeliveryMode;					///< 交割行权方式
	TAPIINT32				DeliveryDays;					///< 交割日偏移
	TAPITIME				AddOneTime;						///< T+1分割时间
	TAPIINT32				CommodityTimeZone;				///< 品种时区
};

//! 交易合约信息
struct TapAPITradeContractInfo
{
	TAPISTR_10              ExchangeNo;                             ///< 交易所编码
	TAPICommodityType		CommodityType;                          ///< 品种类型
	TAPISTR_10              CommodityNo;                            ///< 品种编号
	TAPISTR_10              ContractNo1;                            ///< 合约代码1
	TAPISTR_10              StrikePrice1;                           ///< 执行价1
	TAPICallOrPutFlagType	CallOrPutFlag1;                         ///< 看涨看跌标示1
	TAPISTR_10              ContractNo2;                            ///< 合约代码2
	TAPISTR_10              StrikePrice2;                           ///< 执行价2
	TAPICallOrPutFlagType	CallOrPutFlag2;                         ///< 看涨看跌标示2
	TAPIContractTypeType	ContractType;                           ///< 合约类型
	TAPISTR_10				QuoteUnderlyingContract;				///< 行情真实合约
	TAPISTR_70              ContractName;                           ///< 合约名称
	TAPIDATE                ContractExpDate;                        ///< 合约到期日	
	TAPIDATE                LastTradeDate;                          ///< 最后交易日
	TAPIDATE                FirstNoticeDate;                        ///< 首次通知日
	TAPISTR_10				FutureContractNo;						///< 期货合约编号(期权标的)
};


//! 深度行情信息
struct TapAPIDeepQuoteInfo
{
	TAPISideType				Side;							///< 买卖方向
	TAPIREAL64					Price;							///< 挂单价格
	TAPIUINT32					Qty;							///< 挂单数量
};

//! 深度行情查询应答
struct TapAPIDeepQuoteQryRsp
{
	TapAPIContract			Contract;							///< 合约
	TapAPIDeepQuoteInfo		DeepQuote;							///< 深度行情
};

//! 交易所时间状态信息查询请求结构
struct TapAPIExchangeStateInfoQryReq
{
};

//! 交易所时间状态信息
struct TapAPIExchangeStateInfo
{
	TAPISTR_10				UpperChannelNo;			///< 上手通道编号
	TAPISTR_10				ExchangeNo;				///< 交易所编号
	TAPICommodityType		CommodityType;			///< 品种类型
	TAPISTR_10				CommodityNo;			///< 品种编号
	TAPIDATETIME			ExchangeTime;			///< 交易所时间
	TAPITradingStateType	TradingState;			///< 交易所状态
};

//! 交易所时间状态信息通知结构
struct TapAPIExchangeStateInfoNotice
{
	TAPIYNFLAG				IsLast;					///< 是否最后一包数据
	TapAPIExchangeStateInfo ExchangeStateInfo;		///< 交易所时间状态信息
};

//! 询价通知结构
struct TapAPIReqQuoteNotice
{
	TAPISTR_10					ExchangeNo;						///< 交易所编号
	TAPICommodityType			CommodityType;					///< 品种类型
	TAPISTR_10					CommodityNo;					///< 品种编码类型
	TAPISTR_10					ContractNo;						///< 合约
	TAPISTR_10					StrikePrice;					///< 执行价格
	TAPICallOrPutFlagType		CallOrPutFlag;					///< 看张看跌
	TAPISTR_50					InquiryNo;						///< 询价号
	TAPIDATETIME				UpdateTime;						///< 更新时间                   
};

//! 上手通道信息查询请求结构
struct TapAPIUpperChannelQryReq
{
};

//! 上手通道信息结构
struct TapAPIUpperChannelInfo
{
	TAPISTR_10				UpperChannelNo;			///< 上手通道编号
	TAPISTR_20				UpperChannelName;		///< 上手通道名称
	TAPISTR_10				UpperNo;				///< 上手通道号
	TAPISTR_20				UpperUserNo;			///< 内盘席位号
};
//! 客户最终费率查询请求结构
struct TapAPIAccountRentQryReq
{
    TAPISTR_20                              AccountNo;													//资金账户
    TAPISTR_10                              ExchangeNo;													//交易所编码
	TAPICommodityType			            CommodityType;												//品种类型
	TAPISTR_10                              CommodityNo;												//品种编号
	TAPISTR_10                              ContractNo;													//合约代码 
};
//! 客户最终费率信息结构
struct	TapAPIAccountRentInfo
{
	TAPISTR_20                              AccountNo;													//资金账户
	TAPISTR_10                              ExchangeNo;													//交易所编码
	TAPICommodityType			            CommodityType;												//品种类型
	TAPISTR_10                              CommodityNo;												//品种编号
	TAPISTR_10                              ContractNo;													//合约代码 
	TAPIMatchSourceType			            MatchSource;												//成交来源  
    TAPISTR_10				                CurrencyNo;													//币种编号
	
	TAPICalculateModeType			        FeeMode;                                                    //手续费计算方式 
	TAPIREAL64				                OpenTurnover;												//开仓手续费按金额
	TAPIREAL64				                ClosedTurnover;												//平仓手续费按金额
	TAPIREAL64				                CloseNewTurnover;											//平今手续费按金额
	TAPIREAL64				                OpenVolume;													//开仓手续费按手数
	TAPIREAL64				                ClosedVolume;												//平仓手续费按手数	
    TAPIREAL64				                CloseNewVolume;												//平今手续费按手数
	
    TAPICalculateModeType                   MarginMode;                                                 //保证金计算方式   
	TAPIREAL64				                BuyTInitMargin;												//买投机初始保证金
	TAPIREAL64				                SellTInitMargin;											//卖投机初始保证金
	TAPIREAL64				                BuyBInitMargin;												//买保值初始保证金
	TAPIREAL64				                SellBInitMargin;											//卖保值初始保证金
	TAPIREAL64				                BuyLInitMargin;												//买套利初始保证金
	TAPIREAL64				                SellLInitMargin;											//卖套利初始保证金
	TAPIREAL64				                BuyMInitMargin;												//买做市商初始保证金
	TAPIREAL64				                SellMInitMargin;											//卖做市商初始保证金
	TAPIREAL64				                BuyTMaintMargin;											//买投机维持保证金
	TAPIREAL64				                SellTMaintMargin;											//卖投机维持保证金
	TAPIREAL64				                BuyBMaintMargin;											//买保值维持保证金
	TAPIREAL64				                SellBMaintMargin;											//卖保值维持保证金
	TAPIREAL64				                BuyLMaintMargin;											//买套利维持保证金
	TAPIREAL64				                SellLMaintMargin;											//卖套利维持保证金
	TAPIREAL64				                BuyMMaintMargin;											//买做市商维持保证金
	TAPIREAL64				                SellMMaintMargin;											//卖做市商维持保证金
};

//! 客户账单查询请求结构
struct TapAPIBillQryReq
{
	TAPISTR_20				UserNo;
	TAPIBillTypeType		BillType;
	TAPIDATE				BillDate;
	TAPIBillFileTypeType	BillFileType;
};

//! 客户账单查询应答结构
struct TapAPIBillQryRsp
{
	TapAPIBillQryReq		Reqdata;	
	TAPIINT32				BillLen;
	TAPICHAR				BillText[1];	///< 变长账单内容，长度由BillLen指定
};

//! 客户现货库存查询请求结构
struct TapAPIAccountStorageQryReq
{
    TAPISTR_20						AccountNo;
};

//! 客户现货库存信息
struct TapAPIAccountStorageInfo
{
    TAPISTR_20						AccountNo;
    TAPISTR_10					    ExchangeNo;							///< 交易所编号
	TAPICommodityType				CommodityType;						///< 品种类型
	TAPISTR_10				    	CommodityNo;						///< 品种编号
    TAPIREAL64                      StorageQty;						    ///< 库存量
};

#pragma pack(pop)
#endif //TAP_TRADE_API_DATA_TYPE_H