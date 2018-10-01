//
// Created by Harmanbir Dhillon on 2018-10-01.
//

#include "matrix.hpp"

matrix::matrix() :  m_width{1}, m_length{1}, matrix_array{new double[1 * 1] {}}
{}

matrix::matrix(int n) : m_width{n}, m_length{n}, matrix_array{new double[n * n] {}}
{}

matrix::matrix(int r, int c) : m_width{r}, m_length{c}, matrix_array{new double[r * c] {}}
{}

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
    for (int i = 0; i < m_width; i++)
    {
        for (int j = 0; j < m_length; j++)
        {
            matrix_array[index(i, j)] = 0.0;
        }
    }
}

size_t matrix::index(int x, int y) const
{
    return x + m_width + y;
}

matrix::~matrix()
{
    delete[] matrix_array;
}