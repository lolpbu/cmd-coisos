#include "include/peca.h"
#include <iostream>
#include "include/input.h"

Peca::Peca(Mat4& frmt, Tela* _t) {
    t = _t;
    x = W/2 -2;
    y = 0;
    format = frmt;
    sol = false;

    _debug_str = "";
}

bool Peca::coll(KEY_STATE_T input) {
    if(sol)
        return true;
    if(y == 0 && input == UP)
        return true;

    for(int i=0; i<4; i++) {
        for(int j=0; j<4; j++) {
            if(format.at(i, j) == BG_CHAR) 
                continue;

            int dX = (input == RIGHT) - (input == LEFT);
            int dY = (input == DOWN)  - (input == UP);

            //  if(y == 0)
            //     dY = input == DOWN;

            if(t->tile.at(i + y + dY).at(j + x + dX) == MOV_CHAR ||
               t->tile.at(i + y + dY).at(j + x + dX) == '*'      ||
               t->tile.at(i + y + dY).at(j + x + dX) == ' '        )
                continue;
            if(t->tile.at(i + y + dY).at(j + x + dX) != BG_CHAR)
                return true;
        }
    }

    return false;
}

void Peca::move(KEY_STATE_T input) {
    if(input == UP)
        return;
    if(coll(input))
        return;

    int x_in = (input == RIGHT) - (input == LEFT);
    int y_in = (input == DOWN)  - (input == UP);

    if(x_in != 0)
        x += x_in;

    if(y_in != 0)
        y += y_in;
    
    //draw
    t->clear_mov();
    for(int i=0; i<4; i++) {
        for(int j=0; j<4; j++) {
            if(format.at(i, j) == BG_CHAR)
                continue;

            if(t->tile.at(i + y).at(j + x) == BG_CHAR)
                t->tile.at(i + y).at(j + x) = format.at(i, j);
        }
    }
}