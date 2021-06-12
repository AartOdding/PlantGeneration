#pragma once

#include <memory>
#include <vector>

#include <glm/glm.hpp>

#include <LSystem/Instruction.hpp>
#include <LSystem/Operation.hpp>
#include <LSystem/Parameter.hpp>
#include <LSystem/ParameterOwner.hpp>
#include <LSystem/Plant.hpp>
#include <LSystem/VertexBuffer.hpp>

#include <LSystem/Operations/ColoringOperation.hpp>
#include <LSystem/Operations/ExtrudeOperation.hpp>
#include <LSystem/Operations/FanOperation.hpp>
#include <LSystem/Operations/ForkOperation.hpp>
#include <LSystem/Operations/LoopOperation.hpp>
#include <LSystem/Operations/PhyllotaxisOperation.hpp>
#include <LSystem/Operations/RadiusOperation.hpp>
#include <LSystem/Operations/RandomColorOperation.hpp>
#include <LSystem/Operations/RandomLengthOperation.hpp>
#include <LSystem/Operations/ScaleOperation.hpp>
#include <LSystem/Operations/StartOperation.hpp>

#include <LSystem/Parameters/BoolParameter.hpp>
#include <LSystem/Parameters/ColorParameter.hpp>
#include <LSystem/Parameters/FloatParameter.hpp>
#include <LSystem/Parameters/IntParameter.hpp>

#include <LSystem/Utils/Identifier.hpp>
#include <LSystem/Utils/NoCopy.hpp>
#include <LSystem/Utils/NoMove.hpp>
#include <LSystem/Utils/Serialization.hpp>



namespace LSystem
{

	struct LSystem
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
