#include "mat.h"

template<typename T>
Mat<T> matMulSimpleImpl(const Mat<T> &left, const Mat<T> &right) {
    Mat<T> result(right.nCols(), left.nRows());
    for (size_t i = 0; i != left.nRows(); ++i) {
        for (size_t j = 0; j != right.nCols(); ++j) {
            for (size_t k = 0; k != left.nCols(); ++k) {
                result[i * right.step() + j] += left[i * left.step() + k] * right[k * right.step() + j];
            }
        }
    }
    return result;
}

template<typename T>
Mat<T> matMulImpl(const Mat<T> &left, const Mat<T> &right) {
    return matMulSimpleImpl(left, right);
}

template
Mat<float> matMulImpl(const Mat<float> &left, const Mat<float> &right);

template
Mat<double> matMulImpl(const Mat<double> &left, const Mat<double> &right);

template
Mat<int> matMulImpl(const Mat<int> &left, const Mat<int> &right);