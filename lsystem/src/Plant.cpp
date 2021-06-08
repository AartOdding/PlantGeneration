#include <algorithm>

#include <LSystem/LSystem.hpp>



namespace LSystem
{

	Plant::Plant()
	{
		m_operations_owned.push_back(std::make_unique<StartOperation>(this));
		m_start_operation = m_operations_owned.back().get();
	}

	Operation* Plant::AddOperation(std::unique_ptr<Operation>&& operation)
	{
		m_operations_owned.push_back(std::move(operation));
		return m_operations_owned.back().get();
	}

	bool Plant::DeleteOperation(Operation* operation)
	{
		const auto size_begin = m_operations_owned.size();

		m_operations_owned.erase(
			std::remove_if(
				m_operations_owned.begin(), 
				m_operations_owned.end(), 
				[operation](const auto& op) { return op.get() == operation; }), 
			m_operations_owned.end());

		return m_operations_owned.size() < size_begin;
	}

	bool Plant::CreateConnection(Operation* output, int output_index, Operation* input, int input_index)
	{
		if (m_connections.count(Connection{ output, input, output_index, input_index }) == 0)
		{
			m_connections.emplace(Connection{ output, input, output_index, input_index });
			return true;
		}
		return false;
	}

	bool Plant::DeleteConnection(Operation* output, int output_index, Operation* input, int input_index)
	{
		if (m_connections.count(Connection{ output, input, output_index, input_index }) > 0)
		{
			m_connections.erase(Connection{ output, input, output_index, input_index });
			return true;
		}
		return false;
	}

	bool Plant::AreConnected(Operation* output, int output_index, Operation* input, int input_index) const
	{
		return m_connections.count(Connection{ output, input, output_index, input_index });
	}

	const std::unordered_set<Connection>& Plant::Connections() const
	{
		return m_connections;
	}

	std::vector<Instruction*> Plant::ExecuteOperation(Operation* operation, const std::vector<Instruction*>& instructions, LSystem& lsystem)
	{
		auto new_instructions = operation->Apply(instructions, lsystem);
		auto next_ops = GetNextOperations(operation);

		for (auto op : next_ops)
		{
			ExecuteOperation(op, new_instructions, lsystem);
		}

		return new_instructions;
	}

	VertexBuffer Plant::Generate()
	{
		LSystem lsystem;

		auto start = ExecuteOperation(m_start_operation, {}, lsystem);

		return ::LSystem::Generate(start[0], 1);
	}


	std::vector<Operation*> Plant::GetNextOperations(Operation* operation)
	{
		std::vector<Operation*> next_operations;

		for (auto& c : m_connections)
		{
			if (c.output == operation)
			{
				next_operations.push_back(c.input);
			}
		}

		return next_operations;
	}
}
