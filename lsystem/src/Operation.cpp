#include <LSystem/Operation.hpp>
#include <LSystem/Plant.hpp>



namespace LSystem
{

	Operation::Operation(const OperationInfo& info)
		: m_id(Identifier<Operation>::Generate())
		, m_info(info)
	{

	}

	const OperationInfo& Operation::GetInfo() const
	{
		return m_info;
	}

	Identifier<Operation> Operation::GetID() const
	{
		return m_id;
	}

	Modifier* Operation::AddModifier(std::unique_ptr<Modifier>&& modifier)
	{
		m_modifiers_pointers.push_back(modifier.get());
		m_modifiers_pointers_const.push_back(modifier.get());
		m_modifiers_owned.push_back(std::move(modifier));
		return m_modifiers_pointers.back();
	}

	bool Operation::DeleteModifier(Identifier<Modifier> modifier)
	{
		const auto size_begin = m_modifiers_owned.size();

		m_modifiers_pointers.erase(
			std::remove_if(
				m_modifiers_pointers.begin(),
				m_modifiers_pointers.end(),
				[modifier](auto mod) { return mod->GetID() == modifier; }),
			m_modifiers_pointers.end());

		m_modifiers_pointers_const.erase(
			std::remove_if(
				m_modifiers_pointers_const.begin(),
				m_modifiers_pointers_const.end(),
				[modifier](auto op) { return op->GetID() == modifier; }),
			m_modifiers_pointers_const.end());

		m_modifiers_owned.erase(
			std::remove_if(
				m_modifiers_owned.begin(),
				m_modifiers_owned.end(),
				[modifier](const auto& mod) { return mod->GetID() == modifier; }),
			m_modifiers_owned.end());

		return m_modifiers_owned.size() < size_begin;
	}

	const std::vector<Modifier*>& Operation::Modifiers()
	{
		return m_modifiers_pointers;
	}

	const std::vector<const Modifier*>& Operation::Modifiers() const
	{
		return m_modifiers_pointers_const;
	}

	void Operation::ActivateOutput(int output_index, const std::vector<Instruction*>& output_values, Plant* plant)
	{
		plant->ActivateOutput(this, output_index, output_values);
	}

}
