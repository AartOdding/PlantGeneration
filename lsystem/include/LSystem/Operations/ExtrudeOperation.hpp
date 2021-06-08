#pragma once

#include <LSystem/Operation.hpp>



namespace LSystem
{

	struct ExtrudeOperation : Operation
	{
		ExtrudeOperation(Plant* plant);

		FloatParameter branch_length{ this, "Length", 0, 10, 0.5 };
		FloatParameter roll{ this, "Roll", 0, 360, 0 };
		FloatParameter pitch{ this, "Pitch", 0, 180, 0 };

		std::vector<Instruction*> Apply(const std::vector<Instruction*>& apply_to, LSystem& lsystem) override;

		OperationInfo GetInfo() const override
		{
			return { 1, 1, "Create Extrusion" };
		}
	};

}
