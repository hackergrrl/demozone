#include <limits.h>
#include <stdlib.h>
#include "raylib.h"

float randf (float min, float max) {
  float r = rand() / (float)INT_MAX;
  return r * (max-min) + min;
}

float lerpf (float c, float min, float max) {
  return (max-min) * c + min;
}

float clampf (float c, float min, float max) {
  if (c < min) return min;
  if (c > max) return max;
  return c;
}

int main(void)
{
  const int screenWidth = 640;
  const int screenHeight = 480;

  InitWindow(screenWidth, screenHeight, "DaNcE dAnCe");

  Vector2 pos = { screenWidth/2.0f, screenHeight/2.0f };
  Vector2 vel = { 0, 0 };

  SetTargetFPS(60);
  long tix = 0;
  long tint = 0;
  float staticStrength = 0.1f;

  // Main game loop
  while (!WindowShouldClose())  // detects ESC
  {
    // Update
    if (IsKeyDown(KEY_RIGHT)) vel.x += 4.0f;
    if (IsKeyDown(KEY_LEFT)) vel.x -= 4.0f;
    if (IsKeyDown(KEY_UP)) vel.y -= 4.0f;
    if (IsKeyDown(KEY_DOWN)) vel.y += 4.0f;
    if (IsKeyDown(KEY_SPACE)) tix = 0;
    vel.x *= 0.92f;
    vel.y *= 0.92f;
    pos.x += vel.x;
    pos.y += vel.y;

    if (tix % 95 == 0) {
      vel.x += randf(-100, 100);
      vel.y += randf(-100, 100);
    }
    if (tix % 48 == 0) {
      tint = rand();
    }
    if (tix % 190 == 0) {
      staticStrength = clampf(randf(-0.4f, 0.7f), 0.0f, 1.0f);
    }
    tix++;

    // Draw
    BeginDrawing();
        ClearBackground(RAYWHITE);
        for (int y=0; y < screenHeight; y += 8) {
          for (int x=0; x < screenWidth; x += 8) {
            // xor
            Color color = GetColor((x+(int)pos.x) ^ (y+(int)pos.y) + tint);

            // static
            if (rand()%100 < 50) {
              color.r = lerpf(staticStrength, color.r, 0);
              color.g = lerpf(staticStrength, color.g, 0);
              color.b = lerpf(staticStrength, color.b, 0);
            } else {
              color.r = lerpf(staticStrength, color.r, 255);
              color.g = lerpf(staticStrength, color.g, 255);
              color.b = lerpf(staticStrength, color.b, 255);
            }

            DrawRectangle(x, y, 8, 8, color);
          }
        }
        /* DrawFPS(5, 5); */
    EndDrawing();
  }

  CloseWindow();

  return 0;
}
