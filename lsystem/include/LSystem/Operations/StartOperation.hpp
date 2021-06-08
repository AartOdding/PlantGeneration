#pragma once

#include <LSystem/Operation.hpp>



namespace LSystem
{

	struct StartOperation : Operation
	{
		StartOperation(Plant* plant);

		void Execute(int active_input_index, const std::vector<Instruction*>& active_input_values, LSystem& lsystem) override;

		OperationInfo GetInfo() const override
		{
			return { 1, 1, "Start" };
		}
	};

}
