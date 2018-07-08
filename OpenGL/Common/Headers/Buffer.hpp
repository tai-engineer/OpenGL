#ifndef _BUFFER_HPP_
#define _BUFFER_HPP_

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

class Buffer {

	private:
		GLuint ID;

	public:
		Buffer();

		GLuint getID();
		void deleteBuffer();
};

#endif

