#include "tmatrix.h"
#include <iostream>
#include <gtest.h>

TEST(TDynamicMatrix, can_create_matrix_with_positive_length)
{
  ASSERT_NO_THROW(TDynamicMatrix<int> m(5));
}

TEST(TDynamicMatrix, cant_create_too_large_matrix)
{
  ASSERT_ANY_THROW(TDynamicMatrix<int> m(MAX_MATRIX_SIZE + 1));
}

TEST(TDynamicMatrix, throws_when_create_matrix_with_negative_length)
{
  ASSERT_ANY_THROW(TDynamicMatrix<int> m(-5));
}

TEST(TDynamicMatrix, can_create_copied_matrix)
{
	TDynamicMatrix<int> m(5);
	ASSERT_NO_THROW(TDynamicMatrix<int> m1(m));
}

TEST(TDynamicMatrix, copied_matrix_is_equal_to_source_one)
{
	int* arr = new int [6] { 1, 2, 4, 5, 6};
	TDynamicVector<int> v(arr, 6);
	delete[] arr;
	TDynamicMatrix<int> m(6);
	for (size_t i = 0; i < 6; i++)
	{
		m[i] = v;
	}
	TDynamicMatrix<int> mCopy(10);
	mCopy = m;
	ASSERT_EQ(mCopy, m);
}

TEST(TDynamicMatrix, copied_matrix_has_its_own_memory)
{
	int* arr = new int [6] { 1, 2, 4, 5, 6};
	TDynamicVector<int> v(arr, 6);
	delete[] arr;
	TDynamicMatrix<int> m(6);
	for (size_t i = 0; i < 6; i++)
	{
		m[i] = v;
	}
	TDynamicMatrix<int> mCopy(10);
	mCopy = m;
	mCopy[0][0] = 10000;
	ASSERT_NE(mCopy, m);
}

TEST(TDynamicMatrix, can_get_size)
{
	TDynamicMatrix<int> m(8);
	ASSERT_EQ(m.size(), 8);
}

TEST(TDynamicMatrix, can_set_and_get_element)
{
	TDynamicMatrix<int> m(8);
	ASSERT_EQ(m[0] = 1234, m[0]);
}

TEST(TDynamicMatrix, throws_when_set_element_with_negative_index)
{
	TDynamicMatrix<int> m(6);
	ASSERT_ANY_THROW(m.at(-10) = 100);
}

TEST(TDynamicMatrix, throws_when_set_element_with_too_large_index)
{
	TDynamicMatrix<int> m(6);
	ASSERT_ANY_THROW(m.at(MAX_MATRIX_SIZE + 1) = 100);
}

TEST(TDynamicMatrix, can_assign_matrix_to_itself)
{
	TDynamicMatrix<int> m(6);
	ASSERT_NO_THROW(m = m);
}

TEST(TDynamicMatrix, can_assign_matrices_of_equal_size)
{
	int* arr = new int [6] { 1, 2, 4, 5, 6};
	TDynamicVector<int> v(arr, 6);
	delete[] arr;
	TDynamicMatrix<int> m(6);
	for (size_t i = 0; i < 6; i++)
	{
		m[i] = v;
	}
	TDynamicMatrix<int> mCopy(6);
	mCopy = m;
	ASSERT_EQ(mCopy, m);
}

TEST(TDynamicMatrix, assign_operator_change_matrix_size)
{
	int* arr = new int [6] { 1, 2, 4, 5, 6};
	TDynamicVector<int> v(arr, 6);
	delete[] arr;
	TDynamicMatrix<int> m(6);
	for (size_t i = 0; i < 6; i++)
	{
		m[i] = v;
	}
	TDynamicMatrix<int> mCopy(500);
	mCopy = m;
	ASSERT_EQ(mCopy.size(), 6);
}

TEST(TDynamicMatrix, can_assign_matrices_of_different_size)
{
	int* arr = new int [6] { 1, 2, 4, 5, 6};
	TDynamicVector<int> v(arr, 6);
	delete[] arr;
	TDynamicMatrix<int> m(6);
	for (size_t i = 0; i < 6; i++)
	{
		m[i] = v;
	}
	TDynamicMatrix<int> mCopy(500);
	mCopy = m;
	ASSERT_EQ(mCopy, m);
}

TEST(TDynamicMatrix, compare_equal_matrices_return_true)
{
	int* arr = new int [6] { 1, 2, 4, 5, 6};
	TDynamicVector<int> v(arr, 6);
	delete[] arr;
	TDynamicMatrix<int> m(6);
	for (size_t i = 0; i < 6; i++)
	{
		m[i] = v;
	}
	TDynamicMatrix<int> mCopy(m);
	ASSERT_EQ(mCopy == m, true);
}

TEST(TDynamicMatrix, compare_matrix_with_itself_return_true)
{
	TDynamicMatrix<int> m(6);
	ASSERT_EQ(m, m);
}

TEST(TDynamicMatrix, matrices_with_different_size_are_not_equal)
{
	TDynamicMatrix<int> m1(6);
	TDynamicMatrix<int> m2(20);
	ASSERT_NE(m1, m2);
}

TEST(TDynamicMatrix, can_add_matrices_with_equal_size)
{
	TDynamicMatrix<int> m1(3);
	TDynamicVector<int> v(3);
	for (size_t i = 0; i < 3; i++)
	{
		v[i] = i;
	}
	for (size_t i = 0; i < 3; i++)
	{
		m1[i] = v;
	}
	m1 = m1 + m1;

	TDynamicVector<int> v2(3);
	for (size_t i = 0; i < 3; i++)
	{
		v2[i] = i * 2;
	}
	TDynamicMatrix<int> m2(3);
	for (size_t i = 0; i < 3; i++)
	{
		m2[i] = v2;
	}
	ASSERT_EQ(m1, m2);
}

TEST(TDynamicMatrix, can_multiply_matrices_with_equal_size)
{
	TDynamicMatrix<int> m1(3);
	TDynamicVector<int> v(3);
	for (size_t i = 0; i < 3; i++)
	{
		v[i] = i;
	}
	for (size_t i = 0; i < 3; i++)
	{
		m1[i] = v;
	}
	m1 = m1 * m1;

	TDynamicVector<int> v2(3);
	for (size_t i = 0; i < 3; i++)
	{
		v2[i] = i * 3;
	}
	TDynamicMatrix<int> m2(3);
	for (size_t i = 0; i < 3; i++)
	{
		m2[i] = v2;
	}
	ASSERT_EQ(m1, m2);
}

TEST(TDynamicMatrix, cant_multiply_matrices_with_equal_size)
{
	TDynamicMatrix<int> m1(3);
	TDynamicMatrix<int> m2(10);
	ASSERT_ANY_THROW(m1 * m2);
}

TEST(TDynamicMatrix, cant_add_matrices_with_not_equal_size)
{
	TDynamicMatrix<int> m1(3);
	TDynamicMatrix<int> m2(6);
	ASSERT_ANY_THROW(m1 + m2);
}

TEST(TDynamicMatrix, can_subtract_matrices_with_equal_size)
{
	TDynamicMatrix<int> m1(3);
	TDynamicVector<int> v(3);
	for (size_t i = 0; i < 3; i++)
	{
		v[i] = i;
	}
	for (size_t i = 0; i < 3; i++)
	{
		m1[i] = v;
	}
	m1 = m1 - m1;

	TDynamicVector<int> v2(3);
	for (size_t i = 0; i < 3; i++)
	{
		v2[i] = 0;
	}
	TDynamicMatrix<int> m2(3);
	for (size_t i = 0; i < 3; i++)
	{
		m2[i] = v2;
	}
	ASSERT_EQ(m1, m2);
}

TEST(TDynamicMatrix, cant_subtract_matrixes_with_not_equal_size)
{
	TDynamicMatrix<int> m1(3);
	TDynamicMatrix<int> m2(6);
	ASSERT_ANY_THROW(m1 - m2);
}

TEST(TDynamicMatrix, can_multiply_matrix_with_scalar)
{
	TDynamicMatrix<int> m1(3);
	TDynamicVector<int> v(3);
	for (size_t i = 0; i < 3; i++)
	{
		v[i] = i;
	}
	for (size_t i = 0; i < 3; i++)
	{
		m1[i] = v;
	}
	TDynamicMatrix<int> m2(3);
	TDynamicVector<int> v2(3);
	for (size_t i = 0; i < 3; i++)
	{
		v2[i] = i * 2;
	}
	for (size_t i = 0; i < 3; i++)
	{
		m2[i] = v2;
	}
	m1 = m1 * 2;
	ASSERT_EQ(m1, m2);
}

TEST(TDynamicMatrix, can_multiply_matrix_with_vector_with_equal_size)
{
	TDynamicMatrix<int> m1(3);
	TDynamicVector<int> v(3);
	for (size_t i = 0; i < 3; i++)
	{
		v[i] = i;
	}
	for (size_t i = 0; i < 3; i++)
	{
		m1[i] = v;
	}
	v = m1 * v;
	TDynamicVector<int> v2(3);
	for (size_t i = 0; i < 3; i++)
	{
		v2[i] = 5;
	}
	ASSERT_EQ(v, v2);
}

TEST(TDynamicMatrix, cant_multiply_matrix_with_vector_not_equal_size)
{
	TDynamicMatrix<int> m1(3);
	TDynamicVector<int> v(10);
	ASSERT_ANY_THROW(m1 * v);
}
TEST(TDynamicMatrix, is_addition_matrix_with_vector_correct)
{
	TDynamicMatrix<int> m1(3);
	TDynamicVector<int> v(3);
	for (size_t i = 0; i < 3; i++)
	{
		v[i] = i;
	}
	for (size_t i = 0; i < 3; i++)
	{
		m1[i] = v;
	}
	//std::cout << std::endl << m1 << std::endl << std::endl;
	TDynamicMatrix<int> m2 = m1 + v;
	TDynamicMatrix<int> answer(3);
	for (size_t i = 0; i < answer.size(); i++)
	{
		for (size_t j = 0; j < answer.size(); j++) {
			answer[i][j] = i + j;
		}
	}
	//std::cout << std::endl << m2 << std::endl << std::endl;
	ASSERT_EQ(m2, answer);
}
