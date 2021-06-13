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

	struct Plant
	{
		Plant();

		Operation* AddOperation(std::unique_ptr<Operation>&& operation);
		bool DeleteOperation(Identifier<Operation> operation);

		const std::vector<Operation*>& Operations();
		const std::vector<const Operation*>& Operations() const;

		Operation* GetOperation(Identifier<Operation> operation);
		const Operation* GetOperation(Identifier<Operation> operation) const;

		StartOperation* GetStartOperation();
		const StartOperation* GetStartOperation() const;

		bool AddConnection(const Connection& connection);
		bool DeleteConnection(const Connection& connection);

		const std::unordered_set<Connection>& Connections() const;

		void Clear();
		void SaveTo(std::ostream& output_stream) const;
		void LoadFrom(std::istream& input_stream);

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
			ar(m_operations_owned, m_connections);
		}

		template <class Archive>
		void load(Archive& ar)
		{
			Clear();

			ar(m_operations_owned, m_connections);
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
