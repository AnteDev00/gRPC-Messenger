#include "client.h"

Client::Client(std::shared_ptr<Channel> channel) 
  : stub_(Messenger::NewStub(channel)) {
    InitializeLogger();
  }

void Client::SendRpcMessage(const std::string& message) {
    // Context for the client. It could be used to convey extra information to
    // the server and/or tweak certain RPC behaviors.
    ClientContext context;
    // Data we are receiving from the server.
    MessageResponse response;
    // Data we are sending to the server.
    MessageRequest request;

    SetTimestamp(&request);
    SetRequest(message, &request);

    LogRequest(request);
    Status status = stub_->SendRpcMessage(&context, request, &response); // The actual RPC.
    LogResponse(response, status);
  }

void Client::InitializeLogger() {
  file_logger_ = spdlog::basic_logger_mt("file_logger", "client_logs.txt");
  file_logger_->set_pattern("[%Y-%m-%d %H:%M:%S.%e] [%l] %v");
  file_logger_->flush_on(spdlog::level::trace); // Flush after every log message.
}

void Client::SetTimestamp(MessageRequest* request) {
  // Calculate timestamp .
  system_clock::time_point now = system_clock::now();
  seconds sec = duration_cast<seconds>(now.time_since_epoch());
  nanoseconds nsec = now.time_since_epoch() - sec;
  // Assignt timestamp to the request.
  Timestamp* timestamp = new Timestamp();
  timestamp->set_seconds(sec.count());
  timestamp->set_nanos(nsec.count());
  request->mutable_timestamp()->CopyFrom(*timestamp);

  delete timestamp;
}

void Client::SetRequest(const std::string& message, MessageRequest* request) {
  request->set_message(message);
}

void Client::LogRequest(const MessageRequest& request) {
  // Console and file logging.
  spdlog::info("[Sending] [Contents='{}'] [Timestamp={:d}.{:09d}] ",
    request.message(), request.timestamp().seconds(), request.timestamp().nanos());
  file_logger_->info("[Sending] [Contents='{}'] [Timestamp={:d}.{:09d}] ",
    request.message(), request.timestamp().seconds(), request.timestamp().nanos());
}

void Client::LogResponse(const MessageResponse& response, const Status& status) {
  // Setting level of logging.
  bool success = status.ok();
  spdlog::level::level_enum log_level = success ? spdlog::level::info : spdlog::level::err;
  // Console and file logging.
  spdlog::log(log_level, "[Received={}] [Contents='{}'] [Timestamp={:d}.{:09d}] ",
    success, response.message(), response.timestamp().seconds(), response.timestamp().nanos());
  file_logger_->log(log_level, "[Received={}] [Contents='{}'] [Timestamp={:d}.{:09d}] ",
    success, response.message(), response.timestamp().seconds(), response.timestamp().nanos());
  // In case of error:
  if (!success) {
    spdlog::error("RPC Failed. {}: {} ", std::to_string(status.error_code()), status.error_message());
    file_logger_->error("RPC Failed. {}: {} ", std::to_string(status.error_code()), status.error_message());
  }
}
