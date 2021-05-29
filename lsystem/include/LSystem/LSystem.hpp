#pragma once

#include <memory>
#include <string>
#include <unordered_map>

#include <LSystem/Instruction.hpp>
#include <LSystem/Rule.hpp>
#include <LSystem/VertexBuffer.hpp>


namespace LSystem
{

	VertexBuffer Generate(const Instruction* instruction);


	class LSystem
	{
	public:

		std::string starting_rule;

		std::unordered_map<std::string, std::unique_ptr<Rule>> rules;

		//VertexBuffer Generate(float iterations) const;

	private:


	};

}
