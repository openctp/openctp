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