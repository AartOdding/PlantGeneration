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
		: m_info(info)
		, m_id(Identifier<Operation>::Generate())
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

	void Operation::ActivateOutput(int output_index, const std::vector<Instruction*>& output_values, InstructionPool& lsystem, Plant* plant)
	{
		plant->ActivateOutput(this, output_index, output_values, lsystem);
	}

}
