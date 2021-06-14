#include <algorithm>
#include <cassert>

#include <LSystem/Parameter.hpp>



namespace LSystem
{

	Parameter::Parameter(std::string_view name)
		: m_id(Identifier<Parameter>::Generate())
		, m_name(name)
	{

	}

	const std::string& Parameter::Name() const
	{
		return m_name;
	}

	Identifier<Parameter> Parameter::GetID() const
	{
		return m_id;
	}

}
