#include <algorithm>
#include <cassert>

#include <LSystem/LSystem.hpp>



namespace LSystem
{

	Operation::Operation(OperationOwner* _owner, std::string_view _name)
		: owner(_owner)
		, name(_name)
	{
		assert(owner);

		if (owner)
		{
			owner->m_operations.push_back(this);
		}
	}

	Operation::~Operation()
	{
		if (owner)
		{
			owner->m_operations.erase(
				std::remove(
					owner->m_operations.begin(),
					owner->m_operations.end(), this),
				owner->m_operations.end());
		}
	}

}
