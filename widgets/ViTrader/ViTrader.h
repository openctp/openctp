// ViTrader
// writen by krenx@qq.com
//
//
#ifndef __VI_TRADER_H__
#define __VI_TRADER_H__

#include "curses.h"
#include <map>
#include <vector>

#include "ThostFtdcMdApi.h"
#include "ThostFtdcTraderApi.h"

// openctp ext
#define OPENCTP_FTDC_PC_EQUITY 'E'
#define OPENCTP_FTDC_PC_BOND 'B'
#define OPENCTP_FTDC_PC_FUND 'D'

#define CONNECTION_STATUS_DISCONNECTED	0
#define CONNECTION_STATUS_CONNECTED		1
#define CONNECTION_STATUS_LOGINOK		2
#define CONNECTION_STATUS_LOGINFAILED	3

#define WORKING_STATUS_NONE		0
#define WORKING_STATUS_WORKING	1

class CTradeRsp:public CThostFtdcTraderSpi
{
public:
	CTradeRsp();
	~CTradeRsp();

	//已连接
	void OnFrontConnected();
	
	//未连接
	void OnFrontDisconnected(int nReason);
	
	///认证响应
	void OnRspAuthenticate(CThostFtdcRspAuthenticateField *pRspAuthenticateField, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	//登录应答
	void OnRspUserLogin(CThostFtdcRspUserLoginField *pRspUserLogin,CThostFtdcRspInfoField *pRspInfo,int nRequestID,bool bIsLast);
	
	//登出应答
	void OnRspUserLogout(CThostFtdcUserLogoutField *pUserLogout,CThostFtdcRspInfoField *pRspInfo,int nRequestID,bool bIsLast);
	
	// 查询合约列表
	void OnRspQryInstrument(CThostFtdcInstrumentField *pInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	// 查询行情列表
	void OnRspQryDepthMarketData(CThostFtdcDepthMarketDataField *pDepthMarketData, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	// 查询委托列表
	void OnRspQryOrder(CThostFtdcOrderField *pOrder, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	// 查询成交列表
	void OnRspQryTrade(CThostFtdcTradeField *pTrade, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	// 查询持仓
	void OnRspQryInvestorPosition(CThostFtdcInvestorPositionField *pInvestorPosition, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	// 查询持仓明细
	void OnRspQryInvestorPositionDetail(CThostFtdcInvestorPositionDetailField *pInvestorPositionDetail, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	///请求查询资金账户响应
	void OnRspQryTradingAccount(CThostFtdcTradingAccountField *pTradingAccount, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	///报单录入请求响应
	void OnRspOrderInsert(CThostFtdcInputOrderField *pInputOrder, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
		
	///报单操作请求响应
	void OnRspOrderAction(CThostFtdcInputOrderActionField *pInputOrderAction, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	// 委托回报
	void OnRtnOrder(CThostFtdcOrderField *pOrder);

	// 成交回报
	void OnRtnTrade(CThostFtdcTradeField *pTrade);

	// 报单错误
	void OnErrRtnOrderInsert(CThostFtdcInputOrderField *pInputOrder, CThostFtdcRspInfoField *pRspInfo);

	// 撤单错误回报
	void OnErrRtnOrderAction(CThostFtdcOrderActionField *pOrderAction, CThostFtdcRspInfoField *pRspInfo);


	void HandleFrontDisconnected(int nReason);
	void HandleFrontConnected();
	void HandleRspAuthenticate(CThostFtdcRspAuthenticateField& RspAuthenticateField, CThostFtdcRspInfoField& RspInfo, int nRequestID, bool bIsLast);
	void HandleRspUserLogin(CThostFtdcRspUserLoginField& RspUserLogin,CThostFtdcRspInfoField& RspInfo,int nRequestID,bool bIsLast);
	void HandleRspUserLogout(CThostFtdcUserLogoutField& UserLogout,CThostFtdcRspInfoField& RspInfo,int nRequestID,bool bIsLast);
	void HandleRspQryInstrument(CThostFtdcInstrumentField& Instrument, CThostFtdcRspInfoField& RspInfo, int nRequestID, bool bIsLast);
	void HandleRspQryOrder(CThostFtdcOrderField& Order, CThostFtdcRspInfoField& RspInfo, int nRequestID, bool bIsLast);
	void HandleRspQryTrade(CThostFtdcTradeField& Trade, CThostFtdcRspInfoField& RspInfo, int nRequestID, bool bIsLast);
	void HandleRspQryInvestorPosition(CThostFtdcInvestorPositionField& InvestorPosition, CThostFtdcRspInfoField& RspInfo, int nRequestID, bool bIsLast);
	void HandleRspQryTradingAccount(CThostFtdcTradingAccountField& TradingAccount, CThostFtdcRspInfoField& RspInfo, int nRequestID, bool bIsLast);
	void HandleRtnOrder(CThostFtdcOrderField& Order);
	void HandleRtnTrade(CThostFtdcTradeField& Trade);
	void HandleErrRtnOrderInsert(CThostFtdcInputOrderField& InputOrder, CThostFtdcRspInfoField& RspInfo);
	void HandleErrRtnOrderAction(CThostFtdcOrderActionField& OrderAction, CThostFtdcRspInfoField& RspInfo);
	void HandleRspOrderInsert(CThostFtdcInputOrderField& InputOrder, CThostFtdcRspInfoField& RspInfo, int nRequestID, bool bIsLast);
	void HandleRspOrderAction(CThostFtdcInputOrderActionField& InputOrderAction, CThostFtdcRspInfoField& RspInfo, int nRequestID, bool bIsLast);

	int FrontID;
	int SessionID;
	int OrderRef;
	CThostFtdcTraderApi *m_pTradeReq;
	TThostFtdcUserIDType UserID;
	TThostFtdcPasswordType Password;
	TThostFtdcBrokerIDType BrokerID;
	TThostFtdcDateType TradingDay;
	TThostFtdcProductInfoType	UserProductInfo;
	TThostFtdcIPAddressType		ClientIPAddress;
	TThostFtdcMacAddressType	MacAddress;
	TThostFtdcLoginRemarkType	LoginRemark;
	TThostFtdcAuthCodeType	AuthCode;
	TThostFtdcAppIDType	AppID;
	std::vector<CThostFtdcOrderField> m_mMovingOrders;
	std::vector<CThostFtdcInvestorPositionField> m_vInvestorPositions;
};
class CMarketRsp:public CThostFtdcMdSpi
{
public:
	CMarketRsp();
	~CMarketRsp();

	//已连接
	void OnFrontConnected();
	
	//未连接
	void OnFrontDisconnected(int nReason);
	
	//登录应答
	void OnRspUserLogin(CThostFtdcRspUserLoginField *pRspUserLogin,CThostFtdcRspInfoField *pRspInfo,int nRequestID,bool bIsLast);
	
	//登出应答
	void OnRspUserLogout(CThostFtdcUserLogoutField *pUserLogout,CThostFtdcRspInfoField *pRspInfo,int nRequestID,bool bIsLast);
	
	//定阅应答
	void OnRspSubMarketData(CThostFtdcSpecificInstrumentField *pSpecificInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
	
	//退订应答
	void OnRspUnSubMarketData(CThostFtdcSpecificInstrumentField *pSpecificInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
	
	//行情服务的深度行情通知
	void OnRtnDepthMarketData(CThostFtdcDepthMarketDataField *pDepthMarketData);


	void HandleFrontConnected();
	void HandleFrontDisconnected(int nReason);
	void HandleRspUserLogin(CThostFtdcRspUserLoginField& RspUserLogin,CThostFtdcRspInfoField& RspInfo,int nRequestID,bool bIsLast);
	void HandleRspUserLogout(CThostFtdcUserLogoutField& UserLogout,CThostFtdcRspInfoField& RspInfo,int nRequestID,bool bIsLast);
	void HandleRtnDepthMarketData(CThostFtdcDepthMarketDataField& DepthMarketData);

	CThostFtdcMdApi *m_pMarketReq;
	TThostFtdcUserIDType UserID;
	TThostFtdcPasswordType Password;
	TThostFtdcBrokerIDType BrokerID;
};

typedef struct {
	TThostFtdcBrokerIDType BrokerID;
	TThostFtdcInvestorIDType InvestorID;
	TThostFtdcExchangeIDType ExchangeID;
	TThostFtdcInstrumentIDType InstrumentID;
	int Volume;
	double Price;
	double ProfitLoss;
	double Margin;
	double Balance;
	int BuyVolume;
	double AvgBuyPrice;
	double BuyProfitLoss;
	int TodayBuyVolume;
	int FrozenBuyVolume;
	int TodayFrozenBuyVolume;
	int BuyingVolume;
	int SellVolume;
	double AvgSellPrice;
	double SellProfitLoss;
	int TodaySellVolume;
	int FrozenSellVolume;
	int TodayFrozenSellVolume;
	int SellingVolume;
} stPosition_t;


// Basic
int subscribe(size_t index);
int unsubscribe(size_t index);
void init_screen();
void on_key_pressed(int ch);
void time_thread();
void work_thread();
void HandleTickTimeout();
void HandleStatusClear();
double GetProfitLoss(const char* InstrumentID);
double GetBuyProfitLoss(const char* InstrumentID);
double GetSellProfitLoss(const char* InstrumentID);
double GetPositionBalance(const char* InstrumentID);
stPosition_t& GetPosition(const char* InstrumentID);
CThostFtdcInstrumentField& GetInstrument(const char* InstrumentID);
CThostFtdcDepthMarketDataField& GetDepthMarketData(const char* InstrumentID);
int GetPrecision(const char* InstrumentID);

// Main Board
void refresh_screen();
void display_title();
void display_status();
void display_quotation(size_t index);
int on_key_pressed_mainboard(int ch);
int input_parse(int *num,int *cmd);
int goto_order_window_from_mainboard();
int goto_column_settings_window_from_mainboard();
int goto_symbol_window_from_mainboard();
int goto_orderlist_window_from_mainboard();
int goto_filllist_window_from_mainboard();
int goto_positionlist_window_from_mainboard();
int goto_acclist_window_from_mainboard();
int move_forward_1_line();
int move_backward_1_line();
int scroll_forward_1_line();
int scroll_backward_1_line();
int scroll_left_1_column();
int scroll_right_1_column();
int goto_file_top();
int goto_file_bottom();
int goto_page_top();
int goto_page_bottom();
int goto_page_middle();
int move_left_1_column();
int move_right_1_column();
int move_forward_1_page();
int move_backward_1_page();
int move_forward_half_page();
int move_backward_half_page();
void focus_quotation(int index);

// Favorite
int on_key_pressed_favorite(int ch);


// Order
void order_refresh_screen();
void order_display_title();
void order_display_prices();
void order_display_bid_ask();
void order_display_orders();
void order_display_orders_at_price(double price);
void order_display_status();
void order_display_focus();
void order_reset();
void order_redraw();
void order_display_quotation(const char *InstrumentID);
int on_key_pressed_order(int ch);
int goto_mainboard_window_from_order();
int goto_orderlist_window_from_order();
int goto_filllist_window_from_order();
int goto_positionlist_window_from_order();
int goto_acclist_window_from_order();
void order_centralize_current_price();
void order_move_forward_1_line();
void order_move_backward_1_line();
void order_scroll_forward_1_line();
void order_scroll_backward_1_line();
void order_goto_file_top();
void order_goto_file_bottom();
void order_goto_page_top();
void order_goto_page_bottom();
void order_goto_page_middle();
int order_move_forward_1_page();
int order_move_backward_1_page();
int order_move_forward_half_page();
int order_move_backward_half_page();
int order_refresh_quote();
int order_goto_price(double price);
int order_goto_sell_column();
int order_goto_buy_column();
int order_goto_bid_price();
int order_goto_ask_price();
int order_goto_high_price();
int order_goto_low_price();
int order_goto_open_price();
int order_goto_settlement_price();
int order_goto_last_settlement_price();
void order_buy_at_market(unsigned int n);
void order_sell_at_market(unsigned int n);
void order_buy_at_limit(unsigned int n);
void order_sell_at_limit(unsigned int n);
void order_revert_at_limit();
void order_revert_at_market();
void order_cancel_orders();
void order_cancel_all_orders();
void order_cancel_orders_at_price(double price);
void order_buy_at_limit_price(double price,unsigned int n);
void order_sell_at_limit_price(double price,unsigned int n);
char getOrderOffsetFlag(const char* szInstrument,char cDirection,unsigned int nQty,unsigned int &nOpen,unsigned int &nClose,unsigned int &nCloseToday);
int OrderInsert(const char* InstrumentID,char BSFlag,char OCFlag,double Price,unsigned int Qty);
void order_open_last_symbol();
void order_move_orders();
void order_move_complete();

// Order List
void orderlist_refresh_screen();
void orderlist_display_title();
void orderlist_display_orders();
void orderlist_display_status();
void orderlist_display_focus();
void orderlist_redraw();
void orderlist_reset(const char *UserID);
void orderlist_display_order(int index);
int on_key_pressed_orderlist(int ch);
int goto_mainboard_window_from_orderlist();
int goto_order_window_from_orderlist();
int goto_filllist_window_from_orderlist();
int goto_positionlist_window_from_orderlist();
int goto_acclist_window_from_orderlist();
void orderlist_move_forward_1_line();
void orderlist_move_backward_1_line();
void orderlist_scroll_forward_1_line();
void orderlist_scroll_backward_1_line();
void orderlist_goto_file_top();
void orderlist_goto_file_bottom();
void orderlist_goto_page_top();
void orderlist_goto_page_bottom();
void orderlist_goto_page_middle();
void orderlist_move_forward_1_page();
void orderlist_move_backward_1_page();
void orderlist_move_forward_half_page();
void orderlist_move_backward_half_page();
void orderlist_scroll_left_1_column();
void orderlist_scroll_right_1_column();
int orderlist_cancel_order();
int orderlist_goto_order_window();

// Fill List
void filllist_refresh_screen();
void filllist_display_title();
void filllist_display_filledorders();
void filllist_display_status();
void filllist_display_focus();
void filllist_redraw();
void filllist_reset(const char *UserID);
void filllist_display_filledorder(int index);
int on_key_pressed_filllist(int ch);
int goto_mainboard_window_from_filllist();
int goto_order_window_from_filllist();
int goto_orderlist_window_from_filllist();
int goto_positionlist_window_from_filllist();
int goto_acclist_window_from_filllist();
void filllist_move_forward_1_line();
void filllist_move_backward_1_line();
void filllist_scroll_forward_1_line();
void filllist_scroll_backward_1_line();
void filllist_goto_file_top();
void filllist_goto_file_bottom();
void filllist_goto_page_top();
void filllist_goto_page_bottom();
void filllist_goto_page_middle();
void filllist_move_forward_1_page();
void filllist_move_backward_1_page();
void filllist_move_forward_half_page();
void filllist_move_backward_half_page();
int filllist_goto_order_window();

// Position List
void positionlist_refresh_screen();
void positionlist_display_title();
void positionlist_display_positions();
void positionlist_display_status();
void positionlist_display_focus();
void positionlist_redraw();
void positionlist_reset();
void positionlist_display_position(const char* szInstrumentID);
int on_key_pressed_positionlist(int ch);
int goto_mainboard_window_from_positionlist();
int goto_order_window_from_positionlist();
int goto_orderlist_window_from_positionlist();
int goto_filllist_window_from_positionlist();
int goto_acclist_window_from_positionlist();
void positionlist_move_forward_1_line();
void positionlist_move_backward_1_line();
void positionlist_scroll_forward_1_line();
void positionlist_scroll_backward_1_line();
void positionlist_goto_file_top();
void positionlist_goto_file_bottom();
void positionlist_goto_page_top();
void positionlist_goto_page_bottom();
void positionlist_goto_page_middle();
void positionlist_move_forward_1_page();
void positionlist_move_backward_1_page();
void positionlist_move_forward_half_page();
void positionlist_move_backward_half_page();
int positionlist_goto_order_window();


// Account List
void acclist_refresh_screen();
void acclist_display_title();
void acclist_display_accs();
void acclist_display_status();
void acclist_display_focus();
void acclist_redraw();
void acclist_reset(const char *UserID);
void acclist_display_acc(const char *szBrokerID,const char *szAccID);
int on_key_pressed_acclist(int ch);
int goto_mainboard_window_from_acclist();
int goto_order_window_from_acclist();
int goto_orderlist_window_from_acclist();
int goto_filllist_window_from_acclist();
int goto_positionlist_window_from_acclist();
void acclist_move_forward_1_line();
void acclist_move_backward_1_line();
void acclist_scroll_forward_1_line();
void acclist_scroll_backward_1_line();
void acclist_goto_file_top();
void acclist_goto_file_bottom();
void acclist_goto_page_top();
void acclist_goto_page_bottom();
void acclist_goto_page_middle();
void acclist_move_forward_1_page();
void acclist_move_backward_1_page();
void acclist_move_forward_half_page();
void acclist_move_backward_half_page();
int acclist_goto_order_window();


// Column Settings
void column_settings_refresh_screen();
void column_settings_display_title();
void column_settings_display_status();
void display_column(const char *InstrumentID);
int on_key_pressed_column_settings(int ch);
int column_settings_select_column();
int column_settings_move_forward_1_line();
int column_settings_move_backward_1_line();
int column_settings_move_up_1_line();
int column_settings_move_down_1_line();
int goto_mainboard_window_from_column_settings();


// Instrument
void symbol_refresh_screen();
void symbol_display_title();
void symbol_display_status();
int on_key_pressed_symbol(int ch);
int goto_mainboard_window_from_symbol();


// Corner Window
void corner_refresh_screen();
void corner_display_matches();
void corner_display_focus();
void corner_redraw();
int on_key_pressed_corner(int ch);
void corner_destroy();
void corner_reset();
void corner_display_input();
void corner_choose_item();
void corner_move_left_1_pos();
void corner_move_right_1_pos();
void corner_delete_char_before_current_pos();
void corner_delete_char_at_current_pos();
int input_parse_corner(int *num,int *cmd);
void corner_move_forward_1_line();
void corner_move_backward_1_line();
void corner_research();

// Order Corner Window
void order_corner_refresh_screen();
void order_corner_display_matches();
void order_corner_display_focus();
void order_corner_redraw();
int order_on_key_pressed_corner(int ch);
void order_corner_destroy();
void order_corner_reset();
void order_corner_display_input();
void order_corner_choose_item();
void order_corner_move_left_1_pos();
void order_corner_move_right_1_pos();
void order_corner_delete_char_before_current_pos();
void order_corner_delete_char_at_current_pos();
int order_input_parse_corner(int *num,int *cmd);
void order_corner_move_forward_1_line();
void order_corner_move_backward_1_line();
void order_corner_research();


#endif /*__VI_TRADER_H__*/
