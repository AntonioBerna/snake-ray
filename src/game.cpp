#include "game.hpp"

void Game::Init(void) {
    framesCounter = 0;
    gameOver = false;
    pause = false;

    counterTail = 1;
    allowMove = false;

    offset.x = screenWidth % SQUARE_SIZE;
    offset.y = screenHeight % SQUARE_SIZE;

    for (uint16_t i = 0; i < SNAKE_LENGTH; ++i) {
        snake[i].position = {offset.x / 2, offset.y / 2};
        snake[i].size = {SQUARE_SIZE, SQUARE_SIZE};
        snake[i].speed = {SQUARE_SIZE, 0};
        if (i == 0) snake[i].color = DARKPURPLE; else snake[i].color = VIOLET;
    }
    for (uint16_t i = 0; i < SNAKE_LENGTH; ++i) snakePosition[i] = {0.0f, 0.0f};

    fruit.size = {SQUARE_SIZE, SQUARE_SIZE};
    fruit.color = PURPLE;
    fruit.active = false;
}

void Game::Update(void) {
    if (!gameOver) {
        if (IsKeyPressed(KEY_SPACE)) pause = !pause;

        if (!pause) {
            // Player control
            if (IsKeyPressed(KEY_RIGHT) && (snake[0].speed.x == 0) && allowMove) {
                snake[0].speed = (Vector2){SQUARE_SIZE, 0};
                allowMove = false;
            }
            if (IsKeyPressed(KEY_LEFT) && (snake[0].speed.x == 0) && allowMove) {
                snake[0].speed = (Vector2){-SQUARE_SIZE, 0};
                allowMove = false;
            }
            if (IsKeyPressed(KEY_UP) && (snake[0].speed.y == 0) && allowMove) {
                snake[0].speed = (Vector2){0, -SQUARE_SIZE};
                allowMove = false;
            }
            if (IsKeyPressed(KEY_DOWN) && (snake[0].speed.y == 0) && allowMove) {
                snake[0].speed = (Vector2){0, SQUARE_SIZE};
                allowMove = false;
            }

            // Snake movement
            for (uint16_t i = 0; i < counterTail; ++i) snakePosition[i] = snake[i].position;
            if ((framesCounter % 5) == 0) {
                for (uint16_t i = 0; i < counterTail; ++i) {
                    if (i == 0) {
                        snake[0].position.x += snake[0].speed.x;
                        snake[0].position.y += snake[0].speed.y;
                        allowMove = true;
                    } else {
                        snake[i].position = snakePosition[i - 1];
                    }
                }
            }

            // Wall behaviour
            if (((snake[0].position.x) > (screenWidth - offset.x)) || ((snake[0].position.y) > (screenHeight - offset.y)) || (snake[0].position.x < 0) || (snake[0].position.y < 0)) gameOver = true;

            // Collision with yourself
            for (uint16_t i = 1; i < counterTail; ++i) {
                if ((snake[0].position.x == snake[i].position.x) && (snake[0].position.y == snake[i].position.y)) gameOver = true;
            }

            // Fruit position calculation
            if (!fruit.active) {
                fruit.active = true;
                fruit.position = (Vector2){GetRandomValue(0, (screenWidth / SQUARE_SIZE) - 1) * SQUARE_SIZE + offset.x / 2, GetRandomValue(0, (screenHeight / SQUARE_SIZE) - 1) * SQUARE_SIZE + offset.y / 2};

                for (uint16_t i = 0; i < counterTail; ++i) {
                    while ((fruit.position.x == snake[i].position.x) && (fruit.position.y == snake[i].position.y)) {
                        fruit.position = (Vector2){GetRandomValue(0, (screenWidth / SQUARE_SIZE) - 1) * SQUARE_SIZE + offset.x / 2, GetRandomValue(0, (screenHeight / SQUARE_SIZE) - 1) * SQUARE_SIZE + offset.y / 2};
                        i = 0;
                    }
                }
            }

            // Collision
            if ((snake[0].position.x < (fruit.position.x + fruit.size.x) && (snake[0].position.x + snake[0].size.x) > fruit.position.x) && (snake[0].position.y < (fruit.position.y + fruit.size.y) && (snake[0].position.y + snake[0].size.y) > fruit.position.y)) {
                snake[counterTail].position = snakePosition[counterTail - 1];
                counterTail += 1;
                fruit.active = false;
            }

            framesCounter++;
        }
    } else {
        if (IsKeyPressed(KEY_ENTER)) {
            Init();
            gameOver = false;
        }
    }
}

void Game::Draw(void) {
    BeginDrawing();
    ClearBackground(RAYWHITE);
    if (!gameOver) {
        for (uint16_t i = 0; i < screenWidth / SQUARE_SIZE + 1; ++i) {
            DrawLineV((Vector2){SQUARE_SIZE * i + offset.x / 2, offset.y / 2}, (Vector2){SQUARE_SIZE * i + offset.x / 2, screenHeight - offset.y / 2}, LIGHTGRAY);
        }

        for (uint16_t i = 0; i < screenHeight / SQUARE_SIZE + 1; ++i) {
            DrawLineV((Vector2){offset.x / 2, SQUARE_SIZE * i + offset.y / 2}, (Vector2){screenWidth - offset.x / 2, SQUARE_SIZE * i + offset.y / 2}, LIGHTGRAY);
        }

        // Draw snake
        for (uint16_t i = 0; i < counterTail; ++i) DrawRectangleV(snake[i].position, snake[i].size, snake[i].color);

        // Draw fruit to pick
        DrawRectangleV(fruit.position, fruit.size, fruit.color);

        if (pause) DrawText("GAME PAUSED", screenWidth / 2 - MeasureText("GAME PAUSED", 40) / 2, screenHeight / 2 - 40, 40, GRAY);
    } else {
        DrawText("PRESS [ENTER] TO PLAY AGAIN", GetScreenWidth() / 2 - MeasureText("PRESS [ENTER] TO PLAY AGAIN", 20) / 2, GetScreenHeight() / 2 - 50, 20, GRAY);
    }
    EndDrawing();
}