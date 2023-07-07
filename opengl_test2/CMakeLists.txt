include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
include_directories(3rdpart/glfw/include/)
include_directories(3rdpart/glad/include/)
#glm/
include_directories(3rdpart/)

aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/src SRC_LIST)

link_directories(3rdpart/glfw/lib/)

add_executable (opengl_test2 src/main005.cpp 3rdpart/glad/src/glad.c)#${SRC_LIST}

target_link_libraries(opengl_test2 glfw3)

