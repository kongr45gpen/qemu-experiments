import os
from os.path import join

from conan import ConanFile
from conan.tools.cmake import CMakeToolchain, CMake, cmake_layout, CMakeDeps
from conan.tools.files import copy
from conan.tools.scm import Git
from conan.tools.files import get, chdir, mkdir

class OBCSoftwareRecipe(ConanFile):
    name = "obc-sw"
    version = "1.0"
    revision_mode = "scm"

    # Binary configuration
    settings = "os", "compiler", "build_type", "arch"
    options = {"shared": [True, False], "fPIC": [True, False]}
    default_options = {"shared": False, "fPIC": False, "ecss-services/*:platform_definitions_path": os.path.abspath("original/inc/Platform/")}

    # Sources are located in the same place as this recipe, copy them to the recipe
    exports_sources = "CMakeLists.txt"#, "src/*", "inc/*", "lib/*"
    generators = "CMakeDeps"

    def config_options(self):
        if self.settings.os == "Windows":
            del self.options.fPIC

    def layout(self):
        cmake_layout(self)

    def generate(self):
        tc = CMakeToolchain(self)
        tc.variables["NO_SYSTEM_INCLUDE"] = True
        tc.variables["CMAKE_ASM_COMPILER"] = "arm-none-eabi-gcc"
        tc.variables["CMAKE_C_COMPILER"] = "arm-none-eabi-gcc"
        tc.variables["CMAKE_CXX_COMPILER"] = "arm-none-eabi-g++"
        tc.generate()

    def build(self):
        cmake = CMake(self)
        cmake.configure()
        cmake.build()

    def requirements(self):
        self.requires("etl/20.37.2")
        self.requires("logger/1.0")
        self.requires("ecss-services/1.2")