#pragma once

#include <imgui.h>

#include "Tree.hpp"


bool DrawTreeParameters(Tree* tree, const char* window_name)
{
    bool parameters_changed = false;
    ImGui::Begin(window_name);

    for (auto par : tree->Parameters())
    {
        if (dynamic_cast<Tree::Float*>(par) != nullptr)
        {
            auto float_par = static_cast<Tree::Float*>(par);

            if (ImGui::SliderFloat(float_par->name.c_str(), &float_par->value, float_par->min, float_par->max))
            {
                parameters_changed = true;
            }
        }
        else if (dynamic_cast<Tree::Int*>(par) != nullptr)
        {
            auto int_par = static_cast<Tree::Int*>(par);

            if (ImGui::SliderInt(int_par->name.c_str(), &int_par->value, int_par->min, int_par->max))
            {
                parameters_changed = true;
            }
        }
        else if (dynamic_cast<Tree::Color*>(par) != nullptr)
        {
            auto color_par = static_cast<Tree::Color*>(par);

            if (ImGui::ColorEdit3(color_par->name.c_str(), &color_par->value.x))
            {
                parameters_changed = true;
            }
        }
    }

    ImGui::End();

    return parameters_changed;
}

