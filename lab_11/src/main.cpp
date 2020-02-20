#include <iostream>
#include <fstream>
#include "employees.h"
#include <cassert>

using namespace std;


int main() {
    EmployeesArray employees_list;
    string file_name;
    string command;
    int32_t type;

    while (true) {
        cin >> command;
        if (command == "list") {
            cout << employees_list;
        } else if (command == "add") {
            cin >> type;
            Employee *employee = nullptr;
            if (type == DEVELOPER) {
                employee = new Developer();
            } else if (type == SALES_MANAGER) {
                employee = new SalesManager();
            }
            cin >> *employee;
            assert(employee != nullptr);
            employees_list.add(employee);
        } else if (command == "save") {
            cin >> file_name;
            ofstream f(file_name.c_str(), ios::binary);
            f << employees_list;
            f.close();
        } else if (command == "load") {
            cin >> file_name;
            ifstream f(file_name.c_str(), ios::binary);
            assert(f);
            f >> employees_list;
            f.close();
        } else if (command == "exit") {
            break;
        } else {
            cout << "Unknown command, please try again!\n";
        }
    }
    return 0;
}