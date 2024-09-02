project(audio_win_test)

add_executable (${PROJECT_NAME} "main.cpp")

# 链接 Windows 多媒体库
target_link_libraries(${PROJECT_NAME} winmm)

