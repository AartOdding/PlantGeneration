#pragma once

#include <LSystem/Operation.hpp>



namespace LSystem
{

	struct ScaleOperation : Operation
	{
		ScaleOperation();

		FloatParameter scale{ "Scale", 0.1, 10, 1 };
		BoolParameter enable_scale{ "Override Scale", true };
		FloatParameter scale_change{ "Scale Change", 0.1, 2, 1 };
		BoolParameter enable_scale_change{ "Override Scale Change", true };

		void Execute(int active_input_index, const std::vector<Instruction*>& active_input_values, InstructionPool& lsystem, Plant* plant) override;

		template<class Archive>
		void serialize(Archive& archive)
		{
			archive(cereal::base_class<Operation>(this), scale, enable_scale, scale_change, enable_scale_change);
		}
	};

}
