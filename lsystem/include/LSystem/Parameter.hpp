#pragma once

#include <string>
#include <string_view>

#include <LSystem/Utils/Identifier.hpp>
#include <LSystem/Utils/NoCopy.hpp>
#include <LSystem/Utils/NoMove.hpp>

#include <cereal/access.hpp>
#include <cereal/types/polymorphic.hpp>



namespace LSystem
{

	struct Parameter : NoCopy, NoMove
	{
		Parameter(std::string_view name);

		virtual ~Parameter() = 0 { }
		
		const std::string& Name() const;
		Identifier<Parameter> GetID() const;

		static constexpr std::uint32_t Version = 1;

		template<class Archive>
		void serialize(Archive& archive, const std::uint32_t version)
		{
			if (version > Version)
			{
				throw std::runtime_error("Error: The file you are trying to load has been created with a newer version of this software than you are currently using.");
			}
			archive(m_id, m_name);
		}

	protected:

		Parameter() = default;

	private:

		Identifier<Parameter> m_id;
		std::string m_name;

    };

}
