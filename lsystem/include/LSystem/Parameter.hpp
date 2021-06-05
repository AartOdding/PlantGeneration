#pragma once

#include <string>
#include <string_view>



namespace LSystem
{

	struct ParameterOwner;

	struct Parameter
	{
		Parameter(ParameterOwner* owner, std::string_view name);

		virtual ~Parameter();

		Parameter() = delete;
		Parameter(const Parameter&) = delete;
		Parameter(Parameter&) = delete;
		Parameter& operator=(const Parameter&) = delete;
		Parameter& operator=(Parameter&&) = delete;

		const std::string name;

	private:

		ParameterOwner* owner;
    };

}
