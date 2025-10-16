# Python版CTPAPI

## 直接使用

openctp提供了pip install和文件下载两种方法安装CTPAPI-Python库，可以直接使用，均支持6.3.15~6.7.2各个版本。

### pip install方式

```bash
pip install openctp-ctp==6.3.15.* -i https://pypi.tuna.tsinghua.edu.cn/simple --trusted-host=pypi.tuna.tsinghua.edu.cn
```

### 文件下载方式

[CTPAPI-Python接口下载](http://openctp.cn/CTPAPI-Python.html)

## 自己编译

CTPAPI-Python使用Swig技术开发，可以自己按以下步骤编译，需要安装swig等组件，详细攻略见：[CTPAPI-Python开发攻略](https://zhuanlan.zhihu.com/p/688672132)。

本仓库选用的是CTPAPI-6.3.15，如需编译其它版本，请下载相应的CTPAPI文件覆盖对应目录下的CTPAPI文件。

### 准备

- 安装VirtualStudio、Swig、Python3、boost、cmake，boost库用到的是locale库，用来转换字符集。
- 设置BOOST_INCLUDE、BOOST_LIB环境变量分别指向相应库的头文件及库目录，如E:\boost_1_73_0、E:\boost_1_73_0\stage\lib。
- 设置PYTHON_INCLUDE、PYTHON_LIB环境变量分别指向相应库的头文件及库目录，如C:\Program Files\Python312\include、C:\Program Files\Python312\libs。

### Windows编译

编译成功后，将生成的文件连同CTPAPI的dll（thosttraderapi.dll、thostmduserapi.dll）拷贝到你的程序运行目录下即可：

- thosttraderapi.py
- thostmduserapi.py
- _thostmduserapi.pyd
- _thosttraderapi.pyd

#### Win32

```
cd CTPAPI
mkdir build
cd build
cmake ..
cmake --build . --config Release
```

#### Win64

```
cd CTPAPI
mkdir build
cd build
cmake -A x64 ..
cmake --build . --config Release
```

### Linux编译

编译成功后，将生成的文件连同CTPAPI的so文件（thosttraderapi.so、thostmduserapi.so）拷贝到你的程序运行目录下即可：

- thosttraderapi.py

- thostmduserapi.py

- _thostmduserapi.so

- _thosttraderapi.so
  
  ```
  cd CTPAPI
  mkdir build
  cd build
  cmake ..
  make
  ```
  
  ### 效果
  
  ```
  [krenx]$ cmake ..
  -- The C compiler identification is GNU 9.3.1
  -- The CXX compiler identification is GNU 9.3.1
  -- Check for working C compiler: /opt/rh/devtoolset-9/root/usr/bin/cc
  -- Check for working C compiler: /opt/rh/devtoolset-9/root/usr/bin/cc -- works
  -- Detecting C compiler ABI info
  -- Detecting C compiler ABI info - done
  -- Check for working CXX compiler: /opt/rh/devtoolset-9/root/usr/bin/c++
  -- Check for working CXX compiler: /opt/rh/devtoolset-9/root/usr/bin/c++ -- works
  -- Detecting CXX compiler ABI info
  -- Detecting CXX compiler ABI info - done
  generate swig wrap files ...
  /home/krenx/programming/github-ssh/openctp-ctp-python/CTPAPI/lin64/ThostFtdcTraderApi.h:30: Warning 514: Director base class CThostFtdcTraderSpi has no virtual destructor.
  /home/krenx/programming/github-ssh/openctp-ctp-python/CTPAPI/lin64/ThostFtdcMdApi.h:30: Warning 514: Director base class CThostFtdcMdSpi has no virtual destructor.
  -- Configuring done
  -- Generating done
  -- Build files have been written to: /home/krenx/programming/github-ssh/openctp-ctp-python/CTPAPI/build
  [krenx]$ make
  Scanning dependencies of target _thostmduserapi
  [ 50%] Building CXX object CMakeFiles/_thostmduserapi.dir/thostmduserapi_wrap.cxx.o
  Linking CXX shared library _thostmduserapi.so
  [ 50%] Built target _thostmduserapi
  Scanning dependencies of target _thosttraderapi
  [100%] Building CXX object CMakeFiles/_thosttraderapi.dir/thosttraderapi_wrap.cxx.o
  Linking CXX shared library _thosttraderapi.so
  [100%] Built target _thosttraderapi
  [krenx]$
  ```
  
  ### 技术交流
  
  QQ群：546977604
