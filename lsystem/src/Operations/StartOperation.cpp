#include <LSystem/Operations/StartOperation.hpp>



namespace LSystem
{

	StartOperation::StartOperation()
		: Operation({ 0, 1, "Start" })
	{

	}

	void StartOperation::Execute(int active_input_index, const std::vector<Instruction*>& active_input_values, InstructionPool& lsystem, Plant* plant)
	{
		lsystem.first_instruction = lsystem.CreateExtrusion(0, 0, 0);
		ActivateOutput(0, { lsystem.first_instruction }, lsystem, plant);
	}

}
