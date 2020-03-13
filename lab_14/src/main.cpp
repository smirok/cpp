#include "../include/matrix.h"

int main() {
    std::string command, file_name, reg1, reg2;
    int rows, cols;

    std::map<std::string, Matrix> regs;

    while (true) {
        try {
            std::cin >> command;

            if (command == "load") {
                std::cin >> reg1 >> file_name;
                regs[reg1].loadMatrix(file_name);
            } else if (command == "print") {
                std::cin >> reg1;
                regs[reg1].printMatrix();
            } else if (command == "add") {
                std::cin >> reg1 >> reg2;
                regs[reg1] += regs[reg2];
            } else if (command == "mul") {
                std::cin >> reg1 >> reg2;
                regs[reg1] *= regs[reg2];
            } else if (command == "elem") {
                std::cin >> reg1 >> rows >> cols;
                std::cout << regs[reg1].getCell(rows, cols) << "\n";
            } else if (command == "exit") {
                break;
            }
        } catch (MatrixException &exc) {
            std::cout << exc.what() << "\n";
        }
    }
    return 0;
}