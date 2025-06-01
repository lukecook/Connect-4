// Connect 4
// Header file

#ifndef CONNECT4_H
#define CONNECT4_H

// GameColor (RGBA)
struct GameColor 
{
    unsigned char r, g, b, a;

    GameColor(unsigned char red = 255, unsigned char green = 255, unsigned char blue = 255, unsigned char alpha = 255)
        : r(red), g(green), b(blue), a(alpha) {}
};

// Connect4 Game
class Connect4Game 
{
    public:
        Connect4Game();

        // Game logic
        bool dropPiece(int col);
        int checkWinner();
        bool isColumnFull(int col) const;
        bool isBoardFull() const;
        void resetGame();

        // Getters
        int getBoardValue(int row, int col) const;
        int getCurrentPlayer() const;
        bool isGameOver() const;
        int getWinner() const;

        // Constants for external access
        int getRows() const;
        int getCols() const;

        // (static) - a property of the game type and not a specific game
        // Player constants (other code needs these values)
        static const int EMPTY = 0;
        static const int PLAYER1 = 1;
        static const int PLAYER2 = 2;

    private:
        // Game specific constants
        static const int ROWS = 6;
        static const int COLS = 7;

        // Data 
        int board[ROWS][COLS];
        int currentPlayer;
        bool gameOver;
        int winner;

        // Helper methods
        bool checkHorizontal(int row, int col, int player) const;
        bool checkVertical(int row, int col, int player) const;
        bool checkDiagonalUp(int row, int col, int player) const;
        bool checkDiagonalDown(int row, int col, int player) const;
        bool checkWinFromPosition(int row, int col, int player) const;
};

#endif
