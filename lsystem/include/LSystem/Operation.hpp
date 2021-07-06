#pragma once

#include <functional>
#include <string>
#include <stdexcept>
#include <vector>

#include <LSystem/Forward.hpp>
#include <LSystem/Instruction.hpp>
#include <LSystem/Modifier.hpp>
#include <LSystem/ParameterList.hpp>

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
		std::string short_name;
		std::string description;
		std::function<std::unique_ptr<Operation>()> create_function;
	};

	struct Operation : ParameterList, NoCopy, NoMove
	{
		Operation(const OperationInfo& info);

		virtual ~Operation() = default;

		const OperationInfo& GetInfo() const;
		Identifier<Operation> GetID() const;

		Modifier* AddModifier(std::unique_ptr<Modifier>&& modifier);
		bool DeleteModifier(Identifier<Modifier> modifier);

		const std::vector<Modifier*>& Modifiers();
		const std::vector<const Modifier*>& Modifiers() const;

		// Called by plant, when executing "Return" output using ActivateOutput function.
		virtual void Execute(int active_input_index, const std::vector<Instruction*>& active_input_values, Plant* plant) = 0;

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
		void ActivateOutput(int output_index, const std::vector<Instruction*>& output_values, Plant* plant);

	private:

		Identifier<Operation> m_id;
		OperationInfo m_info;

		std::vector<std::unique_ptr<Modifier>> m_modifiers_owned;
		std::vector<Modifier*> m_modifiers_pointers;
		std::vector<const Modifier*> m_modifiers_pointers_const;

	};

}
