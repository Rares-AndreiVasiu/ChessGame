#include "checkMoves.h"

typedef struct _node
{
    int XInitial;
    int YInitial;

    int XFinal;
    int YFinal;

    int score;
    struct _node *next;

} node;

node *head, *tail;

node *create_node(int xi, int yi, int xf, int yf, int points)
{
    node *p = (node *)malloc(sizeof(node));

    if (p == NULL)
    {
        perror("Error allocating memory!");

        exit(0);
    }

    p->XInitial = xi;

    p->YInitial = yi;

    p->XFinal = xf;

    p->YInitial = yf;

    p->score = points;

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
            printf("Xi coord: %d, Yi coord: %d, Xf coord: %d, Yf coord: %d, Score: %d\n",
                   current->XInitial, current->YInitial, current->XFinal, current->YFinal,
                   current->score);
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

    while (current != NULL)
    {
        nextNode = current->next;

        free(current);

        current = nextNode;
    }

    head = NULL;

    tail = NULL;
}

bool checkIsWhitePiece(int x, int y)
{
    int piece = chess_board[x][y];

    if (piece == white_KING || piece == white_BISHOP || piece == white_KNIGHT || piece == white_QUEEN || piece == white_PAWN || piece == white_ROOK)
    {
        return true;
    }

    return false;
}

int whitePawnsStatus[8][8];

int finalMoveX, finalMoveY;

void initPawnsStatus()
{
    for (int i = 1; i <= 8; ++i)
    {
        for (int j = 1; j <= 8; ++j)
        {
            if (i == 2)
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
            finalMoveX = x - 2;
            finalMoveY = y;

            whitePawnsStatus[x][y] = 0;

            // at each new move we add to the moves list to store them
            node *newNode = create_node(x, y, finalMoveX, finalMoveY, 1);

            add_to_back(newNode);
        }
    }
    else
    {
        // we check if we can move one block up
        finalMoveX = x - 1;
        finalMoveY = y;

        if (checkEmptyBlock(finalMoveX, finalMoveY))
        {
            node *newNode = create_node(x, y, finalMoveX, finalMoveY, 1);

            add_to_back(newNode);
        }
        else
        {
            // we can attack diagonally that is (x - 1, y + 1) and (x - 1, y - 1)

            finalMoveX = x - 1;
            finalMoveY = y + 1;

            if (attackPawn(x, y, finalMoveX, finalMoveY))
            {
                node *newNode = create_node(x, y, finalMoveX, finalMoveY, 1);

                add_to_back(newNode);
            }
            else
            {
                finalMoveX = x - 1;
                finalMoveY = y - 1;

                if (attackPawn(x, y, finalMoveX, finalMoveY))
                {
                    node *newNode = create_node(x, y, finalMoveX, finalMoveY, 1);

                    add_to_back(newNode);
                }
            }
        }
    }
}

void generateRookMoves(int x, int y)
{
    printf("Here we generate the rook moves\n");

    // generate the possible moves on the vertical line above

    int enemies = 0;

    bool flag = true;

    for (int i = 1; i < x && flag; ++i)
    {
        /*
            we loop though all the possible blocks
            but for a valid move
            we can take out max 1 opponent piece
            on our path
        */

        if (checkEmptyBlock(i, y) == false &&
            checkNotAllay(x, y, i, y) == false)
        {
            /*
                we have an allay on this path so we stop
                searching anymore for above possible paths
            */
            flag = false;
        }
        else
        {
            if (checkEmptyBlock(i, y) == false &&
                checkNotAllay(x, y, i, y) == true)
            {
                enemies++;
            }
        }

        if (enemies > 1)
        {
            /*
                if we want to attack more than 1 piece
                on a single iteration
            */
            flag = false;
        }
        else
        {
            if (enemies < 2 && flag)
            {
                node *newNode = create_node(x, y, i, y, 1);

                add_to_back(newNode);
            }
        }
    }

    // generate the possible moves on the vertical line below

    enemies = 0;

    flag = true;

    for (int i = x + 1; i <= 8 && flag; ++i)
    {
        if (checkEmptyBlock(i, y) == false && checkNotAllay(x, y, i, y) == false)
        {
            /*
                we found an allay so we stop searching for more positions
                on the below direction
            */
            flag = false;
        }
        else
        {
            if (checkEmptyBlock(i, y) == false &&
                checkNotAllay(x, y, i, y) == true)
            {
                enemies++;
            }
        }

        if (enemies > 1)
        {
            flag = false;
        }
        else
        {
            if (flag && enemies < 2)
            {
                node *newNode = create_node(x, y, i, y, 1);

                add_to_back(newNode);
            }
        }
    }

    // generate the possible moves on the horizontal lines to the left of rook

    enemies = 0;
    flag = true;

    for (int j = y - 1; j >= 1 && flag; --j)
    {
        if (checkEmptyBlock(x, j) == false && checkNotAllay(x, y, x, j) == false)
        {
            /*
                we have an allay on the way here so we don't need to search anymore
                for any possible moves
            */
            flag = false;
        }
        else
        {
            if (checkEmptyBlock(x, j) == false &&
                checkNotAllay(x, y, x, j) == true)
            {
                enemies++;
            }
        }

        if (enemies > 1)
        {
            flag = false;
        }
        else
        {
            if (enemies < 2 && flag)
            {
                node *newNode = create_node(x, y, x, j, 1);

                add_to_back(newNode);
            }
        }
    }

    enemies = 0;

    flag = true;

    for (int j = y + 1; j <= 8 && flag; ++j)
    {
        if (checkEmptyBlock(x, j) == false && checkNotAllay(x, y, x, j) == false)
        {
            /*
                we have an allay on the way here so we don't need to search anymore
                for any possible moves
            */
            flag = false;
        }
        else
        {
            if (checkEmptyBlock(x, j) == false &&
                checkNotAllay(x, y, x, j) == true)
            {
                enemies++;
            }
        }

        if (enemies > 1)
        {
            flag = false;
        }
        else
        {
            if (enemies < 2 && flag)
            {
                node *newNode = create_node(x, y, x, j, 1);

                add_to_back(newNode);
            }
        }
    }
}

void generateKnightMoves(int x, int y)
{
    printf("Here we generate the knigth moves\n");

    /*
        we can move in 8 directions either
    */

   int finalX, finalY;

   //x + 1, y

   finalX = x + 1;
   finalY = y;

   if(checkEmptyBlock(finalX, finalY) == false)
   {
   }
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
    // we need to iterate through all the possible white pieces of chess

    for (int i = 1; i <= 8; ++i)
    {
        for (int j = 1; j <= 8; ++j)
        {
            if (checkIsWhitePiece(i, j))
            {
                handlePieceType(i, j);
            }
        }
    }
}
