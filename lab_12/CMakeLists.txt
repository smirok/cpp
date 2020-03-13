cmake_minimum_required(VERSION 3.10.2)
project(lab_12)

include_directories("include/")

set(CMAKE_CXX_STANDARD 17)

#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=address -fsanitize=leak -Wall -Werror -Wextra")


add_executable(lab_12 src/main.cpp include/my_vector.h include/my_vector_impl.h)