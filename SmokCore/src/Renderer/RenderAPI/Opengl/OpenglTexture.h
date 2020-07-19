//opengl implementation of texture

#ifndef OpenglTexture_h
#define OpenglTexture_h

#include <Renderer\Assets\Texture.h>
#include <glad\glad.h>

class OpenglTexture : public Texture
{
	//vars
private:

	unsigned int id;
	int width, height, nrChannels;

	//methods
public:

	//Constructor
	OpenglTexture(const std::string& filePath);

	virtual ~OpenglTexture() { Destroy(); }

	// Inherited via Texture
	inline void Destroy() override { glDeleteTextures(1, &id); }
	void Bind(unsigned int slot = 0) override;
	inline void UnBind() override { glBindTexture(GL_TEXTURE_2D, 0); }
};

#endif