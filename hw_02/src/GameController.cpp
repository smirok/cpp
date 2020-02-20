#include "GameController.h"
#include "Board.h"

void GameController::startNewGame() {
    if (_mode != Silent)
        _view.showBoard(_board.getField(), _board.getHeight(), _board.getWidth());
    int x = 0;
    int y = 0;
    while (_board.getState() == GAME_GOES) {

        _view.showMoveNext(_board.getCurPlayer());

        do {
            while (!_view.enterCorrectTurn(x, y, _board.getField(), _board.getHeight(),
                                           _board.getWidth(), _board.getCurPlayer()) || !_board.canMove(x, y)) {
                _view.showBadMove();
                _view.showMoveNext(_board.getCurPlayer());
            }
        } while (!_board.canMove(x, y));


        _board.move(x, y);

        if (_mode != Silent)
            _view.showBoard(_board.getField(), _board.getHeight(), _board.getWidth());

    }

    if (_mode == Curses)
        _view.showWinLine(x, y, _board.getField(), _board.getHeight(),
                          _board.getWidth(), _board.getWinLen());

    if (_mode == Silent)
        _view.showBoard(_board.getField(), _board.getHeight(), _board.getWidth());

    _view.showResultMessage(_board.getState());
}

