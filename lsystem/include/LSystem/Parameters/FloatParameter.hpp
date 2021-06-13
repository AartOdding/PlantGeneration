#pragma once

#include <LSystem/Parameter.hpp>



namespace LSystem
{

	struct FloatParameter : Parameter
	{
		FloatParameter(std::string_view name, float min, float max, float value);

		float min;
		float max;
		float value;

		operator float() const;

		FloatParameter& operator=(float value);

		template<class Archive>
		void serialize(Archive& archive)
		{
			archive(min, max, value, m_name);
		}

	private:

		friend cereal::access;

		FloatParameter() = default;

	};

}
