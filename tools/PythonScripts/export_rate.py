"""
    CTP交易费导出工具
        查询期货合约的手续费、保证金，以行情中最新价格计算出交易1手时的手续费、保证金, 并生成 csv 文件.
        具体表头有: "交易所,合约,合约名称,品种,合约乘数,开仓费率,开仓费/手,平仓费率,平仓费/手,平今仓费率,平今仓费/手,最新价,成交量,空盘量,1手开仓手续费,1手平仓手续费,1手平今仓手续费,做多保证金率,做多保证金/手,做空保证金率,做空保证金/手,做多1手保证金,做空1手保证金"

    支持CTPAPI接口的柜台均可导出

    需先安装 openctp-ctp: pip install openctp-ctp

    运行结果如下：
        python .\export_rate.py
        -------------------------- 启动CTP交易费导出工具
        CTPAPI: v6.7.0_20230209  9:52:16.3535
        交易前置: tcp://180.168.146.187:10130
        Connect to 180.168.146.187:10130
        Session -1313406975 Connected
        交易后台版本: v6.7.1_20230713 16:55:42.4819.tkernel
        交易日: 20230901
        投资者: 209025
        -------------------------- 开始导出CTP交易费
        1. 查询合约
                合约数量: 731
        2. 查询行情
                行情数量: 731
        3. 查询交易费率
                手续费数量: 76
                保证金数量: 725
        4. 计算交易费并导出
                有效合约交易费: 725
                无效合约交易费: 6
        -------------------------- 导出CTP交易费完成: 169 秒
"""

import time
from datetime import datetime as dt
from pathlib import Path
from queue import Queue

from openctp_ctp import tdapi

# 使用前一定配置好以下信息
# 用户/密码
user = ""
password = ""
# 交易前置等
td_front = "tcp://180.168.146.187:10130"  # simnow 7x24
broker_id = "9999"
authcode = "0000000000000000"
appid = "simnow_client_test"

Q_INSTRUMENT = Queue()  # type: Queue[dict]
Q_RATE = Queue()  # type: Queue[dict|None]
Q_MARKET = Queue()  # type: Queue[dict]
Q_MARGIN = Queue()  # type: Queue[dict|None]


class CTdSpi(tdapi.CThostFtdcTraderSpi):
    def __init__(self):
        super().__init__()
        self._front = td_front
        self._user = user
        self._password = password
        self._authcode = authcode
        self._appid = appid
        self._broker_id = broker_id

        flow_dir = Path(self._user)
        flow_dir.mkdir(exist_ok=True)
        flow_dir = flow_dir / self._user

        self._api: tdapi.CThostFtdcTraderApi = (
            tdapi.CThostFtdcTraderApi.CreateFtdcTraderApi(str(flow_dir))
        )

        self._api.RegisterFront(self._front)
        self._api.RegisterSpi(self)
        self._api.SubscribePrivateTopic(tdapi.THOST_TERT_QUICK)
        self._api.SubscribePublicTopic(tdapi.THOST_TERT_QUICK)
        self._api.Init()

        self.is_login = None
        self.trading_day = ""
        self.session_id = ""
        self.sys_version = ""
        self.last_instrument = False
        self.last_market_data = False

    def release(self):
        self._api.Release()

    @property
    def api(self):
        return self._api

    def OnFrontConnected(self):
        req = tdapi.CThostFtdcReqAuthenticateField()
        req.BrokerID = broker_id
        req.UserID = user
        req.AppID = appid
        req.AuthCode = authcode
        self._api.ReqAuthenticate(req, 0)

    def OnFrontDisconnected(self, nReason: int):
        print("交易前置连接断开: nReason=", nReason)

    def OnRspAuthenticate(
        self,
        pRspAuthenticateField: tdapi.CThostFtdcRspAuthenticateField,
        pRspInfo: tdapi.CThostFtdcRspInfoField,
        nRequestID: int,
        bIsLast: bool,
    ):
        if pRspInfo and pRspInfo.ErrorID:
            print(f"认证失败: ErrorID={pRspInfo.ErrorID}, ErrorMsg={pRspInfo.ErrorMsg}")
            return

        if pRspInfo is None or pRspInfo.ErrorID == 0:
            # 登录请求
            req = tdapi.CThostFtdcReqUserLoginField()
            req.BrokerID = broker_id
            req.UserID = user
            req.Password = password
            req.UserProductInfo = "openctp"
            self._api.ReqUserLogin(req, 0)

    def OnRspUserLogin(
        self,
        pRspUserLogin: tdapi.CThostFtdcRspUserLoginField,
        pRspInfo: tdapi.CThostFtdcRspInfoField,
        nRequestID: int,
        bIsLast: bool,
    ):
        if pRspInfo and pRspInfo.ErrorID:
            # print(f"登录失败: ErrorID={pRspInfo.ErrorID}, ErrorMsg={pRspInfo.ErrorMsg}")
            self.is_login = False
            return

        self.is_login = True
        self.trading_day = pRspUserLogin.TradingDay
        self.session_id = pRspUserLogin.SessionID
        self.sys_version = pRspUserLogin.SysVersion

    def OnRspQryInstrument(
        self,
        pInstrument: tdapi.CThostFtdcInstrumentField,
        pRspInfo: tdapi.CThostFtdcRspInfoField,
        nRequestID: int,
        bIsLast: bool,
    ):
        if pRspInfo and pRspInfo.ErrorID:
            print(f"查询合约失败: ErrorID={pRspInfo.ErrorID}, ErrorMsg={pRspInfo.ErrorMsg}")
        elif pInstrument:
            if pInstrument.ProductClass == tdapi.THOST_FTDC_PC_Futures:
                Q_INSTRUMENT.put_nowait(
                    {
                        "ExchangeID": pInstrument.ExchangeID,
                        "InstrumentID": pInstrument.InstrumentID,
                        "InstrumentName": pInstrument.InstrumentName,
                        "ProductID": pInstrument.ProductID,
                        "VolumeMultiple": pInstrument.VolumeMultiple,
                    }
                )

        if bIsLast:
            self.last_instrument = True

    def OnRspQryInstrumentCommissionRate(
        self,
        pInstrumentCommissionRate: tdapi.CThostFtdcInstrumentCommissionRateField,
        pRspInfo: tdapi.CThostFtdcRspInfoField,
        nRequestID: int,
        bIsLast: bool,
    ):
        if pRspInfo and pRspInfo.ErrorID:
            print(
                f"\t查询合约手续费失败: ErrorID={pRspInfo.ErrorID}, ErrorMsg={pRspInfo.ErrorMsg}"
            )
            return

        # print(f"查询合约手续费率响应成功: InstrumentID={pInstrumentCommissionRate.InstrumentID}")
        if pInstrumentCommissionRate:
            Q_RATE.put_nowait(
                {
                    "ExchangeID": pInstrumentCommissionRate.ExchangeID,
                    "InstrumentID": pInstrumentCommissionRate.InstrumentID,
                    "OpenRatioByMoney": pInstrumentCommissionRate.OpenRatioByMoney,
                    "OpenRatioByVolume": pInstrumentCommissionRate.OpenRatioByVolume,
                    "CloseRatioByMoney": pInstrumentCommissionRate.CloseRatioByMoney,
                    "CloseRatioByVolume": pInstrumentCommissionRate.CloseRatioByVolume,
                    "CloseTodayRatioByMoney": pInstrumentCommissionRate.CloseTodayRatioByMoney,
                    "CloseTodayRatioByVolume": pInstrumentCommissionRate.CloseTodayRatioByVolume,
                }
            )
        else:
            Q_RATE.put_nowait(None)

    def OnRspQryInstrumentMarginRate(
        self,
        pInstrumentMarginRate: tdapi.CThostFtdcInstrumentMarginRateField,
        pRspInfo: tdapi.CThostFtdcRspInfoField,
        nRequestID: int,
        bIsLast: bool):
        if pRspInfo and pRspInfo.ErrorID:
            print(
                f"\t查询合约保证金失败: ErrorID={pRspInfo.ErrorID}, ErrorMsg={pRspInfo.ErrorMsg}"
            )
            return

        if pInstrumentMarginRate:
            Q_MARGIN.put_nowait({
                "InstrumentID": pInstrumentMarginRate.InstrumentID,
                "ExchangeID": pInstrumentMarginRate.ExchangeID,
                "LongMarginRatioByMoney": pInstrumentMarginRate.LongMarginRatioByMoney,
                "LongMarginRatioByVolume": pInstrumentMarginRate.LongMarginRatioByVolume,
                "ShortMarginRatioByMoney": pInstrumentMarginRate.ShortMarginRatioByMoney,
                "ShortMarginRatioByVolume": pInstrumentMarginRate.ShortMarginRatioByVolume,
            })
        else:
            Q_MARGIN.put_nowait(None)

    def OnRspQryDepthMarketData(
        self,
        pDepthMarketData: tdapi.CThostFtdcDepthMarketDataField,
        pRspInfo: tdapi.CThostFtdcRspInfoField,
        nRequestID: int,
        bIsLast: bool,
    ):
        if pRspInfo and pRspInfo.ErrorID:
            print(
                "请求查询行情响应失败: ErrorID=",
                pRspInfo.ErrorID,
                "ErrorMsg=",
                pRspInfo.ErrorMsg,
            )
        elif pDepthMarketData:
            Q_MARKET.put_nowait(
                {
                    "ExchangeID": pDepthMarketData.ExchangeID,
                    "InstrumentID": pDepthMarketData.InstrumentID,
                    "LastPrice": pDepthMarketData.LastPrice,
                    "Volume": pDepthMarketData.Volume,
                    "OpenInterest": pDepthMarketData.OpenInterest,
                }
            )

        if bIsLast:
            self.last_market_data = True


class Export(object):
    def __init__(self):
        self._spi = CTdSpi()
        self._d_instrument = {}
        self._d_market_data = {}
        self._d_rate = {}
        self._d_margin = {}

    def run(self):
        print("-------------------------- 启动CTP交易费导出工具")
        print("CTPAPI:", self._spi.api.GetApiVersion())
        print("交易前置:", td_front)

        while self._spi.is_login is None:
            time.sleep(1)

        if not self._spi.is_login:
            print("登录失败")
            exit(-1)

        print("交易后台版本:", self._spi.sys_version)
        print("交易日:", self._spi.trading_day)
        print("投资者:", user)

        _t_start = time.time()
        print("-------------------------- 开始导出CTP交易费")
        self.query_instrument()
        self.query_market_data()
        self.query_rate()
        self.save()

        self.release()
        _t = int(time.time() - _t_start)
        print("-------------------------- 导出CTP交易费完成:", _t, "秒")

    def release(self):
        self._spi.release()

    def query_instrument(self):
        print("1. 查询合约")
        req = tdapi.CThostFtdcQryInstrumentField()
        req.BrokerID = broker_id
        req.InvestorID = user
        self._spi.api.ReqQryInstrument(req, 0)

        while not self._spi.last_instrument:
            time.sleep(1)

        print("\t合约数量:", Q_INSTRUMENT.qsize())

        while Q_INSTRUMENT.qsize():
            ins = Q_INSTRUMENT.get()
            self._d_instrument[ins["InstrumentID"]] = ins

    def query_market_data(self):
        print("2. 查询行情")
        req = tdapi.CThostFtdcQryDepthMarketDataField()
        self._spi.api.ReqQryDepthMarketData(req, 0)

        while not self._spi.last_market_data:
            time.sleep(1)

        while Q_MARKET.qsize():
            market = Q_MARKET.get()
            if market["InstrumentID"] in self._d_instrument:
                self._d_market_data[market["InstrumentID"]] = market

        print("\t行情数量:", len(self._d_market_data))

    def query_rate(self):
        print("3. 查询交易费率")
        for inst_id, ins in self._d_instrument.items():
            if ins["ProductID"] not in self._d_rate:
                req = tdapi.CThostFtdcQryInstrumentCommissionRateField()
                req.BrokerID = broker_id
                req.InvestorID = user
                req.InstrumentID = inst_id
                while True:
                    ret = self._spi.api.ReqQryInstrumentCommissionRate(req, 0)
                    if ret == 0:
                        # 由于不同柜台的请求频率限制不同，按需自定义请求间的睡眠时间
                        time.sleep(0.5)
                        break
                    time.sleep(0.1)
                    print("sleep 0.1")

                rate = Q_RATE.get()
                if rate is None:
                    continue
                self._d_rate[rate["InstrumentID"]] = rate

            req = tdapi.CThostFtdcQryInstrumentMarginRateField()
            req.BrokerID = broker_id
            req.InvestorID = user
            req.HedgeFlag = tdapi.THOST_FTDC_HF_Speculation
            req.InstrumentID = inst_id
            while True:
                ret = self._spi.api.ReqQryInstrumentMarginRate(req, 0)
                if ret == 0:
                    # 由于不同柜台的请求频率限制不同，按需自定义请求间的睡眠时间
                    time.sleep(0.5)
                    break
                time.sleep(0.1)
                print("sleep 0.1")

            margin = Q_MARGIN.get()
            self._d_margin[inst_id] = margin

        print("\t手续费数量:", len(self._d_rate))
        print("\t保证金数量:", len(self._d_margin))

    def save(self):
        print("4. 计算交易费并导出")
        header = "交易所,合约,合约名称,品种,合约乘数,开仓费率,开仓费/手,平仓费率,平仓费/手,平今仓费率,平今仓费/手,最新价,成交量,空盘量,1手开仓手续费,1手平仓手续费,1手平今仓手续费,做多保证金率,做多保证金/手,做空保证金率,做空保证金/手,做多1手保证金,做空1手保证金\n"
        valid_lines, invalid_lines = [header], [header]
        for ins_id, ins in self._d_instrument.items():
            multiple = ins["VolumeMultiple"]
            line = [ins["ExchangeID"], ins_id, ins["InstrumentName"], ins["ProductID"], str(multiple)]
            market = self._d_market_data.get(ins_id, {})
            rate = self._d_rate.get(ins_id, {}) or self._d_rate.get(ins["ProductID"], {})
            margin = self._d_margin.get(ins["InstrumentID"])

            if not market or not rate or not margin:
                invalid_lines.append(",".join(line) + "\n")
                continue

            last_price = market.get("LastPrice", 0)
            open_money = rate.get("OpenRatioByMoney")
            open_volume = rate.get("OpenRatioByVolume")
            close_money = rate.get("CloseRatioByMoney")
            close_volume = rate.get("CloseRatioByVolume")
            close_today_money = rate.get("CloseTodayRatioByMoney")
            close_today_volume = rate.get("CloseTodayRatioByVolume")
            long_money = margin.get("LongMarginRatioByMoney")
            long_volume = margin.get("LongMarginRatioByVolume")
            short_money = margin.get("ShortMarginRatioByMoney")
            short_volume = margin.get("ShortMarginRatioByVolume")
            line.extend([
                f'{open_money:f}',
                str(open_volume),
                f'{close_money:f}',
                str(close_volume),
                f'{close_today_money:f}',
                str(close_today_volume),
                str(last_price),
                str(market["Volume"]),
                str(market["OpenInterest"]),
                str(last_price * multiple * open_money + open_volume),
                str(last_price * multiple * close_money + close_volume),
                str(last_price * multiple * close_today_money + close_today_volume),
                str(long_money),
                str(long_volume),
                str(short_money),
                str(short_volume),
                str(last_price * multiple * long_money + long_volume),
                str(last_price * multiple * short_money + short_volume),
            ])

            valid_lines.append(",".join(line) + "\n")

        print("\t有效合约交易费:", len(valid_lines) - 1)
        print("\t无效合约交易费:", len(invalid_lines) - 1)

        today = dt.today().date()
        valid_name = f"{user}-CTP交易费-{today}.csv"
        invalid_name = f"{user}-CTP交易费-{today}-无效.csv"

        with open(valid_name, mode="w", encoding="utf8") as fp:
            fp.writelines(valid_lines)
        with open(invalid_name, mode="w", encoding="utf8") as fp:
            fp.writelines(invalid_lines)


if __name__ == "__main__":
    cli = Export()
    cli.run()
