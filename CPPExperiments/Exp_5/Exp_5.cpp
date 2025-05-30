#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <iomanip> 
#include <exception>
#include <stdexcept>
#include <typeinfo>
#include <string>
#include <cstring>

using namespace std;

template <typename T>
class MAT {
    T* e;          // 指向矩阵元素
    int r, c;      // 矩阵行列数

public:
    MAT(int rows, int cols) : e(new T[rows * cols]()), r(rows), c(cols) {}

    MAT(const MAT& a) : e(new T[a.r * a.c]), r(a.r), c(a.c) {
        std::copy(a.e, a.e + r * c, e);
    }

    MAT(MAT&& a) noexcept : e(a.e), r(a.r), c(a.c) {
        a.e = nullptr; a.r = 0; a.c = 0;
    }

    ~MAT() noexcept {
        delete[] e;
    }

    MAT& operator=(const MAT& a) {
        if (this == &a) return *this;
        delete[] e;
        r = a.r; c = a.c;
        e = new T[r * c];
        std::copy(a.e, a.e + r * c, e);
        return *this;
    }

    MAT& operator=(MAT&& a) noexcept {
        if (this == &a) return *this;
        delete[] e;
        e = a.e; r = a.r; c = a.c;
        a.e = nullptr; a.r = 0; a.c = 0;
        return *this;
    }

    T* operator[](int row) {
        if (row < 0 || row >= r) throw std::out_of_range("Row index out of range");
        return e + row * c;
    }

    const T* operator[](int row) const {
        if (row < 0 || row >= r) throw std::out_of_range("Row index out of range");
        return e + row * c;
    }

    MAT operator+(const MAT& a) const {
        if (r != a.r || c != a.c) throw std::invalid_argument("Dimension mismatch for addition");
        MAT res(r, c);
        for (int i = 0; i < r * c; ++i)
            res.e[i] = e[i] + a.e[i];
        return res;
    }

    MAT operator-(const MAT& a) const {
        if (r != a.r || c != a.c) throw std::invalid_argument("Dimension mismatch for subtraction");
        MAT res(r, c);
        for (int i = 0; i < r * c; ++i)
            res.e[i] = e[i] - a.e[i];
        return res;
    }

    MAT operator*(const MAT& a) const {
        if (c != a.r) throw std::invalid_argument("Dimension mismatch for multiplication");
        MAT res(r, a.c);
        for (int i = 0; i < r; ++i)
            for (int j = 0; j < a.c; ++j)
                for (int k = 0; k < c; ++k)
                    res.e[i * a.c + j] += e[i * c + k] * a.e[k * a.c + j];
        return res;
    }

    MAT& operator+=(const MAT& a) {
        if (r != a.r || c != a.c) throw std::invalid_argument("Dimension mismatch for addition");
        for (int i = 0; i < r * c; ++i)
            e[i] += a.e[i];
        return *this;
    }

    MAT& operator-=(const MAT& a) {
        if (r != a.r || c != a.c) throw std::invalid_argument("Dimension mismatch for subtraction");
        for (int i = 0; i < r * c; ++i)
            e[i] -= a.e[i];
        return *this;
    }

    MAT operator~() const { // 转置
        MAT res(c, r);
        for (int i = 0; i < r; ++i)
            for (int j = 0; j < c; ++j)
                res.e[j * r + i] = e[i * c + j];
        return res;
    }

    void print() const {
        for (int i = 0; i < r; ++i) {
            for (int j = 0; j < c; ++j)
                std::cout << std::setw(6) << e[i * c + j] << " ";
            std::cout << "\n";
        }
    }
};

template class MAT<int>;
template class MAT<long long>;

int main() {
    try {
        MAT<int> a(1, 2), b(2, 2);
        a[0][0] = 1; a[0][1] = 2;
        b[0][0] = 3; b[0][1] = 4;
        b[1][0] = 5; b[1][1] = 6;

        std::cout << "Matrix A:\n"; a.print();
        std::cout << "Matrix B:\n"; b.print();

        auto c = a * b;
        std::cout << "A * B:\n"; c.print();

        std::cout << "A + A:\n"; (a + a).print();

        c = c - a;
        std::cout << "C - A:\n"; c.print();

        c += a;
        std::cout << "C += A:\n"; c.print();

        std::cout << "Transpose of A:\n"; (~a).print();
    }
    catch (const std::exception& e) {
        std::cerr << "Exception: " << e.what() << "\n";
    }
    return 0;
}
