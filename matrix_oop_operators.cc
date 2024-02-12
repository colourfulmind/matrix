#include "matrix_oop.h"

Matrix &Matrix::operator=(const Matrix &other) noexcept {
  if (rows_ != other.rows_ || cols_ != other.cols_) {
      DeleteMatrix();
    rows_ = other.rows_;
    cols_ = other.cols_;
      CreateMatrix();
  }
    CopyMatrix(other);
  return *this;
}

bool Matrix::operator==(const Matrix &other) const noexcept {
  bool status = EqMatrix(other);
  return status;
}

Matrix &Matrix::operator+(const Matrix &other) {
  return *this += other;
}

Matrix &Matrix::operator+=(const Matrix &other) {
  SumMatrix(other);
  return *this;
}

Matrix &Matrix::operator-(const Matrix &other) {
  return *this -= other;
}

Matrix &Matrix::operator-=(const Matrix &other) {
  SubMatrix(other);
  return *this;
}

Matrix &Matrix::operator*(const double num) noexcept {
  MulNumber(num);
  return *this;
}

Matrix operator*(const double num, const Matrix &other) noexcept {
  Matrix tmp(other);
  tmp.MulNumber(num);
  return tmp;
}

Matrix &Matrix::operator*(const Matrix &other) {
  MulMatrix(other);
  return *this;
}

Matrix &Matrix::operator*=(const double num) noexcept {
  MulNumber(num);
  return *this;
}

Matrix &Matrix::operator*=(const Matrix &other) {
  MulMatrix(other);
  return *this;
}

double &Matrix::operator()(int row, int col) {
  if (row < 0 || col < 0 || row >= rows_ || col >= cols_) {
    throw std::invalid_argument("Index is out of range");
  }
  return matrix_[row][col];
}
