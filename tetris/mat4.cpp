#include "include/mat4.h"

Mat4::Mat4() : _array(4, std::vector<char> (4)) {
    for(int i=0; i<4; i++)
        for(int j=0; j<4; j++)
            _array[i][j] = ' ';
}

Mat4::~Mat4() {
    for(int i=0; i<4; i++)
        delete[] &_array[i];
    delete[] &_array;
}

Mat4::Mat4(const char2d format) : _array(4, std::vector<char> (4)) {
    for(int i=0; i<4; i++)
        for(int j=0; j<4; j++)
            this->_array[i][j] = format[i][j];
}

Mat4::Mat4(const char c) : _array(4, std::vector<char> (4)) {
    for(int i=0; i<4; i++)
        for(int j=0; j<4; j++)
            this->_array[i][j] = c;
}

Mat4& Mat4::operator=(const Mat4& other) {
    for(int i=0; i<4; i++)
        for(int j=0; j<4; j++)
            this->_array[i][j] = other._array[i][j];
    
    return *this;
}

Mat4& Mat4::operator=(const char2d other) {
    for(int i=0; i<4; i++)
        for(int j=0; j<4; j++)
            this->_array[i][j] = other[i][j];

    return *this;
}

void Mat4::print() {
    for(int i=0; i<4; i++) {
        for(int j=0; j<4; j++)
            std::cout << _array[i][j];
        std::cout << std::endl;
    }
}

void Mat4::setChar(const char c) {
    for(int i=0; i<4; i++)
        for(int j=0; j<4; j++)
            if(_array[i][j] != BG_CHAR)
                _array[i][j] = c;
}

/*
A B C D
E F G H
I J K L
M N O P
-------
M I E A
N J F B
O K G C
P L H D

var temp = a[i][j];
                a[i][j] = a[N - 1 - j][i];
                a[N - 1 - j][i] = a[N - 1 - i][N - 1 - j];
                a[N - 1 - i][N - 1 - j] = a[j][N - 1 - i];
                a[j][N - 1 - i] = temp;
*/

void Mat4::rotate90() {
    const int N = 4; //size
    for(int i=0; i<N/2; i++) {
        for(int j=i; j<N-i-1; j++) {
            char tmp = _array[i][j];
            _array[        i][        j] = _array[N - 1 - j][        i];
            _array[N - 1 - j][        i] = _array[N - 1 - i][N - 1 - j];
            _array[N - 1 - i][N - 1 - j] = _array[        j][N - 1 - i];
            _array[        j][N - 1 - i] = tmp;
        }
    }
}