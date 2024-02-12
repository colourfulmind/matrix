#ifndef MATRIX_OOP_H
#define MATRIX_OOP_H

#include <math.h>

#include <iostream>

class Matrix {
 public:
  Matrix() noexcept;
  explicit Matrix(int rows, int cols);
  Matrix(const Matrix &other) noexcept;
  Matrix(Matrix &&other) noexcept;
  ~Matrix() noexcept;

  int GetRows() const noexcept;
  int GetCols() const noexcept;
  void SetRows(int rows);
  void SetCols(int cols);
  double **GetMatrix() noexcept;

  bool EqMatrix(const Matrix &other) const noexcept;
  void SumMatrix(const Matrix &other);
  void SubMatrix(const Matrix &other);
  void MulNumber(const double num) const noexcept;
  void MulMatrix(const Matrix &other);
  Matrix Transpose() const noexcept;
  Matrix CalcComplements() const;
  double Determinant() const;
  Matrix InverseMatrix() const;

  Matrix &operator=(const Matrix &other) noexcept;
  bool operator==(const Matrix &other) const noexcept;
  Matrix &operator+(const Matrix &other);
  Matrix &operator+=(const Matrix &other);
  Matrix &operator-(const Matrix &other);
  Matrix &operator-=(const Matrix &other);
  Matrix &operator*(const double num) noexcept;
  friend Matrix operator*(const double num, const Matrix& other) noexcept;
  Matrix &operator*(const Matrix &other);
  Matrix &operator*=(const double num) noexcept;
  Matrix &operator*=(const Matrix &other);
  double &operator()(int row, int col);

 private:
  int rows_, cols_;
  double **matrix_;

  void CreateMatrix();
  void CopyMatrix(const Matrix &other) noexcept;
  void DeleteMatrix() noexcept;
  void GetMatrixMinor(Matrix &minor, int row, int col) const noexcept;
  double FindDeterminant(int size) const noexcept;
};

#endif  // MATRIX_OOP_H
