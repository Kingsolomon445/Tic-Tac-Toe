#include <stdio.h>
#include <stdlib.h>
#define ROW 3
#define COL 3

 /*********************
 *A Tic Tac Toe Game**
 *********************/

/**************************************************************
 * Create a function that draws the board and set values
 * Create a function to display the board
 * Create a function that takes and set player moves
 * Create a function that checks if either player wins
 * Create a function that marks the board at each player move
 *************************************************************/

int count = -1; //This is used to take the number of moves made

int     get_len(const char played_moves[ROW * COL])// This function gets  length
{
    int length;

    length = -1;
    while (played_moves[++length])
        continue;
    return (length);
}
//void    set_board(char board[ROW][COL]);


void set_board(char board[ROW][COL]) //This function draws up the board
{
    int     pos1;
    int     pos2;
    char    tile;

    pos1 = -1;
    tile = 'a';
    while (++pos1 < ROW)
    {
        pos2 = -1;
        while (++pos2 < COL)
        {
            board[pos1][pos2] = tile++;
        }
    }
}

void    display(char board[ROW][COL]) //This function displays the board
{
    int pos1;
    int pos2;

    pos1 = -1;
    printf("\n_____________________");
    printf("\n \t| \t| \n");
    while (++pos1 < ROW)
    {
        pos2 = -1;
        while(++pos2 < COL)
        {
            if (pos2 == COL - 1)
                printf("%c\t  ", board[pos1][pos2]);
            else
                printf("%c\t| ", board[pos1][pos2]);
        }
        if (pos1 == ROW - 1)
            break;
        printf("\n_____________________");
        printf("\n \t| \t|\n");
    }
    printf("\n_____________________");
}

void    set_moves(char board[ROW][COL], int *player, char move) // this function places each player moves on board
{
    int pos1;
    int pos2;

    pos1 = -1;
    while (++pos1 < ROW)
    {
        pos2 = -1;
        while (++pos2 < COL)
        {
            if (move == board[pos1][pos2])
            {
                //Set player move on board and change to next player
                if (*player == 1) {
                    board[pos1][pos2] = 'X';
                    *player = 2;
                }
                else {
                    board[pos1][pos2] = 'O';
                    *player = 1;
                }
            }
        }
    }
}

void    player_move(int *player, char board[ROW][COL], char played_moves[ROW * COL])// This function takes players move
{
    char move;
    int replay;
    int pos;

    while (1) {
        printf("\nMake your move, Player %d: ", *player);
        scanf("\n%c", &move);
        //checking if move is valid
        if (!(move >= 'a' && move <= 'i')) {
            printf("\nInvalid Move!");
            continue;
        }

        pos = -1;
        //Checking if move have already been played
        replay = 0;
        while (played_moves[++pos]) {
            if (move == played_moves[pos]) {
                printf("\nMove already played!");
                replay = 1;
                break;
            }
        }
        //if move is correct and not played yet , break out of loop
        if (!replay)
            break;
    }
    played_moves[++count] = move; //Update played moves list
    set_moves(board, player, move);
}




int check_if_win(const int *player, char board[ROW][COL]) //This function checks for a winner
{
    int pos;
    int isWin;

    pos = -1;
    isWin = 0;
    //Checking for rows
    while (++pos < ROW && !isWin) {
        if ((board[pos][0] == board[pos][1]) && (board[pos][1] == board[pos][2]))
        {
           isWin = 1;
        }
    }

    pos = -1;
    //Checking for columns
    while (++pos < COL && !isWin) {
        if ((board[0][pos] == board[1][pos]) && (board[1][pos] == board[2][pos])) {
            isWin = 1;
        }
    }
    if (!isWin)
    {
        //Checking for the principal diagonals
        if ((board[0][0] == board[1][1]) && (board[1][1] == board[2][2]))
            isWin = 1;
        //Checking for the secondary diagonals
        if ((board[0][2] == board[1][1]) && (board[1][1] == board[2][0]))
            isWin = 1;
    }
    //Displaying results if winner found!
    if (isWin == 1 && *player == 2)
        printf("\nPlayer 1 wins the game!\n");
    else if (isWin == 1)
        printf("\nPlayer 2 wins the game!\n");
    return (isWin);
}

int main(void)
{
    char    board[ROW][COL];
    int     player;
    char    *played_moves;

    printf("\n\t\tTIC TAC TOE\n");
    printf("\nYou can make your moves with letter a - i representing each tiles\n");
    printf("\nPlayer 1 (X)\tPlayer 2 (O)\n\n");
    player = 1;
    played_moves = malloc(ROW * COL * (sizeof(char) + 1));
    set_board(board);
    display(board);
    while (!check_if_win(&player, board))
    {
        if (get_len(played_moves) == 9)
        {
            printf("\nIt is a draw!\n");
            break;
        }
        player_move(&player, board, played_moves);
        display(board);
    }
    return (0);
}