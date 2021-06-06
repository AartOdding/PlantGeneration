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

	struct Operation : ParameterOwner
	{
		Operation(OperationOwner* owner, std::string_view name);

		virtual ~Operation();

		Operation() = delete;
		Operation(const Operation&) = delete;
		Operation(Operation&) = delete;
		Operation& operator=(const Operation&) = delete;
		Operation& operator=(Operation&&) = delete;

		const std::string name;

		virtual std::vector<Instruction*> Apply(const std::vector<Instruction*>& apply_to, LSystem& lsystem) = 0;
		virtual const std::string& Description() const = 0;

	private:

		OperationOwner* owner;

	};

}
