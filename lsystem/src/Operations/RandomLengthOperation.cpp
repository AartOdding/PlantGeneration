#include <cstdlib>

#include <glm/gtc/random.hpp>
#include <glm/gtx/matrix_decompose.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <LSystem/Operations/RandomLengthOperation.hpp>



namespace LSystem
{

	RandomLengthOperation::RandomLengthOperation()
		: Operation({ 1, 0, "Set Random Length" })
	{
		AddParameter(min);
		AddParameter(max);
		AddParameter(random_seed);
	}

	void RandomLengthOperation::Execute(int active_input_index, const std::vector<Instruction*>& active_input_values, InstructionPool& lsystem, Plant* plant)
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