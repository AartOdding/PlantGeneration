#pragma once

#include <LSystem/Operation.hpp>



namespace LSystem
{

	struct RandomColorOperation : Operation
	{
		RandomColorOperation(Plant* plant);

		ColorParameter color{ "Color", glm::vec3(1, 1, 1)};
		FloatParameter hue_deviation{ "Hue Deviation", 0, 0.2, 0.02 };
		FloatParameter sat_deviation{ "Sat Deviation", 0, 0.5, 0.1 };
		FloatParameter val_deviation{ "Val Deviation", 0, 0.5, 0.1 };
		IntParameter random_seed{ "Random Seed", 0, 10000, 0 };

		void Execute(int active_input_index, const std::vector<Instruction*>& active_input_values, LSystem& lsystem) override;

		void ResetState() override;

		OperationInfo GetInfo() const override
		{
			return { 1, 0, "Random Color" };
		}
	};

}
