#pragma once

#include "Tree.hpp"



struct Dandelion : Tree
{
    LSystem::ForkOperation fork{ this, "fork" };

    Int recurse_count{ this, "recurse_count", 1, 10, 5 };
    Float length_scaling{ this, "length_scaling", 0, 1, 0.7 };

    LSystem::LSystem Generate() override
    {
        LSystem::LSystem l;

        float starting_length = fork.branch_length;

        auto instructions = l.CreateBase(fork.branch_length);

        for (int i = 0; i < recurse_count; ++i)
        {
            fork.branch_length = fork.branch_length * length_scaling;
            instructions = fork.Apply(instructions, l);
        }

        fork.branch_length = starting_length;

        return l;
    }
};

struct Plant1 : Tree
{
    LSystem::PhyllotaxisOperation phylo1{ this, "phylo1" };
    LSystem::PhyllotaxisOperation phylo2{ this, "phylo2" };
    LSystem::PhyllotaxisOperation phylo3{ this, "phylo3" };
    LSystem::PhyllotaxisOperation phylo4{ this, "phylo4" };
    LSystem::ColoringOperation color1{ this, "color1" };
    LSystem::ColoringOperation color2{ this, "color2" };
    LSystem::ColoringOperation color3{ this, "color3" };
    LSystem::ColoringOperation color4{ this, "color4" };

    Float base_length{ this, "base_length", 0, 5, 1 };

    LSystem::LSystem Generate() override
    {
        LSystem::LSystem l;

        auto base = l.CreateBase(base_length);
        color1.Apply(base, l);

        auto branches = phylo1.Apply(base, l);
        color1.Apply(branches, l);

        auto branches_empty = phylo2.Apply(base, l);
        color2.Apply(branches_empty, l);

        auto flowers = phylo3.Apply(branches, l);
        color3.Apply(flowers, l);

        auto flowers_empty = phylo4.Apply(branches, l);
        color4.Apply(flowers_empty, l);

        return l;
    }
};

struct Flower1 : Tree
{
    Float base_length{ this, "base_length", 0, 5, 1 };

    LSystem::ForkOperation base_fork{ this, "base_fork" };
    LSystem::FanOperation base_split{ this, "base_fan" };
    LSystem::ExtrudeOperation base_continue{ this, "base_continue" };

    LSystem::ForkOperation flower_fork{ this, "flower_fork" };
    LSystem::FanOperation flower_split{ this, "flower_split" };

    LSystem::ColoringOperation base_color{ this, "base_color" };
    LSystem::ColoringOperation flower_color{ this, "flower_color" };

    LSystem::LSystem Generate() override
    {
        LSystem::LSystem l;

        auto base = l.CreateBase(base_length);
        base_color.Apply(base, l);
        auto f = base_fork.Apply(base, l);
        base_color.Apply(f, l);
        f = base_split.Apply(f, l);
        base_color.Apply(f, l);

        base = base_continue.Apply(base, l);
        base_color.Apply(base, l);

        auto flowers = flower_fork.Apply(base, l);
        flower_color.Apply(flowers, l);
        flowers = flower_split.Apply(flowers, l);
        flower_color.Apply(flowers, l);

        return l;
    }
};

/*
struct FanningTree : Tree
{
    Int recurse_count{ this, "recurse_count", 1, 10, 5 };
    Int fork_count{ this, "fork_count", 2, 20, 5 };
    Int fan_count{ this, "fan_count", 2, 20, 5 };
    Float base_length{ this, "base_length", 0, 10, 1 };
    Float fork_length{ this, "fork_length", 0, 10, 1 };
    Float fan_length{ this, "fork_length", 0, 10, 1 };
    Float roll{ this, "roll", 0, 360, 0 };
    Float pitch{ this, "pitch", 0, 180, 60 };
    Float spread{ this, "spread", 0, 360, 60 };
    Float base_roll{ this, "base_roll", 0, 360, 25 };

    LSystem::LSystem Generate()
    {
        LSystem::LSystem l;

        auto base = l.CreateExtrusion(base_length, 0, 0);
        l.begin = base[0];

        for (int i = 0; i < recurse_count; ++i)
        {
            auto branches = l.CreateFork(base, fork_count, fork_length, 0, pitch);
            l.CreateFan(branches, fan_count, fan_length, spread, roll);
            base = l.CreateExtrusion(base, base_length, base_roll, 0);
        }

        return l;
    }
};*/

/*
struct Dandelion2 : Tree
{
    Float base_length{ this, "base_length", 0, 10, 1 };
    Int phylo_count_a{ this, "phylo_count_a", 1, 300, 100 };
    Int phylo_count_b{ this, "phylo_count_b", 1, 300, 100 };
    Float phylo_length_a{ this, "phylo_length_a", 0, 10, 1 };
    Float phylo_length_b{ this, "phylo_length_b", 0, 10, 1 };
    Float roll{ this, "roll", 0, 7, 0 };
    Float spread_a{ this, "spread_a", 0, 360, 120 };
    Float spread_b{ this, "spread_b", 0, 360, 120 };

    Int flower_count{ this, "flower_count", 1, 10, 5 };
    Float flower_length{ this, "flower_length", 0, 2, 0.1 };
    Float flower_pitch{ this, "flower_pitch", 0, 360, 100 };
    Color flower_color{ this, "flower_color", glm::vec3(0, 0, 1) };

    LSystem::LSystem Generate()
    {
        LSystem::LSystem l;

        auto base = l.CreateExtrusion(base_length, 0, 0);
        l.begin = base[0];

        auto branches = l.CreatePhyllotaxis(base, phylo_count_a, phylo_length_a, spread_a, 0);
        l.CreatePhyllotaxis(base, phylo_count_b, phylo_length_b, spread_b, roll);

        LSystem::ForkOperation fork{ this, "Flower" };
        auto flowers = fork.Apply(branches, l);
        // = l.CreateFork(branches, flower_count, flower_length, 0, flower_pitch);
        l.SetColor(flowers, flower_color);

        return l;
    }
};
*/
