#include <iostream>
#include <vector>
#include <stack>

using namespace std;

// Node structure for linked list
struct Node {
    char value;
    Node* next;
    Node(char val) : value(val), next(nullptr) {}
};

// Linked list class
class LinkedList {
private:
    Node* head;

public:
    LinkedList() : head(nullptr) {}

    void append(char val) {
        Node* newNode = new Node(val);
        if (head == nullptr) {
            head = newNode;
        } else {
            Node* curr = head;
            while (curr->next != nullptr) {
                curr = curr->next;
            }
            curr->next = newNode;
        }
    }

    char pop() {
        if (head == nullptr) {
            return ' ';
        }
        Node* curr = head;
        char val = curr->value;
        head = curr->next;
        delete curr;
        return val;
    }

    bool isEmpty() {
        return head == nullptr;
    }
};

// Tic Tac Toe game class
class TicTacToe {
private:
    vector<vector<char>> board;
    LinkedList movesList;
    stack<char> undoStack;

public:
    TicTacToe() {
        board.resize(3, vector<char>(3, ' '));
    }

    void displayBoard() {
        cout << "  0 1 2" << endl;
        for (int i = 0; i < 3; i++) {
            cout << i << " ";
            for (int j = 0; j < 3; j++) {
                cout << board[i][j] << " ";
            }
            cout << endl;
        }
    }

    bool makeMove(int row, int col, char player) {
        if (row < 0 || row >= 3 || col < 0 || col >= 3 || board[row][col] != ' ') {
            return false;
        }
        board[row][col] = player;
        movesList.append(player);
        undoStack.push(player);
        return true;
    }

    bool undoMove() {
        if (movesList.isEmpty()) {
            return false;
        }
        char player = undoStack.top();
        undoStack.pop();
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (board[i][j] == player) {
                    board[i][j] = ' ';
                    movesList.pop();
                    return true;
                }
            }
        }
        return false;
    }

    bool checkWin(char player) {
        // Check rows
        for (int i = 0; i < 3; i++) {
            if (board[i][0] == player && board[i][1] == player && board[i][2] == player) {
                return true;
            }
        }

        // Check columns
        for (int i = 0; i < 3; i++) {
            if (board[0][i] == player && board[1][i] == player && board[2][i] == player) {
                return true;
            }
        }

        // Check diagonals
        if (board[0][0] == player && board[1][1] == player && board[2][2] == player) {
            return true;
        }
        if (board[0][2] == player && board[1][1] == player && board[2][0] == player) {
            return true;
        }

        return false;
    }

    bool isBoardFull() {
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (board[i][j] == ' ') {
                    return false;
                }
            }
        }
        return true;
    }
};

int main() {
    TicTacToe game;
    char player = 'X';

    while (true) {
        system("clear");
        game.displayBoard();

        int row, col;
        cout << "Player " << player << ", enter row and column: ";
        cin >> row >> col;

        if (game.makeMove(row, col, player)) {
            if (game.checkWin(player)) {
                cout << "Player " << player << " wins!" << endl;
                break;
            } else if (game.isBoardFull()) {
                cout << "It's a tie!" << endl;
                break;
            }
            player = (player == 'X') ? 'O' : 'X';
        } else {
            cout << "Invalid move! Try again." << endl;
        }

        char undoChoice;
        cout << "Do you want to undo the last move? (y/n): ";
        cin >> undoChoice;
        if (undoChoice == 'y' || undoChoice == 'Y') {
            game.undoMove();
            player = (player == 'X') ? 'O' : 'X';
        }
    }

    return 0;
}
