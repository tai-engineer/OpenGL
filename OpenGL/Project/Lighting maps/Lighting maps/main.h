#ifndef _MAIN_H_
#define _MAIN_H_

#define GLEW_STATIC
#include <GL/glew.h> // include GLEW and new version of GL on Windows
#include <GLFW/glfw3.h> // GLFW helper library
#include <stdio.h>

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

/* User define class*/
#include "Shader.hpp"
#include "Buffer.hpp"
#include "VertexArray.hpp"
#include "Texture.hpp"
#include "Camera.hpp"

#define D_WIDTH		1024
#define D_HEIGHT	1280

GLFWwindow* init_window(const char* name, GLuint major, GLuint minnor, GLuint width, GLuint height);
void init_camera(Camera* objCamera, Camera* lampCamera);

#endif
