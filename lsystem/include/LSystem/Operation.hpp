#pragma once

#include <string>
#include <string_view>
#include <vector>

#include <LSystem/Forward.hpp>
#include <LSystem/ParameterOwner.hpp>

#include <LSystem/Parameters/BoolParameter.hpp>
#include <LSystem/Parameters/ColorParameter.hpp>
#include <LSystem/Parameters/FloatParameter.hpp>
#include <LSystem/Parameters/IntParameter.hpp>

#include <LSystem/Utils/NoCopy.hpp>
#include <LSystem/Utils/NoMove.hpp>



namespace LSystem
{

	struct OperationInfo
	{
		int input_count;
		int output_count;
		std::string description;

		template<class Archive>
		void serialize(Archive& archive)
		{
			archive(input_count, output_count, description);
		}
	};

	struct Operation : ParameterOwner
	{
		Operation(const OperationInfo& info);

		virtual ~Operation() = default;

		const OperationInfo& GetInfo() const;

		// Called by plant, when executing "Return" output using ActivateOutput function.
		virtual void Execute(int active_input_index, const std::vector<Instruction*>& active_input_values, LSystem& lsystem, Plant* plant) = 0;

		virtual void ResetState() { }

		template<class Archive>
		void serialize(Archive& archive)
		{
			archive(m_info);
		}

	protected:

		// Can call back into plant
		void ActivateOutput(int output_index, const std::vector<Instruction*>& output_values, LSystem& lsystem, Plant* plant);

	private:
		
		friend class cereal::access;

		Operation() = default;

		OperationInfo m_info;

	};

}
