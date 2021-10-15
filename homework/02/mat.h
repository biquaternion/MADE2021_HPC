#ifndef HW1_MAT_H
#define HW1_MAT_H

#include <stdio.h>
#include <string>


template<typename T>
class Mat {
public:
    Mat(size_t nCols, size_t nRows, size_t step = 0);

    Mat(T *data, size_t nCols, size_t nRows, size_t step = 0);

    ~Mat();

    void init();

    void release();

    Mat operator*(const Mat &other);

    Mat getSubMat(size_t left, size_t top, size_t nCols, size_t nRows);

    void fillRandom();

    T operator[](size_t i) const;

    T &operator[](size_t i);

    Mat &operator=(const Mat<T> &other);

    Mat operator+(const Mat<T> &other);

    Mat operator-(const Mat<T> &other);

    T *data() const { return _data; }

    size_t nCols() const { return _nCols; }

    size_t nRows() const { return _nRows; }

    size_t step() const { return _step; }

private:
    T *_data;
    size_t _nCols;
    size_t _nRows;

    size_t _step;

    void fillConst(T value);

};

template<typename T>
void saveToCsv(const Mat<T>& mat, const std::string &filename);

#endif //HW1_MAT_H
