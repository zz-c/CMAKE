# CMakeList.txt CMake 项目，在此处包括源代码并定义
# 项目特定的逻辑。

include_directories("E:/clib/libevent-2.1.12-stable/include")
include_directories("E:/clib/libevent-2.1.12-stable/build/include")

link_directories("E:/clib/libevent-2.1.12-stable/build/lib/Debug")

set(SRC_LIST "main.cpp" )
add_executable (libevent_test ${SRC_LIST})
target_link_libraries(libevent_test ws2_32 event event_core event_extra event_openssl)


if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET libevent_test PROPERTY CXX_STANDARD 20)
endif()

# TODO: 如有需要，请添加测试并安装目标。

