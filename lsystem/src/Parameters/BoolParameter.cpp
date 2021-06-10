#include <LSystem/Parameters/BoolParameter.hpp>



namespace LSystem
{

	BoolParameter::BoolParameter(ParameterOwner* owner, std::string_view name, bool val)
		: Parameter(owner, name)
		, value(val)
	{

	}

	BoolParameter::operator bool() const
	{
		return value;
	}

	BoolParameter& BoolParameter::operator=(bool val)
	{
		value = val;
		return *this;
	}

}
