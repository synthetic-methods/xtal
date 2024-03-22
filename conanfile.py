import os
from conan import ConanFile
from conan.tools.files import copy
from conan.tools.cmake import cmake_layout
from conan.tools.build import check_min_cppstd

class Xtal__Conan(ConanFile):
	required_conan_version = ">=2.0.0"

	# Info:
	name    = "xtal"
	version = "0.0.0"
	license = "Boost Software License 1.0"

	url     = "https://github.com/synthetic-methods/xtal"
	author  = "GoomTrex goomtrex@gmail.com"
	
	topics  = ("C++20"
	, "Template Metaprogramming", "TMP", "CRTP", "std::ranges", "range-v3"
	, "Real-Time", "Scheduling", "Stream Processing", "Signal Processing", "DSP", "FFT"
	, "Embedded", "Audio", "AudioUnit", "AudioKit", "JUCE", "VST", "AU"
	, "Modular", "Functors", "Combinators"
	, "VTable", "Branchless", "Control"
	)
	description = """
	XTAL is a cross-platform header-only zipper/combinator library for musical Digital Signal Processing (DSP).
	It provides an extensible and performant platform for rapid prototyping and
	development of real-time instruments and effects.
	"""

	# Build:
	settings = "os", "arch", "compiler", "build_type"
	generators = "CMakeDeps", "CMakeToolchain"
	
	def layout(self):
		cmake_layout(self)

	def validate(self):
		check_min_cppstd(self, 20)

	def requirements(self):
		self.requires("range-v3/0.12.0", transitive_headers=True)
		self.requires("simde/0.7.6", transitive_headers=True)

	# Package:
	no_copy_source = True
	exports_sources = "include*.h*", "include*.i*", "include*.modulemap", "CMakeLists.txt", "LICENSE.*"

	def package(self):
		for glob in self.exports_sources:
			copy(self, glob, self.source_folder, self.package_folder)

	def package_id(self):
		self.info.clear()

	def package_info(self):
		self.cpp_info.bindirs = []
		self.cpp_info.libdirs = []
