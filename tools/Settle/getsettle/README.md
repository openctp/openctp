## ctpsettle
该脚本用于查询结算单，用法如下:
1. 从[ctpapi-python](https://github.com/krenx1983/openctp/tree/master/ctpapi-python)复制ctpapi-python库(具体用法请查看ctpapi-python的README文档)到脚本目录下
2. 运行脚本，命令如下:
```
# windows
python ctpsettle.py -u <user> -p <password> -d <date>

# Linux
LD_LIBRARY_PATH=./ python ctpsettle.py -u <user> -p <password> -d <date>
```

## 更多用法
```
python ctpsettle.py -h   # 查看帮助

options
-a          指定交易前置的地址，也可通过CTP_TRADE_FRONT环境变量进行指定
-b          指定BrokerID，也可以通过CTP_BROKER环境变量进行指定，默认9999
-u          指定用户ID，也可以通过CTP_USER环境变量进行指定
-p          指定密码，也可以通过CTP_PASSWORD环境变量进行指定
--appid     指定App ID，也可以通过CTP_APP_ID环境变量进行指定，默认simnow_client_test
--authcode  指定Auth Code, 也可以通过CTP_AUTH_CODE环境变量进行指定，默认0000000000000000
-v          打印详细日志
--raw       打印原始的结算单，默认为输出json格式的结算单
```

## 文件说明
ctpsettle.py 为查询结算单脚本

testctpsettle.py 为功能性测试脚本或者说代码调用的demo

sample.out 为结算单的原始样式

## 已知问题
目前已经发现在simnow环境查询结算单时，某些日期的结算单可能会丢失某些数据导致脚本报错。这个问题目前还不能确定是CTP SDK的问题还是swig编译的ctpapi-python的问题。
