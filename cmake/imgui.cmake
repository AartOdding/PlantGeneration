
add_library(imgui STATIC
    dependencies/imgui/imconfig.h
    dependencies/imgui/imgui.cpp
    dependencies/imgui/imgui.h
    dependencies/imgui/imgui_demo.cpp
    dependencies/imgui/imgui_draw.cpp
    dependencies/imgui/imgui_internal.h
    dependencies/imgui/imgui_tables.cpp
    dependencies/imgui/imgui_widgets.cpp
    dependencies/imgui/imstb_rectpack.h
    dependencies/imgui/imstb_textedit.h
    dependencies/imgui/imstb_truetype.h
    dependencies/imgui/backends/imgui_impl_glfw.cpp
    dependencies/imgui/backends/imgui_impl_glfw.h
    dependencies/imgui/backends/imgui_impl_opengl3.cpp
    dependencies/imgui/backends/imgui_impl_opengl3.h

    dependencies/imguizmo/ImGuizmo.cpp
    dependencies/imguizmo/ImGuizmo.h

    dependencies/imgui-node-editor/crude_json.cpp
    dependencies/imgui-node-editor/crude_json.h
    dependencies/imgui-node-editor/imgui_bezier_math.h
    dependencies/imgui-node-editor/imgui_bezier_math.inl
    dependencies/imgui-node-editor/imgui_canvas.cpp
    dependencies/imgui-node-editor/imgui_canvas.h
    dependencies/imgui-node-editor/imgui_extra_math.h
    dependencies/imgui-node-editor/imgui_extra_math.inl
    dependencies/imgui-node-editor/imgui_node_editor.cpp
    dependencies/imgui-node-editor/imgui_node_editor.h
    dependencies/imgui-node-editor/imgui_node_editor_api.cpp
    dependencies/imgui-node-editor/imgui_node_editor_internal.h
    dependencies/imgui-node-editor/imgui_node_editor_internal.inl
)

target_include_directories(imgui PUBLIC "${CMAKE_SOURCE_DIR}/dependencies/imgui")
target_include_directories(imgui PUBLIC "${CMAKE_SOURCE_DIR}/dependencies/imgui/backends")
target_include_directories(imgui PUBLIC "${CMAKE_SOURCE_DIR}/dependencies/imguizmo")
target_include_directories(imgui PUBLIC "${CMAKE_SOURCE_DIR}/dependencies/imgui-node-editor")

target_compile_definitions(imgui PUBLIC IMGUI_IMPL_OPENGL_LOADER_CUSTOM="external/glad.h")
target_link_libraries(imgui PRIVATE raylib)
