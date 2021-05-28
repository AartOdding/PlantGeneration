#include <LSystem/LSystem.hpp>



namespace LSystem
{

	// TODO: optimize identity transform adding lines of size 0

	static void GrowBranch(const Branch* branch, const glm::mat4& origin, RenderBuffer& render_buffer)
	{
		if (!branch)
		{
			return;
		}

		if (branch->main_branch)
		{
			const glm::mat4 new_origin = origin * branch->main_branch->transform;

			render_buffer.lines.emplace_back();
			render_buffer.lines.back().point_a.position = origin * glm::vec4(0, 0, 0, 1);
			render_buffer.lines.back().point_b.position = new_origin * glm::vec4(0, 0, 0, 1);

			GrowBranch(branch->main_branch.get(), new_origin, render_buffer);
		}

		for (auto& side_branch : branch->side_branches)
		{
			const glm::mat4 new_origin = origin * side_branch->transform;

			GrowBranch(side_branch.get(), new_origin, render_buffer);
		}
	}

	RenderBuffer Generate(const Branch* branch)
	{
		RenderBuffer render_buffer;

		if (branch)
		{
			render_buffer.lines.emplace_back();
			render_buffer.lines.back().point_a.position = glm::vec3(0, 0, 0);
			auto p = branch->transform * glm::vec4(0, 0, 0, 1);
			render_buffer.lines.back().point_b.position = p;

			GrowBranch(branch, branch->transform, render_buffer);
		}

		return render_buffer;
	}

	/*
	RenderBuffer LSystem::Generate(float iterations) const
	{
		RenderBuffer render_buffer;

		if (rules.count(starting_rule))
		{
			const Rule* rule = rules.at(starting_rule).get();

			if (rule)
			{
				const glm::mat4 new_origin = origin * branch->main_branch->transform;

				render_buffer.lines.emplace_back();
				render_buffer.lines.back().point_a.position = origin * glm::vec4(0, 0, 0, 1);
				render_buffer.lines.back().point_b.position = new_origin * glm::vec4(0, 0, 0, 1);

				GrowBranch(rule->start.get(), glm::mat4(), render_buffer);
			}
		}

		return render_buffer;
	}
	*/
}

