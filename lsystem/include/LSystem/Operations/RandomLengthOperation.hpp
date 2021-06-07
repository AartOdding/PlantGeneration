#pragma once

#include <LSystem/Operation.hpp>



namespace LSystem
{

	struct RandomLengthOperation : Operation
	{
		RandomLengthOperation(OperationOwner* owner, std::string_view name);

		FloatParameter min{ this, "Min", -10, 10, 0.5 };
		FloatParameter max{ this, "Max", -10, 10, 1 };

		std::vector<Instruction*> Apply(const std::vector<Instruction*>& apply_to, LSystem& lsystem) override;
		const std::string& Description() const override;
	};

}
