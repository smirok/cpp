#include <iostream>
#include <cstring>
#include "Board.h"
#include "StdioBoardView.h"
#include "GameController.h"
#include "NcursesBoardView.h"
#include "View.h"

int main(int args, char **argv) {
    Board board(10, 10, 5);
    Mode mode;

    if (args == 1)
        mode = Standard;
    else if (!strcmp(argv[1], "silent")) {
        mode = Silent;
    } else if (!strcmp(argv[1], "curses"))
        mode = Curses;
    else {
        std::cout << "Sorry, not today";
        return 0;
    }

    View *view = nullptr;
    if (mode != Curses)
        view = new StdioBoardView;
    else
        view = new NcursesBoardView;
    GameController controller(board, *view, mode);

    controller.startNewGame();
    delete view;
    return 0;
}
