#pragma once

#include <LSystem/Operation.hpp>



namespace LSystem
{

	struct PhyllotaxisOperation : Operation
	{

		virtual std::vector<Instruction*> Apply(const std::vector<Instruction*>& apply_to) = 0;

	};

}
