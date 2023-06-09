#pragma once

#include <iosfwd>
#include <iterator>
#include <cstddef>
#include <concepts>
#include <ranges>
#include <stdexcept>
#include <initializer_list>
#include <algorithm>

template <typename matrixType>
concept Numeric = std::is_arithmetic_v<matrixType>;
template <typename matrixType>
class Matrix
{
public:
    // CONSTRUCTOR FOR MATRIX
    Matrix();
    Matrix(std::size_t rows, std::size_t columns);
    Matrix(const Matrix<matrixType> &matrix); // copy constructor
    Matrix(const std::initializer_list<std::initializer_list<matrixType>> &matrix);

    // DECONSTRUCTOR FOR MATRIX
    ~Matrix();

    // ITERATOR CLASS(contiguousIterator)
    class Iterator
    {
    public:
        using iterator_category = std::contiguous_iterator_tag;
        using difference_type = std::ptrdiff_t;
        using value_type = matrixType;
        using pointer = matrixType *;
        using reference = matrixType &;

        // CONSTRUCTOR FOR ITERATOR
        Iterator(); // Default
        Iterator(pointer m_ptr);

        // ITERATOR MEMBER FUNCTIONS
        auto operator*() const -> reference;                     // Dereferenceable
        auto operator->() const -> pointer;                      // Arrow-deferenceable
        auto operator[](difference_type gap) const -> reference; // Subscripting
        auto operator++() -> Iterator &;                         // Pre-incrementable
        auto operator++(int) -> Iterator;                        // Post-incrementable
        auto operator--() -> Iterator &;                         // Pre-decrementable
        auto operator--(int) -> Iterator;                        // Post-decrementable
        auto operator+=(difference_type gap) -> Iterator &;      // Compound_addition
        auto operator-=(difference_type gap) -> Iterator &;      // Compound_subraction

        // FRIEND METHODS IMPLEMENTATION
        friend auto operator+(const Iterator &iter, difference_type gap) -> Iterator // Addition(iter + gap)
        {
            typename Matrix<matrixType>::Iterator tempIter(iter);
            tempIter += gap;
            return tempIter;
        }
        friend auto operator+(difference_type gap, const Iterator &iter) -> Iterator // Addition(gap + iter)
        {
            return iter + gap;
        }
        friend auto operator-(const Iterator &iter, difference_type gap) -> Iterator // Subraction(iter - gap)
        {
            typename Matrix<matrixType>::Iterator tempIter(iter);
            tempIter -= gap;
            return tempIter;
        }
        friend auto operator-(const Iterator &lhsIter, const Iterator &rhsIter) -> difference_type // Subraction(gap - iter)
        {
            return lhsIter.m_ptr - rhsIter.m_ptr;
        }
        friend auto operator<=>(const Iterator &lhsIter, const Iterator &rhsIter) -> bool // 3-way-comparision
        {
            return (lhsIter.m_ptr <=> rhsIter.m_ptr);
        }
        friend auto operator==(const Iterator &lhsIter, const Iterator &rhsIter) -> bool // Equality
        {
            return (lhsIter.m_ptr == rhsIter.m_ptr);
        }
        friend auto operator!=(const Iterator &lhsIter, const Iterator &rhsIter) -> bool // Inequality
        {
            return !(lhsIter == rhsIter);
        }

    private:
        pointer m_ptr;
    };

    // ROW CLASS FOR SYNTAX MATRIX[ROWS][COLUMNS]
    class Row
    {
    public:
        Row(matrixType *rowStartElement, std::size_t column);

        auto operator[](std::size_t column) -> matrixType &;
        auto operator[](std::size_t column) const -> const matrixType &;
        auto operator=(const Row &row) const -> const Row;

    private:
        std::size_t columns;
        matrixType *rowStartElement;
    };

    // MATRIX CLASS MEMBER FUCNTIONS
    // RANGE COMPATIBILITY
    auto begin() -> Iterator;
    auto end() -> Iterator;
    auto begin() const -> const Iterator;
    auto end() const -> const Iterator;

    // ACCESSORS
    auto operator[](std::size_t row) -> Row;
    auto operator[](std::size_t row) const -> const Row;
    auto operator()(std::size_t row, std::size_t column) -> matrixType &;
    auto operator()(std::size_t row, std::size_t column) const -> const matrixType &;

    inline auto getRows() -> std::size_t;
    inline auto getColumns() -> std::size_t;
    inline auto getRows() const -> const std::size_t;
    inline auto getColumns() const -> const std::size_t;
    // ASSIGNMENT
    auto operator=(const Matrix<matrixType> &matrix) -> Matrix<matrixType> &;

    // MATRIX CLASS OPERATIONS
    auto transpose() -> Matrix<matrixType>;
    auto power(std::size_t exponent) -> Matrix<matrixType>;
    auto gaussElimination() -> Matrix<matrixType>;

    // OUTPUT MATRIX
    friend auto operator<<(std::ostream &outputStream, const Matrix<matrixType> &matrix) -> std::ostream &
    {
        for (const auto &row : matrix | std::ranges::views::chunk(matrix.mainColumns))
        {
            for (const auto &column : row)
            {
                outputStream << column << " ";
            }
            outputStream << std::endl;
        }

        return outputStream;
    }

    friend auto operator>>(std::istream &inputStream, Matrix<matrixType> &matrix) -> std::istream &
    {
        for (auto &&row : matrix | std::ranges::views::chunk(matrix.mainColumns))
        {
            for (auto &&column : row)
            {
                inputStream >> column;
            }
        }

        return inputStream;
    }

private:
    std::size_t mainRows, mainColumns;
    matrixType *mainMatrix;
};

// MATRIX OPERATIONS
template <typename lhsMatrixType, typename rhsMatrixType>
auto operator+(const Matrix<lhsMatrixType> &lhsMatrix, const Matrix<rhsMatrixType> &rhsMatrix) -> Matrix<decltype(lhsMatrixType() + rhsMatrixType())>;

template <typename lhsMatrixType, typename rhsMatrixType>
auto operator-(const Matrix<lhsMatrixType> &lhsMatrix, const Matrix<rhsMatrixType> &rhsMatrix) -> Matrix<decltype(lhsMatrixType() - rhsMatrixType())>;

template <typename lhsMatrixType, typename rhsMatrixType>
auto operator*(const Matrix<lhsMatrixType> &lhsMatrix, const Matrix<rhsMatrixType> &rhsMatrix) -> Matrix<decltype(lhsMatrixType() * rhsMatrixType())>;

template <typename matrixType, typename constIntergralType>
auto operator*(const Matrix<matrixType> &matrix, const constIntergralType &constIntegral) -> Matrix<decltype(matrixType() * constIntergralType())>;

template <typename matrixType, typename constIntergralType>
auto operator*(const constIntergralType &constIntegral, const Matrix<matrixType> &matrix) -> Matrix<decltype(matrixType() * constIntergralType())>;

template <typename matrixType, typename constIntergralType>
auto operator/(const Matrix<matrixType> &matrix, const constIntergralType &constIntegral) -> Matrix<double>;

template <typename lhsMatrixType, typename rhsMatrixType>
auto operator==(const Matrix<lhsMatrixType> &lhsMatrix, const Matrix<rhsMatrixType> &rhsMatrix) -> bool;

template <typename lhsMatrixType, typename rhsMatrixType>
auto operator!=(const Matrix<lhsMatrixType> &lhsMatrix, const Matrix<rhsMatrixType> &rhsMatrix) -> bool;

#include "Matrix.inl"
