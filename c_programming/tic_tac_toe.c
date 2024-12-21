#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define BOARD_SIZE 3

// Function prototypes
void initializeBoard(char board[BOARD_SIZE][BOARD_SIZE]);
void displayBoard(const char board[BOARD_SIZE][BOARD_SIZE]);
int checkWin(const char board[BOARD_SIZE][BOARD_SIZE], char player);
int isDraw(const char board[BOARD_SIZE][BOARD_SIZE]);
int makeMove(char board[BOARD_SIZE][BOARD_SIZE], int row, int col, char player);

int main() {
    char board[BOARD_SIZE][BOARD_SIZE];
    int row, col;
    char currentPlayer = 'X';
    int gameWon = 0;

    initializeBoard(board);

    printf("Welcome to Tic Tac Toe!\n\n");

    while (!gameWon && !isDraw(board)) {
        displayBoard(board);
        printf("Player %c, enter your move (row and column): ", currentPlayer);
        scanf("%d %d", &row, &col);

        if (row < 1 || row > BOARD_SIZE || col < 1 || col > BOARD_SIZE) {
            printf("Invalid input. Please enter row and column between 1 and %d.\n", BOARD_SIZE);
            continue;
        }

        if (!makeMove(board, row - 1, col - 1, currentPlayer)) {
            printf("Invalid move. The cell is already occupied. Try again.\n");
            continue;
        }

        gameWon = checkWin(board, currentPlayer);

        if (!gameWon) {
            currentPlayer = (currentPlayer == 'X') ? 'O' : 'X';
        }
    }

    displayBoard(board);

    if (gameWon) {
        printf("Congratulations! Player %c wins!\n", currentPlayer);
    } else {
        printf("It's a draw!\n");
    }

    return 0;
}

void initializeBoard(char board[BOARD_SIZE][BOARD_SIZE]) {
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            board[i][j] = ' ';
        }
    }
}

void displayBoard(const char board[BOARD_SIZE][BOARD_SIZE]) {
    printf("\n");
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            printf(" %c ", board[i][j]);
            if (j < BOARD_SIZE - 1) {
                printf("|");
            }
        }
        printf("\n");
        if (i < BOARD_SIZE - 1) {
            for (int k = 0; k < BOARD_SIZE; k++) {
                printf("---");
                if (k < BOARD_SIZE - 1) {
                    printf("+");
                }
            }
            printf("\n");
        }
    }
    printf("\n");
}

int checkWin(const char board[BOARD_SIZE][BOARD_SIZE], char player) {
    // Check rows and columns
    for (int i = 0; i < BOARD_SIZE; i++) {
        if ((board[i][0] == player && board[i][1] == player && board[i][2] == player) ||
            (board[0][i] == player && board[1][i] == player && board[2][i] == player)) {
            return 1;
        }
    }

    // Check diagonals
    if ((board[0][0] == player && board[1][1] == player && board[2][2] == player) ||
        (board[0][2] == player && board[1][1] == player && board[2][0] == player)) {
        return 1;
    }

    return 0;
}

int isDraw(const char board[BOARD_SIZE][BOARD_SIZE]) {
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            if (board[i][j] == ' ') {
                return 0;
            }
        }
    }
    return 1;
}

int makeMove(char board[BOARD_SIZE][BOARD_SIZE], int row, int col, char player) {
    if (board[row][col] == ' ') {
        board[row][col] = player;
        return 1;
    }
    return 0;
}