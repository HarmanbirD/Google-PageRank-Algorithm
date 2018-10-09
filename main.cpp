#include <iostream>
#include "matrix.hpp"

int main() {
    double one_arr [3] = {3.0, 4.0, 2.0};
    double two_arr [12] = {13.0, 9.0, 7.0, 15.0, 8.0, 7.0, 4.0, 6.0, 6.0, 4.0, 0.0, 3.0};
//    double one_arr [6] = {1.0, 2.0, 3.0, 4.0, 5.0, 6.0};
//    double two_arr [12] = {7.0, 8.0, 9.0, 10.0, 11.0, 12.0};
    matrix one(1, 3);
    matrix two(3, 4);
    int k = 0;
    for (int i = 0; i < 1; ++i)
    {
        for (int j = 0; j < 3; ++j)
        {
            one.set_value(i, j, one_arr[k]);
            k++;
        }
    }

    k = 0;
    for (int i = 0; i < 3; ++i)
    {
        for (int j = 0; j < 4; ++j)
        {
            two.set_value(i, j, two_arr[k++]);
        }
    }

    matrix three;

    one = one * two;

    std::cout << one;

//
//    double arr [4] = {1.0, 2.0, 3.0, 4.0};
//    double arr_thre [4] = {2.0, 0.0, 1.0, 2.0};
//
//    matrix three(arr, 4);
//    matrix threee(arr_thre, 4);
//
//    threee *= three;
//
//    std::cout << threee;




}