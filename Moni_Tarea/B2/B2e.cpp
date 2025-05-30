#include <iostream>
#include <stdexcept>

template<typename T>
T maxValue(const T* arr, int n) {
    if (n <= 0) throw std::invalid_argument("Arreglo vacío");
    T max = arr[0];
    for (int i = 1; i < n; ++i) {
        if (arr[i] > max) {
            max = arr[i];
        }
    }
    return max;
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

    const double* data() const {
        return data_;
    }

    int size() const {
        return rows_ * cols_;
    }
};

int main() {
    MatrixOp M(3, 3);

    M.set(0, 0, 1.5);  M.set(0, 1, 42.5); M.set(0, 2, -7);
    M.set(1, 0, 0);    M.set(1, 1, 5.2);  M.set(1, 2, 12.1);
    M.set(2, 0, -3.3); M.set(2, 1, 8);    M.set(2, 2, 4.4);

    double maxElem = maxValue<double>(M.data(), M.size());
    std::cout << "Máximo elemento de M: " << maxElem << "\n";

    return 0;
}
