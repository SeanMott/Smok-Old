#include <smpch.h>
#include "SceneManager.h"

#include <Core\Events\ScriptEvents.h>

using namespace std;

unsigned int SceneManager::scene = 0;
vector<Scene*> SceneManager::scenes;

void SceneManager::AddToSceneList(Scene* s)
{
	if (!s)
	{
		Logger::LogErrorAlways("Scene", "The scene that was passed in to be loaded is a nullptr.");
		return;
	}

	for (unsigned int i = 0; i < scenes.size(); i++)
	{
		if (scenes[i] == s)
		{
			Logger::LogErrorAlways("Scene", "That scene is already in the list.");
			return;
		}
	}

	scenes.emplace_back(s);
}

void SceneManager::RemoveFromSceneList(Scene* s)
{
	for (unsigned int i = 0; i < scenes.size(); i++)
	{
		if (scenes[i] == s)
		{
			vector<Scene*>::iterator it = scenes.begin() + i;
			if (i == scene)
				UnloadScene();
			delete scenes[i];
			scenes.erase(it);
		}
	}
}

void SceneManager::LoadScene(Scene* s)
{
	if (!s)
	{
		Logger::LogErrorAlways("Scene", "The scene that was passed in to be loaded is a nullptr.");
		return;
	}

	AddToSceneList(s);
	ScriptEndEvent::Call();
	scenes[scene]->OnSceneEnd();

	scene = scenes.size() - 1;
	scenes[scene]->OnSceneStart();
	ScriptStartEvent::Call();
}

void SceneManager::LoadScene(unsigned int s)
{
	if (s > scenes.size())
	{
		Logger::LogErrorAlways("Scene", to_string(s) + " is not a valid scene in the scene list.");
		return;
	}

	scene = s;

	ScriptEndEvent::Call();
	scenes[scene]->OnSceneEnd();

	scene = scenes.size() - 1;
	scenes[scene]->OnSceneStart();
	ScriptStartEvent::Call();
}

void SceneManager::UnloadScene()
{
	if (scene > scenes.size())
	{
		Logger::LogErrorAlways("Scene", "Current scene is not a valid scene in the scene list.");
		return;
	}

	scenes[scene]->OnSceneEnd();
	scene = 0;
}
