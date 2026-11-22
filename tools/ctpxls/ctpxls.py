# -*- coding: utf-8 -*-
"""
ctpxls.py —— 用 openctp-ctpcmd 程序化交易工具链中的 ctporder 命令查询交易数据，按照 Excel 模板生成交易数据Excel文档

规则
----
1. 数据全部通过 ctporder 的 query_* 子命令实时取得，只驻留内存，磁盘上不产生任何中间 JSON。
2. --template 指定模板时：只改动 资金/持仓/订单/成交/合约/行情 六张数据表，
   说明、分析、复盘笔记等其余 Sheet 一概不碰（公式、条件格式、版式原样保留）。
3. 模板里已有的数据表：保留第 1 行（表头），从第 2 行起清空旧值再写新值；
   表头第 1 行的单元格内是「中文名 + 换行 + 原生英文字段名」，脚本按英文字段名匹配列，
   所以列顺序怎么调都不影响写入。
4. 模板里没有的数据表：自动新建，表头按同样的「中文\nEnglish」两段式生成。
5. 不指定 --template 时：裸生成，只含六张数据表，不含说明/分析页。
6. 枚举字段（OrderStatus、Direction、OffsetFlag 等）统一翻成中文。

用法
----
    python ctpxls.py --template template.xlsx --out 账户_20261121.xlsx \
        --channel SimNow-7x24 --user 123456 --password xxx
    python ctpxls.py --channel SimNow-7x24 --user 123456 --password xxx

依赖：pip install openpyxl
"""

from __future__ import annotations

import argparse
import datetime as dt
import json
import re
import subprocess
import sys
from typing import Any, Dict, List, Optional

from openpyxl import Workbook, load_workbook
from openpyxl.styles import Font, PatternFill, Alignment, Border, Side
from openpyxl.utils import get_column_letter
from openpyxl.worksheet.worksheet import Worksheet

HEADER_ROW = 1          # 表头行（中文名 + 换行 + 英文字段名，都在这一行的单元格里）
DATA_START_ROW = 2      # 数据起始行

# =============================================================================
# 一、CTP 结构体字段定义
#    格式： (原生字段名, 中文显示名, 类型)
#    类型： S=文本  M=金额  P=价格  I=整数  D=日期  T=时间
# =============================================================================

ACCOUNT_FIELDS = [
    ("BrokerID", "经纪公司代码", "S"),
    ("AccountID", "投资者账号", "S"),
    ("PreMortgage", "上日质押金额", "M"),
    ("PreCredit", "上日信用额度", "M"),
    ("PreDeposit", "上日结存", "M"),
    ("PreBalance", "上日权益", "M"),
    ("PreMargin", "上日占用保证金", "M"),
    ("InterestBase", "利息基数", "M"),
    ("Interest", "利息金额", "M"),
    ("Deposit", "入金金额", "M"),
    ("Withdraw", "出金金额", "M"),
    ("FrozenMargin", "冻结保证金", "M"),
    ("FrozenCash", "冻结资金", "M"),
    ("FrozenCommission", "冻结手续费", "M"),
    ("CurrMargin", "占用保证金", "M"),
    ("CashIn", "资金净流入", "M"),
    ("Commission", "手续费", "M"),
    ("CloseProfit", "平仓盈亏", "M"),
    ("PositionProfit", "持仓盈亏", "M"),
    ("Balance", "账户权益", "M"),
    ("Available", "可用资金", "M"),
    ("WithdrawQuota", "可取资金", "M"),
    ("Reserve", "基本准备金", "M"),
    ("TradingDay", "交易日", "D"),
    ("SettlementID", "结算编号", "I"),
    ("Credit", "信用额度", "M"),
    ("Mortgage", "质押金额", "M"),
    ("ExchangeMargin", "交易所保证金", "M"),
    ("DeliveryMargin", "交割保证金", "M"),
    ("ExchangeDeliveryMargin", "交易所交割保证金", "M"),
    ("ReserveBalance", "保底准备金", "M"),
    ("CurrencyID", "币种", "S"),
    ("PreFundMortgageIn", "上日货币质押入金", "M"),
    ("PreFundMortgageOut", "上日货币质出金额", "M"),
    ("FundMortgageIn", "货币质押入金", "M"),
    ("FundMortgageOut", "货币质出金额", "M"),
    ("FundMortgageAvailable", "货币质押可用", "M"),
    ("MortgageableFund", "可质押资金", "M"),
    ("SpecProductMargin", "特殊产品占用保证金", "M"),
    ("SpecProductFrozenMargin", "特殊产品冻结保证金", "M"),
    ("SpecProductCommission", "特殊产品手续费", "M"),
    ("SpecProductFrozenCommission", "特殊产品冻结手续费", "M"),
    ("SpecProductPositionProfit", "特殊产品持仓盈亏", "M"),
    ("SpecProductCloseProfit", "特殊产品平仓盈亏", "M"),
    ("SpecProductPositionProfitByAlg", "特殊产品算法持仓盈亏", "M"),
    ("SpecProductExchangeMargin", "特殊产品交易所保证金", "M"),
    ("BizType", "业务类型", "S"),
    ("FrozenSwap", "冻结互换资金", "M"),
    ("RemainSwap", "剩余互换资金", "M"),
]

POSITION_FIELDS = [
    ("InstrumentID", "合约代码", "S"),
    ("BrokerID", "经纪公司代码", "S"),
    ("InvestorID", "投资者代码", "S"),
    ("PosiDirection", "持仓方向", "S"),
    ("HedgeFlag", "投机套保标志", "S"),
    ("PositionDate", "持仓日期", "S"),
    ("YdPosition", "上日持仓", "I"),
    ("Position", "持仓数量", "I"),
    ("LongFrozen", "多头冻结", "I"),
    ("ShortFrozen", "空头冻结", "I"),
    ("LongFrozenAmount", "多冻结金额", "M"),
    ("ShortFrozenAmount", "空冻结金额", "M"),
    ("OpenVolume", "开仓量", "I"),
    ("CloseVolume", "平仓量", "I"),
    ("OpenAmount", "开仓金额", "M"),
    ("CloseAmount", "平仓金额", "M"),
    ("PositionCost", "持仓成本", "M"),
    ("PreMargin", "上次结算保证金", "M"),
    ("UseMargin", "占用的保证金", "M"),
    ("FrozenMargin", "冻结保证金", "M"),
    ("FrozenCash", "冻结资金", "M"),
    ("FrozenCommission", "冻结手续费", "M"),
    ("CashIn", "资金流入", "M"),
    ("Commission", "手续费", "M"),
    ("CloseProfit", "平仓盈亏", "M"),
    ("PositionProfit", "持仓盈亏", "M"),
    ("PreSettlementPrice", "上次结算价", "P"),
    ("SettlementPrice", "本次结算价", "P"),
    ("TradingDay", "交易日", "D"),
    ("SettlementID", "结算编号", "I"),
    ("OpenCost", "开仓成本", "M"),
    ("ExchangeMargin", "交易所保证金", "M"),
    ("CombPosition", "组合成交形成的持仓", "I"),
    ("CombLongFrozen", "组合持仓多头冻结", "I"),
    ("CombShortFrozen", "组合持仓空头冻结", "I"),
    ("CloseProfitByDate", "逐日盯市平仓盈亏", "M"),
    ("CloseProfitByTrade", "逐笔对冲平仓盈亏", "M"),
    ("TodayPosition", "今日持仓", "I"),
    ("MarginRateByMoney", "保证金率(按金额)", "M"),
    ("MarginRateByVolume", "保证金率(按手数)", "M"),
    ("StrikeFrozen", "执行冻结", "I"),
    ("StrikeFrozenAmount", "执行冻结金额", "M"),
    ("AbandonFrozen", "放弃执行冻结", "I"),
    ("YdStrikeFrozen", "上日执行冻结", "I"),
    ("OptPositionType", "期权持仓类别", "S"),
    ("ExchangeID", "交易所代码", "S"),
]

ORDER_FIELDS = [
    ("BrokerID", "经纪公司代码", "S"),
    ("InvestorID", "投资者代码", "S"),
    ("InstrumentID", "合约代码", "S"),
    ("OrderRef", "报单引用", "S"),
    ("UserID", "用户代码", "S"),
    ("OrderPriceType", "报单价格条件", "S"),
    ("Direction", "买卖方向", "S"),
    ("CombOffsetFlag", "组合开平标志", "S"),
    ("CombHedgeFlag", "组合投机套保标志", "S"),
    ("LimitPrice", "价格", "P"),
    ("VolumeTotalOriginal", "数量", "I"),
    ("TimeCondition", "有效期类型", "S"),
    ("GTDDate", "GTD日期", "D"),
    ("VolumeCondition", "成交量类型", "S"),
    ("MinVolume", "最小成交量", "I"),
    ("ContingentCondition", "触发条件", "S"),
    ("StopPrice", "止损价", "P"),
    ("ForceCloseReason", "强平原因", "S"),
    ("IsAutoSuspend", "自动挂起标志", "I"),
    ("RequestID", "请求编号", "I"),
    ("OrderLocalID", "本地报单编号", "S"),
    ("ExchangeID", "交易所代码", "S"),
    ("ParticipantID", "会员代码", "S"),
    ("ClientID", "客户代码", "S"),
    ("ExchangeInstID", "合约在交易所的代码", "S"),
    ("TraderID", "交易所交易员代码", "S"),
    ("InstallID", "安装编号", "I"),
    ("OrderSubmitStatus", "报单提交状态", "S"),
    ("NotifySequence", "报单提示序号", "I"),
    ("TradingDay", "交易日", "D"),
    ("SettlementID", "结算编号", "I"),
    ("OrderSysID", "报单编号", "S"),
    ("OrderSource", "报单来源", "S"),
    ("OrderStatus", "报单状态", "S"),
    ("UserForceClose", "用户强平标志", "I"),
    ("ActiveTime", "激活时间", "T"),
    ("ActiveTraderID", "激活交易员代码", "S"),
    ("ClearingPartID", "结算会员代码", "S"),
    ("SequenceNo", "序号", "I"),
    ("FrontID", "前置编号", "I"),
    ("SessionID", "会话编号", "I"),
    ("UserProductInfo", "用户端产品信息", "S"),
    ("StatusMsg", "状态信息", "S"),
    ("BrokerOrderSeq", "经纪公司报单序号", "I"),
    ("RelatedOrderSysID", "相关报单编号", "S"),
    ("InsertTime", "报单时间", "T"),
    ("CancelTime", "撤单时间", "T"),
]

TRADE_FIELDS = [
    ("BrokerID", "经纪公司代码", "S"),
    ("InvestorID", "投资者代码", "S"),
    ("InstrumentID", "合约代码", "S"),
    ("OrderRef", "报单引用", "S"),
    ("UserID", "用户代码", "S"),
    ("ExchangeID", "交易所代码", "S"),
    ("TradeID", "成交编号", "S"),
    ("Direction", "买卖方向", "S"),
    ("OrderSysID", "报单编号", "S"),
    ("ParticipantID", "会员代码", "S"),
    ("ClientID", "客户代码", "S"),
    ("TradingRole", "交易角色", "S"),
    ("ExchangeInstID", "合约在交易所的代码", "S"),
    ("OffsetFlag", "开平标志", "S"),
    ("HedgeFlag", "投机套保标志", "S"),
    ("Price", "成交价格", "P"),
    ("Volume", "成交数量", "I"),
    ("TradeDate", "成交日期", "D"),
    ("TradingDay", "交易日", "D"),
    ("TradeTime", "成交时间", "T"),
    ("TradeType", "成交类型", "S"),
    ("PriceSource", "成交价来源", "S"),
    ("TraderID", "交易所交易员代码", "S"),
    ("OrderLocalID", "本地报单编号", "S"),
    ("ClearingPartID", "结算会员代码", "S"),
    ("BusinessUnit", "业务单元", "S"),
    ("SequenceNo", "序号", "I"),
    ("BrokerOrderSeq", "经纪公司报单序号", "I"),
    ("TradeSource", "成交来源", "S"),
]

INSTRUMENT_FIELDS = [
    ("InstrumentID", "合约代码", "S"),
    ("ExchangeID", "交易所代码", "S"),
    ("InstrumentName", "合约名称", "S"),
    ("ExchangeInstID", "合约在交易所的代码", "S"),
    ("ProductID", "产品代码", "S"),
    ("ProductClass", "产品类型", "S"),
    ("DeliveryYear", "交割年份", "I"),
    ("DeliveryMonth", "交割月份", "I"),
    ("MaxMarketOrderVolume", "市价单最大下单手数", "I"),
    ("MinMarketOrderVolume", "市价单最小下单手数", "I"),
    ("MaxLimitOrderVolume", "限价单最大下单手数", "I"),
    ("MinLimitOrderVolume", "限价单最小下单手数", "I"),
    ("VolumeMultiple", "合约数量乘数", "I"),
    ("PriceTick", "最小变动价位", "P"),
    ("CreateDate", "创建日", "D"),
    ("OpenDate", "上市日", "D"),
    ("ExpireDate", "到期日", "D"),
    ("StartDelivDate", "开始交割日", "D"),
    ("EndDelivDate", "结束交割日", "D"),
    ("InstLifePhase", "合约生命周期状态", "S"),
    ("IsTrading", "当前是否交易", "S"),
    ("PositionType", "持仓类型", "S"),
    ("PositionDateType", "持仓日期类型", "S"),
    ("LongMarginRatio", "多头保证金率", "M"),
    ("ShortMarginRatio", "空头保证金率", "M"),
    ("MaxMarginSideAlgorithm", "是否单向大边保证金", "S"),
    ("UnderlyingInstrID", "标的合约代码", "S"),
    ("StrikePrice", "执行价", "P"),
    ("OptionsType", "期权类型", "S"),
    ("UnderlyingMultiple", "标的合约乘数", "M"),
    ("CombinationType", "组合类型", "S"),
]

DEPTH_FIELDS = [
    ("TradingDay", "交易日", "D"),
    ("InstrumentID", "合约代码", "S"),
    ("ExchangeID", "交易所代码", "S"),
    ("ExchangeInstID", "合约在交易所的代码", "S"),
    ("LastPrice", "最新价", "P"),
    ("PreSettlementPrice", "上次结算价", "P"),
    ("PreClosePrice", "昨收盘", "P"),
    ("PreOpenInterest", "昨持仓量", "I"),
    ("OpenPrice", "今开盘", "P"),
    ("HighestPrice", "最高价", "P"),
    ("LowestPrice", "最低价", "P"),
    ("Volume", "数量", "I"),
    ("Turnover", "成交金额", "M"),
    ("OpenInterest", "持仓量", "I"),
    ("ClosePrice", "今收盘", "P"),
    ("SettlementPrice", "本次结算价", "P"),
    ("UpperLimitPrice", "涨停板价", "P"),
    ("LowerLimitPrice", "跌停板价", "P"),
    ("PreDelta", "昨虚实度", "M"),
    ("CurrDelta", "今虚实度", "M"),
    ("UpdateTime", "最后修改时间", "T"),
    ("UpdateMillisec", "最后修改毫秒", "I"),
    ("BidPrice1", "申买价一", "P"),
    ("BidVolume1", "申买量一", "I"),
    ("AskPrice1", "申卖价一", "P"),
    ("AskVolume1", "申卖量一", "I"),
    ("BidPrice2", "申买价二", "P"),
    ("BidVolume2", "申买量二", "I"),
    ("AskPrice2", "申卖价二", "P"),
    ("AskVolume2", "申卖量二", "I"),
    ("BidPrice3", "申买价三", "P"),
    ("BidVolume3", "申买量三", "I"),
    ("AskPrice3", "申卖价三", "P"),
    ("AskVolume3", "申卖量三", "I"),
    ("BidPrice4", "申买价四", "P"),
    ("BidVolume4", "申买量四", "I"),
    ("AskPrice4", "申卖价四", "P"),
    ("AskVolume4", "申卖量四", "I"),
    ("BidPrice5", "申买价五", "P"),
    ("BidVolume5", "申买量五", "I"),
    ("AskPrice5", "申卖价五", "P"),
    ("AskVolume5", "申卖量五", "I"),
    ("AveragePrice", "当日均价", "P"),
    ("ActionDay", "业务日期", "D"),
]

# =============================================================================
# 二、枚举值 → 中文说明
# =============================================================================

ENUMS: Dict[str, Dict[str, str]] = {
    # ---- 订单 ----
    "OrderStatus": {
        "0": "全部成交",
        "1": "部分成交还在队列中",
        "2": "部分成交不在队列中",
        "3": "未成交还在队列中",
        "4": "未成交不在队列中",
        "5": "已撤销",
        "a": "未知",
        "b": "尚未触发",
        "c": "已触发",
    },
    "OrderSubmitStatus": {
        "0": "已经提交",
        "1": "撤单已经提交",
        "2": "报单已被接受",
        "3": "报单已被拒绝",
        "4": "未接受",
    },
    "OrderPriceType": {
        "1": "任意价",
        "2": "限价",
        "3": "最优价",
        "4": "最新价",
        "5": "最新价+1跳",
        "6": "最新价+2跳",
        "7": "最新价+3跳",
        "8": "申买价一",
        "9": "申买一+1跳",
        "a": "申买一+2跳",
        "b": "申买一+3跳",
        "c": "申卖价一",
        "d": "申卖一+1跳",
        "e": "申卖一+2跳",
        "f": "申卖一+3跳",
    },
    "TimeCondition": {
        "1": "立即完成否则撤销",
        "2": "本节收盘前有效",
        "3": "当日有效",
        "4": "到指定日期有效",
        "5": "撤销前一直有效",
        "6": "集合竞价有效",
    },
    "VolumeCondition": {
        "1": "任何数量",
        "2": "最小数量",
        "3": "全部数量",
    },
    "ContingentCondition": {
        "1": "立即",
        "2": "止损",
        "3": "止盈",
        "4": "预埋单",
        "5": "最新价大于条件价",
        "7": "最新价小于条件价",
    },
    "ForceCloseReason": {
        "0": "非强平",
        "1": "资金不足",
        "2": "客户超仓",
        "3": "会员超仓",
        "4": "持仓为非交易单位",
        "5": "自然人不能进入交割月",
        "6": "风控校验失败",
        "7": "强平",
        "8": "风控为禁止强平",
    },
    "OrderSource": {"0": "来自参与者", "1": "来自管理员"},
    # ---- 通用方向 / 开平 / 投机套保 ----
    "Direction": {"0": "买", "1": "卖"},
    "OffsetFlag": {
        "0": "开仓",
        "1": "平仓",
        "2": "强平",
        "3": "平今",
        "4": "平昨",
        "5": "强减",
        "6": "本地强减",
    },
    "CombOffsetFlag": {"0": "开仓", "1": "平仓", "2": "强平", "3": "平今", "4": "平昨", "5": "强减", "6": "本地强减"},
    "HedgeFlag": {"1": "投机", "2": "套利", "3": "套保", "4": "做市商"},
    "CombHedgeFlag": {"1": "投机", "2": "套利", "3": "套保", "4": "做市商"},
    "TradingRole": {"0": "投机", "1": "套利", "2": "套保", "3": "做市商"},
    # ---- 持仓 ----
    "PosiDirection": {"1": "净", "2": "多头", "3": "空头"},
    "PositionDate": {"1": "历史仓", "2": "今日仓"},
    "OptPositionType": {"1": "权利方", "2": "义务方"},
    # ---- 成交 ----
    "TradeType": {"0": "普通成交", "1": "期权执行", "2": "期权放弃", "3": "自成交"},
    "PriceSource": {"0": "来自参与者", "1": "来自管理员"},
    "TradeSource": {"0": "来自交易所", "1": "来自前台"},
    # ---- 合约 ----
    "ProductClass": {"1": "期货", "2": "期权", "3": "组合", "4": "即期", "5": "期转现", "6": "现货期权"},
    "InstLifePhase": {"1": "上市", "2": "未上市", "3": "连续交易", "4": "暂停交易", "5": "到期", "6": "休市", "7": "停牌"},
    "IsTrading": {"0": "不可交易", "1": "可交易"},
    "PositionType": {"1": "净持仓", "2": "毛持仓"},
    "PositionDateType": {"1": "只可平昨", "2": "只可平今", "3": "全平"},
    "MaxMarginSideAlgorithm": {"0": "不执行", "1": "执行"},
    "OptionsType": {"1": "看涨期权", "2": "看跌期权", "3": "执行"},
    "CombinationType": {
        "0": "非组合",
        "1": "期货组合",
        "2": "跨期组合",
        "3": "跨品种组合",
        "4": "跨市组合",
        "5": "期权组合",
        "6": "期货期权组合",
    },
    # ---- 资金 ----
    "BizType": {"0": "普通", "1": "期权"},
}

# =============================================================================
# 各表定义：sheet 名、查询子命令、字段列表、是否纵向
# =============================================================================
SHEETS = [
    {"sheet": "资金", "query": "query_account", "fields": ACCOUNT_FIELDS,
     "struct": "TThostFtdcTradingAccountField", "vertical": True},
    {"sheet": "持仓", "query": "query_position", "fields": POSITION_FIELDS,
     "struct": "TThostFtdcInvestorPositionField", "vertical": False},
    {"sheet": "订单", "query": "query_order", "fields": ORDER_FIELDS,
     "struct": "TThostFtdcOrderField", "vertical": False},
    {"sheet": "成交", "query": "query_trade", "fields": TRADE_FIELDS,
     "struct": "TThostFtdcTradeField", "vertical": False},
    {"sheet": "合约", "query": "query_instrument", "fields": INSTRUMENT_FIELDS,
     "struct": "TThostFtdcInstrumentField", "vertical": False},
    {"sheet": "行情", "query": "query_price", "fields": DEPTH_FIELDS,
     "struct": "TThostFtdcDepthMarketDataField", "vertical": False},
]

# 中英对照（自动生成，用于新建表头、资金纵向表、中文名兜底匹配）
FIELD_CN_MAP: Dict[str, str] = {}
FIELD_EN_MAP: Dict[str, str] = {}
for _spec in SHEETS:
    for _en, _cn, _t in _spec["fields"]:
        FIELD_CN_MAP.setdefault(_en, _cn)
        FIELD_EN_MAP.setdefault(_cn, _en)

NUM_FORMAT = {"M": '#,##0.00', "P": '#,##0.0##', "I": '#,##0'}

# =============================================================================
# 样式
# =============================================================================
F_HEAD = Font(name="微软雅黑", size=10, bold=True, color="FFFFFF")
F_BODY = Font(name="微软雅黑", size=10)
F_NOTE = Font(name="微软雅黑", size=9, color="7F7F7F")
FILL_HEAD = PatternFill("solid", fgColor="1F3864")
SIDE = Side(style="thin", color="BFBFBF")
BORDER = Border(left=SIDE, right=SIDE, top=SIDE, bottom=SIDE)

# =============================================================================
# 一、调用 ctporder 取数（内存缓存，不落任何中间文件）
# =============================================================================

def parse_output(text: str) -> List[dict]:
    """整段 JSON / 逐行 JSON / 首尾相接的多对象，三种形态都认"""
    text = (text or "").strip()
    if not text:
        return []
    try:
        return _flatten(json.loads(text))
    except json.JSONDecodeError:
        pass

    rows: List[dict] = []
    for line in text.splitlines():
        line = line.strip().rstrip(",")
        if not line.startswith(("{", "[")):
            continue
        try:
            rows.extend(_flatten(json.loads(line)))
        except json.JSONDecodeError:
            continue
    if rows:
        return rows

    dec = json.JSONDecoder()
    pos, n = 0, len(text)
    while pos < n:
        while pos < n and text[pos] in " \t\r\n":
            pos += 1
        if pos >= n:
            break
        try:
            obj, end = dec.raw_decode(text, pos)
        except json.JSONDecodeError:
            break
        rows.extend(_flatten(obj))
        pos = end
    return rows


def _flatten(obj: Any) -> List[dict]:
    if obj is None:
        return []
    if isinstance(obj, list):
        return [x for x in obj if isinstance(x, dict)]
    if isinstance(obj, dict):
        for key in ("data", "Data", "items", "result", "records", "rows"):
            if key in obj and isinstance(obj[key], (list, dict)):
                got = _flatten(obj[key])
                if got:
                    return got
        if obj and all(not isinstance(v, (list, dict)) for v in obj.values()):
            return [obj]
        out: List[dict] = []
        for v in obj.values():
            out.extend(_flatten(v))
        return out
    return []


def build_cmd(args, subcmd: str) -> List[str]:
    cmd = ["ctporder"]
    if args.config:
        cmd += ["--config", args.config]
    cmd += ["--channel", args.channel]
    if args.user:
        cmd += ["--user", args.user]
    if args.password:
        cmd += ["--password", args.password]
    cmd += ["--no-pretty", subcmd]
    return cmd


def fetch_table(args, spec: dict) -> List[dict]:
    subcmd = spec["query"]
    print(f"[query] {spec['sheet']:<4} <- {subcmd}")
    try:
        proc = subprocess.run(
            build_cmd(args, subcmd),
            capture_output=True,          # 不解析，拿原始 bytes
            timeout=args.timeout,         # None = 无限等待
        )
    except FileNotFoundError:
        print(f"[error] 找不到 ctporder")
        raise SystemExit(2)
    except subprocess.TimeoutExpired:
        print(f"[warn] {spec['sheet']} 查询超时（{args.timeout}s），跳过")
        return []

    # 关键：固定按 UTF-8 解码；StatusMsg 等中文字段里偶发非法字节，用 replace 兜住不外崩
    raw = (proc.stdout or b"").decode("utf-8", errors="replace")

    if proc.returncode != 0:
        err = (proc.stderr or b"").decode("utf-8", errors="replace").strip()
        print(f"[warn] {spec['sheet']} 退出码 {proc.returncode}：{err[:160]}")

    rows = parse_output(raw)
    print(f"        -> {len(rows)} 条")
    return rows


def fetch_all(args, specs: List[dict]) -> Dict[str, List[dict]]:
    cache: Dict[str, List[dict]] = {s["sheet"]: [] for s in SHEETS}
    for spec in specs:
        cache[spec["sheet"]] = fetch_table(args, spec)
    return cache

# =============================================================================
# 二、表头解析：单元格里是「中文名\n英文字段名」，取英文名做匹配键
# =============================================================================
_EN_RE = re.compile(r"[A-Za-z_][A-Za-z0-9_]*")


def cell_lines(value: Any) -> List[str]:
    if value is None:
        return []
    text = str(value).replace("\r\n", "\n").replace("\r", "\n")
    return [x.strip() for x in text.split("\n") if x.strip()]


def header_keys(ws: Worksheet, row: int = HEADER_ROW) -> Dict[str, int]:
    """返回 {匹配键: 列号}；同时登记英文名与中文名，两种都命中"""
    keys: Dict[str, int] = {}
    for col in range(1, ws.max_column + 1):
        lines = cell_lines(ws.cell(row=row, column=col).value)
        if not lines:
            continue
        for line in lines:
            if _EN_RE.fullmatch(line):
                keys.setdefault(line, col)
                break
        for line in lines:
            if not _EN_RE.fullmatch(line):
                keys.setdefault(line, col)
                break
    return keys


def header_text(en: str) -> str:
    """单元格内两段式：中文名 + 换行 + 英文字段名"""
    return f"{FIELD_CN_MAP.get(en, en)}\n{en}"

# =============================================================================
# 三、写入数据表
# =============================================================================

def render(value: Any, field: str, ftype: str) -> Any:
    if value is None:
        return None
    if isinstance(value, str):
        value = value.strip()
        if value == "":
            return None
    if field in ENUMS:
        return ENUMS[field].get(str(value), value)
    if ftype in ("M", "P"):
        try:
            return round(float(value), 4)
        except (TypeError, ValueError):
            return value
    if ftype == "I":
        try:
            return int(float(value))
        except (TypeError, ValueError):
            return value
    if ftype == "D":
        s = str(value)
        return f"{s[:4]}-{s[4:6]}-{s[6:]}" if len(s) == 8 and s.isdigit() else s
    return value


def clear_data_area(ws: Worksheet) -> None:
    """清空第 5 行往下的值（只清值，样式/条件格式/列宽全部保留）"""
    if ws.max_row < DATA_START_ROW:
        return
    for r in range(DATA_START_ROW, ws.max_row + 1):
        for c in range(1, ws.max_column + 1):
            ws.cell(row=r, column=c).value = None


def write_header_row(ws: Worksheet, fields: List[tuple]) -> Dict[str, int]:
    """裸模式：生成「中文\nEnglish」表头，返回 {英文名: 列号}"""
    keys: Dict[str, int] = {}
    for i, (en, cn, _t) in enumerate(fields, start=1):
        cell = ws.cell(row=HEADER_ROW, column=i, value=header_text(en))
        cell.font = F_HEAD
        cell.fill = FILL_HEAD
        cell.alignment = Alignment(horizontal="center", vertical="center", wrap_text=True)
        cell.border = BORDER
        ws.column_dimensions[get_column_letter(i)].width = 20 if _t == "S" else 13
        keys[en] = i
    ws.row_dimensions[HEADER_ROW].height = 34
    ws.freeze_panes = f"A{DATA_START_ROW}"
    return keys


def write_rows(ws: Worksheet, fields: List[tuple], rows: List[dict],
               keys: Dict[str, int], style: bool) -> int:
    """按 英文字段名 → 列号 写入；列顺序与模板无关"""
    types = {en: t for en, _cn, t in fields}
    written = 0
    for offset, rec in enumerate(rows):
        r = DATA_START_ROW + offset
        for en in (x[0] for x in fields):
            col = keys.get(en) or keys.get(FIELD_CN_MAP.get(en, ""))
            if not col:
                continue                      # 模板里没有这一列，跳过
            val = render(_pick(rec, en, FIELD_CN_MAP.get(en, en)), en, types.get(en, "S"))
            if val is None:
                continue
            cell = ws.cell(row=r, column=col, value=val)
            if style:
                cell.font = F_BODY
                cell.border = BORDER
            if isinstance(val, (int, float)) and types.get(en) in NUM_FORMAT:
                cell.number_format = NUM_FORMAT[types[en]]
                if style:
                    cell.alignment = Alignment(horizontal="right", vertical="center")
            elif style:
                cell.alignment = Alignment(horizontal="center", vertical="center")
        written += 1
    return written


def _pick(rec: dict, en: str, cn: str):
    if en in rec:
        return rec[en]
    for k, v in rec.items():
        if k.lower() == en.lower():
            return v
    if cn in rec:
        return rec[cn]
    return None


def write_vertical(ws: Worksheet, fields: List[tuple], record: dict, style: bool) -> int:
    """资金表：纵向。模板已有列布局则沿用，没有就生成 字段 | 数值
    A列字段文本格式：中文名(原生字段名)
    """
    if ws.max_row >= DATA_START_ROW and ws.cell(row=HEADER_ROW, column=1).value is not None:
        # 模板模式：自动定位【字段】、【数值】两列
        key_col, val_col = 1, 2
        for col in range(1, ws.max_column + 1):
            t = " ".join(cell_lines(ws.cell(row=HEADER_ROW, column=col).value))
            if "数值" in t or t.endswith("值"):
                val_col = col
            if "字段" in t:
                key_col = col

        # 清空原有数据行的数值列，保留A列的字段标签文本不动
        for r in range(DATA_START_ROW, ws.max_row + 1):
            ws.cell(row=r, column=val_col).value = None

        cnt = 0
        # 遍历模板里每一行A列的标签：文本是 "中文名(En)"，提取括号内英文
        import re
        pat = re.compile(r"\((.+?)\)$")  # 捕获末尾括号里面的英文名字段
        for r in range(DATA_START_ROW, ws.max_row + 1):
            cell_text = ws.cell(row=r, column=key_col).value
            if not cell_text:
                continue
            m = pat.search(str(cell_text).strip())
            if not m:
                continue
            en = m.group(1)
            ftype = {x[0]: x[2] for x in fields}.get(en, "S")
            val = render(_pick(record, en, ""), en, ftype)
            cell = ws.cell(row=r, column=val_col, value=val)
            if style and isinstance(val, (int, float)) and ftype in NUM_FORMAT:
                cell.number_format = NUM_FORMAT[ftype]
            cnt += 1
        return cnt

    # ========== 裸模式：新建资金表，生成两列【字段｜数值】 ==========
    # 表头
    for i, h in enumerate(["字段", "数值"], start=1):
        cell = ws.cell(row=HEADER_ROW, column=i, value=h)
        cell.font = F_HEAD
        cell.fill = FILL_HEAD
        cell.alignment = Alignment(horizontal="center", vertical="center")
        cell.border = BORDER

    # 逐行写入：A列 = 中文名(英文)，B列=数值
    for i, (en, cn, t) in enumerate(fields):
        r = DATA_START_ROW + i
        label = f"{cn}({en})"
        ws.cell(row=r, column=1, value=label).font = F_BODY
        val = render(_pick(record, en, cn), en, t)
        cell = ws.cell(row=r, column=2, value=val)
        cell.font = F_BODY
        if isinstance(val, (int, float)) and t in NUM_FORMAT:
            cell.number_format = NUM_FORMAT[t]

    # 列宽，现在只有2列，删掉第3列宽度设置
    for i, w in enumerate([26, 20], start=1):
        ws.column_dimensions[get_column_letter(i)].width = w
    ws.row_dimensions[HEADER_ROW].height = 24
    ws.freeze_panes = f"A{DATA_START_ROW}"
    return len(fields)


# =============================================================================
# 四、主流程
# =============================================================================

def fill_sheet(wb: Workbook, spec: dict, rows: List[dict], from_template: bool) -> int:
    name = spec["sheet"]
    exists = name in wb.sheetnames
    ws = wb[name] if exists else wb.create_sheet(title=name)

    if exists:
        if not spec["vertical"]:
            clear_data_area(ws)                 # 横向表：清第5行往下的值，1~4 行不动
        keys = header_keys(ws)
    else:
        keys = write_header_row(ws, spec["fields"])

    if spec["vertical"]:
        rec = rows[0] if rows else {}
        return write_vertical(ws, spec["fields"], rec, style=not exists)

    # 模板存在但表头是空的（罕见）：补表头
    if exists and not keys:
        keys = write_header_row(ws, spec["fields"])
    return write_rows(ws, spec["fields"], rows, keys, style=not exists)


def main() -> int:
    ap = argparse.ArgumentParser(
        description="ctpxls —— 用 ctporder 查询交易数据，写入 Excel 文件")
    ap.add_argument("--config", default=None, help="配置文件，默认 brokers.xml")
    ap.add_argument("--channel", required=True, help="channel name")
    ap.add_argument("--user", default=None, help="投资者账号")
    ap.add_argument("--password", default=None, help="登录密码")
    ap.add_argument("--template", default=None, help="xlsx 模板；不指定则只生成六张数据表")
    ap.add_argument("--out", default=None, help="输出 xlsx 文件名，默认 YYYYMMDD_账户.xlsx")
    ap.add_argument("--timeout", type=int, default=None, help="数据查询超时秒数；默认不限制")
    ap.add_argument("--only", default=None, help="只查指定表，逗号分隔：资金,持仓,订单,成交,合约,行情")
    args = ap.parse_args()

    specs = [s for s in SHEETS
             if args.only is None or s["sheet"] in [x.strip() for x in args.only.split(",")]]
    if not specs:
        print("[error] --only 未匹配到任何表")
        return 2

    cache = fetch_all(args, specs)
    if sum(len(cache[s["sheet"]]) for s in specs) == 0:
        print("[error] 六项查询全部无数据，未生成文件")
        print("        检查：channel、账号密码、brokers.xml、是否在交易/结算时段")
        return 3

    if args.template:
        print(f"[template] {args.template}（只更新六张数据表，其余 Sheet 不动）")
        try:
            wb = load_workbook(args.template)
        except Exception as e:  # noqa: BLE001
            print(f"[error] 模板打不开：{e}")
            return 4
        from_template = True
    else:
        wb = Workbook()
        wb.remove(wb.active)
        from_template = False

    for spec in specs:
        n = fill_sheet(wb, spec, cache[spec["sheet"]], from_template)
        print(f"[fill] {spec['sheet']:<4} {n} 行")

    out = args.out or f"{args.user}_{dt.date.today().strftime('%Y%m%d')}.xlsx"
    wb.save(out)
    print(f"[ok] 已生成 {out}")
    return 0


if __name__ == "__main__":
    sys.exit(main())
