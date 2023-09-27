include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

link_directories("G:/project/c/CMAKE/out/build/x64-Debug/msvc_dll")

add_executable (msvc_dll_test "src/main.cpp" "include/SMath.h" )


target_link_libraries(msvc_dll_test msvc_dll)


