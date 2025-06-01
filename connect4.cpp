// Connect 4
// Contains function implementations for the connect 4 game

#include "connect4.h"

// Connect 4 Game Constructor
Connect4Game::Connect4Game()
{
    // Initialize the board to all empty
    for(int row = 0; row < ROWS; ++row)
    {
        for(int col = 0; col < COLS; ++col)
        {
            board[row][col] = EMPTY;
        }
    }

    currentPlayer = PLAYER1;  // Player 1 starts
    gameOver = false;
    winner = 0;
}



//----------------------------------------------------------------------------------------//
// Game logic

// Attempt to drop a piece while checking for game ending conditions
bool Connect4Game::dropPiece(int col)
{
    // Check if column is valid
    if(col < 0 || col >= COLS)
        return false;
    
    // Check if column is full
    if(isColumnFull(col))
        return false;
    
    // Find the lowest empty row in this column
    int targetRow = -1;
    for(int row = ROWS - 1; row >= 0; --row)
    {
        if(board[row][col] == EMPTY)
        {
            targetRow = row;
            break;
        }
    }
    
    // Place the piece
    board[targetRow][col] = currentPlayer;
    
    // Check if this move wins the game
    if(checkWinFromPosition(targetRow, col, currentPlayer))
    {
        gameOver = true;
        winner = currentPlayer;
    }
    else if(isBoardFull())
    {
        gameOver = true;
        winner = -1; // Tie game
    }
    
    // Switch to the other player
    currentPlayer = (currentPlayer == PLAYER1) ? PLAYER2 : PLAYER1;
    
    return true;
}

// Search the entire board for any winning combinations
int Connect4Game::checkWinner()
{
    // Loop through 2d array
    for(int row = 0; row < ROWS; ++row)
    {
        for(int col = 0; col < COLS; ++col)
        {
            if(board[row][col] != EMPTY) // Found a piece
            {
                int player = board[row][col]; // Get player number of that piece
                if(checkWinFromPosition(row, col, player)) // Check for a winning condition
                {
                    winner = player;
                    gameOver = true;
                    return player; // Return winning player
                }
            }
        }
    }

    // Check tie
    if(isBoardFull()) 
    {
        winner = -1;  // Set tie
        gameOver = true;
        return -1;
    }
    
    // No winner yet
    return 0;
}

// This function is used by dropPiece() to check if a move is legal before attempting it
bool Connect4Game::isColumnFull(int col) const
{
    // Check if column is valid
    if(col < 0 || col >= COLS)
        return true; // Treat invalid columns as "full" instead of crashing program
    
    // Check if the top row of this column has a piece
    return board[0][col] != EMPTY;
}

// This function is used by checkWinner() to verify a tie condition
bool Connect4Game::isBoardFull() const
{
    // Check if all columns are full
    for(int col = 0; col < COLS; ++col)
    {
        if(!isColumnFull(col))
            return false; // Found at least one column that's not full
    }
    
    return true; // All columns are full
}

// Reset Game
void Connect4Game::resetGame()
{
    // Clear the entire board
    for(int row = 0; row < ROWS; ++row)
    {
        for(int col = 0; col < COLS; ++col)
        {
            board[row][col] = EMPTY;
        }
    }

    // Reset game state
    currentPlayer = PLAYER1;
    gameOver = false;
    winner = 0;
}



//----------------------------------------------------------------------------------------//
// Getters

// Get Board Value
int Connect4Game::getBoardValue(int row, int col) const
{
    // Check bounds to prevent array access errors
    if(row < 0 || row >= ROWS || col < 0 || col >= COLS)
        return -1; // Invalid position

    return board[row][col]; // either 0, 1, or 2
}

int Connect4Game::getCurrentPlayer() const
{
    return currentPlayer;
}

bool Connect4Game::isGameOver() const
{
    return (getWinner() != 0) || isBoardFull();
}

int Connect4Game::getWinner() const
{
    return winner;  // Return current winner value (0, 1, 2, -1)
}



//----------------------------------------------------------------------------------------//
// Private Helper Methods

/*
Connect4 Board Layout (6 rows x 7 columns):

     0   1   2   3   4   5   6  
   +---+---+---+---+---+---+---+
0  | . | . | . | . | . | . | . |
   +---+---+---+---+---+---+---+
1  | . | . | . | . | . | . | . |
   +---+---+---+---+---+---+---+
2  | . | . | . | . | . | . | . |
   +---+---+---+---+---+---+---+
3  | . | . | . | . | . | . | . |
   +---+---+---+---+---+---+---+
4  | . | . | . | . | . | . | . |
   +---+---+---+---+---+---+---+
5  | . | . | . | . | . | . | . |
   +---+---+---+---+---+---+---+

Traversal Directions:
Horizontal    (-): left (--col), right (++col)
Vertical      (|): up (--row), down (++row)  
Diagonal Up   (/): down-left (++row,--col), up-right (--row,++col)
Diagonal Down (\): up-left (--row,--col), down-right (++row,++col)
*/

// Check for a win horizontally from the location of the dropped piece
// Add the consecutive player pieces in both directions. Total >= 4 is a win
bool Connect4Game::checkHorizontal(int row, int col, int player) const
{
    int count = 1; // Count the piece we're starting from

    // Check to the left
    for(int c = col - 1; c >= 0 && board[row][c] == player; --c)
        ++count;

    // Check to the right
    for(int c = col + 1; c < COLS && board[row][c] == player; ++c)
        ++count;

    return count >= 4;
}

// Check for a win vertically from the location of the dropped piece
bool Connect4Game::checkVertical(int row, int col, int player) const
{
    int count = 1; // Count the piece we're starting from

    // Check upward
    for(int r = row - 1; r >= 0 && board[r][col] == player; --r)
        ++count;

    // Check downward
    for(int r = row + 1; r < ROWS && board[r][col] == player; ++r)
        ++count;

    return count >= 4;
}

// Check for a win diagonally up-right and down-left from the location of the dropped piece
bool Connect4Game::checkDiagonalUp(int row, int col, int player) const
{
    int count = 1; // Count the piece we're starting from

    // Check down-left direction
    for(int r = row + 1, c = col - 1; r < ROWS && c >= 0 && board[r][c] == player; ++r, --c)
        ++count;

    // Check up-right direction
    for(int r = row - 1, c = col + 1; r >= 0 && c < COLS && board[r][c] == player; --r, ++c)
        ++count;

    return count >= 4;
}

// Check for a win diagonally up-left and down-right from the location of the dropped piece
bool Connect4Game::checkDiagonalDown(int row, int col, int player) const
{
    int count = 1; // Count the piece we're starting from

    // Check up-left direction
    for(int r = row - 1, c = col - 1; r >= 0 && c >= 0 && board[r][c] == player; --r, --c)
        ++count;

    // Check down-right direction
    for(int r = row + 1, c = col + 1; r < ROWS && c < COLS && board[r][c] == player; ++r, ++c)
        ++count;

    return count >= 4;
}

// Check for 4 in a row in all directions
bool Connect4Game::checkWinFromPosition(int row, int col, int player) const
{
    return checkHorizontal(row, col, player) ||
           checkVertical(row, col, player) ||
           checkDiagonalUp(row, col, player) ||
           checkDiagonalDown(row, col, player);
}

// Get rows (public data)
int Connect4Game::getRows() const
{ 
    return ROWS; 
}

// Get columns (public data)
int Connect4Game::getCols() const
{ 
    return COLS; 
}

