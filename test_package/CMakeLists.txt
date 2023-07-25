cmake_minimum_required(VERSION 3.14)
project(test_package)

find_package(xtal CONFIG REQUIRED)
find_package(Catch2 CONFIG REQUIRED)

if(EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/../include/FIXME.cxx)
	add_executable(test ../include/FIXME.cxx)
else()
	add_executable(test ../include/xtal.c++)
endif()

target_link_libraries(test xtal::xtal Catch2::Catch2WithMain)
