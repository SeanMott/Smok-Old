//defines a sprite component

#ifndef Sprite_h
#define Sprite_h

#include <Renderer\Assets\Texture.h>
#include <Renderer\Assets\Shader.h>

#include <glm.hpp>

#ifndef SMOK_DIST
#include <stdio.h>
#endif

struct Sprite
{
	Texture* texture = nullptr; //std::string texture = "";
	unsigned int textureSlot = 0;
	Shader* shader = nullptr; //std::string shader = "";

	glm::vec3 color = glm::vec3(0.0f);

	unsigned int layer = 0; //renders sprites from highest layer to lowest 12 to 0

	bool isActive = true;

#ifndef SMOK_DIST
	inline unsigned int PrintLayer() { std::printf("Sprite Layer: %i\n", layer); return layer; }
#endif
};

#endif