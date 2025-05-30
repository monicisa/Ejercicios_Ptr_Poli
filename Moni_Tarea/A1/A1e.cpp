/**
 * @file A1
 * @brief Apuntador 1
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
};

int main() {
    try {
        MatrixOp mat(3, 4); 

        mat.set(1, 2, 5.5); 
        std::cout << "Valor en (1,2): " << mat.get(1, 2) << std::endl;

        
        mat.set(5, 1, 3.3);
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    return 0;
}