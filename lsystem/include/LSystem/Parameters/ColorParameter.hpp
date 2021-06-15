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

		static constexpr std::uint32_t Version = 1;

		template<class Archive>
		void serialize(Archive& archive, const std::uint32_t version)
		{
			if (version > Version)
			{
				throw std::runtime_error("Error: The file you are trying to load has been created with a newer version of this software than you are currently using.");
			}
			archive(cereal::base_class<Parameter>(this), value);
		}

	private:

		friend cereal::access;

		ColorParameter() = default;

	};

}
