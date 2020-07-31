//defines the scene manager

#ifndef SceneManager_h
#define SceneManager_h

#include "Scene.h"

#include <vector>

class SceneManager
{
	//vars
private:

	static unsigned int scene;

	static std::vector<Scene*> scenes;

	//methods
public:

	//adds a scene to the scene list
	static void AddToSceneList(Scene* s);
	//removes a scene from the scene list
	static void RemoveFromSceneList(Scene* s);

	//loads a scene
	static void LoadScene(Scene* s);
	//loads a scene
	static void LoadScene(unsigned int s);
	//unloads the current scene
	static void UnloadScene();

	//clears all scenes
	static inline void Clear() { scenes.clear(); }

	//gets the current scene
	static inline Scene* GetCurrentScene() { return scenes[scene]; }

};

#endif