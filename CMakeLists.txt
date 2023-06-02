# CMakeList.txt: 顶层 CMake 项目文件，在此处执行全局配置
# 并包含子项目。
#
cmake_minimum_required (VERSION 3.8)

# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project ("CMAKE")

# 包含子项目。
add_subdirectory ("cmake_test")
add_subdirectory ("ffmpeg_test")
add_subdirectory ("sdl_test")
add_subdirectory ("thread_test")
add_subdirectory ("ffmpeg_sdl_test")
add_subdirectory ("socket_server_test")
add_subdirectory ("socket_client_test")
add_subdirectory ("socket_udp_server_test")
add_subdirectory ("socket_udp_client_test")
add_subdirectory ("select_test")
add_subdirectory ("opencv_test")
add_subdirectory ("dxgi_test")
add_subdirectory ("dxgi_record_test")

