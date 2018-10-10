//
// Created by Harmanbir Dhillon on 2018-10-01.
//

#pragma once

#include <stdexcept>
#include <math.h>
#include <cstdio>
#include <MacTypes.h>

class matrix {
    public:
        matrix();
        matrix(int n);
        matrix(int r, int c);
        matrix(double mat_array[], int capacity);
        matrix(const matrix& matrix_t);
        void set_value(int row, int column, double value);
        double get_value(int row, int column) const;
        void clear();
        ~matrix();
        friend bool operator==(const matrix& hs, const matrix& rhs);
        friend bool operator!=(const matrix& hs, const matrix& rhs);
        friend matrix operator+(matrix hs, const matrix rhs);
        friend matrix operator-(matrix hs, const matrix rhs);
        friend matrix operator*(matrix hs, const matrix rhs);
        friend void swap(matrix& first, matrix& second);
        friend std::ostream &operator<<(std::ostream &os, const matrix &matrix);
        matrix& operator++();
        matrix operator++(int);
        matrix& operator--();
        matrix operator--(int);
        matrix& operator+=(const matrix& rhs);
        matrix& operator-=(const matrix& rhs);
        matrix& operator*=(const matrix& rhs);
        matrix& operator=(matrix other);
        void multiply_constant(double value);
        void add_columns();


    private:
        int m_length;
        int m_width;
        double * matrix_array;

        bool is_perfect_square(int x) const;


    protected:
        int get_m_width() const;
        int get_m_length() const;
        inline int index(int x, int y) const;


};


