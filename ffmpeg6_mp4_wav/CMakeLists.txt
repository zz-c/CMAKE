# 设置ffmpeg头文件的查找位置
include_directories("E:/clib/ffmpeg-6.0-full_build-shared/include")
include_directories("E:/clib/SDL2-2.26.5/include")

link_directories("E:/clib/ffmpeg-6.0-full_build-shared/lib")
link_directories("E:/clib/SDL2-2.26.5/lib/x64")
# 将源代码添加到此项目的可执行文件。
add_executable (ffmpeg6_mp4_wav "main03.cpp")
#设置编译链接的库ffmpeg
target_link_libraries(ffmpeg6_mp4_wav avutil avcodec avfilter avdevice avformat postproc swresample swscale SDL2 SDL2main)

