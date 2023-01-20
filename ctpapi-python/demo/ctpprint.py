"""
written by krenx on 2023-1-10.
published in openctp@github: https://github.com/krenx1983/openctp/tree/master/ctpapi-python
"""

import sys

import thosttraderapi as api


class CTdSpiImpl(api.CThostFtdcTraderSpi):
    def __init__(self, tdapi):
        super().__init__()
        self.tdapi = tdapi

    def OnFrontConnected(self):
        """ 前置连接成功 """
        print("OnFrontConnected")
        req = api.CThostFtdcReqAuthenticateField()
        req.BrokerID = brokerid
        req.UserID = user
        req.AppID = appid
        req.AuthCode = authcode
        self.tdapi.ReqAuthenticate(req, 0)

    def OnFrontDisconnected(self, nReason: int):
        """ 前置断开 """
        print("OnFrontDisconnected: nReason=", nReason)

    def OnRspAuthenticate(self, pRspAuthenticateField: api.CThostFtdcRspAuthenticateField,
                          pRspInfo: api.CThostFtdcRspInfoField, nRequestID: int, bIsLast: bool):
        """ 客户端认证应答 """
        if pRspInfo is not None:
            print(f"OnRspAuthenticate: ErrorID={pRspInfo.ErrorID}, ErrorMsg={pRspInfo.ErrorMsg}")

        if pRspInfo is None or pRspInfo.ErrorID == 0:
            req = api.CThostFtdcReqUserLoginField()
            req.BrokerID = brokerid
            req.UserID = user
            req.Password = password
            req.UserProductInfo = "openctp"
            self.tdapi.ReqUserLogin(req, 0)

    def OnRspUserLogin(self, pRspUserLogin: api.CThostFtdcRspUserLoginField,
                       pRspInfo: api.CThostFtdcRspInfoField, nRequestID: int, bIsLast: bool):
        """ 登录应答 """
        print(f"OnRspUserLogin: ErrorID={pRspInfo.ErrorID}, ErrorMsg={pRspInfo.ErrorMsg}, "
              f"TradingDay={pRspUserLogin.TradingDay}")

        req = api.CThostFtdcSettlementInfoConfirmField()
        req.BrokerID = brokerid
        req.InvestorID = user
        self.tdapi.ReqSettlementInfoConfirm(req, 0)

    def OnRspSettlementInfoConfirm(self, pSettlementInfoConfirm: api.CThostFtdcSettlementInfoConfirmField,
                                   pRspInfo: api.CThostFtdcRspInfoField, nRequestID: int, bIsLast: bool):
        """ 确认投资者结算结果应答 """
        if pRspInfo is not None:
            print(f"OnRspSettlementInfoConfirm: ErrorID={pRspInfo.ErrorID}, ErrorMsg={pRspInfo.ErrorMsg}")

        req = api.CThostFtdcQryInstrumentField()
        req.BrokerID = brokerid
        req.InvestorID = user
        self.tdapi.ReqQryInstrument(req, 0)

    def OnRspQryInstrument(self, pInstrument: api.CThostFtdcInstrumentField,
                           pRspInfo: api.CThostFtdcRspInfoField, nRequestID: int, bIsLast: bool):
        """ 查询合约应答 """
        if pRspInfo is not None:
            print(f"OnRspQryInstrument: ErrorID={pRspInfo.ErrorID}, ErrorMsg={pRspInfo.ErrorMsg}")

        print(f"OnRspQryInstrument: InstrumentID={pInstrument.InstrumentID}, "
              f"ExchangeID={pInstrument.ExchangeID}, PriceTick={pInstrument.PriceTick}, "
              f"ProductID={pInstrument.ProductID}, ExpireDate={pInstrument.ExpireDate}")

    def OnRtnOrder(self, pOrder: api.CThostFtdcOrderField):
        """ 报单回报 """
        print(f"OnRtnOrder: InstrumentID={pOrder.InstrumentID}, ExchangeID={pOrder.ExchangeID}, "
              f"VolumeTotalOriginal={pOrder.VolumeTotalOriginal}, VolumeTraded={pOrder.VolumeTraded}, "
              f"LimitPrice={pOrder.LimitPrice}, OrderStatus={pOrder.OrderStatus}, OrderSysID={pOrder.OrderSysID}, "
              f"FrontID={pOrder.FrontID}, SessionID={pOrder.SessionID}, OrderRef={pOrder.OrderRef}")

    def OnRtnTrade(self, pTrade: api.CThostFtdcTradeField):
        """ 成交回报 """
        print(f"OnRtnTrade: InstrumentID={pTrade.InstrumentID}, ExchangeID={pTrade.ExchangeID}, "
              f"Volume={pTrade.Volume}, Price={pTrade.Price}, OrderSysID={pTrade.OrderSysID}, "
              f"OrderRef={pTrade.OrderRef}")

    def OnRspOrderInsert(self, pInputOrder: api.CThostFtdcInputOrderField,
                         pRspInfo: api.CThostFtdcRspInfoField, nRequestID: int, bIsLast: bool):
        """ 报单响应 """
        if pRspInfo is not None:
            print(f"OnRspOrderInsert: ErrorID={pRspInfo.ErrorID}, ErrorMsg={pRspInfo.ErrorMsg}")


if __name__ == '__main__':
    if len(sys.argv) != 4:
        print("Usage:\n\tpython ctpprint.py <front_addr> <investorId> <password>")
        sys.exit(1)

    tdfront = 'tcp://' + sys.argv[1]
    user = sys.argv[2]
    password = sys.argv[3]

    brokerid = '9999'
    authcode = '0000000000000000'
    appid = 'simnow_client_test'

    tdapi = api.CThostFtdcTraderApi.CreateFtdcTraderApi(user)
    print("ApiVersion: ", tdapi.GetApiVersion())
    tdspi = CTdSpiImpl(tdapi)
    tdapi.RegisterSpi(tdspi)
    tdapi.SubscribePrivateTopic(api.THOST_TERT_QUICK)
    tdapi.SubscribePublicTopic(api.THOST_TERT_QUICK)
    tdapi.RegisterFront(tdfront)
    tdapi.Init()

    print("press Enter key to exit ...")
    input()
