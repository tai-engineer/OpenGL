#ifndef _TEXTURE_HPP_
#define _TEXTURE_HPP_

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

#include <vector>

class Texture 
{

	private:
		GLuint ID;

	public:
		GLint width = 0;
		GLint height = 0;
		GLint channels = 0;

		Texture();

		GLuint getID();
		GLint getWidth();
		GLint getHeight();
		GLint getChannels();
		GLuint load(const char* file);
		GLuint loadCubeMap(std::vector<std::string> faces);
		void deleteTexture();
};

#endif