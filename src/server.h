#include "server_includes.h" 
#include "server_using.h"

// Logic and data behind the server's behavior.
class MessengerImpl final : public Messenger::Service {
public:
  // Calls InitializeLogger()
  MessengerImpl();
  // Server side SendRpcMessage implementation
  Status SendRpcMessage(ServerContext* context, const MessageRequest* request,
    MessageResponse* response) override;

private:
  void InitializeLogger();
  void LogReceivedMessage(const MessageRequest* request);
  void SetResponse(const MessageRequest* request, MessageResponse* response);
  void LogSentMessage(const MessageResponse* response);
  Timestamp CreateTimestamp();

private:
  std::shared_ptr<spdlog::logger> file_logger_;
};

