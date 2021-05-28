#pragma once

#include <string>

#include <LSystem/Instruction.hpp>


namespace LSystem
{

	class RecurseInstruction : public Instruction
	{
	public:

		std::string next_rule_id;

	private:

	};

}
