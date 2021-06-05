#include <LSystem/LSystem.hpp>


namespace LSystem
{

	const std::vector<Operation*>& OperationOwner::Operations()
	{
		return m_operations;
	}
}

