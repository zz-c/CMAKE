project(ProjectA)
set(CMAKE_INSTALL_PREFIX "F:/install")
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

# 创建一个静态库或者共享库
add_library(ProjectA STATIC "src/SMath.cpp")

message(STATUS "Installation Prefix: ${CMAKE_INSTALL_PREFIX}")
# 安装库文件，头文件以及CMake配置文件
install(TARGETS ProjectA DESTINATION lib)
install(DIRECTORY include/ DESTINATION include)
# 打印安装完成后的路径
message(STATUS "ProjectA library will be installed to: ${CMAKE_INSTALL_PREFIX}/lib")
message(STATUS "Header files will be installed to: ${CMAKE_INSTALL_PREFIX}/include")

# 导出 CMake 配置文件
export(TARGETS ProjectA FILE ProjectAConfig.cmake)





