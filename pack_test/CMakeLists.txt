project(pack_test)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
message( STATUS "CMAKE_VERSION    = ${CMAKE_VERSION}" )
# 设置 CMake 搜索路径
list(APPEND CMAKE_PREFIX_PATH "G:/project/c/CMAKE/out/build/x64-Debug/pack")

# 查找 ProjectA
find_package(ProjectA REQUIRED)

# 使用 ProjectA 库
add_executable(pack_test "src/main.cpp")
target_link_libraries(pack_test ProjectA)


