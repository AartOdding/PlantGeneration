#include <LSystem/LSystem.hpp>



namespace LSystem
{

	StartOperation::StartOperation(Plant* plant)
		: Operation(plant)
	{

	}

	std::vector<Instruction*> StartOperation::Apply(const std::vector<Instruction*>& apply_to, LSystem& lsystem)
	{
		return { lsystem.CreateExtrusion(0, 0, 0) };
	}

}
