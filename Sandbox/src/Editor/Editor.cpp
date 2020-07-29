#ifndef SMOK_DIST

#include "Editor.h"

#include <Core\Events\EngineEvents.h>
#include <imgui.h>

using namespace std;

Entity Editor::selectedEntity("Entity");
Transform* Editor::selectedTrans = nullptr;

void Editor::Init()
{
	ECSGUIRenderEvent::AddMethod(&Editor::Draw);
}

void Editor::Shutdown()
{
	//remove from events
}

void Editor::Draw()
{
	//menu bar

	//Entity Hierarchy
	ImGui::Begin("Entity Hierarchy");
	vector<Entity> entities = EntityManager::GetAllEntities();
	for (unsigned int i = 0; i < entities.size(); i++)
	{
		if (ImGui::Button(entities[i].name.c_str()))
		{
			selectedEntity = entities[i];
			if (selectedEntity.HasComponent<Transform>())
				selectedTrans = selectedEntity.GetComponent<Transform>();
			else
				selectedTrans = nullptr;
		}
	}
	ImGui::End();

	//Selected Entity
	ImGui::Begin("Selected Entity");
	if (!selectedTrans)
		ImGui::Text("Entity: %s\nX: NA, Y: NA, Z: NA", selectedEntity.name.c_str());
	else
		ImGui::Text("Entity: %s\nX: %f, Y: %f, Z: %f", selectedEntity.name.c_str(), selectedTrans->position.x, selectedTrans->position.y, selectedTrans->position.z);

	//allows the Entity to be deleted
	if (ImGui::Button("Delete") && EntityManager::GetReg().valid(selectedEntity.entity))
		EntityManager::Destroy(selectedEntity.name);

	ImGui::End();

	//Selected Entity Inspecter
}

#endif