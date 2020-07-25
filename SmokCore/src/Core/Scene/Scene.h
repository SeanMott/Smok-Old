//defines a scene

#ifndef Scene_h
#define Scene_h

class Scene
{
	//methods
public:

	virtual ~Scene() {}

	//when the scene is loaded
	virtual void OnSceneStart() = 0;
	//when the scene is unloaded
	virtual void OnSceneEnd() = 0;
};

#endif