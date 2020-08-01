#include <smpch.h>
#include "SceneManager.h"

#include <Core\Events\ScriptEvents.h>

using namespace std;

string SceneManager::scene = "";
unordered_map<string, Scene*> SceneManager::scenes;


void SceneManager::AddToSceneList(const std::string& name, Scene* s)
{
	if (!s)
	{
		Logger::LogErrorAlways("Scene", "The scene that was passed in to be loaded is a nullptr.");
		return;
	}

	scenes[name] = s;
}

void SceneManager::RemoveFromSceneList(const std::string& name)
{
	if (!scenes[name])
	{
		Logger::LogErrorAlways("Scene", "No scene was found that is named " + name + '.');
		return;
	}

	scenes.erase(name);
}

void SceneManager::LoadScene(const std::string& name)
{
	if (!scenes[name])
	{
		Logger::LogErrorAlways("Scene", "No scene was found that is named " + name + '.');
		return;
	}

	if (scene != "")
	{
		ScriptEndEvent::Call();
		scenes[name]->OnSceneEnd();
	}

	scenes[name]->OnSceneStart();
	ScriptStartEvent::Call();
}

void SceneManager::LoadScene(const char* name)
{
	if (!scenes[name])
	{
		Logger::LogErrorAlways("Scene", "No scene was found that is named " + (string)name + '.');
		return;
	}

	if (scene != "")
	{
		ScriptEndEvent::Call();
		scenes[name]->OnSceneEnd();
	}

	scenes[name]->OnSceneStart();
	ScriptStartEvent::Call();
}

void SceneManager::UnloadScene()
{
	if (scene == "")
		return;

	scenes[scene]->OnSceneEnd();
	scene = "";
}
