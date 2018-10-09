//
// Created by Harmanbir Dhillon on 2018-10-01.
//

#include <limits>
#include <iostream>
#include "matrix.hpp"

matrix::matrix()
    :   m_length{1},
        m_width{1},
        matrix_array{new double[1 * 1] {}}
{}

matrix::matrix(int n)
    :   m_length{n},
        m_width{n},
        matrix_array{new double[n * n] {}}
{
    if (n <= 0)
    {
        throw std::invalid_argument("received negative or zero value");
    }
}

matrix::matrix(int r, int c)
    :   m_length{r},
        m_width{c},
        matrix_array{new double[r * c] {}}
{
    if (r <= 0 || c <= 0)
    {
        throw std::invalid_argument("received negative or zero value");
    }
}

matrix::matrix(double mat_array[], int capacity)
{

    if (!is_perfect_square(capacity))
    {
        throw std::invalid_argument("array size is not a perfect square");
    }

    int size = sqrt(capacity);

    matrix_array = new double[capacity];
    m_length = size;
    m_width  = size;

    for (int i = 0; i < size; ++i)
    {
        for (int j = 0; j < size; ++j)
        {
            matrix_array[index(i, j)] = mat_array[index(i, j)];
        }
    }
}

matrix::matrix(const matrix& matrix_t)
    :   m_length{matrix_t.m_length},
        m_width{matrix_t.m_width},
        matrix_array{new double[m_length * m_width] {}}
{
    std::copy(matrix_t.matrix_array, matrix_t.matrix_array + (m_length * m_width), matrix_array);
}


void matrix::set_value(int row, int column, double value)
{
    if(row < 0 || column < 0)
    {
        throw std::invalid_argument("row or column cannot be 0");
    }

    if(row >= m_length || column >= m_width)
    {
        throw std::invalid_argument("row or column index have to be in the array");
    }

    matrix_array[index(row, column)] = value;
}

double matrix::get_value(int row, int column) const
{
    if(row < 0 || column < 0)
    {
        throw std::invalid_argument("row or column cannot be 0");
    }

    if(row >= m_length || column >= m_width)
    {
        throw std::invalid_argument("row or column index have to be in the array");
    }

    return matrix_array[index(row, column)];
}

void matrix::clear()
{
    for (int i = 0; i < m_length; i++)
    {
        for (int j = 0; j < m_width; j++)
        {
            matrix_array[index(i, j)] = 0.0;
        }
    }
}

inline int matrix::index(int x, int y) const
{
    return m_width * x + y;
}

bool matrix::is_perfect_square(int x) const
{
    double squared = sqrt(x);

    return ((squared - floor(squared)) == 0);
}

matrix::~matrix()
{
    if (matrix_array != nullptr)
    {
        delete[] matrix_array;
    }
}

bool operator==(const matrix& hs, const matrix& rhs)
{
    if (hs.m_width != rhs.m_width || hs.m_length != rhs.m_length)
    {
        return false;
    }

    for (int i = 0; i < hs.m_length; ++i)
    {
        for (int j = 0; j < hs.m_width; ++j)
        {
            double difference = hs.matrix_array[hs.index(i, j)] = rhs.matrix_array[hs.index(i, j)];
            if (!(difference) <= std::numeric_limits<double>::epsilon() * fabs(hs.matrix_array[hs.index(i, j)]))
            {
                return false;
            }
        }
    }
    return true;
}

bool operator!=(const matrix& hs, const matrix& rhs)
{
    return !operator==(hs, rhs);
}

matrix operator+(matrix hs, const matrix rhs)
{
    if (hs.m_length != rhs.m_length || hs.m_width != rhs.m_width)
    {
        throw std::invalid_argument("matrices have to be the same size");
    }

    matrix temp = matrix(hs);

    temp += rhs;
    return temp;
}

matrix operator-(matrix hs, const matrix rhs)
{
    if (hs.m_length != rhs.m_length || hs.m_width != rhs.m_width)
    {
        throw std::invalid_argument("matrices have to be the same size");
    }

    matrix temp = matrix(hs);

    temp -= rhs;
    return temp;
}

matrix operator*(matrix hs, const matrix rhs)
{
    matrix temp = matrix(hs);

    temp *= rhs;
    return temp;
}

matrix& matrix::operator++()
{
    for (int i = 0; i < m_length; i++)
    {
        for (int j = 0; j < m_width; j++)
        {
            matrix_array[index(i, j)] += 1.0;
        }
    }
    return *this;
}

matrix matrix::operator++(int)
{
    matrix tmp{*this};
    operator++();
    return tmp;
}

matrix& matrix::operator--()
{
    for (int i = 0; i < m_length; i++)
    {
        for (int j = 0; j < m_width; j++)
        {
            matrix_array[index(i, j)] -= 1.0;
        }
    }
    return *this;
}

matrix matrix::operator--(int)
{
    matrix tmp{*this};
    operator--();
    return tmp;
}

matrix& matrix::operator+=(const matrix& rhs)
{
    if (m_length != rhs.m_length || m_width != rhs.m_width)
    {
        throw std::invalid_argument("matrices have to be the same size");
    }

    for (int i = 0; i < m_length; i++)
    {
        for (int j = 0; j < m_width; j++)
        {
            this->matrix_array[index(i, j)] += rhs.matrix_array[index(i, j)];
        }
    }
    return *this;
}

matrix& matrix::operator-=(const matrix& rhs)
{
    if (m_length != rhs.m_length || m_width != rhs.m_width)
    {
        throw std::invalid_argument("matrices have to be the same size");
    }

    for (int i = 0; i < m_length; i++)
    {
        for (int j = 0; j < m_width; j++)
        {
            this->matrix_array[index(i, j)] -= rhs.matrix_array[index(i, j)];
        }
    }
    return *this;
}

matrix& matrix::operator*=(const matrix& rhs)
{
    if (this -> m_width != rhs.m_length)
    {
        throw std::invalid_argument("number of columns of first matrix does not equal number of rows in second matrix");
    }

    auto * new_matrix = new double[this -> m_length * rhs.m_width] {0.0};

    for (int i = 0; i < this -> m_length; ++i)
    {
        for (int j = 0; j < rhs.m_width; ++j)
        {
            for (int k = 0; k < this -> m_width; ++k)
            {
//                double first = this->matrix_array[index(i, k)];
//                double second = rhs.matrix_array[rhs.index(k, j)];
                new_matrix[index(i, j)] += (this->matrix_array[index(i, k)] * rhs.matrix_array[rhs.index(k, j)]);
            }
        }
    }
    delete[] matrix_array;
    matrix_array = new double[this -> m_length * rhs.m_width];
    m_width = rhs.m_width;
    std::copy(new_matrix, new_matrix + (this -> m_length * rhs.m_width), matrix_array);
    delete[] new_matrix;
    return *this;
}

matrix& matrix::operator=(matrix other)
{
    swap(*this, other);
    return *this;
}

void swap(matrix& first, matrix& second)
{
    using std::swap;
    swap(first.m_length, second.m_length);
    swap(first.m_width, second.m_width);
    swap(first.matrix_array, second.matrix_array);
}

std::ostream &operator<<(std::ostream &os, const matrix &matrix) {
    for (int i = 0; i < matrix.m_length; ++i)
    {
        for (int j = 0; j < matrix.m_width; ++j)
        {
            os << matrix.matrix_array[matrix.index(i, j)] << " ";
        }
        os << std::endl;
    }
    return os;
}
