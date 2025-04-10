#ifndef TAP_TRADE_API_H
#define TAP_TRADE_API_H

#include "TapTradeAPIDataType.h"
//#include "TapProtocol.h"

#if defined WIN32 || defined _WIN64
#define TAP_CDECL __cdecl
#define TAP_DLLEXPORT __declspec(dllexport)
#else
#define TAP_CDECL
#define TAP_DLLEXPORT
#endif

//TapTradeAPI.h
//文件定义了TapTradeAPI提供给开发者的对外接口、函数和回调接口。

//TapTradeAPI 的回调通知接口。
class ITapTradeAPINotify
{
public:
	/**
	* @brief 连接成功回调通知
	* @ingroup G_T_Login
	*/
	virtual void TAP_CDECL OnConnect() = 0;
	/**
	* @brief	系统登录过程回调。
	* @details	此函数为Login()登录函数的回调，调用Login()成功后建立了链路连接，然后API将向服务器发送登录认证信息，
	*			登录期间的数据发送情况和登录的回馈信息传递到此回调函数中。
	* @param[in] errorCode 返回错误码,0表示成功。
	* @param[in] loginRspInfo 登陆应答信息，如果errorCode!=0，则loginRspInfo=NULL。
	* @attention	该回调返回成功，说明用户登录成功。但是不代表API准备完毕。
	* @ingroup G_T_Login
	*/
	virtual void TAP_CDECL OnRspLogin(TAPIINT32 errorCode, const TapAPITradeLoginRspInfo *loginRspInfo) = 0;
	/**
	* @brief	通知用户API准备就绪。
	* @details	只有用户回调收到此就绪通知时才能进行后续的各种行情数据查询操作。\n
	*			此回调函数是API能否正常工作的标志。
	* @attention 就绪后才可以进行后续正常操作
	* @ingroup G_T_Login
	*/
	virtual void TAP_CDECL OnAPIReady() = 0;
	/**
	* @brief	API和服务失去连接的回调
	* @details	在API使用过程中主动或者被动与服务器服务失去连接后都会触发此回调通知用户与服务器的连接已经断开。
	* @param[in] reasonCode 断开原因代码。
	* @ingroup G_T_Disconnect
	*/
	virtual void TAP_CDECL OnDisconnect(TAPIINT32 reasonCode) = 0;
	/**
	* @brief 通知用户密码修改结果
	* @param[in] sessionID 修改密码的会话ID,和ChangePassword返回的会话ID对应。
	* @param[in] errorCode 返回错误码，0表示成功。
	* @ingroup G_T_UserInfo
	*/
	virtual void TAP_CDECL OnRspChangePassword(TAPIUINT32 sessionID, TAPIINT32 errorCode) = 0;
	/**
	* @brief 设置用户预留信息反馈
	* @param[in] sessionID 设置用户预留信息的会话ID
	* @param[in] errorCode 返回错误码，0表示成功。
	* @param[in] info 指向返回的信息结构体。当errorCode不为0时，info为空。
	* @attention 不要修改和删除info所指示的数据；函数调用结束，参数不再有效。
	* @note 该接口暂未实现
	* @ingroup G_T_UserInfo
	*/
	virtual void TAP_CDECL OnRspSetReservedInfo(TAPIUINT32 sessionID, TAPIINT32 errorCode, const TAPISTR_50 info) = 0;
	/**
	* @brief	返回用户信息
	* @details	此回调接口向用户返回查询的资金账号的详细信息。用户有必要将得到的账号编号保存起来，然后在后续的函数调用中使用。
	* @param[in] sessionID 请求的会话ID；
	* @param[in] errorCode 错误码。0 表示成功。
	* @param[in] isLast 标示是否是最后一批数据；
	* @param[in] info 指向返回的信息结构体。当errorCode不为0时，info为空。
	* @attention 不要修改和删除info所指示的数据；函数调用结束，参数不再有效。
	* @ingroup G_T_AccountInfo
	*/
	virtual void TAP_CDECL OnRspQryAccount(TAPIUINT32 sessionID, TAPIUINT32 errorCode, TAPIYNFLAG isLast, const TapAPIAccountInfo *info) = 0;
	/**
	* @brief 返回资金账户的资金信息
	* @param[in] sessionID 请求的会话ID；
	* @param[in] errorCode 错误码。0 表示成功。
	* @param[in] isLast 	标示是否是最后一批数据；
	* @param[in] info		指向返回的信息结构体。当errorCode不为0时，info为空。
	* @attention 不要修改和删除info所指示的数据；函数调用结束，参数不再有效。
	* @ingroup G_T_AccountDetails
	*/
	virtual void TAP_CDECL OnRspQryFund(TAPIUINT32 sessionID, TAPIINT32 errorCode, TAPIYNFLAG isLast, const TapAPIFundData *info) = 0;
	/**
	* @brief	用户资金变化通知
	* @details	用户的委托成交后会引起资金数据的变化，因此需要向用户实时反馈。
	* @param[in] info		指向返回的信息结构体。当errorCode不为0时，info为空。
	* @note 如果不关注此项内容，可以设定Login时的NoticeIgnoreFlag以屏蔽。
	* @attention 不要修改和删除info所指示的数据；函数调用结束，参数不再有效。
	* @ingroup G_T_AccountDetails
	*/
	virtual void TAP_CDECL OnRtnFund(const TapAPIFundData *info) = 0;
	/**
	* @brief 返回系统中的交易所信息
	* @param[in] sessionID 请求的会话ID；
	* @param[in] errorCode 错误码。0 表示成功。
	* @param[in] isLast 	标示是否是最后一批数据；
	* @param[in] info		指向返回的信息结构体。当errorCode不为0时，info为空。
	* @attention 不要修改和删除info所指示的数据；函数调用结束，参数不再有效。
	* @ingroup G_T_TradeSystem
	*/
	virtual void TAP_CDECL OnRspQryExchange(TAPIUINT32 sessionID, TAPIINT32 errorCode, TAPIYNFLAG isLast, const TapAPIExchangeInfo *info) = 0;
	/**
	* @brief	返回系统中品种信息
	* @details	此回调接口用于向用户返回得到的所有品种信息。
	* @param[in] sessionID 请求的会话ID，和GetAllCommodities()函数返回对应；
	* @param[in] errorCode 错误码。0 表示成功。
	* @param[in] isLast 	标示是否是最后一批数据；
	* @param[in] info		指向返回的信息结构体。当errorCode不为0时，info为空。
	* @attention 不要修改和删除info所指示的数据；函数调用结束，参数不再有效。
	* @ingroup G_T_Commodity
	*/
	virtual void TAP_CDECL OnRspQryCommodity(TAPIUINT32 sessionID, TAPIINT32 errorCode, TAPIYNFLAG isLast, const TapAPICommodityInfo *info) = 0;
	/**
	* @brief 返回系统中合约信息
	* @param[in] sessionID 请求的会话ID；
	* @param[in] errorCode 错误码。0 表示成功。
	* @param[in] isLast 	标示是否是最后一批数据；
	* @param[in] info		指向返回的信息结构体。当errorCode不为0时，info为空。
	* @attention 不要修改和删除info所指示的数据；函数调用结束，参数不再有效。
	* @ingroup G_T_Contract
	*/
	virtual void TAP_CDECL OnRspQryContract(TAPIUINT32 sessionID, TAPIINT32 errorCode, TAPIYNFLAG isLast, const TapAPITradeContractInfo *info) = 0;
	/**
	* @brief	返回新增合约信息
	* @details	向用户推送新的合约。主要用来处理在交易时间段中服务器添加了新合约时，向用户发送这个合约的信息。
	* @param[in] info		指向返回的信息结构体。当errorCode不为0时，info为空。
	* @attention 不要修改和删除info所指示的数据；函数调用结束，参数不再有效。
	* @ingroup G_T_Contract
	*/
	virtual void TAP_CDECL OnRtnContract(const TapAPITradeContractInfo *info) = 0;
	/**
	* @brief 返回新委托。新下的或者其他地方下的推送过来的。
	* @details	服务器接收到客户下的委托内容后就会保存起来等待触发，同时向用户回馈一个
	*			新委托信息说明服务器正确处理了用户的请求，返回的信息中包含了全部的委托信息，
	*			同时有一个用来标示此委托的委托号。
	* @param[in] info 指向返回的信息结构体。当errorCode不为0时，info为空。
	* @note 如果不关注此项内容，可以设定Login时的NoticeIgnoreFlag以屏蔽。
	* @attention 不要修改和删除info所指示的数据；函数调用结束，参数不再有效。
	* @ingroup G_T_TradeActions
	*/
	virtual void TAP_CDECL OnRtnOrder(const TapAPIOrderInfoNotice *info) = 0;
	/**
	* @brief	返回对报单的主动操作结果
	* @details	如下单，撤单等操作的结果。
	* @param[in] sessionID 请求的会话ID；
	* @param[in] errorCode 错误码。0 表示成功。
	* @param[in] info 报单的具体信息。当errorCode不为0时，info为空。
	* @attention 不要修改和删除info所指示的数据；函数调用结束，参数不再有效。
	* @note 该接口目前没有用到，所有操作结果通过OnRtnOrder返回
	* @ingroup G_T_TradeActions
	*/
	virtual void TAP_CDECL OnRspOrderAction(TAPIUINT32 sessionID, TAPIUINT32 errorCode, const TapAPIOrderActionRsp *info) = 0;
	/**
	* @brief	返回查询的委托信息
	* @details	返回用户查询的委托的具体信息。
	* @param[in] sessionID 请求的会话ID；
	* @param[in] errorCode 错误码。0 表示成功。
	* @param[in] isLast 标示是否是最后一批数据；
	* @param[in] info 指向返回的信息结构体。当errorCode不为0时，info为空。
	* @attention 不要修改和删除info所指示的数据；函数调用结束，参数不再有效。
	* @ingroup G_T_TradeInfo
	*/
	virtual void TAP_CDECL OnRspQryOrder(TAPIUINT32 sessionID, TAPIINT32 errorCode, TAPIYNFLAG isLast, const TapAPIOrderInfo *info) = 0;
	/**
	* @brief 返回查询的委托变化流程信息
	* @param[in] sessionID 请求的会话ID；
	* @param[in] errorCode 错误码，当errorCode==0时，info指向返回的委托变化流程结构体，不然为NULL；
	* @param[in] isLast 标示是否是最后一批数据；
	* @param[in] info 返回的委托变化流程指针。
	* @attention 不要修改和删除info所指示的数据；函数调用结束，参数不再有效。
	* @ingroup G_T_TradeInfo
	*/
	virtual void TAP_CDECL OnRspQryOrderProcess(TAPIUINT32 sessionID, TAPIINT32 errorCode, TAPIYNFLAG isLast, const TapAPIOrderInfo *info) = 0;
	/**
	* @brief 返回查询的成交信息
	* @param[in] sessionID 请求的会话ID；
	* @param[in] errorCode 错误码。0 表示成功。
	* @param[in] isLast 	标示是否是最后一批数据；
	* @param[in] info		指向返回的信息结构体。当errorCode不为0时，info为空。
	* @attention 不要修改和删除info所指示的数据；函数调用结束，参数不再有效。
	* @ingroup G_T_TradeInfo
	*/
	virtual void TAP_CDECL OnRspQryFill(TAPIUINT32 sessionID, TAPIINT32 errorCode, TAPIYNFLAG isLast, const TapAPIFillInfo *info) = 0;
	/**
	* @brief	推送来的成交信息
	* @details	用户的委托成交后将向用户推送成交信息。
	* @param[in] info		指向返回的信息结构体。当errorCode不为0时，info为空。
	* @note 如果不关注此项内容，可以设定Login时的NoticeIgnoreFlag以屏蔽。
	* @attention 不要修改和删除info所指示的数据；函数调用结束，参数不再有效。
	* @ingroup G_T_TradeActions
	*/
	virtual void TAP_CDECL OnRtnFill(const TapAPIFillInfo *info) = 0;
	/**
	* @brief 返回查询的持仓
	* @param[in] sessionID 请求的会话ID；
	* @param[in] errorCode 错误码。0 表示成功。
	* @param[in] isLast 	标示是否是最后一批数据；
	* @param[in] info		指向返回的信息结构体。当errorCode不为0时，info为空。
	* @attention 不要修改和删除info所指示的数据；函数调用结束，参数不再有效。
	* @ingroup G_T_TradeInfo
	*/
	virtual void TAP_CDECL OnRspQryPosition(TAPIUINT32 sessionID, TAPIINT32 errorCode, TAPIYNFLAG isLast, const TapAPIPositionInfo *info) = 0;
	/**
	* @brief 持仓变化推送通知
	* @param[in] info		指向返回的信息结构体。当errorCode不为0时，info为空。
	* @note 如果不关注此项内容，可以设定Login时的NoticeIgnoreFlag以屏蔽。
	* @attention 不要修改和删除info所指示的数据；函数调用结束，参数不再有效。
	* @ingroup G_T_TradeActions
	*/
	virtual void TAP_CDECL OnRtnPosition(const TapAPIPositionInfo *info) = 0;
	/**
	* @brief 返回查询的平仓
	* @param[in] sessionID 请求的会话ID；
	* @param[in] errorCode 错误码。0 表示成功。
	* @param[in] isLast 	标示是否是最后一批数据；
	* @param[in] info		指向返回的信息结构体。当errorCode不为0时，info为空。
	* @attention 不要修改和删除info所指示的数据；函数调用结束，参数不再有效。
	* @ingroup G_T_TradeInfo
	*/
	virtual void TAP_CDECL OnRspQryClose(TAPIUINT32 sessionID, TAPIINT32 errorCode, TAPIYNFLAG isLast, const TapAPICloseInfo *info) = 0;
	/**
	* @brief 平仓数据变化推送
	* @param[in] info		指向返回的信息结构体。当errorCode不为0时，info为空。
	* @note 如果不关注此项内容，可以设定Login时的NoticeIgnoreFlag以屏蔽。
	* @attention 不要修改和删除info所指示的数据；函数调用结束，参数不再有效。
	* @ingroup G_T_TradeActions
	*/
	virtual void TAP_CDECL OnRtnClose(const TapAPICloseInfo *info) = 0;
	/**
	* @brief 持仓盈亏通知
	* @param[in] info		指向返回的信息结构体。当errorCode不为0时，info为空。
	* @note 如果不关注此项内容，可以设定Login时的NoticeIgnoreFlag以屏蔽。
	* @attention 不要修改和删除info所指示的数据；函数调用结束，参数不再有效。
	* @ingroup G_T_TradeActions
	*/
	virtual void TAP_CDECL OnRtnPositionProfit(const TapAPIPositionProfitNotice *info) = 0;
	/**
	* @brief 深度行情查询应答
	* @param[in] sessionID 请求的会话ID；
	* @param[in] errorCode 错误码。0 表示成功。
	* @param[in] isLast 	标示是否是最后一批数据；
	* @param[in] info	  指向返回的深度行情信息结构体。当errorCode不为0时，info为空。
	* @attention 不要修改和删除info所指示的数据；函数调用结束，参数不再有效。
	* @ingroup G_T_DeepQuote
	*/
	virtual void TAP_CDECL OnRspQryDeepQuote(TAPIUINT32 sessionID, TAPIINT32 errorCode, TAPIYNFLAG isLast, const TapAPIDeepQuoteQryRsp *info) = 0;
	/**
	* @brief 交易所时间状态信息查询应答
	* @param[in] sessionID 请求的会话ID；
	* @param[in] errorCode 错误码。0 表示成功。
	* @param[in] isLast 	标示是否是最后一批数据
	* @param[in] info		指向返回的信息结构体。当errorCode不为0时，info为空。
	* @attention  不要修改和删除info所指示的数据；函数调用结束，参数不再有效。
	* @ingroup G_T_TradeSystem
	*/
	virtual void TAP_CDECL OnRspQryExchangeStateInfo(TAPIUINT32 sessionID,TAPIINT32 errorCode, TAPIYNFLAG isLast,const TapAPIExchangeStateInfo * info)=0;
	/**
	* @brief 交易所时间状态信息通知	
	* @param[in] info		指向返回的信息结构体。当errorCode不为0时，info为空。
	* @attention  不要修改和删除info所指示的数据；函数调用结束，参数不再有效。
	* @ingroup G_T_TradeSystem
	*/
	virtual void TAP_CDECL OnRtnExchangeStateInfo(const TapAPIExchangeStateInfoNotice * info)=0;
	/**
	* @brief 询价通知
	* @param[in] info		指向返回的信息结构体。当errorCode不为0时，info为空。
	* @attention 不要修改和删除info所指示的数据；函数调用结束，参数不再有效。
	* @ingroup G_T_TradeActions
	*/
	virtual void TAP_CDECL OnRtnReqQuoteNotice(const TapAPIReqQuoteNotice *info) = 0;

	/**
	* @brief 上手信息查询应答
	* @param[in] sessionID 请求的会话ID；
	* @param[in] errorCode 错误码。0 表示成功。
	* @param[in] isLast 	标示是否是最后一批数据
	* @param[in] info		指向返回的信息结构体。当errorCode不为0时，info为空。
	* @attention  不要修改和删除info所指示的数据；函数调用结束，参数不再有效。
	* @ingroup G_T_UpperChannelInfo
	*/
	virtual void TAP_CDECL OnRspUpperChannelInfo(TAPIUINT32 sessionID,TAPIINT32 errorCode, TAPIYNFLAG isLast, const TapAPIUpperChannelInfo * info)=0;
        /**
	* @brief 客户最终费率应答
        * @details   保证金比例计算方式：手数*每手乘数*计算参数*价格\n
        *             保证金定额计算方式：手数*计算参数\n
        *             手续费绝对方式计算方式：手数*按手数计算参数+手数*每手乘数*价格*按金额计算参数
	* @param[in] sessionID 请求的会话ID；
	* @param[in] errorCode 错误码。0 表示成功。
	* @param[in] isLast 	标示是否是最后一批数据
	* @param[in] info		指向返回的信息结构体。当errorCode不为0时，info为空。
	* @attention  不要修改和删除info所指示的数据；函数调用结束，参数不再有效。
	* @ingroup G_T_AccountRentInfo
	*/
	virtual void TAP_CDECL OnRspAccountRentInfo(TAPIUINT32 sessionID,TAPIINT32 errorCode, TAPIYNFLAG isLast, const TapAPIAccountRentInfo * info)=0;
	/**
	* @brief 用户提交用户登录信息应答。(直连和中继用户都会收到应答)
	* @param[in] sessionID 请求的会话ID；
	* @param[in] errorCode 错误码。0 表示成功。
	* @param[in] isLast 	标示是否是最后一批数据
	* @param[in] info		指向返回的信息结构体。当errorCode不为0时，info为空。
	* @attention  不要修改和删除info所指示的数据；函数调用结束，参数不再有效。
	* @ingroup G_T_UserInfo
	*/
	virtual void TAP_CDECL OnRspSubmitUserLoginInfo(TAPIUINT32 sessionID, TAPIINT32 errorCode, TAPIYNFLAG isLast, const TapAPISubmitUserLoginRspInfo * info) = 0;
    /**
	* @brief 查询用户账单应答
    * @details	查询txt文件格式时将回调数据写入到本地的txt文件中查看，查询pdf文件时，需要将回调数据转存到pdf文件中，用pdf阅读工具打开。
    *           写文件需要用二进制的方式写入。如果文件较大，数据会分包回调，isLast为APIYNFLAG_YES时，文件传送完毕。
	* @param[in] sessionID 请求的会话ID；
	* @param[in] errorCode 错误码。0 表示成功。
	* @param[in] info		指向返回的信息结构体。当errorCode不为0时，info为空。
	* @attention 不要修改和删除info所指示的数据；函数调用结束，参数不再有效。
	* @ingroup G_T_TradeInfo
	*/
	virtual void TAP_CDECL OnRspQryBill(TAPIUINT32 sessionID, TAPIINT32 errorCode, TAPIYNFLAG isLast, const TapAPIBillQryRsp *info) = 0;
    /**
    * @brief 客户现货库存查询应答
	* @param[in] sessionID 请求ID
	* @param[in] errorCode 错误码。0 表示成功。
	* @param[in] isLast 	标示是否是最后一批数据
	* @param[out] info	指向返回的信息结构体。
	* @attention  不要修改和删除pRspInfo所指示的数据；函数调用结束，参数不再有效。
	* @ingroup G_T_TradeInfo
    */
    virtual void TAP_CDECL OnRspQryAccountStorage(TAPIUINT32 sessionID, TAPIINT32 errorCode, TAPIYNFLAG isLast, const TapAPIAccountStorageInfo* info) = 0;
    /**
    * @brief 客户现货库存通知
	* @param[out] pInfo	指向返回的信息结构体。
	* @attention  不要修改和删除pRspInfo所指示的数据；函数调用结束，参数不再有效。
	* @ingroup G_T_TradeInfo
    */
    virtual void TAP_CDECL OnRtnAccountStorage(const TapAPIAccountStorageInfo* info) = 0;
};

//TapTradeAPI 对外功能接口。包含了用户可以调用的功能函数。
class ITapTradeAPI
{
public:
	/**
	* @brief	设置API的回调接口对象。
	* @details	系统对API的通知将通过设置的回调对象通知给使用者。
	*			ITapTradeAPINotify是API的回调接口，用户需要继承实现此接口类对象来完成用户需要的功能。
	*			如果用户没有设置回调接口，则API不会向用户返回任何有用的信息。\n
	*			ITapTradeAPINotify类的详细内容请查看TapTradeAPI.h 文件。
	* @param[in] apiNotify 实现了ITapTradeAPINotify接口的对象指针。
	* @operationtype 同步操作
	* @ingroup G_T_Login
	*/
	virtual TAPIINT32 TAP_CDECL SetAPINotify(ITapTradeAPINotify *apiNotify) = 0;
	/**
	* @brief 设置服务器的IP地址和端口。
	* @param[in] IP   IP地址
	* @param[in] port 端口号
	* @operationtype 同步操作
	* @ingroup G_T_Login
	*/
	virtual TAPIINT32 TAP_CDECL SetHostAddress(const TAPICHAR *IP, TAPIUINT16 port) = 0;
	/**
	* @brief	发起登录请求。API将先连接服务，建立链路，发起登录认证。
	* @details	在使用函数前用户需要完成服务器的设置SetHostAddress()，并且创建TapAPITradeLoginAuth类型的用户信息，
	*			并且需要设置好回调接口。\n
	*			登录过程中建立连接的返回信息通过回调OnConnect返回给用户。\n
	*			连接建立后的用户验证回馈信息通过回调OnLogin()返回给用户。\n
	*			登录成功后API会自动进行API的初始化，API向服务器请求基础数据，查询完以后会通过回调OnAPIReady()
	*			指示用户API初始化完成，可以进行后续的操作了。
	* @param[in] loginAuth 登录验证信息结构指针。包含登录需要的验证信息。
	* @retval 0 登录成功，API开始准备后台数据
	* @retval 非0 错误码
	* @operationtype 异步操作
	* @note TapAPITradeLoginAuth中的NoticeIgnoreFlag用于标记是否忽略特定的通知回调。\n
	*       例如：不需要接收OnRtnFund和OnRtnPositionProfit,可以这么设定：\n 
	*       NoticeIgnoreFlag = TAPI_NOTICE_IGNORE_FUND | TAPI_NOTICE_IGNORE_POSITIONPROFIT;
	* @attention Login()函数调用成功只是代表于服务器建立了链路连接，只有回调OnLogin()的返回能指示用户是否成功登录了。
	* @ingroup G_T_Login
	*/
	virtual TAPIINT32 TAP_CDECL Login(const TapAPITradeLoginAuth *loginAuth) = 0;
	/**
	* @brief	断开和服务器的链路连接。
	* @details	调用函数后API将登出并断开与服务器的连接。
	* @operationtype 同步操作
	* @ingroup G_T_Disconnect
	*/
	virtual TAPIINT32 TAP_CDECL Disconnect() = 0;
	/**
	* @brief	修改密码。
	* @details	成功后用户密码将被设置成newPassword。
	* @param[out]	sessionID 返回此次修改密码的会话ID;
	* @param[in]	req 请求修改密码的结构体指针
	* @retval 0 成功
	* @retval 非0 错误码
	* @operationtype 异步操作
	* @ingroup G_T_UserInfo
	*/
	virtual TAPIINT32 TAP_CDECL ChangePassword(TAPIUINT32 *sessionID, const TapAPIChangePasswordReq *req) = 0;
	/**
	* @brief	判断登录用户是否具有某权限。
	* @details	用户的权限在用户登录时已经传递给API，所以此函数执行的是本地的查询。
	* @param[in] rightID 权限ID。
	* @retval 0 不具有权限
	* @retval 非0 具有权限
	* @operationtype 同步操作
	* @ingroup G_T_UserRight
	*/
	virtual TAPIINT32 TAP_CDECL HaveCertainRight(TAPIRightIDType rightID) = 0;
	/**
	* @brief	设置用户预留信息。
	* @details	用户可以设置一个长度为50以内的字符信息，下次登录后可以得到这个信息。
	*			这个功能主要是用来让用户确认是自己的账号，主要是用来进行防伪。
	* @param[out]	sessionID 返回请求的会话ID;
	* @param[in] info	预留信息字符串指针
	* @retval 0 请求成功
	* @retval 非0 错误码
	* @operationtype 异步操作
	* @note 该接口暂未实现
	* @ingroup G_T_UserInfo
	*/
	virtual TAPIINT32 TAP_CDECL SetReservedInfo(TAPIUINT32 *sessionID, const TAPISTR_50 info) = 0;
	/**
	* @brief 查询用户下属的资金账号
	* @details	TapAPIAccQryReq是包含资金账号结构的结构体，用户需要实例化此结构体，
	*			但是不需要填写，这个结构体主要是用来提醒用户保存资金账号，资金账号
	*			在后续的函数调用中很多函数都需要使用到。
	* @param[out]	sessionID 返回请求的会话ID;
	* @param[in]	qryReq 查询用户下属的资金账号的结构体指针
	* @retval 0 请求成功
	* @retval 非0 错误码
	* @operationtype 异步操作
	* @ingroup G_T_AccountInfo
	*/
	virtual TAPIINT32 TAP_CDECL QryAccount(TAPIUINT32 *sessionID, const TapAPIAccQryReq *qryReq) = 0;
	/**
	* @brief	查询客户资金
	* @details	TapAPIFundReq需要QryAccount()获取的资金账号。
	*			函数的回调将返回资金账号的资金信息。\n
	* @param[out] sessionID 返回请求的会话ID;
	* @param[in] qryReq	查询客户资金请求的结构体指针
	* @retval 0 请求成功
	* @retval 非0 错误码
	* @operationtype 异步操作
	* @ingroup G_T_AccountDetails
	* @attention 每次登陆，该接口只能进行一次调用。建议初始化时调用一次，后续的通知通过OnRtnFund取得。
	*/
	virtual TAPIINT32 TAP_CDECL QryFund(TAPIUINT32 *sessionID, const TapAPIFundReq *qryReq) = 0;
	/**
	* @brief 查询交易系统交易所信息
	* @param[out] sessionID 返回请求的会话ID;
	* @retval 0 请求成功
	* @retval 非0 错误码
	* @operationtype 异步操作
	* @ingroup G_T_TradeSystem
	*/
	virtual TAPIINT32 TAP_CDECL QryExchange(TAPIUINT32 *sessionID) = 0;
	/**
	* @brief	查询系统品种信息
	* @details	函数请求获取所有的品种信息。
	* @param[out] sessionID 返回请求的会话ID;
	* @retval 0 请求成功
	* @retval 非0 错误码
	* @operationtype 异步操作
	* @ingroup G_T_Commodity
	*/
	virtual TAPIINT32 TAP_CDECL QryCommodity(TAPIUINT32 *sessionID) = 0;
	/**
	* @brief	查询系统中指定品种的合约信息
	* @details	使用此函数前需要先QrycommodityInfo()取得品种信息，
	*			然后选择需要的品种将信息填入TapAPICommodity结构体中完成查询请求。
	* @param[out] sessionID 返回请求的会话ID;
	* @param[in] qryReq 查询系统中指定品种的合约信息请求的结构体指针;\n
	*				    该参数各字段为可选字段，可以用以下方法查询：\n
	*					1.全部留空：查所有合约\n
	*					2.仅交易所编码有效：查该交易所下所有品种的合约\n
	*					3.交易所编码和品种类型有效：查该交易所下指定品种类型的合约\n
	*					4.交易所编码、品种类型和品种编码都有效：查该品种下的所有合约
	* @retval 0 请求成功
	* @retval 非0 错误码
	* @operationtype 异步操作
	* @ingroup G_T_Contract
	*/
	virtual TAPIINT32 TAP_CDECL QryContract(TAPIUINT32 *sessionID, const TapAPICommodity *qryReq) = 0;
	/**
	* @brief	下单
	* @details	用户下单的操作函数。
	*			用户的下单操作会造成用户的资金、持仓、平仓、资金、风控标记等多种数据的变化，所以用户下的单成交后，
	*			会有多个回调通知来向用户展示数据的变化。
	* @param[out]	sessionID 返回请求的会话ID;
	* @param[in]	order 新的委托
	* @retval 0 请求成功
	* @retval 非0 错误码
	* @operationtype 异步操作
	* @ingroup G_T_TradeActions
	*/
	virtual TAPIINT32 TAP_CDECL InsertOrder(TAPIUINT32 *sessionID, const TapAPINewOrder *order) = 0;
	/**
	* @brief	撤单
	* @details	用户委托没有完全成交之前撤销剩余的委托。
	* @param[out]	sessionID 返回请求的会话ID;
	* @param[in]	order 撤销的委托
	* @retval 0 请求成功
	* @retval 非0 错误码
	* @operationtype 异步操作
	* @ingroup G_T_TradeActions
	*/
	virtual TAPIINT32 TAP_CDECL CancelOrder(TAPIUINT32 *sessionID, const TapAPIOrderCancelReq *order) = 0;
	/**
	* @brief	查询委托信息
	* @details	返回当前的委托信息，可以查询所有委托，也可以查询所有未结束的委托。\n
	* @retval 0 请求成功
	* @retval 非0 错误码
	* @operationtype 异步操作
	* @ingroup G_T_TradeInfo
	* @attention 该接口可以多次调用，但是有查询频率的要求，每两秒可以查询一次
	*/
	virtual TAPIINT32 TAP_CDECL QryOrder(TAPIUINT32 *sessionID, const TapAPIOrderQryReq *qryReq) = 0;
	/**
	* @brief	查询委托变化流程
	* @details	查询用户的委托的变化流程，查询将返回委托的每一次的变化。
	* @param[out] sessionID 返回请求的会话ID;
	* @param[in] qryReq 委托流程查询信息结构体指针。
	* @retval 0 请求成功
	* @retval 非0 错误码
	* @operationtype 异步操作
	* @ingroup G_T_TradeInfo
	*/
	virtual TAPIINT32 TAP_CDECL QryOrderProcess(TAPIUINT32 *sessionID, const TapAPIOrderProcessQryReq *qryReq) = 0;
	/**
	* @brief 查询成交信息
	* @details	查询系统中成交的信息。
	* @param[out] sessionID 返回请求的会话ID;
	* @param[in] qryReq 成交查询信息结构体指针。
	* @retval 0 请求成功
	* @retval 非0 错误码
	* @operationtype 异步操作
	* @ingroup G_T_TradeInfo
	* @attention 每次登陆，该接口只能进行一次调用。建议初始化时调用一次，后续的通知通过OnRtnFill取得。
	*/
	virtual TAPIINT32 TAP_CDECL QryFill(TAPIUINT32 *sessionID, const TapAPIFillQryReq *qryReq) = 0;
	/**
	* @brief	查询用户持仓
	* @details	查询用户的所有持仓信息。
	* @param[out] sessionID 返回请求的会话ID;
	* @param[in] qryReq	查询用户持仓请求的结构体指针
	* @retval 0 请求成功
	* @retval 非0 错误码
	* @operationtype 异步操作
	* @ingroup G_T_TradeInfo
	* @attention 该接口可以多次调用，但是有查询频率的要求，每两秒可以查询一次
	*/
	virtual TAPIINT32 TAP_CDECL QryPosition(TAPIUINT32 *sessionID, const TapAPIPositionQryReq *qryReq) = 0;
	/**
	* @brief 查询平仓记录
	* @details	查询用户所有的平仓记录。
	* @param[out] sessionID 返回请求的会话ID;
	* @param[in] qryReq	查询平仓记录请求的结构体指针
	* @retval 0 请求成功
	* @retval 非0 错误码
	* @operationtype 异步操作
	* @ingroup G_T_TradeInfo
	* @attention 每次登陆，该接口只能进行一次调用。建议初始化时调用一次，后续的通知通过OnRtnClose取得。
	*/
	virtual TAPIINT32 TAP_CDECL QryClose(TAPIUINT32 *sessionID, const TapAPICloseQryReq *qryReq) = 0;
	/**
	* @brief 查询深度行情
	* @param[out]	sessionID 返回请求的会话ID;
	* @param[in]	qryReq	查询深度行情的请求结构体指针，第二个合约留空。
	* @retval 0 请求成功
	* @retval 非0 错误码
	* @operationtype 异步操作
	* @ingroup G_T_DeepQuote
	*/
	virtual TAPIINT32 TAP_CDECL QryDeepQuote(TAPIUINT32 *sessionID, const TapAPIContract *qryReq) = 0;
	/**
	* @brief	查询交易所时间状态信息
	* @param[out]	sessionID 返回请求的会话ID;
	* @param[in]	qryReq 查询交易所时间状态信息请求结构体指针
	* @retval 0 请求成功
	* @retval 非0 错误码
	* @operationtype 异步操作
	* @ingroup G_T_TradeSystem
	*/
	virtual TAPIINT32 TAP_CDECL QryExchangeStateInfo(TAPIUINT32 * sessionID,const TapAPIExchangeStateInfoQryReq * qryReq)=0;
	/**
	* @brief   查询上手信息,主要是用于客户下单时指定通道号，方便主动选择单子进入交易所前置机
	* @param[out]    sessionID 返回请求的会话ID;
	* @param[in]	 qryReq    上手通道信息查询请求结构体指针
	* @retval  0   请求成功
	* @retval  非0 错误码
	* @operationtype 异步操作
	* @ingroup G_T_UpperChannelInfo
	*/
	virtual TAPIINT32 TAP_CDECL QryUpperChannel(TAPIUINT32 * sessionID, const TapAPIUpperChannelQryReq * qryReq)=0;
        /**
	* @brief   查询客户最终费率,主要是用于客户查询各个合约最终费率，可用于结算等
	* @param[out]    sessionID 返回请求的会话ID;
	* @param[in]	 qryReq    客户最终费率查询请求结构体指针
	* @retval  0   请求成功
	* @retval  非0 错误码
	* @operationtype 异步操作
	* @ingroup G_T_AccountRentInfo
	*/
	virtual TAPIINT32 TAP_CDECL QryAccountRent(TAPIUINT32 * sessionID, const TapAPIAccountRentQryReq * qryReq)=0;
	/**
	* @brief	激活报单
	* @details	激活挂起的报单。委托将可以重新开始触发成交。
	* @param[out]	sessionID 返回请求的会话ID;
	* @param[in]	qryReq 激活的委托
	* @retval 0 请求成功
	* @retval 非0 错误码
	* @operationtype 异步操作
	* @ingroup G_T_TradeActions
	*/
	virtual TAPIINT32 TAP_CDECL ActivateOrder(TAPIUINT32 *sessionID, const TapAPIOrderActivateReq *qryReq) = 0;
	/**
	* @brief		中继用户提交用户登录信息。
	* @details		登录成功后只有中继用户才能使用该函数。
	* @param[out]	sessionID 返回请求的会话ID;
	* @param[in]	qryReq 用户登录信息
	* @retval		0 成功；非0 错误码
	* @operationtype 异步操作
	* @ingroup G_T_UserInfo
	*/
	virtual TAPIINT32 TAP_CDECL SubmitUserLoginInfo(TAPIUINT32 *sessionID, const TapAPISubmitUserLoginInfo* qryReq) = 0;
    /**
	* @brief 查询用户账单
	* @param[out]	sessionID 返回请求的会话ID;
	* @param[in]	qryReq	查询帐单请求的结构体指针
	* @retval 0 请求成功
	* @retval 非0 错误码
	* @operationtype 异步操作
	* @ingroup G_T_TradeInfo
	*/
	virtual TAPIINT32 TAP_CDECL QryBill(TAPIUINT32 *sessionID, const TapAPIBillQryReq *qryReq) = 0;
    /**
	* @brief 客户现货库存查询
	* @param[in]	sessionID 请求ID
	* @param[in]	pReqInfo 客户现货库存查询请求结构
	* @retval		0 请求成功;非0 错误码
	* @operationtype 异步操作
	* @ingroup G_T_TradeInfo
	*/
    virtual TAPIINT32 TAP_CDECL QryAccountStorage(TAPIUINT32 *sessionID, const TapAPIAccountStorageQryReq *qryReq) = 0;
};

//-----------------------------TapTradeAPI导出函数------------------------------------


#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

/**
* @brief	创建TapTradeAPI的接口对象。
* @details	创建整个交易API的接口
* @param[in] appInfo 应用程序相关信息。KeyOperationLogPath 路径为空时不产生其操作日志
* @param[in] iResult 创建接口的错误码。
* @retval NULL	创建失败，具体原因可通过输出参数iResult判断。
* @retval !NULL	实现了ITapTradeAPI接口的对象指针。
* @ingroup G_T_API
*/
TAP_DLLEXPORT ITapTradeAPI *TAP_CDECL CreateTapTradeAPI(const TapAPIApplicationInfo *appInfo, TAPIINT32 &iResult);
/**
* @brief	销毁通过CreateTapTradeAPI函数创建的ITapTradeAPI对象。
* @param[in] apiObj ITapTradeAPI对象指针。
* @ingroup G_T_API
*/
TAP_DLLEXPORT void TAP_CDECL FreeTapTradeAPI(ITapTradeAPI *apiObj);
/**
* @brief	获取TapTradeAPI的版本信息
* @ingroup G_T_API
*/
TAP_DLLEXPORT const TAPICHAR *TAP_CDECL GetTapTradeAPIVersion();
/**
* @brief	设置API自身保存数据目录
* @details	调用函数的同时会在path描述的目录下打开以年月日（格式TapTradeAPI[YYYYMMDD].log)命名的文件，\n
*			没有此文件的情况下会试图创建此文件。\n
*			文件中保存的数据为API接收到的重要数据和API的使用和错误日志。
* @param[in] path 目录。必须可用，目录符号Window下为”\\”或者”/”, Linux下为”/”。
* @retval 0 成功
* @retval 非0 错误码
* @operationtype 同步操作
* @ingroup G_T_LogConfig
*/
TAP_DLLEXPORT TAPIINT32 TAP_CDECL SetTapTradeAPIDataPath(const TAPICHAR *path);
/**
* @brief	设置API的日志级别
* @details	设定日志的输出级别，只有当实际日志级别与此处设定的级别相同或更高时，才会将日志写入SetTapTradeAPIDataPath()函数打开的日志文件。\n
* @param[in]	level 日志级别：\n
*					APILOGLEVEL_NONE	：不记录日志\n
*					APILOGLEVEL_ERROR	：记录Error日志\n
*					APILOGLEVEL_WARNING	：记录Error和Warning日志\n
*					APILOGLEVEL_DEBUG	：记录Error、Warning和Debug日志\n
* @retval 0 设定成功
* @retval 非0 错误码
* @operationtype 同步操作
* @ingroup G_T_LogConfig
*/
TAP_DLLEXPORT TAPIINT32 TAP_CDECL SetTapTradeAPILogLevel(TAPILOGLEVEL level);

#ifdef __cplusplus
}
#endif // __cplusplus


#endif // TAP_TRADE_API_H