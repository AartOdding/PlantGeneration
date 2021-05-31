#include <LSystem/LSystem.hpp>

#include <cassert>



namespace LSystem
{

	// TODO: optimize away lines of size 0

	static void ExecuteInstruction(const Instruction* data, const glm::mat4& world_space, VertexBuffer& vertex_buffer)
	{
		if (!data)
		{
			assert(false); // fail in debug
			return;
		}

		auto local_origin = world_space * data->transform;
		auto branch_transform = local_origin * data->data.transform;

		if (data->data.visible)
		{
			vertex_buffer.lines.emplace_back();
			vertex_buffer.lines.back().point_a.position = local_origin * glm::vec4(0, 0, 0, 1);
			vertex_buffer.lines.back().point_b.position = branch_transform * glm::vec4(0, 0, 0, 1);
		}

		for (const auto& child : data->data.children)
		{
			assert(child); // fail in debug if child is empty

			if (child)
			{
				ExecuteInstruction(child.get(), branch_transform, vertex_buffer);
			}
		}
	}

	VertexBuffer Generate(const Instruction* branch)
	{
		VertexBuffer render_buffer;

		ExecuteInstruction(branch, glm::mat4(1), render_buffer);

		return render_buffer;
	}


	Rule* LSystem::CreateRule(std::string_view id)
	{
		auto rule = std::make_unique<Rule>();
		rule->id = id;
		auto ruleTemp = rule.get();
		rules.emplace(std::string(id), std::move(rule));
		return ruleTemp;
	}

}

