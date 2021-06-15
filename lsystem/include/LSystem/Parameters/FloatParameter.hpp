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

		static constexpr std::uint32_t Version = 1;

		template<class Archive>
		void serialize(Archive& archive, const std::uint32_t version)
		{
			if (version > Version)
			{
				throw std::runtime_error("Error: The file you are trying to load has been created with a newer version of this software than you are currently using.");
			}
			archive(cereal::base_class<Parameter>(this), min, max, value);
		}

	private:

		friend cereal::access;

		FloatParameter() = default;

	};

}
