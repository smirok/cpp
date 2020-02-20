#ifndef HW_2_BOARDTEST_H
#define HW_2_BOARDTEST_H

#include "Test.h"

class BoardTest : public Test {
public:
    void runAllTests() override;

private:
    void TestCanMoveBusy();
    void TestCanMoveFree();
    void TestCanMoveOut();

    void TestMoveO();
    void TestMoveX();
    void TestMoveOX();

    void TestGetStateGameGoes();
    void TestGetStateIsTie();

    void TestGetStateHorizontalX_WIN();
    void TestGetStateHorizontalO_WIN();

    void TestGetStateVerticalX_WIN();
    void TestGetStateVerticalO_WIN();

    void TestGetStateSlashX_WIN();
    void TestGetStateSlashO_WIN();

    void TestGetStateBackSlashX_WIN();
    void TestGetStateBackSlashO_WIN();

    void TestGetCellEmpty();
    void TestGetCellO();
    void TestGetCellX();

    void TestGetHeightDefault();
    void TestGetHeightSet();
    void TestGetHeightBig();

    void TestGetWidthDefault();
    void TestGetWidthSet();
    void TestGetWidthBig();

    void TestGetWinLenDefault();
    void TestGetWinLenSet();
    void TestGetWinLenCorrect();

    void TestGetFieldEmpty();
    void TestGetField();
    void TestGetFieldWin();

    void TestGetCurPlayerO();
    void TestGetCurPlayerX();
    void TestGetCurPlayerManyTurns();
};

#endif //HW_2_BOARDTEST_H
