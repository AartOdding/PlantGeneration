#include <LSystem/Parameters/ColorParameter.hpp>



namespace LSystem
{

	ColorParameter::ColorParameter(std::string_view name, glm::vec3 val)
		: Parameter(name)
		, value(val)
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
