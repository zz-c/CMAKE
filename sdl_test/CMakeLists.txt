# CMakeList.txt: sdl_test 的 CMake 项目，在此处包括源代码并定义
# 项目特定的逻辑。
#

# 设置sdl头文件的查找位置

# 设置sdl库的查找目录 jar

# 将源代码添加到此项目的可执行文件。
add_executable (sdl_test "main.cpp" "main.h")
#设置编译链接的库ffmpeg


if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET sdl_test PROPERTY CXX_STANDARD 20)
endif()

# TODO: 如有需要，请添加测试并安装目标。
