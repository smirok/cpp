#ifndef HW_02_VIEW_H
#define HW_02_VIEW_H

#include <iostream>
#include "Board.h"

class View {
public:

    virtual ~View() {};

    virtual void showBoard(const vector<vector<FieldState>> &field, int, int) const = 0;

    virtual void showResultMessage(GameState) const = 0;

    virtual void showMoveNext(Players) const = 0;

    virtual void showBadMove() const = 0;

    virtual bool enterCorrectTurn(int &x, int &y, const vector<vector<FieldState>> &field,
                                  int height, int width, Players player) const = 0;

    virtual void showWinLine(int &x, int &y, const vector<vector<FieldState>> &field,
                             int height, int width, int winlen) const {};
};

#endif //HW_02_VIEW_H
