//base Texture

#ifndef Texture_h
#define Texture_h

#include <string>

class Texture
{
public:

	virtual ~Texture() {}

	//creates a texture
	static Texture* Create(const std::string& filePath);

	//destroys a texture
	virtual void Destroy() = 0;

	//binds a texture
	virtual void Bind(unsigned int slot = 0) = 0;
	//unbinds a texture
	virtual void UnBind() = 0;
};

#endif