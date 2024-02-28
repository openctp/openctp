# ctpoptping（ctp股票期权通讯链路检测工具）

## 用途：

检测CTP股票期权链路及通讯延时。

## 实现方法：

CTP股票期权交易前置及行情前置均为CTP股票期权交易系统对外提供的接入端，使用的是统一的通讯协议，ctpoptping工具使用该协议的登录接口，通过发送一笔空的登录报文，以期得到正确或错误的登录响应，如果链路正常，将显示响应时延。

**ctpoptping源代码仅仅几十行，就不多说明了，直接看源代码可以更快了解。**

## 用法：

ctpoptping address

## 例：

ctpoptping tcp://180.168.146.187:10130

ctpoptping tcp://180.168.146.187:10131

## 效果：

connected.

response time: 8 milliseconds

## 编译：

windows系统：

cl ctpping.cpp soptthostmduserapi_se.lib soptthosttraderapi_se.lib

linux系统:

g++ --std=c++11 -o ctpping ctpping.cpp soptthostmduserapi_se.so soptthosttraderapi_se.so
