#pragma once

#include <LSystem/Operation.hpp>



namespace LSystem
{

	struct FanOperation : Operation
	{
		FanOperation(OperationOwner* owner, std::string_view name);

		IntParameter fork_count{ this, "Fan Count", 0, 255, 9 };
		FloatParameter fork_length{ this, "Fan Length", 0, 10, 0.5 };
		FloatParameter spread{ this, "Spread", 0, 360, 120 };
		FloatParameter roll{ this, "Roll", 0, 360, 0 };

		std::vector<Instruction*> Apply(const std::vector<Instruction*>& apply_to, LSystem& lsystem) override;

	};

}
