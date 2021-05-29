#include <LSystem/LSystem.hpp>

#include <cassert>



namespace LSystem
{

	// TODO: optimize identity transform adding lines of size 0

	static void ExecuteInstruction(const Instruction* instruction, const glm::mat4& transform, VertexBuffer& vertex_buffer)
	{
		if (!instruction)
		{
			assert(false); // fail in debug
			return;
		}

		for (const auto& child : instruction->children)
		{
			assert(child); // fail in debug if child is empty

			if (child)
			{
				const glm::mat4 new_transform = transform * child->transform;

				if (child->visible)
				{
					// depending on connectedness and amount of sides render different

					vertex_buffer.lines.emplace_back();
					vertex_buffer.lines.back().point_a.position = transform * glm::vec4(0, 0, 0, 1);
					vertex_buffer.lines.back().point_b.position = new_transform * glm::vec4(0, 0, 0, 1);
				}

				ExecuteInstruction(child.get(), new_transform, vertex_buffer);
			}
		}
	}

	VertexBuffer Generate(const Instruction* branch)
	{
		VertexBuffer render_buffer;

		if (branch)
		{
			if (branch->visible)
			{
				render_buffer.lines.emplace_back();
				render_buffer.lines.back().point_a.position = glm::vec3(0, 0, 0);
				render_buffer.lines.back().point_b.position = branch->transform * glm::vec4(0, 0, 0, 1);
			}

			ExecuteInstruction(branch, branch->transform, render_buffer);
		}

		return render_buffer;
	}

	/*
	VertexBuffer LSystem::Generate(float iterations) const
	{
		VertexBuffer vertex_buffer;

		if (rules.count(starting_rule))
		{
			const Rule* rule = rules.at(starting_rule).get();

			if (rule)
			{
				const glm::mat4 new_transform = transform * instruction->main_branch->transform;

				vertex_buffer.lines.emplace_back();
				vertex_buffer.lines.back().point_a.position = transform * glm::vec4(0, 0, 0, 1);
				vertex_buffer.lines.back().point_b.position = new_transform * glm::vec4(0, 0, 0, 1);

				ExecuteInstruction(rule->start.get(), glm::mat4(), vertex_buffer);
			}
		}

		return vertex_buffer;
	}
	*/
}

