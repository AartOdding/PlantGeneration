#include <LSystem/Parameters/FloatParameter.hpp>



namespace LSystem
{

	FloatParameter::FloatParameter(ParameterOwner* owner, std::string_view name, float _min, float _max, float _value)
		: Parameter(owner, name)
		, min(_min)
		, max(_max)
		, value(_value)
	{

	}

	FloatParameter::operator float() const
	{
		return value;
	}

	FloatParameter& FloatParameter::operator=(float _value)
	{
		value = _value;
		return *this;
	}

}
