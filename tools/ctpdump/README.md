# 将合约、行情、资金、持仓、订单等数据dump为json格式，以便查看。

# 用法
python ctpdump.py host broker user password appid authcode

例：python ctpdump.py tcp://180.168.146.187:10130 9999 000001 888888 simnow_client_test 0000000000000000

# 输出效果
```json
Instruments:
[{"InstrumentID": "ss2407", "InstrumentName": "ss2407", "ExchangeID": "SHFE", "ProductClass": "1", "ProductID": "ss", "PriceTick": 5.0},
{"InstrumentID": "ss2406", "InstrumentName": "ss2406", "ExchangeID": "SHFE", "ProductClass": "1", "ProductID": "ss", "PriceTick": 5.0},
{"InstrumentID": "ss2409", "InstrumentName": "ss2409", "ExchangeID": "SHFE", "ProductClass": "1", "ProductID": "ss", "PriceTick": 5.0},
{"InstrumentID": "ss2412", "InstrumentName": "ss2412", "ExchangeID": "SHFE", "ProductClass": "1", "ProductID": "ss", "PriceTick": 5.0},
{"InstrumentID": "ss2411", "InstrumentName": "ss2411", "ExchangeID": "SHFE", "ProductClass": "1", "ProductID": "ss", "PriceTick": 5.0},
{"InstrumentID": "ss2504", "InstrumentName": "ss2504", "ExchangeID": "SHFE", "ProductClass": "1", "ProductID": "ss", "PriceTick": 5.0},
{"InstrumentID": "ss2408", "InstrumentName": "ss2408", "ExchangeID": "SHFE", "ProductClass": "1", "ProductID": "ss", "PriceTick": 5.0},
{"InstrumentID": "ss2503", "InstrumentName": "ss2503", "ExchangeID": "SHFE", "ProductClass": "1", "ProductID": "ss", "PriceTick": 5.0},
{"InstrumentID": "ss2502", "InstrumentName": "ss2502", "ExchangeID": "SHFE", "ProductClass": "1", "ProductID": "ss", "PriceTick": 5.0},
{"InstrumentID": "ss2501", "InstrumentName": "ss2501", "ExchangeID": "SHFE", "ProductClass": "1", "ProductID": "ss", "PriceTick": 5.0},
{"InstrumentID": "rb2410", "InstrumentName": "rb2410", "ExchangeID": "SHFE", "ProductClass": "1", "ProductID": "rb", "PriceTick": 1.0},
{"InstrumentID": "rb2502", "InstrumentName": "rb2502", "ExchangeID": "SHFE", "ProductClass": "1", "ProductID": "rb", "PriceTick": 1.0},
{"InstrumentID": "rb2501", "InstrumentName": "rb2501", "ExchangeID": "SHFE", "ProductClass": "1", "ProductID": "rb", "PriceTick": 1.0},
{"InstrumentID": "rb2408", "InstrumentName": "rb2408", "ExchangeID": "SHFE", "ProductClass": "1", "ProductID": "rb", "PriceTick": 1.0},
{"InstrumentID": "rb2411", "InstrumentName": "rb2411", "ExchangeID": "SHFE", "ProductClass": "1", "ProductID": "rb", "PriceTick": 1.0},
{"InstrumentID": "rb2409", "InstrumentName": "rb2409", "ExchangeID": "SHFE", "ProductClass": "1", "ProductID": "rb", "PriceTick": 1.0}]
```