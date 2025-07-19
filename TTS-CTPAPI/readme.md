# CTP程序接入TTS柜台

TTS柜台是openctp自研的一套股票、期货、期权集中交易柜台，支持CTPAPI兼容接口，CTP程序只需要替换CTPAPI同版本（如6.3.15）dll/so文件即可接入TTS柜台，TTS柜台采用与CTP相似的内存数据库总线架构，支持QUICK、RESUME、RESTART各个流订阅模式，委托回报、成交回报等数据推送流程也均与CTP柜台一致。



## SDK接口

到[openctp官网](http://www.openctp.cn/)下载TTS柜台相应CTPAPI版本的开发包，有交易及行情两个接口，开发方式与CTPAPI一致，可参考CTPAPI相关接口文档。



## 撮合机制

除支持SimNow的做市机制外，openctp还提供了与实盘一致的撮合机制，即可以客户与客户之间成交，便于按自己想要的过程进行测试，仅限于7x24环境的几个合约：TEST、BTC、MINUS，仿真环境均使用做市模式，即以实盘盘口对用户的订单进行撮合，大于等于叫卖价的买单立即成交，小于等于叫买价的卖单立即成交，否则挂在队列中等行情符合条件的时候成交。



## openctp-7x24测试环境

7x24循环回放最近一个交易日行情，主要用于开发调试程序。

交易前置：tcp://121.37.80.177:20002

行情前置：tcp://121.37.80.177:20004

BrokerID：无

AuthCode：无

AppID：无



## openctp-仿真环境

交易时段与实盘一致，主要用于验证策略的实盘效果、培训演示等，支持国内各证券、期货交易所股票、期货及期权全品种合约仿真交易。

交易前置：tcp://121.37.90.193:20002

行情前置：openctp不提供实盘行情推送服务，期货及期权实盘行情可使用CTP官方dll连接实盘柜台（无需账号），实盘柜台地址参见：[CTP实盘环境](http://openctp.cn/env.html)。

BrokerID：无

AuthCode：无

AppID：无



## openctp-vip仿真环境

功能与免费的仿真环境相同，另外还支持etf期权等品种仿真交易，支持CTP股票期权API兼容接口，独立环境，带宽足够高，仿真效果更好，付费环境的可靠性也比免费环境更高，适合对仿真效果有较高要求的用户，费用为500元一年，可注册3个模拟号，如需要更多账号每加一个多100元，有需要的请加微信联系：openctp_helper



## openctp模拟账号密码

openctp对所有模拟账号进行统一管理，所有账号共享一个密码，也就是由同一个微信号注册的模拟号密码是共享的，任意修改其中一个账号的密码即可，可使用MiniTrader等CTP客户端修改密码。



## ViTrader

[CTP交易客户端ViTrader](http://openctp.cn/download.html)的接入效果：
![image](https://user-images.githubusercontent.com/83346523/229337753-f0a7da00-4074-4ed2-99f7-1e82554eb9f3.png)
![image](https://user-images.githubusercontent.com/83346523/229337761-f0e483d8-0914-4a58-aac8-b9fddc1f4f17.png)
![image](https://user-images.githubusercontent.com/83346523/229337765-49bc3a7a-af8a-4704-b896-423622da1aa4.png)
