# 安装 gRPC（默认 x64，如需 x86 替换为 x86-windows）
.\vcpkg install grpc:x64-windows

# 可选：安装 protobuf（gRPC 依赖）
.\vcpkg install protobuf:x64-windows




E:\clib\vcpkg\packages\protobuf_x64-windows\tools\protobuf>


protoc --cpp_out=. helloworld.proto
protoc --grpc_out=. --plugin=protoc-gen-grpc="E:\clib\vcpkg\packages\grpc_x64-windows\tools\grpc\grpc_cpp_plugin.exe" helloworld.proto
