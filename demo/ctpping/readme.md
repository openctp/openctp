# ctpping（ctp通讯链路检测工具）

ctpping工具通过ctpapi的登录接口测试ctp柜台系统响应情况。

## 实现方法：

CTP交易前置及行情前置均为CTP交易系统对外提供的接入端，使用的是统一的通讯协议，ctpping工具使用该协议的登录接口，通过发送一笔空的登录报文，以期得到正确或错误的登录响应，如果链路正常，将显示响应时延。

**ctpping源代码仅仅几十行，就不多说明了，直接看源代码可以更快了解。**

## 用法：

ctpping address

## 例：

ctpping tcp://180.168.146.187:10130

ctpping tcp://180.168.146.187:10131

## 效果：

connected.

response time: 8 milliseconds

## 编译：

windows系统：

cl ctpping.cpp thostmduserapi_se.lib

linux系统:

g++ --std=c++11 -o ctpping ctpping.cpp thostmduserapi_se.so
