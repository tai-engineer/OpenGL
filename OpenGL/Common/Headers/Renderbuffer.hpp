#ifndef _RENDERBUFFER_HPP_
#define _RENDERBUFFER_HPP_

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

class Renderbuffer
{
private:
	GLuint ID;

public:
	Renderbuffer();
	GLuint getID();
	void deleteRenderbuffer();
};
#endif // !_RENDERBUFFER_HPP_

