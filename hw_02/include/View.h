#ifndef HW_02_VIEW_H
#define HW_02_VIEW_H

#include <iostream>
#include "Board.h"

class View {
public:

    virtual ~View() {};

    virtual void showBoard(const std::vector<std::vector<FieldState>> &field) const = 0;

    virtual void showResultMessage(GameState state) const = 0;

    virtual void showMoveNext(Players player) const = 0;

    virtual void showBadMove() const = 0;

    virtual bool enterCorrectTurn(int &x, int &y,
                                  const std::vector<std::vector<FieldState>> &field,
                                  Players player) const = 0;

    virtual void showWinLine(int &x, int &y,
                             const std::vector<std::vector<FieldState>> &field,
                             int winlen) const {};
};

#endif //HW_02_VIEW_H
