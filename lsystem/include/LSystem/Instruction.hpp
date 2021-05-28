#pragma once

#include <memory>


namespace LSystem
{

	class Instruction
	{
	public:

		std::unique_ptr<Instruction> next_instruction = nullptr;

		virtual ~Instruction() = default;

	private:

	};

}
