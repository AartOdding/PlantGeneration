#pragma once

#include <memory>
#include <string>
#include <vector>

#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>


namespace LSystem
{

	struct InstructionData;

	struct Instruction
	{
		InstructionData* data;
		glm::mat4 transform{ 1 };
		bool is_recursion = false;
	};

	struct InstructionData
	{
		glm::mat4 transform{ 1 };
		std::vector<Instruction*> children;
		bool draw_branch = true;
		bool connect_branch_vertices = true;
		int branch_sides = 1; // In case of 1, a line will be drawn.
	};

}
