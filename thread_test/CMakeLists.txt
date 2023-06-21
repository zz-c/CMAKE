# CMakeList.txt CMake 项目，在此处包括源代码并定义
# 项目特定的逻辑。

include_directories(${CMAKE_CURRENT_SOURCE_DIR})
aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR} SRC_LIST)

add_executable (thread_test ${SRC_LIST})


if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET thread_test PROPERTY CXX_STANDARD 20)
endif()

# TODO: 如有需要，请添加测试并安装目标。

