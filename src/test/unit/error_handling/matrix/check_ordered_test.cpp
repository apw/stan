#include <stan/error_handling/matrix/check_ordered.hpp>
#include <gtest/gtest.h>

using stan::error_handling::check_ordered;

TEST(ErrorHandlingMatrix, checkOrdered) {
  double result;
  Eigen::Matrix<double, Eigen::Dynamic, 1> y;
  y.resize(3);

  y << 0, 1, 2;
  EXPECT_TRUE(check_ordered("check_ordered(%1%)", y, "y", &result));

  y << 0, 10, std::numeric_limits<double>::infinity();
  EXPECT_TRUE(check_ordered("check_ordered(%1%)", y, "y", &result));

  y << -10, 10, std::numeric_limits<double>::infinity();
  EXPECT_TRUE(check_ordered("check_ordered(%1%)", y, "y", &result));

  y << -std::numeric_limits<double>::infinity(), 10, std::numeric_limits<double>::infinity();
  EXPECT_TRUE(check_ordered("check_ordered(%1%)", y, "y", &result));

  y << 0, 0, 0;
  EXPECT_THROW(check_ordered("check_ordered(%1%)", y, "y", &result),
               std::domain_error);

  y << 0, std::numeric_limits<double>::infinity(), std::numeric_limits<double>::infinity();
  EXPECT_THROW(check_ordered("check_ordered(%1%)", y, "y", &result),
               std::domain_error);


  y << -1, 3, 2;
  EXPECT_THROW(check_ordered("check_ordered(%1%)", y, "y", &result),
               std::domain_error);

  std::vector<double> y_;
  y_.push_back(0.0);
  y_.push_back(1.0);
  y_.push_back(2.0);
  EXPECT_TRUE(check_ordered("check_ordered(%1%)", y_, "y", &result));

  y_[2] = std::numeric_limits<double>::infinity();
  EXPECT_TRUE(check_ordered("check_ordered(%1%)", y_, "y", &result));

  y_[0] = -10.0;
  EXPECT_TRUE(check_ordered("check_ordered(%1%)", y_, "y", &result));

  y_[0] = -std::numeric_limits<double>::infinity();
  EXPECT_TRUE(check_ordered("check_ordered(%1%)", y_, "y", &result));

  y_[0] = 0.0;
  y_[1] = 0.0;
  y_[2] = 0.0;
  EXPECT_THROW(check_ordered("check_ordered(%1%)", y_, "y", &result),
               std::domain_error);

  y_[1] = std::numeric_limits<double>::infinity();
  y_[2] = std::numeric_limits<double>::infinity();
  EXPECT_THROW(check_ordered("check_ordered(%1%)", y_, "y", &result),
               std::domain_error);
}

TEST(ErrorHandlingMatrix, checkOrdered_one_indexed_message) {
  std::string message;
  double result;
  Eigen::Matrix<double, Eigen::Dynamic, 1> y;
  y.resize(3);
  
  y << 0, 5, 1;
  try {
    check_ordered("check_ordered(%1%)", y, "y", &result);
    FAIL() << "should have thrown";
  } catch (std::domain_error& e) {
    message = e.what();
  } catch (...) {
    FAIL() << "threw the wrong error";
  }

  EXPECT_NE(std::string::npos, message.find("element at 3"))
    << message;
}

TEST(ErrorHandlingMatrix, checkOrdered_nan) {
  double result;
  Eigen::Matrix<double, Eigen::Dynamic, 1> y;
  std::vector<double> y_;
  double nan = std::numeric_limits<double>::quiet_NaN();
  y.resize(3);

  y << 0, 1, 2;
  y_.push_back(0.0);
  y_.push_back(1.0);
  y_.push_back(2.0);
  for (int i = 0; i < y.size(); i++) {
    y[i] = nan;
    y_[i] = nan;
    EXPECT_THROW(check_ordered("check_ordered(%1%)", y, "y", &result),
                 std::domain_error);
    EXPECT_THROW(check_ordered("check_ordered(%1%)", y_, "y", &result),
                 std::domain_error);
    y[i] = i;
    y_[i] = i;
  }
  for (int i = 0; i < y.size(); i++) {
    y << 0, 10, std::numeric_limits<double>::infinity();
    y_[0] = 0.0;
    y_[1] = 10.0;
    y_[2] = std::numeric_limits<double>::infinity();
    y[i] = nan;
    y_[i] = nan;
    EXPECT_THROW(check_ordered("check_ordered(%1%)", y, "y", &result),
                 std::domain_error);
    EXPECT_THROW(check_ordered("check_ordered(%1%)", y_, "y", &result),
                 std::domain_error);
  }
}
