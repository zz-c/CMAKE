include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
include_directories(3rdpart/glfw/include/)
include_directories(3rdpart/glad/include/)

aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/src SRC_LIST)

link_directories(3rdpart/glfw/lib/)

add_executable (opengl_test ${SRC_LIST} 3rdpart/glad/src/glad.c)

target_link_libraries(opengl_test glfw3)

