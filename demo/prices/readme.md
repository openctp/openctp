# Prices

### CTP报价显示工具

​       版本1.0

​     作者 krenx

   krenx@qq.com

![1616771807(1)](https://user-images.githubusercontent.com/83346523/120349092-611bf200-c330-11eb-8bd1-326adc7f7900.png)

### 简介
Prices是一款命令行行情客户端，操作命令只有上下左右四个方向键，也可以使用VI编辑器的四个移动命令j、k、h、l，如果屏幕有乱码，使用Ctrl+L键刷新，支持支持Windows、Linux、MacOS、FreeBSD等操作系统。

Prices支持CTP期货柜台，也支持采用CTP兼容接口的其它平台（[CTP开放平台](https://github.com/krenx1983/openctp)）。

### 用法

prices marketaddr [instrument,instrument ...]
example:
	prices tcp://180.168.146.187:10131（可用于局域网环境，不指定合约可以订阅所有合约，未测试）
	prices tcp://180.168.146.187:10131 rb2105,IF2101

### 编译
Linux：
执行make

Windows：
执行nmake -f makefile.win32

MacOSX:
执行make -f makefile.mac



