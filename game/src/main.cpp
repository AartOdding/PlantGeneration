#include <raylib.h>
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <cmrc/cmrc.hpp>

#include <iostream>
#include <fstream>
#include <vector>
#include <string>

#include "types.hpp"
#include "debug.hpp"
#include "target.hpp"
#include "sphere_world.hpp"
#include "player.hpp"

#include <LSystem/LSystem.hpp>


CMRC_DECLARE(resources);


Vector3 ToVec3(const glm::vec3& vec)
{
    return { vec.x, vec.y, vec.z };
}

Color ToColor(const glm::vec3& rgb)
{
    Color col;
    col.r = rgb.r * 255;
    col.g = rgb.g * 255;
    col.b = rgb.b * 255;
    col.a = 255;
    return col;
}

int main()
{
    try
    {
        auto fs = cmrc::resources::get_filesystem();

        {
            auto plant_data = fs.open("Plant1.plant");
            std::ofstream temp("Plant1.plant", std::ios::binary | std::ios::trunc);
            temp.write(plant_data.begin(), plant_data.size());
            temp.flush();
        }

        LSystem::Plant plant;
        
        {
            auto plant_file = std::ifstream("Plant1.plant", std::ios::binary);
            plant.LoadFrom(plant_file);
        }

        auto vertexBuffer = plant.Generate();

        const int screenWidth = 800;
        const int screenHeight = 450;

        SetConfigFlags(FLAG_MSAA_4X_HINT);
        SetConfigFlags(FLAG_VSYNC_HINT);
        SetConfigFlags(FLAG_WINDOW_RESIZABLE);
        InitWindow(800, 450, "Aart & Aart 4Mb Jam");

        SetExitKey(0); // Removes ESC to exit
        constexpr u32 fps = 60;
        SetTargetFPS(fps);

        // Setup Dear ImGui context
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGui::StyleColorsDark();

        ImGui_ImplGlfw_InitForOpenGL((GLFWwindow*)GetGLFWWindowHandle(), true);
        ImGui_ImplOpenGL3_Init("#version 330");

        Vector2 last_mouse_pos = GetMousePosition();

        Camera camera{};
        camera.position = { 0.0f, 1.8f, 6.0f };    // Camera position
        camera.target = { 0.0f, 0.5f, 0.0f };      // Camera looking at point
        camera.up = { 0.0f, 1.0f, 0.0f };          // Camera up vector (rotation towards target)
        camera.fovy = 45.0f;                       // Camera field-of-view Y
        camera.projection = CAMERA_PERSPECTIVE;    // Camera mode type

        f32 sphere_radius = 1.0_f32;
        Mesh mesh = GenMeshSphere(sphere_radius, 20, 20);
        auto model = LoadModelFromMesh(mesh);
        glm::dvec3 mesh_position(0.0_f32, 0.5_f32, 0.0_f32);
        glm::dvec3 mesh2_position(5.0_f32, 0.0_f32, 0.0_f32);

        f32 gravity = 2.0f;

        Mb4::SphereWorld world(4);

        Mb4::Player player({3.0_f32, 0.0_f32, 0.0_f32}, {0.0_f32, 1.0_f32, 0.0_f32});

        bool isPaused = true;

        while (!WindowShouldClose())
        {
            Vector2 mouse_diff = Vector2Subtract(GetMousePosition(), last_mouse_pos);
            last_mouse_pos = GetMousePosition();

            if (IsKeyPressed(KEY_ESCAPE))
            {
                if (isPaused)
                {
                    isPaused = false;
                    DisableCursor();
                    last_mouse_pos = GetMousePosition();
                }
                else
                {
                    isPaused = true;
                    EnableCursor();
                }
            }

            if (!isPaused)
            {
                player.Update(1.0_f32 / fps, gravity, world, glm::fvec2{mouse_diff.x, mouse_diff.y});
            }

            {
                glm::fvec3 campos = player.position + glm::normalize(player.position) * 1.0_f32;
                camera.position = {campos.x, campos.y, campos.z};
                glm::fvec3 forward = campos + player.GetRotatedForward();
                camera.target = {forward.x, forward.y, forward.z};
                glm::fvec3 up = player.position + player.GetRotatedUp();
                camera.up = {up.x, up.y, up.z};
            }

            BeginDrawing();

            ClearBackground(RAYWHITE);

            BeginMode3D(camera);

            for (auto const& triangle : world.triangles)
            {
                DrawTriangle3D(
                    Vector3{world.points[triangle.index1].x, world.points[triangle.index1].y, world.points[triangle.index1].z},
                    Vector3{world.points[triangle.index2].x, world.points[triangle.index2].y, world.points[triangle.index2].z},
                    Vector3{world.points[triangle.index3].x, world.points[triangle.index3].y, world.points[triangle.index3].z},
                    Color{255, 0, 0, 255});

                DrawLine3D(
                    Vector3{world.points[triangle.index1].x, world.points[triangle.index1].y, world.points[triangle.index1].z},
                    Vector3{world.points[triangle.index2].x, world.points[triangle.index2].y, world.points[triangle.index2].z},
                    Color{0, 0, 255, 255});

                DrawLine3D(
                    Vector3{world.points[triangle.index2].x, world.points[triangle.index2].y, world.points[triangle.index2].z},
                    Vector3{world.points[triangle.index3].x, world.points[triangle.index3].y, world.points[triangle.index3].z},
                    Color{0, 0, 255, 255});

                DrawLine3D(
                    Vector3{world.points[triangle.index1].x, world.points[triangle.index1].y, world.points[triangle.index1].z},
                    Vector3{world.points[triangle.index3].x, world.points[triangle.index3].y, world.points[triangle.index3].z},
                    Color{0, 0, 255, 255});
            }

            DrawGrid(40, 10.0f);

            for (auto& l : vertexBuffer.lines)
            {
                DrawLine3D(ToVec3(l.point_a.position), ToVec3(l.point_b.position), ToColor(l.point_b.color));
            }

            EndMode3D();

            // Start the Dear ImGui frame
            ImGui_ImplOpenGL3_NewFrame();
            ImGui_ImplGlfw_NewFrame();
            ImGui::NewFrame();

            ImGui::Render();
            ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

            if (isPaused)
            {
                DrawText("ESC to start/pause", GetScreenWidth() / 2, GetScreenHeight() / 2, 30, BLACK);
            }

            EndDrawing();
        }

        UnloadModel(model);

        CloseWindow();

        return 0;
    }
    catch(Mb4::AssertError err)
    {
        std::cout << err.what() << std::endl;
        return 1;
    }
}
