# CTP程序接入华鑫证券TORA奇点柜台

openctp已经发布了华鑫证券TORA奇点柜台的CTP兼容接口，以CTP接口对TORA接口进行封装，使得CTP程序无需任何修改，只是更换一下CTP动态库，就可以接入华鑫证券柜台交易股票、债券、ETF期权等商品。

openctp的动态库（dll、so等文件）只是对华鑫证券接口的简单封装，不是经过openctp的模拟服务器进行转发，而是直接调用华鑫证券的dll与柜台进行交互，所以登录用户名、密码均为华鑫证券柜台用户名、密码，模拟账户申请需至华鑫证券官网申请，该接入方式同样支持实盘。

当前发布的版本基于的华鑫证券股票接口版本：

API_C++_行情_v1.0.8_20241220

API_C++_交易_v4.1.3_20250415

## 接入方式

下载相应CTP版本的dll，交易dll有两个文件，thosttraderapi_se.dll为模拟平台的封装dll，fasttraderapi.dll为华鑫证券发布的接口dll，行情也同样是有两个，交易与行情的dll互相独立，可以只接交易或只接行情。

华鑫证券股票柜台的7x24测试环境：

行情前置地址：tcp://210.14.72.16:9402

交易前置地址：tcp://210.14.72.15:4400

华鑫证券N视界模拟平台是跟simnow类似的证券模拟平台，采用与CTP类似的开放式API，更多信息请至官网了解：http://www.n-sight.com.cn/

# 

## 注意事项

- 华鑫的下单与撤单共用一个OrderRef机制，即下单请求的OrderRef与撤单请求的OrderActionRef都要保持同一个序列，或者都填0让柜台自动赋值，可以参照TextTrader中的代码。
- 如果使用域名访问，华鑫的RegisterFensUserInfo接口需要一些额外信息，我们把这些信息组织到名字服务器的地址中了，地址要这样写：tcp://ip:port/EnvID/NodeID，如果你的服务器是部署在18号柜，地址就是这样：tcp://10.166.32.37:42370/stock/18
- 我们封装的时候借用了Login请求中的一些字段，如将硬盘序列号填在了LoginRemark字段，赋值给华鑫接口的TerminalInfo是这么写的：snprintf(LoginReq.TerminalInfo,sizeof(LoginReq.TerminalInfo),"PC;IIP=NA;IPORT=NA;LIP=%s;MAC=%s;HD=%s;@%s", pReqUserLogin->ClientIPAddress,pReqUserLogin->MacAddress,pReqUserLogin->LoginRemark,pReqUserLogin->UserProductInfo);

## TextTrader

[CTP开源客户端ViTrader](https://github.com/openctp/openctp/tree/master/widgets/ViTrader)的接入效果：
![M8$B1FGSOB 3A) T7%PUP P](https://user-images.githubusercontent.com/83346523/128633288-e70f2af9-7106-46a8-bda1-4859c61adf5b.png)
![KLU1WTF~M{{K2VGA28TX VL](https://user-images.githubusercontent.com/83346523/128633135-5173ffa0-762f-40a6-8cbd-74eae4105e06.png)
![$`}{JD~M_S {C4Y9T@O`LQ6](https://user-images.githubusercontent.com/83346523/128633324-471c81f8-8b56-47bb-a9f7-c52c7a1843c6.png)
![Q8U5YDF$4)VSBLX9A5W%U6N](https://user-images.githubusercontent.com/83346523/128633163-c7b532d9-6cbd-4abf-83fa-e9b34d59c112.png)
![F}X6O 2{E83J4OF8XJ)~4AV](https://user-images.githubusercontent.com/83346523/128633183-cf372e87-fa11-40cb-a34d-bc9c562b2bf7.png)
![)Y96T659_YW Y_QZHBUW@}Q](https://user-images.githubusercontent.com/83346523/128633169-94942480-c4bf-4e98-b554-2c3496c0956e.png)
