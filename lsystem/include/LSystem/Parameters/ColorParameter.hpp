#pragma once

#include <glm/glm.hpp>

#include <LSystem/Parameter.hpp>



namespace LSystem
{

	struct ColorParameter : Parameter
	{
		ColorParameter(std::string_view name, glm::vec3 value);

		glm::vec3 value;

		operator glm::vec3() const;
		
		ColorParameter& operator=(const glm::vec3& value);

		template<class Archive>
		void serialize(Archive& archive)
		{
			archive(cereal::base_class<Parameter>(this), value);
		}

	private:

		friend cereal::access;

		ColorParameter() = default;

	};

}
