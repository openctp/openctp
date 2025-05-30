# **openctp（Powered by TTS - Tick Trading System）**

[openctp](http://www.openctp.cn)是一个以CTP生态为依托的技术服务平台，既提供了华鑫证券奇点、中泰证券XTP、东方财富EMT、东方证券OST等柜台的[CTPAPI](http://openctp.cn/CTPAPI.html)兼容接口，也提供了一套与上期技术SimNow模拟环境类似的模拟环境，也支持CTPAPI接口，不仅提供国内各期货交易所的期货与期权品种模拟交易，还提供了A股的股票、基金、债券以及股票期权模拟交易，也支持港股、美股等市场模拟交易。

openctp还提供了[CTPAPI的Python接口](https://github.com/openctp/openctp-ctp-python)以及[CTP股票期权API的Python接口](https://github.com/openctp/openctp-ctpopt-python)，开源了CTP命令行交易客户端[ViTrader](https://github.com/openctp/openctp/tree/master/tools/ViTrader)，还有图形界面交易客户端[TickTrader](http://www.openctp.cn/TickTrader.html)，以及Mini版的[TickTraderMini](http://www.openctp.cn/TickTrader.html)都支持openctp、CTP、CTP股票期权、中泰XTP、华鑫奇点股票与股票期权等柜台，[TickTraderMini](http://www.openctp.cn/TickTrader.html)采用openctp的CTPAPI兼容接口技术支持了CTP、TTS、华鑫证券股票与股票期权等柜台，无需自己再替换dll。

openctp还提供了CTP、华鑫奇点、中泰XTP等柜台接口的开发咨询和培训以及柜台系统等的开发培训服务。

![CTPAPI兼容接口结构图](https://github.com/user-attachments/assets/5974ae64-ae18-4f2a-b459-d5f73243037a)

# 目录结构：

- [ctp2TTS](https://github.com/openctp/openctp/tree/master/ctp2TTS)：openctp模拟环境CTPAPI兼容接口。
- [ctpopt2TTS](https://github.com/openctp/openctp/tree/master/ctpopt2TTS)：openctp模拟环境CTP股票期权API兼容接口。
- [ctp2CTPOPT](https://github.com/openctp/openctp/tree/master/ctp2CTPOPT)：CTP股票期权柜台CTPAPI兼容接口。
- ctp2XTP：中泰证券XTP柜台CTPAPI兼容接口（含源码）。
- ctp2STP：华鑫证券TORA奇点股票柜台CTPAPI兼容接口（含源码）。
- ctp2EMT：东方财富EMT柜台CTPAPI兼容接口（含源码）。
- ctp2STPOPT：华鑫证券TORA奇点股票期权柜台CTPAPI兼容接口。
- ctp2OST：东方证券OST柜台CTPAPI兼容接口。
- ctp2YD：易达柜台CTPAPI兼容接口。（易达官方提供）
- ctp2IB：盈透证券TWS平台CTPAPI兼容接口。
- ctp2QDP：量投QDP柜台CTPAPI兼容接口。
- ctp2TAP：易盛TAP启明星柜台CTPAPI兼容接口。
- ctp2QQ：腾讯行情CTPAPI兼容接口（含源码）。
- ctp2Sina：新浪行情CTPAPI兼容接口（含源码）。
- demo：CTPAPI开发相关的demo及工具源码。
- tools：生产力工具。
- docs：开发文档及行业资料。
- [ctpapi-python](https://github.com/openctp/openctp-ctp-python)：CTPAPI的Python接口（openctp官方开发）。
- [ctpapi-opt-python](https://github.com/openctp/openctp-ctpopt-python)：CTP股票期权API的Python接口（openctp官方开发）。
- ctpapi-java：CTPAPI的Java接口。
- ctpapi-go：CTPAPI的Go接口。
- ctpapi-c：CTPAPI的C语言接口。
- ctpapi-rust：CTPAPI的Rust语言接口。
- ctpapi-csharp：CTPAPI的C#语言接口。
- widgets：图形界面小应用。 

# CTPAPI接口下载：

[CTPAPI接口下载](http://www.openctp.cn/CTPAPI.html)

# openctp模拟环境

openctp提供了3套CTPAPI兼容接口模拟环境，分别为7x24环境、仿真环境、vip仿真环境，具体信息见：[模拟交易](http://openctp.cn/Trading.html)。

# CTPAPI策略交易框架

CTPAPI接口专业性很强，原生接口开发有一定难度，持仓与资金的实时计算也很难处理，各种持仓与资金字段的冻结、计算等，openctp给出了一套轻量的Tick级CTPAPI策略交易框架源码，保持了原汁原味的CTP数据结构，代码很漂亮，不到5000行，简洁易懂，二次开发很容易，更多介绍见：[CTPAPI策略交易框架](http://openctp.cn/TTF.html)。

# openctp培训服务

openctp提供证券期货交易开发方面的技术培训，也提供通用的基础技术培训，openctp的培训偏向于就业方向，比如想去私募或者科技公司从事量化或者柜台系统开发的比较适合，当然如果想自己学习一些技术帮助自己更好地做交易也是可以的。openctp的培训是迭代式的，会不断更新，补充更多的内容，同学可长期在相应课程的群内交流，具体见：[培训](http://openctp.cn/Learning.html)。

## openctp公开课

openctp做了一些免费的0基础学习课程，帮助更多朋友进入到软件编程与证券期货交易行业。

- [C语言公开课](https://www.bilibili.com/video/BV1CK411o743)：以生动有趣的方式讲C语言基础性编程技术，重在兴趣培养和信心建立。
- C++语言公开课：以生动有趣的方式讲C++语言基础性编程技术，课程在准备中。
- [Linux环境编程公开课](https://www.bilibili.com/video/BV1Jw411E7sF)：介绍Unix&Linux的前世今世，讲Shell、VI编辑器等使用，讲netstat、traceroute、ifconfig、lsof等网络工具的使用，讲正则表达式等等，0基础，谁都能听得懂。

# 技术交流

- QQ群：564385877
- 微信群+v：openctp_helper

# openctp官网

[www.openctp.cn](http://www.openctp.cn/)

# openctp公众号

<img src="https://user-images.githubusercontent.com/83346523/225707613-59293970-0f04-4056-8ea4-dd4596a4efec.png" alt="微信公众号" width="300" height="350" />

# 精品文章：

- [如何使用CTP开放平台提供的各项能力](https://mp.weixin.qq.com/s?__biz=Mzk0ODI0NDE2Ng==&mid=2247484094&idx=1&sn=97bd791622333886260bf767bea40db1&chksm=c36bd917f41c50016b676b5f5b11f899aea889cd9b10e6724c7fee0ad443f31351f87ff5a4d2&token=1790747698&lang=zh_CN#rd)
- [CTP接口开发“葵花宝典”](https://zhuanlan.zhihu.com/p/397359483)
- [CTP接口支持pip install](https://zhuanlan.zhihu.com/p/622959788)
- [CTP接口量化交易资料汇总](https://zhuanlan.zhihu.com/p/607325008)
- [开放腾讯行情CTPAPI接口源码](https://mp.weixin.qq.com/s?__biz=Mzk0ODI0NDE2Ng==&mid=2247484606&idx=1&sn=270ba6034d9e45334642236dc315b16e&chksm=c36bdf17f41c56011a5a3bf974022c13f53b21b0cad35d43ea85130748152b4f0739e02f7a0e&token=55513683&lang=zh_CN#rd)
- [开放新浪行情CTPAPI接口源码](https://zhuanlan.zhihu.com/p/585724196)
- [CTP程序无缝接入华鑫证券奇点柜台（CTP2STP）](https://mp.weixin.qq.com/s?__biz=Mzk0ODI0NDE2Ng==&mid=2247483843&idx=1&sn=fdb033a68e9f803183d902dcf92f969b&chksm=c36bda6af41c537c6ed262923f2ee9a4cccb1b02821b918382e51a299cca81556bdb4302cdd3&scene=21#wechat_redirect)
- [发布华鑫证券奇点柜台股票期权CTPAPI](https://mp.weixin.qq.com/s?__biz=Mzk0ODI0NDE2Ng==&mid=2247484767&idx=1&sn=34fc5c6b270cf8c8bdc37981df4ae8e1&chksm=c36bdef6f41c57e075460fca8d670db17310e7d832a240aa37fa0f4666ba92672aa179d8f0dd&token=1435234803&lang=zh_CN#rd)
- [开放华鑫证券奇点柜台行情CTPAPI接口源码](https://mp.weixin.qq.com/s?__biz=Mzk0ODI0NDE2Ng==&mid=2247484647&idx=1&sn=03bef5f9f71ecd879c3520de2564f8dd&chksm=c36bdf4ef41c565895c10adaa558d6ac471ac5003791cbe301771c8884757cef13400e09ca5b&token=1847931716&lang=zh_CN#rd)
- [发布一批行情显示工具（命令行版）](https://mp.weixin.qq.com/s?__biz=Mzk0ODI0NDE2Ng==&mid=2247484039&idx=1&sn=794a13777cb358e01c175439e022d99b&chksm=c36bd92ef41c5038224f3b38740b001ef3b36bec89b0ccede51a446039fd1fa679ff7b4bc3b5&token=1790747698&lang=zh_CN#rd)
- [openctp培训与咨询服务](https://mp.weixin.qq.com/s?__biz=Mzk0ODI0NDE2Ng==&mid=2247484610&idx=1&sn=b7317eb127d22fd52958a41e40121b06&chksm=c36bdf6bf41c567d4f3c16454fc1f5ff2a22f567d893ea35a2135c082b78ce5d01d944b086e4&token=55513683&lang=zh_CN#rd)

<u>*注：openctp不对模拟交易及相关服务作任何保证，使用openctp产品进行实盘交易的后果完全由使用者自己承担。*</u>

# 友情推荐

- [QUANTAXIS（量化交易框架，支持股票、期货、期权，支持回测、多账户等特性。）](https://github.com/yutiansut/QUANTAXIS)
- [KLineChart（基于 html5 canvas 构建的轻量级金融图表。）](https://github.com/klinecharts/KLineChart)
