#pragma once

#include <LSystem/Parameter.hpp>



namespace LSystem
{

	struct IntParameter : Parameter
	{
		IntParameter(ParameterOwner* owner, std::string_view name, int min, int max, int value);

		int min;
		int max;
		int value;

		operator int() const;

		IntParameter& operator=(int value);
	};

}
