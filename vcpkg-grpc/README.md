# ��װ gRPC��Ĭ�� x64������ x86 �滻Ϊ x86-windows��
.\vcpkg install grpc:x64-windows

# ��ѡ����װ protobuf��gRPC ������
.\vcpkg install protobuf:x64-windows




E:\clib\vcpkg\packages\protobuf_x64-windows\tools\protobuf>


protoc --cpp_out=. helloworld.proto
protoc --grpc_out=. --plugin=protoc-gen-grpc="E:\clib\vcpkg\packages\grpc_x64-windows\tools\grpc\grpc_cpp_plugin.exe" helloworld.proto
