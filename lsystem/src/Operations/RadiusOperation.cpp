#include <LSystem/LSystem.hpp>



namespace LSystem
{

	RadiusOperation::RadiusOperation(Plant* plant)
		: Operation(plant)
	{

	}

	void RadiusOperation::Execute(int active_input_index, const std::vector<Instruction*>& active_input_values, LSystem& lsystem)
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
