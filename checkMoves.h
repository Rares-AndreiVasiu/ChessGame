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

/*
    check if a block from the board is empty
    returns true if board[i][j] == 0, false otherwise;
*/


bool checkEmptyBlock(int i, int j)
{
    if(chess_board[i][j] == 0)
    {
        return true;
    }

    return false;
}

//returns true if you can step on an enemy piece, false otherwise
bool checkNotAllay(int Xi, int Yi, int Xf, int Yf)
{
    int piece = chess_board[Xi][Yi];

    if (piece == white_KNIGHT || piece == white_KING || piece == white_QUEEN 
    || piece == white_ROOK || piece == white_PAWN || piece == white_BISHOP)
    {
        int targetPiece = chess_board[Xf][Yf];

        if (targetPiece == black_PAWN || targetPiece == black_KNIGHT || targetPiece == black_BISHOP 
        || targetPiece == black_ROOK || targetPiece == black_QUEEN)
        {
            return true;
        }
    }
    else
    {
        if (piece == black_PAWN || piece == black_KNIGHT || piece == black_BISHOP || piece == black_ROOK 
        || piece == black_QUEEN || piece == black_KING)
        {
            int targetPiece = chess_board[Xf][Yf];

            if (targetPiece == white_KNIGHT || targetPiece == white_QUEEN 
            || targetPiece == white_ROOK || targetPiece == white_PAWN || targetPiece == white_BISHOP)
            {
                return true;
            }
        }
    }

    return false;
}

bool checkRookQueen(int Xi, int Yi, int Xf, int Yf)
{
    int king = chess_board[Xi][Yi];

    if(king == white_KING)
    {
        if(chess_board[Xf][Yf] == black_QUEEN || chess_board[Xf][Yf] == black_ROOK)
        {
            return true;
        }
    }
    else
    {
        if(chess_board[Xf][Yf] == white_QUEEN || chess_board[Xf][Yf] == white_ROOK)
        {
            return true;
        }
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


bool checkQueenBishopPawn(int Xi, int Yi, int Xf, int Yf)
{
    int king = chess_board[Xi][Yi];

    if(king == white_KING)
    {
        if(chess_board[Xf][Yf] == black_QUEEN || chess_board[Xf][Yf] == black_BISHOP)
        {
            return true;
        }
    }
    else
    {
        if(chess_board[Xf][Yf] == white_QUEEN || chess_board[Xf][Yf] == white_BISHOP)
        {
            return true;
        }
    }

    //we don't move on horiz or vertical

    if(Xi != Xf && Yi != Yf && abs(Xi - Xf) == 1 && abs(Yi - Yf) == 1)
    {
        if(king == white_KING)
        {
            //the pawn initial coordinates are the kings final coords
            //and the pawn finall coordinates are the kings initial coords
            if(chess_board[Xf][Yf] == black_PAWN && attackPawn(Xf, Yf, Xi, Yi))
            {
                return true;
            }
        }
        else
        {
            if(chess_board[Xf][Yf] == white_PAWN && attackPawn(Xf, Yf, Xi, Yi))
            {
                return true;
            }
        }
    }

    return false;
}

/*
    function which checks if we get check mate
*/
bool checkGameCheck(int Xi, int Yi, int Xf, int Yf)
{
    bool checkMate = false;

    /*
        we check for white enemies which can check us
        we check horrizontally for threats
    */

    // we can either have queens or rooks

    for (int j = 1; j < Yf; ++j) //leftside for rooks and queens
    {
        if (checkEmptyBlock(Xi, j) == false && checkRookQueen(Xi, Yi, Xf, Yf) == true)
        {
            printf("Left is busted\n");
            checkMate = true;
        }
    }

    for (int j = Yf + 1; j <= 8; ++j) // rightside for rooks and queens
    {
        if (checkEmptyBlock(Xi, j) == false && checkRookQueen(Xi, Yi, Xf, Yf) == true)
        {
            printf("Right is busted\n");
            checkMate = true;
        }
    }

    // we check for vertically queen and rook

    for (int i = 1; i < Xf; ++i) //above checking
    {
        if (checkEmptyBlock(i, Yi) == false && checkRookQueen(Xi, Yi, Xf, Yf) == true)
        {
            printf("Above is busted\n");
            checkMate = true;
        }
    }

    for (int i = Xf + 1; i <= 8; ++i) //below checking
    {
        if (checkEmptyBlock(i, Yi) == false && checkRookQueen(Xi, Yi, Xf, Yf) == true)
        {
            printf("Below is busted\n");
            checkMate = true;
        }
    }

    // we check for diagonal: bishops and queen and pawn

    int i = Xf - 1, j = Yf - 1;

    // check first diagonal
    while (i >= 1 && j >= 1)
    {
        if (checkEmptyBlock(i, j) == false && checkQueenBishopPawn(Xi, Yi, i, j) == true)
        {
            printf("Here is busted: %d %d\n", i, j);
            checkMate = true;
            break;
        }

        i--;

        j--;
    }

    i = Xf - 1, j = Yf + 1;

    while (i >= 1 && j <= 8)
    {
        if (checkEmptyBlock(i, j) == false && checkQueenBishopPawn(Xi, Yi, i, j) == true)
        {
            printf("Here is busted: %d %d\n", i, j);
            checkMate = true;
            break;
        }
        i--;
        
        j++;
    }

    i = Xf + 1, j = Yf - 1;

    while (i <= 8 && j >= 1)
    {
        if (checkEmptyBlock(i, j) == false && checkQueenBishopPawn(Xi, Yi, i, j) == true)
        {
            printf("Here is busted: %d %d\n", i, j);
            checkMate = true;
            break;
        }

        i++;

        j--;
    }

    i = Xf + 1, j = Yf + 1;

    while (i <= 8 && j <= 8)
    {
        if (checkEmptyBlock(i, j) == false && checkQueenBishopPawn(Xi, Yi, i, j) == true)
        {
            printf("Here is busted: %d %d\n", i, j);
            checkMate = true;
            break;
        }
        
        i++;

        j++;
    }

    return checkMate;
}

//the following function checks if you can move the king to finPos
bool checkKingMovement(const char *initialPosition, const char *finalPosition)
{
    printf("POWER KING\n");

    bool validKingMove = true;

    int XInitialCoordinate = (initialPosition[1] - '0');
    int YInitialCoordinate = (initialPosition[0] - 'a') + 1;

    int XFinalCoordinate = (finalPosition[1] - '0');
    int YFinalCoordinate = (finalPosition[0] - 'a') + 1;

    if( (XFinalCoordinate <= 8 && XFinalCoordinate >= 1) && (YFinalCoordinate <= 8 && YInitialCoordinate >= 1) &&
    abs(XInitialCoordinate - XFinalCoordinate) <= 1 && abs(YFinalCoordinate - YInitialCoordinate) <= 1)
    {
        //if we have an allay on path its an invalid move
        if(checkEmptyBlock(XFinalCoordinate, YFinalCoordinate) == false &&
        checkNotAllay(XInitialCoordinate, YInitialCoordinate, XFinalCoordinate, YFinalCoordinate) == false) 
        {
            validKingMove = false;
        }

        //if free space but we step in check its invalid move
        if(checkEmptyBlock(XFinalCoordinate, YFinalCoordinate) == true 
        && checkGameCheck(XInitialCoordinate, YInitialCoordinate, XFinalCoordinate, YFinalCoordinate) == true)
        {
            validKingMove = false;
        }
    }
    else
    {
        validKingMove = false;
    }

    return validKingMove;
}

bool isCheckMate(int XInitialCoordinate, int YInitialCoordinate)
{
    bool vals[] = {false, false, false, false, false, false, false, false};

    /*
        we check all possible movements available for the king
        x + 1, y ~
        x - 1, y ~

        x, y + 1 ~
        x, y - 1 ~

        x - 1, y + 1 ~
        x + 1, y + 1 ~

        x - 1, y - 1 ~
        x + 1, y - 1 ~
    */

    int XFinalCoordinate, YFinalCoordinate;

    // x + 1, y
    XFinalCoordinate = XInitialCoordinate + 1;
    YFinalCoordinate = YInitialCoordinate;

    vals[0] = checkGameCheck(XInitialCoordinate, YInitialCoordinate, XFinalCoordinate, YFinalCoordinate);

    // x - 1, y
    XFinalCoordinate = XInitialCoordinate - 1;
    YFinalCoordinate = YInitialCoordinate;

    vals[1] = checkGameCheck(XInitialCoordinate, YInitialCoordinate, XFinalCoordinate, YFinalCoordinate);

    // x, y + 1
    XFinalCoordinate = XInitialCoordinate;
    YFinalCoordinate = YInitialCoordinate + 1;

    vals[2] = checkGameCheck(XInitialCoordinate, YInitialCoordinate, XFinalCoordinate, YFinalCoordinate);

    // x, y - 1
    XFinalCoordinate = XInitialCoordinate;
    YFinalCoordinate = YInitialCoordinate - 1;

    vals[3] = checkGameCheck(XInitialCoordinate, YInitialCoordinate, XFinalCoordinate, YFinalCoordinate);

    // x - 1, y + 1
    XFinalCoordinate = XInitialCoordinate - 1;
    YFinalCoordinate = YInitialCoordinate + 1;

    vals[4] = checkGameCheck(XInitialCoordinate, YInitialCoordinate, XFinalCoordinate, YFinalCoordinate);

    //x + 1, y + 1
    XFinalCoordinate = XInitialCoordinate + 1;
    YFinalCoordinate = YInitialCoordinate + 1;

    vals[5] = checkGameCheck(XInitialCoordinate, YInitialCoordinate, XFinalCoordinate, YFinalCoordinate);

    //x - 1, y - 1
    XFinalCoordinate = XInitialCoordinate - 1;
    YFinalCoordinate = YInitialCoordinate - 1;

    vals[6] = checkGameCheck(XInitialCoordinate, YInitialCoordinate, XFinalCoordinate, YFinalCoordinate);

    //x + 1, y - 1
    XFinalCoordinate = XInitialCoordinate + 1;
    YFinalCoordinate = YInitialCoordinate - 1;

    vals[7] = checkGameCheck(XInitialCoordinate, YInitialCoordinate, XFinalCoordinate, YFinalCoordinate);

    for(int i = 0; i < 8; ++ i)
    {
        if(vals[i] == false)
        {
            return false;
        }
    }

    return true;
}

void EndGame()
{
    int xW, yW;
    int xB, yB;

    for(int i = 1; i <= 8; ++ i)
    {
        for(int j = 1; j <= 8; ++ i)
        {
            if(chess_board[i][j] == white_KING)
            {
                xW = i;
                yW = j;
            }

            if(chess_board[i][j] == black_KING)
            {
                xB = i;

                yB = j;
            }
        }
    }

    if(isCheckMate(xW, yW))
    {
        endOfTheLine = true;

        printf("Black Wins!");
    }
    
    if(isCheckMate(xB, yB))
    {
        endOfTheLine = true;

        printf("White Wins!");
    }
}

//the following function checks if you can move the queen to finPos
bool checkQueenMovement(const char *initialPosition, const char *finalPosition)
{
    printf("POWER QUEEN\n");

    int XInitialCoordinate = (initialPosition[1] - '0');
    int YInitialCoordinate = (initialPosition[0] - 'a') + 1;

    int XFinalCoordinate = (finalPosition[1] - '0');
    int YFinalCoordinate = (finalPosition[0] - 'a') + 1;

    if ( ( (abs(XInitialCoordinate - XFinalCoordinate) == abs(YInitialCoordinate - YFinalCoordinate)) 
        || (XInitialCoordinate == XFinalCoordinate || YFinalCoordinate == YInitialCoordinate) )
        && ( (XFinalCoordinate <= 8 && XFinalCoordinate >= 1) && (YFinalCoordinate <= 8 && YInitialCoordinate >= 1) ) )
    {
        bool validQueenMove = true;

        // we check if queen moves horrizontally
        if (XInitialCoordinate == XFinalCoordinate)
        {
            if (YInitialCoordinate < YFinalCoordinate) // we move right
            {
                puts("WE move to the right!");

                for (int j = YInitialCoordinate + 1; j <= YFinalCoordinate && validQueenMove; ++j)
                {
                    if (checkEmptyBlock(XInitialCoordinate, j) == false && checkNotAllay(XInitialCoordinate, YInitialCoordinate, XInitialCoordinate, j) == false) //if we have an allay on path
                    {
                        validQueenMove = false;
                        break;
                    }
                    else
                    {
                        if(checkEmptyBlock(XInitialCoordinate, j) == false && checkNotAllay(XInitialCoordinate, YInitialCoordinate, XInitialCoordinate, j) == true
                        && j != YFinalCoordinate) //if we have a enemy piece on path but not at destination
                        {
                            validQueenMove = false;
                            break;
                        }
                    }
                }
            }
            else
            {
                puts("We move to the left");
                // move to the left
                for (int j = YInitialCoordinate - 1; j >= YFinalCoordinate && validQueenMove; --j)
                {
                    if (checkEmptyBlock(XInitialCoordinate, j) == false && checkNotAllay(XInitialCoordinate, YInitialCoordinate, XInitialCoordinate, j) == false)
                    {
                        validQueenMove = false;
                        break;
                    }
                    else
                    {
                        if(checkEmptyBlock(XInitialCoordinate, j) == false && checkNotAllay(XInitialCoordinate, YInitialCoordinate, XInitialCoordinate, j) == true &&
                        j != YFinalCoordinate)
                        {
                            validQueenMove = false;
                            break;
                        }
                    }
                }
            }
        }
        else
        {
            // check if we move vertically
            if (YInitialCoordinate == YFinalCoordinate)
            {
                printf("We move vertically\n");
                // now we check for clear road

                if (XInitialCoordinate < XFinalCoordinate) // check if we move downwards
                {
                    puts("We move downwards!");

                    // we move more than 1 block on the chess board
                    for (int i = XInitialCoordinate + 1; i <= XFinalCoordinate && validQueenMove; ++i)
                    {
                        if (checkEmptyBlock(i, YInitialCoordinate) == false && checkNotAllay(XInitialCoordinate, YInitialCoordinate, i, YInitialCoordinate) == false)
                        {
                            printf("Here is not empty: %d %d\n", i, YInitialCoordinate);

                            validQueenMove = false;
                            break;
                        }
                        else
                        {
                            if(checkEmptyBlock(i, YInitialCoordinate) == false && checkNotAllay(XInitialCoordinate, YInitialCoordinate, i, YInitialCoordinate) == true &&
                            i != XFinalCoordinate)
                            {
                                validQueenMove = false;
                                break;
                            }
                        }
                    }
                }
                else
                {
                    puts("We move upwards!");

                    for (int i = XInitialCoordinate - 1; i >= XFinalCoordinate && validQueenMove; --i)
                    {
                        if (checkEmptyBlock(i, YInitialCoordinate) == false && checkNotAllay(XInitialCoordinate, YInitialCoordinate, i, YInitialCoordinate) == false)
                        {
                            printf("Here is not empty: %d %d\n", i, YInitialCoordinate);

                            validQueenMove = false;

                            break;
                        }
                        else
                        {
                            if(checkEmptyBlock(i, YInitialCoordinate) == false && checkNotAllay(XInitialCoordinate, YInitialCoordinate, i, YInitialCoordinate) == true &&
                            i != XFinalCoordinate)
                            {
                                validQueenMove = false;
                                break;
                            }
                        }
                    }
                }
            }
            else
            {
                // check if we move on diagonals

                /*
                    We have 4 cases
                        =>  1-st quadrant: x1 > x2, y1 < y2
                */

                if (XInitialCoordinate > XFinalCoordinate && YInitialCoordinate < YFinalCoordinate)
                {
                    puts("We are in case 1!");

                    int i = XInitialCoordinate - 1;

                    int j = YInitialCoordinate + 1;

                    while (i >= XFinalCoordinate && j <= YFinalCoordinate)
                    {
                        if (checkEmptyBlock(i, j) == false && checkNotAllay(XInitialCoordinate, YInitialCoordinate, i, j) == false)
                        {
                            printf("Here is not empty: %d %d\n", i, j);

                            validQueenMove = false;

                            break;
                        }
                        else
                        {
                            if(checkEmptyBlock(i, j) == false && checkNotAllay(XInitialCoordinate, YInitialCoordinate, i, j) == true && 
                            i != XFinalCoordinate && j != YFinalCoordinate)
                            {
                                validQueenMove = false;

                                break;
                            }
                        }

                        i--;
                        j++;

                    }
                }
                else
                {
                    /*
                            => 2-st quadrant: x1 > x2, y1 > y2
                    */
                    if (XInitialCoordinate > XFinalCoordinate && YInitialCoordinate > YFinalCoordinate)
                    {
                        puts("We are in case 2!");

                        int i = XInitialCoordinate - 1;

                        int j = YInitialCoordinate - 1;

                        while(i >= XFinalCoordinate && j >= YFinalCoordinate)
                        {
                            if(checkEmptyBlock(i, j) == false && checkNotAllay(XInitialCoordinate, YInitialCoordinate, i, j) == false)
                            {
                                printf("Here is not empty: %d %d\n", i, j);

                                validQueenMove = false;
                                
                                break;
                            }
                            else
                            {
                                if(checkEmptyBlock(i, j) == false && checkNotAllay(XInitialCoordinate, YInitialCoordinate, i, j) == true &&
                                i != XFinalCoordinate && j != YFinalCoordinate)
                                {
                                    validQueenMove = false;
                                    break;
                                }
                            }

                            i--;
                            j--;
                        }
                    }
                    else
                    {
                        /*
                                => 3-rd quadrant: x1 < x2, y1 > y2
                        */

                        if (XInitialCoordinate < XFinalCoordinate && YInitialCoordinate > YFinalCoordinate)
                        {
                            int i = XInitialCoordinate + 1;

                            int j = YInitialCoordinate - 1;

                            while (i <= XFinalCoordinate && j >= YFinalCoordinate)
                            {
                                if (checkEmptyBlock(i, j) == false && checkNotAllay(XInitialCoordinate, YInitialCoordinate, i, j) == false)
                                {
                                    printf("Here is not empty: %d %d\n", i, j);

                                    validQueenMove = false;

                                    break;
                                }
                                else
                                {
                                    if(checkEmptyBlock(i, j) == false && checkNotAllay(XInitialCoordinate, YInitialCoordinate, i, j) == true && 
                                    i != XFinalCoordinate && j != YFinalCoordinate)
                                    {
                                        validQueenMove = false;
                                        
                                        break;
                                    }
                                }

                                i++;
                                j--;
                            }
                        }

                        else
                        {
                            /*
                                => 4-th quadrant: x1 < x2, y1 < y2
                            */

                            if (XInitialCoordinate < XFinalCoordinate && YInitialCoordinate < YFinalCoordinate)
                            {
                                int i = XInitialCoordinate + 1;

                                int j = YInitialCoordinate + 1;

                                while (i <= XFinalCoordinate && j <= YFinalCoordinate)
                                {
                                    if (checkEmptyBlock(i, j) == false && checkNotAllay(XInitialCoordinate, YInitialCoordinate, i, j) == false)
                                    {
                                        printf("Here is not empty: %d %d\n", i, j);

                                        validQueenMove = false;

                                        break;
                                    }
                                    else
                                    {
                                        if(checkEmptyBlock(i, j) == false && checkNotAllay(XInitialCoordinate, YInitialCoordinate, i, j) == true &&
                                        i != XFinalCoordinate && j != YFinalCoordinate)
                                        {
                                            validQueenMove = false;

                                            break;
                                        }
                                    }

                                    i++;

                                    j++;
                                }
                            }
                        }
                    }
                }
            }
        }

        return validQueenMove;
    }
    else
    {
        return false;
    }
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

    if ( (XFinalCoordinate <= 8 && XFinalCoordinate >= 1) && (YFinalCoordinate <= 8 && YInitialCoordinate >= 1) )
    {
        // first check to move online horizontally
        if (XInitialCoordinate == XFinalCoordinate)
        {
            printf("We move horrizontally\n");

            // now to check for clear road
            if (YInitialCoordinate < YFinalCoordinate)
            {
                puts("We move to the right!");

                for (int j = YInitialCoordinate + 1; j <= YFinalCoordinate && validMove; ++j)
                {
                    if (checkEmptyBlock(XInitialCoordinate, j) == false && checkNotAllay(XInitialCoordinate, YInitialCoordinate, XFinalCoordinate, j) == false)
                    {
                        printf("Here is not empty: %d %d\n", XInitialCoordinate, j);
                        
                        validMove = false;
                    }
                    else
                    {
                        if(checkEmptyBlock(XInitialCoordinate, j) == false && checkNotAllay(XInitialCoordinate, YInitialCoordinate, XFinalCoordinate, j) == true &&
                        j != YFinalCoordinate)
                        {
                            validMove = false;
                        }
                    }
                }
            }
            else
            {
                puts("We move to the left!");

                for (int j = YInitialCoordinate - 1; j >= YFinalCoordinate && validMove; --j)
                {
                    if (checkEmptyBlock(XInitialCoordinate, j) == false && checkNotAllay(XInitialCoordinate, YInitialCoordinate, XFinalCoordinate, j) == false)
                    {
                        printf("Here is not empty: %d %d\n", XInitialCoordinate, j);
                        
                        validMove = false;
                    }
                    else
                    {
                        if(checkEmptyBlock(XInitialCoordinate, j) == false && checkNotAllay(XInitialCoordinate, YInitialCoordinate, XFinalCoordinate, j) == true &&
                        j != YFinalCoordinate)
                        {
                            validMove = false;
                        }
                    }
                }
            }
        }
        else
        {
            if (YInitialCoordinate == YFinalCoordinate)
            {
                // now we check for clear road

                if (XInitialCoordinate < XFinalCoordinate)
                {
                    printf("We move down vertically\n");

                    for (int i = XInitialCoordinate + 1; i <= XFinalCoordinate && validMove; ++i)
                    {
                        if (checkEmptyBlock(i, YInitialCoordinate) == false && checkNotAllay(XInitialCoordinate, YInitialCoordinate, i, YInitialCoordinate) == false)
                        {
                            printf("Here is not empty: %d %d\n", i, YInitialCoordinate);

                            validMove = false;
                        }
                        else
                        {
                            if(checkEmptyBlock(i, YInitialCoordinate) == false && checkNotAllay(XInitialCoordinate, YInitialCoordinate, i, YInitialCoordinate) == true &&
                            i != XFinalCoordinate)
                            {
                                validMove = false;
                            }
                        }
                    }
                }
                else
                {
                    puts("We move up vertically!");

                    for (int i = XInitialCoordinate - 1; i >= XFinalCoordinate && validMove; --i)
                    {
                        if (checkEmptyBlock(i, YInitialCoordinate) == false && checkNotAllay(XInitialCoordinate, YInitialCoordinate, i, YInitialCoordinate) == false)
                        {
                            printf("Here is not empty: %d %d\n", i, YInitialCoordinate);

                            validMove = false;
                        }
                        else
                        {
                            if(checkEmptyBlock(i, YInitialCoordinate) == false && checkNotAllay(XInitialCoordinate, YInitialCoordinate, i, YInitialCoordinate) == true &&
                            i != XFinalCoordinate)
                            {
                                validMove = false;
                            }
                        }
                    }
                }
            }
            else
            {
                validMove = false;
            }
        }
    }
    else
    {
        validMove = false;
    }

    return validMove;
}

//the following function checks if you can move the king to finPos
bool checkBishopMovement(const char *initialPosition, const char *finalPosition)
{
    printf("POWER BISHOP\n");

    int XInitialCoordinate = (initialPosition[1] - '0');
    int YInitialCoordinate = (initialPosition[0] - 'a') + 1;

    int XFinalCoordinate = (finalPosition[1] - '0');
    int YFinalCoordinate = (finalPosition[0] - 'a') + 1;

    bool validBishopMove = true;

    bool flagCase = false;

    if ((abs(XInitialCoordinate - XFinalCoordinate) == abs(YInitialCoordinate - YFinalCoordinate)) && ((XFinalCoordinate <= 8 && XFinalCoordinate >= 1) && (YFinalCoordinate <= 8 && YInitialCoordinate >= 1)))
    {
        // check if we move on diagonals

        /*
            We have 4 cases
                =>  1-st quadrant: x1 < x2, y1 > y2
        */

        //we need to separate this case into white stepping bishops and black stepping bishops
        
        int bishopColour = -1;

        if(chess_board[XInitialCoordinate][YInitialCoordinate] == white_BISHOP)
        {
            bishopColour = WHITE;
        }
        
        if(chess_board[XInitialCoordinate][YInitialCoordinate] == black_BISHOP)
        {
            bishopColour = BLACK;
        }

        if (XInitialCoordinate > XFinalCoordinate && YInitialCoordinate < YFinalCoordinate)
        {
            /*
                    => first quadrant: x1 > x2, y1 < y2
            */

            puts("We are in case 1!");

            int i = XInitialCoordinate - 1;

            int j = YInitialCoordinate + 1;

            while (i >= XFinalCoordinate && j <= YFinalCoordinate)
            {
                if (checkEmptyBlock(i, j) == false && checkNotAllay(XInitialCoordinate, YInitialCoordinate, i, j) == false)
                {
                    printf("Here is not empty: %d %d\n", i, j);

                    validBishopMove = false;

                    break;
                }
                else
                {
                    if(checkEmptyBlock(i, j) == false && checkNotAllay(XInitialCoordinate, YInitialCoordinate, i, j) == true && 
                    i != XFinalCoordinate && j != YFinalCoordinate)
                    {
                        validBishopMove = false;

                        break;
                    }
                }

                if ((chess_board[i][j] == white_SQUARE && WHITE != bishopColour) || (chess_board[i][j] == black_SQUARE && BLACK != bishopColour))
                {
                    printf("Here is not matching block: %d %d\n", i, j);

                    validBishopMove = false;

                    break;
                }

                i--;

                j++;
            }
            flagCase = true;
        }
        else
        {
            /*
                    => 2-st quadrant: x1 > x2, y1 > y2
            */
            if (XInitialCoordinate > XFinalCoordinate && YInitialCoordinate > YFinalCoordinate)
            {
                puts("We are in case 2!");

                int i = XInitialCoordinate - 1;

                int j = YInitialCoordinate - 1;

                while (i >= XFinalCoordinate && j >= YFinalCoordinate)
                {
                    if (checkEmptyBlock(i, j) == false && checkNotAllay(XInitialCoordinate, YInitialCoordinate, i, j) == false)
                    {
                        printf("Here is not empty: %d %d\n", i, j);

                        validBishopMove = false;

                        break;
                    }
                    else
                    {
                        if(checkEmptyBlock(i, j) == false && checkNotAllay(XInitialCoordinate, YInitialCoordinate, i, j) == true &&
                        i != XFinalCoordinate && j != YFinalCoordinate)
                        {
                            validBishopMove = false;

                            break;
                        }
                    }

                    if ((chess_board[i][j] == white_SQUARE && WHITE != bishopColour) || (chess_board[i][j] == black_SQUARE && BLACK != bishopColour))
                    {
                        printf("Here is not matching block: %d %d\n", i, j);

                        validBishopMove = false;

                        break;
                    }
                    flagCase = true;

                    i--;

                    j--;
                }
            }
            else
            {
                /*
                        => 3-rd quadrant: x1 < x2, y1 > y2
                */

                if (XInitialCoordinate < XFinalCoordinate && YInitialCoordinate > YFinalCoordinate)
                {
                    int i = XInitialCoordinate + 1;

                    int j = YInitialCoordinate - 1;

                    while (i <= XFinalCoordinate && j >= YFinalCoordinate)
                    {
                        if (checkEmptyBlock(i, j) == false && checkNotAllay(XInitialCoordinate, YInitialCoordinate, i, j) == false)
                        {
                            printf("Here is not empty: %d %d\n", i, j);

                            validBishopMove = false;

                            break;
                        }
                        else
                        {
                            if(checkEmptyBlock(i, j) == false && checkNotAllay(XInitialCoordinate, YInitialCoordinate, i, j) == true &&
                            i != XFinalCoordinate && j != YFinalCoordinate)
                            {
                                validBishopMove = false;

                                break;
                            }
                        }

                        if ((chess_board[i][j] == white_SQUARE && WHITE != bishopColour) || (chess_board[i][j] == black_SQUARE && BLACK != bishopColour))
                        {
                            printf("Here is not matching block: %d %d\n", i, j);

                            validBishopMove = false;

                            break;
                        }

                        flagCase = true;

                        i++;

                        j--;
                    }
                }

                else
                {
                    /*
                        => 4-th quadrant: x1 < x2, y1 < y2
                    */

                    if (XInitialCoordinate < XFinalCoordinate && YInitialCoordinate < YFinalCoordinate)
                    {
                        int i = XInitialCoordinate + 1;

                        int j = YInitialCoordinate + 1;

                        while (i <= XFinalCoordinate && j <= YFinalCoordinate)
                        {
                            if (checkEmptyBlock(i, j) == false && checkNotAllay(XInitialCoordinate, YInitialCoordinate, i, j) == false)
                            {
                                printf("Here is not empty: %d %d\n", i, j);

                                validBishopMove = false;

                                break;
                            }
                            else
                            {
                                if(checkEmptyBlock(i, j) == false && checkNotAllay(XInitialCoordinate, YInitialCoordinate, i, j) == true &&
                                i != XFinalCoordinate && j != YFinalCoordinate)
                                {
                                    validBishopMove = false;

                                    break;
                                }
                            }

                            if ((chess_board[i][j] == white_SQUARE && WHITE != bishopColour) || (chess_board[i][j] == black_SQUARE && BLACK != bishopColour))
                            {
                                printf("Here is not matching block: %d %d\n", i, j);

                                validBishopMove = false;

                                break;
                            }
                            
                            flagCase = true;

                            i++;

                            j++;
                        }
                    }
                    else
                    {
                        validBishopMove = false;
                    }
                }
            }
        }
    }
    else
    {
        validBishopMove = false;
    }

    if(!flagCase)
    {
        validBishopMove = false;
    }

    return validBishopMove;
}

bool checkKnightMovement(const char *initialPosition, const char *finalPosition)
{
    printf("POWER KNIGHT\n");

    int XInitialCoordinate = (initialPosition[1] - '0');
    int YInitialCoordinate = (initialPosition[0] - 'a') + 1;

    int XFinalCoordinate = (finalPosition[1] - '0');
    int YFinalCoordinate = (finalPosition[0] - 'a') + 1;

    if( (XFinalCoordinate <= 8 && XFinalCoordinate >= 1)
     && (YFinalCoordinate <= 8 && YFinalCoordinate >= 1) 
     && ( ((abs(XInitialCoordinate - XFinalCoordinate) == 1) && (abs(YFinalCoordinate - YInitialCoordinate) == 2)) 
     || ((abs(XFinalCoordinate - XInitialCoordinate) == 2) && (abs(YFinalCoordinate - YInitialCoordinate) == 1)) ) )
    {
        if (checkEmptyBlock(XFinalCoordinate, YFinalCoordinate))
        {
            return true;
        }

        if (checkEmptyBlock(XFinalCoordinate, YFinalCoordinate) == false &&
            checkNotAllay(XInitialCoordinate, YInitialCoordinate, XFinalCoordinate, YFinalCoordinate) == true)
        {
            return true;
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

    if ( (XFinalCoordinate <= 8 && XFinalCoordinate >= 1) && (YFinalCoordinate <= 8 && YFinalCoordinate >= 1) )
    {
        if (checkTwoBlocksPawnMovement(XInitialCoordinate, YInitialCoordinate, XFinalCoordinate, YFinalCoordinate))
        {
            return true;
        }
        else
        {
            if (checkOneBlockPawnMovement(XInitialCoordinate, YInitialCoordinate, XFinalCoordinate, YFinalCoordinate))
            {
                return true;
            }
            else
            {
                if (attackPawn(XInitialCoordinate, YInitialCoordinate, XFinalCoordinate, YFinalCoordinate))
                {
                    return true;
                }
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
