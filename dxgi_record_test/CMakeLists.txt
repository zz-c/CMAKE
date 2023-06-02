include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
include_directories("E:/clib/ffmpeg-3.4.2/include")

link_directories("E:/clib/ffmpeg-3.4.2/lib")
#set(SRC_LIST "main.cpp" )
aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/src SRC_LIST)


add_executable (dxgi_record_test ${SRC_LIST})

target_link_libraries(dxgi_record_test avutil avcodec avfilter avdevice avformat postproc swresample swscale d3d11)

