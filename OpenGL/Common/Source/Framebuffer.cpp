#include "FrameBuffer.hpp"

FrameBuffer::FrameBuffer()
{
	glGenFramebuffers(1, &ID);
}

GLuint FrameBuffer::getID()
{
	return ID;
}

void FrameBuffer::deleteFramebuffer()
{
	glDeleteFramebuffers(1, &ID);
}