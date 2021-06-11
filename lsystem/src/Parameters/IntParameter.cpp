#include <LSystem/Parameters/IntParameter.hpp>



namespace LSystem
{

	IntParameter::IntParameter(std::string_view name, int minimum, int maximum, int val)
		: Parameter(name)
		, min(minimum)
		, max(maximum)
		, value(val)
	{

	}

	IntParameter::operator int() const
	{
		return value;
	}

	IntParameter& IntParameter::operator=(int _value)
	{
		value = _value;
		return *this;
	}

}
