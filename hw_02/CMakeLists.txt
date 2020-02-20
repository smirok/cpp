cmake_minimum_required(VERSION 3.10.2)
project(hw_02)

set(CMAKE_CXX_STANDARD 17)

include_directories("include/")

add_executable(hw_02 src/main.cpp src/Board.cpp include/Board.h src/StdioBoardView.cpp include/StdioBoardView.h src/GameController.cpp include/GameController.h src/NcursesBoardView.cpp include/NcursesBoardView.h)
add_executable(test_hw_02 test/test_hw_02.cpp test/Test.cpp include/Test.h test/BoardTest.cpp include/BoardTest.h src/Board.cpp include/Board.h)

target_link_libraries(hw_02 ncurses)
