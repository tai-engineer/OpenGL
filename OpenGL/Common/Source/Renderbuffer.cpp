#include "Renderbuffer.hpp"

Renderbuffer::Renderbuffer()
{
	glGenFramebuffers(1, &ID);
}

GLuint Renderbuffer::getID()
{
	return ID;
}

void Renderbuffer::deleteRenderbuffer()
{
	glDeleteRenderbuffers(1, &ID);
}