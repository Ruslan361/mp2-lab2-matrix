#include "tdynamicvector.h"

#include <gtest.h>

TEST(TDynamicVector, can_create_vector_with_positive_length)
{
  ASSERT_NO_THROW(TDynamicVector<int> v(5));
}

TEST(TDynamicVector, cant_create_too_large_vector)
{
  ASSERT_ANY_THROW(TDynamicVector<int> v(MAX_VECTOR_SIZE + 1));
}

TEST(TDynamicVector, throws_when_create_vector_with_negative_length)
{
  ASSERT_ANY_THROW(TDynamicVector<int> v(-5));
}

TEST(TDynamicVector, can_create_copied_vector)
{
  TDynamicVector<int> v(10);

  ASSERT_NO_THROW(TDynamicVector<int> v1(v));
}

TEST(TDynamicVector, copied_vector_is_equal_to_source_one)
{
	size_t length = 10;
	int* arr = new int[length];
	for (size_t i = 0; i < length; i++)
	{
		arr[i] = i;
	}
	TDynamicVector<int> source(arr, length);
	delete[] arr;
	TDynamicVector<int> copy(source);
	ASSERT_EQ(source, copy);
}

TEST(TDynamicVector, copied_vector_has_its_own_memory)
{
	size_t length = 10;
	int* arr = new int[length];
	for (size_t i = 0; i < length; i++)
	{
		arr[i] = i * 2;
	}
	TDynamicVector<int> source(arr, length);
	delete[] arr;
	TDynamicVector<int> copy(source);
	copy[0] = 8;
	ASSERT_NE(source, copy);
}

TEST(TDynamicVector, can_get_size)
{
  TDynamicVector<int> v(4);

  EXPECT_EQ(4, v.size());
}

TEST(TDynamicVector, can_set_and_get_element)
{
  TDynamicVector<int> v(4);
  v[0] = 4;

  EXPECT_EQ(4, v[0]);
}

TEST(TDynamicVector, throws_when_set_element_with_negative_index)
{
	TDynamicVector<int> v(10);
	ASSERT_ANY_THROW(v.at(-100) = 5);
}

TEST(TDynamicVector, throws_when_set_element_with_too_large_index)
{
	TDynamicVector<int> v(100);
	ASSERT_ANY_THROW(v.at(MAX_VECTOR_SIZE + 1) = 5);
}

TEST(TDynamicVector, can_assign_vector_to_itself)
{
	TDynamicVector<int> v(100);
	ASSERT_NO_THROW(v = v);
}

TEST(TDynamicVector, can_assign_vectors_of_equal_size)
{
	size_t length = 10;
	TDynamicVector<int> v(length);
	for (size_t i = 0; i < length; i++)
	{
		v[i] = i;
	}
	TDynamicVector<int> v2(length);
	v2 = v;
	ASSERT_EQ(v, v2);
}

TEST(TDynamicVector, assign_operator_change_vector_size)
{
	size_t length1 = 100;
	TDynamicVector<int> v1(length1);
	size_t length2 = 50;
	TDynamicVector<int> v2(length2);
	v2 = v1;
	ASSERT_EQ(v2.size(), length1);
}

TEST(TDynamicVector, can_assign_vectors_of_different_size)
{
	size_t length1 = 100;
	TDynamicVector<int> v1(length1);
	for (size_t i = 0; i < length1; i++)
	{
		v1[i] = i;
	}
	size_t length2 = 50;
	TDynamicVector<int> v2(length2);
	v2 = v1;
	ASSERT_EQ(v1, v2);
}

TEST(TDynamicVector, compare_equal_vectors_return_true)
{
	size_t length1 = 100;
	TDynamicVector<int> v1(length1);
	for (size_t i = 0; i < length1; i++)
	{
		v1[i] = i;
	}
	TDynamicVector<int> v2(v1);
	ASSERT_EQ(v1, v2);
}

TEST(TDynamicVector, compare_vector_with_itself_return_true)
{
	size_t length1 = 100;
	TDynamicVector<int> v1(length1);
	for (size_t i = 0; i < length1; i++)
	{
		v1[i] = i;
	}
	ASSERT_EQ(v1, v1);
}

TEST(TDynamicVector, vectors_with_different_size_are_not_equal)
{
	size_t length1 = 100;
	TDynamicVector<int> v1(length1);
	size_t length2 = 50;
	TDynamicVector<int> v2(length2);
	ASSERT_NE(v1, v2);
}

TEST(TDynamicVector, can_add_scalar_to_vector)
{
	size_t length1 = 100;
	TDynamicVector<int> v1(length1);
	for (size_t i = 0; i < length1; i++)
	{
		v1[i] = i;
	}
	int scalar = 8;

	v1 = v1 + scalar;

	TDynamicVector<int> v2(length1);
	for (size_t i = 0; i < length1; i++)
	{
		v2[i] = i + scalar;
	}
	ASSERT_EQ(v1, v2);
}

TEST(TDynamicVector, can_subtract_scalar_from_vector)
{
	size_t length1 = 100;
	TDynamicVector<int> v1(length1);
	for (size_t i = 0; i < length1; i++)
	{
		v1[i] = i;
	}
	int scalar = 8;

	v1 = v1 - scalar;

	TDynamicVector<int> v2(length1);
	for (size_t i = 0; i < length1; i++)
	{
		v2[i] = i - scalar;
	}
	ASSERT_EQ(v1, v2);
}

TEST(TDynamicVector, can_multiply_scalar_by_vector)
{
	size_t length1 = 100;
	TDynamicVector<int> v1(length1);
	for (size_t i = 0; i < length1; i++)
	{
		v1[i] = i;
	}
	int scalar = 8;

	v1 = v1 * scalar;

	TDynamicVector<int> v2(length1);
	for (size_t i = 0; i < length1; i++)
	{
		v2[i] = i * scalar;
	}
	ASSERT_EQ(v1, v2);
}

TEST(TDynamicVector, can_add_vectors_with_equal_size)
{
	size_t length1 = 100;
	TDynamicVector<int> v1(length1);
	for (size_t i = 0; i < length1; i++)
	{
		v1[i] = i;
	}
	TDynamicVector<int> v2(length1);
	for (size_t i = 0; i < length1; i++)
	{
		v2[i] = i * 2;
	}

	TDynamicVector<int> v3 = v1 + v2;
	TDynamicVector<int> v4(length1);
	for (size_t i = 0; i < length1; i++)
	{
		v4[i] = i + i * 2;
	}
	ASSERT_EQ(v3, v4);
}

TEST(TDynamicVector, cant_add_vectors_with_not_equal_size)
{
	size_t length1 = 10;
	size_t length2 = 20;
	TDynamicVector<int> v1(length1);
	TDynamicVector<int> v2(length2);
	ASSERT_ANY_THROW(v1 + v2);
}

TEST(TDynamicVector, can_subtract_vectors_with_equal_size)
{
	size_t length1 = 100;
	TDynamicVector<int> v1(length1);
	for (size_t i = 0; i < length1; i++)
	{
		v1[i] = i;
	}
	TDynamicVector<int> v2(length1);
	for (size_t i = 0; i < length1; i++)
	{
		v2[i] = i * 2;
	}

	TDynamicVector<int> v3 = v1 - v2;
	TDynamicVector<int> v4(length1);
	for (size_t i = 0; i < length1; i++)
	{
		v4[i] = i - i * 2;
	}
	ASSERT_EQ(v3, v4);
}

TEST(TDynamicVector, cant_subtract_vectors_with_not_equal_size)
{
	size_t length1 = 10;
	size_t length2 = 20;
	TDynamicVector<int> v1(length1);
	TDynamicVector<int> v2(length2);
	ASSERT_ANY_THROW(v1 - v2);
}

TEST(TDynamicVector, can_multiply_vectors_with_equal_size)
{
	size_t length1 = 100;
	TDynamicVector<int> v1(length1);
	for (size_t i = 0; i < length1; i++)
	{
		v1[i] = i;
	}
	TDynamicVector<int> v2(length1);
	for (size_t i = 0; i < length1; i++)
	{
		v2[i] = i * 2;
	}

	int currentRes = v1 * v2;
	TDynamicVector<int> v4(length1);
	int actualRes = 0;
	for (size_t i = 0; i < length1; i++)
	{
		actualRes += i * i * 2;
	}
	ASSERT_EQ(currentRes, actualRes);
}

TEST(TDynamicVector, cant_multiply_vectors_with_not_equal_size)
{
	size_t length1 = 10;
	size_t length2 = 20;
	TDynamicVector<int> v1(length1);
	TDynamicVector<int> v2(length2);
	ASSERT_ANY_THROW(v1 * v2);
}

