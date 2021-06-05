#pragma once

#include <string>
#include <string_view>

#include <glm/glm.hpp>


namespace LSystem
{
    struct ParameterOwner;

	struct IParameter
	{
		IParameter(ParameterOwner* owner, std::string_view name);

		virtual ~IParameter();

		IParameter() = delete;
		IParameter(const IParameter&) = delete;
		IParameter(IParameter&) = delete;
		IParameter& operator=(const IParameter&) = delete;
		IParameter& operator=(IParameter&&) = delete;

		const std::string name;

	private:

		ParameterOwner* owner;
    };

    struct FloatParameter : IParameter
	{
		FloatParameter(ParameterOwner* owner, std::string_view name, float min, float max, float value);

		float min;
		float max;
		float value;

		operator float() const { return value; }
	};

	struct IntParameter : IParameter
	{
		IntParameter(ParameterOwner* owner, std::string_view name, int min, int max, int value);

		int min;
		int max;
		int value;

		operator int() const { return value; }
	};

	struct ColorParameter : IParameter
	{
		ColorParameter(ParameterOwner* owner, std::string_view name, glm::vec3 value);

		glm::vec3 value;

		operator glm::vec3() const { return value; }
	};
}
