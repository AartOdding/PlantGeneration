#pragma once

#include <LSystem/Operation.hpp>



namespace LSystem
{

	struct RadiusOperation : Operation
	{
		RadiusOperation(Plant* plant);

		IntParameter sides{ this, "Sides", 0, 21, 1 };
		BoolParameter enable_sides{ this, "Sides", true };
		FloatParameter radius{ this, "Radius", 0.001, 1, 0.01 };
		BoolParameter enable_radius{ this, "Override Radius", true };
		FloatParameter radius_change{ this, "Radius Change", 0.1, 2, 1 };
		BoolParameter enable_radius_change{ this, "Override Radius Change", true };

		void Execute(int active_input_index, const std::vector<Instruction*>& active_input_values, LSystem& lsystem) override;

		OperationInfo GetInfo() const override
		{
			return { 1, 0, "Scale" };
		}
	};

}
