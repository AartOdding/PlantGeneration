#include <LSystem/Operations/LoopOperation.hpp>



namespace LSystem
{

    LoopOperation::LoopOperation()
        : Operation({ 1, 2, "Loop" })
    {
        AddParameter(loop_count);
    }

    void LoopOperation::Execute(int active_input_index, const std::vector<Instruction*>& active_input_values, InstructionPool& lsystem, Plant* plant)
    {
        if (++m_loop_count > loop_count)
        {
            ActivateOutput(0, active_input_values, lsystem, plant);
        }
        else
        {
            ActivateOutput(1, active_input_values, lsystem, plant);
        }
    }

    void LoopOperation::ResetState()
    {
        m_loop_count = 0;
    }


}
