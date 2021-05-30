#include <raylib.h>
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <cmrc/cmrc.hpp>

#include <iostream>
#include <vector>
#include <string>

#include "types.hpp"
#include "debug.hpp"
#include "target.hpp"
#include "sphere_world.hpp"
#include "player.hpp"

CMRC_DECLARE(resources);

int main()
{
    try
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
        constexpr u32 fps = 60;
        SetTargetFPS(fps);

        // Setup Dear ImGui context
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGui::StyleColorsDark();

        ImGui_ImplGlfw_InitForOpenGL((GLFWwindow*)GetGLFWWindowHandle(), true);
        ImGui_ImplOpenGL3_Init("#version 330");

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

        Mb4::SphereWorld world(5);

        Mb4::Player player({3.0_f32, 0.0_f32, 0.0_f32}, {0.0_f32, 1.0_f32, 0.0_f32});

        bool isPaused = true;

        while (!WindowShouldClose())
        {
            {
                std::vector<Mb4::Targetable const*> targetables;
                Mb4::Targetable sphere_targetable(sphere_radius, mesh_position, 123);
                targetables.emplace_back(&sphere_targetable);
                Mb4::Targetable sphere_targetable2(sphere_radius, mesh2_position, 666);
                targetables.emplace_back(&sphere_targetable2);
                std::optional<u32> target = Mb4::GetTarget(
                    targetables.begin(),
                    targetables.end(),
                    camera.position,
                    camera.target);
                /*if (target.has_value())
                    Mb4::DebugPrint(std::to_string(target.value()));
                else
                    Mb4::DebugPrint("No target");*/
            }

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

            if (!isPaused)
            {
                player.Update(1.0_f32 / fps, gravity);
            }
            UpdateCamera(&camera);

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

            /*
            {
                Vector3 model_pos;
                model_pos.x = mesh_position.x;
                model_pos.y = mesh_position.y;
                model_pos.z = mesh_position.z;
                DrawModel(model, model_pos, 1.0_f32, RED);
            }
            {
                Vector3 model_pos;
                model_pos.x = mesh2_position.x;
                model_pos.y = mesh2_position.y;
                model_pos.z = mesh2_position.z;
                DrawModel(model, model_pos, 1.0_f32, RED);
            }*/

            {
                Vector3 player_pos;
                player_pos.x = player.position.x;
                player_pos.y = player.position.y;
                player_pos.z = player.position.z;
                DrawCube(player_pos, 0.5_f32, 0.5_f32, 0.5_f32, Color{255, 0, 0, 255});
                DrawLine3D(player_pos, Vector3Add(player_pos, {player.forward.x, player.forward.y, player.forward.z}), Color{0, 255, 0, 255});
            }

            DrawGrid(40, 10.0f);

            EndMode3D();

            // Start the Dear ImGui frame
            ImGui_ImplOpenGL3_NewFrame();
            ImGui_ImplGlfw_NewFrame();
            ImGui::NewFrame();

            std::string message = std::string("x: ") + std::to_string(player.velocity.x) + std::string(" y: ") + std::to_string(player.velocity.y) + std::string(" z: ") + std::to_string(player.velocity.z);
            ImGui::Text(message.c_str());

            ImGui::Render();
            ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

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
    catch(Mb4::AssertError err)
    {
        std::cout << err.what() << std::endl;
        return 1;
    }
}
