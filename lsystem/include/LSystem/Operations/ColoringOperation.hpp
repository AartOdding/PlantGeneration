#pragma once

#include <LSystem/Operation.hpp>



namespace LSystem
{

	struct ColoringOperation : Operation
	{
		ColoringOperation();

		ColorParameter color{ "Color", glm::vec3(1, 1, 1) };

		void Execute(int active_input_index, const std::vector<Instruction*>& active_input_values, InstructionPool& lsystem, Plant* plant) override;

		static constexpr std::uint32_t Version = 1;

		template<class Archive>
		void serialize(Archive& archive, const std::uint32_t version)
		{
			if (version > Version)
			{
				throw std::runtime_error("Error: The file you are trying to load has been created with a newer version of this software than you are currently using.");
			}
			archive(cereal::base_class<Operation>(this), color);
		}
	};

}
