// ННГУ, ИИТММ, Курс "Алгоритмы и структуры данных"
//
// Copyright (c) Сысоев А.В.
//
//
#ifndef __TDynamicMatrix_H__
#define __TDynamicMatrix_H__
#include "tdynamicvector.h"
const int MAX_MATRIX_SIZE = 10000;

// Динамическая матрица - 
// шаблонная матрица на динамической памяти
template<typename T>
class TDynamicMatrix : private TDynamicVector<TDynamicVector<T>>
{
  using TDynamicVector<TDynamicVector<T>>::pMem;
  using TDynamicVector<TDynamicVector<T>>::sz;
public:
    TDynamicMatrix(size_t s = 1);
  TDynamicMatrix(const TDynamicMatrix& matrix) : TDynamicVector<TDynamicVector<T>>(matrix.pMem, matrix.sz) {}
  using TDynamicVector<TDynamicVector<T>>::operator[];
  using TDynamicVector<TDynamicVector<T>>::at;
  using TDynamicVector<TDynamicVector<T>>::size;
  TDynamicMatrix& operator= (TDynamicMatrix& m);
   //сравнение
  bool operator==(const TDynamicMatrix& m) const noexcept;
  bool operator!=(const TDynamicMatrix& m) const noexcept
  {
      return !(*this == m);
  }
  // матрично-скалярные операции
  TDynamicMatrix operator*(const T& val) const;

  // матрично-векторные операции
  TDynamicVector<T> operator*(const TDynamicVector<T>& v) const;
  TDynamicMatrix<T> operator+(const TDynamicVector<T>& v) const;

  // матрично-матричные операции
  TDynamicMatrix operator+(const TDynamicMatrix& m) const;
  TDynamicMatrix operator-(const TDynamicMatrix& m) const;
  TDynamicMatrix operator*(const TDynamicMatrix& m) const;

  //ввод/вывод
  friend std::istream& operator>>(std::istream& istr, TDynamicMatrix& v)
  {
      for (size_t i = 0; i < v.sz; i++)
      {
          istr >> v.pMem[i];
      }
      return istr;
  }
  friend std::ostream& operator<<(std::ostream& ostr, const TDynamicMatrix<T>& v)
  {
      for (size_t i = 0; i < v.sz; i++)
      {
          ostr << v.pMem[i] << std::endl;
      }
      return ostr;
  }
};
template <typename T>
TDynamicMatrix<T>& TDynamicMatrix<T>::operator= (TDynamicMatrix<T>& m)
{
    if (pMem != m.pMem) {
        if (sz != m.sz) {
            TDynamicVector<T>* newPMem = new TDynamicVector<T>[m.sz];
            delete[] pMem;
            pMem = newPMem;
            sz = m.sz;
        }
        std::copy(m.pMem, m.pMem + sz, pMem);
    }
    return *this;
}
template <typename T>
bool TDynamicMatrix<T>::operator==(const TDynamicMatrix<T>& m) const noexcept
{
    if (sz != m.sz) return false;
    for (int i = 0; i < sz; i++) {
        if (pMem[i] != m.pMem[i])
            return false;
    }
    return true;
}
template <typename T>
TDynamicMatrix<T>::TDynamicMatrix<T>(size_t s = 1) : TDynamicVector<TDynamicVector<T>>(s)
{
    if (s > MAX_MATRIX_SIZE) throw std::out_of_range("Matrix`s size must be less than MAX_MATRIX_SIZE");
    for (size_t i = 0; i < sz; i++)
        pMem[i] = TDynamicVector<T>(sz);
}
template <typename T>
TDynamicMatrix<T> TDynamicMatrix<T>::operator+(const TDynamicMatrix<T>& m) const
{
    if (sz != m.sz) throw std::invalid_argument("You can not sum matrix with not equal sizes");
    TDynamicMatrix<T> res(sz);
    for (size_t i = 0; i < sz; i++)
    {
        res[i] = pMem[i] + m.pMem[i];
    }
    return res;
}
template <typename T>
TDynamicMatrix<T> TDynamicMatrix<T>::operator-(const TDynamicMatrix<T>& m) const
{
    if (sz != m.sz) throw std::invalid_argument("You can not sum matrix with not equal sizes");
    TDynamicMatrix<T> res(sz);
    for (size_t i = 0; i < sz; i++)
    {
        res[i] = pMem[i] - m.pMem[i];
    }
    return res;
}
template <typename T>
TDynamicMatrix<T> TDynamicMatrix<T>::operator*(const TDynamicMatrix<T>& m) const
{
    if (sz != m.sz) throw std::invalid_argument("You can not sum matrix with not equal sizes");
    TDynamicMatrix<T> res(sz);
    for (size_t i = 0; i < sz; i++)
    {
        for (size_t j = 0; j < sz; j++)
        {
            T sum = 0;
            for (size_t k = 0; k < sz; k++)
            {
                sum += pMem[i][k] * m.pMem[k][j];
            }
            res[i][j] = sum;
        }
    }
    return res;
}
template <typename T>
TDynamicMatrix<T> TDynamicMatrix<T>::operator*(const T& val) const
{
    TDynamicMatrix<T> res(sz);
    for (size_t i = 0; i < sz; i++)
    {
        res[i] = pMem[i] * val;
    }
    return res;
}
template <typename T>
TDynamicVector<T> TDynamicMatrix<T>::operator*(const TDynamicVector<T>& v) const
{
    if (sz != v.size()) throw std::invalid_argument("You can not multiply matrix and vector with not equal sizes");
    TDynamicVector<T> res(sz);
    for (size_t i = 0; i < sz; i++)
    {
        T sum = 0;
        for (size_t j = 0; j < sz; j++)
        {
            sum += pMem[i][j] * v[j];
        }
        res[i] = sum;
    }
    return res;
}
template<typename T>
TDynamicMatrix<T> TDynamicMatrix<T>::operator+(const TDynamicVector<T>& v) const
{
    if (sz != v.size()) throw std::invalid_argument("You can not sum matrix and vector with not equal sizes");
    TDynamicMatrix<T> result(size());
    for (size_t i = 0; i < result.size(); i++)
    {
        for (size_t j = 0; j < result.pMem[i].size(); j++)
        {
            result.pMem[i][j] = pMem[i][j] + v[i];
        }
    }
    return result;
}
#endif
