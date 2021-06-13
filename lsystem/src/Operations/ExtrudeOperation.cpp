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

    void ExtrudeOperation::Execute(int active_input_index, const std::vector<Instruction*>& active_input_values, InstructionPool& lsystem, Plant* plant)
    {
        std::vector<Instruction*> instructions;

        if (active_input_values.size() > 0)
        {
            instructions.reserve(active_input_values.size());

            for (auto onto : active_input_values)
            {
                auto new_instruction = lsystem.CreateExtrusion(branch_length, roll, pitch);
                onto->data->children.push_back(new_instruction);
                instructions.push_back(new_instruction);
            }
        }

        ActivateOutput(0, instructions, lsystem, plant);
    }

}
