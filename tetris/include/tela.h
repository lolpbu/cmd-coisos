#ifndef _TELA_H
#define _TELA_H

#include <iostream>
#include <vector>
//#include "peca.h"
#include "mat4.h"

//#define W 12
#define W 12
#define H 24
#define LIMIT_Y 5

struct Tela {
public:
    char2d tile;
    //std::vector<std::vector<char>> tile(4, std::vector<char>(4, ' '));

    Tela();
    ~Tela();

    void clear_mov();
    void clear_sol();
    void clear_lines(int* pont);
    void print();

private:
    void clear_line(int y);
    void move_down(int y);
};

#endif