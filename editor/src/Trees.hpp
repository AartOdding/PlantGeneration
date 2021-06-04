#pragma once

#include "Tree.hpp"



struct Dandelion : Tree
{
    Int fork_count{ this, "fork_count", 2, 20, 5 };
    Int recurse_count{ this, "recurse_count", 1, 10, 5 };
    Float base_length{ this, "base_length", 0, 10, 1 };
    Float length_scaling{ this, "length_scaling", 0, 1, 0.7 };
    Float roll{ this, "roll", 0, 360, 0 };
    Float pitch{ this, "pitch", 0, 180, 60 };

    LSystem::LSystem Generate() override
    {
        LSystem::LSystem l;

        auto instructions = l.CreateExtrusion(base_length, 0, 0);
        l.begin = instructions[0];

        instructions = l.CreateFork(instructions, fork_count, base_length * length_scaling, roll, pitch);

        for (int i = 0; i < recurse_count; ++i)
        {
            auto length = base_length * std::pow(length_scaling, i + 2);
            instructions = l.CreateFork(instructions, fork_count, length, roll, pitch);
        }

        return l;
    }
};

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
};


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

    LSystem::LSystem Generate()
    {
        LSystem::LSystem l;

        auto base = l.CreateExtrusion(base_length, 0, 0);
        l.begin = base[0];

        auto branches = l.CreatePhyllotaxis(base, phylo_count_a, phylo_length_a, spread_a, 0);
        l.CreatePhyllotaxis(base, phylo_count_b, phylo_length_b, spread_b, roll);

        l.CreateFork(branches, flower_count, flower_length, 0, flower_pitch);

        return l;
    }
};
