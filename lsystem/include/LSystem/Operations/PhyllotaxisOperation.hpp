#pragma once

#include <LSystem/Operation.hpp>



namespace LSystem
{

	struct PhyllotaxisOperation : Operation, NoCopy, NoMove
	{
		PhyllotaxisOperation();

		IntParameter branch_count{ "Count", 0, 255, 9 };
		FloatParameter branch_length{ "Length", 0, 10, 0.5 };
		FloatParameter spread{ "Spread", 0, 360, 120 };
		FloatParameter roll{ "Roll", 0, 360, 0 };

		void Execute(int active_input_index, const std::vector<Instruction*>& active_input_values, LSystem& lsystem, Plant* plant) override;
	};

}
