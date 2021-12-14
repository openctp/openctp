# Prices

### CTP报价显示工具

​       版本1.0

​     作者 krenx

   krenx@qq.com

![~N3C2Y%C5B@R2AZG71ED1L9](https://user-images.githubusercontent.com/83346523/145686508-4c819a16-2169-4e87-a9a5-78f353c0bc9c.png)

### 简介
Prices是一款命令行行情客户端，操作命令只有上下左右四个方向键，也可以使用VI编辑器的四个移动命令j、k、h、l，如果屏幕有乱码，使用Ctrl+L键刷新，支持支持Windows、Linux、MacOS、FreeBSD等操作系统。

Prices支持CTP期货柜台，也支持采用CTP兼容接口的其它平台（[CTP开放平台](https://github.com/krenx1983/openctp)）。

### 用法

prices [-u user] [-p password] marketaddr instrument1,instrument2 ...

example:

	prices tcp://180.168.146.187:10131 rb2105,IF2101（绝大部分通道都不需要提供用户名、密码）
	
	prices -u 000001 -p 888888 tcp://180.168.146.187:10131 rb2105,IF2101 （中泰证券XTP需要指定用户，密码可略）

### 编译
Linux：
执行make

Windows：
执行nmake -f makefile.win32，或者直接打开virtual studio 2019工程

MacOSX:
执行make -f makefile.mac



