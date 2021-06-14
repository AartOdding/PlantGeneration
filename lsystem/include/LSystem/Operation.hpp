#pragma once

#include <string>
#include <string_view>
#include <vector>

#include <LSystem/Forward.hpp>
#include <LSystem/Instruction.hpp>
#include <LSystem/InstructionPool.hpp>

#include <LSystem/Parameters/BoolParameter.hpp>
#include <LSystem/Parameters/ColorParameter.hpp>
#include <LSystem/Parameters/FloatParameter.hpp>
#include <LSystem/Parameters/IntParameter.hpp>

#include <LSystem/Utils/Identifier.hpp>
#include <LSystem/Utils/NoCopy.hpp>
#include <LSystem/Utils/NoMove.hpp>

#include <cereal/types/polymorphic.hpp>



namespace LSystem
{

	struct OperationInfo
	{
		int input_count;
		int output_count;
		std::string description;
	};

	struct Operation : NoCopy, NoMove
	{
		Operation(const OperationInfo& info);

		virtual ~Operation() = default;

		const OperationInfo& GetInfo() const;
		Identifier<Operation> GetID() const;

		bool AddParameter(Parameter& parameter);
		bool RemoveParameter(Parameter& parameter);

		const std::vector<Parameter*>& Parameters();
		const std::vector<const Parameter*>& Parameters() const;

		// Called by plant, when executing "Return" output using ActivateOutput function.
		virtual void Execute(int active_input_index, const std::vector<Instruction*>& active_input_values, InstructionPool& lsystem, Plant* plant) = 0;

		virtual void ResetState() { }

		static constexpr std::uint32_t Version = 1;

		template<class Archive>
		void serialize(Archive& archive, const std::uint32_t version)
		{
			if (version > Version)
			{
				throw std::runtime_error("Error: The file you are trying to load has been created with a newer version of this software than you are currently using.");
			}
			archive(m_id);
		}

	protected:

		// Can call back into plant
		void ActivateOutput(int output_index, const std::vector<Instruction*>& output_values, InstructionPool& lsystem, Plant* plant);

	private:

		Identifier<Operation> m_id;
		OperationInfo m_info;

		std::vector<Parameter*> m_parameters;
		std::vector<const Parameter*> m_const_parameters;

	};

}
