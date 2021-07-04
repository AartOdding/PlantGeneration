#include <cassert>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <LSystem/LSystem.hpp>



namespace LSystem
{

    std::vector<glm::vec4> MakeCircle(int sides, float radius)
    {
        std::vector<glm::vec4> circle;

        if (sides > 0)
        {
            circle.resize(sides, glm::vec4(0, 0, 0, 1));

            if (sides > 1)
            {
                const auto angle_increment = glm::two_pi<float>() / sides;

                for (int i = 0; i < sides; ++i)
                {
                    circle[i].x = radius * glm::cos(i * angle_increment);
                    circle[i].z = radius * glm::sin(i * angle_increment);
                }
            }
        }

        return circle;
    }

    std::vector<glm::vec4> TransformCircle(const std::vector<glm::vec4>& circle, const glm::mat4& transform)
    {
        std::vector<glm::vec4> transformed_circle;
        transformed_circle.reserve(circle.size());

        for (auto& pt : circle)
        {
            transformed_circle.push_back(transform * pt);
        }

        return transformed_circle;
    }


	// TODO: optimize away lines of size 0

	void ExecuteInstruction(
        const Instruction* instruction,
        const glm::mat4& parent_space,
        VertexBuffer& vertex_buffer)
	{
		if (!instruction)
		{
			assert(false); // fail in debug
			return;
		}

		const auto branch_begin = parent_space * instruction->LinearTransform();
        const auto branch_end = parent_space * instruction->Transform();

		if (instruction->draw_branch)
		{
            if (instruction->branch_sides == 1)
            {
                vertex_buffer.lines.emplace_back();
                vertex_buffer.lines.back().point_a.position = branch_begin * glm::vec4(0, 0, 0, 1);
                vertex_buffer.lines.back().point_b.position = branch_end * glm::vec4(0, 0, 0, 1);
                vertex_buffer.lines.back().point_a.color = instruction->branch_color;
                vertex_buffer.lines.back().point_b.color = instruction->branch_color;
            }
            else if (instruction->branch_sides > 1)
            {
                auto circle = MakeCircle(instruction->branch_sides, instruction->branch_radius);
                auto circle_a = TransformCircle(circle, branch_begin);
                auto circle_b = TransformCircle(circle, branch_end);

                for (int i = 0; i < instruction->branch_sides; ++i)
                {
                    const int j = i + 1 == instruction->branch_sides ? 0 : i + 1; // Take next index or 0 if were at end

                    // Create triangle with two vertices from circle_a and one from circle_b.
                    auto& tri_1 = vertex_buffer.AddTriangle(circle_a[i], circle_a[j], circle_b[i]);
                    tri_1.point_1.color = instruction->branch_color;
                    tri_1.point_2.color = instruction->branch_color;
                    tri_1.point_3.color = instruction->branch_color;

                    // Create triangle with two vertices from circle_b and one from circle_a, together making a square.
                    auto& tri_2 = vertex_buffer.AddTriangle(circle_a[j], circle_b[i], circle_b[j]);
                    tri_2.point_1.color = instruction->branch_color;
                    tri_2.point_2.color = instruction->branch_color;
                    tri_2.point_3.color = instruction->branch_color;
                }
            }
		}

		for (const auto& child : instruction->children)
		{
			assert(child); // fail in debug if child is empty

			if (child)
			{
                ExecuteInstruction(child.get(), branch_end, vertex_buffer);
			}
		}
	}

    std::unique_ptr<Instruction> CopyInstruction(const Instruction& instruction)
    {
        auto new_instruction = std::make_unique<Instruction>();

        new_instruction->scale = instruction.scale;

        new_instruction->roll = instruction.roll;
        new_instruction->pitch = instruction.pitch;
        new_instruction->yaw = instruction.yaw;

        new_instruction->distance = instruction.distance;

        new_instruction->draw_branch = instruction.draw_branch;
        new_instruction->connect_branch_vertices = instruction.connect_branch_vertices;

        new_instruction->branch_radius = instruction.branch_radius;
        new_instruction->branch_sides = instruction.branch_sides;
        new_instruction->branch_color = instruction.branch_color;

        return new_instruction;
    }

    Instruction* Extrude(Instruction& instruction, float roll, float pitch, float yaw, float distance)
    {
        auto new_instruction = instruction.children.emplace_back(CopyInstruction(instruction)).get();
        new_instruction->roll = roll;
        new_instruction->pitch = pitch;
        new_instruction->yaw = yaw;
        new_instruction->distance = distance;
        return new_instruction;
    }
}
