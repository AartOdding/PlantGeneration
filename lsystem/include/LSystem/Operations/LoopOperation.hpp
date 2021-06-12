#pragma once

#include <LSystem/Operation.hpp>



namespace LSystem
{

	struct LoopOperation : Operation, NoCopy, NoMove
	{
		LoopOperation();

		IntParameter loop_count{ "Loop Count", 0, 20, 5 };

		void Execute(int active_input_index, const std::vector<Instruction*>& active_input_values, LSystem& lsystem, Plant* plant) override;

		void ResetState() override;

	private:

		int m_loop_count = 0;

	};

}
