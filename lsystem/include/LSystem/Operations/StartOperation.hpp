#pragma once

#include <LSystem/Operation.hpp>



namespace LSystem
{

	struct StartOperation : Operation
	{
		StartOperation(Plant* plant);

		std::vector<Instruction*> Apply(const std::vector<Instruction*>& apply_to, LSystem& lsystem) override;

		OperationInfo GetInfo() const override
		{
			return { 1, 1, "Start" };
		}
	};

}
