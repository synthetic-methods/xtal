cmake_minimum_required(VERSION 3.20)
project(test_package)

find_package(xtal CONFIG REQUIRED)
find_package(Catch2 CONFIG REQUIRED)

cmake_path(GET CMAKE_CURRENT_SOURCE_DIR PARENT_PATH XTAL_SOURCE_DIR)

if(EXISTS ${XTAL_SOURCE_DIR}/include/FIXME.c++)
	add_executable(test ${XTAL_SOURCE_DIR}/include/FIXME.c++)
else()
	add_executable(test ${XTAL_SOURCE_DIR}/include/xtal.cc)
endif()

target_link_libraries(test xtal::xtal Catch2::Catch2WithMain)
