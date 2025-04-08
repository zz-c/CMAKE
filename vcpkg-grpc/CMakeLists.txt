project(grpc_example)

# 关键：指定 vcpkg 工具链
set(CMAKE_TOOLCHAIN_FILE "E:\\clib\\vcpkg\\scripts\\buildsystems\\vcpkg.cmake" CACHE STRING "")

# 查找 gRPC 和 Protobuf
find_package(gRPC REQUIRED)
find_package(Protobuf REQUIRED)

message(STATUS "gRPC Found: ${gRPC_FOUND}")
message(STATUS "Protobuf Found: ${Protobuf_FOUND}")

set(PROTO_PATH ${CMAKE_CURRENT_SOURCE_DIR}/protos)
file(GLOB PROTO_FILES ${PROTO_PATH}/*.cc)
include_directories(${PROTO_PATH})

message(STATUS "PROTO_FILES: ${PROTO_FILES}")

foreach(TARGET client server)
    add_executable(${TARGET} "src/${TARGET}.cpp"
        ${HW_PROTO_SRCS}
        ${HW_GRPC_SRCS}
        ${PROTO_FILES})
 
    target_link_libraries(${TARGET}
        gRPC::grpc++
        gRPC::grpc++_reflection
        protobuf::libprotobuf)
endforeach()