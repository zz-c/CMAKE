# CMakeList.txt CMake 项目，在此处包括源代码并定义
# 项目特定的逻辑。


set(SRC_LIST "main.cpp" )
add_executable (socket_client_test ${SRC_LIST})
target_link_libraries(socket_client_test ws2_32)


if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET socket_client_test PROPERTY CXX_STANDARD 20)
endif()

# TODO: 如有需要，请添加测试并安装目标。

