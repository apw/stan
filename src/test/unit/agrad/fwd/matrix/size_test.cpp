#include <stan/math/matrix/size.hpp>
#include <stan/agrad/fwd/fvar.hpp>
#include <stan/agrad/rev/var.hpp>
#include <gtest/gtest.h>

TEST(AgradFwdMatrixSize,fvar_double) {
  using std::vector;
  using Eigen::Matrix;
  using Eigen::Dynamic;
  using stan::math::size;
  using stan::agrad::fvar;

  vector<fvar<double> > y(6);
  EXPECT_EQ(6,size(y));

  vector<Matrix<fvar<double> ,Dynamic,Dynamic> > z(7);
  EXPECT_EQ(7,size(z));

  vector<Matrix<fvar<double> ,Dynamic,1> > a(8);
  EXPECT_EQ(8,size(a));

  vector<Matrix<fvar<double> ,1,Dynamic> > b(9);
  EXPECT_EQ(9,size(b));

  vector<vector<fvar<double> > > c(10);
  EXPECT_EQ(10,size(c));

  vector<vector<fvar<double> > > ci(10);
  EXPECT_EQ(10,size(ci));

  vector<vector<Matrix<fvar<double> ,Dynamic,Dynamic> > > d(11);
  EXPECT_EQ(11,size(d));

  vector<vector<Matrix<fvar<double> ,1,Dynamic> > > e(12);
  EXPECT_EQ(12,size(e));

  vector<vector<Matrix<fvar<double> ,Dynamic,1> > > f(13);
  EXPECT_EQ(13,size(f));

  vector<vector<vector<Matrix<fvar<double> ,Dynamic,1> > > > g(14);
  EXPECT_EQ(14,size(g));
}

TEST(AgradFwdMatrixSize,fvar_fvar_double) {
  using std::vector;
  using Eigen::Matrix;
  using Eigen::Dynamic;
  using stan::math::size;
  using stan::agrad::fvar;

  vector<fvar<fvar<double> > > y(6);
  EXPECT_EQ(6,size(y));

  vector<Matrix<fvar<fvar<double> > ,Dynamic,Dynamic> > z(7);
  EXPECT_EQ(7,size(z));

  vector<Matrix<fvar<fvar<double> > ,Dynamic,1> > a(8);
  EXPECT_EQ(8,size(a));

  vector<Matrix<fvar<fvar<double> > ,1,Dynamic> > b(9);
  EXPECT_EQ(9,size(b));

  vector<vector<fvar<fvar<double> > > > c(10);
  EXPECT_EQ(10,size(c));

  vector<vector<fvar<fvar<double> > > > ci(10);
  EXPECT_EQ(10,size(ci));

  vector<vector<Matrix<fvar<fvar<double> > ,Dynamic,Dynamic> > > d(11);
  EXPECT_EQ(11,size(d));

  vector<vector<Matrix<fvar<fvar<double> > ,1,Dynamic> > > e(12);
  EXPECT_EQ(12,size(e));

  vector<vector<Matrix<fvar<fvar<double> > ,Dynamic,1> > > f(13);
  EXPECT_EQ(13,size(f));

  vector<vector<vector<Matrix<fvar<fvar<double> > ,Dynamic,1> > > > g(14);
  EXPECT_EQ(14,size(g));
}

TEST(AgradFwdMatrixSize,fvar_var) {
  using std::vector;
  using Eigen::Matrix;
  using Eigen::Dynamic;
  using stan::math::size;
  using stan::agrad::fvar;
  using stan::agrad::var;

  vector<fvar<var> > y(6);
  EXPECT_EQ(6,size(y));

  vector<Matrix<fvar<var> ,Dynamic,Dynamic> > z(7);
  EXPECT_EQ(7,size(z));

  vector<Matrix<fvar<var> ,Dynamic,1> > a(8);
  EXPECT_EQ(8,size(a));

  vector<Matrix<fvar<var> ,1,Dynamic> > b(9);
  EXPECT_EQ(9,size(b));

  vector<vector<fvar<var> > > c(10);
  EXPECT_EQ(10,size(c));

  vector<vector<fvar<var> > > ci(10);
  EXPECT_EQ(10,size(ci));

  vector<vector<Matrix<fvar<var> ,Dynamic,Dynamic> > > d(11);
  EXPECT_EQ(11,size(d));

  vector<vector<Matrix<fvar<var> ,1,Dynamic> > > e(12);
  EXPECT_EQ(12,size(e));

  vector<vector<Matrix<fvar<var> ,Dynamic,1> > > f(13);
  EXPECT_EQ(13,size(f));

  vector<vector<vector<Matrix<fvar<var> ,Dynamic,1> > > > g(14);
  EXPECT_EQ(14,size(g));
}

TEST(AgradFwdMatrixSize,fvar_fvar_var) {
  using std::vector;
  using Eigen::Matrix;
  using Eigen::Dynamic;
  using stan::math::size;
  using stan::agrad::fvar;
  using stan::agrad::var;

  vector<fvar<fvar<var> > > y(6);
  EXPECT_EQ(6,size(y));

  vector<Matrix<fvar<fvar<var> > ,Dynamic,Dynamic> > z(7);
  EXPECT_EQ(7,size(z));

  vector<Matrix<fvar<fvar<var> > ,Dynamic,1> > a(8);
  EXPECT_EQ(8,size(a));

  vector<Matrix<fvar<fvar<var> > ,1,Dynamic> > b(9);
  EXPECT_EQ(9,size(b));

  vector<vector<fvar<fvar<var> > > > c(10);
  EXPECT_EQ(10,size(c));

  vector<vector<fvar<fvar<var> > > > ci(10);
  EXPECT_EQ(10,size(ci));

  vector<vector<Matrix<fvar<fvar<var> > ,Dynamic,Dynamic> > > d(11);
  EXPECT_EQ(11,size(d));

  vector<vector<Matrix<fvar<fvar<var> > ,1,Dynamic> > > e(12);
  EXPECT_EQ(12,size(e));

  vector<vector<Matrix<fvar<fvar<var> > ,Dynamic,1> > > f(13);
  EXPECT_EQ(13,size(f));

  vector<vector<vector<Matrix<fvar<fvar<var> > ,Dynamic,1> > > > g(14);
  EXPECT_EQ(14,size(g));
}
