#include <iostream>
#include <fstream>
#include <vector>
#include "matrix.hpp"
#include "connectivity_matrix.hpp"

// reads from file and puts contents in a vector
std::vector<double> read_file_to_vector()
{
    std::ifstream my_file;
    my_file.open("../connectivity.txt");
    if (!my_file) {
        throw std::invalid_argument{"unable to open file"};
    }
    std::vector<double> temp_vector;
    double temp;
    while(my_file >> temp)
    {
        temp_vector.push_back(temp);
    }

    return temp_vector;
}

// converts a vector into a double*, returns the double*
double* vector_to_array(std::vector<double> temp_vector)
{
    size_t size = temp_vector.size();

    auto * matrix_double = new double [size]; {};

    for (size_t i = 0; i < size; ++i)
    {
        matrix_double[i] = temp_vector.at(i);
    }
    return matrix_double;
}

// main
int main()
{
    std::vector<double> temp_vector = read_file_to_vector();

    auto * matrix_double = vector_to_array(temp_vector);

    matrix * j = new connectivity_matrix(matrix_double, (int) temp_vector.size());

    ((connectivity_matrix*)j)->markov_process(((connectivity_matrix*)j)->transition(((connectivity_matrix*)j)->stochastic()));
}
