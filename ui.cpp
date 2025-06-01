// Connect 4
// Contains function implementations for the connect 4 graphics and ui

#include "ui.h"

Connect4UI::Connect4UI(float x, float y, float size): boardX(x), boardY(y), cellSize(size)
{
    // Calculate derived values
    pieceRadius = cellSize * 0.35f;  // Pieces are 70% of cell size
    boardWidth = 7 * cellSize;       // 7 columns
    boardHeight = 6 * cellSize;      // 6 rows
    roundness = 0.1f;                // For rounded rectangles

    // Set default colors using GameColor struct
    boardColor = GameColor(0, 100, 200, 255);         // Blue board
    player1Color = GameColor(255, 0, 0, 255);         // Red player 1
    player2Color = GameColor(255, 255, 0, 255);       // Yellow player 2
    emptySlotColor = GameColor(255, 255, 255, 255);   // White empty slots
    backgroundColors = GameColor(200, 200, 200, 255); // Light gray background
}



// Rendering
//----------------------------------------------------------------------------------------//

// Draw the entire Connect4 board
void Connect4UI::drawBoard(const Connect4Game& game)
{
    // Draw the board background
    DrawRectangleRounded({boardX, boardY, boardWidth, boardHeight}, roundness, 0, gameColorToRaylib(boardColor));

    // Draw all the slots and pieces
    for(int row = 0; row < game.getRows(); ++row)
    {
        for(int col = 0; col < game.getCols(); ++col)
        {
            int cellValue = game.getBoardValue(row, col);
            if(cellValue == 0)
                drawEmptySlot(row, col);
            else
                drawPiece(row, col, cellValue);
        }
    }
}

// Draw colored pieces for players
void Connect4UI::drawPiece(int row, int col, int player)
{
    float centerX = getCellCenterX(col);
    float centerY = getCellCenterY(row);

    Color pieceColor;
    if(player == 1)
    {
        pieceColor = gameColorToRaylib(player1Color);
        DrawCircle(centerX, centerY, pieceRadius, pieceColor);
    }
    else if(player == 2)
    {
        pieceColor = gameColorToRaylib(player2Color);
        DrawCircle(centerX, centerY, pieceRadius, pieceColor);
    }
    else
        return; // Invalid player, don't draw anything
}

// Draw a white circle for empty space
void Connect4UI::drawEmptySlot(int row, int col)
{
    float centerX = getCellCenterX(col);
    float centerY = getCellCenterY(row);
    
    DrawCircle(centerX, centerY, pieceRadius, gameColorToRaylib(emptySlotColor));
}

// Draw game status messages
void Connect4UI::drawGameStatus(const Connect4Game& game)
{
    const char* statusText; // raylib DrawText() function requires a const char*
    Color textColor = BLACK; // raylib color

    if(game.isGameOver())
    {
        int winner = game.getWinner();
        if(winner == 1)
        {
            statusText = "Player 1 Wins!";
            textColor = gameColorToRaylib(player1Color);
        }
        else if(winner == 2)
        {
            statusText = "Player 2 Wins!";
            textColor = gameColorToRaylib(player2Color);
        }
        else if(winner == -1)
        {
            statusText = "It's a Tie!";
            textColor = PURPLE;
        }
    }
    else
        statusText = (game.getCurrentPlayer() == 1) ? "Player 1's Turn" : "Player 2's Turn";

    // Draw player turn text above the board
    float textY = boardY - 60;
    float textX = boardX + 100;
    DrawText(statusText, textX, textY, 32, textColor);
}



// Input handling
//----------------------------------------------------------------------------------------//

// Determine board column number based on mouse x position
int Connect4UI::getColumnFromMouseX(float mouseX) const
{
    // Check if mouse is within board horizontal bounds
    if(mouseX < boardX || mouseX > boardX + boardWidth)
        return -1; // Invalid column don't drop a piece
    
    // Calculate which column the mouse is over
    int col = static_cast<int>((mouseX - boardX) / cellSize);
    
    return col;
}

// Check if mouse is over the game board
bool Connect4UI::isMouseOverBoard(float mouseX, float mouseY) const
{
    return (mouseX >= boardX && mouseX <= boardX + boardWidth && mouseY >= boardY && mouseY <= boardY + boardHeight);
}



// Setters
//----------------------------------------------------------------------------------------//

// Move board to new position
void Connect4UI::setBoardPosition(float x, float y)
{
    boardX = x;
    boardY = y;
}

// Resize board cells
void Connect4UI::setCellSize(float size)
{
    cellSize = size;
    pieceRadius = cellSize * 0.35f;  // Recalculate piece size
    boardWidth = 7 * cellSize;       // Recalculate board dimensions
    boardHeight = 6 * cellSize;
}

// Set new game colors
void Connect4UI::setColors(GameColor board, GameColor p1, GameColor p2, GameColor empty)
{
    boardColor = board;
    player1Color = p1;
    player2Color = p2;
    emptySlotColor = empty;
}



// Getters
//----------------------------------------------------------------------------------------//

float Connect4UI::getBoardX() const 
{ 
    return boardX; 
}

float Connect4UI::getBoardY() const 
{ 
    return boardY; 
}

float Connect4UI::getBoardWidth() const 
{ 
    return boardWidth; 
}

float Connect4UI::getBoardHeight() const 
{ 
    return boardHeight; 
}

float Connect4UI::getCellSize() const
{
    return cellSize;
}



// Private Helper Methods
//----------------------------------------------------------------------------------------//

// Turn gameColor to raylib Color
Color Connect4UI::gameColorToRaylib(GameColor gc) const
{
    return Color{gc.r, gc.g, gc.b, gc.a}; // raylib Color is a c struct use {} to initialize
}

float Connect4UI::getCellCenterX(int col) const
{
    return boardX + (col * cellSize) + (cellSize / 2.0f);
}

float Connect4UI::getCellCenterY(int row) const
{
    return boardY + (row * cellSize) + (cellSize / 2.0f);
}

