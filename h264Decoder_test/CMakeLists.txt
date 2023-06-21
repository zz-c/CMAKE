include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/src SRC_LIST)


add_executable (h264Decoder_test Main.cpp ${SRC_LIST})


FILE(COPY
        E:/clib/data/demo_video_176x144_baseline.h264
        DESTINATION
        ${CMAKE_CURRENT_BINARY_DIR}/
        )

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET h264Decoder_test PROPERTY CXX_STANDARD 20)
endif()
