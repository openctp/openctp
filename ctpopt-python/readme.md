# CTP股票期权Python接口

## 直接使用

openctp提供了pip install和文件下载两种方法安装CTPOPT-Python库，可以直接使用，均支持3.5.8~3.7.0各个版本。

### pip install方式

```bash
pip install openctp-ctpopt==3.7.0.* -i https://pypi.tuna.tsinghua.edu.cn/simple --trusted-host=pypi.tuna.tsinghua.edu.cn
```

### 文件下载方式

[CTPOPT-Python接口下载](http://openctp.cn/CTPAPI-Python.html)

## 自己编译

CTPOPT-Python使用Swig技术开发，可以自己按以下步骤编译，需要安装swig等组件，详细攻略见：[CTPAPI-Python开发攻略](https://zhuanlan.zhihu.com/p/688672132)。

本仓库选用的是CTPOPT-3.7.0，如需编译其它版本，请下载相应的CTPOPT文件覆盖对应目录下的CTPOPT文件。

### 准备

- 安装VirtualStudio、Swig、Python3、boost、cmake，boost库用到的是locale库，用来转换字符集。
- 设置BOOST_INCLUDE、BOOST_LIB环境变量分别指向相应库的头文件及库目录，如E:\boost_1_73_0、E:\boost_1_73_0\stage\lib。
- 设置PYTHON_INCLUDE、PYTHON_LIB环境变量分别指向相应库的头文件及库目录，如C:\Program Files\Python312\include、C:\Program Files\Python312\libs。

### Windows编译

编译成功后，将生成的文件连同CTPOPT的dll（soptthosttraderapi.dll、soptthostmduserapi.dll）拷贝到你的程序运行目录下即可：

- soptthosttraderapi.py
- soptthostmduserapi.py
- _soptthostmduserapi.pyd
- _soptthosttraderapi.pyd

#### Win32

```
cd CTPOPT
mkdir build
cd build
cmake ..
cmake --build . --config Release
```

#### Win64

```
cd CTPOPT
mkdir build
cd build
cmake -A x64 ..
cmake --build . --config Release
```

### Linux编译

编译成功后，将生成的文件连同CTPOPT的so文件（soptthosttraderapi.so、soptthostmduserapi.so）拷贝到你的程序运行目录下即可：

- soptthosttraderapi.py

- soptthostmduserapi.py

- _soptthostmduserapi.so

- _soptthosttraderapi.so
  
  ```
  cd CTPOPT
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
  /home/krenx/programming/github-ssh/openctp-ctpopt-python/CTPOPT/lin64/ThostFtdcTraderApi.h:30: Warning 514: Director base class CThostFtdcTraderSpi has no virtual destructor.
  /home/krenx/programming/github-ssh/openctp-ctpopt-python/CTPOPT/lin64/ThostFtdcMdApi.h:30: Warning 514: Director base class CThostFtdcMdSpi has no virtual destructor.
  -- Configuring done
  -- Generating done
  -- Build files have been written to: /home/krenx/programming/github-ssh/openctp-ctpopt-python/CTPOPT/build
  [krenx]$ make
  Scanning dependencies of target _soptthostmduserapi
  [ 50%] Building CXX object CMakeFiles/_soptthostmduserapi.dir/soptthostmduserapi_wrap.cxx.o
  Linking CXX shared library _soptthostmduserapi.so
  [ 50%] Built target _soptthostmduserapi
  Scanning dependencies of target _soptthosttraderapi
  [100%] Building CXX object CMakeFiles/_soptthosttraderapi.dir/soptthosttraderapi_wrap.cxx.o
  Linking CXX shared library _soptthosttraderapi.so
  [100%] Built target _soptthosttraderapi
  [krenx]$
  ```
  
  ### 技术交流

- QQ群：546977604

- 
