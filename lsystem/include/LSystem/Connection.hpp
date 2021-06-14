#pragma once

#include <LSystem/Forward.hpp>
#include <LSystem/Utils/Hash.hpp>
#include <LSystem/Utils/Identifier.hpp>



namespace LSystem
{

	struct Connection
	{
		Identifier<Operation> output;
		Identifier<Operation> input;
		int output_index;
		int input_index;

		Connection()
			: output()
			, input()
			, output_index(-1)
			, input_index(-1)
		{

		}

		Connection(Identifier<Operation> o, int oi, Identifier<Operation> i, int ii)
			: output(o)
			, input(i)
			, output_index(oi)
			, input_index(ii)
		{

		}

		bool operator==(const Connection& other) const
		{
			return output == other.output && input == other.input
				&& output_index == other.output_index && input_index == other.input_index;
		}

		static constexpr std::uint32_t Version = 1;

		template <typename Archive>
		void serialize(Archive& archive, const std::uint32_t version)
		{
			if (version > Version)
			{
				throw std::runtime_error("Error: The file you are trying to load has been created with a newer version of this software than you are currently using.");
			}
			archive(output, input, output_index, input_index);
		}

	};

}

namespace std
{
	template <>
	struct hash<LSystem::Connection>
	{
		std::size_t operator()(const LSystem::Connection& c) const
		{
			size_t hash_value = 0;
			LSystem::AddToHash(hash_value, std::hash<LSystem::Identifier<LSystem::Operation>>()(c.output));
			LSystem::AddToHash(hash_value, std::hash<LSystem::Identifier<LSystem::Operation>>()(c.input));
			LSystem::AddToHash(hash_value, std::hash<int>()(c.output_index));
			LSystem::AddToHash(hash_value, std::hash<int>()(c.input_index));
			return hash_value;
		}
	};
}
