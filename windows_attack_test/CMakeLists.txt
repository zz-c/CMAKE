set ( CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /SUBSYSTEM:WINDOWS /ENTRY:WinMainCRTStartup" ) 
set(SRC_LIST "demo.cpp" )
add_executable (windows_attack_test ${SRC_LIST})

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET windows_test PROPERTY CXX_STANDARD 20)
endif()



