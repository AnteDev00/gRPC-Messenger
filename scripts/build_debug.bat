:: DEBUG BUILD SCRIPT

@ECHO ON
:: Set BASEDIR to the project's root directory 
set "BASEDIR=%~dp0.."
PUSHD %BASEDIR%

:: Remove existing build directory
RMDIR /Q /S build

:: Detect Conan profile and install dependencies for DEBUG build
conan profile detect --force
conan install . --build=missing --settings=build_type=Debug --settings=compiler.runtime=static --settings=compiler.cppstd=20

:: Run Conan-generated script so that appropriate lib and tool VERSIONS are used
call "build/generators/conanbuild.bat"

:: Generate grpc and pb files from protoc (protobuf compiler)
protoc src/messenger.proto --cpp_out=build/. --grpc_out=build/. --plugin=protoc-gen-grpc="grpc_plugin/windows/grpc_cpp_plugin.exe"

:: Switch to build directory and run CMake configuration for Debug build
cd build
cmake .. -G "Visual Studio 17 2022" -DCMAKE_TOOLCHAIN_FILE=generators/conan_toolchain.cmake
cmake --build . --config Debug

:: Deactivate conanbuild.bat
call "generators/deactivate_conanbuild.bat"

:: Pause to keep the console window open
pause
