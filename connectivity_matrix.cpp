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
    importance();
}

void connectivity_matrix::importance()
{
    int m_length = get_m_length();
    int m_width  = get_m_width();

    matrix S(getMatrix_array(), get_m_width() * get_m_length());

    S.add_columns();

    matrix Q(m_length, m_width, 1.0 / m_length);

    matrix M(m_length);

    S.multiply_constant(p);
    Q.multiply_constant(1 - p);

    M = S + Q;

    matrix rank(m_length, 1, 1);
    matrix test(m_length, 1, 2);
    matrix temp;

    while (rank != test)
    {
        test = rank;
        temp = M;
        temp *= rank;
        rank = temp;
    }

    rank.add_columns();

    rank.make_percentage();

    rank.print_result();
}
