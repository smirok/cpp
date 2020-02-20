#ifndef HW_2_CONTROLLER_H
#define HW_2_CONTROLLER_H

#include "StdioBoardView.h"
#include "NcursesBoardView.h"
#include <ncurses.h>

enum Mode {
    Standard,
    Silent,
    Curses
};

class GameController {
public:
    GameController(Board &board, View &view, Mode mode) :
            _board(board), _view(view), _mode(mode) {};

    void startNewGame();

private:
    View &_view;
    Board &_board;
    Mode _mode;
};

#endif //HW_2_CONTROLLER_H
