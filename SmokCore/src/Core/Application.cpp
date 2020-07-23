#include <smpch.h>
#include "Application.h"

#include <Renderer\Display.h>
#include <Core\Events\EngineEvents.h>
#include <Core\ECS\EntityManager.h>
#include <Core\Input.h>

//#include <future>

const float Application::FIXED_UPDATE_RATE = 60.0f;

FrameBuffer* Application::customeFrameBuffer = nullptr;

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
		if (Input::GetKey(SMOK_KEY_ESCAPE))
			break;
#endif
		
		if (customeFrameBuffer)
			customeFrameBuffer->Bind();

		DisplayI.GetContext()->Clear(); //clears the screen

		//update
		UpdateEvent::Call(DisplayI.GetDeltaTime() * 2);

		//fixed update
		FixedUpdateEvent::Call(FIXED_UPDATE_RATE);

		//trigger systems
		ECSSystemEvent::Call(); //handles all systems except GUI based ones.

		if (customeFrameBuffer)
			customeFrameBuffer->Unbind();

		//DisplayI.GetContext()->Clear();

		/*
		ECSRenderEvent::Call()

		Call() will also handle the frame buffers by assine them to the swap chain

		*/

		ECSGUIRenderEvent::Call(); //allows GUI to be rendered and triggered over the scene.

		//DisplayI.GetContext()->IndexBufferDrawCall(0, 6);
		//DisplayI.GetContext()->Clear();

		if (!DisplayI.IsRunning())
			break;

		DisplayI.Update(); //swaps render buffers

		//DisplayI.GetContext()->Clear();
	}
}