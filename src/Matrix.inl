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

template <typename matrixType>
auto Matrix<matrixType>::Row::operator=(const Row &row) const -> const Row
{
    Row result(columns);
    for (std::size_t rowElement = 0; rowElement < columns; ++rowElement)
    {
        result.rowStartElement[rowElement] = rowStartElement[rowElement] * row.rowStartElement[rowElement];
    }
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

template <typename matrixType>
Matrix<matrixType>::Matrix(const std::initializer_list<std::initializer_list<matrixType>> &matrix) : mainRows(matrix.size()), mainColumns(matrix.begin()->size()), mainMatrix(new matrixType[mainRows * mainColumns])
{
    std::size_t row = 0;
    std::size_t column = 0;
    for (const auto &rowElement : matrix)
    {
        for (const auto &value : rowElement)
        {
            mainMatrix[row * mainColumns + column] = value;
            ++column;
        }
        ++row;
        column = 0;
    }
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
    if (this != &matrix)
    {
        matrixType *tempMatrix = new matrixType[matrix.mainRows * matrix.mainColumns];
        std::copy(matrix.mainMatrix, matrix.mainMatrix + (mainRows * mainColumns), tempMatrix);

        delete[] mainMatrix;
        mainRows = matrix.mainRows;
        mainColumns = matrix.mainColumns;
        std::copy(matrix.mainMatrix, matrix.mainMatrix + (mainRows * mainColumns), mainMatrix);
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

template <typename lhsMatrixType, typename rhsMatrixType>
auto operator*(const Matrix<lhsMatrixType> &lhsMatrix, const Matrix<rhsMatrixType> &rhsMatrix) -> Matrix<decltype(lhsMatrixType() * rhsMatrixType())>
{

    if (!(lhsMatrix.getColumns() == rhsMatrix.getRows()))
    {
        throw std::out_of_range("Invalid Multiplication");
    }

    Matrix<decltype(lhsMatrixType() * rhsMatrixType())> resultMatrix(lhsMatrix.getRows(), rhsMatrix.getColumns());

    for (std::size_t lhsRow = 0; lhsRow < lhsMatrix.getRows(); lhsRow++)
    {
        for (std::size_t rhsColumn = 0; rhsColumn < rhsMatrix.getColumns(); rhsColumn++)
        {
            for (std::size_t lhsColumn = 0; lhsColumn < lhsMatrix.getColumns(); lhsColumn++)
            {
                resultMatrix(lhsRow, rhsColumn) += lhsMatrix(lhsRow, lhsColumn) * rhsMatrix(lhsRow, rhsColumn);
            }
        }
    }

    return resultMatrix;
}

template <typename matrixType, typename constIntergralType>
auto operator*(const Matrix<matrixType> &otherMatrix, const constIntergralType &constIntegral) -> Matrix<decltype(matrixType() * constIntergralType())>
{
    Matrix<decltype(matrixType() * constIntergralType())> resultMatrix(otherMatrix.getRows(), otherMatrix.getColumns());

    for (const auto &[otherMatrixElement, resultMatrixElement] : std::ranges::views::zip(otherMatrix, resultMatrix))
    {
        resultMatrixElement = constIntegral * otherMatrixElement;
    }

    return resultMatrix;
}

template <typename matrixType, typename constIntergralType>
auto operator*(const constIntergralType &constIntegral, const Matrix<matrixType> &otherMatrix) -> Matrix<decltype(matrixType() * constIntergralType())>
{

    return otherMatrix * constIntegral;
}

template <typename matrixType, typename constIntergralType>
auto operator/(const Matrix<matrixType> &otherMatrix, const constIntergralType &constIntegral) -> Matrix<double>
{
    Matrix<double> resultMatrix(otherMatrix.getRows(), otherMatrix.getColumns());

    for (const auto &[otherMatrixElement, resultMatrixElement] : std::ranges::views::zip(otherMatrix, resultMatrix))
    {
        resultMatrixElement = static_cast<double>(otherMatrixElement) / constIntegral;
    }

    return resultMatrix;
}
