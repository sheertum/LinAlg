#include "pch.h"

class MatrixTest : public ::testing::Test {
protected:
	void SetUp() override {
		matrix1 = Matrix{3, 3, {1,1,1,1,1,1,1,1,1}};
		matrix2 = Matrix{ 3, 3, {2,2,2,2,2,2,2,2,2} };
		matrix3 = Matrix{ 3, 3, {1,2,3,4,5,6,7,8,9} };
		matrix4 = Matrix{3, 3, {34,5,76,2,9,1,0,-9,-87}};

		decimalMatrix1 = Matrix{3, 3, { 0.01, 0.002, 0, 0.01, 0.002, 0, 0.01, 0.002, 0 }};
		decimalMatrix2 = Matrix{3, 3, { 0.01, 0.007, 1, 0.01, 0.007, 1, 0.01, 0.007, 1 }};

		negativeDecimalMatrix1 = Matrix{3, 3,{ -0.01, -0.002, 0, -0.01, -0.002, 0, -0.01, -0.002, 0 }};
		negativeDecimalMatrix2 = Matrix{3, 3,{ 0.1,0.007,-1, 0.1,0.007,-1, 0.1,0.007,-1 }};
		
		rowMatrix = Matrix{1, 3, {1,2,3}};
		columnMatrix1 = Matrix{3, 1, {4,5,6}};

	}

	Matrix rowMatrix{1, 3, {0,0,0}};
	Matrix columnMatrix1{3, 1, {0,0,0}};
	Matrix matrix1{3, 3, {0,0,0,0,0,0,0,0,0}};
	Matrix matrix2{ 3, 3, {0,0,0,0,0,0,0,0,0} };
	Matrix matrix3{ 3, 3, {0,0,0,0,0,0,0,0,0} };
	Matrix matrix4{3, 3, {0,0,0,0,0,0,0,0,0}};

	Matrix decimalMatrix1{3, 3, {0,0,0,0,0,0,0,0,0}};
	Matrix decimalMatrix2{3, 3, {0,0,0,0,0,0,0,0,0}};

	Matrix negativeDecimalMatrix1{3, 3, {0,0,0,0,0,0,0,0,0}};
	Matrix negativeDecimalMatrix2{3, 3, {0,0,0,0,0,0,0,0,0}};
};

void compareVector(Matrix expected, Matrix result){
	std::vector<double> expectedData = expected.getData();
	std::vector<double> resultData = result.getData();

	for (int i = 0; i < resultData.size(); ++i) {
   		EXPECT_EQ(round(expectedData[i] * 1000.0) / 1000.0, round(resultData[i] * 1000.0) / 1000.0);
	}
}

/*
* PLUS START
*/
TEST_F(MatrixTest, SimplePlus) {
	Matrix expected(3, 3, {3, 3, 3,
						   3, 3, 3,
						   3, 3, 3, });

	Matrix result = matrix1 + matrix2;
	compareVector(expected, result);
}

TEST_F(MatrixTest, DecimalPlus) {
	Matrix expected(3, 3, { 0.02,   0.009,   1,
							0.02,   0.009,   1,
							0.02,   0.009,   1 });

	Matrix result = decimalMatrix1 + decimalMatrix2;

	compareVector(expected, result);
}

TEST_F(MatrixTest, PlusWithNegativeNumbers) {

	Matrix expected(3, 3, { 0.09,   0.005,   -1,
						  	0.09,   0.005,   -1,
						  	0.09,   0.005,   -1});

	Matrix result = negativeDecimalMatrix1 + negativeDecimalMatrix2;

	compareVector(expected, result);
}

/*
* PLUS END
*/

/*
* MINUS START
*/
TEST_F(MatrixTest, SimpleMinus) {
	Matrix expected(3, 3, { -1, -1, -1,
						    -1, -1, -1,
						    -1, -1, -1 });

	Matrix result = matrix1 - matrix2;

	compareVector(expected, result);
}

TEST_F(MatrixTest, MinusWithNegativeNumbers) {
	Matrix expected(3, 3, { -0.11, -0.009, 1,
						    -0.11, -0.009, 1,
							-0.11, -0.009, 1});
									  
	Matrix result = negativeDecimalMatrix1 - negativeDecimalMatrix2;

	compareVector(expected, result);
}

TEST_F(MatrixTest, DecimalMinus) {
	Matrix expected(3, 3, { 0, -0.005, -1,
						 	0, -0.005, -1,
							0, -0.005, -1});

	Matrix result = decimalMatrix1 - decimalMatrix2;

	compareVector(expected, result);
}

/*
* MINUS END
*/

/*
* MULTIPLY START
*/
TEST_F(MatrixTest, ComplexMultiply) {

	Matrix expected(3, 3, { {38, -4,-183,146,11,-213,254,26,-243} });

	Matrix result = matrix3 * matrix4;
	compareVector(expected, result);
}

TEST_F(MatrixTest, SimpleMultiply) {

	Matrix expected(3, 3, { {6,6,6,6,6,6,6,6,6} });

	Matrix result = matrix1 * matrix2;
	compareVector(expected, result);
}

TEST_F(MatrixTest, RowTimesColumn) {
	Matrix expected{3,3, {{ 4, 5, 6,
							8,10,12,
							12,15,18}}};
	Matrix result = rowMatrix * columnMatrix1;
	
	compareVector(expected, result);
	EXPECT_EQ(result.getRowCount(), 3);
	EXPECT_EQ(result.getColumnCount(), 3);
}


TEST_F(MatrixTest, ColumnTimesRow) {
	Matrix expected{1,1, {{32}}};
	Matrix result = columnMatrix1 * rowMatrix;
	
	EXPECT_EQ(result.getRowCount(), 1);
	EXPECT_EQ(result.getColumnCount(), 1);
	compareVector(expected, result);
}

TEST_F(MatrixTest, 90DegRotateZAxis) {
	Matrix expected{ 3,3, {{-4,-5,-6,1,2,3,7,8,9}} };

	matrix3.zRotate(90);

	compareVector(expected, matrix3);
}

TEST_F(MatrixTest, 60DegRotateZAxis) {
	Matrix expected{ 3,3, {{-2.964,-3.330,-3.696,2.866,4.232,5.598,7,8,9}} };

	matrix3.zRotate(60);

	compareVector(expected, matrix3);
}