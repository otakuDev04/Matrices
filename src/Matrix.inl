#include <iostream>
#include <ranges>
#include "Matrix.h"

// ITERATOR CLASS
template <typename matrixType>
Matrix<matrixType>::Iterator::Iterator() : m_ptr(nullptr) {}

template <typename matrixType>
Matrix<matrixType>::Iterator::Iterator(pointer m_ptr) : m_ptr(m_ptr) {}

// ITERATOR MEMBER METHODS

template <typename matrixType>
auto Matrix<matrixType>::Iterator::operator*() const -> reference
{
    return *m_ptr;
}

template <typename matrixType>
auto Matrix<matrixType>::Iterator::operator->() const -> pointer
{
    return m_ptr;
}

template <typename matrixType>
auto Matrix<matrixType>::Iterator::operator[](difference_type gap) const -> reference
{
    return *(m_ptr + gap);
}

template <typename matrixType>
auto Matrix<matrixType>::Iterator::operator++() -> Matrix::Iterator &
{
    ++m_ptr;
    return *this;
}

template <typename matrixType>
auto Matrix<matrixType>::Iterator::operator++(int) -> Matrix<matrixType>::Iterator
{
    Iterator tempIter = *this;
    ++m_ptr;
    return tempIter;
}

template <typename matrixType>
auto Matrix<matrixType>::Iterator::operator--() -> Matrix<matrixType>::Iterator &
{
    --m_ptr;
    return *this;
}

template <typename matrixType>
auto Matrix<matrixType>::Iterator::operator--(int) -> Matrix<matrixType>::Iterator
{
    Iterator tempIter = *this;
    --m_ptr;
    return tempIter;
}

template <typename matrixType>
auto Matrix<matrixType>::Iterator::operator+=(difference_type gap) -> Matrix<matrixType>::Iterator &
{
    m_ptr += gap;
    return *this;
}

template <typename matrixType>
auto Matrix<matrixType>::Iterator::operator-=(difference_type gap) -> Matrix<matrixType>::Iterator &
{
    m_ptr -= gap;
    return *this;
}

// MATRIX CLASSS MEMBER FUNCTIONS
template <typename matrixType>
auto Matrix<matrixType>::begin() -> Iterator
{
    return Matrix::Iterator(mainMatrix.get());
}

template <typename matrixType>
auto Matrix<matrixType>::end() -> Iterator
{
    return Matrix<matrixType>::Iterator(mainMatrix.get() + (mainRows * mainColumns));
}

// CONSTRUCTORS
template <typename matrixType>
Matrix<matrixType>::Matrix() : mainRows(1), mainColumns(1), mainMatrix(new matrixType[mainRows * mainColumns])
{
    std::ranges::fill(*this, 0);
}

template <typename matrixType>
Matrix<matrixType>::Matrix(std::size_t rows, std::size_t columns) : mainRows(rows), mainColumns(columns), mainMatrix(new matrixType[mainRows * mainColumns])
{
    std::ranges::fill(*this, 0);
}
