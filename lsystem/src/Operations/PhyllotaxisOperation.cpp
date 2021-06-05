#include <LSystem/LSystem.hpp>



namespace LSystem
{

    std::vector<Instruction*> CreatePhyllotaxis(LSystem& lsystem, int count, float length, float spread, float roll)
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

    PhyllotaxisOperation::PhyllotaxisOperation(OperationOwner* owner, std::string_view name)
        : Operation(owner, name)
    {

    }

    std::vector<Instruction*> PhyllotaxisOperation::Apply(const std::vector<Instruction*>& apply_to, LSystem& lsystem)
    {
        std::vector<Instruction*> instructions;

        if (branch_count > 0)
        {
            instructions.reserve(apply_to.size() * branch_count);

            for (auto onto : apply_to)
            {
                auto new_instructions = CreatePhyllotaxis(lsystem, branch_count, branch_length, spread, roll);
                onto->data->children.insert(onto->data->children.end(), new_instructions.begin(), new_instructions.end());
                instructions.insert(instructions.end(), new_instructions.begin(), new_instructions.end());
            }
        }

        return instructions;
    }

}
