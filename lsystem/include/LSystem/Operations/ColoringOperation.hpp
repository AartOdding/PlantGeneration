#pragma once

#include <LSystem/Operation.hpp>



namespace LSystem
{

	struct ColoringOperation : Operation, NoCopy, NoMove
	{
		ColoringOperation();

		ColorParameter color{ "Color", glm::vec3(1, 1, 1) };

		void Execute(int active_input_index, const std::vector<Instruction*>& active_input_values, LSystem& lsystem, Plant* plant) override;
	};

}
