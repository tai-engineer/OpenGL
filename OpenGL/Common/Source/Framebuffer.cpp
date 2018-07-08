#include "Framebuffer.hpp"

Framebuffer::Framebuffer()
{
	glGenFramebuffers(1, &ID);
}

GLuint Framebuffer::getID()
{
	return ID;
}

void Framebuffer::deleteFramebuffer()
{
	glDeleteFramebuffers(1, &ID);
}