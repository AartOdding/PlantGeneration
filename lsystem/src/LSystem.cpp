#include <cassert>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <LSystem/LSystem.hpp>



namespace LSystem
{

    struct CascadingState
    {
        glm::vec3 branch_color = glm::vec3(102.0 / 255, 51.0 / 255, 0);
        int branch_sides = 1;
        float branch_radius = 0.05;
        float branch_radius_change = 1;
        float scale = 1;
        float scale_change = 1;
    };

    void UpdateCascadingState(const Instruction* instruction, CascadingState& cascading_state)
    {
        // Update color
        if (instruction->data->branch_color.has_value())
        {
            cascading_state.branch_color = instruction->data->branch_color.value();
        }

        // Update sides
        if (instruction->data->branch_sides.has_value())
        {
            cascading_state.branch_sides = instruction->data->branch_sides.value();
        }

        // Update Radius
        if (instruction->data->branch_radius_change.has_value())
        {
            cascading_state.branch_radius_change = instruction->data->branch_radius_change.value();
        }
        if (instruction->data->branch_radius.has_value())
        {
            cascading_state.branch_radius = instruction->data->branch_radius.value();
        }
        else
        {
            cascading_state.branch_radius *= cascading_state.branch_radius_change;
        }

        // Update scale
        if (instruction->data->scale_change.has_value())
        {
            cascading_state.scale_change = instruction->data->scale_change.value();
        }
        if (instruction->data->scale.has_value())
        {
            cascading_state.scale = instruction->data->scale.value();
        }
        else
        {
            cascading_state.scale *= cascading_state.scale_change;
        }
    }

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

	static void ExecuteInstruction(
        const Instruction* instruction, 
        const glm::mat4& parent_space, 
        CascadingState cascading_state,
        VertexBuffer& vertex_buffer, 
        int remaining_recursions)
	{
		if (!instruction || !instruction->data)
		{
			assert(false); // fail in debug
			return;
		}

        UpdateCascadingState(instruction, cascading_state);

		auto local_space = parent_space * instruction->transform;
        auto branch_transform = local_space * instruction->data->transform(cascading_state.scale);

		if (instruction->data->draw_branch)
		{
            if (cascading_state.branch_sides == 1)
            {
                vertex_buffer.lines.emplace_back();
                vertex_buffer.lines.back().point_a.position = local_space * glm::vec4(0, 0, 0, 1);
                vertex_buffer.lines.back().point_b.position = branch_transform * glm::vec4(0, 0, 0, 1);
                vertex_buffer.lines.back().point_a.color = cascading_state.branch_color;
                vertex_buffer.lines.back().point_b.color = cascading_state.branch_color;
            }
            else if (cascading_state.branch_sides > 1)
            {
                auto circle = MakeCircle(cascading_state.branch_sides, cascading_state.branch_radius);
                auto circle_a = TransformCircle(circle, local_space);
                auto circle_b = TransformCircle(circle, branch_transform);

                for (int i = 0; i < cascading_state.branch_sides; ++i)
                {
                    int j = i + 1 == cascading_state.branch_sides ? 0 : i + 1; // Take next index or 0 if were at end

                    // Create triangle with two vertices from circle_a and one from circle_b.
                    auto& tri_1 = vertex_buffer.AddTriangle(circle_a[i], circle_a[j], circle_b[i]);
                    tri_1.point_1.color = cascading_state.branch_color;
                    tri_1.point_2.color = cascading_state.branch_color;
                    tri_1.point_3.color = cascading_state.branch_color;

                    // Create triangle with two vertices from circle_b and one from circle_a, together making a square.
                    auto& tri_2 = vertex_buffer.AddTriangle(circle_a[j], circle_b[i], circle_b[j]);
                    tri_2.point_1.color = cascading_state.branch_color;
                    tri_2.point_2.color = cascading_state.branch_color;
                    tri_2.point_3.color = cascading_state.branch_color;
                }
            }
		}

		for (const auto& child : instruction->data->children)
		{
			assert(child); // fail in debug if child is empty

			if (child)
			{
                if (child->is_recursion)
                {
                    ExecuteInstruction(child, branch_transform, cascading_state, vertex_buffer, remaining_recursions - 1);
                }
                else
                {
                    ExecuteInstruction(child, branch_transform, cascading_state, vertex_buffer, remaining_recursions);
                }
			}
		}
	}

}


namespace LSystem
{

    InstructionData* InstructionPool::AddInstructionData()
    {
        m_instructionDatas.emplace_back(std::make_unique<InstructionData>());
        return m_instructionDatas.back().get();
    }

    Instruction* InstructionPool::AddInstruction(InstructionData* data = nullptr)
    {
        m_instructions.emplace_back(std::make_unique<Instruction>());
        m_instructions.back()->data = data;
        return m_instructions.back().get();
    }

    Instruction* InstructionPool::CreateExtrusion(float length, float roll, float pitch)
    {
        auto instruction_data = AddInstructionData();
        auto instruction = AddInstruction(instruction_data);

        const auto roll_matrix = glm::rotate(glm::mat4(1), glm::radians(roll), glm::vec3(0, 1, 0));
        const auto pitch_matrix = glm::rotate(roll_matrix, glm::radians(pitch), glm::vec3(1, 0, 0));
        instruction->transform = pitch_matrix;

        instruction_data->length = length;

        return instruction;
    }

    VertexBuffer InstructionPool::Generate(int recursions)
    {
        VertexBuffer render_buffer;
        CascadingState cascading_state;

        if (first_instruction)
        {
            ExecuteInstruction(first_instruction, glm::mat4(1), cascading_state, render_buffer, recursions);
        }

        return render_buffer;
    }

}
