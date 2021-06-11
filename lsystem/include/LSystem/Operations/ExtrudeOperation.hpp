#pragma once

#include <LSystem/Operation.hpp>



namespace LSystem
{

	struct ExtrudeOperation : Operation
	{
		ExtrudeOperation(Plant* plant);

		FloatParameter branch_length{ "Length", 0, 10, 0.5 };
		FloatParameter roll{ "Roll", 0, 360, 0 };
		FloatParameter pitch{ "Pitch", 0, 180, 0 };

		void Execute(int active_input_index, const std::vector<Instruction*>& active_input_values, LSystem& lsystem) override;

		OperationInfo GetInfo() const override
		{
			return { 1, 1, "Create Extrusion" };
		}
	};

}
