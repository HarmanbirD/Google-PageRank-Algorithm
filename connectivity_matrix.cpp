//
// Created by Harmanbir Dhillon on 2018-10-09.
//

#include "connectivity_matrix.hpp"

// default constructor
// calls supers default constructor
connectivity_matrix::connectivity_matrix()
    :   matrix()
{}

// constructor that takes a double array and the size of the array
// checks to see if the array is a connectivity matrix by checking if every element is a 0 or a 1
// calls the supers constructor that takes an array and size
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
}

// returns a matrix that is a left stochastic matrix
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

// returns a transition matrix
// takes in a stochastic matrix
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

// performs the markov_process on the transition matrix passed in
void connectivity_matrix::markov_process(const matrix transition) {
    int m_length = get_m_length();
    // creates matrix rank with all elements initialized to 1
    matrix rank(m_length, 1, 1);

    while (transition * rank != rank)
    {
        rank = transition * rank;
    }

    // add all the numbers in the column add divide each number by the sum
    // makes the sum of all numbers equal to 1
    rank.add_columns();

    // multiply each number by 100 to make it into a percentage
    rank.make_percentage();

    // prints the matrix along with the page letter
    rank.print_result();
}
