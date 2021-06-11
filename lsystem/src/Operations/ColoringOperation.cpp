#include <LSystem/LSystem.hpp>



namespace LSystem
{

	ColoringOperation::ColoringOperation(Plant* plant)
		: Operation(plant)
	{
		AddParameter(color);
	}

	void ColoringOperation::Execute(int active_input_index, const std::vector<Instruction*>& active_input_values, LSystem& lsystem)
	{
		for (auto& i : active_input_values)
		{
			i->data->branch_color = color;
		}
	}

}
