#ifndef _PECA_H
#define _PECA_H

#include "input.h"
#include "mat4.h"
#include "tela.h"

struct Peca {
    Mat4 format;
    int x, y;
    bool sol;
    
    Peca(Mat4& frmt, Tela* _t);
    //Peca& operator=(const Peca& other);

    void move(KEY_STATE_T input);
    bool coll(KEY_STATE_T input);

    std::string _debug_str;

private:
    Tela* t;
};

#endif