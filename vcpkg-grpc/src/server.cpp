#include <grpcpp/grpcpp.h>
#include "helloworld.grpc.pb.h"

class GreeterServiceImpl final : public Greeter::Service {
    grpc::Status SayHello(grpc::ServerContext* context, const HelloRequest* request, HelloReply* reply) override {
        reply->set_message("Hello zz, " + request->name());
        return grpc::Status::OK;
    }
};

int main() {
    grpc::ServerBuilder builder;
    GreeterServiceImpl service;
    builder.AddListeningPort("0.0.0.0:50051", grpc::InsecureServerCredentials());
    builder.RegisterService(&service);
    std::unique_ptr<grpc::Server> server(builder.BuildAndStart());
    server->Wait();
    return 0;
}