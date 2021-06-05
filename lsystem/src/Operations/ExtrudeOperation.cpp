#include <LSystem/LSystem.hpp>



namespace LSystem
{

    ExtrudeOperation::ExtrudeOperation(OperationOwner* owner, std::string_view name)
        : Operation(owner, name)
    {

    }

    std::vector<Instruction*> ExtrudeOperation::Apply(const std::vector<Instruction*>& apply_to, LSystem& lsystem)
    {
        std::vector<Instruction*> instructions;

        if (apply_to.size() > 0)
        {
            instructions.reserve(apply_to.size());

            for (auto onto : apply_to)
            {
                auto new_instruction = lsystem.CreateExtrusion(branch_length, roll, pitch);
                onto->data->children.push_back(new_instruction);
                instructions.push_back(new_instruction);
            }
        }

        return instructions;
    }

}
