#include <iostream>
#include <memory>
#include <string>
#include <chrono>

#include "absl/flags/flag.h"
#include "absl/flags/parse.h"
#include "absl/strings/str_format.h"

#include <spdlog/spdlog.h>
#include <spdlog/sinks/basic_file_sink.h> // Include file sink for writing to a text file

#include <grpcpp/ext/proto_server_reflection_plugin.h>
#include <grpcpp/grpcpp.h>
#include <grpcpp/health_check_service_interface.h>

#include "src/messenger.grpc.pb.h"  