/**
 * @file A4
 * @brief Apuntador 4
 * @date 2025-05-20
 * @author Mónica Torres
 */

#include <iostream>
#include <stdexcept>

class MatrixOp {
private:
    int rows_;
    int cols_;
    double* data_;

public:
    MatrixOp(int rows, int cols)
        : rows_(rows), cols_(cols) {
        if (rows <= 0 || cols <= 0) {
            throw std::invalid_argument("Dimensiones inválidas");
        }
        data_ = new double[rows_ * cols_]{0};
    }

    ~MatrixOp() {
        delete[] data_;
    }

    void set(int i, int j, double v) {
        if (i < 0 || i >= rows_ || j < 0 || j >= cols_) {
            throw std::out_of_range("Índice fuera de rango");
        }
        int k = i * cols_ + j;
        data_[k] = v;
    }

    double get(int i, int j) const {
        if (i < 0 || i >= rows_ || j < 0 || j >= cols_) {
            throw std::out_of_range("Índice fuera de rango");
        }
        int k = i * cols_ + j;
        return data_[k];
    }

    MatrixOp operator+(const MatrixOp& other) const {
        if (rows_ != other.rows_ || cols_ != other.cols_) {
            throw std::invalid_argument("Dimensiones incompatibles");
        }
        MatrixOp result(rows_, cols_);
        for (int k = 0; k < rows_ * cols_; ++k) {
            result.data_[k] = this->data_[k] + other.data_[k];
        }
        return result;
    }

    MatrixOp operator-(const MatrixOp& other) const {
        if (rows_ != other.rows_ || cols_ != other.cols_) {
            throw std::invalid_argument("Dimensiones incompatibles");
        }
        MatrixOp result(rows_, cols_);
        for (int k = 0; k < rows_ * cols_; ++k) {
            result.data_[k] = this->data_[k] - other.data_[k];
        }
        return result;
    }
};

int main() {
    MatrixOp A(2, 2), B(2, 2);
    A.set(0, 0, 1.0); A.set(0, 1, 2.0);
    A.set(1, 0, 3.0); A.set(1, 1, 4.0);

    B.set(0, 0, 2.0); B.set(0, 1, 3.0);
    B.set(1, 0, 4.0); B.set(1, 1, 5.0);

    MatrixOp C = A + B;
    MatrixOp D = A - B;

    std::cout << "C[0,0] = " << C.get(0, 0) << "\n";
    std::cout << "D[1,1] = " << D.get(1, 1) << "\n";

    return 0;
}
