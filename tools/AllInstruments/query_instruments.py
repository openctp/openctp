import csv
import time
import threading
from sqlalchemy import Column, String, Float, create_engine
from sqlalchemy.ext.declarative import declarative_base
from sqlalchemy.orm import Session
from openctp_ctp_667 import tdapi

Base = declarative_base()

class DBConfig(object):
    
    def __init__(self, user, password, url, database) -> None:
        self.user = user
        self.password = password
        self.url = url
        self.database = database
    
    @property
    def connection_str(self):
        return f'mysql+mysqlconnector://{self.user}:{self.password}@{self.url}/{self.database}?charset=gbk'


class CTPConfig(object):
        
    def __init__(self, front_addr, broker_id, auth_code, app_id, user_id, password) -> None:
        self.front_addr = front_addr
        self.broker_id = broker_id
        self.auth_code = auth_code
        self.app_id = app_id
        self.user_id = user_id
        self.password = password


class Instrument(Base):
    __tablename__ = 'instruments'

    InstrumentID = Column(String(30), primary_key=True)
    InstrumentName = Column(String(50))
    PriceTick = Column(Float)
    ExpireDate = Column(String(8))
    OpenDate = Column(String(8))
    ProductClass = Column(String(1))
    ProductID = Column(String(30))
    LongMarginRatio = Column(Float)
    ShortMarginRatio = Column(Float)
    OpenRatioByMoney = Column(Float)
    OpenRatioByVolume = Column(Float)
    CloseRatioByMoney = Column(Float)
    CloseRatioByVolume = Column(Float)
    CloseTodayRatioByMoney = Column(Float)
    CloseTodayRatioByVolume = Column(Float)
    ExchangeID = Column(String(30), primary_key=True)

    def __repr__(self):
        return "<Instrument(InstrumentID='{}', InstrumentName='{}', PriceTick='{}', ExpireDate='{}', OpenDate='{}', ProductClass='{}', ProductID='{}', LongMarginRatio='{}', ShortMarginRatio='{}', OpenRatioByMoney='{}', OpenRatioByVolume='{}', CloseRatioByMoney='{}', CloseRatioByVolume='{}', CloseTodayRatioByMoney='{}', CloseTodayRatioByVolume='{}', ExchangeID='{}')>".format(
            self.InstrumentID, self.InstrumentName, self.PriceTick, self.ExpireDate, self.OpenDate, self.ProductClass, self.ProductID, self.LongMarginRatio, self.ShortMarginRatio, self.OpenRatioByMoney, self.OpenRatioByVolume, self.CloseRatioByMoney, self.CloseRatioByVolume, self.CloseTodayRatioByMoney, self.CloseTodayRatioByVolume, self.ExchangeID)


class DB(object):

    def __init__(self, dbconfig: DBConfig) -> None:
        self.connection_str = dbconfig.connection_str
        self.engine = create_engine(self.connection_str, echo=False, pool_size=10)
    
    def save_instrument(self, data: Instrument):
        with Session(self.engine) as session:
            # data.InstrumentName = '泽璟制药'
            existed_instrument = session.query(Instrument).filter(Instrument.InstrumentID == data.InstrumentID, Instrument.ExchangeID == data.ExchangeID).one_or_none()
            if not existed_instrument:
                print(f"{data.InstrumentID}-{data.ExchangeID} not existed, insert it")
                session.merge(data)
                # session.add(data)
                session.commit()
    
    def update_instrument(self, update: Instrument):
        with Session(self.engine) as session:
            session.query(Instrument).filter(Instrument.ProductID == update.ProductID).update({
                Instrument.OpenRatioByMoney.name: update.OpenRatioByMoney,
                Instrument.OpenRatioByVolume.name: update.OpenRatioByVolume,
                Instrument.CloseRatioByMoney.name: update.CloseRatioByMoney,
                Instrument.CloseRatioByVolume.name: update.CloseRatioByVolume,
                Instrument.CloseTodayRatioByMoney.name: update.CloseTodayRatioByMoney,
                Instrument.CloseTodayRatioByVolume.name: update.CloseTodayRatioByVolume
            })
            session.commit()


class QueryAllInstruments(tdapi.CThostFtdcTraderSpi):

    def __init__(self, dbconfig: DBConfig, ctpconfig: CTPConfig) -> None:
        super().__init__()
        self.qry_instrument_finished = threading.Event()
        self.qry_commission_finished = threading.Event()
        self.qry_option_commission_finished = threading.Event()
        self.instruments = {}
        self.options = {}
        self.instrumentid_productid = {}
        self.options_productid = {}
        self.connected = None
        self.front_addr = ctpconfig.front_addr
        self.broker_id = ctpconfig.broker_id
        self.auth_code = ctpconfig.auth_code
        self.app_id = ctpconfig.app_id
        self.user_id = ctpconfig.user_id
        self.password = ctpconfig.password
        self.failed_instruments = []
        self.db = DB(dbconfig)

    def connect(self) -> None:
        print("connecting to td client...")
        self.create_api()
        self.connected = threading.Event()
        self.api.Init()
        self.connected.wait()
        print("connect finished")
        self.main()
    
    def create_api(self) -> None:
        self.api: tdapi.CThostFtdcTraderApi = tdapi.CThostFtdcTraderApi.CreateFtdcTraderApi(self.user_id)
        self.api.RegisterSpi(self)
        self.api.SubscribePrivateTopic(tdapi.THOST_TERT_QUICK)
        self.api.SubscribePublicTopic(tdapi.THOST_TERT_QUICK)
        self.api.RegisterFront(self.front_addr)

    def OnFrontConnected(self):
        """called when connect success"""
        print("Td client connected")
        self.authenticate()

    def OnFrontDisconnected(self, nReason):
        """called when connection broken"""
        print(f"Td client disconnected, error_code={nReason}")

    def authenticate(self):
        req = tdapi.CThostFtdcReqAuthenticateField()
        req.BrokerID = self.broker_id
        req.UserID = self.user_id
        req.AppID = self.app_id
        req.AuthCode = self.auth_code
        self.api.ReqAuthenticate(req, 0)

    def OnRspAuthenticate(self, pRspAuthenticateField: tdapi.CThostFtdcRspAuthenticateField,
                          pRspInfo: tdapi.CThostFtdcRspInfoField, nRequestID: int, bIsLast: bool):
        """called when authenticate success"""
        if pRspInfo is not None:
            print(f"authenticate rsp info, ErrorID: {pRspInfo.ErrorID}, ErrorMsg: {pRspInfo.ErrorMsg}")

        if pRspInfo is None or pRspInfo.ErrorID == 0:
            print("authenticate success, start to login")
            self.login()
        else:
            print("authenticate failed, please try again")
            exit(1)

    def login(self):
        req = tdapi.CThostFtdcReqUserLoginField()
        req.BrokerID = self.broker_id
        req.UserID = self.user_id
        req.Password = self.password
        req.UserProductInfo = "openctp"
        self.api.ReqUserLogin(req, 0)

    def OnRspUserLogin(self, pRspUserLogin: tdapi.CThostFtdcRspUserLoginField, pRspInfo: tdapi.CThostFtdcRspInfoField, nRequestID: int, bIsLast: bool):
        """called when login responds"""
        if pRspInfo is not None:
            print(f"login rsp info, ErrorID: {pRspInfo.ErrorID}, ErrorMsg: {pRspInfo.ErrorMsg}")

        if pRspInfo is None or pRspInfo.ErrorID == 0:
            print("login success, start to confirm settlement info")
            # self.settlementConfirm()
            self.connected.set()
        else:
            print("login failed, please try again")
            exit(1)

    def settlementConfirm(self):
        req = tdapi.CThostFtdcSettlementInfoConfirmField()
        req.BrokerID = self.broker_id
        req.InvestorID = self.user_id
        self.api.ReqSettlementInfoConfirm(req, 0)
    
    def OnRspQrySettlementInfoConfirm(self, pSettlementInfoConfirm: tdapi.CThostFtdcSettlementInfoConfirmField, pRspInfo: tdapi.CThostFtdcRspInfoField, nRequestID: int, bIsLast: bool):
        print("confirm settlement info success")
        if pRspInfo is not None:
            print(f"settlemnt confirm rsp info, ErrorID: {pRspInfo.ErrorID}, ErrorMsg: {pRspInfo.ErrorMsg}")
    
    def main(self):
        self.qry_instrument()
        self.qry_commission_rate()
        self.qry_option_instrument_commision_rate()
    
    def qry_instrument(self):
        request = tdapi.CThostFtdcQryInstrumentField()
        # request.InstrumentID = "688266"
        # request.InstrumentID = "UR"
        # request.InstrumentID = "RI401"
        n = self.api.ReqQryInstrument(request, 1)
        while n != 0:
            time.sleep(1)
            n = self.api.ReqQryInstrument(request, 1)
        self.qry_instrument_finished.wait()
   
    def OnRspQryInstrument(self, pInstrument: tdapi.CThostFtdcInstrumentField, pRspInfo: tdapi.CThostFtdcRspInfoField, nRequestID: int, bIsLast: bool):
        if pInstrument:
            instrument = Instrument()
            instrument.InstrumentID = pInstrument.InstrumentID
            instrument.InstrumentName = pInstrument.InstrumentName
            instrument.PriceTick = pInstrument.PriceTick
            instrument.ExpireDate = pInstrument.ExpireDate
            instrument.OpenDate = pInstrument.OpenDate
            instrument.ProductClass = pInstrument.ProductClass
            instrument.ProductID = pInstrument.ProductID
            instrument.LongMarginRatio = pInstrument.LongMarginRatio if pInstrument.LongMarginRatio < 1e8 else 0.0
            instrument.ShortMarginRatio = pInstrument.ShortMarginRatio if pInstrument.ShortMarginRatio < 1e8 else 0.0
            instrument.ExchangeID = pInstrument.ExchangeID
            try:
                print(f"save instrument {instrument.InstrumentID}-{instrument.ExchangeID}")
                self.db.save_instrument(instrument)
                if instrument.ProductClass == '1':
                    self.instruments[instrument.ProductID] = instrument.InstrumentID
                elif instrument.ProductClass == '2':
                    self.options[instrument.ProductID] = instrument.InstrumentID
                else:
                    pass
                print(f"save finished")
            except Exception as e:
                print(e)
                self.failed_instruments.append((instrument, e))

        if bIsLast:
            print('qry instrument finished')
            self.qry_instrument_finished.set()
    
    def qry_commission_rate(self):
        for product_id, instrument_id in self.instruments.items():
            self.instrumentid_productid[instrument_id] = product_id

        i = 0
        product_ids = list(self.instruments.keys())
        while i < len(product_ids):
            product_id = product_ids[i]
            time.sleep(1)
            request = tdapi.CThostFtdcQryInstrumentCommissionRateField()
            request.InstrumentID = self.instruments[product_id]
            print(f'qry commission rate {product_id} {request.InstrumentID}')
            request.BrokerID = self.broker_id
            request.InvestorID = self.user_id
            n = self.api.ReqQryInstrumentCommissionRate(request, i)
            if n == 0:
                i += 1
                self.qry_commission_finished.wait()
                self.qry_commission_finished.clear()
    
    def OnRspQryInstrumentCommissionRate(self, pInstrumentCommissionRate: tdapi.CThostFtdcInstrumentCommissionRateField, pRspInfo: tdapi.CThostFtdcRspInfoField, nRequestID, bIsLast):
        if pRspInfo:
            print(f"OnRspQryInstrumentCommissionRate {pRspInfo.ErrorID} {pRspInfo.ErrorMsg}")

        if pInstrumentCommissionRate:
            print(f"OnRspQryInstrumentCommissionRate {pInstrumentCommissionRate.InstrumentID}")
            try:
                instrument = Instrument()
                instrument.InstrumentID = pInstrumentCommissionRate.InstrumentID
                instrument.ProductID = self.instrumentid_productid.get(instrument.InstrumentID, pInstrumentCommissionRate.InstrumentID)
                instrument.OpenRatioByMoney = pInstrumentCommissionRate.OpenRatioByMoney
                instrument.OpenRatioByVolume = pInstrumentCommissionRate.OpenRatioByVolume
                instrument.CloseRatioByMoney = pInstrumentCommissionRate.CloseRatioByMoney
                instrument.CloseRatioByVolume = pInstrumentCommissionRate.CloseRatioByVolume
                instrument.CloseTodayRatioByMoney = pInstrumentCommissionRate.CloseTodayRatioByMoney
                instrument.CloseTodayRatioByVolume = pInstrumentCommissionRate.CloseTodayRatioByVolume
                instrument.ExchangeID = pInstrumentCommissionRate.ExchangeID
                print(f"update instrument {instrument}")
                self.db.update_instrument(instrument)
            except Exception as e:
                print(e)
                raise e
        self.qry_commission_finished.set()
    
    def qry_option_instrument_commision_rate(self):
        for product_id, instrument_id in self.options.items():
            self.options_productid[instrument_id] = product_id

        i = 0
        product_ids = list(self.options.keys())
        while i < len(product_ids):
            product_id = product_ids[i]
            time.sleep(1)
            request = tdapi.CThostFtdcQryOptionInstrCommRateField()
            request.InstrumentID = self.options[product_id]
            print(f'qry option commission rate {product_id} {request.InstrumentID}')
            request.BrokerID = self.broker_id
            request.InvestorID = self.user_id
            n = self.api.ReqQryOptionInstrCommRate(request, i)
            if n == 0:
                i += 1
                self.qry_option_commission_finished.wait()
                self.qry_option_commission_finished.clear()
    
    def OnRspQryOptionInstrCommRate(self, pOptionInstrCommRate: tdapi.CThostFtdcOptionInstrCommRateField, pRspInfo: tdapi.CThostFtdcRspInfoField, nRequestID, bIsLast):
        if pRspInfo:
            print(f"OnRspQryOptionInstrCommRate {pRspInfo.ErrorID} {pRspInfo.ErrorMsg}")

        if pOptionInstrCommRate:
            print(f"OnRspQryOptionInstrCommRate {pOptionInstrCommRate.InstrumentID}")
            try:
                instrument = Instrument()
                instrument.InstrumentID = pOptionInstrCommRate.InstrumentID
                instrument.ProductID = self.options_productid.get(instrument.InstrumentID, pOptionInstrCommRate.InstrumentID)
                instrument.OpenRatioByMoney = pOptionInstrCommRate.OpenRatioByMoney
                instrument.OpenRatioByVolume = pOptionInstrCommRate.OpenRatioByVolume
                instrument.CloseRatioByMoney = pOptionInstrCommRate.CloseRatioByMoney
                instrument.CloseRatioByVolume = pOptionInstrCommRate.CloseRatioByVolume
                instrument.CloseTodayRatioByMoney = pOptionInstrCommRate.CloseTodayRatioByMoney
                instrument.CloseTodayRatioByVolume = pOptionInstrCommRate.CloseTodayRatioByVolume
                instrument.ExchangeID = pOptionInstrCommRate.ExchangeID
                print(f"update instrument {instrument}")
                self.db.update_instrument(instrument)
            except Exception as e:
                print(e)
                raise e
        self.qry_option_commission_finished.set()


if __name__ == "__main__":
    db_config = DBConfig("user", "password", "host:port", "database")
    ctp_config = CTPConfig("tcp://180.168.146.187:10202", "9999", "0000000000000000", "simnow_client_test", "uid", "password")
    q = QueryAllInstruments(db_config, ctp_config)
    q.connect()
    if q.failed_instruments:
        print("failed instruments")
        with open('failed_instruments.csv', 'w') as f:
            csv.writer(f).writerows(q.failed_instruments)
