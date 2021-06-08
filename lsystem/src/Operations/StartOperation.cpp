#include <LSystem/LSystem.hpp>



namespace LSystem
{

	StartOperation::StartOperation(Plant* plant)
		: Operation(plant)
	{

	}

	void StartOperation::Execute(int active_input_index, const std::vector<Instruction*>& active_input_values, LSystem& lsystem)
	{
		lsystem.first_instruction = lsystem.CreateExtrusion(0, 0, 0);
		ActivateOutput(0, { lsystem.first_instruction }, lsystem);
	}

}
