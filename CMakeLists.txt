cmake_minimum_required(VERSION 3.14)

project(xtal VERSION 0.0.0)

add_library(${PROJECT_NAME} INTERFACE)
target_include_directories(${PROJECT_NAME} INTERFACE include)


find_package(range-v3 REQUIRED)
find_package(mdspan REQUIRED)
find_package(simde REQUIRED)
target_link_libraries(${PROJECT_NAME} range-v3::range-v3)
target_link_libraries(${PROJECT_NAME} std::mdspan)
target_link_libraries(${PROJECT_NAME} simde::simde)


set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
