from conan import ConanFile
from conan.tools.cmake import CMakeToolchain, CMake, cmake_layout, CMakeDeps
from conan.tools.files import copy
import os

class pkgRecipe(ConanFile):
    name = "Image_Viewer"
    version = "1.0.0"
    package_type = "application"

    # Optional metadata
    license = "<Put the package license here>"
    author = "<Put your name here> <And your email here>"
    url = "https://github.com/wikko75/Image-Viewer.git"
    description = "My own image viewer using ImGui and OpenCV"
    topics = ("<Put some tag here>", "<here>", "<and here>")

    # Binary configuration
    settings = "os", "compiler", "build_type", "arch"

    # Sources are located in the same place as this recipe, copy them to the recipe
    exports_sources = "CMakeLists.txt", "src/*"

    def build_requirements(self):
        self.tool_requires("cmake/[^3.25]")
        self.tool_requires("ninja/[^1.11]")

    def requirements(self):
        self.requires("imgui/1.91.8-docking")
        self.requires("glfw/3.4")
        self.requires("glew/2.2.0")
        self.requires("opencv/4.11.0")

    def layout(self):
        cmake_layout(self)

    def generate(self):
        deps = CMakeDeps(self)
        deps.generate()
        tc = CMakeToolchain(self)
        tc.generator = "Ninja"
        tc.generate()
        
        self.output.info(f"self.dependencies['imgui'].package_folder = {self.dependencies['imgui'].package_folder}")
        
        copy(self, "*glfw*", os.path.join(self.dependencies["imgui"].package_folder, "res", "bindings"),
             os.path.join(self.source_folder, "bindings"))
        copy(self, "*opengl3*", os.path.join(self.dependencies["imgui"].package_folder, "res", "bindings"),
             os.path.join(self.source_folder, "bindings"))

    def build(self):
        cmake = CMake(self)
        cmake.configure()
        cmake.build()

    # def package(self):
    #     cmake = CMake(self)
    #     cmake.install()

    

    
