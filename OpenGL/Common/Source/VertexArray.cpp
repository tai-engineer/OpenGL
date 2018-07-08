#include "VertexArray.hpp"

VertexArray::VertexArray() {
	glGenVertexArrays(1, &ID);
}

GLuint VertexArray::getID() {
	return ID;
}

void VertexArray::deleteVertexArray() {
	glDeleteVertexArrays(1, &ID);
}
