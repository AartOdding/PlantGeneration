#include <algorithm>
#include <cassert>

#include <LSystem/LSystem.hpp>



namespace LSystem
{

	struct ExecutionContext
	{
		Plant* plant;
	};

	Operation::Operation(const OperationInfo& info)
		: m_id(Identifier<Operation>::Generate())
		, m_info(info)
	{

	}

	const OperationInfo& Operation::GetInfo() const
	{
		return m_info;
	}

	Identifier<Operation> Operation::GetID() const
	{
		return m_id;
	}

	bool Operation::AddParameter(Parameter& parameter)
	{
		auto par = std::find(m_parameters.begin(), m_parameters.end(), &parameter);

		if (par == m_parameters.end())
		{
			m_parameters.push_back(&parameter);
			m_const_parameters.push_back(&parameter);
			return true;
		}
		return false;
	}

	bool Operation::RemoveParameter(Parameter& parameter)
	{
		auto par = std::find(m_parameters.begin(), m_parameters.end(), &parameter);
		auto par_const = std::find(m_const_parameters.begin(), m_const_parameters.end(), &parameter);

		if (par != m_parameters.end())
		{
			m_parameters.erase(par);
			m_const_parameters.erase(par_const);
			return true;
		}
		return false;
	}

	const std::vector<Parameter*>& Operation::Parameters()
	{
		return m_parameters;
	}

	const std::vector<const Parameter*>& Operation::Parameters() const
	{
		return m_const_parameters;
	}

	void Operation::ActivateOutput(int output_index, const std::vector<Instruction*>& output_values, InstructionPool& lsystem, Plant* plant)
	{
		plant->ActivateOutput(this, output_index, output_values, lsystem);
	}

}
