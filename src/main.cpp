#include "game.hpp"

int main(void) {
    Game game(800, 450);
    
    InitWindow(game.screenWidth, game.screenHeight, "Snake Game by CleverCode");
    game.Init();
    SetTargetFPS(60);
    
    while (!WindowShouldClose()) {
        game.Update();
        game.Draw();
    }

    CloseWindow();
    return 0;
}
