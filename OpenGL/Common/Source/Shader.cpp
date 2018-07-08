#include "Shader.hpp"

Shader::Shader()
{
	;
}

Shader::Shader(const char* vsh, const char* fsh) 
{
	GLuint vShader;
	GLuint fShader;
	GLuint pShader;

	vShader = glCreateShader(GL_VERTEX_SHADER);
	fShader = glCreateShader(GL_FRAGMENT_SHADER);

	std::string str_vshader = readFromFile(vsh);
	std::string str_fshader = readFromFile(fsh);
	const char* vshaderCode = str_vshader.c_str();
	const char* fshaderCode = str_fshader.c_str();

	glShaderSource(vShader, 1, &vshaderCode, NULL);
	glShaderSource(fShader, 1, &fshaderCode, NULL);

	glCompileShader(vShader);
	if (!checkShader(vShader))
	{
		return;
	}

	glCompileShader(fShader);
	if (!checkShader(fShader))
	{
		return;
	}

	pShader = glCreateProgram();
	glAttachShader(pShader, vShader);
	glAttachShader(pShader, fShader);
	glLinkProgram(pShader);

	glDeleteShader(vShader);
	glDeleteShader(fShader);

	if (!checkProgram(pShader))
	{
		return;
	}
	ID = pShader;
}
std::string Shader::readFromFile(const char* path) 
{
	std::string str_shaderCode;
	std::ifstream shaderFile;
	std::stringstream shaderStream;
	try
	{
		shaderFile.open(path);
		shaderStream << shaderFile.rdbuf();
		shaderFile.close();

		str_shaderCode = shaderStream.str();
	}
	catch (std::ifstream::failure e)
	{
		printf("[ERROR] Cannot read shader file.");
	}

	return str_shaderCode;
}

void Shader::createShader(GLuint target, const char* path) 
{
	std::string str_shaderCode = readFromFile(path);
	const char* shaderCode = str_shaderCode.c_str();

	ID = glCreateShader(target);
	glShaderSource(ID, 1, &shaderCode, NULL);
}

void Shader::createProgram(GLuint vertex, GLuint fragment) 
{
	ID = glCreateProgram();
	glAttachShader(ID, vertex);
	glAttachShader(ID, fragment);
	glLinkProgram(ID);
}

void Shader::compile() 
{
	glCompileShader(ID);
	if (!checkShader(ID)) 
	{
		return;
	}
}

GLuint Shader::checkShader(GLuint sID) 
{
	int status = 0;
	char compileLog[512];

	glGetShaderiv(sID, GL_COMPILE_STATUS, &status);
	if (status != GL_TRUE) 
	{
		glGetShaderInfoLog(sID, 512, NULL, compileLog);
		printf("[ERROR] %s\n", compileLog);
		return GL_FALSE;
	}
	return GL_TRUE;
}

GLuint Shader::checkProgram(GLuint pID) 
{
	int success;
	char infoLog[512];

	glGetProgramiv(pID, GL_LINK_STATUS, &success);
	if (!success) 
	{
		glGetProgramInfoLog(pID, 512, NULL, infoLog);
		printf("[ERROR] %s\n", infoLog);
		return GL_FALSE;
	}
	return GL_TRUE;
}

GLuint Shader::getID() 
{
	return ID;
}

void Shader::use() 
{
	glUseProgram(ID);
}

void Shader::setBool(const std::string &name, bool value)
{
	glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
}

void Shader::setInt(const std::string &name, GLint value)
{
	glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
}

void Shader::setFloat(const std::string &name, GLfloat value)
{
	glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
}

void Shader::setVec2(const std::string &name, glm::vec2 &value)
{
	glUniform2fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]);
}
void Shader::setVec2(const std::string &name, GLfloat x, GLfloat y)
{
	glUniform2f(glGetUniformLocation(ID, name.c_str()), x, y);
}

void Shader::setVec3(const std::string &name, glm::vec3 &value)
{
	glUniform3fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]);
}

void Shader::setVec3(const std::string &name, GLfloat x, GLfloat y, GLfloat z)
{
	glUniform3f(glGetUniformLocation(ID, name.c_str()), x, y, z);
}

void Shader::setVec4(const std::string &name, glm::vec4 &value)
{
	glUniform4fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]);
}

void Shader::setVec4(const std::string &name, GLfloat x, GLfloat y, GLfloat z, GLfloat w)
{
	glUniform4f(glGetUniformLocation(ID, name.c_str()), x, y, z, w);
}

void Shader::setMat2(const std::string &name, glm::mat2 &value)
{
	glUniformMatrix2fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &value[0][0]);
}

void Shader::setMat3(const std::string &name, glm::mat3 &value)
{
	glUniformMatrix3fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &value[0][0]);
}

void Shader::setMat4(const std::string &name, glm::mat4 &value)
{
	glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &value[0][0]);
}

void Shader::deleteShader() 
{
	glDeleteShader(ID);
}

void Shader::deleteProgram() 
{
	glDeleteProgram(ID);
}