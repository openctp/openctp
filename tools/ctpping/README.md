# ctpping

ctpping工具是一款类似于网络工具ping的通道检测工具，通过ctpping，既可以检测底层网络连接问题，也可以检测业务层响应问题。既可以检测交易通道，也可以检测行情通道。

## 用法
usage:ctpping [-s milliseconds] [-t] [-m] address
- -t  使用tdapi检测
- -m  使用mdapi检测
- -s  超时时间（毫秒）

example:ctpping tcp://180.168.146.187:10130

example:ctpping -m tcp://180.168.146.187:10131

example:ctpping -s 1000 -t tcp://180.168.146.187:10130

<img width="584" alt="ctpping2" src="https://github.com/user-attachments/assets/d8ca174d-4455-4d66-b478-695cadb1878a">

## 源码
[ctpping工具源码](https://github.com/openctp/openctp/blob/master/demo/ctpping/ctpping.cpp)
