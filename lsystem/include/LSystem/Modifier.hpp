#pragma once

#include <string>
#include <stdexcept>
#include <vector>

#include <LSystem/Forward.hpp>
#include <LSystem/ParameterList.hpp>

#include <LSystem/Parameters/BoolParameter.hpp>
#include <LSystem/Parameters/ColorParameter.hpp>
#include <LSystem/Parameters/FloatParameter.hpp>
#include <LSystem/Parameters/IntParameter.hpp>

#include <LSystem/Utils/Identifier.hpp>
#include <LSystem/Utils/NoCopy.hpp>
#include <LSystem/Utils/NoMove.hpp>

#include <cereal/types/polymorphic.hpp>



namespace LSystem
{

	struct ModifierInfo
	{
		std::string description;
	};
	
	struct Modifier : ParameterList, NoCopy, NoMove
	{
		Modifier(const ModifierInfo& info);

		virtual ~Modifier() = default;

		const ModifierInfo& GetInfo() const;
		Identifier<Modifier> GetID() const;

		virtual void Execute(const std::vector<Instruction*>& input_values, Plant* plant) = 0;

		virtual void ResetState() { }

		static constexpr std::uint32_t Version = 1;

		template<class Archive>
		void serialize(Archive& archive, const std::uint32_t version)
		{
			if (version > Version)
			{
				throw std::runtime_error("Error: The file you are trying to load has been created with a newer version of this software than you are currently using.");
			}
			archive(m_id);
		}

	private:

		Identifier<Modifier> m_id;
		ModifierInfo m_info;

	};

}
