//defines Editor code for debug

#ifndef SMOK_DIST
#ifndef Editor_h
#define Editor_h

#include <Core\ECS\EntityManager.h>
#include <Core\ECS\Components\Transform.h>

class Editor
{
	//vars
private:

	static Entity selectedEntity;
	static Transform* selectedTrans;

	//methods
public:

	//inits the Editor
	static void Init();
	//shutsdown the Editor
	static void Shutdown();

	//draws the Editor
	static void Draw();

};

#endif
#endif