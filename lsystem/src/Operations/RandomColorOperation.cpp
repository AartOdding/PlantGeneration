#include <algorithm>
#include <cmath>
#include <cstdlib>

#include <glm/gtc/random.hpp>
#include <glm/gtx/color_space.hpp>

#include <LSystem/LSystem.hpp>



namespace LSystem
{

	RandomColorOperation::RandomColorOperation(OperationOwner* owner, std::string_view name)
		: Operation(owner, name)
	{

	}

	std::vector<Instruction*> RandomColorOperation::Apply(const std::vector<Instruction*>& apply_to, LSystem& lsystem)
	{
		std::srand(random_seed.value);

		auto hsv = glm::hsvColor(color.value);
		auto deviation = glm::vec3(hue_deviation.value * 360, sat_deviation.value, val_deviation.value);

		// sometimes hsv conversion results in nan
		auto is_nan = glm::isnan(hsv);

		if (!is_nan.x && !is_nan.y && !is_nan.z)
		{
			for (auto& i : apply_to)
			{
				auto new_hsv = glm::clamp(glm::gaussRand(hsv, deviation), { 0.0f, 0.0f, 0.0f }, { 360.0f, 1.0f, 1.0f });
				i->data->branch_color = glm::rgbColor(new_hsv);
			}
		}
		return {};
	}

	const std::string& RandomColorOperation::Description() const
	{
		static const std::string type_name_friendly = "Random Color";
		return type_name_friendly;
	}

}