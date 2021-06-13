#pragma once

#include <LSystem/Operation.hpp>



namespace LSystem
{

	struct RadiusOperation : Operation, NoCopy, NoMove
	{
		RadiusOperation();

		IntParameter sides{ "Sides", 0, 21, 1 };
		BoolParameter enable_sides{ "Sides", true };
		FloatParameter radius{ "Radius", 0.001, 1, 0.01 };
		BoolParameter enable_radius{ "Override Radius", true };
		FloatParameter radius_change{ "Radius Change", 0.1, 2, 1 };
		BoolParameter enable_radius_change{ "Override Radius Change", true };

		void Execute(int active_input_index, const std::vector<Instruction*>& active_input_values, InstructionPool& lsystem, Plant* plant) override;

		template<class Archive>
		void serialize(Archive& archive)
		{
			archive(cereal::base_class<Operation>(this), sides, enable_sides, radius, enable_radius, radius_change, enable_radius_change);
		}
	};

}
