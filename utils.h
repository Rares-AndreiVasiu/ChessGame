#ifndef CHESS // if not defined the chess pieces we define it
#define CHESS
/*
    here we declare all the chess pieces 
    and block squres to display
*/
#define black_KING   0x2654    
#define black_QUEEN  0x2655
#define black_ROOK   0x2656
#define black_BISHOP 0x2657    
#define black_KNIGHT 0x2658
#define black_PAWN   0x2659

#define white_KING   0x265A
#define white_QUEEN  0x265B
#define white_ROOK   0x265C    
#define white_BISHOP 0x265D
#define white_KNIGHT 0x265E
#define white_PAWN   0x265F

#define black_SQUARE 0x25A0
#define white_SQUARE 0x25A1

#define WHITE 0
#define BLACK 1

//declare the chess board at this point
unsigned int chess_board[9][9];

unsigned int whitePawnsStart[9];

unsigned int blackPawnsStart[9];

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

	for(int i = 1; i <= 8; ++ i)
	{
		whitePawnsStart[i] = 1;
		
		blackPawnsStart[i] = 1;
	}
}
/*
    now we create some helper functions
    for the user to understand the game 
    input format
*/

void printUserInputHelper()
{
    printf("\x1b[H\x1b[J");

    puts("Hey you! Yes you! This is a chess game!");
  
    puts("Before you start here is a short tutorial on how to add your moves.");
   
    puts("You ought to follow the format:");

    puts("Example moving the queen: Queen d8 d7");

    puts("Example moving the king: King e8 e7");

    puts("Example moving the rook: Rook a8 a3");
    
    puts("Example moving the bishop: Bishop c8 a6");
    
    puts("Example moving the pawn: Pawn a7 a6");

    puts("Example moving the knight: Knight a8 a3");

    printf("\n");
}

void ExitGame()
{
    exit(EXIT_SUCCESS);
}

void Tutorial()
{
    char tutorialUserInput;
	
	bool waitForMenuCompletion = true;

	//call the init board fct in order to set the initial settings of the board

	// printf("%u", waitForMenuCompletion);

	while(waitForMenuCompletion)
	{
		printUserInputHelper();

		printf("Press 1 to continue the game, 0 to exit: ");

		if(scanf("%c", &tutorialUserInput) == 1)
		{
			switch (tutorialUserInput)
			{
				case '0':
				{
					ExitGame();
					break;
				}

				case '1':
				{
					waitForMenuCompletion = false;
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

void printOptionsMainMenu()
{
	puts("<===== Chess Game =====>");

	puts("Press 1 for multiplayer");

	puts("Press 2 for single player");

	puts("Press 0 to exit game");
}

#endif //we end the declaration of the chess pieces
