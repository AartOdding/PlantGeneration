#include <LSystem/Operations/ScaleOperation.hpp>



namespace LSystem
{

	ScaleOperation::ScaleOperation()
		: Operation({ 1, 0, "Set Scale" })
	{
		AddParameter(scale);
		AddParameter(enable_scale);
		AddParameter(scale_change);
		AddParameter(enable_scale_change);
	}

	void ScaleOperation::Execute(int active_input_index, const std::vector<Instruction*>& active_input_values, Plant* plant)
	{
		if (enable_scale)
		{
			for (auto& i : active_input_values)
			{
				i->scale = scale;
			}
		}
	}

}
