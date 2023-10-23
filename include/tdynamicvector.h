// ННГУ, ИИТММ, Курс "Алгоритмы и структуры данных"
//
// Copyright (c) Сысоев А.В.
//
//

#ifndef __TDynamicVector_H__
#define __TDynamicVector_H__

#include <iostream>
#include <cassert>
#include <algorithm>
#include <iomanip>
//using namespace std;

const int MAX_VECTOR_SIZE = 100000000;


// Динамический вектор - 
// шаблонный вектор на динамической памяти
template<typename T>
class TDynamicVector
{
protected:
  size_t sz;
  T* pMem;
public:
  TDynamicVector(size_t size = 1);
  TDynamicVector(T* arr, size_t s);
  TDynamicVector(const TDynamicVector& v);
  TDynamicVector(TDynamicVector&& v) noexcept
  {
      sz = v.sz;
      pMem = v.pMem;
      v.pMem = nullptr;
  }
  ~TDynamicVector()
  {
      delete[] pMem;
  }
  TDynamicVector& operator=(const TDynamicVector& v);
  
  TDynamicVector& operator=(TDynamicVector&& v) noexcept
  {
      std::swap(sz, v.sz);
      std::swap(pMem, v.pMem);
      return *this;
  }

  size_t size() const noexcept { return sz; }

  // индексация
  T& operator[](size_t ind)
  {
      return pMem[ind];
  }
  const T& operator[](size_t ind) const
  {
      return pMem[ind];
  }
  // индексация с контролем
  T& at(size_t ind)
  {
      if (ind >= sz) throw std::out_of_range("You can not set/read value from vector in this position");
      return pMem[ind];
  }
  const T& at(size_t ind) const
  {
      if (ind >= sz) throw throw std::out_of_range("You can not set/read value from vector in this position");
      return pMem[ind];
  }
  // сравнение
  bool operator==(const TDynamicVector& v) const noexcept;
  bool operator!=(const TDynamicVector& v) const noexcept
  {
      return !(*this == v);
  }
  // скалярные операции
  TDynamicVector operator+(T val) const;
  TDynamicVector operator-(T val) const;
  TDynamicVector operator*(T val) const;

  // векторные операции
  TDynamicVector operator+(const TDynamicVector& v) const;
  TDynamicVector operator-(const TDynamicVector& v) const;
  T operator*(const TDynamicVector& v) const; //noexcept(noexcept(T()));

  friend void swap(TDynamicVector& lhs, TDynamicVector& rhs) noexcept
  {
    std::swap(lhs.sz, rhs.sz);
    std::swap(lhs.pMem, rhs.pMem);
  }

  // ввод/вывод
  friend std::istream& operator>>(std::istream& istr, TDynamicVector& v)
  {
    for (size_t i = 0; i < v.sz; i++)
      istr >> v.pMem[i]; // требуется оператор>> для типа T
    return istr;
  }
  friend std::ostream& operator<<(std::ostream& ostr, const TDynamicVector& v)
  {
    for (size_t i = 0; i < v.sz; i++)
      ostr << std::setw(5)<< v.pMem[i]; // требуется оператор<< для типа T
    return ostr;
  } 
};
template <typename T>
TDynamicVector<T>& TDynamicVector<T>::operator=(const TDynamicVector<T>& v)
{
    if (pMem != v.pMem) {
        if (sz != v.sz) {
            T* newPMem = new T[v.sz];
            delete[] pMem;
            pMem = newPMem;
            sz = v.sz;
        }
        std::copy(v.pMem, v.pMem + sz, pMem);
    }
    return *this;
}
template <typename T>
bool TDynamicVector<T>::operator==(const TDynamicVector<T>& v) const noexcept
{
    if (sz != v.sz) return false;
    for (size_t i = 0; i < sz; i++)
    {
        if (pMem[i] != v.pMem[i])
            return false;
    }
    return true;
}
template <typename T>
TDynamicVector<T>::TDynamicVector<T>(size_t size = 1) : sz(size)
{
    //sz = size;
    if (sz == 0)
        throw std::out_of_range("Vector size should be greater than zero");
    if (sz > MAX_VECTOR_SIZE)
        throw std::out_of_range("Vector size should be less than MAX_VECTOR_SIZE");
    pMem = new T[sz]();// {}; // У типа T д.б. констуктор по умолчанию
}
template <typename T>
TDynamicVector<T>::TDynamicVector<T>(T* arr, size_t s) : sz(s)
{
    assert(arr != nullptr && "TDynamicVector ctor requires non-nullptr arg");
    pMem = new T[sz];
    std::copy(arr, arr + sz, pMem);
}
template <typename T>
TDynamicVector<T>::TDynamicVector<T>(const TDynamicVector<T>& v)
{
    sz = v.sz;
    pMem = new T[sz];
    std::copy(v.pMem, v.pMem + sz, pMem);
}
template <typename T>
TDynamicVector<T> TDynamicVector<T>::operator+(T val) const
{
    TDynamicVector<T> res(sz);
    for (size_t i = 0; i < sz; i++)
    {
        res.pMem[i] = pMem[i] + val;
    }
    return res;
}
template <typename T>
TDynamicVector<T> TDynamicVector<T>::operator-(T val) const
{
    TDynamicVector<T> res(sz);
    for (size_t i = 0; i < sz; i++)
    {
        res.pMem[i] = pMem[i] - val;
    }
    return res;
}
template <typename T>
TDynamicVector<T> TDynamicVector<T>::operator*(T val) const
{
    TDynamicVector<T> res(sz);
    for (size_t i = 0; i < sz; i++)
    {
        res.pMem[i] = pMem[i] * val;
    }
    return res;
}
template <typename T>
TDynamicVector<T> TDynamicVector<T>::operator+(const TDynamicVector<T>& v) const
{
    if (v.sz != sz) throw std::invalid_argument("Vectors have not equal sizes");
    TDynamicVector<T> res(sz);
    for (size_t i = 0; i < sz; i++)
    {
        res.pMem[i] = pMem[i] + v.pMem[i];
    }
    return res;
}
template <typename T>
TDynamicVector<T> TDynamicVector<T>::operator-(const TDynamicVector<T>& v) const
{
    if (v.sz != sz) throw std::invalid_argument("Vectors have not equal sizes");
    TDynamicVector<T> res(sz);
    for (size_t i = 0; i < sz; i++)
    {
        res.pMem[i] = pMem[i] - v.pMem[i];
    }
    return res;
}
template <typename T>
T TDynamicVector<T>::operator*(const TDynamicVector<T>& v) const //noexcept(noexcept(T()))
{
    if (v.sz != sz) throw std::invalid_argument("Vectors have not equal sizes");
    T res = {};
    for (size_t i = 0; i < sz; i++)
    {
        res += pMem[i] * v.pMem[i];
    }
    return res;
}
#endif