import os
from conan import ConanFile
from conan.tools.files import copy
from conan.tools.cmake import cmake_layout
from conan.tools.build import check_min_cppstd

class XTAL(ConanFile):
	required_conan_version = ">=2.0.0"

	name    = "xtal"
	version = "0.0.0"
	license = "MIT License"

	url     = "https://github.com/synthetic-methods/xtal"
	author  = "GoomTrex goomtrex@gmail.com"
	
	topics  = ("C++20", "ranges-v3"
	,	"Streams", "Combinators", "Functional", "Metaprogramming"
	,	"DSP", "Signal Processing", "Branchless", "Mathematics"
	,	"Embedded", "PlugIn", "JUCE", "VST", "AudioUnit"
	)
	description = """
	XTAL is a range-based header-only combinator library for musical Digital Signal Processing (DSP).
	It provides an extensible and performant platform for rapid prototyping and development,
	aimed at building real-time instruments and effects for both hardware and software.
	"""

	settings = "os", "arch", "compiler", "build_type"
	generators = "CMakeToolchain", "CMakeDeps"
	exports_sources = "include/*"
	no_copy_source = True

	def layout(self):
		cmake_layout(self)

	def package(self):
		copy(self, "*.h*", self.source_folder, self.package_folder)
		copy(self, "*.i*", self.source_folder, self.package_folder)

	def package_id(self):
		self.info.clear()

	def package_info(self):
		self.cpp_info.bindirs = []
		self.cpp_info.libdirs = []

	def validate(self):
		check_min_cppstd(self, 20)

	def requirements(self):
		self.requires("range-v3/0.12.0")
