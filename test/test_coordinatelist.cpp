#include <iostream>
#include <gtest.h>
#include "tcoordinatelist.h"
TEST(TCoordinateList, can_init_by_TDynamicMatrix) {
	TDynamicMatrix<int> matrix(10);
	for (size_t i = 0; i < 5; i++)
	{
		matrix[i][i] = i;
	}
	ASSERT_NO_THROW(TCoordinateList<int> CSR(matrix));
}
TEST(TCoordinateList, can_convert_TCoordinateList_to_TDynamicMatrix) {
	TDynamicMatrix<int> matrix(4);
	for (size_t i = 0; i < 4; i++)
	{
		matrix[i][i] = i - 2;
	}
	matrix[0][1] = 5;
	matrix[3][2] = 6;
	TCoordinateList<int> CSR(matrix);
	ASSERT_NO_THROW(TDynamicMatrix<int>(CSR));
}