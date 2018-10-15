//
// Created by Harmanbir Dhillon on 2018-10-01.
//

#include "matrix.hpp"

// default constructor
// Sets m_length and m_width to 1
// Creates matrix_array of size 1, initialized to 0.0
matrix::matrix()
    :   m_length{1},
        m_width{1},
        matrix_array{new double[1 * 1] {0.0}}
{}

// constructor that takes an int value which is the dimension of the matrix
// sets m_length and m_width to n
// Creates matrix of size n * n, initialized to 0.0
matrix::matrix(const int n)
    :   m_length{n},
        m_width{n},
        matrix_array{new double[n * n] {0.0}}
{
    if (n <= 0)
    {
        throw std::invalid_argument("received negative or zero value");
    }
}

// constructor that takes an int value for rows and columns
// sets m_length to r and m_width to c
// Creates matrix of size r * c, initialized to 0.0
matrix::matrix(const int r, const int c)
    :   m_length{r},
        m_width{c},
        matrix_array{new double[r * c] {0.0}}
{
    if (r <= 0 || c <= 0)
    {
        throw std::invalid_argument("received negative or zero value");
    }
}

// constructor that takes an array that's size is able to be square rooted
// also takes an int that contains the size of the array
// sets m_length and m_width to square root of capacity
// creates matrix of size capacity, initialized to 0.0
matrix::matrix(const double mat_array[], const int capacity)
{

    // checks if capacity(size of mat_array) is a perfect square
    if (!is_perfect_square(capacity))
    {
        throw std::invalid_argument("array size is not a perfect square");
    }

    int size = sqrt(capacity);

    matrix_array = new double[capacity];
    m_length = size;
    m_width  = size;

    // copies mat_array into matrix_array
    for (int i = 0; i < size; ++i)
    {
        for (int j = 0; j < size; ++j)
        {
            matrix_array[index(i, j)] = mat_array[index(i, j)];
        }
    }
}

// copy constructor
// copies all variables from matrix_t to this
matrix::matrix(const matrix& matrix_t)
    :   m_length{matrix_t.m_length},
        m_width{matrix_t.m_width},
        matrix_array{new double[matrix_t.m_length * matrix_t.m_width] {}}
{
    std::copy(matrix_t.matrix_array, matrix_t.matrix_array + (m_length * m_width), matrix_array);
}

// constructor that takes an int value for rows and columns
// sets m_length to r and m_width to c
// Creates matrix of size r * c, initialized to default_value
matrix::matrix(const int r, const int c, const double default_value)
        :   m_length{r},
            m_width{c},
            matrix_array{new double[r * c] {}}
{
    if (r <= 0 || c <= 0)
    {
        throw std::invalid_argument("received negative or zero value");
    }

    std::fill_n(matrix_array, r * c, default_value);
}

// sets matrix[row, column] to value
void matrix::set_value(const int row, const int column, const double value)
{
    if(row < 0 || column < 0)
    {
        throw std::invalid_argument("row or column cannot be less than 0");
    }

    if(row >= m_length || column >= m_width)
    {
        throw std::invalid_argument("row or column index have to be in the array");
    }

    matrix_array[index(row, column)] = value;
}

// returns the value of matrix[row, column]
double matrix::get_value(const int row, const int column) const
{
    if(row < 0 || column < 0)
    {
        throw std::invalid_argument("row or column cannot be less than 0");
    }

    if(row >= m_length || column >= m_width)
    {
        throw std::invalid_argument("row or column index have to be in the array");
    }

    return matrix_array[index(row, column)];
}

// sets all elements in matrix_array to 0.0
void matrix::clear()
{
    for (int i = 0; i < m_length; i++)
    {
        for (int j = 0; j < m_width; j++)
        {
            matrix_array[index(i, j)] = 0.0;
        }
    }
}

// returns index of a 1d array from a 2d array arguments
int matrix::index(const int x, const int y) const
{
    return m_width * x + y;
}

// returns true if x is a perfect square, else false
bool matrix::is_perfect_square(const int x) const
{
    double squared = sqrt(x);

    return ((squared - floor(squared)) == 0);
}

// destructor
// deletes matrix_array which is a dynamically allocated array
matrix::~matrix()
{
        delete[] matrix_array;
}

// overloaded equality operator
// returns true if both matrices are the same size and contain the same values at each index, else false
bool operator==(const matrix& hs, const matrix& rhs)
{
    if (hs.m_width != rhs.m_width || hs.m_length != rhs.m_length)
    {
        return false;
    }

    for (int i = 0; i < hs.m_length; ++i)
    {
        for (int j = 0; j < hs.m_width; ++j)
        {
            double difference = hs.matrix_array[hs.index(i, j)] - rhs.matrix_array[hs.index(i, j)];
            if (!(difference) <= epsilon * fabs(hs.matrix_array[hs.index(i, j)]))
            {
                return false;
            }
        }
    }
    return true;
}

// overloaded equality operator
bool operator!=(const matrix& hs, const matrix& rhs)
{
    return !operator==(hs, rhs);
}

// overloaded addition operator
// adds the 2 matrices if they are the same size
matrix operator+(matrix hs, const matrix rhs)
{
    if (hs.m_length != rhs.m_length || hs.m_width != rhs.m_width)
    {
        throw std::invalid_argument("matrices have to be the same size");
    }

    matrix temp = matrix(hs);

    temp += rhs;
    return temp;
}

// overloaded minus operator
// subtracts the two matrices if they are the same size
matrix operator-(matrix hs, const matrix rhs)
{
    if (hs.m_length != rhs.m_length || hs.m_width != rhs.m_width)
    {
        throw std::invalid_argument("matrices have to be the same size");
    }

    matrix temp = matrix(hs);

    temp -= rhs;
    return temp;
}

// overloaded multiplication operator
// multiplies both matrices is number of columns in first equals number of rows in the second
matrix operator*(matrix hs, const matrix rhs)
{
    if (hs.m_width != rhs.m_length)
    {
        throw std::invalid_argument("number of columns of first matrix does not equal number of rows in second matrix");
    }

    matrix temp = matrix(hs);

    temp *= rhs;
    return temp;
}

// overloaded pre-increment operator
// increments each element by 1
matrix& matrix::operator++()
{
    for (int i = 0; i < m_length; i++)
    {
        for (int j = 0; j < m_width; j++)
        {
            matrix_array[index(i, j)] += 1.0;
        }
    }
    return *this;
}

// overloaded post-increment operator
// increments each element by 1
matrix matrix::operator++(int)
{
    matrix tmp{*this};
    operator++();
    return tmp;
}

// overloaded pre-decrement operator
// decrements each element by 1
matrix& matrix::operator--()
{
    for (int i = 0; i < m_length; i++)
    {
        for (int j = 0; j < m_width; j++)
        {
            matrix_array[index(i, j)] -= 1.0;
        }
    }
    return *this;
}

// overloaded post-decrement operator
// decrements each element by 1
matrix matrix::operator--(int)
{
    matrix tmp{*this};
    operator--();
    return tmp;
}

// overloaded += operator
// adds the 2 matrices if they are the same size
matrix& matrix::operator+=(const matrix& rhs)
{
    if (m_length != rhs.m_length || m_width != rhs.m_width)
    {
        throw std::invalid_argument("matrices have to be the same size");
    }

    for (int i = 0; i < m_length; i++)
    {
        for (int j = 0; j < m_width; j++)
        {
            this->matrix_array[index(i, j)] += rhs.matrix_array[index(i, j)];
        }
    }
    return *this;
}

// overloaded -= operator
// subtracts the 2 matrices if they are the same size
matrix& matrix::operator-=(const matrix& rhs)
{
    if (m_length != rhs.m_length || m_width != rhs.m_width)
    {
        throw std::invalid_argument("matrices have to be the same size");
    }

    for (int i = 0; i < m_length; i++)
    {
        for (int j = 0; j < m_width; j++)
        {
            this->matrix_array[index(i, j)] -= rhs.matrix_array[index(i, j)];
        }
    }
    return *this;
}

// overloaded *= operator
// multiplies both matrices is number of columns in first equals number of rows in the second
matrix& matrix::operator*=(const matrix& rhs)
{
    if (this -> m_width != rhs.m_length)
    {
        throw std::invalid_argument("number of columns of first matrix does not equal number of rows in second matrix");
    }

    auto * new_matrix = new double[this -> m_length * rhs.m_width] {0.0};

    for (int i = 0; i < this -> m_length; ++i)
    {
        for (int j = 0; j < rhs.m_width; ++j)
        {
            for (int k = 0; k < this -> m_width; ++k)
            {
                double first = this->matrix_array[index(i, k)];
                double second = rhs.matrix_array[rhs.index(k, j)];
                new_matrix[rhs.index(i, j)] += (first * second);
            }
        }
    }
    delete[] matrix_array;
    matrix_array = new double[this -> m_length * rhs.m_width];
    m_width = rhs.m_width;
    std::copy(new_matrix, new_matrix + (this -> m_length * rhs.m_width), matrix_array);
    delete[] new_matrix;
    return *this;
}

// overloaded assignment operator
matrix& matrix::operator=(matrix other)
{
    swap(*this, other);
    return *this;
}

// overloaded swap function
void swap(matrix& first, matrix& second)
{
    using std::swap;
    swap(first.m_length, second.m_length);
    swap(first.m_width, second.m_width);
    swap(first.matrix_array, second.matrix_array);
}

// overloaded insertion operator
std::ostream &operator<<(std::ostream &os, const matrix &matrix)
{
    for (int i = 0; i < matrix.m_length; ++i)
    {
        for (int j = 0; j < matrix.m_width; ++j)
        {
            os << matrix.get_value(i, j) << " ";
        }
        os << std::endl;
    }
    return os;
}

// returns m_length
int matrix::get_m_length() const
{
    return m_length;
}

// returns m_width
int matrix::get_m_width() const
{
    return m_width;
}

// multiples each element in a matrix by a single value(value passed in)
void matrix::multiply_constant(const double value)
{
    for (int i = 0; i < m_length; ++i)
    {
        for (int j = 0; j < m_width; ++j)
        {
            set_value(i, j, get_value(i, j) * value);
        }
    }
}

// adds each column in the matrix and then divides every number in the column by the sum
// if sum is 0 then sets every value in the column to 1 / n (n is the number of columns)
void matrix::add_columns()
{
    for (int i = 0; i < m_width; ++i)
    {
        double sum = 0;
        for (int j = 0; j < m_length; ++j)
        {
            sum += get_value(j, i);
        }
        if (sum == 0)
        {
            for (int j = 0; j < m_length; ++j) {
                double temp = 1.0 / m_length;
                set_value(j, i, temp);
            }
        } else {
            for (int j = 0; j < m_length; ++j) {
                double temp = get_value(j, i);
                if (temp == 0) {
                    set_value(j, i, 0.0);
                } else {
                    set_value(j, i, temp / sum);
                }
            }
        }
    }
}

// returns matrix_array
double *matrix::getMatrix_array() const {
    return matrix_array;
}

// makes every element in the matrix into a percentage out of 100
void matrix::make_percentage()
{
    for (int i = 0; i < m_length; ++i)
    {
        for (int j = 0; j < m_width; ++j)
        {
            double temp = get_value(i, j) * percentage;
            temp = roundf(temp * percentage) / percentage;
            set_value(i, j, temp);
        }
    }
}

// prints the page rank
void matrix::print_result()
{
    char current_alpha = 'A';

    for (int i = 0; i < m_length; ++i)
    {
        for (int j = 0; j < m_width; ++j)
        {
            std::cout << "Page " << current_alpha++ << ": " << std::setw(5) << std::fixed << std::setprecision(2) << get_value(i, j) << "%\n";
        }
    }
}
