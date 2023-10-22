#include <iostream>
#include <gtest.h>
#include "tcompressedsparserow.h"

TEST(TCompressedSparseRow, can_init_by_TDynamicMatrix) {
	TDynamicMatrix<int> matrix(10);
	for (size_t i = 0; i < 5; i++)
	{
		matrix[i][i] = i;
	}
	ASSERT_NO_THROW(TCompressedSparseRow<int> CSR(matrix));

}
TEST(TCompressedSparseRow, can_convert_TCompressedSparseRow_to_TDynamicMatrix) {
	TDynamicMatrix<int> matrix(4);
	for (size_t i = 0; i < 4; i++)
	{
		matrix[i][i] = i -2;
	}
	matrix[0][1] = 5;
	matrix[3][2] = 6;
	ASSERT_NO_THROW(TCompressedSparseRow<int> CSR2(matrix));
}
TEST(TCompressedSparseRow, is_convert_matrix_equal_to_origin) {
	TDynamicMatrix<int> matrix(4);
	for (size_t i = 0; i < 4; i++)
	{
		matrix[i][i] = i - 2;
	}
	matrix[0][1] = 5;
	matrix[3][2] = 6;
	TCompressedSparseRow<int> CSR(matrix);
	TDynamicMatrix<int> matrix2(CSR);
	ASSERT_EQ(matrix, matrix2);
}
TEST(TCompressedSparseRow, can_transpose_matrix) {
	TDynamicMatrix<int> matrix(4);
	for (size_t i = 0; i < 4; i++)
	{
		matrix[i][i] = i - 2;
	}
	matrix[0][1] = 5;
	matrix[3][2] = 6;
	TCompressedSparseRow<int> CSR(matrix);
	ASSERT_NO_THROW(CSR.transpose());
}
TEST(TCompressedSparseRow, is_transpose_matrix_equal_to_origin) {
	TDynamicMatrix<int> matrix(4);
	for (size_t i = 0; i < 4; i++)
	{
		matrix[i][i] = i - 2;
	}
	matrix[0][1] = 5;
	matrix[3][2] = 6;
	TCompressedSparseRow<int> CSR(matrix);
	//std::cout << std::endl << matrix << std::endl << std::endl << CSR;
	TCompressedSparseRow<int> CSR_transpose = CSR.transpose();
	//std::cout << std::endl << std::endl << CSR_transpose << std::endl << std::endl << TDynamicMatrix<int>(CSR_transpose);
	//std::cout << std::endl << std::endl << CSR_transpose.transpose() << std::endl << std::endl << TDynamicMatrix<int>(CSR_transpose.transpose());
	TCompressedSparseRow<int> CSR2 = CSR.transpose().transpose();
	ASSERT_EQ(CSR, CSR2);
}
TEST(TCompressedSparseRow, can_multiply_matrix) {
	TDynamicMatrix<int> matrix(4);
	for (size_t i = 0; i < 4; i++)
	{
		matrix[i][i] = i - 2;
	}
	matrix[0][1] = 5;
	matrix[3][2] = 6;

	TDynamicMatrix<int> matrix2(4);
	for (size_t i = 0; i < 4; i++)
	{
		matrix2[i][i] = i - 3;
	}
	matrix2[0][1] = 5;
	matrix2[3][2] = 6;
	TCompressedSparseRow<int> CSR(matrix);
	TCompressedSparseRow<int> CSR2(matrix2);
	ASSERT_NO_THROW(CSR * CSR2);
}
TEST(TCompressedSparseRow, is_multiply_matrix_equal_to_result) {
	TDynamicMatrix<int> matrix(4);
	for (size_t i = 0; i < 4; i++)
	{
		matrix[i][i] = i - 2;
	}
	matrix[0][1] = 5;
	matrix[3][2] = 6;

	TDynamicMatrix<int> matrix2(4);
	for (size_t i = 0; i < 4; i++)
	{
		matrix2[i][i] = i - 3;
	}
	matrix2[0][1] = 5;
	matrix2[3][2] = 6;
	TCompressedSparseRow<int> CSR(matrix);
	TCompressedSparseRow<int> CSR2(matrix2);
	TCompressedSparseRow<int> CSR3 = CSR * CSR2;
	TDynamicMatrix<int> convertedMatrix(CSR3);
	TDynamicMatrix<int> multiplyedMatrix = matrix * matrix2;
	ASSERT_EQ(convertedMatrix, multiplyedMatrix);
}
TEST(TCompressedSparseRow, can_sum_TCompressedSparseRow_to_TDynamicMatrix) {
	TDynamicMatrix<int> matrix(4);
	for (size_t i = 0; i < 4; i++)
	{
		matrix[i][i] = i - 2;
	}
	matrix[0][1] = 5;
	matrix[3][2] = 6;

	TDynamicMatrix<int> matrix2(4);
	for (size_t i = 0; i < 4; i++)
	{
		matrix2[i][i] = i - 3;
	}
	TCompressedSparseRow<int> CSR(matrix);
	TCompressedSparseRow<int> CSR2(matrix2);
	TCompressedSparseRow<int> CSR3 = CSR + CSR2;
	//std::cout << matrix << std::endl << std::endl << matrix2 << std::endl;
	TDynamicMatrix<int> sum = matrix + matrix2;
	//std::cout << std::endl << sum << std::endl << std::endl << CSR3 << std::endl;

	TDynamicMatrix<int> newMatrix(CSR3);
	//std::cout << newMatrix;
	ASSERT_NO_THROW(TCompressedSparseRow<int> CSR2(matrix));
}
TEST(TCompressedSparseRow, can_sub_TCompressedSparseRow_to_TDynamicMatrix) {
	TDynamicMatrix<int> matrix(4);
	for (size_t i = 0; i < 4; i++)
	{
		matrix[i][i] = i - 2;
	}
	matrix[0][1] = 5;
	matrix[3][2] = 6;

	TDynamicMatrix<int> matrix2(4);
	for (size_t i = 0; i < 4; i++)
	{
		matrix2[i][i] = i - 3;
	}
	TCompressedSparseRow<int> CSR(matrix);
	TCompressedSparseRow<int> CSR2(matrix2);
	TCompressedSparseRow<int> CSR3 = CSR - CSR2;
	//std::cout << matrix << std::endl << std::endl << matrix2 << std::endl;
	TDynamicMatrix<int> sum = matrix - matrix2;
	//std::cout << std::endl << sum << std::endl << std::endl << CSR3 << std::endl;

	TDynamicMatrix<int> newMatrix(CSR3);
	//std::cout << newMatrix;
	ASSERT_NO_THROW(TCompressedSparseRow<int> CSR2(matrix));
}
TEST(TCompressedSparseRow, can_get_element_from_matrix) {
	TDynamicMatrix<int> matrix(4);
	for (size_t i = 0; i < 4; i++)
	{
		matrix[i][i] = i - 2;
	}
	matrix[0][1] = 5;
	matrix[3][2] = 6;
	TCompressedSparseRow<int> CSR(matrix);
	ASSERT_EQ(CSR.get(0, 1), 5);
}
TEST(TCompressedSparseRow, can_set_and_get_element_from_matrix) {
	TCompressedSparseRow<int> CSR(4);
	CSR.set(5, 0, 2);
	ASSERT_EQ(CSR.get(0, 2), 5);
}
TEST(TCompressedSparseRow, can_set_and_get_zero_element_from_matrix) {
	TCompressedSparseRow<int> CSR(4);
	CSR.set(5, 0, 2);
	CSR.set(0, 0, 2);
	ASSERT_EQ(CSR.get(0, 2), 0);
}
TEST(TCompressedSparseRow, can_multiple_matrix_and_vector) {
	TDynamicMatrix<int> matrix(4);
	for (size_t i = 0; i < 4; i++)
	{
		matrix[i][i] = i - 2;
	}
	matrix[0][1] = 5;
	matrix[3][2] = 6;
	TCompressedSparseRow<int> CSR(matrix);
	int* v = new int [4] {1, 2, 3, 4};
	TDynamicVector<int> vector(v, 4);
	ASSERT_NO_THROW(CSR * vector);
}
TEST(TCompressedSparseRow, is_multiplication_matrix_and_vector_right) {
	TDynamicMatrix<int> matrix(4);
	for (size_t i = 0; i < 4; i++)
	{
		matrix[i][i] = i - 2;
	}
	matrix[0][1] = 5;
	matrix[3][2] = 6;
	//std::cout << matrix;
	TCompressedSparseRow<int> CSR(matrix);
	int* v = new int [4] {1, 2, 3, 4};
	TDynamicVector<int> vector(v, 4);
	delete[] v;
	int* res = new int [4] {8, -2, 0, 22};
	TDynamicVector<int> result(res, 4);
	delete[] res;
	ASSERT_EQ(CSR * vector, result);
}
//TEST(TCompressedSparseRow, can_sum_matrix_and_vector) {
//	TDynamicMatrix<int> matrix(4);
//	for (size_t i = 0; i < 4; i++)
//	{
//		matrix[i][i] = i - 2;
//	}
//	matrix[0][1] = 5;
//	matrix[3][2] = 6;
//	//std::cout << matrix;
//	TCompressedSparseRow<int> CSR(matrix);
//	int* v = new int [4] {1, 2, 3, 4};
//	TDynamicVector<int> vector(v, 4);
//	delete[] v;
//	ASSERT_NO_THROW(CSR + vector);
//}
//TEST(TCompressedSparseRow, is_the_addition_matrix_and_vector_correct) {
//	TDynamicMatrix<int> matrix(4);
//	for (size_t i = 0; i < 4; i++)
//	{
//		matrix[i][i] = i - 2;
//	}
//	matrix[0][1] = 5;
//	matrix[3][2] = 6;
//	std::cout << matrix;
//	TCompressedSparseRow<int> CSR(matrix);
//	int* v = new int [4] {1, 2, 3, 4};
//	TDynamicVector<int> vector(v, 4);
//	std::cout << std::endl << std::endl << vector;
//	delete[] v;
//	TDynamicMatrix<int> answer = matrix + vector;
//	std::cout << std::endl << std::endl << answer;
//	TCompressedSparseRow<int> answer2 (answer);
//	TCompressedSparseRow<int> result = CSR + vector;
//	ASSERT_EQ(result, answer2);
//}