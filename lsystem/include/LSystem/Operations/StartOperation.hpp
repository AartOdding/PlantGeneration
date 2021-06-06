#pragma once

#include <LSystem/Operation.hpp>



namespace LSystem
{

	struct StartOperation : Operation
	{
		StartOperation(OperationOwner* owner, std::string_view name);

		std::vector<Instruction*> Apply(const std::vector<Instruction*>& apply_to, LSystem& lsystem) override;
		const std::string& Description() const override;
	};

}
