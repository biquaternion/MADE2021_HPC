#include <cstring>
#include <cstdlib>
#include <string>
#include <fstream>
#include "mat.h"
#include "matmul.h"

template<typename T>
Mat<T>::Mat(size_t nCols,
            size_t nRows,
            size_t step) :
        _nCols(nCols),
        _nRows(nRows),
        _data(nullptr),
        _step(step) {
    init();
}

template<typename T>
void Mat<T>::init() {
    release();
    _data = new T[_nCols * _nRows];
    memset(_data, _nCols * _nRows * sizeof(T), 0);
    if (_step == 0) {
        _step = _nCols;
    }
}

template<typename T>
void Mat<T>::release() {
    if (_data != nullptr) {
        delete[] _data;
    }
}

template<typename T>
void Mat<T>::fillRandom() {
    static unsigned int seedp = 42;
    for (size_t i = 0; i != _nCols * _nRows; ++i) {
        _data[i] = static_cast<T>(rand_r(&seedp)) / static_cast<T>(RAND_MAX);
    }
}

template<typename T>
void Mat<T>::fillConst(T value) {
    for (size_t i = 0; i != _nCols * _nRows; ++i) {
        _data[i] = value;
    }
}

template<typename T>
Mat<T> Mat<T>::operator*(const Mat<T> &other) {
    return matMulImpl(*this, other);
}

template<typename T>
T Mat<T>::operator[](size_t i) const {
    //todo: check boundaries
    return _data[i];
}

template<typename T>
T &Mat<T>::operator[](size_t i) {
    // todo: check boundaries
    return _data[i];
}

template<typename T>
Mat<T>::Mat(T *data, size_t nCols, size_t nRows, size_t step) :
        _data(data),
        _nCols(nCols),
        _nRows(nRows),
        _step(step) {
    // todo: check boundaries
    if (_step == 0) {
        _step = _nCols;
    }
}

template<typename T>
Mat<T>::~Mat() {
    release();
}

template<typename T>
Mat<T> Mat<T>::getSubMat(size_t left, size_t top, size_t nCols, size_t nRows) {
    // todo: check boundaries
    return Mat<T>(&(_data[top * _step + left]), nCols, nRows, _step);
}

template<typename T>
void saveToCsv(const Mat<T> &mat, const std::string &filename) {
    std::ofstream ofs(filename, std::ios::trunc);
    ofs.flush();
    T *pItem = &(mat.data()[0]);
    for (size_t i = 0; i != mat.nRows(); ++i) {
        for (size_t j = 0; j != mat.nCols(); ++j) {
            ofs << *pItem;
            if (j != mat.nCols() - 1) {
                ofs << ',';
            }
            pItem++;
        }
        if (i != mat.nRows() - 1) {
            ofs << '\n';
        }
    }
    ofs.close();
}

template
class Mat<float>;

template
class Mat<double>;

template
class Mat<int>;

template
void saveToCsv<float>(const Mat<float> &mat, const std::string &filename);

template
void saveToCsv<double>(const Mat<double> &mat, const std::string &filename);

template
void saveToCsv<int>(const Mat<int> &mat, const std::string &filename);