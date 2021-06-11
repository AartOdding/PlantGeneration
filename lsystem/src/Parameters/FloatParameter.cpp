#include <LSystem/Parameters/FloatParameter.hpp>



namespace LSystem
{

	FloatParameter::FloatParameter(std::string_view name, float minimum, float maximum, float val)
		: Parameter(name)
		, min(minimum)
		, max(maximum)
		, value(val)
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
