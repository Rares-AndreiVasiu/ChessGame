/*
chess pieces unicodes
*/

#define clear() printf("\x1b[H\x1b[J")

#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <wchar.h>
#include <stdint.h>
#include <stdbool.h>

#include "utils.h"

uint16_t board[9][9];

void initBoard(){
	/*
	initial chess board definition
	*/
	board[1][1] = black_ROOK;
	board[1][2] = black_KNIGHT;
	board[1][3] = black_BISHOP;
	board[1][4] = black_QUEEN;
	board[1][5] = black_KING;
	board[1][6] = black_BISHOP;
	board[1][7] = black_KNIGHT;
	board[1][8] = black_ROOK;

	for(int i = 1; i <= 8; ++i)
	{
		board[2][i] = black_PAWN;
	}

	board[8][1] = white_ROOK;
	board[8][2] = white_KNIGHT;
	board[8][3] = white_BISHOP;
	board[8][4] = white_QUEEN;
	board[8][5] = white_KING;
	board[8][6] = white_BISHOP;
	board[8][7] = white_KNIGHT;
	board[8][8] = white_ROOK;

	for(int i = 1; i <= 8;++ i)
	{
		board[7][i] = white_PAWN;
	}
}

void printBoard()
{
	clear();

	//board coordinates
	printf("  ");

	// system("clear");
	for(int j=0;j<8;++j)
	{
		printf(" %c",'a'+j);
	}
	
	printf("\n\n");
	
	for(int i=1;i<9;++i)
	{
		//board coordinates
		printf("%d ",i);
		
		for(int j=1;j<9;++j){
			/*
				if a space is empty, we put an empty square
			*/

			if(!board[i][j])
			{
				printf(" %lc",((i + j) % 2 == 1) ? white_SQUARE : black_SQUARE);
			}

			else
			{
				printf(" %lc", board[i][j]);
			}
		}
		//board coordinates
		printf("  %d\n", i);
	}

	//board coordinates
	printf("\n  ");

	for(int j = 0; j< 8; ++ j)
	{
		printf(" %c", 'a' + j);
	}

	putchar('\n');
}

/*
void analizeCommand(const char* command, int* a){
	
}
*/

void play()
{
	initBoard();

	unsigned int gameOver = 0;
	
	unsigned int toMove = WHITE;
	
	char command[5];
	
	while(!gameOver)
	{
		printBoard();

		printf("%s to move: ",(toMove == WHITE) ? "WHITE" : "BLACK");

		scanf("%4s",command);

		toMove = !toMove;
	}
}
		
int main()
{
	setlocale(LC_CTYPE,"");

	play();

	return 0;
}
