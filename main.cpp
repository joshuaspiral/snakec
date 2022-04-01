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

vector<pair<int, int>> snake = {pair<int, int> {0, 0}};
snake.push_back(pair<int, int> {0, 1});
snake.push_back(pair<int, int> {0, 2});
snake.push_back(pair<int, int> {0, 3});
snake.push_back(pair<int, int> {0, 4});
snake.push_back(pair<int, int> {1, 4});
snake.push_back(pair<int, int> {2, 4});

void moveSnake(Dir direction, vector<pair<int, int>> snake) {
    pair<int, int> newHead = snake[0];
    switch (direction) {
        case NORTH:
            cout << "NORTH" << endl;
            newHead.first += 1;
            break;
        case EAST:
            newHead.second += 1;
            break;
        case SOUTH:
            newHead.first -= 1;
            break;
        case WEST:
            newHead.second -= 1;
            break;
        default:
            break;
    }
    snake.insert(snake.begin(), newHead); 
    snake.pop_back();
}

void drawSnake(vector<pair<int, int>> snake) {
    for (pair<int,int> snakePart : snake) {
        DrawRectangle(snakePart.second * cellWidth, snakePart.first * cellHeight, cellWidth, cellHeight, BLACK);
    }
}

cellState board[ROWS][COLS] = {{EMPTY}};

int main() {
    InitWindow(WIDTH, HEIGHT, "Snake");
    SetTargetFPS(60);

    moveSnake(NORTH, snake);
    while (!WindowShouldClose()) {
        BeginDrawing();
        drawSnake(snake);
        EndDrawing();
    }
    CloseWindow();
}

