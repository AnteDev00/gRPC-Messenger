from conan import ConanFile
from conan.tools.cmake import cmake_layout

class AmagiTaskRecipe(ConanFile):
    settings = "os", "compiler", "build_type", "arch"
    generators = "CMakeDeps", "CMakeToolchain"

    def requirements(self):
        self.requires("grpc/[>1.54.2]")
        self.requires("spdlog/[>1.12.0]")
        self.requires("protobuf/[>3.21.11]")

    def build_requirements(self):
        self.tool_requires("cmake/[>3.22.5]")
        self.tool_requires("protobuf/[>3.21.11]")
    
    def layout(self):
        cmake_layout(self)
        
    