#include "../include/matrix.h"
#include <new>

Matrix::Matrix(int rows, int cols) try : matrix_(rows, std::vector<int>(cols)) {
} catch (std::bad_alloc &exc) {
    throw MatrixException("Unable to allocate memory.");
}

int Matrix::getRows() const {
    return matrix_.size();
}

int Matrix::getCols() const {
    return matrix_[0].size();
}

void Matrix::setCell(int row, int col, int value) {
    matrix_[row][col] = value;
}

int Matrix::getCell(int row, int col) const {
    if (row < 0 || row >= getRows() || col < 0 || col >= getCols())
        throw MatrixException("ACCESS: bad index.");
    return matrix_[row][col];
}

Matrix &Matrix::operator*=(const Matrix &other) {
    return *this = *this * other;
}

Matrix &Matrix::operator+=(const Matrix &other) {
    if (getRows() != other.getRows() || getCols() != other.getCols())
        throw MatrixException("ADD: dimensions do not match.");
    for (int i = 0; i < getRows(); i++)
        for (int j = 0; j < getCols(); j++)
            matrix_[i][j] += other.getCell(i, j);
    return *this;
}

Matrix Matrix::operator*(const Matrix &other) {
    if (getRows() != other.getRows())
        throw MatrixException("MUL: #arg1.columns != #arg2.rows.");
    Matrix newMatrix = Matrix(getRows(), other.getCols());
    for (int i = 0; i < getRows(); i++) {
        for (int j = 0; j < other.getCols(); j++) {
            for (int k = 0; k < getCols(); k++) {
                newMatrix.setCell(i, j, newMatrix.getCell(i, j) + matrix_[i][k] * other.getCell(k, j));
            }
        }
    }
    return newMatrix;
}

void Matrix::loadMatrix(const std::string &file_name) {
    int rows, cols, value;
    std::ifstream file(file_name);
    if (!file)
        throw MatrixException("LOAD: unable to open file.");
    if (!(file >> rows >> cols))
        throw MatrixException("LOAD: invalid file format.");
    Matrix temp = Matrix(rows, cols);
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (!(file >> value)) {
                throw MatrixException("LOAD: invalid file format.");
            }
            temp.matrix_[i][j] = value;
        }
    }
    *this = temp;
}

void Matrix::printMatrix() const {
    for (int i = 0; i < getRows(); i++) {
        for (int j = 0; j < getCols(); j++) {
            std::cout << matrix_[i][j] << " ";
        }
        std::cout << "\n";
    }
}