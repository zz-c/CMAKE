cmake_minimum_required (VERSION 3.8)
project(hellojni)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
if(WIN32)
    message(STATUS "This is a Windows system.")
    include_directories("C:/Program Files/Java/jdk1.8.0_31/include")
    include_directories("C:/Program Files/Java/jdk1.8.0_31/include/win32")
else()
    message(STATUS "This is not a Windows system.")
    include_directories("/usr/lib/jvm/java-8-openjdk-amd64/include")
    include_directories("/usr/lib/jvm/java-8-openjdk-amd64/include/linux")
endif()
aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/src SRC_LIST)

#add_executable (hellojni ${SRC_LIST})
add_library(hellojni SHARED ${SRC_LIST})



