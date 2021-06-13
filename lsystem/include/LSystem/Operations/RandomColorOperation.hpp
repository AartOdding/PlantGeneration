#pragma once

#include <LSystem/Operation.hpp>



namespace LSystem
{

	struct RandomColorOperation : Operation, NoCopy, NoMove
	{
		RandomColorOperation();

		ColorParameter color{ "Color", glm::vec3(1, 1, 1)};
		FloatParameter hue_deviation{ "Hue Deviation", 0, 0.2, 0.02 };
		FloatParameter sat_deviation{ "Sat Deviation", 0, 0.5, 0.1 };
		FloatParameter val_deviation{ "Val Deviation", 0, 0.5, 0.1 };
		IntParameter random_seed{ "Random Seed", 0, 10000, 0 };

		void Execute(int active_input_index, const std::vector<Instruction*>& active_input_values, InstructionPool& lsystem, Plant* plant) override;

		void ResetState() override;

		template<class Archive>
		void serialize(Archive& archive)
		{
			archive(cereal::base_class<Operation>(this), color, hue_deviation, sat_deviation, val_deviation, random_seed);
		}
	};

}
