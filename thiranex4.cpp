#include <iostream>

using namespace std;

char board[3][3];
char currentPlayer = 'X';

// Function to initialize board
void initializeBoard()
{
    char ch = '1';

    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            board[i][j] = ch++;
        }
    }
}
void displayBoard()
{
    cout << "\n";

    for (int i = 0; i < 3; i++)
    {
        cout << " ";

        for (int j = 0; j < 3; j++)
        {
            cout << board[i][j];

            if (j < 2)
                cout << " | ";
        }

        cout << endl;

        if (i < 2)
            cout << "-----------" << endl;
    }

    cout << "\n";
}
bool placeMark(int choice)
{
    int row = (choice - 1) / 3;
    int col = (choice - 1) % 3;

    if (board[row][col] != 'X' && board[row][col] != 'O')
    {
        board[row][col] = currentPlayer;
        return true;
    }

    return false;
}
bool checkWinner()
{
    // Rows and Columns
    for (int i = 0; i < 3; i++)
    {
        if (board[i][0] == board[i][1] &&
            board[i][1] == board[i][2])
            return true;

        if (board[0][i] == board[1][i] &&
            board[1][i] == board[2][i])
            return true;
    }

    // Diagonals
    if (board[0][0] == board[1][1] &&
        board[1][1] == board[2][2])
        return true;

    if (board[0][2] == board[1][1] &&
        board[1][1] == board[2][0])
        return true;

    return false;
}
bool checkDraw()
{
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (board[i][j] != 'X' &&
                board[i][j] != 'O')
                return false;
        }
    }

    return true;
}
int main()
{
    int choice;
    bool gameWon = false;

    initializeBoard();

    while (!gameWon)
    {
        displayBoard();

        cout << "Player " << currentPlayer
             << ", enter position (1-9): ";

        cin >> choice;

        if (choice < 1 || choice > 9)
        {
            cout << "\nInvalid position! Try again.\n";
            continue;
        }

        if (!placeMark(choice))
        {
            cout << "\nPosition already taken! Try again.\n";
            continue;
        }

        gameWon = checkWinner();

        if (gameWon)
        {
            displayBoard();

            cout << "\nPlayer " << currentPlayer
                 << " wins the game!\n";

            break;
        }

        if (checkDraw())
        {
            displayBoard();

            cout << "\nGame Draw!\n";

            break;
        }

        // Switch Player
        currentPlayer =
            (currentPlayer == 'X') ? 'O' : 'X';
    }

    return 0;
}