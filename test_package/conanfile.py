from os import path

from conan             import ConanFile
from conan.tools.files import copy
from conan.tools.cmake import CMake, cmake_layout

class XtalTestPackageConan(ConanFile):
	settings = "os", "compiler", "build_type", "arch"
	generators = "CMakeToolchain", "CMakeDeps"

	def requirements(self):
		self.requires(self.tested_reference_str)
		self.requires("catch2/3.3.2")

	def layout(self):
		cmake_layout(self)

	def build(self):
		cmake = CMake(self)
		cmake.configure()
		cmake.build()

	def test(self):
		bin = path.join(self.cpp.build.bindir, "test")
		bin += " --skip-benchmarks"
		self.run(bin, env="conanrun")
