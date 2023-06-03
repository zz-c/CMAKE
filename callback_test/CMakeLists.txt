include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/src SRC_LIST)

add_executable (callback_test ${SRC_LIST})




