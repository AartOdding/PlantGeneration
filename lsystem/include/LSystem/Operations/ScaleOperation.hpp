#pragma once

#include <LSystem/Operation.hpp>



namespace LSystem
{

	struct ScaleOperation : Operation, NoCopy, NoMove
	{
		ScaleOperation();

		FloatParameter scale{ "Scale", 0.1, 10, 1 };
		BoolParameter enable_scale{ "Override Scale", true };
		FloatParameter scale_change{ "Scale Change", 0.1, 2, 1 };
		BoolParameter enable_scale_change{ "Override Scale Change", true };

		void Execute(int active_input_index, const std::vector<Instruction*>& active_input_values, LSystem& lsystem, Plant* plant) override;
	};

}
