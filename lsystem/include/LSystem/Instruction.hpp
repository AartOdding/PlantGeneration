#pragma once

#include <memory>
#include <string>
#include <vector>

#include <glm/glm.hpp>


namespace LSystem
{

	struct Instruction
	{
		glm::mat4 transform{ 1 };
		std::vector<std::unique_ptr<Instruction>> children;
		std::vector<std::string> next_rules;
		bool visible = true;
		bool connect_vertices = true;
		int sides = 1; // 1 or less is line, 2 is plane, 3+ cylinder
	};

}
