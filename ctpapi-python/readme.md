## 简介

- ctpapi-python 是通过 swig 将 c++ 版本 ctpapi 转换为 python 版本，命名和使用方法与 c++ 一致。
- 分为 Linux64/Win64/Mac 三个版本
- Windows 下, Python 3.7/3.8/3.9/3.10/3.11... 等版本编译的 api 又互不兼容，不可串用。
- 3.7 <= Supported Python <= 3.11


## 使用方法

安装
```python
# pip install openctp-ctp-<ctp version> 
pip install openctp-ctp-6319 
pip install openctp-ctp-667
```
代码示例
```python
from openctp_ctp_667 import mdapi, tdapi  
md_api = mdapi.CThostFtdcMdApi.CreateFtdcMdApi("market") 
td_api = tdapi.CThostFtdcTraderApi.CreateFtdcTraderApi('user_id')
```
**更多说明及demo请移步[openctp-ctp-python](https://github.com/openctp/openctp-ctp-python)**
