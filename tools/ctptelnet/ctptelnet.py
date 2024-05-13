# -*- coding: utf-8 -*-

"""
author: krenx@openctp.
last modify: 2024/5/2
"""

import sys
import threading
from openctp_ctp import tdapi


# import thosttraderapi as tdapi

class CTPTelnet(tdapi.CThostFtdcTraderSpi):
    def __init__(self, host, broker, user, password, appid, authcode):
        self.broker = broker
        self.user = user
        self.password = password
        self.appid = appid
        self.authcode = authcode

        tdapi.CThostFtdcTraderSpi.__init__(self)
        self.api: tdapi.CThostFtdcTraderApi = tdapi.CThostFtdcTraderApi.CreateFtdcTraderApi()
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
        self.api.ReqQryInstrument(req, 0)

    def QryExchange(self):
        req = tdapi.CThostFtdcQryExchangeField()
        self.api.ReqQryExchange(req, 0)

    def QryProduct(self, ExchangeID, ProductID):
        req = tdapi.CThostFtdcQryProductField()
        req.ExchangeID = ExchangeID
        req.ProductID = ProductID
        self.api.ReqQryProduct(req, 0)

    def QryPrice(self, ExchangeID, InstrumentID):
        req = tdapi.CThostFtdcQryDepthMarketDataField()
        req.ExchangeID = ExchangeID
        req.InstrumentID = InstrumentID
        self.api.ReqQryDepthMarketData(req, 0)

    def QryAccount(self):
        req = tdapi.CThostFtdcQryTradingAccountField()
        req.BrokerID = self.broker
        req.InvestorID = self.user
        self.api.ReqQryTradingAccount(req, 0)

    def QryPosition(self, InstrumentID):
        req = tdapi.CThostFtdcQryInvestorPositionField()
        req.InvestorID = self.user
        req.BrokerID = self.broker
        req.InstrumentID = InstrumentID
        self.api.ReqQryInvestorPosition(req, 0)

    def QryPositionDetail(self, InstrumentID):
        req = tdapi.CThostFtdcQryInvestorPositionDetailField()
        req.InvestorID = self.user
        req.BrokerID = self.broker
        req.InstrumentID = InstrumentID
        self.api.ReqQryInvestorPositionDetail(req, 0)

    def QryOrder(self, InstrumentID):
        req = tdapi.CThostFtdcQryOrderField()
        req.BrokerID = self.broker
        req.InvestorID = self.user
        req.InstrumentID = InstrumentID
        self.api.ReqQryOrder(req, 0)

    def QryTrade(self, InstrumentID):
        req = tdapi.CThostFtdcQryTradeField()
        req.BrokerID = self.broker
        req.InvestorID = self.user
        req.InstrumentID = InstrumentID
        self.api.ReqQryTrade(req, 0)

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
        req.BrokerID = self.broker
        req.UserID = self.user
        req.Password = self.password
        req.UserProductInfo = "ctptelnet"
        self.api.ReqUserLogin(req, 0)

    def OnRspUserLogin(self, pRspUserLogin: 'CThostFtdcRspUserLoginField', pRspInfo: 'CThostFtdcRspInfoField',
                       nRequestID: 'int', bIsLast: 'bool') -> "void":
        if pRspInfo is not None and pRspInfo.ErrorID != 0:
            print(f"Login failed. {pRspInfo.ErrorMsg}")
            exit(-1)
        print(f"Login succeed. TradingDay: {pRspUserLogin.TradingDay}")

        semaphore.release()

    def OnRspQryInstrument(self, pInstrument: tdapi.CThostFtdcInstrumentField, pRspInfo: "CThostFtdcRspInfoField",
                           nRequestID: "int", bIsLast: "bool") -> "void":
        if pRspInfo is not None and pRspInfo.ErrorID != 0:
            print(f"OnRspQryInstrument failed: {pRspInfo.ErrorMsg}")
            return

        if pInstrument is not None:
            print(
                f"OnRspQryInstrument:{pInstrument.InstrumentID}, {pInstrument.InstrumentName}, {pInstrument.ExchangeID} "
                f"ProductID={pInstrument.ProductID} "
                f"VolumeMultiple={pInstrument.VolumeMultiple} "
                f"PositionType={pInstrument.PositionType} "
                f"PriceTick={pInstrument.PriceTick} "
            )
        if bIsLast == True:
            print("Completed.")

    def OnRspQryExchange(self, pExchange: "CThostFtdcExchangeField", pRspInfo: "CThostFtdcRspInfoField",
                         nRequestID: "int", bIsLast: "bool") -> "void":
        if pRspInfo is not None and pRspInfo.ErrorID != 0:
            print(f"OnRspQryExchange failed: {pRspInfo.ErrorMsg}")
            return
        print(f"OnRspQryExchange:{pExchange.ExchangeID},{pExchange.ExchangeName}")
        if bIsLast == True:
            print("Completed.")

    def OnRspQryProduct(self, pProduct: "CThostFtdcProductField", pRspInfo: "CThostFtdcRspInfoField", nRequestID: "int",
                        bIsLast: "bool") -> "void":
        if pRspInfo is not None and pRspInfo.ErrorID != 0:
            print(f"OnRspQryProduct failed: {pRspInfo.ErrorMsg}")
            return
        print(f"OnRspQryProduct:{pProduct.ProductID}, {pProduct.ProductName}, {pProduct.ExchangeID}")
        if bIsLast == True:
            print("Completed.")

    def OnRtnOrder(self, pOrder):
        print(
            f"OnRtnOrder:{pOrder.InstrumentID}, {pOrder.ExchangeID}, {pOrder.Direction}, {pOrder.LimitPrice},  {pOrder.VolumeTotalOriginal}, {pOrder.VolumeTraded}, {pOrder.OrderStatus}, {pOrder.StatusMsg}")

    def OnRtnTrade(self, pTrade):
        print(
            f"OnRtnTrade:{pTrade.InstrumentID}, {pTrade.ExchangeID}, {pTrade.Direction}, {pTrade.Price},  {pTrade.Volume}")

    def OnRspQryInvestorPosition(self, pInvestorPosition: tdapi.CThostFtdcInvestorPositionField,
                                 pRspInfo: "CThostFtdcRspInfoField", nRequestID: "int", bIsLast: "bool") -> "void":
        if pRspInfo is not None and pRspInfo.ErrorID != 0:
            print(f"OnRspQryInvestorPosition failed: {pRspInfo.ErrorMsg}")
            return

        if pInvestorPosition is not None:
            print(f"OnRspInvestorPosition:{pInvestorPosition.InstrumentID}, "
                  f"PosiDirection={pInvestorPosition.PosiDirection}, "
                  f"HedgeFlag={pInvestorPosition.HedgeFlag}, "
                  f"PositionDate={pInvestorPosition.PositionDate}, "
                  f"YdPosition={pInvestorPosition.YdPosition} "
                  f"TodayPosition={pInvestorPosition.TodayPosition} "
                  f"Position={pInvestorPosition.Position} ")

        if bIsLast == True:
            print("Completed.")

    def OnRspQryInvestorPositionDetail(self, pInvestorPositionDetail: tdapi.CThostFtdcInvestorPositionDetailField,
                                       pRspInfo: "CThostFtdcRspInfoField", nRequestID: "int",
                                       bIsLast: "bool") -> "void":
        if pRspInfo is not None and pRspInfo.ErrorID != 0:
            print(f"OnRspQryInvestorPositionDetail failed: {pRspInfo.ErrorMsg}")
            return

        if pInvestorPositionDetail is not None:
            print(f"OnRspInvestorPosition:{pInvestorPositionDetail.InstrumentID}, "
                  f"Direction={pInvestorPositionDetail.Direction} "
                  f"HedgeFlag={pInvestorPositionDetail.HedgeFlag} "
                  f"Volume={pInvestorPositionDetail.Volume} "
                  f"OpenPrice={pInvestorPositionDetail.OpenPrice} "
                  f"Margin={pInvestorPositionDetail.Margin} "
                  f"CloseVolume={pInvestorPositionDetail.CloseVolume} "
                  f"CloseAmount={pInvestorPositionDetail.CloseAmount} "
                  f"OpenDate={pInvestorPositionDetail.OpenDate} "
                  f"TradingDay={pInvestorPositionDetail.TradingDay} "
                  )

        if bIsLast == True:
            print("Completed.")

    def OnRspQryOrder(self, pOrder: tdapi.CThostFtdcOrderField, pRspInfo: "CThostFtdcRspInfoField", nRequestID: "int",
                      bIsLast: "bool") -> "void":
        if pRspInfo is not None and pRspInfo.ErrorID != 0:
            print(f"OnRspQryOrder failed: {pRspInfo.ErrorMsg}")
            return

        if pOrder is not None:
            print(f"OnRspQryOrder: {InstrumentID} "
                  f"ExchangeID={pOrder.ExchangeID} "
                  f"Direction={pOrder.Direction} "
                  f"LimitPrice={pOrder.LimitPrice} "
                  f"VolumeTotalOriginal={pOrder.VolumeTotalOriginal} "
                  f"OrderSysID={pOrder.OrderSysID} "
                  f"OrderStatus={pOrder.OrderStatus} "
                  f"VolumeTotal={pOrder.VolumeTotal} "
                  )

        if bIsLast == True:
            print("Completed.")

    def OnRspQryTrade(self, pTrade: tdapi.CThostFtdcTradeField, pRspInfo: "CThostFtdcRspInfoField", nRequestID: "int",
                      bIsLast: "bool") -> "void":
        if pRspInfo is not None and pRspInfo.ErrorID != 0:
            print(f"OnRspQryTrade failed: {pRspInfo.ErrorMsg}")
            return

        if pTrade is not None:
            print(f"OnRspQryTrade: {InstrumentID} "
                  f'Direction={pTrade.Direction} '
                  f'TradeID={pTrade.TradeID} '
                  f'Price={pTrade.Price} '
                  f'Volume={pTrade.Volume} '
                  f'OffsetFlag={pTrade.OffsetFlag} '
                  f'HedgeFlag={pTrade.HedgeFlag} '
                  )

        if bIsLast == True:
            print("Completed.")

    def OnRspQryTradingAccount(self, pTradingAccount: tdapi.CThostFtdcTradingAccountField,
                               pRspInfo: "CThostFtdcRspInfoField", nRequestID: "int", bIsLast: "bool") -> "void":
        if pRspInfo is not None and pRspInfo.ErrorID != 0:
            print(f"OnRspQryTradingAccount failed: {pRspInfo.ErrorMsg}")
            return

        if pTradingAccount is not None:
            print(f"OnRspQryTradingAccount: "
                  f"PreBalance={pTradingAccount.PreBalance} "
                  f"PreMargin={pTradingAccount.PreMargin} "
                  f"FrozenMargin={pTradingAccount.FrozenMargin} "
                  f"Commission={pTradingAccount.Commission} "
                  f"Available={pTradingAccount.Available} "
                  f"Balance={pTradingAccount.Balance} "
                  )

        if bIsLast == True:
            print("Completed.")

    def OnRspQryDepthMarketData(self, pDepthMarketData: tdapi.CThostFtdcDepthMarketDataField,
                                pRspInfo: "CThostFtdcRspInfoField", nRequestID: "int", bIsLast: "bool") -> "void":
        if pRspInfo is not None and pRspInfo.ErrorID != 0:
            print(f"OnRspQryDepthMarketData failed: {pRspInfo.ErrorMsg}")
            return

        if pDepthMarketData is not None:
            print(f":OnRspQryDepthMarketData: {pDepthMarketData.InstrumentID} "
                  f"LastPrice={pDepthMarketData.LastPrice} "
                  f"PreSettlementPrice={pDepthMarketData.PreSettlementPrice} "
                  f"OpenPrice={pDepthMarketData.OpenPrice} "
                  f"HighestPrice={pDepthMarketData.HighestPrice} "
                  f"LowestPrice={pDepthMarketData.LowestPrice} "
                  f"Volume={pDepthMarketData.Volume} "
                  f"OpenInterest={pDepthMarketData.OpenInterest} "
                  f"UpperLimitPrice={pDepthMarketData.UpperLimitPrice} "
                  f"LowerLimitPrice={pDepthMarketData.LowerLimitPrice} "
                  f"BidPrice1={pDepthMarketData.BidPrice1} "
                  f"BidVolume1={pDepthMarketData.BidVolume1} "
                  f"AskPrice1={pDepthMarketData.AskPrice1} "
                  f"AskVolume1={pDepthMarketData.AskVolume1} "
                  )

        if bIsLast == True:
            print("Completed.")


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
        print("example: {} tcp://180.168.146.187:10130 9999 000001 888888 simnow_client_test 0000000000000000".format(
            sys.argv[0]))
        exit(0)

    semaphore = threading.Semaphore(0)

    host = sys.argv[1]
    broker = sys.argv[2]
    user = sys.argv[3]
    password = sys.argv[4]
    appid = sys.argv[5]
    authcode = sys.argv[6]
    ctptelnet = CTPTelnet(host, broker, user, password, appid, authcode)
    ctptelnet.Run()

    # wait for login ok.
    semaphore.acquire()

    i = 1
    command_query_instrument = str(i)
    i = i + 1
    command_query_exchange = str(i)
    i = i + 1
    command_query_product = str(i)
    i = i + 1
    command_query_price = str(i)
    i = i + 1
    command_query_account = str(i)
    i = i + 1
    command_query_position = str(i)
    i = i + 1
    command_query_position_detail = str(i)
    i = i + 1
    command_query_order = str(i)
    i = i + 1
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
            ExchangeId = input("ExchangeID: (Default:All)")
            ProductId = input("ProductID: (Default:All)")
            ctptelnet.QryProduct(ExchangeId, ProductId)
        elif command == command_query_position:
            InstrumentID = input("InstrumentID:(Default:All)")
            ctptelnet.QryPosition(InstrumentID)
        elif command == command_query_position_detail:
            InstrumentID = input("InstrumentID:(Default:All)")
            ctptelnet.QryPositionDetail(InstrumentID)
        elif command == command_query_order:
            InstrumentID = input("InstrumentID:(Default:All)")
            ctptelnet.QryOrder(InstrumentID)
        elif command == command_query_trade:
            InstrumentID = input("InstrumentID:(Default:All)")
            ctptelnet.QryTrade(InstrumentID)
        elif command == command_query_price:
            ExchangeId = input("ExchangeID: (Default:All)")
            InstrumentID = input("InstrumentID:(Default:All)")
            ctptelnet.QryPrice(ExchangeId, InstrumentID)
        elif command == command_query_account:
            ctptelnet.QryAccount()
        elif command == command_quit:
            break
