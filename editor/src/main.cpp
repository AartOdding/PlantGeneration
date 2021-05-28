#include <external/glad.h>
#include <raylib.h>
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include <GLFW/glfw3.h>

#include <cmrc/cmrc.hpp>
#include <iostream>

#include <LSystem/LSystem.hpp>


#include <glm/gtc/matrix_transform.hpp>


CMRC_DECLARE(resources);

auto up1 = glm::translate(glm::mat4(1), glm::vec3(0, 1, 0));
auto right1 = glm::translate(glm::mat4(1), glm::vec3(0.5, 0.5, 0));
auto left1 = glm::translate(glm::mat4(1), glm::vec3(-0.5, 0.5, 0));


void CreateTree(LSystem::Branch* prev, int depth, int max_depth)
{
    if (depth > max_depth) return;

    auto branch1 = std::make_unique<LSystem::Branch>();
    branch1->transform = up1;
    auto branch2 = std::make_unique<LSystem::Branch>();
    branch2->transform = right1;
    auto branch3 = std::make_unique<LSystem::Branch>();
    branch3->transform = left1;

    prev->main_branch = std::move(branch1);
    prev->side_branches.push_back(std::move(branch2));
    prev->side_branches.push_back(std::move(branch3));

    CreateTree(prev->main_branch.get(), depth + 1, max_depth);
    CreateTree(prev->side_branches[0].get(), depth + 1, max_depth);
    CreateTree(prev->side_branches[1].get(), depth + 1, max_depth);
}

int main()
{
    auto branch1 = std::make_unique<LSystem::Branch>();
    branch1->transform = up1;

    CreateTree(branch1.get(), 0, 5);

    auto buf = LSystem::Generate(branch1.get());


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

        //DrawModel(model, { 0, 0, 0 }, 0.5, RED);
        DrawGrid(40, 10.0f);

        for (auto& l : buf.lines)
        {
            DrawLine3D({ l.point_a.position.x, l.point_a.position.y, l.point_a.position.z }, 
                       { l.point_b.position.x, l.point_b.position.y, l.point_b.position.z }, RED);
        }

        EndMode3D();

        // Start the Dear ImGui frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        bool show = true;
        //ImGui::ShowDemoWindow(&show);

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
