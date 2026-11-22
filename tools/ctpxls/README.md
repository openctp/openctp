# ctpxls - 交易数据导出与分析

ctpxls是使用[openctp-ctpcmd工具链](http://www.openctp.cn/ctpcmd.html)中的ctporder命令查询交易数据并存入Excel表，便于盘后复盘分析，已支持导出的数据有资金、持仓、订单、成交、合约、行情，附带的Excel模板中列出了数据中的所有列，可以根据需要删除不需要的列，分析页的计算公式均以列名为准，列顺序的变化不影响计算，可以修改ctpxls.py脚本自行添加其它导出数据。

# 用法

```batch
>python ctpxls.py --help
usage: ctpxls.py [-h] [--config CONFIG] --channel CHANNEL [--user USER] [--password PASSWORD] [--template TEMPLATE]
                 [--out OUT] [--timeout TIMEOUT] [--only ONLY]

ctpxls —— 用 ctporder 查询交易数据，写入 Excel 文件

options:
  -h, --help           show this help message and exit
  --config CONFIG      配置文件，默认 brokers.xml
  --channel CHANNEL    channel name
  --user USER          投资者账号
  --password PASSWORD  登录密码
  --template TEMPLATE  xlsx 模板；不指定则只生成六张数据表
  --out OUT            输出 xlsx 文件名，默认 YYYYMMDD_账户.xlsx
  --timeout TIMEOUT    数据查询超时秒数；默认不限制
  --only ONLY          只查指定表，逗号分隔：资金,持仓,订单,成交,合约,行情
```

**例：**

python ctpxls.py --channel SimNow-7x24 --user 123456 --password xxx

python ctpxls.py --template template.xlsx --out 账户_20261121.xlsx  --channel SimNow-7x24 --user 123456 --password xxx

# 数据格式与定义
导出数据的列名及定义与CTPAPI数据结构与定义完全一致，并且同时显示字段的中英文名，方便对照。
```cpp
///投资者持仓
struct CThostFtdcInvestorPositionField
{
	///经纪公司代码
	TThostFtdcBrokerIDType	BrokerID;
	///投资者代码
	TThostFtdcInvestorIDType	InvestorID;
	///持仓多空方向
	TThostFtdcPosiDirectionType	PosiDirection;
	///投机套保标志
	TThostFtdcHedgeFlagType	HedgeFlag;
	///持仓日期
	TThostFtdcPositionDateType	PositionDate;
	///上日持仓
	TThostFtdcVolumeType	YdPosition;
	///今日持仓
	TThostFtdcVolumeType	Position;
	///多头冻结
	TThostFtdcVolumeType	LongFrozen;
	///空头冻结
	TThostFtdcVolumeType	ShortFrozen;
	///开仓冻结金额
	TThostFtdcMoneyType	LongFrozenAmount;
	///开仓冻结金额
	TThostFtdcMoneyType	ShortFrozenAmount;
	///开仓量
	TThostFtdcVolumeType	OpenVolume;
	///平仓量
	TThostFtdcVolumeType	CloseVolume;
	///开仓金额
	TThostFtdcMoneyType	OpenAmount;
	///平仓金额
	TThostFtdcMoneyType	CloseAmount;
	///持仓成本
	TThostFtdcMoneyType	PositionCost;
	///上次占用的保证金
	TThostFtdcMoneyType	PreMargin;
	///占用的保证金
	TThostFtdcMoneyType	UseMargin;
	///冻结的保证金
	TThostFtdcMoneyType	FrozenMargin;
	///冻结的资金
	TThostFtdcMoneyType	FrozenCash;
	///冻结的手续费
	TThostFtdcMoneyType	FrozenCommission;
	///资金差额
	TThostFtdcMoneyType	CashIn;
	///手续费
	TThostFtdcMoneyType	Commission;
	///平仓盈亏
	TThostFtdcMoneyType	CloseProfit;
	///持仓盈亏
	TThostFtdcMoneyType	PositionProfit;
	///上次结算价
	TThostFtdcPriceType	PreSettlementPrice;
	///本次结算价
	TThostFtdcPriceType	SettlementPrice;
	///交易日
	TThostFtdcDateType	TradingDay;
	///结算编号
	TThostFtdcSettlementIDType	SettlementID;
	///开仓成本
	TThostFtdcMoneyType	OpenCost;
	///交易所保证金
	TThostFtdcMoneyType	ExchangeMargin;
	///组合成交形成的持仓
	TThostFtdcVolumeType	CombPosition;
	///组合多头冻结
	TThostFtdcVolumeType	CombLongFrozen;
	///组合空头冻结
	TThostFtdcVolumeType	CombShortFrozen;
	///逐日盯市平仓盈亏
	TThostFtdcMoneyType	CloseProfitByDate;
	///逐笔对冲平仓盈亏
	TThostFtdcMoneyType	CloseProfitByTrade;
	///今日持仓
	TThostFtdcVolumeType	TodayPosition;
	///保证金率
	TThostFtdcRatioType	MarginRateByMoney;
	///保证金率(按手数)
	TThostFtdcRatioType	MarginRateByVolume;
	///执行冻结
	TThostFtdcVolumeType	StrikeFrozen;
	///执行冻结金额
	TThostFtdcMoneyType	StrikeFrozenAmount;
	///放弃执行冻结
	TThostFtdcVolumeType	AbandonFrozen;
	///交易所代码
	TThostFtdcExchangeIDType	ExchangeID;
	///执行冻结的昨仓
	TThostFtdcVolumeType	YdStrikeFrozen;
	///投资单元代码
	TThostFtdcInvestUnitIDType	InvestUnitID;
	///持仓成本差值
	TThostFtdcMoneyType	PositionCostOffset;
	///tas持仓手数
	TThostFtdcVolumeType	TasPosition;
	///tas持仓成本
	TThostFtdcMoneyType	TasPositionCost;
	///合约代码
	TThostFtdcInstrumentIDType	InstrumentID;
	///期权市值
	TThostFtdcMoneyType	OptionValue;
};
```

# Excel模板

ctpxls脚本只替换模板Excel文件数据页（资金、持仓、订单等）中的数据部分，并且以模板中的列名为准写入相应的数据，ctpxls不修改模板文档，只依照模板内容生成新的Excel文件，默认输出文件名为xxx账户_yyyymmdd.xlsx，也可以通过--out参数指定输出文件名。如果不指定模板文件，则只生成包含资金、持仓、订单等数据页所有列的Excel文件。

<img width="1709" height="950" alt="image" src="https://github.com/user-attachments/assets/e4d6e29c-52a7-4e6e-9414-53c1fea14940" />

# 效果

## 资金
<img width="1709" height="950" alt="5815c239e5d3976192b2039a2285c237" src="https://github.com/user-attachments/assets/d22a05e9-54d0-4269-8f8d-80206afa0272" />

## 持仓
<img width="1709" height="950" alt="6505d2bc-6a9b-4a54-86bb-bb3a09a8e738" src="https://github.com/user-attachments/assets/9a7db0f2-6c72-44e8-a87c-beee5d6d6ca2" />

## 订单
<img width="1709" height="950" alt="1fdce613e037127aea9bbe79e2c434bb" src="https://github.com/user-attachments/assets/72240336-8170-4543-8857-8aaa954c9233" />

## 统计分析
<img width="1709" height="950" alt="c7d1cdc40cb13638915814110ef59773" src="https://github.com/user-attachments/assets/fda8e033-d598-45a9-857f-35fac3399da5" />
