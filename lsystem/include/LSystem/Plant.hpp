#pragma once

#include <memory>
#include <string_view>
#include <unordered_set>
#include <utility>
#include <vector>

#include <LSystem/Forward.hpp>
#include <LSystem/VertexBuffer.hpp>
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

		template <class Archive>
		void serialize(Archive& ar) const
		{
			ar(output, input, output_index, input_index);
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
			auto h1 = std::hash<LSystem::Identifier<LSystem::Operation>>()(c.output);
			auto h2 = std::hash<LSystem::Identifier<LSystem::Operation>>()(c.input);
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
		bool DeleteOperation(Identifier<Operation> operation);

		const std::vector<Operation*>& Operations();
		const std::vector<const Operation*>& Operations() const;

		Operation* GetOperation(Identifier<Operation> operation);
		const Operation* GetOperation(Identifier<Operation> operation) const;

		bool AddConnection(const Connection& connection);
		bool DeleteConnection(const Connection& connection);

		const std::unordered_set<Connection>& Connections() const;

		void Clear();

		VertexBuffer Generate();

		void ActivateOutput(Operation* output, int output_index, const std::vector<Instruction*>& output_values, InstructionPool& lsystem);

	private:

		std::vector<std::pair<Operation*, int>> GetConnectedOperations(Operation* output, int output_index);

		std::vector<std::unique_ptr<Operation>> m_operations_owned;
		std::vector<Operation*> m_operation_pointers;
		std::vector<const Operation*> m_operation_pointers_const;

		std::unordered_set<Connection> m_connections;

	public:

		template <class Archive>
		void save(Archive& ar) const
		{
			ar(m_operations_owned);
		}

		template <class Archive>
		void load(Archive& ar)
		{
			Clear();

			ar(m_operations_owned);
			m_operation_pointers.reserve(m_operations_owned.size());
			m_operation_pointers_const.reserve(m_operations_owned.size());

			for (auto& op : m_operations_owned)
			{
				m_operation_pointers.push_back(op.get());
				m_operation_pointers_const.push_back(op.get());
			}
		}

	};

}
