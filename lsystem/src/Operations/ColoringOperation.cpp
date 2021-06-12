#include <LSystem/LSystem.hpp>



namespace LSystem
{

	ColoringOperation::ColoringOperation()
		: Operation({ 1, 0, "Apply Color" })
	{
		AddParameter(color);
	}

	void ColoringOperation::Execute(int active_input_index, const std::vector<Instruction*>& active_input_values, LSystem& lsystem, Plant* plant)
	{
		for (auto& i : active_input_values)
		{
			i->data->branch_color = color;
		}
	}

}
