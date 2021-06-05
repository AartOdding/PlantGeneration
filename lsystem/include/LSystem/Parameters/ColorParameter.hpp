#pragma once

#include <glm/glm.hpp>

#include <LSystem/Parameter.hpp>



namespace LSystem
{

	struct ColorParameter : Parameter
	{
		ColorParameter(ParameterOwner* owner, std::string_view name, glm::vec3 value);

		glm::vec3 value;

		operator glm::vec3() const { return value; }
	};

}
