#include <LSystem/Instruction.hpp>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>


namespace LSystem
{

    std::vector<std::unique_ptr<Instruction>> CreateFork(int count, float length, float roll, float pitch)
    {
        std::vector<std::unique_ptr<Instruction>> instructions;
     
        if (count > 0)
        {
            instructions.reserve(count);

            const float angle_increment = glm::two_pi<float>() / count;

            for (int i = 0; i < count; ++i)
            {
                instructions.push_back(std::move(CreateExtrusion(length, roll + i * angle_increment, pitch)[0]));
            }
        }

        return instructions;
    }

    std::vector<std::unique_ptr<Instruction>> CreateFan(int count, float length, float spread, float roll)
    {
        std::vector<std::unique_ptr<Instruction>> instructions;

        if (count > 0)
        {
            instructions.reserve(count);

            const float angle_start = -spread / 2;
            const float angle_increment = spread / count;

            for (int i = 0; i < count; ++i)
            {
                instructions.push_back(std::move(CreateExtrusion(length, roll, angle_start + i * angle_increment)[0]));
            }
        }

        return instructions;
    }

    std::vector<std::unique_ptr<Instruction>> CreateExtrusion(float length, float roll, float pitch)
    {
        std::vector<std::unique_ptr<Instruction>> instructions(1);
        instructions[0] = std::make_unique<Instruction>();

        const auto roll_matrix = glm::rotate(glm::mat4(1), roll, glm::vec3(0, 1, 0));
        const auto pitch_matrix = glm::rotate(roll_matrix, pitch, glm::vec3(1, 0, 0));
        instructions[0]->transform = pitch_matrix;
        
        instructions[0]->data.transform = glm::translate(glm::mat4(1), glm::vec3(0, length, 0));

        return instructions;
    }

    std::vector<RuleReference> CreateRecursion(const std::shared_ptr<Rule>& rule, float scale, float roll, float pitch)
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

    std::vector<RuleReference> CreateRecursingFork(const std::shared_ptr<Rule>& rule, int count, float scale, float roll, float pitch)
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

    std::vector<RuleReference> CreateRecursingFan(const std::shared_ptr<Rule>& rule, int count, float spread, float scale, float roll)
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

}
