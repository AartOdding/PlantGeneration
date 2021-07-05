#include <LSystem/Modifier.hpp>
#include <LSystem/Plant.hpp>



namespace LSystem
{

	Modifier::Modifier(const ModifierInfo& info)
		: m_id(Identifier<Operation>::Generate())
		, m_info(info)
	{

	}

	const ModifierInfo& Modifier::GetInfo() const
	{
		return m_info;
	}

	Identifier<Modifier> Modifier::GetID() const
	{
		return m_id;
	}

}
