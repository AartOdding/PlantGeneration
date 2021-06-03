#include <cassert>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <LSystem/LSystem.hpp>



namespace LSystem
{

	// TODO: optimize away lines of size 0

	static void ExecuteInstruction(const Instruction* instruction, const glm::mat4& parent_space, VertexBuffer& vertex_buffer, int remaining_recursions)
	{
		if (!instruction || !instruction->data)
		{
			assert(false); // fail in debug
			return;
		}

		auto local_space = parent_space * instruction->transform;
        auto branch_transform = local_space * instruction->data->transform;

		if (instruction->data->draw_branch)
		{
			vertex_buffer.lines.emplace_back();
			vertex_buffer.lines.back().point_a.position = local_space * glm::vec4(0, 0, 0, 1);
			vertex_buffer.lines.back().point_b.position = branch_transform * glm::vec4(0, 0, 0, 1);
		}

		for (const auto& child : instruction->data->children)
		{
			assert(child); // fail in debug if child is empty

			if (child)
			{
                if (child->is_recursion)
                {
                    ExecuteInstruction(child, branch_transform, vertex_buffer, remaining_recursions - 1);
                }
                else
                {
                    ExecuteInstruction(child, branch_transform, vertex_buffer, remaining_recursions);
                }
			}
		}
	}

	VertexBuffer Generate(const Instruction* branch, int recursions)
	{
		VertexBuffer render_buffer;

		ExecuteInstruction(branch, glm::mat4(1), render_buffer, recursions);

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

    std::vector<Instruction*> LSystem::CreateExtrusion(float length, float roll, float pitch)
    {
        auto instruction_data = AddInstructionData();
        auto instruction = AddInstruction(instruction_data);

        const auto roll_matrix = glm::rotate(glm::mat4(1), roll, glm::vec3(0, 1, 0));
        const auto pitch_matrix = glm::rotate(roll_matrix, pitch, glm::vec3(1, 0, 0));
        instruction->transform = pitch_matrix;

        instruction_data->transform = glm::translate(glm::mat4(1), glm::vec3(0, length, 0));

        return { instruction };
    }

    std::vector<Instruction*> LSystem::CreateExtrusion(const std::vector<Instruction*>& onto, float length, float roll, float pitch)
    {
        std::vector<Instruction*> instructions;
        instructions.reserve(onto.size());

        for (auto on : onto)
        {
            auto new_instructions = CreateExtrusion(length, roll, pitch);
            on->data->children.insert(on->data->children.end(), new_instructions.begin(), new_instructions.end());
            instructions.insert(instructions.end(), new_instructions.begin(), new_instructions.end());
        }

        return instructions;
    }

    std::vector<Instruction*> LSystem::CreateFork(int count, float length, float roll, float pitch)
    {
        std::vector<Instruction*> instructions;

        if (count > 0)
        {
            instructions.reserve(count);

            const float angle_increment = glm::two_pi<float>() / count;

            for (int i = 0; i < count; ++i)
            {
                instructions.push_back(CreateExtrusion(length, roll + i * angle_increment, pitch)[0]);
            }
        }

        return instructions;
    }

    std::vector<Instruction*> LSystem::CreateFork(const std::vector<Instruction*>& onto, int count, float length, float roll, float pitch)
    {
        std::vector<Instruction*> instructions;

        if (count > 0)
        {
            instructions.reserve(onto.size() * count);

            for (auto on : onto)
            {
                auto new_instructions = CreateFork(count, length, roll, pitch);
                on->data->children.insert(on->data->children.end(), new_instructions.begin(), new_instructions.end());
                instructions.insert(instructions.end(), new_instructions.begin(), new_instructions.end());
            }
        }

        return instructions;
    }

    std::vector<Instruction*> LSystem::CreateFan(int count, float length, float spread, float roll)
    {
        std::vector<Instruction*> instructions;

        if (count > 0)
        {
            instructions.reserve(count);

            const float angle_start = -spread / 2;
            const float angle_increment = spread / count;

            for (int i = 0; i < count; ++i)
            {
                instructions.push_back(CreateExtrusion(length, roll, angle_start + i * angle_increment)[0]);
            }
        }

        return instructions;
    }

    std::vector<Instruction*> LSystem::CreateFan(const std::vector<Instruction*>& onto, int count, float length, float spread, float roll)
    {
        std::vector<Instruction*> instructions;

        if (count > 0)
        {
            instructions.reserve(onto.size() * count);

            for (auto on : onto)
            {
                auto new_instructions = CreateFan(count, length, spread, roll);
                on->data->children.insert(on->data->children.end(), new_instructions.begin(), new_instructions.end());
                instructions.insert(instructions.end(), new_instructions.begin(), new_instructions.end());
            }
        }

        return instructions;
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
