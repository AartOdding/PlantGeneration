#pragma once

#include <LSystem/Operation.hpp>



namespace LSystem
{

	struct RandomLengthOperation : Operation
	{
		RandomLengthOperation(Plant* plant);

		FloatParameter min{ this, "Min", -10, 10, 0.5 };
		FloatParameter max{ this, "Max", -10, 10, 1 };

		std::vector<Instruction*> Apply(const std::vector<Instruction*>& apply_to, LSystem& lsystem) override;

		OperationInfo GetInfo() const override
		{
			return { 1, 1, "Random Length" };
		}
	};

}
