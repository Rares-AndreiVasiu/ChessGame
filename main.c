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
#include <string.h>
#include <stdbool.h>

#include "checkMoves.h"

char option[10];

void print_chess_board()
{
	// printf("\x1b[H\x1b[J");

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

	Tutorial();

	initBoard();

	while(!endOfTheLine)
	{
		//we print the chess chess_board

        bool flag = false;

        print_chess_board();
        
        while(!flag)
        {
            printf("\n");

            //require for input from user
            printf("%s's turn.", (movement == WHITE) ? "WHITE" : "BLACK");

            flag = movementHandler(movement);

			printf("FLAG IS: %d\n", flag);
        }

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
