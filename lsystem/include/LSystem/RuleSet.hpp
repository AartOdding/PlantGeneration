#pragma once

#include <memory>
#include <string>
#include <unordered_map>

#include <LSystem/Rule.hpp>


namespace LSystem
{

	class RuleSet
	{
	public:

		std::unordered_map<std::string, std::unique_ptr<Rule>> rules;

	private:

	};

}
