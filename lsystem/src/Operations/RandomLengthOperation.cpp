#include <cstdlib>

#include <glm/gtc/random.hpp>
#include <glm/gtx/matrix_decompose.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <LSystem/LSystem.hpp>



namespace LSystem
{

	RandomLengthOperation::RandomLengthOperation(Plant* plant)
		: Operation(plant)
	{

	}

	void RandomLengthOperation::Execute(int active_input_index, const std::vector<Instruction*>& active_input_values, LSystem& lsystem)
	{
		for (auto& i : active_input_values)
		{
			i->data->length = glm::linearRand<float>(min, max);
		}
	}

	void RandomLengthOperation::ResetState()
	{
		std::srand(random_seed.value);
	}

}