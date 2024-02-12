#include "matrix_oop.h"

Matrix::Matrix() noexcept : rows_(0), cols_(0), matrix_(nullptr) {}

Matrix::Matrix(int rows, int cols)
    : rows_(rows), cols_(cols), matrix_(nullptr) {
  if (rows < 1 || cols < 1) {
    throw std::out_of_range("Incorrect input");
  }
  CreateMatrix();
}

Matrix::Matrix(const Matrix &other) noexcept
    : rows_(other.rows_), cols_(other.cols_), matrix_(nullptr) {
  CreateMatrix();
  CopyMatrix(other);
}

Matrix::Matrix(Matrix &&other) noexcept
    : rows_(other.rows_), cols_(other.cols_), matrix_(other.matrix_) {
  other.rows_ = 0;
  other.cols_ = 0;
  other.matrix_ = nullptr;
}

Matrix::~Matrix() noexcept { DeleteMatrix(); }

void Matrix::CreateMatrix() {
  matrix_ = new (std::nothrow) double *[rows_];
  if (matrix_ == nullptr) throw std::bad_alloc();
  for (double **ptr = matrix_; ptr - matrix_ < rows_; ptr++) {
    *ptr = new (std::nothrow) double[cols_];
    if (*ptr == nullptr) throw std::bad_alloc();
  }
}

void Matrix::CopyMatrix(const Matrix &other) noexcept {
  for (int i = 0; i < rows_ && i < other.rows_; ++i) {
    for (int j = 0; j < cols_ && j < other.cols_; j++) {
      matrix_[i][j] = other.matrix_[i][j];
    }
  }
}

void Matrix::DeleteMatrix() noexcept {
  for (int i = 0; i < rows_; ++i) {
    delete[] matrix_[i];
  }
  delete[] matrix_;
}

int Matrix::GetRows() const noexcept { return rows_; }

int Matrix::GetCols() const noexcept { return cols_; }

void Matrix::SetRows(int rows) {
  if (rows < 1) {
    throw std::out_of_range("Value must be greater than zero");
  }
  if (rows != rows_) {
    Matrix res(rows, cols_);
    res.CopyMatrix(*this);
    *this = std::move(res);
  }
}

void Matrix::SetCols(int cols) {
  if (cols < 1) {
    throw std::out_of_range("Value must be greater than zero");
  }
  if (cols != cols_) {
    Matrix res(rows_, cols);
    res.CopyMatrix(*this);
    *this = std::move(res);
  }
}

double **Matrix::GetMatrix() noexcept { return matrix_; }
