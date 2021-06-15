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

		static constexpr std::uint32_t Version = 1;

		template<class Archive>
		void serialize(Archive& archive, const std::uint32_t version)
		{
			if (version > Version)
			{
				throw std::runtime_error("Error: The file you are trying to load has been created with a newer version of this software than you are currently using.");
			}
			archive(cereal::base_class<Operation>(this), loop_count);
		}

	private:

		int m_loop_count = 0;

	};

}
