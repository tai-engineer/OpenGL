#ifndef _TRANSFORM_FEEDBACK_H_
#define _TRANSFORM_FEEDBACK_H_

#define GLEW_STATIC
#include <GL/glew.h> // include GLEW and new version of GL on Windows
#include <GLFW/glfw3.h> // GLFW helper library
#include <stdio.h>

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

/* User define class*/
#include "Shader.hpp"
#include "Texture.hpp"
#include "Buffer.hpp"
#include "VertexArray.hpp"
#include "Camera.hpp"

GLFWwindow* window;
GLuint windowHeight = 800;
GLuint windowWidth = 600;

void init_window(const char* name, GLuint major, GLuint minnor, GLuint width, GLuint height);
void get_version();
void _update_fps_counter(GLFWwindow* window);
#endif
