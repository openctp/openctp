CTP、XTP、UFX、TTS等柜台开发辅助工具

xxxprint系列工具已发布CTP、XTP、恒生等8个柜台版本，只是查询并打印收到的订单、成交、持仓、资金等数据，当然也包含订单回报、成交回报等推送数据的显示，中泰证券、华鑫证券都借鉴了CTP的运营模式，接口的设计也是参照了CTP的形式，但是也有一定的差异，其中XTP的差异非常大，但是好的是这些柜台系统都是开放API接口的，证券柜台的API接口虽然前几年管的很严，但是最近两年都已放开对私募、专业投资者等层级的客户限制，只要客户的程序放在证券公司的托管机房运行即可，当然是给你远程那台机器的权限的，不然怎么玩。

目录：
- ttsprint - TTS系统（openctp自研模拟柜台）
- ctpprint - CTP系统
- ibprint - 盈透证券TWS
- xtpprint - 中泰证券XTP系统
- ufxprint -  恒生UFX柜台（股票）
- stpprint - 华鑫证券奇点股票柜台
- stpoptprint - 华鑫证券奇点股票期权柜台
- ostprint - 东方证券雨燕系统
- emtprint - 东方财富证券EMT柜台

**[CTP开放平台](https://link.zhihu.com/?target=https%3A//github.com/krenx1983/openctp)**的TTS系统已支持A股、国内期货及部分港美股合约模拟交易，也提供了通过仿CTPAPI直连华鑫证券、中泰证券（行情接口已发布，交易接口本周发布）柜台的能力，为了便于开发者快速了解各柜台接口的交互逻辑，发布了三个demo程序的源码，都是交易接口的demo，行情接口由于比较简单，所以就不针对行情接口写demo了。

TTS工具ttsprint就是拿ctpprint换上了TTS对应的仿ctp接口dll，dll版本是6.3.15。其实XTP、STP也可以拿ctpprint换上相应的仿ctp接口dll，但是这批工具针对的是原生接口开发辅助，所以CTP、XTP、STP都是基于官方发布的接口做的，以便开发者了解原生接口开发逻辑。

### ctpdemo运行效果：

![img](https://pic1.zhimg.com/80/v2-56b9e17d7c94fffbb2c7c9aa77957f04_720w.jpg)

### xtpdemo运行效果：

![preview](https://pic2.zhimg.com/v2-fd47d5973ee93ecf91172238b4a5c555_r.jpg)

### stpdemo运行效果：

![preview](https://pic2.zhimg.com/v2-39dfa038c414e5a39312a16aaa9bf09d_r.jpg)

