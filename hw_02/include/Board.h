#ifndef HW_2_BOARD_H
#define HW_2_BOARD_H

#include <vector>

using std::vector;

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

class Board {
public:
    explicit Board(int height = 10, int width = 10, int win_length = 5);

    bool canMove(int x, int y) const;

    void move(int x, int y);

    GameState getState() const;

    FieldState getCell(int x, int y) const;

    int getHeight() const;

    int getWidth() const;

    int getWinLen() const;

    vector<vector<FieldState >> getField() const;

    Players getCurPlayer() const;

private:
    Players _current_player;
    int _height;
    int _width;
    int _win_len;
    vector<vector<FieldState >> _field;
};

#endif //HW_2_BOARD_H
