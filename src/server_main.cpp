#include "server_includes.h" // can be removed, included in server.h
#include "server_using.h" // can be removed, included in server.h
#include "server.h"

// Command-line arguments for specifying server port and IP address and 
// custom message (defined in server.cpp).
ABSL_FLAG(uint16_t, port, 50051, "Default Server port");
ABSL_FLAG(std::string, IP, "0.0.0.0", "Default Server IP address");

void RunServer() {

  std::string server_address = absl::GetFlag(FLAGS_IP) + ":" + std::to_string(absl::GetFlag(FLAGS_port));
  MessengerImpl service;

  grpc::EnableDefaultHealthCheckService(true);
  grpc::reflection::InitProtoReflectionServerBuilderPlugin();
  ServerBuilder builder;
  // Listen on the given address without any authentication mechanism.
  builder.AddListeningPort(server_address, grpc::InsecureServerCredentials());
  // Register "service" as the instance through which we'll communicate with
  // clients. In this case it corresponds to an *synchronous* service.
  builder.RegisterService(&service);
  // Finally assemble the server.
  std::unique_ptr<Server> server(builder.BuildAndStart());
  spdlog::info("Server listening on {}", server_address);

  // Wait for the server to shutdown. Note that some other thread must be
  // responsible for shutting down the server for this call to ever return.
  server->Wait();
}

int main(int argc, char** argv) {
  // Logs info level messages and above.
  spdlog::set_level(spdlog::level::info); 
  absl::ParseCommandLine(argc, argv);
  RunServer();
  return 0;
}
