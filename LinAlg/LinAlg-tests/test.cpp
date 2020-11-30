#include "pch.h"


TEST(VectorTest, ScalarmultiplicationTest) {
	Vector testVector{ {1,0,0} };
	EXPECT_EQ(testVector[0], 1);
}

/*
* PLUS START
*/
TEST(MatrixTest, SimplePlus) {
	
	Matrix matrix1(3, 1, {1, 1, 1});
	Matrix matrix2(1, 3, 
		{1,
		 1, 
		 1});

	Matrix expected(3, 3, {2, 2, 2,
						   2, 2, 2,
						   2, 2, 2, });

	Matrix result = matrix1 + matrix2;

	EXPECT_EQ(result.getData(), expected.getData());
}

TEST(MatrixTest, DecimalPlus) {

	Matrix matrix1(3, 1, { 0.01, 0.002, 0 });
	Matrix matrix2(1, 3,
		{ 0.1,
		 0.007,
		 1 });

	Matrix expected(3, 3, { 0.1100000,   0.1020000,   0.1000000,
							0.0170000,   0.0090000,   0.0070000,
							1.0100000,   1.0020000,   1.0000000 });

	Matrix result = matrix1 + matrix2;

	EXPECT_EQ(result.getData(), expected.getData());
}

TEST(MatrixTest, PlusWithNegativeNumbers) {

	Matrix matrix1(3, 1, { -0.01, -0.002, 0 });
	Matrix matrix2(1, 3,
		{ 0.1,
		 0.007,
		 -1 });

	Matrix expected(3, 3, { 0.0900000,   0.0980000,   0.1000000,
						  - 0.0030000,   0.0050000,   0.0070000,
						  - 1.0100000, - 1.0020000, - 1.0000000 });

	Matrix result = matrix1 + matrix2;

	EXPECT_EQ(result.getData(), expected.getData());
}

/*
* PLUS END
*/

/*
* MINUS START
*/
TEST(MatrixTest, SimpleMinus) {

	Matrix matrix1(3, 1, { 1, 1, 1 });
	Matrix matrix2(1, 3,
		{ 1,
		 1,
		 1 });

	Matrix expected(3, 3, { 0, 0, 0,
						    0, 0, 0,
						    0, 0, 0, });

	Matrix result = matrix1 - matrix2;

	EXPECT_EQ(result.getData(), expected.getData());
}

TEST(MatrixTest, MinusWithNegativeNumbers) {
	Matrix matrix1(3, 1, { -0.01, -0.002, 0 });
	Matrix matrix2(1, 3,
		{ 0.1,
		 0.007,
		 -1 });

	Matrix expected(3, 3, { -0.1100000, - 0.1020000, - 0.1000000,
						   - 0.0170000, - 0.0090000, - 0.0070000,
							 0.9900000,   0.9980000,   1.0000000 });
									  
	Matrix result = matrix1 - matrix2;

	EXPECT_EQ(result.getData(), expected.getData());
}

TEST(MatrixTest, DecimalMinus) {
	Matrix matrix1(3, 1, { 0.01, 0.002, 0 });
	Matrix matrix2(1, 3, { 0.1, 0.007, 1 });

	Matrix expected(3, 3, { -0.0900000, -0.0980000, -0.1000000,
						  0.0030000, -0.0050000, -0.0070000,
						-0.9900000, -0.9980000, -1.0000000 });

	Matrix result = matrix1 - matrix2;

	EXPECT_EQ(result.getData(), expected.getData());
}

/*
* MINUS END
*/

/*
* MULTIPLY START
*/
TEST(MatrixTest, SimpleMinus) {

	Matrix matrix1(3, 1, { 112, 211, 212 });
	Matrix matrix2(1, 3,
		{ 2,
		 0,
		 1 });

	Matrix expected1(1, 1, { 436 });
	Matrix expected2(3, 3, { 224,   422,   424,
							0  ,   0  ,   0	 ,
						112,   211,   212 });

	Matrix result1 = matrix1 * matrix2;
	Matrix result2 = matrix2 * matrix1;

	EXPECT_EQ(result1.getData(), expected1.getData());
	EXPECT_EQ(result2.getData(), expected2.getData());
}

TEST(MatrixTest, MinusWithNegativeNumbers) {
	Matrix matrix1(3, 1, { -0.01, -0.002, 0 });
	Matrix matrix2(1, 3,
		{ 0.1,
		 0.007,
		 -1 });

	Matrix expected1(1, 1, { 436 });
	Matrix expected2(3, 3, { 224,   422,   424,
							0  ,   0  ,   0	 ,
						112,   211,   212 });

	Matrix result1 = matrix1 * matrix2;
	Matrix result2 = matrix2 * matrix1;

	EXPECT_EQ(result1.getData(), expected1.getData());
	EXPECT_EQ(result2.getData(), expected2.getData());
}

TEST(MatrixTest, DecimalMinus) {
	Matrix matrix1(3, 1, { 0.01, 0.002, 0 });
	Matrix matrix2(1, 3, { 0.1, 0.007, 1 });

	Matrix expected1(1, 1, { 436 });
	Matrix expected2(3, 3, { 224,   422,   424,
							0  ,   0  ,   0	 ,
						112,   211,   212 });

	Matrix result1 = matrix1 * matrix2;
	Matrix result2 = matrix2 * matrix1;

	EXPECT_EQ(result1.getData(), expected1.getData());
	EXPECT_EQ(result2.getData(), expected2.getData());
}

/*
* MULTIPLY END
*/