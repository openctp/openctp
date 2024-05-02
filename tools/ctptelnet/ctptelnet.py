# -*- coding: utf-8 -*-

"""
author: krenx@openctp.
last modify: 2024/5/2
"""

import sys
import thosttraderapi as tdapi
import threading

class CTPTelnet(tdapi.CThostFtdcTraderSpi):
    def __init__(self, host,broker,user,password,appid,authcode):
        self.broker = broker
        self.user = user
        self.password = password
        self.appid = appid
        self.authcode = authcode

        tdapi.CThostFtdcTraderSpi.__init__(self)
        self.api = tdapi.CThostFtdcTraderApi.CreateFtdcTraderApi()
        self.api.RegisterSpi(self)
        self.api.RegisterFront(host)
        self.api.SubscribePrivateTopic(tdapi.THOST_TERT_QUICK)
        self.api.SubscribePublicTopic(tdapi.THOST_TERT_QUICK)

    def Run(self):
        self.api.Init()

    def QryInstrument(self, exchangeid, productid, instrumentid):
        req = tdapi.CThostFtdcQryInstrumentField()
        req.ExchangeID = exchangeid
        req.ProductID = productid
        req.InstrumentID = instrumentid
        # if productclass == "futures":
        #    req.ProductClass = tdapi.THOST_FTDC_PC_Futures
        #elif productclass == "options":
        #    req.ProductClass = tdapi.THOST_FTDC_PC_Options
        self.api.ReqQryInstrument(req, 0)

    def QryExchange(self):
        req = tdapi.CThostFtdcQryExchangeField()
        self.api.ReqQryExchange(req, 0)

    def QryProduct(self):
        req = tdapi.CThostFtdcQryProductField()
        self.api.ReqQryProduct(req, 0)

    def QryPrice(self):
        pass

    def QryAccount(self):
        pass

    def QryPosition(self):
        pass

    def QryPositionDetail(self):
        pass

    def QryOrder(self):
        pass

    def QryTrade(self):
        pass

    def OnFrontConnected(self) -> "void":
        print("OnFrontConnected")

        req = tdapi.CThostFtdcReqAuthenticateField()
        req.BrokerID = self.broker
        req.UserID = self.user
        req.AppID = self.appid
        req.AuthCode = self.authcode
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
        req.UserProductInfo = "ctptelnet"
        self.api.ReqUserLogin(req, 0)

    def OnRspUserLogin(self, pRspUserLogin: 'CThostFtdcRspUserLoginField', pRspInfo: 'CThostFtdcRspInfoField', nRequestID: 'int', bIsLast: 'bool') -> "void":
        if pRspInfo is not None and pRspInfo.ErrorID != 0:
            print(f"Login failed. {pRspInfo.ErrorMsg}")
            exit(-1)
        print(f"Login succeed. TradingDay: {pRspUserLogin.TradingDay}")

        semaphore.release()

    def OnRspQryInstrument(self, pInstrument: "CThostFtdcInstrumentField", pRspInfo: "CThostFtdcRspInfoField", nRequestID: "int", bIsLast: "bool") -> "void":
        if pRspInfo is not None and pRspInfo.ErrorID != 0:
            print(f"OnRspQryInstrument failed: {pRspInfo.ErrorMsg}")
            return
        print(f"OnRspQryInstrument:{pInstrument.InstrumentID}, {pInstrument.InstrumentName}, {pInstrument.ExchangeID}")
        if bIsLast == True:
            print("Completed.")

    def OnRspQryExchange(self, pExchange: "CThostFtdcExchangeField", pRspInfo: "CThostFtdcRspInfoField", nRequestID: "int", bIsLast: "bool") -> "void":
        if pRspInfo is not None and pRspInfo.ErrorID != 0:
            print(f"OnRspQryExchange failed: {pRspInfo.ErrorMsg}")
            return
        print(f"OnRspQryExchange:{pExchange.ExchangeID},{pExchange.ExchangeName}")
        if bIsLast == True:
            print("Completed.")

    def OnRspQryProduct(self, pProduct: "CThostFtdcProductField", pRspInfo: "CThostFtdcRspInfoField", nRequestID: "int", bIsLast: "bool") -> "void":
        if pRspInfo is not None and pRspInfo.ErrorID != 0:
            print(f"OnRspQryProduct failed: {pRspInfo.ErrorMsg}")
            return
        print(f"OnRspQryProduct:{pProduct.ProductID}, {pProduct.ProductName}, {pProduct.ExchangeID}")
        if bIsLast == True:
            print("Completed.")

    def OnRtnOrder(self, pOrder):
        print(f"OnRtnOrder:{pOrder.InstrumentID}, {pOrder.ExchangeID}, {pOrder.Direction}, {pOrder.LimitPrice},  {pOrder.VolumeTotalOriginal}, {pOrder.VolumeTraded}, {pOrder.OrderStatus}, {pOrder.StatusMsg}")

    def OnRtnTrade(self, pTrade):
        print(f"OnRtnTrade:{pTrade.InstrumentID}, {pTrade.ExchangeID}, {pTrade.Direction}, {pTrade.Price},  {pTrade.Volume}")

def print_commands():
    print("Commands:")

    print("{}: query instrument".format(command_query_instrument))
    print("{}: query exchange".format(command_query_exchange))
    print("{}: query product".format(command_query_product))
    print("{}: query price".format(command_query_price))
    print("{}: query account".format(command_query_account))
    print("{}: query position".format(command_query_position))
    print("{}: query position detail".format(command_query_position_detail))
    print("{}: query order".format(command_query_order))
    print("{}: query trade".format(command_query_trade))
    print("{}: quit".format(command_quit))
    print("please enter a command number.")

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
    ctptelnet = CTPTelnet(host,broker,user,password,appid,authcode)
    ctptelnet.Run()

    # wait for login ok.
    semaphore.acquire()

    i = 1
    command_query_instrument = str(i)
    i = i +1
    command_query_exchange = str(i)
    i = i +1
    command_query_product = str(i)
    i = i +1
    command_query_price = str(i)
    i = i +1
    command_query_account = str(i)
    i = i +1
    command_query_position = str(i)
    i = i +1
    command_query_position_detail = str(i)
    i = i +1
    command_query_order = str(i)
    i = i +1
    command_query_trade = str(i)
    command_quit = 'q'

    while True:
        print_commands()
        command = input("")
        if command == command_query_instrument:
            exchangeid = input("ExchangeID: (Default:All)")
            productid = input("ProductID: (Default:All)")
            instrumentid = input("InstrumentID: (Default:All)")
            ctptelnet.QryInstrument(exchangeid, productid, instrumentid)
        elif command == command_query_exchange:
            ctptelnet.QryExchange()
        elif command == command_query_product:
            ctptelnet.QryProduct()
        elif command == command_query_position:
            ctptelnet.QryPosition()
        elif command == command_query_position_detail:
            ctptelnet.QryPositionDetail()
        elif command == command_query_order:
            ctptelnet.QryOrder()
        elif command == command_query_trade:
            ctptelnet.QryTrade()
        elif command == command_query_price:
            ctptelnet.QryPrice()
        elif command == command_query_account:
            ctptelnet.QryAccount()
        elif command == command_quit:
            break
