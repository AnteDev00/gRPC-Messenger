#include "client_includes.h" // can be removed, included in client.h
#include "client_using.h" // can be removed, included in client.h
#include "client.h"

ABSL_FLAG(std::string, target, "localhost:50051", "Server address");
ABSL_FLAG(std::string, message, "Hi server!", "Client's message to server");

int main(int argc, char** argv) {
  // logs info level messages and above
  spdlog::set_level(spdlog::level::info); 
  absl::ParseCommandLine(argc, argv);
  // Instantiate the client. It requires a channel, out of which the actual RPCs
  // are created. This channel models a connection to an endpoint specified by
  // the argument "--target="
  std::string connection_target = absl::GetFlag(FLAGS_target);
  // We indicate that the channel isn't authenticated (use of
  // InsecureChannelCredentials()).
  Client client(grpc::CreateChannel(connection_target, grpc::InsecureChannelCredentials()));
  // "--message" is the other possible argument, for custom message
  std::string message = absl::GetFlag(FLAGS_message);
  client.SendRpcMessage(message);

  return 0;
}
