# CMakeList.txt CMake 项目，在此处包括源代码并定义
# 项目特定的逻辑。

set ( CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /SUBSYSTEM:WINDOWS /ENTRY:WinMainCRTStartup" ) 
set(SRC_LIST "main.cpp" )
add_executable (windows_test ${SRC_LIST})

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET windows_test PROPERTY CXX_STANDARD 20)
endif()

# TODO: 如有需要，请添加测试并安装目标。

