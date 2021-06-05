#include <LSystem/LSystem.hpp>



namespace LSystem
{

    std::vector<Instruction*> CreateFan(LSystem& lsystem, int count, float length, float spread, float roll)
    {
        std::vector<Instruction*> instructions;

        if (count > 0)
        {
            instructions.reserve(count);

            const float angle_start = -spread / 2;
            const float angle_increment = spread / (count - 1);

            for (int i = 0; i < count; ++i)
            {
                instructions.push_back(lsystem.CreateExtrusion(length, roll, angle_start + i * angle_increment));
            }
        }

        return instructions;
    }

    FanOperation::FanOperation(OperationOwner* owner, std::string_view name)
        : Operation(owner, name)
    {

    }

    std::vector<Instruction*> FanOperation::Apply(const std::vector<Instruction*>& apply_to, LSystem& lsystem)
    {
        std::vector<Instruction*> instructions;

        if (branch_count > 0)
        {
            instructions.reserve(apply_to.size() * branch_count);

            for (auto onto : apply_to)
            {
                auto new_instructions = CreateFan(lsystem, branch_count, branch_length, spread, roll);
                onto->data->children.insert(onto->data->children.end(), new_instructions.begin(), new_instructions.end());
                instructions.insert(instructions.end(), new_instructions.begin(), new_instructions.end());
            }
        }

        return instructions;
    }

}
