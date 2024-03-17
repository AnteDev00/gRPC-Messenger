# GrpcMessenger

GrpcMessenger is a gRPC-based client-server messaging application in C++.

## Prerequisites
Before building and running GrpcMessenger, ensure you have the following tools and libraries installed:

- [Conan](https://conan.io/): Dependency manager for C/C++ projects.
- [CMake](https://cmake.org/): Cross-platform build system.
- [Visual Studio](https://visualstudio.microsoft.com/): Development environment with MSVC compiler (other C++ compilers might work, but haven't been tested).

## Libraries/frameworks Used
GrpcMessenger utilizes the following libraries:

- [gRPC](https://grpc.io/): A high-performance RPC framework.
- [Protocol Buffers](https://developers.google.com/protocol-buffers): A language-neutral, platform-neutral extensible mechanism for serializing structured data.
- [Spdlog](https://github.com/gabime/spdlog): A fast C++ logging library.

## Tools Used
In addition to the libraries, GrpcMessenger also utilizes the following tools:

- Protocol Buffers Compiler: Used to generate gRPC service stubs and message serialization code.
- CMake: Used for configuring the build process and generating platform-specific build files.

## Building and Running
To build and run GrpcMessenger, follow these steps:

1. Install the required prerequisites listed above.
2. Clone this repository to your local machine.
3. Navigate to the project directory and then to the `scripts` directory.
4. Run the build script provided to download dependencies, configure the build, and compile the project.
5. After successful compilation, you can find the executable files in the `build/{build_type}` directory.
6. Run the server executable and then client executable

## Contributing
Contributions are welcome! If you'd like to contribute to GrpcMessenger, please fork the repository, make your changes, and submit a pull request.

## License
This project is licensed under the [MIT License](LICENSE).
