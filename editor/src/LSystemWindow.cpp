#include "LSystemWindow.hpp"

#include <imgui.h>


static std::string gen_random(const int len) {

	std::string tmp_s;

    static const char alphanum[] =
        "0123456789"
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz";

    tmp_s.reserve(len);

    for (int i = 0; i < len; ++i)
        tmp_s += alphanum[rand() % (sizeof(alphanum) - 1)];

    return tmp_s;
}

/*
LSystemWindow::LSystemWindow(LSystem::LSystem* lsystem)
	: m_lsystem(lsystem)
	, m_activeRule(nullptr)
{
	if (!lsystem->rules.empty())
	{
		m_activeRule = m_lsystem->rules.begin()->second.get();
	}
}

LSystem::Rule* LSystemWindow::ActiveRule()
{
	return m_activeRule;
}

void LSystemWindow::Draw()
{
	ImGui::Begin("LSystem");


	if (ImGui::Button("Create Rule"))
	{
		auto id = gen_random(4);
		auto rule = std::make_unique<LSystem::Rule>();
		rule->id = id;
		m_lsystem->rules.emplace(id, std::move(rule));
	}

	if (ImGui::BeginCombo("Active Rule", m_activeRule ? m_activeRule->id.c_str() : nullptr))
	{
		for (auto& [id, rule] : m_lsystem->rules)
		{
			ImGui::Selectable(id.c_str(), rule.get() == m_activeRule);
		}

		ImGui::EndCombo();
	}

	ImGui::Text("Rules");

	for (auto& [id, rule] : m_lsystem->rules)
	{
		DrawRule(rule.get());
	}


	ImGui::End();
}

void LSystemWindow::DrawRule(LSystem::Rule* rule)
{
	ImGui::CollapsingHeader(rule->id.c_str());
}

*/