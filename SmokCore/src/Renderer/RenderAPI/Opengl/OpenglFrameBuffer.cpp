#include <smpch.h>
#include "OpenglFrameBuffer.h"

#include <glad\glad.h>

using namespace std;

//Constructor
OpenglFrameBuffer::OpenglFrameBuffer(const FrameBufferData& _data)
	:data(_data)
{
	Recreate(data.colorBufferIds.size(), data.depthBufferIds.size(), data.stencilBufferIds.size());
}

void OpenglFrameBuffer::Destroy()
{
	DestroyAllStencilBuffers();
	DestroyAllDepthBuffers();
	DestroyAllColorBuffers();

	glDeleteFramebuffers(1, &id);
}

void OpenglFrameBuffer::Bind()
{
	//glBindFramebuffer(GL_FRAMEBUFFER, id);
	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, id);
}

void OpenglFrameBuffer::Unbind()
{
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void OpenglFrameBuffer::Recreate(unsigned int colorBufferCount, unsigned int depthBufferCount, unsigned int stencilBufferCount)
{
	DestroyAllColorBuffers();
	DestroyAllDepthBuffers();
	DestroyAllStencilBuffers();

	glGenFramebuffers(1, &id);
	glBindFramebuffer(GL_FRAMEBUFFER, id);
	
	if (colorBufferCount == 0 && depthBufferCount == 0 && stencilBufferCount == 0)
	{
		CreateColorBuffer();
		CreateDepthBuffer();
		CreateStencilBuffer();
	}

	else
	{
		CreateColorBuffer(colorBufferCount);
		CreateDepthBuffer(depthBufferCount);
		CreateStencilBuffer(stencilBufferCount);
	}

	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		Logger::LogError("Frame Buffer Opengl", "Frame Buffer is incomplete");
}

void OpenglFrameBuffer::Recreate()
{
	DestroyAllColorBuffers();
	DestroyAllDepthBuffers();
	DestroyAllStencilBuffers();

	glGenFramebuffers(1, &id);
	glBindFramebuffer(GL_FRAMEBUFFER, id);
	CreateColorBuffer();
	CreateDepthBuffer();
	CreateStencilBuffer();

	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		Logger::LogError("Frame Buffer Opengl", "Frame Buffer is incomplete");
}

void OpenglFrameBuffer::CreateColorBuffer(unsigned int count)
{
	if (count == 0)
		return;

	for (unsigned int i = 0; i < count; i++)
	{
		data.colorBufferIds.emplace_back(0);
		const unsigned int pos = data.colorBufferIds.size() - 1;

		glGenTextures(1, &data.colorBufferIds[pos]);
		glBindTexture(GL_TEXTURE_2D, data.colorBufferIds[pos]);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB8, data.width, data.height, 0, GL_RGB, GL_UNSIGNED_BYTE, nullptr);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + pos, GL_TEXTURE_2D, data.colorBufferIds[pos], 0);
	}
}

void OpenglFrameBuffer::CreateDepthBuffer(unsigned int count)
{
	if (count == 0)
		return;

	for (unsigned int i = 0; i < count; i++)
	{
		data.depthBufferIds.emplace_back(0);
		const unsigned int pos = data.depthBufferIds.size() - 1;

		glGenTextures(1, &data.depthBufferIds[pos]);
		glBindTexture(GL_TEXTURE_2D, data.depthBufferIds[pos]);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH24_STENCIL8, data.width, data.height, 0, GL_DEPTH_STENCIL, GL_UNSIGNED_INT_24_8, nullptr);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_TEXTURE_2D, data.depthBufferIds[pos], 0);
	}
}

void OpenglFrameBuffer::CreateStencilBuffer(unsigned int count)
{
	if (count == 0)
		return;
}

void OpenglFrameBuffer::DestroyColorBuffer(unsigned int count)
{
	if (count == 0)
		return;
}

void OpenglFrameBuffer::DestroyDepthBuffer(unsigned int count)
{
}

void OpenglFrameBuffer::DestroyStencilBuffer(unsigned int count)
{
}

void OpenglFrameBuffer::DestroyAllColorBuffers()
{
}

void OpenglFrameBuffer::DestroyAllDepthBuffers()
{
}

void OpenglFrameBuffer::DestroyAllStencilBuffers()
{
}

unsigned int OpenglFrameBuffer::GetColorBufferId() const
{
	if (data.colorBufferIds.size() < 1)
	{
		Logger::LogError("Frame Buffer Opengl", "No Color Buffers are attachted");
		return (unsigned int)0;
	}

	return data.colorBufferIds[0];
}

unsigned int OpenglFrameBuffer::GetDepthBufferId() const
{
	if (data.depthBufferIds.size() < 1)
	{
		Logger::LogError("Frame Buffer Opengl", "No Depth Buffers are attachted");
		return (unsigned int)0;
	}

	return data.depthBufferIds[0];
}

unsigned int OpenglFrameBuffer::GetStencilBufferId() const
{
	if (data.stencilBufferIds.size() < 1)
	{
		Logger::LogError("Frame Buffer Opengl", "No Depth Buffers are attachted");
		return (unsigned int)0;
	}

	return data.stencilBufferIds[0];
}

vector<unsigned int>& OpenglFrameBuffer::GetAllColorBufferIds()
{
	return data.colorBufferIds;
}

vector<unsigned int>& OpenglFrameBuffer::GetAllDepthBufferIds()
{
	return data.depthBufferIds;
}

vector<unsigned int>& OpenglFrameBuffer::GetAllStencilBufferIds()
{
	return data.stencilBufferIds;
}