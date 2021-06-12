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
	{

	}

	const OperationInfo& Operation::GetInfo() const
	{
		return m_info;
	}

	void Operation::ActivateOutput(int output_index, const std::vector<Instruction*>& output_values, LSystem& lsystem, Plant* plant)
	{
		plant->ActivateOutput(this, output_index, output_values, lsystem);
	}

}
