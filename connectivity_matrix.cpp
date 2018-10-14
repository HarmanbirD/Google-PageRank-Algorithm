//
// Created by Harmanbir Dhillon on 2018-10-09.
//

#include "connectivity_matrix.hpp"

connectivity_matrix::connectivity_matrix()
    :   matrix()
{}

connectivity_matrix::connectivity_matrix(const double *matrix_array, const int size)
    :   matrix(matrix_array, size)
{
    for (int i = 0; i < size; ++i)
    {
        if (matrix_array[i] != 0 && matrix_array[i] != 1)
        {
            throw std::invalid_argument("matrix should contain all 1's or 0's");
        }
    }
    markov_process(transition(stochastic()));
}

matrix connectivity_matrix::stochastic()
{
    int m_length = get_m_length();
    int m_width  = get_m_width();

    // copies the connectivity matrix into a new matrix S
    matrix S(getMatrix_array(), m_width * m_length);

    // makes the matrix into a left stochastic matrix
    S.add_columns();

    // returns stochastic matrix
    return S;
}

matrix connectivity_matrix::transition(const matrix stochastic) {
    int m_length = get_m_length();
    int m_width  = get_m_width();

    matrix S(stochastic);
    // makes an array of elements that are 1/n
    matrix Q(m_length, m_width, 1.0 / m_length);
    // transitive matrix
    matrix M(m_length);

    // multiplies matrix by 0.85
    S.multiply_constant(p);
    // multiplies matrix by 0.15
    Q.multiply_constant(1 - p);

    // transitive matrix is stochastic matrix + Q
    M = S + Q;

    // returns transitive matrix
    return M;
}

void connectivity_matrix::markov_process(const matrix transition) {
    int m_length = get_m_length();
    matrix rank(m_length, 1, 1);
    matrix test(m_length, 1, 2);
    matrix temp;

    while (rank != test)
    {
        test = rank;
        temp = transition;
        temp *= rank;
        rank = temp;
    }

    // add all the numbers in the column add divide each number by the sum
    // makes the sum of all numbers equal to 1
    rank.add_columns();

    // multiply each number by 100 to make it into a percentage
    rank.make_percentage();

    // prints the matrix along with the page letter
    rank.print_result();
}
