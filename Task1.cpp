#include <iostream>
#include <vector>
#include <stdexcept>

template<typename T, size_t Rows, size_t Cols>
class Matrix {
    static_assert(Rows > 0 && Cols > 0, "Rows and Cols must be greater than 0.");

public:
    Matrix() : data(Rows, std::vector<T>(Cols)) {}

    // Matrix transpose
    Matrix<Cols, Rows> Transpose() const {
        Matrix<Cols, Rows> result;
        for (size_t i = 0; i < Rows; ++i) {
            for (size_t j = 0; j < Cols; ++j) {
                result(j, i) = data[i][j];
            }
        }
        return result;
    }

    // Matrix element access
    T& operator()(size_t row, size_t col) {
        if (row >= Rows || col >= Cols) {
            throw std::out_of_range("Matrix indices out of range");
        }
        return data[row][col];
    }

    const T& operator()(size_t row, size_t col) const {
        if (row >= Rows || col >= Cols) {
            throw std::out_of_range("Matrix indices out of range");
        }
        return data[row][col];
    }

    // Matrix arithmetic operations
    template<size_t R, size_t C>
    Matrix<T, Rows, C> operator*(const Matrix<T, R, C>& other) const {
        static_assert(Cols == R, "Invalid matrix dimensions for multiplication");
        Matrix<T, Rows, C> result;
        for (size_t i = 0; i < Rows; ++i) {
            for (size_t j = 0; j < C; ++j) {
                for (size_t k = 0; k < Cols; ++k) {
                    result(i, j) += data[i][k] * other(k, j);
                }
            }
        }
        return result;
    }

    Matrix<T, Rows, Cols> operator+(const Matrix<T, Rows, Cols>& other) const {
        Matrix<T, Rows, Cols> result;
        for (size_t i = 0; i < Rows; ++i) {
            for (size_t j = 0; j < Cols; ++j) {
                result(i, j) = data[i][j] + other(i, j);
            }
        }
        return result;
    }

    Matrix<T, Rows, Cols> operator-(const Matrix<T, Rows, Cols>& other) const {
        Matrix<T, Rows, Cols> result;
        for (size_t i = 0; i < Rows; ++i) {
            for (size_t j = 0; j < Cols; ++j) {
                result(i, j) = data[i][j] - other(i, j);
            }
        }
        return result;
    }

    // Scalar multiplication
    Matrix<T, Rows, Cols> operator*(const T& scalar) const {
        Matrix<T, Rows, Cols> result;
        for (size_t i = 0; i < Rows; ++i) {
            for (size_t j = 0; j < Cols; ++j) {
                result(i, j) = data[i][j] * scalar;
            }
        }
        return result;
    }

private:
    std::vector<std::vector<T>> data;
};

// Specialization for vector (n,1) with 'int' type
template<size_t N>
class Matrix<int, N, 1> {
    static_assert(N > 0, "N must be greater than 0.");

public:
    Matrix() : data(N, 0) {}

    int& operator()(size_t index) {
        if (index >= N) {
            throw std::out_of_range("Matrix index out of range");
        }
        return data[index];
    }

    const int& operator()(size_t index) const {
        if (index >= N) {
            throw std::out_of_range("Matrix index out of range");
        }
        return data[index];
    }

    // Vector norm (L2 norm)
    double Norm() const {
        double sum = 0.0;
        for (size_t i = 0; i < N; ++i) {
            sum += data[i] * data[i];
        }
        return std::sqrt(sum);
    }

private:
    std::vector<int> data;
};

int main() {
    // Example usage
    Matrix<int, 2, 3> A;
    A(0, 0) = 1; A(0, 1) = 2; A(0, 2) = 3;
    A(1, 0) = 4; A(1, 1) = 5; A(1, 2) = 6;

    Matrix<int, 3, 2> B;
    B(0, 0) = 1; B(0, 1) = 2;
    B(1, 0) = 3; B(1, 1) = 4;
    B(2, 0) = 5; B(2, 1) = 6;

    Matrix<int, 2, 2> C = A * B;

    std::cout << "Result of matrix multiplication:" << std::endl;
    for (size_t i = 0; i < 2; ++i) {
        for (size_t j = 0; j < 2; ++j) {
            std::cout << C(i, j) << " ";
        }
        std::cout << std::endl;
    }

    Matrix<int, 3, 1> vector;
    vector(0) = 1; vector(1) = 2; vector(2) = 3;
    std::cout << "Norm of the vector: " << vector.Norm() << std::endl;

    return 0;
}
