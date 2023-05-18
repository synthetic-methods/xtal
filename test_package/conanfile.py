from os import path

from conan             import ConanFile
from conan.tools.files import copy
from conan.tools.cmake import CMake, cmake_layout

class XTALTestPackageConan(ConanFile):
	settings = "os", "compiler", "build_type", "arch"
	generators = "CMakeToolchain", "CMakeDeps"

	def requirements(self):
		self.requires(self.tested_reference_str)
		self.requires("catch2/3.3.2")

	def layout(self):
		cmake_layout(self)

	def build(self):
	#	Instead of mirroring the directory structure of `../include` within `./src`,
	#	the tests for each header-file live in the same directory,
	#	and are copied over prior to `build`:
	#
		includes = path.join(self.source_folder, "..", "include")
		excludes = path.join(self.source_folder, "src")

	#	copy(self, "*.c*", includes, excludes) #import <this>
		copy(self,    "*", includes, excludes) #import "this"

		cmake = CMake(self)
		cmake.configure()
		cmake.build()

	def test(self):
		cmd = path.join(self.cpp.build.bindir, "test")
		self.run(cmd, env="conanrun")
