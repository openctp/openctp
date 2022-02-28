#ifndef DATA_DEF_H_
#define DATA_DEF_H_

//33100 单腿行情(内部结构体->随意改！！！)
struct CMarketInfo_UFX
{
	char     quote_type;                  //行情类型(0-境内普通行情1-境外行情)                 
	int      quote_length;                //行情数据长度（从第3字段开始到最后一个字段计算长度）
	int      update_time;                 //时间戳(eg:144510500,14点45分10秒500毫秒)           
	int      quote_index;                 //行情序号                                           
	char     futu_exch_type[5];           //交易类别                                           
	char     commodity_type[7];           //商品代码                                           
	char     contract_code[31];           //合约代码                                           
	double   pre_settlement_price;        //昨日结算价                                         
	double   pre_close_price;             //昨日收盘价                                         
	double   pre_open_interest;           //昨日空盘量                                         
	double   pre_delta;                   //昨日虚实度                                         
	double   futu_open_price;             //开盘价                                             
	double   futu_last_price;             //最新价格                                           
	double   buy_high_price;              //最高买入价                                         
	double   buy_high_amount;             //最高买价买入量                                     
	double   sale_low_price;              //最低卖价价格                                       
	double   sale_low_amount;             //最低卖价卖量                                       
	double   futu_high_price;             //最高价                                             
	double   futu_low_price;              //最低价                                             
	double   uplimited_price;             //涨停板                                             
	double   downlimited_price;           //跌停板                                             
	double   average_price;               //均价                                               
	double   change_direction;            //趋势                                               
	double   business_amount;             //成交量                                             
	double   open_interest;               //总持量                                             
	double   business_balance;            //成交额                                             
	double   futu_close_price;            //今日收盘价                                         
	double   settlement_price;            //结算价                                             
	int      actionday;                   //当前日期(yyyymmdd)                                 
};

//33101 委托回报
struct COrderRspInfo_UFX
{
	char     entrust_no[10];               //委托号                                                
	char     futures_account[13];          //交易编码                                 
	char     futu_exch_type[4];            //交易所类别（F1-郑州F2大连-F3上海-F4中金）
	char     contract_code[31];            //合约代码                                 
	char     entrust_bs;                   //买卖标识(1-买入 2-卖出)                  
	char     entrust_direction;            //开平标识(1-开仓2-平仓4-平今仓，境外为空) 
	char     hedge_type;                   //套保标识(0-投机1-套保2-套利)             
	char     fund_account[19];             //资金账户                                 
	char     futu_report_no[22];           //本地单号                                 
	char     firm_no[22];                  //会员号                                   
	char     operator_no[19];              //操作员号                                 
	int      client_group;                 //客户类别                                 
	double   entrust_amount;               //委托数量                                 
	double   business_total_amount;        //成交总数量                               
	double   cacel_amount;                 //撤单数量                                 
	double   entrust_price;                //委托价格                                 
	char     entrust_status;               //委托状态                                 
	int      branch_no;                    //营业部号                                 
	int      batch_no;                     //委托批号                                 
	char     futu_entrust_type;            //委托类型                                 
	int      amount_per_hand;              //合约乘数                                 
	char     forceclose_reason;            //强平原因                                 
	char     init_date[9];                 //交易日期                                 
	char     curr_time[9];                 //当前时间                                 
	char     confirm_no[21];               //主场单号                                 
	char     entrust_occasion[33];         //委托场景                                 
	double   entrust_price2;               //委托数量(委托输入价格)     
	char     futu_entrust_prop[4];         //期货委托属性
	char     arbitrage_code[31];           //组合委托
	char     entrust_reference[33];        //委托引用
	char     error_message[33];            //错误说明
	char     position_str[33];             //定位串
	//int      request_id;                   //请求编号
	//int      session_id;                   //会话编号
};

//33101 成交回报
struct CRealRspInfo_UFX
{
	char     entrust_no[10];               //委托号                                  
	char     futures_account[13];          //交易编码                                
	char     futu_exch_type[5];            //交易所类别                              
	char     business_no[10];              //成交编号                                
	char     contract_code[31];            //合约代码                                
	char     entrust_bs;                   //买卖标识(1-买入 2-卖出)                 
	char     entrust_direction;            //开平标识(1-开仓2-平仓3-平今仓  境外为空)
	double   business_price;               //成交价格                                
	double   business_amount;              //成交数量                                
	char     hedge_type;                   //套保标识(0-投机1-套保2-套利)            
	char     fund_account[19];             //资金账户                                
	char     futu_report_no[22];           //本地单号                                
	char     firm_no[22];                  //会员号                                  
	char     operator_no[18];              //操作员号                                
	int      client_group;                 //客户类别                                
	double   entrust_amount;               //委托数量                                
	double   business_total_amount;        //成交总数量                              
	double   cacel_amount;                 //撤单数量                                
	double   entrust_price;                //委托价格                                
	char     entrust_status;               //委托状态                                
	int      branch_no;                    //营业部号                                
	int      batch_no;                     //委托批号                                
	char     futu_entrust_type;            //委托类型                                
	int      amount_per_hand;              //合约乘数                                
	char     forceclose_reason;            //强平原因                                
	char     init_date[9];                 //交易日期                                
	char     business_time[9];             //成交时间                                
	char     confirm_no[21];               //主场单号                                
	char     entrust_occasion[33];         //委托场景                                
	double   entrust_price2;               //委托数量(委托输入价格)                   
	char     futu_entrust_prop[4];         //期货委托属性
	char     arbitrage_code[31];           //组合委托
	char     entrust_reference[33];        //委托引用
	char     position_str[33];             //定位串
	//int      request_id;                   //请求编号(暂时)
	//int      session_id;                   //会话编号(暂时)
};

//33102 组合行情(内部结构体->随意改！！！)
struct CArgMarketInfo_UFX
{
	char    arbicontract_id[31];        //套利合约号           
	char    futu_exch_type[5];          //交易类别             
	char    first_code[31];             //第一腿               
	char    second_code[31];            //第二腿               
	char    weave_type;                 //组合类型1-SPD, 2 -IPS
	double  buy_price;                  //最高买入价           
	double  buy_amount;                 //最高买入价买量       
	double  buy_total_amount;           //全部买量             
	double  sale_price;                 //最低卖价价格         
	double  sale_amount;                //最低卖价卖量         
	double  sale_total_amount;          //全部卖量             
	double  futu_high_price;            //最高价               
	double  futu_low_price;             //最低价               
	double  uplimited_price;            //涨停板价格           
	double  downlimited_price;          //跌停板价格  
};

//33105 交易所状态通知
struct CExchangeStatus_UFX
{
	char      futu_exch_type[5];       //交易所类别（F1-郑州F2大连-F3上海-F4中?
	char      exch_status;             //交易所状态（0连接断开,1开盘前, 2集合报
	char      entrade_flag;            //是否可交易（0不可交易，1可交易）      
};

#endif //DATA_DEF_H_

