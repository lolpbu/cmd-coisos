#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#define toString(num) num+'0'

#define W 8
#define H 4
#define BOMBS_N 7

const int bombs[BOMBS_N][2] = {
//{y, x}
  {1, 0},
  {1, 1},
  {1, 2},
  {3, 6},
  {2, 6},
  {0, 7},
  {3, 5},
};

bool isBomb(int col, int row) {
    for(int i=0; i<BOMBS_N; i++) {
        if(bombs[i][0] == col && bombs[i][1] == row)
            return true;
    }
    return false;
}

int totalBombs(int col, int row) {
    int total = 0;
    for(int i=0; i<BOMBS_N; i++) {
        bool u = col == 0;
        bool d = col == H - 1;
        bool l = row == 0;
        bool r = row == W - 1;
        
        // a b c
        // d   e
        // f g h
        if(!u && !l) total += (bombs[i][0]==col-1 && bombs[i][1]==row-1); //a
        if(!u)       total += (bombs[i][0]==col-1 && bombs[i][1]==row  ); //b
        if(!u && !r) total += (bombs[i][0]==col-1 && bombs[i][1]==row+1); //c
        if(!l)       total += (bombs[i][0]==col   && bombs[i][1]==row-1); //d
        if(!r)       total += (bombs[i][0]==col   && bombs[i][1]==row+1); //e
        if(!d && !l) total += (bombs[i][0]==col+1 && bombs[i][1]==row-1); //f
        if(!d)       total += (bombs[i][0]==col+1 && bombs[i][1]==row  ); //g
        if(!d && !r) total += (bombs[i][0]==col+1 && bombs[i][1]==row+1); //h
    }
    return total;
}

int main() {
  char tiles[H][W];
  
  
  
  for(int i=0; i<BOMBS_N; i++)
    tiles[bombs[i][0]][bombs[i][1]] = 'B';
  for(int i=0; i<H; i++)
    for(int j=0; j<W; j++)
      if(tiles[i][j] != 'B')
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
    
    if(isBomb(input_col, input_row)) {
        printf("GAME OVER\n");
        exit = true;
        break;
    }
    
    int total = totalBombs(input_col, input_row);
    if(total != 0) {
      tiles[input_col][input_row] = toString(total);
    }else{   
      tiles[input_col][input_row] = '.';
      
      int col = input_col;
      int row = input_row;
      while(total == 0)   {
          bool u = col == 0;
          bool d = col == H - 1;
          bool l = row == 0;
          bool r = row == W - 1;
          
          // AAAAAAAAAAAAAAAAAAAAAAAAAAA
      }
    }
  }

  return 0;
}
