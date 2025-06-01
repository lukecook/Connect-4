// Connect 4
// Graphics and ui header file

#ifndef UI_H
#define UI_H

#include "raylib.h"
#include "connect4.h"

// Connect4 UI
class Connect4UI 
{
    public:
        Connect4UI(float x, float y, float size);

        // Rendering
        void drawBoard(const Connect4Game& game);
        void drawPiece(int row, int col, int player);
        void drawEmptySlot(int row, int col);
        void drawGameStatus(const Connect4Game& game);

        // Input handling
        int getColumnFromMouseX(float mouseX) const;
        bool isMouseOverBoard(float mouseX, float mouseY) const;

        // Setters
        void setBoardPosition(float x, float y);
        void setCellSize(float size);
        void setColors(GameColor board, GameColor p1, GameColor p2, GameColor empty);

        // Getters
        float getBoardX() const;
        float getBoardY() const; 
        float getBoardWidth() const;
        float getBoardHeight() const;
        float getCellSize() const;

    private:
        float boardX, boardY;
        float cellSize;
        float pieceRadius;
        float boardWidth, boardHeight;
        float roundness;

        GameColor boardColor;
        GameColor player1Color;
        GameColor player2Color;
        GameColor emptySlotColor;
        GameColor backgroundColors;

        // Helper functions
        Color gameColorToRaylib(GameColor gc) const;
        float getCellCenterX(int col) const;
        float getCellCenterY(int row) const;
};

#endif
