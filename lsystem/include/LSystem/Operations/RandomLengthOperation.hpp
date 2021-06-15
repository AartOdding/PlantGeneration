#pragma once

#include <LSystem/Operation.hpp>



namespace LSystem
{

	struct RandomLengthOperation : Operation
	{
		RandomLengthOperation();

		FloatParameter min{ "Min", -10, 10, 0.5 };
		FloatParameter max{ "Max", -10, 10, 1 };
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
			archive(cereal::base_class<Operation>(this), min, max, random_seed);
		}
	};

}
