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

class IMatrix {
public:
    virtual ~IMatrix() = default;
    virtual double determinant() const = 0;
};

class MatrixOp : public IMatrix {
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

    double determinant() const override {
        if (rows_ == 2 && cols_ == 2) {
            return get(0,0)*get(1,1) - get(0,1)*get(1,0);
        }
        if (rows_ == 3 && cols_ == 3) {
            return get(0,0)*(get(1,1)*get(2,2) - get(1,2)*get(2,1))
                 - get(0,1)*(get(1,0)*get(2,2) - get(1,2)*get(2,0))
                 + get(0,2)*(get(1,0)*get(2,1) - get(1,1)*get(2,0));
        }
        throw std::logic_error("Implementar para 2x2 o 3x3");
    }
};

int main() {
    IMatrix* mat = new MatrixOp(2, 2);
    MatrixOp* m = dynamic_cast<MatrixOp*>(mat);
    m->set(0, 0, 1);
    m->set(0, 1, 2);
    m->set(1, 0, 3);
    m->set(1, 1, 4);
    std::cout << "Determinante: " << mat->determinant() << "\n";
    delete mat;

    return 0;
}
