﻿# CMakeList.txt: sdl_test 的 CMake 项目，在此处包括源代码并定义
# 项目特定的逻辑。
#
add_definitions (-DCOMPILE_M1)
add_definitions (-DCOMPILE_M2=0x100)
 
add_compile_definitions (COMPILE_M3=0x200)
 

message("cmake_test PROJECT_BINARY_DIR = ${PROJECT_BINARY_DIR}")
option (USE_MYDEF "Use provided math implementation" ON)
message("USE_MYDEF = ${USE_MYDEF}")

option(TEST_FLAG "单元测试开关" OFF)
message("TEST_FLAG = ${TEST_FLAG}")

if(USE_MYDEF)
    message("add_compile_definitions COMPILE_M4")
    add_compile_definitions (COMPILE_M4)
endif()

set(VAR_SUB "VAR_SUB_TEST")
message("cmake_test VAR_SUB = ${VAR_SUB}")
message("cmake_test VAR_MAIN = ${VAR_MAIN}")
# 将源代码添加到此项目的可执行文件。
set(SRC_LIST "main.cpp" )
# 指定可执行文件存放目录
SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)
add_executable (cmake_test ${SRC_LIST})

INSTALL(
        TARGETS cmake_test
        RUNTIME DESTINATION bin
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib
)


if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET cmake_test PROPERTY CXX_STANDARD 20)
endif()

# TODO: 如有需要，请添加测试并安装目标。

