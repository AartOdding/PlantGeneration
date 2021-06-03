#pragma once

#include <memory>
#include <string>
#include <vector>

#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>


namespace LSystem
{

	struct Rule;
	struct Instruction;

	struct RuleReference
	{
		glm::mat4 transform{ 1 };
		std::weak_ptr<Rule> rule;
	};

	struct InstructionData
	{
		glm::mat4 transform{ 1 };
		std::vector<std::unique_ptr<Instruction>> children;
		std::vector<RuleReference> next_rules;
		bool visible = true;
		bool connect_vertices = true;
		int sides = 1; // 1 or less is line, 2 is plane, 3+ cylinder
	};

	struct Instruction
	{
		glm::mat4 transform{ 1 };
		InstructionData data;
	};

	struct Rule
	{
		std::string id;
		InstructionData data;
	};

	std::vector<std::unique_ptr<Instruction>> CreateExtrusion(float length, float roll = 0, float pitch = 0);

	std::vector<std::unique_ptr<Instruction>> CreateFork(int count, float length, float roll = 0, float pitch = glm::quarter_pi<float>());

	std::vector<std::unique_ptr<Instruction>> CreateFan(int count, float length, float spread = glm::quarter_pi<float>(), float roll = 0);

	std::vector<RuleReference> CreateRecursion(const std::shared_ptr<Rule>& rule, float scale = 1, float roll = 0, float pitch = 0);

	std::vector<RuleReference> CreateRecursingFork(const std::shared_ptr<Rule>& rule, int count, float scale = 1, float roll = 0, float pitch = glm::quarter_pi<float>());

	std::vector<RuleReference> CreateRecursingFan(const std::shared_ptr<Rule>& rule, int count, float spread = glm::quarter_pi<float>(), float scale = 1, float roll = 0);

}
