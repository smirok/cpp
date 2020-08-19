cmake_minimum_required(VERSION 3.16)
project(lab_15)

set(CMAKE_CXX_STANDARD 17)

include_directories(../include)

add_executable(minimal_smoke_test ../include/linq.hpp minimal_smoke_test.cpp)
add_executable(smoke_test ../include/linq.hpp smoke_test.cpp)