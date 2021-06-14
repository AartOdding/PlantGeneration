#pragma once

#include <LSystem/Operation.hpp>



namespace LSystem
{

	struct LoopOperation : Operation
	{
		LoopOperation();

		IntParameter loop_count{ "Loop Count", 0, 20, 5 };

		void Execute(int active_input_index, const std::vector<Instruction*>& active_input_values, InstructionPool& lsystem, Plant* plant) override;

		void ResetState() override;

		template<class Archive>
		void serialize(Archive& archive)
		{
			archive(cereal::base_class<Operation>(this), loop_count);
		}

	private:

		int m_loop_count = 0;

	};

}
