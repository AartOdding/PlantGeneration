#pragma once

#include <vector>

#include <LSystem/Operation.hpp>



namespace LSystem
{

	struct OperationDatabase
	{
		OperationDatabase();

		const std::vector<OperationInfo>& Operations() const;

	private:

		std::vector<OperationInfo> m_operations;

	};

}
