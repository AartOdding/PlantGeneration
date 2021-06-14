#include <external/glad.h>
#include <raylib.h>
#include <raymath.h>
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include <imgui_node_editor.h>
#include <GLFW/glfw3.h>

#include <cmrc/cmrc.hpp>

#include <algorithm>
#include <cmath>
#include <fstream>
#include <iostream>

#include <LSystem/LSystem.hpp>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/random.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "OperationDatabase.hpp"
#include "TreeEditWindow.hpp"


CMRC_DECLARE(resources);

namespace ed = ax::NodeEditor;

static std::string random_name(const int len) {

    std::string tmp_s;

    static const char alphanum[] =
        "0123456789"
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz";

    tmp_s.reserve(len);

    for (int i = 0; i < len; ++i)
        tmp_s += alphanum[rand() % (sizeof(alphanum) - 1)];

    return tmp_s;
}


struct EditorConfig
{
    float camera_min_y = -0.3;
    float camera_max_y = 0.3;
    float camera_speed_sideways = 0.007;
    float camera_speed_updown = 0.3;

    bool orbit_mode = false;
    bool editing_mode = true;
    
    glm::vec3 background_color = glm::vec3(0, 0, 0);

    int last_width = 1080;
    int last_height = 1350;
};

bool DrawEditorConfigWindow(EditorConfig& editor_config, LSystem::Plant* plant)
{
    bool anything_changed = false;
    ImGui::Begin("Editor Config");

    ImGui::SliderFloat("Camera min Y", &editor_config.camera_min_y, -1.5, 1.5);
    ImGui::SliderFloat("Camera max Y", &editor_config.camera_max_y, -1.5, 1.5);
    ImGui::SliderFloat("Camera rotation speed", &editor_config.camera_speed_sideways, 0, 0.05);
    ImGui::SliderFloat("Camera up/down speed", &editor_config.camera_speed_updown, 0, 2);
    ImGui::Checkbox("Orbiting", &editor_config.orbit_mode);
    ImGui::ColorEdit3("Background color", &editor_config.background_color.x);

    if (ImGui::Button("Save"))
    {
        std::ofstream stream("Plant1.plant", std::ios::binary | std::ios::trunc);
        plant->SaveTo(stream);
    }
    if (ImGui::Button("Load"))
    {
        std::ifstream stream("Plant1.plant", std::ios::binary);
        plant->LoadFrom(stream);
        anything_changed = true;
    }

    ImGui::End();
    return anything_changed;
}

void DrawCreateOperationWindow(LSystem::Plant* plant)
{
    ImGui::Begin("Create Operation");

    if (ImGui::Button("Extrude"))
    {
        plant->AddOperation(std::make_unique<LSystem::ExtrudeOperation>());
    }
    if (ImGui::Button("Fork"))
    {
        plant->AddOperation(std::make_unique<LSystem::ForkOperation>());
    }
    if (ImGui::Button("Fan"))
    {
        plant->AddOperation(std::make_unique<LSystem::FanOperation>());
    }
    if (ImGui::Button("Phyllotaxis"))
    {
        plant->AddOperation(std::make_unique<LSystem::PhyllotaxisOperation>());
    }
    if (ImGui::Button("Color"))
    {
        plant->AddOperation(std::make_unique<LSystem::ColoringOperation>());
    }
    if (ImGui::Button("Random Length"))
    {
        plant->AddOperation(std::make_unique<LSystem::RandomLengthOperation>());
    }
    if (ImGui::Button("Random Color"))
    {
        plant->AddOperation(std::make_unique<LSystem::RandomColorOperation>());
    }
    if (ImGui::Button("Loop"))
    {
        plant->AddOperation(std::make_unique<LSystem::LoopOperation>());
    }
    if (ImGui::Button("Scale"))
    {
        plant->AddOperation(std::make_unique<LSystem::ScaleOperation>());
    }
    if (ImGui::Button("Radius"))
    {
        plant->AddOperation(std::make_unique<LSystem::RadiusOperation>());
    }

    ImGui::End();
}

bool DrawNodeEditorWindow(LSystem::Plant* plant, OperationDatabase* id_db, ed::EditorContext* context)
{
    bool anything_changed = false;

    ImGui::Begin("Node Editor");
    ed::SetCurrentEditor(context);
    ed::Begin("Node Editor", ImVec2(0.0, 0.0f));

    // Draw nodes:
    for (auto op : plant->Operations())
    {
        constexpr static float parameter_width = 250;
        float max_text_width = 0;

        for (auto par : op->Parameters())
        {
            max_text_width = std::max(max_text_width, ImGui::CalcTextSize(par->Name().c_str()).x);
        }

        float total_width = max_text_width + parameter_width;

        const auto info = op->GetInfo();

        const int row_count = std::max(info.input_count, info.output_count);

        ed::BeginNode(id_db->GetOperationID(op->GetID()));
        ImGui::Text(info.description.c_str());

        for (int i = 0; i < row_count; ++i)
        {
            if (i < info.input_count)
            {
                ed::BeginPin(id_db->GetInputID(op->GetID(), i), ed::PinKind::Input);
                ImGui::Text("->");
                ed::EndPin();
            }
            else
            {
                ImGui::Text(" ");
            }
            if (i < info.output_count)
            {
                ImGui::SameLine(total_width - ImGui::CalcTextSize("->").x);

                ed::BeginPin(id_db->GetOutputID(op->GetID(), i), ed::PinKind::Output);
                ImGui::Text("->");
                ed::EndPin();
            }
        }

        for (auto par : op->Parameters())
        {
            anything_changed |= DrawParameter(par, parameter_width);
        }

        ed::EndNode();
    }

    // Draw links

    for (auto con : plant->Connections())
    {
        ed::Link(
            id_db->GetConnectionID(con), 
            id_db->GetOutputID(con.output, con.output_index), 
            id_db->GetInputID(con.input, con.input_index));
    }

    // create links

    if (ed::BeginCreate())
    {
        ed::PinId dragged_from, dragged_to;

        if (ed::QueryNewLink(&dragged_from, &dragged_to))
        {
            // QueryNewLink returns true if editor want to create new link between pins.
            
            // If either on is valid but not both, link drag was started, but released above the background.
            if (dragged_from && dragged_to) // If both are valid link was dragged from and to a pin
            {
                // ed::AcceptNewItem() return true when user release mouse button.
                if (ed::AcceptNewItem())
                {
                    // imgui-node-editor gived the output as the place where the drag is started, for us the start and end
                    // doesnt matter only the in and output
                    if (id_db->IsInputID(dragged_from.Get()) && id_db->IsOutputID(dragged_to.Get()))
                    {
                        auto [output_op, output_index] = id_db->GetOutput(dragged_to.Get());
                        auto [input_op, input_index] = id_db->GetInput(dragged_from.Get());
                        anything_changed |= plant->AddConnection({ output_op, output_index, input_op, input_index });
                    }
                    else if (id_db->IsInputID(dragged_to.Get()) && id_db->IsOutputID(dragged_from.Get()))
                    {
                        auto [output_op, output_index] = id_db->GetOutput(dragged_from.Get());
                        auto [input_op, input_index] = id_db->GetInput(dragged_to.Get());
                        anything_changed |= plant->AddConnection({ output_op, output_index, input_op, input_index });
                    }
                }
            }
        }
    }
    ed::EndCreate();

    // delete links and nodes

    if (ed::BeginDelete())
    {
        ed::NodeId node_id;
        while (ed::QueryDeletedNode(&node_id))
        {
            if (ed::AcceptDeletedItem())
            {
                auto op = id_db->GetOperation(node_id.Get());
                anything_changed |= plant->DeleteOperation(op);
            }
        }

        // There may be many links marked for deletion, let's loop over them.
        ed::LinkId connection_id;
        while (ed::QueryDeletedLink(&connection_id))
        {
            // If you agree that link can be deleted, accept deletion.
            if (ed::AcceptDeletedItem())
            {
                auto c = id_db->GetConnection(connection_id.Get());
                anything_changed |= plant->DeleteConnection(c);
            }
        }
    }
    ed::EndDelete(); // Wrap up deletion action

    ed::End();
    ed::SetCurrentEditor(nullptr);
    ImGui::End();

    return anything_changed;
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
        float updown = std::sin(editor_config.camera_speed_updown * GetTime());
        camera_state.camera_rotation_updown = LSystem::MapRange<float>(updown, -1, 1, editor_config.camera_min_y, editor_config.camera_max_y);
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

std::array<uint8_t, 4> ToByteColor(const glm::vec3& rgb)
{
    uint8_t r = std::clamp<int>(static_cast<int>(rgb.r * 255.0f), 0, 255);
    uint8_t g = std::clamp<int>(static_cast<int>(rgb.g * 255.0f), 0, 255);
    uint8_t b = std::clamp<int>(static_cast<int>(rgb.b * 255.0f), 0, 255);
    return { r, g, b, 255 };
}

std::array<uint8_t, 4> ToByteColor(const glm::vec4& rgba)
{
    uint8_t r = std::clamp<int>(static_cast<int>(rgba.r * 255.0f), 0, 255);
    uint8_t g = std::clamp<int>(static_cast<int>(rgba.g * 255.0f), 0, 255);
    uint8_t b = std::clamp<int>(static_cast<int>(rgba.b * 255.0f), 0, 255);
    uint8_t a = std::clamp<int>(static_cast<int>(rgba.a * 255.0f), 0, 255);
    return { r, g, b, a };
}

int main()
{
    EditorConfig editor_config;
    CameraState camera_state;

    LSystem::Plant plant;
    OperationDatabase operation_database;
    auto plant_vertices = plant.Generate();

    Mesh mesh{};
    bool mesh_loaded = false;

    SetConfigFlags(FLAG_MSAA_4X_HINT);
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    SetConfigFlags(FLAG_VSYNC_HINT);
    
    InitWindow(1080, 1350, "Aart & Aart 4Mb Jam");

    SetTargetFPS(30);
    glDisable(GL_CULL_FACE);

    // Setup Dear ImGui context
    ImGui::CreateContext();
    ImGui::StyleColorsDark();
    ImGui::GetIO().FontGlobalScale = 2;

    ImGui_ImplGlfw_InitForOpenGL((GLFWwindow*)GetGLFWWindowHandle(), true);
    ImGui_ImplOpenGL3_Init("#version 330");


    ed::Config config;
    config.SettingsFile = "node_editor.json";
    auto node_editor_context = ed::CreateEditor(&config);

    Camera camera{};
    camera.position = { 0.0f, 1.8f, 6.0f };    // Camera position
    camera.target = { 0.0f, 1.7f, 0.0f };      // Camera looking at point
    camera.up = { 0.0f, 1.0f, 0.0f };          // Camera up vector (rotation towards target)
    camera.fovy = 45.0f;                       // Camera field-of-view Y
    camera.projection = CAMERA_PERSPECTIVE;    // Camera mode type

    while (!WindowShouldClose())
    {
        operation_database.Update(&plant);

        UpdateCameraState(camera, camera_state, editor_config);

        if (IsKeyPressed(KEY_E))
        {
            editor_config.editing_mode = !editor_config.editing_mode;
            editor_config.orbit_mode = !editor_config.editing_mode;

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

        for (auto& l : plant_vertices.lines)
        {
            DrawLine3D(ToVec3(l.point_a.position), ToVec3(l.point_b.position), ToColor(l.point_b.color));
        }

        if (mesh_loaded)
        {
            DrawMesh(mesh, LoadMaterialDefault(), MatrixIdentity());
        }

        EndMode3D();

        // Start the Dear ImGui frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        DrawCreateOperationWindow(&plant);
        operation_database.Update(&plant);

        // Do in two steps instead of using || to avoid shortcircuiting.
        bool changed = DrawNodeEditorWindow(&plant, &operation_database, node_editor_context);
        changed |= DrawEditorConfigWindow(editor_config, &plant);

        if (changed)
        {
            if (mesh_loaded)
            {
                UnloadMesh(mesh);
                mesh = Mesh{};
                mesh_loaded = false;
            }

            plant_vertices = plant.Generate();

            if (!plant_vertices.triangles.empty())
            {
                mesh.vertexCount = plant_vertices.triangles.size() * 3;

                auto position_data = new glm::vec3[plant_vertices.triangles.size() * 3]; // Cleaned by raylib
                auto color_data = new std::array<uint8_t, 4>[plant_vertices.triangles.size() * 3]; // Cleaned by raylib

                for (int i = 0; i < plant_vertices.triangles.size(); ++i)
                {
                    position_data[3 * i + 0] = plant_vertices.triangles[i].point_1.position;
                    position_data[3 * i + 1] = plant_vertices.triangles[i].point_2.position;
                    position_data[3 * i + 2] = plant_vertices.triangles[i].point_3.position;
                    color_data[3 * i + 0] = ToByteColor(plant_vertices.triangles[i].point_1.color);
                    color_data[3 * i + 1] = ToByteColor(plant_vertices.triangles[i].point_2.color);
                    color_data[3 * i + 2] = ToByteColor(plant_vertices.triangles[i].point_3.color);
                }

                mesh.vertices = &position_data[0].x;
                mesh.colors = color_data[0].data();

                UploadMesh(&mesh, false);
                mesh_loaded = true;
            }
        }

        ImGui::Render();

        if (editor_config.editing_mode)
        {
            ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        }

        EndDrawing();
    }

    ed::DestroyEditor(node_editor_context);

    CloseWindow();

    return 0;
}
