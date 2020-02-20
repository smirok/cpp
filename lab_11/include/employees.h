#ifndef LAB11_EMPLOYEES_H_INCLUDED
#define LAB11_EMPLOYEES_H_INCLUDED

#include <cstdint>
#include <iostream>

enum employees_type_and_constants{
    DEVELOPER = 1,
    SALES_MANAGER = 2,
    DEVELOPER_SALARY_BONUS = 1000,
    SM_SALARY_COEFF = 100
};


class Employee {
public:
    virtual ~Employee() = default;

    virtual int salary() const = 0;

    virtual std::istream &operator>>(std::istream &) = 0;

    virtual std::ifstream &operator>>(std::ifstream &) = 0;

    virtual std::ostream &operator<<(std::ostream &) const = 0;

    virtual std::ofstream &operator<<(std::ofstream &) const = 0;

protected:
    std::string _name;
    int32_t _base_salary;
};

std::istream &operator>>(std::istream &is, Employee &e);

std::ifstream &operator>>(std::ifstream &ifs, Employee &e);

std::ostream &operator<<(std::ostream &os, const Employee &e);

std::ofstream &operator<<(std::ofstream &ofs, const Employee &e);

class Developer : public Employee {
public:
    Developer() { _name = ""; };

    int32_t salary() const override;

    std::istream &operator>>(std::istream &) override;

    std::ifstream &operator>>(std::ifstream &) override;

    std::ostream &operator<<(std::ostream &) const override;

    std::ofstream &operator<<(std::ofstream &) const override;

private:
    Developer(const Developer &) {};

    Developer &operator=(Developer &other) { return other; };
    bool _has_bonus;
};

class SalesManager : public Employee {
public:
    SalesManager() { _name = ""; };

    int32_t salary() const override;

    std::istream &operator>>(std::istream &is) override;

    std::ifstream &operator>>(std::ifstream &ifs) override;

    std::ostream &operator<<(std::ostream &os) const override;

    std::ofstream &operator<<(std::ofstream &ofs) const override;

private:
    SalesManager(const SalesManager &) {};

    SalesManager &operator=(SalesManager &other) { return other; };

    int32_t _sold_nm, _price;
};

class EmployeesArray {
public:
    EmployeesArray();

    ~EmployeesArray();

    void add(const Employee *e);

    int total_salary() const;

    friend std::ifstream &operator>>(std::ifstream &ifs, EmployeesArray &);

    friend std::ostream &operator<<(std::ostream &os, const EmployeesArray &);

    friend std::ofstream &operator<<(std::ofstream &ofs, const EmployeesArray &);

private:
    Employee **_employees;
    int32_t _capacity;
    int32_t _size;
};

#endif