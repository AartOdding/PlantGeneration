#pragma once

#include <imgui.h>

#include <LSystem/LSystem.hpp>


bool DrawParameter(LSystem::Parameter* par, float width)
{
    bool changed = false;
    ImGui::PushID(par);

    if (dynamic_cast<LSystem::FloatParameter*>(par) != nullptr)
    {
        auto float_par = static_cast<LSystem::FloatParameter*>(par);
        ImGui::SetNextItemWidth(width);
        changed = ImGui::SliderFloat(float_par->Name().c_str(), &float_par->value, float_par->min, float_par->max);
    }
    else if (dynamic_cast<LSystem::IntParameter*>(par) != nullptr)
    {
        auto int_par = static_cast<LSystem::IntParameter*>(par);
        ImGui::SetNextItemWidth(width);
        changed = ImGui::SliderInt(int_par->Name().c_str(), &int_par->value, int_par->min, int_par->max);
    }
    else if (dynamic_cast<LSystem::ColorParameter*>(par) != nullptr)
    {
        auto color_par = static_cast<LSystem::ColorParameter*>(par);
        ImGui::SetNextItemWidth(width);
        changed = ImGui::ColorPicker3(color_par->Name().c_str(), &color_par->value.x,
            ImGuiColorEditFlags_NoSidePreview | ImGuiColorEditFlags_NoTooltip);
    }
    else if (dynamic_cast<LSystem::BoolParameter*>(par) != nullptr)
    {
        auto bool_par = static_cast<LSystem::BoolParameter*>(par);
        ImGui::SetNextItemWidth(width);
        changed = ImGui::Checkbox(bool_par->Name().c_str(), &bool_par->value);
    }

    ImGui::PopID();
    return changed;
}
