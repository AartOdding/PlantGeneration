#include <LSystem/Parameters/ColorParameter.hpp>

using namespace LSystem;


ColorParameter::ColorParameter(ParameterOwner* owner, std::string_view name, glm::vec3 _value)
	: Parameter(owner, name)
	, value(_value)
{

}
