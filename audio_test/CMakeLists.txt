# 设置文件的查找位置
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
include_directories("E:/clib/SDL2-2.26.5/include")
# 设置sdl库的查找目录
link_directories("E:/clib/SDL2-2.26.5/lib/x64")

aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/src SRC_LIST)
add_executable (audio_test ${SRC_LIST})
#设置编译链接的库ffmpeg
target_link_libraries(audio_test SDL2 SDL2main)



