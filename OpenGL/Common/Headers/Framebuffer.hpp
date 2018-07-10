#ifndef _FRAMEBUFFER_HPP_
#define _FRAMEBUFFER_HPP_

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

class FrameBuffer
{
private:
	GLuint ID;

public:
	FrameBuffer();
	GLuint getID();
	void deleteFramebuffer();
};
#endif // !_FRAMEBUFFER_HPP_

