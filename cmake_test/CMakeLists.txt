# CMakeList.txt: sdl_test 的 CMake 项目，在此处包括源代码并定义
# 项目特定的逻辑。
#

message("this is my cmake test")
message(STATUS "this is my STATUS TEST")
message(WARNING  "this is my WARNING TEST")
 
message("1.PROJECT_BINARY_DIR = ${PROJECT_BINARY_DIR}")
option (USE_MYDEF "Use provided math implementation" ON)
set(VAR "VAR_NEW")
message("1.PROJECT_BINARY_DIR = ${VAR}")
# 将源代码添加到此项目的可执行文件。
set(SRC_LIST "main.cpp" "main.h")
# 指定可执行文件存放目录
SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)
add_executable (cmake_test ${SRC_LIST})


if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET cmake_test PROPERTY CXX_STANDARD 20)
endif()

# TODO: 如有需要，请添加测试并安装目标。

