#pragma once

#include <memory>
#include <string>
#include <vector>

#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>


namespace LSystem
{
	struct Instruction;

	struct InstructionData
	{
		glm::mat4 transform{ 1 };
		std::vector<std::unique_ptr<Instruction>> children;
		std::vector<std::string> next_rules;
		bool visible = true;
		bool connect_vertices = true;
		int sides = 1; // 1 or less is line, 2 is plane, 3+ cylinder
	};

	struct Instruction
	{
		glm::mat4 transform{ 1 };
		InstructionData data;
	};

	std::vector<std::unique_ptr<Instruction>> CreateFork(int count, float length, float roll = 0, float pitch = glm::quarter_pi<float>(), float yaw = 0);

	std::vector<std::unique_ptr<Instruction>> CreateExtrusion(float length, float roll = 0, float pitch = 0, float yaw = 0);


}
