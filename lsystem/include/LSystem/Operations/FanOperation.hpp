#pragma once

#include <LSystem/Operation.hpp>



namespace LSystem
{

	struct FanOperation : Operation
	{
		FanOperation();

		IntParameter branch_count{ "Count", 0, 255, 9 };
		FloatParameter branch_length{ "Length", 0, 10, 0.5 };
		FloatParameter spread{ "Spread", 0, 360, 120 };
		FloatParameter roll{ "Roll", 0, 360, 0 };

		void Execute(int active_input_index, const std::vector<Instruction*>& active_input_values, InstructionPool& lsystem, Plant* plant) override;

		static constexpr std::uint32_t Version = 1;

		template<class Archive>
		void serialize(Archive& archive, const std::uint32_t version)
		{
			if (version > Version)
			{
				throw std::runtime_error("Error: The file you are trying to load has been created with a newer version of this software than you are currently using.");
			}
			archive(cereal::base_class<Operation>(this), branch_count, branch_length, spread, roll);
		}
	};

}
