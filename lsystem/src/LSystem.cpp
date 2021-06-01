#include <LSystem/LSystem.hpp>

#include <cassert>



namespace LSystem
{

	// TODO: optimize away lines of size 0

	static void ExecuteInstruction(const InstructionData* data, const glm::mat4& local_space, VertexBuffer& vertex_buffer, int remaining_recursions)
	{
		if (!data)
		{
			assert(false); // fail in debug
			return;
		}

		auto branch_transform = local_space * data->transform;

		if (data->visible)
		{
			vertex_buffer.lines.emplace_back();
			vertex_buffer.lines.back().point_a.position = local_space * glm::vec4(0, 0, 0, 1);
			vertex_buffer.lines.back().point_b.position = branch_transform * glm::vec4(0, 0, 0, 1);
		}

		for (const auto& child : data->children)
		{
			assert(child); // fail in debug if child is empty

			if (child)
			{
				ExecuteInstruction(&child->data, branch_transform * child->transform, vertex_buffer, remaining_recursions);
			}
		}

		if (remaining_recursions > 0)
		{
			for (const auto& r : data->next_rules)
			{
				auto rule = r.rule.lock();

				assert(rule); // fail in debug if rule is empty

				if (rule)
				{
					ExecuteInstruction(&rule->data, branch_transform * r.transform, vertex_buffer, remaining_recursions - 1);
				}
			}
		}
	}

	VertexBuffer Generate(const InstructionData* branch, int recursions)
	{
		VertexBuffer render_buffer;

		ExecuteInstruction(branch, glm::mat4(1), render_buffer, recursions);

		return render_buffer;
	}


	std::shared_ptr<Rule> LSystem::CreateRule(std::string_view id)
	{
		auto rule = std::make_shared<Rule>();
		rule->id = id;
		rules.emplace(std::string(id), rule);
		return rule;
	}

}

