#include <LSystem/Operations/FanOperation.hpp>



namespace LSystem
{

    FanOperation::FanOperation()
        : Operation({ 1, 1, "Create Fan" })
    {
        AddParameter(branch_count);
        AddParameter(branch_length);
        AddParameter(spread);
        AddParameter(roll);
    }

    void FanOperation::Execute(int active_input_index, const std::vector<Instruction*>& active_input_values, Plant* plant)
    {
        std::vector<Instruction*> instructions;

        if (branch_count > 0)
        {
            const float angle_start = -spread / 2;
            const float angle_increment = spread / (branch_count - 1);

            instructions.reserve(active_input_values.size() * branch_count);

            for (auto onto : active_input_values)
            {
                for (int i = 0; i < branch_count; ++i)
                {
                    instructions.push_back(Extrude(*onto, roll, 0, angle_start + i * angle_increment, branch_length));
                }
            }
        }

        ActivateOutput(0, instructions, plant);
    }

}
