#include <iostream>
#include <iomanip>
#include <vector>
#include <cassert>
#include <cstdlib>
#include <ctime>
#include <algorithm>

double random_double() {
    return (double) rand() / (double) RAND_MAX;
}

double rand_range(int low, int high) {
    return low + (high - low) * random_double();
}

class Matrix {
private:
    std::vector<double> entries;

public:
    size_t rows;
    size_t cols;
    explicit Matrix(size_t rows, size_t cols) : rows(rows), 
                                                cols(cols), 
                                                entries(std::vector<double>(rows * cols)) {
        assert(rows > 0 && cols > 0);
    }

    double at(size_t i, size_t j) const {
        return entries[cols * i + j];
    }

    void set(size_t i, size_t j, double val) {
        entries[cols * i + j] = val;
    }

    void transpose() {
        std::vector<double> newEntries(rows * cols);

        for (size_t i = 0; i < cols; i++) {
            for (size_t j = 0; j < rows; j++) {
                newEntries.at(rows * i + j) = at(j, i);
            }
        }

        entries = newEntries;

        std::swap(rows, cols);
    }

    void initializeEntries(int low, int high) {
        srand(time(nullptr));
        for (size_t i = 0; i < rows; i++) {
            for(size_t j = 0; j < cols; j++) {
                set(i, j, rand_range(low, high));
            }
        }
    }

    Matrix operator+ (const Matrix& mat) {
        assert(rows == mat.rows);
        assert(cols == mat.cols);

        Matrix ret(mat.rows, mat.cols);
        for (size_t i = 0; i < rows; i++) {
            for (size_t j = 0; j < cols; j++) {
                ret.set(i, j, at(i, j) + mat.at(i, j));
            }
        }

        return ret;
    }

    Matrix operator- (const Matrix& mat) {
        assert(rows == mat.rows);
        assert(cols == mat.cols);

        Matrix ret(mat.rows, mat.cols);
        for (size_t i = 0; i < rows; i++) {
            for (size_t j = 0; j < cols; j++) {
                ret.set(i, j, at(i, j) - mat.at(i, j));
            }
        }

        return ret;
    }

    void addInPlace(const Matrix& mat) {
        assert(rows == mat.rows);
        assert(cols == mat.cols);
        for (size_t i = 0; i < rows; i++) {
            for (size_t j = 0; j < cols; j++) {
                set(i, j, at(i, j) + mat.at(i, j));
            }
        }
    }

    void subtractInPlace(const Matrix& mat) {
        assert(rows == mat.rows);
        assert(cols == mat.cols);
        for (size_t i = 0; i < rows; i++) {
            for (size_t j = 0; j < cols; j++) {
                set(i, j, at(i, j) - mat.at(i, j));
            }
        }
    }

    void scalarMultiply(const double& d) {
        for (size_t i = 0; i < rows; i++) {
            for (size_t j = 0; j < cols; j++) {
                set(i, j, at(i, j) * d);
            }
        }
    }

    Matrix operator* (const Matrix& mat) {
        assert(cols == mat.rows);
        Matrix ret(rows, mat.cols);

        size_t n = cols;

        for (size_t i = 0; i < ret.rows; i++) {
            for (size_t j = 0; j < ret.cols; j++) {
                double aggregate = 0.0;
                for (size_t k = 0; k < n; k++) {
                    aggregate += at(i, k) * mat.at(k, j);
                }
                ret.set(i, j, aggregate);
            }
        }

        return ret;
    }

    void print() {
        for (size_t i = 0; i < rows; i++) {
            for (size_t j = 0; j < cols; j++) {
                std::cout << std::fixed << std::setprecision(6) << at(i, j) << '\t';
            }
            std::cout << "\n";
        }
    }
};

int main() {
    Matrix matrix1(1, 2);
    matrix1.initializeEntries(0, 4);

    Matrix matrix2(2, 2);
    matrix2.initializeEntries(5, 9);

    Matrix result = matrix1 * matrix2;

    matrix1.print();
    std::cout << "------------------------------------------------------------\n";
    matrix2.print();
    std::cout << "------------------------------------------------------------\n";

    result.print();
    return 0;
}