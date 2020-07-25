#include <smpch.h>
#include "SceneManager.h"

#include <Core\Events\ScriptEvents.h>

Scene* SceneManager::scene = nullptr;

void SceneManager::LoadScene(Scene* s)
{
	if (!s)
	{
		Logger::LogErrorAlways("Scene", "The scene that was passed in to be loaded is a nullptr.");
		return;
	}

	if (scene)
	{
		ScriptEndEvent::Call();
		scene->OnSceneEnd();
	}

	scene = s;
	scene->OnSceneStart();
	ScriptStartEvent::Call();
}

void SceneManager::UnloadScene()
{
	if (scene)
		scene->OnSceneEnd();

	scene = nullptr;
}
