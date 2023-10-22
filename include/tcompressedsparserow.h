#pragma once
#include "tmatrix.h"
#include <vector>
#include <iostream>
template <typename T>
class TCompressedSparseRow
{
public:
	operator TDynamicMatrix<T>() const;
	TCompressedSparseRow(size_t size);
	TCompressedSparseRow(const TDynamicMatrix<T>& matrix);
	~TCompressedSparseRow();
	//compare
	bool operator== (const TCompressedSparseRow& CSR) const noexcept;
	bool operator!= (const TCompressedSparseRow& CSR) const noexcept;
	//matrix to matrix operations
	TCompressedSparseRow operator+ (const TCompressedSparseRow& CSR) const;
	TCompressedSparseRow operator* (const TCompressedSparseRow& CSR) const;
	TCompressedSparseRow operator- (const TCompressedSparseRow& CSR) const;

	//matrix operations
	TCompressedSparseRow operator-() const noexcept;
	friend std::ostream& operator<< (std::ostream& stream, const TCompressedSparseRow& CSR) 
	{
		stream << CSR.values << std::endl << CSR.columns << std::endl << CSR.rows;
		return stream;
	}
	TCompressedSparseRow transpose() const noexcept;
	const T& get(size_t row, size_t column) const;
	void set(const T& element, size_t row, size_t column);
	
	//matrix to vector operations
	//TCompressedSparseRow<T> operator+ (const TDynamicVector<T>& vector) const;
	TDynamicVector<T> operator* (const TDynamicVector<T>& vector) const;
	//TDynamicVector<T> operator* (const TDynamicVector<T>& vector) const;
	//TCompressedSparseRow<T> operator- (const TDynamicVector<T>& vector) const;

private:
	size_t size;
	std::vector<T> values;
	std::vector<size_t> columns;
	std::vector<size_t> rows;
};

template<typename T>
inline TCompressedSparseRow<T>::operator TDynamicMatrix<T>() const
{
	TDynamicMatrix<T> matrix(size);
	for (size_t i = 1; i < rows.size(); i++)
	{
		for (size_t j = rows[i-1]; j < rows[i]; j++)
		{
			matrix[i-1][columns[j]] = values[j];
			//matrix.at(i - 1).at(columns[j]) = values[j];
		}
	}
	return matrix;
}
template <typename T>
TCompressedSparseRow<T>::TCompressedSparseRow(size_t _size = 0) : values(), columns(), size(_size)
{
	rows = std::vector<size_t>(2 * _size, 0);
}
template<typename T>
inline TCompressedSparseRow<T>::TCompressedSparseRow(const TDynamicMatrix<T>& matrix)
{
	size = matrix.size();
	for (size_t i = 0; i < matrix.size(); i++)
	{
		bool is_start = true;
		for (size_t j = 0; j < matrix[i].size(); j++)
		{
			if (matrix[i][j] != 0) {
				if (is_start)
				{
					rows.push_back(values.size());
					is_start = false;
				}
				values.push_back(matrix[i][j]);
				columns.push_back(j);
			}
		}
		if (is_start) {
			rows.push_back(values.size());
		}
	}
	rows.push_back(values.size());
}
template <typename T>
TCompressedSparseRow<T>::~TCompressedSparseRow()
{
}
template<typename T>
inline bool TCompressedSparseRow<T>::operator==(const TCompressedSparseRow& CSR) const noexcept
{
	if (size != CSR.size) return false;
	if (values.size() != CSR.values.size()) return false;
	for (size_t i = 0; i < values.size(); i++)
	{
		if (values[i] != CSR.values[i])
			return false;
	}
	if (rows.size() != CSR.rows.size()) return false;
	for (size_t i = 0; i < rows.size(); i++)
	{
		if (rows[i] != CSR.rows[i])
			return false;
	}
	if (columns.size() != CSR.columns.size()) return false;
	for (size_t i = 0; i < columns.size(); i++)
	{
		if (columns[i] != CSR.columns[i])
			return false;
	}
	return true;
}
template<typename T>
inline bool TCompressedSparseRow<T>::operator!=(const TCompressedSparseRow& CSR) const noexcept
{
	return !(*this == CSR)
}
template <typename T>
std::ostream& operator<< (std::ostream& stream, const std::vector<T>& vector)
{
	for (size_t i = 0; i < vector.size(); i++)
	{
		stream << std::setw(3) << vector[i];
	}
	//stream << CSR.values << std::endl << CSR.columns << std::endl << CSR.rows;
	return stream;
}
template <typename T>
TCompressedSparseRow<T> TCompressedSparseRow<T>::transpose() const noexcept
{
	TCompressedSparseRow CSR_transpose(size);
	CSR_transpose.rows.clear();
	for (size_t i = 0; i < columns.size(); i++)
	{
		bool is_first = true;
		for (size_t j = 1; j < rows.size(); j++)
		{
			for (size_t k = rows[j - 1]; k < rows[j]; k++)
			{
				
				if (columns[k] == i) {
					CSR_transpose.values.push_back(values[k]);
					CSR_transpose.columns.push_back(j - 1);
					if (is_first) {
						is_first = false;
						CSR_transpose.rows.push_back(CSR_transpose.values.size() - 1);
					}
					//std::cout << std::endl << (CSR_transpose) << std::endl << std::endl;
				}
			}
		}
		if (is_first) {
			CSR_transpose.rows.push_back(CSR_transpose.values.size());
		}

	}
	//CSR_transpose.rows.push_back(values.size());
	return CSR_transpose;
}
template<typename T>
inline const T& TCompressedSparseRow<T>::get(size_t row, size_t column) const
{
	if (column >= size && row >= size) throw std::out_of_range("you can not get out of range element");
	for (size_t i = rows[row]; i < rows[row+1]; i++)
	{
		if (columns[i] == column)
			return values[i];
	}
	return (T)0;
}
template<typename T>
inline void TCompressedSparseRow<T>::set(const T& element, size_t row, size_t column)
{
	if (column >= size && row >= size) throw std::out_of_range("you can not get out of range element");
	for (size_t i = rows[row]; i < rows[row + 1]; i++)
	{
		if (columns[i] == column) {
			if (element != 0) 
			{
				values[i] = element;
			}
			else
			{
				values.erase(values.begin() + i);
				columns.erase(columns.begin() + i);
				for (size_t j = rows[row] + 1; j < rows.size(); j++)
				{
					rows[j]--;
				}
			}
			return;
		}
	}
	values.insert(values.begin() + rows[row], element);
	columns.insert(columns.begin() + rows[row], column);
	for (size_t j = rows[row] + 1; j < rows.size(); j++)
	{
		rows[j]++;
	}
	return;
}
//template<typename T>
//TCompressedSparseRow<T> TCompressedSparseRow<T>::operator+(const TDynamicVector<T>& vector) const
//{
//	TCompressedSparseRow<T> result(size);
//	result.rows.clear();
//	size_t k = 0;
//	for (size_t i = 0; i < size; i++)
//	{
//		size_t j = 0;
//		for (; j < size && k < columns.size(); j++)
//		{
//			if (columns[k] == j) {
//				result.values.push_back(values[j] + vector[i]);
//				k++;
//			}
//			else
//			{
//				result.values.push_back(vector[i]);
//			}
//		}
//		while (j < size)
//		{
//			result.values.push_back(vector[i]);
//			j++;
//		}
//	}
//	return result;
//}
template<typename T>
TDynamicVector<T> TCompressedSparseRow<T>::operator* (const TDynamicVector<T>& vector) const
{
	TDynamicVector<T> result(size);
	size_t row = 1;
	T sum = {};
	for (size_t i = 0; i < values.size();)
	{
		sum += values[i] * vector[columns[i]];
		i++;
		if (row < size && rows[row] == i) {
			result[row-1] = sum;
			sum = {};
			row++;
		}
	}
	result[row] = sum;
	return result;
}
//template<typename T>
//inline TCompressedSparseRow<T> TCompressedSparseRow<T>::operator-(const TDynamicVector<T>& vector) const
//{
//	return TDynamicVector<T>();
//}
template <typename T>
TCompressedSparseRow<T> TCompressedSparseRow<T>::operator+ (const TCompressedSparseRow& CSR) const
{
	if (size != CSR.size) throw std::invalid_argument("sizes of matrix should be equal");
	TCompressedSparseRow result(size);
	result.rows.clear();
	size_t this_row_num = 0;
	size_t CSR_row_num = 0;
	size_t k = 0;
	size_t j = 0;
	bool is_next_line_this = false;
	bool is_next_line_CSR = false;
	result.rows.push_back(0);
	while (k < values.size() && j < CSR.values.size()) 
	{
		if (this_row_num == CSR_row_num) 
		{
			if (columns[k] < CSR.columns[j]) 
			{
				result.values.push_back(values[k]);
				result.columns.push_back(columns[k]);
				k++;
			}
			else if(columns[k] > CSR.columns[j]) 
			{
				result.values.push_back(CSR.values[j]);
				result.columns.push_back(CSR.columns[j]);
				j++;
			}
			else {
				T sum = values[k] + CSR.values[j];
	/*			if (sum != 0) {*/
					result.values.push_back(sum);
					result.columns.push_back(columns[k]);
					j++;
					k++;
				//}
			}
		}
		else
		{
			if (this_row_num < CSR_row_num) 
			{
				result.values.push_back(values[k]);
				result.columns.push_back(columns[k]);
				k++;
			}
			else
			{
				result.values.push_back(CSR.values[j]);
				result.columns.push_back(CSR.columns[j]);
				j++;
			}
		}
		while (this_row_num + 1 < size && rows[this_row_num + 1] == k) {
			is_next_line_this = true;
			this_row_num++;
		}
		while (CSR_row_num + 1 < size && CSR.rows[CSR_row_num + 1] == j) {
			CSR_row_num++;
			is_next_line_CSR = true;
		}
		if (is_next_line_this && is_next_line_CSR) {
			result.rows.push_back(result.values.size());
			is_next_line_CSR = false;
			is_next_line_this = false;
		}
	}
	if ((is_next_line_this || is_next_line_CSR)) {
		result.rows.push_back(result.values.size());
	}
	while (k < values.size()) {
		result.values.push_back(values[k]);
		result.columns.push_back(columns[k]);
		k++;
	}
	while (j < CSR.values.size())
	{
		result.values.push_back(CSR.values[j]); 
		result.columns.push_back(CSR.columns[j]);
		j++;
	}
	result.rows.push_back(result.values.size());
	return result;
}

template<typename T>
inline TCompressedSparseRow<T> TCompressedSparseRow<T>::operator*(const TCompressedSparseRow<T>& CSR) const
{
	if (size != CSR.size) throw std::invalid_argument("sizes of matrix should be equal");
	const TCompressedSparseRow<T> CSR_transpose = CSR.transpose();
	TCompressedSparseRow<T> result(size);
	result.rows.clear();
	result.rows.push_back(0);
	for (size_t j = 1; j < rows.size(); j++) {
		for (size_t i = 1; i < CSR_transpose.rows.size(); i++)
		{
			{
				T sum = {};
				size_t t = CSR_transpose.rows[i - 1];
				size_t k = rows[j-1];
				for (; k < rows[j] && t < CSR_transpose.rows[i]; )
				{
					if (columns[k] < CSR_transpose.columns[t])
					{
						k++;
					}
					else if (columns[k] > CSR_transpose.columns[t])
					{
						t++;
					}
					else
					{
						sum += values[k] * CSR_transpose.values[t];
						k++;
						t++;
					}
				}
				if (sum != (T)0) {
					result.values.push_back(sum);
					result.columns.push_back(i - 1);
				}
			}
		}
		result.rows.push_back(result.values.size());
	}
	return result;
}

template<typename T>
inline TCompressedSparseRow<T> TCompressedSparseRow<T>::operator-(const TCompressedSparseRow& CSR) const
{
	return *this + (-CSR);
}

template<typename T>
inline TCompressedSparseRow<T> TCompressedSparseRow<T>::operator-() const noexcept
{
	TCompressedSparseRow<T> result(*this);
	for (size_t i = 0; i < result.values.size(); i++)
	{
		result.values[i] *= -1;
	}
	return result;
}
