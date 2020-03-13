cmake_minimum_required(VERSION 3.10.2)
project(lab_13)

set(CMAKE_CXX_STANDARD 17)

#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=address -fsanitize=leak -Wall -Werror -Wextra")

include_directories(include)

add_executable(lab_13 src/main.cpp include/my_array.h)