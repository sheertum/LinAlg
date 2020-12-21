#include "pch.h"

class BoundingBoxTest : public ::testing::Test {
protected:
	void SetUp() override {
		box1 = BoundingBox{{ 0, 0, 0,
				0,1,1,
				1,1,0}};
		box2 = BoundingBox{{ 1.1, 1.1, 1.1,
							1.1,2.1,2.1,
							2.1,2.1,1.1}};
		box3 = BoundingBox{ { 1, 1, 1,
							1,2,2,
							2,2,1} };
		box4 = BoundingBox{{ 0.5, 0.5, 0.5,
							0.5,1.5,1.5,
							1.5,1.5,0.5}};
		box5 = BoundingBox{ { 0.2, 0.2, 0.2,
				0.2,0.8,0.8,
				0.8,0.8,0.2} };
	}
	BoundingBox box1;
	BoundingBox box2;
	BoundingBox box3;
	BoundingBox box4;
	BoundingBox box5;
};

TEST_F(BoundingBoxTest, NotTouchingBoxes) {
	bool expected = false;
	bool result = box1.isInside(box2);

	EXPECT_EQ(expected, result);
}

TEST_F(BoundingBoxTest, TouchingBoxes) {
	bool expected = true;
	bool result = box1.isInside(box3);

	EXPECT_EQ(expected, result);
}

TEST_F(BoundingBoxTest, CollidingBoxes) {
	bool expected = true;
	bool result = box1.isInside(box4);

	EXPECT_EQ(expected, result);
}

TEST_F(BoundingBoxTest, BoxWithinABox) {
	bool expected = true;
	bool result = box1.isInside(box5);

	EXPECT_EQ(expected, result);
}

TEST_F(BoundingBoxTest, BoxWithinABox) {
	bool expected = true;
	bool result = box5.isInside(box1);

	EXPECT_EQ(expected, result);
}