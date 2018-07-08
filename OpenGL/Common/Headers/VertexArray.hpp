#ifndef _VERTEXARRAY_HPP_
#define _VERTEXARRAY_HPP_

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

class VertexArray {

	private:
		GLuint ID;

	public:
		VertexArray();

		GLuint getID();
		void deleteVertexArray();
};

#endif