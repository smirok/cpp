#include "BoardTest.h"
#include "Board.h"

void BoardTest::TestCanMoveBusy() {
    Board b;
    b.Board::move(0, 0);
    DO_CHECK(!b.Board::canMove(0, 0));
}

void BoardTest::TestCanMoveFree() {
    Board b;
    bool checker = true;
    for (int i = 0; i < b.getHeight(); i++) {
        for (int j = 0; j < b.getWidth(); j++) {
            if (!b.canMove(i, j)) {
                checker = false;
                break;
            }
        }
    }
    DO_CHECK(checker);
}

void BoardTest::TestCanMoveOut() {
    Board b;
    DO_CHECK(!b.canMove(2 * b.getHeight(), 2 * b.getWidth()));
}

void BoardTest::TestMoveO() {
    Board b;
    b.move(2, 5);
    DO_CHECK(b.getCell(2, 5) == FieldState::O);
}

void BoardTest::TestMoveX() {
    Board b;
    b.move(1, 1);
    b.move(4, 3);
    DO_CHECK(b.getCell(4, 3) == FieldState::X);
}

void BoardTest::TestMoveOX() {
    Board b;
    b.move(1, 0);
    b.move(0, 1);
    DO_CHECK(b.getCell(1, 0) == FieldState::O && b.getCell(0, 1) == FieldState::X);
}

void BoardTest::TestGetStateGameGoes() {
    Board b;
    b.move(1, 0);
    b.move(4, 2);
    b.move(8, 8);
    b.move(4, 7);
    b.move(0, 9);
    DO_CHECK(b.getState() == GAME_GOES);
}

void tie_moves_even_row(Board &b, int num_row) {
    b.move(num_row, 0);
    b.move(num_row, 2);
    b.move(num_row, 1);
    b.move(num_row, 3);
    b.move(num_row, 4);
    b.move(num_row, 6);
    b.move(num_row, 5);
    b.move(num_row, 7);
    b.move(num_row, 8);
    b.move(num_row + 1, 0);
}

void tie_moves_odd_row(Board &b, int num_row) {
    b.move(num_row - 1, 9);
    b.move(num_row, 1);
    b.move(num_row, 2);
    b.move(num_row, 4);
    b.move(num_row, 3);
    b.move(num_row, 5);
    b.move(num_row, 6);
    b.move(num_row, 8);
    b.move(num_row, 7);
    b.move(num_row, 9);
}

void BoardTest::TestGetStateIsTie() { // 10 x 10
    Board b;
    for (int i = 0; i < b.getHeight(); i++) {
        if (i % 2 == 0)
            tie_moves_even_row(b, i);
        else
            tie_moves_odd_row(b, i);
    }
    DO_CHECK(b.getState() == IS_TIE);
}

void BoardTest::TestGetStateHorizontalX_WIN() {
    Board b;
    b.move(0, 0);
    b.move(1, 0);
    b.move(0, 1);
    b.move(1, 1);
    b.move(0, 2);
    b.move(1, 2);
    b.move(0, 3);
    b.move(1, 3);
    b.move(0, 5);
    b.move(1, 4);
    DO_CHECK(b.getState() == X_WIN);
}

void BoardTest::TestGetStateHorizontalO_WIN() {
    Board b;
    b.move(7, 4);
    b.move(0, 0);
    b.move(7, 5);
    b.move(0, 1);
    b.move(7, 6);
    b.move(0, 2);
    b.move(7, 7);
    b.move(0, 3);
    b.move(7, 8);
    DO_CHECK(b.getState() == O_WIN);
}

void BoardTest::TestGetStateVerticalX_WIN() {
    Board b;
    b.move(0, 0);
    b.move(5, 4);
    b.move(0, 1);
    b.move(6, 4);
    b.move(0, 2);
    b.move(7, 4);
    b.move(0, 3);
    b.move(8, 4);
    b.move(0, 5);
    b.move(9, 4);
    DO_CHECK(b.getState() == X_WIN);
}

void BoardTest::TestGetStateVerticalO_WIN() {
    Board b;
    b.move(8, 3);
    b.move(0, 0);
    b.move(7, 3);
    b.move(0, 1);
    b.move(6, 3);
    b.move(0, 2);
    b.move(5, 3);
    b.move(0, 3);
    b.move(4, 3);
    DO_CHECK(b.getState() == O_WIN);
}

void BoardTest::TestGetStateSlashX_WIN() {
    Board b;
    b.move(0, 0);
    b.move(1, 9);
    b.move(0, 1);
    b.move(2, 8);
    b.move(0, 2);
    b.move(3, 7);
    b.move(0, 3);
    b.move(4, 6);
    b.move(0, 5);
    b.move(5, 5);
    DO_CHECK(b.getState() == X_WIN);
}

void BoardTest::TestGetStateSlashO_WIN() {
    Board b;
    b.move(8, 3);
    b.move(0, 0);
    b.move(7, 4);
    b.move(0, 1);
    b.move(6, 5);
    b.move(0, 2);
    b.move(5, 6);
    b.move(0, 3);
    b.move(4, 7);
    DO_CHECK(b.getState() == O_WIN);
}

void BoardTest::TestGetStateBackSlashX_WIN() {
    Board b;
    b.move(9, 9);
    b.move(0, 0);
    b.move(9, 8);
    b.move(1, 1);
    b.move(9, 7);
    b.move(2, 2);
    b.move(9, 6);
    b.move(3, 3);
    b.move(9, 4);
    b.move(4, 4);
    DO_CHECK(b.getState() == X_WIN);
}

void BoardTest::TestGetStateBackSlashO_WIN() {
    Board b;
    b.move(7, 8);
    b.move(0, 0);
    b.move(6, 7);
    b.move(0, 1);
    b.move(5, 6);
    b.move(0, 2);
    b.move(4, 5);
    b.move(0, 3);
    b.move(3, 4);
    DO_CHECK(b.getState() == O_WIN);
}

void BoardTest::TestGetCellEmpty() {
    Board b;
    DO_CHECK(b.getCell(5, 5) == FieldState::NONE);
}

void BoardTest::TestGetCellO() {
    Board b;
    b.move(0, 0);
    DO_CHECK(b.getCell(0, 0) == FieldState::O);
}

void BoardTest::TestGetCellX() {
    Board b;
    b.move(0, 0);
    b.move(2, 4);
    DO_CHECK(b.getCell(2, 4) == FieldState::X);
}

void BoardTest::TestGetHeightDefault() {
    Board b;
    DO_CHECK(b.getHeight() == 10);
}

void BoardTest::TestGetHeightSet() {
    Board b(5);
    DO_CHECK(b.getHeight() == 5);
}

void BoardTest::TestGetHeightBig() {
    Board b(1000);
    DO_CHECK(b.getHeight() == 1000);
}

void BoardTest::TestGetWidthDefault() {
    Board b;
    DO_CHECK(b.getWidth() == 10);
}

void BoardTest::TestGetWidthSet() {
    Board b(10, 5);
    DO_CHECK(b.getWidth() == 5);
}

void BoardTest::TestGetWidthBig() {
    Board b(10, 1000);
    DO_CHECK(b.getWidth() == 1000);
}

void BoardTest::TestGetWinLenDefault() {
    Board b;
    DO_CHECK(b.getWinLen() == 5);
}

void BoardTest::TestGetWinLenSet() {
    Board b(10, 10, 10);
    DO_CHECK(b.getWinLen() == 10);
}

void BoardTest::TestGetWinLenCorrect() {
    Board b(15, 20, 25);
    DO_CHECK(b.getWinLen() == 20);
}

void BoardTest::TestGetFieldEmpty() {
    Board b;
    std::vector<std::vector<FieldState >> replica(10);
    for (int i = 0; i < 10; i++) {
        replica[i].resize(10);
        for (int j = 0; j < 10; j++)
            replica[i][j] = FieldState::NONE;
    }
    DO_CHECK(b.getField() == replica);
}

void BoardTest::TestGetField() {
    Board b;
    std::vector<std::vector<FieldState >> replica(10);
    for (int i = 0; i < 10; i++) {
        replica[i].resize(10);
        for (int j = 0; j < 10; j++)
            replica[i][j] = FieldState::NONE;
    }
    b.move(0, 0);
    b.move(1, 4);
    replica[0][0] = FieldState::O;
    replica[1][4] = FieldState::X;
    DO_CHECK(b.getField() == replica);
}

void BoardTest::TestGetFieldWin() {
    Board b(5, 5, 5);
    std::vector<std::vector<FieldState >> replica(5);
    for (int i = 0; i < 5; i++) {
        replica[i].resize(5);
        for (int j = 0; j < 5; j++)
            replica[i][j] = FieldState::NONE;
    }
    for (int i = 0; i < 4; i++) {
        b.move(i, 0);
        b.move(i, 1);
        replica[i][0] = FieldState::O;
        replica[i][1] = FieldState::X;
    }
    b.move(4, 0);
    replica[4][0] = FieldState::O;
    DO_CHECK(b.getField() == replica);

}

void BoardTest::TestGetCurPlayerO() {
    Board b;
    DO_CHECK(b.getCurPlayer() == Players::O);
}

void BoardTest::TestGetCurPlayerX() {
    Board b;
    b.move(0, 0);
    DO_CHECK(b.getCurPlayer() == Players::X);
}

void BoardTest::TestGetCurPlayerManyTurns() {
    Board b;
    for (int i = 0; i < 10; i++)
        b.move(i, i);
    DO_CHECK(b.getCurPlayer() == Players::O);
}

void BoardTest::runAllTests() {
    TestCanMoveBusy();
    TestCanMoveFree();
    TestCanMoveOut();

    TestMoveO();
    TestMoveX();
    TestMoveOX();

    TestGetStateGameGoes();
    TestGetStateIsTie();

    TestGetStateHorizontalX_WIN();
    TestGetStateHorizontalO_WIN();

    TestGetStateVerticalX_WIN();
    TestGetStateVerticalO_WIN();

    TestGetStateSlashX_WIN();
    TestGetStateSlashO_WIN();

    TestGetStateBackSlashX_WIN();
    TestGetStateBackSlashO_WIN();

    TestGetCellEmpty();
    TestGetCellO();
    TestGetCellX();

    TestGetHeightDefault();
    TestGetHeightSet();
    TestGetHeightBig();

    TestGetWidthDefault();
    TestGetWidthSet();
    TestGetWidthBig();

    TestGetWinLenDefault();
    TestGetWinLenSet();
    TestGetWinLenCorrect();

    TestGetFieldEmpty();
    TestGetField();
    TestGetFieldWin();

    TestGetCurPlayerO();
    TestGetCurPlayerX();
    TestGetCurPlayerManyTurns();
}
