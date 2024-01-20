# ctpapi-python

众所周知，CTPAPI是基于C++语言编写的，但是直接使用C++来编写交易软件或策略来对接CTP，比较复杂，开发相对慢。Python是一个开发效率非常高的语言，便于快速的编写、验证交易逻辑和策略。

openctp 团队专门提供了经 swig 转换的 CTPAPI Python 版，使用 `pip install` 方式安装使用，支持Windows/Linux/Mac多平台，3.7~3.12多Python版本。

## openctp-ctp-python
官方 CTPAPI 的Python版, 可以用来连接 SimNow 以及支持 CTPAPI官方实现 的柜台，详情见 https://github.com/openctp/openctp-ctp-python :airplane:

## openctp-tts-python
这是 TTSAPI 的Python版, 可以用来连接 openctp TTS 的[模拟、仿真服务](http://121.37.80.177:50080/)，详情见 https://github.com/openctp/openctp-tts-python :airplane:
