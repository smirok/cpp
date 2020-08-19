#ifndef HW_2_STDIOBOARDVIEW_H
#define HW_2_STDIOBOARDVIEW_H

#include "Board.h"
#include "View.h"


class StdioBoardView : public View {
public:

    void showBoard(const std::vector<std::vector<FieldState >> &field) const override;

    void showResultMessage(GameState) const override;

    void showMoveNext(Players player) const override;

    void showBadMove() const override;

    bool enterCorrectTurn(int &x, int &y,
                          const std::vector<std::vector<FieldState>> &field,
                          Players player) const override;

};

#endif //HW_2_STDIOBOARDVIEW_H
