# CTPAPI Schema

从 SimNow 官网下载的 CTPAPI 接口文件，并将其转化为语言无关的通用格式 JsonSchema。  
可以通过读取通用JsonSchema数据，遍历CTPAPI的接口、参数、数据类型等，并根据业务需要批量生成代码。

支持 ctpapi 6.3.15/6.3.19/6.5.1/6.6.1/6.6.7/6.6.9 。

## JsonSchema 文件

1. types.json
   对应 ThostFtdcUserApiDataType.h

   在 `definitions` 下定义了各种数据类型/宏定义/枚举值

2. structs.json

   对应 ThostFtdcUserApiStruct.h

   在 `definitions` 下定义各种 Struct 数据结构对象, `properties` 下定义了数据结构的各个元素

3. mdapi.json

   对应 ThostFtdcMdApi.h, 定义行情API的各种方法

   在根对象的 `properties` 下定义了行情API的 `CThostFtdcMdSpi` 回调类 和 `CThostFtdcMdApi` 请求类

   在 `CThostFtdcMdSpi/CThostFtdcMdApi` 下的 `properties` 中定义了各自包含的接口方法

   在 接口方法（如`OnRspUserLogout`）下的 `properties` 中定义了接口的入参，若没有`properties`则表示没有入参。

4. tdapi.json

   对应 ThostFtdcTraderApi.h, 定义了交易API的各种方法

   在 `properties` 下定义了行情API的 `CThostFtdcTraderSpi` 回调类 和 `CThostFtdcTraderApi` 请求类

   在 `CThostFtdcTraderSpi/CThostFtdcTraderApi` 下的 `properties` 中定义了各自包含的接口方法

   在 接口方法（如`OnRspUserLogin`）下的 `properties` 中定义了接口的入参，若没有`properties`则表示没有入参。

## 说明

1. CTPAPI 和 JsonSchema 的基本数据类型的映射关系为

   | CTPAPI | JsonSchema |
   | --- | --- |
   | char | string |
   | bool | boolean |
   | int | integer |
   | short | integer |
   | double | number |

   其中 `string` 参照CTPAPI做了最大长度的限制

2. 未对接口方法的返回值进行定义（CTPAPI中只有个别接口方法有返回值）。
3. 使用的接口文件是 Windows/Linux 平台的
