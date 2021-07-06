#include <LSystem/OperationDatabase.hpp>

#include <LSystem/Operations/ForkOperation.hpp>


namespace LSystem
{

	OperationDatabase::OperationDatabase()
	{
		m_operations.push_back(ForkOperation::info);
	}

	const std::vector<OperationInfo>& OperationDatabase::Operations() const
	{
		return m_operations;
	}

}
