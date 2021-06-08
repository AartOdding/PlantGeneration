#pragma once

#include <LSystem/Operation.hpp>



namespace LSystem
{

	struct ColoringOperation : Operation
	{
		ColoringOperation(Plant* plant);

		ColorParameter color{ this, "Color", glm::vec3(1, 1, 1) };

		std::vector<Instruction*> Apply(const std::vector<Instruction*>& apply_to, LSystem& lsystem) override;

		OperationInfo GetInfo() const override
		{
			return { 1, 1, "Apply Color" };
		}
	};

}
