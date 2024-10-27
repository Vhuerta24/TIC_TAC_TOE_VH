#include <iostream>
#include <vector>
#include <limits>

using namespace std;

// Function to display the board
void displayBoard(vector<char> board) {
    cout << " " << board[0] << " | " << board[1] << " | " << board[2] << "\n";
    cout << "---|---|---\n";
    cout << " " << board[3] << " | " << board[4] << " | " << board[5] << "\n";
    cout << "---|---|---\n";
    cout << " " << board[6] << " | " << board[7] << " | " << board[8] << "\n\n";
}

// Function to check if a player has won
bool select_winner(vector<char> board, char player) {
    // Check rows and columns
    for (int i = 0; i < 3; i++) {
        if ((board[i * 3] == player && board[i * 3 + 1] == player && board[i * 3 + 2] == player) || // Row
            (board[i] == player && board[i + 3] == player && board[i + 6] == player)) { // Column
            return true;
        }
    }
    // Check diagonals
    if ((board[0] == player && board[4] == player && board[8] == player) ||
        (board[2] == player && board[4] == player && board[6] == player)) {
        return true;
    }
    return false;
}

// Function to check for a draw
bool isDraw(vector<char> board) {
    for (char c : board) {
        if (c != 'X' && c != 'O') {
            return false;
        }
    }
    return true;
}

// Function to get a move from the player
int getMove(vector<char> board) {
    int move;
    while (true) {
        cout << "Choose a spot (1-9): ";
        cin >> move;

        // Check if input is valid
        if (move < 1 || move > 9 || cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Not a valid number! Try again.\n";
            continue;
        }

        move--; // Convert to 0-indexed

        if (board[move] != 'X' && board[move] != 'O') {
            return move; // Valid move
        }
        else {
            cout << "That spot is taken! Please choose another one.\n";
        }
    }
}

// Main game function
void playGame() {
    vector<char> board = { '1', '2', '3', '4', '5', '6', '7', '8', '9' };
    char currentPlayer = 'X';
    bool gameFinished = false;

    cout << "Hello, welcome to Tic-Tac-Toe!\n";

    while (!gameFinished) {
        displayBoard(board);
        int move = getMove(board);
        board[move] = currentPlayer;

        if (select_winner(board, currentPlayer)) {
            displayBoard(board);
            cout << "Player " << currentPlayer << " wins, congratulations!\n";
            gameFinished = true;
        }
        else if (isDraw(board)) {
            displayBoard(board);
            cout << "It's a draw!\n";
            gameFinished = true;
        }
        else {
            // Here we switch player
            currentPlayer = (currentPlayer == 'X') ? 'O' : 'X';
        }
    }
}

// Main function
int main() {
    char playAgain;
    do {
        playGame();
        cout << "Would you like to play again? (y/n): ";
        cin >> playAgain;
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear input buffer
    } while (playAgain == 'y' || playAgain == 'Y');

    cout << "Thank you for playing, Goodbye!\n";
    return 0;
}
