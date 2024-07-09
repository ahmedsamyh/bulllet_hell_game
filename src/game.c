#include <raylib.h>
#include <raymath.h>
#include <stdio.h>
#include <config.h>

int main(void) {

    InitWindow(WIDTH, HEIGHT, "Game");

    while (!WindowShouldClose())
    {
        BeginDrawing();
            ClearBackground(BLACK);
        EndDrawing();
    }

    CloseWindow();

    return 0;
}
