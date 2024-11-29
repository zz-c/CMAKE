set(BOOST_ROOT "E:/clib/boost_1_79_0")

find_package(Boost REQUIRED)
message("Boost version: ${Boost_VERSION}")
message("Boost_INCLUDE_DIRS: ${Boost_INCLUDE_DIRS}")
message("Boost_LIBRARY_DIRS: ${Boost_LIBRARY_DIRS}")
message("Boost_LIBRARIES: ${Boost_LIBRARIES}")


include_directories(${CMAKE_CURRENT_SOURCE_DIR})
# 包含Boost头文件目录
include_directories(${Boost_INCLUDE_DIRS})

# 链接Boost库目录
link_directories(${Boost_LIBRARY_DIRS})


aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR} SRC_LIST)

add_executable (boost_test ${SRC_LIST})

target_link_libraries(boost_test ${Boost_LIBRARIES})



