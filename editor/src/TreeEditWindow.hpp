#pragma once

#include <imgui.h>

#include <LSystem/LSystem.hpp>

#include "Tree.hpp"


bool DrawParameter(LSystem::Parameter* par)
{
    if (dynamic_cast<LSystem::FloatParameter*>(par) != nullptr)
    {
        auto float_par = static_cast<LSystem::FloatParameter*>(par);
        return ImGui::SliderFloat(float_par->name.c_str(), &float_par->value, float_par->min, float_par->max);
    }
    else if (dynamic_cast<LSystem::IntParameter*>(par) != nullptr)
    {
        auto int_par = static_cast<LSystem::IntParameter*>(par);
        return ImGui::SliderInt(int_par->name.c_str(), &int_par->value, int_par->min, int_par->max);
    }
    else if (dynamic_cast<LSystem::ColorParameter*>(par) != nullptr)
    {
        auto color_par = static_cast<LSystem::ColorParameter*>(par);
        return ImGui::ColorEdit3(color_par->name.c_str(), &color_par->value.x);
    }
    return false;
}

bool DrawParameterOwner(LSystem::ParameterOwner* owner, const char* name)
{
    bool parameters_changed = false;

    if (ImGui::CollapsingHeader(name))
    {
        ImGui::PushID(owner);

        for (auto par : owner->Parameters())
        {
            parameters_changed |= DrawParameter(par);
        }

        ImGui::PopID();
    }

    return parameters_changed;
}

bool DrawTreeParameters(Tree* tree, const char* window_name)
{
    ImGui::Begin(window_name);

    bool parameters_changed = DrawParameterOwner(tree, "Tree");

    for (auto* operation : tree->Operations())
    {
        parameters_changed |= DrawParameterOwner(operation, operation->name.c_str());
    }

    ImGui::End();

    return parameters_changed;
}

