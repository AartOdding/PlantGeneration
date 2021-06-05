#pragma once

#include <LSystem/Operation.hpp>



namespace LSystem
{

	struct ExtrudeOperation : Operation
	{
		ExtrudeOperation(OperationOwner* owner, std::string_view name);

		FloatParameter branch_length{ this, "Branch Length", 0, 10, 0.5 };
		FloatParameter roll{ this, "Roll", 0, 360, 0 };
		FloatParameter pitch{ this, "Pitch", 0, 180, 0 };

		std::vector<Instruction*> Apply(const std::vector<Instruction*>& apply_to, LSystem& lsystem) override;
	};

}
