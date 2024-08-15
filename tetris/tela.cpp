#include "include/tela.h"

Tela::Tela() : tile(H, std::vector<char> (W)) {
    for(int i=0; i<H; i++)
        for(int j=0; j<W; j++)
            tile[i][j] = BG_CHAR;

    // if(BG_CHAR != ' ') {
    //     for(int i=0; i<LIMIT_Y; i++)
    //         for(int j=0; j<W; j++)
    //             tile[i][j] = ' ';
    // }

    for(int i=0; i<H; i++) {
        tile[i][0]   = '|';
        tile[i][W-1] = '|';
    }

    for(int j=0; j<W; j++) {
        tile[H-1][j]     = '-';
        tile[LIMIT_Y][j] = '*';
    }
}

Tela::~Tela() {
    for(int i=0; i<W; i++)
        delete[] &tile[i];
    delete[] &tile;
}

void Tela::print() {
    for(int i=0; i<H; i++) {
        for(int j=0; j<W; j++)
            std::cout << tile[i][j];
        std::cout << std::endl;
    }
};

void Tela::clear_mov() {
    for(int i=0; i<H; i++) {
        for(int j=0; j<W; j++) {
            if(tile.at(i).at(j) == MOV_CHAR)
                tile[i][j] = BG_CHAR;
        }
    }
}

void Tela::clear_sol() {
    for(int i=0; i<H; i++) {
        for(int j=0; j<W; j++) {
            if(tile.at(i).at(j) == MOV_CHAR)
                tile[i][j] = SOL_CHAR;
        }
    }
}



void Tela::clear_lines(int* pont) {
    for(int i=0; i<H; i++) {
        int t = 0;

        for(int j=0; j<W; j++) {
            if(tile.at(i).at(j) == SOL_CHAR)
                t++;
        }

        if(t == W - 2) {
            clear_line(i);
            move_down(i+1);
            (*pont)++;
        }
    }
}

void Tela::move_down(int y) {
    char2d tmp = tile;
    for(int i=LIMIT_Y+2; i<y; i++) {
        for(int j=0; j<W; j++) {
            tile[i][j] = tmp[i-1][j];
        }
    }
}

void Tela::clear_line(int y) {
    for(int i=1; i<W-1; i++) {
        tile[y][i] = BG_CHAR;
    }
}