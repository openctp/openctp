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


@dataclass
class InvestorPositionField:
    """投资者持仓"""

    BrokerID: str = ""  # 经纪公司代码
    InvestorID: str = ""  # 投资者代码
    PosiDirection: str = ""  # 持仓多空方向
    HedgeFlag: str = ""  # 投机套保标志
    PositionDate: str = ""  # 持仓日期
    YdPosition: int = 0  # 上日持仓
    Position: int = 0  # 今日持仓
    LongFrozen: int = 0  # 多头冻结
    ShortFrozen: int = 0  # 空头冻结
    LongFrozenAmount: float = 0.0  # 开仓冻结金额
    ShortFrozenAmount: float = 0.0  # 开仓冻结金额
    OpenVolume: int = 0  # 开仓量
    CloseVolume: int = 0  # 平仓量
    OpenAmount: float = 0.0  # 开仓金额
    CloseAmount: float = 0.0  # 平仓金额
    PositionCost: float = 0.0  # 持仓成本
    PreMargin: float = 0.0  # 上次占用的保证金
    UseMargin: float = 0.0  # 占用的保证金
    FrozenMargin: float = 0.0  # 冻结的保证金
    FrozenCash: float = 0.0  # 冻结的资金
    FrozenCommission: float = 0.0  # 冻结的手续费
    CashIn: float = 0.0  # 资金差额
    Commission: float = 0.0  # 手续费
    CloseProfit: float = 0.0  # 平仓盈亏
    PositionProfit: float = 0.0  # 持仓盈亏
    PreSettlementPrice: float = 0.0  # 上次结算价
    SettlementPrice: float = 0.0  # 本次结算价
    TradingDay: str = ""  # 交易日
    SettlementID: int = 0  # 结算编号
    OpenCost: float = 0.0  # 开仓成本
    ExchangeMargin: float = 0.0  # 交易所保证金
    CombPosition: int = 0  # 组合成交形成的持仓
    CombLongFrozen: int = 0  # 组合多头冻结
    CombShortFrozen: int = 0  # 组合空头冻结
    CloseProfitByDate: float = 0.0  # 逐日盯市平仓盈亏
    CloseProfitByTrade: float = 0.0  # 逐笔对冲平仓盈亏
    TodayPosition: int = 0  # 今日持仓
    MarginRateByMoney: float = 0.0  # 保证金率
    MarginRateByVolume: float = 0.0  # 保证金率(按手数)
    StrikeFrozen: int = 0  # 执行冻结
    StrikeFrozenAmount: float = 0.0  # 执行冻结金额
    AbandonFrozen: int = 0  # 放弃执行冻结
    ExchangeID: str = ""  # 交易所代码
    YdStrikeFrozen: int = 0  # 执行冻结的昨仓
    InvestUnitID: str = ""  # 投资单元代码
    PositionCostOffset: float = 0.0  # 持仓成本差值
    TasPosition: int = 0  # tas持仓手数
    TasPositionCost: float = 0.0  # tas持仓成本
    InstrumentID: str = ""  # 合约代码


@dataclass
class TradingAccountField:
    """资金账户"""

    BrokerID: str = ""  # 经纪公司代码
    AccountID: str = ""  # 投资者帐号
    PreMortgage: float = 0.0  # 上次质押金额
    PreCredit: float = 0.0  # 上次信用额度
    PreDeposit: float = 0.0  # 上次存款额
    PreBalance: float = 0.0  # 上次结算准备金
    PreMargin: float = 0.0  # 上次占用的保证金
    InterestBase: float = 0.0  # 利息基数
    Interest: float = 0.0  # 利息收入
    Deposit: float = 0.0  # 入金金额
    Withdraw: float = 0.0  # 出金金额
    FrozenMargin: float = 0.0  # 冻结的保证金
    FrozenCash: float = 0.0  # 冻结的资金
    FrozenCommission: float = 0.0  # 冻结的手续费
    CurrMargin: float = 0.0  # 当前保证金总额
    CashIn: float = 0.0  # 资金差额
    Commission: float = 0.0  # 手续费
    CloseProfit: float = 0.0  # 平仓盈亏
    PositionProfit: float = 0.0  # 持仓盈亏
    Balance: float = 0.0  # 期货结算准备金
    Available: float = 0.0  # 可用资金
    WithdrawQuota: float = 0.0  # 可取资金
    Reserve: float = 0.0  # 基本准备金
    TradingDay: str = ""  # 交易日
    SettlementID: int = 0  # 结算编号
    Credit: float = 0.0  # 信用额度
    Mortgage: float = 0.0  # 质押金额
    ExchangeMargin: float = 0.0  # 交易所保证金
    DeliveryMargin: float = 0.0  # 投资者交割保证金
    ExchangeDeliveryMargin: float = 0.0  # 交易所交割保证金
    ReserveBalance: float = 0.0  # 保底期货结算准备金
    CurrencyID: str = ""  # 币种代码
    PreFundMortgageIn: float = 0.0  # 上次货币质入金额
    PreFundMortgageOut: float = 0.0  # 上次货币质出金额
    FundMortgageIn: float = 0.0  # 货币质入金额
    FundMortgageOut: float = 0.0  # 货币质出金额
    FundMortgageAvailable: float = 0.0  # 货币质押余额
    MortgageableFund: float = 0.0  # 可质押货币金额
    SpecProductMargin: float = 0.0  # 特殊产品占用保证金
    SpecProductFrozenMargin: float = 0.0  # 特殊产品冻结保证金
    SpecProductCommission: float = 0.0  # 特殊产品手续费
    SpecProductFrozenCommission: float = 0.0  # 特殊产品冻结手续费
    SpecProductPositionProfit: float = 0.0  # 特殊产品持仓盈亏
    SpecProductCloseProfit: float = 0.0  # 特殊产品平仓盈亏
    SpecProductPositionProfitByAlg: float = 0.0  # 根据持仓盈亏算法计算的特殊产品持仓盈亏
    SpecProductExchangeMargin: float = 0.0  # 特殊产品交易所保证金
    BizType: str = ""  # 业务类型
    FrozenSwap: float = 0.0  # 延时换汇冻结金额
    RemainSwap: float = 0.0  # 剩余换汇额度


@dataclass
class OrderField:
    """报单"""

    BrokerID: str = ""  # 经纪公司代码
    InvestorID: str = ""  # 投资者代码
    OrderRef: str = ""  # 报单引用
    UserID: str = ""  # 用户代码
    OrderPriceType: str = ""  # 报单价格条件
    Direction: str = ""  # 买卖方向
    CombOffsetFlag: str = ""  # 组合开平标志
    CombHedgeFlag: str = ""  # 组合投机套保标志
    LimitPrice: float = 0.0  # 价格
    VolumeTotalOriginal: int = 0  # 数量
    TimeCondition: str = ""  # 有效期类型
    GTDDate: str = ""  # GTD日期
    VolumeCondition: str = ""  # 成交量类型
    MinVolume: int = 0  # 最小成交量
    ContingentCondition: str = ""  # 触发条件
    StopPrice: float = 0.0  # 止损价
    ForceCloseReason: str = ""  # 强平原因
    IsAutoSuspend: int = 0  # 自动挂起标志
    BusinessUnit: str = ""  # 业务单元
    RequestID: int = 0  # 请求编号
    OrderLocalID: str = ""  # 本地报单编号
    ExchangeID: str = ""  # 交易所代码
    ParticipantID: str = ""  # 会员代码
    ClientID: str = ""  # 客户代码
    TraderID: str = ""  # 交易所交易员代码
    InstallID: int = 0  # 安装编号
    OrderSubmitStatus: str = ""  # 报单提交状态
    NotifySequence: int = 0  # 报单提示序号
    TradingDay: str = ""  # 交易日
    SettlementID: int = 0  # 结算编号
    OrderSysID: str = ""  # 报单编号
    OrderSource: str = ""  # 报单来源
    OrderStatus: str = ""  # 报单状态
    OrderType: str = ""  # 报单类型
    VolumeTraded: int = 0  # 今成交数量
    VolumeTotal: int = 0  # 剩余数量
    InsertDate: str = ""  # 报单日期
    InsertTime: str = ""  # 委托时间
    ActiveTime: str = ""  # 激活时间
    SuspendTime: str = ""  # 挂起时间
    UpdateTime: str = ""  # 最后修改时间
    CancelTime: str = ""  # 撤销时间
    ActiveTraderID: str = ""  # 最后修改交易所交易员代码
    ClearingPartID: str = ""  # 结算会员编号
    SequenceNo: int = 0  # 序号
    FrontID: int = 0  # 前置编号
    SessionID: int = 0  # 会话编号
    UserProductInfo: str = ""  # 用户端产品信息
    StatusMsg: str = ""  # 状态信息
    UserForceClose: int = 0  # 用户强评标志
    ActiveUserID: str = ""  # 操作用户代码
    BrokerOrderSeq: int = 0  # 经纪公司报单编号
    RelativeOrderSysID: str = ""  # 相关报单
    ZCETotalTradedVolume: int = 0  # 郑商所成交数量
    IsSwapOrder: int = 0  # 互换单标志
    BranchID: str = ""  # 营业部编号
    InvestUnitID: str = ""  # 投资单元代码
    AccountID: str = ""  # 资金账号
    CurrencyID: str = ""  # 币种代码
    MacAddress: str = ""  # Mac地址
    InstrumentID: str = ""  # 合约代码
    ExchangeInstID: str = ""  # 合约在交易所的代码
    IPAddress: str = ""  # IP地址


@dataclass
class TradeField:
    """成交"""

    BrokerID: str = ""  # 经纪公司代码
    InvestorID: str = ""  # 投资者代码
    OrderRef: str = ""  # 报单引用
    UserID: str = ""  # 用户代码
    ExchangeID: str = ""  # 交易所代码
    TradeID: str = ""  # 成交编号
    Direction: str = ""  # 买卖方向
    OrderSysID: str = ""  # 报单编号
    ParticipantID: str = ""  # 会员代码
    ClientID: str = ""  # 客户代码
    TradingRole: str = ""  # 交易角色
    OffsetFlag: str = ""  # 开平标志
    HedgeFlag: str = ""  # 投机套保标志
    Price: float = 0.0  # 价格
    Volume: int = 0  # 数量
    TradeDate: str = ""  # 成交时期
    TradeTime: str = ""  # 成交时间
    TradeType: str = ""  # 成交类型
    PriceSource: str = ""  # 成交价来源
    TraderID: str = ""  # 交易所交易员代码
    OrderLocalID: str = ""  # 本地报单编号
    ClearingPartID: str = ""  # 结算会员编号
    BusinessUnit: str = ""  # 业务单元
    SequenceNo: int = 0  # 序号
    TradingDay: str = ""  # 交易日
    SettlementID: int = 0  # 结算编号
    BrokerOrderSeq: int = 0  # 经纪公司报单编号
    TradeSource: str = ""  # 成交来源
    InvestUnitID: str = ""  # 投资单元代码
    InstrumentID: str = ""  # 合约代码
    ExchangeInstID: str = ""  # 合约在交易所的代码


@dataclass
class DepthMarketDataField:
    """深度行情"""

    TradingDay: str = ""  # 交易日
    ExchangeID: str = ""  # 交易所代码
    LastPrice: float = 0.0  # 最新价
    PreSettlementPrice: float = 0.0  # 上次结算价
    PreClosePrice: float = 0.0  # 昨收盘
    PreOpenInterest: float = 0.0  # 昨持仓量
    OpenPrice: float = 0.0  # 今开盘
    HighestPrice: float = 0.0  # 最高价
    LowestPrice: float = 0.0  # 最低价
    Volume: int = 0  # 数量
    Turnover: float = 0.0  # 成交金额
    OpenInterest: float = 0.0  # 持仓量
    ClosePrice: float = 0.0  # 今收盘
    SettlementPrice: float = 0.0  # 本次结算价
    UpperLimitPrice: float = 0.0  # 涨停板价
    LowerLimitPrice: float = 0.0  # 跌停板价
    PreDelta: float = 0.0  # 昨虚实度
    CurrDelta: float = 0.0  # 今虚实度
    UpdateTime: str = ""  # 最后修改时间
    UpdateMillisec: int = 0  # 最后修改毫秒
    BidPrice1: float = 0.0  # 申买价一
    BidVolume1: int = 0  # 申买量一
    AskPrice1: float = 0.0  # 申卖价一
    AskVolume1: int = 0  # 申卖量一
    BidPrice2: float = 0.0  # 申买价二
    BidVolume2: int = 0  # 申买量二
    AskPrice2: float = 0.0  # 申卖价二
    AskVolume2: int = 0  # 申卖量二
    BidPrice3: float = 0.0  # 申买价三
    BidVolume3: int = 0  # 申买量三
    AskPrice3: float = 0.0  # 申卖价三
    AskVolume3: int = 0  # 申卖量三
    BidPrice4: float = 0.0  # 申买价四
    BidVolume4: int = 0  # 申买量四
    AskPrice4: float = 0.0  # 申卖价四
    AskVolume4: int = 0  # 申卖量四
    BidPrice5: float = 0.0  # 申买价五
    BidVolume5: int = 0  # 申买量五
    AskPrice5: float = 0.0  # 申卖价五
    AskVolume5: int = 0  # 申卖量五
    AveragePrice: float = 0.0  # 当日均价
    ActionDay: str = ""  # 业务日期
    InstrumentID: str = ""  # 合约代码
    ExchangeInstID: str = ""  # 合约在交易所的代码
    BandingUpperPrice: float = 0.0  # 上带价
    BandingLowerPrice: float = 0.0  # 下带价


def convert_field(src_instance, dst_field_class):
    dst_instance = dst_field_class()

    if src_instance is None:
        return dst_instance

    for k in src_instance.__annotations__.keys():
        setattr(dst_instance, k, getattr(src_instance, k))
    return dst_instance


class CTPDump(tdapi.CThostFtdcTraderSpi):
    def __init__(self, host, broker, user, password, appid, authcode):
        self.broker = broker
        self.user = user
        self.password = password
        self.appid = appid
        self.authcode = authcode

        self.Exchanges = []
        self.Products = []
        self.Instruments = []
        self.Positions = []
        self.TradingAccount = []
        self.Orders = []
        self.Trades = []
        self.MarketData = []

        tdapi.CThostFtdcTraderSpi.__init__(self)
        self.api: tdapi.CThostFtdcTraderApi = tdapi.CThostFtdcTraderApi.CreateFtdcTraderApi()
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
    
    def QryPosition(self):
        req = tdapi.CThostFtdcQryInvestorPositionField()
        req.BrokerID = self.broker
        req.InvestorID = self.user
        self.api.ReqQryInvestorPosition(req, 0)
    
    def QryTradingAccount(self):
        req = tdapi.CThostFtdcQryTradingAccountField()
        req.BrokerID = self.broker
        req.InvestorID = self.user
        self.api.ReqQryTradingAccount(req, 0)
    
    def QryOrder(self):
        req = tdapi.CThostFtdcQryOrderField()
        req.BrokerID = self.broker
        req.InvestorID = self.user
        self.api.ReqQryOrder(req, 0)
    
    def QryTrade(self):
        req = tdapi.CThostFtdcQryTradeField()
        req.BrokerID = self.broker
        req.InvestorID = self.user
        self.api.ReqQryTrade(req, 0)
    
    def QryDepthMarketData(self):
        req = tdapi.CThostFtdcQryDepthMarketDataField()
        self.api.ReqQryDepthMarketData(req, 0)

    def OnFrontConnected(self) -> "None":
        print("OnFrontConnected")

        req = tdapi.CThostFtdcReqAuthenticateField()
        req.BrokerID = self.broker
        req.UserID = self.user
        req.AppID = self.appid
        req.AuthCode = self.authcode
        req.UserProductInfo = "ctpdump"
        self.api.ReqAuthenticate(req, 0)


    def OnFrontDisconnected(self, nReason: int) -> "None":
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

    def OnRspUserLogin(self, pRspUserLogin: 'CThostFtdcRspUserLoginField', pRspInfo: 'CThostFtdcRspInfoField', nRequestID: 'int', bIsLast: 'bool') -> "None":
        if pRspInfo is not None and pRspInfo.ErrorID != 0:
            print(f"Login failed. {pRspInfo.ErrorMsg}")
            exit(-1)
        print(f"Login succeed. TradingDay: {pRspUserLogin.TradingDay}")

        semaphore.release()

    def OnRspQryExchange(self, pExchange: "CThostFtdcExchangeField", pRspInfo: "CThostFtdcRspInfoField", nRequestID: "int", bIsLast: "bool") -> "None":
        if pRspInfo is not None and pRspInfo.ErrorID != 0:
            print(f"OnRspQryExchange failed: {pRspInfo.ErrorMsg}")
            exit(-1)
        # print(f"OnRspQryExchange:{pExchange.ExchangeID}, {pExchange.ExchangeName}")

        exchange = Exchange(ExchangeID = pExchange.ExchangeID, ExchangeName = pExchange.ExchangeName)
        self.Exchanges.append(exchange)

        if bIsLast is True:
            semaphore.release()

    def OnRspQryProduct(self, pProduct: "CThostFtdcProductField", pRspInfo: "CThostFtdcRspInfoField", nRequestID: "int", bIsLast: "bool") -> "None":
        if pRspInfo is not None and pRspInfo.ErrorID != 0:
            print(f"OnRspQryProduct failed: {pRspInfo.ErrorMsg}")
            exit(-1)
        # print(f"OnRspQryProduct:{pProduct.ProductID}, {pProduct.ProductName}, {pProduct.ExchangeID}")

        product = Product(ProductID = pProduct.ProductID, ProductName = pProduct.ProductName)
        self.Products.append(product)

        if bIsLast is True:
            semaphore.release()

    def OnRspQryInstrument(
        self,
        pInstrument: "CThostFtdcInstrumentField",
        pRspInfo: "CThostFtdcRspInfoField",
        nRequestID: "int",
        bIsLast: "bool"
    ) -> "None":
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

        if bIsLast is True:
            semaphore.release()
    
    def OnRspQryInvestorPosition(self, pInvestorPosition, pRspInfo, nRequestID, bIsLast):
        if pRspInfo is not None and pRspInfo.ErrorID != 0:
            print(f'OnRspQryInvestorPosition failed: {pRspInfo.ErrorMsg}')
            exit(-1)
        
        if pInvestorPosition:
            position = convert_field(pInvestorPosition, InvestorPositionField)
            self.Positions.append(position)
        if bIsLast is True:
            semaphore.release()
    
    def OnRspQryOrder(self, pOrder, pRspInfo, nRequestID, bIsLast):
        if pRspInfo is not None and pRspInfo.ErrorID != 0:
            print(f'OnRspQryOrder failed: {pRspInfo.ErrorMsg}')
            exit(-1)
        
        if pOrder:
            order = convert_field(pOrder, OrderField)
            self.Orders.append(order)
        if bIsLast is True:
            semaphore.release()

    def OnRspQryTrade(self, pTrade, pRspInfo, nRequestID, bIsLast):
        if pRspInfo is not None and pRspInfo.ErrorID != 0:
            print(f'OnRspQryTrade failed: {pRspInfo.ErrorMsg}')
            exit(-1)
            
        if pTrade:
            trade = convert_field(pTrade, TradeField)
            self.Trades.append(trade)
        if bIsLast is True:
            semaphore.release()
    
    def OnRspQryTradingAccount(self, pTradingAccount, pRspInfo, nRequestID, bIsLast):
        if pRspInfo is not None and pRspInfo.ErrorID != 0:
            print(f'OnRspQryTradingAccount failed: {pRspInfo.ErrorMsg}')
            exit(-1)
        
        if pTradingAccount:
            account = convert_field(pTradingAccount, TradingAccountField)
            self.TradingAccount.append(account)
        if bIsLast is True:
            semaphore.release()
    
    def OnRspQryDepthMarketData(self, pDepthMarketData, pRspInfo, nRequestID, bIsLast):
        if pRspInfo is not None and pRspInfo.ErrorID != 0:
            print(f'OnRspQryDepthMarketData failed: {pRspInfo.ErrorMsg}')
            exit(-1)
        if pDepthMarketData:
            data = convert_field(pDepthMarketData, DepthMarketDataField)
            self.MarketData.append(data)
        if bIsLast is True:
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
    time.sleep(1)
    semaphore.acquire()
    ctpdump.QryDepthMarketData()

    # query positions
    time.sleep(1)
    semaphore.acquire()
    ctpdump.QryPosition()

    # query accounts
    time.sleep(1)
    semaphore.acquire()
    ctpdump.QryTradingAccount()

    # query orders
    time.sleep(1)
    semaphore.acquire()
    ctpdump.QryOrder()

    # query trades
    time.sleep(1)
    semaphore.acquire()
    ctpdump.QryTrade()

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
    
    print("DepthMarketData:")
    print(json.dumps([data.__dict__ for data in ctpdump.MarketData], indent=2))
    jsonstr = ',\n'.join(json.dumps(item) for item in [data.__dict__ for data in ctpdump.MarketData])
    print("[{}]".format(jsonstr))
   
    print("Account:")
    print(json.dumps([account.__dict__ for account in ctpdump.TradingAccount], indent=2))
    jsonstr = ',\n'.join(json.dumps(item) for item in [data.__dict__ for data in ctpdump.TradingAccount])
    print("[{}]".format(jsonstr))

    print("Positions:")
    print(json.dumps([position.__dict__ for position in ctpdump.Positions], indent=2))
    jsonstr = ',\n'.join(json.dumps(item) for item in [data.__dict__ for data in ctpdump.Positions])
    print("[{}]".format(jsonstr))

    print("Orders:")
    print(json.dumps([order.__dict__ for order in ctpdump.Orders], indent=2))
    jsonstr = ',\n'.join(json.dumps(item) for item in [data.__dict__ for data in ctpdump.Orders])
    print("[{}]".format(jsonstr))

    print("Trades:")
    print(json.dumps([trade.__dict__ for trade in ctpdump.Trades], indent=2))
    jsonstr = ',\n'.join(json.dumps(item) for item in [data.__dict__ for data in ctpdump.Trades])
    print("[{}]".format(jsonstr))
