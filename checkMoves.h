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
    int Xcoordinate = (pos[1] - '0');

    int Ycoordinate = (pos[0] - 'a') + 1;

    printf("Initial position: %d %d\n", Xcoordinate, Ycoordinate);

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

//the following function checks if you can move the king to finPos
bool checkKingMovement(const char *initialPosition, const char *finalPosition)
{
    printf("POWER KING\n");

    return true;
}

//the following function checks if you can move the queen to finPos
bool checkQueenMovement(const char *initialPosition, const char *finalPosition)
{
    printf("POWER QUEEN\n");

    return true;
}

//check if a block from the board is empty
bool checkEmptyBlock(int i, int j)
{
    return chess_board[i][j] == 0;
}

//the following function checks if you can move the rook to finPos
bool checkRookMovement(const char *initialPosition, const char *finalPosition)
{
    printf("POWER ROOk\n");

    /*
        the rook can move any number of squares horizontally and vertically
        EXCEPTIONS:
            1)The Rook cannot jump over other pieces, hence its movement options can be blocked 
            2)Special move -> Castling
    */

    int XInitialCoordinate = (initialPosition[1] - '0');
    int YInitialCoordinate = (initialPosition[0] - 'a') + 1;

    int XFinalCoordinate = (finalPosition[1] - '0');
    int YFinalCoordinate = (finalPosition[0] - 'a') + 1;

    bool validMove = true; 

    //first check to move online horiz
    if(XInitialCoordinate == XFinalCoordinate)
    {
        printf("We move horrizontally\n");

        //now to check for clear road
        if(YInitialCoordinate < YFinalCoordinate)
        {
            for(int j = YInitialCoordinate + 1; j <= YFinalCoordinate && validMove; ++ j)
            {
                if(!checkEmptyBlock(XInitialCoordinate, j))
                {
                    validMove = false;
                }
            }
        }
        else
        {
            for(int j = YInitialCoordinate - 1; j >= YFinalCoordinate && validMove; -- j)
            {
                if(!checkEmptyBlock(XInitialCoordinate, j))
                {
                    validMove = false;
                }
            }
        }
    }
    else
    {
        if(YInitialCoordinate == YFinalCoordinate)
        {
            printf("We move vertically\n");
            //now we check for clear road

            if(XInitialCoordinate < XFinalCoordinate)
            {
                for(int i = XInitialCoordinate + 1; i <= XFinalCoordinate && validMove; ++ i)
                {
                    if(!checkEmptyBlock(i, YInitialCoordinate))
                    {
                        printf("Here is not empty: %d %d\n", i, YInitialCoordinate);
                        validMove = false;
                    }
                }
            }
            else
            {
                for(int i = XInitialCoordinate - 1; i >= XFinalCoordinate && validMove; -- i)
                {
                    if(!checkEmptyBlock(i, YInitialCoordinate))
                    {
                        printf("Here is not empty: %d %d\n", i, YInitialCoordinate);
                        validMove = false;
                    }
                }
            }
        }
        else
        {
            validMove = false;
        }   
    }

    return validMove;
}


//the following function checks if you can move the king to finPos
bool checkBishopMovement(const char *initialPosition, const char *finalPosition)
{
    printf("POWER BISHOP\n");

    return true;
}

bool checkKnightMovement(const char *initialPosition, const char *finalPosition)
{
    printf("POWER KNIGHT\n");

    int XInitialCoordinate = (initialPosition[1] - '0');
    int YInitialCoordinate = (initialPosition[0] - 'a') + 1;

    int XFinalCoordinate = (finalPosition[1] - '0');
    int YFinalCoordinate = (finalPosition[0] - 'a') + 1;


    if( ( ( abs(XInitialCoordinate - XFinalCoordinate) == 1) && ( abs(YFinalCoordinate - YInitialCoordinate) == 2)) 
     || ( ( abs(XFinalCoordinate - XInitialCoordinate) == 2) && ( abs(YFinalCoordinate - YInitialCoordinate) == 1)) )
    {
        int colorKnight = chess_board[XInitialCoordinate][YInitialCoordinate];

        if(colorKnight == white_KNIGHT)
        {
            switch(chess_board[XFinalCoordinate][XInitialCoordinate])
            {
                case white_KING:
                {
                    return false;
                    break;
                }

                case white_QUEEN:
                {
                    return false;
                    break;
                }

                case white_ROOK:
                {
                    return false;
                    break;
                }

                case white_BISHOP:
                {
                    return false;
                    break;
                }

                case white_KNIGHT:
                {
                    return false;
                    break;
                }

                case white_PAWN:
                {
                    return false;
                    break;
                }
                default:
                {
                    return true;
                    break;
                }
            }
        }
        else
        {
            if(colorKnight == black_KNIGHT)
            {
                //knight is black 
                switch(chess_board[XFinalCoordinate][XInitialCoordinate])
                {
                    case black_KING:
                    {
                        return false;
                        break;
                    }

                    case black_QUEEN:
                    {
                        return false;
                        break;
                    }

                    case black_ROOK:
                    {
                        return false;
                        break;
                    }

                    case black_BISHOP:
                    {
                        return false;
                        break;
                    }

                    case black_KNIGHT:
                    {
                        return false;
                        break;
                    }

                    case black_PAWN:
                    {
                        return false;
                        break;
                    }
                    default:
                    {
                        return true;
                        break;
                    }
                }
            }
        }
    }

    return false;
}

bool checkTwoBlocksPawnMovement(int XInitial, int YInitial, int XFinal, int YFinal)
{
    puts("Let's check if the pawn is able to move 2 blocks!");

    //check if we are able to move 2 blocks in front for white pawns

    // printf("Able to jump 2: %d, distance: %d, same y: %d\n", whitePawnsStart[YInitial],
    // ((XInitial - XFinal) == 2), (YInitial == YFinal));

    if(whitePawnsStart[YInitial] && ((XInitial - XFinal) == 2) && (YInitial == YFinal))
    {
        //we can move even 2 blocks if the path is free

        printf("Block ahead free: %d, 2 Blocks ahead free: %d\n", checkEmptyBlock(XInitial - 1, YInitial), checkEmptyBlock(XInitial - 2, YInitial));

        if(checkEmptyBlock(XInitial - 1, YInitial) && checkEmptyBlock(XInitial - 2, YInitial))
        {
            whitePawnsStart[YInitial] = 0;

            return true;
        }
    }


    if(blackPawnsStart[YInitial] && ((XFinal - XInitial) == 2) && (YFinal == YInitial))
    {
        //now we can move 2 square blocks if the path is empty

        if(checkEmptyBlock(XInitial + 1, YInitial) && checkEmptyBlock(XInitial + 2, YInitial))
        {
            blackPawnsStart[YInitial] = 0;

            return true;
        }
    }

    return false;
}

bool checkOneBlockPawnMovement(int XInitial, int YInitial, int XFinal, int YFinal)
{
    if(checkEmptyBlock(XFinal, YInitial) && (YFinal == YInitial) && abs(XInitial - XFinal) == 1)
    {
        return true;
    }

    return false;
}

bool attackPawn(int XInitial, int YInitial, int XFinal, int YFinal)
{
    /*
    FOR WHITE PAWNS
        we check if the diagonal coordinates related to the initial positions are
        either: x - 1, j - 1 OR x - 1, j + 1
    FOR BLACK PAWNS
        we check the coordinates which can be 
        either: x + 1, j - 1 OR x + 1, j + 1
    */

   //check if the pawn is white
    if( (((XInitial - 1) == XFinal) && ((YInitial - 1) == YFinal))
        || (((XInitial - 1) == XFinal) && ((YInitial + 1) == YFinal)))
    {
            //the pawn is white now
            //now we check if there is a piece in the final position to attack

            if(!checkEmptyBlock(XFinal, YFinal))
            {
                return true;
            }
    }

    //check if the pawn is black
    if( (((XInitial + 1) == XFinal) && ((YInitial - 1) == YFinal)) 
        || (((XInitial + 1) == XFinal) && (YInitial + 1 == YFinal)))
        {
            if(!checkEmptyBlock(XFinal, YFinal))
            {
                return true;
            }
        }

    return false;
}

bool checkPawnMovement(const char *initialPosition, const char *finalPosition)
{
    printf("POWER PAWN\n");

    /*
        Can move only straight forward and only 1 square

        Exceptions:
            1) Pawns capture diagonally 1 square
            2) First move
            3) En Passant
            4) Promotion
    */

    //convert the coordinates from char to valid coordinates from the matrix
    int XInitialCoordinate = (initialPosition[1] - '0');
    int YInitialCoordinate = (initialPosition[0] - 'a') + 1;

    int XFinalCoordinate = (finalPosition[1] - '0');
    int YFinalCoordinate = (finalPosition[0] - 'a') + 1;
    
    if(checkTwoBlocksPawnMovement(XInitialCoordinate, YInitialCoordinate, XFinalCoordinate, YFinalCoordinate))
    {
        return true;
    }
    else
    {
        if(checkOneBlockPawnMovement(XInitialCoordinate, YInitialCoordinate, XFinalCoordinate, YFinalCoordinate))
        {
            return true;
        }
        else
        {
            if(attackPawn(XInitialCoordinate, YInitialCoordinate, XFinalCoordinate, YFinalCoordinate))
            {
                return true;
            }
        }
    }

    return false;
}

/*
    in this function we check if the final position is a valid option
    we need to create 6 umbrella functions for each piece
*/
bool checkFinalPosition(const char * initalPosition, const char *finalPosition)
{
    unsigned YInitialcoordinate = (initalPosition[0] - 'a') + 1;

    unsigned XInitialcoordinate = (initalPosition[1] - '0'); 

    printf("Coordinates: x = %d, y =  %d\n", XInitialcoordinate, YInitialcoordinate);

    unsigned pieceType = chess_board[XInitialcoordinate][YInitialcoordinate];

    switch (pieceType)
    {
        // we handle both kings in a function to check their final position availability
        case 0x2654:
            case 0x265A:
            {
                printf("Let's check this kings\n");
                return checkKingMovement(initalPosition, finalPosition);
                break;
            }

        // we handle both queens in an single function
        case 0x2655:
            case 0x265B:
            {
                printf("Let's check this queens\n");
                return checkQueenMovement(initalPosition, finalPosition);
                break;
            }
        
        // we handle rooks in this part
        case 0x2656:
            case 0x265C:
            {
                printf("Let's check this rooks\n");
                return checkRookMovement(initalPosition, finalPosition);
                break;
            }

        //here we handle the bishops movement on the chess board
        case 0x2657:
            case 0x265D:
            {
                printf("Let's check this bishops\n");
                return checkBishopMovement(initalPosition, finalPosition);
                break;
            }

        //now we take care of the knights
        case 0x2658:
            case 0x265E:
            {
                printf("Let's check this knights\n");
                return checkKnightMovement(initalPosition, finalPosition);
                break;
            }

        //handle all pawns
        case 0x2659:
            case 0x265F:
            {
                printf("Let's check this pawns\n");
                return checkPawnMovement(initalPosition, finalPosition);
                break;
            }

        default:
        {
            break;
        }
    }
}

// main funuction for user input movement
bool checkMovement(const char piece[], const char initialPosition[], const char finalPosition[], unsigned int movement)
{
    // printf("Piece: %s, initial pos: %s, final pos: %s\n", piece, initialPosition, finalPosition);

    // printf("Checking: piece = %d, initialPosition = %d, finalPosition = %d\n", checkPieceType(piece) , checkInitialPosition(initialPosition, piece, movement) , checkFinalPosition(initialPosition, finalPosition));
    
    if(checkPieceType(piece))
    {
        if(checkInitialPosition(initialPosition, piece, movement))
        {
            if(checkFinalPosition(initialPosition, finalPosition))
            {
                return true;
            }
        }
    }

    return false;
}

void makeMoveOnBoard(int XInitial, int YInitial, int XFinal, int YFinal)
{
    chess_board[XFinal][YFinal] = chess_board[XInitial][YInitial];

    chess_board[XInitial][YInitial] = 0;
}

bool movementHandler(unsigned int movement)
{
    char userOptionPiece[10], userOptionInitialPosition[3], userOptionFinalPosition[3];

    if(scanf("%12s %3s %3s", userOptionPiece, userOptionInitialPosition, userOptionFinalPosition) == 3)
    {
        printf("Piece: %s, I: %s, F: %s\n", userOptionPiece,userOptionInitialPosition, userOptionFinalPosition);
        
        if(checkMovement(userOptionPiece, userOptionInitialPosition, userOptionFinalPosition, movement))
        {
            int XInitialCoordinate = (userOptionInitialPosition[1] - '0');
            int YInitialCoordinate = (userOptionInitialPosition[0] - 'a') + 1;

            int XFinalCoordinate = (userOptionFinalPosition[1] - '0');
            int YFinalCoordinate = (userOptionFinalPosition[0] - 'a') + 1;

            makeMoveOnBoard(XInitialCoordinate, YInitialCoordinate, XFinalCoordinate, YFinalCoordinate);

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