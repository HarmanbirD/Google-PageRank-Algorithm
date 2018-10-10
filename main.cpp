#include <iostream>
#include <fstream>
#include <vector>
#include "matrix.hpp"
#include "connectivity_matrix.hpp"

int main()
{
    std::ifstream myfile;
    myfile.open("../matrix_test.txt");
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

    double * matrix_double = new double [temp_vector.size()] {};

    for (int i = 0; i < temp_vector.size(); ++i)
    {
        matrix_double[i] = temp_vector.at(i);
    }

    connectivity_matrix * j = new connectivity_matrix(matrix_double, temp_vector.size());
    j->importance();

//    double one_arr [4] = {1, 1, 1, 1};
//    double two_arr [16] = {0, 1, 1, 0, 1, 0, 1, 0, 1, 1, 0, 0, 0, 0, 0, 0};
////    double one_arr [6] = {1.0, 2.0, 3.0, 4.0, 5.0, 6.0};
////    double two_arr [12] = {7.0, 8.0, 9.0, 10.0, 11.0, 12.0};
//    matrix one(4, 1);
//    matrix two(4);
//    int k = 0;
//    for (int i = 0; i < 4; ++i)
//    {
//        for (int j = 0; j < 1; ++j)
//        {
//            one.set_value(i, j, one_arr[k]);
//            k++;
//        }
//    }
//
//    k = 0;
//    for (int i = 0; i < 4; ++i)
//    {
//        for (int j = 0; j < 4; ++j)
//        {
//            two.set_value(i, j, two_arr[k++]);
//        }
//    }
//
//    two *= one;
//
//    std::cout << one;
}