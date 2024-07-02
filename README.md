## 系统环境

### CUDA平台

- OS: Ubuntu 20.04.6 LTS
- CUDA: 11.8
- CUDNN: 8.9
- CMake: 3.27.7

### ROCm平台

- OS: kylin V10
- DTK: 23.10.1
- MiOpen: 2.15.3
- CMake: 3.27.7

## 问题现象

重点关注`CMakeLists.txt`中为可执行测试文件设置属性的代码。

```cmake
set_tests_properties(EnvVarTest PROPERTIES ENVIRONMENT "LD_LIBRARY_PATH=/work/Paddle/build/python/paddle/libs:\$LD_LIBRARY_PATH")
```

在CUDA平台下，`\$LD_LIBRARY_PATH`可以被正常解析，执行测试能够获取到cudnn的版本。但在ROCm平台下，`\$LD_LIBRARY_PATH`无法被正确解析，必须改为`$ENV{LD_LIBRARY_PATH}`才能正常执行。

## 测试步骤

### CUDA平台

```shell
cd CTestDemo
mkdir build
cmake .. -DWITH_CUDA=ON
make
ctest -VV
```

### ROCm平台

```shell
cd CTestDemo
mkdir build
cmake .. -DWITH_ROCM=ON
make
ctest -VV
```