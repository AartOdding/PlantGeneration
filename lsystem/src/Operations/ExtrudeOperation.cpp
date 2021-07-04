#include <LSystem/Operations/ExtrudeOperation.hpp>



namespace LSystem
{

    ExtrudeOperation::ExtrudeOperation()
        : Operation({ 1, 1, "Create Extrusion" })
    {
        AddParameter(branch_length);
        AddParameter(roll);
        AddParameter(pitch);
    }

    void ExtrudeOperation::Execute(int active_input_index, const std::vector<Instruction*>& active_input_values, Plant* plant)
    {
        std::vector<Instruction*> instructions;

        if (active_input_values.size() > 0)
        {
            instructions.reserve(active_input_values.size());

            for (auto onto : active_input_values)
            {
                instructions.push_back(Extrude(*onto, roll, pitch, 0, branch_length));
            }
        }

        ActivateOutput(0, instructions, plant);
    }

}
