#ifndef HW_2_BOARD_H
#define HW_2_BOARD_H

#include <vector>

enum class Players : char {
    O = 'O',
    X = 'X'
};

enum GameState {
    O_WIN,
    X_WIN,
    IS_TIE,
    GAME_GOES
};

enum class FieldState : char {
    NONE = '.',
    O = 'O',
    X = 'X'

};

enum class PARAMS : int {
    HEIGHT = 10,
    WIDTH = 10,
    WIN_LENGTH = 5
};

class Board {
public:
    explicit Board(int height = static_cast<int>(PARAMS::HEIGHT),
                   int width = static_cast<int>(PARAMS::WIDTH),
                   int win_length = static_cast<int>(PARAMS::WIN_LENGTH));

    bool canMove(int x, int y) const;

    void move(int x, int y);

    GameState getState() const;

    FieldState getCell(int x, int y) const;

    int getHeight() const;

    int getWidth() const;

    int getWinLen() const;

    std::vector<std::vector<FieldState >> getField() const;

    Players getCurPlayer() const;

private:
    Players _current_player;
    int _height;
    int _width;
    int _win_len;
    std::vector<std::vector<FieldState >> _field;
};

#endif //HW_2_BOARD_H
