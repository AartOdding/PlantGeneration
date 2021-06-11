#pragma once

#include <LSystem/Operation.hpp>



namespace LSystem
{

	struct RandomLengthOperation : Operation
	{
		RandomLengthOperation(Plant* plant);

		FloatParameter min{ "Min", -10, 10, 0.5 };
		FloatParameter max{ "Max", -10, 10, 1 };
		IntParameter random_seed{ "Random Seed", 0, 10000, 0 };

		void Execute(int active_input_index, const std::vector<Instruction*>& active_input_values, LSystem& lsystem) override;

		void ResetState() override;

		OperationInfo GetInfo() const override
		{
			return { 1, 0, "Random Length" };
		}
	};

}
