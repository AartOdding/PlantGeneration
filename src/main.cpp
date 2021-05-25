#include "raylib.h"

#include <cmrc/cmrc.hpp>
#include <iostream>

CMRC_DECLARE(resources);


int main()
{
    auto fs = cmrc::resources::get_filesystem();
    auto f = fs.open("shaders/test.frag");

    std::string frag = std::string(f.begin(), f.end());
    std::cout << frag << std::endl;

    const int screenWidth = 800;
    const int screenHeight = 450;

    SetConfigFlags(FLAG_MSAA_4X_HINT);
    SetConfigFlags(FLAG_VSYNC_HINT);
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(800, 450, "Aart & Aart 4Mb Jam");

    SetExitKey(0); // Removes ESC to exit
    SetTargetFPS(60);

    Camera camera{};
    camera.position = { 0.0f, 1.8f, 6.0f };    // Camera position
    camera.target = { 0.0f, 0.5f, 0.0f };      // Camera looking at point
    camera.up = { 0.0f, 1.0f, 0.0f };          // Camera up vector (rotation towards target)
    camera.fovy = 45.0f;                       // Camera field-of-view Y
    camera.projection = CAMERA_PERSPECTIVE;    // Camera mode type

    auto mesh = GenMeshCube(1, 1, 1);
    auto model = LoadModelFromMesh(mesh);

    bool isPaused = true;

    while (!WindowShouldClose())
    {
        if (IsMouseButtonReleased(0)) // Only fires on the frame where the button is released
        {
            SetCameraMode(camera, CAMERA_FIRST_PERSON);
            isPaused = false;
        }
        if (IsKeyPressed(KEY_ESCAPE) || IsKeyPressed(KEY_P)) // Only fires on the frame where a key is released
        {
            SetCameraMode(camera, CAMERA_CUSTOM);
            isPaused = true;
        }

        UpdateCamera(&camera);

        BeginDrawing();

        ClearBackground(RAYWHITE);

        BeginMode3D(camera);

        DrawModel(model, { 0, 0, 0 }, 0.5, RED);
        DrawGrid(40, 10.0f);

        EndMode3D();

        if (isPaused)
        {
            DrawText("Click to start", GetScreenWidth() / 2, GetScreenHeight() / 2, 30, BLACK);
        }

        EndDrawing();
    }

    UnloadModel(model);

    CloseWindow();

    return 0;
}
