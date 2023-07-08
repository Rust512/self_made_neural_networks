#include <iostream>
#include <iomanip>
#include <vector>
#include <cassert>
#include <cstdlib>
#include <ctime>

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

    double& at(size_t i, size_t j) {
        return entries.at(cols * i + j);
    }

    void initializeEntries(int low, int high) {
        srand(time(nullptr));
        for (size_t i = 0; i < rows; i++) {
            for(size_t j = 0; j < cols; j++) {
                at(i, j) = rand_range(low, high);
            }
        }
    }

    Matrix operator+ (Matrix mat) {
        assert(rows == mat.rows);
        assert(cols == mat.cols);

        Matrix ret(mat.rows, mat.cols);
        for (size_t i = 0; i < rows; i++) {
            for (size_t j = 0; j < cols; j++) {
                ret.at(i, j) = at(i, j) + mat.at(i, j);
            }
        }

        return ret;
    }

    void operator+= (Matrix mat) {
        assert(rows == mat.rows);
        assert(cols == mat.cols);
        for (size_t i = 0; i < rows; i++) {
            for (size_t j = 0; j < cols; j++) {
                at(i, j) = at(i, j) + mat.at(i, j);
            }
        }
    }

    void print() {
        for (size_t i = 0; i < rows; i++) {
            for (size_t j = 0; j < cols; j++) {
                std::cout << std::setprecision(12) << at(i, j) << '\t';
            }
            std::cout << '\n';
        }
    }
};

int main() {
    Matrix matrix1(5, 3);
    matrix1.initializeEntries(0, 4);

    Matrix matrix2(5, 3);
    matrix2.initializeEntries(2, 3);

    Matrix sum = matrix1 + matrix2;

    std::cout << "---------------------------------\n";
    matrix1.print();
    std::cout << "---------------------------------\n";
    matrix2.print();
    std::cout << "---------------------------------\n";
    sum.print();

    matrix1 += matrix2;
    std::cout << "---------------------------------\n";
    matrix1.print();
    return 0;
}