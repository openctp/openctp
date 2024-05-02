# -*- coding: utf-8 -*-

"""
author: krenx@openctp.
last modify: 2024/5/2
"""


import json
import sys
import threading
import time
from dataclasses import dataclass
from openctp_ctp import tdapi
#import thosttraderapi as tdapi

@dataclass
class Instrument:
    InstrumentID: str
    InstrumentName: str
    ExchangeID: str
    ProductClass: str
    ProductID: str
    PriceTick: float

@dataclass
class Exchange:
    ExchangeID: str
    ExchangeName: str
@dataclass
class Product:
    ProductID: str
    ProductName: str

class CTPDump(tdapi.CThostFtdcTraderSpi):
    def __init__(self, host,broker,user,password,appid,authcode):
        self.broker = broker
        self.user = user
        self.password = password
        self.appid = appid
        self.authcode = authcode

        self.Exchanges = []
        self.Products = []
        self.Instruments = []

        tdapi.CThostFtdcTraderSpi.__init__(self)
        self.api = tdapi.CThostFtdcTraderApi.CreateFtdcTraderApi()
        self.api.RegisterSpi(self)
        self.api.RegisterFront(host)

    def Run(self):
        self.api.Init()

    def QryInstrument(self):
        req = tdapi.CThostFtdcQryInstrumentField()
        self.api.ReqQryInstrument(req, 0)

    def QryExchange(self):
        req = tdapi.CThostFtdcQryExchangeField()
        self.api.ReqQryExchange(req, 0)

    def QryProduct(self):
        req = tdapi.CThostFtdcQryProductField()
        self.api.ReqQryProduct(req, 0)

    def OnFrontConnected(self) -> "void":
        print("OnFrontConnected")

        req = tdapi.CThostFtdcReqAuthenticateField()
        req.BrokerID = self.broker
        req.UserID = self.user
        req.AppID = self.appid
        req.AuthCode = self.authcode
        req.UserProductInfo = "ctpdump"
        self.api.ReqAuthenticate(req, 0)


    def OnFrontDisconnected(self, nReason: int) -> "void":
        print(f"OnFrontDisconnected.[nReason={nReason}]")

    def OnRspAuthenticate(
            self,
            pRspAuthenticateField: tdapi.CThostFtdcRspAuthenticateField,
            pRspInfo: tdapi.CThostFtdcRspInfoField,
            nRequestID: int,
            bIsLast: bool,
    ):
        """客户端认证响应"""
        if pRspInfo and pRspInfo.ErrorID != 0:
            print("认证失败：{}".format(pRspInfo.ErrorMsg))
            exit(-1)
        print("Authenticate succeed.")

        # 登录
        req = tdapi.CThostFtdcReqUserLoginField()
        req.BrokerID  = self.broker
        req.UserID = self.user
        req.Password = self.password
        req.UserProductInfo = "ctpdump"
        self.api.ReqUserLogin(req, 0)

    def OnRspUserLogin(self, pRspUserLogin: 'CThostFtdcRspUserLoginField', pRspInfo: 'CThostFtdcRspInfoField', nRequestID: 'int', bIsLast: 'bool') -> "void":
        if pRspInfo is not None and pRspInfo.ErrorID != 0:
            print(f"Login failed. {pRspInfo.ErrorMsg}")
            exit(-1)
        print(f"Login succeed. TradingDay: {pRspUserLogin.TradingDay}")

        semaphore.release()

    def OnRspQryExchange(self, pExchange: "CThostFtdcExchangeField", pRspInfo: "CThostFtdcRspInfoField", nRequestID: "int", bIsLast: "bool") -> "void":
        if pRspInfo is not None and pRspInfo.ErrorID != 0:
            print(f"OnRspQryExchange failed: {pRspInfo.ErrorMsg}")
            exit(-1)
        # print(f"OnRspQryExchange:{pExchange.ExchangeID}, {pExchange.ExchangeName}")

        exchange = Exchange(ExchangeID = pExchange.ExchangeID, ExchangeName = pExchange.ExchangeName)
        self.Exchanges.append(exchange)

        if bIsLast == True:
            semaphore.release()

    def OnRspQryProduct(self, pProduct: "CThostFtdcProductField", pRspInfo: "CThostFtdcRspInfoField", nRequestID: "int", bIsLast: "bool") -> "void":
        if pRspInfo is not None and pRspInfo.ErrorID != 0:
            print(f"OnRspQryProduct failed: {pRspInfo.ErrorMsg}")
            exit(-1)
        # print(f"OnRspQryProduct:{pProduct.ProductID}, {pProduct.ProductName}, {pProduct.ExchangeID}")

        product = Product(ProductID = pProduct.ProductID, ProductName = pProduct.ProductName)
        self.Products.append(product)

        if bIsLast == True:
            semaphore.release()

    def OnRspQryInstrument(self, pInstrument: "CThostFtdcInstrumentField", pRspInfo: "CThostFtdcRspInfoField",
                           nRequestID: "int", bIsLast: "bool") -> "void":
        if pRspInfo is not None and pRspInfo.ErrorID != 0:
            print(f"OnRspQryInstrument failed: {pRspInfo.ErrorMsg}")
            exit(-1)
        # print(f"OnRspQryInstrument:{pInstrument.InstrumentID}, {pInstrument.InstrumentName}, ExchangeID:{pInstrument.ExchangeID}")

        instrument = Instrument(InstrumentID = pInstrument.InstrumentID,
                                InstrumentName = pInstrument.InstrumentName,
                                ProductID = pInstrument.ProductID,
                                ProductClass = pInstrument.ProductClass,
                                ExchangeID = pInstrument.ExchangeID,
                                PriceTick = pInstrument.PriceTick)
        self.Instruments.append(instrument)

        if bIsLast == True:
            semaphore.release()


if __name__ == '__main__':
    if len(sys.argv) != 7:
        print("Usage: {} host broker user password appid authcode".format(sys.argv[0]))
        print("example: {} tcp://180.168.146.187:10130 9999 000001 888888 simnow_client_test 0000000000000000".format(sys.argv[0]))
        exit(0)

    semaphore = threading.Semaphore(0)

    host = sys.argv[1]
    broker = sys.argv[2]
    user = sys.argv[3]
    password = sys.argv[4]
    appid = sys.argv[5]
    authcode = sys.argv[6]
    ctpdump = CTPDump(host,broker,user,password,appid,authcode)
    ctpdump.Run()

    # waiting for login ok.
    semaphore.acquire()

    # query exchange
    ctpdump.QryExchange()

    # query product
    time.sleep(1)
    semaphore.acquire()
    ctpdump.QryProduct()

    # query instrument
    time.sleep(1)
    semaphore.acquire()
    ctpdump.QryInstrument()

    # query prices

    # query positions

    # query accounts

    # query orders

    # query trades

    # wait for completed.
    semaphore.acquire()

    print("Exchanges:")
    jsonstr = ',\n'.join(json.dumps(item) for item in [exchange.__dict__ for exchange in ctpdump.Exchanges])
    print("[{}]".format(jsonstr))

    print("Products:")
    jsonstr = ',\n'.join(json.dumps(item) for item in [product.__dict__ for product in ctpdump.Products])
    print("[{}]".format(jsonstr))

    print("Instruments:")
    #print(json.dumps([instrument.__dict__ for instrument in ctpdump.Instruments]))
    jsonstr = ',\n'.join(json.dumps(item) for item in [instrument.__dict__ for instrument in ctpdump.Instruments])
    print("[{}]".format(jsonstr))