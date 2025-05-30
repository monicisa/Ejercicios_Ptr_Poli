/**
 * @file A4
 * @brief Apuntador 4
 * @date 2025-05-20
 * @author Mónica Torres
 */

 #include <iostream>
#include <stdexcept>

using OpFunc = double(*)(double, double);

double sub(double a, double b) {
    return a - b;
}

double mul(double a, double b) {
    return a * b;
}

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
            throw std::out_of_range("Índices fuera de rango");
        }
        int k = i * cols_ + j;
        data_[k] = v;
    }

    double get(int i, int j) const {
        if (i < 0 || i >= rows_ || j < 0 || j >= cols_) {
            throw std::out_of_range("Índices fuera de rango");
        }
        int k = i * cols_ + j;
        return data_[k];
    }

    void add(const MatrixOp* other, MatrixOp* result) const {
        if (rows_ != other->rows_ || cols_ != other->cols_ ||
            rows_ != result->rows_ || cols_ != result->cols_) {
            throw std::invalid_argument("Dimensiones incompatibles");
        }
        for (int k = 0; k < rows_ * cols_; ++k) {
            result->data_[k] = this->data_[k] + other->data_[k];
        }
    }

    void apply(const MatrixOp* A, const MatrixOp* B, MatrixOp* out, OpFunc op) const {
        if (A->rows_ != B->rows_ || A->cols_ != B->cols_ ||
            A->rows_ != out->rows_ || A->cols_ != out->cols_) {
            throw std::invalid_argument("Dimensiones incompatibles");
        }
        for (int k = 0; k < A->rows_ * A->cols_; ++k) {
            out->data_[k] = op(A->data_[k], B->data_[k]);
        }
    }

    void print() const {
        for (int i = 0; i < rows_; ++i) {
            for (int j = 0; j < cols_; ++j) {
                std::cout << get(i, j) << " ";
            }
            std::cout << std::endl;
        }
    }

    void printAt(int i, int j) const {
        std::cout << get(i, j) << " ";
    }

    void forEachDiagonal(void (MatrixOp::*fn)(int, int)) const {
        int n = (rows_ < cols_) ? rows_ : cols_;
        for (int i = 0; i < n; ++i) {
            (this->*fn)(i, i);
        }
        std::cout << std::endl;
    }
};

int main() {
    try {
        MatrixOp A(2, 3);
        MatrixOp B(2, 3);
        MatrixOp C(2, 3);
        MatrixOp D(2, 3);

        A.set(0, 0, 1); A.set(0, 1, 2); A.set(0, 2, 3);
        A.set(1, 0, 4); A.set(1, 1, 5); A.set(1, 2, 6);

        B.set(0, 0, 10); B.set(0, 1, 20); B.set(0, 2, 30);
        B.set(1, 0, 40); B.set(1, 1, 50); B.set(1, 2, 60);

        A.add(&B, &C);
        std::cout << "A + B:" << std::endl;
        C.print();

        A.apply(&A, &B, &C, sub);
        std::cout << "A - B:" << std::endl;
        C.print();

        A.apply(&A, &B, &D, mul);
        std::cout << "A * B:" << std::endl;
        D.print();

        MatrixOp M(3, 3);
        M.set(0, 0, 11); M.set(0, 1, 12); M.set(0, 2, 13);
        M.set(1, 0, 21); M.set(1, 1, 22); M.set(1, 2, 23);
        M.set(2, 0, 31); M.set(2, 1, 32); M.set(2, 2, 33);

        std::cout << "Diagonal de M:" << std::endl;
        M.forEachDiagonal(&MatrixOp::printAt);

    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    return 0;
}
