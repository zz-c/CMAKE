cmake_minimum_required (VERSION 3.8)
project(hellojnilib)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/src SRC_LIST)
link_directories(${CMAKE_CURRENT_SOURCE_DIR}/lib)

add_library(hellojnilib SHARED ${SRC_LIST})

target_link_libraries(hellojnilib msvc_lib)




