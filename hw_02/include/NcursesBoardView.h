#ifndef HW_02_NCURSESBOARDVIEW_H
#define HW_02_NCURSESBOARDVIEW_H

#include <ncurses.h>
#include "Board.h"
#include "View.h"


class NcursesBoardView : public View {

public:
    NcursesBoardView ();

    virtual ~NcursesBoardView();

    void showResultMessage(GameState) const override;

    void showBoard(const vector <vector <FieldState>>&, int height, int width) const override;

    void showMoveNext(Players) const override;

    void showBadMove() const override;

    bool enterCorrectTurn(int &x, int &y,const vector <vector <FieldState>>&,
                          int height, int width, Players player) const override;

    void showWinLine(int &x, int &y, const vector<vector<FieldState>>&,
                        int height, int width, int winlen) const override;

    void screenClear() const;

private:
    WINDOW *title;
    WINDOW *win;
    WINDOW *message;
};

#endif //HW_02_NCURSESBOARDVIEW_H
