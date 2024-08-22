set ( CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /SUBSYSTEM:WINDOWS /ENTRY:WinMainCRTStartup" ) 
set(SRC_LIST "demo01.cpp" )
add_executable (windows_test ${SRC_LIST})

# set_target_properties(windows_test PROPERTIES LINK_FLAGS "/SUBSYSTEM:WINDOWS")
# set_target_properties(windows_test PROPERTIES LINK_FLAGS_DEBUG "/SUBSYSTEM:CONSOLE")

MESSAGE(STATUS "CMAKE_BUILD_TYPE: ${CMAKE_BUILD_TYPE}")
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    # set_target_properties(windows_test PROPERTIES LINK_FLAGS "/SUBSYSTEM:WINDOWS")
    set_target_properties(windows_test PROPERTIES LINK_FLAGS_DEBUG "/SUBSYSTEM:CONSOLE")
else()
    set_target_properties(windows_test PROPERTIES LINK_FLAGS "/SUBSYSTEM:WINDOWS")
endif()
