#pragma once

#include <glm/glm.hpp>

#include <LSystem/Parameter.hpp>



namespace LSystem
{

	struct BoolParameter : Parameter
	{
		BoolParameter(ParameterOwner* owner, std::string_view name, bool value);

		bool value;

		operator bool() const;

		BoolParameter& operator=(bool value);
	};

}
