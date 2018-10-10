//
// Created by Harmanbir Dhillon on 2018-10-09.
//
#include "matrix.hpp"
#include <iostream>

#pragma once

class connectivity_matrix : public matrix {
    public:
        connectivity_matrix();
        connectivity_matrix(double * matrix_array, int size);
        void importance();


private:
        static constexpr double p = 0.85;
};


