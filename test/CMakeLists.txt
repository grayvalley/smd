cmake_minimum_required(VERSION 3.16)
set(CMAKE_CXX_STANDARD 17)

get_filename_component(PARENT_DIR ../ ABSOLUTE)
include_directories(${PARENT_DIR}/src)

add_executable(TestSMDParser test_main.cc)
target_link_libraries(TestSMDParser gtest gtest_main)
target_link_libraries(TestSMDParser pthread)
target_link_libraries(TestSMDParser kwant)

add_subdirectory(test)