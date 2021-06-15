#pragma once

#include <LSystem/Parameter.hpp>



namespace LSystem
{

	struct IntParameter : Parameter
	{
		IntParameter(std::string_view name, int min, int max, int value);

		int min;
		int max;
		int value;

		operator int() const;

		IntParameter& operator=(int value);

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

		IntParameter() = default;

	};

}
