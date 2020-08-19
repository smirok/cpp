#include "StdioBoardView.h"
#include <iostream>
#include <cstdio>
#include <string>

namespace {
    constexpr int CORRECT_FORMAT_SIZE = 3;
}

void StdioBoardView::showBoard(const std::vector<std::vector<FieldState >> &field) const {
    printf("%c", '\n');
    for (int i = 0; i < field.size(); i++) {
        for (int j = 0; j < field[0].size(); j++) {
            printf("%c", (char) field[i][j]);
        }
        printf("%c", '\n');
    }
}

void StdioBoardView::showResultMessage(GameState state) const {
    if (state == O_WIN) { // != game goes
        printf("%s", "O wins!\n");
    } else if (state == X_WIN) {
        printf("%s", "X wins!\n");
    } else
        printf("%s", "Draw.\n");
}

void StdioBoardView::showBadMove() const {
    printf("%s", "Bad move!\n");
}

void StdioBoardView::showMoveNext(Players player) const {
    printf("%c%s", (char) player, " move: ");
}

bool StdioBoardView::enterCorrectTurn(int &x, int &y,
                                      const std::vector<std::vector<FieldState>> &field,
                                      Players player) const {
    static_cast<void>(field);
    static_cast<void>(player);

    std::string buffer;
    char space_catcher, trash_catcher;
    bool flag = false;

    std::getline(std::cin, buffer);
    while (!buffer.empty() && buffer.back() == ' ')
        buffer.pop_back();

    int size_num = sscanf(buffer.c_str(), "%d%c%d%c",
            &x, &space_catcher, &y, &trash_catcher);

    if (size_num == CORRECT_FORMAT_SIZE && space_catcher == ' ')
        flag = true;
    if (x == -1 && y == -1 && size_num == CORRECT_FORMAT_SIZE && space_catcher == ' ')
        exit(0);
    return flag;
}
