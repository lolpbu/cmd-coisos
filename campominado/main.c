#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>

#define toString(num) num+'0'

#define W 8
#define H 5
#define BOMBS_N 12

int bombs[BOMBS_N][2];

bool isBomb(int row, int col) {
    for(int i=0; i<BOMBS_N; i++) {
        if(bombs[i][0] == row && bombs[i][1] == col)
            return true;
    }
    return false;
}

int totalBombs(int row, int col) {
    int total = 0;
    bool _a=0, _b=0, _c=0, _d=0, _e=0, _f=0, _g=0, _h=0;
    for(int i=0; i<BOMBS_N; i++) {
        bool u = row == 0;
        bool d = row == H - 1;
        bool l = col == 0;
        bool r = col == W - 1;
        
        // a b c
        // d   e
        // f g h

        // if(!u && !l) total += (bombs[i][0]==row-1 && bombs[i][1]==col-1);
        // if(!u)       total += (bombs[i][0]==row-1 && bombs[i][1]==col  );
        // if(!u && !r) total += (bombs[i][0]==row-1 && bombs[i][1]==col+1);
        // if(!l)       total += (bombs[i][0]==row   && bombs[i][1]==col-1);
        // if(!r)       total += (bombs[i][0]==row   && bombs[i][1]==col+1);
        // if(!d && !l) total += (bombs[i][0]==row+1 && bombs[i][1]==col-1);
        // if(!d)       total += (bombs[i][0]==row+1 && bombs[i][1]==col  );
        // if(!d && !r) total += (bombs[i][0]==row+1 && bombs[i][1]==col+1);

        if(!u && !l && !_a) _a = (bombs[i][0]==row-1 && bombs[i][1]==col-1);
        if(!u       && !_b) _b = (bombs[i][0]==row-1 && bombs[i][1]==col  );
        if(!u && !r && !_c) _c = (bombs[i][0]==row-1 && bombs[i][1]==col+1);
        if(!l       && !_d) _d = (bombs[i][0]==row   && bombs[i][1]==col-1);
        if(!r       && !_e) _e = (bombs[i][0]==row   && bombs[i][1]==col+1);
        if(!d && !l && !_f) _f = (bombs[i][0]==row+1 && bombs[i][1]==col-1);
        if(!d       && !_g) _g = (bombs[i][0]==row+1 && bombs[i][1]==col  );
        if(!d && !r && !_h) _h = (bombs[i][0]==row+1 && bombs[i][1]==col+1);
    }
    total = _a + _b + _c + _d + _e + _f + _g + _h;
    return total;
}


void print_tiles(char t[H][W]) {
  for(int i=0; i<H; i++) {
    printf("%d ", i);
    for(int j=0; j<W; j++)
      printf("%c", t[i][j]);
    printf("\n");
  }
  printf("  ");
  for(int i=0; i<W; i++)
    printf("%c", (char)(i+65));
  printf("\n");
}

void fill_empty(char t[H][W], int row, int col) {
  if(t[row][col]=='.' || !totalBombs(row, col)==0)
    return;
  else
    t[row][col] = '.';

  if(row != 0) fill_empty(t, row-1, col  ); //u
  if(col != 0) fill_empty(t, row  , col-1); //l
  if(col <= W) fill_empty(t, row  , col+1); //r
  if(row <= H) fill_empty(t, row+1, col  ); //d
}

void gen_bombs() {
  for(int i=0; i<BOMBS_N; i++) {
    int r1 = rand() % H;
    bombs[i][0] = r1;
    int r2 = rand() % W;
    bombs[i][1] = r2;
  }
}

int main() {

  srand(time(NULL));
  gen_bombs();

  char tiles[H][W];
  
  // for(int i=0; i<BOMBS_N; i++)
  //   tiles[bombs[i][0]][bombs[i][1]] = 'B';
  for(int i=0; i<H; i++)
    for(int j=0; j<W; j++)
      // if(tiles[i][j] != 'B')
        tiles[i][j] = '#';

  bool exit = false;
  int input_row=-1, input_col=-1;

  while (!exit) {
    //system("CLS");
    printf("---------------------------------\n");
    print_tiles(tiles);

    while(input_row < 0 || input_row > H) {
      printf("input_row (0-%d): ", H-1);
      fflush(stdout);
      scanf("%d", &input_row);
    }

    while(input_col < 0 || input_col > W) {
      printf("input_col (A-%c): ", (char)(W-1+65));
      // printf("input_col (0-%d): ", W-1);
      fflush(stdout);
      // scanf("%d", &input_col);
      scanf(" %c", &input_col);

      if(input_col < 0) {
        input_col *= -1;
        if(input_col <= 159)//a-z
          input_col += 32; //A-Z
        input_col = 191 - input_col;
      } else {
        if(input_col > 90) //a-z
          input_col -= 32;
        input_col -= 65;
      }

    }//set path=%path%;C:\msys64\ucrt64\bin
    
    if(isBomb(input_row, input_col)) {
        tiles[input_row][input_col] = 'B';
        printf("---------------------------------\n");
        print_tiles(tiles);
        printf("GAME OVER-----------------------------\n");
        exit = true;
        break;
    }
    
    int total = totalBombs(input_row, input_col);
    if(total != 0) {
      tiles[input_row][input_col] = toString(total);
    }else{   
      fill_empty(tiles, input_row, input_col);
    }

    input_row = -1;
    input_col = -1;
  }

  return 0;
}
