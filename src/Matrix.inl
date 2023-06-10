#include <iostream>
#include "Matrix.h"

// ITERATOR CLASS CONSTRUCTORS
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
// ROW CLASS CONSTRUCTORS
template <typename matrixType>
Matrix<matrixType>::Row::Row(matrixType *rowStartElement, std::size_t column) : rowStartElement(rowStartElement), columns(column) {}

// ROW CLASS MEMBER FUNCTIONS
template <typename matrixType>
auto Matrix<matrixType>::Row::operator[](std::size_t column) -> matrixType &
{
    if (column >= columns)
    {
        throw std::out_of_range("Column index out of range");
    }
    return rowStartElement[column];
}

template <typename matrixType>
auto Matrix<matrixType>::Row::operator[](std::size_t column) const -> const matrixType &
{
    if (column >= columns)
    {
        throw std::out_of_range("Column index out of range");
    }
    return rowStartElement[column];
}

// MATRIX CLASS CONSTRUCTORS
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

template <typename matrixType>
Matrix<matrixType>::Matrix(const Matrix<matrixType> &matrix) : mainRows(matrix.mainRows), mainColumns(matrix.mainColumns)
{
    mainMatrix = new matrixType[mainRows * mainColumns];
    std::copy(matrix.mainMatrix, matrix.mainMatrix + (mainRows * mainColumns), mainMatrix);
}

// MATRIX CLASS DECONSTRUCTORS
template <typename matrixtype>
Matrix<matrixtype>::~Matrix()
{
    delete[] mainMatrix;
}

// MATRIX CLASSS MEMBER FUNCTIONS
// RANGE COMPATIBILITY
template <typename matrixType>
auto Matrix<matrixType>::begin() -> Iterator
{
    return Matrix<matrixType>::Iterator(mainMatrix);
}

template <typename matrixType>
auto Matrix<matrixType>::end() -> Iterator
{
    return Matrix<matrixType>::Iterator(mainMatrix + (mainRows * mainColumns));
}

template <typename matrixType>
auto Matrix<matrixType>::begin() const -> const Iterator
{
    return Matrix<matrixType>::Iterator(mainMatrix);
}

template <typename matrixType>
auto Matrix<matrixType>::end() const -> const Iterator
{
    return Matrix<matrixType>::Iterator(mainMatrix + (mainRows * mainColumns));
}
// ACCESSORS
template <typename matrixType>
auto Matrix<matrixType>::operator[](std::size_t row) -> Row
{
    if (row >= mainRows)
    {
        throw std::out_of_range("Row index out of range");
    }
    return Row(mainMatrix + row * mainColumns, mainColumns);
}

template <typename matrixType>
auto Matrix<matrixType>::operator[](std::size_t row) const -> const Row
{
    if (row >= mainRows)
    {
        throw std::out_of_range("Row index out of range");
    }
    return Row(mainMatrix + row * mainColumns, mainColumns);
}

template <typename matrixType>
auto Matrix<matrixType>::operator()(std::size_t row, std::size_t column) -> matrixType &
{
    if (row >= mainRows || column >= mainColumns)
    {
        throw std::out_of_range("Row or Column index out of range");
    }
    return mainMatrix[(row * mainColumns) + column];
}

template <typename matrixType>
auto Matrix<matrixType>::operator()(std::size_t row, std::size_t column) const -> const matrixType &
{
    if (row >= mainRows || column >= mainColumns)
    {
        throw std::out_of_range("Row or Column index out of range");
    }
    return mainMatrix[(row * mainColumns) + column];
}

template <typename matrixType>
auto Matrix<matrixType>::getRows() -> std::size_t
{
    return mainRows;
}

template <typename matrixType>
auto Matrix<matrixType>::getColumns() -> std::size_t
{
    return mainColumns;
}

template <typename matrixType>
auto Matrix<matrixType>::getRows() const -> const std::size_t
{
    return mainRows;
}

template <typename matrixType>
auto Matrix<matrixType>::getColumns() const -> const std::size_t
{
    return mainColumns;
}
// ASSIGNMENT
template <typename matrixType>
auto Matrix<matrixType>::operator=(const Matrix<matrixType> &matrix) -> Matrix<matrixType> &
{
    if (this != matrix)
    {
        mainRows = matrix.mainRows;
        mainColumns = matrix.mainColumns;
        std::copy(matrix.begin, matrix.end, mainMatrix);
    }
    return *this;
}

// MATRIX OPERATIONS
template <typename lhsMatrixType, typename rhsMatrixType>
auto operator+(const Matrix<lhsMatrixType> &lhsMatrix, const Matrix<rhsMatrixType> &rhsMatrix) -> Matrix<decltype(lhsMatrixType() + rhsMatrixType())>
{

    if (!((lhsMatrix.getRows() == rhsMatrix.getRows()) || (lhsMatrix.getColumns() == rhsMatrix.getColumns())))
    {
        throw std::out_of_range("size of matrices doesnt Match");
    }

    Matrix<decltype(lhsMatrixType() + rhsMatrixType())> resultMatrix(lhsMatrix.getRows(), lhsMatrix.getColumns());

    for (auto &&[resultMatrixElement, lhsMatrixElement, rhsMatrixElement] : std::ranges::views::zip(resultMatrix, lhsMatrix, rhsMatrix))
    {
        resultMatrixElement = lhsMatrixElement + rhsMatrixElement;
    }

    return resultMatrix;
}

template <typename lhsMatrixType, typename rhsMatrixType>
auto operator-(const Matrix<lhsMatrixType> &lhsMatrix, const Matrix<rhsMatrixType> &rhsMatrix) -> Matrix<decltype(lhsMatrixType() - rhsMatrixType())>
{

    if (!((lhsMatrix.getRows() == rhsMatrix.getRows()) || (lhsMatrix.getColumns() == rhsMatrix.getColumns())))
    {
        throw std::out_of_range("size of matrices doesnt Match");
    }

    Matrix<decltype(lhsMatrixType() - rhsMatrixType())> resultMatrix(lhsMatrix.getRows(), lhsMatrix.getColumns());

    for (auto &&[resultMatrixElement, lhsMatrixElement, rhsMatrixElement] : std::ranges::views::zip(resultMatrix, lhsMatrix, rhsMatrix))
    {
        resultMatrixElement = lhsMatrixElement - rhsMatrixElement;
    }

    return resultMatrix;
}
