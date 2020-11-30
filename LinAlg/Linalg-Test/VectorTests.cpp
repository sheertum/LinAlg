#include "pch.h"
#include "../LinAlg/Headers/Matrix.h"
#include "../LinAlg/Headers/Vector.h"

class VectorTest : public ::testing::Test {
 protected:
  void SetUp() override {
     V1 = Vector{{1,2,3}};
     twosVector = Vector{{2,2,2}};
     negative = Vector{{-1,-2,-3}};
     oneFiveSeven= Vector{{1,5,7}};
  }

  Vector V1{{0,0,0}};
  Vector twosVector{{0,0,0}};
  Vector oneFiveSeven{{0,0,0}};
  Vector negative{{0,0,0}};
  Vector result{{0,0,0}};

  // void TearDown() override {}
};

TEST_F(VectorTest, Addition) {
    result = V1 + twosVector;
    EXPECT_EQ(result[0], 3);
    EXPECT_EQ(result[1], 4);
    EXPECT_EQ(result[2], 5);
}

TEST_F(VectorTest, AdditionOfNegatives) {
    result = V1 + negative;
    EXPECT_EQ(result[0], 0);
    EXPECT_EQ(result[1], 0);
    EXPECT_EQ(result[2], 0);
}

TEST_F(VectorTest, Subtract) {
    result = V1 - twosVector;
    EXPECT_EQ(result[0], 1-2);
    EXPECT_EQ(result[1], 2-2);
    EXPECT_EQ(result[2], 3-2);
}

TEST_F(VectorTest, SubtractNegative) {
    result = V1 - negative;
    EXPECT_EQ(result[0], 1+1);
    EXPECT_EQ(result[1], 2+2);
    EXPECT_EQ(result[2], 3+3);
}

TEST_F(VectorTest, ScalarMultiply) {
    double factor = 3;
    result = V1 * factor;
    EXPECT_EQ(result[0], 3);
    EXPECT_EQ(result[1], 6);
    EXPECT_EQ(result[2], 9);
}

TEST_F(VectorTest, ScalarMultiplyNegative) {
    double factor = -2;
    result = V1 * factor;
    EXPECT_EQ(result[0], -2);
    EXPECT_EQ(result[1], -4);
    EXPECT_EQ(result[2], -6);
}

TEST_F(VectorTest, InProductNegative) {
    double inproductResult = V1 * negative;
    EXPECT_EQ(inproductResult, (-1 -4 -9));
}

TEST_F(VectorTest, InProductTwos) {
    double inproductResult = V1 * twosVector;
    EXPECT_EQ(inproductResult, 1*2+2*2+3*2);
}

TEST_F(VectorTest, InProduct157) {
    double inproductResult = V1 * oneFiveSeven;
    EXPECT_EQ(inproductResult, 32);
}

TEST_F(VectorTest, CrossProduct1) {
    result = V1.crossProduct(oneFiveSeven);
    EXPECT_EQ(result[0], -1);
    EXPECT_EQ(result[1], -4);
    EXPECT_EQ(result[2], 3);
}

TEST_F(VectorTest, CrossProduct2) {
    V1 = Vector {{-1, -2 ,3}};
    Vector V2 = Vector {{4, 0 ,-8}};
    result = V1.crossProduct(V2);
    EXPECT_EQ(result[0], 16);
    EXPECT_EQ(result[1], 4);
    EXPECT_EQ(result[2], 8);
}

TEST_F(VectorTest, Length1) {
    V1 = Vector {{1,0,-3}};
    double length = V1.getLength();
    EXPECT_EQ(length, sqrt(10));
}