# CTP程序接入易盛TAP启明星柜台

TAP启明星柜台是郑商所旗下技术公司易盛开发的期货交易柜台，支持上期、中金、大连、郑州、广州及上海黄金交易所品种，

## 模拟账号注册
https://www.esunny.com.cn/market/invol

## 模拟环境
#### 前置地址
- 交易前置-电信：123.161.206.213:6160
- 行情前置-电信：123.161.206.213:6161
- 交易前置-联通：61.163.243.173:6160
- 行情前置-联通：61.163.243.173:6161

#### 模拟环境运行状态
http://www.openctp.cn/

## 易盛官方接口下载
https://www.esunny.com.cn/market/info/155

## CTPAPI兼容接口
openctp开发的CTPAPI转接口，CTP程序只需更换ctp的交易和行情dll即可对接到易盛TAP柜台，程序无需重新编译，[ViTrader](https://github.com/openctp/ViTrader)、[MiniTrader](https://github.com/openctp/MiniTrader)均采用这样的方式对接易盛柜台的。

#### 认证信息
- BrokerID: 不需要填。
- AppID: Demo_TestCollect
- AuthCode: Demo_TestCollect

#### 下载地址
http://www.openctp.cn/download.html

## ViTrader接入易盛柜台
<img width="867" alt="微信图片_20240605004653" src="https://github.com/openctp/openctp/assets/83346523/b2dc77ee-b9e6-48c7-9832-f5cb782eb3b0">
<img width="443" alt="微信图片_20240605004717" src="https://github.com/openctp/openctp/assets/83346523/fbd78676-0eb8-4614-a80e-540076ff445f">
<img width="868" alt="微信图片_20240605004725" src="https://github.com/openctp/openctp/assets/83346523/39a726f9-2d57-47b4-aa1f-b3f813372900">

## MiniTrader接入易盛柜台
<img width="540" alt="MiniTrader易盛" src="https://github.com/openctp/openctp/assets/83346523/b908203a-e3da-4e25-b5d3-c1c6851f4aea">

## 技术交流
QQ群：127235179

## 文章
- [发布易盛TAP柜台CTPAPI兼容接口](https://mp.weixin.qq.com/s?__biz=Mzk0ODI0NDE2Ng==&mid=2247485322&idx=1&sn=ee64ebd1f7f02eaf4389958094caedb3&chksm=c36bdc23f41c5535db8de4be76b107f2c84a5c08d29421d32c036b9582f0779323dd0156152c&token=2002405740&lang=zh_CN#rd)
- [易盛柜台CTPAPI开发过程中的点滴](https://mp.weixin.qq.com/s?__biz=Mzk0ODI0NDE2Ng==&mid=2247485300&idx=1&sn=adfa7d261f6093eee8f2ef829784174e&chksm=c36bdcddf41c55cb432e7417b32eb6c62f3b325d3ab54478f0208736dbab58ed77b8d673ac3b&token=2002405740&lang=zh_CN#rd)
- [xxxprint系列demo增加易达、易盛版](https://mp.weixin.qq.com/s?__biz=Mzk0ODI0NDE2Ng==&mid=2247485259&idx=1&sn=c94e49cbea39c1bc376c981c8c81f2e8&chksm=c36bdce2f41c55f47589d35a2a9dd3e5fa7a2517187d35316299c44968c05b0be1458a40f6e6#rd)
- [openctp的产品与服务](https://zhuanlan.zhihu.com/p/683874612)
- [如何使用CTP开放平台提供的各项能力](https://mp.weixin.qq.com/s?__biz=Mzk0ODI0NDE2Ng==&mid=2247484094&idx=1&sn=97bd791622333886260bf767bea40db1&chksm=c36bd917f41c50016b676b5f5b11f899aea889cd9b10e6724c7fee0ad443f31351f87ff5a4d2&token=1437331958&lang=zh_CN#rd)
