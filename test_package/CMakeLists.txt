cmake_minimum_required (VERSION 3.20)
project (test_package)

set (CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package (xtal   CONFIG REQUIRED)
find_package (Catch2 CONFIG REQUIRED)
find_package (Eigen3 CONFIG REQUIRED)

cmake_path(GET CMAKE_CURRENT_SOURCE_DIR PARENT_PATH XTAL_SOURCE_DIR)

if (EXISTS ${XTAL_SOURCE_DIR}/include/FIXME.cc)
	add_executable (test ${XTAL_SOURCE_DIR}/include/FIXME.cc)
else  ()
	add_executable (test ${XTAL_SOURCE_DIR}/include/xtal/all.cc)
endif ()

if (NOT CMAKE_CXX_COMPILER_ID MATCHES "MSVC")
	set (CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3")
	set (CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -ffast-math")
#	set (CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE}    -fcx-fortran-rules")# Alternative...
#	set (CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE}    -fcx-limited-range")
#	set (CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE}    -fno-honor-nans")
#	set (CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE}    -fno-honor-infinities")
#	set (CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE}    -fno-rounding-math")
#	set (CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE}    -ffinite-math-only")
##	set (CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE}    -ffp-model=fast")
#	set (CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE}       -fno-math-errno")
##	set (CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE}       -funsafe-math-optimizations")
#	set (CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE}          -fapprox-func")
#	set (CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE}          -fno-signed-zeros")
#	set (CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE}          -freciprocal-math")
#	set (CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE}          -fassociative-math")
#	set (CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE}          -ffp-contract=fast")
#	set (CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE}          -fno-trapping-math")
endif ()

target_link_libraries (test xtal::xtal Catch2::Catch2WithMain Eigen3::Eigen)

target_precompile_headers (test INTERFACE xtal::xtal Catch2::Catch2WithMain Eigen3::Eigen)
