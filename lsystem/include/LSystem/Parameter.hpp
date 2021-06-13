#pragma once

#include <string>
#include <string_view>

#include <cereal/access.hpp>



namespace LSystem
{

	struct Parameter
	{
		Parameter(std::string_view name);

		virtual ~Parameter() = 0 { }
		
		const std::string& Name() const;

	protected:

		Parameter() = default;

		std::string m_name;

    };

}
