project(python_call)
include_directories("C:/Program Files/Python312/include")
link_directories("C:/Program Files/Python312/libs")
add_executable(python_call example.cpp)
target_link_libraries(python_call python312_d)



