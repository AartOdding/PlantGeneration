#pragma once

#include <string>
#include <string_view>
#include <vector>

#include <LSystem/Forward.hpp>
#include <LSystem/ParameterOwner.hpp>

#include <LSystem/Parameters/ColorParameter.hpp>
#include <LSystem/Parameters/FloatParameter.hpp>
#include <LSystem/Parameters/IntParameter.hpp>



namespace LSystem
{

	struct OperationInfo
	{
		int input_count;
		int output_count;
		std::string description;
	};

	struct Operation : ParameterOwner
	{
		Operation(Plant* plant);

		virtual ~Operation();

		Operation() = delete;
		Operation(const Operation&) = delete;
		Operation(Operation&) = delete;
		Operation& operator=(const Operation&) = delete;
		Operation& operator=(Operation&&) = delete;

		// OperationInfo is not allowed to change between calls.
		virtual OperationInfo GetInfo() const = 0;

		// Called by plant, when executing "Return" output using ActivateOutput function.
		virtual void Execute(int active_input_index, const std::vector<Instruction*>& active_input_values, LSystem& lsystem) { };

		virtual std::vector<Instruction*> Apply(const std::vector<Instruction*>& apply_to, LSystem& lsystem) = 0;

	protected:

		// Can call back into plant
		void ActivateOutput(int output_index, const std::vector<Instruction*>& output_values);

	private:

		Plant* m_plant;

	};

}
