﻿cmake_minimum_required (VERSION 3.8)
project(hellojni)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/src SRC_LIST)

#add_executable (hellojni ${SRC_LIST})
add_library(hellojni SHARED ${SRC_LIST})



