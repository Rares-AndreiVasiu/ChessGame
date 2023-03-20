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


/*
    now we create some helper functions
    for the user to understand the game 
    input format
*/

void printUserInputHelper()
{
    puts("Hey you! Yes you! This is a chess game!");
  
    puts("Before you start here is a short tutorial on how to add your moves.");
   
    puts("You ought to follow the format:");

    puts("Example moving the queen: Queen d8 d7\n");

    puts("Example moving the king: King e8 e7");

    puts("Example moving the rook: Rook a8 a3");
    
    puts("Example moving the bishop: Bishop c8 a6");
    
    puts("Example moving the pawn: Pawn a7 a6");

    puts("Example moving the knight: Knight a8 a3");

    printf("\n\n");
}

#endif //we end the declaration of the chess pieces