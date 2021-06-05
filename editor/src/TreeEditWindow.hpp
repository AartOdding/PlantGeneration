#pragma once

#include <imgui.h>

#include <LSystem/LSystem.hpp>


bool DrawTreeParameters(LSystem::ParameterOwner* owner, const char* window_name)
{
    bool parameters_changed = false;
    ImGui::Begin(window_name);

    for (auto par : owner->Parameters())
    {
        if (dynamic_cast<LSystem::FloatParameter*>(par) != nullptr)
        {
            auto float_par = static_cast<LSystem::FloatParameter*>(par);

            if (ImGui::SliderFloat(float_par->name.c_str(), &float_par->value, float_par->min, float_par->max))
            {
                parameters_changed = true;
            }
        }
        else if (dynamic_cast<LSystem::IntParameter*>(par) != nullptr)
        {
            auto int_par = static_cast<LSystem::IntParameter*>(par);

            if (ImGui::SliderInt(int_par->name.c_str(), &int_par->value, int_par->min, int_par->max))
            {
                parameters_changed = true;
            }
        }
        else if (dynamic_cast<LSystem::ColorParameter*>(par) != nullptr)
        {
            auto color_par = static_cast<LSystem::ColorParameter*>(par);

            if (ImGui::ColorEdit3(color_par->name.c_str(), &color_par->value.x))
            {
                parameters_changed = true;
            }
        }
    }

    ImGui::End();

    return parameters_changed;
}

