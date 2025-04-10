prices是一款CTP接口行情显示工具，可以指定订阅并显示多个合约行情，只依赖一个行情dll，极其简洁，可以用于检测行情接口问题。默认只支持CTP行情通道，其它通道可通过CTPAPI兼容接口方式使用。

prices工具源码：[openctp/demo/prices/prices.cpp](https://github.com/openctp/openctp/blob/master/demo/prices/prices.cpp)

**用法:**

```shell
prices marketaddr [instrument,instrument ...]
example:
prices tcp://180.168.146.187:10131 rb2105,IF2101
```

![image](https://user-images.githubusercontent.com/83346523/146631757-026f20c5-1fe7-4dd3-a57e-f0084ddeb2b3.png)
