#pragma once

#include <cstdint>

#include "raylib.h"

struct Snake {
    Vector2 position;
    Vector2 size;
    Vector2 speed;
    Color color;
};

class Food {
public:
    Vector2 position;
    Vector2 size;
    bool active;
    Color color;
};

class Game {
public:
    const int screenWidth;
    const int screenHeight;

    Game(const int width, const int height) : screenWidth(width), screenHeight(height) {}
    
    void Init(void);
    void Update(void);
    void Draw(void);

private:
    int framesCounter;
    bool gameOver;
    bool pause;

    uint16_t counterTail;
    bool allowMove;
    
    Vector2 offset;

    static const uint16_t SNAKE_LENGTH = 1 << 8;
    static const uint8_t SQUARE_SIZE = 1 << 5;
    Snake snake[SNAKE_LENGTH];
    Vector2 snakePosition[SNAKE_LENGTH];

    Food fruit;
};
