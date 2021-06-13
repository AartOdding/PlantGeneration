#include <LSystem/Operations/PhyllotaxisOperation.hpp>



namespace LSystem
{

    std::vector<Instruction*> CreatePhyllotaxis(InstructionPool& lsystem, int count, float length, float spread, float roll)
    {
        std::vector<Instruction*> instructions;

        if (count > 0)
        {
            instructions.reserve(count);

            auto pitch_ratio = (spread / 2.0f) / glm::sqrt(static_cast<float>(count));
            constexpr float golden_angle = 137.508;

            for (int i = 0; i < count; ++i)
            {
                instructions.push_back(lsystem.CreateExtrusion(length, roll + i * golden_angle, pitch_ratio * glm::sqrt(static_cast<float>(i))));
            }
        }

        return instructions;
    }

    PhyllotaxisOperation::PhyllotaxisOperation()
        : Operation({ 1, 1, "Create Phyllotaxis" })
    {
        AddParameter(branch_count);
        AddParameter(branch_length);
        AddParameter(spread);
        AddParameter(roll);
    }

    void PhyllotaxisOperation::Execute(int active_input_index, const std::vector<Instruction*>& active_input_values, InstructionPool& lsystem, Plant* plant)
    {
        std::vector<Instruction*> instructions;

        if (branch_count > 0)
        {
            instructions.reserve(active_input_values.size() * branch_count);

            for (auto onto : active_input_values)
            {
                auto new_instructions = CreatePhyllotaxis(lsystem, branch_count, branch_length, spread, roll);
                onto->data->children.insert(onto->data->children.end(), new_instructions.begin(), new_instructions.end());
                instructions.insert(instructions.end(), new_instructions.begin(), new_instructions.end());
            }
        }

        ActivateOutput(0, instructions, lsystem, plant);
    }

}
