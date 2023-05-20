cmake_minimum_required(VERSION 3.14)
project(test_package)

find_package(xtal CONFIG REQUIRED)
find_package(Catch2 CONFIG REQUIRED)

add_executable(test ../include/xtal.cxx)

target_link_libraries(test xtal::xtal Catch2::Catch2WithMain)
