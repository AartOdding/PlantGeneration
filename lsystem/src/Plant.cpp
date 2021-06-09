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

	VertexBuffer Plant::Generate()
	{
		LSystem lsystem;

		for (auto& op : m_operations_owned)
		{
			op->ResetState();
		}

		m_start_operation->Execute(0, {}, lsystem);

		//auto start = ExecuteOperation(m_start_operation, {}, lsystem);

		return lsystem.Generate(1);
	}

	void Plant::ActivateOutput(Operation* output, int output_index, const std::vector<Instruction*>& output_values, LSystem& lsystem)
	{
		auto next = GetConnectionsTo(output, output_index);

		for (auto& n : next)
		{
			n.input->Execute(n.input_index, output_values, lsystem);
		}
	}

	std::vector<Connection> Plant::GetConnectionsTo(Operation* output, int output_index)
	{
		std::vector<Connection> connections;

		for (auto& c : m_connections)
		{
			if (c.output == output && c.output_index == output_index)
			{
				connections.push_back(c);
			}
		}

		return connections;
	}
}
