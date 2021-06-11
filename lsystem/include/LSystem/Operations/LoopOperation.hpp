#pragma once

#include <LSystem/Operation.hpp>



namespace LSystem
{

	struct LoopOperation : Operation
	{
		LoopOperation(Plant* plant);

		IntParameter loop_count{ "Loop Count", 0, 20, 5 };

		void Execute(int active_input_index, const std::vector<Instruction*>& active_input_values, LSystem& lsystem) override;

		void ResetState() override;

		OperationInfo GetInfo() const override
		{
			return { 1, 2, "Loop" };
		}

	private:

		int m_loop_count = 0;

	};

}
