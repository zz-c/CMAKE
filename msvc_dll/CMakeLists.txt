add_definitions (-DSMATH_EXPORT)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)


#add_executable (msvc_dll_main "src/main.cpp" "include/SMath.h" "src/SMath.cpp")

add_library (msvc_dll SHARED "include/SMath.h" "src/SMath.cpp")





