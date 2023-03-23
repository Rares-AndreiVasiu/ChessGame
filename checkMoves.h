#ifndef CHECKMOVE //if we didn't define the file we define it now
#define CHECKMOVE

#include "utils.h"

bool checkPieceType(const char *piceType)
{
    if(strcmp("Queen", piceType) == 0 || strcmp("King", piceType) == 0 
    || strcmp("Rook", piceType) == 0 || strcmp("Bishop", piceType) == 0 ||
    strcmp("Pawn", piceType) == 0  || strcmp("Knight", piceType) == 0)
    {
        return true;
    }
    return false;
}

int selectPieceType(const char *piceType, int movement)
{
    if(strcmp("Queen", piceType) == 0)
    {
        return movement == WHITE ? white_QUEEN : black_QUEEN;
    }

    if( strcmp("King", piceType) == 0)
    {
        return movement == WHITE ? white_KING : black_KING;
    }
    
    if(strcmp("Rook", piceType) == 0)
    {
        return movement == WHITE ? white_ROOK : black_ROOK;
    }

    if(strcmp("Bishop", piceType) == 0)
    {
        return movement == WHITE ? white_BISHOP : black_BISHOP;
    }

    if(strcmp("Pawn", piceType) == 0)
    {
        return movement == WHITE ? white_PAWN : black_PAWN;
    }

    if(strcmp("Knight", piceType) == 0)
    {
        return movement == WHITE ? white_KNIGHT : black_KNIGHT;
    }
    return -1;
}

/*
    in pos we have the initial position
    in pieceType we got: Knight, King, Queen, Bishop, Rook, Pawn
    in movement we got either BLACK or WHITE
*/
bool checkInitialPosition(const char *pos, const char *piceType, unsigned int movement)
{
    int Xcoordinate = (pos[0] - 'a') + 1;

    int Ycoordinate = (pos[1] - '0') + 1;

    printf("Initial position: %c %c\n", pos[0], pos[1]);

    int pieceCode = selectPieceType(piceType, movement);

    if(chess_board[Xcoordinate][Ycoordinate] == pieceCode)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool checkMovementFormat(char *command, unsigned int movement)
{
    char *token =  strtok(command, " ");

    char *piceType = token;

    printf("You entered this piece: %s\n", piceType);

    if(checkPieceType(piceType))
    {
        token = strtok(NULL, " ");

        char *initialPosition = token;

        printf("These are your initial position: %s\n", initialPosition);

        if(checkInitialPosition(initialPosition, piceType, movement))
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    return false;
}


bool movementHandler(unsigned int movement)
{
    char userOptionMovement[13];

    if(scanf("%12s", userOptionMovement) == 1)
    {
        if(checkMovementFormat(userOptionMovement, movement))
        {
            return true;
        }  
        else
        {
            return false;
        }
    }   
    else
    {
        return false;
    }
}



#endif