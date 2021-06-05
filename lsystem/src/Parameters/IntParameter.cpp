#include <LSystem/Parameters/IntParameter.hpp>



namespace LSystem
{

	IntParameter::IntParameter(ParameterOwner* owner, std::string_view name, int _min, int _max, int _value)
		: Parameter(owner, name)
		, min(_min)
		, max(_max)
		, value(_value)
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
