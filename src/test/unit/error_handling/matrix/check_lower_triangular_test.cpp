#include <stan/error_handling/matrix/check_lower_triangular.hpp>
#include <gtest/gtest.h>

TEST(ErrorHandlingMatrix, checkLowerTriangular) {
  using stan::error_handling::check_lower_triangular;
  Eigen::Matrix<double,Eigen::Dynamic,Eigen::Dynamic> y;
  double result;
  
  y.resize(1,1);
  y << 1;
  EXPECT_TRUE(check_lower_triangular("checkLowerTriangular(%1%)", y, "y",
                                        &result));

  y.resize(1,2);
  y << 1, 0;
  EXPECT_TRUE(check_lower_triangular("checkLowerTriangular(%1%)", y, "y", 
                                        &result));

  y(0,1) = 1;
  EXPECT_THROW(check_lower_triangular("checkLowerTriangular(%1%)", y, "y", 
                                         &result), 
               std::domain_error);
  
  

  y.resize(2,2);
  y << 1, 0, 2, 3;
  EXPECT_TRUE(check_lower_triangular("checkLowerTriangular(%1%)", y, "y", 
                                        &result));

  y << 1, 2, 3, 4;
  EXPECT_THROW(check_lower_triangular("checkLowerTriangular(%1%)", y, "y", 
                                         &result), 
               std::domain_error);

  y.resize(3,2);
  y << 1, 0,
    2, 3,
    4, 5;
  EXPECT_TRUE(check_lower_triangular("checkLowerTriangular(%1%)", y, "y", 
                                        &result));
  
  y(0,1) = 1.5;
  EXPECT_THROW(check_lower_triangular("checkLowerTriangular(%1%)", y, "y", 
                                         &result),
               std::domain_error);
  
  y.resize(2,3);
  y << 
    1, 0, 0,
    4, 5, 0;
  EXPECT_TRUE(check_lower_triangular("checkLowerTriangular(%1%)", y, "y", 
                                        &result));
  y(0,2) = 3;
}


TEST(ErrorHandlingMatrix, checkLowerTriangular_one_indexed_message) {
  using stan::error_handling::check_lower_triangular;
  Eigen::Matrix<double,Eigen::Dynamic,Eigen::Dynamic> y;
  double result;
  std::string message;

  y.resize(2,3);
  y << 
    1, 0, 3,
    4, 5, 0;
  try {
    check_lower_triangular("checkLowerTriangular(%1%)", y, "y", &result);
    FAIL() << "should have thrown";
  } catch (std::domain_error& e) {
    message = e.what();
  } catch (...) {
    FAIL() << "threw the wrong error";
  }

  EXPECT_NE(std::string::npos, message.find("[1,3]"))
    << message;
}

TEST(ErrorHandlingMatrix, checkLowerTriangular_nan) {
  using stan::error_handling::check_lower_triangular;
  Eigen::Matrix<double,Eigen::Dynamic,Eigen::Dynamic> y;
  double result;
    double nan = std::numeric_limits<double>::quiet_NaN();

  y.resize(1,1);
  y << nan;
  EXPECT_TRUE(check_lower_triangular("checkLowerTriangular(%1%)", y, "y",
                                        &result));

  y.resize(1,2);
  y << nan, 0;
  EXPECT_TRUE(check_lower_triangular("checkLowerTriangular(%1%)", y, "y", 
                                        &result));

  y(0,1) = nan;
  EXPECT_THROW(check_lower_triangular("checkLowerTriangular(%1%)", y, "y", 
                                         &result), 
               std::domain_error);
  
  

  y.resize(2,2);
  y << nan, 0, nan, nan;
  EXPECT_TRUE(check_lower_triangular("checkLowerTriangular(%1%)", y, "y", 
                                        &result));

  y << 1, nan, nan, 4;
  EXPECT_THROW(check_lower_triangular("checkLowerTriangular(%1%)", y, "y", 
                                         &result), 
               std::domain_error);

  y.resize(3,2);
  y << nan, 0,
    2, nan,
    4, 5;
  EXPECT_TRUE(check_lower_triangular("checkLowerTriangular(%1%)", y, "y", 
                                        &result));
  
  y(0,1) = nan;
  EXPECT_THROW(check_lower_triangular("checkLowerTriangular(%1%)", y, "y", 
                                         &result),
               std::domain_error);
  
  y.resize(2,3);
  y << 
    nan, 0, 0,
    4, nan, 0;
  EXPECT_TRUE(check_lower_triangular("checkLowerTriangular(%1%)", y, "y", 
                                        &result));

  y(0,2) = nan;
  EXPECT_THROW(check_lower_triangular("checkLowerTriangular(%1%)", y, "y", 
                                         &result),
               std::domain_error);
}
