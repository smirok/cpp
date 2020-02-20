#ifndef HW_2_STDIOBOARDVIEW_H
#define HW_2_STDIOBOARDVIEW_H

#include "Board.h"
#include "View.h"


class StdioBoardView : public View {
public:

    void showBoard(const vector<vector<FieldState >>&, int, int) const override;

    void showResultMessage(GameState) const override;

    void showMoveNext(Players) const override;

    void showBadMove() const override;

    bool enterCorrectTurn(int &x, int &y, const vector <vector <FieldState>>& field,
                            int height, int width, Players player) const override;

};

#endif //HW_2_STDIOBOARDVIEW_H
