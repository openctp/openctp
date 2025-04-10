#include <iostream>
#include <float.h>
#include <math.h>
#include <string>
#include <map>
#include <vector>
#include <functional>
#include <stdlib.h>
#include <string.h>
#include <curses.h>
#ifdef _WIN32
#undef getch
#undef ungetch
#include<conio.h>
#endif
#include <thread>
#include <mutex>
#include <condition_variable>
#include <chrono>

#include "ThostFtdcMdApi.h"

// 控制键定义
#define KEYBOARD_UP 19 // 72
#define KEYBOARD_DOWN 20 // 80
#define KEYBOARD_LEFT 21 //75
#define KEYBOARD_RIGHT 22 // 77
#define KEYBOARD_REFRESH 28 // 12 ^L

#define CONNECTION_STATUS_DISCONNECTED	0
#define CONNECTION_STATUS_CONNECTED		1
#define CONNECTION_STATUS_LOGINOK		2
#define CONNECTION_STATUS_LOGINFAILED	3

std::vector<CThostFtdcDepthMarketDataField> vquotes;
std::map<std::string, size_t> mquotes; // 索引，合约号==>vquotes下标
int ConnectionStatus = CONNECTION_STATUS_DISCONNECTED;
char** instruments = NULL; // 要订阅的合约列表
size_t instrument_count = 0;
std::string user,password;

#define PRECISION 2 // 报价显示2位小数

// Basic
void init_screen();
int on_key_pressed(int ch);
void time_thread();
void work_thread();
void HandleTickTimeout();

// Main Board
void refresh_screen();
void display_title();
void display_status();
void display_quotation(const char* InstrumentID);
int on_key_pressed_mainboard(int ch);
int move_forward_1_line();
int move_backward_1_line();
int scroll_left_1_column();
int scroll_right_1_column();
void focus_quotation(int index);


void post_task(std::function<void()> task);


// CTP
class CCTPMdSpiImp :public CThostFtdcMdSpi
{
public:
	CCTPMdSpiImp(CThostFtdcMdApi* pMdApi) :m_pMdApi(pMdApi) {}

	//已连接
	void OnFrontConnected() { post_task(std::bind(&CCTPMdSpiImp::HandleFrontConnected, this)); }

	//未连接
	void OnFrontDisconnected(int nReason) { post_task(std::bind(&CCTPMdSpiImp::HandleFrontDisconnected, this, nReason)); }

	//登录应答
	void OnRspUserLogin(CThostFtdcRspUserLoginField* pRspUserLogin, CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast) { post_task(std::bind(&CCTPMdSpiImp::HandleRspUserLogin, this, *pRspUserLogin, *pRspInfo, nRequestID, bIsLast)); }

	//行情服务的深度行情通知
	void OnRtnDepthMarketData(CThostFtdcDepthMarketDataField* pDepthMarketData) { post_task(std::bind(&CCTPMdSpiImp::HandleRtnDepthMarketData, this, *pDepthMarketData)); }

	void HandleFrontConnected()
	{
		ConnectionStatus = CONNECTION_STATUS_CONNECTED;
		CThostFtdcReqUserLoginField Req;

		memset(&Req, 0x00, sizeof(Req));
		strncpy(Req.UserID,user.c_str(),sizeof(Req.UserID)-1);
		strncpy(Req.Password,password.c_str(),sizeof(Req.Password)-1);
		m_pMdApi->ReqUserLogin(&Req, 0);
	}

	void HandleFrontDisconnected(int nReason)
	{
		ConnectionStatus = CONNECTION_STATUS_DISCONNECTED;
		refresh_screen();
	}

	void HandleRspUserLogin(CThostFtdcRspUserLoginField& RspUserLogin, CThostFtdcRspInfoField& RspInfo, int nRequestID, bool bIsLast)
	{
		ConnectionStatus = CONNECTION_STATUS_LOGINOK;
		display_status();

		if (instrument_count == 0)
		{
			char* contracts[1];
			contracts[0] = (char*)"*";
			m_pMdApi->SubscribeMarketData(contracts, 1);
		}
		else
		{
			m_pMdApi->SubscribeMarketData(instruments, instrument_count);
		}
	}

	void HandleRtnDepthMarketData(CThostFtdcDepthMarketDataField& DepthMarketData)
	{
		if (mquotes.find(DepthMarketData.InstrumentID)==mquotes.end()) {
			// new
			vquotes.push_back(DepthMarketData);
			mquotes[DepthMarketData.InstrumentID] = vquotes.size() - 1;
		}else {
			// update
			vquotes[mquotes[DepthMarketData.InstrumentID]]=DepthMarketData;
		}
		display_quotation(DepthMarketData.InstrumentID);
	}

	CThostFtdcMdApi* m_pMdApi;
};


class semaphore
{
public:
	semaphore(int value = 1) :count(value) {}

	void wait()
	{
		std::unique_lock<std::mutex> lck(mt);
		if (--count < 0)//资源不足挂起线程
			cv.wait(lck);
	}

	void signal()
	{
		std::unique_lock<std::mutex> lck(mt);
		if (++count <= 0)//有线程挂起，唤醒一个
			cv.notify_one();
	}

private:
	int count;
	std::mutex mt;
	std::condition_variable cv;
};


std::mutex _lock;
semaphore _sem;
std::vector< std::function<void()> > _vTasks;

typedef struct {
	char name[30];
	int width;
} column_item_t;

column_item_t column_items[]={
#define COL_SYMBOL			0		// 合约
	{"合约",		20},
#define COL_SYMBOL_NAME		1		// 名称
	{"名称",		20},
#define COL_CLOSE			2		// 现价
	{"现价",		10},
#define COL_PERCENT			3		// 涨幅
	{"涨幅",		10},
#define COL_VOLUME			4		// 成交量
	{"成交量",		10},
#define COL_ADVANCE			5		// 涨跌
	{"涨跌",		10},
#define COL_OPEN			6		// 开盘
	{"开盘",		10},
#define COL_HIGH			7		// 最高
	{"最高",		10},
#define COL_LOW				8		// 最低
	{"最低",		10},
#define COL_BID_PRICE		9		// 买价
	{"买价",		10},
#define COL_BID_VOLUME		10		// 买量
	{"买量",		10},
#define COL_ASK_PRICE		11		// 卖价
	{"卖价",		10},
#define COL_ASK_VOLUME		12		// 卖量
	{"卖量",		10},
#define COL_PREV_SETTLEMENT	13		// 昨结
	{"昨结",		10},
#define COL_SETTLEMENT		14		// 今结
	{"今结",		10},
#define COL_PREV_CLOSE		15		// 昨收
	{"昨收",		10},
#define COL_OPENINT			16		// 今仓
	{"今仓",		10},
#define COL_PREV_OPENINT	17		// 昨仓
	{"昨仓",		10},
#define COL_HIGH_LIMIT		18		// 涨停
	{"涨停",		10},
#define COL_LOW_LIMIT		19		// 跌停
	{"跌停",		10},
#define COL_TURNOVER		20		// 成交金额
	{"成交金额",	15},
#define COL_EXCHANGE		21		// 交易所
	{"交易所",		10},
#define COL_TRADINGDAY		22		// 交易日
	{"交易日",		10}
};
std::vector<int> vcolumns;	// columns in order
std::map<int,bool> mcolumns;	// column select status

// Mainboard Curses
int curr_line=0,curr_col=1,max_lines,max_cols=7;
int curr_pos=0,curr_col_pos=2;

#if !(defined(WIN32) || defined(_WIN32) || defined(WIN64))
#include <unistd.h>
#else
int opterr = 1, optind = 1, optopt, optreset;
char* optarg;
int getopt(int argc, char* argv[], const char* ostr)
{
	static char* place = (char*)"";		/* option letter processing */
	const char* oli;				/* option letter list index */

	if (optreset || !*place) {		/* update scanning pointer */
		optreset = 0;
		if (optind >= argc || *(place = argv[optind]) != '-') {
			place = (char*)"";
			return (EOF);
		}
		if (place[1] && *++place == '-') {	/* found "--" */
			++optind;
			place = (char*)"";
			return (EOF);
		}
	}					/* option letter okay? */
	if ((optopt = (int)*place++) == (int)':' ||
		!(oli = strchr(ostr, optopt))) {
		/*
		 * if the user didn't specify '-' as an option,
		 * assume it means EOF.
		 */
		if (optopt == (int)'-')
			return (EOF);
		if (!*place)
			++optind;
		return ('?');
	}
	if (*++oli != ':') {			/* don't need argument */
		optarg = NULL;
		if (!*place)
			++optind;
	}
	else {					/* need an argument */
		if (*place)			/* no white space */
			optarg = place;
		else if (argc <= ++optind) {	/* no arg */
			place = (char*)"";
			if (*ostr == ':')
				return (':');
			return ('?');
		}
		else				/* white space */
			optarg = argv[optind];
		place = (char*)"";
		++optind;
	}
	return (optopt);			/* dump back option letter */
}
#endif

void display_usage()
{
	std::cout << "usage:prices [-u user] [-p password] marketaddr instrument1,instrument2 ..." << std::endl;
	std::cout << "example:prices -u 000001 -p 888888 tcp://180.168.146.187:10131 rb2205,IF2201" << std::endl;
	std::cout << "example:prices tcp://180.168.146.187:10131 rb2205,IF2201" << std::endl;
}

int main(int argc, char * argv[])
{
	int opt;
	while ((opt = getopt(argc, argv, "u:p:")) != -1)
	{
		switch (opt) 
		{
		case 'u':
		       user = optarg;
		       break;
		case 'p':
		       password = optarg;
		       break;
		case '?':
			display_usage();
			return -1;
		}
	}

	if (argc - optind != 2)
	{
		display_usage();
		return -1;
	}

	char* servaddr = argv[optind];
	const char* p;
	
	// instruments
	instrument_count =1;
	for (p = argv[optind+1]; *p != '\0'; p++)
		if (*p == ',')
			instrument_count++;
	
	instruments = (char**)malloc(sizeof(char*)* instrument_count);
	char** instrument = instruments;
	char* token=NULL;
	for (int i=0; i<instrument_count; i++) {
		if (token == NULL) {
			token = strtok(argv[optind + 1], ",");
		}
		else {
			token = strtok(NULL, ",");
		}
		*instrument++ = token;
	}

	if (strstr(servaddr,"://") == NULL) {
		std::cout << "invalid address format" << std::endl;
		return -1;
	}
	CThostFtdcMdApi* pMdApi = CThostFtdcMdApi::CreateFtdcMdApi();
	CCTPMdSpiImp Spi(pMdApi);
	pMdApi->RegisterSpi(&Spi);
	pMdApi->RegisterFront(servaddr);
	pMdApi->Init();


	// Init Columns
	mcolumns[COL_SYMBOL]=true;vcolumns.push_back(COL_SYMBOL);
	mcolumns[COL_SYMBOL_NAME]=false;vcolumns.push_back(COL_SYMBOL_NAME);
	mcolumns[COL_CLOSE]=true;vcolumns.push_back(COL_CLOSE);
	mcolumns[COL_PERCENT]=true;vcolumns.push_back(COL_PERCENT);
	mcolumns[COL_ADVANCE]=true;vcolumns.push_back(COL_ADVANCE);
	mcolumns[COL_VOLUME]=true;vcolumns.push_back(COL_VOLUME);
	mcolumns[COL_TURNOVER] = true; vcolumns.push_back(COL_TURNOVER);
	mcolumns[COL_BID_PRICE]=true;vcolumns.push_back(COL_BID_PRICE);
	mcolumns[COL_BID_VOLUME]=true;vcolumns.push_back(COL_BID_VOLUME);
	mcolumns[COL_ASK_PRICE]=true;vcolumns.push_back(COL_ASK_PRICE);
	mcolumns[COL_ASK_VOLUME]=true;vcolumns.push_back(COL_ASK_VOLUME);
	mcolumns[COL_PREV_SETTLEMENT]=true;vcolumns.push_back(COL_PREV_SETTLEMENT);
	mcolumns[COL_OPEN]=true;vcolumns.push_back(COL_OPEN);
	mcolumns[COL_HIGH]=true;vcolumns.push_back(COL_HIGH);
	mcolumns[COL_LOW]=true;vcolumns.push_back(COL_LOW);
	mcolumns[COL_HIGH_LIMIT] = true; vcolumns.push_back(COL_HIGH_LIMIT);
	mcolumns[COL_LOW_LIMIT] = true; vcolumns.push_back(COL_LOW_LIMIT);
	mcolumns[COL_PREV_CLOSE]=true;vcolumns.push_back(COL_PREV_CLOSE);
	mcolumns[COL_OPENINT]=true;vcolumns.push_back(COL_OPENINT);
	mcolumns[COL_PREV_OPENINT]=true;vcolumns.push_back(COL_PREV_OPENINT);
	mcolumns[COL_SETTLEMENT]=true;vcolumns.push_back(COL_SETTLEMENT);
	mcolumns[COL_EXCHANGE] = true; vcolumns.push_back(COL_EXCHANGE);
	mcolumns[COL_TRADINGDAY] = true; vcolumns.push_back(COL_TRADINGDAY);

	std::thread workthread(&work_thread);
	std::thread timerthread(&time_thread);

	// Idle
	int ch;
	while (1) {
#ifdef _WIN32
		ch = _getch();
#else
		ch = getchar();
#endif
		if (ch == 224) {
#ifdef _WIN32
			ch = _getch();
#else
			ch = getchar();
#endif
			switch (ch)
			{
			case 75: // 左
				ch = KEYBOARD_LEFT;
				break;
			case 80: // 下
				ch = KEYBOARD_DOWN;
				break;
			case 72: // 上
				ch = KEYBOARD_UP;
				break;
			case 77: // 右
				ch = KEYBOARD_RIGHT;
				break;
			case 12: // ^L（刷新）
				ch = KEYBOARD_REFRESH;
				break;
			default:
				break;
			}
		}
		else if (ch == 0) {
#ifdef WIN32
			ch = _getch();
#else
			ch = getchar();
#endif
			switch (ch)
			{
			case 59: // F1
			case 60: // F2
			case 61: // F3
			case 62: // F4
			case 63: // F5
			case 64: // F6
			case 65: // F7
			case 66: // F8
			case 67: // F9
			case 68: // F10
				break;
			default:
				break;
			}
		}
		else {
			switch (ch)
			{
			case 12: // ^L（刷新）
				ch = KEYBOARD_REFRESH;
				break;
			default:
				break;
			}
		}
		post_task(std::bind(on_key_pressed, ch));
	}

	return 0;
}

void post_task(std::function<void()> task)
{
	_lock.lock();
	_vTasks.push_back(task);
	_lock.unlock();
	_sem.signal();
}

void HandleTickTimeout()
{
	display_status();
	refresh();
}

int move_forward_1_line()
{
	if(vquotes.size()==0)
		return 0;
	if(curr_line==0){	// first select
		curr_line=1;
		mvchgat(curr_line,0,-1,A_REVERSE,0,NULL);
		return 0;
	}
	if(curr_line==vquotes.size()-curr_pos)	// Already bottom
		return 0;
	if(curr_line!=max_lines){
		mvchgat(curr_line,0,-1,A_NORMAL,0,NULL);
		curr_line++;
		mvchgat(curr_line,0,-1,A_REVERSE,0,NULL);
	}else{
		mvchgat(curr_line,0,-1,A_NORMAL,0,NULL);
		move(1,0);
		setscrreg(1,max_lines);
		scroll(stdscr);
		setscrreg(0,max_lines+1);
		curr_pos++;
		display_quotation(vquotes[curr_pos+max_lines-1].InstrumentID);	// new line
		mvchgat(curr_line,0,-1,A_REVERSE,0,NULL);
	}

	return 0;
}
int scroll_left_1_column()
{
	int i;
	
	if(curr_col_pos==2)
		return 0;
	while(mcolumns[vcolumns[--curr_col_pos]]==false); //	取消所在列的反白显示
	display_title();
	if(vquotes.size()==0)
		return 0;
	for(i=curr_pos;i<vquotes.size() && i<curr_pos+max_lines;i++)
		display_quotation(vquotes[i].InstrumentID);
	
	return 0;
}
int scroll_right_1_column()
{
	int i;
	
	if(curr_col_pos==sizeof(column_items)/sizeof(column_item_t)-1)
		return 0;
	while(mcolumns[vcolumns[++curr_col_pos]]==false); //	取消所在列的反白显示
	display_title();
	if(vquotes.size()==0)
		return 0;
	for(i=curr_pos;i<vquotes.size() && i<curr_pos+max_lines;i++)
		display_quotation(vquotes[i].InstrumentID);

	return 0;
}

int move_backward_1_line()
{
	if(vquotes.size()==0)
		return 0;
	if(curr_line==0){	// first select
		curr_line=1;
		mvchgat(curr_line,0,-1,A_REVERSE,0,NULL);
		return 0;
	}
	if(curr_line==1 && curr_pos==0)	// Already top
		return 0;
	if(curr_line>1){
		mvchgat(curr_line,0,-1,A_NORMAL,0,NULL);
		curr_line--;
		mvchgat(curr_line,0,-1,A_REVERSE,0,NULL);
	}else{
		mvchgat(curr_line,0,-1,A_NORMAL,0,NULL);
		move(1,0);
		setscrreg(1,max_lines);
		scrl(-1);
		setscrreg(0,max_lines+1);
		curr_pos--;
		display_quotation(vquotes[curr_pos].InstrumentID);
		mvchgat(curr_line,0,-1,A_REVERSE,0,NULL);
	}

	return 0;
}

void focus_quotation(int index)
{
	if(vquotes.size()==0)
		return;
	if(curr_line==0){	// first select
		curr_line=1;
		mvchgat(curr_line,0,-1,A_REVERSE,0,NULL);
	}
	if(index>curr_pos+max_lines-1){
		mvchgat(curr_line,0,-1,A_NORMAL,0,NULL);
		curr_line=max_lines;
		mvchgat(curr_line,0,-1,A_REVERSE,0,NULL);
		int i,n;
		
		n=index-(curr_pos+max_lines-1);
		for(i=0;i<n;i++)
			move_forward_1_line();
	}else if(index<curr_pos){
		mvchgat(curr_line,0,-1,A_NORMAL,0,NULL);
		curr_line=1;
		mvchgat(curr_line,0,-1,A_REVERSE,0,NULL);
		int i,n;
		
		n=curr_pos-index;
		for(i=0;i<n;i++)
			move_backward_1_line();
	}else{
		mvchgat(curr_line,0,-1,A_NORMAL,0,NULL);
		curr_line=index-curr_pos+1;
		mvchgat(curr_line,0,-1,A_REVERSE,0,NULL);
	}
}

void display_quotation(const char *InstrumentID)
{
	int i,y,x,pos,maxy,maxx;
	std::vector<int>::iterator iter;

	getmaxyx(stdscr,maxy,maxx);
	i = mquotes[InstrumentID];
	if(i<curr_pos || i>curr_pos+max_lines-1)
		return;
	y=i-curr_pos+1;
	x=0;

	move(y,0);
	clrtoeol();

	double PreClosePrice = vquotes[i].PreClosePrice;
	if (PreClosePrice == DBL_MAX || fabs(PreClosePrice) < 0.000001)
		PreClosePrice = vquotes[i].PreSettlementPrice;

	for(iter=vcolumns.begin(),pos=0;iter!=vcolumns.end();iter++,pos++){
		if(mcolumns[*iter]==false)
			continue;
		if(*iter!=COL_SYMBOL && *iter!=COL_SYMBOL_NAME && pos<curr_col_pos)
			continue;
		if(maxx-x<column_items[*iter].width)
			break;
		switch(*iter){
		case COL_SYMBOL:		//InstrumentID
			mvprintw(y,x,"%-*s",column_items[COL_SYMBOL].width,vquotes[i].InstrumentID);
			x+=column_items[COL_SYMBOL].width;
			break;
		case COL_SYMBOL_NAME:		//InstrumentName
			//mvprintw(y,x,"%-*s",column_items[COL_SYMBOL].width,vquotes[i].InstrumentName);
			x+=column_items[COL_SYMBOL_NAME].width+1;
			break;
		case COL_CLOSE:		//close
			if(vquotes[i].LastPrice==DBL_MAX)
				mvprintw(y,x,"%*c",column_items[COL_CLOSE].width,'-');
			else
			mvprintw(y,x,"%*.*f",column_items[COL_CLOSE].width,PRECISION,vquotes[i].LastPrice);
			x+=column_items[COL_CLOSE].width+1;
			break;
		case COL_PERCENT:		//close
			if (PreClosePrice == DBL_MAX || fabs(PreClosePrice) < 0.000001 || vquotes[i].LastPrice == DBL_MAX || fabs(vquotes[i].LastPrice) < 0.000001)
				mvprintw(y, x, "%*c", column_items[COL_PERCENT].width, '-');
			else
				mvprintw(y, x, "%*.1f%%", column_items[COL_PERCENT].width - 1, (vquotes[i].LastPrice - PreClosePrice) / PreClosePrice * 100.0);
			x+=column_items[COL_PERCENT].width+1;
			break;
		case COL_ADVANCE:		//close
			if (PreClosePrice == DBL_MAX || fabs(PreClosePrice) < 0.000001 || vquotes[i].LastPrice == DBL_MAX || fabs(vquotes[i].LastPrice) < 0.000001)
				mvprintw(y,x,"%*c",column_items[COL_ADVANCE].width,'-');
			else
				mvprintw(y,x,"%*.*f",column_items[COL_ADVANCE].width-1,PRECISION,vquotes[i].LastPrice-vquotes[i].PreClosePrice);
			x+=column_items[COL_ADVANCE].width+1;
			break;
		case COL_VOLUME:		//Volume
			mvprintw(y,x,"%*d",column_items[COL_VOLUME].width,vquotes[i].Volume);
			x+=column_items[COL_VOLUME].width+1;
			break;
		case COL_TURNOVER:		// Turnover
			mvprintw(y, x, "%*.0lf", column_items[COL_TURNOVER].width, vquotes[i].Turnover);
			x += column_items[COL_TURNOVER].width + 1;
			break;
		case COL_BID_PRICE:		//BidPrice1
			if(vquotes[i].BidPrice1==DBL_MAX)
				mvprintw(y,x,"%*c",column_items[COL_BID_PRICE].width,'-');
			else
				mvprintw(y,x,"%*.*f",column_items[COL_BID_PRICE].width,PRECISION,vquotes[i].BidPrice1);
			x+=column_items[COL_BID_PRICE].width+1;
			break;
		case COL_BID_VOLUME:		//BidVolume1
			mvprintw(y,x,"%*d",column_items[COL_BID_VOLUME].width,vquotes[i].BidVolume1);
			x+=column_items[COL_BID_VOLUME].width+1;
			break;
		case COL_ASK_PRICE:		//ask price
			if(vquotes[i].AskPrice1==DBL_MAX)
				mvprintw(y,x,"%*c",column_items[COL_ASK_PRICE].width,'-');
			else
				mvprintw(y,x,"%*.*f",column_items[COL_ASK_PRICE].width,PRECISION,vquotes[i].AskPrice1);
			x+=column_items[COL_ASK_PRICE].width+1;
			break;
		case COL_ASK_VOLUME:		//ask volume
			mvprintw(y,x,"%*d",column_items[COL_ASK_VOLUME].width,vquotes[i].AskVolume1);
			x+=column_items[COL_ASK_VOLUME].width+1;
			break;
		case COL_OPEN:		//OpenPrice
			if(vquotes[i].OpenPrice==DBL_MAX)
				mvprintw(y,x,"%*c",column_items[COL_OPEN].width,'-');
			else
				mvprintw(y,x,"%*.*f",column_items[COL_OPEN].width,PRECISION,vquotes[i].OpenPrice);
			x+=column_items[COL_OPEN].width+1;
			break;
		case COL_PREV_SETTLEMENT:		//PreSettlementPrice
			if(vquotes[i].PreSettlementPrice==DBL_MAX)
				mvprintw(y,x,"%*c",column_items[COL_PREV_SETTLEMENT].width,'-');
			else
				mvprintw(y,x,"%*.*f",column_items[COL_PREV_SETTLEMENT].width,PRECISION,vquotes[i].PreSettlementPrice);
			x+=column_items[COL_PREV_SETTLEMENT].width+1;
			break;
		case COL_HIGH:		//HighestPrice
			if(vquotes[i].HighestPrice==DBL_MAX)
				mvprintw(y,x,"%*c",column_items[COL_HIGH].width,'-');
			else
				mvprintw(y,x,"%*.*f",column_items[COL_HIGH].width,PRECISION,vquotes[i].HighestPrice);
			x+=column_items[COL_HIGH].width+1;
			break;
		case COL_LOW:		//LowestPrice
			if(vquotes[i].LowestPrice==DBL_MAX)
				mvprintw(y,x,"%*c",column_items[COL_LOW].width,'-');
			else
				mvprintw(y,x,"%*.*f",column_items[COL_LOW].width,PRECISION,vquotes[i].LowestPrice);
			x+=column_items[COL_LOW].width+1;
			break;
		case COL_HIGH_LIMIT:		//UpperLimitPrice
			if (vquotes[i].UpperLimitPrice == DBL_MAX)
				mvprintw(y, x, "%*c", column_items[COL_HIGH].width, '-');
			else
				mvprintw(y, x, "%*.*f", column_items[COL_HIGH].width, PRECISION, vquotes[i].UpperLimitPrice);
			x += column_items[COL_HIGH].width + 1;
			break;
		case COL_LOW_LIMIT:		//LowerLimitPrice
			if (vquotes[i].LowerLimitPrice == DBL_MAX)
				mvprintw(y, x, "%*c", column_items[COL_HIGH].width, '-');
			else
				mvprintw(y, x, "%*.*f", column_items[COL_HIGH].width, PRECISION, vquotes[i].LowerLimitPrice);
			x += column_items[COL_HIGH].width + 1;
			break;
		case COL_SETTLEMENT:		//SettlementPrice
			if(vquotes[i].SettlementPrice==DBL_MAX)
				mvprintw(y,x,"%*c",column_items[COL_SETTLEMENT].width,'-');
			else
				mvprintw(y,x,"%*.*f",column_items[COL_SETTLEMENT].width,PRECISION,vquotes[i].SettlementPrice);
			x+=column_items[COL_SETTLEMENT].width+1;
			break;
		case COL_PREV_CLOSE:		//PreClosePrice
			if(vquotes[i].PreClosePrice==DBL_MAX)
				mvprintw(y,x,"%*c",column_items[COL_PREV_CLOSE].width,'-');
			else
				mvprintw(y,x,"%*.*f",column_items[COL_PREV_CLOSE].width,PRECISION,vquotes[i].PreClosePrice);
			x+=column_items[COL_PREV_CLOSE].width+1;
			break;
		case COL_OPENINT:		//OpenInterest
			mvprintw(y,x,"%*d",column_items[COL_OPENINT].width,vquotes[i].OpenInterest);
			x+=column_items[COL_OPENINT].width+1;
			break;
		case COL_PREV_OPENINT:		//PreOpenInterest
			mvprintw(y,x,"%*d",column_items[COL_PREV_OPENINT].width,vquotes[i].PreOpenInterest);
			x+=column_items[COL_PREV_OPENINT].width+1;
			break;
		case COL_EXCHANGE:		//ExchangeID
			mvprintw(y, x, "%-*s", column_items[COL_EXCHANGE].width, vquotes[i].ExchangeID);
			x += column_items[COL_EXCHANGE].width + 1;
			break;
		case COL_TRADINGDAY:		//TradingDay
			mvprintw(y, x, "%-*s", column_items[COL_TRADINGDAY].width, vquotes[i].TradingDay);
			x += column_items[COL_TRADINGDAY].width + 1;
			break;
		default:
			break;
		}
	}

	if(curr_line!=0)
		mvchgat(curr_line,0,-1,A_REVERSE,0,NULL);
}

void display_status()
{
	int y,x;
	char status[100]={0};
	char tradetime[20]={0};

	struct tm *t;
	time_t tt;
	getmaxyx(stdscr,y,x);
	tt=time(NULL);
	t=localtime(&tt);
	sprintf(tradetime,"%02d:%02d:%02d",t->tm_hour,t->tm_min,t->tm_sec);
	switch (ConnectionStatus)
	{
	case CONNECTION_STATUS_DISCONNECTED:
		strcpy(status,"断线");
		break;
	case CONNECTION_STATUS_CONNECTED:
		strcpy(status,"断线");
		break;
	case CONNECTION_STATUS_LOGINOK:
		strcpy(status,"在线");
		break;
	case CONNECTION_STATUS_LOGINFAILED:
		strcpy(status,"断线");
		break;
	default:
		strcpy(status,"");
		break;
	}
	move(y-1,0);
	clrtoeol();
	
	mvprintw(y-1,0,"[%d/%d]",curr_pos+curr_line,vquotes.size());
	mvprintw(y-1,x-35,"krenx@qq.com  %s  %s", status,tradetime);
}

void init_screen()
{
	int i,y,x;

	initscr();
	cbreak();
	nodelay(stdscr,TRUE);
	keypad(stdscr,TRUE);
	noecho();
	curs_set(0);
	scrollok(stdscr,TRUE);
	clear();
	getmaxyx(stdscr,y,x);
	max_lines=y-2;
	display_title();
	for(i=0;i<vquotes.size();i++)
		display_quotation(vquotes[i].InstrumentID);
	display_status();
	if(curr_line!=0)
		mvchgat(curr_line,0,-1,A_REVERSE,0,NULL);
}

void refresh_screen()
{
	int i,y,x;

	endwin();
	initscr();
	cbreak();
	nodelay(stdscr,TRUE);
	keypad(stdscr,TRUE);
	noecho();
	curs_set(0);
	scrollok(stdscr,TRUE);
	clear();
	getmaxyx(stdscr,y,x);
	max_lines=y-2;
	display_title();
	for(i=0;i<vquotes.size();i++)
		display_quotation(vquotes[i].InstrumentID);
	display_status();
	if(curr_line!=0)
		mvchgat(curr_line,0,-1,A_REVERSE,0,NULL);
}


void display_title()
{
	int y,x,pos,maxy,maxx;
	std::vector<int>::iterator iter;

	getmaxyx(stdscr,maxy,maxx);
	y=0;
	x=0;
	move(0,0);
	clrtoeol();
	for(iter=vcolumns.begin(),pos=0;iter!=vcolumns.end();iter++,pos++){
		if(mcolumns[*iter]==false)
			continue;
		if(*iter!=COL_SYMBOL && *iter!=COL_SYMBOL_NAME && pos<curr_col_pos)
			continue;
		if(maxx-x<column_items[*iter].width)
			break;
		switch(*iter){
		case COL_SYMBOL:		//InstrumentID
			mvprintw(y,x,"%-*s",column_items[COL_SYMBOL].width,column_items[COL_SYMBOL].name);
			x+=column_items[COL_SYMBOL].width;
			break;
		case COL_SYMBOL_NAME:		//InstrumentName
			mvprintw(y,x,"%-*s",column_items[COL_SYMBOL_NAME].width,column_items[COL_SYMBOL_NAME].name);
			x+=column_items[COL_SYMBOL_NAME].width+1;
			break;
		case COL_CLOSE:		//close
			mvprintw(y,x,"%*s",column_items[COL_CLOSE].width,column_items[COL_CLOSE].name);
			x+=column_items[COL_CLOSE].width+1;
			break;
		case COL_PERCENT:		//close
			mvprintw(y,x,"%*s",column_items[COL_PERCENT].width,column_items[COL_PERCENT].name);
			x+=column_items[COL_PERCENT].width+1;
			break;
		case COL_ADVANCE:		//close
			mvprintw(y,x,"%*s",column_items[COL_ADVANCE].width,column_items[COL_ADVANCE].name);
			x+=column_items[COL_ADVANCE].width+1;
			break;
		case COL_VOLUME:		//volume
			mvprintw(y,x,"%*s",column_items[COL_VOLUME].width,column_items[COL_VOLUME].name);
			x+=column_items[COL_VOLUME].width+1;
			break;
		case COL_TURNOVER:		//turnover
			mvprintw(y, x, "%*s", column_items[COL_TURNOVER].width, column_items[COL_TURNOVER].name);
			x += column_items[COL_TURNOVER].width + 1;
			break;
		case COL_BID_PRICE:		//bid price
			mvprintw(y,x,"%*s",column_items[COL_BID_PRICE].width,column_items[COL_BID_PRICE].name);
			x+=column_items[COL_BID_PRICE].width+1;
			break;
		case COL_BID_VOLUME:		// bid volume
			mvprintw(y,x,"%*s",column_items[COL_BID_VOLUME].width,column_items[COL_BID_VOLUME].name);
			x+=column_items[COL_BID_VOLUME].width+1;
			break;
		case COL_ASK_PRICE:		// ask price
			mvprintw(y,x,"%*s",column_items[COL_ASK_PRICE].width,column_items[COL_ASK_PRICE].name);
			x+=column_items[COL_ASK_PRICE].width+1;
			break;
		case COL_ASK_VOLUME:		// ask volume
			mvprintw(y,x,"%*s",column_items[COL_ASK_VOLUME].width,column_items[COL_ASK_VOLUME].name);
			x+=column_items[COL_ASK_VOLUME].width+1;
			break;
		case COL_OPEN:		// open
			mvprintw(y,x,"%*s",column_items[COL_OPEN].width,column_items[COL_OPEN].name);
			x+=column_items[COL_OPEN].width+1;
			break;
		case COL_PREV_SETTLEMENT:		// pre_settlement
			mvprintw(y,x,"%*s",column_items[COL_PREV_SETTLEMENT].width,column_items[COL_PREV_SETTLEMENT].name);
			x+=column_items[COL_PREV_SETTLEMENT].width+1;
			break;
		case COL_HIGH:		// high
			mvprintw(y,x,"%*s",column_items[COL_HIGH].width,column_items[COL_HIGH].name);
			x+=column_items[COL_HIGH].width+1;
			break;
		case COL_LOW:		// low
			mvprintw(y,x,"%*s",column_items[COL_LOW].width,column_items[COL_LOW].name);
			x+=column_items[COL_LOW].width+1;
			break;
		case COL_HIGH_LIMIT:		// highlimit
			mvprintw(y, x, "%*s", column_items[COL_HIGH_LIMIT].width, column_items[COL_HIGH_LIMIT].name);
			x += column_items[COL_HIGH_LIMIT].width + 1;
			break;
		case COL_LOW_LIMIT:		// lowlimit
			mvprintw(y, x, "%*s", column_items[COL_LOW_LIMIT].width, column_items[COL_LOW_LIMIT].name);
			x += column_items[COL_LOW_LIMIT].width + 1;
			break;
		case COL_SETTLEMENT:		// settlement
			mvprintw(y,x,"%*s",column_items[COL_SETTLEMENT].width,column_items[COL_SETTLEMENT].name);
			x+=column_items[COL_SETTLEMENT].width+1;
			break;
		case COL_PREV_CLOSE:		// preclose
			mvprintw(y,x,"%*s",column_items[COL_PREV_CLOSE].width,column_items[COL_PREV_CLOSE].name);
			x+=column_items[COL_PREV_CLOSE].width+1;
			break;
		case COL_OPENINT:		// openint
			mvprintw(y,x,"%*s",column_items[COL_OPENINT].width,column_items[COL_OPENINT].name);
			x+=column_items[COL_OPENINT].width+1;
			break;
		case COL_PREV_OPENINT:		// pre_openint
			mvprintw(y,x,"%*s",column_items[COL_PREV_OPENINT].width,column_items[COL_PREV_OPENINT].name);
			x+=column_items[COL_PREV_OPENINT].width+1;
			break;
		case COL_EXCHANGE:		// exchange
			mvprintw(y, x, "%-*s", column_items[COL_EXCHANGE].width, column_items[COL_EXCHANGE].name);
			x += column_items[COL_EXCHANGE].width + 1;
			break;
		case COL_TRADINGDAY:		// tradingday
			mvprintw(y, x, "%-*s", column_items[COL_TRADINGDAY].width, column_items[COL_TRADINGDAY].name);
			x += column_items[COL_TRADINGDAY].width + 1;
			break;
		default:
			break;
		}
	}
}

void work_thread()
{
	// Init screen
	init_screen();
	
	// Run
	while (true) {
		_sem.wait();
		_lock.lock();
		auto task = _vTasks.begin();
		if (task == _vTasks.end()) {
			_lock.unlock();
			continue;
		}
		(*task)();
		_vTasks.erase(task);
		_lock.unlock();
	}

	// End screen
	endwin();
}

void time_thread()
{
	while (true) {
		std::this_thread::sleep_for(std::chrono::seconds(1));
		post_task(std::bind(HandleTickTimeout));
	}
}

int on_key_pressed(int ch)
{
	int r=0;
	r=on_key_pressed_mainboard(ch);

	refresh();

	if(r<0){
		endwin();
		exit(0);
	}
	
	return 0;
}


int on_key_pressed_mainboard(int ch)
{
	if(ch =='q'){
		return -1;
	}

	switch(ch){
	case KEYBOARD_REFRESH:		// ^L
		refresh_screen();
		break;
	case 'k':
	case KEYBOARD_UP:
		move_backward_1_line();
		break;
	case 'j':
	case KEYBOARD_DOWN:
		move_forward_1_line();
		break;
	case 'h':
	case KEYBOARD_LEFT:
		scroll_left_1_column();
		break;
	case 'l':
	case KEYBOARD_RIGHT:
		scroll_right_1_column();
		break;
	default:
		break;
	}
	display_status();

	return 0;
}
