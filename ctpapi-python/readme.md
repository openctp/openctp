## 简介

- ctpapi-python 是通过 swig 将 c++ 版本 ctpapi 转换为 python 版本，命名和使用方法与 c++ 一致。
- 分为 Linux64/Win64/Mac 三个版本
- Windows 下, Python 3.7/3.8/3.9/3.10/3.11... 等版本编译的 api 又互不兼容，不可串用。
- 3.7 < Supported Python <3.11

## 使用方法

将需要的文件放在同一个目录下

1. Linux
   ```text
   thosttraderapi.py
   libthosttraderapi_se.so
   _thosttraderapi.so
   thostmduserapi.so
   libthostmduserapi_se.so
   _thosttraderapi.so

   prices.py
   ctpprint.py
   ```


2. Windows:
   注意: 使用的python版本需要和库文件`pyd`对应的Python版本一致
   ```text
   thosttraderapi.py
   thosttraderapi_se.dll
   _thosttraderapi.pyd
   thostmduserapi.py
   thostmduserapi_se.dll
   _thosttraderapi.pyd

   prices.py
   ctpprint.py
   ```

3. Mac:
  ```text
  _thostmduserapi.so
  thostmduserapi.py
  prices.py
  ```

## Demo

1. demo/prices.py

   行情API demo, 可登录及订阅行情

   使用方法 `python prices.py <front_addr> <instrumentId1 instrumentId2 ...>`

    ```bash
   PS E:\projects\ctp\demo> python prices.py 180.168.146.187:10131 au2305 rb2305 TA305 i2305 IF2302
   ApiVersion:  v6.6.9_20220914  9:57:19.2466
   press Enter key to exit ...
   OnFrontConnected
   OnRspUserLogin: ErrorID=0, ErrorMsg=CTP:No Error
   OnRspSubMarketData:ErrorID= 0  ErrorMsg= CTP:No Error
   OnRspSubMarketData:ErrorID= 0  ErrorMsg= CTP:No Error
   OnRspSubMarketData:ErrorID= 0  ErrorMsg= CTP:No Error
   OnRspSubMarketData:ErrorID= 0  ErrorMsg= CTP:No Error
   OnRspSubMarketData:ErrorID= 0  ErrorMsg= CTP:No Error
   InstrumentID: rb2305  LastPrice: 4160.0  Volume: 870346  PreSettlementPrice: 4102.0  PreClosePrice: 4093.0  TradingDay: 20230118
   InstrumentID: TA305  LastPrice: 5726.0  Volume: 1572945  PreSettlementPrice: 5542.0  PreClosePrice: 5514.0  TradingDay: 20230118
   InstrumentID: i2305  LastPrice: 839.5  Volume: 600870  PreSettlementPrice: 834.0  PreClosePrice: 832.5  TradingDay: 20230118
   InstrumentID: IF2302  LastPrice: 4148.6  Volume: 16017  PreSettlementPrice: 4156.4  PreClosePrice: 4166.2  TradingDay: 20230118
   InstrumentID: i2305  LastPrice: 839.5  Volume: 600870  PreSettlementPrice: 834.0  PreClosePrice: 832.5  TradingDay: 20230118
   InstrumentID: TA305  LastPrice: 5728.0  Volume: 1572949  PreSettlementPrice: 5542.0  PreClosePrice: 5514.0  TradingDay: 20230118
   InstrumentID: rb2305  LastPrice: 4160.0  Volume: 870349  PreSettlementPrice: 4102.0  PreClosePrice: 4093.0  TradingDay: 20230118
   InstrumentID: IF2302  LastPrice: 4148.6  Volume: 16017  PreSettlementPrice: 4156.4  PreClosePrice: 4166.2  TradingDay: 20230118
   InstrumentID: i2305  LastPrice: 839.0  Volume: 600871  PreSettlementPrice: 834.0  PreClosePrice: 832.5  TradingDay: 20230118
   InstrumentID: rb2305  LastPrice: 4160.0  Volume: 870350  PreSettlementPrice: 4102.0  PreClosePrice: 4093.0  TradingDay: 20230118
   InstrumentID: i2305  LastPrice: 839.0  Volume: 600871  PreSettlementPrice: 834.0  PreClosePrice: 832.5  TradingDay: 20230118
   InstrumentID: IF2302  LastPrice: 4148.6  Volume: 16017  PreSettlementPrice: 4156.4  PreClosePrice: 4166.2  TradingDay: 20230118
   InstrumentID: TA305  LastPrice: 5726.0  Volume: 1572959  PreSettlementPrice: 5542.0  PreClosePrice: 5514.0  TradingDay: 20230118
   InstrumentID: rb2305  LastPrice: 4160.0  Volume: 870353  PreSettlementPrice: 4102.0  PreClosePrice: 4093.0  TradingDay: 20230118
    ``` 
2. demo/ctpprint.py

   交易API demo, 可登录、查询合约等

   使用方法 `python ctpprint.py <front_addr> <investorId> <password>`

   ```
   python ctpprint.py 180.168.146.187:10201 209025 *******
   ApiVersion:  v6.6.9_20220914  9:57:19.2466
   press Enter key to exit ...
   Connect to 180.168.146.187:10201
   Session 716374017 Connected
   OnFrontConnected
   OnRspAuthenticate: ErrorID=0, ErrorMsg=正确
   OnRspUserLogin: ErrorID=0, ErrorMsg=正确, TradingDay=20230120
   OnRspSettlementInfoConfirm: ErrorID=0, ErrorMsg=正确
   OnRspQryInstrument: InstrumentID=sc2503, ExchangeID=INE, PriceTick=0.1, ProductID=sc, ExpireDate=20250228
   OnRspQryInstrument: InstrumentID=RI309, ExchangeID=CZCE, PriceTick=1.0, ProductID=RI, ExpireDate=20230914
   OnRspQryInstrument: InstrumentID=ZC302, ExchangeID=CZCE, PriceTick=0.2, ProductID=ZC, ExpireDate=20230207
   OnRspQryInstrument: InstrumentID=eb2303, ExchangeID=DCE, PriceTick=1.0, ProductID=eb, ExpireDate=20230328
   OnRspQryInstrument: InstrumentID=eg2303, ExchangeID=DCE, PriceTick=1.0, ProductID=eg, ExpireDate=20230328
   OnRspQryInstrument: InstrumentID=jd2303, ExchangeID=DCE, PriceTick=1.0, ProductID=jd, ExpireDate=20230328
   OnRspQryInstrument: InstrumentID=lh2303, ExchangeID=DCE, PriceTick=5.0, ProductID=lh, ExpireDate=20230328
   OnRspQryInstrument: InstrumentID=pg2303, ExchangeID=DCE, PriceTick=1.0, ProductID=pg, ExpireDate=20230328
   OnRspQryInstrument: InstrumentID=a2303, ExchangeID=DCE, PriceTick=1.0, ProductID=a, ExpireDate=20230314
   OnRspQryInstrument: InstrumentID=b2303, ExchangeID=DCE, PriceTick=1.0, ProductID=b, ExpireDate=20230314
   OnRspQryInstrument: InstrumentID=bb2303, ExchangeID=DCE, PriceTick=0.05, ProductID=bb, ExpireDate=20230314
   ```
