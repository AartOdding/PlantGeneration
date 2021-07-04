#include <LSystem/Operations/StartOperation.hpp>



namespace LSystem
{

	StartOperation::StartOperation()
		: Operation({ 0, 1, "Start" })
	{

	}

	void StartOperation::Execute(int active_input_index, const std::vector<Instruction*>& active_input_values, Plant* plant)
	{
		start_instruction = std::make_unique<Instruction>();
		ActivateOutput(0, { start_instruction.get() }, plant);
	}

}
