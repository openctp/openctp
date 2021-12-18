前面已经发布了[CTP行情显示工具源码（使用curses技术）](https://github.com/krenx1983/openctp/tree/master/demo/prices)，鉴于开发者经常问系统正不正常，能不能收到行情等问题，使用快期等比较大的客户端软件来验证这个问题可能未必合适，因为程序很重并且那些程序还依赖交易系统的正常运作，Prices工具是一个极轻巧的小程序，只依赖一个CTP行情dll，根本不连交易系统，并且没有什么复杂的逻辑，所以用来检测行情系统是不是工作正常再合适不过了。

由于**CTP开放平台**提供了除CTP之外的各股票柜台、期货柜台、综合柜台等柜台的CTP兼容接口，Prices工具可以依靠CTP开放平台的CTP兼容接口轻松连接其它各柜台，如**中泰证券XTP、华鑫证券奇点、腾讯、新浪、TTS**等，因此我们也就自然地发布了其它柜台的行情显示工具。

![image](https://user-images.githubusercontent.com/83346523/146631748-552cbd01-277e-497c-b524-666675a8f69b.png)

![image](https://user-images.githubusercontent.com/83346523/146631754-73499463-0caf-495f-ae8d-d32ec7d9e08e.png)

一共发布了**六个平台**对应的Prices工具，并且为方便使用，也顺带发布了十来个脚本，想检查哪一个环境，双击一下脚本即可，均为windows版本，如需linux、MacOS版本，可自己下载Prices工具源码编译。

**工具运行效果：**

![image](https://user-images.githubusercontent.com/83346523/146631757-026f20c5-1fe7-4dd3-a57e-f0084ddeb2b3.png)

**用法:**
```shell
prices marketaddr [instrument,instrument ...]
example:
prices tcp://180.168.146.187:10131 rb2105,IF2101
```

**各个平台用法可参考附带的各个脚本写法。**
