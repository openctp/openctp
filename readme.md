# **openctp**

[openctp](http://www.openctp.cn)是一个以CTP生态为依托的技术服务平台，既提供了华鑫证券奇点、中泰证券XTP、东方财富EMT、东方证券OST等柜台的[CTPAPI](http://openctp.cn/CTPAPI.html)兼容接口，也提供了一套与上期技术SimNow模拟环境类似的模拟环境，也支持CTPAPI接口，不仅提供国内各期货交易所的期货与期权品种模拟交易，还提供了A股的股票、基金、债券以及股票期权模拟交易，也支持港股、美股等市场模拟交易。

openctp提供了[CTPAPI的Python接口](https://github.com/openctp/openctp/tree/master/ctpapi-python)以及[CTP股票期权API的Python接口](https://github.com/openctp/openctp/tree/master/ctpopt-python)，CTPAPI命令行交易客户端[ViTrader](https://github.com/openctp/openctp/tree/master/widgets/ViTrader)，还有图形界面交易客户端[TickTrader](http://www.openctp.cn/TickTrader.html)，以及Mini版的[TickTraderMini](http://www.openctp.cn/TickTrader.html)都支持openctp、CTP、CTP股票期权、中泰XTP、华鑫奇点股票与股票期权等柜台，[TickTraderMini](http://www.openctp.cn/TickTrader.html)采用openctp的CTPAPI兼容接口技术支持了CTP、TTS、华鑫证券股票与股票期权等柜台，无需自己再替换dll。

openctp还提供了CTP、华鑫奇点、中泰XTP等柜台接口的开发咨询和培训以及柜台系统等的开发培训服务。
![CTPAPI兼容接口结构图](https://github.com/user-attachments/assets/5974ae64-ae18-4f2a-b459-d5f73243037a)

# 目录结构：

- [TTS-CTPAPI](https://github.com/openctp/openctp/tree/master/TTS-CTPAPI)：openctp模拟环境TTS系统CTPAPI兼容接口。

- [TTS-CTPOPT](https://github.com/openctp/openctp/tree/master/TTS-CTPOPT)：openctp模拟环境TTS系统CTP股票期权API兼容接口。

- [CTPOPT-CTPAPI](https://github.com/openctp/openctp/tree/master/CTPOPT-CTPAPI)：CTP股票期权柜台CTPAPI兼容接口。

- XTP-CTPAPI：中泰证券XTP柜台CTPAPI兼容接口。

- TORA-CTPAPI：华鑫证券TORA奇点股票柜台CTPAPI兼容接口。

- EMT-CTPAPI：东方财富EMT柜台CTPAPI兼容接口。

- TORA_OPT-CTPAPI：华鑫证券TORA奇点股票期权柜台CTPAPI兼容接口。

- OST-CTPAPI：东方证券OST柜台CTPAPI兼容接口。

- YD-CTPAPI：易达柜台CTPAPI兼容接口。（易达官方提供）

- IB-CTPAPI：盈透证券TWS平台CTPAPI兼容接口。

- QDP-CTPAPI：量投QDP柜台CTPAPI兼容接口。

- TAP-CTPAPI：易盛TAP启明星柜台CTPAPI兼容接口。

- QQ-CTPAPI：腾讯行情CTPAPI兼容接口（含源码）。

- SINA-CTPAPI：新浪行情CTPAPI兼容接口（含源码）。

- demo：CTPAPI开发相关的demo及工具源码。

- tools：小工具。

- docs：开发文档及行业资料。

- [ctpapi-python](https://github.com/openctp/openctp-ctp-python)：CTPAPI的Python接口。

- [ctpopt-python](https://github.com/openctp/openctp-ctpopt-python)：CTP股票期权API的Python接口。

- ctpapi-java：CTPAPI的Java接口。

- ctpapi-go：CTPAPI的Go接口。

- ctpapi-c：CTPAPI的C语言接口。

- ctpapi-rust：CTPAPI的Rust语言接口。

- ctpapi-csharp：CTPAPI的C#语言接口。

- widgets：基于CTPAPI的小应用。 
  
  # CTPAPI接口下载：
  
  [CTPAPI接口下载](http://www.openctp.cn/CTPAPI.html)
  
  # openctp模拟环境
  
  openctp提供了3套CTPAPI兼容接口模拟环境，分别为7x24环境、仿真环境、vip仿真环境，具体信息见：[模拟交易](http://openctp.cn/Trading.html)。
  
  # CTPAPI策略交易框架
  
  CTPAPI接口专业性很强，原生接口开发有一定难度，持仓与资金的实时计算也很难处理，各种持仓与资金字段的冻结、计算等，openctp给出了一套轻量的Tick级CTPAPI策略交易框架源码，保持了原汁原味的CTP数据结构，代码很漂亮，不到5000行，简洁易懂，二次开发很容易，更多介绍见：[CTPAPI策略交易框架](http://openctp.cn/TTF.html)。
  
  # 培训服务
  
  openctp提供证券期货交易开发方面的技术培训，也提供通用的基础技术培训，openctp的培训偏向于就业方向，比如想去私募或者科技公司从事量化或者柜台系统开发的比较适合，当然如果想自己学习一些技术帮助自己更好地做交易也是可以的。openctp的培训是迭代式的，会不断更新，补充更多的内容，同学可长期在相应课程的群内交流，具体见：[培训](http://openctp.cn/Learning.html)。
  
  # 就业服务
  
  为帮助解决金融、互联网等行业就业问题，openctp提供了招聘、兼职服务，有招聘、兼职需求的甲乙方可联系openctp咨询，具体见：[就业](http://openctp.cn/Jobs.html)。
  
  # 技术交流

- QQ群：564385877
  
  # openctp官网
  
  [www.openctp.cn](http://www.openctp.cn/)
  
  # openctp公众号
  
  ![公众号二维码](https://github.com/user-attachments/assets/14b3b875-acf9-4d27-940b-459401cc3401)

# CTPAPI相关文章：

- [CTP接口量化交易资料汇总](https://zhuanlan.zhihu.com/p/607325008)
- [量化交易数据接口汇总](https://zhuanlan.zhihu.com/p/681814762)
- [景色大佬的CTP接口开发技术讲解](https://www.zhihu.com/column/QuantRoad2019)
- [秋水大佬的CTP接口开发技术讲解](https://link.zhihu.com/?target=https%3A//mp.weixin.qq.com/mp/appmsgalbum%3F__biz%3DMzAxOTQ2ODA3OA%3D%3D%26action%3Dgetalbum%26album_id%3D1501810151681523713%26scene%3D173%26from_msgid%3D2247483738%26from_itemidx%3D1%26count%3D3%26nolastread%3D1%23wechat_redirect)
- [krenx的CTP柜台系统相关技术讲解](https://www.zhihu.com/column/c_1356686503654109184)
- [发布CTPAPI-Python源码](https://zhuanlan.zhihu.com/p/12295276223)
- [发布CTP股票期权柜台CTPAPI](https://zhuanlan.zhihu.com/p/709700501)
- [发布QDP极速柜台CTPAPI](https://zhuanlan.zhihu.com/p/709307501)
- [开放新浪行情CTPAPI接口源码](https://zhuanlan.zhihu.com/p/585724196)
- [开放腾讯行情CTPAPI接口源码](https://zhuanlan.zhihu.com/p/583796057)
- [发两个ctp开发者生产力工具](https://zhuanlan.zhihu.com/p/695782688)
- [发布openctp数据中心接口](https://zhuanlan.zhihu.com/p/1899531333975375926)

# 友情推荐

- [LocalCTP（兼容CTPAPI接口的嵌入式模拟交易环境（无服务端），支持全市场期货、期权及组合合约的模拟交易，支持FAK、FOK订单及条件单等指令，支持回测及结算单功能。）](https://github.com/dearleeyoung/LocalCTP)
- [VeighNa（基于Python的开源量化交易平台开发框架）](https://github.com/vnpy/vnpy)
- [QUANTAXIS（量化交易框架，支持股票、期货、期权，支持回测、多账户等特性。）](https://github.com/yutiansut/QUANTAXIS)
- [WonderTrader（一个基于C++核心模块的，适应全市场全品种交易的，高效率、高可用的量化交易开发框架。）](https://github.com/wondertrader/wondertrader)
- [MT5CTP（MT5客户端直连期货公司CTP柜台的期货程序化交易软件）](https://gitee.com/mt5ctp/MT5CTP)
- [ctpbee（简单易用的期货实盘ctp交易框架 支持ctp和ctp_mini）](https://github.com/ctpbee/ctpbee)
- [HQChart（基于国内传统PC股票客户端软件(C++)移植到js/py平台的一个项目, 包含K线图图形库及麦语法(分析家语法)指标执行器）](https://github.com/jones2000/HQChart)
- [KLineChart（基于 html5 canvas 构建的轻量级金融图表。）](https://github.com/klinecharts/KLineChart)
