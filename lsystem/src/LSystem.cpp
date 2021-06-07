#include <cassert>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <LSystem/LSystem.hpp>



namespace LSystem
{

    struct CascadingState
    {
        glm::vec3 branch_color = glm::vec3(102.0 / 255, 51.0 / 255, 0);
        float branch_radius = 0.1;
        int branch_sides = 5;
    };

    std::vector<glm::vec4> GetCircle(int sides, float radius)
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

	// TODO: optimize away lines of size 0

	static void ExecuteInstruction(
        const Instruction* instruction, 
        const glm::mat4& parent_space, 
        CascadingState& cascading_state,
        VertexBuffer& vertex_buffer, 
        int remaining_recursions)
	{
		if (!instruction || !instruction->data)
		{
			assert(false); // fail in debug
			return;
		}

        // Update cascading state:

        if (instruction->data->branch_color.has_value())
        {
            cascading_state.branch_color = instruction->data->branch_color.value();
        }
        if (instruction->data->branch_radius.has_value())
        {
            cascading_state.branch_radius = instruction->data->branch_radius.value();
        }
        if (instruction->data->branch_radius.has_value())
        {
            cascading_state.branch_radius = instruction->data->branch_radius.value();
        }

		auto local_space = parent_space * instruction->transform;
        auto branch_transform = local_space * instruction->data->transform();

		if (instruction->data->draw_branch)
		{
			vertex_buffer.lines.emplace_back();
			vertex_buffer.lines.back().point_a.position = local_space * glm::vec4(0, 0, 0, 1);
			vertex_buffer.lines.back().point_b.position = branch_transform * glm::vec4(0, 0, 0, 1);
            vertex_buffer.lines.back().point_a.color = color;
            vertex_buffer.lines.back().point_b.color = color;
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

	VertexBuffer Generate(const Instruction* branch, int recursions)
	{
		VertexBuffer render_buffer;
        CascadingState cascading_state;

        ExecuteInstruction(branch, glm::mat4(1), cascading_state, render_buffer, recursions);

		return render_buffer;
	}

}


namespace LSystem
{

    InstructionData* LSystem::AddInstructionData()
    {
        m_instructionDatas.emplace_back(std::make_unique<InstructionData>());
        return m_instructionDatas.back().get();
    }

    Instruction* LSystem::AddInstruction(InstructionData* data = nullptr)
    {
        m_instructions.emplace_back(std::make_unique<Instruction>());
        m_instructions.back()->data = data;
        return m_instructions.back().get();
    }

    Instruction* LSystem::CreateExtrusion(float length, float roll, float pitch)
    {
        auto instruction_data = AddInstructionData();
        auto instruction = AddInstruction(instruction_data);

        const auto roll_matrix = glm::rotate(glm::mat4(1), glm::radians(roll), glm::vec3(0, 1, 0));
        const auto pitch_matrix = glm::rotate(roll_matrix, glm::radians(pitch), glm::vec3(1, 0, 0));
        instruction->transform = pitch_matrix;

        instruction_data->length = length;

        return instruction;
    }

    std::vector<Instruction*> LSystem::CreateBase(float length)
    {
        begin = CreateExtrusion(length, 0, 0);
        return { begin };
    }

    /*
    std::vector<Instruction*> LSystem::CreateRecursion(Instruction* rule, float scale, float roll, float pitch)
    {
        std::vector<RuleReference> rule_reference;
        rule_reference.resize(1);

        const auto roll_matrix = glm::rotate(glm::mat4(1), roll, glm::vec3(0, 1, 0));
        const auto pitch_matrix = glm::rotate(roll_matrix, pitch, glm::vec3(1, 0, 0));
        const auto scale_matrix = glm::scale(pitch_matrix, glm::vec3(scale, scale, scale));
        rule_reference[0].transform = scale_matrix;

        rule_reference[0].rule = rule;
        return rule_reference;
    }

    std::vector<Instruction*> LSystem::CreateRecursingFork(Instruction* rule, int count, float scale, float roll, float pitch)
    {
        std::vector<RuleReference> rule_references;

        if (count > 0)
        {
            rule_references.reserve(count);

            const float angle_increment = glm::two_pi<float>() / count;

            for (int i = 0; i < count; ++i)
            {
                rule_references.push_back(std::move(CreateRecursion(rule, scale, roll + i * angle_increment, pitch)[0]));
            }
        }

        return rule_references;
    }

    std::vector<Instruction*> LSystem::CreateRecursingFan(Instruction* rule, int count, float spread, float scale, float roll)
    {
        std::vector<RuleReference> rule_references;

        if (count > 0)
        {
            rule_references.reserve(count);

            const float angle_start = -spread / 2;
            const float angle_increment = spread / count;

            for (int i = 0; i < count; ++i)
            {
                rule_references.push_back(std::move(CreateRecursion(rule, scale, roll, angle_start + i * angle_increment)[0]));
            }
        }

        return rule_references;
    }
    */
}
