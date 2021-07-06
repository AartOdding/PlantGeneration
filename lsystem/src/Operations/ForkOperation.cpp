#include <LSystem/Operations/ForkOperation.hpp>



namespace LSystem
{

    const OperationInfo ForkOperation::info
    {
        1,
        1,
        "Fork",
        "Creates a fork",
        []() { return std::make_unique<ForkOperation>(); }
    };

    ForkOperation::ForkOperation()
        : Operation(info)
    {
        AddParameter(branch_count);
        AddParameter(branch_length);
        AddParameter(spread);
        AddParameter(roll);
    }

    void ForkOperation::Execute(int active_input_index, const std::vector<Instruction*>& active_input_values, Plant* plant)
    {
        std::vector<Instruction*> instructions;

        if (branch_count > 0)
        {
            instructions.reserve(active_input_values.size() * branch_count);

            const float angle_increment = 360.0f / branch_count;

            for (auto onto : active_input_values)
            {
                for (int i = 0; i < branch_count; ++i)
                {
                    instructions.push_back(Extrude(*onto, roll + i * angle_increment, spread / 2, 0, branch_length));
                }
            }
        }
        ActivateOutput(0, instructions, plant);
    }

}
