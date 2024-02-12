#include <gtest/gtest.h>

#include "matrix_oop.h"

// CONSTRUCTOR
TEST(constructor, case1) {
  Matrix a;

  ASSERT_EQ(a.GetRows(), 0) << "Expected 0 rows to be created";
  ASSERT_EQ(a.GetCols(), 0) << "Expected 0 columns to be created";
}

TEST(constructor, case2) {
  Matrix a(2, 2);

  ASSERT_NE(a.GetMatrix(), nullptr) << "Matrix must be a null pointer";
  ASSERT_EQ(a.GetRows(), 2) << "Expected 2 rows to be created";
  ASSERT_EQ(a.GetCols(), 2) << "Expected 2 columns to be created";
}

TEST(constructor, case3) {
  Matrix a(2, 2);
  a(0, 0) = 1;
  a(0, 1) = 5;
  a(1, 0) = -4;
  a(1, 1) = 0;
  Matrix b(a);

  ASSERT_EQ(b.GetRows(), 2) << "Expected 2 rows to be created";
  ASSERT_EQ(b.GetCols(), 2) << "Expected 2 columns to be created";
  ASSERT_EQ(b(0, 0), 1) << "Matrix's value [0][0] must be 1";
  ASSERT_EQ(b(0, 1), 5) << "Matrix's value [0][1] must be 5";
  ASSERT_EQ(b(1, 0), -4) << "Matrix's value [1][0] must be -4";
  ASSERT_EQ(b(1, 1), 0) << "Matrix's value [1][1] must be 0";
}

TEST(constructor, case4) {
  Matrix a(2, 2);
  Matrix b = std::move(a);

  ASSERT_EQ(a.GetRows(), 0) << "Expected 0 rows";
  ASSERT_EQ(a.GetCols(), 0) << "Expected 0 columns";
  ASSERT_EQ(a.GetMatrix(), nullptr) << "Matrix must be removed in this case";
  ASSERT_EQ(b.GetRows(), 2) << "Expected 2 rows to be created";
  ASSERT_EQ(b.GetCols(), 2) << "Expected 2 cols to be created";
  ASSERT_NE(b.GetMatrix(), nullptr) << "Matrix must point to the NULL";
}

TEST(constructor, case5) {
  EXPECT_THROW(Matrix a(0, 8);, std::out_of_range)
      << "Exception must be thrown";
}

TEST(constructor, case6) {
  Matrix a(2, 2);
  Matrix b(3, 5);

  ASSERT_NE(a.GetRows(), b.GetRows())
      << "Created matrices must be different size";
  ASSERT_NE(a.GetCols(), b.GetCols())
      << "Created matrices must be different size";
}

// EQUALITY
TEST(equality, case1) {
  Matrix a(2, 2);
  Matrix b(2, 2);
  double reference[2][2] = {{1, 5}, {-4, 0}};
  for (int i = 0; i < 2; ++i) {
    for (int j = 0; j < 2; ++j) {
      a(i, j) = reference[i][j];
      b(i, j) = reference[i][j];
    }
  }
  ASSERT_EQ(a.EqMatrix(b), 1) << "Matrices must be equal";
}

TEST(equality, case2) {
  Matrix a(2, 2);
  double reference[2][2] = {{1, 5}, {-4, 0}};
  for (int i = 0; i < 2; ++i) {
    for (int j = 0; j < 2; ++j) {
      a(i, j) = reference[i][j];
    }
  }
  Matrix b(a);

  ASSERT_EQ(a.EqMatrix(b), 1) << "Matrices must be equal";
}

TEST(equality, case3) {
  Matrix a(2, 2);
  double reference[2][2] = {{1, 5}, {-4, 0}};
  for (int i = 0; i < 2; ++i) {
    for (int j = 0; j < 2; ++j) {
      a(i, j) = reference[i][j];
    }
  }
  Matrix b = std::move(a);

  ASSERT_NE(a.EqMatrix(b), 1) << "Matrices must not be equal";
}

TEST(equality, case4) {
  Matrix a(2, 2);
  double reference_a[2][2] = {{1, 5}, {-4, 0}};
  for (int i = 0; i < 2; ++i) {
    for (int j = 0; j < 2; ++j) {
      a(i, j) = reference_a[i][j];
    }
  }
  Matrix b(2, 2);
  double reference_b[2][2] = {{1.0000004, 5}, {-4, 0}};
  for (int i = 0; i < 2; ++i) {
    for (int j = 0; j < 2; ++j) {
      b(i, j) = reference_b[i][j];
    }
  }

  ASSERT_NE(a.EqMatrix(b), 1) << "Matrices must not be equal";
}

TEST(equality, case5) {
  Matrix a(2, 2);
  Matrix b(2, 2);
  double reference[2][2] = {{1, 5}, {-4, 0}};
  for (int i = 0; i < 2; ++i) {
    for (int j = 0; j < 2; ++j) {
      a(i, j) = reference[i][j];
      b(i, j) = reference[i][j];
    }
  }

  ASSERT_EQ(a == b, 1) << "Matrices must be equal";
}

// ADDITION
TEST(addition, case1) {
  Matrix a(2, 2);
  double reference_a[2][2] = {{15, -8}, {-4, 26}};
  Matrix b(2, 2);
  double reference_b[2][2] = {{1, 5}, {-4, 0}};
  Matrix r(2, 2);
  double reference_r[2][2] = {{16, -3}, {-8, 26}};
  for (int i = 0; i < 2; ++i) {
    for (int j = 0; j < 2; ++j) {
      a(i, j) = reference_a[i][j];
      b(i, j) = reference_b[i][j];
      r(i, j) = reference_r[i][j];
    }
  }
  a.SumMatrix(b);

  ASSERT_EQ(a.EqMatrix(r), 1)
      << "an error occurred while trying to add matrices";
}

TEST(addition, case2) {
  Matrix a(3, 3);
  Matrix b(2, 2);

  EXPECT_THROW(a.SumMatrix(b);, std::invalid_argument)
      << "Exception must be thrown";
}

TEST(addition, case3) {
  Matrix a(2, 2);
  double reference_a[2][2] = {{15, -8}, {-4, 26}};
  Matrix b(2, 2);
  double reference_b[2][2] = {{1, 5}, {-4, 0}};
  Matrix r(2, 2);
  double reference_r[2][2] = {{16, -3}, {-8, 26}};
  for (int i = 0; i < 2; ++i) {
    for (int j = 0; j < 2; ++j) {
      a(i, j) = reference_a[i][j];
      b(i, j) = reference_b[i][j];
      r(i, j) = reference_r[i][j];
    }
  }
  a = a + b;

  ASSERT_EQ(a.EqMatrix(r), 1)
      << "an error occurred while trying to add matrices";
}

TEST(addition, case4) {
  Matrix a(3, 3);
  Matrix b(2, 2);

  EXPECT_THROW(a = a + b;, std::invalid_argument) << "Exception must be thrown";
}

TEST(addition, case5) {
  Matrix a(2, 2);
  double reference_a[2][2] = {{15, -8}, {-4, 26}};
  Matrix b(2, 2);
  double reference_b[2][2] = {{1, 5}, {-4, 0}};
  Matrix r(2, 2);
  double reference_r[2][2] = {{16, -3}, {-8, 26}};
  for (int i = 0; i < 2; ++i) {
    for (int j = 0; j < 2; ++j) {
      a(i, j) = reference_a[i][j];
      b(i, j) = reference_b[i][j];
      r(i, j) = reference_r[i][j];
    }
  }
  a += b;

  ASSERT_EQ(a.EqMatrix(r), 1)
      << "an error occurred while trying to add matrices";
}

TEST(addition, case6) {
  Matrix a(3, 3);
  Matrix b(2, 2);

  EXPECT_THROW(a += b;, std::invalid_argument) << "Exception must be thrown";
}

// SUBTRACTION
TEST(subtraction, case1) {
  Matrix a(2, 2);
  double reference_a[2][2] = {{15, -8}, {-4, 26}};
  Matrix b(2, 2);
  double reference_b[2][2] = {{15, -8}, {-4, 26}};
  Matrix r(2, 2);
  double reference_r[2][2] = {{0, 0}, {0, 0}};
  for (int i = 0; i < 2; ++i) {
    for (int j = 0; j < 2; ++j) {
      a(i, j) = reference_a[i][j];
      b(i, j) = reference_b[i][j];
      r(i, j) = reference_r[i][j];
    }
  }
  a.SubMatrix(b);

  ASSERT_EQ(a.EqMatrix(r), 1)
      << "an error occurred while trying to subtract matrices";
}

TEST(subtraction, case2) {
  Matrix a(3, 3);
  Matrix b(2, 2);

  EXPECT_THROW(a.SubMatrix(b);, std::invalid_argument)
      << "Exception must be thrown";
}

TEST(subtraction, case3) {
  Matrix a(2, 2);
  double reference_a[2][2] = {{15, -8}, {-4, 26}};
  Matrix b(2, 2);
  double reference_b[2][2] = {{15, -8}, {-4, 26}};
  Matrix r(2, 2);
  double reference_r[2][2] = {{0, 0}, {0, 0}};
  for (int i = 0; i < 2; ++i) {
    for (int j = 0; j < 2; ++j) {
      a(i, j) = reference_a[i][j];
      b(i, j) = reference_b[i][j];
      r(i, j) = reference_r[i][j];
    }
  }
  a = a - b;

  ASSERT_EQ(a.EqMatrix(r), 1)
      << "an error occurred while trying to subtract matrices";
}

TEST(subtraction, case4) {
  Matrix a(3, 3);
  Matrix b(2, 2);

  EXPECT_THROW(a = a - b;, std::invalid_argument) << "Exception must be thrown";
}

TEST(subtraction, case5) {
  Matrix a(2, 2);
  double reference_a[2][2] = {{15, -8}, {-4, 26}};
  Matrix b(2, 2);
  double reference_b[2][2] = {{15, -8}, {-4, 26}};
  Matrix r(2, 2);
  double reference_r[2][2] = {{0, 0}, {0, 0}};
  for (int i = 0; i < 2; ++i) {
    for (int j = 0; j < 2; ++j) {
      a(i, j) = reference_a[i][j];
      b(i, j) = reference_b[i][j];
      r(i, j) = reference_r[i][j];
    }
  }
  a -= b;

  ASSERT_EQ(a.EqMatrix(r), 1)
      << "an error occurred while trying to subtract matrices";
}

TEST(subtraction, case6) {
  Matrix a(3, 3);
  Matrix b(2, 2);

  EXPECT_THROW(a -= b;, std::invalid_argument) << "Exception must be thrown";
}

// MULTIPLICATION BY NUMBER
TEST(multiplication, case1) {
  Matrix a(2, 3);
  double reference_a[2][3] = {{14, -2, 0}, {8, -12, -6}};
  Matrix r(2, 3);
  double reference_r[2][3] = {{42, -6, 0}, {24, -36, -18}};
  for (int i = 0; i < 2; ++i) {
    for (int j = 0; j < 3; ++j) {
      a(i, j) = reference_a[i][j];
      r(i, j) = reference_r[i][j];
    }
  }
  a.MulNumber(3);

  ASSERT_EQ(a.EqMatrix(r), 1)
      << "an error occurred while trying to multiply matrix by number";
}

TEST(multiplication, case2) {
  Matrix a(3, 3);
  double reference_a[3][3] = {{15, -8, 1}, {-4, 26, 4}, {-4, 26, 4}};
  Matrix r(3, 3);
  double reference_r[3][3] = {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}};
  for (int i = 0; i < 2; ++i) {
    for (int j = 0; j < 2; ++j) {
      a(i, j) = reference_a[i][j];
      r(i, j) = reference_r[i][j];
    }
  }
  a.MulNumber(0);

  ASSERT_EQ(a.EqMatrix(r), 1)
      << "an error occurred while trying to multiply matrix by number";
}

TEST(multiplication, case3) {
  Matrix a(2, 3);
  double reference_a[2][3] = {{14, -2, 0}, {8, -12, -6}};
  Matrix r(2, 3);
  double reference_r[2][3] = {{42, -6, 0}, {24, -36, -18}};
  for (int i = 0; i < 2; ++i) {
    for (int j = 0; j < 3; ++j) {
      a(i, j) = reference_a[i][j];
      r(i, j) = reference_r[i][j];
    }
  }
  a = 3 * a;

  ASSERT_EQ(a.EqMatrix(r), 1)
      << "an error occurred while trying to multiply matrix by number";
}

TEST(multiplication, case4) {
  Matrix a(3, 3);
  double reference_a[3][3] = {{15, -8, 1}, {-4, 26, 4}, {-4, 26, 4}};
  Matrix r(3, 3);
  double reference_r[3][3] = {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}};
  for (int i = 0; i < 2; ++i) {
    for (int j = 0; j < 2; ++j) {
      a(i, j) = reference_a[i][j];
      r(i, j) = reference_r[i][j];
    }
  }
  a = a * 0;

  ASSERT_EQ(a.EqMatrix(r), 1)
      << "an error occurred while trying to multiply matrix by number";
}

TEST(multiplication, case5) {
  Matrix a(2, 3);
  double reference_a[2][3] = {{14, -2, 0}, {8, -12, -6}};
  Matrix r(2, 3);
  double reference_r[2][3] = {{42, -6, 0}, {24, -36, -18}};
  for (int i = 0; i < 2; ++i) {
    for (int j = 0; j < 3; ++j) {
      a(i, j) = reference_a[i][j];
      r(i, j) = reference_r[i][j];
    }
  }
  a *= 3;

  ASSERT_EQ(a.EqMatrix(r), 1)
      << "an error occurred while trying to multiply matrix by number";
}

TEST(multiplication, case6) {
  Matrix a(3, 3);
  double reference_a[3][3] = {{15, -8, 1}, {-4, 26, 4}, {-4, 26, 4}};
  Matrix r(3, 3);
  double reference_r[3][3] = {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}};
  for (int i = 0; i < 2; ++i) {
    for (int j = 0; j < 2; ++j) {
      a(i, j) = reference_a[i][j];
      r(i, j) = reference_r[i][j];
    }
  }
  a *= 0;

  ASSERT_EQ(a.EqMatrix(r), 1)
      << "an error occurred while trying to multiply matrix by number";
}

// MULTIPLICATION BY MATRIX

TEST(multiplication, case7) {
  Matrix a(2, 3);
  double reference_a[2][3] = {{1.4, -2, 0}, {88, -123, -0.6}};
  for (int i = 0; i < 2; ++i) {
    for (int j = 0; j < 3; ++j) {
      a(i, j) = reference_a[i][j];
    }
  }
  Matrix b(3, 4);
  double reference_b[3][4] = {
      {1.1, 2.2, -3.3, 0.1}, {880, -1230, -0.6, 123}, {1, 2, 3, 4}};
  for (int i = 0; i < 3; ++i) {
    for (int j = 0; j < 4; ++j) {
      b(i, j) = reference_b[i][j];
    }
  }
  Matrix r(2, 4);
  double reference_r[2][4] = {{-1758.46, 2463.08, -3.42, -245.86},
                              {-108143.8, 151482.4, -218.4, -15122.6}};
  for (int i = 0; i < 2; ++i) {
    for (int j = 0; j < 4; ++j) {
      r(i, j) = reference_r[i][j];
    }
  }
  a.MulMatrix(b);

  ASSERT_EQ(a.EqMatrix(r), 1)
      << "an error occurred while trying to multiply matrix by number";
}

TEST(multiplication, case8) {
  Matrix a(3, 3);
  Matrix b(2, 2);

  EXPECT_THROW(a.MulMatrix(b);, std::invalid_argument)
      << "Exception must be thrown";
}

TEST(multiplication, case9) {
  Matrix a(2, 3);
  double reference_a[2][3] = {{1.4, -2, 0}, {88, -123, -0.6}};
  for (int i = 0; i < 2; ++i) {
    for (int j = 0; j < 3; ++j) {
      a(i, j) = reference_a[i][j];
    }
  }
  Matrix b(3, 4);
  double reference_b[3][4] = {
      {1.1, 2.2, -3.3, 0.1}, {880, -1230, -0.6, 123}, {1, 2, 3, 4}};
  for (int i = 0; i < 3; ++i) {
    for (int j = 0; j < 4; ++j) {
      b(i, j) = reference_b[i][j];
    }
  }
  Matrix r(2, 4);
  double reference_r[2][4] = {{-1758.46, 2463.08, -3.42, -245.86},
                              {-108143.8, 151482.4, -218.4, -15122.6}};
  for (int i = 0; i < 2; ++i) {
    for (int j = 0; j < 4; ++j) {
      r(i, j) = reference_r[i][j];
    }
  }
  a = a * b;

  ASSERT_EQ(a.EqMatrix(r), 1)
      << "an error occurred while trying to multiply matrix by number";
}

TEST(multiplication, case10) {
  Matrix a(3, 3);
  Matrix b(2, 2);

  EXPECT_THROW(a = a * b;, std::invalid_argument) << "Exception must be thrown";
}

TEST(multiplication, case11) {
  Matrix a(2, 3);
  double reference_a[2][3] = {{1.4, -2, 0}, {88, -123, -0.6}};
  for (int i = 0; i < 2; ++i) {
    for (int j = 0; j < 3; ++j) {
      a(i, j) = reference_a[i][j];
    }
  }
  Matrix b(3, 4);
  double reference_b[3][4] = {
      {1.1, 2.2, -3.3, 0.1}, {880, -1230, -0.6, 123}, {1, 2, 3, 4}};
  for (int i = 0; i < 3; ++i) {
    for (int j = 0; j < 4; ++j) {
      b(i, j) = reference_b[i][j];
    }
  }
  Matrix r(2, 4);
  double reference_r[2][4] = {{-1758.46, 2463.08, -3.42, -245.86},
                              {-108143.8, 151482.4, -218.4, -15122.6}};
  for (int i = 0; i < 2; ++i) {
    for (int j = 0; j < 4; ++j) {
      r(i, j) = reference_r[i][j];
    }
  }
  a *= b;

  ASSERT_EQ(a.EqMatrix(r), 1)
      << "an error occurred while trying to multiply matrix by number";
}

TEST(multiplication, case12) {
  Matrix a(3, 3);
  Matrix b(2, 2);

  EXPECT_THROW(a *= b;, std::invalid_argument) << "Exception must be thrown";
}

// TRANSPOSE
TEST(transpose, case1) {
  Matrix a(3, 4);
  double reference_a[3][4] = {{1, 2, 3, 4}, {2, 3, 4, 5}, {3, 4, 5, 6}};
  Matrix r(4, 3);
  double reference_r[4][3] = {{1, 2, 3}, {2, 3, 4}, {3, 4, 5}, {4, 5, 6}};
  for (int i = 0; i < 3; ++i) {
    for (int j = 0; j < 4; ++j) {
      a(i, j) = reference_a[i][j];
      r(j, i) = reference_r[j][i];
    }
  }
  Matrix result = a.Transpose();

  ASSERT_EQ(result.EqMatrix(r), 1)
      << "an error occurred while trying to transpose matrix";
}

// COMPLEMENTS CALCULATION
TEST(complements, case1) {
  Matrix a(1, 1), r(1, 1);
  double matrix[1][1] = {{1}};
  a(0, 0) = matrix[0][0];
  r(0, 0) = matrix[0][0];
  Matrix result = a.CalcComplements();

  ASSERT_EQ(result.EqMatrix(r), 1)
      << "an error occurred while calculating complements of the matrix";
}

TEST(complements, case2) {
  Matrix a(2, 2), r(2, 2);
  double matrix_a[2][2] = {{1, 2}, {3, 4}};
  double matrix_r[2][2] = {{4, -3}, {-2, 1}};
  for (int i = 0; i < 2; ++i) {
    for (int j = 0; j < 2; ++j) {
      a(i, j) = matrix_a[i][j];
      r(i, j) = matrix_r[i][j];
    }
  }
  Matrix result = a.CalcComplements();

  ASSERT_EQ(result.EqMatrix(r), 1)
      << "an error occurred while calculating complements of the matrix";
}

TEST(complements, case3) {
  Matrix a(3, 3), r(3, 3);
  double matrix_a[3][3] = {{1, 22, 333}, {-0.1, 5.5, 0}, {123, 9, 5.5}};
  double matrix_r[3][3] = {
      {30.25, 0.55, -677.4}, {2876, -40953.5, 2697}, {-1831.5, -33.3, 7.7}};
  for (int i = 0; i < 3; ++i) {
    for (int j = 0; j < 3; ++j) {
      a(i, j) = matrix_a[i][j];
      r(i, j) = matrix_r[i][j];
    }
  }
  Matrix result = a.CalcComplements();

  ASSERT_EQ(result.EqMatrix(r), 1)
      << "an error occurred while calculating complements of the matrix";
}

TEST(complements, case4) {
  Matrix a(4, 4), r(4, 4);
  double matrix_a[4][4] = {
      {9, -2222, 0, 1000}, {6, 5, 467, 3}, {12, 23, 34, 45}, {-1, 2, 3, -4}};
  double matrix_r[4][4] = {{83642, 15, -936, -21605},
                           {-603162, 67561, -38696, 155549},
                           {3251694, -468107, -29896, -1069399},
                           {57039686, -5211783, -599352, -12093939}};
  for (int i = 0; i < 4; ++i) {
    for (int j = 0; j < 4; ++j) {
      a(i, j) = matrix_a[i][j];
      r(i, j) = matrix_r[i][j];
    }
  }
  Matrix result = a.CalcComplements();

  ASSERT_EQ(result.EqMatrix(r), 1)
      << "an error occurred while calculating complements of the matrix";
}

TEST(complements, case5) {
  Matrix a(3, 4);

  EXPECT_THROW(a.CalcComplements();, std::invalid_argument)
      << "Exception must be thrown";
}

// DETERMINANT
TEST(determinant, case1) {
  Matrix a(4, 4);
  double matrix_a[4][4] = {
      {1, 2, 3, 4}, {2, 3, 4, 5}, {3, 4, 5, 6}, {4, 5, 6, 7}};
  for (int i = 0; i < 4; ++i) {
    for (int j = 0; j < 4; ++j) {
      a(i, j) = matrix_a[i][j];
    }
  }
  double res = a.Determinant();

  ASSERT_EQ(res, 0)
      << "an error occurred while calculating determinant of the matrix";
}

TEST(determinant, case2) {
  Matrix a(4, 4);
  double matrix_a[4][4] = {
      {1, 1, 1, -1}, {1, -2, 1, -1}, {1, 1, 3, 1}, {1, 1, 1, -4}};
  for (int i = 0; i < 4; ++i) {
    for (int j = 0; j < 4; ++j) {
      a(i, j) = matrix_a[i][j];
    }
  }
  double res = a.Determinant();

  ASSERT_EQ(res, 18)
      << "an error occurred while calculating determinant of the matrix";
}

TEST(determinant, case3) {
  Matrix a(3, 4);

  EXPECT_THROW(a.Determinant();, std::invalid_argument)
      << "Exception must be thrown";
}

// INVERSE MATRIX
TEST(inverse, case1) {
  Matrix a(2, 2), r(2, 2);
  double matrix_a[2][2] = {{100, -54.45}, {411, 0}};
  double matrix_r[2][2] = {{1, 0}, {0, 1}};
  for (int i = 0; i < 2; ++i) {
    for (int j = 0; j < 2; ++j) {
      a(i, j) = matrix_a[i][j];
      r(i, j) = matrix_r[i][j];
    }
  }
  Matrix t = a.InverseMatrix();
  a.MulMatrix(t);

  ASSERT_EQ(a.EqMatrix(r), 1)
      << "an error occurred while trying to inverse matrix";
}

TEST(inverse, case2) {
  Matrix a(3, 3), r(3, 3);
  double matrix_a[3][3] = {{1, 2, 3}, {4, 5, 6}, {12, 34, -56}};
  double matrix_r[3][3] = {{1, 0, 0}, {0, 1, 0}, {0, 0, 1}};
  for (int i = 0; i < 3; ++i) {
    for (int j = 0; j < 3; ++j) {
      a(i, j) = matrix_a[i][j];
      r(i, j) = matrix_r[i][j];
    }
  }
  Matrix t = a.InverseMatrix();
  a.MulMatrix(t);

  ASSERT_EQ(a.EqMatrix(r), 1)
      << "an error occurred while trying to inverse matrix";
}

TEST(inverse, case3) {
  Matrix a(3, 3);
  double matrix_a[3][3] = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
  for (int i = 0; i < 3; ++i) {
    for (int j = 0; j < 3; ++j) {
      a(i, j) = matrix_a[i][j];
    }
  }

  EXPECT_THROW(a.InverseMatrix();, std::invalid_argument)
      << "Exception must be thrown";
}

// BRACES
TEST(braces, case1) {
  Matrix a(2, 2);
  double matrix_a[2][2] = {{1, 2}, {3, 4}};
  for (int i = 0; i < 2; ++i) {
    for (int j = 0; j < 2; ++j) {
      a(i, j) = matrix_a[i][j];
    }
  }
  ASSERT_EQ(a(0, 1), 2) << "Values mast be equal";
}

TEST(braces, case2) {
  Matrix a(3, 4);

  EXPECT_THROW(a(-1, 2);, std::invalid_argument) << "Exception must be thrown";
}

// ACCESSORS
TEST(accessor, case1) {
  Matrix a(3, 4);
  a.SetRows(5);

  ASSERT_EQ(a.GetRows(), 5) << "rows must be equal 5";
}

TEST(accessor, case2) {
  Matrix a(3, 4);
  a.SetCols(5);

  ASSERT_EQ(a.GetCols(), 5) << "Columns must be equal 5";
}

// MUTATORS
TEST(mutator, case1) {
  Matrix a(3, 4);

  EXPECT_THROW(a.SetRows(0);, std::out_of_range) << "Exception must be thrown";
}

TEST(mutator, case2) {
  Matrix a(3, 4);

  EXPECT_THROW(a.SetCols(-2);, std::out_of_range) << "Exception must be thrown";
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
