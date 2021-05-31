#include <LSystem/Instruction.hpp>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>


namespace LSystem
{

    std::vector<std::unique_ptr<Instruction>> CreateFork(int count, float length, float roll, float pitch, float yaw)
    {
        std::vector<std::unique_ptr<Instruction>> instructions;
     
        if (count > 0)
        {
            instructions.reserve(count);

            const float angle_increment = glm::two_pi<float>() / count;

            for (int i = 0; i < count; ++i)
            {
                instructions.push_back(std::move(CreateExtrusion(length, roll + i * angle_increment, pitch, yaw)[0]));
            }
        }

        return instructions;
    }

    std::vector<std::unique_ptr<Instruction>> CreateExtrusion(float length, float roll, float pitch, float yaw)
    {
        std::vector<std::unique_ptr<Instruction>> instructions(1);
        instructions[0] = std::make_unique<Instruction>();

        const auto roll_matrix = glm::rotate(glm::mat4(1), roll, glm::vec3(0, 1, 0));
        const auto pitch_matrix = glm::rotate(roll_matrix, pitch, glm::vec3(1, 0, 0));
        instructions[0]->transform = pitch_matrix;
        
        instructions[0]->data.transform = glm::translate(glm::mat4(1), glm::vec3(0, length, 0));

        return instructions;
    }

}
