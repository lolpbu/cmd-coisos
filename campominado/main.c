#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#define toString(num) num+'0'

#define W 8
#define H 4
#define BOMBS_N 7

int main() {
  char tiles[H][W];
  
  const int bombs[BOMBS_N][2] = {
   // {y, x}
      {1, 0},
      {1, 1},
      {1, 2},
      {3, 6},
      {2, 6},
      {0, 7},
      {3, 5},
  };
  
//   for(int i=0; i<BOMBS_N; i++)
//     tiles[bombs[i][0]][bombs[i][1]] = 'B';
  for(int i=0; i<H; i++)
    for(int j=0; j<W; j++)
    //   if(tiles[i][j] != 'B'):
        tiles[i][j] = '#';

  bool exit = false;
  int input_col, input_row;

  while (!exit) {
    //system("CLS");
    printf("---------------------------------\n");

    for (int i = 0; i < H; i++) {
      for (int j = 0; j < W; j++)
        printf("%c", tiles[i][j]);
      printf("\n");
    }

    printf("input_col (0-%d): ", H);
    fflush( stdout );
    scanf("%d", &input_col);
    printf("input_row (0-%d): ", W);
    fflush( stdout );
    scanf("%d", &input_row);

    // bool _a=0, _b=0, _c=0, _d=0, _e=0, _f=0, _g=0, _h=0;
    // bool u = input_col == 0;
    // bool d = input_col == H - 1;
    // bool l = input_row == 0;
    // bool r = input_row == W - 1;
    
    // if(!u && !l)
    //   _a = tiles[input_col-1][input_row-1] == 'B';
    // if(!u)
    //   _b = tiles[input_col-1][input_row] == 'B';
    // if(!u && !r)
    //   _c = tiles[input_col-1][input_row+1] == 'B';
    // if(!l)
    //   _d = tiles[input_col][input_row-1] == 'B';
    // if(!r)
    //   _e = tiles[input_col][input_row+1] == 'B';
    // if(!d && !l)
    //   _f = tiles[input_col+1][input_row-1] == 'B';
    // if(!d)
    //   _g = tiles[input_col+1][input_row] == 'B';
    // if(!d && !r)
    //   _h = tiles[input_col+1][input_row+1] == 'B';

    // int total = _a+_b+_c+_d+_e+_f+_g+_h;
    
    int total = 0;
    for(int i=0; i<BOMBS_N; i++) {
        //bool _a=0, _b=0, _c=0, _d=0, _e=0, _f=0, _g=0, _h=0;
        bool u = input_col == 0;
        bool d = input_col == H - 1;
        bool l = input_row == 0;
        bool r = input_row == W - 1;
        if(!u && !l) total += (bombs[i][0]==input_col-1 && bombs[i][1]==input_row-1);
        if(!u)       total += (bombs[i][0]==input_col-1 && bombs[i][1]==input_row  );
        if(!u && !r) total += (bombs[i][0]==input_col-1 && bombs[i][1]==input_row+1);
        if(!l)       total += (bombs[i][0]==input_col   && bombs[i][1]==input_row-1);
        if(!r)       total += (bombs[i][0]==input_col   && bombs[i][1]==input_row+1);
        if(!d && !l) total += (bombs[i][0]==input_col+1 && bombs[i][1]==input_row-1);
        if(!d)       total += (bombs[i][0]==input_col+1 && bombs[i][1]==input_row  );
        if(!d && !r) total += (bombs[i][0]==input_col+1 && bombs[i][1]==input_row+1);
    }
    if(total != 0)
      tiles[input_col][input_row] = toString(total);
    else
      tiles[input_col][input_row] = '.';
  }
  //_a _b _c
  //_d    _e
  //_f _g _h

  return 0;
}
