/*
This code is a simulation of the real life
chess game
is divided in separate stages
*/
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <wchar.h>
#include <stdint.h>
#include <string.h>
#include <stdbool.h>
#include <errno.h>

bool endOfTheLine;

#include "checkMoves.h"
#include "genMoves.c"
#include "utils.h"
// #include "load.c"

char option[10];

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

int handleUserDecision();

void menuSaveGame();

//function for fun
void multiplayer(int flag)
{
	/*
		we set the endOfTheLine variable to 0
		and the option order to be set to White
	*/ 

	unsigned int movement = WHITE;

	Tutorial();

	if(flag == 0)
	{
		initBoard();
	}

	while(!endOfTheLine)
	{
		//we print the chess chess_board

        bool flag = false;

        print_chess_board();

		int flagDecision;

		menuSaveGame();

		flagDecision = handleUserDecision();

		if (flagDecision == 1) // we can keep going
		{
			while (!flag)
			{
				printf("\n");

				// require for input from user
				printf("%s's turn.", (movement == WHITE) ? "WHITE" : "BLACK");

				flag = movementHandler(movement);

				// printf("FLAG IS: %d\n", flag);
			}

			// EndGame();

			if (movement == 1)
			{
				movement = 0;
			}
			else
			{
				movement = 1;
			}
		}
		else
		{
			saveGame(1);

			endOfTheLine = true;
		}
	}

	if(endOfTheLine)
	{
		puts("Thank you for playing this game!");

		ExitGame();

		return;
	}
}

void menuSaveGame()
{
	puts("Continue? Press 1");
	puts("Save Game? Press 2");
}

int handleUserDecision()
{
	bool flag = false;

	while(!flag)
	{
		int opt;

		printf("Player decision: ");

		if(scanf("%d", &opt) == 1)
		{
			if(opt == 1 || opt == 2) //we can either continue or save game
			{
				flag = true;

				return opt;
			}
		}
		printf("\n");
	}

	return 0;
}

void mainMenu();

void singleplayer(int flag)
{	
	puts("We play single player!");

	Tutorial();

	if(flag == 0)
	{
		initPawnsStatus();

		initBoard();
	}

	unsigned int movement = BLACK;

	while(!endOfTheLine)
	{
		//we print the chess chess_board

        bool flag = false;

        print_chess_board();

		int flagDecision;

		if(movement == BLACK)
		{
			menuSaveGame();

			flagDecision = handleUserDecision();
		}
		else
		{
			//we let the computer to play
			flagDecision = 1;
		}

		if (flagDecision == 1) // we continue
		{
			while (!flag)
			{
				printf("\n");
				// require for input from user
				printf("%s's turn.", (movement == WHITE) ? "WHITE" : "BLACK");

				if (movement == BLACK)
				{
					// human player is assigned black
					flag = movementHandler(movement);
				}
				else
				{
					// here is the computer assigned as white

					puts("nice game");

					flag = true;

					movementComputer();
				}
				// printf("FLAG IS: %d\n", flag);
			}

			// EndGame();

			if (movement == 1)
			{
				movement = 0;
			}
			else
			{
				movement = 1;
			}
		}
		else
		{
			//we save the game and go back to main menu

			saveGame(2);

			endOfTheLine = true;
		}
	}

	if(endOfTheLine)
	{
		puts("Thank you for playing this game!");

		ExitGame();

		return;
	}
}


void mainMenu()
{
	bool waitForMenuCompletion = true;

	int opt;

	//call the init board fct in order to set the initial settings of the board

	// printf("%u", waitForMenuCompletion);

	while(waitForMenuCompletion)
	{
		printOptionsMainMenu();

		if(scanf("%d", &opt) == 1)
		{
			switch (opt)
			{
				case 0:
				{
					ExitGame();
					break;
				}

				case 1:
				{
					//multiplayer
					waitForMenuCompletion = false;

					multiplayer(0);

					break;
				}
			
				case 2:
				{
					waitForMenuCompletion = false;

					singleplayer(0);

					break;
				}

				case 3:
				{
					//we want to load to a previous game saved
					int optionGame;	

					printf("Here we load the game\n");

					waitForMenuCompletion = false;

					loadGame(&optionGame);

					printf("This is the game option: %d\n", optionGame);

					if(optionGame == 1)
					{
						multiplayer(1); //we put the index 1 to load game data from file
					}
					else
					{
						singleplayer(1); //put 1 to save game data from file
					}
					
					break;
				}

				default:
				{
					waitForMenuCompletion = true;
					break;
				}
			}
		}
		else
		{
			waitForMenuCompletion = true;
		}
	}
}

int main()
{
	//needed to print special characters
	setlocale(LC_CTYPE,"");

	//we call the main function to play
	mainMenu();

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
