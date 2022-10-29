#include "raylib.h"
#include <cstdio>

int main()
{
    // Window Dimensions
    const int window_width = 800;
    const int window_height = 450;
    InitWindow(window_width, window_height, "My Window");

    // Circle Coordinates
    int circle_x = 200;
    int circle_y = 200;
    const int circle_radius = 25;
    // Circle Edges
    int l_circle_x = circle_x - circle_radius;
    int r_circle_x = circle_x + circle_radius;
    int u_circle_y = circle_y - circle_radius;
    int b_circle_y = circle_y + circle_radius;
    // Circle Movement
    const int circle_speed = 10;

    // Axe Coordinates
    int axe_x = 375;
    int axe_y = 0;
    const int axe_height = 50;
    const int axe_width = 50;
    // Axe Edges
    int l_axe_x = axe_x;
    int r_axe_x = axe_x + axe_width;
    int u_axe_y = axe_y;
    int b_axe_y = axe_y + axe_height;
    // Axe Movement
    int axe_velocity = 10;

    // Coin Coordinates
    const int coin_radius = 10;
    int coin_x_shift = 200;
    const int coin_y = 200;
    int coin_x = (window_width / 2) + coin_x_shift;
    int coin_count = 0;

    // Game variables
    const int win_coin_count = 10;

    bool collision_with_axe = b_axe_y >= u_circle_y && u_axe_y <= b_circle_y && l_axe_x <= r_circle_x && r_axe_x >= l_circle_x;
    bool collision_with_coin = (coin_x - coin_radius) <= r_circle_x && (coin_x + coin_radius) >= l_circle_x;

    SetTargetFPS(60);
    // Game Loop
    while (!WindowShouldClose())
    {
        // Start Drawing
        BeginDrawing();
        ClearBackground(WHITE);

        if (collision_with_axe)
        {
            DrawText("Game Over!", 350, 200, 20, RED);
        }
        else if (coin_count == win_coin_count)
        {
            DrawText("You Win!", 350, 200, 20, BLUE);
        }
        else
        {
            // ***** Game Logic Begins *****

            // Update circle edges
            l_circle_x = circle_x - circle_radius;
            r_circle_x = circle_x + circle_radius;
            u_circle_y = circle_y - circle_radius;
            b_circle_y = circle_y + circle_radius;
            // Update axe edges
            l_axe_x = axe_x;
            r_axe_x = axe_x + axe_width;
            u_axe_y = axe_y;
            b_axe_y = axe_y + axe_height;
            // Check for collision
            collision_with_axe = b_axe_y >= u_circle_y && u_axe_y <= b_circle_y && l_axe_x <= r_circle_x && r_axe_x >= l_circle_x;
            collision_with_coin = (coin_x - coin_radius) <= r_circle_x && (coin_x + coin_radius) >= l_circle_x;
            // Check for coin collection
            if (collision_with_coin)
            {
                coin_count += 1;
                coin_x_shift = -coin_x_shift;
            }
            // Axe movement
            axe_y += axe_velocity;
            if (axe_y > window_height - axe_height || axe_y < 0)
            {
                axe_velocity = -axe_velocity;
            }
            // Circle movement
            if (IsKeyDown(KEY_D) && circle_x < window_width)
            {
                circle_x += circle_speed;
            }
            if (IsKeyDown(KEY_A) && circle_x > 0)
            {
                circle_x -= circle_speed;
            }
            // Coin movement
            coin_x = (window_width / 2) + coin_x_shift;

            // ***** Game Logic Ends *****

            // Draw coin counter
            DrawText(TextFormat("Coins: %i/%i", coin_count, win_coin_count), 700, 10, 10, BLACK);
            // Draw player
            DrawCircle(circle_x, circle_y, circle_radius, BLUE);
            // Draw axe
            DrawRectangle(axe_x, axe_y, axe_width, axe_height, RED);
            // Draw coin
            DrawCircle(coin_x, coin_y, coin_radius, YELLOW);
        }
        // Stop Drawing
        EndDrawing();
    }
}