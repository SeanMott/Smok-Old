//defines the scene manager

#ifndef SceneManager_h
#define SceneManager_h

#include "Scene.h"

class SceneManager
{
	//vars
private:
	static Scene* scene;

	//methods
public:

	//loads a scene
	static void LoadScene(Scene* s);
	//unloads the current scene
	static void UnloadScene();

	//gets the current scene
	static inline Scene* GetCurrentScene() { return scene; }

};

#endif