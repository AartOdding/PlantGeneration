#pragma once

#include <memory>

#include <glm/glm.hpp>


namespace LSystem
{

	struct Branch
	{
		glm::mat4 transform{ 1 };
		std::unique_ptr<Branch> main_branch;
		std::vector<std::unique_ptr<Branch>> side_branches;
	};

	class Instruction
	{
	public:

		glm::mat4 transform;

		std::unique_ptr<Instruction> next_instruction = nullptr;


		virtual ~Instruction() = default;

	private:

	};

}
