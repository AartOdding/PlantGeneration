#pragma once

#include <glm/glm.hpp>

#include <LSystem/Parameter.hpp>



namespace LSystem
{

	struct BoolParameter : Parameter
	{
		BoolParameter(std::string_view name, bool value);

		bool value;

		operator bool() const;

		BoolParameter& operator=(bool value);

		template<class Archive>
		void serialize(Archive& archive)
		{
			archive(value, m_name);
		}

	private:

		friend cereal::access;

		BoolParameter() = default;

	};

}
