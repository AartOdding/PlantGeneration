#pragma once

#include <LSystem/Operation.hpp>



namespace LSystem
{

	struct PhyllotaxisOperation : Operation
	{
		PhyllotaxisOperation(OperationOwner* owner, std::string_view name);

		IntParameter branch_count{ this, "Count", 0, 255, 9 };
		FloatParameter branch_length{ this, "Length", 0, 10, 0.5 };
		FloatParameter spread{ this, "Spread", 0, 360, 120 };
		FloatParameter roll{ this, "Roll", 0, 360, 0 };

		std::vector<Instruction*> Apply(const std::vector<Instruction*>& apply_to, LSystem& lsystem) override;
		const std::string& Description() const override;
	};

}
