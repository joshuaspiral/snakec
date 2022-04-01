#include <iostream>
#include <raylib.h>
#include <vector>
#include <utility>
#define HEIGHT 800
#define WIDTH 800
#define ROWS 50
#define COLS 50

const int cellHeight = HEIGHT / ROWS;
const int cellWidth = WIDTH / COLS;

using namespace std;

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
    if (direction == NORTH) newHead.first = (newHead.first - 1 + ROWS) % ROWS;
    if (direction == EAST) newHead.second = (newHead.second + 1) % COLS;
    if (direction == SOUTH) newHead.first = (newHead.first + 1) % ROWS;
    if (direction == WEST) newHead.second = (newHead.second - 1 + COLS)  % COLS;

    snake.insert(snake.begin(), newHead); 
    snake.pop_back();
    return true;
}

void addPart(Dir direction) {
    pair<int, int> tail = snake[snake.size() - 1];
    if (direction == NORTH) tail.first = (tail.first - 1 + ROWS) % ROWS;
    if (direction == EAST) tail.second = (tail.second + 1) % COLS;
    if (direction == SOUTH) tail.first = (tail.first + 1) % ROWS;
    if (direction == WEST) tail.second = (tail.second - 1 + COLS)  % COLS;
    snake.push_back(tail);
}

void drawSnake() {
    for (pair<int,int> snakePart : snake) {
        DrawRectangle(snakePart.second * cellWidth, snakePart.first * cellHeight, cellWidth, cellHeight, BLACK);
    }
}

int main() {
    srand(time(0));
    InitWindow(WIDTH, HEIGHT, "Snake");
    SetTargetFPS(15);

    Dir curDir;
    int points = 0;
    pair<int, int> fruitPos = {rand() % ROWS, rand() % COLS};

    while (!WindowShouldClose()) {
        if (IsKeyDown(KEY_UP) && curDir != SOUTH) curDir = NORTH;
        else if (IsKeyDown(KEY_RIGHT) && curDir != WEST) curDir = EAST;
        else if (IsKeyDown(KEY_DOWN) && curDir != NORTH) curDir = SOUTH;
        else if (IsKeyDown(KEY_LEFT) && curDir != EAST) curDir = WEST;
        if (snake.front() == fruitPos) {
            fruitPos = {rand() % ROWS, rand() % COLS};
            addPart(curDir);
            points++;
        }
        for (unsigned long i = 1; i < snake.size(); i++) {
            if (snake[0] == snake[i]) {
                printf("Game over");
                return EXIT_SUCCESS;
            }
        }
        changeDirection(curDir);
        BeginDrawing();
        ClearBackground(WHITE);
        drawSnake();
        DrawRectangle(fruitPos.second * cellWidth, fruitPos.first * cellHeight, cellWidth, cellHeight, RED);
        string pointStr = to_string(points);
        char* pointChar = &pointStr[0];
        DrawText(pointChar, 0, 0, 50, BLACK);
        EndDrawing();
    }
    CloseWindow();
    return EXIT_SUCCESS;
}

