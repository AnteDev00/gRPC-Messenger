#pragma once
#include "client_includes.h"
#include "client_using.h"

class Client {
public:
  // Calls InitializeLogger() and sets up the client stub.
  Client(std::shared_ptr<Channel> channel);
  // Assembles the client's payload, logs reuqest, sends it and presents the 
  // response back from the server, and logs the response.
  void SendRpcMessage(const std::string& message);

private:
  void InitializeLogger();
  void SetTimestamp(MessageRequest* request);
  void SetRequest(const std::string& message, MessageRequest* request);
  void LogRequest(const MessageRequest& request);
  void LogResponse(const MessageResponse& response, const Status& status);

private:
  std::unique_ptr<Messenger::Stub> stub_;
  std::shared_ptr<spdlog::logger> file_logger_;
};