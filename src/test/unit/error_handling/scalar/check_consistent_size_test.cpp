#include <stan/error_handling/scalar/check_consistent_size.hpp>
#include <gtest/gtest.h>

TEST(MathMatrixErrorHandling, checkConsistentSize) {
  using Eigen::Matrix;
  using Eigen::Dynamic;
  using stan::error_handling::check_consistent_size;
  using stan::size_of;

  const char* function = "checkConsistentSize(%1%)";
  const char* name1 = "name1";
  
  double result;

  Matrix<double,Dynamic,1> v1(4);
  EXPECT_EQ(4U, size_of(v1));
  EXPECT_TRUE(check_consistent_size(4U, function, v1, name1, &result));
  EXPECT_THROW(check_consistent_size(2U, function, v1, name1, &result), std::domain_error);
}

TEST(MathMatrixErrorHandling, checkConsistentSize_nan) {
  using Eigen::Matrix;
  using Eigen::Dynamic;
  using stan::error_handling::check_consistent_size;
  using stan::size_of;

  const char* function = "checkConsistentSize(%1%)";
  const char* name1 = "name1";
  
  double result;
  double nan = std::numeric_limits<double>::quiet_NaN();

  Matrix<double,Dynamic,1> v1(4);
  v1 << nan,nan,4,nan;
  EXPECT_EQ(4U, size_of(v1));
  EXPECT_TRUE(check_consistent_size(4U, function, v1, name1, &result));
  EXPECT_THROW(check_consistent_size(2U, function, v1, name1, &result), std::domain_error);
}
