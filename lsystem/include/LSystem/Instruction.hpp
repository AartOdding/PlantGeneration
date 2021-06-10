#pragma once

#include <optional>
#include <vector>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <LSystem/Forward.hpp>



namespace LSystem
{

	struct Instruction
	{
		InstructionData* data;
		glm::mat4 transform{ 1 };
		bool is_recursion = false;
	};

	struct InstructionData
	{
		float length = 0;

		glm::mat4 transform(float scale) const
		{
			const auto scale_matrix = glm::scale(glm::mat4(1), glm::vec3(scale));
			return glm::translate(scale_matrix, glm::vec3(0, length, 0));
		}

		std::vector<Instruction*> children;
		bool draw_branch = true;
		bool connect_branch_vertices = true;

		std::optional<float> scale;
		std::optional<float> scale_change;

		std::optional<float> branch_radius;
		std::optional<float> branch_radius_change;

		std::optional<int> branch_sides; // In case of 1, a line will be drawn.
		std::optional<glm::vec3> branch_color;
	};

}
