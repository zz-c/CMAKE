﻿# CMakeList.txt CMake 项目，在此处包括源代码并定义
# 项目特定的逻辑。


set(SRC_LIST "main.cpp" )
add_executable (shareptr_test ${SRC_LIST})


if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET shareptr_test PROPERTY CXX_STANDARD 20)
endif()

# TODO: 如有需要，请添加测试并安装目标。

