#include <iostream>
#include <vector>
#include <limits>
#include <string>

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
bool select_winner(vector<char> board, char player, string archetype) {
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

    // Swarm archetype: all four corners
    if (archetype == "Swarm" &&
        board[0] == player && board[2] == player && board[6] == player && board[8] == player) {
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
        cout << "Choose a spot by typing a number 1-9: ";
        cin >> move;

        // Check if input is valid
        if (move < 1 || move > 9 || cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Not a valid number! Please try again.\n";
            continue;
        }

        move--; // Convert to 0-indexed

        if (board[move] != 'X' && board[move] != 'O') {
            return move; 
        }
        else {
            cout << "That spot is taken! Please choose another one.\n";
        }
    }
}

// Archetype selection
string chooseArchetype(char player) {
    string archetype;
    while (true) {
        cout << "Player " << player << ", choose your archetype by typing Swarm or Pyromancer: ";
        cin >> archetype;

        if (archetype == "Swarm" || archetype == "swarm") {
            cout << "Swarm: You win by normal rules or by filling all four corners of the board.\n";
            return "Swarm";
        }
        else if (archetype == "Pyromancer" || archetype == "pyromancer") {
            cout << "Pyromancer: You can clear the board once during this game as a special move.\n";
            return "Pyromancer";
        }
        else {
            cout << "\nInvalid archetype! Please choose 'Swarm' or 'Pyromancer'.\n";
        }
    }
}

// Battle Tic-Tac-Toe gameplay
void playBattleGame() {
    vector<char> board = { '1', '2', '3', '4', '5', '6', '7', '8', '9' };
    char currentPlayer = 'X';
    string archetypes[2];
    bool usedSpecialMove[2] = { false, false }; // Track Pyromancer's special move usage

    archetypes[0] = chooseArchetype('X');
    archetypes[1] = chooseArchetype('O');

    bool gameFinished = false;
    cout << "\nStarting Battle Tic-Tac-Toe!\n";

    while (!gameFinished) {
        displayBoard(board);

        if (archetypes[currentPlayer == 'X' ? 0 : 1] == "Pyromancer" && !usedSpecialMove[currentPlayer == 'X' ? 0 : 1]) {
            // Pyromancer special move menu
            char choice;
            cout << "Player " << currentPlayer << ", do you want to make a (R)egular move or use your (S)pecial move? ";
            cin >> choice;

            if (choice == 's' || choice == 'S') {
                cout << "Player " << currentPlayer << " used the Pyromancer's special move to clear the board!\n";
                board = { '1', '2', '3', '4', '5', '6', '7', '8', '9' };
                usedSpecialMove[currentPlayer == 'X' ? 0 : 1] = true;
                continue;
            }
        }

        int move = getMove(board);
        board[move] = currentPlayer;

        if (select_winner(board, currentPlayer, archetypes[currentPlayer == 'X' ? 0 : 1])) {
            displayBoard(board);
            cout << "Player " << currentPlayer << " wins, congratulations!!\n";
            gameFinished = true;
        }
        else if (isDraw(board)) {
            displayBoard(board);
            cout << "It's a draw!\n";
            gameFinished = true;
        }
        else {
            currentPlayer = (currentPlayer == 'X') ? 'O' : 'X';
        }
    }
}

// Main game function
void playGame() {
    char gameType;
    cout << "Welcome to Tic-Tac-Toe!\n";
    cout << "Please choose a game type: (R)egular or (B)attle: ";
    cin >> gameType;

    if (gameType == 'r' || gameType == 'R') {
        vector<char> board = { '1', '2', '3', '4', '5', '6', '7', '8', '9' };
        char currentPlayer = 'X';
        bool gameFinished = false;

        cout << "\nStarting Regular Tic-Tac-Toe!\n";

        while (!gameFinished) {
            displayBoard(board);
            int move = getMove(board);
            board[move] = currentPlayer;

            if (select_winner(board, currentPlayer, "")) {
                displayBoard(board);
                cout << "Player " << currentPlayer << " wins, congratulations!!\n";
                gameFinished = true;
            }
            else if (isDraw(board)) {
                displayBoard(board);
                cout << "It's a draw!\n";
                gameFinished = true;
            }
            else {
                currentPlayer = (currentPlayer == 'X') ? 'O' : 'X';
            }
        }
    }
    else if (gameType == 'b' || gameType == 'B') {
        playBattleGame();
    }
    else {
        cout << "Invalid choice! Exiting.\n";
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
