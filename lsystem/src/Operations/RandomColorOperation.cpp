#include <algorithm>
#include <cmath>
#include <cstdlib>

#include <glm/gtc/random.hpp>
#include <glm/gtx/color_space.hpp>

#include <LSystem/Operations/RandomColorOperation.hpp>



namespace LSystem
{

	RandomColorOperation::RandomColorOperation()
		: Operation({ 1, 0, "Apply Random Color" })
	{
		AddParameter(color);
		AddParameter(hue_deviation);
		AddParameter(sat_deviation);
		AddParameter(val_deviation);
		AddParameter(random_seed);
	}

	void RandomColorOperation::Execute(int active_input_index, const std::vector<Instruction*>& active_input_values, InstructionPool& lsystem, Plant* plant)
	{
		auto hsv = glm::hsvColor(color.value);
		auto deviation = glm::vec3(hue_deviation.value * 360, sat_deviation.value, val_deviation.value);

		// sometimes hsv conversion results in nan
		auto is_nan = glm::isnan(hsv);

		if (!is_nan.x && !is_nan.y && !is_nan.z)
		{
			for (auto& i : active_input_values)
			{
				auto new_hsv = glm::clamp(glm::gaussRand(hsv, deviation), { 0.0f, 0.0f, 0.0f }, { 360.0f, 1.0f, 1.0f });
				i->data->branch_color = glm::rgbColor(new_hsv);
			}
		}
	}

	void RandomColorOperation::ResetState()
	{
		std::srand(random_seed.value);
	}

}