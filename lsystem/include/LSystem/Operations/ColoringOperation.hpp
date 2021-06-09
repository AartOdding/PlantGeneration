#pragma once

#include <LSystem/Operation.hpp>



namespace LSystem
{

	struct ColoringOperation : Operation
	{
		ColoringOperation(Plant* plant);

		ColorParameter color{ this, "Color", glm::vec3(1, 1, 1) };

		void Execute(int active_input_index, const std::vector<Instruction*>& active_input_values, LSystem& lsystem) override;

		OperationInfo GetInfo() const override
		{
			return { 1, 0, "Apply Color" };
		}
	};

}
