# ctpprice

> 一个轻量、单文件、命令行直接调用的 CTP 行情工具。  
> 一条命令拿到合约的最新价、涨跌停价、昨结算价与五档盘口，输出标准 JSON，供脚本、策略和运维工具直接消费。

**和线上 `dict.openctp.cn/prices` 接口返回结构完全一致** —— 同一套解析代码，线上 HTTP 接口与本地 CTP 直连可以无缝切换，切换成本几乎为零。

---

## 为什么会有这个工具

日常写策略、做风控、跑批量校验的时候，往往只需要一件事：

> "把 fu2612、ag2612 这几个合约现在的价格给我，我拿来算保证金、校验涨跌停、核对昨结算。"

这件事用 CTP API 做起来不算难，但每次都要：

1. 拉一个行情 API 实例，登录、订阅；
2. 等 `OnRtnDepthMarketData` 回调把数据凑齐；
3. 写一堆结构体解析代码，把 30 多个字段转成自己想要的格式；
4. 处理断线、合约写错、非交易时段等等异常分支。

`ctpprice` 把这一整套封装成了一条命令：不用写 CTP 代码，不用管回调，标准输出直接给 JSON。

它作为 [openctp](http://www.openctp.cn) 生态里的一个小工具，设计目标是**低复杂度、低依赖、可脚本化**：一个 exe，一个配置文件，没有服务端、没有数据库、没有 Web 界面，跑完即退。

---

## 特性

- **两种模式**：`query` 一次性快照，`subscribe` 持续 Tick 推送
- **合约写法双兼容**：`ag2612`（简写）和 `SHFE.fu2612`（带交易所前缀）都认
- **批量查询**：一条命令传多个合约，逗号分隔
- **完整字段**：CTP `CThostFtdcDepthMarketDataField` 全字段输出，含五档买卖盘、持仓、成交额、涨跌停价
- **标准 JSON**：一行一条 JSON，管道给 `jq` / Python / 任何语言都能直接解析
- **格式对齐**：与 `dict.openctp.cn/prices` 报文结构一致，线上线下随时切
- **异常也有结构化输出**：断线、参数错误都返回带 `rsp_code` 的 JSON，不会只抛一句日志就崩掉
- **多通道**：通过 `brokers.xml` 配置多个行情前置通道，`--channel` 指定用哪个

---

## 快速开始

### 1. 获取程序

从 Release 页面下载预编译版本（Windows x64）：

```
ctpprice.exe
brokers.xml
```

两个文件放在同一个目录即可运行。

### 2. 运行

```bash
ctpprice.exe --channel SimNow-7x24 query ag2612,fu2612
```

输出（已格式化，实际是一行）：

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

## 命令行参数

```
ctpprice.exe [--config <file>] [--channel <name>] <query|subscribe> <instrument_list>
```

| 参数                  | 说明                            | 默认值           |
| ------------------- | ----------------------------- | ------------- |
| `--config <file>`   | 通道配置文件路径                      | `brokers.xml` |
| `--channel <name>`  | 使用哪个行情通道，取值来自配置文件中的 channel 名 | 配置文件中的默认通道    |
| `query`             | 子命令：一次性查询快照，返回后退出             | —             |
| `subscribe`         | 子命令：订阅并持续输出 Tick              | —             |
| `<instrument_list>` | 合约列表，逗号分隔，位置参数                | 必填            |

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

> 支持的前缀：`SHFE`、`DCE`、`CZCE`、`CFFEX`、`INE`、`GFEX`。

### 通道配置（brokers.xml）

`--channel` 的取值来自 `brokers.xml` 中定义的通道，配置文件里包含行情前置地址、BrokerID、认证信息等。切换通道只需换 `--channel` 名字，不用改命令行其他部分。

```bash
# 用另一个通道
ctpprice.exe --channel 生产通道 query ag2612

# 用另一份配置文件
ctpprice.exe --config my_brokers.xml --channel SimNow-7x24 query ag2612
```

---

## 输出格式

### 成功

```json
{"data":[{...},{...}],"rsp_code":0,"rsp_message":""}
```

- `data`：数组，每个合约一个对象，字段为 CTP 行情结构体全字段
- `rsp_code`：`0` 表示成功
- `rsp_message`：成功时为空字符串

### 异常

```json
{"rsp_code":9999,"rsp_message":"Disconnected."}
```

所有错误都是同样的 JSON 外形，只有 `rsp_code` / `rsp_message` 不同 —— 上层脚本**不需要区分"正常输出"和"错误输出"，统一按行读 JSON，判断 `rsp_code` 即可**。

| rsp_code | 含义  |
| -------- | --- |
| `0`      | 成功  |
| `9999`   | 错误  |

### 字段说明

`data[]` 中每个对象的字段（与 CTP `CThostFtdcDepthMarketDataField` 一一对应，按字母序输出）：

| 字段                        | 类型     | 说明                |
| ------------------------- | ------ | ----------------- |
| `TradingDay`              | string | 交易日               |
| `ActionDay`               | string | 自然日               |
| `UpdateTime`              | string | 更新时间 `HH:MM:SS`   |
| `UpdateMillisec`          | int    | 更新毫秒              |
| `InstrumentID`            | string | 合约代码              |
| `ExchangeID`              | string | 交易所代码（见下方说明）      |
| `LastPrice`               | double | 最新价               |
| `PreClosePrice`           | double | 昨收盘               |
| `OpenPrice`               | double | 今开盘               |
| `HighestPrice`            | double | 最高价               |
| `LowestPrice`             | double | 最低价               |
| `PreSettlementPrice`      | double | 昨结算               |
| `SettlementPrice`         | double | 今结算（盘中通常为 0）      |
| `ClosePrice`              | double | 收盘价（盘中通常为 0）      |
| `PreOpenInterest`         | double | 昨持仓量              |
| `OpenInterest`            | double | 持仓量               |
| `Volume`                  | int    | 成交量               |
| `Turnover`                | double | 成交额               |
| `AveragePrice`            | double | 均价（部分品种为隐含值，仅供参考） |
| `UpperLimitPrice`         | double | 涨停价               |
| `LowerLimitPrice`         | double | 跌停价               |
| `BidPrice1`~`BidPrice5`   | double | 买一至买五价            |
| `BidVolume1`~`BidVolume5` | int    | 买一至买五量            |
| `AskPrice1`~`AskPrice5`   | double | 卖一至卖五价            |
| `AskVolume1`~`AskVolume5` | int    | 卖一至卖五量            |

> **关于 `ExchangeID`**：该字段取自 CTP 回调原值，部分柜台返回空字符串。工具不做额外推断，柜台给什么就输出什么；需要交易所信息时以自己传入的合约前缀为准。

> **关于五档为 0**：SimNow 及部分模拟环境只推送一档盘口，`BidPrice2`~`5`、`AskPrice2`~`5` 为 0 属正常现象，不是解析问题。生产环境 CTP 五档为完整值。

---

## 使用示例

### 示例一：Windows 批处理 + jq（单次查询）

`query_prices.bat`

```bat
@echo off
chcp 65001 >nul
ctpprice.exe --channel SimNow-7x24 query ag2612,fu2612,CFFEX.IF2612,DCE.i2701 ^
  | jq ".data[] | {InstrumentID,LastPrice,UpdateTime,TradingDay}"
echo.
pause
```

`chcp 65001` 保证中文与 UTF-8 输出不乱码；`pause` 防止窗口一闪而过。

提取结果：

```json
{
  "InstrumentID": "ag2612",
  "LastPrice": 12294,
  "UpdateTime": "00:00:53",
  "TradingDay": "20261106"
}
```

> 没有安装 `jq` 的话，直接去掉 `| jq ...` 部分，输出完整原始 JSON。`jq` 是 GitHub 上的单文件 exe（`jq-windows-amd64.exe`），下载后改名为 `jq.exe` 放到同目录即可，无需安装。
> 注意：Windows 批处理里 jq 表达式外层用**双引号**（Linux/PowerShell 下用单引号）。

### 示例二：Python 订阅 Tick

`subscribe_prices.py`

```python
import json
import subprocess

proc = subprocess.Popen(
    [
        "ctpprice.exe",
        "--channel", "SimNow-7x24",
        "subscribe",
        "ag2612,fu2612,CFFEX.IF2612,DCE.i2701",
    ],
    stdout=subprocess.PIPE,
    text=True,
)

for line in proc.stdout:
    line = line.strip()
    if not line:
        continue
    tick = json.loads(line)
    if tick["rsp_code"] != 0:
        print("行情异常：", tick["rsp_message"])
        break
    for item in tick["data"]:
        print({
            "InstrumentID": item["InstrumentID"],
            "LastPrice": item["LastPrice"],
            "UpdateTime": item["UpdateTime"],
            "TradingDay": item["TradingDay"],
        })
```

> `subprocess` 列表参数里，`--channel` 和它的值必须拆成两个元素。写成 `"--channel SimNow-7x24"` 会被当成一个完整参数，程序认不出来。

### 示例三：Python 单次查询 + 断线重连

```python
import json
import subprocess
import time


def query(instruments):
    cmd = ["ctpprice.exe", "--channel", "SimNow-7x24", "query", instruments]
    out = subprocess.run(cmd, capture_output=True, text=True).stdout.strip()
    if not out:
        return None
    return json.loads(out)


while True:
    msg = query("ag2612,fu2612")
    if msg and msg["rsp_code"] == 0:
        for item in msg["data"]:
            print(item["InstrumentID"], item["LastPrice"], item["UpperLimitPrice"])
        break
    print("查询失败，3 秒后重试：", msg and msg["rsp_message"])
    time.sleep(3)
```

### 示例四：涨跌停与保证金校验

```python
price = item["LastPrice"]
upper = item["UpperLimitPrice"]
lower = item["LowerLimitPrice"]

if price >= upper * 0.995:
    print(f"{item['InstrumentID']} 逼近涨停 {price}/{upper}")
elif price <= lower * 1.005:
    print(f"{item['InstrumentID']} 逼近跌停 {price}/{lower}")
```

---

## 常见问题

**Q：订阅了一个写错的合约，为什么没有任何报错？**

CTP 原生行情前置的 `SubscribeMarketData` 只表示"订阅报文投递成功"，**不校验合约是否存在**。合约代码写错、已摘牌时，应答依然返回成功，只是永远不会推送 `OnRtnDepthMarketData`，看起来就是"没反应"。

- 使用 **TTS 柜台**：无效合约会直接返回"合约不存在"，可以立即识别；
- 使用 **原生 CTP 前置**：需要靠"超时未收到行情"来判断，并按自己业务逻辑处理；

**Q：`query` 一直没有返回？**

`query` 需要等待每个合约的首次行情回推才输出。常见原因：

1. 合约代码写错或不存在的合约（见上一条，永远等不到）；
2. 当前非交易时段，没有 Tick 推送（夜盘/日盘之外查询会卡住）；
3. 通道地址填错或网络不通（此时应返回 `rsp_code 9999`）。

建议在用 `query` 前确认：合约代码正确、当前处于该品种交易时段。

**Q：五档盘口后面的档位全是 0？**

模拟环境（如 SimNow）多数只推一档，属正常现象。

**Q：输出中文乱码 / JSON 解析失败？**

Windows 控制台先执行 `chcp 65001`（批处理里加在首行）。另外 `subscribe` 模式下每条消息都是一行完整 JSON，按行拆分解析，不要按字节流随意切。

**Q：`instruments is required` 报错？**

合约列表必须跟着子命令一起给，形如 `query ag2612,fu2612`，不能只写 `query`。

---

## 编译

**Windows编译：**

直接打开vs工程进行编译。

**Linux与MacOS编译：**

直接make。

```bash
make
```

## 下载

可直接至openctp官网下载编译好的可执行文件：[ctpcmd工具链](http://www.openctp.cn/ctpcmd.html)

## 说明

- 本工具是**本地自用命令行工具**，用于策略开发、风控校验、盘前盘后参数核对；
- 行情数据仅在本地使用，不对外分发、不对外提供行情服务；
- 需要线上可调用的静态基准参数接口，请使用 `dict.openctp.cn/prices`（本工具输出结构与其一致）。

## 相关

- openctp：<http://www.openctp.cn>
- 线上价格接口：`http://dict.openctp.cn/prices`

## License

BSD 3-Clause License
