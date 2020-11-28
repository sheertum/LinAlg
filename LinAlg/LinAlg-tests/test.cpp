#include "pch.h"


TEST(VectorTest, ScalarmultiplicationTest) {
	Vector testVector{ {1,0,0} };
	EXPECT_EQ(testVector[0], 1);
}