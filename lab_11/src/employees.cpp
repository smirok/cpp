#include "employees.h"
#include <string>
#include <fstream>
#include <iostream>
#include "bin_manip.h"
#include <iosfwd>
#include <cassert>

//EMPLOYEE start

std::istream &operator>>(std::istream &is, Employee &e) {
    return e >> is;
}

std::ifstream &operator>>(std::ifstream &ifs, Employee &e) {
    return e >> ifs;
}

std::ostream &operator<<(std::ostream &os, const Employee &e) {
    return e << os;
}

std::ofstream &operator<<(std::ofstream &ofs, const Employee &e) {
    return e << ofs;
}

//EMPLOYEE finish

//DEVELOPER start

int32_t Developer::salary() const {
    int salary = _base_salary;
    if (_has_bonus) { salary += DEVELOPER_SALARY_BONUS; }
    return salary;
}

std::istream &Developer::operator>>(std::istream &is) {
    is >> _name >> _base_salary >> _has_bonus;
    return is;
}

std::ifstream &Developer::operator>>(std::ifstream &ifs) {
    ifs >> read_str(_name)
        >> read_le_int32(_base_salary)
        >> read_bool(_has_bonus);
    return ifs;
}

std::ostream &Developer::operator<<(std::ostream &os) const {
    os << "Developer" << "\n"
       << "Name: " << _name << "\n"
       << "Base Salary: " << _base_salary << "\n"
       << "Has bonus: " << (_has_bonus ? "+" : "-") << "\n";
    return os;
}

std::ofstream &Developer::operator<<(std::ofstream &ofs) const {
    int32_t type = DEVELOPER;
    ofs << write_le_int32(type)
        << write_str(_name)
        << write_le_int32(_base_salary)
        << write_bool(_has_bonus);
    return ofs;
}

//DEVELOPER finish

//SALES MANAGER start

int32_t SalesManager::salary() const {
    return (int32_t) (_base_salary + (_sold_nm * _price) / (double) SM_SALARY_COEFF);
}

std::istream &SalesManager::operator>>(std::istream &is) {
    is >> _name >> _base_salary >> _sold_nm >> _price;
    return is;
}

std::ifstream &SalesManager::operator>>(std::ifstream &ifs) {
    ifs >> read_str(_name)
        >> read_le_int32(_base_salary)
        >> read_le_int32(_sold_nm)
        >> read_le_int32(_price);
    return ifs;
}

std::ostream &SalesManager::operator<<(std::ostream &os) const {
    os << "Sales Manager" << "\n"
       << "Name: " << _name << "\n"
       << "Base Salary: " << _base_salary << "\n"
       << "Sold items: " << _sold_nm << "\n"
       << "Item price: " << _price << "\n";
    return os;
}

std::ofstream &SalesManager::operator<<(std::ofstream &ofs) const {
    int32_t type = SALES_MANAGER;
    ofs << write_le_int32(type)
        << write_str(_name)
        << write_le_int32(_base_salary)
        << write_le_int32(_sold_nm)
        << write_le_int32(_price);
    return ofs;
}

//SALES MANAGER finish

//EMPLOYEES ARRAY start

EmployeesArray::EmployeesArray() : _capacity(100), _size(0) {
    _employees = new Employee *[_capacity];
}

EmployeesArray::~EmployeesArray() {
    for (int i = 0; i < _size; i++)
        delete _employees[i];

    delete[] _employees;
}

void EmployeesArray::add(const Employee *e) {
    if (_size == _capacity) {
        _capacity *= 2;
        auto **temp_employees = new Employee *[_capacity];
        for (int i = 0; i < _size; i++)
            temp_employees[i] = _employees[i];
        delete[] _employees;
        _employees = temp_employees;
    }
    _employees[_size++] = const_cast<Employee *>(e);
}

int EmployeesArray::total_salary() const {
    int32_t total = 0;
    for (int i = 0; i < _size; i++)
        total += _employees[i]->salary();
    return total;
}

std::ifstream &operator>>(std::ifstream &ifs, EmployeesArray &emp_arr) {
    int32_t count;
    ifs >> read_le_int32(count);
    int32_t type;
    for (int i = 0; i < count; i++) {
        ifs >> read_le_int32(type);
        Employee *employee = nullptr;
        if (type == DEVELOPER) {
            employee = new Developer();
        } else if (type == SALES_MANAGER) {
            employee = new SalesManager();
        }
        assert(employee != nullptr);
        ifs >> *employee;
        emp_arr.add(employee);
    }
    return ifs;
}

std::ostream &operator<<(std::ostream &os, const EmployeesArray &emp_arr) {
    for (int i = 0; i < emp_arr._size; i++) {
        os << i + 1 << ". " << *emp_arr._employees[i];
    }
    os << "== Total salary: " << emp_arr.total_salary() << "\n";
    return os;
}

std::ofstream &operator<<(std::ofstream &ofs, const EmployeesArray &emp_arr) {
    ofs << write_le_int32(emp_arr._size);
    for (int i = 0; i < emp_arr._size; i++) {
        ofs << *emp_arr._employees[i];
    }
    return ofs;
}

//EMPLOYEES ARRAY finish