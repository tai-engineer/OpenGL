#ifndef _MAIN_H_
#define _MAIN_H_

#define GLEW_STATIC
#include <GL/glew.h> // include GLEW and new version of GL on Windows
#include <GLFW/glfw3.h> // GLFW helper library
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "RenderToTexture.hpp"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouseMoverment(double xoffset, double yoffset);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void mouseScroll(double yoffset);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);

void createWindow(GLFWwindow*& win, const char* name, unsigned int major, unsigned int minnor, unsigned int width, unsigned int height);
void processInput(GLFWwindow *window, Camera* camera, float deltaTime);
#endif
