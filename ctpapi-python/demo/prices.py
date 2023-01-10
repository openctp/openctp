# -*- coding: utf-8 -*-

'''
written by krenx on 2023-1-10.
published in openctp@github: https://github.com/krenx1983/openctp/tree/master/ctpapi-python
'''

import thostmduserapi
import sys


class CMdSpiImpl(thostmduserapi.CThostFtdcMdSpi):
    def __init__(self, api):
        thostmduserapi.CThostFtdcMdSpi.__init__(self)
        self.api = api
        
    def OnFrontConnected(self) -> "void":
        print("OnFrontConnected")
        req = thostmduserapi.CThostFtdcReqUserLoginField()
        self.api.ReqUserLogin(req, 0)
        
    def OnRspUserLogin(self, pRspUserLogin: 'CThostFtdcRspUserLoginField', pRspInfo: 'CThostFtdcRspInfoField', nRequestID: 'int', bIsLast: 'bool') -> "void":
        print(f"OnRspUserLogin: ErrorID={pRspInfo.ErrorID}, ErrorMsg={pRspInfo.ErrorMsg}")
        if len(instruments) == 0:
            print("no instruments.")
            return
        self.api.SubscribeMarketData([id.encode('utf-8') for id in instruments], len(instruments))

    def OnRtnDepthMarketData(self, pDepthMarketData: 'CThostFtdcDepthMarketDataField') -> "void":
        print("InstrumentID:", pDepthMarketData.InstrumentID, " LastPrice:", pDepthMarketData.LastPrice,
              " Volume:", pDepthMarketData.Volume, " PreSettlementPrice:", pDepthMarketData.PreSettlementPrice,
              " PreClosePrice:", pDepthMarketData.PreClosePrice, " TradingDay:", pDepthMarketData.TradingDay)

    def OnRspSubMarketData(self, pSpecificInstrument: 'CThostFtdcSpecificInstrumentField', pRspInfo: 'CThostFtdcRspInfoField', nRequestID: 'int', bIsLast: 'bool') -> "void":
        print ("OnRspSubMarketData:ErrorID=", pRspInfo.ErrorID, " ErrorMsg=", pRspInfo.ErrorMsg)


if __name__ == '__main__':
    usage = "prices tcp://180.168.146.187:10131 au2305 rb2305 TA305 i2305 IF2302 ..."
    if len(sys.argv) == 1:
        print(usage)
        sys.exit(1)

    mdfront = sys.argv[1]
    instruments = sys.argv[2:]

    mdapi = thostmduserapi.CThostFtdcMdApi.CreateFtdcMdApi("market")
    print("ApiVersion: ", mdapi.GetApiVersion())
    mdspi = CMdSpiImpl(mdapi)
    mdapi.RegisterFront(mdfront)
    mdapi.RegisterSpi(mdspi)
    mdapi.Init()

    print("press Enter key to exit ...")
    input()
