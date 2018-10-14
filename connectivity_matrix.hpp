//
// Created by Harmanbir Dhillon on 2018-10-09.
//
#include "matrix.hpp"
#include <iostream>

#pragma once

constexpr double p{0.85};

class connectivity_matrix : public matrix {
    public:
        connectivity_matrix();
        connectivity_matrix(const double * matrix_array, const int size);
        matrix stochastic();
        matrix transition(const matrix stochastic);
        void markov_process(const matrix transition);
};


