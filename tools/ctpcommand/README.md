# ctpcommand工具是一个互式命令行工具，像telnet一样通过命令与ctp柜台进行交互，支持查询合约、资金、持仓、订单等

# 用法

python ctpcommand.py host broker user password appid authcode

例：python ctpcommand.py tcp://180.168.146.187:10130 9999 000001 888888 simnow_client_test 0000000000000000

# 效果

```commandline
> python ctpcommand.py tcp://180.168.146.187:10130 9999 058762 123456 simnow_client_test 0000000000000000
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
q: quit
please enter a command number.
2
OnRspQryExchange:CFFEX,中国金融期货交易所
OnRspQryExchange:SHFE,上海期货交易所
OnRspQryExchange:DCE,大连商品交易所
OnRspQryExchange:CZCE,郑州商品交易所
OnRspQryExchange:INE,上海国际能源交易中心
OnRspQryExchange:GFEX,广州期货交易所
Completed.

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
q: quit
please enter a command number.
```