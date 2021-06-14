#pragma once

#include <cstdint>
#include <functional>
#include <iostream>
#include <type_traits>
#include <string>



namespace LSystem
{

	template<typename Type>
	struct Identifier
	{
		static_assert(std::is_same_v<Type, std::remove_cv_t<Type>>);

		static Identifier Generate()
		{
			extern std::atomic_uint64_t lsystem_detail_next_id;
			return Identifier(lsystem_detail_next_id.fetch_add(1, std::memory_order_relaxed));
		}

		explicit Identifier(std::uint64_t id) : m_id(id) { }

		Identifier() = default;
		Identifier(const Identifier&) = default;
		Identifier& operator=(const Identifier&) = default;

		bool operator==(Identifier rhs) const { return m_id == rhs.m_id; }
		bool operator!=(Identifier rhs) const { return m_id != rhs.m_id; }
		bool operator<(Identifier rhs) const { return m_id < rhs.m_id; }
		bool operator>(Identifier rhs) const { return m_id > rhs.m_id; }
		bool operator<=(Identifier rhs) const { return m_id <= rhs.m_id; }
		bool operator>=(Identifier rhs) const { return m_id >= rhs.m_id; }

		explicit operator std::uint64_t() const { return m_id; }

		operator bool() const { return m_id != 0; }

	private:

		std::uint64_t m_id = 0;

	public:

		template <typename Archive>
		void serialize(Archive& archive)
		{
			// Because Identifier is a class template, and not a concrete class it is unfortunately not possible to specify a version
			// using the CEREAL_CLASS_VERSION() macro. For this reason it is impossible to ever create new versions of this struct
			// and maintain backwards compatibility! The best is nover to change the layout.
			archive(m_id);
		}

	};

	static_assert(sizeof(Identifier<bool>) == sizeof(std::uint64_t), "To maintain backwards compatibility the layout of Identifier is not allowed to change.");
}

namespace std
{
	template<typename Type>
	struct hash<LSystem::Identifier<Type>>
	{
		std::size_t operator()(const LSystem::Identifier<Type>& id) const noexcept
		{
			return hash<std::uint64_t>()(static_cast<std::uint64_t>(id));
		}
	};
}

template<typename Type>
std::ostream& operator<<(std::ostream& os, LSystem::Identifier<Type> const& id)
{
	return os << "<" << static_cast<std::uint64_t>(id) << ">";
}
