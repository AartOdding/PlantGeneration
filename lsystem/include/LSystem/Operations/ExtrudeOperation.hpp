#pragma once

#include <LSystem/Operation.hpp>



namespace LSystem
{

	struct ExtrudeOperation : Operation
	{

		virtual std::vector<Instruction*> Apply(const std::vector<Instruction*>& apply_to) = 0;

	};

}
