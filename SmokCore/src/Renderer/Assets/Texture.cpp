#include <smpch.h>
#include "Texture.h"

#include <Renderer\RenderAPI\RenderAPI.h>
#include <Renderer\RenderAPI\Opengl\OpenglTexture.h>
//#include <Renderer\RenderAPI\Vulkin\VulkinTexture.h>
//#include <Renderer\RenderAPI\DirectX\DirectXTexture.h>
//#include <Renderer\RenderAPI\Metal\MetalTexture.h>

using namespace std;

//creates a texture
Texture* Texture::Create(const string& filePath)
{
	RenderAPIType type = RenderAPI::GetAPI();

	if (type == RenderAPIType::Vulkin)
	{
		Logger::LogError("Texture", "Vulkin is currently not supported, Opengl will be used.");
		//return new VulkinTexture(filePath);
		return new OpenglTexture(filePath);
	}

	else if (type == RenderAPIType::DirectX)
	{
		Logger::LogError("Texture", "DirectX is currently not supported, Opengl will be used.");
		//return new DirectXTexture(filePath);
		return new OpenglTexture(filePath);
	}

	else if (type == RenderAPIType::Metal)
	{
		Logger::LogError("Texture", "Metal is currently not supported, Opengl will be used.");
		//return new MetalTexture(filePath);
		return new OpenglTexture(filePath);
	}

	else
		return new OpenglTexture(filePath);
}