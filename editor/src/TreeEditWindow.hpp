#pragma once

#include <imgui.h>

#include <LSystem/LSystem.hpp>

#include "Tree.hpp"


bool DrawParameter(LSystem::Parameter* par)
{
    bool changed = false;
    ImGui::PushID(par);

    if (dynamic_cast<LSystem::FloatParameter*>(par) != nullptr)
    {
        auto float_par = static_cast<LSystem::FloatParameter*>(par);
        ImGui::SetNextItemWidth(300);
        changed = ImGui::SliderFloat(float_par->name.c_str(), &float_par->value, float_par->min, float_par->max);
    }
    else if (dynamic_cast<LSystem::IntParameter*>(par) != nullptr)
    {
        auto int_par = static_cast<LSystem::IntParameter*>(par);
        ImGui::SetNextItemWidth(300);
        changed = ImGui::SliderInt(int_par->name.c_str(), &int_par->value, int_par->min, int_par->max);
    }
    else if (dynamic_cast<LSystem::ColorParameter*>(par) != nullptr)
    {
        auto color_par = static_cast<LSystem::ColorParameter*>(par);
        ImGui::SetNextItemWidth(300);
        changed = ImGui::ColorPicker3(color_par->name.c_str(), &color_par->value.x,
            ImGuiColorEditFlags_NoSidePreview | ImGuiColorEditFlags_NoTooltip | ImGuiColorEditFlags_NoLabel);
    }

    ImGui::PopID();
    return changed;
}
