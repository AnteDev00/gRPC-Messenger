cmake_minimum_required(VERSION 3.15)
set(CMAKE_CXX_STANDARD 20)
project(GrpcMessenger)

# Required packages
find_package(protobuf REQUIRED)
find_package(grpc CONFIG REQUIRED)
find_package(spdlog REQUIRED)

# Path to the generated protobuf files
set(PROTO_FILES_DIR ${CMAKE_CURRENT_BINARY_DIR}/src)

# Source files for executables
set(CLIENT_SOURCES src/client_main.cpp src/client.cpp)
set(SERVER_SOURCES src/server_main.cpp src/server.cpp)
# Create executables
add_executable(GrpcClient ${CLIENT_SOURCES})
add_executable(GrpcServer ${SERVER_SOURCES})

# Create library target for protobuf-generated files
add_library(ProtobufLib ${PROTO_FILES_DIR}/messenger.grpc.pb.cc ${PROTO_FILES_DIR}/messenger.pb.cc)

# Link protobuf and grpc libs to ProtobufLibrary
target_link_libraries(ProtobufLib PUBLIC protobuf::protobuf grpc::grpc)

# Link all libs to executables
target_link_libraries(GrpcClient PRIVATE 
					  ProtobufLib abseil::abseil spdlog::spdlog)
target_link_libraries(GrpcServer PRIVATE 
					  ProtobufLib abseil::abseil spdlog::spdlog)

# Include generated protobuf files directory
target_include_directories(ProtobufLib PUBLIC ${CMAKE_CURRENT_BINARY_DIR})




