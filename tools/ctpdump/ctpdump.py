"""
author: krenx@openctp.
last modify: 2024/5/2
"""


import json
import sys
import threading
import time
from dataclasses import dataclass, asdict
from openctp_ctp import tdapi
# import thosttraderapi as tdapi


def adjust_price(price: float) -> float:
    if price == sys.float_info.max:
        price = 0
    return price


@dataclass
class InstrumentField:
    ExchangeID: str = ""
    InstrumentID: str = ""
    InstrumentName: str = ""
    ProductClass: str = ""
    ProductID: str = ""
    PriceTick: float = 0.0
    VolumeMultiple: int = 0
    DeliveryYear: int = 0
    DeliveryMonth: int = 0
    MaxMarketOrderVolume: int = 0
    MinMarketOrderVolume: int = 0
    MaxLimitOrderVolume: int = 0
    MinLimitOrderVolume: int = 0
    OpenDate: str = ""
    ExpireDate: str = ""
    StartDelivDate: str = ""
    EndDelivDate: str = ""
    InstLifePhase: str = ""
    IsTrading: int = 0
    PositionType: str = ""
    PositionDateType: str = ""
    LongMarginRatio: float = 0.0
    ShortMarginRatio: float = 0.0
    MaxMarginSideAlgorithm: str = ""
    UnderlyingInstrID: str = ""
    StrikePrice: float = 0
    OptionsType: str = ""
    UnderlyingMultiple: int = 0
    CombinationType: str = ""


@dataclass
class ExchangeField:
    ExchangeID: str = ""
    ExchangeName: str = ""


@dataclass
class ProductField:
    ExchangeID: str = ""
    ProductID: str = ""
    ProductName: str = ""
    ProductClass: str = ""
    VolumeMultiple: int = 0
    PriceTick: float = 0.0
    PositionType: str = ""
    PositionDateType: str = ""
    TradeCurrencyID: str = ""
    UnderlyingMultiple: int = 0


@dataclass
class InvestorPositionField:
    """投资者持仓"""

    BrokerID: str = ""  # 经纪公司代码
    InvestorID: str = ""  # 投资者代码
    ExchangeID: str = ""  # 交易所代码
    InstrumentID: str = ""  # 合约代码
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
    YdStrikeFrozen: int = 0  # 执行冻结的昨仓
    InvestUnitID: str = ""  # 投资单元代码
    PositionCostOffset: float = 0.0  # 持仓成本差值
    TasPosition: int = 0  # tas持仓手数
    TasPositionCost: float = 0.0  # tas持仓成本


@dataclass
class InvestorPositionDetailField:
    """持仓明细"""
    BrokerID: str = ""  # 经纪公司代码
    InvestorID: str = ""  # 投资者代码
    ExchangeID: str = ""  # 交易所代码
    InstrumentID: str = ""  # 合约代码
    Direction: str = ""  # 多空方向
    HedgeFlag: str = ""  # 投机套保标志
    OpenDate: str = ""  # 开仓日期
    TradeID: str = ""  # 成交编号
    Volume: int = 0  # 数量
    OpenPrice: float = 0.0  # 开仓价
    TradeType: str = ""  # 成交类型
    TradingDay: str = ""  # 交易日
    SettlementID: int = 0  # 结算编号
    CloseProfitByDate: int = 0  # 逐日盯市平仓盈亏
    CloseProfitByTrade: int = 0  # 逐笔对冲平仓盈亏
    PositionProfitByDate: float = 0.0  # 逐日盯市持仓盈亏
    PositionProfitByTrade: float = 0.0  # 逐笔对冲持仓盈亏
    Margin: int = 0  # 投资者保证金
    ExchMargin: int = 0  # 交易所保证金
    MarginRateByMoney: float = 0.0  # 保证金率
    MarginRateByVolume: float = 0.0  # 保证金率(按手数)
    LastSettlementPrice: float = 0.0  # 昨结算价
    SettlementPrice: float = 0.0  # 结算价
    CloseVolume: float = 0.0  # 平仓量
    CloseAmount: float = 0.0  # 平仓金额
    TimeFirstVolume: float = 0.0  # 按照时间顺序平仓的笔数,大商所专用
    InvestUnitID: float = 0.0  # 投资单元代码


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

    ExchangeID: str = ""  # 交易所代码
    InstrumentID: str = ""  # 合约代码
    LastPrice: float = 0.0  # 最新价
    Volume: int = 0  # 数量
    Turnover: float = 0.0  # 成交金额
    OpenPrice: float = 0.0  # 今开盘
    HighestPrice: float = 0.0  # 最高价
    LowestPrice: float = 0.0  # 最低价
    ClosePrice: float = 0.0  # 今收盘
    UpperLimitPrice: float = 0.0  # 涨停板价
    LowerLimitPrice: float = 0.0  # 跌停板价
    OpenInterest: float = 0.0  # 持仓量
    SettlementPrice: float = 0.0  # 本次结算价
    PreSettlementPrice: float = 0.0  # 上次结算价
    PreClosePrice: float = 0.0  # 昨收盘
    PreOpenInterest: float = 0.0  # 昨持仓量
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
    TradingDay: str = ""  # 交易日
    ActionDay: str = ""  # 业务日期
    ExchangeInstID: str = ""  # 合约在交易所的代码
    BandingUpperPrice: float = 0.0  # 上带价
    BandingLowerPrice: float = 0.0  # 下带价

@dataclass
class InstrumentCommissionRateField:
    """合约手续费率"""

    BrokerID: str = ""  # 经纪公司代码
    InvestorID: str = ""  # 投资者代码
    InvestorRange: str = ""  # 投资者范围
    ExchangeID: str = ""  # 交易所代码
    InstrumentID: str = ""  # 合约代码
    OpenRatioByMoney: float = 0.0  # 开仓手续费率
    OpenRatioByVolume: float = 0.0  # 开仓手续费
    CloseRatioByMoney: float = 0.0  # 平仓手续费率
    CloseRatioByVolume: float = 0.0  # 平仓手续费
    CloseTodayRatioByMoney: float = 0.0  # 平今手续费率
    CloseTodayRatioByVolume: float = 0.0  # 平今手续费


@dataclass
class InstrumentMarginRateField:
    """合约保证金率"""

    BrokerID: str = ""  # 经纪公司代码
    InvestorID: str = ""  # 投资者代码
    InvestorRange: str = ""  # 投资者范围
    ExchangeID: str = ""  # 交易所代码
    InstrumentID: str = ""  # 合约代码
    HedgeFlag: str = ""  # 投机套保标志
    LongMarginRatioByMoney: float = 0.0  # 多头保证金率
    LongMarginRatioByVolume: float = 0.0  # 多头保证金费
    ShortMarginRatioByMoney: float = 0.0  # 空头保证金率
    ShortMarginRatioByVolume: float = 0.0  # 空头保证金费
    IsRelative: int = 0  # 是否相对交易所收取


@dataclass
class InstrumentOrderCommRateField:
    """当前报单手续费的详细内容"""

    BrokerID: str = ""  # 经纪公司代码
    InvestorID: str = ""  # 投资者代码
    InvestorRange: str = ""  # 投资者范围
    ExchangeID: str = ""  # 交易所代码
    InstrumentID: str = ""  # 合约代码
    HedgeFlag: str = ""  # 投机套保标志
    OrderCommByVolume: float = 0.0  # 报单手续费
    OrderActionCommByVolume: float = 0.0  # 撤单手续费
    OrderCommByTrade: float = 0.0  # 报单手续费
    OrderActionCommByTrade: float = 0.0  # 撤单手续费

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
        self.PositionDetails = []
        self.TradingAccount = []
        self.Orders = []
        self.Trades = []
        self.MarketData = []
        self.CommissionRates = []
        self.MarginRates = []
        self.OrderCommRates = []

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

    def QryPositionDetail(self):
        req = tdapi.CThostFtdcQryInvestorPositionDetailField()
        req.BrokerID = self.broker
        req.InvestorID = self.user
        self.api.ReqQryInvestorPositionDetail(req, 0)

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

    def QryCommissionRate(self):
        req = tdapi.CThostFtdcQryInstrumentCommissionRateField()
        req.BrokerID = self.broker
        req.InvestorID = self.user
        self.api.ReqQryInstrumentCommissionRate(req, 0)

    def QryMarginRate(self):
        req = tdapi.CThostFtdcQryInstrumentMarginRateField()
        req.BrokerID = self.broker
        req.InvestorID = self.user
        self.api.ReqQryInstrumentMarginRate(req, 0)

    def QryOrderCommRate(self):
        req = tdapi.CThostFtdcQryInstrumentOrderCommRateField()
        req.BrokerID = self.broker
        req.InvestorID = self.user
        self.api.ReqQryInstrumentOrderCommRate(req, 0)

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
        print(f"Login succeed. TradingDay: {pRspUserLogin.TradingDay}, MaxOrderRef: {pRspUserLogin.MaxOrderRef}, SystemName: {pRspUserLogin.SystemName}")

        semaphore.release()

    def OnRspQryExchange(self, pExchange: "CThostFtdcExchangeField", pRspInfo: "CThostFtdcRspInfoField", nRequestID: "int", bIsLast: "bool") -> "None":
        if pRspInfo is not None and pRspInfo.ErrorID != 0:
            print(f"OnRspQryExchange failed: {pRspInfo.ErrorMsg}")
            # exit(-1)
        # print(f"OnRspQryExchange:{pExchange.ExchangeID}, {pExchange.ExchangeName}")

        if pExchange:
            exchange = convert_field(pExchange, ExchangeField)
            self.Exchanges.append(exchange)

        if bIsLast is True:
            semaphore.release()

    def OnRspQryProduct(self, pProduct: "CThostFtdcProductField", pRspInfo: "CThostFtdcRspInfoField", nRequestID: "int", bIsLast: "bool") -> "None":
        if pRspInfo is not None and pRspInfo.ErrorID != 0:
            print(f"OnRspQryProduct failed: {pRspInfo.ErrorMsg}")
            # exit(-1)
        # print(f"OnRspQryProduct:{pProduct.ProductID}, {pProduct.ProductName}, {pProduct.ExchangeID}")

        if pProduct:
            product = convert_field(pProduct, ProductField)
            product.UnderlyingMultiple = adjust_price(pProduct.UnderlyingMultiple)
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
            # exit(-1)
        # print(f"OnRspQryInstrument:{pInstrument.InstrumentID}, {pInstrument.InstrumentName}, ExchangeID:{pInstrument.ExchangeID}")

        if pInstrument:
            instrument = convert_field(pInstrument, InstrumentField)
            instrument.UnderlyingMultiple = adjust_price(pInstrument.UnderlyingMultiple)
            instrument.StrikePrice = adjust_price(pInstrument.StrikePrice)
            instrument.LongMarginRatio = adjust_price(pInstrument.LongMarginRatio)
            instrument.ShortMarginRatio = adjust_price(pInstrument.ShortMarginRatio)
            self.Instruments.append(instrument)

        if bIsLast is True:
            semaphore.release()
    
    def OnRspQryInvestorPosition(self, pInvestorPosition, pRspInfo, nRequestID, bIsLast):
        if pRspInfo is not None and pRspInfo.ErrorID != 0:
            print(f'OnRspQryInvestorPosition failed: {pRspInfo.ErrorMsg}')
            # exit(-1)
        
        if pInvestorPosition:
            position = convert_field(pInvestorPosition, InvestorPositionField)
            self.Positions.append(position)
        if bIsLast is True:
            semaphore.release()

    def OnRspQryInvestorPositionDetail(self, pInvestorPositionDetail: "CThostFtdcInvestorPositionDetailField", pRspInfo: "CThostFtdcRspInfoField", nRequestID: "int", bIsLast: "bool") -> "void":
        if pRspInfo is not None and pRspInfo.ErrorID != 0:
            print(f'OnRspQryInvestorPositionDetail failed: {pRspInfo.ErrorMsg}')
            # exit(-1)

        if pInvestorPositionDetail:
            position_detail = convert_field(pInvestorPositionDetail, InvestorPositionDetailField)
            self.PositionDetails.append(position_detail)
        if bIsLast is True:
            semaphore.release()

    def OnRspQryOrder(self, pOrder, pRspInfo, nRequestID, bIsLast):
        if pRspInfo is not None and pRspInfo.ErrorID != 0:
            print(f'OnRspQryOrder failed: {pRspInfo.ErrorMsg}')
            # exit(-1)
        
        if pOrder:
            order = convert_field(pOrder, OrderField)
            self.Orders.append(order)
        if bIsLast is True:
            semaphore.release()

    def OnRspQryTrade(self, pTrade, pRspInfo, nRequestID, bIsLast):
        if pRspInfo is not None and pRspInfo.ErrorID != 0:
            print(f'OnRspQryTrade failed: {pRspInfo.ErrorMsg}')
            # exit(-1)
            
        if pTrade:
            trade = convert_field(pTrade, TradeField)
            self.Trades.append(trade)
        if bIsLast is True:
            semaphore.release()
    
    def OnRspQryTradingAccount(self, pTradingAccount, pRspInfo, nRequestID, bIsLast):
        if pRspInfo is not None and pRspInfo.ErrorID != 0:
            print(f'OnRspQryTradingAccount failed: {pRspInfo.ErrorMsg}')
            # exit(-1)
        
        if pTradingAccount:
            account = convert_field(pTradingAccount, TradingAccountField)
            self.TradingAccount.append(account)
        if bIsLast is True:
            semaphore.release()
    
    def OnRspQryDepthMarketData(self, pDepthMarketData, pRspInfo, nRequestID, bIsLast):
        if pRspInfo is not None and pRspInfo.ErrorID != 0:
            print(f'OnRspQryDepthMarketData failed: {pRspInfo.ErrorMsg}')
            # exit(-1)
        if pDepthMarketData:
            data = convert_field(pDepthMarketData, DepthMarketDataField)
            data.PreSettlementPrice = adjust_price(data.PreSettlementPrice)
            data.PreClosePrice = adjust_price(data.PreClosePrice)
            data.LastPrice = adjust_price(data.LastPrice)
            data.OpenPrice = adjust_price(data.OpenPrice)
            data.ClosePrice = adjust_price(data.ClosePrice)
            data.LowestPrice = adjust_price(data.LowestPrice)
            data.AveragePrice = adjust_price(data.AveragePrice)
            data.HighestPrice = adjust_price(data.HighestPrice)
            data.SettlementPrice = adjust_price(data.SettlementPrice)
            data.CurrDelta = adjust_price(data.CurrDelta)
            data.PreDelta = adjust_price(data.PreDelta)
            data.BandingLowerPrice = adjust_price(data.BandingLowerPrice)
            data.BandingUpperPrice = adjust_price(data.BandingUpperPrice)
            data.AskPrice1 = adjust_price(data.AskPrice1)
            data.AskPrice2 = adjust_price(data.AskPrice2)
            data.AskPrice3 = adjust_price(data.AskPrice3)
            data.AskPrice4 = adjust_price(data.AskPrice4)
            data.AskPrice5 = adjust_price(data.AskPrice5)
            data.BidPrice1 = adjust_price(data.BidPrice1)
            data.BidPrice2 = adjust_price(data.BidPrice2)
            data.BidPrice3 = adjust_price(data.BidPrice3)
            data.BidPrice4 = adjust_price(data.BidPrice4)
            data.BidPrice5 = adjust_price(data.BidPrice5)
            self.MarketData.append(data)
        if bIsLast is True:
            semaphore.release()

    def OnRspQryInstrumentCommissionRate(self, pInstrumentCommissionRate: tdapi.CThostFtdcInstrumentCommissionRateField,
                                         pRspInfo: tdapi.CThostFtdcRspInfoField, nRequestID: int, bIsLast: bool):
        if pRspInfo is not None and pRspInfo.ErrorID != 0:
            print(f'OnRspQryInstrumentCommissionRate failed: {pRspInfo.ErrorMsg}')
            # exit(-1)
        if pInstrumentCommissionRate:
            CommissionRate = convert_field(pInstrumentCommissionRate, InstrumentCommissionRateField)
            self.CommissionRates.append(CommissionRate)
        if bIsLast is True:
            semaphore.release()

    def OnRspQryInstrumentMarginRate(self, pInstrumentMarginRate: tdapi.CThostFtdcInstrumentMarginRateField,
                                     pRspInfo: tdapi.CThostFtdcRspInfoField, nRequestID: int, bIsLast: bool):
        if pRspInfo is not None and pRspInfo.ErrorID != 0:
            print(f'OnRspQryInstrumentMarginRate failed: {pRspInfo.ErrorMsg}')
            # exit(-1)
        if pInstrumentMarginRate:
            MarginRate = convert_field(pInstrumentMarginRate, InstrumentMarginRateField)
            self.MarginRates.append(MarginRate)
        if bIsLast is True:
            semaphore.release()

    def OnRspQryInstrumentOrderCommRate(self, pInstrumentOrderCommRate: tdapi.CThostFtdcInstrumentOrderCommRateField,
                                        pRspInfo: tdapi.CThostFtdcRspInfoField, nRequestID: int, bIsLast: bool):
        if pRspInfo is not None and pRspInfo.ErrorID != 0:
            print(f'OnRspQryInstrumentOrderCommRate failed: {pRspInfo.ErrorMsg}')
            # exit(-1)
        if pInstrumentOrderCommRate:
            OrderCommRate = convert_field(pInstrumentOrderCommRate, InstrumentOrderCommRateField)
            self.OrderCommRates.append(OrderCommRate)
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
    print("querying exchange ...")
    ctpdump.QryExchange()

    # query product
    time.sleep(1)
    semaphore.acquire()
    print("querying product ...")
    ctpdump.QryProduct()

    # query instrument
    time.sleep(1)
    semaphore.acquire()
    print("querying instrument ...")
    ctpdump.QryInstrument()

    # query CommissionRate
    time.sleep(1)
    semaphore.acquire()
    print("querying CommissionRate ...")
    ctpdump.QryCommissionRate()

    # query MarginRate
    time.sleep(1)
    semaphore.acquire()
    print("querying MarginRate ...")
    ctpdump.QryMarginRate()

    # query OrderCommRate
    time.sleep(1)
    semaphore.acquire()
    print("querying OrderCommRate ...")
    ctpdump.QryOrderCommRate()

    # query prices
    time.sleep(1)
    semaphore.acquire()
    print("querying price ...")
    ctpdump.QryDepthMarketData()

    # query positions
    time.sleep(1)
    semaphore.acquire()
    print("querying position ...")
    ctpdump.QryPosition()

    # query position details
    time.sleep(1)
    semaphore.acquire()
    print("querying position detail ...")
    ctpdump.QryPositionDetail()

    # query accounts
    time.sleep(1)
    semaphore.acquire()
    print("querying account ...")
    ctpdump.QryTradingAccount()

    # query orders
    time.sleep(1)
    semaphore.acquire()
    print("querying order ...")
    ctpdump.QryOrder()

    # query trades
    time.sleep(1)
    semaphore.acquire()
    print("querying trade ...")
    ctpdump.QryTrade()

    # wait for completed.
    semaphore.acquire()

    print("Exchanges:")
    jsonstr = ',\n'.join(json.dumps(item, ensure_ascii=False) for item in [asdict(exchange) for exchange in ctpdump.Exchanges])
    print("[{}]".format(jsonstr))

    print("Products:")
    jsonstr = ',\n'.join(json.dumps(item, ensure_ascii=False) for item in [asdict(product) for product in ctpdump.Products])
    print("[{}]".format(jsonstr))

    print("Instruments:")
    jsonstr = ',\n'.join(json.dumps(item, ensure_ascii=False) for item in [asdict(instrument) for instrument in ctpdump.Instruments])
    print("[{}]".format(jsonstr))
    
    print("CommissionRates:")
    jsonstr = ',\n'.join(json.dumps(item, ensure_ascii=False) for item in [asdict(data) for data in ctpdump.CommissionRates])
    print("[{}]".format(jsonstr))

    print("MarginRates:")
    jsonstr = ',\n'.join(json.dumps(item, ensure_ascii=False) for item in [asdict(data) for data in ctpdump.MarginRates])
    print("[{}]".format(jsonstr))

    print("OrderCommRates:")
    jsonstr = ',\n'.join(json.dumps(item, ensure_ascii=False) for item in [asdict(data) for data in ctpdump.OrderCommRates])
    print("[{}]".format(jsonstr))

    print("DepthMarketData:")
    jsonstr = ',\n'.join(json.dumps(item, ensure_ascii=False) for item in [asdict(data) for data in ctpdump.MarketData])
    print("[{}]".format(jsonstr))
   
    print("Account:")
    jsonstr = ',\n'.join(json.dumps(item, ensure_ascii=False) for item in [asdict(data) for data in ctpdump.TradingAccount])
    print("[{}]".format(jsonstr))

    print("Positions:")
    jsonstr = ',\n'.join(json.dumps(item, ensure_ascii=False) for item in [asdict(data) for data in ctpdump.Positions])
    print("[{}]".format(jsonstr))

    print("PositionDetails:")
    jsonstr = ',\n'.join(json.dumps(item, ensure_ascii=False) for item in [asdict(data) for data in ctpdump.PositionDetails])
    print("[{}]".format(jsonstr))

    print("Orders:")
    jsonstr = ',\n'.join(json.dumps(item, ensure_ascii=False) for item in [asdict(data) for data in ctpdump.Orders])
    print("[{}]".format(jsonstr))

    print("Trades:")
    jsonstr = ',\n'.join(json.dumps(item, ensure_ascii=False) for item in [asdict(data) for data in ctpdump.Trades])
    print("[{}]".format(jsonstr))
