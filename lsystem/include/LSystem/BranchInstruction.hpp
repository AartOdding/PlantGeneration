#pragma once

#include <memory>
#include <vector>

#include <LSystem/Instruction.hpp>


namespace LSystem
{

	class BranchInstruction : public Instruction
	{
	public:

		std::vector<std::unique_ptr<Instruction>> branches;

	private:

	};

}
