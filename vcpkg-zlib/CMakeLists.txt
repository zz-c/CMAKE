cmake_minimum_required(VERSION 3.10)

project(ZlibExample)

# 设置 CMake 使用 vcpkg 的工具链文件
set(CMAKE_TOOLCHAIN_FILE "E:\\clib\\vcpkg\\scripts\\buildsystems\\vcpkg.cmake" CACHE STRING "")

# 设置 C++ 标准
set(CMAKE_CXX_STANDARD 11)

# 找到并链接 zlib 库
find_package(ZLIB REQUIRED)

message(STATUS "ZLIB Found: ${ZLIB_FOUND}")
message(STATUS "ZLIB Includes: ${ZLIB_INCLUDE_DIRS}")
message(STATUS "ZLIB Libraries: ${ZLIB_LIBRARIES}")

add_executable(main "main.cpp")

# 链接 zlib 库
target_link_libraries(main PRIVATE ZLIB::ZLIB)

# 在 Windows 上需要定义宏
if(WIN32)
    target_compile_definitions(main PRIVATE ZLIB_WINAPI)
endif()
