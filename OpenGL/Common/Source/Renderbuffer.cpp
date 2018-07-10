#include "RenderBuffer.hpp"

RenderBuffer::RenderBuffer()
{
	glGenFramebuffers(1, &ID);
}

GLuint RenderBuffer::getID()
{
	return ID;
}

void RenderBuffer::deleteRenderBuffer()
{
	glDeleteRenderbuffers(1, &ID);
}