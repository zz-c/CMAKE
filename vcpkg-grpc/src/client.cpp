#include <grpcpp/grpcpp.h>
#include "helloworld.grpc.pb.h"

int main() {
	auto channel = grpc::CreateChannel("localhost:50051", grpc::InsecureChannelCredentials());
	auto stub = Greeter::NewStub(channel);
	HelloRequest request;
	request.set_name("World");
	HelloReply reply;
	grpc::ClientContext context;
	stub->SayHello(&context, request, &reply);
	std::cout << "Server says: " << reply.message() << std::endl;
	return 0;
}