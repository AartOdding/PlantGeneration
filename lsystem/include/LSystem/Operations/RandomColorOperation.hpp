#pragma once

#include <LSystem/Operation.hpp>



namespace LSystem
{

	struct RandomColorOperation : Operation
	{
		RandomColorOperation(Plant* plant);

		ColorParameter color{ this, "Color", glm::vec3(1, 1, 1)};
		IntParameter random_seed{ this, "Random Seed", 0, 10000, 0 };
		FloatParameter hue_deviation{ this, "Hue Deviation", 0, 0.2, 0.02 };
		FloatParameter sat_deviation{ this, "Sat Deviation", 0, 0.5, 0.1 };
		FloatParameter val_deviation{ this, "Val Deviation", 0, 0.5, 0.1 };

		std::vector<Instruction*> Apply(const std::vector<Instruction*>& apply_to, LSystem& lsystem) override;

		OperationInfo GetInfo() const override
		{
			return { 1, 1, "Random Color" };
		}
	};

}
