#ifndef _MAT_4_H
#define _MAT_4_H

#include <iostream>
#include <vector>

typedef std::vector<std::vector<char>> char2d;

const char MOV_CHAR = '#';
const char SOL_CHAR = '@';
const char BG_CHAR  = '.';

class Mat4 {
private:
    char2d _array;
    // char2d _array = {
    //     {' ', ' ', ' ', ' '},
    //     {' ', ' ', ' ', ' '},
    //     {' ', ' ', ' ', ' '},
    //     {' ', ' ', ' ', ' '}
    // };
    //char2d _array(4, std::vector<char>(4, ' '));

public:
    Mat4();
    ~Mat4();
    Mat4(const char2d format);
    Mat4(const char c);
    Mat4& operator=(const char2d other);
    Mat4& operator=(const Mat4& other);

    void print();
    void setChar(const char c);
    void rotate90();

    //static inline Mat4& from(const char format[4][4]) { return Mat4(format); };
    //inline char at(int r, int c) { return _array.at(r).at(c); };
    inline char at(int r, int c) { return _array.at(r).at(c); };
};

#endif