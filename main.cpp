#include <iostream>
#include <raylib.h>
#include <vector>
#include <utility>
#define HEIGHT 800
#define WIDTH 800
#define ROWS 100
#define COLS 100

using namespace std;

const int cellHeight = HEIGHT / ROWS;
const int cellWidth = WIDTH / COLS;

typedef enum {
    EMPTY, 
    FOOD,
    PLAYER
} cellState;

typedef enum {
    NORTH, 
    EAST,
    SOUTH,
    WEST,
} Dir;

vector<pair<int, int>> snake = {pair<int, int> {ROWS / 2, COLS / 2}};


bool changeDirection(Dir direction) {
    pair<int, int> newHead = snake[0];
    switch (direction) {
        case NORTH:
            newHead.first = (newHead.first - 1) % ROWS;
            break;
        case EAST:
            newHead.second = (newHead.second + 1) % COLS;
            break;
        case SOUTH:
            newHead.first = (newHead.first + 1) % ROWS;
            break;
        case WEST:
            newHead.second = (newHead.second - 1 + COLS)  % COLS;
            break;
        default:
            break;
    }

    snake.insert(snake.begin(), newHead); 
    snake.pop_back();
    return true;
}

void addPart(Dir direction) {
    pair<int, int> tail = snake[snake.size() - 1];
    switch (direction) {
        case NORTH:
            tail.first = (tail.first - 1) % ROWS;
            break;
        case EAST:
            tail.second = (tail.second + 1) % COLS;
            break;
        case SOUTH:
            tail.first = (tail.first + 1) % ROWS;
            break;
        case WEST:
            tail.second = (tail.second - 1 + COLS)  % COLS;
            break;
        default:
            break;
    }
    snake.push_back(tail);
}
void drawSnake() {
    for (pair<int,int> snakePart : snake) {
        DrawRectangle(snakePart.second * cellWidth, snakePart.first * cellHeight, cellWidth, cellHeight, BLACK);
    }
}

int main() {
    InitWindow(WIDTH, HEIGHT, "Snake");
    SetTargetFPS(30);

    Dir curDir;
    while (!WindowShouldClose()) {
        if (IsKeyDown(KEY_UP)) curDir = NORTH;
        else if (IsKeyDown(KEY_RIGHT)) curDir = EAST;
        else if (IsKeyDown(KEY_DOWN)) curDir = SOUTH;
        else if (IsKeyDown(KEY_LEFT)) curDir = WEST;
        else if (IsKeyDown(KEY_EQUAL)) addPart(curDir);
        changeDirection(curDir);
        BeginDrawing();
        ClearBackground(WHITE);
        drawSnake();
        EndDrawing();
    }
    CloseWindow();
}

