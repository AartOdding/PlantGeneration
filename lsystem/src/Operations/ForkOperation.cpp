#include <LSystem/Operations/ForkOperation.hpp>



namespace LSystem
{

    std::vector<Instruction*> CreateFork(InstructionPool& lsystem, int count, float length, float spread, float roll)
    {
        std::vector<Instruction*> instructions;

        if (count > 0)
        {
            instructions.reserve(count);

            const float angle_increment = 360.0f / count;

            for (int i = 0; i < count; ++i)
            {
                instructions.push_back(lsystem.CreateExtrusion(length, roll + i * angle_increment, spread / 2));
            }
        }

        return instructions;
    }


    ForkOperation::ForkOperation()
        : Operation({ 1, 1, "Create Fork" })
    {
        AddParameter(branch_count);
        AddParameter(branch_length);
        AddParameter(spread);
        AddParameter(roll);
    }

    void ForkOperation::Execute(int active_input_index, const std::vector<Instruction*>& active_input_values, InstructionPool& lsystem, Plant* plant)
    {
        std::vector<Instruction*> instructions;

        if (branch_count > 0)
        {
            instructions.reserve(active_input_values.size() * branch_count);

            for (auto onto : active_input_values)
            {
                auto new_instructions = CreateFork(lsystem, branch_count, branch_length, spread, roll);
                onto->data->children.insert(onto->data->children.end(), new_instructions.begin(), new_instructions.end());
                instructions.insert(instructions.end(), new_instructions.begin(), new_instructions.end());
            }
        }

        ActivateOutput(0, instructions, lsystem, plant);
    }

}
