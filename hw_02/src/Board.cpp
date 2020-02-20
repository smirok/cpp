#include "Board.h"
#include <algorithm>

using std::max;
using std::min;

Board::Board(int height, int width, int win_len) : _height(height), _width(width),
                                                   _win_len(win_len), _current_player(Players::O) {
    if (height <= 0 || width <= 0 || win_len <= 0)
        exit(0);
    if (_win_len > max(_height, _width))
        _win_len = max(_height, _width);
    _field.resize(_height);
    for (int i = 0; i < _height; i++) {
        _field[i].resize(_width);
        for (int j = 0; j < _width; j++)
            _field[i][j] = FieldState::NONE;
    }
}

bool Board::canMove(int x, int y) const {
    if (x < 0 || y < 0 || x >= _height || y >= _width)
        return false;
    return _field[x][y] == FieldState::NONE;
}

void Board::move(int x, int y) {
    if (_current_player == Players::O) {
        _field[x][y] = FieldState::O;
        _current_player = Players::X;
    } else {
        _field[x][y] = FieldState::X;
        _current_player = Players::O;
    }
}

GameState Board::getState() const {
    bool draw = true;

    for (int i = 0; i < _height; i++) {
        for (int j = 0; j < _width; j++) {
            if (_field[i][j] == FieldState::NONE) {
                draw = false;
                continue;
            }
            // из каждой клетки пытаемся найти ряд из пяти одинаковых крестиков/ноликов,
            // пуская волну вправо, вниз, вниз-вправо, вверх-вправо , при этом не выходя за границы массива
            bool direction[4] = {true, true, true, true};
            for (int k = 0; k < _win_len; k++) {
                direction[0] &= (i + k < _height && _field[i + k][j] == _field[i][j]); // down
                direction[1] &= (j + k < _width && _field[i][j + k] == _field[i][j]); // right
                direction[2] &= (max(i, j) + k < min(_height, _width) &&
                                 _field[i + k][j + k] == _field[i][j]); // down-right
                direction[3] &= (j - k >= 0 && i + k < min(_height, _width) &&
                                 _field[i + k][j - k] == _field[i][j]); // up-right
            }
            if (direction[0] || direction[1] || direction[2] || direction[3]) {
                return (_field[i][j] == FieldState::X ? X_WIN : O_WIN);
            }
        }
    }

    return draw ? IS_TIE : GAME_GOES;
}

FieldState Board::getCell(int x, int y) const {
    return _field[x][y];
}

int Board::getWinLen() const {
    return _win_len;
}

Players Board::getCurPlayer() const {
    return _current_player;
}

int Board::getHeight() const {
    return _height;
}

int Board::getWidth() const {
    return _width;
}

vector<vector<FieldState >> Board::getField() const {
    return _field;
}
