#include "utils.h"

typedef struct _node
{
    int XInitial;
    int YInitial;

    int XFinal;
    int YFinal;

    int step;

    float score;
    struct _node *next;

} node;

node *head, *tail;

node *create_node(int xi, int yi, int xf, int yf, int movement)
{
    node *p = (node *)malloc(sizeof(node));

    if (p == NULL)
    {
        perror("Error allocating memory!");

        exit(0);
    }

    p -> XInitial = xi;

    p -> YInitial = yi;

    p -> XFinal = xf;

    p -> YFinal = yf;

    p -> step = movement;

    p -> score = 0;// we set the score to 0 because we will calculate it later

    return p;
}

float pieceCounter(int finalX, int finalY);

void print()
{
    node *current;

    if (head == NULL)
    {
        // printf("Empty list!\n");
    }
    else
    {
        int index = 0;

        for (current = head; current != NULL; current = current->next)
        {
            index ++;
            printf( "%d) Xi coord: %d, Yi coord: %d, Xf coord: %d, Yf coord: %d, mobility: %d, score: %f\n",index,
                   current->XInitial, current->YInitial, current->XFinal, current->YFinal, current->step, current ->score);

            //printf("Piece counter: %f\n",pieceCounter(current->XFinal, current->YFinal));
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

bool checkExistingPieceMovement(int x, int y)
{
    node *current;

    if (head == NULL)
    {
        // printf("Empty list!\n");
    }
    else
    {
        for (current = head; current != NULL; current = current->next)
        {
            if(current -> XInitial == x && current -> YInitial == y)
            {
                return true;
            }
        }
    }

    return false;
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

int finalMoveX, finalMoveY;

void initPawnsStatus()
{
    for (int i = 1; i <= 8; ++i)
    {
        whitePawnsStatus[i] = 7;
    }
}

void setMobility(int x, int y, int mobilty)
{
    node *current;

    if (head == NULL)
    {
        // printf("Empty list!\n");
    }
    else
    {
        for (current = head; current != NULL; current = current->next)
        {
            if(current -> XInitial == x && current -> YInitial == y)
            {
                current -> step = mobilty;
            }
        }
    }
}

void printPossibleMove(int Xi, int Yi, int Xf, int Yf)
{
    // printf("Start pos: %d %d, End pos: %d %d\n", Xi, Yi, Xf, Yf);
    return;
}

void generatePawnMoves(int x, int y)
{
    int finalMoveX, finalMoveY;

    // printf("Here we generate the pawn moves\n");

    // check if we can move 2 positions
    if (whitePawnsStatus[y] == 7)
    {
        // want to move 2 blocks ahead

        if (checkEmptyBlock(x - 1, y) && checkEmptyBlock(x - 2, y))
        {
            finalMoveX = x - 2;
            finalMoveY = y;

            // at each new move we add to the moves list to store them
            node *newNode = create_node(x, y, finalMoveX, finalMoveY, 1);

            add_to_back(newNode);

            // whitePawnsStatus[y] = finalMoveX;
        }
    }

    // or if we want to move only one block up
    finalMoveX = x - 1;
    finalMoveY = y;

    if (checkEmptyBlock(finalMoveX, finalMoveY))
    {
        node *newNode = create_node(x, y, finalMoveX, finalMoveY, 1);

        add_to_back(newNode);

        // whitePawnsStatus[y] = finalMoveX;

        // printPossibleMove(x, y, finalMoveX, finalMoveY);
    }

    // we can attack diagonally that is (x - 1, y + 1) and (x - 1, y - 1)

    finalMoveX = x - 1;

    finalMoveY = y + 1;

    if (attackPawn(x, y, finalMoveX, finalMoveY))
    {
        node *newNode = create_node(x, y, finalMoveX, finalMoveY, 1);

        add_to_back(newNode);

        // whitePawnsStatus[y] = finalMoveX;

        // printPossibleMove(x, y, finalMoveX, finalMoveY);
    }
    else
    {
        finalMoveX = x - 1;
        finalMoveY = y - 1;

        if (attackPawn(x, y, finalMoveX, finalMoveY))
        {
            node *newNode = create_node(x, y, finalMoveX, finalMoveY, 1);

            add_to_back(newNode);

            // whitePawnsStatus[y] = finalMoveX;

            // printPossibleMove(x, y, finalMoveX, finalMoveY);
        }
    }
}

int blackPawnMobility(int x, int y)
{
    int finalMoveX, finalMoveY;

    int mobility = 0;

    // printf("Here we generate the pawn moves\n");

    // check if we can move 2 positions
    if (blackPawnsStart[y])
    {
        // want to move 2 blocks ahead

        if (checkEmptyBlock(x + 1, y) && checkEmptyBlock(x + 2, y))
        {
            // at each new move we add to the moves list to store them
            // node *newNode = create_node(x, y, finalMoveX, finalMoveY, 1);

            // add_to_back(newNode);

            // whitePawnsStatus[y] = finalMoveX;

            mobility++;
        }

        // or if we want to move only one block up
        finalMoveX = x + 1;
        finalMoveY = y;

        if (checkEmptyBlock(finalMoveX, finalMoveY))
        {
            // node *newNode = create_node(x, y, finalMoveX, finalMoveY, 1);

            // add_to_back(newNode);

            // whitePawnsStatus[y] = finalMoveX;

            // printPossibleMove(x, y, finalMoveX, finalMoveY);

            mobility++;
        }
        else
        {
            // we can attack diagonally that is (x + 1, y + 1) and (x + 1, y - 1)

            finalMoveX = x + 1;
            finalMoveY = y + 1;

            if (attackPawn(x, y, finalMoveX, finalMoveY))
            {
                // node *newNode = create_node(x, y, finalMoveX, finalMoveY, 1);

                // add_to_back(newNode);

                mobility++;

                // whitePawnsStatus[y] = finalMoveX;

                // printPossibleMove(x, y, finalMoveX, finalMoveY);
            }
            else
            {
                finalMoveX = x + 1;
                finalMoveY = y - 1;

                if (attackPawn(x, y, finalMoveX, finalMoveY))
                {
                    // node *newNode = create_node(x, y, finalMoveX, finalMoveY, 1);

                    // add_to_back(newNode);

                    mobility++;

                    // whitePawnsStatus[y] = finalMoveX;

                    // printPossibleMove(x, y, finalMoveX, finalMoveY);
                }
            }
        }
    }
    else
    {
        // we check if we can move one block up
        finalMoveX = x + 1;
        finalMoveY = y;

        if (checkEmptyBlock(finalMoveX, finalMoveY))
        {
            // node *newNode = create_node(x, y, finalMoveX, finalMoveY, 1);

            // add_to_back(newNode);

            mobility++;

            // whitePawnsStatus[y] = finalMoveX;

            // printPossibleMove(x, y, finalMoveX, finalMoveY);
        }
        else
        {
            // we can attack diagonally that is (x + 1, y + 1) and (x + 1, y - 1)

            finalMoveX = x + 1;
            finalMoveY = y + 1;

            if (attackPawn(x, y, finalMoveX, finalMoveY))
            {
                // node *newNode = create_node(x, y, finalMoveX, finalMoveY, 1);

                // add_to_back(newNode);

                // whitePawnsStatus[y] = finalMoveX;

                mobility++;

                // printPossibleMove(x, y, finalMoveX, finalMoveY);
            }
            else
            {
                finalMoveX = x + 1;
                finalMoveY = y - 1;

                if (attackPawn(x, y, finalMoveX, finalMoveY))
                {
                    // whitePawnsStatus[y] = finalMoveX;

                    // node *newNode = create_node(x, y, finalMoveX, finalMoveY, 1);

                    // add_to_back(newNode);

                    // printPossibleMove(x, y, finalMoveX, finalMoveY);

                    mobility++;
                }
            }
        }
    }

    return mobility;
}

void generateRookMoves(int x, int y)
{
    // printf("Here we generate the rook moves\n");

    // generate the possible moves on the vertical line above
    for (int i = 1; i < x; ++ i)
    {
        char initialPosition[] = "a1";
        char finalPosition[] = "a1";

        initialPosition[1] = x + '0';
        initialPosition[0] = y + 'a' - 1;

        finalPosition[1] = i + '0';
        finalPosition[0] = y + 'a' - 1;

        if(checkRookMovement(initialPosition, finalPosition))
        {
            node *newNode = create_node(x, y, i, y, x - i);

            add_to_back(newNode);

            printPossibleMove(x, y, i, y);
        }
        else
        {
            break;
        }
    }

    // generate the possible moves on the vertical line below

    for (int i = x + 1; i <= 8; ++i)
    {
        char initialPosition[] = "a1";
        char finalPosition[] = "a1";

        initialPosition[1] = x + '0';
        initialPosition[0] = y + 'a' - 1;

        finalPosition[1] = i + '0';
        finalPosition[0] = y + 'a' - 1;
        
        if(checkRookMovement(initialPosition, finalPosition))
        {
            node *newNode = create_node(x, y, i, y, i - x);

            add_to_back(newNode);

            printPossibleMove(x, y, i, y);
        }
        else
        {
            break;
        }
    }

    // generate the possible moves on the horizontal lines to the left of rook

    for (int j = 1; j < y; ++ j)
    {
        char initialPosition[] = "a1";
        char finalPosition[] = "a1";

        initialPosition[1] = x + '0';
        initialPosition[0] = y + 'a' - 1;

        finalPosition[1] = x + '0';
        finalPosition[0] = j + 'a' - 1;

        if(checkRookMovement(initialPosition, finalPosition))
        {
            node *newNode = create_node(x, y, x, j, y - j);

            add_to_back(newNode);

            printPossibleMove(x, y, x, j);
        }
        else
        {
            break;
        }
    }

    for (int j = y + 1; j <= 8; ++j)
    {
        char initialPosition[] = "a1";
        char finalPosition[] = "a1";

        initialPosition[1] = x + '0';
        initialPosition[0] = y + 'a' - 1;

        finalPosition[1] = x + '0';
        finalPosition[0] = j + 'a' - 1;

        if (checkRookMovement(initialPosition, finalPosition))
        {
            node *newNode = create_node(x, y, x, j, j - y);

            add_to_back(newNode);

            printPossibleMove(x, y, x, j);
        }
        else
        {
            break;
        }
    }
}

int blackRookMobility(int x, int y)
{
    // printf("Here we generate the rook moves\n");

    int mobility = 0;

    // generate the possible moves on the vertical line above
    for (int i = 1; i < x; ++ i)
    {
        char initialPosition[] = "a1";
        char finalPosition[] = "a1";

        initialPosition[1] = x + '0';
        initialPosition[0] = y + 'a' - 1;

        finalPosition[1] = i + '0';
        finalPosition[0] = y + 'a' - 1;

        if(checkRookMovement(initialPosition, finalPosition))
        {
            // node *newNode = create_node(x, y, i, y, x - i);

            // add_to_back(newNode);?

            // printPossibleMove(x, y, i, y);

            mobility++;
        }
        else
        {
            break;
        } 
    }

    // generate the possible moves on the vertical line below

    for (int i = x + 1; i <= 8; ++i)
    {
        char initialPosition[] = "a1";
        char finalPosition[] = "a1";

        initialPosition[1] = x + '0';
        initialPosition[0] = y + 'a' - 1;

        finalPosition[1] = i + '0';
        finalPosition[0] = y + 'a' - 1;
        
        if(checkRookMovement(initialPosition, finalPosition))
        {
            // node *newNode = create_node(x, y, i, y, i - x);

            // add_to_back(newNode);

            // printPossibleMove(x, y, i, y);

            mobility++;
        }
        else
        {
            break;
        }
    }

    // generate the possible moves on the horizontal lines to the left of rook

    for (int j = 1; j < y; ++ j)
    {
        char initialPosition[] = "a1";
        char finalPosition[] = "a1";

        initialPosition[1] = x + '0';
        initialPosition[0] = y + 'a' - 1;

        finalPosition[1] = x + '0';
        finalPosition[0] = j + 'a' - 1;

        if(checkRookMovement(initialPosition, finalPosition))
        {
            // node *newNode = create_node(x, y, x, j, y - j);

            // add_to_back(newNode);

            // printPossibleMove(x, y, x, j);

            mobility++;
        }
        else
        {
            break;
        }
    }

    for (int j = y + 1; j <= 8; ++j)
    {
        char initialPosition[] = "a1";
        char finalPosition[] = "a1";

        initialPosition[1] = x + '0';
        initialPosition[0] = y + 'a' - 1;

        finalPosition[1] = x + '0';
        finalPosition[0] = j + 'a' - 1;

        if (checkRookMovement(initialPosition, finalPosition))
        {
            // node *newNode = create_node(x, y, x, j, j - y);

            // add_to_back(newNode);

            // printPossibleMove(x, y, x, j);

            mobility++;
        }
        else
        {
            break;
        }
    }

    return mobility;
}

void generateKnightMoves(int x, int y)
{
    // printf("Here we generate the knigth moves\n");

    //we generate all the 8 possible L movements

    char initialPosition[] = "a1";
    char finalPosition[] = "a1";

    initialPosition[1] = x + '0';
    initialPosition[0] = y + 'a' - 1;

    //case 1, we L to the left up and down
    finalPosition[1] = (x - 1) + '0';
    finalPosition[0] = (y - 2) + 'a' - 1; //move up

    if(checkKnightMovement(initialPosition, finalPosition))
    {
        node *newNode = create_node(x, y, x - 1, y - 2, 3);

        add_to_back(newNode);

        printPossibleMove(x, y, x - 1, y - 2);
    }

    finalPosition[1] = (x + 1) + '0';
    finalPosition[0] = (y - 2) + 'a' - 1; //move down

    if(checkKnightMovement(initialPosition, finalPosition))
    {
        node *newNode = create_node(x, y, x + 1, y - 2, 3);

        add_to_back(newNode);

        printPossibleMove(x, y, x + 1, y - 2);
    }

    //case 2, we L to the right up and down

    finalPosition[1] = (x - 1) + '0';
    finalPosition[0] = (y + 2) + 'a' - 1; // move up

    if(checkKnightMovement(initialPosition, finalPosition))
    {
        node *newNode = create_node(x, y, x - 1, y + 2, 3);

        add_to_back(newNode);

        printPossibleMove(x, y, x - 1, y + 2);
    } 

    finalPosition[1] = (x + 1) + '0';
    finalPosition[0] = (y + 2) + 'a' - 1; // move down

    if(checkKnightMovement(initialPosition, finalPosition))
    {
        node *newNode = create_node(x, y, x + 1, y + 2, 3);

        add_to_back(newNode);

        printPossibleMove(x, y, x + 1, y + 2);
    }  


    //case 3 we move L in up

    finalPosition[1] = (x - 2) + '0';
    finalPosition[0] = (y - 1) + 'a' - 1; //on the left

    if(checkKnightMovement(initialPosition, finalPosition))
    {
        node *newNode = create_node(x, y, x - 2, y - 1, 3);

        add_to_back(newNode);

        printPossibleMove(x, y, x - 2, y - 1);
    }

    finalPosition[1] = (x - 2) + '0';
    finalPosition[0] = (y + 1) + 'a' - 1; //on the right

    if(checkKnightMovement(initialPosition, finalPosition))
    {
        node *newNode = create_node(x, y, x - 2, y + 1, 3);

        add_to_back(newNode);

        printPossibleMove(x, y, x - 2, y + 1);
    }   

    //case 4: we move L downwords

    finalPosition[1] = (x + 2) + '0';
    finalPosition[0] = (y - 1) + 'a' - 1; //on the left

    if(checkKnightMovement(initialPosition, finalPosition))
    {
        node *newNode = create_node(x, y, x + 2, y - 1, 3);

        add_to_back(newNode);

        printPossibleMove(x, y, x + 2, y - 1);
    }  

    finalPosition[1] = (x + 2) + '0';
    finalPosition[0] = (y + 1) + 'a' - 1; //on the right

    if(checkKnightMovement(initialPosition, finalPosition))
    {
        node *newNode = create_node(x, y, x + 2, y + 1, 3);

        add_to_back(newNode);

        printPossibleMove(x, y, x + 2, y + 1);
    }
}

int blackKnightMoblity(int x, int y)
{
    // printf("Here we generate the knigth moves\n");

    //we generate all the 8 possible L movements

    char initialPosition[] = "a1";
    char finalPosition[] = "a1";

    initialPosition[1] = x + '0';
    initialPosition[0] = y + 'a' - 1;

    //case 1, we L to the left up and down
    finalPosition[1] = (x - 1) + '0';
    finalPosition[0] = (y - 2) + 'a' - 1; //move up

    int mobility = 0;

    if(checkKnightMovement(initialPosition, finalPosition))
    {
        // node *newNode = create_node(x, y, x - 1, y - 2, 3);

        // add_to_back(newNode);

        // printPossibleMove(x, y, x - 1, y - 2);

        mobility++;
    }

    finalPosition[1] = (x + 1) + '0';
    finalPosition[0] = (y - 2) + 'a' - 1; //move down

    if(checkKnightMovement(initialPosition, finalPosition))
    {
        // node *newNode = create_node(x, y, x + 1, y - 2, 3);

        // add_to_back(newNode);

        // printPossibleMove(x, y, x + 1, y - 2);

        mobility++;
    }

    //case 2, we L to the right up and down

    finalPosition[1] = (x - 1) + '0';
    finalPosition[0] = (y + 2) + 'a' - 1; // move up

    if(checkKnightMovement(initialPosition, finalPosition))
    {
        // node *newNode = create_node(x, y, x - 1, y + 2, 3);

        // add_to_back(newNode);

        // printPossibleMove(x, y, x - 1, y + 2);

        mobility++;
    } 

    finalPosition[1] = (x + 1) + '0';
    finalPosition[0] = (y + 2) + 'a' - 1; // move down

    if(checkKnightMovement(initialPosition, finalPosition))
    {
        // node *newNode = create_node(x, y, x + 1, y + 2, 3);

        // add_to_back(newNode);

        // printPossibleMove(x, y, x + 1, y + 2);

        mobility++;
    }  


    //case 3 we move L in up

    finalPosition[1] = (x - 2) + '0';
    finalPosition[0] = (y - 1) + 'a' - 1; //on the left

    if(checkKnightMovement(initialPosition, finalPosition))
    {
        // node *newNode = create_node(x, y, x - 2, y - 1, 3);

        // add_to_back(newNode);

        // printPossibleMove(x, y, x - 2, y - 1);

        mobility++;
    }

    finalPosition[1] = (x - 2) + '0';
    finalPosition[0] = (y + 1) + 'a' - 1; //on the right

    if(checkKnightMovement(initialPosition, finalPosition))
    {
        // node *newNode = create_node(x, y, x - 2, y + 1, 3);

        // add_to_back(newNode);

        // printPossibleMove(x, y, x - 2, y + 1);

        mobility++;
    }   

    //case 4: we move L downwords

    finalPosition[1] = (x + 2) + '0';
    finalPosition[0] = (y - 1) + 'a' - 1; //on the left

    if(checkKnightMovement(initialPosition, finalPosition))
    {
        // node *newNode = create_node(x, y, x + 2, y - 1, 3);

        // add_to_back(newNode);

        // printPossibleMove(x, y, x + 2, y - 1);

        mobility++;
    }  

    finalPosition[1] = (x + 2) + '0';
    finalPosition[0] = (y + 1) + 'a' - 1; //on the right

    if(checkKnightMovement(initialPosition, finalPosition))
    {
        // node *newNode = create_node(x, y, x + 2, y + 1, 3);

        // add_to_back(newNode);

        // printPossibleMove(x, y, x + 2, y + 1);

        mobility++;
    }

    return mobility;
}

void generateBishopMoves(int x, int y)
{
    // printf("Here we generate the bishop moves\n");

    char initialPosition[] = "a1";
    char finalPosition[] = "a1";

    initialPosition[1] = x + '0';
    initialPosition[0] = y + 'a' - 1;

    int downRightX = x, downRightY = y;

    int counter = 0;

    while(downRightX <= 8 && downRightY <= 8)
    {
        counter ++;

        downRightX ++;
        downRightY ++;

        finalPosition[1] = downRightX + '0';
        finalPosition[0] = downRightY + 'a' - 1;

        if(checkBishopMovement(initialPosition, finalPosition))
        {
            node *newNode = create_node(x, y, downRightX, downRightY, counter);

            add_to_back(newNode);

            printPossibleMove(x, y, downRightX, downRightY);
        }
        else
        {
            //if we have an invalid movement we exit
            break;
        }
    }   

    //now we move diagonally down on the left
    int downLeftX = x, downLeftY = y;

    counter = 0;

    while(downLeftX <= 8 && downLeftY >= 1)
    {
        counter ++;
        
        downLeftX ++;
        downLeftY --;

        finalPosition[1] = downLeftX + '0';
        finalPosition[0] = downLeftY + 'a' - 1;

        if(checkBishopMovement(initialPosition, finalPosition))
        {
            node *newNode = create_node(x, y, downLeftX, downLeftY, counter);

            add_to_back(newNode);

            printPossibleMove(x, y, downLeftX, downLeftY);
        }
        else
        {
            break;
        }
    }

    //now we move diagonally up on the right

    int upRightX = x, upRightY = y;

    counter = 0;

    while(upRightX >= 1 && upRightY <= 8)
    {
        counter ++;

        upRightX --;

        upRightY ++;

        finalPosition[1] = upRightX + '0';
        finalPosition[0] = upRightY + 'a' - 1;

        if(checkBishopMovement(initialPosition, finalPosition))
        {
            node *newNode = create_node(x, y, upRightX, upRightY, counter);

            add_to_back(newNode);

            printPossibleMove(x, y, upRightX, upRightY);
        }
        else
        {
            break;
        }
    }

    int upLeftX = x, upLeftY = y;

    counter = 0;

    while (upLeftX >= 1 && upLeftY >= 1)
    {
        counter++;

        upLeftX--;

        upLeftY--;

        finalPosition[1] = upLeftX + '0';
        finalPosition[0] = upLeftY + 'a' - 1;

        if (checkBishopMovement(initialPosition, finalPosition))
        {
            node *newNode = create_node(x, y, upLeftX, upLeftY, counter);

            add_to_back(newNode);

            printPossibleMove(x, y, upLeftX, upLeftY);
        }
        else
        {
            break;
        }
    }
}

int blackBishopMobility(int x, int y)
{
    // printf("Here we generate the bishop moves\n");

    char initialPosition[] = "a1";
    char finalPosition[] = "a1";

    initialPosition[1] = x + '0';
    initialPosition[0] = y + 'a' - 1;

    int downRightX = x, downRightY = y;

    int counter = 0;

    int mobility = 0;

    while(downRightX <= 8 && downRightY <= 8)
    {
        counter ++;

        downRightX ++;
        downRightY ++;

        finalPosition[1] = downRightX + '0';
        finalPosition[0] = downRightY + 'a' - 1;

        if(checkBishopMovement(initialPosition, finalPosition))
        {
            // node *newNode = create_node(x, y, downRightX, downRightY, counter);

            // add_to_back(newNode);

            // printPossibleMove(x, y, downRightX, downRightY);

            mobility++;
        }
        else
        {
            break;
        }
    }   

    //now we move diagonally down on the left
    int downLeftX = x, downLeftY = y;

    counter = 0;

    while(downLeftX <= 8 && downLeftY >= 1)
    {
        counter ++;
        
        downLeftX ++;
        downLeftY --;

        finalPosition[1] = downLeftX + '0';
        finalPosition[0] = downLeftY + 'a' - 1;

        if(checkBishopMovement(initialPosition, finalPosition))
        {
            // node *newNode = create_node(x, y, downLeftX, downLeftY, counter);

            // add_to_back(newNode);

            // printPossibleMove(x, y, downLeftX, downLeftY);

            mobility++;
        }
        else
        {
            break;
        }
    }

    //now we move diagonally up on the right

    int upRightX = x, upRightY = y;

    counter = 0;

    while(upRightX >= 1 && upRightY <= 8)
    {
        counter ++;

        upRightX --;

        upRightY ++;

        finalPosition[1] = upRightX + '0';
        finalPosition[0] = upRightY + 'a' - 1;

        if(checkBishopMovement(initialPosition, finalPosition))
        {
            // node *newNode = create_node(x, y, upRightX, upRightY, counter);

            // add_to_back(newNode);

            // printPossibleMove(x, y, upRightX, upRightY);

            mobility++;
        }
        else
        {
            break;
        }
    }

    int upLeftX = x, upLeftY = y;

    counter = 0;

    while (upLeftX >= 1 && upLeftY >= 1)
    {
        counter++;

        upLeftX--;

        upLeftY--;

        finalPosition[1] = upLeftX + '0';
        finalPosition[0] = upLeftY + 'a' - 1;

        if (checkBishopMovement(initialPosition, finalPosition))
        {
            // node *newNode = create_node(x, y, upLeftX, upLeftY, counter);

            // add_to_back(newNode);

            // printPossibleMove(x, y, upLeftX, upLeftY);

            mobility++;
        }
        else
        {
            break;
        }
    }

    return mobility;
}

void generateQueenMoves(int x, int y)
{
    // printf("Here we generate the queen moves\n");

    //we can copy paste the code from bishop
    //since the queen is just a combo of rook and bishop
    char initialPosition[] = "a1";
    char finalPosition[] = "a1";

    initialPosition[1] = x + '0';
    initialPosition[0] = y + 'a' - 1;

    int downRightX = x, downRightY = y;

    int counter = 0;

    while(downRightX <= 8 && downRightY <= 8)
    {
        counter ++;

        downRightX ++;
        downRightY ++;

        finalPosition[1] = downRightX + '0';
        finalPosition[0] = downRightY + 'a' - 1;

        if(checkQueenMovement(initialPosition, finalPosition))
        {
            node *newNode = create_node(x, y, downRightX, downRightY, counter);

            add_to_back(newNode);

            printPossibleMove(x, y, downRightX, downRightY);
        }
        else
        {
            break;
        }
    }   

    //now we move diagonally down on the left
    int downLeftX = x, downLeftY = y;

    counter = 0;

    while(downLeftX <= 8 && downLeftY >= 1)
    {
        counter ++;
        
        downLeftX ++;
        downLeftY --;

        finalPosition[1] = downLeftX + '0';
        finalPosition[0] = downLeftY + 'a' - 1;

        if(checkQueenMovement(initialPosition, finalPosition))
        {
            node *newNode = create_node(x, y, downLeftX, downLeftY, counter);

            add_to_back(newNode);

            printPossibleMove(x, y, downLeftX, downLeftY);
        }
        else
        {
            break;
        }
    }

    //now we move diagonally up on the right

    int upRightX = x, upRightY = y;

    counter = 0;

    while(upRightX >= 1 && upRightY <= 8)
    {
        counter ++;

        upRightX --;

        upRightY ++;

        finalPosition[1] = upRightX + '0';
        finalPosition[0] = upRightY + 'a' - 1;

        if(checkQueenMovement(initialPosition, finalPosition))
        {
            node *newNode = create_node(x, y, upRightX, upRightY, counter);

            add_to_back(newNode);

            printPossibleMove(x, y, upRightX, upRightY);
        }
        else
        {
            break;
        }
    }

    int upLeftX = x, upLeftY = y;

    counter = 0;

    while (upLeftX >= 1 && upLeftY >= 1)
    {
        counter++;

        upLeftX--;

        upLeftY--;

        finalPosition[1] = upLeftX + '0';
        finalPosition[0] = upLeftY + 'a' - 1;

        if (checkQueenMovement(initialPosition, finalPosition))
        {
            node *newNode = create_node(x, y, upLeftX, upLeftY, counter);

            add_to_back(newNode);

            printPossibleMove(x, y, upLeftX, upLeftY);
        }
        else
        {
            break;
        }
    }

    //now we generate the rook-ish movement

    // generate the possible moves on the vertical line above
    for (int i = 1; i < x; ++ i)
    {
        char initialPosition[] = "a1";
        char finalPosition[] = "a1";

        initialPosition[1] = x + '0';
        initialPosition[0] = y + 'a' - 1;

        finalPosition[1] = i + '0';
        finalPosition[0] = y + 'a' - 1;

        if(checkQueenMovement(initialPosition, finalPosition))
        {
            node *newNode = create_node(x, y, i, y, x - i);

            add_to_back(newNode);

            printPossibleMove(x, y, i, y);
        }
        else
        {
            break;
        }
    }

    // generate the possible moves on the vertical line below

    for (int i = x + 1; i <= 8; ++i)
    {
        char initialPosition[] = "a1";
        char finalPosition[] = "a1";

        initialPosition[1] = x + '0';
        initialPosition[0] = y + 'a' - 1;

        finalPosition[1] = i + '0';
        finalPosition[0] = y + 'a' - 1;
        
        if(checkQueenMovement(initialPosition, finalPosition))
        {
            node *newNode = create_node(x, y, i, y, i - x);

            add_to_back(newNode);

            printPossibleMove(x, y, i, y);
        }
        else
        {
            break;
        }
    }

    // generate the possible moves on the horizontal lines to the left of rook

    for (int j = 1; j < y; ++ j)
    {
        char initialPosition[] = "a1";
        char finalPosition[] = "a1";

        initialPosition[1] = x + '0';
        initialPosition[0] = y + 'a' - 1;

        finalPosition[1] = x + '0';
        finalPosition[0] = j + 'a' - 1;

        if(checkQueenMovement(initialPosition, finalPosition))
        {
            node *newNode = create_node(x, y, x, j, y - j);

            add_to_back(newNode);

            printPossibleMove(x, y, x, j);
        }
        else
        {
            break;
        }
    }

    for (int j = y + 1; j <= 8; ++j)
    {
        char initialPosition[] = "a1";
        char finalPosition[] = "a1";

        initialPosition[1] = x + '0';
        initialPosition[0] = y + 'a' - 1;

        finalPosition[1] = x + '0';
        finalPosition[0] = j + 'a' - 1;

        if (checkQueenMovement(initialPosition, finalPosition))
        {
            node *newNode = create_node(x, y, x, j, j - y);

            add_to_back(newNode);

            printPossibleMove(x, y, x, j);
        }
        else
        {
            break;
        }
    }
}

int blackQueenMobility(int x, int y)
{
    // printf("Here we generate the queen moves\n");

    //we can copy paste the code from bishop
    //since the queen is just a combo of rook and bishop
    char initialPosition[] = "a1";
    char finalPosition[] = "a1";

    initialPosition[1] = x + '0';
    initialPosition[0] = y + 'a' - 1;

    int downRightX = x, downRightY = y;

    int counter = 0;

    int mobility = 0;

    while(downRightX <= 8 && downRightY <= 8)
    {
        counter ++;

        downRightX ++;
        downRightY ++;

        finalPosition[1] = downRightX + '0';
        finalPosition[0] = downRightY + 'a' - 1;

        if(checkQueenMovement(initialPosition, finalPosition))
        {
            // node *newNode = create_node(x, y, downRightX, downRightY, counter);

            // add_to_back(newNode);

            // printPossibleMove(x, y, downRightX, downRightY);

            mobility++;
        }
        else
        {
            break;
        }
    }   

    //now we move diagonally down on the left
    int downLeftX = x, downLeftY = y;

    counter = 0;

    while(downLeftX <= 8 && downLeftY >= 1)
    {
        counter ++;
        
        downLeftX ++;
        downLeftY --;

        finalPosition[1] = downLeftX + '0';
        finalPosition[0] = downLeftY + 'a' - 1;

        if(checkQueenMovement(initialPosition, finalPosition))
        {
            // node *newNode = create_node(x, y, downLeftX, downLeftY, counter);

            // add_to_back(newNode);

            // printPossibleMove(x, y, downLeftX, downLeftY);

            mobility++;
        }
        else
        {
            break;
        }
    }

    //now we move diagonally up on the right

    int upRightX = x, upRightY = y;

    counter = 0;

    while(upRightX >= 1 && upRightY <= 8)
    {
        counter ++;

        upRightX --;

        upRightY ++;

        finalPosition[1] = upRightX + '0';
        finalPosition[0] = upRightY + 'a' - 1;

        if(checkQueenMovement(initialPosition, finalPosition))
        {
            // node *newNode = create_node(x, y, upRightX, upRightY, counter);

            // add_to_back(newNode);

            // printPossibleMove(x, y, upRightX, upRightY);

            mobility++;
        }
        else
        {
            break;
        }
    }

    int upLeftX = x, upLeftY = y;

    counter = 0;

    while (upLeftX >= 1 && upLeftY >= 1)
    {
        counter++;

        upLeftX--;

        upLeftY--;

        finalPosition[1] = upLeftX + '0';
        finalPosition[0] = upLeftY + 'a' - 1;

        if (checkQueenMovement(initialPosition, finalPosition))
        {
            // node *newNode = create_node(x, y, upLeftX, upLeftY, counter);

            // add_to_back(newNode);

            // printPossibleMove(x, y, upLeftX, upLeftY);

            mobility++;
        }
        else
        {
            break;
        }
    }

    //now we generate the rook-ish movement

    // generate the possible moves on the vertical line above
    for (int i = 1; i < x; ++ i)
    {
        char initialPosition[] = "a1";
        char finalPosition[] = "a1";

        initialPosition[1] = x + '0';
        initialPosition[0] = y + 'a' - 1;

        finalPosition[1] = i + '0';
        finalPosition[0] = y + 'a' - 1;

        if(checkQueenMovement(initialPosition, finalPosition))
        {
            // node *newNode = create_node(x, y, i, y, x - i);

            // add_to_back(newNode);

            // printPossibleMove(x, y, i, y);

            mobility++;
        }
        else
        {
            break;
        }
    }

    // generate the possible moves on the vertical line below

    for (int i = x + 1; i <= 8; ++i)
    {
        char initialPosition[] = "a1";
        char finalPosition[] = "a1";

        initialPosition[1] = x + '0';
        initialPosition[0] = y + 'a' - 1;

        finalPosition[1] = i + '0';
        finalPosition[0] = y + 'a' - 1;
        
        if(checkQueenMovement(initialPosition, finalPosition))
        {
            // node *newNode = create_node(x, y, i, y, i - x);

            // add_to_back(newNode);

            // printPossibleMove(x, y, i, y);

            mobility++;
        }
        else
        {
            break;
        }
    }

    // generate the possible moves on the horizontal lines to the left of rook

    for (int j = 1; j < y; ++ j)
    {
        char initialPosition[] = "a1";
        char finalPosition[] = "a1";

        initialPosition[1] = x + '0';
        initialPosition[0] = y + 'a' - 1;

        finalPosition[1] = x + '0';
        finalPosition[0] = j + 'a' - 1;

        if(checkQueenMovement(initialPosition, finalPosition))
        {
            // node *newNode = create_node(x, y, x, j, y - j);

            // add_to_back(newNode);

            // printPossibleMove(x, y, x, j);

            mobility++;
        }
        else
        {
            break;
        }
    }

    for (int j = y + 1; j <= 8; ++j)
    {
        char initialPosition[] = "a1";
        char finalPosition[] = "a1";

        initialPosition[1] = x + '0';
        initialPosition[0] = y + 'a' - 1;

        finalPosition[1] = x + '0';
        finalPosition[0] = j + 'a' - 1;

        if (checkQueenMovement(initialPosition, finalPosition))
        {
            // node *newNode = create_node(x, y, x, j, j - y);

            // add_to_back(newNode);

            // printPossibleMove(x, y, x, j);

            mobility++;
        }
        else
        {
            break;
        }
    }

    return mobility;
}

void generateKingMoves(int x, int y)
{
    // printf("Here we generate the king moves\n");

    char initialPosition[] = "a1";
    char finalPosition[] = "a1";

    //the king can move in all 8 adjacent directions
    initialPosition[1] = x + '0';
    initialPosition[0] = y + 'a' - 1;

    //we move to N
    finalPosition[1] = (x - 1) + '0';
    finalPosition[0] = y + 'a' - 1;

    if (checkKingMovement(initialPosition, finalPosition))
    {
        node *newNode = create_node(x, y, x - 1, y, 1);

        add_to_back(newNode);

        printPossibleMove(x, y, x - 1, y);
    }

    //we move to N-W
    finalPosition[1] = (x - 1) + '0';
    finalPosition[0] = (y - 1) + 'a' - 1;

    if (checkKingMovement(initialPosition, finalPosition))
    {
        node *newNode = create_node(x, y, x - 1, y - 1, 1);

        add_to_back(newNode);

        printPossibleMove(x, y, x - 1, y - 1);
    }

    // we move to W
    finalPosition[1] = x + '0';
    finalPosition[0] = (y - 1) + 'a' - 1;

    if (checkKingMovement(initialPosition, finalPosition))
    {
        node *newNode = create_node(x, y, x, y - 1, 1);

        add_to_back(newNode);

        printPossibleMove(x, y, x, y - 1);
    }

    // we move to S-W
    finalPosition[1] = (x + 1) + '0';
    finalPosition[0] = (y - 1) + 'a' - 1;

    if (checkKingMovement(initialPosition, finalPosition))
    {
        node *newNode = create_node(x, y, x + 1, y - 1, 1);

        add_to_back(newNode);

        printPossibleMove(x, y, x + 1, y - 1);
    }

    // we move to S
    finalPosition[1] = (x + 1) + '0';
    finalPosition[0] = y + 'a' - 1;

    if (checkKingMovement(initialPosition, finalPosition))
    {
        node *newNode = create_node(x, y, x + 1, y, 1);

        add_to_back(newNode);

        printPossibleMove(x, y, x + 1, y);
    }

    // we move to S-E

    finalPosition[1] = (x + 1) + '0';
    finalPosition[0] = (y + 1) + 'a' - 1;

    if (checkKingMovement(initialPosition, finalPosition))
    {
        node *newNode = create_node(x, y, x + 1, y + 1, 1);

        add_to_back(newNode);

        printPossibleMove(x, y, x + 1, y + 1);
    }

    // we move to E

    finalPosition[1] = x + '0';
    finalPosition[0] = (y + 1) + 'a' - 1;

    if (checkKingMovement(initialPosition, finalPosition))
    {
        node *newNode = create_node(x, y, x, y + 1, 1);

        add_to_back(newNode);

        printPossibleMove(x, y, x, y + 1);
    }

    //we move to N-E
    finalPosition[1] = (x - 1) + '0';
    finalPosition[0] = (y + 1) + 'a' - 1;

    if (checkKingMovement(initialPosition, finalPosition))
    {
        node *newNode = create_node(x, y, x - 1, y + 1, 1);

        add_to_back(newNode);

        printPossibleMove(x, y, x - 1, y + 1);
    }
}

int blackKingMobility(int x, int y)
{
    // printf("Here we generate the king moves\n");

    char initialPosition[] = "a1";
    char finalPosition[] = "a1";

    int mobility = 0;

    //the king can move in all 8 adjacent directions
    initialPosition[1] = x + '0';
    initialPosition[0] = y + 'a' - 1;

    //we move to N
    finalPosition[1] = (x - 1) + '0';
    finalPosition[0] = y + 'a' - 1;

    if (checkKingMovement(initialPosition, finalPosition))
    {
        // node *newNode = create_node(x, y, x - 1, y, 1);

        // add_to_back(newNode);

        // printPossibleMove(x, y, x - 1, y);

        mobility++;
    }

    //we move to N-W
    finalPosition[1] = (x - 1) + '0';
    finalPosition[0] = (y - 1) + 'a' - 1;

    if (checkKingMovement(initialPosition, finalPosition))
    {
        // node *newNode = create_node(x, y, x - 1, y - 1, 1);

        // add_to_back(newNode);

        // printPossibleMove(x, y, x - 1, y - 1);

        mobility++;
    }

    // we move to W
    finalPosition[1] = x + '0';
    finalPosition[0] = (y - 1) + 'a' - 1;

    if (checkKingMovement(initialPosition, finalPosition))
    {
        // node *newNode = create_node(x, y, x, y - 1, 1);

        // add_to_back(newNode);

        // printPossibleMove(x, y, x, y - 1);

        mobility++;
    }

    // we move to S-W
    finalPosition[1] = (x + 1) + '0';
    finalPosition[0] = (y - 1) + 'a' - 1;

    if (checkKingMovement(initialPosition, finalPosition))
    {
        // node *newNode = create_node(x, y, x + 1, y - 1, 1);

        // add_to_back(newNode);

        // printPossibleMove(x, y, x + 1, y - 1);

        mobility++;
    }

    // we move to S
    finalPosition[1] = (x + 1) + '0';
    finalPosition[0] = y + 'a' - 1;

    if (checkKingMovement(initialPosition, finalPosition))
    {
        // node *newNode = create_node(x, y, x + 1, y, 1);

        // add_to_back(newNode);

        // printPossibleMove(x, y, x + 1, y);

        mobility++;
    }

    // we move to S-E

    finalPosition[1] = (x + 1) + '0';
    finalPosition[0] = (y + 1) + 'a' - 1;

    if (checkKingMovement(initialPosition, finalPosition))
    {
        // node *newNode = create_node(x, y, x + 1, y + 1, 1);

        // add_to_back(newNode);

        // printPossibleMove(x, y, x + 1, y + 1);

        mobility++;
    }

    // we move to E

    finalPosition[1] = x + '0';
    finalPosition[0] = (y + 1) + 'a' - 1;

    if (checkKingMovement(initialPosition, finalPosition))
    {
        // node *newNode = create_node(x, y, x, y + 1, 1);

        // add_to_back(newNode);

        // printPossibleMove(x, y, x, y + 1);

        mobility++;
    }

    //we move to N-E
    finalPosition[1] = (x - 1) + '0';
    finalPosition[0] = (y + 1) + 'a' - 1;

    if (checkKingMovement(initialPosition, finalPosition))
    {
        // node *newNode = create_node(x, y, x - 1, y + 1, 1);

        // add_to_back(newNode);

        // printPossibleMove(x, y, x - 1, y + 1);

        mobility++;
    }

    return mobility;
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

int getPieceScore(int x, int y)
{
    int piece = chess_board[x][y];

    // since we play by white
    // black pieces are the enemies
    switch (piece)
    {
        case black_KING:
        {
            return 200;

            break;
        }

        case black_QUEEN:
        {
            return 9;

            break;
        }

        case black_ROOK:
        {
            return 5;

            break;
        }

        case black_BISHOP:
        {
            return 3;

            break;
        }

        case black_KNIGHT:
        {
            return 2;

            break;
        }

        case black_PAWN:
        {
            return 1;

            break;
        }
    }
}

int getMobility(int i, int j)
{
    int mobility = 0;

    node *current;

    if (head == NULL)
    {
        // printf("Empty list!\n");
    }
    else
    {
        for (current = head; current != NULL; current = current->next)
        {
            if(current -> XInitial == i && current -> YInitial == j)
            {
                mobility++;
            }
        }
    }

    return mobility;
}


int tableMobility(int x, int y, int finalX, int finalY)
{
    int mobilty = 0;

    // we add the white mobility

    for(int i = 1; i <= 8; ++ i)
    {
        for(int j = 1; j <= 8; ++ j)
        {
            int piece = chess_board[i][j];
            
            //we need to check if on the move we don't attack an enemy piece
            if (i != finalX && j != finalY)
            {
                switch (piece)
                {
                    case black_PAWN:
                    {
                        mobilty -= blackPawnMobility(i, j);
                        break;
                    }

                    case black_BISHOP:
                    {
                        mobilty -= blackBishopMobility(i, j);
                        break;
                    }

                    case black_KING:
                    {
                        mobilty -= blackKingMobility(i, j);
                        break;
                    }

                    case black_KNIGHT:
                    {
                        mobilty -= blackKnightMoblity(i, j);
                        break;
                    }

                    case black_QUEEN:
                    {
                        mobilty -= blackQueenMobility(i, j);
                        break;
                    }

                    case black_ROOK:
                    {
                        mobilty -= blackRookMobility(i, j);
                        break;
                    }

                    default:
                    {
                        break;
                    }
                }
            }
        }
    }

    // we care about the table mobility
    node *current;

    if(head == NULL)
    {
        // printf("Empty list\n");
    }
    else
    {
        int prevX, prevY;

        prevX = head -> XInitial;

        prevY = head -> YInitial;

        mobilty += head->step;

        //we care only about original mobility of pieces not duplicates
        for(current = head; current != NULL; current = current -> next)
        {
            if(current ->XInitial != prevX && current->YInitial != prevY)
            {
                prevX = current->XInitial;

                prevY = current->YInitial;
                
                mobilty += current -> step;
            }
        }
    }

    return mobilty;
}

bool doublePawns(int x, int y)
{
    int mainPawn = chess_board[x][y];

    //check the upper piece
    if (x - 1 >= 1)
    {
        int upperPiece = chess_board[x - 1][y];

        // if we have double pawns
        if (upperPiece == mainPawn)
        {
            return true;
        }
    }

    //check the lower piece
    if(x + 1 <= 8)
    {
        int lowerPiece = chess_board[x + 1][y];

        if(lowerPiece == mainPawn)
        {
            return true;
        }
    }

    return false;
}

bool isolatedPawn(int x, int y)
{   
    int counter = 0;

    // we check for N-W empty
    if(x - 1 >= 1 && y - 1 >= 1)
    {
        if(checkEmptyBlock(x - 1, y - 1))
        {
            counter++;
        }
        else
        {
            return false;
        }
    }

    // we check the N-E empty
    if(x - 1 >= 1 && y + 1 <= 8)
    {
        if(checkEmptyBlock(x - 1, y + 1))
        {
            counter++;
        }
        else
        {
            return false;
        }
    }

    // we check the S-W empty
    if(x + 1 <= 8 && y - 1 >= 1)
    {
        if(checkEmptyBlock(x + 1, y - 1))
        {
            counter++;
        }
        else
        {
            return false;
        }
    }

    //we check the S-E empty
    if(x + 1 <= 8 && y + 1 <= 8)
    {
        if(checkEmptyBlock(x + 1, y + 1))
        {
            counter ++;
        }
        else
        {
            return false;
        }
    }

    return counter == 4;
}

bool blockedPawn(int x, int y)
{
    int piece = chess_board[x][y];

    //the pawn is black
    if(piece == white_PAWN)
    {
        if(x - 1 >= 1)
        {
            if(!checkEmptyBlock(x - 1, y))
            {
                return true;
            }
        }
    }
    else
    {
        //the pawn is black

        if(x + 1 <= 8)
        {
            if(!checkEmptyBlock(x + 1, y))
            {
                return true;
            }
        }
    }
    return false;
}

float pieceCounter(int finalX, int finalY)
{
    //we count the score of existing enemy and allay pieces

    float counter = chess_board[finalX][finalY]; //we set this value to be sure we don't forget about it

    for(int i = 1; i <= 8; ++ i)
    {
        for(int j = 1; j <= 8; ++ j)
        {   
            if(finalX != i && finalY != j)
            {
                int piece = chess_board[i][j];

                switch (piece)
                {
                    case white_PAWN:
                    {
                        counter += 1;

                        if(doublePawns(finalX, finalY))
                        {
                            counter -= 0.5;
                        }

                        if(isolatedPawn(finalX, finalY))
                        {
                            counter -= 0.5;
                        }

                        if(blockedPawn(finalX, finalY))
                        {
                            counter -= 0.5;
                        }
                        break;
                    }

                    case black_PAWN:
                    {
                        counter -= 1;

                        if(doublePawns(finalX, finalY))
                        {
                            counter += 0.5;
                        }

                        if(isolatedPawn(finalX, finalY))
                        {
                            counter += 0.5;
                        }

                        if(blockedPawn(finalX, finalY))
                        {
                            counter += 0.5;
                        }
                        break;
                    }

                    case white_ROOK:
                    {
                        counter += 5;
                        break;
                    }

                    case black_ROOK:
                    {
                        counter -= 5;
                        break;
                    }

                    case white_BISHOP:
                    {
                        counter += 3;
                        break;
                    }

                    case black_BISHOP:
                    {
                        counter -= 3;
                        break;
                    }

                    case white_KNIGHT:
                    {
                        counter += 3;
                        break;
                    }

                    case black_KNIGHT:
                    {
                        counter -= 3;
                        break;
                    }

                    case white_QUEEN:
                    {
                        counter += 9;
                        break;
                    }

                    case black_QUEEN:
                    {
                        counter -= 9;
                        break;
                    }

                    case white_KING:
                    {
                        counter += 200;
                        break;
                    }

                    case black_KING:
                    {
                        counter -= 200;
                        break;
                    }

                    default:
                    {
                        break;
                    }
                }
            }
        }
    }
    // printf("Piece counter: %f\n", counter);

    return counter;
}

void setScore()
{
    node *current;

    if(head == NULL)
    {
        printf("Empty list\n");
    }
    else 
    {
        for(current = head; current != NULL; current = current -> next)
        {
            // we check if we step on the enemy
            // then we make up the score 
            // if(checkEmptyBlock(current -> XFinal, current ->YFinal) == false && checkNotAllay(current->XInitial, current->YInitial, current->XFinal, current->YFinal) == true)
            // {
            //     printf("This piece performs a massive attack: (%d, %d) to (%d, %d)\n", current ->XInitial, current ->YInitial, current->XFinal, current ->YFinal);
            //     current ->score += current -> step + getPieceScore(current -> XFinal, current -> YFinal);
            // }
            // else
            // {
            //     //if free to move on the block

            //     current -> score += current -> step;
            // }

            current -> score = 0.1 * tableMobility(current->XInitial, current->YInitial, current->XFinal, current->YFinal)
            + pieceCounter(current->XFinal, current->YFinal);
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

                int mobility = getMobility(i, j);

                setMobility(i, j, mobility);
            }
        }
    }
    setScore();

    print();

    // now we need to select the best move of the all stored in the list
    if (head == NULL)
    {
        printf("Empty list!\n");
    }
    else
    {
        float mx = -999.9;

        int XInitialCoordinate, YInitialCoordinate, XFinalCoordinate, YFinalCoordinate;

        node *current;
        
        for (current = head; current != NULL; current = current->next)
        {
            if(mx < current -> score)
            {
                XInitialCoordinate = current -> XInitial;

                YInitialCoordinate = current -> YInitial;
                
                XFinalCoordinate = current -> XFinal;
                
                YFinalCoordinate = current -> YFinal;

                mx = current -> score;
            }
        }

        printf("THE BEST OPTIONS IS: %d %d %d %d\n", XInitialCoordinate, YInitialCoordinate,XFinalCoordinate, YFinalCoordinate);
        
        if(chess_board[XInitialCoordinate][YInitialCoordinate] == white_PAWN)
        {
            whitePawnsStatus[YInitialCoordinate] = YFinalCoordinate;
        }
        //now we have stored the best move and make it real
        makeMoveOnBoard(XInitialCoordinate, YInitialCoordinate, XFinalCoordinate, YFinalCoordinate);

        delete();
    }
}
