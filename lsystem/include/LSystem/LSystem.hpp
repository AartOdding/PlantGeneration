#pragma once

#include <memory>
#include <string>
#include <unordered_map>

#include <LSystem/Instruction.hpp>
#include <LSystem/BranchInstruction.hpp>
#include <LSystem/MoveInstruction.hpp>
#include <LSystem/RecurseInstruction.hpp>

#include <LSystem/Rule.hpp>
#include <LSystem/RuleSet.hpp>

#include <LSystem/RenderBuffer.hpp>
#include <LSystem/TreeModel.hpp>


namespace LSystem
{

	RenderBuffer Generate(const Branch* branch);


	class LSystem
	{
	public:

		std::string starting_rule;

		std::unordered_map<std::string, std::unique_ptr<Rule>> rules;

		RenderBuffer Generate(float iterations) const;

	private:


	};

}
