#include <utility>
#include <vector>
#include <string>
#include <map>
#include <fstream>
#include <iostream>

#ifndef LAB_14_MATRIX_H
#define LAB_14_MATRIX_H


class Matrix {
public:
    explicit Matrix(int rows = 0, int cols = 0);

    void setCell(int row, int col, int value);
    int getCell(int row, int col) const;
    int getRows() const;
    int getCols() const;

    void loadMatrix(const std::string &file_name);
    void printMatrix() const;

    Matrix operator*(const Matrix &other);
    Matrix &operator+=(const Matrix &other);
    Matrix &operator*=(const Matrix &other);

private:
    std::vector<std::vector<int>> matrix_;
};

class MatrixException : public std::exception {
public:
    explicit MatrixException(std::string error_message) : error_message_(std::move(error_message)) {};

    const char *what() const noexcept { return this->error_message_.c_str(); };
private:
    std::string error_message_;
};

#endif //LAB_14_MATRIX_H
