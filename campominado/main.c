#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#define W 8
#define H 4

int main() {
  char tiles[H][W];
  tiles[1][1] = 'B';
  tiles[1][2] = 'B';
  tiles[3][6] = 'B';
  tiles[2][6] = 'B';
  tiles[0][7] = 'B';
  tiles[3][5] = 'B';

  for(int i=0; i<H; i++)
    for(int j=0; j<W; j++)
      if(tiles[i][j] != 'B')
        tiles[i][j] = '#';

  bool exit = false;
  int input_col, input_row;

  while (!exit) {
    system("CLS");

    for (int i = 0; i < H; i++) {
      for (int j = 0; j < W; j++)
        printf("%c", tiles[i][j]);
      printf("\n");
    }

    printf("input_col (0-%d): ", H);
    scanf("%d", &input_col);
    printf("input_row (0-%d): ", W);
    scanf("%d", &input_row);

    bool _a=0, _b=0, _c=0, _d=0, _e=0, _f=0, _g=0, _h=0;
    bool u = input_col == 0;
    bool d = input_col == H - 1;
    bool l = input_row == 0;
    bool r = input_row == W - 1;
    if(!u && !l)
      _a = tiles[input_col-1][input_row-1] == 'B';
    if(!u)
      _b = tiles[input_col-1][input_row] == 'B';
    if(!u && !r)
      _c = tiles[input_col-1][input_row+1] == 'B';
    if(!l)
      _d = tiles[input_col][input_row-1] == 'B';
    if(!r)
      _e = tiles[input_col][input_row+1] == 'B';
    if(!d && !l)
      _f = tiles[input_col+1][input_row-1] == 'B';
    if(!d)
      _g = tiles[input_col+1][input_row] == 'B';
    if(!d && !r)
      _h = tiles[input_col+1][input_row+1] == 'B';

    int total = _a+_b+_c+_d+_e+_f+_g+_h;
    if(total != 0)
      tiles[input_col][input_row] = total + '0';
    else
      tiles[input_col][input_row] = '.';
  }
  //_a _b _c
  //_d    _e
  //_f _g _h

  //  for(int i=0; i<H; i++) {
  //   for(int j=0; j<W; j++) {
  //    if(tiles[i][j] == 'B')
  //     continue;

  //    bool _a=0, _b=0, _c=0, _d=0, _e=0, _f=0, _g=0, _h=0;
  //    bool u = i == 0;
  //    bool d = i == H - 1;
  //    bool l = j == 0;
  //    bool r = j == W - 1;
  //    //_a _b _c
  //    //_d    _e
  //    //_f _g _h
  //    if(!u && !l)
  //     _a = tiles[i-1][j-1] == 'B';
  //    if(!u)
  //     _b = tiles[i-1][j] == 'B';
  //    if(!u && !r)
  //     _c = tiles[i-1][j+1] == 'B';
  //    if(!l)
  //     _d = tiles[i][j-1] == 'B';
  //    if(!r)
  //     _e = tiles[i][j+1] == 'B';
  //    if(!d && !l)
  //     _f = tiles[i+1][j-1] == 'B';
  //    if(!d)
  //     _g = tiles[i+1][j] == 'B';
  //    if(!d && !r)
  //     _h = tiles[i+1][j+1] == 'B';

  //    int total = _a+_b+_c+_d+_e+_f+_g+_h;
  //    if(total != 0)
  //     tiles[i][j] = total + '0';
  //    else
  //     tiles[i][j] = '.';
  //   }
  //  }

  //  for(int i=0; i<H; i++) {
  //   for(int j=0; j<W; j++)
  //    printf("%c", tiles[i][j]);
  //   printf("\n");
  //  }

  return 0;
}
