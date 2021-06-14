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

		template<class Archive>
		void serialize(Archive& archive)
		{
			archive(cereal::base_class<Parameter>(this), min, max, value);
		}

	private:

		friend cereal::access;

		IntParameter() = default;

	};

}
