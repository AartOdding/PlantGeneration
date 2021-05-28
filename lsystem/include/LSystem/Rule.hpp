#pragma once

#include <memory>
#include <string>

#include <LSystem/Instruction.hpp>



namespace LSystem
{

	class Rule
	{
	public:

		std::string id;
		std::unique_ptr<Instruction> first_instruction;

		virtual ~Rule() = default;

	private:

	};

}
