/**
 * Tic Tac Toe Game
 * 
 * A simple console-based Tic Tac Toe game for two players. Players take turns, to play their moves on a 3x3 grid.
 * The game checks for valid moves, determines the winner, and allows players to play multiple rounds.
 * 
 * @author Nicolai Gravdal Johnsen
 * @file TicTacToe.c
 */

#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>
#include <string.h>

#define BOARD_SIZE 9
#define STRING_LENGTH 80

// Function declarations
void resetBoard();
bool isValidMove(int position);
bool checkWinner();
void printBoard();
int playGame();

// Global game board
char board[BOARD_SIZE];

/**
 * Main program
 */
int main() {
    char player1[STRING_LENGTH];
    char player2[STRING_LENGTH];
    char playAgain;
    int winner;

    do {
        resetBoard();
        printBoard();

        printf("\nName of player 1: ");
        fgets(player1, STRING_LENGTH, stdin);
        player1[strcspn(player1, "\n")] = '\0';

        printf("Name of player 2: ");
        fgets(player2, STRING_LENGTH, stdin);
        player2[strcspn(player2, "\n")] = '\0';

        winner = playGame();

        if (winner == 1)
            printf("\nCongratulations %s!\n\n", player1);
        else if (winner == 2)
            printf("\nCongratulations %s!\n\n", player2);
        else
            printf("\nNo winner this time.\n\n");

        printf("Play another round (Y/N): ");
        scanf(" %c", &playAgain);
        playAgain = toupper(playAgain);

        while (getchar() != '\n'); // clear buffer

    } while (playAgain == 'Y');

    return 0;
}

/**
 * Clears the game board
 */
void resetBoard() {
    for (int i = 0; i < BOARD_SIZE; i++) {
        board[i] = ' ';
    }
}

/**
 * Checks if a move is valid
 */
bool isValidMove(int position) {
    if (position < 0 || position >= BOARD_SIZE)
        return false;

    return board[position] == ' ';
}

/**
 * Checks if a player has won
 */
bool checkWinner() {
    const int winCombos[8][3] = {
        {0,1,2}, {3,4,5}, {6,7,8},
        {0,3,6}, {1,4,7}, {2,5,8},
        {0,4,8}, {2,4,6}
    };

    for (int i = 0; i < 8; i++) {
        int a = winCombos[i][0];
        int b = winCombos[i][1];
        int c = winCombos[i][2];

        if (board[a] != ' ' &&
            board[a] == board[b] &&
            board[b] == board[c]) {
            return true;
        }
    }

    return false;
}

/**
 * Prints the game board
 */
void printBoard() {
    for (int row = 0; row < 3; row++) {
        printf("-");
        for (int col = 0; col < 3; col++) {
            printf("--%d---", row * 3 + col + 1);
        }
        printf("\n");

        for (int col = 0; col < 3; col++) {
            printf(" | %c", board[row * 3 + col]);
        }
        printf(" |\n");
    }
    printf("-------------------\n");
}

/**
 * Handles gameplay and returns the winner
 */
int playGame() {
    int currentPlayer = 1;
    int move;
    int moveCount = 0;
    int winner = 0;

    do {
        printBoard();

        while (1) {
            printf("Player %d, your turn (1–9): ", currentPlayer);

            if (scanf("%d", &move) != 1) {
                printf("Invalid input. Please enter a number.\n");
                while (getchar() != '\n');
                continue;
            }

            move--; // Convert to 0–8 index

            if (isValidMove(move))
                break;

            printf("Invalid move. Try again.\n");
        }

        board[move] = (currentPlayer == 1) ? 'X' : 'O';
        moveCount++;

        if (checkWinner()) {
            winner = currentPlayer;
        } else {
            currentPlayer = (currentPlayer == 1) ? 2 : 1;
        }

    } while (winner == 0 && moveCount < BOARD_SIZE);

    printBoard();
    return winner;
}
