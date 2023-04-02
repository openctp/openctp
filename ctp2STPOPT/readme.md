# CTP程序接入华鑫证券STP奇点股票期权柜台

openctp已经发布了华鑫证券STP奇点股票期权柜台的CTP兼容接口，以CTP接口对STPOPT接口进行封装，使得CTP程序无需任何修改，只是更换一下CTP动态库，就可以接入华鑫证券股票期权柜台ETF期权等商品。

openctp的动态库（dll、so等文件）只是对华鑫证券接口的简单封装，不是经过openctp的模拟服务器进行转发，而是直接调用华鑫证券的dll与柜台进行交互，所以登录用户名、密码均为华鑫证券柜台用户名、密码，模拟账户申请需至华鑫证券官网申请，该接入方式同样支持实盘。

当前版本基于的华鑫证券股票期权接口版本：API_C++_交易_v1.3.3_20220908。

## 接入方式
下载openctp相应CTP版本的dll，交易dll有两个文件，thosttraderapi_se.dll为openctp的封装dll，fastsptraderapi.dll为华鑫证券发布的接口dll，行情也同样是有两个，交易与行情的dll互相独立，可以只接交易或只接行情。

行情的dll请至openctp的华鑫证券股票接口目录下载，华鑫证券的股票、两融、期权柜台均使用同一套行情接口，这里不重复发布。

华鑫证券股票期权的7x24测试环境：

行情前置地址：tcp://210.14.72.16:9402

交易前置地址：tcp://210.14.72.17:15500

华鑫证券N视界模拟平台是跟simnow类似的证券模拟平台，采用与CTP类似的开放式API，更多信息请至官网了解：http://www.n-sight.com.cn/

[CTP开源客户端TextTrader](https://github.com/openctp/TextTrader/tree/master/Releases/Linux/TextTraderSTPOPT)的接入效果：
![image](https://user-images.githubusercontent.com/83346523/229337753-f0a7da00-4074-4ed2-99f7-1e82554eb9f3.png)
![image](https://user-images.githubusercontent.com/83346523/229337761-f0e483d8-0914-4a58-aac8-b9fddc1f4f17.png)
![image](https://user-images.githubusercontent.com/83346523/229337765-49bc3a7a-af8a-4704-b896-423622da1aa4.png)

