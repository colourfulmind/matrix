#include "matrix_oop.h"

bool Matrix::EqMatrix(const Matrix &other) const noexcept {
  bool status = 1;
  if (rows_ != other.rows_ || cols_ != other.cols_) {
    status = 0;
  } else {
    double tmp = 0;
    for (int i = 0; i < rows_; ++i) {
      for (int j = 0; j < cols_; ++j) {
        tmp = matrix_[i][j] - other.matrix_[i][j];
        if (fabs(tmp) >= 1e-7) {
          status = 0;
          break;
        }
      }
    }
  }
  return status;
}

void Matrix::SumMatrix(const Matrix &other) {
  if (rows_ != other.rows_ || cols_ != other.cols_) {
    throw std::invalid_argument("Matrices are different size");
  }
  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < cols_; ++j) {
      matrix_[i][j] += other.matrix_[i][j];
    }
  }
}

void Matrix::SubMatrix(const Matrix &other) {
  other.MulNumber(-1);
  SumMatrix(other);
}

void Matrix::MulNumber(const double num) const noexcept {
  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < cols_; ++j) {
      matrix_[i][j] *= num;
    }
  }
}

void Matrix::MulMatrix(const Matrix &other) {
  if (cols_ != other.rows_) {
    throw std::invalid_argument("Can't multiply matrices");
  }
  Matrix res(rows_, other.cols_);
  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < other.cols_; ++j) {
      for (int k = 0; k < cols_; k++) {
        res.matrix_[i][j] += matrix_[i][k] * other.matrix_[k][j];
      }
    }
  }
  *this = std::move(res);
}

Matrix Matrix::Transpose() const noexcept {
  Matrix res(cols_, rows_);
  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < cols_; ++j) {
      res(j, i) = matrix_[i][j];
    }
  }
  return res;
}

Matrix Matrix::CalcComplements() const {
  if (rows_ != cols_) {
    throw std::invalid_argument("Matrix has to be square");
  }
  Matrix res(rows_, cols_);
  if (rows_ == 1) {
    res.matrix_[0][0] = matrix_[0][0];
  } else {
    for (int i = 0; i < rows_; ++i) {
      for (int j = 0; j < cols_; ++j) {
        Matrix minor(rows_ - 1, cols_ - 1);
        GetMatrixMinor(minor, i, j);
        double det = 0.0;
        det = minor.Determinant();
        res.matrix_[i][j] = pow(-1, i + j) * det;
      }
    }
  }
  return res;
}

void Matrix::GetMatrixMinor(Matrix &minor, int row, int col) const noexcept {
  int minor_row = 0;
  int minor_column = 0;
  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < cols_; ++j) {
      if (i != row && j != col) {
        minor.matrix_[minor_row][minor_column] = matrix_[i][j];
        minor_column++;
      }
    }
    if (i != row) minor_row++;
    minor_column = 0;
  }
}

double Matrix::Determinant() const {
  double result = 0;
  if (rows_ != cols_) {
    throw std::invalid_argument("Matrix has to be square");
  }
  result = FindDeterminant(rows_);
  return result;
}

double Matrix::FindDeterminant(int size) const noexcept {
  double det = 0.0;
  int sign = 1;
  if (size == 1) {
    det = matrix_[0][0];
  } else if (size == 2) {
    det = matrix_[0][0] * matrix_[1][1] - matrix_[0][1] * matrix_[1][0];
  } else {
    Matrix buffer(size - 1, size - 1);
    for (int i = 0; i < size; ++i) {
      GetMatrixMinor(buffer, i, 0);
      det += (sign * matrix_[i][0] * buffer.FindDeterminant(buffer.rows_));
      sign *= -1;
    }
  }
  return det;
}

Matrix Matrix::InverseMatrix() const {
  double det = Determinant();
  if (fabs(det) < 1e-7) {
    throw std::invalid_argument("Determinant can't be equal zero");
  }
  Matrix buffer = Transpose();
  Matrix res = buffer.CalcComplements();
  res.MulNumber(1.0 / det);
  return res;
}
