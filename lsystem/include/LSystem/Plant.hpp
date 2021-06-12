#pragma once

#include <memory>
#include <string_view>
#include <unordered_set>
#include <utility>
#include <vector>

#include <LSystem/Forward.hpp>
#include <LSystem/VertexBuffer.hpp>



namespace LSystem
{

	struct Connection
	{
		Operation* const output;
		Operation* const input;
		const int output_index;
		const int input_index;

		bool operator==(const Connection& other) const
		{
			return output == other.output && input == other.input
				&& output_index == other.output_index && input_index == other.input_index;
		}
	};

}

template <typename SizeT>
inline void hash_combine_impl(SizeT& seed, SizeT value)
{
	seed ^= value + 0x9e3779b9 + (seed << 6) + (seed >> 2);
}

namespace std
{
	template <>
	struct hash<LSystem::Connection>
	{
		std::size_t operator()(const LSystem::Connection& c) const
		{
			auto h1 = std::hash<LSystem::Operation*>()(c.output);
			auto h2 = std::hash<LSystem::Operation*>()(c.input);
			auto h3 = std::hash<int>()(c.output_index);
			auto h4 = std::hash<int>()(c.input_index);
			size_t result = 0;
			hash_combine_impl(result, h1);
			hash_combine_impl(result, h2);
			hash_combine_impl(result, h3);
			hash_combine_impl(result, h4);
			return result;
		}
	};
}


namespace LSystem
{

	struct Plant
	{
		Plant();

		Operation* AddOperation(std::unique_ptr<Operation>&& operation);
		bool DeleteOperation(Operation* operation);

		const std::vector<Operation*>& Operations();
		const std::vector<const Operation*>& Operations() const;

		bool CreateConnection(Operation* output, int output_index, Operation* input, int input_index);
		bool DeleteConnection(Operation* output, int output_index, Operation* input, int input_index);
		bool AreConnected(Operation* output, int output_index, Operation* input, int input_index) const;

		const std::unordered_set<Connection>& Connections() const;

		VertexBuffer Generate();

		void ActivateOutput(Operation* output, int output_index, const std::vector<Instruction*>& output_values, LSystem& lsystem);

	private:

		std::vector<Connection> GetConnectionsTo(Operation* output, int output_index);

		std::unordered_set<Connection> m_connections;
		std::vector<std::unique_ptr<Operation>> m_operations_owned;
		std::vector<Operation*> m_operation_pointers;
		std::vector<const Operation*> m_operation_pointers_const;

		Operation* m_start_operation;

	};

}
