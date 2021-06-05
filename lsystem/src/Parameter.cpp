#include <algorithm>
#include <cassert>

#include <LSystem/LSystem.hpp>


namespace LSystem
{

	Parameter::Parameter(ParameterOwner* _owner, std::string_view _name)
		: owner(_owner)
		, name(_name)
	{
		assert(owner);

		if (owner)
		{
			owner->m_parameters.push_back(this);
		}
	}

	Parameter::~Parameter()
	{
		if (owner)
		{
			owner->m_parameters.erase(
				std::remove(
					owner->m_parameters.begin(),
					owner->m_parameters.end(), this),
				owner->m_parameters.end());
		}
	}

}
