"""
订阅行情 demo
注意选择有效合约, 没有行情可能是过期合约或者不再交易时间内导致
环境信息: https://www.simnow.com.cn/product.action

written by krenx on 2023-1-10.
published in openctp@github: https://github.com/krenx1983/openctp/tree/master/ctpapi-python
"""

import sys

import thostmduserapi as api


class CMdSpiImpl(api.CThostFtdcMdSpi):
    def __init__(self, md_api):
        super().__init__()
        self.md_api = md_api

    def OnFrontConnected(self):
        """ 前置连接成功 """
        print("OnFrontConnected")
        req = api.CThostFtdcReqUserLoginField()
        self.md_api.ReqUserLogin(req, 0)

    def OnRspUserLogin(self, pRspUserLogin: api.CThostFtdcRspUserLoginField,
                       pRspInfo: api.CThostFtdcRspInfoField, nRequestID: int, bIsLast: bool):
        """ 登录应答 """
        print(f"OnRspUserLogin: ErrorID={pRspInfo.ErrorID}, ErrorMsg={pRspInfo.ErrorMsg}")
        if len(instruments) == 0:
            print("no instruments.")
            return
        self.md_api.SubscribeMarketData([i.encode('utf-8') for i in instruments], len(instruments))

    def OnRtnDepthMarketData(self, pDepthMarketData: api.CThostFtdcDepthMarketDataField):
        """ 深度行情 """
        print("InstrumentID:", pDepthMarketData.InstrumentID, " LastPrice:", pDepthMarketData.LastPrice,
              " Volume:", pDepthMarketData.Volume, " PreSettlementPrice:", pDepthMarketData.PreSettlementPrice,
              " PreClosePrice:", pDepthMarketData.PreClosePrice, " TradingDay:", pDepthMarketData.TradingDay)

    def OnRspSubMarketData(self, pSpecificInstrument: api.CThostFtdcSpecificInstrumentField,
                           pRspInfo: api.CThostFtdcRspInfoField, nRequestID: int, bIsLast: bool):
        """ 订阅行情应答 """
        print("OnRspSubMarketData:ErrorID=", pRspInfo.ErrorID, " ErrorMsg=", pRspInfo.ErrorMsg)


if __name__ == '__main__':
    if len(sys.argv) == 1:
        print("Usage:\n\tpython prices.py <front_addr> <instrumentId> <instrumentId>...")
        sys.exit(1)

    md_front = 'tcp://' + sys.argv[1]
    instruments = sys.argv[2:]

    md_api = api.CThostFtdcMdApi.CreateFtdcMdApi("market")
    print("ApiVersion: ", md_api.GetApiVersion())
    md_spi = CMdSpiImpl(md_api)
    md_api.RegisterFront(md_front)
    md_api.RegisterSpi(md_spi)
    md_api.Init()

    print("press Enter key to exit ...")
    input()
