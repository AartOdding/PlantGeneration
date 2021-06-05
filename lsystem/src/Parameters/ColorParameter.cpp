#include <LSystem/Parameters/ColorParameter.hpp>



namespace LSystem
{

	ColorParameter::ColorParameter(ParameterOwner* owner, std::string_view name, glm::vec3 _value)
		: Parameter(owner, name)
		, value(_value)
	{

	}

	ColorParameter::operator glm::vec3() const
	{
		return value;
	}

	ColorParameter& ColorParameter::operator=(const glm::vec3& _value)
	{
		value = _value;
		return *this;
	}

}
