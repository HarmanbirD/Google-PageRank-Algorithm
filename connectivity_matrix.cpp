//
// Created by Harmanbir Dhillon on 2018-10-09.
//

#include "connectivity_matrix.hpp"

connectivity_matrix::connectivity_matrix()
    :   matrix()
{}

connectivity_matrix::connectivity_matrix(double *matrix_array, int size)
    :   matrix(matrix_array, size)
{
    for (int i = 0; i < size; ++i)
    {
        if (matrix_array[i] != 0 && matrix_array[i] != 1)
        {
            throw std::invalid_argument("matrix should contain all 1's or 0's");
        }
    }
}

void connectivity_matrix::importance()
{
    int m_length = get_m_length();
    int m_width  = get_m_width();

    matrix S(m_length);

    for (int i = 0; i < m_width; ++i)
    {
        int sum = 0;
        for (int j = 0; j < m_length; ++j)
        {
            sum += get_value(j, i);
        }
        if (sum == 0)
        {
            for (int j = 0; j < m_length; ++j) {
                double temp = 1.0 / m_length;
                S.set_value(j, i, temp);
            }
        } else {
            for (int j = 0; j < m_length; ++j) {
                double temp = get_value(j, i);
                if (temp == 0) {
                    S.set_value(j, i, 0.0);
                } else if (temp == 1) {
                    S.set_value(j, i, temp / sum);
                }
            }
        }
    }

    matrix Q (m_length);
    for (int i = 0; i < m_length; ++i)
    {
        for (int j = 0; j < m_width; ++j)
        {
            Q.set_value(i, j, 1.0 / m_length);
        }
    }

    matrix M(m_length);

    S.multiply_constant(p);
    Q.multiply_constant(1 - p);

    M = S + Q;

    matrix rank(m_length, 1);
    for (int i = 0; i < m_length; ++i)
    {
        for (int j = 0; j < 1; ++j)
        {
            rank.set_value(i, j, 1.0);
        }
    }

    for (int i = 0; i < 10000; ++i)
    {
        matrix temp(M);
        temp *= rank;
        rank = temp;
    }


    rank.add_columns();

    std::cout << rank;


}
