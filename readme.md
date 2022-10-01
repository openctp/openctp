## **CTP开放平台（Powered by TTS - Tick Trading System）**

### Github集 1000 Star，[知乎krenx](https://www.zhihu.com/people/krenx)集 10000 收藏，将开启平台各接口源码开放进程。

开放平台采用与CTPAPI完全兼容的接口，一定程度上可替代simnow等模拟平台进行功能测试。 CTP程序无需修改代码也无需重新编译，只需在这里**下载与CTP API版本号一致的动态库**，覆盖掉自己的即可。

提供CTPAPI 6.3.15、6.3.19、6.5.1、6.6.1、6.6.7全部在用的版本，对应支持win32、win64、linux、MacOS等多个操作系统。

![ctp开放平台全景图](https://user-images.githubusercontent.com/83346523/148639077-6c328032-b75a-4979-be8d-157de60cf3b4.jpg)

### openctp培训与咨询服务
openctp现已推出培训与技术咨询服务，**培训服务**共准备了四期培训课程，培训时间为每个周日晚20:00～21:30，培训方式为腾讯会议，课后可无限回看，课后可无限时间交流，现在推广期报名费为每期2000元，10月1号开始每月上调500元，直至5000元/期，一次性购买四期培训只需交三期的钱，报名请在openctp公众号回复“培训”两个字，培训完成可帮推荐工作，可长期跟同学们沟通交流，培训内容是我个人从业近二十年的技术精华，希望报名的同学能有一定的C/C++语言基础，完成四期培训，在金融交易领域的工作应该会得心应手。

**咨询服务**为零散问题解答服务，如果你在CTP技术群等等地方问问题没人理你，你可以来咨询我们，纯编程技术问题也可以，涵盖各主流语言：C/C++、Java、Python、Go等，Linux环境编程问题也可以，这项服务我们是以团队的形式对外进行服务，由各项技术的大厂专家组成，对技术都有丰富的经验和极高的追求，服务收费推广期只收1000元/年，不限次，报名请在openctp公众号回复“咨询”两个字。

### 各期培训内容安排：
- 第一期：C/C++高级编程（大概以Think库为基准进行讲解，含socket网络编程、IPC进程通讯等）
- 第二期：CTP技术开发（大概以openctp相关技术为基准进行讲解，含CTPAPI底层逻辑、CTPAPI各种注意事项、开源CTP客户端TextTrader源码讲解等）
- 第三期：交易系统开发（大概以TTS交易系统为基准进行讲解，含内存数据库架构技术、双机热备技术、重演技术、业务表结构设计、关键业务处理等）
- 第四期：金融交易业务（通讲全球股票、期货、期权交易发展历程、交易规则以及交易中的风险）

### 第一期的安排大致如下：
- 第一节课：Think库概览，讲解文件数据库（Think DB）、进程间通讯（共享内存、消息队列、信号量、文件映射等）、网络通讯（TCP、UDP、IP等）等跨平台开发技术（Windows、Linux、UNIX、MacOS等）。
- 第二节课：讲解Think NetCenter通讯框架（融合select、poll、epoll、kevent等各项IO复用技术）
- 第三节课：讲解使用共享内存及信号量技术实现共享内存队列（Think shmqueue），并对比System V消息队列。
- 第四节课：BML语言（TTS系统各模块之间及对外API的通讯语言）的讲解与实践，可连接openctp环境的TTS系统进行实操。Think库重要工具讲解，讲解netpeek代码（tcp通讯拦截并显示字节流），讲解udprecv、udpsend工具代码，都是极其实用的通用工具，Think库重要服务器程序讲解，讲解logserver日志服务器代码。

### 第二期的安排大致如下：
- 第一节课：通过[开源客户端TextTrader](https://github.com/krenx1983/TextTrader)源码带你对CTPAPI应用程序有个直观的体验，也通过TextTrader调用了的CTPAPI接口带你了解开发CTP程序大概需要用到哪些CTPAPI接口。
- 第二节课：系统性讲解CTPAPI各常用接口。
- 第三节课：以openctp的CTPAPI封装技术讲解CTPAPI的底层逻辑，让你知其然也知其所以然，从而更能够更准确高效地使用CTPAPI。
- 第四节课：讲解CTPAPI应用开发的各个特别注意事项，CTP系统很复杂，有许多需要特别注意的点，我们尽可能多地把踩过的坑都总结给你。

### 第四期的安排大致如下：
- 第一节课：通讲股票、期货、期权、A股、港美股、海外期货等各种投资品种的知识，有个全局性的认识，从而对自己能够和适合做什么样的投资有个大概的了解。
- 第二节课：详细讲解A股、国内期货的主要交易规则。
- 第三节课：详细讲解期权交易规则及基本投资策略。
- 第四节课：讲解风险控制，结合历史上典型的案例带你了解交易中的风险，也从我自己的交易经验谈谈我对风控的理解。

### 目录结构：
- 6.3.15 ~ 6.6.7：开放平台标准模拟环境TTS系统的CTPAPI兼容接口，替换CTP官方动态库即可连接TTS系统。
- ctp2IB盈透：盈透证券的CTPAPI兼容接口。
- ctp2OST东方证券：东方证券的CTPAPI兼容接口。
- ctp2中泰证券XTP：中泰证券XTP柜台的CTPAPI兼容接口。
- ctp2华鑫证券STP：华鑫证券奇点柜台的CTPAPI兼容接口。
- ctp2QQ行情：腾讯行情的CTPAPI兼容接口。
- ctp2Sina行情：新浪行情的CTPAPI兼容接口。
- demo：CTPAPI开发相关的demo及工具源码。
- tools：生产力工具。
- docs：开发文档及行业资料。

### 各套环境运行状态监控：
- 监控页面地址：http://122.51.136.165:50080/detail.html
- 使用的技术：https://github.com/krenx1983/openctp/tree/master/tools/Ping
- 相关源码：https://github.com/krenx1983/openctp/tree/master/demo/ctpping

![613dc093f916d1bf0764e5365f202ff](https://user-images.githubusercontent.com/83346523/148802378-2c9b3d3f-1959-4aab-851a-cf55666806d8.png)
### **支持品种：**
- A股股票、债券、基金
- 上期所等国内全品种期货、期权
- 港股、美股（支持00700（腾讯）、03690（美团）、AAPL（苹果）、MSFT（微软）、GOOG、AMZN、BABA（阿里巴巴）等主流港美股合约模拟交易）
- CME等外盘期货品种（即将上线）

### 相对Simnow优点：
- 支持负价交易（负价合约的合约号为MINUS，仅在7x24环境提供）。
- 支持部分撮合、部分撤消。
- 提供各交易所全商品模拟交易。
- 关注“CTP开放平台”公众号即可自动得到一个模拟号，回复注册可再注册多个模拟号，且即时在两套环境同时生效。
- QQ群546977604有问必答，解答CTP及各交易相关问题。
- 真正的7x24，1秒钟都不停。
- 除国内期货及期权外，还提供A股股票、债券、基金及港美股、外盘期货等全球市场模拟交易。
- 支持市价单。

### 知乎热门文章：
- [CTP开放平台（Powered by TTS - Tick Trading System）](https://zhuanlan.zhihu.com/p/425679896)
- [如何使用CTP开放平台提供的各项能力](https://zhuanlan.zhihu.com/p/451403422)
- [连接CTP开放平台报错4097的解决方法](https://zhuanlan.zhihu.com/p/453332727)
- [发布一批CTP链路检测工具](https://zhuanlan.zhihu.com/p/447148174)
- [发布一批行情显示工具（命令行版）](https://zhuanlan.zhihu.com/p/446972353)
- [CTP开放平台支撑系统（TTS）架构](https://zhuanlan.zhihu.com/p/367326886)
- [期货交易系统架构演变](https://zhuanlan.zhihu.com/p/360872258)
- [内存数据库交易系统架构第一篇--概览篇](https://zhuanlan.zhihu.com/p/382019469)
- [内存数据库交易系统架构第二篇--数据恢复机制](https://zhuanlan.zhihu.com/p/399605670)
- [交易系统的“白”（一）](https://zhuanlan.zhihu.com/p/430975046)

### 撮合方式（同时支持做市与撮合）：
- 撮合：完全由用户之间撮合，按价格优先、时间优先撮合成交。撮合模式的合约只有三个，合约代码分别为TEST、BTC、MINUS，其它合约均为做市模式。
- 做市：Simnow用的就是做市模式，以实盘行情盘口做市成交，即高于叫卖价的多单立即成交，低于叫买价的空单立即成交，否则挂在队列中等行情符合条件的时候成交。

### 部分成交、部分撤消：
- 模拟撮合在做市处理时对成交数量作了一定的随机处理，可能一次全部成交，可能部分成交并且间隔1秒左右再次撮合，再次撮合的时候如果果盘口不符合成交条件则不会成交。

### **开放平台仿真环境（交易时段与实盘一致）：**
- 交易前置 - tcp://121.36.146.182:20002
- 行情前置 - tcp://121.36.146.182:20004（建议直接使用CTP实盘行情前置，行情前置均不校验密码）

### **开放平台7x24环境（不间断轮播某天行情）：**
- 交易前置 - tcp://122.51.136.165:20002
- 行情前置 - tcp://122.51.136.165:20004

### **开放平台VIP环境（需要付费申请，具体[点这里](https://mp.weixin.qq.com/s?__biz=Mzk0ODI0NDE2Ng==&mid=2247484339&idx=1&sn=3c56cb0b201d3635a67f40b78dd7ae98&chksm=c36bd81af41c510c8d8e2ab43396a2de2fc73432f23b3cdff46debb85ec1170856903717a23b&token=1217034697&lang=zh_CN#rd)）：**
- 交易前置 - tcp://42.192.226.242:20002
- 行情前置 - 无（行情需要直连相应通道）

### **模拟账号：** 
扫扫下面的二维码，关注开放平台公众号，即可获得一个模拟账号，也可以回复"注册"再申请新的模拟号，一个微信号最多可以申请3个模拟账号，可以回复"查询"得到已注册的模拟账号列表。注册的模拟账号都可以在以上两个环境使用，两套环境独立结算，但是账号相同。

![qrcode_for_gh_564e4bf4668c_258](https://user-images.githubusercontent.com/83346523/120095274-ad600a00-c157-11eb-8496-7d680bd1f39b.jpg)

### **CTP程序接入股票柜台：**
除提供开放平台模拟交易外，还提供使用CTP接口接入证券柜台的能力，可以进行股票、债券、逆回购、新股申购、融资融券、ETF期权等交易，同样使用CTP接口将证券柜台接口封装成跟CTP完全兼容的动态库，使得CTP程序无需任何修改，只更换CTP动态库即可接入证券柜台，目前已完成华鑫证券、中泰证券股票交易接入功能，同样发布了目前在用的四个CTPAPI版本，分别提供win32、win64、linux三套动态库。

股票接入方式采用**直连证券柜台**方式，不经过开放平台处理，因此需要向证券公司申请模拟账号。
- **华鑫证券**，N视界模拟平台QQ客服群：860160807，加群验证信息填openctp（否则可能通过不了），模拟账号申请地址：http://www.n-sight.com.cn
- **中泰证券**，XTP柜台QQ客服群：188500929，加群验证信息填openctp（否则可能通过不了），模拟账号申请地址：https://xtp.zts.com.cn


### **已官方支持TTS通道（CTP开放平台）的产品：**
- [vn.py（知名Python量化交易客户端，支持全球市场交易）](https://www.vnpy.com/)
<img src="https://user-images.githubusercontent.com/83346523/136988918-1159fc88-073e-4b6f-a8d6-3f33991e8a72.png" alt="vnpy" width="700" height="400" />

- [MT5CTP（MT5软件，已支持国内A股、期货及期权交易，QQ：967352413）](https://www.zhihu.com/people/mt5ctp)
<img src="https://user-images.githubusercontent.com/83346523/136989596-b12d91e8-48a0-4b26-bcaf-fdfca52d962c.png" alt="mt5ctp" width="700" height="400" />

- [TextTrader（CTP开源命令行交易终端，支持A股、期货及期权交易）](https://github.com/krenx1983/TextTrader)
<img src="https://user-images.githubusercontent.com/83346523/136989754-1f0130e6-5d75-427f-bbf3-7ed084b6eae1.png" alt="texttrader" width="700" height="400" />

- [WonderTrader（一个基于C++核心模块的，适应全市场全品种交易的，高效率、高可用的量化交易开发框架）](https://dumengru.github.io/docs_wondertrader/wtcpp/folder02/file02.html)
<img src="https://user-images.githubusercontent.com/83346523/183711253-0cb71eed-016a-40c8-9415-c40e74aa0bca.jpg" alt="WonderTrader" width="700" height="400" />

### **通过自己替换dll可接入TTS通道（CTP开放平台）的产品：**
- [快期V3（CTP期货交易客户端）](https://zhuanlan.zhihu.com/p/376482285)
<img src="https://user-images.githubusercontent.com/83346523/138928402-f7e12a28-50d3-457b-9c0a-32b356448913.png" alt="快期V3" width="700" height="400" />
- [快期V2（CTP期货交易客户端）](https://zhuanlan.zhihu.com/p/432252376)
<img src="https://user-images.githubusercontent.com/83346523/148678947-b2a7ed9c-f77f-43d6-8e85-74b2c9ca4c44.png" alt="快期V2" width="700" height="400" />
- [TBTerminalCTP（交易开拓者）](https://zhuanlan.zhihu.com/p/437818698)
<img src="https://user-images.githubusercontent.com/83346523/149624377-01c97148-9e34-4f2b-8bb3-c43b57340284.png" alt="TBTerminal" width="700" height="400" />

### **QQ交流群：564385877**

<img src="https://user-images.githubusercontent.com/83346523/146651068-3c2b3401-8c87-4ff3-beb4-a86492ea6bef.png" alt="QQ群二维码" width="300" height="300" />

### **特别说明：**

AuthCode、AppID认证信息任意填，不作校验

Broker任意填，填什么就回什么

### **咨询服务：**
需要C/C++、Python、Java、Go、CTPAPI、交易系统等相关技术咨询服务的，请在openctp公众号回复”咨询“两个字。
### **招聘服务：**
需要C/C++、量化交易、互联网等方面的人才或职位请在openctp公众号回复“找工作”三个字，通过openctp推荐工作将免费得到openctp咨询服务（价值1000元/年）。
### **活动：**
openctp每个月至少会有一次粉丝线下活动，可以是吃饭、喝茶、徒步等等，想参加的请在openctp公众号回复“活动”两个字。
### **培训：**
年轻时投资自己是最划算的，因为时间比任何东西都值钱，借别人的力量充实自己，在很短的时间内获得别人的经验值。openctp培训旨在为行业培养高端人才，目前已设计了五期培训课程，分别是C语言0基础课程、C/C++高级编程、CTPAPI接口开发、交易系统开发、金融交易业务，每期四节课，每节课1小时，上课时间为每周日晚8点～9点。

<u>*本模拟平台不对模拟结果作任何保证，依据本平台测试结果进行实盘交易的后果完全由使用者自己承担。*</u>
