include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
include_directories("G:/project/c/study/jsoncpp-1.9.5/include")

link_directories("E:/clib/jsoncpp-1.9.5/lib/Debug")

aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/src SRC_LIST)

add_executable (json_test ${SRC_LIST})

target_link_libraries(json_test jsoncpp)




