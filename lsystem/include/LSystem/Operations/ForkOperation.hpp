#pragma once

#include <LSystem/Operation.hpp>



namespace LSystem
{

	struct ForkOperation : Operation
	{
		ForkOperation(OperationOwner* owner, std::string_view name);

		IntParameter fork_count{ this, "Fork Count", 0, 255, 9 };
		FloatParameter fork_length{ this, "Fork Length", 0, 10, 0.5 };
		FloatParameter spread{ this, "Spread", 0, 360, 120 };
		FloatParameter roll{ this, "Roll", 0, 360, 0 };

		std::vector<Instruction*> Apply(const std::vector<Instruction*>& apply_to, LSystem& lsystem) override;

	};

}
