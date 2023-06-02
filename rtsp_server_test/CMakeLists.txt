


set(SRC_LIST "main.cpp" )
add_executable (rtsp_server_test ${SRC_LIST})
target_link_libraries(rtsp_server_test ws2_32)



