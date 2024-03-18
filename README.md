# GrpcMessenger

GrpcMessenger is a gRPC-based client-server messaging application in C++.

## Prerequisites

Before building and running GrpcMessenger, ensure you have the following tools and libraries installed:

- [Conan](https://conan.io/): Dependency manager for C/C++ projects.
- [CMake](https://cmake.org/): Cross-platform build system.
- [Visual Studio](https://visualstudio.microsoft.com/): Development environment with MSVC compiler. The project is set up to use the "Visual Studio 17 2022" generator for CMake (`cmake .. -G "Visual Studio 17 2022"`). Other CMake generators might also work, but they haven't been tested and may require modifications to the build scripts.

## Libraries/Frameworks Used

GrpcMessenger utilizes the following libraries:

- [gRPC](https://grpc.io/): A high-performance RPC framework, used in combination with Protocol Buffers.
- [Protocol Buffers](https://developers.google.com/protocol-buffers): A language-neutral, platform-neutral extensible mechanism for serializing structured data.
- [Spdlog](https://github.com/gabime/spdlog): A fast C++ logging library.

## Tools Used

In addition to the libraries, GrpcMessenger also utilizes the following tools:

- [Protocol Buffers Compiler](https://developers.google.com/protocol-buffers): Used to generate code for message serialization and gRPC service communication.
- [CMake](https://cmake.org/): Used for configuring the build process and generating platform-specific build files.

## Building and Running

To build and run GrpcMessenger, follow these steps:

1. Install the required prerequisites listed above.
2. Clone this repository to your local machine.
3. Navigate to the project directory and then to the `scripts` directory.
4. Run the build script provided to download dependencies, configure the build, and compile the project.
5. After successful compilation, you can find the executable files in the `build/{build_type}` directory.
6. Run the server executable and then the client executable.

## Contributing

Contributions are welcome! If you'd like to contribute to GrpcMessenger, please fork the repository, make your changes, and submit a pull request.

## License

- This project, excluding the provided gRPC plugin, is governed by the terms of the MIT License. For details, please refer to the [MIT License](LICENSE) file.
- The gRPC plugin is licensed under the Apache License Version 2.0. For comprehensive license details, please refer to the official repository at [grpc/grpc](https://github.com/grpc/grpc).
