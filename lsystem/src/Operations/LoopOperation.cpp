#include <LSystem/LSystem.hpp>



namespace LSystem
{

    LoopOperation::LoopOperation(Plant* plant)
        : Operation(plant)
    {
        AddParameter(loop_count);
    }

    void LoopOperation::Execute(int active_input_index, const std::vector<Instruction*>& active_input_values, LSystem& lsystem)
    {
        if (++m_loop_count > loop_count)
        {
            ActivateOutput(0, active_input_values, lsystem);
        }
        else
        {
            ActivateOutput(1, active_input_values, lsystem);
        }
    }

    void LoopOperation::ResetState()
    {
        m_loop_count = 0;
    }


}
