# ctpcmd - 命令行程序化交易

ctpcmd是openctp开发的一套命令行程序化交易工具链，包括ctporder、ctpprice、ctpoptorder、ctpoptprice等命令，从命令行选项获取参数调用CTPAPI发起请求，将响应信息以Json文本形式输出到命令行，可以通过bat、bash、Python等脚本语言结合基础命令编写出强大的策略或自动化工具。

---

## ctporder、ctpoptorder

CTP及CTP股票期权柜台交易命令，支持查询资金、持仓、订单、合约、行情等数据，也支持自然语言式下单撤单，如：

```shell
ctporder buy open 1 share of SHFE.fu2701 at 3500.0
ctporder sell close 3 shares of CZCE.MA701 at market
ctporder cancel "    157620" of CFFEX.IF2612
```

## ctpprice、ctpoptprice

CTP及CTP股票期权柜台报价命令，支持查询行情、订阅行情，支持一次查询/订阅多个合约，如：

```shell
ctpprice query CFFEX.IF2612,SHFE.ag2701,MA701,i2612
ctpprice subscribe fu2701,rb2612,cu2701,AP612
```

---

## 快速开始

### 1. 获取程序

从[openctp官网](http://www.openctp.cn/ctpcmd.html)下载预编译版本ctpcmd工具。

### 2. 运行

```bash
ctpprice.exe --channel SimNow-7x24 query ag2612,fu2612
```

输出（默认为美化格式，单行格式请用--no-pretty选项）：

```json
{
  "data": [
    {
      "InstrumentID": "ag2612",
      "LastPrice": 12294,
      "UpperLimitPrice": 15110,
      "LowerLimitPrice": 10073,
      "PreSettlementPrice": 12592,
      "BidPrice1": 12293,
      "AskPrice1": 12294,
      "Volume": 562214,
      "OpenInterest": 173936,
      "UpdateTime": "00:00:53",
      "TradingDay": "20261106",
      ...
    }
  ],
  "rsp_code": 0,
  "rsp_message": ""
}
```

---

## ctpprice命令用法

```
ctpprice.exe [--no-pretty] [--config <file>] [--channel <name>] <query|subscribe> <instrument_list>
```

| 参数                  | 说明                            | 默认值                  |
| ------------------- | ----------------------------- | -------------------- |
| `--flowpath`        | CTPAPI的Flow文件存放路径             | 默认为当前目录              |
| `--no-pretty`       | 以单行形式输出Json报文，适合程序化场景         | 默认以美化形式输出Json报文，便于阅读 |
| `--config <file>`   | 通道配置文件路径                      | `brokers.xml`        |
| `--channel <name>`  | 使用哪个行情通道，取值来自配置文件中的 channel 名 | 配置文件中的默认通道           |
| `query`             | 子命令：一次性查询快照，返回后退出             | —                    |
| `subscribe`         | 子命令：订阅并持续输出 Tick              | —                    |
| `<instrument_list>` | 合约列表，逗号分隔，位置参数                | 必填                   |

### 合约书写格式

两种写法都支持，可混用：

```bash
# 简写（不带交易所）
ctpprice.exe --channel SimNow-7x24 query ag2612,fu2612

# 带交易所前缀
ctpprice.exe --channel SimNow-7x24 query SHFE.fu2612,DCE.i2701,CFFEX.IF2612

# 混用
ctpprice.exe --channel SimNow-7x24 query SHFE.fu2612,ag2612
```

### 通道配置（brokers.xml、brokers_opt.xml）

`--channel` 的取值来自 `brokers.xml` 中定义的通道，配置文件里包含行情前置地址、BrokerID、认证信息等。切换通道只需换 `--channel` 名字，不用改命令行其他部分。

```bash
# 用另一个通道
ctpprice.exe --channel 生产通道 query ag2612

# 用另一份配置文件
ctpprice.exe --config my_brokers.xml --channel SimNow-7x24 query ag2612
```

---

## ctporder命令用法

ctporder命令支持查询与确认结算单、查询资金、持仓、订单、成交及下单撤单等功能。

```shell
> ctporder --help
ctporder -- ctp command-line trading tool


ctporder [OPTIONS] SUBCOMMAND


OPTIONS:
  -h,     --help              Show this help message
          --help-all          Show full help of all subcommands
  -v,     --version           show program's version and exit
          --no-pretty         no pretty json
          --flowpath TEXT (Env:CTPCMD_FLOWPATH)
                              flow path
          --config TEXT (Env:CTPCMD_CONFIG)
                              config file[brokers.xml]
          --channel TEXT REQUIRED (Env:CTPCMD_CHANNEL)
                              channel name
          --user TEXT REQUIRED (Env:CTPCMD_USER)
          --password TEXT REQUIRED (Env:CTPCMD_PASSWORD)

SUBCOMMANDS:
  subscribe                   Subscribe events
  query_settlement            QrySettlementInfo
  confirm_settlement          SettlementInfoConfirm
  query_confirm               QrySettlementInfoConfirm
  query_investor              QryInvestor
  query_code                  QryTradingCode
  query_account               QryTradingAccount
  query_position              QryInvestorPosition
  query_detail                QryInvestorPositionDetail
  query_order                 QryOrder
  query_trade                 QryTrade
  query_exchange              QryExchange
  query_product               QryProduct
  query_instrument            QryInstrument
  query_price                 QryDepthMarketData
  query_fee                   QryInstrumentCommissionRate
  query_optionfee             QryOptionInstrCommRate
  query_orderfee              QryInstrumentOrderCommRate
  query_margin                QryInstrumentMarginRate
  query_cashflow              QryTransferSerial
  query_register              QryAccountRegister
  query_bank                  QryTransferBank
  buy                         Order Buy
  sell                        Order Sell
  cancel                      Order Cancel
```

查询持仓、订单、合约、行情等子命令均有相应的子命令选项如`--instrument xxx`、`--exchange xxx`等以查询指定合约或交易所的数据。

```shell
> ctporder --channel SimNow-7x24 --user 058762 --password xxx query_position --instrument ag2701
```

## 输出格式

### 查询响应

```json
{
"rsp_code":0,
"rsp_message":"",
"data":
[{...},
{...}]
}
```

### 行情推送

```json
{
"event":"DepthMarketData",
"data":{...}
}
```

- `data`：查询行情响应为记录，data为数组，行情推送时为单记录，data为结构体{}，字段定义与 CTP数据结构定义完全一致
- `rsp_code`：`0` 表示成功
- `rsp_message`：成功时为空字符串

### 错误处理

```json
{"rsp_code":9999,"rsp_message":"Disconnected."}
```

所有错误都是同样的 JSON 外形，只有 `rsp_code` / `rsp_message` 不同 —— 上层脚本**不需要区分"正常输出"和"错误输出"，统一按行读 JSON，判断 `rsp_code` 即可**。

| rsp_code | 含义  |
| -------- | --- |
| `0`      | 成功  |
| `9999`   | 错误  |

## 字符集

ctpcmd响应的Json文本编码格式为UTF-8。

## --no-pretty

默认Json响应信息以美化格式显示，以便人工使用，如果需要程序获取并解析Json文本，请加--no-pretty命令行选项使命令以单行模式输出。

```json
> ctpprice --no-pretty --channel SimNow-7x24 query ag2612
{"rsp_code":0,"rsp_message":"","data":[{"ExchangeID":"","InstrumentID":"ag2612","LastPrice":10122.0,"OpenPrice":10020.0,"HighestPrice":10185.0,"LowestPrice":9637.0,"ClosePrice":0.0,"SettlementPrice":0.0,"AveragePrice":148710.60385022112,"Volume":249648,"Turnover":37125304830.0,"OpenInterest":85853.0,"PreSettlementPrice":10320.0,"PreClosePrice":10015.0,"PreOpenInterest":93721.0,"UpperLimitPrice":12384.0,"LowerLimitPrice":8256.0,"ActionDay":"20261123","UpdateTime":"00:32:32","UpdateMillisec":0,"TradingDay":"20261123","BidPrice1":10120.0,"BidVolume1":6,"BidPrice2":0.0,"BidVolume2":0,"BidPrice3":0.0,"BidVolume3":0,"BidPrice4":0.0,"BidVolume4":0,"BidPrice5":0.0,"BidVolume5":0,"AskPrice1":10124.0,"AskVolume1":2,"AskPrice2":0.0,"AskVolume2":0,"AskPrice3":0.0,"AskVolume3":0,"AskPrice4":0.0,"AskVolume4":0,"AskPrice5":0.0,"AskVolume5":0}]}
```

---

## 使用示例

### 示例一：Windows 批处理 + jq工具解析Json（查询行情快照）

`query_prices.bat`

```bat
chcp 65001
ctpprice.exe --no-pretty --channel SimNow-7x24 query ag2612,fu2612,CFFEX.IF2612,DCE.i2701 ^
  | jq ".data[] | {InstrumentID,LastPrice,UpdateTime,TradingDay}"

pause
```

`chcp 65001` 切换字符集以显示 UTF-8 中文信息。

提取结果：

```json
{
  "InstrumentID": "ag2612",
  "LastPrice": 12294,
  "UpdateTime": "00:00:53",
  "TradingDay": "20261106"
}
```

### 示例二：Python 订阅实时行情

`subscribe_prices.py`

```python
import json
import subprocess

proc = subprocess.Popen(
    [
        "ctpprice",
        "--no-pretty",
        "--channel", "SimNow-7x24",
        "subscribe",
        "ag2612,fu2612,CFFEX.IF2612,DCE.i2701",
    ],
    stdout=subprocess.PIPE,
    text=True,
)

for line in proc.stdout:
    line = line.strip()
    if not line or (not line.startswith("{") or not line.endswith("}")):
        continue
    msg = json.loads(line)
    if msg.get("event") == "DepthMarketData":
        tick = msg["data"]
        
        print({
            "InstrumentID": tick["InstrumentID"],
            "LastPrice": tick["LastPrice"],
            "UpdateTime": tick["UpdateTime"],
            "TradingDay": tick["TradingDay"],
        })
```

### 示例三：下单（命令行）

```batch
> ctporder --channel SimNow-7x24 --user 058762 --password xxx sell open 1 share of SHFE.ag2701 at 10500.0
Connect to 182.254.243.31:40001
Session -1512636415 Connected
{
  "rsp_code": 0,
  "rsp_message": "",
  "data": {
    "BrokerID": "9999",
    "UserID": "058762",
    "InvestorID": "058762",
    "ExchangeID": "SHFE",
    "InstrumentID": "ag2701",
    "FrontID": 1,
    "SessionID": -1512600288,
    "OrderRef": "1",
    "OrderSysID": "       20219"
  }
}
```

### 示例四：撤单（命令行）

```batch
> ctporder --channel SimNow-7x24 --user 058762 --password xxx cancel "       20219" of SHFE.ag2701
Connect to 182.254.243.31:40001
Session -1511129087 Connected
{
  "rsp_code": 0,
  "rsp_message": "",
  "data": {
    "BrokerID": "9999",
    "UserID": "058762",
    "InvestorID": "058762",
    "ExchangeID": "SHFE",
    "InstrumentID": "ag2701",
    "FrontID": 1,
    "SessionID": -1512600288,
    "OrderRef": "1",
    "OrderSysID": "       20219",
    "VolumeTraded": 0,
    "VolumeTotal": 1,
    "OrderStatus": "5",
    "StatusMsg": "已撤单"
  }
```

---

### 示例五：回报订阅（命令行）

```batch
>ctporder --channel SimNow-7x24 --user 058762 --password xxx subscribe quick
Connect to 182.254.243.31:40001
Session -1223098367 Connected
{
  "event": "Order",
  "data": {
    "BrokerID": "9999",
    "InvestorID": "058762",
    "OrderRef": "1",
    "UserID": "058762",
    "OrderPriceType": "2",
    "Direction": "1",
    "CombOffsetFlag": "0",
    "CombHedgeFlag": "1",
    "LimitPrice": 10500.0,
    "VolumeTotalOriginal": 1,
    "ExchangeID": "SHFE",
    "OrderSubmitStatus": "3",
    "OrderSysID": "       22865",
    "OrderStatus": "3",
    "VolumeTraded": 0,
    "VolumeTotal": 1,
    "InsertDate": "20261123",
    "InsertTime": "00:17:45",
    "FrontID": 1,
    "SessionID": -1222598518,
    "UserProductInfo": "ctpcmd",
    "StatusMsg": "未成交",
    "InstrumentID": "ag2701"
  }
}
```

---

## 编译

**Windows编译：**

打开Virtual Studio命令行用nmake进行编译。

```bash
nmake -f makefile.mk
```

**Linux与MacOS编译：**

直接make。

```bash
make
```

## 下载

可直接至openctp官网下载预编译程序：[ctpcmd工具链](http://www.openctp.cn/ctpcmd.html)

## License

BSD 3-Clause License
