#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include <errno.h>

#define to_string(num) num+'0'

// #define W 20
// #define H 12
// #define BOMBS_N 40
// int bombs[BOMBS_N][2] = {0};
// char tiles[H][W];

#define DEFAULT_W 20
#define DEFAULT_H 12
#define DEFAULT_BOMBS_N 40

int W, H, BOMBS_N;
int** bombs;
char** tiles;

int found = 0;

bool is_bomb(int row, int col) {
	for(int i=0; i<BOMBS_N; i++) {
    	if(bombs[i][0] == row && bombs[i][1] == col)
            return true;
    }
    return false;
}

int total_bombs(int row, int col) {
    int total = 0;
    for(int i=0; i<BOMBS_N; i++) {
        bool u = row == 0;
        bool d = row == H - 1;
        bool l = col == 0;
        bool r = col == W - 1;
        
        // a b c
        // d   e
        // f g h
        if(!u && !l) total += (bombs[i][0]==row-1 && bombs[i][1]==col-1);//a
        if(!u)       total += (bombs[i][0]==row-1 && bombs[i][1]==col  );//b
        if(!u && !r) total += (bombs[i][0]==row-1 && bombs[i][1]==col+1);//c
        if(!l)       total += (bombs[i][0]==row   && bombs[i][1]==col-1);//d
        if(!r)       total += (bombs[i][0]==row   && bombs[i][1]==col+1);//e
        if(!d && !l) total += (bombs[i][0]==row+1 && bombs[i][1]==col-1);//f
        if(!d)       total += (bombs[i][0]==row+1 && bombs[i][1]==col  );//g
        if(!d && !r) total += (bombs[i][0]==row+1 && bombs[i][1]==col+1);//h
    }

    return total;
}

void fill_empty(int row, int col) {
	if(tiles[row][col] == '.')
		return;
		
	if(total_bombs(row, col) != 0) {
		if(tiles[row][col] == '#') found++;
		tiles[row][col] = to_string(total_bombs(row, col));
		return;
	}

	tiles[row][col] = '.';
	found++;
	

  	if(row != 0)  fill_empty(row-1, col  ); //u
  	if(col != 0)  fill_empty(row  , col-1); //l
  	if(col < W-1) fill_empty(row  , col+1); //r
  	if(row < H-1) fill_empty(row+1, col  ); //d
}

bool has_dup() {
    for (int i=0; i<BOMBS_N-1; i++) {
        for (int j=i+1; j<BOMBS_N; j++)
            if (bombs[i][0] == bombs[j][0] && bombs[i][1] == bombs[j][1])
                return true;
    }
    return false;
}

void gen_bombs() {
  while(has_dup()) {
        for (int i = 0; i < BOMBS_N; i++) {
            bombs[i][0] = rand()%H;
            bombs[i][1] = rand()%W;
        }
    }
}

void print_tiles() {
	for(int i=0; i<H; i++) {
		printf((i<10)?" %d-":"%d-", i);
    	for(int j=0; j<W; j++)
      		printf("%c", tiles[i][j]);
    	printf("\n");
  	}

  	printf("   ");
	for(int i=0; i<W; i++) 
		printf("|");
	printf("\n   ");
  	for(int i=0; i<W; i++)
	    printf("%c", (char)(i+65));
	printf("\t espacos seguros encontrados: %d/%d\n", found, W*H - BOMBS_N);
}

int main(const int argc, const char** argv) {
	if(argc < 2 || argc > 4) {
		W = DEFAULT_W;
		H = DEFAULT_H;
		BOMBS_N = DEFAULT_BOMBS_N;
		printf("USO: coiso.exe NUMERO_DE_LINHAS(2-25) NUMERO_DE_COLUNAS[2-50] NUMERO_DE_BOMBAS[2-L*C-1]\n");
		printf("USANDO CONFIGURACOES NORMAIS: %dx%d, %d bombas\n", W, H, BOMBS_N);
		system("PAUSE");
	} else {
		char* p;
		errno = 0;

		W = strtol(argv[1], &p, 10);
		if(W<2 || W>25 || errno!=0 || *p!='\0'|| W>INT_MAX || W<INT_MIN) {
			printf("NUMERO INVALIDO DE LINHAS: %d, deve ser entre 2 e 50\n", argv[1]);
			return 1;
		}

		H = strtol(argv[2], &p, 10);
		if(H<2 || H>50 || errno!=0 || *p!='\0'|| H>INT_MAX || H<INT_MIN) {
			printf("NUMERO INVALIDO DE COLUNAS: %d, deve ser entre 2 e 25\n", argv[2]);
			return 1;
		}

		BOMBS_N = strtol(argv[3], &p, 10);
		if(BOMBS_N<2 || BOMBS_N>W*H -1|| errno!=0 || *p!='\0'|| BOMBS_N>INT_MAX || BOMBS_N<INT_MIN) {
			printf("NUMERO INVALIDO DE BOMBAS: %d, deve ser entre 2 e %d\n", argv[3], W*H -1);
			return 1;
		}
	}

	srand(time(NULL));

	bombs = (int**) malloc(BOMBS_N * sizeof(int*));
	for (int i=0; i<BOMBS_N; i++)
        bombs[i] = malloc(2 * sizeof(int));
	
	tiles = (char**) malloc(H * sizeof(char*));
	for(int i=0; i<H; i++)
		tiles[i] = malloc(W * sizeof(char));

  	gen_bombs();
  
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
	    printf("-----------------------------------\n");
    	print_tiles();

    	while(input_row < 0 || input_row > H) {
      		printf("linha (0-%d): ", H-1);
      		fflush(stdout);
      		scanf("%d", &input_row);
    	}

    	while(input_col < 0 || input_col > W) {
      		printf("coluna (A-%c): ", (char)(W-1+65));
      		fflush(stdout);
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
    	}
    
    	if(is_bomb(input_row, input_col)) {
			tiles[input_row][input_col] = 'B';
			printf("-----------------------------------\n");
			print_tiles();
			printf("GAME OVER--------------------------\n");
			exit = true;
			break;
    	}
    
    	int total = total_bombs(input_row, input_col);
		if(total != 0) {
			if(tiles[input_row][input_col] == '#') found++;
			tiles[input_row][input_col] = to_string(total);
		}else{   
			fill_empty(input_row, input_col);
		}

		if(found >= W*H - BOMBS_N) {
			printf("GG---------------------------------\n");
			exit = true;
			break;
		}

    	input_row = -1;
    	input_col = -1;
  	}

	free(tiles);
	free(bombs);
  	return 0;
}
