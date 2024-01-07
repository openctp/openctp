## **CTP开放平台（Powered by TTS - Tick Trading System）**

###     [知乎](https://www.zhihu.com/people/krenx)     [公众号](https://mp.weixin.qq.com/s?__biz=Mzk0ODI0NDE2Ng==&mid=2247484484&idx=1&sn=61385fada56d0e4ff620ce15b5dac864&chksm=c36bdfedf41c56fb52d5a200d01cf96be2f3c6578ede02571346717c821c769f192dae4f6a25&token=1790747698&lang=zh_CN#rd)     [B站](https://space.bilibili.com/549478063/video)     [西瓜](https://www.ixigua.com/home/4388848858576499/?source=pgc_author_profile&list_entrance=UserPlayList) [镜像ftpserver](http://121.37.80.177:8000)

开放平台采用与CTPAPI完全兼容的接口，一定程度上可替代simnow等模拟平台进行功能测试。 CTP程序无需修改代码也无需重新编译，只需在这里**下载与CTP API版本号一致的动态库**，覆盖掉自己的即可。

提供CTPAPI 6.3.15、6.3.19、6.5.1、6.6.1、6.6.7、6.6.9、6.7.0、6.7.1、6.7.2全部在用的版本，对应支持win32、win64、linux、MacOS等多个操作系统。

![ctp开放平台全景图](https://user-images.githubusercontent.com/83346523/148639077-6c328032-b75a-4979-be8d-157de60cf3b4.jpg)

### 目录结构：
- 6.3.15 ~ 6.7.2：开放平台标准模拟环境TTS系统的CTPAPI兼容接口，替换CTP官方动态库即可连接TTS系统。
- ctp2IB盈透：盈透证券的CTPAPI兼容接口。
- ctp2OST东方证券：东方证券的CTPAPI兼容接口。
- ctp2中泰证券XTP：中泰证券XTP柜台的CTPAPI兼容接口。
- ctp2华鑫证券STP：华鑫证券奇点柜台股票的CTPAPI兼容接口。
- ctp2EMT东方财富：东方财富EMT极速柜台的CTPAPI兼容接口。
- ctp2STPOPT：华鑫证券奇点柜台股票期权的CTPAPI兼容接口。
- ctp2QQ行情：腾讯行情的CTPAPI兼容接口（含源码）。
- ctp2Sina行情：新浪行情的CTPAPI兼容接口（含源码）。
- demo：CTPAPI开发相关的demo及工具源码。
- tools：生产力工具。
- docs：开发文档及行业资料。
- ctpapi-python：CTPAPI的Python接口。
- ctpapi-java：CTPAPI的Java接口。
- ctpapi-go：CTPAPI的Go接口。
- ctpapi-c：CTPAPI的C语言接口。
- ctpapi-rust：CTPAPI的Rust语言接口。
- ctpapi-C#：CTPAPI的C#语言接口。
- widgets：图形界面小应用。

### 各套环境运行状态监控：
- 监控页面地址：http://121.37.80.177:50080/detail.html
- 使用的技术：https://github.com/openctp/openctp/tree/master/tools/Ping
- 相关源码：https://github.com/openctp/openctp/tree/master/demo/ctpping

![613dc093f916d1bf0764e5365f202ff](https://user-images.githubusercontent.com/83346523/148802378-2c9b3d3f-1959-4aab-851a-cf55666806d8.png)
### **支持品种：**
- 沪深交易所股票、债券、基金、股票期权等
- 上期所、中金所等国内期货交易所全品种期货、期权
- 港股、美股全部股票合约模拟交易
- CME等外盘期货品种（即将上线）

### 相对Simnow优点：
- 支持负价交易（负价合约的合约号为MINUS，仅在7x24环境提供）。
- 支持部分撮合、部分撤消。
- 提供各交易所全商品模拟交易。
- 关注“CTP开放平台”公众号即可自动得到一个7x24测试账号及仿真账号，回复“注册仿真”可再注册多个仿真账号，回复“注册24”可再注册多个7x24测试账号，且立即生效。
- QQ群127235179有问必答，解答CTP及各交易相关问题。
- 真正的7x24，1秒钟都不停。
- 除国内期货及期权外，还提供A股股票、债券、基金、股票期权、港美股以及外盘期货等全球市场模拟交易。
- 支持市价单。

### 热门文章：
- [openctp欢迎你](https://mp.weixin.qq.com/s?__biz=Mzk0ODI0NDE2Ng==&mid=2247484484&idx=1&sn=61385fada56d0e4ff620ce15b5dac864&chksm=c36bdfedf41c56fb52d5a200d01cf96be2f3c6578ede02571346717c821c769f192dae4f6a25&token=1790747698&lang=zh_CN#rd)
- [CTP接口开发“葵花宝典”](https://zhuanlan.zhihu.com/p/397359483)
- [CTP接口支持pip install](https://zhuanlan.zhihu.com/p/622959788)
- [openctp私募成长计划](https://mp.weixin.qq.com/s?__biz=Mzk0ODI0NDE2Ng==&mid=2247484581&idx=1&sn=c8858fdabf575675d6af6eec363c5fa8&chksm=c36bdf0cf41c561a5185e2d5a8f2e69e33f031395afb3c9f9780e6f73f7b1f755eba142c4737&token=1790747698&lang=zh_CN#rd)
- [openctp培训与咨询服务](https://mp.weixin.qq.com/s?__biz=Mzk0ODI0NDE2Ng==&mid=2247484610&idx=1&sn=b7317eb127d22fd52958a41e40121b06&chksm=c36bdf6bf41c567d4f3c16454fc1f5ff2a22f567d893ea35a2135c082b78ce5d01d944b086e4&token=55513683&lang=zh_CN#rd)
- [CTP接口量化交易资料汇总](https://zhuanlan.zhihu.com/p/607325008)
- [开放腾讯行情CTPAPI接口源码](https://mp.weixin.qq.com/s?__biz=Mzk0ODI0NDE2Ng==&mid=2247484606&idx=1&sn=270ba6034d9e45334642236dc315b16e&chksm=c36bdf17f41c56011a5a3bf974022c13f53b21b0cad35d43ea85130748152b4f0739e02f7a0e&token=55513683&lang=zh_CN#rd)
- [开放新浪行情CTPAPI接口源码](https://zhuanlan.zhihu.com/p/585724196)
- [CTP程序无缝接入华鑫证券奇点柜台（CTP2STP）](https://mp.weixin.qq.com/s?__biz=Mzk0ODI0NDE2Ng==&mid=2247483843&idx=1&sn=fdb033a68e9f803183d902dcf92f969b&chksm=c36bda6af41c537c6ed262923f2ee9a4cccb1b02821b918382e51a299cca81556bdb4302cdd3&scene=21#wechat_redirect)
- [发布华鑫证券奇点柜台股票期权CTPAPI](https://mp.weixin.qq.com/s?__biz=Mzk0ODI0NDE2Ng==&mid=2247484767&idx=1&sn=34fc5c6b270cf8c8bdc37981df4ae8e1&chksm=c36bdef6f41c57e075460fca8d670db17310e7d832a240aa37fa0f4666ba92672aa179d8f0dd&token=1435234803&lang=zh_CN#rd)
- [开放华鑫证券奇点柜台行情CTPAPI接口源码](https://mp.weixin.qq.com/s?__biz=Mzk0ODI0NDE2Ng==&mid=2247484647&idx=1&sn=03bef5f9f71ecd879c3520de2564f8dd&chksm=c36bdf4ef41c565895c10adaa558d6ac471ac5003791cbe301771c8884757cef13400e09ca5b&token=1847931716&lang=zh_CN#rd)
- [如何使用CTP开放平台提供的各项能力](https://mp.weixin.qq.com/s?__biz=Mzk0ODI0NDE2Ng==&mid=2247484094&idx=1&sn=97bd791622333886260bf767bea40db1&chksm=c36bd917f41c50016b676b5f5b11f899aea889cd9b10e6724c7fee0ad443f31351f87ff5a4d2&token=1790747698&lang=zh_CN#rd)
- [发布一批行情显示工具（命令行版）](https://mp.weixin.qq.com/s?__biz=Mzk0ODI0NDE2Ng==&mid=2247484039&idx=1&sn=794a13777cb358e01c175439e022d99b&chksm=c36bd92ef41c5038224f3b38740b001ef3b36bec89b0ccede51a446039fd1fa679ff7b4bc3b5&token=1790747698&lang=zh_CN#rd)
- [openctp支撑系统（TTS）架构](https://zhuanlan.zhihu.com/p/367326886)
- [期货交易系统架构演变](https://zhuanlan.zhihu.com/p/360872258)
- [内存数据库交易系统架构第一篇--概览篇](https://mp.weixin.qq.com/s?__biz=Mzk0ODI0NDE2Ng==&mid=2247483745&idx=1&sn=555d1c26d66f5888f9f043f15335929c&chksm=c36bdac8f41c53de648bb55ae139d6f205827937872a74d6781e55162a7aaae3a1a6ad5acd2c&token=1790747698&lang=zh_CN#rd)
- [csdn技术文章](https://blog.csdn.net/krenx1983)

### 撮合方式（同时支持做市与撮合）：
- 撮合：完全由用户之间撮合，按价格优先、时间优先撮合成交。撮合模式的合约只有三个，合约代码分别为TEST、BTC、MINUS，其它合约均为做市模式。
- 做市：Simnow用的就是做市模式，以实盘行情盘口做市成交，即高于叫卖价的多单立即成交，低于叫买价的空单立即成交，否则挂在队列中等行情符合条件的时候成交。

### 部分成交、部分撤消：
- 仿真环境的做市模式不会部分成交，要测试部分成交可在7x24环境交易TEST、BTC、MINUS这三个合约。

### **openctp-7x24环境（不间断轮播某天行情）：**
- 交易前置 - tcp://121.37.80.177:20002
- 行情前置 - tcp://121.37.80.177:20004

### **openctp-仿真环境（交易时段与实盘一致）：**
- 交易前置 - tcp://121.37.90.193:20002
- 行情前置 - 无（订阅行情需要直连相应行情通道）

### **openctp-VIP仿真环境（需要付费申请，提供更快的速度、更全的品种，具体[点这里](https://mp.weixin.qq.com/s?__biz=Mzk0ODI0NDE2Ng==&mid=2247484339&idx=1&sn=3c56cb0b201d3635a67f40b78dd7ae98&chksm=c36bd81af41c510c8d8e2ab43396a2de2fc73432f23b3cdff46debb85ec1170856903717a23b&token=1217034697&lang=zh_CN#rd)）：**
- 交易前置 - tcp://42.192.226.242:20002
- 行情前置 - 无（订阅行情需要直连相应行情通道）

### **模拟账号：** 
扫扫下面的二维码，关注openctp公众号，即可获得一个7x24账号及一个仿真账号，也可以回复"注册24"或"注册仿真"再申请新的模拟号，一个微信号最多可以申请3个7x24测试账号及3个仿真模拟账号，可以回复"查询"得到已注册的模拟账号列表。7x24与仿真环境独立结算，账号也是独立的，但是密码是同一个，包括vip环境的密码也是同一个，也就是一个微信号申请的所有账号都共用一个密码，可以使用快期等支持修改密码的软件修改任何一个模拟号密码即可。

openctp除免费仿真环境外，还提供了vip仿真环境，具有更高的带宽，更全的品种，更多的模拟账号，分三个级别。
- vip1 - 300元/年，可申请10个模拟号，可交易国内期货、期货期权品种。
- vip2 - 500元/年，可申请10个模拟号，可交易品种增加A股股票、基金、债券。
- vip3 - 1000元/年，可申请10个模拟号，可交易品种增加A股股票期权、港股、美股、外盘期货等。

**vip权限申请方法：关注openctp公众号并回复“注册vip”。**

<img src="https://user-images.githubusercontent.com/83346523/225707613-59293970-0f04-4056-8ea4-dd4596a4efec.png" alt="微信公众号" width="300" height="350" />

### **CTP程序接入股票柜台：**
除提供开放平台模拟交易外，还提供使用CTP接口接入证券柜台的能力，可以进行股票、债券、逆回购、新股申购、融资融券、ETF期权等交易，同样使用CTP接口将证券柜台接口封装成跟CTP完全兼容的动态库，使得CTP程序无需任何修改，只更换CTP动态库即可接入证券柜台，目前已完成华鑫证券（股票、债券、基金、股票期权）、中泰证券（股票、债券、基金）股票交易接入功能，同样发布了目前在用的四个CTPAPI版本，分别提供win32、win64、linux三套动态库。

股票接入方式采用**直连证券柜台**方式，不经过开放平台处理，因此需要向证券公司申请模拟账号。**如需实盘接入股票柜台（个人投资者也可接入）或实盘交易请在openctp公众号回复咨询两个字。**
- **华鑫证券**，模拟账号申请地址：http://www.n-sight.com.cn
- **中泰证券**，模拟账号申请地址：https://xtp.zts.com.cn

**股票柜台接口与接入问题请加QQ群 127235179 咨询。**

### **CTPAPI及各柜台CTPAPI兼容接口下载：**

|柜台                                                      | 文档资料                                                                                | 6.3.15                                                                                    | 6.3.19_P1                                                                                |6.5.1                                                                                    |6.6.1_P1                                                                                        |6.6.7                                                                                        |6.6.9                                                                                        |6.7.0                                                                                        |6.7.1                                                                                        |6.7.2                                                                                        |
|  ----                                                            | ----                                                                                    |  ----                                                                                        | ----                                                                                    |----                                                                                    |----                                                                                            |----                                                                                        |----                                                                                        |----                                                                                        |----                                                                                        |----                                                                                        |
|CTP柜台官方接口| [ctp_docs.zip](http://121.37.80.177:50080/Download/CTPAPI/CTP/ctp_docs.zip)            |[ctp_6.3.15.zip](http://121.37.80.177:50080/Download/CTPAPI/CTP/ctp_6.3.15.zip)            | [ctp_6.3.19_P1.zip](http://121.37.80.177:50080/Download/CTPAPI/CTP/ctp_6.3.19_P1.zip)        | [ctp_6.5.1.zip](http://121.37.80.177:50080/Download/CTPAPI/CTP/ctp_6.5.1.zip)            | [ctp_6.6.1_P1.zip](http://121.37.80.177:50080/Download/CTPAPI/CTP/ctp_6.6.1_P1.zip)            | [ctp_6.6.7.zip](http://121.37.80.177:50080/Download/CTPAPI/CTP/ctp_6.6.7.zip)                | [ctp_6.6.9.zip](http://121.37.80.177:50080/Download/CTPAPI/CTP/ctp_6.6.9.zip)                | [ctp_6.7.0.zip](http://121.37.80.177:50080/Download/CTPAPI/CTP/ctp_6.7.0.zip)                | [ctp_6.7.1.zip](http://121.37.80.177:50080/Download/CTPAPI/CTP/ctp_6.7.1.zip)                | [ctp_6.7.2.zip](http://121.37.80.177:50080/Download/CTPAPI/CTP/ctp_6.7.2.zip)                |
|openctp模拟柜台（TTS）| [tts_docs.zip](http://121.37.80.177:50080/Download/CTPAPI/TTS/tts_docs.zip)            | [tts_6.3.15.zip](http://121.37.80.177:50080/Download/CTPAPI/TTS/tts_6.3.15.zip)            | [tts_6.3.19_P1.zip](http://121.37.80.177:50080/Download/CTPAPI/TTS/tts_6.3.19_P1.zip)        | [tts_6.5.1.zip](http://121.37.80.177:50080/Download/CTPAPI/TTS/tts_6.5.1.zip)            | [tts_6.6.1_P1.zip](http://121.37.80.177:50080/Download/CTPAPI/TTS/tts_6.6.1_P1.zip)            | [tts_6.6.7.zip](http://121.37.80.177:50080/Download/CTPAPI/TTS/tts_6.6.7.zip)                | [tts_6.6.9.zip](http://121.37.80.177:50080/Download/CTPAPI/TTS/tts_6.6.9.zip)                | [tts_6.7.0.zip](http://121.37.80.177:50080/Download/CTPAPI/TTS/tts_6.7.0.zip)                | [tts_6.7.1.zip](http://121.37.80.177:50080/Download/CTPAPI/TTS/tts_6.7.1.zip)                | [tts_6.7.2.zip](http://121.37.80.177:50080/Download/CTPAPI/TTS/tts_6.7.2.zip)                |
|华鑫证券奇点股票柜台| [tora_docs.zip](http://121.37.80.177:50080/Download/CTPAPI/TORA/tora_docs.zip)            | [tora_6.3.15.zip](http://121.37.80.177:50080/Download/CTPAPI/TORA/tora_6.3.15.zip)            | [tora_6.3.19_P1.zip](http://121.37.80.177:50080/Download/CTPAPI/TORA/tora_6.3.19_P1.zip)        | [tora_6.5.1.zip](http://121.37.80.177:50080/Download/CTPAPI/TORA/tora_6.5.1.zip)        | [tora_6.6.1_P1.zip](http://121.37.80.177:50080/Download/CTPAPI/TORA/tora_6.6.1_P1.zip)            | [tora_6.6.7.zip](http://121.37.80.177:50080/Download/CTPAPI/TORA/tora_6.6.7.zip)            | [tora_6.6.9.zip](http://121.37.80.177:50080/Download/CTPAPI/TORA/tora_6.6.9.zip)            | [tora_6.7.0.zip](http://121.37.80.177:50080/Download/CTPAPI/TORA/tora_6.7.0.zip)            | [tora_6.7.1.zip](http://121.37.80.177:50080/Download/CTPAPI/TORA/tora_6.7.1.zip)            | [tora_6.7.2.zip](http://121.37.80.177:50080/Download/CTPAPI/TORA/tora_6.7.2.zip)            |
|华鑫证券奇点股票期权柜台| [tora_opt_docs.zip](http://121.37.80.177:50080/Download/CTPAPI/TORA_OPT/tora_opt_docs.zip)    | [tora_opt_6.3.15.zip](http://121.37.80.177:50080/Download/CTPAPI/TORA_OPT/tora_opt_6.3.15.zip)    | [tora_opt_6.3.19_P1.zip](http://121.37.80.177:50080/Download/CTPAPI/TORA_OPT/tora_6.3.19_P1.zip)    | [tora_6.5.1.zip](http://121.37.80.177:50080/Download/CTPAPI/TORA_OPT/tora_opt_6.5.1.zip)    | [tora_opt_6.6.1_P1.zip](http://121.37.80.177:50080/Download/CTPAPI/TORA_OPT/tora_opt_6.6.1_P1.zip)    | [tora_opt_6.6.7.zip](http://121.37.80.177:50080/Download/CTPAPI/TORA_OPT/tora_opt_6.6.7.zip)    | [tora_opt_6.6.9.zip](http://121.37.80.177:50080/Download/CTPAPI/TORA_OPT/tora_opt_6.6.9.zip)    | [tora_opt_6.7.0.zip](http://121.37.80.177:50080/Download/CTPAPI/TORA_OPT/tora_opt_6.7.0.zip)    | [tora_opt_6.7.1.zip](http://121.37.80.177:50080/Download/CTPAPI/TORA_OPT/tora_opt_6.7.1.zip)    | [tora_opt_6.7.2.zip](http://121.37.80.177:50080/Download/CTPAPI/TORA_OPT/tora_opt_6.7.2.zip)    |
|中泰证券XTP股票柜台| [xtp_docs.zip](http://121.37.80.177:50080/Download/CTPAPI/XTP/xtp_docs.zip)            | [xtp_6.3.15.zip](http://121.37.80.177:50080/Download/CTPAPI/XTP/xtp_6.3.15.zip)            | [xtp_6.3.19_P1.zip](http://121.37.80.177:50080/Download/CTPAPI/XTP/xtp_6.3.19_P1.zip)        | [xtp_6.5.1.zip](http://121.37.80.177:50080/Download/CTPAPI/XTP/xtp_6.5.1.zip)            | [xtp_6.6.1_P1.zip](http://121.37.80.177:50080/Download/CTPAPI/XTP/xtp_6.6.1_P1.zip)            | [xtp_6.6.7.zip](http://121.37.80.177:50080/Download/CTPAPI/XTP/xtp_6.6.7.zip)                | [xtp_6.6.9.zip](http://121.37.80.177:50080/Download/CTPAPI/XTP/xtp_6.6.9.zip)                | [xtp_6.7.0.zip](http://121.37.80.177:50080/Download/CTPAPI/XTP/xtp_6.7.0.zip)                | [xtp_6.7.1.zip](http://121.37.80.177:50080/Download/CTPAPI/XTP/xtp_6.7.1.zip)                | [xtp_6.7.2.zip](http://121.37.80.177:50080/Download/CTPAPI/XTP/xtp_6.7.2.zip)                |
|东方财富EMT股票柜台| [emt_docs.zip](http://121.37.80.177:50080/Download/CTPAPI/EMT/emt_docs.zip)            | [emt_6.3.15.zip](http://121.37.80.177:50080/Download/CTPAPI/EMT/emt_6.3.15.zip)            | [emt_6.3.19_P1.zip](http://121.37.80.177:50080/Download/CTPAPI/EMT/emt_6.3.19_P1.zip)        | [emt_6.5.1.zip](http://121.37.80.177:50080/Download/CTPAPI/EMT/emt_6.5.1.zip)            | [emt_6.6.1_P1.zip](http://121.37.80.177:50080/Download/CTPAPI/EMT/emt_6.6.1_P1.zip)            | [emt_6.6.7.zip](http://121.37.80.177:50080/Download/CTPAPI/EMT/emt_6.6.7.zip)                | [emt_6.6.9.zip](http://121.37.80.177:50080/Download/CTPAPI/EMT/emt_6.6.9.zip)                | [emt_6.7.0.zip](http://121.37.80.177:50080/Download/CTPAPI/EMT/emt_6.7.0.zip)                | [emt_6.7.2.zip](http://121.37.80.177:50080/Download/CTPAPI/EMT/emt_6.7.2.zip)                | [emt_6.7.2.zip](http://121.37.80.177:50080/Download/CTPAPI/EMT/emt_6.7.2.zip)                |
|东方证券OST股票柜台| [ost_docs.zip](http://121.37.80.177:50080/Download/CTPAPI/OST/ost_docs.zip)            | [ost_6.3.15.zip](http://121.37.80.177:50080/Download/CTPAPI/OST/ost_6.3.15.zip)            | [ost_6.3.19_P1.zip](http://121.37.80.177:50080/Download/CTPAPI/OST/ost_6.3.19_P1.zip)        | [ost_6.5.1.zip](http://121.37.80.177:50080/Download/CTPAPI/OST/ost_6.5.1.zip)            | [ost_6.6.1_P1.zip](http://121.37.80.177:50080/Download/CTPAPI/OST/ost_6.6.1_P1.zip)            | [ost_6.6.7.zip](http://121.37.80.177:50080/Download/CTPAPI/OST/ost_6.6.7.zip)                | [ost_6.6.9.zip](http://121.37.80.177:50080/Download/CTPAPI/OST/ost_6.6.9.zip)                | [ost_6.7.0.zip](http://121.37.80.177:50080/Download/CTPAPI/OST/ost_6.7.0.zip)                | [ost_6.7.1.zip](http://121.37.80.177:50080/Download/CTPAPI/OST/ost_6.7.1.zip)                | [ost_6.7.2.zip](http://121.37.80.177:50080/Download/CTPAPI/OST/ost_6.7.2.zip)                |
|腾讯股票行情| [qq_docs.zip](http://121.37.80.177:50080/Download/CTPAPI/QQ/qq_docs.zip)                | [qq_6.3.15.zip](http://121.37.80.177:50080/Download/CTPAPI/QQ/qq_6.3.15.zip)                | [qq_6.3.19_P1.zip](http://121.37.80.177:50080/Download/CTPAPI/QQ/qq_6.3.19_P1.zip)            | [qq_6.5.1.zip](http://121.37.80.177:50080/Download/CTPAPI/QQ/qq_6.5.1.zip)            | [qq_6.6.1_P1.zip](http://121.37.80.177:50080/Download/CTPAPI/QQ/qq_6.6.1_P1.zip)                | [qq_6.6.7.zip](http://121.37.80.177:50080/Download/CTPAPI/QQ/qq_6.6.7.zip)                | [qq_6.6.9.zip](http://121.37.80.177:50080/Download/CTPAPI/QQ/qq_6.6.9.zip)                | [qq_6.7.0.zip](http://121.37.80.177:50080/Download/CTPAPI/QQ/qq_6.7.0.zip)                | [qq_6.7.1.zip](http://121.37.80.177:50080/Download/CTPAPI/QQ/qq_6.7.1.zip)                | [qq_6.7.2.zip](http://121.37.80.177:50080/Download/CTPAPI/QQ/qq_6.7.2.zip)                |
|新浪股票行情| [sina_docs.zip](http://121.37.80.177:50080/Download/CTPAPI/SINA/sina_docs.zip)            | [sina_6.3.15.zip](http://121.37.80.177:50080/Download/CTPAPI/SINA/sina_6.3.15.zip)            | [sina_6.3.19_P1.zip](http://121.37.80.177:50080/Download/CTPAPI/SINA/sina_6.3.19_P1.zip)        | [sina_6.5.1.zip](http://121.37.80.177:50080/Download/CTPAPI/SINA/sina_6.5.1.zip)        | [sina_6.6.1_P1.zip](http://121.37.80.177:50080/Download/CTPAPI/SINA/sina_6.6.1_P1.zip)            | [sina_6.6.7.zip](http://121.37.80.177:50080/Download/CTPAPI/SINA/sina_6.6.7.zip)            | [sina_6.6.9.zip](http://121.37.80.177:50080/Download/CTPAPI/SINA/sina_6.6.9.zip)            | [sina_6.7.0.zip](http://121.37.80.177:50080/Download/CTPAPI/SINA/sina_6.7.0.zip)            | [sina_6.7.1.zip](http://121.37.80.177:50080/Download/CTPAPI/SINA/sina_6.7.1.zip)            | [sina_6.7.2.zip](http://121.37.80.177:50080/Download/CTPAPI/SINA/sina_6.7.2.zip)            |

### **已官方支持TTS通道（CTP开放平台）的产品：**
- [TickTrader（openctp出品的交易客户端，支持全球市场交易，支持TTS、CTP、华鑫证券等柜台）](https://github.com/openctp/TickTrader)
![image](https://github.com/openctp/openctp/assets/83346523/bc458496-172b-4cb3-bc70-dbde12c0bc17)

- [vn.py（知名Python量化交易客户端，支持全球市场交易）](https://www.vnpy.com/)
<img src="https://user-images.githubusercontent.com/83346523/136988918-1159fc88-073e-4b6f-a8d6-3f33991e8a72.png" alt="vnpy" width="700" height="400" />

- [MT5CTP（MT5软件，已支持国内A股、期货及期权交易，QQ群：967352413，备注openctp。）](https://www.zhihu.com/people/mt5ctp)
<img src="https://user-images.githubusercontent.com/83346523/136989596-b12d91e8-48a0-4b26-bcaf-fdfca52d962c.png" alt="mt5ctp" width="700" height="400" />

- [TextTrader（CTP开源命令行交易终端，支持A股、期货及期权交易）](https://github.com/krenx1983/TextTrader)
<img src="https://user-images.githubusercontent.com/83346523/136989754-1f0130e6-5d75-427f-bbf3-7ed084b6eae1.png" alt="texttrader" width="700" height="400" />

- [WonderTrader（一个基于C++核心模块的，适应全市场全品种交易的，高效率、高可用的量化交易开发框架，QQ群：610730738，备注openctp。）](https://www.zhihu.com/column/c_1338797723131740161)
<img src="https://user-images.githubusercontent.com/83346523/198839414-d72614d8-9752-497a-b9a9-19b38d3da326.png" alt="WonderTrader" width="700" height="400" />

- [ctpbee（一个轻量级Python量化交易框架，支持CTP柜台。）](https://github.com/ctpbee/ctpbee)
<img src="https://github.com/openctp/openctp/assets/83346523/c0448edf-a1fe-4e7a-92c9-5a7652f83f94" alt="WonderTrader" width="700" height="400" />

### **通过自己替换dll可接入TTS通道（CTP开放平台）的产品：**
- [快期V3（CTP期货交易客户端）](https://zhuanlan.zhihu.com/p/376482285)
<img src="https://user-images.githubusercontent.com/83346523/138928402-f7e12a28-50d3-457b-9c0a-32b356448913.png" alt="快期V3" width="700" height="400" />
- [快期V2（CTP期货交易客户端）](https://zhuanlan.zhihu.com/p/432252376)
<img src="https://user-images.githubusercontent.com/83346523/148678947-b2a7ed9c-f77f-43d6-8e85-74b2c9ca4c44.png" alt="快期V2" width="700" height="400" />
- [TBTerminalCTP（交易开拓者）](https://zhuanlan.zhihu.com/p/437818698)
<img src="https://user-images.githubusercontent.com/83346523/149624377-01c97148-9e34-4f2b-8bb3-c43b57340284.png" alt="TBTerminal" width="700" height="400" />

### **QQ交流群：127235179**

<img src="https://user-images.githubusercontent.com/83346523/225706658-5dde7246-d837-4d13-9207-aea48b688184.png" alt="QQ群二维码" width="300" height="500" />


### **特别说明：**

AuthCode、AppID不需要填，不作校验

BrokerID也不需要填

### **咨询服务：**
为零散问题解答服务，如果你在CTP技术群、编程语言群等等地方问问题没人理你，你可以来咨询我们，这项服务我们是以团队的形式对外进行服务，由各项技术的大厂专家组成，对技术都有丰富的经验和极高的追求，现推广阶段咨询费也很便宜，报名请在openctp公众号回复“咨询”两个字。请注意，咨询不是培训，如果你需要的是系统性的学习，请报相应的培训课程，咨询也不会帮忙写代码，也不保证能回答你的任何问题，非诚勿扰。
- 上期技术CTP、中泰证券XTP、华鑫证券Tora、恒生等柜台接口开发咨询：1000元，永久有效，建立统一的咨询群，可永久在群内交流，群内也有更加专业、清晰的接口开发技术资料。注：目前主要以CTP接口咨询服务为主，逐步加强华鑫证券Tora、中泰证券XTP等接口咨询服务。
- 技术顾问：10000元/年，可以咨询编程框架、系统架构、业务规划等高阶内容。
### **招聘服务：**
需要C/C++、Python、Java、量化交易、互联网、智能汽车等方面的人才或职位请在openctp公众号回复“工作”两个字。
### **活动：**
参与openctp粉丝线下活动，可以是吃饭、喝茶、徒步等等，想参加的请在openctp公众号回复“活动”两个字。

### **培训（视频回放+答疑交流，随时可报名）**
openctp的支撑系统TTS（Tick Trading System）采用与CTP柜台同样的设计，均为内存数据库总线架构，也是金融交易领域最高级别的架构技术，openctp的各柜台CTPAPI兼容接口也与CTP接口完全兼容，基于这样的核心技术，我们做了五期培训课程，帮助量化开发者及从业人员，既能够更精准掌握CTP接口的使用，也能够提升工作技能，让自己更加自信和从容。培训方式为视频回看+答疑交流，报名请在openctp公众号回复“培训”两个字，培训完成可帮推荐工作，可长期在群内跟同学们沟通交流，群内也有业内各位大佬。培训内容也会不断迭代，可一直在群内学习提升，也会适当安排线下学习交流。已有数十名同学参与了培训，早培训早受益，要学会站在别人的肩膀上，正值找工作换工作的黄金时期，花一点钱学习行业最好的技术，值。
### 各期培训内容安排（已完成的课程可至[B站](https://space.bilibili.com/549478063/video)及[西瓜](https://www.ixigua.com/home/4388848858576499/?source=pgc_author_profile&list_entrance=anyVideo)试看）：
- 第一期：[C/C++高级编程](https://mp.weixin.qq.com/s?__biz=Mzk0ODI0NDE2Ng==&mid=2247484363&idx=1&sn=0d74fb1a61e1c595d36527b23eb23323&chksm=c36bd862f41c51749f9490a2b0027fb6a8df53d22c9768b73353a995d7a879171e9fea4d03b4&token=1790747698&lang=zh_CN#rd)，3000元，以krenx开发的C语言跨平台开发框架[Think库](https://github.com/krenx1983/think)为基准进行讲解，含socket网络编程、IPC进程通讯等，有众多实用的工具，可立即应用到工作中。另外还有boost.asio异步网络通讯框架等开发技术的讲解，也提供相应的实例源码。
- 第二期：[CTP技术开发](https://mp.weixin.qq.com/s?__biz=Mzk0ODI0NDE2Ng==&mid=2247484422&idx=1&sn=0165c1b7b5f964ce32c34445d8230f25&chksm=c36bdfaff41c56b9d05870e0d54880a7c62b9dea092372c074b786bc390e5d665fe5e9ef5f84&token=1790747698&lang=zh_CN#rd)，5000元，以openctp相关技术为基准进行讲解，含CTPAPI底层逻辑、CTPAPI各种注意事项、开源CTP客户端TextTrader源码讲解等。送高质量轻量级Tick级多策略交易框架源码（约三五千行），保持原汁原味的CTP数据结构，实时计算持仓、资金，框架正在开发中，开发完成后也将免费发给前面已报名的同学。
- 第三期：[交易系统开发](https://mp.weixin.qq.com/s?__biz=Mzk0ODI0NDE2Ng==&mid=2247484574&idx=1&sn=4ff8d92d1f810ad456ac3eda9b3736f7&chksm=c36bdf37f41c5621d1ba8eed48b5ba46a674b57b66ce8e312d364bedec32913b5eb00413fbc4&token=1790747698&lang=zh_CN#rd)，5000元，以TTS交易系统为基准进行讲解，含交易系统结构、架构技术、业务表结构设计、关键业务处理等。送一套完整的交易撮合系统源码，含下单、仓位与资金计算、委托回报、成交回报、撮合成交、行情推送等完整功能，正在开发中，开发完成后也将免费发给前面已报名的同学。
- 第四期：[金融交易业务与产品设计](https://mp.weixin.qq.com/s?__biz=Mzk0ODI0NDE2Ng==&mid=2247484661&idx=1&sn=b7bc4c5141fc36f1aa395a644ffa586b&chksm=c36bdf5cf41c564ad6b2395e01553372d9ea93375e63e81fb60e2a78178b2419d4864ab548aa&token=798261616&lang=zh_CN#rd)，5000元，通讲全球股票、期货、期权交易发展历程、交易规则、计算公式、风险控制及产品设计，提供一份CTP全部常用字段的详细说明。
- 第五期：[内存数据库架构交易系统总线开发技术](https://mp.weixin.qq.com/s?__biz=Mzk0ODI0NDE2Ng==&mid=2247484747&idx=1&sn=21b2d57102daa4305860d61f844784fe&chksm=c36bdee2f41c57f4db3fa23bb41c21cfa5b909843590f179b4761f24aad385fbccfde5ae5002&token=798261616&lang=zh_CN#rd)，8000元，通过TTS的总线架构技术讲解CTP那样的总线开发技术，包括重演、热备、负载均衡、最短路由、分布式计算等技术，内存计算架构在各行业的高性能通讯方面都可以应用，远不止金融交易领域。

### openctp公开课：
- [C语言0基础](https://mp.weixin.qq.com/s?__biz=Mzk0ODI0NDE2Ng==&mid=2247484592&idx=1&sn=7b0caf96f497461a45f5940dfa6c5361&chksm=c36bdf19f41c560f8a9ebcf7b7031820414d997a7c151e520c006423cf6f9c6f6d890adcda7b&token=798261616&lang=zh_CN#rd)：以生动有趣的方式讲C语言基础性编程技术，重在兴趣培养和信心建立。
- C++语言0基础：以生动有趣的方式讲C++语言基础性编程技术。
- Python语言0基础：以生动有趣的方式讲Python语言基础性编程技术。
- Java语言0基础：以生动有趣的方式讲Java语言基础性编程技术。
- Go语言0基础：以生动有趣的方式讲Go语言基础性编程技术。
- Linux环境编程0基础：以生动有趣的方式讲Linux环境编程技术。

<u>*本模拟平台不对模拟结果作任何保证，依据本平台测试结果进行实盘交易的后果完全由使用者自己承担。*</u>
