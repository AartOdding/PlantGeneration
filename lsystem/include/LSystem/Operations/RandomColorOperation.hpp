#pragma once

#include <LSystem/Operation.hpp>



namespace LSystem
{

	struct RandomColorOperation : Operation
	{
		RandomColorOperation();

		ColorParameter color{ "Color", glm::vec3(1, 1, 1)};
		FloatParameter hue_deviation{ "Hue Deviation", 0, 0.2, 0.02 };
		FloatParameter sat_deviation{ "Sat Deviation", 0, 0.5, 0.1 };
		FloatParameter val_deviation{ "Val Deviation", 0, 0.5, 0.1 };
		IntParameter random_seed{ "Random Seed", 0, 10000, 0 };

		void Execute(int active_input_index, const std::vector<Instruction*>& active_input_values, InstructionPool& lsystem, Plant* plant) override;

		void ResetState() override;

		static constexpr std::uint32_t Version = 1;

		template<class Archive>
		void serialize(Archive& archive, const std::uint32_t version)
		{
			if (version > Version)
			{
				throw std::runtime_error("Error: The file you are trying to load has been created with a newer version of this software than you are currently using.");
			}
			archive(cereal::base_class<Operation>(this), color, hue_deviation, sat_deviation, val_deviation, random_seed);
		}
	};

}
