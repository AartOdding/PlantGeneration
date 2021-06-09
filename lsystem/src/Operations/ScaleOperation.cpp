#include <LSystem/LSystem.hpp>



namespace LSystem
{

	ScaleOperation::ScaleOperation(Plant* plant)
		: Operation(plant)
	{

	}

	void ScaleOperation::Execute(int active_input_index, const std::vector<Instruction*>& active_input_values, LSystem& lsystem)
	{
		for (auto& i : active_input_values)
		{
			//i->data->scale = scale;
			i->data->scale_change = scale_change;
		}
	}

}
