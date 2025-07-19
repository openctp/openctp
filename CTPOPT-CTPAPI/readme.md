# CTP程序接入CTP股票期权柜台

CTP股票期权柜台是上期技术开发的支持上交所及深交所股票期权品种交易的柜台，延用了CTP柜台开发技术，对于CTP开发者来说很容易即可将CTP程序牵移到CTP股票期权柜台，尤其是openctp提供了CTP程序无缝接入CTP股票期权柜台的方法，只需要换一个dll即可。

## 模拟账号申请

不同于CTP柜台有SimNow那样的统一测试环境，CTP股票期权接口的测试环境由各期货公司自己独立运维，因此也需要向各期货公司申请账号。与CTP柜台不同，支持CTP股票期权柜台的期货公司不多，并且模拟账号也不太好申请，我们合作的宏源期货提供了CTP股票期权柜台，并且较容易申请模拟账号，可联系工作人员微信：qic7xi，或联系openctp申请。



openctp也提供了CTP股票期权接口的测试环境，与CTPAPI接口测试一样，我们也提供了CTP股票期权柜台API的兼容接口，也是换一下dll即可对接到openctp模拟环境进行股票期权接口的测试。

## **宏源期货CTP股票期权仿真环境：**

- 交易前置：tcp://118.26.194.228:42205
- 行情前置：tcp://118.26.194.228:42213

## **兴证期货CTP股票期权仿真环境（电信）：**

- 交易前置：tcp://58.32.234.179:46666
- 行情前置：tcp://58.32.234.179:47777

## **兴证期货CTP股票期权仿真环境（联通）：**

- 交易前置：tcp://58.247.2.86:46666
- 行情前置：tcp://58.247.2.86:47777

## 模拟环境状态监控

[http://www.openctp.cn/](http://www.openctp.cn/)

## CTP股票期权API兼容接口

openctp做了CTP股票期权API兼容接口，CTP股票期权程序只需更换交易和行情dll即可对接到openctp模拟环境，程序无需重新编译。

## CTP股票期权柜台CTPAPI兼容接口

openctp做了CTP股票期权柜台CTPAPI兼容接口，CTP程序只需更换交易和行情dll即可对接到CTP股票期权柜台，程序无需重新编译。

#### 认证信息：

- BrokerID: 需申请。
- AppID: 需申请。
- AuthCode: 需申请。

#### 下载地址：

[CTP股票期权柜台API及CTPAPI兼容接口下载](http://www.openctp.cn/download.html)

## 技术交流

QQ群：127235179

## ViTrader接入CTP股票期权柜台

![image](https://github.com/user-attachments/assets/96d29dd1-ef7b-40c7-94db-d9016c24bc39)

## MiniTrader接入CTP股票期权柜台

![image](https://github.com/user-attachments/assets/ce69ccd5-8be8-44da-b89f-e68f9c47e53b)

## 相关文章

- [发布QDP极速柜台CTPAPI](https://mp.weixin.qq.com/s?__biz=Mzk0ODI0NDE2Ng==&mid=2247485377&idx=1&sn=5149412546fbb3d6acb96e4154adcf53&chksm=c36bdc68f41c557e3c7caacaf662b9983c37f9f1004cb9dda2b3da3c009cf7b947c46260329a&token=2114132773&lang=zh_CN#rd)
- [openctp的产品与服务](https://zhuanlan.zhihu.com/p/683874612)
- [如何使用CTP开放平台提供的各项能力](https://mp.weixin.qq.com/s?__biz=Mzk0ODI0NDE2Ng==&mid=2247484094&idx=1&sn=97bd791622333886260bf767bea40db1&chksm=c36bd917f41c50016b676b5f5b11f899aea889cd9b10e6724c7fee0ad443f31351f87ff5a4d2&token=1437331958&lang=zh_CN#rd)
- [发布量投QDP极速柜台接口demo](https://mp.weixin.qq.com/s?__biz=Mzk0ODI0NDE2Ng==&mid=2247485329&idx=1&sn=913785be3306908909ce3a160abfb18c&chksm=c36bdc38f41c552e35ba6c39e4b1addb6f4aee4ece068f697a11b1c5f264cc30f7bab4c516ed&token=2114132773&lang=zh_CN#rd)
- [MiniTrader新版支持CTP股票期权及QDP柜台](https://mp.weixin.qq.com/s?__biz=Mzk0ODI0NDE2Ng==&mid=2247485364&idx=1&sn=1715660a76ec62651b3504141f9f32f5&chksm=c36bdc1df41c550b40d2c9cab250871df00e2743be65965b73640d8ffd64f1567055e9cb4576&token=2114132773&lang=zh_CN#rd)
- [CTP接口量化交易资料汇总](https://zhuanlan.zhihu.com/p/607325008)
- [量化交易数据接口汇总](https://zhuanlan.zhihu.com/p/681814762)
