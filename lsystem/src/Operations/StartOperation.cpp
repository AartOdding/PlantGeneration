#include <LSystem/LSystem.hpp>



namespace LSystem
{

	StartOperation::StartOperation(OperationOwner* owner, std::string_view name)
		: Operation(owner, name)
	{

	}

	std::vector<Instruction*> StartOperation::Apply(const std::vector<Instruction*>& apply_to, LSystem& lsystem)
	{
		return { lsystem.CreateExtrusion(0, 0, 0) };
	}

	const std::string& StartOperation::Description() const
	{
		static const std::string type_name_friendly = "Start";
		return type_name_friendly;
	}

}
