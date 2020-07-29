
#include <Core\Application.h>
#include <Core\AssetManager.h>
#include <Core\ECS\EntityManager.h>
#include <Core\Logger.h>

#ifndef SMOK_DIST
#include <iostream>
#endif

using namespace std;

const unsigned int SCREEN_WIDTH = 800, SCREEN_HEIGHT = 800;

int main(int args, char* argv[]) //use EntryPoint in other apps for multiplatform
{
	//inits app
	Application::Init(SCREEN_WIDTH, SCREEN_HEIGHT);

	//load assets

	//link Systems

	//load scene

	//game loop
	Application::Run();

	//clean up Entities
	EntityManager::DestroyAllEntitiesIndependent();

	//clean up assets
	AssetManager::DestroyAllAssets();

	//clean up Systems

	//clean up app
	Application::Destroy();

#ifndef SMOK_DIST
	cin.get();
#endif
	return 0;
}