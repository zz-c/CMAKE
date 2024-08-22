set ( CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /SUBSYSTEM:WINDOWS /ENTRY:WinMainCRTStartup" ) 
set(SRC_LIST "demo01.cpp" )
add_executable (windows_attack_test ${SRC_LIST})

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    set_target_properties(windows_attack_test PROPERTIES LINK_FLAGS_DEBUG "/SUBSYSTEM:CONSOLE")
else()
    set_target_properties(windows_attack_test PROPERTIES LINK_FLAGS "/SUBSYSTEM:WINDOWS")
endif()

