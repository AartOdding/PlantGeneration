#pragma once

#include <memory>
#include <string>
#include <string_view>
#include <unordered_map>

#include <glm/glm.hpp>

#include <LSystem/Instruction.hpp>
#include <LSystem/Operation.hpp>
#include <LSystem/OperationOwner.hpp>
#include <LSystem/Parameter.hpp>
#include <LSystem/ParameterOwner.hpp>
#include <LSystem/VertexBuffer.hpp>

#include <LSystem/Operations/ColoringOperation.hpp>
#include <LSystem/Operations/ExtrudeOperation.hpp>
#include <LSystem/Operations/FanOperation.hpp>
#include <LSystem/Operations/ForkOperation.hpp>
#include <LSystem/Operations/PhyllotaxisOperation.hpp>

#include <LSystem/Parameters/ColorParameter.hpp>
#include <LSystem/Parameters/FloatParameter.hpp>
#include <LSystem/Parameters/IntParameter.hpp>



namespace LSystem
{

	VertexBuffer Generate(const Instruction* data, int recursions);


	struct LSystem
	{
		Instruction* begin = nullptr;

		Instruction* CreateExtrusion(float length, float roll, float pitch);

		std::vector<Instruction*> CreateBase(float length);

		/*
		std::vector<Instruction*> CreateRecursion(Instruction* rule, float scale = 1, float roll = 0, float pitch = 0);
		std::vector<Instruction*> CreateRecursion(const std::vector<Instruction*>& onto, Instruction* rule, float scale = 1, float roll = 0, float pitch = 0);

		std::vector<Instruction*> CreateRecursingFork(Instruction* rule, int count, float scale = 1, float roll = 0, float pitch = glm::quarter_pi<float>());
		std::vector<Instruction*> CreateRecursingFork(const std::vector<Instruction*>& onto, Instruction* rule, int count, float scale = 1, float roll = 0, float pitch = glm::quarter_pi<float>());

		std::vector<Instruction*> CreateRecursingFan(Instruction* rule, int count, float spread = glm::quarter_pi<float>(), float scale = 1, float roll = 0);
		std::vector<Instruction*> CreateRecursingFan(const std::vector<Instruction*>& onto, Instruction* rule, int count, float spread = glm::quarter_pi<float>(), float scale = 1, float roll = 0);
		*/
	private:

		InstructionData* AddInstructionData();
		Instruction* AddInstruction(InstructionData* data);

		std::vector<std::unique_ptr<Instruction>> m_instructions;
		std::vector<std::unique_ptr<InstructionData>> m_instructionDatas;

	};

}
