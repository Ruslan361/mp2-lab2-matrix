#pragma once
#include "tmatrix.h"
#include <iomanip>
template <typename T>
struct TContainer
{
	T element;
	size_t row;
	size_t column;
	friend std::ostream& operator<< (std::ostream& stream, const TCoordinateList<T>& list) {
		stream << std::setw(5) << list.element << std::setw(5) << list.row << std::setw(5) << list.column;
		return stream;
	}

};
template <typename T>
class TCoordinateList 
{
	TDynamicVector<TContainer<T>> elements;
public:
	TCoordinateList() : elements(), rows(), columns() {}
	explicit TCoordinateList(size_t size) 
	{
		elements = TDynamicVector<TContainer<T>>(size);
	}
	TCoordinateList(const TDynamicMatrix<T>& matrix);
	friend std::ostream& operator<< (std::ostream& stream, const TCoordinateList& list)
	{
		size_t size = list.elements.size()
		for (size_t i = 0; i < size; i++)
		{
			std::cout << list.elements[i] << '\n';
			return stream;
		}
	}
};
template <typename T>
TCoordinateList<T>::TCoordinateList<T>(const TDynamicMatrix<T>& matrix)
{
	size_t size = matrix.size();
	size_t count_of_not_zero_elements = 0;
	for (size_t i = 0; i < size; i++)
	{
		for (size_t j = 0; j < size; j++)
		{
			if (matrix[i][j] != 0) {
				count_of_not_zero_elements++;
			}
		}
	}
	elements = TDynamicVector<TContainer<T>>(count_of_not_zero_elements);
	size_t k = 0;
	for (size_t i = 0; i < size; i++)
	{
		for (size_t j = 0; j < size; j++)
		{
			if (matrix[i][j] != 0) {
				elements[k].element = matrix[i][j];
				elements[k].row = i;
				elements[k].column = j;
				k++;
			}
		}
	}
}