#include "Buffer.hpp"

Buffer::Buffer() 
{
	glGenBuffers(1, &ID);
}

GLuint Buffer::getID() 
{
	return ID;
}

void Buffer::deleteBuffer() 
{
	glDeleteBuffers(1, &ID);
}