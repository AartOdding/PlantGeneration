#include <external/glad.h>
#include <raylib.h>
#include <raymath.h>
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include <ImGuizmo.h>
#include <GLFW/glfw3.h>

#include <cmrc/cmrc.hpp>
#include <algorithm>
#include <iostream>

#include <LSystem/LSystem.hpp>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/random.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "LSystemWindow.hpp"

CMRC_DECLARE(resources);

int recurse_count = 5;
int fork_count = 5;
float roll = 0;
float pitch = glm::quarter_pi<float>();
float scale = 0.7;
float spread = 0.7;

float camera_minmax_y = 0.3;
float camera_speed_sideways = 0.007;
float camera_speed_updown = 0.3;


LSystem::LSystem CreateDandelion()
{
    LSystem::LSystem lsystem;

    auto rule = lsystem.CreateRule("A");
    lsystem.starting_rule = rule->id;

    auto start = LSystem::CreateExtrusion(0.5);

    //start[0]->data.children = LSystem::CreateFork(fork_count, 0, 0, pitch);
    start[0]->data.next_rules = LSystem::CreateRecursingFork(rule, fork_count, scale, roll, pitch);

    rule->data = std::move(start[0]->data);

    return lsystem;
}

LSystem::LSystem CreateTree()
{
    LSystem::LSystem lsystem;

    auto rule = lsystem.CreateRule("A");
    lsystem.starting_rule = rule->id;

    auto start = LSystem::CreateExtrusion(0.5);

    start[0]->data.next_rules = LSystem::CreateRecursingFan(rule, fork_count, spread, scale, roll);
    //start[0]->data.next_rules = LSystem::CreateRecursingFork(rule, fork_count, scale, roll, pitch);

    rule->data = std::move(start[0]->data);

    return lsystem;
}

int main()
{
    auto lsystem = CreateTree();

    SetConfigFlags(FLAG_MSAA_4X_HINT);
    SetConfigFlags(FLAG_VSYNC_HINT);
    //SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(1080, 1350, "Aart & Aart 4Mb Jam");

    SetTargetFPS(30);

    // Setup Dear ImGui context
    ImGui::CreateContext();
    ImGui::StyleColorsDark();
    ImGui::GetIO().FontGlobalScale = 2;

    ImGui_ImplGlfw_InitForOpenGL((GLFWwindow*)GetGLFWWindowHandle(), true);
    ImGui_ImplOpenGL3_Init("#version 330");

    Camera camera{};
    camera.position = { 0.0f, 1.8f, 6.0f };    // Camera position
    camera.target = { 0.0f, 1.7f, 0.0f };      // Camera looking at point
    camera.up = { 0.0f, 1.0f, 0.0f };          // Camera up vector (rotation towards target)
    camera.fovy = 45.0f;                       // Camera field-of-view Y
    camera.projection = CAMERA_PERSPECTIVE;    // Camera mode type

    float camera_distance = 7;
    float camera_rotation_sideways = 0;
    float camera_rotation_updown = 0.3;

    Vector2 previous_mouse_pos{ -1, -1 };
    bool render_gui = true;
    bool orbit_mode = true;

    while (!WindowShouldClose())
    {
        if (IsKeyDown(KEY_DOWN))
        {
            camera.target.y += 0.02;
        }
        if (IsKeyDown(KEY_UP))
        {
            camera.target.y -= 0.02;
        }
        if (GetMouseWheelMove() != 0)
        {
            const float desired_distance = camera_distance * std::pow(0.9, GetMouseWheelMove());
            camera_distance = std::clamp<float>(desired_distance, 0.1, 1000);
        }

        if (orbit_mode)
        {
            camera_rotation_sideways += camera_speed_sideways;
            camera_rotation_updown = camera_minmax_y * sin(camera_speed_updown * GetTime());
        }
        else
        {
            // Manual controls:

            if (IsMouseButtonDown(1))
            {
                if (previous_mouse_pos.x == -1 && previous_mouse_pos.y == -1)
                {
                    previous_mouse_pos = GetMousePosition();
                }
                auto movement = Vector2Subtract(GetMousePosition(), previous_mouse_pos);

                camera_rotation_sideways += -movement.x / (GetScreenWidth() / 5.0f);
                camera_rotation_updown += movement.y / (GetScreenHeight() / 5.0f);
            }
        }

        const Quaternion sideways_quaternion = QuaternionFromEuler(0, camera_rotation_sideways, 0);
        const Vector3 pos_xz = Vector3RotateByQuaternion({ 0, 0, camera_distance }, sideways_quaternion);
        const Vector3 tangent = Vector3RotateByQuaternion(pos_xz, QuaternionFromEuler(0, -glm::half_pi<float>(), 0));
        const Quaternion updown_quaternion = QuaternionFromAxisAngle(tangent, camera_rotation_updown);
        const Vector3 camera_position = Vector3RotateByQuaternion(pos_xz, updown_quaternion);

        camera.position = Vector3Add(camera.target, camera_position);

        previous_mouse_pos = GetMousePosition();

        if (IsKeyPressed(KEY_E))
        {
            render_gui = !render_gui;
        }
        if (IsKeyPressed(KEY_O))
        {
            orbit_mode = !orbit_mode;
        }

        BeginDrawing();

        ClearBackground(BLACK);

        BeginMode3D(camera);


        //DrawGrid(40, 10.0f);

        auto buf = LSystem::Generate(&lsystem.rules.begin()->second->data, recurse_count);

        for (auto& l : buf.lines)
        {
            DrawLine3D({ l.point_a.position.x, l.point_a.position.y, l.point_a.position.z }, 
                       { l.point_b.position.x, l.point_b.position.y, l.point_b.position.z }, WHITE);
        }

        EndMode3D();

        // Start the Dear ImGui frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
        ImGuizmo::BeginFrame();

        /*
        auto projection_matrix = glm::perspective<float>(camera.fovy, GetScreenHeight() / GetScreenWidth(), 0.1, 1000);
        auto cam_pos = glm::vec3(camera.position.x, camera.position.y, camera.position.z);
        auto cam_target = glm::vec3(camera.target.x, camera.target.y, camera.target.z);
        auto cam_up = glm::vec3(camera.up.x, camera.up.y, camera.up.z);
        auto view_matrix = glm::lookAt(cam_pos, cam_target, cam_up);

        static glm::mat4 mat{ 1 };

        ImGuizmo::Manipulate(glm::value_ptr(view_matrix), glm::value_ptr(projection_matrix), 
            ImGuizmo::TRANSLATE, ImGuizmo::LOCAL, glm::value_ptr(mat));*/
        //ImGuizmo::Manipulate()

        if (ImGui::SliderInt("Recursions", &recurse_count, 1, 10))
        {
            lsystem = CreateTree();
        }
        if (ImGui::SliderInt("Divisions", &fork_count, 1, 20))
        {
            lsystem = CreateTree();
        }
        if (ImGui::SliderFloat("Roll", &roll, 0, glm::two_pi<float>()))
        {
            lsystem = CreateTree();
        }
        if (ImGui::SliderFloat("Pitch", &pitch, 0, glm::two_pi<float>()))
        {
            lsystem = CreateTree();
        }
        if (ImGui::SliderFloat("Scale", &scale, 0, 2))
        {
            lsystem = CreateTree();
        }
        if (ImGui::SliderFloat("Spread", &spread, 0, 8))
        {
            lsystem = CreateTree();
        }

        bool show = true;
        //ImGui::ShowDemoWindow(&show);
        //lsystemWindow.Draw();

        ImGui::Render();

        if (render_gui)
        {
            ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        }

        EndDrawing();
    }

    CloseWindow();

    return 0;
}
