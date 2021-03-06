#include <stan/error_handling/scalar/check_less.hpp>
#include <gtest/gtest.h>

using stan::error_handling::check_less;

TEST(ErrorHandling,CheckLess) {
  const char* function = "check_less(%1%)";
  double x = -10.0;
  double lb = 0.0;
  double result;
 
  EXPECT_TRUE(check_less(function, x, lb, "x", &result)) 
    << "check_less should be true with x < lb";
  
  x = 1.0;
  EXPECT_THROW(check_less(function, x, lb, "x", &result), std::domain_error)
    << "check_less should throw an exception with x > lb";

  x = lb;
  EXPECT_THROW(check_less(function, x, lb, "x", &result), std::domain_error)
    << "check_less should throw an exception with x == lb";

  x = -std::numeric_limits<double>::infinity();
  EXPECT_TRUE(check_less(function, x, lb, "x", &result))
    << "check_less should be true with x == -Inf and lb = 0.0";

  x = -10.0;
  lb = -std::numeric_limits<double>::infinity();
  EXPECT_THROW(check_less(function, x, lb, "x", &result), std::domain_error)
    << "check_less should throw an exception with x == -10.0 and lb == -Inf";

  x = -std::numeric_limits<double>::infinity();
  lb = -std::numeric_limits<double>::infinity();
  EXPECT_THROW(check_less(function, x, lb, "x", &result), std::domain_error)
    << "check_less should throw an exception with x == -Inf and lb == -Inf";
}

TEST(ErrorHandling,CheckLess_Matrix) {
  const char* function = "check_less(%1%)";
  double result;
  double x;
  double high;
  Eigen::Matrix<double,Eigen::Dynamic,1> x_vec;
  Eigen::Matrix<double,Eigen::Dynamic,1> high_vec;
  x_vec.resize(3);
  high_vec.resize(3);
  
  
  // x_vec, high
  result = 0;
  x_vec << -5, 0, 5;
  high = 10;
  EXPECT_TRUE(check_less(function, x_vec, high, "x", &result));

  result = 0;
  x_vec << -5, 0, 5;
  high = std::numeric_limits<double>::infinity();
  EXPECT_TRUE(check_less(function, x_vec, high, "x", &result));

  result = 0;
  x_vec << -5, 0, 5;
  high = 5;
  EXPECT_THROW(check_less(function, x_vec, high, "x", &result),
               std::domain_error);
  
  result = 0;
  x_vec << -5, 0, std::numeric_limits<double>::infinity();
  high = 5;
  EXPECT_THROW(check_less(function, x_vec, high, "x", &result),
               std::domain_error);

  result = 0;
  x_vec << -5, 0, std::numeric_limits<double>::infinity();
  high = std::numeric_limits<double>::infinity();
  EXPECT_THROW(check_less(function, x_vec, high, "x", &result),
               std::domain_error);
  
  // x_vec, high_vec
  result = 0;
  x_vec << -5, 0, 5;
  high_vec << 0, 5, 10;
  EXPECT_TRUE(check_less(function, x_vec, high_vec, "x", &result));

  result = 0;
  x_vec << -5, 0, 5;
  high_vec << std::numeric_limits<double>::infinity(), 10, 10;
  EXPECT_TRUE(check_less(function, x_vec, high_vec, "x", &result));

  result = 0;
  x_vec << -5, 0, 5;
  high_vec << 10, 10, 5;
  EXPECT_THROW(check_less(function, x_vec, high_vec, "x", &result),
               std::domain_error);
  
  result = 0;
  x_vec << -5, 0, std::numeric_limits<double>::infinity();
  high_vec << 10, 10, 10;
  EXPECT_THROW(check_less(function, x_vec, high_vec, "x", &result), 
               std::domain_error);

  result = 0;
  x_vec << -5, 0, std::numeric_limits<double>::infinity();
  high_vec << 10, 10, std::numeric_limits<double>::infinity();
  EXPECT_THROW(check_less(function, x_vec, high_vec, "x", &result),
               std::domain_error);

  
  // x, high_vec
  result = 0;
  x = -100;
  high_vec << 0, 5, 10;
  EXPECT_TRUE(check_less(function, x, high_vec, "x", &result));

  result = 0;
  x = 10;
  high_vec << 100, 200, std::numeric_limits<double>::infinity();
  EXPECT_TRUE(check_less(function, x, high_vec, "x", &result));

  result = 0;
  x = 5;
  high_vec << 100, 200, 5;
  EXPECT_THROW(check_less(function, x, high_vec, "x", &result),
               std::domain_error);
  
  result = 0;
  x = std::numeric_limits<double>::infinity();
  high_vec << 10, 20, 30;
  EXPECT_THROW(check_less(function, x, high_vec, "x", &result), 
               std::domain_error);

  result = 0;
  x = std::numeric_limits<double>::infinity();
  high_vec << std::numeric_limits<double>::infinity(), 
    std::numeric_limits<double>::infinity(), 
    std::numeric_limits<double>::infinity();
  EXPECT_THROW(check_less(function, x, high_vec, "x", &result),
               std::domain_error);
}


TEST(ErrorHandling,CheckLess_Matrix_one_indexed_message) {
  const char* function = "check_less(%1%)";
  double result;
  double x;
  double high;
  Eigen::Matrix<double,Eigen::Dynamic,1> x_vec;
  Eigen::Matrix<double,Eigen::Dynamic,1> high_vec;
  x_vec.resize(3);
  high_vec.resize(3);
  std::string message;

  // x_vec, high
  result = 0;
  x_vec << -5, 0, 5;
  high = 5;

  try {
    check_less(function, x_vec, high, "x", &result);
    FAIL() << "should have thrown";
  } catch (std::domain_error& e) {
    message = e.what();
  } catch (...) {
    FAIL() << "threw the wrong error";
  }

  EXPECT_NE(std::string::npos, message.find("[3]"))
    << message;

  // x_vec, high_vec
  result = 0;
  x_vec << -5, 5, 0;
  high_vec << 10, 5, 10;

  try {
    check_less(function, x_vec, high_vec, "x", &result);
    FAIL() << "should have thrown";
  } catch (std::domain_error& e) {
    message = e.what();
  } catch (...) {
    FAIL() << "threw the wrong error";
  }

  EXPECT_NE(std::string::npos, message.find("[2]"))
    << message;


  // x, high_vec
  result = 0;
  x = 30;
  high_vec << 10, 20, 30;

  try {
    check_less(function, x, high_vec, "x", &result);
    FAIL() << "should have thrown";
  } catch (std::domain_error& e) {
    message = e.what();
  } catch (...) {
    FAIL() << "threw the wrong error";
  }

  EXPECT_EQ(std::string::npos, message.find("["))
    << "no index provided" << std::endl
    << message;
}

TEST(ErrorHandling,CheckGreaterOrEqual_nan) {
  const char* function = "check_less(%1%)";
  double x = 10.0;
  double lb = 0.0;
  double result;
  double nan = std::numeric_limits<double>::quiet_NaN();

  EXPECT_THROW(check_less(function, nan, lb, "x", &result),
               std::domain_error);
  EXPECT_THROW(check_less(function, x, nan, "x", &result),
               std::domain_error);
  EXPECT_THROW(check_less(function, nan, nan, "x", &result),
               std::domain_error);


  Eigen::Matrix<double,Eigen::Dynamic,1> x_vec(3);
  Eigen::Matrix<double,Eigen::Dynamic,1> low_vec(3);

  // x_vec, low_vec
  x_vec   << -1, 0, 1;
  low_vec << -2, -1, 0;
  EXPECT_THROW(check_less(function, x_vec, nan, "x", &result),
               std::domain_error);

  for (int i = 0; i < x_vec.size(); i++) {
    x_vec   << -1, 0, 1;
    x_vec(i) = nan;
    EXPECT_THROW(check_less(function, x_vec, low_vec, "x", &result),
                 std::domain_error);
  }

  x_vec   << -1, 0, 1;
  for (int i = 0; i < low_vec.size(); i++) {
    low_vec   << -1, 0, 1;
    low_vec(i) = nan;
    EXPECT_THROW(check_less(function, x_vec, low_vec, "x", &result),
                 std::domain_error);
  }

  for (int i = 0; i < x_vec.size(); i++) {
    x_vec   << -1, 0, 1;
    low_vec << -2, -1, 0;
    x_vec(i) = nan;
    for (int j = 0; j < low_vec.size(); j++) {
      low_vec(i) = nan;
      EXPECT_THROW(check_less(function, x_vec, low_vec, "x", &result),
                   std::domain_error);
    }
  }
}
