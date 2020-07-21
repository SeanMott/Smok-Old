#include <smpch.h>
#include "GraphicContext.h"

#include <Renderer\RenderAPI\RenderAPI.h>
#include <Renderer\RenderAPI\Opengl\OpenglGraphicContext.h>
//#include <Renderer\RenderAPI\DirectX\DirectXGraphicContext.h>
//#include <Renderer\RenderAPI\Vulkin\VulkinGraphicContext.h>
//#include <Renderer\RenderAPI\Metal\MetalGraphicContext.h>

//creates a graphic context
GraphicContext* GraphicContext::Create()
{
	RenderAPIType type = RenderAPI::GetAPI();

	if(type == RenderAPIType::Vulkin)
	{
		Logger::LogError("Graphic Context", "Vulkin is currently not supported, Opengl will be used.");
		//return new VulkinGraphicContext;
		return new OpenglGraphicContext;
	}

	else if(type == RenderAPIType::DirectX)
	{
		Logger::LogError("Graphic Context", "DirectX is currently not supported, Opengl will be used.");
		//return new DirectXGraphicContext;
		return new OpenglGraphicContext;
	}

	else if(type == RenderAPIType::Metal)
	{
		Logger::LogError("Graphic Context", "Metal is currently not supported, Opengl will be used.");
		//return new MetalGraphicContext;
		return new OpenglGraphicContext;
	}

	else
		return new OpenglGraphicContext;
}