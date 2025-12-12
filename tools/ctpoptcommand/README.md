# ctpoptcommand工具是一个互式命令行工具，像telnet一样通过命令与ctp股票期权柜台进行交互，支持查询合约、资金、持仓、订单等

# 用法

python ctpoptcommand.py host broker user password appid authcode

例：python ctpoptcommand.py tcp://114.94.59.94:46666 8200 xxxxxx 888888 openctp_ticktrader_1.0.0 V2B1CUV2C9RGF1SE

# 效果

```commandline
> python ctpoptcommand.py tcp://114.94.59.94:46666 8200 xxxxxx 888888 openctp_ticktrader_1.0.0 V2B1CUV2C9RGF1SE
OnFrontConnected
Authenticate succeed.
Login succeed. TradingDay: 20240430
Commands:
1: query instrument
2: query exchange
3: query product
4: query price
5: query account
6: query position
7: query position detail
8: query order
9: query trade
10: query CommissionRate
11: query MarginRate
12: query OrderCommRate
13: query OptionInstrCommRate
14: query OptionInstrTradeCost
15: query investor
16: query tradingcode
17: query settlement
18: confirm settlement
19: order insert
20: order cancel
21: money transfer to ctp
22: money transfer to bank
23: query money transfer detail
24: query bank account
25: query account register
26: query contract bank
q: quit
please enter a command number.
2
OnRspQryExchange:ExchangeID=SSE ExchangeName=上海证券交易所 
OnRspQryExchange:ExchangeID=SZSE ExchangeName=深圳证券交易所
Completed.

please enter a command number.
```