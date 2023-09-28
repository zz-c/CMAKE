include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

link_directories("G:/project/c/CMAKE/out/build/x64-Debug/msvc_lib")

add_executable (msvc_lib_test "src/main.cpp" "include/SMath.h" )


target_link_libraries(msvc_lib_test msvc_lib)


