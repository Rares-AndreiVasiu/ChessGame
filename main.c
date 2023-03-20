/*
	This code is a simulation of the real life
	chess game
	its divided in separate stages
*/

#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <wchar.h>
#include <stdint.h>

#include "checkMoves.h"

unsigned int chess_board[9][9];

char option[10];

void initBoard()
{
	/*
		chess chess_board initialization
	*/

	chess_board[1][1] = black_ROOK;

	chess_board[1][2] = black_KNIGHT;
	
	chess_board[1][3] = black_BISHOP;
	
	chess_board[1][4] = black_QUEEN;
	
	chess_board[1][5] = black_KING;
	
	chess_board[1][6] = black_BISHOP;
	
	chess_board[1][7] = black_KNIGHT;
	
	chess_board[1][8] = black_ROOK;

	/*
		init chess board with its pieces
	*/

	for(int i = 1; i <= 8; ++i)
	{
		chess_board[2][i] = black_PAWN;
	}

	chess_board[8][1] = white_ROOK;

	chess_board[8][2] = white_KNIGHT;
	
	chess_board[8][3] = white_BISHOP;
	
	chess_board[8][4] = white_QUEEN;
	
	chess_board[8][5] = white_KING;
	
	chess_board[8][6] = white_BISHOP;
	
	chess_board[8][7] = white_KNIGHT;
	
	chess_board[8][8] = white_ROOK;

	for(int i = 1; i <= 8; ++ i)
	{
		chess_board[7][i] = white_PAWN;
	}
}

void print_chess_board()
{
	printf("\x1b[H\x1b[J");

	//chess_board coordinates
	printf("  ");

	// system("clear"); -> doesn't work? why....
	for(int j = 0; j <= 7; ++j)
	{
		printf(" %c",'a' + j);
	}
	
	printf("\n\n");
	
	for(int i = 1; i <= 8; ++ i)
	{
		//chess_board coordinates
		printf("%d ",i);
		
		for(int j = 1; j < 9;++j)
		{
			/*
				if a space is empty, we put an different colour square		
			*/

			if(!chess_board[i][j])
			{
				if((i + j) % 2 == 1)
				{
					printf(" %lc", white_SQUARE);
				}
				else
				{
					printf(" %lc", black_SQUARE);
				}
			}
			else
			{
				printf(" %lc", chess_board[i][j]);
			}
		}
		printf("  %d\n", i);
	}

	printf("\n  ");

	//print the abdcefgh for the board
	for(int j = 0; j <= 7; ++ j)
		printf(" %c", 'a' + j);
	printf("\n");
}

//function for fun :))
void gamePlay()
{
	/*
		we set the endOfTheLine variable to 0
		and the option order to be set to White
	*/

	unsigned int endOfTheLine = 0;

	unsigned int movement = WHITE;

	unsigned int waitForMenuCompletion = -1;
	
	//call the init board fct in order to set the initial settings of the board
	
	printUserInputHelper();

	while(waitForMenuCompletion != -1)
	{
		puts("Feel prepared? Press 1 to continue, 0 to exit: ");

		
	}

	initBoard();
	
	while(!endOfTheLine)
	{
		//we print the chess chess_board
		print_chess_board();

		//require for input from user
		printf("%s's turn.", (movement == WHITE) ? "WHITE" : "BLACK");

		//we call this function in order to guide the user
		//to acknoledge the format of its input

		//take user input with scanf
		//further checking required	
		scanf("%9s", option);

		if(movement == 1)
		{
			movement = 0;
		}
		else
		{
			movement = 1;
		}
	}
}
		
int main()
{
	//needed to print special characters
	setlocale(LC_CTYPE,"");

	//we call the main function to play
	gamePlay();

	return 0;
}

/*
TO DO LIST:
	1. create checking functions for user input
	2. fix scanf for user input
	3. create movement function
	4. consider the following pattern user input: rook e4 e1... <pieceType> <initialPosition> <endPosition>

IMPORTANT:
	1. 
*/
