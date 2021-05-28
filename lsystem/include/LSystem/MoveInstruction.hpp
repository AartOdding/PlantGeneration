#pragma once

#include <glm/glm.hpp>

#include <LSystem/Instruction.hpp>


namespace LSystem
{

	class MoveInstruction : public Instruction
	{
	public:

		glm::mat4 movement = glm::mat4();


	private:

	};

}
