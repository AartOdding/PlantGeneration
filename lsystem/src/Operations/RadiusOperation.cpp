#include <LSystem/Operations/RadiusOperation.hpp>



namespace LSystem
{

	RadiusOperation::RadiusOperation()
		: Operation({ 1, 0, "Set Radius" })
	{
		AddParameter(sides);
		AddParameter(enable_sides);
		AddParameter(radius);
		AddParameter(enable_radius);
		AddParameter(radius_change);
		AddParameter(enable_radius_change);
	}

	void RadiusOperation::Execute(int active_input_index, const std::vector<Instruction*>& active_input_values, InstructionPool& lsystem, Plant* plant)
	{
		if (enable_sides)
		{
			for (auto& i : active_input_values)
			{
				i->data->branch_sides = sides;
			}
		}
		if (enable_radius)
		{
			for (auto& i : active_input_values)
			{
				i->data->branch_radius = radius;
			}
		}
		if (enable_radius_change)
		{
			for (auto& i : active_input_values)
			{
				i->data->branch_radius_change = radius_change;
			}
		}
	}

}
