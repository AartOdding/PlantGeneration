#include <external/glad.h>
#include <raylib.h>
#include <raymath.h>
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include <GLFW/glfw3.h>

#include <cmrc/cmrc.hpp>
#include <algorithm>
#include <iostream>

#include <LSystem/LSystem.hpp>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/random.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Tree.hpp"
#include "Trees.hpp"
#include "TreeEditWindow.hpp"


CMRC_DECLARE(resources);


struct EditorConfig
{
    float camera_minmax_y = 0.3;
    float camera_speed_sideways = 0.007;
    float camera_speed_updown = 0.3;

    bool orbit_mode = true;
    bool editing_mode = true;
    
    glm::vec3 background_color = glm::vec3(0, 0, 0);

    int last_width = 1080;
    int last_height = 1350;
};

void DrawEditorConfigindow(EditorConfig& editor_config)
{
    ImGui::Begin("Editor Config");

    ImGui::SliderFloat("Camera min/max Y", &editor_config.camera_minmax_y, 0, 1.5);
    ImGui::SliderFloat("Camera rotation speed", &editor_config.camera_speed_sideways, 0, 0.05);
    ImGui::SliderFloat("Camera up/down speed", &editor_config.camera_speed_updown, 0, 2);
    ImGui::ColorEdit3("Background color", &editor_config.background_color.x);

    ImGui::End();
}

struct CameraState
{
    float camera_distance = 7;
    float camera_rotation_sideways = 0;
    float camera_rotation_updown = 0.3;

    Vector2 previous_mouse_pos{ -1, -1 };
};

void UpdateCameraState(Camera& camera, CameraState& camera_state, EditorConfig& editor_config)
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
        const float desired_distance = camera_state.camera_distance * std::pow(0.95, GetMouseWheelMove());
        camera_state.camera_distance = std::clamp<float>(desired_distance, 0.1, 1000);
    }

    if (editor_config.orbit_mode)
    {
        camera_state.camera_rotation_sideways += editor_config.camera_speed_sideways;
        camera_state.camera_rotation_updown = editor_config.camera_minmax_y * sin(editor_config.camera_speed_updown * GetTime());
    }
    else
    {
        // Manual controls:

        if (IsMouseButtonDown(1))
        {
            if (camera_state.previous_mouse_pos.x == -1 && camera_state.previous_mouse_pos.y == -1)
            {
                camera_state.previous_mouse_pos = GetMousePosition();
            }
            auto movement = Vector2Subtract(GetMousePosition(), camera_state.previous_mouse_pos);

            camera_state.camera_rotation_sideways += -movement.x / (GetScreenWidth() / 5.0f);
            camera_state.camera_rotation_updown += movement.y / (GetScreenHeight() / 5.0f);
        }
    }

    const Quaternion sideways_quaternion = QuaternionFromEuler(0, camera_state.camera_rotation_sideways, 0);
    const Vector3 pos_xz = Vector3RotateByQuaternion({ 0, 0, camera_state.camera_distance }, sideways_quaternion);
    const Vector3 tangent = Vector3RotateByQuaternion(pos_xz, QuaternionFromEuler(0, -glm::half_pi<float>(), 0));
    const Quaternion updown_quaternion = QuaternionFromAxisAngle(tangent, camera_state.camera_rotation_updown);
    const Vector3 camera_position = Vector3RotateByQuaternion(pos_xz, updown_quaternion);

    camera.position = Vector3Add(camera.target, camera_position);

    camera_state.previous_mouse_pos = GetMousePosition();
}


int main()
{
    EditorConfig editor_config;
    CameraState camera_state;

    Flower1 current_tree;
    auto lsystem = current_tree.Generate();

    SetConfigFlags(FLAG_MSAA_4X_HINT);
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    SetConfigFlags(FLAG_VSYNC_HINT);
    
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


    while (!WindowShouldClose())
    {
        UpdateCameraState(camera, camera_state, editor_config);

        if (IsKeyPressed(KEY_E))
        {
            editor_config.editing_mode = !editor_config.editing_mode;

            if (editor_config.editing_mode)
            {
                SetWindowSize(editor_config.last_width, editor_config.last_height);
            }
            else
            {
                editor_config.last_width = GetScreenWidth();
                editor_config.last_height = GetScreenHeight();
                SetWindowSize(1080, 1350);
            }
        }
        if (IsKeyPressed(KEY_O))
        {
            editor_config.orbit_mode = !editor_config.orbit_mode;
        }

        BeginDrawing();

        ClearBackground(Color(editor_config.background_color.r * 255, 
                              editor_config.background_color.g * 255, 
                              editor_config.background_color.b * 255, 255));

        BeginMode3D(camera);


        auto buf = LSystem::Generate(lsystem.begin, 5);

        for (auto& l : buf.lines)
        {
            DrawLine3D({ l.point_a.position.x, l.point_a.position.y, l.point_a.position.z }, 
                       { l.point_b.position.x, l.point_b.position.y, l.point_b.position.z }, 
                       Color(l.point_b.color.r * 255, l.point_b.color.g * 255, l.point_b.color.b * 255, 255));
        }

        EndMode3D();

        // Start the Dear ImGui frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        DrawEditorConfigindow(editor_config);

        if (DrawTreeParameters(&current_tree, "Tree"))
        {
            lsystem = current_tree.Generate();
        }

        ImGui::Render();

        if (editor_config.editing_mode)
        {
            ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        }

        EndDrawing();
    }

    CloseWindow();

    return 0;
}
