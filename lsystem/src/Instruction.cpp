#include <LSystem/Instruction.hpp>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>


namespace LSystem
{

    std::vector<Instruction*> CreateEqualBranches(Instruction& instruction, int count, float pitch, float length)
    {
        std::vector<Instruction*> new_branches;
        new_branches.reserve(count);

        const float angle_increment = glm::two_pi<float>() / count;

        for (int i = 0; i < count; ++i)
        {
            new_branches.push_back(CreateExtrudingBranch(instruction, i * angle_increment, pitch, length));
        }
        return new_branches;
    }

    Instruction* CreateExtrudingBranch(Instruction& i, float roll, float pitch, float length)
    {
        auto new_instruction = std::make_unique<Instruction>();

        auto roll_ = glm::rotate(glm::mat4(1), roll, glm::vec3(0, 1, 0));
        auto pitch_ = glm::rotate(roll_, pitch, glm::vec3(1, 0, 0));
        new_instruction->transform = glm::translate(pitch_, glm::vec3(0, length, 0));

        auto new_instruction_temp = new_instruction.get();
        i.children.push_back(std::move(new_instruction));
        return new_instruction_temp;
    }

}
