#pragma once

#include <LSystem/Operation.hpp>



namespace LSystem
{

	struct StartOperation : Operation, NoCopy, NoMove
	{
		StartOperation();

		void Execute(int active_input_index, const std::vector<Instruction*>& active_input_values, InstructionPool& lsystem, Plant* plant) override;

		template<class Archive>
		void serialize(Archive& archive)
		{
			archive(cereal::base_class<Operation>(this));
		}
	};

}
