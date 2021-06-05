#pragma once

#include <LSystem/Parameter.hpp>



namespace LSystem
{

	struct FloatParameter : Parameter
	{
		FloatParameter(ParameterOwner* owner, std::string_view name, float min, float max, float value);

		float min;
		float max;
		float value;

		operator float() const;

		FloatParameter& operator=(float value);
	};

}
