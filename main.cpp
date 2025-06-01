// Connect 4
// This is the main function for the Connect 4 game

#include "ui.h"
#include <iostream>

using std::cout, std::endl;

int main()
{
    // Initialize raylib window
    const int screenWidth = 900;
    const int screenHeight = 700;
    InitWindow(screenWidth, screenHeight, "Connect 4");
    SetTargetFPS(60);

    // Create game objects
    Connect4Game game;
    Connect4UI ui(150, 150, 70); // x = 150, y = 150, cellSize = 70

    // Game state variables
    bool gameRunning = true;
    int hoveredColumn = -1; // Default invalid column chosen

    // Main game loop
    while(!WindowShouldClose() && gameRunning)
    {
        // INPUT HANDLING
        Vector2 mousePos = GetMousePosition(); // Vector2: float x, y;

        // Get column mouse is hovering over
        hoveredColumn = ui.getColumnFromMouseX(mousePos.x);

        // Handle mouse clicks
        if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        {
            // Hovered column is valid and game is running
            if(hoveredColumn != -1 && !game.isGameOver())
            {
                // Attempt to drop piece in clicked column
                bool success = game.dropPiece(hoveredColumn);
                if(success)
                {
                    cout << "Player " << (game.getCurrentPlayer() == 1 ? 2 : 1)
                         << " dropped piece in column " << hoveredColumn << endl;

                    // Update game state by checking for winner/tie
                    game.checkWinner();

                    // Check if game is over after the move
                    if(game.isGameOver())
                    {
                        if(game.getWinner() != 0)
                            cout << "Game Over! Player " << game.getWinner() << " wins!" << endl;
                        else
                            cout << "Game Over! It's a tie!" << endl;
                    }
                }
                else // !success
                    cout << "Column " << hoveredColumn << " is full!" << endl;
            }
        }

        // Handle keyboard input
        if(IsKeyPressed(KEY_R)) // R - reset game
        {
            game.resetGame();
            cout << "Game reset!" << endl;
        }

        if(IsKeyPressed(KEY_ESCAPE)) // ESC - quit game
            gameRunning = false;

        // RENDERING
        BeginDrawing(); // Tells raylib to start a new frame

        // Clear background
        ClearBackground(LIGHTGRAY); // Fill screen with background color

        // Draw game title
        DrawText("Connect 4", 10, 10, 32, DARKBLUE);

        // Draw instructions
        DrawText("Click to drop piece", 10, 50, 20, DARKGRAY);
        DrawText("Press R to reset", 10, 75, 20, DARKGRAY);
        DrawText("Press ESC to quit", 10, 100, 20, DARKGRAY);

        // Draw game status (Player turn / Win / Tie)
        ui.drawGameStatus(game);

        // Draw the board
        ui.drawBoard(game);

        // Draw column hover effect
        if(hoveredColumn != -1 && !game.isGameOver() && ui.isMouseOverBoard(mousePos.x, mousePos.y))
        {
            float columnX = ui.getBoardX() + (hoveredColumn * ui.getCellSize());
            Color hoverColor;
            if(game.getCurrentPlayer() == 1)
                hoverColor = RED; // RED - Player 1
            else
                hoverColor = YELLOW; // YELLOW - Player 2

            // Draw rounded rectangle with correct hover color for player
            Rectangle hoverRect = {columnX, ui.getBoardY() - 20, 70, 20};
            DrawRectangleRounded(hoverRect, 0.3f, 0, hoverColor);
        }

        EndDrawing(); // Tells raylib "frame is complete, show it on screen"
    }

    // Cleanup
    CloseWindow();
    return 0;
}
