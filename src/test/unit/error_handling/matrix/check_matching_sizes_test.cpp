#include <stan/error_handling/matrix/check_matching_sizes.hpp>
#include <gtest/gtest.h>

TEST(ErrorHandlingMatrix, checkMatchingSizesMatrix) {
  Eigen::Matrix<double,Eigen::Dynamic,Eigen::Dynamic> y;
  Eigen::Matrix<double,Eigen::Dynamic,Eigen::Dynamic> x;
  double result;
  
  y.resize(3,3);
  x.resize(3,3);
  EXPECT_TRUE(stan::error_handling::check_matching_sizes("checkMatchingSizes(%1%)",x,"x",
                                             y, "y", &result));
  x.resize(0,0);
  y.resize(0,0);
  EXPECT_TRUE(stan::error_handling::check_matching_sizes("checkMatchingSizes(%1%)",x,"x",
                                             y, "y", &result));

  y.resize(1,2);


  EXPECT_THROW(stan::error_handling::check_matching_sizes("checkMatchingSizes(%1%)",x,"x",
                                               y, "y",&result), 
               std::domain_error);

  x.resize(2,1);
  EXPECT_TRUE(stan::error_handling::check_matching_sizes("checkMatchingSizes(%1%)",x,"x",
                                               y, "y",&result));

  std::vector<double> a;
  std::vector<double> b;
  x.resize(0,0);

  EXPECT_TRUE(stan::error_handling::check_matching_sizes("checkMatchingSizes(%1%)",a,"a",
                                             b, "b", &result));
  EXPECT_TRUE(stan::error_handling::check_matching_sizes("checkMatchingSizes(%1%)",x,"x",
                                               b, "b", &result));
  EXPECT_TRUE(stan::error_handling::check_matching_sizes("checkMatchingSizes(%1%)",a,"a",
                                               x, "x", &result));
  EXPECT_THROW(stan::error_handling::check_matching_sizes("checkMatchingSizes(%1%)",a,"a",
                                                y, "y", &result),
               std::domain_error);


  a.push_back(3.0);
  a.push_back(3.0);

  EXPECT_THROW(stan::error_handling::check_matching_sizes("checkMatchingSizes(%1%)",a,"a",
                                                b, "b", &result),
               std::domain_error);

  b.push_back(3.0);
  b.push_back(3.0);
  x.resize(2,1);

  EXPECT_TRUE(stan::error_handling::check_matching_sizes("checkMatchingSizes(%1%)",a,"a",
                                             b, "b", &result));
  EXPECT_TRUE(stan::error_handling::check_matching_sizes("checkMatchingSizes(%1%)",x,"x",
                                               b, "b", &result));
}

TEST(ErrorHandlingMatrix, checkMatchingSizesMatrix_nan) {
  Eigen::Matrix<double,Eigen::Dynamic,Eigen::Dynamic> y;
  Eigen::Matrix<double,Eigen::Dynamic,Eigen::Dynamic> x;
  double result;
  double nan = std::numeric_limits<double>::quiet_NaN();

  y.resize(3,3);
  x.resize(3,3);
  y << nan, nan, nan,nan, nan, nan,nan, nan, nan;
  x << nan, nan, nan,nan, nan, nan,nan, nan, nan;
  EXPECT_TRUE(stan::error_handling::check_matching_sizes("checkMatchingSizes(%1%)",x,"x",
                                             y, "y", &result));
  x.resize(0,0);
  y.resize(0,0);
  EXPECT_TRUE(stan::error_handling::check_matching_sizes("checkMatchingSizes(%1%)",x,"x",
                                             y, "y", &result));

  y.resize(1,2);
  y << nan, nan;
  EXPECT_THROW(stan::error_handling::check_matching_sizes("checkMatchingSizes(%1%)",x,"x",
                                               y, "y",&result), 
               std::domain_error);

  x.resize(2,1);
  x << nan, nan;
  EXPECT_TRUE(stan::error_handling::check_matching_sizes("checkMatchingSizes(%1%)",x,"x",
                                               y, "y",&result));

  std::vector<double> a;
  std::vector<double> b;
  x.resize(0,0);
  EXPECT_TRUE(stan::error_handling::check_matching_sizes("checkMatchingSizes(%1%)",a,"a",
                                             b, "b", &result));
  EXPECT_TRUE(stan::error_handling::check_matching_sizes("checkMatchingSizes(%1%)",x,"x",
                                               b, "b", &result));
  EXPECT_TRUE(stan::error_handling::check_matching_sizes("checkMatchingSizes(%1%)",a,"a",
                                               x, "x", &result));
  EXPECT_THROW(stan::error_handling::check_matching_sizes("checkMatchingSizes(%1%)",a,"a",
                                                y, "y", &result),
               std::domain_error);


  a.push_back(nan);
  a.push_back(nan);
  EXPECT_THROW(stan::error_handling::check_matching_sizes("checkMatchingSizes(%1%)",a,"a",
                                                b, "b", &result),
               std::domain_error);

  b.push_back(nan);
  b.push_back(nan);
  x.resize(2,1);
  x << nan, nan;
  EXPECT_TRUE(stan::error_handling::check_matching_sizes("checkMatchingSizes(%1%)",a,"a",
                                             b, "b", &result));
  EXPECT_TRUE(stan::error_handling::check_matching_sizes("checkMatchingSizes(%1%)",x,"x",
                                               b, "b", &result));
}

