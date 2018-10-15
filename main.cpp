#include <iostream>
#include <fstream>
#include <vector>
#include "matrix.hpp"
#include "connectivity_matrix.hpp"

int main()
{
    std::ifstream myfile;
    myfile.open("../connectivity.txt");
    if (!myfile) {
        std::cerr << "unable to open file";
        exit(1);
    }
    std::vector<double> temp_vector;
    double temp;
    while(myfile >> temp)
    {
        temp_vector.push_back(temp);
    }

    size_t size = temp_vector.size();

    auto * matrix_double = new double [size]; {};

    for (size_t i = 0; i < size; ++i)
    {
        matrix_double[i] = temp_vector.at(i);
    }

    matrix * j = new connectivity_matrix(matrix_double, size);

    ((connectivity_matrix*)j)->markov_process(((connectivity_matrix*)j)->transition(((connectivity_matrix*)j)->stochastic()));


}
