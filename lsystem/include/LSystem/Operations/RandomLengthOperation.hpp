#pragma once

#include <LSystem/Operation.hpp>



namespace LSystem
{

	struct RandomLengthOperation : Operation
	{
		RandomLengthOperation(Plant* plant);

		FloatParameter min{ this, "Min", -10, 10, 0.5 };
		FloatParameter max{ this, "Max", -10, 10, 1 };

		void Execute(int active_input_index, const std::vector<Instruction*>& active_input_values, LSystem& lsystem) override;

		OperationInfo GetInfo() const override
		{
			return { 1, 1, "Random Length" };
		}
	};

}
