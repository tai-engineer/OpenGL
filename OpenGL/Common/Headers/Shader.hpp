#ifndef _SHADER_HPP_
#define _SHADER_HPP_

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

class Shader 
{
	private:
		GLuint ID;

		std::string readFromFile(const char* path);
		GLuint Shader::checkShader(GLuint sID);
		GLuint checkProgram(GLuint pID);

	public:
		/* Constructor */
		Shader();
		Shader(const char* vsh, const char* fsh);

		void createShader(GLuint target, const char* path);
		void createProgram(GLuint, GLuint);
		void compile();
		GLuint getID();
		void use();

		void setBool(const std::string &name, bool value);
		void setInt(const std::string &name, GLint value);
		void setFloat(const std::string &name, GLfloat value);
		void setVec2(const std::string &name, glm::vec2 &value);
		void setVec2(const std::string &name, GLfloat x, GLfloat y);
		void setVec3(const std::string &name, glm::vec3 &value);
		void setVec3(const std::string &name, GLfloat x, GLfloat y, GLfloat z);
		void setVec4(const std::string &name, glm::vec4 &value);
		void setVec4(const std::string &name, GLfloat x, GLfloat y, GLfloat z, GLfloat w);
		void setMat2(const std::string &name, glm::mat2 &value);
		void setMat3(const std::string &name, glm::mat3 &value);
		void setMat4(const std::string &name, glm::mat4 &value);

		void deleteShader();
		void deleteProgram();
};

#endif