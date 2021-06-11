#include <LSystem/LSystem.hpp>



namespace LSystem
{

	ScaleOperation::ScaleOperation(Plant* plant)
		: Operation(plant)
	{
		AddParameter(scale);
		AddParameter(enable_scale);
		AddParameter(scale_change);
		AddParameter(enable_scale_change);
	}

	void ScaleOperation::Execute(int active_input_index, const std::vector<Instruction*>& active_input_values, LSystem& lsystem)
	{
		if (enable_scale)
		{
			for (auto& i : active_input_values)
			{
				i->data->scale = scale;
			}
		}
		if (enable_scale_change)
		{
			for (auto& i : active_input_values)
			{
				i->data->scale_change = scale_change;
			}
		}
	}

}
