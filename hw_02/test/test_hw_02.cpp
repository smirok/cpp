#include "BoardTest.h"

int main() {
    BoardTest bt;
    bt.runAllTests();
    return !Test::showFinalResults();
}

