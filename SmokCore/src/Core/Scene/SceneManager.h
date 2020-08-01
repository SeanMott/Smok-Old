//defines the scene manager

#ifndef SceneManager_h
#define SceneManager_h

#include "Scene.h"

#include <string>
#include <unordered_map>

class SceneManager
{
	//vars
private:

	static std::string scene;

	static std::unordered_map<std::string, Scene*> scenes;

	//methods
public:

	//adds a scene to the scene list
	static void AddToSceneList(const std::string& name, Scene* s);
	//removes a scene from the scene list
	static void RemoveFromSceneList(const std::string& name);

	//loads a scene
	static void LoadScene(const std::string& name);
	//loads a scene
	static void LoadScene(const char* name);
	//unloads the current scene
	static void UnloadScene();

	//clears all scenes
	static inline void Clear() { scenes.clear(); }

	//gets the current scene
	static inline Scene* GetCurrentScene() { if (scene == "") return nullptr; return scenes[scene]; }
	//gets the current scene name
	static inline std::string GetCurrentSceneName() { return scene; }
};

#endif