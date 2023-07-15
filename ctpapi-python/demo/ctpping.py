# author: Jedore https://github.com/Jedore
# date: 2023/07/15
# 描述: ctp通讯链路检测工具；参考c++ ctpping https://github.com/openctp/openctp/tree/master/demo/ctpping
#   使用前安装 openctp-ctp: pip install openctp-ctp==6.6.9
#   适用 Win/Linux/Mac, python 3.7~3.11
# 用法: python ctpping.py address
# 示例: python ctpping.py tcp://180.168.146.187:10131
# 正常输出:
#   version: v6.6.9_MacOS_20220926 15:00:00
#   connected.
#   response time: 27 milliseconds
# 异常输出:
#   version: v6.6.9_MacOS_20220926 15:00:00
#   time out.

import os
import sys
import time
from queue import Queue, Empty

from openctp_ctp import mdapi

Q_EXIT = Queue(maxsize=1)


class CMarketSpi(mdapi.CThostFtdcMdSpi):
    def __init__(self, _api: mdapi.CThostFtdcMdApi):
        super().__init__()

        self._api = _api
        self._start_time = None
        self._end_time = None

    def OnFrontConnected(self):
        print("connected.")

        self._start_time = int(time.time() * 1000)
        self._api.ReqUserLogin(mdapi.CThostFtdcReqUserLoginField(), 0)

    def OnFrontDisconnected(self, nReason: int):
        print("disconnected.")
        Q_EXIT.put_nowait(None)

    def OnRspUserLogin(
        self,
        pRspUserLogin: mdapi.CThostFtdcRspUserLoginField,
        pRspInfo: mdapi.CThostFtdcRspInfoField,
        nRequestID: int,
        bIsLast: bool,
    ):
        self._end_time = int(time.time() * 1000)
        print("response time:", self._end_time - self._start_time, "milliseconds")
        Q_EXIT.put_nowait(None)


if __name__ == "__main__":
    if len(sys.argv) != 2:
        print(sys.argv)
        print("usage: python ctpping.py address")
        print("example: python ctpping.py tcp://180.168.146.187:10100")
        exit(0)

    print("version:", mdapi.CThostFtdcMdApi.GetApiVersion())
    api = mdapi.CThostFtdcMdApi.CreateFtdcMdApi()
    spi = CMarketSpi(api)
    api.RegisterFront(sys.argv[1])
    api.RegisterSpi(spi)
    api.Init()

    try:
        Q_EXIT.get(timeout=5)
    except Empty:
        print("time out.")
    else:
        os.remove("DialogRsp.con")
        os.remove("QueryRsp.con")
        os.remove("TradingDay.con")
    finally:
        api.Release()
