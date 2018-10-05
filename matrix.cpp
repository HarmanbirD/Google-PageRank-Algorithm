//
// Created by Harmanbir Dhillon on 2018-10-01.
//

#include <limits>
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

matrix::matrix(double mat_array[])
{
    int size = sizeof(mat_array) / sizeof(mat_array[0]);

    if (!is_perfect_square(size))
    {
        throw std::invalid_argument("array size is not a perfect square");
    }

    matrix_array = new double[size * size];

    for (int i = 0; i < size; ++i)
    {
        for (int j = 0; j < size; ++j)
        {
            matrix_array[index(i, j)] = mat_array[i * j];
        }
    }
}

void matrix::set_value(int row, int column, double value)
{
    matrix_array[index(row, column)] = value;
}

double matrix::get_value(int row, int column) const
{
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

size_t matrix::index(int x, int y) const
{
    return m_width * y + x;
}

bool matrix::is_perfect_square(int x)
{
    int squared = sqrt(x);

    return ((squared - floor(squared)) == 0);
}

matrix::~matrix()
{
    delete[] matrix_array;
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

}

matrix operator-(matrix hs, const matrix rhs)
{

}

matrix operator*(matrix hs, const matrix rhs)
{

}

matrix& matrix::operator++()
{
    return *this;
}

matrix matrix::operator++(int)
{

}

matrix& matrix::operator--()
{
    return *this;
}

matrix matrix::operator--(int)
{

}

matrix& matrix::operator+=(const matrix& rhs)
{

}

matrix& matrix::operator-=(const matrix& rhs)
{

}

matrix& matrix::operator*=(const matrix& rhs)
{

}

matrix matrix::operator=(matrix other)
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
