#include "Test.h"

#include <iostream>

int Test::failedNum = 0;
int Test::totalNum = 0;

void Test::check(bool expr, const char *func, const char *filename, size_t lineNum) {
    totalNum++;
    if (!expr) {
        failedNum++;
        std::cout << "Test failed : " << func
                  << " in " << filename << " in "
                  << lineNum << " line\n";
    }
}

bool Test::showFinalResults() {
    if (!failedNum) {
        std::cout << "Accepted" << "\n";
        return true;
    } else {
        std::cout << "Failed " << failedNum << " of "
                  << totalNum << " tests" << "\n";
        return false;
    }
}


