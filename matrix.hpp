//
// Created by Harmanbir Dhillon on 2018-10-01.
//

#pragma once

#include <cstdio>

class matrix {
    public:
        matrix();
        matrix(int n);
        matrix(int r, int c);
        void set_value(int row, int column, double value);
        double get_value(int row, int column) const;
        void clear();
        ~matrix();

    private:
        int m_width;
        int m_length;
        double * matrix_array;
        size_t index(int x, int y) const;
};


