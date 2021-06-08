#include <LSystem/LSystem.hpp>



namespace LSystem
{

	ColoringOperation::ColoringOperation(Plant* plant)
		: Operation(plant)
	{

	}

	std::vector<Instruction*> ColoringOperation::Apply(const std::vector<Instruction*>& apply_to, LSystem& lsystem)
	{
		for (auto& i : apply_to)
		{
			i->data->branch_color = color;
		}
		return {};
	}

}
