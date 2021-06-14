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

		template<class Archive>
		void serialize(Archive& archive)
		{
			archive(cereal::base_class<Operation>(this), min, max, random_seed);
		}
	};

}
