#include <gtest/gtest.h>
#include <stan/agrad/fwd/matrix/typedefs.hpp>
#include <stan/agrad/fwd/fvar.hpp>
#include <stan/agrad/rev/var.hpp>
#include <stan/math/matrix/fill.hpp>

using stan::agrad::fvar;
using stan::agrad::var;

TEST(AgradFwdMatrixFill, fd) {
  using stan::math::fill;
  using std::vector;
  using Eigen::Matrix;
  using Eigen::Dynamic;

  fvar<double>  x;
  fvar<double>  y = 10;
  fill(x,y);
  EXPECT_FLOAT_EQ(10.0, x.val_);

  std::vector<fvar<double> > z(2);
  fvar<double>  a = 15;
  fill(z,a);
  EXPECT_FLOAT_EQ(15.0, z[0].val_);
  EXPECT_FLOAT_EQ(15.0, z[1].val_);
  EXPECT_EQ(2U,z.size());

  Matrix<fvar<double> ,Dynamic,Dynamic> m(2,3);
  fill(m,fvar<double> (12));
  for (int i = 0; i < 2; ++i)
    for (int j = 0; j < 3; ++j)
      EXPECT_FLOAT_EQ(12.0, m(i,j).val_);
  
  Matrix<fvar<double> ,Dynamic,1> rv(3);
  fill(rv,fvar<double> (13));
  for (int i = 0; i < 3; ++i)
    EXPECT_FLOAT_EQ(13.0, rv(i).val_);

  Matrix<fvar<double> ,1,Dynamic> v(4);
  fill(v,fvar<double> (22));
  for (int i = 0; i < 4; ++i)
    EXPECT_FLOAT_EQ(22.0, v(i).val_);

  vector<vector<fvar<double> > > d(3,vector<fvar<double> >(2));
  fill(d,fvar<double> (54));
  for (size_t i = 0; i < 3; ++i)
    for (size_t j = 0; j < 2; ++j)
      EXPECT_FLOAT_EQ(54, d[i][j].val_);
}
TEST(AgradFwdMatrixFill, fd2) {
  using Eigen::Matrix;
  using Eigen::Dynamic;
  using stan::math::fill;
  Matrix<fvar<double> ,Dynamic,1> y(3);
  fill(y,3.0);
  EXPECT_EQ(3,y.size());
  EXPECT_FLOAT_EQ(3.0,y[0].val_);
}

TEST(AgradFwdMatrixFill, fv) {
  using stan::math::fill;
  using std::vector;
  using Eigen::Matrix;
  using Eigen::Dynamic;

  fvar<var>  x;
  fvar<var>  y = 10;
  fill(x,y);
  EXPECT_FLOAT_EQ(10.0, x.val_.val());

  std::vector<fvar<var> > z(2);
  fvar<var>  a = 15;
  fill(z,a);
  EXPECT_FLOAT_EQ(15.0, z[0].val_.val());
  EXPECT_FLOAT_EQ(15.0, z[1].val_.val());
  EXPECT_EQ(2U,z.size());

  Matrix<fvar<var> ,Dynamic,Dynamic> m(2,3);
  fill(m,fvar<var> (12));
  for (int i = 0; i < 2; ++i)
    for (int j = 0; j < 3; ++j)
      EXPECT_FLOAT_EQ(12.0, m(i,j).val_.val());
  
  Matrix<fvar<var> ,Dynamic,1> rv(3);
  fill(rv,fvar<var> (13));
  for (int i = 0; i < 3; ++i)
    EXPECT_FLOAT_EQ(13.0, rv(i).val_.val());

  Matrix<fvar<var> ,1,Dynamic> v(4);
  fill(v,fvar<var> (22));
  for (int i = 0; i < 4; ++i)
    EXPECT_FLOAT_EQ(22.0, v(i).val_.val());

  vector<vector<fvar<var> > > d(3,vector<fvar<var> >(2));
  fill(d,fvar<var> (54));
  for (size_t i = 0; i < 3; ++i)
    for (size_t j = 0; j < 2; ++j)
      EXPECT_FLOAT_EQ(54, d[i][j].val_.val());
}
TEST(AgradFwdMatrixFill, fv2) {
  using Eigen::Matrix;
  using Eigen::Dynamic;
  using stan::math::fill;
  Matrix<fvar<var> ,Dynamic,1> y(3);
  fill(y,3.0);
  EXPECT_EQ(3,y.size());
  EXPECT_FLOAT_EQ(3.0,y[0].val_.val());
}

TEST(AgradFwdMatrixFill, ffd) {
  using stan::math::fill;
  using std::vector;
  using Eigen::Matrix;
  using Eigen::Dynamic;

  fvar<fvar<double> >  x;
  fvar<fvar<double> >  y = 10;
  fill(x,y);
  EXPECT_FLOAT_EQ(10.0, x.val_.val_);

  std::vector<fvar<fvar<double> > > z(2);
  fvar<fvar<double> >  a = 15;
  fill(z,a);
  EXPECT_FLOAT_EQ(15.0, z[0].val_.val_);
  EXPECT_FLOAT_EQ(15.0, z[1].val_.val_);
  EXPECT_EQ(2U,z.size());

  Matrix<fvar<fvar<double> > ,Dynamic,Dynamic> m(2,3);
  fill(m,fvar<fvar<double> > (12));
  for (int i = 0; i < 2; ++i)
    for (int j = 0; j < 3; ++j)
      EXPECT_FLOAT_EQ(12.0, m(i,j).val_.val_);
  
  Matrix<fvar<fvar<double> > ,Dynamic,1> rv(3);
  fill(rv,fvar<fvar<double> > (13));
  for (int i = 0; i < 3; ++i)
    EXPECT_FLOAT_EQ(13.0, rv(i).val_.val_);

  Matrix<fvar<fvar<double> > ,1,Dynamic> v(4);
  fill(v,fvar<fvar<double> > (22));
  for (int i = 0; i < 4; ++i)
    EXPECT_FLOAT_EQ(22.0, v(i).val_.val_);

  vector<vector<fvar<fvar<double> > > > d(3,vector<fvar<fvar<double> > >(2));
  fill(d,fvar<fvar<double> > (54));
  for (size_t i = 0; i < 3; ++i)
    for (size_t j = 0; j < 2; ++j)
      EXPECT_FLOAT_EQ(54, d[i][j].val_.val_);
}
TEST(AgradFwdMatrixFill, ffd2) {
  using Eigen::Matrix;
  using Eigen::Dynamic;
  using stan::math::fill;
  Matrix<fvar<fvar<double> > ,Dynamic,1> y(3);
  fill(y,3.0);
  EXPECT_EQ(3,y.size());
  EXPECT_FLOAT_EQ(3.0,y[0].val_.val_);
}

TEST(AgradFwdMatrixFill, ffv) {
  using stan::math::fill;
  using std::vector;
  using Eigen::Matrix;
  using Eigen::Dynamic;

  fvar<fvar<var> >  x;
  fvar<fvar<var> >  y = 10;
  fill(x,y);
  EXPECT_FLOAT_EQ(10.0, x.val_.val_.val());

  std::vector<fvar<fvar<var> > > z(2);
  fvar<fvar<var> >  a = 15;
  fill(z,a);
  EXPECT_FLOAT_EQ(15.0, z[0].val_.val_.val());
  EXPECT_FLOAT_EQ(15.0, z[1].val_.val_.val());
  EXPECT_EQ(2U,z.size());

  Matrix<fvar<fvar<var> > ,Dynamic,Dynamic> m(2,3);
  fill(m,fvar<fvar<var> > (12));
  for (int i = 0; i < 2; ++i)
    for (int j = 0; j < 3; ++j)
      EXPECT_FLOAT_EQ(12.0, m(i,j).val_.val_.val());
  
  Matrix<fvar<fvar<var> > ,Dynamic,1> rv(3);
  fill(rv,fvar<fvar<var> > (13));
  for (int i = 0; i < 3; ++i)
    EXPECT_FLOAT_EQ(13.0, rv(i).val_.val_.val());

  Matrix<fvar<fvar<var> > ,1,Dynamic> v(4);
  fill(v,fvar<fvar<var> > (22));
  for (int i = 0; i < 4; ++i)
    EXPECT_FLOAT_EQ(22.0, v(i).val_.val_.val());

  vector<vector<fvar<fvar<var> > > > d(3,vector<fvar<fvar<var> > >(2));
  fill(d,fvar<fvar<var> > (54));
  for (size_t i = 0; i < 3; ++i)
    for (size_t j = 0; j < 2; ++j)
      EXPECT_FLOAT_EQ(54, d[i][j].val_.val_.val());
}
TEST(AgradFwdMatrixFill, ffv2) {
  using Eigen::Matrix;
  using Eigen::Dynamic;
  using stan::math::fill;
  Matrix<fvar<fvar<var> > ,Dynamic,1> y(3);
  fill(y,3.0);
  EXPECT_EQ(3,y.size());
  EXPECT_FLOAT_EQ(3.0,y[0].val_.val_.val());
}
