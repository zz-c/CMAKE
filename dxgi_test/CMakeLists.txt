﻿
add_compile_definitions (UNICODE)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
include_directories("E:/clib/opencv-3.4.10/include")

link_directories("E:/clib/opencv-3.4.10/x64/vc15/lib")
#set(SRC_LIST "main.cpp" )
#aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/src SRC_LIST)


add_executable (dxgi_test src/main.cpp src/DxgiCapture.cpp)
target_link_libraries(dxgi_test opencv_world3410d d3d11)

add_executable (d3d9_test src/mainD3d9.cpp)
target_link_libraries(d3d9_test opencv_world3410d)

add_executable (dgi_test src/mainDgi.cpp)
target_link_libraries(dgi_test opencv_world3410d)

# 有问题
#add_executable (winapi_test src/mainWinapi.cpp)
#target_link_libraries(winapi_test opencv_world3410d)