#pragma once

#include <iosfwd>
#include <memory>
#include <iterator>
#include <cstddef>
#include <concepts>

template <typename matrixType>
concept Numeric = std::is_arithmetic_v<matrixType>;

template <typename matrixType>
class Matrix
{
public:
    // CONSTRUCTOR FOR MATRIX
    Matrix();
    Matrix(std::size_t rows, std::size_t columns);
    Matrix(const Matrix &matrix);

    // ITERATOR CLASS(randomAccessIterator)
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

        // MEMBER FUNCTIONS
        auto operator*() const -> reference;                     // Dereferenceable
        auto operator->() const -> pointer;                      // Arrow-deferenceable
        auto operator[](difference_type gap) const -> reference; // Subscripting
        // auto operator=(const Iterator &) -> Iterator;                                      // Copy assognable
        auto operator++() -> Iterator &;                    // Pre-incrementable
        auto operator++(int) -> Iterator;                   // Post-incrementable
        auto operator--() -> Iterator &;                    // Pre-decrementable
        auto operator--(int) -> Iterator;                   // Post-decrementable
        auto operator+=(difference_type gap) -> Iterator &; // Compound_addition
        auto operator-=(difference_type gap) -> Iterator &; // Compound_subraction

        /*
         * FRIEND METHODS IMPLEMENTATION
         */
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

    auto begin() -> Iterator;
    auto end() -> Iterator;

private:
    std::size_t mainRows, mainColumns;
    std::unique_ptr<matrixType[]> mainMatrix;
};

#include "Matrix.inl"
