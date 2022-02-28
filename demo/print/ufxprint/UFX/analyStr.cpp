#include "analyStr.h"

bool ParseMarketInfo_UFX(CMarketInfo_UFX *marketinfo, char* qhstr)
{
	memset(marketinfo, 0, sizeof(CMarketInfo_UFX));
	BEGINPPARSE(CMarketInfo_UFX,marketinfo,qhstr,UDP_DELIMITE_STR);
	PARSEVALUE(	quote_type );
	PARSEVALUE(	quote_length );
	PARSEVALUE(	update_time );
	PARSEVALUE(	quote_index );
	PARSEVALUE(	futu_exch_type );
	PARSEVALUE(	commodity_type );
	PARSEVALUE(	contract_code );
	PARSEVALUE(	pre_settlement_price );
	PARSEVALUE(	pre_close_price );
	PARSEVALUE(	pre_open_interest );
	PARSEVALUE(	pre_delta );
	PARSEVALUE(	futu_open_price );
	PARSEVALUE(	futu_last_price );
	PARSEVALUE(	buy_high_price );
	PARSEVALUE(	buy_high_amount );
	PARSEVALUE(	sale_low_price );
	PARSEVALUE(	sale_low_amount );
	PARSEVALUE(	futu_high_price );
	PARSEVALUE(	futu_low_price );
	PARSEVALUE(	uplimited_price );
	PARSEVALUE(	downlimited_price );
	PARSEVALUE(	average_price );
	PARSEVALUE(	change_direction );
	PARSEVALUE(	business_amount );
	PARSEVALUE(	open_interest );
	PARSEVALUE(	business_balance );
	PARSEVALUE(	futu_close_price );
	PARSEVALUE(	settlement_price );
	PARSEVALUE(	actionday );
	ENDPARSE;
	return ISPACKValid;
}

bool ParseOrderRspInfo_UFX(COrderRspInfo_UFX *orderinfo, char* qhstr)
{
	memset(orderinfo, 0, sizeof(COrderRspInfo_UFX));
	BEGINPPARSE(COrderRspInfo_UFX,orderinfo,qhstr,UDP_DELIMITE_STR);
	PARSEVALUE( entrust_no            ); 
	PARSEVALUE( futures_account       ); 
	PARSEVALUE( futu_exch_type        ); 
	PARSEVALUE( contract_code         ); 
	PARSEVALUE( entrust_bs            ); 
	PARSEVALUE( entrust_direction     ); 
	PARSEVALUE( hedge_type            ); 
	PARSEVALUE( fund_account          ); 
	PARSEVALUE( futu_report_no        ); 
	PARSEVALUE( firm_no               ); 
	PARSEVALUE( operator_no           ); 
	PARSEVALUE( client_group          ); 
	PARSEVALUE( entrust_amount        ); 
	PARSEVALUE( business_total_amount ); 
	PARSEVALUE( cacel_amount          ); 
	PARSEVALUE( entrust_price         ); 
	PARSEVALUE( entrust_status        ); 
	PARSEVALUE( branch_no             ); 
	PARSEVALUE( batch_no              ); 
	PARSEVALUE( futu_entrust_type     ); 
	PARSEVALUE( amount_per_hand       ); 
	PARSEVALUE( forceclose_reason     ); 
	PARSEVALUE( init_date             ); 
	PARSEVALUE( curr_time             ); 
	PARSEVALUE( confirm_no            ); 
	PARSEVALUE( entrust_occasion      ); 
	PARSEVALUE( entrust_price2        ); 
	PARSEVALUE( futu_entrust_prop     ); 
	PARSEVALUE( arbitrage_code        ); 
	PARSEVALUE( entrust_reference     ); 
	//PARSEVALUE( request_id            ); 
	ENDPARSE;
	return ISPACKValid;
}

bool ParseRealRspInfo_UFX(CRealRspInfo_UFX *realinfo, char* qhstr)
{
	memset(realinfo, 0, sizeof(CRealRspInfo_UFX));
	BEGINPPARSE(CRealRspInfo_UFX,realinfo,qhstr,UDP_DELIMITE_STR);
	PARSEVALUE( entrust_no            );
	PARSEVALUE( futures_account       );
	PARSEVALUE( futu_exch_type        );
	PARSEVALUE( business_no           );
	PARSEVALUE( contract_code         );
	PARSEVALUE( entrust_bs            );
	PARSEVALUE( entrust_direction     );
	PARSEVALUE( business_price        );
	PARSEVALUE( business_amount       );
	PARSEVALUE( hedge_type            );
	PARSEVALUE( fund_account          );
	PARSEVALUE( futu_report_no        );
	PARSEVALUE( firm_no               );
	PARSEVALUE( operator_no           );
	PARSEVALUE( client_group          );
	PARSEVALUE( entrust_amount        );
	PARSEVALUE( business_total_amount );
	PARSEVALUE( cacel_amount          );
	PARSEVALUE( entrust_price         );
	PARSEVALUE( entrust_status        );
	PARSEVALUE( branch_no             );
	PARSEVALUE( batch_no              );
	PARSEVALUE( futu_entrust_type     );
	PARSEVALUE( amount_per_hand       );
	PARSEVALUE( forceclose_reason     );
	PARSEVALUE( init_date             );
	PARSEVALUE( business_time         );
	PARSEVALUE( confirm_no            );
	PARSEVALUE( entrust_occasion      ); 
	PARSEVALUE( entrust_price2        );
	PARSEVALUE( futu_entrust_prop     ); 
	PARSEVALUE( arbitrage_code        ); 
	PARSEVALUE( entrust_reference     ); 
	//PARSEVALUE( request_id            ); 
	ENDPARSE;
	return ISPACKValid;
}

bool ParseArgMarketInfo_UFX(CArgMarketInfo_UFX *marketinfo, char* qhstr)
{
	memset(marketinfo, 0, sizeof(CArgMarketInfo_UFX));
	BEGINPPARSE(CArgMarketInfo_UFX,marketinfo,qhstr,UDP_DELIMITE_STR);
	PARSEVALUE(	arbicontract_id );
	PARSEVALUE(	futu_exch_type );
	PARSEVALUE(	first_code );
	PARSEVALUE(	second_code );
	PARSEVALUE(	weave_type );
	PARSEVALUE(	buy_price );
	PARSEVALUE(	buy_amount );
	PARSEVALUE(	buy_total_amount );
	PARSEVALUE(	sale_price );
	PARSEVALUE(	sale_amount );
	PARSEVALUE(	sale_total_amount );
	PARSEVALUE(	futu_high_price );
	PARSEVALUE(	futu_low_price );
	PARSEVALUE(	uplimited_price );
	PARSEVALUE(	downlimited_price );
	ENDPARSE;
	return ISPACKValid;
}

bool ParseEchangeStatus_UFX(CExchangeStatus_UFX *exchstatus, char* qhstr)
{
	memset(exchstatus, 0, sizeof(CExchangeStatus_UFX));
	BEGINPPARSE(CExchangeStatus_UFX,exchstatus,qhstr,UDP_DELIMITE_STR);
	PARSEVALUE(	futu_exch_type );
	PARSEVALUE(	exch_status );
	PARSEVALUE(	entrade_flag );
	ENDPARSE;
	return ISPACKValid;
}
