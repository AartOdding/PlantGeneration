#pragma once

#include <string>
#include <string_view>

#include <LSystem/Utils/NoCopy.hpp>
#include <LSystem/Utils/NoMove.hpp>



namespace LSystem
{

	struct Parameter : NoCopy,
		               NoMove
	{
		Parameter(std::string_view name);

		virtual ~Parameter() = default;
		
		const std::string& name() const;

	private:

		Parameter() = default;
		
		std::string m_name;

    };

}
