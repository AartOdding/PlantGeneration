#pragma once

#include <LSystem/Operation.hpp>



namespace LSystem
{

	struct RadiusOperation : Operation
	{
		RadiusOperation();

		IntParameter sides{ "Sides", 0, 21, 1 };
		BoolParameter enable_sides{ "Sides", true };
		FloatParameter radius{ "Radius", 0.001, 1, 0.01 };
		BoolParameter enable_radius{ "Override Radius", true };
		FloatParameter radius_change{ "Radius Change", 0.1, 2, 1 };
		BoolParameter enable_radius_change{ "Override Radius Change", true };

		void Execute(int active_input_index, const std::vector<Instruction*>& active_input_values, InstructionPool& lsystem, Plant* plant) override;

		static constexpr std::uint32_t Version = 1;

		template<class Archive>
		void serialize(Archive& archive, const std::uint32_t version)
		{
			if (version > Version)
			{
				throw std::runtime_error("Error: The file you are trying to load has been created with a newer version of this software than you are currently using.");
			}
			archive(cereal::base_class<Operation>(this), sides, enable_sides, radius, enable_radius, radius_change, enable_radius_change);
		}
	};

}
