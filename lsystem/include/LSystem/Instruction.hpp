#pragma once

#include <optional>
#include <memory>
#include <vector>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <LSystem/Forward.hpp>



namespace LSystem
{

	struct Instruction
	{
		// Variables used to calculate the transform:

		float scale = 1;
		
		float roll = 0;
		float pitch = 0;
		float yaw = 0;

		float distance = 1;

		// Variables to decide how / if to draw branch:

		bool draw_branch = true;
		bool connect_branch_vertices = true;

		float branch_radius = 0.01;
		int branch_sides = 5; // In case of 1, a line will be drawn.
		glm::vec3 branch_color = glm::vec3(63.0 / 255.0, 48.0 / 255.0, 29.0 / 255.0);

		// Instructions that come after this one:

		std::vector<std::unique_ptr<Instruction>> children;


		glm::mat4 Transform() const
		{
			return glm::translate(LinearTransform(), glm::vec3(0, distance, 0));;
		}

		glm::mat4 LinearTransform() const
		{
			const auto scale_matrix = glm::scale(glm::mat4(1), glm::vec3(scale));
			const auto roll_matrix = glm::rotate(scale_matrix, glm::radians(roll), glm::vec3(0, 1, 0));
			const auto pitch_matrix = glm::rotate(roll_matrix, glm::radians(pitch), glm::vec3(1, 0, 0));
			const auto yaw_matrix = glm::rotate(pitch_matrix, glm::radians(yaw), glm::vec3(0, 0, 1));
			return yaw_matrix;
		}
	};

	void ExecuteInstruction(const Instruction* instruction, const glm::mat4& parent_space, VertexBuffer& vertex_buffer);

	std::unique_ptr<Instruction> CopyInstruction(const Instruction& instruction);

	Instruction* Extrude(Instruction& instruction, float roll, float pitch, float yaw, float distance);
}
