#include <smpch.h>
#include "SpriteRenderer.h"

#include <Core\ECS\EntityManager.h>
#include <Core\ECS\Components\Transform.h>
#include "Smok2D\Components\OrthographicCamera.h"
#include "Smok2D\Components\Sprite.h"

#include <Renderer\Display.h>

#include <Renderer\BufferLayout.h>

#include <Core\Events\EngineEvents.h>

#include <gtc/matrix_transform.hpp>

using namespace glm; using namespace std;

Shader* SpriteRenderer::lastShader = nullptr;
Texture* SpriteRenderer::lastTexture = nullptr;

VertexBuffer* SpriteRenderer::spriteBuffer = nullptr;
IndexBuffer* SpriteRenderer::spriteIndexBuffer = nullptr;
bool SpriteRenderer::hasSentWarning = false;

GraphicContext* SpriteRenderer::context = nullptr;

//sets the sprite renderer and links it
void SpriteRenderer::Init()
{
#ifdef DISABLE_SMOK_2D
	return;
#endif

	context = DisplayI.GetContext();

	float vertices[] = {
	-0.5f, -0.5f, 0.0f,
	 0.5f, -0.5f, 0.0f,
	 0.5f,  0.5f, 0.0f,
	 -0.5f, 0.5f, 0.0f
	};

	unsigned int indices[] = {
		0, 1, 2, 
		2, 3, 0
	};

	BufferLayout layout = {
		{ShaderDataType::Float3, "Position"}
	};

	/*
	float vertices[] = {
		// pos      // tex
		0.0f, 1.0f, 0.0f, 1.0f,
		1.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 0.0f,

		0.0f, 1.0f, 0.0f, 1.0f,
		1.0f, 1.0f, 1.0f, 1.0f,
		1.0f, 0.0f, 1.0f, 0.0f
	};

	BufferLayout layout = {
		{ShaderDataType::Float2, "Position"},
		{ShaderDataType::Float2, "texCoords"}
	};
	*/

	spriteBuffer = VertexBuffer::Create(vertices, sizeof(vertices));
	spriteBuffer->SetLayout(layout);
	spriteIndexBuffer = IndexBuffer::Create(indices, sizeof(indices));

	ECSSystemEvent::AddMethod(&SpriteRenderer::Render);
}

//shuts down the sprite renderer
void SpriteRenderer::Shutdown()
{
	if(spriteBuffer)
		spriteBuffer->Destroy();
	if (spriteIndexBuffer)
		spriteIndexBuffer->Destroy();

	//remove Render from the system event call
}

//renders all the sprites
void SpriteRenderer::Render()
{
	mat4 model = mat4(1.0f);
	mat4 projection = mat4(1.0f);
	mat4 view = mat4(1.0f);

	if (hasSentWarning)
		return;

	if (!spriteBuffer && !hasSentWarning)
	{
		LogError("Sprite Renderer", "Sprite Buffer was not initialised properly, make sure DISABLE_SMOK_2D was not defined and or project settings enable Smok 2D.");
		hasSentWarning = true;
		return;
	}

	if (!spriteIndexBuffer && !hasSentWarning)
	{
		LogError("Sprite Renderer", "Sprite Index Buffer was not initialised properly, make sure DISABLE_SMOK_2D was not defined and or project settings enable Smok 2D.");
		hasSentWarning = true;
		return;
	}

	spriteBuffer->Bind();
	spriteIndexBuffer->Bind();

	//gets camera
	auto c = EntityManager::GetReg().view<OrthographicCamera, Transform>();
	if (c.size() < 1)
	{
		LogError("Sprite Renderer", "No Orhtographic Camera components were found, at least put one but make it inactive if you don't want it.");
		hasSentWarning = true;
		return;
	}

	for (auto cam : c)
	{
		auto& camera = c.get<OrthographicCamera>(cam);
		if (!camera.isActive)
			continue;

		//auto& trans = c.get<Transform>(cam);

		projection = ortho(0.0f, camera.viewLength, camera.viewHeight, 0.0f, -1.0f, 1.0f);
		//handle position later
	}

	//render entities
	auto entities = EntityManager::GetReg().view<Sprite, Transform>();

	for (auto entity : entities)
	{
		auto& sprite = entities.get<Sprite>(entity);
		if (!sprite.isActive)
			continue;
		auto& trans = entities.get<Transform>(entity);

		if (lastShader != sprite.shader)
		{
			lastShader = sprite.shader;
			if (lastShader == nullptr)
			{
				LogMessage("Not all entites with a active Sprite component has a shader assigned.");
				continue;
			}

			lastShader->Bind();
		}

		if (lastTexture != sprite.texture)
		{
			lastTexture = sprite.texture;
			if (lastTexture == nullptr)
			{
				LogMessage("Not all entites with a active Sprite component has a texture assigned.");
				continue;
			}

			lastTexture->Bind(sprite.textureSlot);
		}

		//cal transform
		model = translate(model, trans.position) *
			rotate(model, radians(trans.rotation.x), vec3(0.0f, 0.0f, 1.0f)) *
			scale(model, trans.scale * 50.0f);

		lastShader->SetMatrix4("PVM", projection * model);

		//draw call
		context->IndexBufferDrawCall(0, spriteIndexBuffer->GetCount());
	}

	/*
	auto entities = EntityManager::GetReg().view<Sprite, Transform>();

	spriteBuffer->Bind();

	for (auto entity : entities)
	{
		auto& sprite = entities.get<Sprite>(entity);
		if (!sprite.isActive)
			continue;
		auto& trans = entities.get<Transform>(entity);

		//check if shader is already bound
		if (lastShader != sprite.shader)
		{
			lastShader = sprite.shader;
			if (lastShader == nullptr)
			{
				LogMessage("Not all entites with a active Sprite component has a shader assigned.");
				continue;
			}

			lastShader->Bind();
		}


		//check if texture is already bound
		if (lastTexture != sprite.texture)
		{
			lastTexture = sprite.texture;
			if (lastTexture == nullptr)
			{
				LogMessage("Not all entites with a active Sprite component has a texture assigned.");
				continue;
			}

			lastTexture->Bind(sprite.textureSlot);
			if (lastShader)
				lastShader->SetInt("Sprite", sprite.textureSlot);
		}

		model = mat4(1.0);

		model = translate(model, trans.position);
		model = translate(model, vec3(0.5f * trans.scale.x, 0.5f * trans.scale.y, trans.scale.z));
		model = rotate(model, radians(trans.rotation.x), vec3(0.0f, 0.0f, 1.0f));
		model = translate(model, glm::vec3(-0.5f * trans.scale.x, -0.5f * trans.scale.y, trans.scale.z));
		model = scale(model, trans.scale);

		lastShader->SetMatrix4("PVM", mat4(projection /* cam.view * model));

		//draw call
		glDrawArrays(GL_TRIANGLES, 0, 6);
		
	}
	*/
}

	/*

	----Note----
	add batch rendering later
	----Note----

	*/