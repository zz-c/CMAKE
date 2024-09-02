project(easyx_test)

include_directories("G:/project/c/CMAKE/easyx_test/easyx/include")

# link_directories("G:/project/c/CMAKE/easyx_test/easyx/lib")
# 将源代码添加到此项目的可执行文件。
add_executable ( ${PROJECT_NAME} "main.cpp" )

