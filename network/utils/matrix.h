#ifndef MATRIX_H
#define MATRIX_H

#include <sstream>

template <typename T>
class Matrix
{
private:
    unsigned int m, n, size;
    T *data = nullptr;

public:
    Matrix() {}

    Matrix(const Matrix &other) : m(other.get_m()), n(other.get_n())
    {
        size = m * n;
        data = new T[m * n];
        const T *_data = other.get_data();
        for (unsigned int i = 0; i < size; i++)
            data[i] = _data[i];
    }

    Matrix(int _m, int _n) : m(_m), n(_n)
    {
        if (data != nullptr)
            delete[] data;

        size = m * n;
        data = new T[m * n];
    }

    Matrix(int _m, int _n, std::vector<T> _data) : m(_m), n(_n)
    {
        size = m * n;
        if (size != _data.size())
            throw std::invalid_argument("Matrix instanciated with wrong size datas");
        data = new T[m * n];
        for (unsigned int i = 0; i < _data.size(); i++)
        {
            data[i] = _data[i];
        }
    }

    ~Matrix()
    {
        delete[] data;
    }

    void randomise(T min, T max)
    {
        for (unsigned int i = 0; i < size; i++)
        {
            data[i] = (float)rand() / (float)RAND_MAX * (max - min) + min;
        }
    }

    inline unsigned int get_m() const { return m; }
    inline unsigned int get_n() const { return n; }
    inline const T *get_data() const { return data; }

    // Multiply right
    static Matrix *product(Matrix *A, Matrix *B);
    static Matrix product(Matrix &A, Matrix &B);

    void print(std::stringstream &ss)
    {
        for (unsigned int i = 0; i < size; i++)
        {
            ss << round(data[i] * 1000) / 1000;
            ss << ((i % n == n - 1) ? '\n' : ' ');
        }
    }

    void print()
    {
        for (unsigned int i = 0; i < size; i++)
        {
            printf("%f %c", round(data[i] * 1000) / 1000, ((i % n == n - 1) ? '\n' : ' '));
        }
    }

    Matrix transposed()
    {
        Matrix mat(n, m);
        for (unsigned int i = 0; i < n; i++)
        {
            for (unsigned int j = 0; j < m; j++)
            {
                mat(i, j) = (*this)(j, i);
            }
        }
        return mat;
    }
    // Affect operator
    Matrix &operator=(const Matrix &other);
    // Accesses operators
    T &operator()(int i, int j);
    T operator()(int i, int j) const;

    //Term by term operators
    Matrix<T> operator+(Matrix &other);
    Matrix<T> operator-(Matrix &other);
    Matrix<T> operator*(Matrix &other);
    Matrix<T> operator/(Matrix &other);

    Matrix<T> operator*(T other);

    // Matrix multiplication
    Matrix<T> operator%(Matrix &other);

    Matrix<T> cyclic_apply(Matrix &other, T (*operation)(T, T));
    Matrix<T> total_apply(T value, T (*operation)(T, T));
};

template <typename T>
Matrix<T> Matrix<T>::cyclic_apply(Matrix &other, T (*operation)(T, T))
{
    unsigned int m = (*this).get_m();
    unsigned int n = (*this).get_n();
    unsigned int m_ = other.get_m();
    unsigned int n_ = other.get_n();

    Matrix<T> mat(m, n);

    for (unsigned int i = 0; i < m; i++)
    {
        for (unsigned int j = 0; j < n; j++)
        {
            mat(i, j) = operation((*this)(i, j), other(i % m_, j % n_));
        }
    }
    return mat;
}

template <typename T>
Matrix<T> Matrix<T>::total_apply(T value, T (*operation)(T, T))
{
    unsigned int m = (*this).get_m();
    unsigned int n = (*this).get_n();
    Matrix<T> mat(m, n);

    for (unsigned int i = 0; i < m; i++)
    {
        for (unsigned int j = 0; j < n; j++)
        {
            mat(i, j) = operation((*this)(i, j), value);
        }
    }

    return mat;
}

template <typename T>
Matrix<T> &Matrix<T>::operator=(const Matrix<T> &other)
{
    if (this != &other)
    {
        m = other.get_m();
        n = other.get_n();
        size = m * n;
        data = new T[m * n];
        const T *_data = other.get_data();
        for (unsigned int i = 0; i < size; i++)
            data[i] = _data[i];
    }
    return *this;
}

template <typename T>
Matrix<T> Matrix<T>::operator+(Matrix &other)
{
    return cyclic_apply(other, [](T a, T b) -> T { return a + b; });
}

template <typename T>
Matrix<T> Matrix<T>::operator-(Matrix &other)
{
    return cyclic_apply(other, [](T a, T b) -> T { return a - b; });
}

template <typename T>
Matrix<T> Matrix<T>::operator/(Matrix &other)
{
    return cyclic_apply(other, [](T a, T b) -> T { return a / b; });
}

template <typename T>
Matrix<T> Matrix<T>::operator*(Matrix &other)
{
    return cyclic_apply(other, [](T a, T b) -> T { return a * b; });
}

template <typename T>
Matrix<T> Matrix<T>::operator*(T value)
{
    return total_apply(value, [](T a, T b) -> T { return a * b; });
}

template <typename T>
Matrix<T> Matrix<T>::operator%(Matrix &other)
{
    return Matrix<T>::product(*this, other);
}

template <typename T>
T &Matrix<T>::operator()(int i, int j)
{
    return data[i * n + j];
}

template <typename T>
T Matrix<T>::operator()(int i, int j) const
{
    return data[i * n + j];
}

template <typename T>
Matrix<T> Matrix<T>::product(Matrix<T> &A, Matrix<T> &B)
{
    unsigned int m = A.get_m();
    unsigned int n = B.get_n();
    unsigned int m_ = B.get_m();
    unsigned int n_ = A.get_n();

    if (m_ != n_)
    {
        throw std::invalid_argument("Matrix multiplication with wrong shapes");
    }

    Matrix<T> mat(m, n);

    for (unsigned int i = 0; i < m; i++)
    {
        for (unsigned int j = 0; j < n; j++)
        {
            mat(i, j) = 0;
            for (unsigned int k = 0; k < m_; k++)
            {
                mat(i, j) += A(i, k) * B(k, j);
            }
        }
    }

    return mat;
}
#endif