#include <LSystem/Operations/PhyllotaxisOperation.hpp>



namespace LSystem
{

    PhyllotaxisOperation::PhyllotaxisOperation()
        : Operation({ 1, 1, "Create Phyllotaxis" })
    {
        AddParameter(branch_count);
        AddParameter(branch_length);
        AddParameter(spread);
        AddParameter(roll);
    }

    void PhyllotaxisOperation::Execute(int active_input_index, const std::vector<Instruction*>& active_input_values, Plant* plant)
    {
        std::vector<Instruction*> instructions;

        if (branch_count > 0)
        {
            instructions.reserve(active_input_values.size() * branch_count);

            const auto pitch_ratio = (spread / 2.0f) / glm::sqrt(static_cast<float>(branch_count));
            const auto golden_angle = 137.508f;

            for (auto onto : active_input_values)
            {
                for (int i = 0; i < branch_count; ++i)
                {
                    instructions.push_back(Extrude(*onto, roll + i * golden_angle, pitch_ratio * glm::sqrt(static_cast<float>(i)), 0, branch_length));
                }
            }
        }

        ActivateOutput(0, instructions, plant);
    }

}
