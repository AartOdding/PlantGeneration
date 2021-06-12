#pragma once

#include <LSystem/Operation.hpp>



namespace LSystem
{

	struct StartOperation : Operation, NoCopy, NoMove
	{
		StartOperation();

		void Execute(int active_input_index, const std::vector<Instruction*>& active_input_values, LSystem& lsystem, Plant* plant) override;
	};

}
