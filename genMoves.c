#include "checkMoves.h"

typedef struct _node
{
	int XInitial;
    int YInitial;

    int XFinal;
    int YFinal;
	struct _node *next;

}node;

node *head, *tail;

node *create_node(int xi, int yi, int xf, int yf)
{
    node *p = (node *) malloc(sizeof(node));

    if (p == NULL)
    {
        perror("Error allocating memory!");

        exit(0);
    }

    p -> XInitial = xi;

    p -> YInitial = yi;

    p -> XFinal = xf;
 
    p -> YInitial = yf;

    return p;
}

void print()
{
    node *current;

    if (head == NULL)
    {
        printf("Empty list!\n");
    }
    else
    {
        for (current = head; current != NULL; current = current->next)
        {
            printf("Xi coord: %d, Yi coord: %d, Xf coord: %d, Yf coord: %d\n",
                current -> XInitial, current -> YInitial, current ->XFinal, current->YFinal);
        }
    }
}

void add_to_back(node *node_to_add)
{
    if (tail == NULL)
    {
        head = node_to_add;
    }
    else
    {
        tail->next = node_to_add;
    }

    tail = node_to_add;

    node_to_add->next = NULL;
}

void delete()
{
    node *current = head;

    node *nextNode = NULL;

    while(current != NULL)
    {
        nextNode = current -> next;

        free(current);

        current = nextNode;
    }

    head = NULL;

    tail = NULL;
}

bool checkIsWhitePiece(int x, int y)
{
    int piece = chess_board[x][y];

    if(piece == white_KING || piece == white_BISHOP || piece == white_KNIGHT
    || piece == white_QUEEN || piece == white_PAWN || piece == white_ROOK)
    {
        return true;
    }

    return false;
}

int whitePawnsStatus[9][9];

int finalMoveX, finalMoveY;

void initPawnsStatus()
{
    for(int i = 1; i <= 8; ++ i)
    {
        for(int j = 1; j <= 8; ++ j)
        {
            if(i == 2)
            {
                whitePawnsStatus[i][j] = 1;
            }
            else
            {
                whitePawnsStatus[i][j] = 0;
            }
        }
    }
}

void generatePawnMoves(int x, int y)
{
    int finalMoveX, finalMoveY;

    printf("Here we generate the pawn moves\n");

    // check if we can move 2 positions
    if (whitePawnsStatus[x][y])
    {
        // want to move 2 blocks ahead

        if (checkEmptyBlock(x - 1, y) && checkEmptyBlock(x - 2, y))
        {
            finalMoveX = x + 2;
            finalMoveY = y;
            whitePawnsStatus[x][y] = 0;

            // at each new move we add to the moves list to store them
            node *newNode = create_node(x, y, finalMoveX, finalMoveY);

            add_to_back(newNode);
        }
    }
    else
    {
        //we check if we can move one block up
        finalMoveX = x - 1;
        finalMoveY = y;

        if(checkEmptyBlock(finalMoveX, finalMoveY))
        {
            node *newNode = create_node(x, y, finalMoveX, finalMoveY);

            add_to_back(newNode);
        }
        else
        {
            //we can attack diagonally that is (x - 1, y + 1) and (x - 1, y - 1)

            finalMoveX = x - 1;
            finalMoveY = y + 1;

            if(attackPawn(x, y, finalMoveX, finalMoveY))
            {
                node *newNode = create_node(x, y, finalMoveX, finalMoveY);

                add_to_back(newNode);
            }   
            else
            {
                finalMoveX = x - 1;
                finalMoveY = y - 1;

                if(attackPawn(x, y, finalMoveX, finalMoveY))
                {
                    node *newNode = create_node(x, y, finalMoveX, finalMoveY);

                    add_to_back(newNode);
                }   
            }
        }
    }
}

void generateRookMoves(int x, int y)
{
    printf("Here we generate the rook moves\n");
}

void generateKnightMoves(int x, int y)
{
    printf("Here we generate the knigth moves\n");
}

void generateBishopMoves(int x, int y)
{
    printf("Here we generate the bishop moves\n");
}

void generateKingMoves(int x, int y)
{
    printf("Here we generate the king moves\n");
}

void generateQueenMoves(int x, int y)
{
    printf("Here we generate the queen moves\n");
}


void handlePieceType(int x, int y)
{
   int piece = chess_board[x][y];

   switch (piece)
   {
        case white_PAWN:
        {
            generatePawnMoves(x, y);
            break;
        }

        case white_ROOK:
        {
            generateRookMoves(x, y);
            break;
        }

        case white_KNIGHT:
        {
            generateKnightMoves(x, y);
            break;
        }

        case white_BISHOP:
        {
            generateBishopMoves(x, y);
            break;
        }

        case white_KING:
        {
            generateKingMoves(x, y);
            break;
        }

        case white_QUEEN:
        {
            generateQueenMoves(x, y);
            break;
        }
   } 
}

void movementComputer()
{
    //we need to iterate through all the possible white pieces of chess

    for(int i = 1; i <= 8; ++ i)
    {
        for(int j = 1; j <= 8; ++ j)
        {
            if(checkIsWhitePiece(i, j))
            {
                handlePieceType(i, j);
            }
        }
    }
}