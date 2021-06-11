#pragma once

#include <LSystem/Operation.hpp>



namespace LSystem
{

	struct RadiusOperation : Operation
	{
		RadiusOperation(Plant* plant);

		IntParameter sides{ "Sides", 0, 21, 1 };
		BoolParameter enable_sides{ "Sides", true };
		FloatParameter radius{ "Radius", 0.001, 1, 0.01 };
		BoolParameter enable_radius{ "Override Radius", true };
		FloatParameter radius_change{ "Radius Change", 0.1, 2, 1 };
		BoolParameter enable_radius_change{ "Override Radius Change", true };

		void Execute(int active_input_index, const std::vector<Instruction*>& active_input_values, LSystem& lsystem) override;

		OperationInfo GetInfo() const override
		{
			return { 1, 0, "Radius" };
		}
	};

}
