#pragma once

#include <LSystem/Operation.hpp>



namespace LSystem
{

	struct ScaleOperation : Operation
	{
		ScaleOperation(Plant* plant);

		FloatParameter scale{ this, "Scale", 0.1, 10, 1 };
		FloatParameter scale_change{ this, "Scale Change", 0.1, 2, 1 };

		void Execute(int active_input_index, const std::vector<Instruction*>& active_input_values, LSystem& lsystem) override;

		OperationInfo GetInfo() const override
		{
			return { 1, 0, "Scale" };
		}
	};

}
