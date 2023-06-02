include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
include_directories("E:/clib/opencv-3.4.10/include")

link_directories("E:/clib/opencv-3.4.10/x64/vc15/lib")
#set(SRC_LIST "main.cpp" )
aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/src SRC_LIST)


add_executable (dxgi_test ${SRC_LIST})

target_link_libraries(dxgi_test opencv_world3410d d3d11)

