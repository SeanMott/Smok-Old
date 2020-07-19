#include <smpch.h>
#include "Application.h"

#include <Renderer\Display.h>
#include <Core\Events\EngineEvents.h>
#include <Core\ECS\EntityManager.h>
#include <Core\Input.h>

const float Application::FIXED_UPDATE_RATE = 60.0f;

//inits the application
void Application::Init(const unsigned int width, const int height, const std::string& name)
{
	DisplayI.Init(width, height, name);
	DisplayI.GetContext()->SetClearColor(0.0f, 0.5f, 0.5f);

	//links events needed for differnt parts of the engine
	Input::LinkEvents();

	//push layers default layer
	EntityManager::GetLayers().emplace_back("Default");
}

//destroys the application
void Application::Destroy()
{
	DisplayI.Destroy();
}

//runs the application
void Application::Run()
{
	while (DisplayI.IsRunning())
	{
		DisplayI.CalDeltaTime();

#ifndef SMOK_DIST
		if (Input::GetKey(Smok_KEY_ESCAPE))
			break;
#endif

		//update
		UpdateEvent::Call(DisplayI.GetDeltaTime());
		
		//fixed update
		FixedUpdateEvent::Call(FIXED_UPDATE_RATE);

		DisplayI.GetContext()->Clear(); //clears the screen

		//trigger systems
		ECSSystemEvent::Call(); //handles all systems except GUI based ones.
		//ECSGUISystemEvent::Call(); //allows GUI to be rendered and triggered over the scene.

		DisplayI.Update(); //swaps render buffers
	}
}