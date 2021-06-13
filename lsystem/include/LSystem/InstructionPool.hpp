#pragma once

#include <memory>
#include <vector>

#include <LSystem/Forward.hpp>
#include <LSystem/VertexBuffer.hpp>



namespace LSystem
{

	struct InstructionPool
	{
		Instruction* first_instruction = nullptr;

		Instruction* CreateExtrusion(float length, float roll, float pitch);

		VertexBuffer Generate(int recursions); // Start from first_instruction

	private:

		InstructionData* AddInstructionData();
		Instruction* AddInstruction(InstructionData* data);

		std::vector<std::unique_ptr<Instruction>> m_instructions;
		std::vector<std::unique_ptr<InstructionData>> m_instructionDatas;

	};

}
