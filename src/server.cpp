#include "server.h"

ABSL_FLAG(std::string, message, "*Hi client*", "Server's default response to client");

MessengerImpl::MessengerImpl() {
    InitializeLogger();
  }

Status MessengerImpl::SendRpcMessage(ServerContext* context, const MessageRequest* request, MessageResponse* response) {
  LogReceivedMessage(request);
  SetResponse(request, response);
  LogSentMessage(response);
  return Status::OK;
}

void MessengerImpl::InitializeLogger() {
  file_logger_ = spdlog::basic_logger_mt("file_logger", "server_logs.txt");
  file_logger_->set_pattern("[%Y-%m-%d %H:%M:%S.%e] [%l] %v");
  file_logger_->flush_on(spdlog::level::trace); // Flush after every log message
}

void MessengerImpl::LogReceivedMessage(const MessageRequest* request) {
  // Console and file logging
  spdlog::info("[Received] [Contents='{}'] [Timestamp={:d}.{:09d}]",
    request->message(), request->timestamp().seconds(), request->timestamp().nanos());
  file_logger_->info("[Received] [Contents='{}'] [Timestamp={:d}.{:09d}]",
    request->message(), request->timestamp().seconds(), request->timestamp().nanos());
}

void MessengerImpl::SetResponse(const MessageRequest* request, MessageResponse* response) {
  std::string message = absl::GetFlag(FLAGS_message);
  response->set_message(message);
  response->mutable_timestamp()->CopyFrom(CreateTimestamp());
}

void MessengerImpl::LogSentMessage(const MessageResponse* response) {
  // Console and file logging
  spdlog::info("[Sent] [Contents='{}'] [Timestamp={:d}.{:09d}]",
    response->message(), response->timestamp().seconds(), response->timestamp().nanos());
  file_logger_->info("[Sent] [Contents='{}'] [Timestamp={:d}.{:09d}]",
    response->message(), response->timestamp().seconds(), response->timestamp().nanos());
}

Timestamp MessengerImpl::CreateTimestamp() {
  // Number of seconds since January 1, 1970, 00:00:00 UTC
  system_clock::time_point now = system_clock::now();
  seconds sec = duration_cast<seconds>(now.time_since_epoch());
  nanoseconds nsec = now.time_since_epoch() - sec;
  Timestamp timestamp;
  timestamp.set_seconds(sec.count());
  timestamp.set_nanos(nsec.count());
  return timestamp;
}

