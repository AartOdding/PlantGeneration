#include <algorithm>
#include <cassert>

#include <LSystem/LSystem.hpp>


namespace LSystem
{

	Parameter::Parameter(std::string_view name)
		: m_name(name)
	{

	}

	const std::string& Parameter::Name() const
	{
		return m_name;
	}

}
