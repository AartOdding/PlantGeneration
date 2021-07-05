#include <LSystem/Operation.hpp>
#include <LSystem/Plant.hpp>



namespace LSystem
{

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

	void Operation::ActivateOutput(int output_index, const std::vector<Instruction*>& output_values, Plant* plant)
	{
		plant->ActivateOutput(this, output_index, output_values);
	}

}
